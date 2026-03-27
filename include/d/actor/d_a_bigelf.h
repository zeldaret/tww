#ifndef D_A_BIGELF_H
#define D_A_BIGELF_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daBigelf_c : public fopAc_ac_c {
public:
    typedef BOOL (daBigelf_c::*ActionFunc)(void*);

    enum State_t {
        BIGELF_STATE_UNK0 = 0b1,
        BIGELF_STATE_UNK1 = 0b10,
        BIGELF_STATE_UNK2 = 0b100,
        BIGELF_STATE_UNK3 = 0b1000,
        BIGELF_STATE_UNK4 = 0b10000,
        BIGELF_STATE_UNK5 = 0b100000,
        BIGELF_STATE_UNK6 = 0b1000000,
        BIGELF_STATE_UNK7 = 0b10000000,
        BIGELF_STATE_UNK8 = 0b100000000,
        BIGELF_STATE_UNK9 = 0b1000000000,
        BIGELF_STATE_UNK10 = 0b10000000000,
        //BIGELF_STATE_UNK11 = 0b100000000000,
    };

    bool chkFlag(u16 mask) {
        return (this->mStateBits & mask) == mask;
    }
    void clrFlag(u16 mask) {
        this->mStateBits &= ~mask; 
    }
    void getBackboneJntNum() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void incAttnSetCount() {}
    void setAction(ActionFunc, void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setFlag(u16 mask) {
        this->mStateBits |= mask;
    }

    void oct_delete();
    void nodeCallBack(J3DNode*);
    void lightInit(cXyz*);
    void lightEnd();
    void lightProc();
    void darkInit();
    void darkEnd();
    void darkProc();
    void demoInitFlDelete();
    BOOL demoProcFlDelete();
    void demoInitFlLink();
    BOOL demoProcFlLink();
    void demoInitFlDmAf();
    BOOL demoProcFlDmAf();
    void demoInitFlDmMd();
    BOOL demoProcFlDmMd();
    void demoInitFlDmBf();
    BOOL demoProcFlDmBf();
    void demoInitFlDemo();
    BOOL demoProcFlDemo();
    void demoInitExit();
    BOOL demoProcExit();
    void demoInitTalk();
    BOOL demoProcTalk();
    void demoInitAppear();
    BOOL demoProcAppear();
    void demoInitFa1();
    BOOL demoProcFa1();
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitCom();
    void demoProcCom();
    int getNowEventAction();
    void demoProc();
    u8 getType();
    u8 getSwbit();
    u8 getSwbit2();
    u16 getEventFlag();
    void makeFa1S();
    void makeFa1();
    void setAnm(s8);
    void setAnmStatus();
    fopMsg_MessageStatus_e next_msgStatus(u32*);
    int getMsg();
    void msgPushButton();
    void msgAnm(u8);
    void talkInit();
    u16 talk();
    BOOL init();
    void setAttention(bool);
    void lookBack();
    bool hunt();
    bool oct_search();
    bool oct();
    bool ready0();
    bool event0();
    bool dead();
    BOOL wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhaseProcReq;
    /* 0x298 */ mDoExt_McaMorf* mpBckAnimator;
    /* 0x29C */ mDoExt_brkAnm mBrkAnimator;
    /* 0x2B4 */ mDoExt_btkAnm mBtkAnimator;
    /* 0x2C8 */ J3DModel* mpFlowerModel;
    /* 0x2CC */ mDoExt_brkAnm mFlowerBrkAnimator;
    /* 0x2E4 */ s8 m_fl_jnt;
    /* 0x2E8 */ dNpc_JntCtrl_c m_jnt;
    /* 0x31C */ cXyz mUnkPos;
    /* 0x328 */ cXyz mCurrentPos;
    /* 0x334 */ u16 m334;
    /* 0x336 */ s8 m336;
    /* 0x337 */ u8 m337;
    /* 0x338 */ f32 m338;
    /* 0x33C */ u32 mMsgIdx;
    /* 0x340 */ u16 mStateBits;
    /* 0x342 */ u16 m342;
    /* 0x344 */ u8 m344;
    /* 0x345 */ u8 m345;
    /* 0x346 */ u8 mGivenItem;
    /* 0x347 */ u8 m347[0x348 - 0x347];
    /* 0x348 */ u32 mCurrentMessageId;
    /* 0x34C */ fpc_ProcID mFairyActorID;
    /* 0x350 */ u8 m350[0x352 - 0x350];
    /* 0x352 */ bool mIsLightShining;
    /* 0x353 */ u8 m353[0x354 - 0x353];
    /* 0x354 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x374 */ cXyz mLightInfluencePos;
    /* 0x380 */ GXColorS10 mLightInfluenceColor;
    /* 0x388 */ f32 mLightInfluencePower;
    /* 0x38C */ f32 mLightInfluenceFluctuation;
    /* 0x390 */ u8 m390[0x39C - 0x390];
    /* 0x39C */ u8 bIsDark;
    /* 0x3A0 */ f32 m3A0;
    /* 0x3A4 */ f32 m3A4;
    /* 0x3A8 */ f32 mBlend;
    /* 0x3AC */ s16 m3AC;
    /* 0x3B0 */ ActionFunc mCurrentStateFunc;
    /* 0x3BC */ s8 m3BC;
    /* 0x3BD */ s8 m3BD;
    /* 0x3BE */ u8 m3BE[0x3C0 - 0x3BE];
    /* 0x3C0 */ s16 m3C0;
    /* 0x3C4 */ int mStaffId;
    /* 0x3C8 */ s16 mArrivalEvtID;
    /* 0x3CA */ s16 iAttCnt;
    /* 0x3CC */ JPABaseEmitter* m3CC;
    /* 0x3D0 */ cXyz m3D0;
    /* 0x3DC */ u8 m3DC;
    /* 0x3E0 */ JPABaseEmitter* m3E0;
    /* 0x3E4 */ JPABaseEmitter* m3E4;
    /* 0x3E8 */ f32 mHeightOffset;
    /* 0x3EC */ f32 m3EC;
    /* 0x3F0 */ f32 m3F0;
    /* 0x3F4 */ u8 m3F4;
    /* 0x3F5 */ s8 iBrkFrame;
    /* 0x3F6 */ s8 m3F6;
    /* 0x3F7 */ s8 m3F7;
    /* 0x3F8 */ fpc_ProcID mOctID;
};

#endif /* D_A_BIGELF_H */
