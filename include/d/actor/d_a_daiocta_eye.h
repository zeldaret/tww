#ifndef D_A_DAIOCTA_EYE_H
#define D_A_DAIOCTA_EYE_H

#include "SSystem/SComponent/c_math.h"
#include "d/d_cc_d.h"
#include "d/d_jnt_hit.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class daDaiocta_c;

class daDaiocta_Eye_c : public fopAc_ac_c {
public:
    enum Mode_e {
        MODE_WAIT   = 0,
        MODE_DAMAGE = 1,
        MODE_DEATH  = 2
    };

    typedef void (daDaiocta_Eye_c::*ModeProcFunc)(void);
public:
    void rndRotEye() {
        mEyeRotTargetX = cM_rndF(mEyeRndRotMaxX);

        if (std::fabsf(mEyeRotTargetX - mCurEyeRot.x) < m2EC) {
            mEyeRotTargetX += m2EC;
        }
        
        mEyeRotTargetY = cM_rndF(mEyeRndRotMaxY);
        if (std::fabsf(mEyeRotTargetY - mCurEyeRot.y) < m2EE) {
            mEyeRotTargetY += m2EE;
        }
        
        mEyeRotTargetZ = cM_rndF(mEyeRndRotMaxZ);
        if (std::fabsf(mEyeRotTargetZ - mCurEyeRot.z) < m2F0) {
            mEyeRotTargetZ += m2F0;
        }
    }

    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    void _coHit(fopAc_ac_c*);
    void setMtx();
    void checkTgHit();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDeathInit();
    void modeDeath();
    void modeProcCall();
    bool _execute();
    bool _draw();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const s32 m_heapsize;
    static const char m_arc_name[];
    static const s32 m_scale_damage_time;
public:
    /* 0x290 */ s32 mEyeNo;
    /* 0x294 */ bool mbIsDead;
    /* 0x295 */ bool m295;
    /* 0x296 */ bool mbIsDamaged;
    /* 0x297 */ bool mbIsDamagedBomb;
    /* 0x298 */ bool mbAppear;
    /* 0x299 */ u8 m299[0x29C - 0x299];
    /* 0x29C */ s32 mMode;
    /* 0x2A0 */ request_of_phase_process_class mPhs;
    /* 0x2A8 */ J3DModel* mpModel;
    /* 0x2AC */ J3DAnmTevRegKey* mpBrk;
    /* 0x2B0 */ mDoExt_brkAnm mBrkAnm;
    /* 0x2C8 */ J3DAnmTextureSRTKey* mpBtk;
    /* 0x2CC */ mDoExt_btkAnm mBtkAnm;
    /* 0x2E0 */ s16 mEyeRotTargetX;
    /* 0x2E2 */ s16 mEyeRotTargetY;
    /* 0x2E4 */ s16 mEyeRotTargetZ;
    /* 0x2E6 */ csXyz mCurEyeRot;
    /* 0x2EC */ s16 m2EC;
    /* 0x2EE */ s16 m2EE;
    /* 0x2F0 */ s16 m2F0;
    /* 0x2F2 */ s16 mEyeRndRotMaxX;
    /* 0x2F4 */ s16 mEyeRndRotMaxY;
    /* 0x2F6 */ s16 mEyeRndRotMaxZ;
    /* 0x2F8 */ dCcD_Sph mSph;
    /* 0x424 */ dCcD_Stts mStts;
    /* 0x460 */ cXyz mEyeScale;
    /* 0x46C */ int mScaleAnimeIdx;
    /* 0x470 */ JntHit_c* mpJntHit;
    /* 0x474 */ daDaiocta_c* mpParentActor;
    /* 0x478 */ dPa_followEcallBack mParticleCallback;
    /* 0x48C */ cXyz mParticlePos;
    /* 0x48C */ csXyz m498;
    /* 0x49E */ u8 m49E[0x4A0 - 0x49E];
};  // Size: 0x4A0
STATIC_ASSERT(sizeof(daDaiocta_Eye_c) == 0x4A0);

class daDaiocta_Eye_HIO_c : public mDoHIO_entry_c {
public:
    daDaiocta_Eye_HIO_c();
public:
    s16 m04;
    u8 m06[0x08 - 0x06];
    f32 m08;
    f32 m0C;
    f32 mParticleTranslationX;
    f32 mParticleTranslationY;
    f32 mParticleTranslationZ;
    f32 mSphRadius;
    s16 mEyeRotStep;
    s16 mEyeRotScale;
    s16 m24;
    s16 m26;
    s16 m28;
    s16 mEyeRndRotMaxX;
    s16 mEyeRndRotMaxY;
    s16 mEyeRndRotMaxZ;
    JntHit_HIO_c m30;
};

#endif /* D_A_DAIOCTA_EYE_H */
