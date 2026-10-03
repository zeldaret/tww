#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class dBgW;
class J3DModel;

class daObjKanoke_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_TYPE_W = 1,
        PRM_TYPE_S = 0,
        PRM_SEARCH_W = 5,
        PRM_SEARCH_S = 1,
        PRM_YURE_W = 1,
        PRM_YURE_S = 6,
        PRM_SWNO_W = 8,
        PRM_SWNO_S = 8,
        PRM_SWNO2_W = 8,
        PRM_SWNO2_S = 16,
    };

    typedef void (daObjKanoke_c::*MoveProc)();

    daObjKanoke_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    void executeYureYoko();
    void executeOpenYoko();
    void executeEffectYoko();
    void executeYureTate();
    void executeOpenTate();
    void executeEffectTate();
    void executeWait();
    u8 getPrmType();
    u8 getPrmSearch();
    u8 getPrmYure();
    u8 getPrmSwNo();
    u8 getPrmSwNo2();
    void setMtx();
    void setMtxHontai();
    void setMtxHuta(cXyz*);

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpBodyModel;
    /* 0x29C */ J3DModel* mpLidModel;
    /* 0x2A0 */ dBgW* mpBodyBgW;
    /* 0x2A4 */ dBgW* mpLidBgW;
    /* 0x2A8 */ Mtx mBodyMtx;
    /* 0x2D8 */ Mtx mLidMtx;
    /* 0x308 */ dCcD_Stts mStts;
    /* 0x344 */ dCcD_Cps mBodyCps;
    /* 0x47C */ dCcD_Cps mLidCps[3];
    /* 0x824 */ JPABaseEmitter* mpEmitters[2];
    /* 0x82C */ dPa_smokeEcallBack mSmokeCallback;
    /* 0x84C */ cXyz mEffectPos;
    /* 0x858 */ csXyz mEffectAngle;
    /* 0x860 */ cXyz mPivotOffset;
    /* 0x86C */ cXyz mLidOffset;
    /* 0x878 */ f32 mEffectScale;
    /* 0x87C */ s16 mLidRotX;
    /* 0x87E */ s16 mBodyRotY;
    /* 0x880 */ s16 mLidRotZ;
    /* 0x882 */ s16 mRotStep;
    /* 0x884 */ s16 mTimer;
    /* 0x886 */ s16 mMoveSpeed;
    /* 0x888 */ s16 mLightTimer;
    /* 0x88A */ u8 mType;
    /* 0x88B */ u8 mState;
    /* 0x88C */ u8 mSearchRange;
    /* 0x88D */ u8 mSwitchNo;
    /* 0x88E */ u8 mSwitchNo2;
    /* 0x88F */ u8 mFlags;
};

STATIC_ASSERT(sizeof(daObjKanoke_c) == 0x890);

#endif /* D_A_OBJ_KANOKE_H */
