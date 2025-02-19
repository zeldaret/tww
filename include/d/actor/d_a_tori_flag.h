#ifndef D_A_TORI_FLAG_H
#define D_A_TORI_FLAG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cloth_packet.h"

class daTori_Flag_HIO_c {
    public:
        // Constructor
        daTori_Flag_HIO_c();

        // Virtual Destructor
        virtual ~daTori_Flag_HIO_c(){}
        
    public:
        /* Place member variables here */
        /* 0x00 */ //vtable
        /* 0x04 */ signed char flag;
        /* 0x08 */ float someFloat;
        /* 0x0c */ signed short someShort;
};

class daTori_Flag_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void set_mtx();
    BOOL CreateHeap();
    s32 CreateInit();

    static const char M_arcname[7];

public:
    /* 0x290 */ request_of_phase_process_class mPhsTrflag;
    /* 0x298 */ request_of_phase_process_class mPhsCloth;
    /* 0x2A0 */ J3DModel* mpModel;
    /* 0x2A4 */ dCloth_packet_c* mpCloth;
    /* 0x2A8 */ cXyz mWindvec;
    /* 0x2B4 */ dKy_tevstr_c mClothTevStr;
    /* 0x364 */ dCcD_Stts mStts;
    /* 0x3A0 */ dCcD_Cyl mCyl;
    /* 0x4D0 */ dCcD_Cyl mCyl2;
};

extern daTori_Flag_HIO_c l_HIO;
extern cXyz l_flag_offset;

#endif /* D_A_TORI_FLAG_H */
