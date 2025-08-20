#ifndef D_A_OBJ_GNNDEMOTAKIS_H
#define D_A_OBJ_GNNDEMOTAKIS_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daObjGnntakis_c : public fopAc_ac_c {
public:
    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class field_0x294;
    /* 0x29C */ mDoExt_btkAnm field_0x29C;
    /* 0x2B0 */ int field_0x2B0;
};  // Size: 0x2B4

#endif /* D_A_OBJ_GNNDEMOTAKIS_H */
