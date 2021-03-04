#pragma once

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

  int clk_pin() { return clk_pin_; }

  int dt_pin() { return dt_pin_; }

  void set_value(int value) { value_ = value; }

  int value() { return value_; }

  int read_button_and_reset_state() {
    if (button_state_ == LOW) {
      button_state_ = HIGH;
      return LOW;
    }

    return HIGH;
  }
};
