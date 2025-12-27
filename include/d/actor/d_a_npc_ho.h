#ifndef D_A_NPC_HO_H
#define D_A_NPC_HO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_npc.h"

class daNpc_Ho_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder() {}
    void SetOrder(unsigned char) {}
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Ho_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void XyCheckCB(int);
    void receivePendant(int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void setAnmStatus();
    void chkAttentionLocal();
    void chkAttention();
    void eventOrder();
    void checkOrder();
    void next_msg_sub0(unsigned long);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void msgPushButton();
    void msgAnm(unsigned char);
    void talkInit();
    void talk();
    void init();
    void setAttention(bool);
    void lookBack();
    void wait01();
    void talk01();
    void talk02();
    void talk03();
    void give01();
    void give02();
    void preach();
    void wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ mDoExt_McaMorf* mpMcaMorf;
    /* 0x29C */ J3DModel* mpJoyPendentModel;
    /* 0x2A0 */ u8 m2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ J3DAnmTexPattern* mpCurrentBtpAnim;
    /* 0x2A8 */ mDoExt_btpAnm mBtpAnimator;
    /* 0x2BC */ u8 mBtpTimer;
    /* 0x2BD */ u8 m2BD[0x2BE - 0x2BD];
    /* 0x2BE */ s16 mTimer1;
    /* 0x2C0 */ dBgS_Acch mAcch;
    /* 0x484 */ dBgS_AcchCir mAcchCir;
    /* 0x4C4 */ dCcD_Stts mStts;
    /* 0x500 */ dCcD_Cyl mCylinderCollision;
    /* 0x630 */ dNpc_JntCtrl_c* mpJointControl;
    /* 0x634 */ u8 m634[0x638 - 0x634];
    /* 0x638 */ u8 mHeadJointIndex;
    /* 0x639 */ u8 mBackboneJointIndex;
    /* 0x63A */ u8 m63A[0x664 - 0x63A];
    /* 0x664 */ cXyz mEyePos;
    /* 0x670 */ cXyz mAttentionBasePos;
    /* 0x67C */ u8 m67C[0x680 - 0x67C];
    /* 0x680 */ f32 mLastMorftime;
    /* 0x684 */ int mCurrentMessageId;
    /* 0x688 */ u8 m688[0x68C - 0x688];
    /* 0x68C */ u8 mCurrentSpeakingAnimIdx;
    /* 0x68D */ u8 m68D[0x690 - 0x68D];
    /* 0x690 */ int mNextMessageId;
    /* 0x694 */ f32 mCylinderCollisionRadius;
    /* 0x698 */ u8 m698[0x6A5 - 0x698];
    /* 0x6A5 */ s8 mCurrentAnimIndex;
    /* 0x6A6 */ u8 m6A6[0x6A7 - 0x6A6];
    /* 0x6A7 */ u8 mCurrentState;
    /* 0x6A8 */ u8 m6A8[0x6AC - 0x6A8];
    /* 0x6AC */ int mCurrentFloorSoundId;
    /* 0x6B0 */ u8 m6B0[0x6B4 - 0x6B0];
};

#endif /* D_A_NPC_HO_H */
