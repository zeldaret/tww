#ifndef D_A_MOZO_H
#define D_A_MOZO_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"

class daMozo_c : public fopAc_ac_c {
public:
    typedef void(daMozo_c::*proc_t)(void);

    void setProcess(void (daMozo_c::*)()) {}

    s32 _create();
    bool _delete();
    bool _draw();
    bool _execute();
    void anime_proc();
    void checkRange(int);
    BOOL CreateHeap();
    s32 CreateInit();
    void event_move();
    void getBeamActor(u32);
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
    // TODO: add offset comments
    proc_t mCurrentProc;
    request_of_phase_process_class mPhs;
    mDoExt_McaMorf* mAnimMorf;
    mDoExt_brkAnm mBrkAnm;
    J3DAnmTevRegKey* m_brk;
    mDoExt_btkAnm mBtkAnm;
    J3DAnmTextureSRTKey* m_btk;
    // TODO: insert missing members
    Quaternion mQuatRotation;
    dCcD_Stts mColStatus;
    dCcD_Cps mCapsuleCol;
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
