#ifndef D_A_ATDOOR_H
#define D_A_ATDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

class daAtdoor_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(u8 action) { mAction = action; }

    u8 getSwbit();
    BOOL CreateHeap();
    void calcMtx();
    bool CreateInit();
    cPhs_State create();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ u8 mAction;
    /* 0x2A2 */ s16 unk_2A2;
}; // size = 0x2A4

#endif /* D_A_ATDOOR_H */
