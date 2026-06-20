#ifndef D_A_WARPHR_H
#define D_A_WARPHR_H

#include "f_op/f_op_actor.h"

class mDoExt_btkAnm;
class mDoExt_brkAnm;
class JPABaseEmitter;

class daWarphr_c : public fopAc_ac_c {
public:
    inline void set_mtx();

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
    void eventOrder();
    void checkOrder();
    void anim_play(int);
    void set_end_anim();
    s32 get_return_count();
    BOOL check_warp();
    bool _draw();

    static const char m_arcname[];
    static const s16 m_residxA[];
    static const s16 m_residxB[];
    static const u32 m_heapsize;

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel1;
    /* 0x29C */ mDoExt_btkAnm* mpBtkAnm1;
    /* 0x2A0 */ J3DModel* mpModel2;
    /* 0x2A4 */ mDoExt_btkAnm* mpBtkAnm2;
    /* 0x2A8 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2AC */ JPABaseEmitter* m2AC;
#if VERSION > VERSION_JPN
    /* 0x2B0 */ JPABaseEmitter* m2B0;
    /* 0x2B4 */ Mtx m2B4;
    /* 0x2E4 */ bool m2E4;
    /* 0x2E5 */ u8 m2E5[0x2E8 - 0x2E5];
#endif
    /* 0x2E8 */ u8 m2E8[0x2F0 - 0x2E8];
    /* 0x2F0 */ s32 m2F0;
    /* 0x2F4 */ u8 m2F4[0x2F8 - 0x2F4];
    /* 0x2F8 */ s16 m2F8;
    /* 0x2FA */ u8 m2FA;
    /* 0x2FB */ u8 m2FB[0x300 - 0x2FB];
    /* 0x300 */ u32 m300;
    /* 0x304 */ s32 m304;
}; // size = 0x308

#endif /* D_A_WARPHR_H */
