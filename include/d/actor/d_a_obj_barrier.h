#ifndef D_A_OBJ_BARRIER_H
#define D_A_OBJ_BARRIER_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_a_obj.h"

class dBgW;

class daObjBarrier_anm_c {
public:
    daObjBarrier_anm_c() { mBrkFrame = 0.0f; }

    bool init();

    J3DModel* getMdlP() { return mpModel; }
    mDoExt_btkAnm* getBtkAnmP() { return &mBtk; }
    mDoExt_brkAnm* getBrkAnmP() { return &mBrk; }

    f32 getBrkFrame() { return mBrkFrame; }
    void setBrkFrame(f32 i_frame) { mBrkFrame = i_frame; }

    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ mDoExt_btkAnm mBtk;
    /* 0x18 */ mDoExt_brkAnm mBrk;
    /* 0x30 */ f32 mBrkFrame;
};

class daObjBarrier_ef_c {
public:
    daObjBarrier_ef_c() {
        mActiveEffFlags = 0;
    }
    ~daObjBarrier_ef_c() {}

    void setDummyTexture(int);
    bool checkHitActor(fopAc_ac_c*);
    void birth(fopAc_ac_c*, f32, cXyz, cXyz, int);
    bool init();
    void create();
    void execute();
    void draw();

    f32 getBtkFrame(int i_idx) { return mBtk[i_idx].getFrame(); }

    /* 0x000 */ u32 mActiveEffFlags;
    /* 0x004 */ J3DModel* mpModel[4];
    /* 0x014 */ mDoExt_btkAnm mBtk[4];
    /* 0x064 */ mDoExt_bckAnm mBck[4];
    /* 0x0A4 */ mDoExt_brkAnm mBrk[4];
    /* 0x104 */ cXyz mPos[4];
    /* 0x134 */ s16 mAngle[4];
    /* 0x13C */ fopAc_ac_c* mHitActor[4];
};

class daObjBarrier_c : public fopAc_ac_c {
public:
    enum PROC_e {
        PROC_BREAK_START_WAIT,
        PROC_BREAK_ORDER,
        PROC_BREAK_END_WAIT,
    };
    enum Param_e {
        PRM_DAMAGE_W = 0x01,
        PRM_DAMAGE_S = 0x10,
        PRM_MOYA_W = 0x01,
        PRM_MOYA_S = 0x08,
    };

    void init_mtx();
    static int solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    bool checkCollision_Tg();
    void checkCollision_At();
    void registCollisionTable();
    void brkAnmPlay();
    void break_start_wait_proc();
    void break_order_proc();
    void break_end_wait_proc();
    bool break_check();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

    bool param_get_damage() const { return daObj::PrmAbstract(this, PRM_DAMAGE_W, PRM_DAMAGE_S); }
    int param_get_moya() const { return daObj::PrmAbstract(this, PRM_MOYA_W, PRM_MOYA_S); }

    /* 0x290 */ daObjBarrier_anm_c mAnm;
    /* 0x2C4 */ request_of_phase_process_class mPhase;
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ Mtx mBgMtx;
    /* 0x300 */ dCcD_Stts mAtStts;
    /* 0x33C */ dCcD_Stts mTgStts;
    /* 0x378 */ dCcD_Cyl mAtCyl;
    /* 0x4A8 */ dCcD_Cyl mTgCyl;
    /* 0x5D8 */ daObjBarrier_ef_c mEffect;
    /* 0x724 */ u8 mBarrierActive;
    /* 0x728 */ int mMoya;
#if VERSION > VERSION_JPN
    /* 0x72C */ s16 mEventID;
    /* 0x730 */ int mBarrierProc;
#endif
};

#endif /* D_A_OBJ_BARRIER_H */
