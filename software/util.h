#pragma once

#include "constants.h"

float temp_in_fahrenheit(int pin) {
  float pin_reading = analogRead(pin) * (VCC / ANALOG_MAX);
  float vr = VCC - pin_reading;

  float ln = log((pin_reading / (vr / THERMISTOR_PAIRED_RESISTOR)) /
                 NOMINAL_RESISTANCE);
  float temp_in_kelvin =
      (1 / ((ln / THERMISTOR_B_CONSTANT) + (1 / NOMINAL_TEMPERATURE)));

  return ((temp_in_kelvin - CELCIUS_OFFSET) * 1.8) + 32;
}

template <int S> class WindowedReading {
  float values[S];
  int index = 0;

public:
  WindowedReading() { clear(); }

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

  void clear() {
    for (int i = 0; i < S; i++) {
      values[i] = 0.0;
    }
  }
};

class TempReading {
  const float reading_;
  const bool is_error_;

public:
  TempReading(float reading, bool is_error)
      : reading_(reading), is_error_(is_error) {}

  float reading() {
    if (is_error_) {
      return 0.0;
    }

    return reading_;
  }

  bool is_error() { return is_error_; }
};

TempReading temp_error() { return TempReading(0.0, /* is_error = */ true); }

TempReading temp_success(float reading) {
  return TempReading(reading, /* is_error = */ false);
}

template <int S> class Temps {
  const int pump_pin_;
  const int grouphead_pin_;
  const int sample_count_;

  unsigned int samples_;

  WindowedReading<S> pump_temps_;
  WindowedReading<S> grouphead_temps_;

  TempReading check_reading(float reading) {
    if (reading > MAX_TEMP_F || reading < MIN_TEMP_F) {
      return temp_error();
    } else {
      return temp_success(reading);
    }
  }

public:
  Temps(int pump_pin, int grouphead_pin, int sample_count)
      : pump_pin_(pump_pin), grouphead_pin_(grouphead_pin),
        sample_count_(sample_count) {
    samples_ = 0;
  }

  Temps(int pump_pin, int grouphead_pin) : Temps(pump_pin, grouphead_pin, 5) {}

  void update_samples_blocking() {
    do {
      pump_temps_.add_value(temp_in_fahrenheit(pump_pin_));
      grouphead_temps_.add_value(temp_in_fahrenheit(grouphead_pin_));

      samples_ += 1;

      const auto now = millis();

      delayMicroseconds(100);
    } while (samples_ % sample_count_ != 0);
  }

  TempReading average_pump_temperature() {
    const float reading = pump_temps_.average_reading();
    return check_reading(reading);
  }

  TempReading average_grouphead_temperature() {
    const float reading = grouphead_temps_.average_reading();
    return check_reading(reading);
  }
};

void pump_on() { digitalWrite(PUMP, HIGH); }

void pump_off() { digitalWrite(PUMP, LOW); }
