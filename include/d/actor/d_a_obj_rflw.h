#ifndef D_A_OBJ_RFLW_H
#define D_A_OBJ_RFLW_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

class daObjRflw_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ s16 m408;
    /* 0x40A */ s16 m40A;
    /* 0x40C */ s16 m40C;
    /* 0x40E */ s16 m40E;
    /* 0x410 */ bool m410;
    /* 0x411 */ u8 m411[0x414 - 0x411];
};  // Size: 0x414

#endif /* D_A_OBJ_RFLW_H */
