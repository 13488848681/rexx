

#ifndef WEBSOCKETPP_VERSION_HPP
#define WEBSOCKETPP_VERSION_HPP

/// Namespace for the WebSocket++ project
namespace websocketpp {

/*
 other places where version information is kept
 - readme.md
 - changelog.md
 - Doxyfile
 - CMakeLists.txt
*/

/// Library major version number
static int const major_version = 0;
/// Library minor version number
static int const minor_version = 6;
/// Library patch version number
static int const patch_version = 1;
/// Library pre-release flag
/**
 * This is a textual flag indicating the type and number for pre-release
 * versions (dev, alpha, beta, rc). This will be blank for release versions.
 */
static char const prerelease_flag[] = "";

/// Default user agent string
static char const user_agent[] = "WebSocket++/0.6.0";

} // namespace websocketpp

#endif // WEBSOCKETPP_VERSION_HPP
