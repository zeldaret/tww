#ifndef D_NPC_H
#define D_NPC_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_msg.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_path.h"
#include "m_Do/m_Do_ext.h"

class fopNpc_npc_c;

class dNpc_HIO_c {
public:
    virtual ~dNpc_HIO_c() {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ s16 mMaxHeadX;
    /* 0x0A */ s16 mMaxBackboneX;
    /* 0x0C */ s16 mMaxHeadY;
    /* 0x0E */ s16 mMaxBackboneY;
    /* 0x10 */ s16 mMinHeadX;
    /* 0x12 */ s16 mMinBackboneX;
    /* 0x14 */ s16 mMinHeadY;
    /* 0x16 */ s16 mMinBackboneY;
    /* 0x18 */ s16 mMaxTurnStep;
    /* 0x1A */ s16 mMaxHeadTurnVel; // TODO: Not sure what the difference between this and the above field is
    /* 0x1C */ f32 mAttnYOffset;
    /* 0x20 */ s16 mMaxAttnAngleY;
    /* 0x22 */ u8 m22;
    /* 0x23 */ u8 m23[0x24 - 0x23];
    /* 0x24 */ f32 mMaxAttnDistXZ;
}; // Size: 0x28

class dNpc_JntCtrl_c {
public:
    /* 0x00 */ s16 mAngles[2][2];
    // /* 0x00 */ s16 mHeadUpDownRot;
    // /* 0x02 */ s16 mHeadLeftRightRot;
    // /* 0x04 */ s16 mBackboneUpDownRot;
    // /* 0x06 */ s16 mBackboneLeftRightRot;
    /* 0x08 */ s8 mHeadJntNum;
    /* 0x09 */ s8 mBackboneJntNum;
    /* 0x0A */ bool mbTrn;
    /* 0x0B */ bool mbHeadLock;
    /* 0x0C */ bool mbBackBoneLock;
    /* 0x0D */ u8 field_0x0D;
    /* 0x0E */ s16 mMinAngles[2][2];
    /* 0x16 */ s16 mMaxAngles[2][2];
    // /* 0x0E */ s16 field_0x0E;
    // /* 0x10 */ s16 mMinHeadRot;
    // /* 0x12 */ s16 field_0x12;
    // /* 0x14 */ s16 mMinSpineRot;
    // /* 0x16 */ s16 field_0x16;
    // /* 0x18 */ s16 mMaxHeadRot;
    // /* 0x1A */ s16 field_0x1A;
    // /* 0x1C */ s16 mMaxSpineRot;
    /* 0x1E */ s16 mMaxTurnStep[2][2];
    /* 0x26 */ u8 pad_0x26[0x2C - 0x26];
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;

public:
    dNpc_JntCtrl_c() {
        mbBackBoneLock = false;
        mbHeadLock = false;
    }

    s8 getHeadJntNum() { return mHeadJntNum; }
    s8 getBackboneJntNum() { return mBackboneJntNum; }
    void setHeadJntNum(s8 jnt) { mHeadJntNum = jnt; }
    void setBackboneJntNum(s8 jnt) { mBackboneJntNum = jnt; }
    s16 getHead_x() { return mAngles[0][0]; }
    s16 getHead_y() { return mAngles[0][1]; }
    s16 getBackbone_x() { return mAngles[1][0]; }
    s16 getBackbone_y() { return mAngles[1][1]; }
    void setHead_x(s16 angle) { mAngles[0][0] = angle; }
    void setHead_y(s16 angle) { mAngles[0][1] = angle; }
    void setBackBone_x(s16 angle) { mAngles[1][0] = angle; }
    void setBackBone_y(s16 angle) { mAngles[1][1] = angle; }
    bool trnChk() { return mbTrn; }
    void setTrn() { mbTrn = true; }
    void clrTrn() { mbTrn = false; }
    void onHeadLock() { mbHeadLock = true; }
    void onBackBoneLock() { mbBackBoneLock = true; }
    void offHeadLock() { mbHeadLock = false; }
    void offBackBoneLock() { mbBackBoneLock = false; }

