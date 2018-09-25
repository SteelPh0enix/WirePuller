#ifndef JSONCONSTANTS_HPP
#define JSONCONSTANTS_HPP

struct AppError {
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

    constexpr const char* ErrorCode = "code";
    constexpr const char* ErrorMessage = "message";

    constexpr const char* MotorSpeed = "speed";
    constexpr const char* MotorCurrent = "current";
    constexpr const char* MotorError = "error";

    constexpr const char* MotorDataObject = "motors";
    constexpr const char* EndstopDataObject = "endstops";
    constexpr const char* EncoderDataObject = "encoders";
}

namespace RequestType {
    constexpr const char* SetMotorSpeed = "set_motor_speed";
    constexpr const char* GetData = "data_request";
}

namespace ResponseType {
    constexpr const char* Error = "error";
    constexpr const char* Data = "data";
}

namespace JsonError {
    constexpr auto UnknownError = AppError{"Unknown error happened", 0};
    constexpr auto InvalidJson = AppError{"Invalid JSON", 1};
    constexpr auto NoTypeKey = AppError{"No type key in request JSON", 2};
    constexpr auto NoDataKey = AppError{"No data key in request JSON", 3};
}

#endif