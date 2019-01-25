#ifndef __CURL_CURLVER_H
#define __CURL_CURLVER_H

#define LIBCURL_COPYRIGHT "1996 - 2016 Daniel Stenberg, <daniel@haxx.se>."

/* This is the version number of the libcurl package from which this header
   file origins: */
#define LIBCURL_VERSION "7.47.1"

/* The numeric version number is also available "in parts" by using these
   defines: */
#define LIBCURL_VERSION_MAJOR 7
#define LIBCURL_VERSION_MINOR 47
#define LIBCURL_VERSION_PATCH 1

#define LIBCURL_VERSION_NUM 0x072f01

#define LIBCURL_TIMESTAMP "Mon Feb  8 09:27:16 UTC 2016"

#define CURL_VERSION_BITS(x,y,z) ((x)<<16|(y)<<8|z)
#define CURL_AT_LEAST_VERSION(x,y,z) \
  (LIBCURL_VERSION_NUM >= CURL_VERSION_BITS(x, y, z))

#endif /* __CURL_CURLVER_H */
