#ifndef D_NPC_H
#define D_NPC_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_msg.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_path.h"
#include "m_Do/m_Do_ext.h"

class fopNpc_npc_c;

class dNpc_JntCtrl_c {
    /* 0x00 */ s16 mHeadUpDownRot;
    /* 0x02 */ s16 mHeadLeftRightRot;
    /* 0x04 */ s16 mBackboneUpDownRot;
    /* 0x06 */ s16 mBackboneLeftRightRot;
    /* 0x08 */ u8 mHeadJntNum;
    /* 0x09 */ u8 mBackboneJntNum;
    /* 0x0A */ bool field_0x0A;
    /* 0x0B */ u8 field_0x0B;
    /* 0x0C */ u8 field_0x0C;
    /* 0x0D */ u8 field_0x0D;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 mMinHeadRot;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 mMinSpineRot;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 mMaxHeadRot;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ s16 mMaxSpineRot;
    /* 0x1E */ s16 field_0x1E;
    /* 0x20 */ s16 field_0x20;
    /* 0x22 */ s16 field_0x22;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ u8 pad_0x26[0x32 - 0x26];
    /* 0x32 */ s16 field_0x32;

public:
    bool angCalcS(s16*, s16, s16, s16);
    void limitter(s16*, s16, s16);
    void follow(s16*, s16, s16, int);
    void move(s16, int);
    void lookAtTarget(s16*, cXyz*, cXyz, s16, s16, bool);
    void setParam(s16, s16, s16, s16, s16, s16, s16, s16, s16);

    s16 chkLim(s16, int, int);
    void turn_fromBackbone2Head(s16, s16*, s16*, bool);
    void turn_fromHead2Backbone(s16, s16*, s16*);
    s16 follow_current(s16*, s16);
    void lookAtTarget_2(s16*, cXyz*, cXyz, s16, s16, bool);
};

class dNpc_EventCut_c {
    /* 0x00 */ char* mpEvtStaffName;
    /* 0x04 */ s32 mEvtStaffId;
    /* 0x08 */ fopAc_ac_c* mpActor;
    /* 0x0C */ fopNpc_npc_c* mpTalkActor;
    /* 0x10 */ s32 mCurActIdx;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int mTimer;
    /* 0x1C */ char* mpActorName;
    /* 0x20 */ u32 field_0x20;
    /* 0x24 */ s32 mSetID;
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
    /* 0x68 */ u8* field_0x68;

public:
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
    
    static fopAc_ac_c* findActorCallBack(fopAc_ac_c*, void*);
};

class dNpc_PathRun_c {
public:
    bool setInfDrct(dPath* pPath);
    bool setInf(u8 pathIdx, s8 roomNo, u8 forwards);
    dPath* nextPath(s8 roomNo);
    cXyz getPoint(u8 pointIdx);
    void chkPointPass(cXyz, bool);
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
};

class dNpc_HeadAnm_c {
public:
    void swing_vertical_init(s16 param_1, s16 param_2, s16 param_3, int param_4);
    void swing_vertical();
    void swing_horizone_init(s16 param_1, s16 param_2, s16 param_3, int param_4);
    void swing_horizone();
    void move();

    typedef void (dNpc_HeadAnm_c::*swing_func)(void);

    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ u32 field_0x04;
    /* 0x08 */ swing_func mFunc;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
    /* 0x20 */ s16 field_0x20;
};

enum dNpc_MessageStatus_e {
    dNpcMsgStts_MSG_PREPARING_e = 0x01,
    dNpcMsgStts_BOX_OPENING_e = 0x02,
    dNpcMsgStts_MSG_TYPING_e = 0x06,
    dNpcMsgStts_MSG_DISPLAYED_e = 0x0E,

    dNpcMsgStts_MSG_CONTINUES_e = 0x0F,
    dNpcMsgStts_MSG_ENDS_e = 0x10,

    dNpcMsgStts_BOX_CLOSING_e = 0x11,
    dNpcMsgStts_BOX_CLOSED_e = 0x12,
    dNpcMsgStts_MSG_DESTROYED_e = 0x13,
};

class fopNpc_npc_c : public fopAc_ac_c {
public:
    /* 0x290 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x2C4 */ dNpc_EventCut_c mEventCtrl;
    /* 0x330 */ mDoExt_McaMorf* mpMcaMorf;
    /* 0x334 */ dBgS_ObjAcch mObjAcch;
    /* 0x4F8 */ dBgS_AcchCir mAcchCir;
    /* 0x538 */ dCcD_Stts mStts;
    /* 0x574 */ dCcD_Cyl mCyl;
    /* 0x6A4 */ u32 mCurrMsgID;
    /* 0x6A8 */ u32 mEndMsgID;
    /* 0x6AC */ s32 mCurrMsgBsPcId;
    /* 0x6B0 */ msg_class* mpCurrMsg;
    /* 0x6B4 */ u8 pad_0x6B4[0x6C0 - 0x6B4];

    virtual u32 next_msgStatus(u32*) { return 0x10; }
    virtual u32 getMsg() { return 1; }
    virtual void anmAtr(u16) {}

    void setCollision(float radius, float height);
    u16 talk(int);
};

bool dNpc_setAnmIDRes(mDoExt_McaMorf* pMorf, int loopMode, float morf, float speed, int animResId, int soundResId, const char* arcName);
bool dNpc_setAnmFNDirect(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, char* animFilename, char* soundFilename, const char* arcName);
bool dNpc_setAnm(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileidx, int soundFileIdx, const char* arcName);
void dNpc_setShadowModel(J3DModel*, J3DModelData*, J3DModel*);
cXyz dNpc_playerEyePos(f32);
void dNpc_calc_DisXZ_AngY(cXyz, cXyz, float*, short*);
bool dNpc_chkArasoi();
BOOL dNpc_chkLetterPassed();
bool dNpc_setAnm_2(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileidx, int soundFileIdx, const char* arcName);

#endif /* D_NPC_H */
