#ifndef JSONCONSTANTS_HPP
#define JSONCONSTANTS_HPP

struct ParseError {
    const char* message;
    unsigned code;
};

enum class DataFlags : u8 {
    Motor   = 1,
    Endstop = 2,
    Encoder = 4
};

namespace JsonKey {
    constexpr const char* Type = "type";
    constexpr const char* Data = "data";
    constexpr const char* Error = "error";

    const char* ErrorCode = "code";
    constexpr const char* ErrorMessage = "message";

    constexpr const char* MotorSpeed = "speed";
    constexpr const char* MotorCurrent = "current";
    constexpr const char* MotorError = "error";

    constexpr const char* MotorDataObject = "motors";
    constexpr const char* EndstopDataObject = "endstops";
    constexpr const char* EncoderDataObject = "encoders";
}

namespace RequestType {
    constexpr const char* Error = "error";
    constexpr const char* SetMotorSpeed = "set_motor_speed";
    constexpr const char* GetData = "data_request";
}

namespace ResponseType {
    constexpr const char* Error = "error";
    constexpr const char* Data = "data";
}

namespace JsonError {
    constexpr auto UnknownError = ParseError{"Unknown error happened", 0};
    constexpr auto NoTypeKey = ParseError{"No type key in request JSON", 1};
    constexpr auto NoDataKey = ParseError{"No data key in request JSON", 2};
}

#endif