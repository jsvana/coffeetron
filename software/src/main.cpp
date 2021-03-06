#include <Arduino.h>

#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <HX711.h>
#include <PID_v2.h>
#include <SPI.h>
#include <Wire.h>

#include "constants.h"
#include "util.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
HX711 scale;

// Calibrated to my specific scale, YMMV
float calibration_factor = 416.0;

int desired_weight_in_grams;
int desired_pump_temperature;
// TODO: handle underflow
unsigned long desired_preinfuse_pump_time_in_milliseconds;
unsigned long desired_preinfuse_wait_time_in_milliseconds;

bool preinfusion_enabled;

unsigned long state_start_millis = 0;

unsigned long heater_window_start = 0;
unsigned short last_report_window = 0;
unsigned short last_brew_report_window = 0;

bool has_most_recent_pour = false;
unsigned short last_pour_seconds;
float last_pour_weight;

Encoder encoder(3, 4);
Bounce brew_button;
Bounce flush_button;
Bounce encoder_button;
Bounce stats_button;

PID_v2 heater_pid(PID_KP, PID_KI, PID_KD, PID::Direct);

DynamicJsonDocument doc(1024);

enum State {
  Waiting,

  ConfigurePumpTemp,
  ConfigureWeight,
  ConfigurePreinfuseEnabled,
  ConfigurePreinfusePumpTime,
  ConfigurePreinfuseWaitTime,

  Preinfusing,
  WaitingAfterPreinfusing,
  Brewing,

  Flushing,

  BrewStats,

  Error,
};

State current_state;

Temps<5, A0, A1> temps;

State (*tick_func)();

void set_temp_led(float reading) {
  if (abs(reading - desired_pump_temperature) < ACCEPTABLE_TEMP_ERROR) {
    digitalWrite(TEMP_OK_LED, HIGH);
  } else {
    digitalWrite(TEMP_OK_LED, LOW);
  }
}

void display_temps() {
  display.setTextSize(1);

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println(F("ERR"));
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println(F("ERR"));
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }
}

void display_coffee_image() {
  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);
}

void send_preinfusion_start_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "preinfusion_start";
  serializeJson(doc, Serial);
  Serial.println();
}

void send_preinfusion_done_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "preinfusion_end";
  serializeJson(doc, Serial);
  Serial.println();
}

void send_brew_start_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "brew_start";
  serializeJson(doc, Serial);
  Serial.println();
}

void send_brew_done_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "brew_end";
  doc["total_seconds"] = last_pour_seconds;
  doc["total_weight"] = last_pour_weight;
  doc["preinfusion_pump_time_millis"] =
      desired_preinfuse_pump_time_in_milliseconds;
  doc["preinfusion_wait_time_millis"] =
      desired_preinfuse_wait_time_in_milliseconds;
  serializeJson(doc, Serial);
  Serial.println();
}

void send_flush_start_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "flush_start";
  serializeJson(doc, Serial);
  Serial.println();
}

void send_flush_done_event() {
  doc.clear();

  doc["type"] = "event";
  doc["event"] = "flush_end";
  serializeJson(doc, Serial);
  Serial.println();
}

State waiting_tick() {
  brew_button.update();
  flush_button.update();
  encoder_button.update();
  stats_button.update();

  State next_state;
  if (brew_button.fell()) {
    scale.tare();

    if (preinfusion_enabled) {
      next_state = State::Preinfusing;
      send_preinfusion_start_event();
    } else {
      next_state = State::Brewing;
      send_brew_start_event();
    }
  } else if (flush_button.fell()) {
    next_state = State::Flushing;
    send_flush_start_event();
  } else if (encoder_button.fell()) {
    encoder.write(desired_pump_temperature * 4);
    next_state = State::ConfigurePumpTemp;
  } else if (stats_button.fell()) {
    next_state = State::BrewStats;
  } else {
    next_state = State::Waiting;
  }

  pump_off();

  display.setTextSize(2);

  display.println(F("Coffeetron"));

  display_temps();

  display_coffee_image();

  return next_state;
}

State configure_pump_temp_tick() {
  desired_pump_temperature = encoder.read() / 4;

  heater_pid.Setpoint(desired_pump_temperature);

  if (desired_pump_temperature < 1) {
    desired_pump_temperature = 1;
    encoder.write(4);
  }

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    encoder.write(desired_weight_in_grams * 4);
    next_state = State::ConfigureWeight;
  } else {
    next_state = State::ConfigurePumpTemp;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Set target pump temp"));

  display.print(desired_pump_temperature);
  display.println(F(" degF"));

  display_coffee_image();

  return next_state;
}

