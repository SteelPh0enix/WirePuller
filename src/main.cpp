// #define DEBUG_TRANSMISSION

#include <Arduino.h>
#include <Globals.hpp>
#include <WirePullerApp.hpp>

using WirePullerApp = WirePuller<Globals::MaxJsonSize * 2>;

WirePullerApp app;

void setup() {
  // Serial.begin(Globals::SerialDataRate);
  // Serial.setTimeout(Globals::SerialTimeout);
  app.initialize();
}

const char* CMD_1 =
    R"({"type": "set_motor_speed", "data": {"MOT_OX": -150, "MOT_WH": 200, "MOT_BK": -100}})";
const char* CMD_2 =
    R"({"type": "set_motor_speed", "data": {"MOT_OX": 150, "MOT_WH": -200, "MOT_BK": 100}})";

void loop() {
  // if (Serial.available()) {
    // char buffer[Globals::MaxJsonSize];
    char response[Globals::MaxJsonSize];
    // Serial.readBytesUntil(Globals::JsonTerminator, buffer,
    // Globals::MaxJsonSize);
// #ifdef DEBUG_TRANSMISSION
//     Serial.println(buffer);
// #else
    // if (app.execute(buffer, response)) {
      // Serial.println(response);
    // }
// #endif
  // }

  app.execute(CMD_1, response);
  delay(2000);
  app.execute(CMD_2, response);
  delay(2000);
  app.endstopCheck();
}