    bool angCalcS(s16*, s16, s16, s16);
    void limitter(s16*, s16, s16);
    bool follow(s16*, s16, s16, int);
    bool move(s16, int);
    void lookAtTarget(s16* outY, cXyz* pDstPos, cXyz srcPos, s16 defaultY, s16 maxVel, bool param_6);
    void setParam(s16 max_backbone_x, s16 max_backbone_y, s16 min_backbone_x, s16 min_backbone_y,
                  s16 max_head_x, s16 max_head_y, s16 min_head_x, s16 min_head_y,
                  s16 max_turn_step);

    int chkLim(s16, int, int);
    void turn_fromBackbone2Head(s16, s16*, s16*, bool);
    void turn_fromHead2Backbone(s16, s16*, s16*);
    s16 follow_current(s16*, s16);
    void lookAtTarget_2(s16*, cXyz*, cXyz, s16, s16, bool);
}; // Size: 0x34

class dNpc_EventCut_c {
private:
    /* 0x00 */ char* mpEvtStaffName;
    /* 0x04 */ int mEvtStaffId;
    /* 0x08 */ fopAc_ac_c* mpActor;
    /* 0x0C */ fopNpc_npc_c* mpTalkActor;
    /* 0x10 */ int mCurActIdx;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int mTimer;
    /* 0x1C */ char* mpActorName;
    /* 0x20 */ u32 field_0x20;
    /* 0x24 */ s32 mSetId;
    /* 0x28 */ cXyz mOffsetPos;
    /* 0x34 */ cXyz mTargetActorPos;
    /* 0x40 */ fopAc_ac_c* mpTargetActor;
    /* 0x44 */ s16 field_0x44;
    /* 0x48 */ f32 mSpeed;
    /* 0x4C */ f32 pDelDistance;
    /* 0x50 */ s16 mAddAngle;
    /* 0x52 */ u8 field_0x52;
    /* 0x54 */ cXyz mPos;
    /* 0x60 */ u8 mbAttention;
    /* 0x61 */ u8 mbNoTurn;
    /* 0x62 */ s16 mTurnSpeed;
    /* 0x64 */ u32 mTurnType;
    /* 0x68 */ dNpc_JntCtrl_c* mpJntCtrl;

public:
    dNpc_EventCut_c() {
        mpActor = 0;
        mpTalkActor = 0;
        mpJntCtrl = 0;
    }

    void setActorInfo(char*, fopAc_ac_c*);
    void setActorInfo2(char*, fopNpc_npc_c*);

    bool cutProc();
    void cutWaitStart();
    void cutWaitProc();
    void cutTurnToActorStart();
    void cutTurnToActorProc();
    void cutMoveToActorStart();
    void cutMoveToActorProc();
    void cutTurnToPosStart();
    void cutTurnToPosProc();
    void cutMoveToPosStart();
    void cutMoveToPosProc();
    void cutTalkMsgStart();
    void cutContinueTalkStart();
    void cutTalkMsgProc();

    char* getActorName() {
        return mpEvtStaffName;
    }

    bool getAttnFlag() {
        return mbAttention;
    }
    cXyz getAttnPos() {
        return mPos;
    }

    void setJntCtrlPtr(dNpc_JntCtrl_c* ctrl) {
        mpJntCtrl = ctrl;
    }
    
