#ifndef D_A_OBJ_YGUSH00_H
#define D_A_OBJ_YGUSH00_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_a_obj.h"
#include "m_Do/m_Do_hostIO.h"

class daObjGryw00_c;

class daObjYgush00_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_TYPE_W = 3,
        PRM_TYPE_S = 0,
    };

    int param_get_arg() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }

    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();
    bool create_heap();
    static BOOL solidHeapCB(fopAc_ac_c*);

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel * mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ mDoExt_bckAnm mBckAnm;
    /* 0x2C0 */ s32 mType;
    /* 0x2C4 */ daObjGryw00_c * mpGryw00;
};

class daObjYgush00_HIO_c : public JORReflexible  {
public:
    daObjYgush00_HIO_c();
    virtual ~daObjYgush00_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 m05;
    /* 0x06 */ s8 m06;
    /* 0x07 */ s8 m07;
};

#endif /* D_A_OBJ_YGUSH00_H */
