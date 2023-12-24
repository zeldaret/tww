#ifndef D_A_TAG_ETC_H
#define D_A_TAG_ETC_H

#include "f_op/f_op_actor.h"

class daTag_Etc_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setActio(unsigned char) {}

    u8 getEventNo();
    u32 getType2();
    BOOL rangeCheck(fopAc_ac_c*);
    BOOL otherCheck(fopAc_ac_c*);
    void demoProc();
    void demoInitProc();
    s32 create();

public:
    /* 0x290 */ u8 field_0x290;
    /* 0x291*/  u8 field_0x291;
    /* 0x292*/  u8 field_0x292;
    /* 0x293*/  u8 field_0x293;
    /* 0x294 */ s32 processId;
    /* 0x298 */ s16 eventIndex;
    /* 0x29A */ short field_0x29A;
};

#endif /* D_A_TAG_ETC_H */
