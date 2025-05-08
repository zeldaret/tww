#ifndef D_A_OBJ_VMSMS_H
#define D_A_OBJ_VMSMS_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObjVmsms_c : public fopAc_ac_c {
public:
    inline bool check_demo() const; // weak but not inlined

    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
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

#endif /* D_A_OBJ_VMSMS_H */
