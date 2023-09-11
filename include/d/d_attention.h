#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

#include "SSystem/SComponent/c_angle.h"
#include "m_Do/m_Do_ext.h"

class fopAc_ac_c;

class dAttHint_c {
public:
    dAttHint_c() {}
    u32 getPId(void*);
    fopAc_ac_c* convPId(unsigned int);
    int request(fopAc_ac_c*, int);
    void init();
    void proc();

private:
    /* 0x0 */ u32 mHintActorID;
    /* 0x4 */ int mPriority;
    /* 0x8 */ u32 field_0x8;
};

class dAttCatch_c {
public:
    dAttCatch_c() {}
    fopAc_ac_c* convPId(unsigned int);
    void init();
    void proc();
    void request(fopAc_ac_c*, u8, f32, f32, f32, s16, int);

    fopAc_ac_c* getCatghTarget() { return convPId(mCatghTargetID); }
    u8 getChangeItem() { return mChangeItem; }

private:
    /* 0x00 */ u32 field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u32 mCatghTargetID;
    /* 0x14 */ u8 mChangeItem;
};  // Size: 0x18

class dAttParam_c {
public:
    /* 0x00 */ u16 field_0x00;
    /* 0x02 */ u8 field_0x02[0x04 - 0x02];
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;

public:
    dAttParam_c() {}
    dAttParam_c(s32);

    virtual ~dAttParam_c();

    /* 0x1C vtable */
};  // Size: 0x20

class dAttLook_c {
public:
    /* 80073CA4 */ fopAc_ac_c* convPId(unsigned int);
    /* 80073CD4 */ void init();
    /* 80073CEC */ void proc();
    /* 80073D08 */ void request(fopAc_ac_c*, f32, f32, f32, s16, int);

private:
    u32 field_0x0;
    u32 field_0x4;
    f32 field_0x8;
    u32 mLookTargetID;
};  // Size: 0x10

class dAttList_c {
public:
    fopAc_ac_c* getActor();
    void setActor(fopAc_ac_c*);

    u32 getPid() { return mActorID; }

    /* 0x0 */ f32 mWeight;
    /* 0x4 */ f32 mDistance;
    /* 0x8 */ u32 mType;
    /* 0xC */ u32 mActorID;
};  // Size: 0x10

class dAttDraw_CallBack_c : public mDoExt_McaMorfCallBack1_c {
public:
    /* 80070178 */ virtual void execute(u16, J3DTransformInfo*);
};

class daPy_lk_c;

class dAttention_c {
public:
    dAttention_c() {}

    dAttention_c(fopAc_ac_c*, u32);
    ~dAttention_c();

    void GetActionList(s32);
    void GetLockonList(s32);
    void getActionBtnB();
    void getActionBtnXYZ_local(int);
    void getActionBtnX();
    void getActionBtnY();
    void getActionBtnZ();
    void chkAttMask(u32, u32);
    void calcWeight(int, fopAc_ac_c*, f32, s16, s16, u32*);
    void setLList(fopAc_ac_c*, f32, f32, u32);
    void setAList(fopAc_ac_c*, f32, f32, u32);
    void initList(u32);
    void makeList();
    void SelectAttention(fopAc_ac_c*);
    void sortList();
    void stockAttention(u32);
    void nextAttention(u32);
    void freeAttention();
    void chaseAttention();
    void EnemyDistance(fopAc_ac_c*);
    void runSoundProc();
    void runDrawProc();
    void runDebugDisp0();
    void runDebugDisp();
    void judgementButton();
    void judgementTriggerProc();
    void judgementLostCheck();
    void judgementStatusSw(u32);
    void judgementStatusHd(u32);
    void Run(u32);
    void Draw();
    void LockonTarget(s32);
    void LockonReleaseDistanse();
    void LockonTargetPId(s32);
    void ActionTarget(s32);
    void LockonTruth();
    void Lockon();

public:
    /* 0x000 */ daPy_lk_c* mpPlayer;
    /* 0x004 */ int mLockOnTargetBsPcID;
    /* 0x008 */ dAttDraw_CallBack_c field_0x8;
    /* 0x00C */ int mPlayerNo;
    /* 0x010 */ u32 mFlagMask;
    /* 0x014 */ u8 field_0x014[0x018 - 0x014];
    /* 0x018 */ u8 mLockOnState;
    /* 0x019 */ u8 field_0x019;
    /* 0x01A */ u8 field_0x01a;
    /* 0x01B */ u8 field_0x01b;
    /* 0x01C */ s16 field_0x01c;
    /* 0x01E */ u8 field_0x01E[0x020 - 0x01E];
    /* 0x020 */ u32 mFlags;
    /* 0x024 */ JKRHeap* mpHeap;
    /* 0x028 */ u8 field_0x028;
    /* 0x029 */ u8 field_0x029[0x054 - 0x029];
    /* 0x054 */ dAttList_c mLockOnList[8];
    /* 0x0D4 */ int mLockOnNum;
    /* 0x0D8 */ int mLockOnOffs;
    /* 0x0DC */ dAttList_c mActionList[4];
    /* 0x11C */ int mActionNum;
    /* 0x120 */ int mActionOffs;
    /* 0x124 */ dAttHint_c mHint;
    /* 0x130 */ dAttCatch_c mCatch;
    /* 0x148 */ dAttLook_c field_0x148;
    /* 0x158 */ dAttLook_c field_0x158;
    /* 0x168 */ int mEnemyBsPcId;
    /* 0x16C */ f32 mEnemyDistance;
    /* 0x170 */ dAttParam_c mAttParam;
};  // Size: 0x190

STATIC_ASSERT(sizeof(dAttention_c) == 0x190);

#endif /* D_D_ATTENTION_H */