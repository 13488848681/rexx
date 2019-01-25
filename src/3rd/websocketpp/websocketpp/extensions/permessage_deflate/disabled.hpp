

#ifndef WEBSOCKETPP_EXTENSION_PERMESSAGE_DEFLATE_DISABLED_HPP
#define WEBSOCKETPP_EXTENSION_PERMESSAGE_DEFLATE_DISABLED_HPP

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/common/system_error.hpp>

#include <websocketpp/http/constants.hpp>
#include <websocketpp/extensions/extension.hpp>

#include <map>
#include <string>
#include <utility>

namespace websocketpp {
namespace extensions {
namespace permessage_deflate {

/// Stub class for use when disabling permessage_deflate extension
/**
 * This class is a stub that implements the permessage_deflate interface
 * with minimal dependencies. It is used to disable permessage_deflate
 * functionality at compile time without loading any unnecessary code.
 */
template <typename config>
class disabled {
    typedef std::pair<lib::error_code,std::string> err_str_pair;

public:
    /// Negotiate extension
    /**
     * The disabled extension always fails the negotiation with a disabled 
     * error.
     *
     * @param offer Attribute from client's offer
     * @return Status code and value to return to remote endpoint
     */
    err_str_pair negotiate(http::attribute_list const &) {
        return make_pair(make_error_code(error::disabled),std::string());
    }

    /// Returns true if the extension is capable of providing
    /// permessage_deflate functionality
    bool is_implemented() const {
        return false;
    }

    /// Returns true if permessage_deflate functionality is active for this
    /// connection
    bool is_enabled() const {
        return false;
    }

    /// Compress bytes
    /**
     * @param [in] in String to compress
     * @param [out] out String to append compressed bytes to
     * @return Error or status code
     */
    lib::error_code compress(std::string const &, std::string &) {
        return make_error_code(error::disabled);
    }

    /// Decompress bytes
    /**
     * @param buf Byte buffer to decompress
     * @param len Length of buf
     * @param out String to append decompressed bytes to
     * @return Error or status code
     */
    lib::error_code decompress(uint8_t const *, size_t, std::string &) {
        return make_error_code(error::disabled);
    }
};

} // namespace permessage_deflate
} // namespace extensions
} // namespace websocketpp

#endif // WEBSOCKETPP_EXTENSION_PERMESSAGE_DEFLATE_DISABLED_HPP
