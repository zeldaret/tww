#ifndef D_A_NPC_BJ1_H
#define D_A_NPC_BJ1_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;

class daNpc_Bj1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x00 */ s8 anmNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    }; // Size: 0x10

    struct bj1_prm_c {
        /* 0x00 */ Vec head_scale;
        /* 0x0C */ Vec backbone_scale;
        /* 0x18 */ Vec eye_offset;
    }; // Size: 0x24

    typedef BOOL (daNpc_Bj1_c::*ActionFunc)(void*);

    void nodeBj1Control(J3DNode*, J3DModel*);
    void nodePrpControl(J3DNode*, J3DModel*);
    bool init_BJ4_0();
    bool init_BJ6_0();
    bool init_BJ7_0();
    bool init_BJX_0();
    bool init_BJX_1();
    bool createInit();
    void setMtx_anmProc();
    void setMtx(bool);
    u32 anmNum_toResID(int);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    BOOL setAnm();
    void setAnm_prp(s8);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_drct(f32);
    bool chk_partsNotMove();
    void lookBack();
    bool getMaskInf(u8*);
    bool chkReg(u16);
    void setReg(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_BJ1_0();
    u32 getMsg_BJ2_0();
    u32 getMsg_BJ3_0();
    u32 getMsg_BJ4_0();
    u32 getMsg_BJ5_0();
    u32 getMsg_BJ6_0();
    u32 getMsg_BJ7_0();
    u32 getMsg_BJ8_0();
    u32 getMsg_BJ9_0();
    u32 getMsg_Corog();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(fpcLyIt_JudgeFunc);
    void partner_srch();
    void setCollision_SP_();
    void set_pthPoint(u8);
    void bj_clcFlySpd();
    u32 bj_movPass(bool);
    bool bj_flyMove();
    void bj_clcMovSpd();
    void bj_nMove();
    void setPrtcl_drugPot_1();
    void setPrtcl_drugPot_2();
    void delPrtcl_drugPot();
    void setPrtcl_danceLR();
    void flwPrtcl_danceLR();
    void delPrtcl_danceLR();
    void setPrtcl_peraProOpen();
    BOOL createSeed();
    BOOL deleteSeed();
    bool charDecide(BOOL);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, s16);
    void eInit_setEvTimer(int*);
    cXyz eInit_calcRelativPos(cXyz*, int*);
    f32 eInit_prmFloat(f32*, f32);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_PLYER_MOV_1_();
    BOOL eInit_MOV_(f32*, f32*, f32*, int*);
    void eInit_JMP_(f32*, f32*);
    void eInit_CHG_PTH_(int*, int*);
    void eInit_END_MOV_();
    void eInit_SET_TNE_();
    void eInit_DEL_TNE_();
    void eInit_SET_ANM_(int*, f32*);
    void event_actionInit(int);
    bool eMove_ATTENTION_();
    bool eMove_MOV_();
    bool eMove_JMP_();
    bool eMove_SET_TNE_();
    bool eMove_PTH_MOV_();
    bool event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL wait_4();
    BOOL flyMov();
    BOOL fall01();
    BOOL talk_1();
    BOOL walk_1();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_prp_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_backbone_jnt_num;
    /* 0x6CE */ s8 m_armL_jnt_num;
    /* 0x6CF */ s8 m_armR_jnt_num;
    /* 0x6D0 */ J3DModel* mpFaceModel;
    /* 0x6D4 */ J3DModel* mpArmLModel;
    /* 0x6D8 */ J3DModel* mpArmRModel;
    /* 0x6DC */ s8 field_0x6DC;
    /* 0x6DD */ s8 field_0x6DD;
    /* 0x6DE */ u8 padding_0x6DE[0x6E0 - 0x6DE];
    /* 0x6E0 */ u32 mShadowId;
    /* 0x6E4 */ mDoExt_McaMorf* mpPrpMorf;
    /* 0x6E8 */ s8 m_prp_jnt_num;
    /* 0x6E9 */ s8 field_0x6E9;
    /* 0x6EA */ u8 padding_0x6EA[0x6F0 - 0x6EA];
    /* 0x6F0 */ s16 field_0x6F0;
    /* 0x6F2 */ s16 mPrpSpin;
    /* 0x6F4 */ u8 padding_0x6F4[0x6F8 - 0x6F4];
    /* 0x6F8 */ ActionFunc mCurrActionFunc;
    /* 0x704 */ Mtx mHandMtx;
    /* 0x734 */ dNpc_PathRun_c mPathRun;
    /* 0x73C */ dNpc_EventCut_c mEventCut;
    /* 0x7A8 */ u32 mPartnerProcID;
    /* 0x7AC */ cXyz mInitialPos;
    /* 0x7B8 */ csXyz mInitialAngle;
    /* 0x7BE */ u8 padding_0x7BE[0x7C0 - 0x7BE];
    /* 0x7C0 */ cXyz mEyePos;
    /* 0x7CC */ cXyz field_0x7CC;
    /* 0x7D8 */ cXyz mTargetPos;
    /* 0x7E4 */ cXyz mEyeOffset;
    /* 0x7F0 */ cXyz mHeadScale;
    /* 0x7FC */ cXyz mBackboneScale;
    /* 0x808 */ f32 mFrame;
    /* 0x80C */ f32 mTargetFlySpeed;
    /* 0x810 */ u8 padding_0x810[0x814 - 0x810];
    /* 0x814 */ f32 mTargetFlyStep;
    /* 0x818 */ u8 padding_0x818[0x81C - 0x818];
    /* 0x81C */ f32 mArrivalDist;
    /* 0x820 */ s16 field_0x820;
    /* 0x822 */ s16 field_0x822;
    /* 0x824 */ s16 field_0x824;
    /* 0x826 */ s16 field_0x826[3];
    /* 0x82C */ s16 field_0x82C;
    /* 0x82E */ s16 mFlyDelayTimer;
    /* 0x830 */ s16 mEvTimer;
    /* 0x832 */ s16 mAttTimer;
    /* 0x834 */ s16 mFlyWaitTimer;
    /* 0x836 */ u8 padding_0x836[0x838 - 0x836];
    /* 0x838 */ s16 mHeadLookAtMaxVel;
    /* 0x83A */ s16 mLookTargetAngleY;
    /* 0x83C */ s8 mbMorfAnimStopped;
    /* 0x83D */ u8 field_0x83D;
    /* 0x83E */ u8 field_0x83E;
    /* 0x83F */ u8 mPathIdx;
    /* 0x840 */ u8 field_0x840;
    /* 0x841 */ u8 field_0x841;
    /* 0x842 */ u8 field_0x842;
    /* 0x843 */ u8 field_0x843;
    /* 0x844 */ u8 field_0x844;
    /* 0x845 */ u8 field_0x845;
    /* 0x846 */ bool field_0x846;
    /* 0x847 */ u8 field_0x847;
    /* 0x848 */ u8 mbAscending;
    /* 0x849 */ bool mbFlyMoveEnd;
    /* 0x84A */ bool mbMoveEnd;
    /* 0x84B */ bool field_0x84B;
    /* 0x84C */ u8 mpDrawPrp;
    /* 0x84D */ u8 mbSetPeraPrtcl;
    /* 0x84E */ u8 field_0x84E;
    /* 0x84F */ u8 padding_0x84F[0x850 - 0x84F];
    /* 0x850 */ BOOL mbSetEyePos;
    /* 0x854 */ u8 mbAttention;
    /* 0x855 */ u8 field_0x855;
    /* 0x856 */ bool mHeadOnlyFollow;
    /* 0x857 */ bool mbInDemo;
    /* 0x858 */ csXyz mDrugPotAngle;
    /* 0x85E */ u8 padding_0x85E[0x860 - 0x85E];
    /* 0x860 */ cXyz mDrugPotPos;
    /* 0x86C */ cXyz mPeraProPos;
    /* 0x878 */ JPABaseEmitter* mpPeraProEmitter;
    /* 0x87C */ JPABaseEmitter* mpDrugPotEmitter0;
    /* 0x880 */ JPABaseEmitter* mpDrugPotEmitter1;
    /* 0x884 */ JPABaseEmitter* mpDrugPotEmitter2;
    /* 0x888 */ JPABaseEmitter* mpDrugPotEmitter3;
    /* 0x88C */ JPABaseEmitter* mpDanceEmitterL;
    /* 0x890 */ JPABaseEmitter* mpDanceEmitterR;
    /* 0x894 */ s16 mDrugPotTimer;
    /* 0x896 */ u8 padding_0x896[0x898 - 0x896];
    /* 0x898 */ fpc_ProcID mSeedProcID[4];
    /* 0x8A8 */ s8 mFlyMode;
    /* 0x8A9 */ s8 mJumpMode;
    /* 0x8AA */ s8 mMoveMode;
    /* 0x8AB */ s8 mActionIndex;
    /* 0x8AC */ s8 field_0x8AC;
    /* 0x8AD */ u8 field_0x8AD;
    /* 0x8AE */ u8 field_0x8AE;
    /* 0x8AF */ s8 mAnmNum;
    /* 0x8B0 */ s8 field_0x8B0;
    /* 0x8B1 */ s8 mStatus;
    /* 0x8B2 */ s8 mPrevStatus;
    /* 0x8B3 */ s8 mLookBackState;
    /* 0x8B4 */ s8 mType;
    /* 0x8B5 */ s8 mSpecificType;
    /* 0x8B6 */ s8 field_0x8B6;
    /* 0x8B7 */ s8 field_0x8B7;
}; // size 0x8B8;

