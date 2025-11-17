#ifndef MAC_COMPAT_H
#define MAC_COMPAT_H

#ifdef __APPLE__

// macOS compatibility layer for Windows-specific functions
#include <time.h>


#define Sleep(ms) do { \
    struct timespec ts; \
    ts.tv_sec = (ms) / 1000; \
    ts.tv_nsec = ((ms) % 1000) * 1000000; \
    nanosleep(&ts, NULL); \
} while (0)

#endif // __APPLE__

#endif // MAC_COMPAT_H
