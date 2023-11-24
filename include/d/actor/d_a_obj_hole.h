#ifndef D_A_OBJ_HOLE_H
#define D_A_OBJ_HOLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_lin_chk.h"

class daObj_Hole_c : public fopAc_ac_c {
public:
    void modeProcInit(int) {}

    void setMtx();
    void getPosAndAngle();
    void modeWaitInit();
    void modeWait();
    void modeEventInit();
    void modeEvent();
    void modeProc(daObj_Hole_c::Proc_e mode, int i_nextState);
    void debugDraw();
    void createInit();
    void getArg();

public:
    /* 0x290 */ int mState;
    /* 0x294 */ u8 mbHasModel;
    /* 0x295 */ u8 mSclsNum;
    /* 0x296 */ s16 mScale;
    /* 0x298 */ u8 m298[0x2A0 - 0x298];
    /* 0x2A0 */ J3DModel* mpModel;
    /* 0x2A4 */ dBgS_LinChk mLinChk;
    /* 0x310 */ u8 m310[0x338 - 0x310];
    /* 0x338 */ int m338;
    /* 0x33C */ u8 m33C[0x800 - 0x33C];
};

#endif /* D_A_OBJ_HOLE_H */
