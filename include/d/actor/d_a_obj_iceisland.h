#ifndef D_A_OBJ_ICEISLAND_H
#define D_A_OBJ_ICEISLAND_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"

class daObjIceisland_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL CreateHeap();
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
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm1;
    /* 0x2B0 */ mDoExt_btkAnm mBtkAnm2;
    /* 0x2C4 */ mDoExt_brkAnm mBrkAnm;
    /* 0x2DC */ JPABaseEmitter* mEmitter1;
    /* 0x2E0 */ JPABaseEmitter* mEmitter2;
    /* 0x2E4 */ dKy_tevstr_c mTevStr;
    /* 0x394 */ u8 field_0x394[0x396 - 0x394];
    /* 0x396 */ s16 field_0x396;
    /* 0x398 */ s16 mMeltIceEventIdx;
    /* 0x39A */ s16 mFreezeIceEventIdx;
    /* 0x39C */ int field_0x39C;
};  // Size: 0x3A0

namespace daObjIceisland_prm {
    inline u8 getSwitchNo(daObjIceisland_c* ac) { return (fopAcM_GetParam(ac) >> 8) & 0xFF; }
};

#endif /* D_A_OBJ_ICEISLAND_H */
