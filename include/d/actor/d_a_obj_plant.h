#ifndef D_A_OBJ_PLANT_H
#define D_A_OBJ_PLANT_H

#include "f_op/f_op_actor.h"

class daObjPlant_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts field_0x29C;
    /* 0x2D8 */ dCcD_Cyl field_0x2D8;
    /* 0x408 */ s16 field_0x408;
    /* 0x40A */ u8 field_0x40A[0x40E - 0x40A];
    /* 0x40E */ s16 field_0x40E;
    /* 0x410 */ u8 field_0x410;
    /* 0x411 */ u8 field_0x411[0x414 - 0x411];
};  // Size: 0x414

#endif /* D_A_OBJ_PLANT_H */
