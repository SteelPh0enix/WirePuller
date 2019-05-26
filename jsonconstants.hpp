#ifndef JSONCONSTANTS_HPP
#define JSONCONSTANTS_HPP

namespace JsonKey {
constexpr char const* Type = "type";
constexpr char const* Data = "data";

constexpr char const* ErrorCode = "code";
constexpr char const* ErrorMessage = "message";

constexpr char const* MotorSpeed = "speed";
constexpr char const* MotorCurrent = "current";
constexpr char const* MotorError = "error";

constexpr char const* MotorDataObject = "motors";
constexpr char const* EndstopDataObject = "endstops";
constexpr char const* EncoderDataObject = "encoders";

constexpr char const* DataRequestFlag = "flag";
}  // namespace JsonKey

namespace JsonValue {
namespace RequestType {
constexpr char const* SetMotorSpeed = "set_motor_speed";
constexpr char const* GetData = "data_request";
constexpr char const* ResetEncoder = "reset_encoder";
}  // namespace RequestType

namespace ResponseType {
constexpr char const* Error = "error";
constexpr char const* Data = "data";
}  // namespace ResponseType
}  // namespace JsonValue

#endif  // JSONCONSTANTS_HPP
