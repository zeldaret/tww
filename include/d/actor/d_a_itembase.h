#ifndef D_A_ITEMBASE_H
#define D_A_ITEMBASE_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"

class mDoExt_btkAnm;
class mDoExt_brkAnm;
class mDoExt_bckAnm;

struct daItemBase_c_m_data {
    /* 0x00 */ float mFieldItemGravity;
    /* 0x04 */ float field1_0x4;
    /* 0x08 */ float field2_0x8;
    /* 0x0C */ float mScaleAnimSpeed;
    /* 0x10 */ float field4_0x10;
    /* 0x14 */ short field5_0x14;
    /* 0x16 */ short mDuration;
    /* 0x18 */ short field7_0x18;
    /* 0x1A */ u8 field8_0x1a;
    /* 0x1B */ u8 field9_0x1b;
    /* 0x1C */ short mNumFramesPerFullSpin;
    u8 temp1[0x1A];
    /* 0x38 */ f32 mPickedUpInitialSpeedY;
    /* 0x3C */ f32 mPickedUpGravity;
    /* 0x40 */ short field45_0x40;
    /* 0x42 */ short field47_0x42;
    u8 temp2[0x4];
    /* 0x48 */ float mVelocityScale;
};

STATIC_ASSERT(sizeof(daItemBase_c_m_data) == 0x4C);

struct daItemBase_c : public fopAc_ac_c {
public:
    s32 DeleteBase(const char*);
    s32 CreateItemHeap(const char*, short, short, short, short, short, short, short);
    virtual s32 DrawBase();
    virtual void setListStart();
    void setListEnd();
    virtual void settingBeforeDraw();
    virtual void setTevStr();
    virtual void setShadow();
    virtual void animEntry();
    void animPlay(float, float, float, float, float);
    virtual s32 clothCreate();

    void getItemNo();
    void getHeight();
    void getR();
    void hide();
    void show();
    void changeDraw();
    bool chkDraw();
    void dead();
    void chkDead();
    void setLoadError();

    daItemBase_c_m_data* getData();

    static daItemBase_c_m_data m_data;

public:
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ J3DModel* mModel;
    /* 0x2A0 */ J3DModel* mModelArrow[2]; // Extra models for arrow bundles
    /* 0x2A8 */ mDoExt_btkAnm* mBtkAnm1;
    /* 0x2AC */ mDoExt_btkAnm* mBtkAnm2;
    /* 0x2B0 */ mDoExt_brkAnm* mBrkAnm1;
    /* 0x2B4 */ mDoExt_brkAnm* mBrkAnm2;
    /* 0x2B8 */ mDoExt_bckAnm* mBckAnm;
    /* 0x2BC */ dBgS_Acch mAcch;
    /* 0x480 */ dBgS_AcchCir mAcchCir;
    /* 0x4C0 */ dCcD_Stts mStts;
    /* 0x4FC */ dCcD_Cyl mCyl;
    /* 0x62C */ u8 field14_0x62c[0x630 - 0x62C];
    /* 0x630 */ int mPickupFlag;
    /* 0x634 */ int field19_0x634;
    /* 0x638 */ short field20_0x638;
    /* 0x63A */ u8 m_itemNo;
    /* 0x63B */ u8 mDrawFlags;
    /* 0x63C */ cXyz mScaleTarget;
};

STATIC_ASSERT(sizeof(daItemBase_c) == 0x648);

#endif /* D_A_ITEMBASE_H */