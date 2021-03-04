#include <Adafruit_SSD1306.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <HX711.h>
#include <SPI.h>
#include <Wire.h>

#include "constants.h"
#include "util.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
HX711 scale;

// Calibrated to my specific scale, YMMV
float calibration_factor = 416;

int desired_weight_in_grams;

unsigned long state_start_millis = 0;

bool has_most_recent_pour = false;
unsigned long last_pour_seconds;
float last_pour_weight;

Encoder encoder(2, 3);
Bounce brew_button;
Bounce flush_button;
Bounce encoder_button;

enum State {
  Waiting,

  ConfigureWeight,

  Preinfusing,
  WaitingAfterPreinfusing,
  Brewing,
  Flushing,

  Error,
};

State current_state;

Temps<5> temps{A0, A1};

State (*tick_func)();

State waiting_tick() {
  brew_button.update();
  flush_button.update();
  encoder_button.update();

  State next_state;
  if (brew_button.fell()) {
    scale.tare();

    next_state = State::Preinfusing;
  } else if (flush_button.fell()) {
    next_state = State::Flushing;
  } else if (encoder_button.fell()) {
    next_state = State::ConfigureWeight;
  } else {
    next_state = State::Waiting;
  }

  pump_off();

  display.setTextSize(2);

  display.println(F("Coffeetron"));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  display.print(temps.average_pump_temperature());
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(temps.average_grouphead_temperature());
  display.println(F("F"));

  if (has_most_recent_pour) {
    display.println(F("Most recent pour:"));
    display.print(F(" Total time: "));
    display.print(last_pour_seconds);
    display.println(F("s"));
    display.print(F(" Total weight: "));
    display.print(last_pour_weight);
    display.println(F("g"));
  } else {
    display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);
  }

  return next_state;
}

State configure_weight_tick() {
  desired_weight_in_grams = encoder.read() / 4;

  encoder_button.update();

  State next_state;
  if (encoder_button.fell()) {
    next_state = State::Waiting;
  } else {
    next_state = State::ConfigureWeight;
  }

  pump_off();

  display.setTextSize(2);

  display.println(F("Weight"));

  display.setTextSize(1);

  display.print(desired_weight_in_grams);
  display.println(F("g"));
  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);

  return next_state;
}

State preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > PREINFUSE_PUMP_TIME_MILLIS) {
    next_state = State::WaitingAfterPreinfusing;
  } else {
    next_state = State::Preinfusing;
  }

  pump_on();

  display.setTextSize(2);

  display.println(F("Infusing"));

  display.setTextSize(1);

  display.println(F("Pumping"));
  display.print((state_start_millis + PREINFUSE_PUMP_TIME_MILLIS - now + 500) /
                1000);
  display.println(F("s remaining"));

  display.println(F(""));

  display.print(F("Pump temp: "));
  display.print(temps.average_pump_temperature());
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(temps.average_grouphead_temperature());
  display.println(F("F"));

  return next_state;
}

State waiting_after_preinfusing_tick() {
  const auto now = millis();

  State next_state;
  if (now - state_start_millis > PREINFUSE_TIME_MILLIS) {
    next_state = State::Brewing;
  } else {
    next_state = State::WaitingAfterPreinfusing;
  }

  digitalWrite(LED, HIGH);
  digitalWrite(PUMP, LOW);

  display.setTextSize(2);

  display.println(F("Infusing"));

  display.setTextSize(1);

  display.println(F("Waiting"));
  display.print((state_start_millis + PREINFUSE_TIME_MILLIS - now + 500) /
                1000);
  display.println(F("s remaining"));

  display.println(F(""));

  display.print(F("Pump temp: "));
  display.print(temps.average_pump_temperature());
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(temps.average_grouphead_temperature());
  display.println(F("F"));

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

  // Display
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
  display.print(temps.average_pump_temperature());
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(temps.average_grouphead_temperature());
  display.println(F("F"));

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
  display.print(temps.average_pump_temperature());
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(temps.average_grouphead_temperature());
  display.println(F("F"));

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

  case State::ConfigureWeight:
    tick_func = &configure_weight_tick;
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

  case State::Error:
  default:
    tick_func = &error_tick;
    break;
  }
}

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

  pinMode(LED, OUTPUT);
  pinMode(PUMP, OUTPUT);

  encoder_button.attach(10, INPUT_PULLUP);
  encoder_button.interval(25);

  encoder.write(INITIAL_DESIRED_WEIGHT_GRAMS * 4);
  desired_weight_in_grams = INITIAL_DESIRED_WEIGHT_GRAMS;

  set_new_state(State::Waiting);

  display.clearDisplay();
  display.display();
}

void loop() {
  temps.update_samples_blocking();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  State new_state = tick_func();

  if (current_state != new_state) {
    set_new_state(new_state);
  }

  display.display();
}
