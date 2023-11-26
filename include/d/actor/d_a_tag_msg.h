#ifndef D_A_TAG_MSG_H
#define D_A_TAG_MSG_H

#include "f_op/f_op_actor.h"

class daTag_Msg_c : public fopAc_ac_c {
public:
    typedef BOOL (ActionFunc)(daTag_Msg_c*);

    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();
    void setActio(u8 action) { mAction = action; }

    u32 getEventNo();
    u32 getSwbit();
    u32 getSwbit2();
    u32 getType2();
    const char* myDemoName();
    u16 getMessage();
    u16 getEventFlag();
    BOOL arrivalTerms();
    int rangeCheck();
    int otherCheck();

public:
    /* 0x290 */ u8 mAction;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292;
    /* 0x293 */ u8 field_0x293;
};

#endif /* D_A_TAG_MSG_H */
