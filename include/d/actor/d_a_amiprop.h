#ifndef D_A_AMIPROP_H
#define D_A_AMIPROP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"

class daAmiProp_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    bool _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dBgW* mpBgW;
    /* 0x40C */ Mtx unk_40C;
    /* 0x43C */ u32 unk_43C;
    /* 0x440 */ s32 unk_440;
    /* 0x444 */ bool unk_444;
    /* 0x446 */ s16 unk_446;
}; // size = 0x448

#endif /* D_A_AMIPROP_H */
