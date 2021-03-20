#include "StepperMotorMbed.hpp"
#include "mbed.h"

StepperMotorUP::StepperMotorUP(PinName one, PinName two, PinName three,
                               PinName four)
    : _one(one), _two(two), _three(three), _four(four) {
  _one = 0;
  _two = 0;
  _three = 0;
  _four = 0;
}

void StepperMotorUP::RunningUP(short Steps, char Mode, char Ctrl) {
  _steps = Steps;
  switch (Ctrl) {
  case ('F'): // forward
    ControlF(Mode);
    break;
  case ('B'): // Backward
    ControlB(Mode);
    break;
  case ('S'): // Stop
  default:
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}

// protected
void StepperMotorUP::ControlF(char Mode) {
  switch (Mode) {
  case ('F'):
    max_steps = 4;
    FullStepF();
    break;
  case ('H'):
    max_steps = 8;
    HalfStepF();
    break;
  case ('W'):
    max_steps = 4;
    WaveF();
    break;
  }
}

void StepperMotorUP::ControlB(char Mode) {
  switch (Mode) {
  case ('F'):
    max_steps = 4;
    FullStepB();
    break;
  case ('H'):
    max_steps = 8;
    HalfStepB();
    break;
  case ('W'):
    max_steps = 4;
    WaveB();
    break;
  }
}

// private
void StepperMotorUP::WaveF() {
  switch (_steps) {
  case (1):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  case (2):
    _one = 0;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 0;
    _three = 1; // 3
    _four = 0;
    break;
  case (4):
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  }
}
void StepperMotorUP::HalfStepF() {
  switch (_steps) {
  case (1):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  case (2):
    _one = 1;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 0; // 3
    _four = 0;
    break;
  case (4):
    _one = 0;
    _two = 1;
    _three = 1;
    _four = 0; // 4
    break;
  case (5):
    _one = 0; // 1
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  case (6):
    _one = 0;
    _two = 0; // 2
    _three = 1;
    _four = 1;
    break;
  case (7):
    _one = 0;
    _two = 0;
    _three = 0; // 3
    _four = 1;
    break;
  case (8):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  }
}
void StepperMotorUP::FullStepF() {
  switch (_steps) {
  case (1):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  case (2):
    _one = 1;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 1; // 3
    _four = 0;
    break;
  case (4):
    _one = 0;
    _two = 0;
    _three = 1;
    _four = 1; // 4
    break;
  }
}

void StepperMotorUP::WaveB() {
  switch (_steps) {
  case (1):
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  case (2):
    _one = 0;
    _two = 0;
    _three = 1; // 3
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (4):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}
void StepperMotorUP::HalfStepB() {
  switch (_steps) {
    break;
  case (1):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  case (2):
    _one = 0;
    _two = 0;
    _three = 0; // 3
    _four = 1;
  case (3):
    _one = 0;
    _two = 0; // 2
    _three = 1;
    _four = 1;
    break;
  case (4):
    _one = 0; // 1
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  case (5):
    _one = 0;
    _two = 1;
    _three = 1;
    _four = 0; // 4
    break;
  case (6):
    _one = 0;
    _two = 1;
    _three = 0; // 3
    _four = 0;
    break;
  case (7):
    _one = 1;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (8):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}
void StepperMotorUP::FullStepB() {
  switch (_steps) {
  case (1):
    _one = 0;
    _two = 0;
    _three = 1;
    _four = 1; // 4
    break;
  case (2):
    _one = 0;
    _two = 1;
    _three = 1; // 3
    _four = 0;
    break;
  case (3):
    _one = 1;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (4):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  }
}

/**********************************************************************************************************************/

StepperMotorBP::StepperMotorBP(PinName one, PinName two, PinName three,
                               PinName four)
    : _one(one), _two(two), _three(three), _four(four) {
  _one = 0;
  _two = 0;
  _three = 0;
  _four = 0;
}

void StepperMotorBP::RunningBP(short Steps, char Mode, char Ctrl) {
  _steps = Steps;
  switch (Ctrl) {
  case ('F'): // forward
    ControlF(Mode);
    break;
  case ('B'): // Backward
    ControlB(Mode);
    break;
  case ('S'): // Stop
  default:
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}

// protected
void StepperMotorBP::ControlF(char Mode) {
  switch (Mode) {
  case ('F'):
    max_steps = 4;
    FullStepF();
    break;
  case ('H'):
    max_steps = 8;
    HalfStepF();
    break;
  case ('W'):
    max_steps = 4;
    WaveF();
    break;
  }
}

void StepperMotorBP::ControlB(char Mode) {
  switch (Mode) {
  case ('F'):
    max_steps = 4;
    FullStepB();
    break;
  case ('H'):
    max_steps = 8;
    HalfStepB();
    break;
  case ('W'):
    max_steps = 4;
    WaveB();
    break;
  }
}

void StepperMotorBP::WaveF() {
  switch (_steps) {
  case (1):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  case (2):
    _one = 0;
    _two = 0; // 2
    _three = 1;
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 0; // 3
    _four = 0;
    break;
  case (4):
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  }
}

void StepperMotorBP::HalfStepF() {
  switch (_steps) {
  case (1):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  case (2):
    _one = 1; // 1
    _two = 0;
    _three = 1; // 3
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 0;
    _three = 1; // 3
    _four = 0;
    break;
  case (4):
    _one = 0;
    _two = 1;   // 2
    _three = 1; // 3
    _four = 0;
    break;
  case (5):
    _one = 0;
    _two = 1; // 2
    _three = 0;
    _four = 0;
    break;
  case (6):
    _one = 0;
    _two = 1;
    _three = 0; // 3
    _four = 1;
    break;
  case (7):
    _one = 0;
    _two = 0; // 2
    _three = 0;
    _four = 1;
    break;
  case (8):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  }
}
void StepperMotorBP::FullStepF() {
  switch (_steps) {
  case (1):
    _one = 1;
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  case (2):
    _one = 0;
    _two = 1;
    _three = 1;
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 0;
    _four = 1;
    break;
  case (4):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  }
}

void StepperMotorBP::WaveB() {
  switch (_steps) {
  case (1):
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 1; // 4
    break;
  case (2):
    _one = 0;
    _two = 1;
    _three = 0; // 3
    _four = 0;
    break;
  case (3):
    _one = 0;
    _two = 0; // 2
    _three = 1;
    _four = 0;
    break;
  case (4):
    _one = 1; // 1
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}
void StepperMotorBP::HalfStepB() {
  switch (_steps) {
  case (1):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  case (2):
    _one = 0;
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 0;
    _four = 1;
    break;
  case (4):
    _one = 0;
    _two = 1;
    _three = 0;
    _four = 0;
    break;
  case (5):
    _one = 0;
    _two = 1;
    _three = 1;
    _four = 0;
    break;
  case (6):
    _one = 0;
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  case (7):
    _one = 1;
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  case (8):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 0;
    break;
  }
}
void StepperMotorBP::FullStepB() {
  switch (_steps) {
  case (1):
    _one = 1;
    _two = 0;
    _three = 0;
    _four = 1;
    break;
  case (2):
    _one = 0;
    _two = 1;
    _three = 0;
    _four = 1;
    break;
  case (3):
    _one = 0;
    _two = 1;
    _three = 1;
    _four = 0;
    break;
  case (4):
    _one = 1;
    _two = 0;
    _three = 1;
    _four = 0;
    break;
  }
}