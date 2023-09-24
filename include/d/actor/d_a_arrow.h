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

class daArrow_c : fopAc_ac_c {
public:
    enum ArrowType {
        TYPE_NORMAL = 0,
        TYPE_FIRE = 1,
        TYPE_ICE = 2,
        TYPE_LIGHT = 3,
    };
    
    typedef BOOL (daArrow_c::*daArrow_c_ProcFunc)();
    
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
    void check_water_in();
    BOOL changeArrowMp();
    void changeArrowType();
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
    daArrow_c();
    BOOL _delete();
    
    // TODO inlines
    // setAtHitPosBuff__9daArrow_cFP4cXyz
    // setAtHitNormal__9daArrow_cFv
    // setAtHitNormalActor__9daArrow_cFP10fopAc_ac_c
    // clrAtHitNormal__9daArrow_cFv
    // isSetByZelda__9daArrow_cFv
    // clrAtHitPosBuff__9daArrow_cFP4cXyz
    // getAtHitPosBuffP__9daArrow_cFv
    // getAtHitNormalActor__9daArrow_cFv
    // chkAtHitNormal__9daArrow_cFv
    // isLinkReflect__9daArrow_cFv
    // ArrowAtOff__9daArrow_cFv

public:
    /* 0x290 */ bool mbShotByZelda;
    /* 0x291 */ u8 field_0x291[0x294 - 0x291];
    /* 0x294 */ J3DModel* mpModel;
    /* 0x298 */ J3DMaterial* mpTipMat;
    /* 0x29C */ J3DAnmTextureSRTKey* mpBtk;
    /* 0x2A0 */ dBgS_ArrowLinChk mLinChk;
    /* 0x30C */ dBgS_ObjGndChk mGndChk;
    /* 0x360 */ dCcD_Stts mStts;
    /* 0x39C */ dCcD_Cps mCps;
    /* 0x4D4 */ dCcD_Sph mSph;
    /* 0x600 */ u8 field_0x600[0x601 - 0x600];
    /* 0x601 */ u8 mArrowType;
    /* 0x602 */ s16 field_0x602;
    /* 0x604 */ s16 field_0x604;
    /* 0x606 */ u8 field_0x606[0x608 - 0x606];
    /* 0x608 */ s16 field_0x608;
    /* 0x60A */ u8 field_0x60A[0x60C - 0x60A];
    /* 0x60C */ JPABaseEmitter* mpSparkleEmitter;
    /* 0x610 */ s32 mHitActorProcID;
    /* 0x614 */ s32 mHitJointIndex;
    /* 0x618 */ cXyz field_0x618;
    /* 0x624 */ u8 field_0x624[0x660 - 0x624];
    /* 0x660 */ f32 mBtkFrame;
    /* 0x664 */ u8 field_0x664;
    /* 0x665 */ u8 field_0x665[0x668 - 0x665];
    /* 0x668 */ dPa_followEcallBack mPtclFollowCb;
    /* 0x67C */ csXyz field_0x67c;
    /* 0x682 */ u8 field_0x682;
    /* 0x683 */ u8 field_0x683[0x684 - 0x683];
    /* 0x684 */ u32 field_0x684;
    /* 0x688 */ bool field_0x688;
    /* 0x689 */ u8 field_0x689[0x68C - 0x689];
    /* 0x68C */ daArrow_c_ProcFunc mCurrProcFunc;
    /* 0x698 */ u8 field_0x698;
    /* 0x699 */ u8 field_0x699;
    /* 0x69A */ u8 field_0x69a;
    /* 0x69B */ u8 field_0x69B[0x69C - 0x69B];
    /* 0x69C */ s16 field_0x69c;
    /* 0x69E */ u8 field_0x69E[0x6A0 - 0x69E];
    /* 0x6A0 */ s32 field_0x6a0;
    /* 0x6A4 */ s32 mInWaterTimer;
    /* 0x6A8 */ cXyz field_0x6a8;
    /* 0x6B4 */ u8 field_0x6B4[0x6E4 - 0x6B4];
    /* 0x6E4 */ u8 field_0x6e4;
    /* 0x6E5 */ u8 field_0x6E5[0x6E6 - 0x6E5];
    /* 0x6E6 */ csXyz field_0x6e6;
    /* 0x6EC */ fopAc_ac_c* field_0x6ec;
    /* 0x6F0 */ cXyz mNearestHitPos;
    /* 0x6FC */ f32 mNearestHitDist;
    /* 0x700 */ bool mbHitActor;
    /* 0x701 */ u8 field_0x701[0x704 - 0x701];
    
    static u8 m_keep_type;
    static s16 m_count;
    static const char m_arc_name[];
    static const dCcD_SrcCps m_at_cps_src;
    static const dCcD_SrcSph m_co_sph_src;
};

// Intellisense doesn't understand PTMF sizes
#ifndef __INTELLISENSE__
STATIC_ASSERT(sizeof(daArrow_c) == 0x704);
#endif

#endif /* D_A_ARROW_H */
