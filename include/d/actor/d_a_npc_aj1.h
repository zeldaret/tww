#ifndef D_A_NPC_AJ1_H
#define D_A_NPC_AJ1_H

#include "d/d_npc.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class J3DNode;
class JPABaseEmitter;

class daNpc_Aj1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Aj1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    enum BckNum {
        /* 0x00 */ BCKNUM_WAIT01_e,
        /* 0x01 */ BCKNUM_WAIT02_e,
        /* 0x02 */ BCKNUM_ANGRY_e,
        /* 0x03 */ BCKNUM_JAMP_e,
        /* 0x04 */ BCKNUM_SHOCK_e,
        /* 0x05 */ BCKNUM_LOOK_e,
        /* 0x06 */ BCKNUM_TIRE_e,
        /* 0x07 */ BCKNUM_CALL_e,
        /* 0x08 */ BCKNUM_NOBI_e,
        /* 0x09 */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_MABA_e,
        /* 0x01 */ BTPNUM_NULL_e,
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    s16 _XyCheckCB(int);
    bool init_AJ1_0();
    bool init_AJ1_1();
    bool init_AJ1_2();
    bool createInit();
    void play_animation();
    void ctrl_WAITanm();
    void ctrl_TIREanm();
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
    u32 getMsg_AJ1_0();
    u32 getMsg_AJ1_1();
    u32 getMsg_AJ1_2();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_AJ1_TLK();
    bool cut_move_AJ1_TLK();
    void cut_init_INI_ANGRY();
    bool cut_move_INI_ANGRY();
    void cut_init_VIVRATE();
    bool cut_move_VIVRATE();
    void cut_init_JMP();
    bool cut_move_JMP();
    void cut_init_SPPRISE();
    bool cut_move_SPPRISE();
    void cut_init_LOK();
    bool cut_move_LOK();
    void cut_init_DAN();
    bool cut_move_DAN();
    void cut_init_INVIT();
    bool cut_move_INVIT();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    void set_pa_pun();
    void set_pa_aka();
    void set_pa_don();
    void set_pa_smk();
    void flw_pa_pun();
    void flw_pa_aka();
    void del_pa_aka();
    void del_pa(JPABaseEmitter**);
    void setSmoke();
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    bool chk_areaIN(f32, s16, cXyz);
    BOOL FARwai();
    BOOL call_1();
    BOOL wait_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6CF */ s8 m_fot_L_jnt_num;
    /* 0x6D0 */ J3DModel* mpStickModel;
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 mBtpFrame;
    /* 0x6EE */ s16 mBlinkTimer;
    /* 0x6F0 */ ProcFunc mCurrProcFunc;
    /* 0x6FC */ cXyz mHomePos;
    /* 0x708 */ csXyz mHomeAngle;
    /* 0x70E */ csXyz mAngle;
    /* 0x714 */ cXyz mTransformedEyePos;
    /* 0x720 */ cXyz mLookPos;
    /* 0x72C */ cXyz mHeadPos;
    /* 0x738 */ s16 mActorAngleY;
    /* 0x73A */ s16 mJointHeadY;
    /* 0x73C */ s16 mJointBackboneY;
    /* 0x740 */ f32 mPrevMorfFrame;
    /* 0x744 */ s16 mEventIDTbl[1];
    /* 0x746 */ s16 mEventIndex;
    /* 0x748 */ s16 mWaitTimer;
    /* 0x74A */ s16 mPunTimer;
    /* 0x74C */ s16 mCutTimer;
    /* 0x74E */ s16 mTalkTimer;
    /* 0x750 */ s16 mFarTimer;
    /* 0x752 */ u8 m752[0x754 - 0x752];
    /* 0x754 */ s16 mHeadTurnVel;
    /* 0x756 */ s16 mTargetAngleY;
    /* 0x758 */ s8 mbMorfAnimStopped;
    /* 0x759 */ s8 m759;
    /* 0x75A */ u8 mItemNo;
    /* 0x75B */ u8 mSwitchNo;
    /* 0x75C */ u8 mTireTimer;
    /* 0x75D */ u8 m75D;
    /* 0x75E */ bool m75E;
    /* 0x75F */ bool m75F;
    /* 0x760 */ u8 m760;
    /* 0x761 */ bool mbInitDone;
    /* 0x762 */ u8 m762[0x764 - 0x762];
    /* 0x764 */ BOOL mbSetEyePos;
    /* 0x768 */ bool mbAttention;
    /* 0x769 */ bool mbTalkReq;
    /* 0x76A */ bool m76A;
    /* 0x76B */ bool mbDemo;
    /* 0x76C */ dPa_smokeEcallBack mSmokeCb;
    /* 0x78C */ JPABaseEmitter* mpSmkEmitter;
    /* 0x790 */ JPABaseEmitter* mpPunEmitter;
    /* 0x794 */ JPABaseEmitter* mpAkaEmitter;
    /* 0x798 */ JPABaseEmitter* mpDonEmitter;
    /* 0x79C */ cXyz mSmokePos;
    /* 0x7A8 */ cXyz mDonPos;
    /* 0x7B4 */ bool mbDelAka;
    /* 0x7B5 */ s8 mActionIndex;
    /* 0x7B6 */ u8 mAnmAtr;
    /* 0x7B7 */ u8 mMesgAnimeTag;
    /* 0x7B8 */ s8 mBtpNum;
    /* 0x7B9 */ s8 mBckNum;
    /* 0x7BA */ s8 mOrder;
    /* 0x7BB */ s8 mStt;
    /* 0x7BC */ s8 mPrevStt;
    /* 0x7BD */ s8 mLookMode;
    /* 0x7BE */ s8 m7BE;
    /* 0x7BF */ s8 mType;
    /* 0x7C0 */ s8 mActionState;
    /* 0x7C1 */ s8 mMsgCount;
};  // Size: 0x7C4

#endif /* D_A_NPC_AJ1_H */
