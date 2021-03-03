#include <HX711.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define FALSE 0
#define TRUE 1

#define HX711_CLK  8
#define HX711_DOUT  9
#define BREW_BUTTON 4
#define LED 5
#define PUMP 6
#define FLUSH_BUTTON 7

#define SAMPLE_COUNT 5

#define VCC 5.0
#define ANALOG_MAX 1023
#define THERMISTOR_PAIRED_RESISTOR 10000.0
#define NOMINAL_RESISTANCE 10000.0
#define THERMISTOR_B_CONSTANT 3434.0
#define NOMINAL_TEMPERATURE 298.15
#define CELCIUS_OFFSET 273.15

#define FLUSH_TIME_MILLIS 1000
#define PREINFUSE_PUMP_TIME_MILLIS 3000
#define PREINFUSE_TIME_MILLIS 7000

#define OLED_RESET -1

int desired_weight_in_grams = 38;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
HX711 scale;

// Calibrated to my specific scale, YMMV
float calibration_factor = 416;

int running = FALSE;
int flushing = FALSE;

unsigned long state_start_millis = 0;

int has_most_recent_pour = FALSE;
unsigned long last_pour_seconds;
float last_pour_weight;

enum State {
  Waiting,
  Flushing,
  Preinfusing,
  WaitingAfterPreinfusing,
  Brewing,
};

State state = State::Waiting;

// Cute coffee cup bitmap to display, 128x32 pixels
const unsigned char coffee_bitmap[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x06, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

class BrewData {
 public:
  unsigned long now;
  float pump_temp;
  float grouphead_temp;
  float weight;
};

template <int S>
class WindowedReading {
  float values[S];
  int index = 0;

 public:
  WindowedReading() {
    for (int i = 0; i < S; i++) {
      values[i] = 0.0;
    }
  }

  void add_value(float value) {
    values[index] = value;
    index = (index + 1) % S;
  }

  float average_reading() {
    float sum = 0;
    for (int i = 0; i < S; i++) {
      sum += values[i];
    }

    return sum / S;
  }
};

class RotaryEncoderWithButton {
  const int clk_pin_;
  const int dt_pin_;

  const int button_pin_;

  const int button_debounce_timeout_;
  const int button_actuation_timeout_;

  unsigned long previous_button_press_time_;
  unsigned long previous_button_accepted_press_time_;

  int last_button_state_;

  int button_state_;

  int last_clk_state_;
  int last_dt_state_;

  int value_;

public:
  RotaryEncoderWithButton(int clk_pin, int dt_pin, int button_pin)
      : RotaryEncoderWithButton(clk_pin, dt_pin, button_pin, 0) {}

  RotaryEncoderWithButton(int clk_pin, int dt_pin, int button_pin,
                          int initial_value_offset)
      : clk_pin_(clk_pin), dt_pin_(dt_pin), button_pin_(button_pin),
        button_debounce_timeout_(5), button_actuation_timeout_(150) {
    last_clk_state_ = HIGH;
    last_dt_state_ = HIGH;

    value_ = initial_value_offset;

    previous_button_press_time_ = 0;
    previous_button_accepted_press_time_ = 0;

    last_button_state_ = HIGH;

    pinMode(clk_pin_, INPUT_PULLUP);
    pinMode(dt_pin_, INPUT_PULLUP);
    pinMode(button_pin_, INPUT_PULLUP);
  }

  void update_clk_on_change() {
    if (last_clk_state_ == HIGH) {
      last_clk_state_ = LOW;
    } else {
      last_clk_state_ = HIGH;
    }

    // TODO: == HIGH
    if (last_dt_state_ && last_clk_state_ == HIGH) {
      value_ -= 1;
    }
  }

  void update_dt_on_change() {
    if (last_dt_state_ == HIGH) {
      last_dt_state_ = LOW;
    } else {
      last_dt_state_ = HIGH;
    }

    if (last_clk_state_ && last_dt_state_ == HIGH) {
      value_ += 1;
    }
  }

  void update(const unsigned long now) {
    /*
    int current_clk_state = digitalRead(clk_pin_);
    int current_dt_state = digitalRead(dt_pin_);

    if (current_dt_state && current_clk_state != last_clk_state_ &&
        current_clk_state == HIGH) {
      value_ -= 1;
    } else if (current_clk_state && current_dt_state != last_dt_state_ &&
               current_dt_state == HIGH) {
      value_ += 1;
    }

    last_clk_state_ = current_clk_state;
    last_dt_state_ = current_dt_state;
    */

    int current_button_state = digitalRead(button_pin_);

    if (current_button_state != last_button_state_) {
      previous_button_press_time_ = now;
      last_button_state_ = current_button_state;
    }

    if (now - previous_button_press_time_ > button_debounce_timeout_) {
      if (now - previous_button_accepted_press_time_ >
          button_actuation_timeout_) {
        previous_button_accepted_press_time_ = now;
        button_state_ = current_button_state;
      }
    }
  }

  int clk_pin() {
    return clk_pin_;
  }

  int dt_pin() {
    return dt_pin_;
  }

  void set_value(int value) {
    value_ = value;
  }

  int value() { return value_; }

  int read_button_and_reset_state() {
    if (button_state_ == LOW) {
      button_state_ = HIGH;
      return LOW;
    }

    return HIGH;
  }
};

WindowedReading<SAMPLE_COUNT> pump_temps;
WindowedReading<SAMPLE_COUNT> grouphead_temps;
WindowedReading<SAMPLE_COUNT> weights;

RotaryEncoderWithButton encoder{2, 3, 10};

unsigned int windows_read = 0;

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("failed to initialize OLED display");
    for(;;); // Don't proceed, loop forever
  }

  scale.begin(HX711_DOUT, HX711_CLK);
  scale.set_scale(calibration_factor);
  scale.tare();

  pinMode(BREW_BUTTON, INPUT);
  pinMode(FLUSH_BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PUMP, OUTPUT);

  encoder.set_value(38);

  /*
  attachInterrupt(digitalPinToInterrupt(encoder.clk_pin()), update_encoder_clk, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder.dt_pin()), update_encoder_dt, CHANGE);
  */

  display.clearDisplay();
  display.display();
}

