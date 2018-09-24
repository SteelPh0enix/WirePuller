#include <Arduino.h>
#include <Globals.hpp>
#include <Span.hpp>
#include <EndstopManager.hpp>
#include <string.h>

constexpr uint maxJsonSize = 256u;
constexpr char jsonTerminator = '\n';

EndstopManager<2, 4> manager;

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.print("Initialized endstops: ");
    Serial.println(manager.initializedEndstops());

    for(uint i = 0; i < manager.endstopCount; i++) {
        char id[4];
        sprintf(id, "END%d", i);

        Serial.print("Initializing endstop ");
        Serial.print(id);
        Serial.print(": ");
        Serial.println(manager.initializeEndstop(id, 0));
    }

    char addr[16];

    Serial.print("Endstop END1 address: ");
    sprintf(addr, "0x%x", manager["END1"]);
    Serial.println(addr);

    Serial.print("Endstop N_EX address: ");
    sprintf(addr, "0x%x", manager["N_EX"]);
    Serial.println(addr);

    delay(3000);
}