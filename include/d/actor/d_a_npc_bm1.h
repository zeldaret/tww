#ifndef D_A_NPC_BM1_H
#define D_A_NPC_BM1_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;

typedef s8 SpecificType;
enum {
    Quill_0,
    Quill_1,
    Quill_2,
    Quill_3,
    Quill_4,
    Akoot,  //0x5
    Skett,  //0x6
    Basht,
    Bisht,
    Hoskit,
    Ilari_0xA,
    Ilari_0xB,
    Ilari_0xC,
    Pashli,
    Namali,
    Kogoli,
    Invalid = 0xFF
};

typedef s8 Type;
enum{
    t_Uninitialized,
    t_Quill,
    t_Akoot,
    t_Skett,
    t_Basht,
    t_Bisht,
    t_Hoskit,
    t_Ilari,
    t_Pashli,
    t_Namali,
    t_Kogoli,
    t_Invalid = 0xFF,
};


class daNpc_Bm1_c : public fopNpc_npc_c {
public:

    struct anm_prm_c{
        s8 mBckResIndex;
        s8 mResIndex;
        f32 mMorf;
        f32 mSpeed;
        s32 mLoopMode;
        BOOL mbHasArms;
    };

    typedef BOOL (daNpc_Bm1_c::*ActionFunc)(void*);

