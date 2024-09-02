#ifndef D_A_OBJ_VMSDZ_H
#define D_A_OBJ_VMSDZ_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObjVmsdz_c : public fopAc_ac_c {
public:
    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    s32 _create();
    bool _delete();
    void init_mtx();
    bool _execute();
    bool _draw();

public:
    static const char M_arcname[];

public:
    /* 0x290 */ J3DModel* mModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
};

#endif /* D_A_OBJ_VMSDZ_H */
