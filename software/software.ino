#include <Adafruit_SSD1306.h>
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
float calibration_factor = 416;

int desired_weight_in_grams;
int desired_pump_temperature;
int desired_preinfuse_pump_time_in_milliseconds;
int desired_preinfuse_wait_time_in_milliseconds;

bool preinfusion_enabled;

unsigned long state_start_millis = 0;

bool has_most_recent_pour = false;
unsigned long last_pour_seconds;
float last_pour_weight;

Encoder encoder(2, 3);
Bounce brew_button;
Bounce flush_button;
Bounce encoder_button;
Bounce stats_button;

double Kp = 4.5;
double Ki = 0.175;
double Kd = 0.4;

PID_v2 heater_pid(Kp, Ki, Kd, PID::Direct);

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

Temps<5> temps{A0, A1};

State (*tick_func)();

void set_temp_led(float reading) {
  if (abs(reading - desired_pump_temperature) < ACCEPTABLE_TEMP_ERROR) {
    digitalWrite(TEMP_OK_LED, HIGH);
  } else {
    digitalWrite(TEMP_OK_LED, LOW);
  }
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
    } else {
      next_state = State::Brewing;
    }
  } else if (flush_button.fell()) {
    next_state = State::Flushing;
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

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

  return next_state;
}

State preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > desired_preinfuse_pump_time_in_milliseconds) {
    next_state = State::WaitingAfterPreinfusing;
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

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }

  return next_state;
}

State waiting_after_preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > desired_preinfuse_wait_time_in_milliseconds) {
    next_state = State::Brewing;
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

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }

  return next_state;
}

State brewing_tick() {
  const auto now = millis();

  // Note that this is very slow
  const auto weight = scale.get_units();

  State next_state;

  if (weight > desired_weight_in_grams) {
    scale.tare();

    last_pour_seconds = (now - state_start_millis) / 1000;
    last_pour_weight = weight;

    has_most_recent_pour = true;

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

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }

  return next_state;
}

State flushing_tick() {
  State next_state;
  if (millis() - state_start_millis > FLUSH_TIME_MILLIS) {
    next_state = State::Waiting;
  } else {
    next_state = State::Flushing;
  }

  pump_on();

  display.setTextSize(2);

  display.println(F("Flushing"));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  const auto pump_reading = temps.average_pump_temperature();
  if (pump_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(pump_reading.reading());
    display.println(F("F"));
  }
  display.print(F("GH temp: "));
  const auto grouphead_reading = temps.average_grouphead_temperature();
  if (grouphead_reading.is_error()) {
    display.println("ERR");
  } else {
    display.print(grouphead_reading.reading());
    display.println(F("F"));
  }

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

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
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("failed to initialize OLED display");
    for (;;)
      ; // Don't proceed, loop forever
  }

  scale.begin(HX711_DOUT, HX711_CLK);
  scale.set_scale(calibration_factor);
  scale.tare();

  brew_button.attach(4, INPUT_PULLUP);
  brew_button.interval(25);

  flush_button.attach(7, INPUT_PULLUP);
  flush_button.interval(25);

  encoder_button.attach(10, INPUT_PULLUP);
  encoder_button.interval(25);

  stats_button.attach(11, INPUT_PULLUP);
  stats_button.interval(25);

  pinMode(PUMP, OUTPUT);
  pinMode(HEATER_RELAY, OUTPUT);
  pinMode(TEMP_OK_LED, OUTPUT);

  digitalWrite(PUMP, LOW);
  digitalWrite(HEATER_RELAY, LOW);
  digitalWrite(TEMP_OK_LED, LOW);

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

unsigned long heater_window_start = 0;

void control_heater_relay() {
  const auto reading = temps.average_pump_temperature();
  if (reading.is_error()) {
    heater_relay_off();
    return;
  }

  const auto temp = reading.reading();

  set_temp_led(temp);

  unsigned long now = millis();

  const auto heater_runtime = heater_pid.Run(temp);
  Serial.println(heater_runtime);

  if (now - heater_window_start > HEATER_PID_WINDOW_SIZE) {
    heater_window_start += HEATER_PID_WINDOW_SIZE;
  }
  if (heater_runtime < now - heater_window_start) {
    digitalWrite(HEATER_RELAY, LOW);
  } else {
    digitalWrite(HEATER_RELAY, HIGH);
  }
}

void loop() {
  temps.update_samples_blocking();

  control_heater_relay();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  State new_state = tick_func();

  if (current_state != new_state) {
    set_new_state(new_state);
  }

  display.display();
}
