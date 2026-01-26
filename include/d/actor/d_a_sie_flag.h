#ifndef D_A_SIE_FLAG_H
#define D_A_SIE_FLAG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cloth_packet.h"

class daSie_Flag_c : public fopAc_ac_c {
public:
    void set_mtx();
    BOOL CreateHeap();
    cPhs_State CreateInit();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhsEshata;
    /* 0x298 */ request_of_phase_process_class mPhsCloth;
    /* 0x2A0 */ J3DModel* mpModel;
    /* 0x2A4 */ dCloth_packet_c* mpClothPacket;
    /* 0x2A8 */ cXyz mWindvec;
    /* 0x2B4 */ dKy_tevstr_c mTevStr;
    /* 0x364 */ dCcD_Stts mStts;
    /* 0x3A0 */ dCcD_Cyl mCyl;
    /* 0x4D0 */ dCcD_Cyl mCyl2;
};

class daSie_Flag_HIO_c {
public:
    daSie_Flag_HIO_c();

    virtual ~daSie_Flag_HIO_c() {};

public:
    /* 0x00 */ //vtable
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0c;
};

#endif /* D_A_SIE_FLAG_H */
