#ifndef MAC_COMPAT_H
#define MAC_COMPAT_H

// macOS compatibility layer for Windows-specific functions
#include <unistd.h>


#define Sleep(ms) usleep((ms) * 1000)

#endif // MAC_COMPAT_H
