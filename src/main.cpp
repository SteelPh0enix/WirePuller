#include <Arduino.h>
#include <Globals.hpp>
#include <Utils.hpp>
#include <WirePullerApp.hpp>

constexpr uint maxJsonSize = 256u;
constexpr char jsonTerminator = '\n';

WirePuller<maxJsonSize> app;

void setup() {
    app.initialize();
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        Bytes<maxJsonSize> bytes;
        Serial.readBytesUntil(jsonTerminator, bytes.ptr, maxJsonSize);
        app.execute(bytes);
    }
}