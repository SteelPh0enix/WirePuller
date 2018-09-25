#include <Arduino.h>
#include <Globals.hpp>
#include <WirePullerApp.hpp>

using WirePullerApp = WirePuller<Globals::MaxJsonSize>;

WirePullerApp app;

void setup() {
    app.initialize();
    Serial.begin(Globals::SerialDataRate);
}

void loop() {
    if (Serial.available()) {
        char buffer[Globals::MaxJsonSize];
        char response[Globals::MaxJsonSize];
        Serial.readBytesUntil(Globals::JsonTerminator, buffer, Globals::MaxJsonSize);
        if (app.execute(buffer, response)) {
            Serial.println(response);
        }
    }
}