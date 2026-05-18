#ifndef D_A_DEMO00_H
#define D_A_DEMO00_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"

class dDemo_actor_c;
class mDoExt_McaMorf;
class J3DModel;
class mDoExt_invisibleModel;
class mDoExt_btpAnm;
class mDoExt_btkAnm;
class mDoExt_brkAnm;
struct DEMO_PLIGHT;
class dBgS_GndChk;

class daDemo00_shadow_c {
public:
#if VERSION > VERSION_DEMO
    /* 0x00 */ u32 mShadowID;
#endif
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ f32 mCasterSize;
    /* 0x14 */ f32 mSimpleScale;
};

class daDemo00_resID_c {
public:
    void reset();

public:
    /* 0x00 */ u32 mShapeID;
    /* 0x04 */ u32 mBckID;
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ u32 mBtpID;
    /* 0x10 */ u32 mBtkID;
    /* 0x14 */ u32 mBrkID;
    /* 0x18 */ u32 field_0x18;
    /* 0x1C */ u32 field_0x1C;
    /* 0x20 */ u32 mPlightID;
    /* 0x24 */ u32 mShadowID;
};

class daDemo00_bgc_c {
public:
    /* 0x00 */ dBgS_GndChk mGndChk;
    /* 0x54 */ f32 mGroundY;
};

class daDemo00_model_c {
public:
    void reset();

public:
    /* 0x00 */ daDemo00_resID_c mID;
    /* 0x28 */ mDoExt_McaMorf* mpMorf;
    /* 0x2C */ J3DModel* mpModel;
    /* 0x30 */ mDoExt_invisibleModel* mpInvisibleModel;
    /* 0x34 */ mDoExt_btpAnm* mpBtpAnm;
    /* 0x38 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x3C */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x40 */ void* field_0x40;
    /* 0x44 */ daDemo00_shadow_c* mpShadow;
    /* 0x48 */ DEMO_PLIGHT* mpPlight;
    /* 0x4C */ daDemo00_bgc_c* mBgc;
};

class daDemo00_c : public fopAc_ac_c {
public:
#if VERSION > VERSION_DEMO
    ~daDemo00_c();
#endif

    typedef BOOL (daDemo00_c::*ActionFunc)(dDemo_actor_c* act);

    BOOL action(dDemo_actor_c* act) { return (this->*mActionFunc)(act); }
    void setAction(ActionFunc func) { mActionFunc = func; }

    void setBaseMtx();
    void setShadowSize();
    BOOL createHeap();
    BOOL actStandby(dDemo_actor_c*);
    BOOL actPerformance(dDemo_actor_c*);
    BOOL actLeaving(dDemo_actor_c*);
    inline BOOL create();
    BOOL draw();
    inline BOOL execute();

public:
    /* 0x290 */ ActionFunc mActionFunc;
    /* 0x29C */ u8 field_0x29c;
    /* 0x29D */ s8 field_0x29d;
    /* 0x29E */ u8 field_0x29e;
    /* 0x29F */ u8 field_0x29f;
    /* 0x2A0 */ daDemo00_resID_c mNextID;
    /* 0x2C8 */ daDemo00_model_c mModel;
};

#endif /* D_A_DEMO00_H */
