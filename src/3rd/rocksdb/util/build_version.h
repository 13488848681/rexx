
#pragma once
#if !defined(IOS_CROSS_COMPILE)
// if we compile with Xcode, we don't run build_detect_vesion, so we don't
// generate these variables
// this variable tells us about the git revision
extern const char* rocksdb_build_git_sha;

// Date on which the code was compiled:
extern const char* rocksdb_build_compile_date;
#endif
