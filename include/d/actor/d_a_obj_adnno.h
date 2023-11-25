#ifndef D_A_OBJ_ADNNO_H
#define D_A_OBJ_ADNNO_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObjAdnno_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _execute();
    inline bool _draw();
    inline bool _delete();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel[16];
};

#endif /* D_A_OBJ_ADNNO_H */