State configure_weight_tick() {
  desired_weight_in_grams = encoder.read() / 4;

  if (desired_weight_in_grams < 1) {
    desired_weight_in_grams = 1;
    encoder.write(4);
  }

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    encoder.write(preinfusion_enabled ? 4 : 0);
    next_state = State::ConfigurePreinfuseEnabled;
  } else {
    next_state = State::ConfigureWeight;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Set target weight"));

  display.print(desired_weight_in_grams);
  display.println(F("g"));

  display_coffee_image();

  return next_state;
}

State configure_preinfuse_enabled_tick() {
  auto encoder_value = encoder.read() / 4;

  if (encoder_value < 0) {
    encoder_value = 1;
    encoder.write(4);
  }

  preinfusion_enabled = encoder_value % 2 == 1;

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    if (preinfusion_enabled) {
      encoder.write(desired_preinfuse_pump_time_in_milliseconds * 4 / 1000);
      next_state = State::ConfigurePreinfusePumpTime;
    } else {
      next_state = State::Waiting;
    }
  } else {
    next_state = State::ConfigurePreinfuseEnabled;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Enable preinfusion?"));

  display.print(preinfusion_enabled ? "yes" : "no");

  display_coffee_image();

  return next_state;
}

State configure_preinfuse_pump_time_tick() {
  auto encoder_value = encoder.read() / 4;

  if (encoder_value < 0) {
    encoder_value = 0;
    encoder.write(0);
  }

  desired_preinfuse_pump_time_in_milliseconds = encoder_value * 1000;

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    encoder.write(desired_preinfuse_wait_time_in_milliseconds * 4 / 1000);
    next_state = State::ConfigurePreinfuseWaitTime;
  } else {
    next_state = State::ConfigurePreinfusePumpTime;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Set preinfuse pump time"));

  display.print(desired_preinfuse_pump_time_in_milliseconds / 1000);
  display.println(F("s"));

  display_coffee_image();

  return next_state;
}

State configure_preinfuse_wait_time_tick() {
  auto encoder_value = encoder.read() / 4;

  if (encoder_value < 0) {
    encoder_value = 0;
    encoder.write(0);
  }

  desired_preinfuse_wait_time_in_milliseconds = encoder_value * 1000;

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    next_state = State::Waiting;
  } else {
    next_state = State::ConfigurePreinfuseWaitTime;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Set preinfuse wait time"));

  display.print(desired_preinfuse_wait_time_in_milliseconds / 1000);
  display.println(F("s"));

  display_coffee_image();

  return next_state;
}

State preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > desired_preinfuse_pump_time_in_milliseconds) {
    next_state = State::WaitingAfterPreinfusing;
    send_preinfusion_done_event();
  } else {
    next_state = State::Preinfusing;
  }

  pump_on();

  display.setTextSize(2);

  display.println(F("Infusing"));

  display.setTextSize(1);

  display.println(F("Pumping"));
  display.print((state_start_millis +
                 desired_preinfuse_pump_time_in_milliseconds - now + 500) /
                1000);
  display.println(F("s remaining"));

  display.println(F(""));

  display_temps();

  return next_state;
}

State waiting_after_preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > desired_preinfuse_wait_time_in_milliseconds) {
    next_state = State::Brewing;
    send_brew_start_event();
  } else {
    next_state = State::WaitingAfterPreinfusing;
  }

  pump_off();

  display.setTextSize(2);

  display.println(F("Infusing"));

  display.setTextSize(1);

  display.println(F("Waiting"));
  display.print((state_start_millis +
                 desired_preinfuse_wait_time_in_milliseconds - now + 500) /
                1000);
  display.println(F("s remaining"));

  display.println(F(""));

  display_temps();

  return next_state;
}

