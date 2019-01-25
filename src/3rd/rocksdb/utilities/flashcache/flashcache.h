
#pragma once

#include <string>
#include "rocksdb/env.h"

namespace rocksdb {

// This is internal API that will make hacking on flashcache easier. Not sure if
// we need to expose this to public users, probably not
extern int FlashcacheBlacklistCurrentThread(Env* flashcache_aware_env);
extern int FlashcacheWhitelistCurrentThread(Env* flashcache_aware_env);

}  // namespace rocksdb
