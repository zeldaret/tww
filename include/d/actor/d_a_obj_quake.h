#ifndef D_A_OBJ_QUAKE_H
#define D_A_OBJ_QUAKE_H

#include "f_op/f_op_actor.h"

class daObjQuake_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_SCH_W = 0x8,
        PRM_SCH_S = 0x0,

        PRM_TYPE_W = 0x3,
        PRM_TYPE_S = 0x8,

        PRM_POWER_W = 0x3,
        PRM_POWER_S = 0xB,
    };

    s32 _create();
    BOOL _delete();
    BOOL _is_delete();
    BOOL _execute();
    u8 getPrmType();
    u8 getPrmSch();
    s32 getPrmPower();

public:
    /* Place member variables here */
};

class daObjQuake_HIO_c {
public:
    daObjQuake_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_QUAKE_H */
