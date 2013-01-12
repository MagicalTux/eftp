// some common settings for EFTP that needs to be the same on both client & server

// block size is used to checksum of large files, to update large files
// without re-downloading the whole file. Put a smaller value if you have
// lots of changes on large files while not having much bandwidth.
#define EFTP_BLOCK (2*1024*1024)
