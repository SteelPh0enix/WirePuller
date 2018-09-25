#ifndef WIREPULLERAPP_HPP
#define WIREPULLERAPP_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Globals.hpp>
#include <MotorManager.hpp>
#include <EndstopManager.hpp>
#include <string.h>

//! Main application
template <uint BufferSizeValue>
class WirePuller {
public:
    //! Alias for buffer size
    static constexpr uint bufferSize = BufferSizeValue;

    //! ID string length
    static constexpr uint IDLength = 15;

    //! Maximal motor count
    static constexpr uint motorCount = 3;

    //! Maximal endstop
    static constexpr uint endstopCount = 4;

    //! Initializes the object and I/O
    void initialize() {
        // initialize motors (names are temporary)
        m_motors.initializeMotor("MOTOR_1", {6, 29, A2, 25, 24});
        m_motors.initializeMotor("MOTOR_2", {7, 30, A0, 23, 22});
        m_motors.initializeMotor("MOTOR_3", {8, 31, A1, 23, 22});

        m_endstops.initializeEndstop("ENDSTOP_1", 32);
        m_endstops.initializeEndstop("ENDSTOP_2", 33);
        m_endstops.initializeEndstop("ENDSTOP_3", 34);
        m_endstops.initializeEndstop("ENDSTOP_4", 35);
    }

    //! Excutes JSON in byte form, readed from stream
    /*!
        \param data Data with JSON to be parsed and executed
        \param response Pointer to char buffer in which response will be stored

        \invariant Buffer must have enought capacity to store a response, or program will most probably crash

    */
    bool execute(const char* data, char* response) {
        strcpy(response, data);
        return true;
    }

protected:
    StaticJsonBuffer<bufferSize> m_jsonBuffer{};

    MotorManager<motorCount, IDLength> m_motors;
    EndstopManager<endstopCount, IDLength> m_endstops;
};

#endif