#ifndef D_A_OBJ_CAFELMP_H
#define D_A_OBJ_CAFELMP_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObjCafelmp_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel;
};

#endif /* D_A_OBJ_CAFELMP_H */
