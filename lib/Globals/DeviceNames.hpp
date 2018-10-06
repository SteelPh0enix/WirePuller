#ifndef DEVICENAMES_HPP
#define DEVICENAMES_HPP

namespace DeviceName {
constexpr char const* MotorXAxis = "MOT_OX";
constexpr char const* MotorWheel = "MOT_WH";

constexpr char const* EndstopXAxisRight = "END_OX_R";
constexpr char const* EndstopXAxisLeft = "END_OX_L";
constexpr char const* EndstopWheelXAxisRight = "END_WH_R";
constexpr char const* EndstopWheelXAxisLeft = "END_WH_L";

constexpr char const* EncoderXAxis = "ENC_OX";
constexpr char const* EncoderWheel = "ENC_WH";

constexpr unsigned MaxLength = 10u;
}  // namespace DeviceName

#endif
