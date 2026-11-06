#ifndef JASOSCILLATOR_H
#define JASOSCILLATOR_H

#include "dolphin/types.h"

namespace JASystem {
    class TOscillator {
    public:
        struct Osc_ {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ s16* table;
            /* 0x0C */ s16* rel_table;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
        };

        TOscillator() { init(); }
        ~TOscillator() {}
        void init();
        void initStart();
        f32 getOffset();
        bool forceStop();
        bool release();
        f32 calc(s16*);

        const Osc_* getOsc() const { return mOsc; }
        void setOsc(const Osc_* osc) { mOsc = osc; }
        BOOL isOsc() { return mOsc != NULL ? TRUE : FALSE; }
        void releaseDirect(u16 param_0) { mDirectRelease = param_0; }
        void bankOscToOfs() {}
        void getEffectorKind() const {}
        void getOscMode() const {}

        static s16 oscTableForceStop[6];
        static const f32 relTableSampleCell[17];
        static const f32 relTableSqRoot[17];
        static const f32 relTableSquare[17];

        /* 0x00 */ const Osc_* mOsc;
        /* 0x04 */ u8 mState;
        /* 0x05 */ u8 field_0x5;
        /* 0x06 */ u16 field_0x6;
        /* 0x08 */ f32 mReleaseRate;
        /* 0x0C */ f32 mPhase;
        /* 0x10 */ f32 mTargetPhase;
        /* 0x14 */ f32 mPhaseChangeRate;
        /* 0x18 */ u16 mDirectRelease;
        /* 0x1C */ f32 mInitialReleaseRate;
    };
}

#endif /* JASOSCILLATOR_H */
