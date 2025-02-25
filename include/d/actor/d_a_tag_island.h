#ifndef D_A_TAG_ISLAND_H
#define D_A_TAG_ISLAND_H

#include "f_op/f_op_actor.h"

class msg_class;

class daTag_Island_c : public fopAc_ac_c {
public:
    enum {
        daTagIsl_UNK_01 = 0x01,
        daTagIsl_UNK_02 = 0x02,
        daTagIsl_UNK_04 = 0x04,
    };

    bool chkFlag(u16 flag) { return (mFlag & flag) == flag; }
    void clrFlag(u16 flag) { mFlag &= ~flag; }
    void setFlag(u16 flag) { mFlag |= flag; }

    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();
    void setActio(u8 action) { mAction = action; }

    u8 getEventNo();
    u8 getSwbit();
    u8 getType();
    BOOL checkArea();
    void makeEvId();
    u16 getArrivalFlag();
    BOOL otherCheck();
    BOOL arrivalTerms();
    void demoInitProc();
    int next_msgStatus(unsigned long*);
    u32 getMsg();
    void talkInit();
    u16 talk();
    void demoInitTact_Bf();
    BOOL demoProcTact_Bf();
    void demoInitTact_Af();
    BOOL demoProcTact_Af();
    void demoInitSpeak();
    BOOL demoProcSpeak();
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitCom();
    void demoProcCom();
    void demoProcCom_ikada();
    int getNowEventAction();
    BOOL demoProc();
    BOOL actionTact();
    BOOL actionEvent();
    BOOL actionReady();
    BOOL actionHunt();
    BOOL actionArrival();
    BOOL actionWait();

public:
    /* Place member variables here */
    /* 0x290 */ u16 m290;
    /* 0x292 */ u16 m292;
    /* 0x294 */ u8 mAction;
    /* 0x296 */ u16 mFlag;
    /* 0x298 */ u32 mMsg;
    /* 0x29C */ s8 mTalkState;
    /* 0x29D */ u8 pad[3];
    /* 0x2A0 */ u8 m2A0;
    /* 0x2A2 */ s16 mTimer;
    /* 0x2A4 */ u32 mStaffId;
    /* 0x2A8 */ s16 mEventId;
    /* 0x2AC */ s32 m2AC;
};

#endif /* D_A_TAG_ISLAND_H */
