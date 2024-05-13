#ifndef D_A_DEKU_ITEM_H
#define D_A_DEKU_ITEM_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"

class daDekuItem_c : public fopAc_ac_c {
public:
    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void mode_proc_call();
    void mode_wait();
    void mode_getdemo_init();
    void mode_getdemo_wait();
    void mode_getdemo();
    void eventOrder();
    void checkOrder();
    BOOL _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs; /* inferred */
    /* 0x298 */ J3DModel* mpModel;                   /* inferred */
    /* 0x29C */ mDoExt_bckAnm mBck1;               /* inferred */
    /* 0x2AC */ mDoExt_bckAnm mBck2;               /* inferred */
    /* 0x2BC */ dBgS_ObjAcch mAcch;                   /* inferred */
    /* 0x480 */ dBgS_AcchCir mAcchCir;                /* inferred */
    /* 0x4C0 */ dCcD_Stts mStts;                   /* inferred */
    /* 0x4FC */ dCcD_Cyl mCyl;                    /* inferred */
    /* 0x62C */ s32 unk62C;                         /* inferred */
    /* 0x630 */ s32 unk630;                         /* inferred */
    /* 0x634 */ s32 mItemBitNo;                         /* inferred */
    /* 0x638 */ s32 unk638;                         /* inferred */
    /* 0x63C */ JPABaseEmitter* mpEmitter;                       /* inferred */
};

namespace daDekuItem_prm {
inline u8 getItemBitNo(daDekuItem_c* ac) {
    return (fopAcM_GetParam(ac) >> 0) & 0xFF;
}
};

#endif /* D_A_DEKU_ITEM_H */
