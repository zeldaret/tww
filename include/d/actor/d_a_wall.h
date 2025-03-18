#ifndef D_A_WALL_H
#define D_A_WALL_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class daWall_c : public fopAc_ac_c {
public:
    daWall_c() : mSmokeCb(m_smoke_color, NULL, 0) {}
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    void mode_wait();
    void mode_break();
    void set_tri();
    void set_effect();
    void set_se();
    bool _draw();

    static GXColor m_smoke_color;
    static const s16 m_heapsize[3];
    static const char* m_arcname[3];
    static const Vec m_cull_size[][2];
    static const Vec m_tri_vtx[3][4];
    static const s16 m_bmdname[3];
    static const s16 m_dzbname[3];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Tri mTri[2];
    /* 0x578 */ dBgW* mpBgW;
    /* 0x57C */ Mtx mMtx;
    /* 0x5AC */ u8 mState;
    /* 0x5B0 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x5D0 */ JPABaseEmitter* mpEmitter;
    /* 0x5D4 */ f32 mDst;
    /* 0x5D8 */ u8 mBreakCounter;
    /* 0x5DC */ s32 mSwitchNo;
    /* 0x5E0 */ u8 mType;
};  // Size: 0x5E4

#endif /* D_A_WALL_H */
