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
}  // namespace Key

namespace Value {
namespace GeneralError {
constexpr char const* const InitializationFailed{"InitializationFailed"};
}
namespace RequestType {
constexpr char const* const Callibrate{"Callibrate"};
constexpr char const* const SetPower{"SetPower"};
}  // namespace RequestType

namespace RequestError {
constexpr char const* const NoRequestType{"NoRequestType"};
constexpr char const* const InvalidRequestType{"InvalidRequest"};
}  // namespace RequestError
}  // namespace Value
}  // namespace Json
}  // namespace Constant