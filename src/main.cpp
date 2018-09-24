#include <Arduino.h>
#include <Globals.hpp>
#include <Span.hpp>
#include <WirePullerApp.hpp>

constexpr uint maxJsonSize = 512u;
constexpr char jsonTerminator = '\n';

WirePuller<maxJsonSize> app;

void setup() {
    app.initialize();
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        Span<byte, maxJsonSize> bytes;
        Serial.readBytesUntil(jsonTerminator, bytes.data, maxJsonSize);
        app.execute(bytes);
    }
}