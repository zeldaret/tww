#ifndef D_A_MDOOR_H
#define D_A_MDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class dBgW;

class daMdoor_c : public fopAc_ac_c {
public:
    enum Action_e {
        ACT_WAIT0_e      = 0,
        ACT_DEMO_WAIT_e  = 1,
        ACT_DEMO_e       = 2,
        ACT_WAIT3_e      = 3,
        ACT_GENOCIDE_e   = 4,
        ACT_READY5_e     = 5,
        ACT_EVENT6_e     = 6,
        ACT_WAIT7_e      = 7,
        ACT_SWITCH8_e    = 8,
        ACT_READY9_e     = 9,
        ACT_EVENT10_e    = 10,
        ACT_WAIT11_e     = 11,
        ACT_SWITCH12_e   = 12,
        ACT_READY_OPEN_e = 13,
        ACT_OPEN_e       = 14,
        ACT_WAIT15_e     = 15,
    };

    bool chkFlag(unsigned short bit) { return (m2CA & bit) == bit; }
    void clrFlag(unsigned short bit) { m2CA &= ~bit; }
    inline BOOL draw();
    inline BOOL execute();
    void nextAction() { mAction++; }
    void setAction(unsigned char action) { mAction = action; }
    void setFlag(unsigned short bit) { m2CA |= bit; }

    u8 getSwbit();
    u8 getType();
    u8 getToolId();
    u8 getShapeType();
    BOOL CreateHeap();
    void calcMtx();
    void smokeInit();
    void smokeEnd();
    BOOL CreateInit();
    cPhs_State create();
    void demoProc();

    static const char M_arcname[];

public:
    /* 0x290 */ dPa_smokeEcallBack m290;
    /* 0x2B0 */ request_of_phase_process_class mPhase;
    /* 0x2B8 */ J3DModel* mpModel;
    /* 0x2BC */ dBgW* mpBgW;
    /* 0x2C0 */ s32 m2C0;
    /* 0x2C4 */ s16 m2C4;
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ u8 m2C8;
    /* 0x2C9 */ u8 mAction;
    /* 0x2CA */ u16 m2CA;
    /* 0x2CC */ f32 m2CC;
}; // size = 0x2D0

#endif /* D_A_MDOOR_H */