    static fopAc_ac_c* findActorCallBack(fopAc_ac_c*, void*);
}; // Size: 0x6C

class dNpc_PathRun_c {
public:
    bool setInfDrct(dPath* pPath);
    bool setInf(u8 pathIdx, s8 roomNo, u8 forwards);
    dPath* nextPath(s8 roomNo);
    cXyz getPoint(u8 pointIdx);
    bool chkPointPass(cXyz, bool);
    bool incIdx();
    bool incIdxLoop();
    bool incIdxAuto();
    bool decIdx();
    bool decIdxLoop();
    bool decIdxAuto();
    bool nextIdx();
    bool nextIdxAuto();
    s32 absIdx(u8, u8);
    u8 maxPoint();
    u8 pointArg(u8 idx);
    bool setNearPathIndx(cXyz*, f32);
    f32 setNearPathIndxMk(cXyz*);
    bool setNearPathIndxMk2(cXyz*, u8, u8);
    bool chkInside(cXyz*);

    /* 0x00 */ dPath* mPath;
    /* 0x04 */ u8 field_0x04;
    /* 0x05 */ u8 mCurrPointIndex;
    /* 0x06 */ u8 mbGoingForwards;
    /* 0x07 */ u8 field_0x07;
}; // Size: 0x08

class dNpc_HeadAnm_c {
public:
    void swing_vertical_init(s16 param_1, s16 param_2, s16 param_3, int param_4);
    void swing_vertical();
    void swing_horizone_init(s16 param_1, s16 param_2, s16 param_3, int param_4);
    void swing_horizone();
    void move();
    
    dNpc_HeadAnm_c() {
        field_0x14 = 0.0f;
        field_0x18 = 0.0f;
        field_0x1C = 0.0f;
        field_0x1E = 0;
        field_0x20 = 0;
        field_0x00 = 0;
        field_0x02 = 0;
        field_0x04 = 0;
    }

    typedef void (dNpc_HeadAnm_c::*swing_func)(void);

    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x08 */ swing_func mFunc;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
    /* 0x20 */ s16 field_0x20;
}; // Size: 0x22

class fopNpc_npc_c : public fopAc_ac_c {
public:
    fopNpc_npc_c() {
        mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
        mpCurrMsg = 0;
    }
    /* 0x290 */ dNpc_JntCtrl_c m_jnt;
    /* 0x2C4 */ dNpc_EventCut_c mEventCut;
    /* 0x330 */ mDoExt_McaMorf* mpMorf;
    /* 0x334 */ dBgS_ObjAcch mObjAcch;
    /* 0x4F8 */ dBgS_AcchCir mAcchCir;
    /* 0x538 */ dCcD_Stts mStts;
    /* 0x574 */ dCcD_Cyl mCyl;
    /* 0x6A4 */ u32 mCurrMsgNo;
    /* 0x6A8 */ u32 mEndMsgNo;
    /* 0x6AC */ uint mCurrMsgBsPcId;
    /* 0x6B0 */ msg_class* mpCurrMsg;
    /* 0x6B4 */ u8 field_0x6b4[6];
    /* 0x6BA */ u16 field_0x6ba;
    /* 0x6BC */ u8 field_0x6bc[4];
    /* 0x6C0 */ /* vtable */

    virtual u16 next_msgStatus(u32* pMsgNo) { return fopMsgStts_MSG_ENDS_e; }
    virtual u32 getMsg() { return 0; }
    virtual void anmAtr(u16) {}

    void setCollision(float radius, float height);
    u16 talk(int);
};  // Size: 0x6C4

bool dNpc_setAnmIDRes(mDoExt_McaMorf* pMorf, int loopMode, float morf, float speed, int animResId, int soundResId, const char* arcName);
bool dNpc_setAnmFNDirect(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, char* animFilename, char* soundFilename, const char* arcName);
bool dNpc_setAnm(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileIdx, int soundFileIdx, const char* arcName);
void dNpc_setShadowModel(J3DModel*, J3DModelData*, J3DModel*);
cXyz dNpc_playerEyePos(f32);
void dNpc_calc_DisXZ_AngY(cXyz, cXyz, float*, short*);
bool dNpc_chkArasoi();
bool dNpc_chkLetterPassed();
bool dNpc_setAnm_2(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileIdx, int soundFileIdx, const char* arcName);

#endif /* D_NPC_H */
