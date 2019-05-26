#include <Arduino.h>
#include <Constants.hpp>
#include <MC33926.hpp>

MC33926 motor;

void setup() { Serial.begin(Constant::Serial::BaudRate); }

void loop() {}