State brewing_tick() {
  const auto now = millis();

  // Note that this is very slow
  const auto weight = scale.get_units();

  const unsigned short current_brew_report_window = now / 1000;
  if (current_brew_report_window != last_brew_report_window) {
    last_brew_report_window = current_brew_report_window;
    doc.clear();

    doc["type"] = "brew";
    doc["weight"] = weight;
    doc["target_weight"] = desired_weight_in_grams;
    serializeJson(doc, Serial);
    Serial.println();
  }

  State next_state;

  if (weight > desired_weight_in_grams) {
    scale.tare();

    last_pour_seconds = (now - state_start_millis) / 1000;
    last_pour_weight = weight;

    has_most_recent_pour = true;

    send_brew_done_event();

    next_state = State::Waiting;
  } else {
    next_state = State::Brewing;
  }

  pump_on();

  display.setTextSize(2);

  display.println(F("Brewing..."));

  display.setTextSize(1);

  display.print(F("Target weight: "));
  display.print(desired_weight_in_grams);
  display.println(F("g"));

  display.print(F("Weight: "));
  display.print(weight);
  display.println(F("g"));

  display.print(F("Elapsed: "));
  display.print((now - state_start_millis) / 1000);
  display.println(F("s"));

  display_temps();

  return next_state;
}

State flushing_tick() {
  State next_state;
  if (millis() - state_start_millis > FLUSH_TIME_MILLIS) {
    send_flush_done_event();

    next_state = State::Waiting;
  } else {
    next_state = State::Flushing;
  }

  pump_on();

  display.setTextSize(2);

  display.println(F("Flushing"));

  display.setTextSize(1);

  display_temps();

  display_coffee_image();

  return next_state;
}

State brew_stats_tick() {
  stats_button.update();

  State next_state;
  if (stats_button.fell()) {
    next_state = State::Waiting;
  } else {
    next_state = State::BrewStats;
  }

  pump_off();

  display.setTextSize(1);

  display.println(F("Brew stats"));

  if (has_most_recent_pour) {
    display.println(F("Most recent pour:"));
    display.print(F(" Total time: "));
    display.print(last_pour_seconds);
    display.println(F("s"));
    display.print(F(" Total weight: "));
    display.print(last_pour_weight);
    display.println(F("g"));
  } else {
    display.println(F("No pour found"));
  }

  display_coffee_image();

  return next_state;
}

State error_tick() {
  display.setTextSize(2);

  display.println(F("ERROR"));

  display.setTextSize(1);
  display.print(F("Unknown state \""));
  display.print(current_state);
  display.println(F("\""));

  return State::Error;
}

void set_new_state(const State &state) {
  state_start_millis = millis();
  current_state = state;

  switch (state) {
  case State::Waiting:
    tick_func = &waiting_tick;
    break;

  case State::ConfigurePumpTemp:
    tick_func = &configure_pump_temp_tick;
    break;

  case State::ConfigureWeight:
    tick_func = &configure_weight_tick;
    break;

  case State::ConfigurePreinfuseEnabled:
    tick_func = &configure_preinfuse_enabled_tick;
    break;

  case State::ConfigurePreinfusePumpTime:
    tick_func = &configure_preinfuse_pump_time_tick;
    break;

  case State::ConfigurePreinfuseWaitTime:
    tick_func = &configure_preinfuse_wait_time_tick;
    break;

  case State::Flushing:
    tick_func = &flushing_tick;
    break;

  case State::Preinfusing:
    tick_func = &preinfusing_tick;
    break;

  case State::WaitingAfterPreinfusing:
    tick_func = &waiting_after_preinfusing_tick;
    break;

  case State::Brewing:
    tick_func = &brewing_tick;
    break;

  case State::BrewStats:
    tick_func = &brew_stats_tick;
    break;

  case State::Error:
  default:
    tick_func = &error_tick;
    break;
  }
}

void heater_relay_off() { digitalWrite(HEATER_RELAY, LOW); }

void heater_relay_on() { digitalWrite(HEATER_RELAY, HIGH); }

