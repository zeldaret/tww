#ifndef DVDFS_H
#define DVDFS_H

#include "dolphin/types.h"
#include "dolphin/os/OS.h"

extern struct OSThreadQueue __DVDThreadQueue;
extern u32 __DVDLongFileNameFlag;

void __DVDFSInit();

#endif /* DVDFS_H */
