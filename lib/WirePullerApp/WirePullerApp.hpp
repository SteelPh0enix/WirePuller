#ifndef WIREPULLERAPP_HPP
#define WIREPULLERAPP_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
#include <DeviceNames.hpp>
#include <EncoderManager.hpp>
#include <EndstopManager.hpp>
#include <Globals.hpp>
#include <JsonConstants.hpp>
#include <MotorManager.hpp>

//! Main application
template <uint BufferSizeValue>
class WirePuller {
 public:
  //! Alias for buffer size
  static constexpr uint bufferSize = BufferSizeValue;

  //! ID string length
  static constexpr uint IDLength = DeviceName::MaxLength;

  //! Motor count
  static constexpr uint motorCount = 3;

  //! Endstop count
  static constexpr uint endstopCount = 4;

  //! Encoder count
  static constexpr uint encoderCount = 2;

  //! Maximal JSON nesting level
  static constexpr uint maxJsonNestLevel = 5;

  //! Initializes the object and I/O
  void initialize() {
    // initialize motors
    m_motors.initializeMotor(DeviceName::MotorXAxis,
                             {7, 28, A0, 23, 22});  // M1
    m_motors.initializeMotor(DeviceName::MotorWheel,
                             {8, 29, A1, 23, 22});  // M2
    m_motors.initializeMotor(DeviceName::MotorBreakerAxis,
                             {6, 31, A2, 26, 25});  // M3

    // initialize endstops
    m_endstops.initializeEndstop(DeviceName::EndstopXAxisLeft, 32);
    m_endstops.initializeEndstop(DeviceName::EndstopXAxisRight, 33);
    m_endstops.initializeEndstop(DeviceName::EndstopWheelXAxisLeft, 34);
    m_endstops.initializeEndstop(DeviceName::EndstopWheelXAxisRight, 35);

    // initailze encoders
    m_encoders.initializeEncoder(DeviceName::EncoderXAxis);
    m_encoders.initializeEncoder(DeviceName::EncoderWheel);
  }

  //! Excutes JSON in byte form, readed from stream
  /*!
      \param data Data with JSON to be parsed and executed
      \param response Pointer to char buffer in which response will be stored
  */
  bool execute(char const* data, char* response) {
    JsonObject& jsonData = m_jsonBuffer.parseObject(data, maxJsonNestLevel);
    JsonObject& jsonResponse = m_jsonBuffer.createObject();

    auto setError = [&jsonResponse, this](uint code) {
      jsonResponse.set(JsonKey::Type, ResponseType::Error);
      jsonResponse.set(JsonKey::Data, getErrorJson(code));
    };

    if (jsonData != JsonObject::invalid()) {
      char const* request_type = jsonData.get<char const*>(JsonKey::Type);
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
            } else if (strcmp(request_type, RequestType::ResetEncoder) == 0) {
              jsonResponse.set(JsonKey::Type, ResponseType::Data);
              jsonResponse.set(JsonKey::Data, resetEncoders(requestData));
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

  void endstopCheck() {
    // TODO: test this, because i don't know which endstop is for which
    // direction. Rewire the motors if necessary.

    auto* leftXEndstop = m_endstops[DeviceName::EndstopXAxisLeft];
    auto* rightXEndstop = m_endstops[DeviceName::EndstopXAxisRight];
    auto* wheelLeftEndstop = m_endstops[DeviceName::EndstopWheelXAxisLeft];
    auto* wheelRightEndstop = m_endstops[DeviceName::EndstopWheelXAxisRight];
    auto* xMotor = m_motors[DeviceName::MotorXAxis];
    auto* wheelMotor = m_motors[DeviceName::MotorWheel];

    if (leftXEndstop->state() && xMotor->speed() > 0)
      xMotor->speed(0);
    if (rightXEndstop->state() && xMotor->speed() < 0)
      xMotor->speed(0);

    if (wheelLeftEndstop->state() && wheelMotor->speed() > 0)
      wheelMotor->speed(0);
    if (wheelRightEndstop->state() && wheelMotor->speed() < 0)
      wheelMotor->speed(0);
  }

 protected:
  JsonObject& setMotorSpeed(JsonObject& data) {
    for (auto const& motorData : data) {
      PololuMC33926* motor = m_motors[motorData.key];

      if (motor == nullptr)
        continue;

      motor->speed(motorData.value.as<int>());
    }

    JsonObject& responseData = m_jsonBuffer.createObject();
    responseData.set(JsonKey::MotorDataObject, getMotorData());
    return responseData;
  }

  JsonObject& getData(JsonObject& data) {
    JsonObject& responseData = m_jsonBuffer.createObject();
    u8 flag = data.get<u8>(JsonKey::DataRequestFlag);

    if (flag & static_cast<u8>(DataFlags::Motor))
      responseData.set(JsonKey::MotorDataObject, getMotorData());

    if (flag & static_cast<u8>(DataFlags::Endstop))
      responseData.set(JsonKey::EndstopDataObject, getEndstopData());

    if (flag & static_cast<u8>(DataFlags::Encoder))
      responseData.set(JsonKey::EncoderDataObject, getEncoderData());

    return responseData;
  }

  JsonObject& resetEncoders(JsonObject& data) {
    JsonObject& responseData = m_jsonBuffer.createObject();
    for (auto const& encoderData : data) {
      Encoder* encoder = m_encoders[encoderData.key];

      if (encoder == nullptr)
        continue;

      if (encoderData.value.as<bool>())
        encoder->write(0);
    }
    return responseData;
  }

  JsonObject& getMotorData() {
    JsonObject& responseData = m_jsonBuffer.createObject();
    for (const auto& motor : m_motors) {
      JsonObject& motorData = m_jsonBuffer.createObject();
      motorData.set(JsonKey::MotorSpeed, motor.motor.speed());
      motorData.set(JsonKey::MotorCurrent, motor.motor.current());
      motorData.set(JsonKey::MotorError, motor.motor.error());
      responseData.set(motor.id, motorData);
    }
    return responseData;
  }

  JsonObject& getEndstopData() {
    JsonObject& responseData = m_jsonBuffer.createObject();
    for (const auto& endstop : m_endstops) {
      responseData.set(endstop.id, endstop.endstop.state());
    }
    return responseData;
  }

  JsonObject& getEncoderData() {
    JsonObject& responseData = m_jsonBuffer.createObject();
    for (auto& encoder : m_encoders) {
      responseData.set(encoder.id, encoder.encoder.read());
    }
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
  EncoderManager<encoderCount, IDLength> m_encoders;
};

#endif
