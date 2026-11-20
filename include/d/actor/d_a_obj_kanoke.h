#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class daObjKanoke_c : public fopAc_ac_c {
public:

    typedef void(daObjKanoke_c::*ProcFunc_t)();

    enum Mode_e {
        MODE_NORMAL = 0,
        MODE_YURE_YOKO,
        MODE_OPEN_YOKO,
        MODE_EFFECT_YOKO,
        MODE_YURE_TATE,
        MODE_OPEN_TATE,
        MODE_EFFECT_TATE,
        MODE_WAIT
    };

    enum Prm_e {
        PRM_TYPE_W = 1,
        PRM_TYPE_S = 0,
        PRM_YURE_W = 1,
        PRM_YURE_S = 6,
        PRM_SEARCH_W = 5,
        PRM_SEARCH_S = 1,
        PRM_SWNO_W = 8,
        PRM_SWNO_S = 8,
        PRM_SWNO2_W = 8,
        PRM_SWNO2_S = 16,        
    };
    
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
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpModel2;
    /* 0x2A0 */ dBgW* mpBgW;
    /* 0x2A4 */ dBgW* mpBgW2;
    /* 0x2A8 */ Mtx mMtx;
    /* 0x2D8 */ Mtx mMtx2;
    /* 0x308 */ dCcD_Stts mStts;
    /* 0x344 */ dCcD_Cps mCps;
    /* 0x47C */ dCcD_Cps mCps2[3];
    /* 0x824 */ JPABaseEmitter* mpEmitters[2];
    /* 0x82C */ dPa_smokeEcallBack mParticleCallBack;
    /* 0x84C */ cXyz mPartPos;
    /* 0x858 */ csXyz field_0x858;
    /* 0x85E */ u8 field_0x85E[0x860 - 0x85E];
    /* 0x860 */ cXyz field_0x860;
    /* 0x86C */ cXyz field_0x86C;
    /* 0x878 */ float mPartAlpha;
    /* 0x87C */ s16 field_0x87C;
    /* 0x87E */ s16 field_0x87E;
    /* 0x880 */ s16 field_0x880;
    /* 0x882 */ s16 field_0x882;
    /* 0x884 */ s16 field_0x884;
    /* 0x886 */ s16 field_0x886;
    /* 0x888 */ s16 field_0x888;
    /* 0x88A */ u8 mType;
    /* 0x88B */ u8 mMode;
    /* 0x88C */ u8 mSearch;
    /* 0x88D */ u8 mSwNo;
    /* 0x88E */ u8 mSwNo2;
    /* 0x88F */ u8 field_0x88F;
};  // Size: 0x890

#endif /* D_A_OBJ_KANOKE_H */
