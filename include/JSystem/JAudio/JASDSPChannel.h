#ifndef JASDSPCHANNEL_H
#define JASDSPCHANNEL_H

#include "dolphin/os/OSTime.h"

namespace JASystem {
    namespace DSPInterface {
        class DSPBuffer;
    }

    extern OSTick history[];
    extern f32 DSP_LIMIT_RATIO;
    extern OSTick old_time;

    class TDSPChannel {
    public:
        TDSPChannel() {
            field_0xc = NULL;
            mCallback = NULL;
        }
        ~TDSPChannel() {}
        void init(u8);
        int allocate(u32);
        void free();
        bool forceStop();
        void forceDelete();
        void play();
        void stop();
        static void initAll();
        static TDSPChannel* alloc(u32, u32);
        static int free(TDSPChannel*, u32);
        static TDSPChannel* getLower();
        static TDSPChannel* getLowerActive();
        static BOOL breakLower(u8);
        static bool breakLowerActive(u8);
        static void updateAll();
        void onUpdate(u32);
        static int getNumBreak();

        u8 getNumber() { return mNumber; }
        // TODO: inlines
        void checkSign(u32) {}
        void isFree() {}
        void getPriority() {}
        void getStatus() {}
        void getCBInterval() {}
        void decCBInterval() {}
        void getPriorityTime() {}
        void setCBInterval(u16) {}
        void setPriorityTime(u16) {}
        void setPriority(u8) {}
        void getLogicalChannel() {}
        void forceStop(TDSPChannel*) {}
        void release(TDSPChannel*, u32) {}

        /* 0x00 */ u8 mNumber;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 field_0x2;
        /* 0x03 */ u8 field_0x3;
        /* 0x04 */ u16 field_0x4;
        /* 0x06 */ u16 field_0x6;
        /* 0x08 */ int field_0x8;
        /* 0x0C */ DSPInterface::DSPBuffer* field_0xc;
        /* 0x10 */ int (*mCallback)(TDSPChannel*, u32);

        static int smnFree;
        static TDSPChannel* DSPCH;
        static int smnUse;
    };
}

#endif /* JASDSPCHANNEL_H */
