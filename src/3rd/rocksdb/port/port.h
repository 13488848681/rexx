
#pragma once

#include <string>

// Include the appropriate platform specific file below.  If you are
// porting to a new platform, see "port_example.h" for documentation
// of what the new port_<platform>.h file must provide.
#if defined(ROCKSDB_PLATFORM_POSIX)
#include "port/port_posix.h"
#endif

