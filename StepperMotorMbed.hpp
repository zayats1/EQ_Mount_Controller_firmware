#pragma once

#ifndef StepperMotorMbed_HPP
#define StepperMotorMbed_HPP

#include "mbed.h"

class StepperMotorUP {
public:
  StepperMotorUP(PinName one, PinName two, PinName three, PinName four);

  void RunningUP(short Steps, char Mode, char Ctrl); // driving mode and  motor rotating direction

  unsigned short max_steps;

protected:
  volatile short _steps; // for debug i did't make it private

private:
  DigitalOut _one;
  DigitalOut _two;
  DigitalOut _three;
  DigitalOut _four;

  void ControlF(char Mode);
  void ControlB(char Mode);

  // Forward
  void WaveF();
  void FullStepF();
  void HalfStepF();

  // Backward
  void WaveB();
  void FullStepB();
  void HalfStepB();
};


/*********************************************************************************************************************/

class StepperMotorBP {
public:
  StepperMotorBP(PinName one, PinName two, PinName three, PinName four);

  void RunningBP(short Steps, char Ctrl, char Mode);

  unsigned short max_steps;

protected:
  volatile short _steps;

private:
  DigitalOut _one;
  DigitalOut _two;
  DigitalOut _three;
  DigitalOut _four;

  void ControlF(char Mode);
  void ControlB(char Mode);

  // Forward
  void WaveF();
  void FullStepF();
  void HalfStepF();

  // Backward
  void WaveB();
  void FullStepB();
  void HalfStepB();
};
#endif