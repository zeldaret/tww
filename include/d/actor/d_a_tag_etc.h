#ifndef D_A_TAG_ETC_H
#define D_A_TAG_ETC_H

#include "f_op/f_op_actor.h"

class daTag_Etc_c : public fopAc_ac_c {
public:
    typedef BOOL (ActionFunc)(daTag_Etc_c*);

    inline BOOL draw();
    inline BOOL execute();
    void setActio(u8 action) { mAction = action; }

    u8 getEventNo();
    u8 getType2();
    BOOL rangeCheck(fopAc_ac_c*);
    BOOL otherCheck(fopAc_ac_c*);
    void demoProc();
    void demoInitProc();
    s32 create();

public:
    /* 0x290 */ u8 mAction;
    /* 0x291*/  u8 field_0x291;
    /* 0x292*/  u8 field_0x292;
    /* 0x293*/  u8 field_0x293;
    /* 0x294 */ uint mMedliPID;
    /* 0x298 */ s16 mEventIdx;
    /* 0x29A */ short field_0x29A;
};

#endif /* D_A_TAG_ETC_H */
