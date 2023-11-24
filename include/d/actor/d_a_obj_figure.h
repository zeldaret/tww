#ifndef D_A_OBJ_FIGURE_H
#define D_A_OBJ_FIGURE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "d/d_npc.h"

class daObjFigure_c : public fopAc_ac_c {
public:
    void getFigureNo() {}
    void getPhase1P() {}
    void getPhase2P() {}
    void isDispFigure() {}
    void setResFlag(unsigned char) {}

    void _create();
    void createHeap();
    void createInit();
    void _delete();
    void _draw();
    void _execute();
    void executeNormal();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventOnPlrInit();
    void eventOffPlrInit();
    void talk(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setMessage(unsigned long);
    void getPrmFigureNo();
    void setMtx();
    void isFigureGet(unsigned char);
    void getFigureBmd(unsigned char);

public:
    /* 0x290 */ request_of_phase_process_class mPhsLoad;
    /* 0x298 */ request_of_phase_process_class mPhsFigure;
    /* 0x2A0 */ request_of_phase_process_class mPhsRoomArc;
    /* 0x2A8 */ J3DModel* mpModel;
    /* 0x2AC */ J3DModel* mpPedestalModel;
    /* 0x2B0 */ J3DAnmTexPattern* mpPedestalBtp;
    /* 0x2B4 */ mDoExt_btpAnm mBtpAnm1;
    /* 0x2C8 */ u8 m2C8[0x2CC - 0x2C8];
    /* 0x2CC */ mDoExt_btpAnm mBtpAnm2;
    /* 0x2E0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2E4 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2E8 */ dKy_tevstr_c mTevStrBG2;
    /* 0x398 */ u8 m398[0x3C8 - 0x398];
    /* 0x3C8 */ Mtx mMtx;
    /* 0x3F8 */ dCcD_Stts mStts;
    /* 0x434 */ dCcD_Cyl mCyl1;
    /* 0x564 */ dCcD_Cyl mCyl2;
    /* 0x694 */ int m694;
    /* 0x698 */ u8 m698[0x69C - 0x698];
    /* 0x69C */ int m69C;
    /* 0x6A0 */ dNpc_EventCut_c mEventCut;
    /* 0x704 */ u8 m704[0x72C - 0x704];
    /* 0x72C */ int m72C;
    /* 0x730 */ s16 mFigureCheckEvtIdx;
    /* 0x732 */ s16 m732;
    /* 0x734 */ s16 m734;
    /* 0x736 */ s16 m736;
    /* 0x738 */ u8 m738[0x73C - 0x738];
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 mPrmFigureNo;
    /* 0x73E */ u8 mbIsFigureGet;
    /* 0x73F */ u8 m73F[0x741 - 0x73F];
    /* 0x741 */ u8 m741;
    /* 0x742 */ u8 mLoadFlags;
    /* 0x743 */ u8 m743[0x744 - 0x743];
};

#endif /* D_A_OBJ_FIGURE_H */
