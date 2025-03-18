#ifndef D_A_OBJ_ICEISLAND_H
#define D_A_OBJ_ICEISLAND_H

#include "f_op/f_op_actor.h"

class daObjIceisland_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void CreateHeap();
    void daObjIceisland_particle_set();
    void CreateInit();
    void set_mtx();
    void daObjIceisland_freeze_main();
    void daObjIceisland_melt_demo_wait();
    void daObjIceisland_melt_demo();
    void daObjIceisland_melt_main();
    void daObjIceisland_freeze_demo_wait();
    void daObjIceisland_freeze_demo();
    void daObjIceisland_fail_demo_wait();
    void daObjIceisland_fail_demo_main();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_ICEISLAND_H */
