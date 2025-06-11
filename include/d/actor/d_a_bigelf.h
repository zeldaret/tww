#ifndef D_A_BIGELF_H
#define D_A_BIGELF_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daBigelf_c : public fopAc_ac_c {
public:
    typedef BOOL (daBigelf_c::*ActionFunc)(void*);

    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void incAttnSetCount() {}
    void setAction(ActionFunc, void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void oct_delete();
    void nodeCallBack(J3DNode*);
    void lightInit(cXyz*);
    void lightEnd();
    void lightProc();
    void darkInit();
    void darkEnd();
    void darkProc();
    void demoInitFlDelete();
    void demoProcFlDelete();
    void demoInitFlLink();
    void demoProcFlLink();
    void demoInitFlDmAf();
    void demoProcFlDmAf();
    void demoInitFlDmMd();
    void demoProcFlDmMd();
    void demoInitFlDmBf();
    void demoProcFlDmBf();
    void demoInitFlDemo();
    void demoProcFlDemo();
    void demoInitExit();
    void demoProcExit();
    void demoInitTalk();
    void demoProcTalk();
    void demoInitAppear();
    void demoProcAppear();
    void demoInitFa1();
    void demoProcFa1();
    void demoInitWait();
    void demoProcWait();
    void demoInitCom();
    void demoProcCom();
    void getNowEventAction();
    void demoProc();
    void getType();
    void getSwbit();
    void getSwbit2();
    void getEventFlag();
    void makeFa1S();
    void makeFa1();
    void setAnm(signed char);
    void setAnmStatus();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void msgPushButton();
    void msgAnm(unsigned char);
    void talkInit();
    void talk();
    void init();
    void setAttention(bool);
    void lookBack();
    void hunt();
    void oct_search();
    void oct();
    void ready0();
    void event0();
    void dead();
    void wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhaseProcReq;
    /* 0x298 */ mDoExt_McaMorf* mpBckAnimator;
    /* 0x29C */ mDoExt_brkAnm mBrkAnimator;
    /* 0x2B4 */ mDoExt_btkAnm mBtkAnimator;
    /* 0x2C8 */ J3DModel* mpFlowerModel;
    /* 0x2CC */ mDoExt_brkAnm mFlowerBrkAnimator;
    /* 0x2E4 */ s8 mHandRBJointIndex;
    /* 0x2E5 */ u8 m2E5[0x2F0 - 0x2E5];
    /* 0x2F0 */ s8 mHeadJointIndex;
    /* 0x2F1 */ s8 mBackboneJointIndex;
    /* 0x2F2 */ u8 m2F2[0x31C - 0x2F2];
    /* 0x31C */ cXyz mUnkPos;
    /* 0x328 */ cXyz mCurrentPos;
    /* 0x334 */ u8 m334[0x340 - 0x334];
    /* 0x340 */ u16 mStateBits;
    /* 0x342 */ u8 m342[0x346 - 0x342];
    /* 0x346 */ u8 mGivenItem;
    /* 0x347 */ u8 m347[0x348 - 0x347];
    /* 0x348 */ int mCurrentMessageId;
    /* 0x34C */ void* mpFairyActor;
    /* 0x350 */ u8 m350[0x352 - 0x350];
    /* 0x352 */ bool mIsLightShining;
    /* 0x353 */ u8 m353[0x354 - 0x353];
    /* 0x354 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x374 */ cXyz mLightInfluencePos;
    /* 0x380 */ GXColorS10 mLightInfluenceColor;
    /* 0x388 */ f32 mLightInfluencePower;
    /* 0x38C */ f32 mLightInfluenceFluctuation;
    /* 0x390 */ u8 m390[0x3A0 - 0x390];
    /* 0x3A0 */ f32 m3A0;
    /* 0x3A4 */ f32 m3A4;
    /* 0x3A8 */ f32 m3A8;
    /* 0x3AC */ u8 m3AC[0x3B0 - 0x3AC];
    /* 0x3B0 */ ActionFunc mCurrentStateFunc;
    /* 0x3BC */ u8 m3BC[0x3C4 - 0x3BC];
    /* 0x3C4 */ int mStaffId;
    /* 0x3C8 */ s16 m3C8;
    /* 0x3CA */ u8 m3CA[0x3E8 - 0x3CA];
    /* 0x3E8 */ f32 mHeightOffset;
    /* 0x3EC */ u8 m3EC[0x3FC - 0x3EC];
};

#endif /* D_A_BIGELF_H */
