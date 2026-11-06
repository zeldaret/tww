#ifndef JASDSPBUF_H
#define JASDSPBUF_H

#include "dolphin/types.h"

namespace JASystem {
    namespace TDSP_DACBuffer {
        void init();
        void updateDSP();
        s16* mixDSP(s32);
        void finishDSPFrame();

        extern u8 numDSPBuf;
        extern int isInit;
        extern s16** dsp_buf;
        extern u8 writeBuffer;
        extern u8 readBuffer;
        extern u8 dspStatus;
        extern int dacSyncCounter;
        extern void (*callback)(s16*, u32);
    }
}

#endif /* JASDSPBUF_H */
