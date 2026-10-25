#ifndef D_A_TAG_SO_H
#define D_A_TAG_SO_H

#include "f_op/f_op_actor.h"

class daTag_So_c : public fopAc_ac_c {
public:
    f32 getJumpRange() { return mJumpRange; }
    u8 getRndNum() { return mRndNum;}
    BOOL isMinigame() { return mType == 1; }
    BOOL isTag() { return mType != 1; }

    bool _execute();
    void debugDraw();
    bool _draw();
    void getArg();
    cPhs_State _create();
    bool _delete();

private:
    /* 0x290 */ u8 mRndNum;
    /* 0x294 */ f32 mJumpRange;
    /* 0x298 */ u8 mType;
    /* 0x299 */ u8 m299[0x2A4 - 0x299];
};

#endif /* D_A_TAG_SO_H */
