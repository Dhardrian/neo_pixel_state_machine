// -*- mode: c++ -*-
// State base class
//
// Copyright (c) 2021 Dave Astels

#ifndef __STATE_H__
#define __STATE_H__

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class StateMachine;

class State {
 protected:
  StateMachine *_machine;
  void update_neopixels(uint8_t red, uint8_t green, uint8_t blue);

 private:
  char *_name;


 public:
  State(StateMachine *owner_machine=nullptr, char *name=nullptr);
  char *name() { return _name; }
  bool is_named(char *name);

  virtual void enter(void *data=nullptr) {}
  virtual void exit(void *data=nullptr) {}
  virtual void tick(uint32_t now) {}
  virtual void mode_button() {}
  virtual void red_button() {}
  virtual void green_button() {}
  virtual void blue_button() {}
  void go_to(char *state_name, void *data=nullptr);
};

#endif
