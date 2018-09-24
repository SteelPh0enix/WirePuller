#include <Arduino.h>
#include <Globals.hpp>
#include <WirePullerApp.hpp>

using WirePullerApp = WirePuller<MaxJsonSize>;

WirePullerApp app;

void setup() {
    app.initialize();
    Serial.begin(SerialDataRate);
}

void loop() {
    if (Serial.available()) {
        WirePullerApp::JsonSpan bytes;
        Serial.readBytesUntil(JsonTerminator, bytes.data, MaxJsonSize);
        bytes.clear();
        Serial.println(app.execute(bytes).data);
    }
}