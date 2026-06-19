#ifndef D_A_TAG_MK_H
#define D_A_TAG_MK_H

#include "f_op/f_op_actor.h"

class daTag_Mk_c : public fopAc_ac_c {
    enum Act_e {
        /* 0 */ ACT_WAIT_e,
        /* 1 */ ACT_ARRIVAL_e,
        /* 2 */ ACT_HUNT_e,
        /* 3 */ ACT_READY_e,
        /* 4 */ ACT_EVENT_e,
        /* 5 */ ACT_VILLA_e,
        /* 6 */ ACT_VILLATALK_e,
        /* 7 */ ACT_TAGWP_e,
        /* 8 */ ACT_TAGWP2_e,
        /* 9 */ ACT_DAICHI_e,
    };
    
public:
    inline cPhs_State create();
    inline BOOL draw();
    inline void setAction(u8 action) {
        mActionTypes = action;    
    }

    u8 getSwbit();
    u8 getSwbit2();
    u8 getType();
    BOOL checkArea(float, float, float);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void talkInit();
    u16 talk();
    void setTagWpEvId();
    void demoInitSetgoal();
    void demoInitDelete();
    void demoInitMake();
    BOOL demoProcMake();
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitCom();
    BOOL demoProcCom();
    s32 getNowEventAction();
    void demoProc();
    BOOL actionEvent();
    BOOL actionReady();
    BOOL actionHunt();
    BOOL actionArrival();
    BOOL actionWait();
    BOOL actionVillaTalk();
    BOOL actionVilla();
    BOOL actionTagWp2();
    BOOL actionTagWp();
    BOOL actionDaichi();
    BOOL execute();

public:
    /* 0x290 */ u32 m290;
    /* 0x294 */ s8 m294;
    /* 0x295 */ u8 m295[0x296 - 0x295];
    /* 0x296 */ s16 m296;
    /* 0x298 */ u8 m298[0x29C - 0x298];
    /* 0x29C */ cXyz m29C;
    /* 0x2A8 */ u8 mActionTypes;
    /* 0x2A9 */ u8 m2A9[0x2AA - 0x2A9];
    /* 0x2AA */ s16 mEventIdx;
    /* 0x2AC */ int mStaffIdx;
    /* 0x2B0 */ s16 mCutEndTimer;
    /* 0x2B2 */ u8 m2B2[0x2B4 - 0x2B2];
    /* 0x2B4 */ fpc_ProcID m2B4;
    /* 0x2B8 */ char* m2B8;
};  // Size: 0x2BC

#endif /* D_A_TAG_MK_H */
