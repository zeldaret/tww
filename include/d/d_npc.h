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
    /* 0x0A */ bool field_0x0B;
    /* 0x0B */ u8 field_0x0C;
    /* 0x0C */ u8 field_0x0D;
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
    void angCalcS(short*, short, short, short);
    void limitter(short*, short, short);
    void follow(short*, short, short, int);
    void move(short, int);
    void lookAtTarget(short*, cXyz*, cXyz, short, short, bool);
    void setParam(short, short, short, short, short, short, short, short, short);

    void chkLim(short, int, int);
    void turn_fromBackbone2Head(short, short*, short*, bool);
    void turn_fromHead2Backbone(short, short*, short*);
    void follow_current(short*, short);
    void lookAtTarget_2(short*, cXyz*, cXyz, short, short, bool);
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
    void setInfDrct(dPath*);
    void setInf(unsigned char, signed char, unsigned char);
    void nextPath(signed char);
    void getPoint(unsigned char);
    void chkPointPass(cXyz, bool);
    void incIdx();
    void incIdxLoop();
    void incIdxAuto();
    void decIdx();
    void decIdxLoop();
    void decIdxAuto();
    void nextIdx();
    void nextIdxAuto();
    void absIdx(unsigned char, unsigned char);
    void maxPoint();
    void pointArg(unsigned char);
    void setNearPathIndx(cXyz*, float);
    void setNearPathIndxMk(cXyz*);
    void setNearPathIndxMk2(cXyz*, unsigned char, unsigned char);
    void chkInside(cXyz*);
};

class dNpc_HeadAnm_c {
public:
    void swing_vertical_init(short, short, short, int);
    void swing_vertical();
    void swing_horizone_init(short, short, short, int);
    void swing_horizone();
    void move();
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

void dNpc_setAnmIDRes(mDoExt_McaMorf*, int, float, float, int, int, const char*);
void dNpc_setAnmFNDirect(mDoExt_McaMorf*, int, float, float, char*, char*, const char*);
void dNpc_setAnm(mDoExt_McaMorf*, int, float, float, int, int, const char*);
void dNpc_setShadowModel(J3DModel*, J3DModelData*, J3DModel*);
cXyz dNpc_playerEyePos(f32);
void dNpc_calc_DisXZ_AngY(cXyz, cXyz, float*, short*);
void dNpc_chkArasoi();
bool dNpc_chkLetterPassed();
void dNpc_setAnm_2(mDoExt_McaMorf*, int, float, float, int, int, const char*);

#endif /* D_NPC_H */
