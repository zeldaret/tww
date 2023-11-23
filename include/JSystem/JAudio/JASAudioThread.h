#ifndef JASAUDIOTHREAD_H
#define JASAUDIOTHREAD_H

#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSThread.h>
#include "global.h"

class JKRSolidHeap;

namespace JASystem {
    namespace TAudioThread {
        void syncAudio();
        void* audioproc(void*);
        void syncDSP(void*);
        void setPriority(u8, u8);
        void start(JKRSolidHeap*, u32, u32);

        extern OSThread sAudioThread;
        extern u8 saAudioStack[4096] ALIGN_DECL(32);
        extern OSMessageQueue sAudioprocMQ;
        extern OSMessage saAudioMsgBuf[16];
        extern u32 sAudioprocMQInit;
        extern int sbIsPrioritySet;
        extern s32 sDSPPrio;
        extern s32 sDVDPrio;
        extern vs32 snIntCount;
        extern int sbIsDSPBoot;
    };
}

#endif /* JASAUDIOTHREAD_H */
