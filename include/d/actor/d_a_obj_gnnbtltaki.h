#ifndef D_A_OBJ_GNNBTLTAKI_H
#define D_A_OBJ_GNNBTLTAKI_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daObjGnnbtaki_c : public fopAc_ac_c {
public:
    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    bool _execute();
    bool _draw();
    static const char M_arcname[];
public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhase;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ u8 field_0x2B0;
    /* 0x2B1 */ u8 field_0x2B1;
};

#endif /* D_A_OBJ_GNNBTLTAKI_H */
