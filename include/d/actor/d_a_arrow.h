#ifndef D_A_ARROW_H
#define D_A_ARROW_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "dolphin/types.h"

class J3DAnmTextureSRTKey;
class J3DMaterial;

class daArrow_c : public fopAc_ac_c {
public:
    enum ArrowType {
        TYPE_NORMAL = 0,
        TYPE_FIRE = 1,
        TYPE_ICE = 2,
        TYPE_LIGHT = 3,
    };
    
    typedef BOOL (daArrow_c::*daArrow_c_ProcFunc)();
    
    daArrow_c() {}
    BOOL _createHeap();
    void _atHit(dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void checkCreater();
    void setLightEffect();
    void setBlur();
    void createBlur();
    void setArrowShootSe();
    void setDrawShapeMaterial();
    void arrowShooting();
    void arrowUseMp();
    void ShieldReflect();
    bool check_water_in();
    BOOL changeArrowMp();
    daArrow_c* changeArrowType();
    void changeArrowTypeNotReady();
    void setRoomInfo();
    void setKeepMatrix();
    void setStopActorMatrix();
    BOOL procWait();
    BOOL procMove();
    BOOL procReturn();
    BOOL procStop_BG();
    BOOL procStop_Actor();
    BOOL procWater();
    void checkRestMp();
    void setTypeByPlayer();
    BOOL createInit();
    BOOL _execute();
    BOOL _draw();
    s32 _create();
    BOOL _delete();
    
    static u8 getKeepType();
    static void setKeepType(u8 type);
    
    bool isSetByZelda() { return mbSetByZelda; }
    bool isLinkReflect() { return mbLinkReflect; }
    void ArrowAtOff() { mAtCps.OffAtSetBit(); }
    bool chkAtHitNormal() { return mbHitActor; }
    void setAtHitNormal() { mbHitActor = true; }
    void clrAtHitNormal() { mbHitActor = false; }
    fopAc_ac_c* getAtHitNormalActor() { return mpAtHitActor; }
    void setAtHitNormalActor(fopAc_ac_c* actor) { mpAtHitActor = actor; }
    cXyz* getAtHitPosBuffP() { return &mAtHitPos; }
    void setAtHitPosBuff(cXyz* pos) { mAtHitPos = *pos; }
    void clrAtHitPosBuff(cXyz* pos) {} // Not sure what this inline would have been for

public:
    /* 0x290 */ bool mbSetByZelda;
    /* 0x294 */ J3DModel* mpModel;
    /* 0x298 */ J3DMaterial* mpTipMat;
    /* 0x29C */ J3DAnmTextureSRTKey* mpBtk;
    /* 0x2A0 */ dBgS_ArrowLinChk mLinChk;
    /* 0x30C */ dBgS_ObjGndChk mGndChk;
    /* 0x360 */ dCcD_Stts mStts;
    /* 0x39C */ dCcD_Cps mAtCps;
    /* 0x4D4 */ dCcD_Sph mCoSph;
    /* 0x600 */ bool field_0x600;
    /* 0x601 */ u8 mArrowType;
    /* 0x602 */ s16 field_0x602;
    /* 0x604 */ s16 field_0x604;
    /* 0x606 */ u8 field_0x606[0x608 - 0x606];
    /* 0x608 */ s16 mSparkleTimer;
    /* 0x60C */ JPABaseEmitter* mpSparkleEmitter;
    /* 0x610 */ uint mHitActorProcID;
    /* 0x614 */ s32 mHitJointIndex;
    /* 0x618 */ cXyz field_0x618;
    /* 0x624 */ u8 field_0x624[0x660 - 0x624];
    /* 0x660 */ f32 mBtkFrame;
    /* 0x664 */ bool mbLinkReflect;
    /* 0x668 */ dPa_followEcallBack mBlurFollowCb;
    /* 0x67C */ csXyz mBlurAngle;
    /* 0x682 */ u8 field_0x682;
    /* 0x684 */ uint mLightEffPID;
    /* 0x688 */ bool mbHasLightEff;
    /* 0x68C */ daArrow_c_ProcFunc mCurrProcFunc;
    /* 0x698 */ bool field_0x698;
    /* 0x699 */ u8 field_0x699;
    /* 0x69A */ bool field_0x69a;
    /* 0x69C */ s16 field_0x69c;
    /* 0x6A0 */ s32 field_0x6a0;
    /* 0x6A4 */ s32 mInWaterTimer;
    /* 0x6A8 */ cXyz field_0x6a8;
    /* 0x6B4 */ Mtx field_0x6b4;
    /* 0x6E4 */ bool field_0x6e4;
    /* 0x6E6 */ csXyz field_0x6e6;
    /* 0x6EC */ fopAc_ac_c* mpAtHitActor;
    /* 0x6F0 */ cXyz mAtHitPos;
    /* 0x6FC */ f32 mNearestHitDist;
    /* 0x700 */ bool mbHitActor;
    
    static u8 m_keep_type;
    static s16 m_count;
    static const char m_arc_name[];
    static const dCcD_SrcCps m_at_cps_src;
    static const dCcD_SrcSph m_co_sph_src;
};

#endif /* D_A_ARROW_H */
