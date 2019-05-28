#pragma once

namespace Constant {
namespace Serial {
constexpr unsigned long BaudRate{115200};
constexpr char LineTerminator{'\n'};
}  // namespace Serial

namespace Json {
constexpr size_t DocumentSize{256};

namespace Key {
constexpr char* const ParsingError{"PARSE_ERROR"};
}
}  // namespace Json
}  // namespace Constant