#ifndef D_A_OBJ_PBCO_H
#define D_A_OBJ_PBCO_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"

class dBgW;

class daObj_Pbco_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    static const char M_arcname[];
    BOOL CreateHeap();
    cPhs_State CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
};  // Size: 0x2A0

class daObj_Pbco_HIO_c {
public:
    daObj_Pbco_HIO_c();
    virtual ~daObj_Pbco_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
};  // Size: 0x08

#endif /* D_A_OBJ_PBCO_H */
