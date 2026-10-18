#ifndef D_A_NPC_SV_H
#define D_A_NPC_SV_H

#include "d/d_cc_d.h"
#include "d/d_npc.h"

struct sSvAnmDat {};

class daNpcSv_c : public fopNpc_npc_c {
public:
    void getMsgPtn() {}
    void getNpcNo() {}
    void getPhaseP() {}
    void setResFlag(u8) {
    }

    daNpcSv_c();
    cPhs_State _create();
    void createHeap();
    void createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeCommon();
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
    void eventMesSet();
    void eventGetItemInit(int);
    bool eventGetItem();
    void eventSetAngleInit();
    void eventAttentionInit(int);
    void eventAttention();
    void eventTurnOkInit();
    void talk2(int, fopAc_ac_c*);
    virtual u16 next_msgStatus(u32*);
    virtual u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(u8, int, f32);
    void setAnmTbl(sSvAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    void getTalkNo();
    void isTalkOK();

private:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ request_of_phase_process_class mPhaseCreate;
    /* 0x6D4 */ u8 padding_0x6D4[0x6EC - 0x6D4];
    /* 0x6EC */ f32 field_0x6EC;
    /* 0x6F0 */ f32 field_0x6F0;
    /* 0x6F4 */ f32 field_0x6F4;
    /* 0x6F8 */ u8 padding_0x6F8[0x704 - 0x6F8];
    /* 0x704 */ int field_0x704;
    /* 0x708 */ int field_0x708;
    /* 0x70C */ u32 field_0x70C;
    /* 0x710 */ f32 field_0x710;
    /* 0x714 */ u8 padding_0x714[0x718 - 0x714];
    /* 0x718 */ u32 field_0x718;
    /* 0x71C */ u8 field_0x71C;
    /* 0x71D */ u8 field_0x71D;
    /* 0x71E */ s16 field_0x71E;
    /* 0x720 */ s16 field_0x720;
    /* 0x722 */ s16 field_0x722;
    /* 0x724 */ s16 field_0x724;
    /* 0x726 */ s16 field_0x726;
    /* 0x728 */ s16 field_0x728;
    /* 0x72A */ u16 field_0x72A;
    /* 0x72C */ u16 field_0x72C;
    /* 0x72E */ u16 field_0x72E;
    /* 0x730 */ s16 field_0x730;
    /* 0x732 */ u16 field_0x732;
    /* 0x734 */ u16 field_0x734;
    /* 0x736 */ u8 field_0x736;
    /* 0x737 */ u8 field_0x737;
    /* 0x738 */ u8 field_0x738;
    /* 0x739 */ u8 mMoveState;
    /* 0x73A */ u8 field_0x73A;
    /* 0x73B */ u8 field_0x73B;
    /* 0x73C */ u8 field_0x73C;
    /* 0x73D */ u8 field_0x73D;
    /* 0x73E */ u8 field_0x73E;
    /* 0x73F */ u8 field_0x73F;
    /* 0x740 */ u8 field_0x740;
    /* 0x741 */ u8 field_0x741;
    /* 0x742 */ u8 field_0x742;
    /* 0x743 */ u8 field_0x743;
    /* 0x744 */ u8 field_0x744;
    /* 0x745 */ u8 field_0x745;
    /* 0x746 */ u8 field_0x746;
    /* 0x747 */ u8 field_0x747;
    /* 0x748 */ u8 field_0x748;
    /* 0x749 */ u8 field_0x749;
    /* 0x74A */ u8 padding_0x74A[0x74C - 0x74A];
}; // Size: 0x74C

#endif /* D_A_NPC_SV_H */
