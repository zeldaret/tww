#ifndef D_A_MOZO_H
#define D_A_MOZO_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"

class daMozo_c : public fopAc_ac_c {
public:
    typedef void (daMozo_c::*proc_t)();

    void setProcess(proc_t proc) { mCurrentProc = proc; }

    s32 _create();
    bool _delete();
    bool _draw();
    bool _execute();
    void anime_proc();
    void checkRange(int);
    BOOL CreateHeap();
    s32 CreateInit();
    void event_move();
    fopAc_ac_c* getBeamActor(uint);
    void search_beam_proc_init();
    void search_beam_proc();
    void search_fire_proc_init();
    void search_fire_proc();
    void towait_proc_init();
    void towait_proc();
    void wait_proc_init();
    void wait_proc();
    void set_mtx();
    void setAnm(int, float);

public:
    /* 0x290 */ proc_t mCurrentProc;
    /* 0x29C */ request_of_phase_process_class mPhs;
    /* 0x2A4 */ mDoExt_McaMorf* mAnimMorf;
    /* 0x2A8 */ mDoExt_brkAnm mBrkAnm;
    /* 0x2C0 */ J3DAnmTevRegKey* m_brk;
    /* 0x2C4 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2D8 */ J3DAnmTextureSRTKey* m_btk;
    /* 0x2DC */ u8 m2DC[0x35C - 0x2DC];
    /* 0x35C */ Quaternion mQuatRotation;
    /* 0x36C */ u8 m36C[0x376 - 0x36C];
    /* 0x376 */ u8 field_0x376;
    /* 0x377 */ u8 field_0x377[7];
    /* 0x380 */ dCcD_Stts mStts;
    /* 0x3BC */ dCcD_Cps mCps;
};

class daMozo_HIO_c {
public:
    daMozo_HIO_c();
    ~daMozo_HIO_c() {}
};

class daMozo_childHIO_c {
public:
    ~daMozo_childHIO_c() {}
};

class daMozo_FireChildHIO_c {
public:
    ~daMozo_FireChildHIO_c() {}
};

class daMozo_BeamChildHIO_c {
public:
    ~daMozo_BeamChildHIO_c() {}
};

#endif /* D_A_MOZO_H */
