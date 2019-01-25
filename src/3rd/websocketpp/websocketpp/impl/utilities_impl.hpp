

#ifndef WEBSOCKETPP_UTILITIES_IMPL_HPP
#define WEBSOCKETPP_UTILITIES_IMPL_HPP

#include <algorithm>
#include <string>

namespace websocketpp {
namespace utility {

inline std::string to_lower(std::string const & in) {
    std::string out = in;
    std::transform(out.begin(),out.end(),out.begin(),::tolower);
    return out;
}

inline std::string to_hex(std::string const & input) {
    std::string output;
    std::string hex = "0123456789ABCDEF";

    for (size_t i = 0; i < input.size(); i++) {
        output += hex[(input[i] & 0xF0) >> 4];
        output += hex[input[i] & 0x0F];
        output += " ";
    }

    return output;
}

inline std::string to_hex(uint8_t const * input, size_t length) {
    std::string output;
    std::string hex = "0123456789ABCDEF";

    for (size_t i = 0; i < length; i++) {
        output += hex[(input[i] & 0xF0) >> 4];
        output += hex[input[i] & 0x0F];
        output += " ";
    }

    return output;
}

inline std::string to_hex(const char* input,size_t length) {
    return to_hex(reinterpret_cast<const uint8_t*>(input),length);
}

inline std::string string_replace_all(std::string subject, std::string const &
    search, std::string const & replace)
{
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

} // namespace utility
} // namespace websocketpp

#endif // WEBSOCKETPP_UTILITIES_IMPL_HPP
