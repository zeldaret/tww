#ifndef D_A_SIE_FLAG_H
#define D_A_SIE_FLAG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cloth_packet.h"

class daSie_Flag_c : public fopAc_ac_c {
public:
    void set_mtx();
    void CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhsEshata;
    /* 0x298 */ request_of_phase_process_class mPhsCloth;
    /* 0x2A0 */ J3DModel* mpModel;
    /* 0x2A4 */ dCloth_packet_c* mpClothPacket;
    /* 0x2A8 */ cXyz mWindvec;
    /* 0x2B4 */ dKy_tevstr_c mTevStr;
    /* 0x364 */ dCcD_Stts mStts;
    /* 0x3A0 */ dCcD_Cyl mCyl;
};

class daSie_Flag_HIO_c {
public:
    daSie_Flag_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_SIE_FLAG_H */
