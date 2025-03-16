#ifndef D_A_OBJ_BSCURTAIN_H
#define D_A_OBJ_BSCURTAIN_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"

class daObj_Bscurtain_c : public fopAc_ac_c {
public:
    BOOL CreateHeap();
    s32 CreateInit();
    inline s32 _create();
    inline bool _delete();
    inline bool _execute();
    inline bool _draw();
    void set_mtx();
    static const char M_arcname[4];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u32 field_0x298;
    /* 0x29C */ J3DModel * mpModel;
};

class daObj_Bscurtain_HIO_c {
public:
    daObj_Bscurtain_HIO_c();
    virtual ~daObj_Bscurtain_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ u16 field_0x0c;
};

#endif /* D_A_OBJ_BSCURTAIN_H */
