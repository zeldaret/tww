#ifndef D_THROWSTONE_H
#define D_THROWSTONE_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daThrowstone_c : public fopAc_ac_c {
public:
    BOOL CreateHeap();
    inline s32 _create();
    inline bool _delete();
    inline bool _execute();
    inline bool _draw();

    static const char M_arcname[5];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel;
    /* 0x29C */ Mtx mMtx;
};

#endif /* D_THROWSTONE_H */
