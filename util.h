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

template <int S> class Temps {
  const int pump_pin_;
  const int grouphead_pin_;
  const int sample_count_;

  unsigned int samples_;

  WindowedReading<S> pump_temps_;
  WindowedReading<S> grouphead_temps_;

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

  float average_pump_temperature() { return pump_temps_.average_reading(); }

  float average_grouphead_temperature() {
    return grouphead_temps_.average_reading();
  }
};

void pump_on() {
  digitalWrite(LED, HIGH);
  digitalWrite(PUMP, HIGH);
}

void pump_off() {
  digitalWrite(LED, LOW);
  digitalWrite(PUMP, LOW);
}
