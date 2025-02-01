#ifndef D_A_DAI_H
#define D_A_DAI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class daDai_c : public fopAc_ac_c {
public:
    void decNowItemNum() {}
    void incNowDaizaNum() {}
    void incNowItemNum() {}

    bool _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void eventOrder();
    void checkOrder();
    void XyCheckCB(int);
    void XyEventCB(int);
    bool _execute();
    void proc();
    bool _draw();
    void getMsg();
    void next_msgStatus(unsigned long*);

    static void init() {
        mNowDaizaNum = 0;
        mNowItemNum = 0;
    }
    static int getMaxDaiza();
    static int getDaizaSetItemNum();

    static s8 mNowDaizaNum;
    static s8 mNowItemNum;
    static const u16 m_savelabel[];

public:
    /* 0x6C4 */ request_of_phase_process_class mPhsFdai;
    /* 0x6CC */ request_of_phase_process_class mPhsCloth;
    /* 0x6D4 */ J3DModel* mpModel;
    /* 0x6D8 */ dCcD_Stts mStts;
    /* 0x714 */ dCcD_Cyl mCyl;
    /* 0x844 */ s16 m844;
    /* 0x846 */ s16 mEvtDaiItemIdx;
    /* 0x848 */ s16 mEvtDefaultTalkIdx;
    /* 0x84A */ u8 m84A;
    /* 0x84B */ u8 m84B[0x84C - 0x84B];
    /* 0x84C */ u8 m84C;
    /* 0x84D */ u8 mSaveID;
    /* 0x84E */ u8 m84E[0x850 - 0x84E];
    /* 0x850 */ int m850;
};

#endif /* D_A_DAI_H */
