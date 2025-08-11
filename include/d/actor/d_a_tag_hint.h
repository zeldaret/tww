#ifndef D_A_TAG_HINT_H
#define D_A_TAG_HINT_H

#include "f_op/f_op_actor.h"

class daTag_Hint_c : public fopAc_ac_c {
public:
    bool chkFlag(unsigned short flg) { return (m2A6 & flg) == flg; }
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    void setActio(unsigned char action) { mCurProc = action; }
    void setFlag(unsigned short flg) { m2A6 |= flg; }

    u8 getEventNo();
    u8 getSwbit();
    u8 getSwbit2();
    u8 getType();
    u8 getType2();
    u16 getMessage();
    u16 getEventFlag();
    s32 arrivalTerms();
    s32 waitTerms();
    BOOL rangeCheck_local(cXyz*);
    BOOL rangeCheck();
    s32 otherCheck();
    s32 getPriority();
    void makeEventId();
    void initLight();
    void setLightPos();
    void makeLight();
    void deleteLight();
    BOOL moveBoxCheck();
    void setPlayerAngle();
    void darkProc();
    void startProc();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void talkInit();
    u16 talk();
    BOOL actionEvent();
    BOOL actionHunt();
    BOOL actionArrival();
    BOOL actionLight();
    BOOL actionWait();

public:
    /* 0x290 */ u32 m290;
    /* 0x294 */ s8 m294;
    /* 0x298 */ u32 mMsgNo;
    /* 0x29C */ s32 m29C;
    /* 0x2A0 */ s16 m2A0;
    /* 0x2A2 */ u8 mCurProc;
    /* 0x2A3 */ bool m2A3;
    /* 0x2A4 */ s16 m2A4;
    /* 0x2A6 */ u16 m2A6;
    /* 0x2A8 */ f32 m2A8;
    /* 0x2AC */ f32 m2AC;
    /* 0x2B0 */ f32 m2B0;
}; // size = 0x2B4

#endif /* D_A_TAG_HINT_H */