class daNpc_Bj1_childHIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ u8 field_0x00[0x12];
        /* 0x12 */ s16 mCalcAngleTarget;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u8 field_0x18;
        /* 0x19 */ u8 field_0x19[0x20 - 0x19];
        /* 0x20 */ s16 field_0x20;
        /* 0x22 */ s16 mFlyScale;
        /* 0x24 */ s16 mFlyMaxStep;
        /* 0x26 */ u8 field_0x26[0x28 - 0x26];
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ f32 field_0x38;
        /* 0x3C */ f32 field_0x3C;
        /* 0x40 */ s16 field_0x40;
        /* 0x42 */ s16 field_0x42;
        /* 0x44 */ u8 field_0x44[0x46 - 0x44];
        /* 0x46 */ s16 field_0x46;
        /* 0x48 */ f32 field_0x48;
        /* 0x4C */ s16 field_0x4C;
        /* 0x4E */ s16 field_0x4E;
        /* 0x50 */ s16 field_0x50;
        /* 0x52 */ u8 field_0x52[0x54 - 0x52];
        /* 0x54 */ f32 field_0x54;
        /* 0x58 */ f32 field_0x58;
        /* 0x5C */ f32 field_0x5C;
        /* 0x60 */ f32 field_0x60;
    }; // Size: 0x64

    daNpc_Bj1_childHIO_c();
    void genMessage(JORMContext* ctx) {
        UNUSED(ctx);
    };

    /* 0x04 */ hio_prm_c hio_prm;
    /* 0x68 */ u32 field_0x68;
}; // Size: 0x6C

class daNpc_Bj1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Bj1_HIO_c();
    virtual ~daNpc_Bj1_HIO_c() {
    }
    void genMessage(JORMContext* ctx) {
        UNUSED(ctx);
    }

    /* 0x04 */ s8 field_0x04;
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ daNpc_Bj1_childHIO_c children[9];
}; // Size: 0x3D8

#endif /* D_A_NPC_BJ1_H */
