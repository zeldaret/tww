#ifndef D_A_DEMO00_H
#define D_A_DEMO00_H

#include "f_op/f_op_actor.h"

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
    /* 0x00 */ u32 shadowID;
#endif
    /* 0x04 */ cXyz pos;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};

class daDemo00_resID_c {
public:
    void reset();

public:
    /* 0x00 */ u32 modelID;
    /* 0x04 */ s32 bckID;
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ s32 btpID;
    /* 0x10 */ s32 btkID;
    /* 0x14 */ s32 brkID;
    /* 0x18 */ s32 field_0x18;
    /* 0x1C */ s32 field_0x1C;
    /* 0x20 */ u32 plightID;
    /* 0x24 */ s32 shadowID;
};

class daDemo00_model_c {
public:
    void reset();

public:
    /* 0x00 */ daDemo00_resID_c resID;
    /* 0x28 */ mDoExt_McaMorf* morf;
    /* 0x2C */ J3DModel* model;
    /* 0x30 */ mDoExt_invisibleModel* invisibleModel;
    /* 0x34 */ mDoExt_btpAnm* btpAnm;
    /* 0x38 */ mDoExt_btkAnm* btkAnm;
    /* 0x3C */ mDoExt_brkAnm* brkAnm;
    /* 0x40 */ void * field_0x40;
    /* 0x44 */ daDemo00_shadow_c* shadow;
    /* 0x48 */ DEMO_PLIGHT* plight;
};

class daDemo00_bgc_c {
};

class daDemo00_c : public fopAc_ac_c {
public:
#if VERSION > VERSION_DEMO
    ~daDemo00_c();
#endif

    typedef BOOL (daDemo00_c::*ActionFunc)(dDemo_actor_c* act);

    BOOL action(dDemo_actor_c* act) { return (this->*actionFunc)(act); }
    void setAction(ActionFunc func) { actionFunc = func; }

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
    /* 0x290 */ ActionFunc actionFunc;
    /* 0x29C */ u8 field_0x29c;
    /* 0x29D */ s8 field_0x29d;
    /* 0x29E */ u8 field_0x29e;
    /* 0x29F */ u8 field_0x29f;
    /* 0x2A0 */ daDemo00_resID_c nextRes;
    /* 0x2C8 */ daDemo00_model_c model;
    /* 0x314 */ dBgS_GndChk* chk;
};

#endif /* D_A_DEMO00_H */
