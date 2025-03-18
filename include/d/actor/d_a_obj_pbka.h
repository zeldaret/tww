#ifndef D_A_OBJ_PBKA_H
#define D_A_OBJ_PBKA_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObjPbka_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
};

#endif /* D_A_OBJ_PBKA_H */
