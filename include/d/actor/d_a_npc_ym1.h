#ifndef D_A_NPC_YM1_H
#define D_A_NPC_YM1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Ym1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ym1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    enum BckNum {
        /* 0x00 */ BCKNUM_WAIT01_e,
        /* 0x01 */ BCKNUM_KARI01_e,
        /* 0x02 */ BCKNUM_KARI2WAIT_e,
        /* 0x03 */ BCKNUM_KWAIT_e,
        /* 0x04 */ BCKNUM_KTALK_e,
        /* 0x05 */ BCKNUM_NBTWAIT_e,
        /* 0x06 */ BCKNUM_NBTLOOK_e,
        /* 0x07 */ BCKNUM_NBTTALK_e,
        /* 0x08 */ BCKNUM_KTALK02_e,
        /* 0x09 */ BCKNUM_WAIT02_e,
        /* 0x0A */ BCKNUM_SIT_e,
        /* 0x0B */ BCKNUM_SITTALK_e,
        /* 0x0C */ BCKNUM_TALK01_e,
        /* 0x0D */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_HEAD_e,
        /* 0x01 */ BTPNUM_NULL_e,
    };

    inline daNpc_Ym1_c();

    void setKariFlg();
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_YM1_0();
    bool init_YM1_1();
    bool init_YM2_0();
    bool init_YM2_1();
    bool init_YM2_2();
    bool init_YM2_3();
    bool init_YMx_error();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool init_texPttrnAnm(s8, bool);
    void play_texPttrnAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_YM1_0();
    u32 getMsg_YM1_1();
    u32 getMsg_YM2_0();
    u32 getMsg_YM2_1();
    u32 getMsg_YM2_2();
    u32 getMsg_YM2_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void set_collision_sp();
    void set_cutGrass();
    bool chk_BlackPig();
    bool chk_nbt_attn();
    bool chk_talk();
    bool chk_parts_notMov();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    bool chk_areaIN(f32, cXyz);
    BOOL kari_1();
    BOOL wait_1();
    BOOL wait_2();
    BOOL talk_1();
    BOOL turn_1();
    BOOL NBTwai();
    BOOL SITwai();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    BOOL demo_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL headCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6CF */ s8 m_hnd_R_jnt_num;
    /* 0x6D0 */ J3DModel* mpItemModel;
    /* 0x6D4 */ char mArcName[4];
    /* 0x6D8 */ u32 mShadowID;
    /* 0x6DC */ J3DModel* mpHeadModel;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 mBtpFrame;
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ ProcFunc mCurrProcFunc;
    /* 0x704 */ dCcD_Cyl mAreaCyl;
    /* 0x834 */ cXyz mHomePos;
    /* 0x840 */ csXyz mHomeAngle;
    /* 0x846 */ csXyz mAngle;
    /* 0x84C */ cXyz mTransformedEyePos;
    /* 0x858 */ cXyz mPlayerEyePos;
    /* 0x864 */ cXyz mNbtPos;
    /* 0x870 */ cXyz mHeadPos;
    /* 0x87C */ f32 mPrevMorfFrame;
    /* 0x880 */ s16 mActorAngleY;
    /* 0x882 */ s16 mJointHeadY;
    /* 0x884 */ s16 mJointBackboneY;
    /* 0x886 */ u8 m886[0x888 - 0x886];
    /* 0x888 */ BOOL mbSetEyePos;
    /* 0x88C */ u8 m88C[0x88E - 0x88C];
    /* 0x88E */ s16 mLookTimer;
    /* 0x890 */ s16 mTimer;
    /* 0x892 */ u8 m892[0x896 - 0x892];
    /* 0x896 */ s16 mTargetAngleY;
    /* 0x898 */ s8 mbMorfAnimStopped;
    /* 0x899 */ s8 m899;
    /* 0x89A */ u8 mItemNo;
    /* 0x89B */ bool mbKari;
    /* 0x89C */ bool mbPrevKari;
    /* 0x89D */ bool mbResLoadIsComplete;
    /* 0x89E */ bool m89E;
    /* 0x89F */ bool m89F;
    /* 0x8A0 */ u8 m8A0;
    /* 0x8A1 */ bool mbInitDone;
    /* 0x8A2 */ bool mbAttention;
    /* 0x8A3 */ bool mbTalkReq;
    /* 0x8A4 */ bool m8A4;
    /* 0x8A5 */ bool mbTurnHome;
    /* 0x8A6 */ bool mbDemo;
    /* 0x8A7 */ s8 mActionIndex;
    /* 0x8A8 */ u8 mAnmAtr;
    /* 0x8A9 */ u8 mMesgAnimeTag;
    /* 0x8AA */ s8 mBtpNum;
    /* 0x8AB */ s8 mBckNum;
    /* 0x8AC */ s8 mOrder;
    /* 0x8AD */ s8 mStt;
    /* 0x8AE */ s8 mPrevStt;
    /* 0x8AF */ s8 mLookMode;
    /* 0x8B0 */ s8 mHioType;
    /* 0x8B1 */ s8 mType;
    /* 0x8B2 */ s8 mActionState;
    /* 0x8B3 */ s8 mMsgCount;
};  // Size: 0x8B4

#endif /* D_A_NPC_YM1_H */
