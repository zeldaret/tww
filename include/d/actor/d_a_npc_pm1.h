#ifndef D_A_NPC_PM1_H
#define D_A_NPC_PM1_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daNpc_Pm1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Pm1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 mBckResIndex;
        /* 0x01 */ s8 mResIndex;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };  // Size: 0x10

    s8 getHeadJntNum() { return m_head_jnt_num; }
    s8 getBackboneJntNum()  {return m_backbone_jnt_num; }
    s16 getBackbone_x() { return m_jnt.getBackbone_x(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }
    Vec* getAttPos() { return &mAttPos; }
    Vec* getEyePos() { return &mEyePos; }

    bool createInit();
    void setMtx();
    BOOL anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(s8);
    u8 init_btp(bool, int);
    u8 initTexPatternAnm(bool);
    void playTexPatternAnm();
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16 i_msgStatus);
    void setStt(s8);
    u16 next_msgStatus(u32* pMsgNo);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    bool chkAttention();
    void setAttention();
    bool decideType(int);
    void event_actionInit(int);
    u8 event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    BOOL set_action(ActionFunc, void*);
    BOOL wait01();
    BOOL talk01();
    int wait_action1(void*);
    u8 demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();
public:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_backbone_jnt_num;
    /* 0x6CE */ u8 field_0x6CE[2];
    /* 0x6D0 */ u32 mShadowId;
    /* 0x6D4 */ J3DModel* mpModel;
    /* 0x6D8 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6DC */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F0 */ u8 mBtpFrame;
    /* 0x6F1 */ u8 field_0x6F1;
    /* 0x6F2 */ s16 mTimer;
    /* 0x6F4 */ ActionFunc mCurrActionFunc;
    /* 0x700 */ dNpc_EventCut_c mEventCut;
    /* 0x76C */ csXyz mRot;
    /* 0x772 */ u8 field_0x772[2];
    /* 0x774 */ cXyz mPos;
    /* 0x780 */ cXyz mAttPos;
    /* 0x78C */ cXyz mEyePos;
    /* 0x798 */ cXyz field_0x798;
    /* 0x7A4 */ f32 field_0x7A4;
    /* 0x7A8 */ u8 field_0x7A8[4];
    /* 0x7AC */ f32 field_0x7AC;
    /* 0x7B0 */ s16 field_0x7B0;
    /* 0x7B2 */ s16 field_0x7B2;
    /* 0x7B4 */ s8 field_0x7B4;
    /* 0x7B5 */ s8 field_0x7B5;
    /* 0x7B6 */ u8 field_0x7B6;
    /* 0x7B7 */ u8 mPreItemNo;
    /* 0x7B8 */ u8 field_0x7B8;
    /* 0x7B9 */ u8 field_0x7B9[3];
    /* 0x7BC */ s32 field_0x7BC;
    /* 0x7C0 */ s32 field_0x7C0;
    /* 0x7C4 */ u8 field_0x7C4;
    /* 0x7C5 */ u8 field_0x7C5;
    /* 0x7C6 */ bool mHeadOnlyFollow;
    /* 0x7C7 */ u8 field_0x7C7;
    /* 0x7C8 */ u8 field_0x7C8;
    /* 0x7C9 */ s8 field_0x7C9;
    /* 0x7CA */ u8 field_0x7CA;
    /* 0x7CB */ u8 field_0x7CB;
    /* 0x7CC */ u8 field_0x7CC;
    /* 0x7CD */ s8 mTexPatternNum;
    /* 0x7CE */ s8 mBckResIndex;
    /* 0x7CF */ s8 field_0x7CF;
    /* 0x7D0 */ s8 mStt;
    /* 0x7D1 */ s8 mPrevStt;
    /* 0x7D2 */ s8 field_0x7D2;
    /* 0x7D3 */ s8 mType;
    /* 0x7D4 */ s8 field_0x7D4;
    /* 0x7D5 */ s8 field_0x7D5;
    /* 0x7D6 */ s8 field_0x7D6;
    /* 0x7D7 */ s8 field_0x7D7;
};  // Size: 0x7D8

#endif /* D_A_NPC_PM1_H */
