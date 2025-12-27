#ifndef D_A_OBJ_HOLE_H
#define D_A_OBJ_HOLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_acch.h"

class daObj_Hole_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1,
    };

    enum Mode {
        MODE_WAIT  = 0,
        MODE_EVENT = 1,
        MODE_NULL,
    };

    static const char m_arc_name[];

    void modeProcInit(int newMode) { modeProc(PROC_INIT, newMode); }

    void setMtx();
    void getPosAndAngle();
    void modeWaitInit();
    void modeWait();
    void modeEventInit();
    void modeEvent();
    void modeProc(Proc_e proc, int newMode);
    void debugDraw();
    void createInit();
    void getArg();

    bool _execute();
    bool _draw();
    BOOL _createHeap();
    cPhs_State _create();
    bool _delete();

public:
    /* 0x0290 */ s32 mMode;
    /* 0x0294 */ u8 mHasModel;
    /* 0x0295 */ u8 mExitIdx;
    /* 0x0296 */ u16 mScaleLocal;
    /* 0x0298 */ request_of_phase_process_class mPhs;
    /* 0x02A0 */ J3DModel* mpMdl;
    /* 0x02A4 */ dBgS_ObjLinChk mLinChk;
    /* 0x0310 */ dBgS_ObjAcch mAcch;
    /* 0x04D4 */ dBgS_AcchCir mAcchCir;
};

class daObj_Hole_HIO_c {
public:
    daObj_Hole_HIO_c();
    virtual ~daObj_Hole_HIO_c() {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
    /* 0x10 */ f32 m10;
};

#endif /* D_A_OBJ_HOLE_H */
