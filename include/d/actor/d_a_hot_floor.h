#ifndef D_A_HOT_FLOOR_H
#define D_A_HOT_FLOOR_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;

class daHot_Floor_c : public fopAc_ac_c {
public:
    void set_mtx_init();
    void set_mtx();
    cPhs_State CreateInit();
    inline cPhs_State _create();
    inline bool _execute();
    inline bool _draw();
    inline bool _delete();
    inline bool create_heap();
    void setAimMtx(MtxP i_mtx) { 
        mtx_p = i_mtx; 
        mbSpawnParticle = true;
    }

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u32 field_0x298;
    /* 0x298 */ u32 field_0x29c;
    /* 0x2A0 */ mDoExt_brkAnm mBrkAnm;
    /* 0x2B8 */ f32 mSpawnTimer;
    /* 0x2BC */ u32 field_0x2bc;
    /* 0x2C0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2D4 */ JPABaseEmitter * mEmitter1;
    /* 0x2D8 */ JPABaseEmitter * mEmitter2;
    /* 0x2DC */ bool mbSpawnParticle;
    /* 0x2E0 */ Mtx mtx[5];
    /* 0x3D0 */ MtxP mtx_p;
    /* 0x3D4 */ u32 field_0x3d4;
};

#endif /* D_A_HOT_FLOOR_H */
