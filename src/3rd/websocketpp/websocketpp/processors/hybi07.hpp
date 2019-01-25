

#ifndef WEBSOCKETPP_PROCESSOR_HYBI07_HPP
#define WEBSOCKETPP_PROCESSOR_HYBI07_HPP

#include <websocketpp/processors/hybi08.hpp>

#include <string>
#include <vector>

namespace websocketpp {
namespace processor {

/// Processor for Hybi Draft version 07
/**
 * The primary difference between 07 and 08 is a version number.
 */
template <typename config>
class hybi07 : public hybi08<config> {
public:
    typedef typename config::request_type request_type;

    typedef typename config::con_msg_manager_type::ptr msg_manager_ptr;
    typedef typename config::rng_type rng_type;

    explicit hybi07(bool secure, bool p_is_server, msg_manager_ptr manager, rng_type& rng)
      : hybi08<config>(secure, p_is_server, manager, rng) {}

    /// Fill in a set of request headers for a client connection request
    /**
     * The Hybi 07 processor only implements incoming connections so this will
     * always return an error.
     *
     * @param [out] req  Set of headers to fill in
     * @param [in] uri The uri being connected to
     * @param [in] subprotocols The list of subprotocols to request
     */
    lib::error_code client_handshake_request(request_type &, uri_ptr,
        std::vector<std::string> const &) const
    {
        return error::make_error_code(error::no_protocol_support);
    }

    int get_version() const {
        return 7;
    }
private:
};

} // namespace processor
} // namespace websocketpp

#endif //WEBSOCKETPP_PROCESSOR_HYBI07_HPP