float temp_in_fahrenheit(int pin) {
  float pin_reading = analogRead(pin) * (VCC / ANALOG_MAX);
  float vr = VCC - pin_reading;

  float ln = log((pin_reading / (vr / THERMISTOR_PAIRED_RESISTOR)) / NOMINAL_RESISTANCE);
  float temp_in_kelvin = (1 / ((ln / THERMISTOR_B_CONSTANT) + (1 / NOMINAL_TEMPERATURE)));

  return ((temp_in_kelvin - CELCIUS_OFFSET) * 1.8) + 32;
}

State waiting_update(const BrewData& data) {
  desired_weight_in_grams = encoder.value();

  if (digitalRead(BREW_BUTTON) == HIGH) {
    scale.tare();

    return State::Preinfusing;
  }

  if (digitalRead(FLUSH_BUTTON) == HIGH) {
    return State::Flushing;
  }

  return State::Waiting;
}

State preinfusing_update(const BrewData& data) {
  if (data.now - state_start_millis > PREINFUSE_PUMP_TIME_MILLIS) {
    return State::WaitingAfterPreinfusing;
  }

  return State::Preinfusing;
}

State waiting_after_preinfusing_update(const BrewData& data) {
  if (data.now - state_start_millis > PREINFUSE_TIME_MILLIS) {
    return State::Brewing;
  }

  return State::WaitingAfterPreinfusing;
}

State brewing_update(const BrewData& data) {
  if (data.weight > desired_weight_in_grams) {
    scale.tare();

    last_pour_seconds = (data.now - state_start_millis) / 1000;
    last_pour_weight = data.weight;

    has_most_recent_pour = TRUE;

    return State::Waiting;
  }

  return State::Brewing;
}