void setup() {
  pinMode(TEMP_OK_LED, OUTPUT);

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to initialize OLED display"));
    digitalWrite(TEMP_OK_LED, HIGH);
    for (;;)
      ; // Don't proceed, loop forever
  }

  scale.begin(HX711_DOUT, HX711_CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
  digitalWrite(TEMP_OK_LED, HIGH);

  encoder_button.attach(2, INPUT_PULLUP);
  encoder_button.interval(25);

  flush_button.attach(7, INPUT_PULLUP);
  flush_button.interval(25);

  brew_button.attach(8, INPUT_PULLUP);
  brew_button.interval(25);

  stats_button.attach(9, INPUT_PULLUP);
  stats_button.interval(25);

  // blue white == A0 == pump temp
  // blue == A1 == grouphead temp
  // brown white == GND
  // brown == VCC
  // orange white == pump relay

  pinMode(PUMP, OUTPUT);
  pinMode(HEATER_RELAY, OUTPUT);
  // pinMode(TEMP_OK_LED, OUTPUT);

  digitalWrite(PUMP, LOW);
  digitalWrite(HEATER_RELAY, LOW);
  // digitalWrite(TEMP_OK_LED, LOW);
  digitalWrite(TEMP_OK_LED, HIGH);

  desired_pump_temperature = INITIAL_DESIRED_PUMP_TEMPERATURE;
  desired_weight_in_grams = INITIAL_DESIRED_WEIGHT_GRAMS;
  desired_preinfuse_pump_time_in_milliseconds =
      INITIAL_DESIRED_PREINFUSE_PUMP_TIME_MILLISECONDS;
  desired_preinfuse_wait_time_in_milliseconds =
      INITIAL_DESIRED_PREINFUSE_WAIT_TIME_MILLISECONDS;

  heater_pid.SetOutputLimits(0, HEATER_PID_WINDOW_SIZE);

  while (true) {
    temps.update_samples_blocking();

    const auto reading = temps.average_pump_temperature();
    if (reading.is_error()) {
      heater_relay_off();
      continue;
    }

    heater_pid.SetOutputLimits(0, HEATER_PID_WINDOW_SIZE);
    heater_pid.Start(reading.reading(), 0, desired_pump_temperature);

    break;
  }

  preinfusion_enabled = true;

  set_new_state(State::Waiting);

  display.clearDisplay();
  display.display();
}

void control_heater_relay() {
  // Disable heater while pulling a shot
  if (current_state == State::Brewing) {
    heater_relay_off();
    return;
  }

  const auto reading = temps.average_pump_temperature();
  if (reading.is_error()) {
    heater_relay_off();
    return;
  }

  const auto temp = reading.reading();

  set_temp_led(temp);

  const auto heater_runtime = heater_pid.Run(temp);
  const auto now = millis();

  if (now - heater_window_start > HEATER_PID_WINDOW_SIZE) {
    heater_window_start += HEATER_PID_WINDOW_SIZE;
  }

  if (heater_runtime < now - heater_window_start) {
    heater_relay_off();
  } else {
    heater_relay_on();
  }
}

const __FlashStringHelper *state_as_string(const State &state) {
  switch (state) {
  case State::Waiting:
    return F("waiting");

  case State::ConfigurePumpTemp:
    return F("configure_pump_temp");

  case State::ConfigureWeight:
    return F("configure_weight");

  case State::ConfigurePreinfuseEnabled:
    return F("configure_preinfuse_enabled");

  case State::ConfigurePreinfusePumpTime:
    return F("configure_preinfuse_pump_time");

  case State::ConfigurePreinfuseWaitTime:
    return F("configure_preinfuse_wait_time");

  case State::Flushing:
    return F("flushing");

  case State::Preinfusing:
    return F("preinfusing");

  case State::WaitingAfterPreinfusing:
    return F("waiting_after_preinfusing");

  case State::Brewing:
    return F("brewing");

  case State::BrewStats:
    return F("brew_stats");

  case State::Error:
  default:
    return F("error");
  }
}

void report_stats() {
  const auto boiler_reading = temps.average_pump_temperature();
  bool boiler_temp_error = false;
  if (boiler_reading.is_error()) {
    boiler_temp_error = true;
  }

  const auto boiler_temp = boiler_reading.reading();

  const auto grouphead_reading = temps.average_grouphead_temperature();
  bool grouphead_temp_error = false;
  if (grouphead_reading.is_error()) {
    grouphead_temp_error = true;
  }

  const auto grouphead_temp = grouphead_reading.reading();

  const auto now = millis();

  const unsigned short current_report_window = now / 1000;
  if (current_report_window != last_report_window) {
    last_report_window = current_report_window;
    doc.clear();

    doc["type"] = "temp";
    doc["boiler_temp_err"] = boiler_temp_error;
    doc["boiler_temp"] = boiler_temp;
    doc["target_boiler_temp"] = desired_pump_temperature;
    doc["grouphead_temp_err"] = grouphead_temp_error;
    doc["grouphead_temp"] = grouphead_temp;
    doc["state"] = state_as_string(current_state);
    serializeJson(doc, Serial);
    Serial.println();
  }
}

void loop() {
  temps.update_samples_blocking();

  control_heater_relay();

  report_stats();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  State new_state = tick_func();

  if (current_state != new_state) {
    set_new_state(new_state);
  }

  display.display();
}
