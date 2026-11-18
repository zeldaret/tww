#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class dBgW;
class JPABaseEmitter;

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
    bool createHeap();
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
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModelBody;
    /* 0x29C */ J3DModel* mpModelHuta;
    /* 0x2A0 */ dBgW* mpBgWBody;
    /* 0x2A4 */ dBgW* mpBgWHuta;
    /* 0x2A8 */ Mtx mMtxBody;
    /* 0x2D8 */ Mtx mMtxHuta;
    /* 0x308 */ dCcD_Stts mStts;
    /* 0x344 */ dCcD_Cps mCpsBody;
    /* 0x47C */ dCcD_Cps mCpsHuta[3];
    /* 0x824 */ JPABaseEmitter* mpEmitter[2];
    /* 0x82C */ dPa_smokeEcallBack mSmoke;
    /* 0x84C */ cXyz mEffPos;
    /* 0x858 */ csXyz mEffAngle;
    /* 0x860 */ cXyz mHutaOffset;
    /* 0x86C */ cXyz mPivot;
    /* 0x878 */ f32 mAlpha;
    /* 0x87C */ s16 mAngleX;
    /* 0x87E */ s16 mAngleY;
    /* 0x880 */ s16 mAngleZ;
    /* 0x882 */ s16 mSpeed;
    /* 0x884 */ s16 mTimer;
    /* 0x886 */ s16 mAmp;
    /* 0x888 */ s16 mLightCount;
    /* 0x88A */ u8 mType;
    /* 0x88B */ u8 mMode;
    /* 0x88C */ u8 mSearch;
    /* 0x88D */ u8 mSwNo;
    /* 0x88E */ u8 mSwNo2;
    /* 0x88F */ u8 mHideFlag;
}; // Size: 0x890

#endif /* D_A_OBJ_KANOKE_H */
