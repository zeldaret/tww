#ifndef D_A_ITEMBASE_H
#define D_A_ITEMBASE_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

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
    /* 0x16 */ short field6_0x16;
    /* 0x18 */ short field7_0x18;
    /* 0x1A */ u8 field8_0x1a;
    /* 0x1B */ u8 field9_0x1b;
    /* 0x1C */ short mNumFramesPerFullSpin;
    u8 temp1[0x26];
    /* 0x42 */ short field47_0x42;
    u8 temp2[0x4];
    /* 0x48 */ float mVelocityScale;
};

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
    void chkDraw();
    void dead();
    void chkDead();
    void setLoadError();
    void CheckItemCreateHeap(fopAc_ac_c*);
    void CheckFieldItemCreateHeap(fopAc_ac_c*);

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
    // /* 0x2BC */ dBgS_Acch mAcch;
    // /* 0x480 */ dBgS_AcchCir mAcchCir;
    // /* 0x4C0 */ dCcD_Stts mStts;
    // /* 0x4FC */ dCcD_Cyl mCyl;
    // /* 0x62C */ undefined field14_0x62c;
    // /* 0x62D */ undefined field15_0x62d;
    // /* 0x62E */ undefined field16_0x62e;
    // /* 0x62F */ undefined field17_0x62f;
    u8 temp[0x374];
    /* 0x630 */ int mPickupFlag;
    /* 0x634 */ int field19_0x634;
    /* 0x638 */ short field20_0x638;
    /* 0x63A */ u8 m_itemNo;
    /* 0x63B */ u8 mDrawFlags;
    /* 0x63C */ cXyz mScaleTarget;
};

STATIC_ASSERT(sizeof(daItemBase_c) == 0x648);

#endif /* D_A_ITEMBASE_H */