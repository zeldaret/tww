#ifndef D_A_WBIRD_H
#define D_A_WBIRD_H

#include "f_op/f_op_actor.h"

class daWbird_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(int action) {
        mAction = action;
    }

    void calcMtx();
    void setStartPos();
    BOOL CreateInit();
    cPhs_State create();
    void actionWait();
    void actionEnd();
    void actionMove();
    void actionSelect();

    static const char M_arcname[];

public:
    /* 0x290 */ u8 field_0x290[0x29C - 0x290];
    /* 0x29C */ u8 mAction;
    /* 0x29D */ bool field_0x29D;
    /* 0x29E */ s16 field_0x29E;
    /* 0x2A0 */ f32 field_0x2A0;
    /* 0x2A4 */ s16 mAngle;
    /* 0x2A6 */ s16 mEventIdx;
};  // Size: 0x2A8
#endif /* D_A_WBIRD_H */
