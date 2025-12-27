#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

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
    fpc_ProcID getPId(void*);
    fopAc_ac_c* convPId(fpc_ProcID);
    int request(fopAc_ac_c*, int);
    void init();
    void proc();

    fopAc_ac_c* getZHintTarget() { return convPId(mZHintTargetID); }

private:
    /* 0x0 */ fpc_ProcID mHintActorID;
    /* 0x4 */ int mPriority;
    /* 0x8 */ fpc_ProcID mZHintTargetID;
};

class dAttCatch_c {
public:
    dAttCatch_c() {}
    fopAc_ac_c* convPId(fpc_ProcID);
    void init();
    void proc();
    bool request(fopAc_ac_c*, u8, f32, f32, f32, s16, int);

    fopAc_ac_c* getCatghTarget() { return convPId(mCatghTargetID); }
    u8 getChangeItem() { return mChangeItem; }

private:
    /* 0x00 */ fpc_ProcID mRequestActorID;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ f32 mDistance;
    /* 0x0C */ u8 mCatchItemNo;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ fpc_ProcID mCatghTargetID;
    /* 0x14 */ u8 mChangeItem;
};  // Size: 0x18

class dAttParam_c {
public:
    /* 0x00 */ u16 mFlags;
    /* 0x02 */ u8 field_0x02[0x04 - 0x02];
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 mDangerBGMDistance;
    /* 0x14 */ f32 mBGMDistMargin;
    /* 0x18 */ f32 mSWModeDisable;
    /* 0x1C vtable */

public:
    dAttParam_c() {}
    dAttParam_c(s32);

    virtual ~dAttParam_c();

    // These are likely debug-only functions.
    // void CheckFlag(u16) {}
    // void FreeStick() {}
    // void connectHIO() {}
    // void genMessage(JORMContext*) {}
    // void releaseHIO() {}
};  // Size: 0x20

class dAttLook_c {
public:
    fopAc_ac_c* convPId(fpc_ProcID);
    void init();
    void proc();
    bool request(fopAc_ac_c*, f32, f32, f32, s16, int);
    bool requestF(fopAc_ac_c*, s16, int);

    fopAc_ac_c* getLookTarget() { return convPId(mLookTargetID); }

private:
    /* 0x0 */ fpc_ProcID mRequestActorID;
    /* 0x4 */ s32 field_0x4;
    /* 0x8 */ f32 mDistance;
    /* 0xC */ fpc_ProcID mLookTargetID;
};  // Size: 0x10

class dAttList_c {
public:
    fopAc_ac_c* getActor();
    void setActor(fopAc_ac_c*);

    fpc_ProcID getPid() { return mActorID; }

    /* 0x0 */ f32 mWeight;
    /* 0x4 */ f32 mDistance;
    /* 0x8 */ u32 mType;
    /* 0xC */ fpc_ProcID mActorID;
};  // Size: 0x10

class dAttDraw_CallBack_c : public mDoExt_McaMorfCallBack1_c {
public:
    virtual bool execute(u16, J3DTransformInfo*);
};

class daPy_lk_c;

enum AttentionFlags {
    AttnFlag_00000001 = 0x00000001,
    AttnFlag_00000002 = 0x00000002,
    AttnFlag_00000004 = 0x00000004,
    AttnFlag_00000008 = 0x00000008,
    AttnFlag_00000010 = 0x00000010,
    AttnFlag_00000020 = 0x00000020,
    AttnFlag_00000040 = 0x00000040,
    AttnFlag_00000080 = 0x00000080,
    AttnFlag_00000100 = 0x00000100,
    AttnFlag_00000200 = 0x00000200,
    AttnFlag_00000400 = 0x00000400,
    AttnFlag_00000800 = 0x00000800,
    AttnFlag_00001000 = 0x00001000,
    AttnFlag_00002000 = 0x00002000,
    AttnFlag_00004000 = 0x00004000,
    AttnFlag_00008000 = 0x00008000,
    AttnFlag_00010000 = 0x00010000,
    AttnFlag_00020000 = 0x00020000,
    AttnFlag_00040000 = 0x00040000,
    AttnFlag_00080000 = 0x00080000,
    AttnFlag_00100000 = 0x00100000,
    AttnFlag_00200000 = 0x00200000,
    AttnFlag_00400000 = 0x00400000,
    AttnFlag_00800000 = 0x00800000,
    AttnFlag_01000000 = 0x01000000,
    AttnFlag_02000000 = 0x02000000,
    AttnFlag_04000000 = 0x04000000,
    AttnFlag_08000000 = 0x08000000,
    AttnFlag_10000000 = 0x10000000,
    AttnFlag_20000000 = 0x20000000,
    AttnFlag_40000000 = 0x40000000,
    AttnFlag_80000000 = 0x80000000,
};
class dAttention_c {
    enum LockState {
        LockState_NONE = 0,
        LockState_LOCK = 1,
        LockState_RELEASE = 2,
    };
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
    BOOL chkAttMask(u32, u32);
    f32 calcWeight(int, fopAc_ac_c*, f32, s16, s16, u32*);
    void setLList(fopAc_ac_c*, f32, f32, u32);
    void setAList(fopAc_ac_c*, f32, f32, u32);
    void initList(u32);
    s32 makeList();
    int SelectAttention(fopAc_ac_c*);
    void sortList();
    fopAc_ac_c *stockAttention(u32);
    fopAc_ac_c *nextAttention(u32);
    s32 freeAttention();
    bool chaseAttention();
    f32 EnemyDistance(fopAc_ac_c*);
    void runSoundProc();
    void runDrawProc();
    void runDebugDisp0();
    void runDebugDisp();
    void judgementButton();
    void judgementTriggerProc();
    BOOL judgementLostCheck();
    void judgementStatusSw(u32);
    void judgementStatusHd(u32);
    bool Run(u32 interactMask);
    void Draw();
    fopAc_ac_c* LockonTarget(s32);
    f32 LockonReleaseDistanse();
    fpc_ProcID LockonTargetPId(s32);
    fopAc_ac_c* ActionTarget(s32);
    bool LockonTruth();

