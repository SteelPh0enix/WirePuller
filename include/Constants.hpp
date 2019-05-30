#pragma once

namespace Constant {
namespace Serial {
constexpr unsigned long BaudRate{115200};
constexpr char LineTerminator{'\n'};
}  // namespace Serial

namespace Json {
constexpr size_t DocumentSize{256};

namespace Key {
constexpr char const* const GeneralError{"Error"};
constexpr char const* const ParsingError{"ParseError"};

constexpr char const* const RequestType{"Request"};
constexpr char const* const RequestError{"RequestError"};

constexpr char const* const RequestData{"Data"};

constexpr char const* const Callibration{"Callibration"};

constexpr char const* const EncoderTicks{"EncoderTicks"};
constexpr char const* const EndstopLeft{"EndstopLeft"};
constexpr char const* const EndstopRight{"EndstopRight"};

namespace Motor {
constexpr char const* const Name{"MotorName"};
constexpr char const* const Power{"Power"};
constexpr char const* const Current{"Current"};
constexpr char const* const Error{"Error"};
}  // namespace Motor

namespace AxisName {
constexpr char const* const X{"X"};
constexpr char const* const Wheel{"Wheel"};
constexpr char const* const Breaker{"Breaker"};
}  // namespace AxisName
}  // namespace Key

namespace Value {
constexpr char const* const OK{"OK"};

namespace GeneralError {
constexpr char const* const InitializationFailed{"InitializationFailed"};
}
namespace RequestType {
constexpr char const* const Callibrate{"Callibrate"};
constexpr char const* const SetPower{"SetPower"};
constexpr char const* const GetData{"GetData"};
constexpr char const* const ResetEncoder{"ResetEncoder"};
}  // namespace RequestType

namespace RequestError {
constexpr char const* const NoRequestType{"NoRequestType"};
constexpr char const* const InvalidRequestType{"InvalidRequest"};
constexpr char const* const NoData{"NoData"};
}  // namespace RequestError

}  // namespace Value
}  // namespace Json
}  // namespace Constant