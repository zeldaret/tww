
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "dolphin/types.h"

class daArrow_c : fopAc_ac_c {
public:
    enum ArrowType {
        NORMAL_ARROWS = 0,
        FIRE_ARROWS = 1,
        ICE_ARROWS = 2,
        LIGHT_ARROWS = 3,
    };
    
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
    void procWait();
    void procMove();
    void procReturn();
    void procStop_BG();
    void procStop_Actor();
    void procWater();
    void checkRestMp();
    void setTypeByPlayer();
    void createInit();
    BOOL _execute();
    BOOL _draw();
    s32 _create();
    daArrow_c();
    BOOL _delete();

public:
    /* 0x290 */ bool mbShotByZelda;
    /* 0x291 */ u8 field_0x291[0x294 - 0x291];
    /* 0x294 */ J3DModel* mpModel;
    /* 0x298 */ u8 field_0x298[0x2A0 - 0x298];
    /* 0x2A0 */ dBgS_ArrowLinChk mLinChk;
    /* 0x30C */ dBgS_ObjGndChk mGndChk;
    /* 0x360 */ dCcD_Stts mStts;
    /* 0x39C */ dCcD_Cps mCps;
    /* 0x4D4 */ dCcD_Sph mSph;
    /* 0x600 */ u8 field_0x600[0x601 - 0x600];
    /* 0x601 */ u8 mArrowType;
    /* 0x602 */ s16 field_0x602;
    /* 0x604 */ s16 field_0x604;
    /* 0x606 */ u8 field_0x606[0x610 - 0x606];
    /* 0x610 */ s32 mHitActorProcID;
    /* 0x614 */ s32 mHitJointIndex;
    /* 0x618 */ cXyz field_0x618;
    /* 0x624 */ u8 field_0x624[0x668 - 0x624];
    /* 0x668 */ dPa_followEcallBack mPtclFollowCb;
    /* 0x67C */ csXyz field_0x67c;
    /* 0x682 */ u8 field_0x682;
    /* 0x683 */ u8 field_0x683[0x684 - 0x683];
    /* 0x684 */ u32 field_0x684;
    /* 0x688 */ bool field_0x688;
    /* 0x689 */ u8 field_0x689[0x6A8 - 0x689];
    /* 0x6A8 */ cXyz field_0x6a8;
    /* 0x6B4 */ u8 field_0x6B4[0x6E6 - 0x6B4];
    /* 0x6E6 */ csXyz field_0x6e6;
    /* 0x6EC */ fopAc_ac_c* field_0x6ec;
    /* 0x6F0 */ cXyz mNearestHitPos;
    /* 0x6FC */ f32 mNearestHitDist;
    /* 0x700 */ bool mbHitActor;
    /* 0x701 */ u8 field_0x701[0x704 - 0x701];
    
    static u8 m_keep_type;
    static const char m_arc_name[];
};

STATIC_ASSERT(sizeof(daArrow_c) == 0x704);
