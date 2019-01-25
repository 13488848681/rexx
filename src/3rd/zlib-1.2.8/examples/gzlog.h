#ifndef GZLOG_H
#define GZLOG_H

/* gzlog object type */
typedef void gzlog;

/* Open a gzlog object, creating the log file if it does not exist.  Return
   NULL on error.  Note that gzlog_open() could take a while to complete if it
   has to wait to verify that a lock is stale (possibly for five minutes), or
   if there is significant contention with other instantiations of this object
   when locking the resource.  path is the prefix of the file names created by
   this object.  If path is "foo", then the log file will be "foo.gz", and
   other auxiliary files will be created and destroyed during the process:
   "foo.dict" for a compression dictionary, "foo.temp" for a temporary (next)
   dictionary, "foo.add" for data being added or compressed, "foo.lock" for the
   lock file, and "foo.repairs" to log recovery operations performed due to
   interrupted gzlog operations.  A gzlog_open() followed by a gzlog_close()
   will recover a previously interrupted operation, if any. */
gzlog *gzlog_open(char *path);

/* Write to a gzlog object.  Return zero on success, -1 if there is a file i/o
   error on any of the gzlog files (this should not happen if gzlog_open()
   succeeded, unless the device has run out of space or leftover auxiliary
   files have permissions or ownership that prevent their use), -2 if there is
   a memory allocation failure, or -3 if the log argument is invalid (e.g. if
   it was not created by gzlog_open()).  This function will write data to the
   file uncompressed, until 1 MB has been accumulated, at which time that data
   will be compressed.  The log file will be a valid gzip file upon successful
   return. */
int gzlog_write(gzlog *log, void *data, size_t len);

/* Force compression of any uncompressed data in the log.  This should be used
   sparingly, if at all.  The main application would be when a log file will
   not be appended to again.  If this is used to compress frequently while
   appending, it will both significantly increase the execution time and
   reduce the compression ratio.  The return codes are the same as for
   gzlog_write(). */
int gzlog_compress(gzlog *log);

/* Close a gzlog object.  Return zero on success, -3 if the log argument is
   invalid.  The log object is freed, and so cannot be referenced again. */
int gzlog_close(gzlog *log);

#endif
