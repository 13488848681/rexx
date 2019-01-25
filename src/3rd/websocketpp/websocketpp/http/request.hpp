

#ifndef HTTP_PARSER_REQUEST_HPP
#define HTTP_PARSER_REQUEST_HPP

#include <string>

#include <websocketpp/common/memory.hpp>
#include <websocketpp/http/parser.hpp>

namespace websocketpp {
namespace http {
namespace parser {

/// Stores, parses, and manipulates HTTP requests
/**
 * http::request provides the following functionality for working with HTTP
 * requests.
 *
 * - Initialize request via manually setting each element
 * - Initialize request via reading raw bytes and parsing
 * - Once initialized, access individual parsed elements
 * - Once initialized, read entire request as raw bytes
 */
class request : public parser {
public:
    typedef request type;
    typedef lib::shared_ptr<type> ptr;

    request()
      : m_buf(lib::make_shared<std::string>())
      , m_ready(false) {}

    /// Process bytes in the input buffer
    /**
     * Process up to len bytes from input buffer buf. Returns the number of
     * bytes processed. Bytes left unprocessed means bytes left over after the
     * final header delimiters.
     *
     * Consume is a streaming processor. It may be called multiple times on one
     * request and the full headers need not be available before processing can
     * begin. If the end of the request was reached during this call to consume
     * the ready flag will be set. Further calls to consume once ready will be
     * ignored.
     *
     * Consume will throw an http::exception in the case of an error. Typical
     * error reasons include malformed requests, incomplete requests, and max
     * header size being reached.
     *
     * @param buf Pointer to byte buffer
     * @param len Size of byte buffer
     * @return Number of bytes processed.
     */
    size_t consume(char const * buf, size_t len);

    /// Returns whether or not the request is ready for reading.
    bool ready() const {
        return m_ready;
    }

    /// Returns the full raw request (including the body)
    std::string raw() const;
    
    /// Returns the raw request headers only (similar to an HTTP HEAD request)
    std::string raw_head() const;

    /// Set the HTTP method. Must be a valid HTTP token
    void set_method(std::string const & method);

    /// Return the request method
    std::string const & get_method() const {
        return m_method;
    }

    /// Set the HTTP uri. Must be a valid HTTP uri
    void set_uri(std::string const & uri);

    /// Return the requested URI
    std::string const & get_uri() const {
        return m_uri;
    }

private:
    /// Helper function for message::consume. Process request line
    void process(std::string::iterator begin, std::string::iterator end);

    lib::shared_ptr<std::string>    m_buf;
    std::string                     m_method;
    std::string                     m_uri;
    bool                            m_ready;
};

} // namespace parser
} // namespace http
} // namespace websocketpp

#include <websocketpp/http/impl/request.hpp>

#endif // HTTP_PARSER_REQUEST_HPP
