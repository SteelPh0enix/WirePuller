#ifndef JSONCONSTANTS_HPP
#define JSONCONSTANTS_HPP

enum class DataFlags : u8 { Motor = 1, Endstop = 2, Encoder = 4 };

namespace Error {
constexpr const char* AppError[]{"Unknown error",
                                 "Invalid JSON",
                                 "No type key in request JSON",
                                 "No data key in request JSON",
                                 "Data key does not contain a JSON object",
                                 "Request type not found"};

constexpr unsigned Count = sizeof(AppError) / sizeof(const char*);

}  // namespace Error

namespace JsonKey {
constexpr const char* Type = "type";
constexpr const char* Data = "data";

constexpr const char* ErrorCode = "code";
constexpr const char* ErrorMessage = "message";

constexpr const char* MotorSpeed = "speed";
constexpr const char* MotorCurrent = "current";
constexpr const char* MotorError = "error";

constexpr const char* MotorDataObject = "motors";
constexpr const char* EndstopDataObject = "endstops";
constexpr const char* EncoderDataObject = "encoders";

constexpr const char* DataRequestFlag = "flag";
}  // namespace JsonKey

namespace RequestType {
constexpr const char* SetMotorSpeed = "set_motor_speed";
constexpr const char* GetData = "data_request";
constexpr const char* ResetEncoder = "reset_encoder";
}  // namespace RequestType

namespace ResponseType {
constexpr const char* Error = "error";
constexpr const char* Data = "data";
}  // namespace ResponseType

#endif
