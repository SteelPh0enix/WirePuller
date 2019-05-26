#ifndef DEVICENAMES_HPP
#define DEVICENAMES_HPP

namespace DeviceName {
constexpr char const* MotorXAxis = "MOT_OX";
constexpr char const* MotorWheel = "MOT_WH";
constexpr char const* MotorBreakerAxis = "MOT_BK";

constexpr char const* EndstopXAxisRight = "END_OX_R";
constexpr char const* EndstopXAxisLeft = "END_OX_L";
constexpr char const* EndstopWheelXAxisRight = "END_WH_R";
constexpr char const* EndstopWheelXAxisLeft = "END_WH_L";
constexpr char const* EndstopBreakerAxisLeft = "END_BK_L";
constexpr char const* EndstopBreakerAxisRight = "END_BK_R";

constexpr char const* EncoderXAxis = "ENC_OX";
constexpr char const* EncoderWheel = "ENC_WH";
constexpr char const* EncoderBreakerAxis = "ENC_BK";

constexpr unsigned MaxLength = 10u;
}  // namespace DeviceName

#endif  // DEVICENAMES_HPP
