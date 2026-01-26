#ifndef D_A_NH_H
#define D_A_NH_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "m_Do/m_Do_ext.h"

class daNh_c : public fopAc_ac_c {
public:
    enum Type {
        TYPE_BOTTLE = 0x01,
        // Any other value besides 0x01 will behave as the normal, non-bottled type.
        // All three of the Forest Fireflies placed in stages have their type set to 0xFF.
        // TYPE_BOTTLE (0x01) is spawned via daPy_lk_c::procBottleOpen.
    };
    
    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };
    
    typedef BOOL (daNh_c::*ActionFunc)(void*);
    
    bool isTypeBottle() { return mType == TYPE_BOTTLE; }
    
    ~daNh_c();
    void setBaseMtx();
    BOOL createHeap();
    cPhs_State create();
    BOOL init();
    void action(void*);
    BOOL setAction(ActionFunc, void*);
    BOOL checkBinCatch();
    BOOL searchPlayer();
    BOOL moveProc(f32, f32, s16);
    f32 getHomeDistance();
    BOOL checkTimer();
    void BGCheck();
    void airMove();
    BOOL waitAction(void*);
    BOOL checkEscapeEnd();
    BOOL escapeAction(void*);
    BOOL returnAction(void*);
    BOOL execute();
    BOOL initBrkAnm(bool);
    void playBrkAnm();
    BOOL draw();

public:
    /* 0x290 */ u8 temp1[0x298 - 0x290];
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgS_ObjAcch mAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ dCcD_Stts mStts;
    /* 0x4DC */ dCcD_Cyl mCyl;
    /* 0x60C */ mDoExt_brkAnm mBrkAnm;
    /* 0x624 */ u8 temp2[0x630 - 0x624];
    /* 0x630 */ cBgS_PolyInfo mPolyInfo;
    /* 0x640 */ ActionFunc mCurrActionFunc;
    /* 0x64C */ Mtx mGlowMtx;
    /* 0x67C */ f32 mPlayerDist;
    /* 0x680 */ f32 mGroundY;
    /* 0x684 */ int mBottleTimer;
    /* 0x688 */ s32 mAlpha;
    /* 0x68C */ u8 unk68C;
    /* 0x68D */ s8 mActionStatus;
    /* 0x68E */ u8 mGlowAlpha;
    /* 0x68F */ u8 mWobbleDir;
    /* 0x690 */ u8 mWobbleTimer;
    /* 0x691 */ u8 mType;
    /* 0x692 */ u8 temp5[0x694 - 0x692];
    /* 0x694 */ s16 mEscapeTimer;
    /* 0x696 */ s16 unk696;
    /* 0x698 */ s16 unk698;
    /* 0x69A */ s16 unk69A;
    /* 0x69C */ u8 temp6[0x6A0 - 0x69C];
    /* 0x6A0 */ f32 unk6A0;
    /* 0x6A4 */ u8 temp7[0x6A8 - 0x6A4];
};

class daNh_HIO_c : public JORReflexible {
    struct hio_prm_c {
        // Note: Offsets are relative to daNh_HIO_c instead of hio_prm_c for convenience.
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ f32 field_0x0c;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 mGlowOffsetY;
        /* 0x18 */ f32 mGlowScale;
        /* 0x1C */ f32 mMinFrightenSpeed;
        /* 0x20 */ f32 mHeightAboveGround;
        /* 0x24 */ f32 mAscentSpeed;
        /* 0x28 */ f32 mDescentSpeed;
        /* 0x2C */ f32 mGravity;
        /* 0x30 */ f32 mMaxHomeDist;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ f32 mModelScale;
        /* 0x3C */ s16 field_0x3c;
        /* 0x3E */ s16 mDefaultGlowAlpha;
        /* 0x40 */ s16 mBottleLifetime;
    };  // Size: 0x3C

public:
    daNh_HIO_c();
    virtual ~daNh_HIO_c() {}
    
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
    /* 0x44 */ daNh_c* mpActor;
};  // Size: 0x48

#endif /* D_A_NH_H */
