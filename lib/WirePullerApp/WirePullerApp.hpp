#ifndef WIREPULLERAPP_HPP
#define WIREPULLERAPP_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Globals.hpp>
#include <MotorManager.hpp>
#include <EndstopManager.hpp>
#include <JsonConstants.hpp>
#include <DeviceNames.hpp>
#include <string.h>

#include <Encoder.h>

//! Main application
template <uint BufferSizeValue>
class WirePuller {
public:
    //! Alias for buffer size
    static constexpr uint bufferSize = BufferSizeValue;

    //! ID string length
    static constexpr uint IDLength = DeviceName::MaxLength;

    //! Motor count
    static constexpr uint motorCount = 2;

    //! Endstop count
    static constexpr uint endstopCount = 4;

    //! Encoder count
    static constexpr uint encoderCount = 2;

    //! Maximal JSON nesting level
    static constexpr uint maxJsonNestLevel = 5;

    //! Initializes the object and I/O
    void initialize() {
        // initialize motors
        m_motors.initializeMotor(DeviceName::MotorXAxis, {6, 29, A2, 25, 24});
        m_motors.initializeMotor(DeviceName::MotorWheel, {7, 30, A0, 23, 22});

        // initialize endstops
        m_endstops.initializeEndstop(DeviceName::EndstopXAxisLeft, 32);
        m_endstops.initializeEndstop(DeviceName::EndstopXAxisRight, 33);
        m_endstops.initializeEndstop(DeviceName::EndstopWheelXAxisLeft, 34);
        m_endstops.initializeEndstop(DeviceName::EndstopWheelXAxisRight, 35);

        // initailze encoders
        // TODO
    }

    //! Excutes JSON in byte form, readed from stream
    /*!
        \param data Data with JSON to be parsed and executed
        \param response Pointer to char buffer in which response will be stored
    */
    bool execute(const char* data, char* response) {
        JsonObject& jsonData = m_jsonBuffer.parseObject(data, maxJsonNestLevel);
        JsonObject& jsonResponse = m_jsonBuffer.createObject();

        auto setError = [&jsonResponse, this](uint code){
            jsonResponse.set(JsonKey::Type, ResponseType::Error);
            jsonResponse.set(JsonKey::Data, getErrorJson(code));
        };


        if (jsonData != JsonObject::invalid()) {

            const char* request_type = jsonData.get<const char*>(JsonKey::Type);
            if (request_type != nullptr) {
                if (jsonData.containsKey(JsonKey::Data)) {

                    JsonObject& requestData = jsonData.get<JsonObject&>(JsonKey::Data);
                    if (requestData != JsonObject::invalid()) {
                        if (strcmp(request_type, RequestType::SetMotorSpeed) == 0) {
                            jsonResponse.set(JsonKey::Type, ResponseType::Data);
                            jsonResponse.set(JsonKey::Data, setMotorSpeed(requestData));
                        } else if (strcmp(request_type, RequestType::GetData) == 0) {
                            jsonResponse.set(JsonKey::Type, ResponseType::Data);
                            jsonResponse.set(JsonKey::Data, getData(requestData));
                        } else {
                            setError(5);
                        }
                    } else {
                        setError(4);
                    }
                } else {
                    setError(3);
                }
            } else {
                setError(2);
            }
        } else {
            setError(1);
        }

        auto bytes_written = jsonResponse.printTo(response, Globals::MaxJsonSize);
        m_jsonBuffer.clear();
        return bytes_written != 0;
    }

protected:
    
    JsonObject& setMotorSpeed(JsonObject& data) {
        JsonObject& responseData = m_jsonBuffer.createObject();
        
        return responseData;
    }

    JsonObject& getData(JsonObject& data) {
        JsonObject& responseData = m_jsonBuffer.createObject();

        return responseData;
    }

    JsonObject& getErrorJson(uint code) {
        JsonObject& data = m_jsonBuffer.createObject();

        if (code >= Error::Count) {
            data.set(JsonKey::ErrorCode, 0);
            data.set(JsonKey::ErrorMessage, Error::AppError[0]);
        } else {
            data.set(JsonKey::ErrorCode, code);
            data.set(JsonKey::ErrorMessage, Error::AppError[code]);
        }

        return data;
    }

    StaticJsonBuffer<bufferSize> m_jsonBuffer{};

    MotorManager<motorCount, IDLength> m_motors;
    EndstopManager<endstopCount, IDLength> m_endstops;
};

#endif