State flushing_update(const BrewData& data) {
  if (data.now - state_start_millis > FLUSH_TIME_MILLIS) {
    return State::Waiting;
  }

  return State::Flushing;
}

void pump_on() {
  digitalWrite(LED, HIGH);
  digitalWrite(PUMP, HIGH);
}

void pump_off() {
  digitalWrite(LED, LOW);
  digitalWrite(PUMP, LOW);
}

void waiting_set_outputs() {
  pump_off();
}

void preinfusing_set_outputs() {
  pump_on();
}

void waiting_after_preinfusing_set_outputs() {
  digitalWrite(LED, HIGH);
  digitalWrite(PUMP, LOW);
}

void brewing_set_outputs() {
  pump_on();
}

void flushing_set_outputs() {
  pump_on();
}

void waiting_display(const BrewData& data) {
  display.setTextSize(2);

  display.println(F("Coffeetron"));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  display.print(data.pump_temp);
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(data.grouphead_temp);
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
}

void preinfusing_display(const BrewData& data) {
  display.setTextSize(2);

  display.println(F("Brewing..."));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  display.print(data.pump_temp);
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(data.grouphead_temp);
  display.println(F("F"));

  display.println(F("Preinfusing..."));
}

// WaitingAfterPreinfusing uses the same display as Preinfusing
// TODO: show time remaining for preinfuse

void brewing_display(const BrewData& data) {
  display.setTextSize(2);

  display.println(F("Brewing..."));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  display.print(data.pump_temp);
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(data.grouphead_temp);
  display.println(F("F"));

  display.print(F("Weight: "));
  display.print(data.weight);
  display.println(F("g"));

  display.print(F("Elapsed: "));
  display.print((data.now - state_start_millis) / 1000);
  display.println(F("s"));
}

void flushing_display(const BrewData& data) {
  display.setTextSize(2);

  display.println(F("Flushing..."));

  display.setTextSize(1);

  display.print(F("Pump temp: "));
  display.print(data.pump_temp);
  display.println(F("F"));
  display.print(F("GH temp: "));
  display.print(data.grouphead_temp);
  display.println(F("F"));

  display.drawBitmap(0, 32, coffee_bitmap, 128, 32, WHITE);
}

void update_encoder_clk() {
  encoder.update_clk_on_change();
}

void update_encoder_dt() {
  encoder.update_dt_on_change();
}

void loop() {
  pump_temps.add_value(temp_in_fahrenheit(A0));
  grouphead_temps.add_value(temp_in_fahrenheit(A1));
  weights.add_value(scale.get_units());

  windows_read += 1;

  auto now = millis();

  /*encoder.update(now);*/

  if (windows_read % SAMPLE_COUNT != 0) {
    delayMicroseconds(100);
    return;
  }

  // Gather measurements
  const BrewData data = BrewData {
    now,
    pump_temps.average_reading(),
    grouphead_temps.average_reading(),
    weights.average_reading(),
  };

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  State prev_state = state;

  switch (state) {
    case State::Waiting:
      state = waiting_update(data);
      waiting_set_outputs();
      waiting_display(data);
      break;
    case State::Preinfusing:
      state = preinfusing_update(data);
      preinfusing_set_outputs();
      preinfusing_display(data);
      break;
    case State::WaitingAfterPreinfusing:
      state = waiting_after_preinfusing_update(data);
      waiting_after_preinfusing_set_outputs();
      preinfusing_display(data);
      break;
    case State::Brewing:
      state = brewing_update(data);
      brewing_set_outputs();
      brewing_display(data);
      break;
    case State::Flushing:
      state = flushing_update(data);
      flushing_set_outputs();
      flushing_display(data);
      break;
  }

  if (prev_state != state) {
    state_start_millis = now;
  }

  display.display();
}
