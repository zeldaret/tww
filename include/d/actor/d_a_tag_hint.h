#ifndef D_A_TAG_HINT_H
#define D_A_TAG_HINT_H

#include "f_op/f_op_actor.h"

class daTag_Hint_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned short) {}
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();
    void setActio(unsigned char) {}
    void setFlag(unsigned short) {}

    void getEventNo();
    void getSwbit();
    void getSwbit2();
    void getType();
    void getType2();
    void getMessage();
    void getEventFlag();
    void arrivalTerms();
    void waitTerms();
    void rangeCheck_local(cXyz*);
    void rangeCheck();
    void otherCheck();
    void getPriority();
    void makeEventId();
    void initLight();
    void setLightPos();
    void makeLight();
    void deleteLight();
    void moveBoxCheck();
    void setPlayerAngle();
    void darkProc();
    void startProc();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void talkInit();
    void talk();
    void actionEvent();
    void actionHunt();
    void actionArrival();
    void actionLight();
    void actionWait();

public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ u32 mMsgNo;
    /* 0x29C */ int m29C;
    /* 0x2A0 */ s16 m2A0;
    /* 0x2A2 */ u8 mCurProc;
    /* 0x2A3 */ u8 m2A3[0x2A4 - 0x2A3];
    /* 0x2A4 */ s16 m2A4;
    /* 0x2A6 */ u8 m2A6[0x2A8 - 0x2A6];
    /* 0x2A8 */ f32 m2A8;
    /* 0x2AC */ f32 m2AC;
    /* 0x2B0 */ f32 m2B0;
};

#endif /* D_A_TAG_HINT_H */
