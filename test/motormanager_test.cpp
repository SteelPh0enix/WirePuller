#include <Arduino.h>
#include <Globals.hpp>
#include <Span.hpp>
#include <MotorManager.hpp>
#include <string.h>

constexpr uint maxJsonSize = 256u;
constexpr char jsonTerminator = '\n';

MotorManager<2, 4> manager;

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.print("Initialized motors: ");
    Serial.println(manager.initializedMotors());

    for(uint i = 0; i < manager.motorCount; i++) {
        char id[4];
        sprintf(id, "MOT%d", i);

        Serial.print("Initializing motor ");
        Serial.print(id);
        Serial.print(": ");
        Serial.println(manager.initializeMotor(id, {0, 0, 0, 0, 0}));
    }

    char addr[16];

    Serial.print("Motor MOT1 address: ");
    sprintf(addr, "0x%x", manager["MOT1"]);
    Serial.println(addr);

    Serial.print("Motor N_EX address: ");
    sprintf(addr, "0x%x", manager["N_EX"]);
    Serial.println(addr);

    delay(3000);
}