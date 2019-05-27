#pragma once
#include <Arduino.h>
#include <stdint.h>

namespace Pin {
namespace XAxis {
namespace MotorDriver {
constexpr uint8_t PWM{7};
constexpr uint8_t Direction{28};
constexpr uint8_t Feedback{A0};
constexpr uint8_t Disable{23};
constexpr uint8_t StatusFlag{22};
}  // namespace MotorDriver
namespace Endstop {
constexpr uint8_t Left{33};
constexpr uint8_t Right{32};
}  // namespace Endstop
namespace Encoder {
constexpr uint8_t A{18};
constexpr uint8_t B{19};
}  // namespace Encoder
}  // namespace XAxis
namespace WheelAxis {
namespace MotorDriver {
constexpr uint8_t PWM{8};
constexpr uint8_t Direction{29};
constexpr uint8_t Feedback{A1};
constexpr uint8_t Disable{23};
constexpr uint8_t StatusFlag{22};
}  // namespace MotorDriver
namespace Endstop {
constexpr uint8_t Left{35};
constexpr uint8_t Right{34};
}  // namespace Endstop
namespace Encoder {
constexpr uint8_t A{20};
constexpr uint8_t B{21};
}  // namespace Encoder
}  // namespace WheelAxis
namespace BreakerAxis {
namespace MotorDriver {
constexpr uint8_t PWM{6};
constexpr uint8_t Direction{31};
constexpr uint8_t Feedback{A2};
constexpr uint8_t Disable{26};
constexpr uint8_t StatusFlag{25};
}  // namespace MotorDriver
// This is disabled due to lack of endstops and encoder on breaker axis.
/*
namespace Endstop {
constexpr uint8_t Left{};
constexpr uint8_t Right{};
}  // namespace Endstop
namespace Encoder {
constexpr uint8_t A{};
constexpr uint8_t B{};
}  // namespace Encoder
*/
}  // namespace BreakerAxis
}  // namespace Pin
