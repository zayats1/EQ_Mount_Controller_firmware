#include "StepperMotorMbed.hpp"
#include "StrangeServo.hpp"
#include "map_constrain.h"
#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define DATA_TRANSPORT static volatile

ServoConfig ServoConf;

UnbufferedSerial serial_port(PA_2, PA_3, 19200);

StrangeServo DS = StrangeServo(PB_3);

StepperMotorBP PolarAxisMotor = StepperMotorBP(PA_7, PA_6, PA_5, PA_4);

Thread DataProcesing;

DATA_TRANSPORT short dec_degree = 90;
DATA_TRANSPORT short polar_degree = 90;
DATA_TRANSPORT short between_step_delay = 300;
DATA_TRANSPORT char ctrl = 'S';

const char EndLine = '\n';

static void data_procesing();
static void goto_position();

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

  DataProcesing.start(&data_procesing);
  while (1) {
    goto_position();
  }
}

void diurnal_motion(short degree, short delay, char _ctrl) {

  // uint16_t total_steps = degree / 1.8; // total_steps = degree/degre
  // per_steps (fs)

  // uint16_t total_steps = uint16_t(round(degree / 1.8));  // @Todo
  for (uint8_t step = 1; step < 5; ++step) { //? why 5
    PolarAxisMotor.RunningBP(step, 'W', _ctrl);
    thread_sleep_for(delay);
  }
}

void goto_position() {
  DS.SetPosition(dec_degree);
  diurnal_motion(polar_degree, between_step_delay, ctrl);
}

// converts 3 chars to  one short
short chars_to_short(const char one_num, const char two_num,
                     const char third_num) {
  return ((one_num - '0') * 100) + ((two_num - '0') * 10) + (third_num - '0');
}

// "cooks" and sends data to mail

void send_data_to_motors(char chars[4]) {
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
    // send delay
    between_step_delay = chars_to_short(chars[1], chars[2], chars[3]);
    break;

    // for servo
  case 'D':
    dec_degree = chars_to_short(chars[1], chars[2], chars[3]);
    break;

  default:
    break;
  }
}

// example data  is P180 or  F200 or B010, F010, D025 ,D090, D180, D135 where
// P -- Polar axis,180 - RA degree F - dir for motor(Forward) D = Dec. axis 125
// is a dec.degree
// To stop  motor -- write S000

void data_procesing() {
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
