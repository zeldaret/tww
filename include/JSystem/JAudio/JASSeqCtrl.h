#ifndef JASSEQCTRL_H
#define JASSEQCTRL_H

#include "dolphin/types.h"

namespace JASystem {
    class TTrack;

    class TSeqCtrl {
    public:
        void call(u32 offset) {
            mLoopStartPositions[mLoopIndex++] = mCurrentFilePtr;
            mCurrentFilePtr = mRawFilePtr + offset;
        }
        void clrIntr() { mPreviousFilePtr = 0; }
        u8* getAddr(u32 offset) { return mRawFilePtr + offset; }
        u8* getBase() { return mRawFilePtr; }
        u8 getByte(u32 offset) const { return mRawFilePtr[offset]; }
        u16 getLoopCount() const {
            if (mLoopIndex == 0) {
                return 0;
            }
            return mLoopTimers[mLoopIndex - 1]; 
        }
        s32 getWait() const { return mWaitTimer; }
        void isIntr() const {}
        void jump(u32 offset) {
            mCurrentFilePtr = mRawFilePtr + offset;
        }
        void loopStart(u32 timer) {
            mLoopStartPositions[mLoopIndex] = mCurrentFilePtr;
            mLoopTimers[mLoopIndex++] = timer;
        }
        u8 readByte() { return *mCurrentFilePtr++; }
        bool ret() {
            mCurrentFilePtr = mLoopStartPositions[--mLoopIndex];
            return true;
        }
        void wait(s32 timer) {
            mWaitTimer = timer;
        }

        void init();
        void start(void*, u32);
        int loopEnd();
        bool waitCountDown();
        bool callIntr(void*);
        bool retIntr();
        u16 get16(u32) const;
        u32 get24(u32) const;
        u32 get32(u32) const;
        u16 read16();
        u32 read24();

        /* 0x00 */ u8* mRawFilePtr;
        /* 0x04 */ u8* mCurrentFilePtr;
        /* 0x08 */ s32 mWaitTimer;
        /* 0x0C */ u32 mLoopIndex;
        /* 0x10 */ u8* mLoopStartPositions[8];
        /* 0x30 */ u16 mLoopTimers[8];
        /* 0x40 */ int field_0x40;
        /* 0x44 */ u8* mPreviousFilePtr;
    };
}

#endif /* JASSEQCTRL_H */
