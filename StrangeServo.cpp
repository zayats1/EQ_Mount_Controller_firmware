#include "StrangeServo.hpp"
#include "mbed.h"
#include <cstdint>

// For digital and analog servos
StrangeServo::StrangeServo(PinName ctrl) : _ctrl(ctrl) {}
// public
void StrangeServo::Init(const ServoConfig &sc) {
  // My servo has a 0.5 for 45 and 2.5 for 180;
  // Constrains diapason
  _min_angle = sc.MinRotatoinAngle;
  _max_angle = sc.MaxRotatoinAngle;

  _min_pulse_duration = sc.MinPulseDuration;
  _max_pulse_duration = sc.MaxPulseDuration;

  _mow_precesion = sc.MovingPrecesion;

  _ctrl.period_us(sc.PulsePeriodUs);
}

void StrangeServo::SetPosition(unsigned short pos_angle) {
  // Long code for safety
  if (pos_angle < _min_angle) {
    _ctrl.pulsewidth_us(dur_calc(_min_angle));
  } else if (pos_angle > _max_angle) {
    _ctrl.pulsewidth_us(dur_calc(_max_angle));
  } else {
    _ctrl.pulsewidth_us(dur_calc(pos_angle));
  }
}

// private
short StrangeServo::dur_calc(
    short angle) { // I convert ms to us for better precesion
  return round(((((_min_pulse_duration / 45) * angle) + _min_pulse_duration) *
                _mow_precesion)) *
         1000 / _mow_precesion;
}
