#ifndef D_A_NPC_MT_H
#define D_A_NPC_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

struct sMtAnmDat {
    
};

class daNpcMt_c : public fopNpc_npc_c {
public:
    void attnOff() {
        m753 = false;
    }
    void attnOn() {
        m753 = true;
    }
    void getNpcNo() {}
    void getPhaseP() {}
    void setResFlag(u8) {}

    daNpcMt_c();
    cPhs_State _create();
    void createHeap();
    void createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeCommon();
    void executeSetMode(u8);
    void executeWaitInit();
    void executeWait();
    void executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventGetItemInit();
    void talk2(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void chkMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(u8, int, f32);
    void setAnmTbl(sMtAnmDat*);
    void XyCheckCB(int);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    void chkEndEvent();
    bool isFigureGet(u8);
    void setFigure(u8);
    int getFigureMakeNum();
    bool isComp();
    void changePhotoNo(u8);

public:
    /* 0x6C4 */ request_of_phase_process_class mPhsArcname;
    /* 0x6CC */ request_of_phase_process_class mPhs;
    /* 0x6D4 */ u8 m6D4[0x6D8 - 0x6D4];
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 m6EC[0x710 - 0x6EC];
    /* 0x710 */ sMtAnmDat* mpAnmDat;
    /* 0x714 */ int* mpMsgTbl;
    /* 0x718 */ u8 m718[0x71C - 0x718];
    /* 0x71C */ f32 m71C;
    /* 0x720 */ u8 m720[0x72A - 0x720];
    /* 0x72A */ s16 mMtGetItemEventIdx;
    /* 0x72C */ u8 m72C[0x732 - 0x72C];
    /* 0x732 */ s16 m732;
    /* 0x734 */ u8 m734[0x742 - 0x734];
    /* 0x742 */ u8 m742;
    /* 0x743 */ u8 m743[0x747 - 0x743];
    /* 0x747 */ u8 m747;
    /* 0x748 */ u8 mPrmNpcNo;
    /* 0x749 */ u8 m749[0x74A - 0x749];
    /* 0x74A */ u8 m74A;
    /* 0x74B */ u8 m74B[0x750 - 0x74B];
    /* 0x750 */ u8 m750;
    /* 0x751 */ u8 m751;
    /* 0x752 */ u8 m752[0x753 - 0x752];
    /* 0x753 */ bool m753;
    /* 0x754 */ u8 m754[0x758 - 0x754];
};

#endif /* D_A_NPC_MT_H */
