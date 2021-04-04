#include "StepperMotorMbed.hpp"
#include "StrangeServo.hpp"
#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define DATA_TRANSPORT static volatile

ServoConfig ServoConf;

UnbufferedSerial serial_port(PA_2, PA_3, 19200);

StrangeServo DS = StrangeServo(PB_3);

StepperMotorBP PolarAxisMotor = StepperMotorBP(PA_7, PA_6, PA_5, PA_4);

Thread DeclinationMotion, DiurnalMotion;

DATA_TRANSPORT short dec_degree = 90;
DATA_TRANSPORT short polar_degree = 90;
DATA_TRANSPORT short between_step_delay = 300;
DATA_TRANSPORT char ctrl = 'S';
DATA_TRANSPORT bool hold_motor_position = 0;

const char EndLine = '\n';

static void data_procesing();
static void diurnal_motion();     // Stepper motor
static void declination_motion(); // Digital ervo

// Main runs in it's own thread

int main() {
  // Servo initilization

  ServoConf.MinRotatoinAngle = 0;
  ServoConf.MaxRotatoinAngle = 270;

  // ms per 45* mid point(90 = 1.5, 1.5 - low_angle(for 0 it eqals 0.5-1) and
  // /2)
  ServoConf.MinPulseDuration = 0.5f;
  ServoConf.MaxPulseDuration = 2.5f; // ms per max angle

  ServoConf.PulsePeriodUs =
      3333; // for digital experment  I set 3,333ms (20 ms for analog servo);
  // T = 1/f (f = 300hz)
  ServoConf.MovingPrecesion = PRETTY;

  DS.Init(ServoConf);

  DiurnalMotion.start(&diurnal_motion);
  DeclinationMotion.start(&declination_motion);

  while (1) {
    data_procesing();
  }
}

void diurnal_motion() {
  uint8_t step = 1;
  while (1) {
    if (step > PolarAxisMotor.max_steps)
      step = 1;
    PolarAxisMotor.RunningBP(step, 'H', ctrl);
    thread_sleep_for(between_step_delay);
    if (!hold_motor_position)
      ++step;
  }
}

static void declination_motion() {
  while (1) {
    DS.SetPosition(dec_degree);
  }
}

// converts 3 chars to  one short
static short chars_to_short(const char one_num, const char two_num,
                            const char third_num) {
  return ((one_num - '0') * 100) + ((two_num - '0') * 10) + (third_num - '0');
}

static void send_data_to_motors(char chars[4]) {
  switch (chars[0]) {
  // for stepper motor
  case 'P':
    polar_degree = chars_to_short(chars[1], chars[2], chars[3]);
    break;

  // control stepper motor direction char
  case 'F':
  case 'B':
  case 'S':
    ctrl = chars[0];
    hold_motor_position = 0;
    between_step_delay = chars_to_short(chars[1], chars[2], chars[3]);
    break;

    // for servo
  case 'D':
    dec_degree = chars_to_short(chars[1], chars[2], chars[3]);
    break;

  case 'H':
    hold_motor_position = 1;
  default:
    break;
  }
}

// example data  is P180 or  F200 or B010 or H450, F010, D025 ,D090, D180, D135
// where P -- Polar axis,180 - RA degree F - dir for motor(Forward) D = Dec.
// axis 125 is a dec.degree To stop  motor -- write S000

static void data_procesing() {
  char buffer[4] = {0}; // Buffer for receiving information
  while (1) {
    if (serial_port.readable()) {
      serial_port.read(&buffer[0], 1);
      serial_port.read(&buffer[1], 1);
      serial_port.read(&buffer[2], 1);
      serial_port.read(&buffer[3], 1);
      send_data_to_motors(buffer);
      for (int num = sizeof(buffer); num > 0; num--)
        buffer[num] = 0;
    }
  }
}
