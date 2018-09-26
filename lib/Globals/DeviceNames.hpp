#ifndef DEVICENAMES_HPP
#define DEVICENAMES_HPP

namespace DeviceName {
constexpr const char* MotorXAxis = "MOT_OX";
constexpr const char* MotorWheel = "MOT_WH";

constexpr const char* EndstopXAxisRight = "END_OX_R";
constexpr const char* EndstopXAxisLeft = "END_OX_L";
constexpr const char* EndstopWheelXAxisRight = "END_WH_R";
constexpr const char* EndstopWheelXAxisLeft = "END_WH_L";

constexpr const char* EncoderXAxis = "ENC_OX";
constexpr const char* EncoderWheel = "ENC_WH";

constexpr unsigned MaxLength = 10u;
}  // namespace DeviceName

#endif
