#ifndef D_A_NPC_SV_H
#define D_A_NPC_SV_H

#include "d/d_cc_d.h"
#include "d/d_npc.h"

struct sSvAnmDat {
    /* 0x00 */ u8 mBckIdx;
    /* 0x01 */ u8 mMorf;
    /* 0x02 */ s8 mLoopCount;
}; // Size: 0x03

struct NpcDatStruct {
    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ u8 field_0x42;
    /* 0x43 */ u8 field_0x43;
}; // size 0x44;

class daNpcSv_c : public fopNpc_npc_c {
public:
    void getMsgPtn() {}
    u8 getNpcNo() {
        return mNpcNo;
    }
    request_of_phase_process_class* getPhaseP() {
        return &mPhase;
    }
    void setResFlag(u8 flag) {
        mResFlag = flag;
    }

    daNpcSv_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    BOOL executeCommon();
    void executeSetMode(u8);
    BOOL executeWaitInit();
    void executeWait();
    BOOL executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    BOOL eventMesSet();
    void eventGetItemInit(int);
    bool eventGetItem();
    void eventSetAngleInit();
    void eventAttentionInit(int);
    void eventAttention();
    void eventTurnOkInit();
    u16 talk2(int, fopAc_ac_c*);
    virtual u16 next_msgStatus(u32*);
    virtual u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sSvAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    u8 getTalkNo();
    BOOL isTalkOK();

    static const char m_arcname[];

private:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ request_of_phase_process_class mPhaseCreate;
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ int field_0x6D8;
    /* 0x6DC */ u8 padding_0x6DC[0x6EC - 0x6DC];
    /* 0x6EC */ cXyz field_0x6EC;
    /* 0x6F8 */ u8 padding_0x6F8[0x704 - 0x6F8];
    /* 0x704 */ sSvAnmDat* mpAnmDat;
    /* 0x708 */ u32* mpMsgNo;
    /* 0x70C */ f32 mAnmMorfOverride;
    /* 0x710 */ f32 field_0x710;
    /* 0x714 */ u32 field_0x714;
    /* 0x718 */ u32 field_0x718;
    /* 0x71C */ u8 field_0x71C;
    /* 0x71D */ u8 field_0x71D;
    /* 0x71E */ s16 field_0x71E[3];
    /* 0x724 */ s16 field_0x724;
    /* 0x726 */ s16 field_0x726;
    /* 0x728 */ s16 field_0x728;
    /* 0x72A */ u16 field_0x72A;
    /* 0x72C */ s16 field_0x72C;
    /* 0x72E */ u16 field_0x72E;
    /* 0x730 */ s16 field_0x730;
    /* 0x732 */ u16 field_0x732;
    /* 0x734 */ u16 mTalkFlags;
    /* 0x736 */ u8 field_0x736;
    /* 0x737 */ u8 field_0x737;
    /* 0x738 */ u8 mEvtOrderType;
    /* 0x739 */ u8 mMoveState;
    /* 0x73A */ u8 mResFlag;
    /* 0x73B */ u8 mNpcNo;
    /* 0x73C */ u8 field_0x73C;
    /* 0x73D */ u8 mBckIdx;
    /* 0x73E */ u8 mAnmFlag;
    /* 0x73F */ s8 mAnmLoopCnt;
    /* 0x740 */ u8 field_0x740;
    /* 0x741 */ u8 field_0x741;
    /* 0x742 */ u8 field_0x742;
    /* 0x743 */ u8 field_0x743;
    /* 0x744 */ u8 field_0x744;
    /* 0x745 */ u8 field_0x745;
    /* 0x746 */ u8 mTalkNo;
    /* 0x747 */ u8 field_0x747;
    /* 0x748 */ u8 field_0x748;
    /* 0x749 */ u8 field_0x749;
    /* 0x74A */ u8 field_0x74A;
    /* 0x74B */ u8 padding_0x74B[0x74C - 0x74B];
}; // Size: 0x74C

#endif /* D_A_NPC_SV_H */
