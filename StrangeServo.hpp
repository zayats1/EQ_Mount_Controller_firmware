#pragma once

#ifndef StrangeServo_HPP
#define StrangeServo_HPP

#include "mbed.h"
#include <cstdint>

// Precesion  settings constants
const short PRETTY = 1000;
const short DEFAULT = 100;
const short LOW_PREC = 10;

/*
Default parameters, please change  this values if you  servo needs
another parameters
*/
typedef struct {
  /*
  1.5 = ( in default) 90* Pulse duration - 0* pulse duration and /2 it
  */
  float MinPulseDuration = 0.5; // 0
  float MaxPulseDuration = 2.5; // 180

  short MovingPrecesion = PRETTY; // default value

  unsigned short PulsePeriodUs = 20000; // T = 1/frequency(khz)  * 1000

  // for lazy makers :=)
  uint8_t MinRotatoinAngle = 0;
  short MaxRotatoinAngle = 180; // 2.5
} ServoConfig;

// for digital and analog servo controling(just adjust config parameters)

class StrangeServo {
public:
  StrangeServo(PinName ctrl); // const uint16_t DefaultServoPeriod_us = 20100;

  /*
   Sets parameters to servo
   and default servo position to 0-1* for servo controling
  */

  void Init(const ServoConfig &sc);

  // Runs to preassigned position(angle)
  void SetPosition(unsigned short pos_angle);

private:
  PwmOut _ctrl;

  // Calculates duration of pulse in PWM
  short dur_calc(short angle);

  short _mow_precesion;

  uint8_t _min_angle;
  short _max_angle;

  float _min_pulse_duration;
  float _max_pulse_duration;
};

#endif