    bool IamKakkuto() {return mSpecificType == Akoot;}
    bool IamSukketo() {return mSpecificType == Skett;}
    void clr_manzai() {mbManzai = false;}
    cXyz& getOdoroki() { return attention_info.position;}
    s8 getStt() { return mStatus;}
    u16 get_oldMsgStat() {
        return mOldMsgStat;
    }
    void setFocus() {m882 = true;}
    void setTelescopeDemo() {m881 = true;}
    void set_manzai() {mbManzai = true;}


    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeBm1Control(J3DNode*, J3DModel*);
    bool chk_appCnd();
    bool init_PST_0();
    bool init_PST_1();
    bool init_PST_2();
    bool init_PST_3();
    bool init_PST_4();
    bool init_BMB_0();
    bool init_BMB_1();
    bool init_BMB_2();
    bool init_BMC_0();
    bool init_BMC_1();
    bool init_BMC_2();
    bool init_BMC_3();
    bool init_BMD_0();
    bool init_BMD_1();
    bool init_SKT_0();
    bool init_KKT_0();
    bool createInit();
    void setMtx(bool);
    char* anmNum_toResID(int);
    char* headAnmNum_toResID(int);
    char* wingAnmNum_toResID(int);
    char* btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    bool setAnm();
    void setPlaySpd(float);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    u8 chk_manzai();
    bool chk_talk();
    bool chk_partsNotMove();
    BOOL lookBack();
    u16 next_msgStatus(unsigned long*);
    s8 getBitMask();
    u32 getMsg_PST_1();
    u32 getMsg_PST_3();
    u32 getMsg_SKT_0();
    u32 getMsg_KKT_0();
    u32 getMsg_BMB_0();
    u32 getMsg_BMB_1();
    u32 getMsg_BMB_2();
    u32 getMsg_BMC_0();
    u32 getMsg_BMC_2();
    u32 getMsg_BMC_3();
    u32 getMsg_BMD_0();
    u32 getMsg_BMD_1();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    u32 bm_movPass(bool);
    void bm_setFlyAnm();
    void bm_clcFlySpd();
    void bm_clcMovSpd();
    bool bm_flyMove();
    void bm_nMove();
    void setPrtcl_Flyaway();
    void delPrtcl_Flyaway();
    void setPrtcl_Land0();
    void delPrtcl_Land0();
    void setPrtcl_Hane0();
    void flwPrtcl_Hane0();
    void delPrtcl_Hane0();
    void setPrtcl_Hane1();
    void flwPrtcl_Hane1();
    void delPrtcl_Hane1();
    bool decideType(int, int);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, short);
    void eInit_setEvTimer(int*);
    cXyz eInit_calcRelativPos(cXyz*, int*);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_SET_PLYER_GOL_(int*, cXyz*, int*);
    float eInit_prmFloat(float*, float);
    void eInit_FLY_(int*, float*, float*, float*, float*);
    void eInit_DEL_ACTOR_();
    void eInit_WLK_(int*, float*, float*, cXyz*, int*, int*, int*);
    void eInit_INI_EVN_1_();
    void eInit_SET_NXT_PTH_INF_();
    void eInit_SET_ANM_(int*);
    void eInit_MOV_PTH_POINT_(int*, int*, int*, int*);
    void event_actionInit(int);
    bool eMove_ATTENTION_();
    bool eMove_KMA_FLY_();
    bool eMove_FLY_();
    bool eMove_WLK_();
    bool event_action();
    void cut_init_360_TRN(int);
    bool cut_move_360_TRN();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(int (daNpc_Bm1_c::*)(void*), void*);
    BOOL chk_action(int (daNpc_Bm1_c::*)(void*)); //Unused
    void setStt(signed char);
    BOOL d_wait();
    BOOL lookup();
    BOOL orooro();
    BOOL wait_1();
    BOOL talk_1();
    BOOL talk_2();
    BOOL manzai();
    BOOL wait_4();
    BOOL flyawy();
    BOOL wait_5();
    BOOL wait_6();  //Unused
    BOOL h_wait();
    BOOL wait_7();
    BOOL wait_3();
    BOOL wait_8();
    BOOL wait_2();
    BOOL walk_1();
    BOOL CHKwai();
    BOOL demo_action1(void*);
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    BOOL wait_action5(void*);
    BOOL wait_action6(void*);
    BOOL wait_action7(void*);
    BOOL wait_action8(void*);
    BOOL wait_action9(void*);
    BOOL wait_actionA(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_hed_Anm();
    J3DModelData* create_wng_Anm();
    J3DModelData* create_arm_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ char mArcName[4];
    /* 0x6D0 */ s8 m_hed_jnt_num;
    /* 0x6D1 */ s8 m_bbone_jnt_num;
    /* 0x6D2 */ s8 m_nec_jnt_num;
    /* 0x6D3 */ s8 m_arm_L_jnt_num;
    /* 0x6D4 */ s8 m_arm_R_jnt_num;
                J3DModel* mpBinderModel;
                J3DModel* mpBagModel;
                J3DModel* mpKnifeModel;
                J3DModel* mpStickModel;
    /* 0x6E8 */ u32 mShadowID;
    /* 0x6EC */ mDoExt_McaMorf* mpHeadMorf;
    /* 0x6F0 */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6F4 */ mDoExt_btpAnm mHeadBtpAnm;
    /* 0x708 */ u8 mBlinkFrame;
                // u8 pad709;
                s16 mBlinkTimer;
                s16 pad70C;
    /* 0x710 */ mDoExt_McaMorf* mpWingMorf;
                s8 m_wngL1_jnt_num;
                s8 m_wngR1_jnt_num;
                s8 m_wngL3_jnt_num;
                s8 m_wngR3_jnt_num;
    /* 0x718 */ u8 pad718[0x71C - 0x718];   //Possibly an unused mDoExt_McaMorf* ?
    /* 0x71C */ mDoExt_McaMorf* mpArmMorf;
    /* 0x720 */ s8 m_armL1_jnt_num;
    /* 0x721 */ s8 m_armR1_jnt_num;
    /* 0x722 */ s8 m_armL2_jnt_num;
    /* 0x722 */ s8 m_armR2_jnt_num;
    /* 0x723 */ s8 m_hnd_R_jnt_num;
    /* 0x724 */ ActionFunc mCurrActionFunc;
    /* 0x734 */ Mtx mLeftArmMtx;
    /* 0x764 */ Mtx mRightArmMtx;
    /* 0x794 */ dNpc_PathRun_c mPathRun;
                dNpc_EventCut_c mEventCut;
                fpc_ProcID mPartnerProcID;
    /* 0x80C */ cXyz m80C;
    /* 0x818 */ csXyz m818;
    /* 0x81E */ u8 m81E[0x820 - 0x81E];
    /* 0x820 */ cXyz mEyePos;
                cXyz mAttentionPos;
    /* 0x838 */ cXyz mTargetPos;
                f32 mFrame;
    /* 0x844 */ f32 mTargetFlySpeed;
                f32 mFlySpeedY;
                f32 mTargetFlyStep;
                f32 mFlyAccelY;
                f32 m858;
                s16 m85C;
                s16 m85E;
                s16 m860;
                s16 m862[4];
                s16 m86A;
                s16 m86C;
    /* 0x86E */ s16 m86E;
    /* 0x870 */ s16 m870;
    /* 0x872 */ s16 m872;
    /* 0x874 */ s16 mHeadLookAtMaxVel;
    /* 0x876 */ s16 m876;
    /* 0x878 */ u16 mOldMsgStat;
                s8 mbMorfAnimStopped;
                s8 m87B;
                s8 m87C;
                u8 m87D;
                u8 m87E;
    /* 0x87F */ bool m87F;

    /* 0x880 */ bool m880;
    /* 0x881 */ bool m881;
    /* 0x882 */ u8 m882;
                bool mbManzai;
    /* 0x884 */ bool mbInitPostman0;
                bool mbHasArms;
                bool mbSetShapeAngle;
    /* 0x887 */ u8 m887;
    /* 0x888 */ u8 m888;
                bool m889;
                bool m88A;
                u8 m88B;
                bool mbRanExecute;
                u8 m88D;
                u8 m88E;
                u8 m88F;                
    /* 0x890 */ s32 mbSetEyePos;
    /* 0x894 */ bool mbAttention;
    /* 0x895 */ bool m895;
    /* 0x896 */ bool m896;
    /* 0x897 */ bool mbInDemo;
    /* 0x898 */ cXyz mWingLPos;
    /* 0x8A4 */ cXyz mWingRPos;
    /* 0x8B0 */ cXyz mArmLPos;
    /* 0x8BC */ cXyz mArmRPos;
    /* 0x8C8 */ u8 m8C8;
    /* 0x8C9 */ u8 m8C9[0x8CC - 0x8C9];
    /* 0x8CC */ u8 m8CC;
    /* 0x8CD */ u8 m8CD[0x8D4 - 0x8CD];
    /* 0x8D4 */ JPABaseEmitter* mpFlyawayEmitterL;
    /* 0x8D8 */ JPABaseEmitter* mpFlyawayEmitterR;
    /* 0x8DC */ JPABaseEmitter* mpLandEmitterL;
    /* 0x8E0 */ JPABaseEmitter* mpLandEmitterR;
    /* 0x8E4 */ JPABaseEmitter* mpFeatherEmitterL;
    /* 0x8E8 */ JPABaseEmitter* mpFeatherEmitterR;
    /* 0x8EC */ JPABaseEmitter* mpFeather1EmitterL;
    /* 0x8F0 */ JPABaseEmitter* mpFeather1EmitterR;
#if VERSION == VERSION_DEMO
    /* 0x900 */ u32 mDemoOnly;  //Possibly an unused emitter
#endif
    /* 0x8F4 */ s8 m8F4;
    /* 0x8F5 */ s8 m8F5;
    /* 0x8F6 */ s8 mActNo;
    /* 0x8F7 */ u8 m8F7;
    /* 0x8F8 */ u8 m8F8;
    /* 0x8F9 */ s8 m8F9;
    /* 0x8FA */ s8 mBckResIndex;
    /* 0x8FB */ u8 m8FB[0x8FD - 0x8FB];
    /* 0x8FD */ s8 m8FD;
    /* 0x8FE */ s8 mStatus;
    /* 0x8FF */ s8 m8FF;

    /* 0x900 */ s8 mLookBackState;
    /* 0x901 */ s8 mType;
    /* 0x902 */ SpecificType mSpecificType;
    /* 0x903 */ s8 mSpawnCondition;
    /* 0x904 */ s8 m904;
    /* 0x904 */ s8 m905;   


}; 
STATIC_ASSERT(sizeof(daNpc_Bm1_c) == DEMO_SELECT(0x90C,0x908));


struct hio_prm_c{
    s16 mMaxHeadX;
    s16 mMaxHeadY;
    s16 mMinHeadX;
    s16 mMinHeadY;
    s16 mMaxBackboneX;
    s16 mMaxBackboneY;
    s16 mMinBackboneX;
    s16 mMinBackboneY;
    s16 mMaxTurnStep;
    s16 mCalcAngleTarget;
    f32 mAttPosOffsetY;
    u8 m18;
    s16 mFlyScale;
    s16 mFlyMaxStep;
    s16 m1E;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    s16 m34;
    s16 m36;
    f32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
    f32 m48;
};


#endif /* D_A_NPC_BM1_H */
