#ifndef D_A_TOGE_H
#define D_A_TOGE_H

#include "d/d_cc_d.h"
#include "d/d_stage.h"
#include "f_op/f_op_actor.h"

class daToge_c : public fopAc_ac_c {
public:
    void set_mtx();  // weak but not inlined?

    BOOL _delete();
    BOOL CreateHeap();
    BOOL Create();
    s32 _create();
    BOOL _execute();
    void set_collision();
    void search_wind();
    void toge_move();
    void toge_seStart(u32 i_seNum);
    BOOL _draw();

    static const char m_arcname[];
    static const s16 m_bdlidx;
    static const s16 m_dzbidx;
    static const u32 m_heapsize;
    static const f32 m_y_min;

public:
    /* 0x290 */ request_of_phase_process_class m_Phs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dBgW* mpBgW1;
    /* 0x40C */ Mtx mtx1;
    /* 0x43C */ dBgW* mpBgW2;
    /* 0x440 */ Mtx mtx2;
    /* 0x470 */ f32 unk470;
    /* 0x474 */ f32 unk474;
    /* 0x478 */ s32 mSwitchNo;
    /* 0x47C */ char pad47C[4];
    /* 0x480 */ s32 mWindTagId;
    /* 0x484 */ u8 mEventState;
    /* 0x485 */ u8 unk485;
    /* 0x486 */ u8 unk486;
};

namespace daToge_prm {
inline u8 getSwitchNo(daToge_c* ac) {
    return (fopAcM_GetParam(ac) >> 0) & 0xFF;
}

inline u8 getSeEnabled(daToge_c* ac) {
    return (fopAcM_GetParam(ac) >> 8) & 0xF;
}
};  // namespace daToge_prm

#endif /* D_A_TOGE_H */
