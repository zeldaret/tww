#ifndef D_A_OBJ_FIGURE_H
#define D_A_OBJ_FIGURE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

class daObjFigure_c : public fopAc_ac_c {
public:
    daObjFigure_c();

    u8 getFigureNo() { return mFigureNo; }
    request_of_phase_process_class* getPhase1P() { return &mPhsFigure; }
    request_of_phase_process_class* getPhase2P() { return &mPhsRoomArc; }
    bool isDispFigure() { return mbDisplay; }
    void setResFlag(u8 flag) { mLoadFlags |= flag; }

    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventOnPlrInit();
    void eventOffPlrInit();
    u16 talk(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setMessage(u32);
    u8 getPrmFigureNo();
    void setMtx();
    u8 isFigureGet(u8);
    int getFigureBmd(u8);
    
    enum Prm_e {
        PRM_FIGURE_NO_W = 8,
        PRM_FIGURE_NO_S = 0,
    };

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
    /* 0x694 */ fpc_ProcID m694;
    /* 0x698 */ msg_class* mpCurrMsg;
    /* 0x69C */ u32 m69C;
    /* 0x6A0 */ dNpc_EventCut_c mEventCut;
    /* 0x70C */ cXyz m70C;
    /* 0x718 */ cXyz m718;
    /* 0x724 */ f32 m724;
    /* 0x728 */ f32 m728;
    /* 0x72C */ u32* m72C;
    /* 0x730 */ s16 mFigureCheckEvtIdx;
    /* 0x732 */ s16 m732;
    /* 0x734 */ s16 m734;
    /* 0x736 */ s16 m736;
    /* 0x738 */ s16 m738;
    /* 0x73A */ s16 m73A;
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 mFigureNo;
    /* 0x73E */ u8 mbDisplay;
    /* 0x73F */ u8 m73F;
    /* 0x740 */ u8 m740;
    /* 0x741 */ s8 m741;
    /* 0x742 */ u8 mLoadFlags;
    /* 0x743 */ u8 m743[0x744 - 0x743];
};

#endif /* D_A_OBJ_FIGURE_H */
