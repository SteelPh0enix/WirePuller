#include <Arduino.h>
#include <Endstop.hpp>
#include <Globals.hpp>

Endstop endstops[4];
void setup() {
  endstops[0].initialize(32);  // up-left
  endstops[1].initialize(33);  // up-right
  endstops[2].initialize(34);  // down-left
  endstops[3].initialize(35);  // down-right
  Serial.begin(115200);
}

void loop() {
  for (uint i = 0; i < 4; i++) {
    Serial.print("Endstop #");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(endstops[i].state());
  }
  Serial.println("--------");
  delay(500);
}