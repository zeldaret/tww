#ifndef D_A_OBJ_HFUCK1_H
#define D_A_OBJ_HFUCK1_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#if VERSION == VERSION_DEMO
#include "m_Do/m_Do_hostIO.h"
#endif

class daObjHfuck1_c : public fopAc_ac_c {
public:
    void init_mtx();
    cPhs_State _create();
    bool _execute();
    bool _draw();
    bool _delete();
    bool create_heap();
    bool checkCollision();
    static BOOL solidHeapCB(fopAc_ac_c *i_this);

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel;
    /* 0x29C */ dBgW * mpBgW;
    /* 0x2A0 */ dCcD_Stts mStts;
    /* 0x408 */ dCcD_Sph mSph;
    /* 0x40C */ fopAc_ac_c * mpHookshotActor;
};

#if VERSION == VERSION_DEMO
class daObjHfuck1_HIO_c : public JORReflexible {
public:
    daObjHfuck1_HIO_c();
    virtual ~daObjHfuck1_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};
#endif

#endif /* D_A_OBJ_HFUCK1_H */
