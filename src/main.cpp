#include <Arduino.h>
#include <Globals.hpp>
#include <WirePullerApp.hpp>

// #define DEBUG_TRANSMISSION

using WirePullerApp = WirePuller<Globals::MaxJsonSize * 2>;

WirePullerApp app;

void setup() {
  app.initialize();
  Serial.begin(Globals::SerialDataRate);
  Serial.setTimeout(Globals::SerialTimeout);
}

void loop() {
  if (Serial.available()) {
    char buffer[Globals::MaxJsonSize];
    char response[Globals::MaxJsonSize];
    Serial.readBytesUntil(Globals::JsonTerminator, buffer,
                          Globals::MaxJsonSize);
#ifdef DEBUG_TRANSMISSION
    Serial.println(buffer);
#else
    if (app.execute(buffer, response)) {
      Serial.println(response);
    }
#endif
  }
}
