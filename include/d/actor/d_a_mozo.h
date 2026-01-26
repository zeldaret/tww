#ifndef D_A_MOZO_H
#define D_A_MOZO_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_hostIO.h"

class daMozo_c : public fopAc_ac_c {
public:
    typedef void (daMozo_c::*proc_t)();

    void setProcess(proc_t proc) { mCurrentProc = proc; }

    cPhs_State _create();
    bool _delete();
    bool _draw();
    bool _execute();
    void anime_proc();
    void checkRange(int);
    BOOL CreateHeap();
    cPhs_State CreateInit();
    void event_move();
    fopAc_ac_c* getBeamActor(fpc_ProcID);
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

class daMozo_childHIO_c {
public:
    virtual ~daMozo_childHIO_c() {}

    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ s16 m0E;
    /* 0x10 */ u8 m10;
    /* 0x11 */ u8 m11[0x14 - 0x11];
};  // Size: 0x14

class daMozo_BeamChildHIO_c : public daMozo_childHIO_c {
public:
    virtual ~daMozo_BeamChildHIO_c() {}
};

class daMozo_FireChildHIO_c : public daMozo_childHIO_c {
public:
    virtual ~daMozo_FireChildHIO_c() {}
};

class daMozo_HIO_c : public JORReflexible {
public:
    daMozo_HIO_c();
    virtual ~daMozo_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m08;
    /* 0x0C */ daMozo_BeamChildHIO_c* mpBeamChild;
    /* 0x10 */ daMozo_FireChildHIO_c* mpFireChild;
    /* 0x14 */ daMozo_BeamChildHIO_c mBeamChild;
    /* 0x28 */ daMozo_FireChildHIO_c mFireChild;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
};  // Size: 0x48

#endif /* D_A_MOZO_H */
