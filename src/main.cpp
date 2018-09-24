#include <Arduino.h>
#include <Globals.hpp>
#include <WirePullerApp.hpp>

constexpr uint maxJsonSize = 256u;
constexpr char jsonTerminator = '\n';

using WirePullerApp = WirePuller<maxJsonSize>;

WirePullerApp app;

void setup() {
    app.initialize();
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        WirePullerApp::JsonSpan bytes;
        Serial.readBytesUntil(jsonTerminator, bytes.data, maxJsonSize);
        bytes.clear();
        Serial.println(app.execute(bytes).data);
    }
}