#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DModel;
class dBgW;
class dChain_packet_c;
struct dPath;

class daBalancelift_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void calc_quat();
    void set_mtx();
    void calc_weight();
    BOOL CreateHeap();
    cPhs_State CreateInit();

    static const char M_arcname[];

public:
    /* 0x290 */ cXyz mTopPos;
    /* 0x29C */ cXyz mSwingPos;
    /* 0x2A8 */ cXyz mSwingTarget;
    /* 0x2B4 */ cXyz mSwingSpeed;
    /* 0x2C0 */ cXyz mSwingWorldPos;
    /* 0x2CC */ Quaternion mArmQuat;
    /* 0x2DC */ Quaternion mPlateQuat;
    /* 0x2EC */ cXyz mPlatePos;
    /* 0x2F8 */ cXyz mPlateSpeed;
    /* 0x304 */ cXyz mPlateWorldPos;
    /* 0x310 */ f32 mLength;
    /* 0x314 */ s16 mWeight;
    /* 0x318 */ s16* mpWeight;
    /* 0x31C */ s16 mSide;
    /* 0x31E */ s16 mFlag;
    /* 0x320 */ s16* mpFlag;
    /* 0x324 */ request_of_phase_process_class mPhs;
    /* 0x32C */ J3DModel* M_mdl;
    /* 0x330 */ Mtx mMtx;
    /* 0x360 */ dPath* mpPath;
    /* 0x364 */ dBgW* pm_bgw;
    /* 0x368 */ f32 mLengthSpeed;
    /* 0x36C */ cXyz m36C[4];
    /* 0x39C */ mDoExt_3DlineMat0_c mLineMat;
    /* 0x3B8 */ dChain_packet_c* m_chain;
    /* 0x3BC */ dCcD_Stts mStts;
    /* 0x3F8 */ dCcD_Cyl mCyl;
};  // Size: 0x528

class daBalancelift_HIO_c : public JORReflexible {
public:
    daBalancelift_HIO_c();
    virtual ~daBalancelift_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 mPlateSpring;
    /* 0x10 */ f32 mRideSpring;
    /* 0x14 */ f32 mPlateDamp;
    /* 0x18 */ f32 mHitSwing;
    /* 0x1C */ f32 mSwingDamp;
    /* 0x20 */ f32 mSwingSpring;
    /* 0x24 */ f32 mMoveRange;
    /* 0x28 */ f32 mMaxLength;
    /* 0x2C */ cXyz mScale;
};  // Size: 0x38

#endif /* D_A_OBJ_BALANCELIFT_H */
