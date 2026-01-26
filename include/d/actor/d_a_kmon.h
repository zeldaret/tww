#ifndef D_A_KMON_H
#define D_A_KMON_H

#include "d/actor/d_a_npc_ji1.h"

class daKmon_c : public fopAc_ac_c {
public:
    void set_mtx();
    BOOL CreateHeap();
    cPhs_State CreateInit();
    void checkTalk();

    inline cPhs_State _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ mDoExt_bckAnm mBckAnm;
    /* 0x2C0 */ dBgS_ObjAcch mAcch;
    /* 0x484 */ dBgS_AcchCir mAcchCir;
    /* 0x4C4 */ daNpc_Ji1_c* mpJi1;
}; // Size: 0x4C8

#endif /* D_A_KMON_H */
