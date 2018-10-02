#ifndef JSONCONSTANTS_HPP
#define JSONCONSTANTS_HPP

enum class DataFlags : u8 { Motor = 1, Endstop = 2, Encoder = 4 };

namespace Error {
constexpr char const* AppError[]{"Unknown error",
                                 "Invalid JSON",
                                 "No type key in request JSON",
                                 "No data key in request JSON",
                                 "Data key does not contain a JSON object",
                                 "Request type not found"};

constexpr unsigned Count = sizeof(AppError) / sizeof(char const*);

}  // namespace Error

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

namespace RequestType {
constexpr char const* SetMotorSpeed = "set_motor_speed";
constexpr char const* GetData = "data_request";
constexpr char const* ResetEncoder = "reset_encoder";
}  // namespace RequestType

namespace ResponseType {
constexpr char const* Error = "error";
constexpr char const* Data = "data";
}  // namespace ResponseType

#endif
