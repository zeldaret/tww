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
    BOOL normal_execute();
    BOOL demo_execute();
    void demo_proc();
    void initWait(int);
    BOOL actWait(int);
    void initStartWarp(int);
    BOOL actStartWarp(int);
    void initWarp(int);
    BOOL actWarp(int);
    void initWarpArrive(int);
    BOOL actWarpArrive(int);
    void initWarpArriveEnd(int);
    BOOL actWarpArriveEnd(int);
    void initAppear(int);
    BOOL actAppear(int);
    void eventOrder();
    void checkOrder();
    void anim_play(int);
    void set_end_anim();
    BOOL check_warp();
    BOOL checkValidWarp();
    bool _draw();

    static const char m_arcname[];
    static const u32 m_heapsize;

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm* mpBtkAnm1;
    /* 0x2A0 */ mDoExt_btkAnm* mpBtkAnm2;
    /* 0x2A4 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A8 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2AC */ JPABaseEmitter* mpEmitter1;
    /* 0x2B0 */ JPABaseEmitter* mpEmitter2;
    /* 0x2B4 */ JPABaseEmitter* mpEmitter3;
    /* 0x2B8 */ u32 mSwitchNo;
    /* 0x2BC */ u8 mIsSwitch;
    /* 0x2BD */ u8 m2BD[0x2C0 - 0x2BD];
    /* 0x2C0 */ u32 mSceneNo;
    /* 0x2C4 */ s32 m2C4;
    /* 0x2C8 */ s16 mEvtToMajyuuWarpIdx;
    /* 0x2CA */ s16 mEvtAppearWarpIdx;
    /* 0x2CC */ s32 mStaffId;
    /* 0x2D0 */ u32 mDemoShape;
    /* 0x2D4 */ int mTimer;
    /* 0x2D8 */ dKy_tevstr_c mTevStr;
    /* 0x388 */ bool m388;
    /* 0x389 */ u8 m389[0x38C - 0x389];
}; // Size: 0x38C

namespace daWarpgn_prm {
inline u32 getSwitchNo(daWarpgn_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 8) & 0xFF;
}
inline u32 getSceneNo(daWarpgn_c* i_this) {
    return fopAcM_GetParam(i_this) & 0xFF;
}
} // namespace daWarpgn_prm

#endif /* D_A_WARPGN_H */
