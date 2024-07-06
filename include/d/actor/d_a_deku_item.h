#ifndef D_A_DEKU_ITEM_H
#define D_A_DEKU_ITEM_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"

class daDekuItem_c : public fopAc_ac_c {
public:
    typedef void (daDekuItem_c::*ModeFunc)();

    enum Mode_e {
        Mode_WAIT_e,
        Mode_GETDEMO_INIT_e,
        Mode_GETDEMO_WAIT_e,
        Mode_GETDEMO_e,
    };

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    bool _execute();
    void mode_proc_call();
    void mode_wait();
    void mode_getdemo_init();
    void mode_getdemo_wait();
    void mode_getdemo();
    void eventOrder();
    void checkOrder();
    bool _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_bckAnm mBck1;
    /* 0x2AC */ mDoExt_bckAnm mBck2;
    /* 0x2BC */ dBgS_ObjAcch mAcch;
    /* 0x480 */ dBgS_AcchCir mAcchCir;
    /* 0x4C0 */ dCcD_Stts mStts;
    /* 0x4FC */ dCcD_Cyl mCyl;
    /* 0x62C */ Mode_e mMode;
    /* 0x630 */ BOOL unk630;
    /* 0x634 */ s32 mItemBitNo;
    /* 0x638 */ uint mItemPID;
    /* 0x63C */ JPABaseEmitter* mpEmitter;
};

namespace daDekuItem_prm {
inline u8 getItemBitNo(daDekuItem_c* ac) {
    return (fopAcM_GetParam(ac) >> 0) & 0xFF;
}
};

#endif /* D_A_DEKU_ITEM_H */
