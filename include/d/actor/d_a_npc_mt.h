#ifndef D_A_NPC_MT_H
#define D_A_NPC_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

struct sMtAnmDat {
    
};

class daNpcMt_c : public fopAc_ac_c {
public:
    void attnOff() {}
    void attnOn() {}
    void getNpcNo() {}
    void getPhaseP() {}
    void setResFlag(unsigned char) {}

    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
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
    void next_msgStatus(unsigned long*);
    void getMsg();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sMtAnmDat*);
    void XyCheckCB(int);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void chkEndEvent();
    void isFigureGet(unsigned char);
    void setFigure(unsigned char);
    void getFigureMakeNum();
    void isComp();
    void changePhotoNo(unsigned char);

public:
    /* 0x290 */ dNpc_JntCtrl_c mJnt;
    /* 0x2C4 */ dNpc_EventCut_c mEventCut;
    /* 0x328 */ u8 m328[0x330 - 0x328];
    /* 0x330 */ mDoExt_McaMorf* mpMorf;
    /* 0x334 */ dBgS_Acch mAcch;
    /* 0x4F8 */ dBgS_AcchCir mAcchCir;
    /* 0x538 */ dCcD_Stts mStts;
    /* 0x574 */ dCcD_GObjInf mGObjInf;
    /* 0x66C */ u8 m66C[0x6C4 - 0x66C];
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
    /* 0x752 */ u8 m752[0x758 - 0x752];
};

#endif /* D_A_NPC_MT_H */
