#ifndef D_A_OBJ_ROTEN_H
#define D_A_OBJ_ROTEN_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "d/d_bg_w.h"

class daObj_Roten_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void set_mtx();
    BOOL CreateHeap();
    cPhs_State CreateInit();
    
    static int getCreateCount();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ u8 field_0x29C[0x2CC - 0x29C];
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ u8 mType;
    /* 0x2D1 */ u8 field_0x2D1;

    static const char M_arcname[];
}; // Size: 0x2D2

class daObj_Roten_HIO_c : public JORReflexible {
public:
    daObj_Roten_HIO_c();
    virtual ~daObj_Roten_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ s16 field_0x0C;
}; // Size: 0x0E

#endif /* D_A_OBJ_ROTEN_H */
