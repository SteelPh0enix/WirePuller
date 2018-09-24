#ifndef WIREPULLERAPP_HPP
#define WIREPULLERAPP_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Globals.hpp>
#include <Utils.hpp>

//! Main application
template <uint MaxBufferSize>
class WirePuller {
public:
    static constexpr uint BufferSize = MaxBufferSize;
    //! Initializes the object and I/O
    void initialize() {

    }

    //! Excutes JSON in byte form, readed from stream
    /*!
        \param jsonBytes Bytes object with pointer to data and size of it
    */
    void execute(Bytes<BufferSize> jsonBytes) {

    }

protected:
    StaticJsonBuffer<BufferSize> m_jsonBuffer{};
};

#endif