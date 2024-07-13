#ifndef _DOLPHIN_OS_OSUTIL_H
#define _DOLPHIN_OS_OSUTIL_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

// Macro to make it more clear when something is an address, and to prevent intellisense errors.
#ifdef __MWERKS__
#define AT_ADDRESS(addr) : (addr)
#else
#define AT_ADDRESS(addr)
#endif

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
