#ifndef D_A_NPC_CO1_H
#define D_A_NPC_CO1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Co1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Co1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 mBckResIndex;
        /* 0x01 */ s8 mResIndex;
        /* 0x02 */ s8 field_0x02;
        /* 0x03 */ s8 field_0x03;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    }; // Size: 0x10

    void nodeCo1Control(J3DNode*, J3DModel*);
    BOOL init_CO1_0();
    BOOL createInit();
    void setMtx(bool);
    s32 anmNum_toResID(int);
    s32 anmNum_toResID_prl(int);
    s32 btpNum_toResID(int);
    BOOL setBtp(bool, int);
    BOOL setBtk(bool);
    BOOL iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    BOOL setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void setCollision_SP_();
    void set_target(int);
    u8 chk_talk();
    BOOL chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_CO1_0();
    u32 getMsg();
    BOOL chkAttention();
    void setAttention(bool);
    BOOL charDecide(int);
    void eInit_MDR_();
    void eInit_RED_LTR_();
    void event_actionInit(int);
    BOOL eMove_MDR_();
    BOOL eMove_RED_LTR_();
    BOOL event_action();
    void privateCut(int);
    void endEvent();
    s32 isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(signed char);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wakeup();
    BOOL talk_1();
    BOOL toru_1();
    BOOL read_1();
    BOOL modoru();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_prl_Anm();
    BOOL create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_R_jnt_num;
    /* 0x6CF */ u8 field_0x6CF;
    /* 0x6D0 */ mDoExt_McaMorf* mpPrlMorf;
    /* 0x6D4 */ J3DAnmTextureSRTKey* m_prl_btk;
    /* 0x6D8 */ s8 m_prl_jnt_num;
    /* 0x6D9 */ u8 field_0x6D9[0x6DC - 0x6D9];
    /* 0x6DC */ mDoExt_btkAnm mBtkAnm;
    /* 0x6F0 */ u8 mBtkFrame;
    /* 0x6F1 */ u8 field_0x6F1[0x6F4 - 0x6F1];
    /* 0x6F4 */ J3DModel* mpItmModel;
    /* 0x6F8 */ u32 mShadowIdx;
    /* 0x6FC */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x700 */ mDoExt_btpAnm mBtpAnm;
    /* 0x714 */ u8 mBtpFrame;
    /* 0x715 */ u8 field_0x715;
    /* 0x716 */ s16 mBtpTimer;
    /* 0x718 */ ActionFunc mCurrActionFunc;
    /* 0x724 */ u8 field_0x724[8];
    /* 0x72C */ dNpc_EventCut_c mDemoEventCut;
    /* 0x798 */ u8 field_0x798[4];
    /* 0x79C */ cXyz mBkPos;
    /* 0x7A8 */ s16 mBkAngleX;
    /* 0x7AA */ s16 mBkAngleY;
    /* 0x7AC */ s16 mBkAngleZ;
    /* 0x7B0 */ cXyz mHeadPos;
    /* 0x7BC */ cXyz mEventPos;
    /* 0x7C8 */ u8 field_0x7C8[0x7D4 - 0x7C8];
    /* 0x7D4 */ f32 mPrevMorfFrame;
    /* 0x7D8 */ u8 field_0x7D8[0x7EC - 0x7D8];
    /* 0x7EC */ s16 mPrevJntHeadX;
    /* 0x7EE */ s16 mPrevJntBackboneX;
    /* 0x7F0 */ s16 mPrevAngleY;
    /* 0x7F2 */ s16 mEventIdx[3];
    /* 0x7F8 */ s16 mEvtIdxSel;
    /* 0x7FA */ u8 field_0x7FA[0x7FC - 0x7FA];
    /* 0x7FC */ s16 mTimer;
    /* 0x7FE */ u8 field_0x7FE[0x802 - 0x7FE];
    /* 0x802 */ s16 mHeadAngle;
    /* 0x804 */ s16 mDesiredYRot;
    /* 0x806 */ u8 field_0x806[0x808 - 0x806];
    /* 0x808 */ s8 mMorfEnd;
    /* 0x809 */ s8 mAnmLoaded;
    /* 0x80A */ s8 mHasLetter;
    /* 0x80B */ u8 mGetItem;
    /* 0x80C */ u8 field_0x80C;
    /* 0x80D */ u8 mInitFlags;
    /* 0x80E */ u8 field_0x80E;
    /* 0x80F */ u8 mNoPosMove;
    /* 0x810 */ u8 mLookFlags;
    /* 0x811 */ u8 mDemoFlags;
    /* 0x812 */ u8 field_0x812;
    /* 0x813 */ bool mDrawHandR;
    /* 0x814 */ u8 mInitStep2;
    /* 0x815 */ u8 mExecStarted;
    /* 0x816 */ u8 field_0x816[0x818 - 0x816];
    /* 0x818 */ fopAc_ac_c* mpAttnActor;
    /* 0x81C */ u8 mAttnFlag;
    /* 0x81D */ bool mHide;
    /* 0x81E */ bool mInitDone;
    /* 0x81F */ bool mDemo;
    /* 0x820 */ cXyz mPrevPos;
    /* 0x82C */ s16 mPrevPos2[3];
    /* 0x832 */ u8 field_0x832[2];
    /* 0x834 */ f32 mFloatVal;
    /* 0x838 */ u8 field_0x838[0x840 - 0x838];
    /* 0x840 */ cXyz mCurPos;
    /* 0x84C */ f32 field_0x84C;
    /* 0x850 */ s16 mSinAngle;
    /* 0x852 */ u8 field_0x852[0x854 - 0x852];
    /* 0x854 */ s8 mCurActIdx;
    /* 0x855 */ s8 mEventActNo;
    /* 0x856 */ u8 mCurrAnmAtr;
    /* 0x857 */ s8 mCurrAnmTag;
    /* 0x858 */ s8 mTexPatternNum;
    /* 0x859 */ s8 mCurrAnmNum;
    /* 0x85A */ u8 field_0x85A[0x85C - 0x85A];
    /* 0x85C */ s8 mEventState;
    /* 0x85D */ s8 mAnmTagIndex;
    /* 0x85E */ s8 mNextAnmNum;
    /* 0x85F */ s8 mActionIndex;
    /* 0x860 */ s8 mType;
    /* 0x861 */ s8 mInitStep;
    /* 0x862 */ s8 mActionState;
    /* 0x863 */ s8 field_0x863;
}; // Size: 0x864

class daNpc_Co1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Co1_HIO_c();
    virtual ~daNpc_Co1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ s32 mNo2;

    struct {
        /* 0x0C */ s16 mMaxHeadX;
        /* 0x0E */ s16 mMaxHeadY;
        /* 0x10 */ s16 mMinHeadX;
        /* 0x12 */ s16 mMinHeadY;
        /* 0x14 */ s16 mMaxBackboneX;
        /* 0x16 */ s16 mMaxBackboneY;
        /* 0x18 */ s16 mMinBackboneX;
        /* 0x1A */ s16 mMinBackboneY;
        /* 0x1C */ s16 mMaxTurnStep;
        /* 0x1E */ s16 mMaxTurnVel;
        /* 0x20 */ f32 mAttnYOff;
        /* 0x24 */ s16 mAttnAngleY;
        /* 0x26 */ s16 mPrm26;
        /* 0x28 */ s16 mPrm28;
        /* 0x2A */ s16 mPrm2A;
        /* 0x2C */ f32 mPrm2C;
        /* 0x30 */ f32 mPrm30;
        /* 0x34 */ s16 mPrm34;
        /* 0x36 */ s16 mAlpha;
    } mNpc;
};

#endif /* D_A_NPC_CO1_H */
