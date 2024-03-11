#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

#include "SSystem/SComponent/c_angle.h"
#include "m_Do/m_Do_ext.h"

class fopAc_ac_c;
class mDoExt_McaMorf;
class J3DAnmColor;
class J3DMatColorAnm;

class dAttDraw_c {
public:
    void setAnm(int, int, int);
    void draw(cXyz&, Mtx);

    /* 0x0 */ mDoExt_McaMorf * anm;
    /* 0x4 */ J3DAnmColor * mpAnmClr;
    /* 0x8 */ J3DMatColorAnm * mpAnmMatClr;
};

class dAttHint_c {
public:
    dAttHint_c() {}
    uint getPId(void*);
    fopAc_ac_c* convPId(uint);
    int request(fopAc_ac_c*, int);
    void init();
    void proc();

    fopAc_ac_c* getZHintTarget() { return convPId(field_0x8); }

private:
    /* 0x0 */ uint mHintActorID;
    /* 0x4 */ int mPriority;
    /* 0x8 */ uint field_0x8;
};

class dAttCatch_c {
public:
    dAttCatch_c() {}
    fopAc_ac_c* convPId(uint);
    void init();
    void proc();
    void request(fopAc_ac_c*, u8, f32, f32, f32, s16, int);

    fopAc_ac_c* getCatghTarget() { return convPId(mCatghTargetID); }
    u8 getChangeItem() { return mChangeItem; }

private:
    /* 0x00 */ uint field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ uint mCatghTargetID;
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
    fopAc_ac_c* convPId(uint);
    void init();
    void proc();
    void request(fopAc_ac_c*, f32, f32, f32, s16, int);
    void requestF(fopAc_ac_c*, s16, int);

    uint getLookTarget() { return mLookTargetID; }

private:
    /* 0x0 */ uint field_0x0;
    /* 0x4 */ u32 field_0x4;
    /* 0x8 */ f32 field_0x8;
    /* 0xC */ uint mLookTargetID;
};  // Size: 0x10

class dAttList_c {
public:
    fopAc_ac_c* getActor();
    void setActor(fopAc_ac_c*);

    uint getPid() { return mActorID; }

    /* 0x0 */ f32 mWeight;
    /* 0x4 */ f32 mDistance;
    /* 0x8 */ u32 mType;
    /* 0xC */ uint mActorID;
};  // Size: 0x10

class dAttDraw_CallBack_c : public mDoExt_McaMorfCallBack1_c {
public:
    virtual bool execute(u16, J3DTransformInfo*);
};

class daPy_lk_c;

class dAttention_c {
public:
    dAttention_c() {}

    dAttention_c(fopAc_ac_c*, u32);
    ~dAttention_c();

    dAttList_c* GetActionList(s32);
    dAttList_c* GetLockonList(s32);
    dAttList_c* getActionBtnB();
    dAttList_c* getActionBtnXYZ_local(int);
    dAttList_c* getActionBtnX();
    dAttList_c* getActionBtnY();
    dAttList_c* getActionBtnZ();
    u32 chkAttMask(u32, u32);
    f32 calcWeight(int, fopAc_ac_c*, f32, s16, s16, u32*);
    void setLList(fopAc_ac_c*, f32, f32, u32);
    void setAList(fopAc_ac_c*, f32, f32, u32);
    void initList(u32);
    s32 makeList();
    int SelectAttention(fopAc_ac_c*);
    void sortList();
    void stockAttention(u32);
    void nextAttention(u32);
    s32 freeAttention();
    void chaseAttention();
    f32 EnemyDistance(fopAc_ac_c*);
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
    fopAc_ac_c* LockonTarget(s32);
    void LockonReleaseDistanse();
    uint LockonTargetPId(s32);
    fopAc_ac_c* ActionTarget(s32);
    bool LockonTruth();

    void Init(fopAc_ac_c* i_owner, u32 i_playerNo) {
        mpPlayer = (daPy_lk_c*)i_owner;
        mPlayerNo = i_playerNo;
    }

    fopAc_ac_c* Owner() { return (fopAc_ac_c*)mpPlayer; }
    
    bool chkFlag(u32 flag) { return (mFlags & flag) ? true : false; }
    void setFlag(u32 flag) { mFlags |= flag; }
    void clrFlag(u32 flag) { mFlags &= ~flag; }
    bool Lockon() { return LockonTruth() || chkFlag(0x20000000); } // regswap
    void CatchRequest(fopAc_ac_c* param_0, u8 param_1, f32 param_2, f32 param_3,
                      f32 param_4, s16 param_5, int param_6) {
        mCatch.request(param_0, param_1, param_2, param_3, param_4, param_5, param_6);
    }

    fopAc_ac_c* getLookTarget() { return mLook[0].convPId(mLook[0].getLookTarget()); }
    fopAc_ac_c* getLook2Target() { return mLook[1].convPId(mLook[1].getLookTarget()); }
    fopAc_ac_c* getZHintTarget() { return mHint.getZHintTarget(); }

    static s32 loc_type_num;
    static u32 act_type_num;
    static struct LocTbl {
        s16 mType;
        u16 mMask;
    } loc_type_tbl[3];
    static struct DistTbl {
        f32 mDistXZMax;
        f32 mDistXZMaxRelease;
        f32 mDistXZAngleAdjust;
        f32 mDeltaYMax;
        f32 mDeltaYMin;
        f32 mWeightDivisor;
        int mFrontAngleCheckBits;
    } dist_table[];

    // TODO:
    void GetLockonCount() {}
    void LockEdge() {}
    void changeOwner() {}
    void chkEnemySound() {}
    u8 getCatchChgItem() { return mCatch.getChangeItem(); }
    void getCatghTarget() {}
    void offAleart() {}
    void revivalAleart() {
        clrFlag(0x80000000);
    }
    void LookRequest(fopAc_ac_c*, f32, f32, f32, s16, int) {}
    void Look2RequestF(fopAc_ac_c*, s16, int) {}
    void ZHintRequest(fopAc_ac_c*, int) {}

public:
    /* 0x000 */ daPy_lk_c* mpPlayer;
    /* 0x004 */ int mLockOnTargetBsPcID;
    /* 0x008 */ dAttDraw_CallBack_c mCallBack;
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
    /* 0x024 */ JKRSolidHeap* heap;
    /* 0x028 */ s8 field_0x028;
    /* 0x02C */ cXyz field_0x02c;
    /* 0x038 */ dAttDraw_c draw[2];
    /* 0x050 */ u32 field_0x050;
    /* 0x054 */ dAttList_c mLockOnList[8];
    /* 0x0D4 */ int mLockOnNum;
    /* 0x0D8 */ int mLockOnOffs;
    /* 0x0DC */ dAttList_c mActionList[4];
    /* 0x11C */ int mActionNum;
    /* 0x120 */ int mActionOffs;
    /* 0x124 */ dAttHint_c mHint;
    /* 0x130 */ dAttCatch_c mCatch;
    /* 0x148 */ dAttLook_c mLook[2];
    /* 0x168 */ int mEnemyBsPcId;
    /* 0x16C */ f32 mEnemyDistance;
    /* 0x170 */ dAttParam_c mAttParam;
};  // Size: 0x190

STATIC_ASSERT(sizeof(dAttention_c) == 0x190);

#endif /* D_D_ATTENTION_H */
