#ifndef D_A_OBJ_TOWER_H
#define D_A_OBJ_TOWER_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"

class daObjTower_c : public fopAc_ac_c {
public:
    inline cPhs__Step _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ u8 field_0x2d0;
    /* 0x2D1 */ u8 m2D0[0x2D4 - 0x2D1];
};

#endif /* D_A_OBJ_TOWER_H */
