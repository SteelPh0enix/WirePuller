#ifndef WIREPULLERAPP_HPP
#define WIREPULLERAPP_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Globals.hpp>
#include <Span.hpp>
#include <MotorManager.hpp>
#include <EndstopManager.hpp>

//! Main application
template <uint BufferSizeValue>
class WirePuller {
public:
    static constexpr uint BufferSize = BufferSizeValue;
    //! Initializes the object and I/O
    void initialize() {
        // Put I/O initialization here
    }

    //! Excutes JSON in byte form, readed from stream
    /*!
        \param jsonBytes Bytes object with pointer to data and size of it
    */
    void execute(Span<byte, BufferSize> jsonBytes) {
        
    }

protected:
    StaticJsonBuffer<BufferSize> m_jsonBuffer{};

    MotorManager<2, 3> m_motors;
    EndstopManager<4, 3> m_endstops;
};

#endif