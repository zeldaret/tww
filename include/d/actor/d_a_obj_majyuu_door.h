#ifndef D_A_OBJ_MAJYUU_DOOR_H
#define D_A_OBJ_MAJYUU_DOOR_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class dBgW;

class daObj_MjDoor_c : public fopAc_ac_c {
public:
    typedef void (daObj_MjDoor_c::*ModeProc)();
    daObj_MjDoor_c() : mSmoke(smoke_col, &tevStr, 0) {}

    void modeProcCall();
    void set_mtx();
    BOOL _createHeap();
    void getArg();
    void CreateInit();
    cPhs_State _create();
    bool _delete();
    void setCollision();
    void modeWaitInit();
    void modeWait();
    void smoke_set();
    void modeDeleteInit();
    void modeDelete();
    bool _execute();
    bool _draw();

    static const u32 m_heapsize;
    static const char m_arc_name[];
    static GXColor smoke_col;

    /* 0x290 */ s32 mMode;
    /* 0x294 */ cXyz mSmokePos;
    /* 0x2A0 */ csXyz mSmokeAngle;
    /* 0x2A8 */ dPa_smokeEcallBack mSmoke;
    /* 0x2C8 */ int mSmokeTimer;
    /* 0x2CC */ u8 mSwitchNo;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ request_of_phase_process_class mPhs;
    /* 0x2DC */ dBgW* mpBgw;
    /* 0x2E0 */ Mtx mMtx;
    /* 0x310 */ int mDeleteTimer;
    /* 0x314 */ dCcD_Stts mStts;
    /* 0x350 */ dCcD_Cyl mCyl[10];
};

STATIC_ASSERT(sizeof(daObj_MjDoor_c) == 0xF30);

class daObj_MjDoorHIO_c : public mDoHIO_entry_c {
public:
    daObj_MjDoorHIO_c();
    virtual ~daObj_MjDoorHIO_c() {}

    /* 0x4 */ u8 field_0x4;
};

#endif /* D_A_OBJ_MAJYUU_DOOR_H */