    void Init(fopAc_ac_c* i_owner, u32 i_padNo) {
        mpPlayer = (daPy_lk_c*)i_owner;
        mPadNo = i_padNo;
    }

    fopAc_ac_c* Owner() { return (fopAc_ac_c*)mpPlayer; }
    
    bool chkFlag(u32 flag) { return (mFlags & flag) ? true : false; }
    void setFlag(u32 flag) { mFlags |= flag; }
    void clrFlag(u32 flag) { mFlags &= ~flag; }
    void changeOwner() { setFlag(AttnFlag_00000080); }
    bool Lockon() { return LockonTruth() || chkFlag(AttnFlag_20000000); } // regswap
    void offAleart() { setFlag(AttnFlag_80000000); }
    void revivalAleart() { clrFlag(AttnFlag_80000000); }

    void CatchRequest(fopAc_ac_c* reqActor, u8 itemNo, f32 horizontalDist, f32 upDist,
                      f32 downDist, s16 angle, int param_6) {
        mCatch.request(reqActor, itemNo, horizontalDist, upDist, downDist, angle, param_6);
    }
    u8 getCatchChgItem() { return mCatch.getChangeItem(); }
    fopAc_ac_c* getCatghTarget() { return mCatch.getCatghTarget(); }

    fopAc_ac_c* getLookTarget() { return mLook[0].getLookTarget(); }
    fopAc_ac_c* getLook2Target() { return mLook[1].getLookTarget(); }
    fopAc_ac_c* getZHintTarget() { return mHint.getZHintTarget(); }

    int ZHintRequest(fopAc_ac_c* i_actor, int priority) {
        return mHint.request(i_actor, priority);
    }

    int GetLockonCount() { return mLockonCount; }

    static s32 loc_type_num;
    static u32 act_type_num;
    struct LocTbl {
        s16 mType;
        u16 mMask;
    };
    static LocTbl loc_type_tbl[3];
    static LocTbl act_type_tbl[5];
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
    void LockEdge() {}
    bool chkEnemySound() { return chkFlag(AttnFlag_00000100); }
    void LookRequest(fopAc_ac_c* reqActor, f32 horizontalDist, f32 upDist, f32 downDist, s16 angle, int param_5) {
        mLook[0].request(reqActor, horizontalDist, upDist, downDist, angle, param_5);
    }
    void Look2RequestF(fopAc_ac_c* param_1, s16 param_2, int param_3) {mLook[1].requestF(param_1,param_2,param_3);}

public:
    /* 0x000 */ daPy_lk_c* mpPlayer;
    /* 0x004 */ fpc_ProcID mLockonTargetID;
    /* 0x008 */ dAttDraw_CallBack_c mCallBack;
    /* 0x00C */ int mPadNo;
    /* 0x010 */ u32 mFlagMask;
    /* 0x014 */ u8 field_0x014[0x018 - 0x014];
    /* 0x018 */ u8 mLockOnState;
    /* 0x019 */ u8 field_0x019; // data copied from mLockState, looks to be same as TP's dAttention_c::field_0x32a
    /* 0x01A */ u8 field_0x01a;
    /* 0x01B */ u8 field_0x01b;
    /* 0x01C */ s16 field_0x01c;
    /* 0x020 */ u32 mFlags;
    /* 0x024 */ JKRSolidHeap* heap;
    /* 0x028 */ s8 field_0x028; // looks to be same as TP's dAttention_c::field_0x328
    /* 0x02C */ cXyz mDrawAttnPos;
    /* 0x038 */ dAttDraw_c draw[2];
    /* 0x050 */ fpc_ProcID mDrawLockonTargetID;
    /* 0x054 */ dAttList_c mLockOnList[8];
    /* 0x0D4 */ int mLockonCount;
    /* 0x0D8 */ int mLockOnOffset;
    /* 0x0DC */ dAttList_c mActionList[4];
    /* 0x11C */ int mActionCount;
    /* 0x120 */ int mActionOffset;
    /* 0x124 */ dAttHint_c mHint;
    /* 0x130 */ dAttCatch_c mCatch;
    /* 0x148 */ dAttLook_c mLook[2];
    /* 0x168 */ fpc_ProcID mEnemyID;
    /* 0x16C */ f32 mEnemyDistance;
    /* 0x170 */ dAttParam_c mAttParam;
};  // Size: 0x190

STATIC_ASSERT(sizeof(dAttention_c) == 0x190);

#endif /* D_D_ATTENTION_H */
