#ifndef D_A_TOGE_H
#define D_A_TOGE_H

#include "d/d_stage.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"


class daToge_c : public fopAc_ac_c {
public:
    void set_mtx();  // weak but not inlined?

    BOOL _delete();
    BOOL CreateHeap();
    s32 Create();
    s32 _create();
    BOOL _execute();
    void set_collision();
    void search_wind();
    void toge_move();
    void toge_seStart(unsigned long);
    BOOL _draw();

    static const char m_arcname[];
    static const s16 m_bdlidx;
    static const s16 m_dzbidx;
    static const u32 m_heapsize;
    static const f32 m_y_min;
    static const Vec m_cull_min;
    static const Vec m_cull_max;


public:
    /* Place member variables here */

    /* 0x290 */ request_of_phase_process_class m_Phs; /* inferred */
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl; /* inferred */
    /* 0x408 */ dBgW* mpBgW1;      /* inferred */
    /* 0x40C */ Mtx mtx1;          /* maybe part of unk408[0xD]? */
    /* 0x43C */ dBgW* mpBgW2;      /* inferred */
    /* 0x440 */ Mtx mtx2;          /* inferred */
    /* 0x470 */ f32 unk470;        /* inferred */
    /* 0x47C */ char pad47C[4];
    /* 0x480 */ s32 unk480; /* inferred */
};

#endif /* D_A_TOGE_H */
