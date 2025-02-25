#ifndef D_A_LEAFLIFT_H
#define D_A_LEAFLIFT_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"

class dBgW;

class daLlift_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    void emitterCtrl();
    BOOL MoveDownLift();
    bool _draw();

    s32 checkEndDownLift();
    BOOL MoveUpLift();

    static const f32 m_height;
    static const f32 m_max_speed;
    static const f32 m_min_speed;

    static const char m_arcname[6];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */	dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dBgW* mpBgW;
    /* 0x40C */ Mtx mMtx;
    /* 0x43C */ bool m43C;
    /* 0x43D */ bool m43D;
    /* 0x43E */ bool m43E;
    /* 0x43F */ u8 m43F;
    /* 0x440 */ s16 mTiltAngle;
    /* 0x442 */ u8 m442[0x444-0x442];
    /* 0x444 */ s16 mGlideFrameCounter;
    /* 0x446 */ u8 m446[0x448-0x446];
    /* 0x448 */ Quaternion mCurrentRotation;
    /* 0x458 */ Quaternion mTargetRotation;
    /* 0x468 */ bool mbIsDescending;
    /* 0x469 */ bool mbIsUpdraftBoosted;
    /* 0x46A */ u8 m46A[0x46C-0x46A];
    /* 0x46C */ Mtx mBGMtx;
    /* 0x49C */ s32 mEmitterTimer;
    /* 0x4A0 */ JPABaseEmitter* mEmitter1;
    /* 0x4A4 */ JPABaseEmitter* mEmitter2;
    /* 0x4A8 */ JPABaseEmitter* mEmitter3;
    /* 0x4AC */ JPABaseEmitter* mEmitter4;
    /* 0x4B0 */ f32 mWaterY;
};

namespace daLlift_prm {
    inline u8 getPos(daLlift_c* item) { return fopAcM_GetParam(item) & 0x0F; }
}

#endif /* D_A_LEAFLIFT_H */
