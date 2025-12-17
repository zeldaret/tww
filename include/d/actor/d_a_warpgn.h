#ifndef D_A_WARPGN_H
#define D_A_WARPGN_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"

class daWarpgn_c : public fopAc_ac_c {
public:
    void set_mtx(); // weak but not inlined?

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _execute();
    void normal_execute();
    void demo_execute();
    void demo_proc();
    void initWait(int);
    void actWait(int);
    void initStartWarp(int);
    void actStartWarp(int);
    void initWarp(int);
    void actWarp(int);
    void initWarpArrive(int);
    void actWarpArrive(int);
    void initWarpArriveEnd(int);
    void actWarpArriveEnd(int);
    void initAppear(int);
    void actAppear(int);
    void eventOrder();
    void checkOrder();
    void anim_play(int);
    void set_end_anim();
    void check_warp();
    BOOL checkValidWarp();
    bool _draw();

    static const char m_arcname[];
    static const u32 m_heapsize;

public:
    /* 0x290 */ request_of_phase_process_class field_0x290;
    /* 0x298 */ J3DModel* field_0x298;
    /* 0x29C */ mDoExt_btkAnm* field_0x29C;
    /* 0x2A0 */ mDoExt_btkAnm* field_0x2A0;
    /* 0x2A4 */ mDoExt_brkAnm* field_0x2A4;
    /* 0x2A8 */ mDoExt_bckAnm* field_0x2A8;
    /* 0x2AC */ JPABaseEmitter* field_0x2AC;
    /* 0x2B0 */ JPABaseEmitter* field_0x2B0;
    /* 0x2B4 */ JPABaseEmitter* field_0x2B4;
    /* 0x2B8 */ u32 field_0x2B8;
    /* 0x2BC */ bool field_0x2BC;
    /* 0x2BD */ u8 field_0x2BD[0x2C0 - 0x2BD];
    /* 0x2C0 */ u32 field_0x2C0;
    /* 0x2C4 */ s32 field_0x2C4;
    /* 0x2C8 */ s16 field_0x2C8;
    /* 0x2CA */ s16 field_0x2CA;
    /* 0x2CC */ u8 field_0x2CC[0x2D8 - 0x2CC];
    /* 0x2D8 */ dKy_tevstr_c field_0x2D8;
    /* 0x388 */ bool field_0x388;
    /* 0x389 */ u8 field_0x389[0x38C - 0x389];
};  // Size: 0x38C

namespace daWarpgn_prm {
    inline u32 getSwitchNo(daWarpgn_c* i_this) { return (fopAcM_GetParam(i_this) >> 8) & 0xFF; }
    inline u32 getSceneNo(daWarpgn_c* i_this) { return fopAcM_GetParam(i_this) & 0xFF; } 
}

#endif /* D_A_WARPGN_H */
