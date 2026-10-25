#ifndef JAISOUNDPARAMS_H
#define JAISOUNDPARAMS_H

#include "dolphin/types.h"

class JAISound;

namespace JAInter {
    class MoveParaSet {
    public:
        MoveParaSet(f32 param_1=1.0f) { init(param_1); }
        int set(f32 param_1, u32 param_2);
        BOOL move();

        void init(f32 value) {
            mCurrentValue = value;
            mTargetValue = value;
            mMoveCounter = 0;
        }

        /* 0x00 */ f32 mTargetValue;
        /* 0x04 */ f32 mCurrentValue;
        /* 0x08 */ f32 mMoveAmount;
        /* 0x0C */ u32 mMoveCounter;
    };

    class MoveParaSetInitHalf : public MoveParaSet {
    public:
        MoveParaSetInitHalf() : MoveParaSet(0.5f) {}
    };

    class MoveParaSetInitZero : public MoveParaSet {
    public:
        MoveParaSetInitZero() : MoveParaSet(0.0f) {}
    };

    class LinkSound {
    public:
        void init(JAISound* param_1, u32 param_2);
        JAISound* getSound();
        void releaseSound(JAISound* param_1);

        /* 0x00 */ JAISound* field_0x0;
        /* 0x04 */ JAISound* field_0x4;
        /* 0x08 */ JAISound* Buffer;
    };
}

#endif /* JAISOUNDPARAMS_H */
