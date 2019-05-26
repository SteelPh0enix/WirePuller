#ifndef MESSAGETYPES_HPP
#define MESSAGETYPES_HPP

namespace Message {
enum class RequestType { Invalid, SetMotorSpeed, GetData, ResetEncoder };

enum class ResponseType { Invalid, Error, Data };

enum class DataFlag { Motor = 1, Endstop = 2, Encoder = 4 };
}  // namespace Message

#endif  // MESSAGETYPES_HPP
