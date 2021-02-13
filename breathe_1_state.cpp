// -*- mode: c++ -*-
// Breathing state with colour adjust
//
// Copyright (c) 2021 Dave Astels

#include "breathe_1_state.h"

#define DEFAULT_BREATH_TIME (5000) // in milliseconds

Breathe1State::Breathe1State(StateMachine *machine)
  : State(machine, "breathe1")
  , breathe_delta(5.0)          // changes of 5%
  , step_interval(DEFAULT_BREATH_TIME / 100)
  , step_time(0)
{

}


void Breathe1State::enter(uint8_t *data)
{
  cached_data = data;
  red = data[0];
  green = data[1];
  blue = data[2];
  breathe_value = 100.0;
  update_fractional(red, green, blue);
}


uint8_t Breathe1State::compute_fractional(uint8_t colour)
{
  return (uint8_t)((float)colour * breathe_value / 100.0);
}

void Breathe1State::update_fractional(uint8_t r, uint8_t g, uint8_t b)
{
  update_neopixels(compute_fractional(r), compute_fractional(g), compute_fractional(b));
}


void Breathe1State::mode_button(void)
{
  cached_data[0] = red;
  cached_data[1] = green;
  cached_data[2] = blue;
  go_to("breathe2", cached_data);
}


void Breathe1State::red_button(void)
{
  red = next_colour(red);
  update_fractional(red, green, blue);
}


void Breathe1State::green_button(void)
{
  green = next_colour(green);
  update_fractional(red, green, blue);
}


void Breathe1State::blue_button(void)
{
  blue = next_colour(blue);
  update_fractional(red, green, blue);
}


void Breathe1State::tick(uint32_t now)
{
  if (now >= step_time) {
    breathe_value += breathe_delta;
    if (breathe_value > 100.0) {
      breathe_value = 100.0;
      breathe_delta *= -1;
    } else if (breathe_value <= 0.0) {
      breathe_value = 0.0;
      breathe_delta *= -1;
    }
    update_fractional(red, green, blue);
    step_time = now + step_interval;
  }
}
