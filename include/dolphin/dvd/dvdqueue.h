#ifndef DVDQUEUE_H
#define DVDQUEUE_H

#include "dolphin/dvd/dvd.h"

void __DVDClearWaitingQueue();
int __DVDPushWaitingQueue(long prio, DVDCommandBlock * block);
struct DVDCommandBlock * __DVDPopWaitingQueue();
int __DVDCheckWaitingQueue();
int __DVDDequeueWaitingQueue(DVDCommandBlock * block);
int __DVDIsBlockInWaitingQueue(DVDCommandBlock * block);

#endif /* DVDQUEUE_H */
