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
        WirePullerApp::JsonSpan bytes;
        Serial.readBytesUntil(Globals::JsonTerminator, bytes.data, Globals::MaxJsonSize);
        bytes.clear();
        Serial.println(app.execute(bytes).data);
    }
}