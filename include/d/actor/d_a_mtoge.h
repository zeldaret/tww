#ifndef D_A_MTOGE_H
#define D_A_MTOGE_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

class daMtoge_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(u8 action) { mAction = action; }

    u8 getSwbit();
    BOOL CreateHeap();
    void calcMtx();
    BOOL CreateInit();
    cPhs_State create();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhaseProcReq;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ u8 mAction;
    /* 0x2A1 */ s8 m2A1;
    /* 0x2A2 */ s8 m2A2;
    /* 0x2A3 */ s8 m2A3;
    /* 0x2A4 */ f32 mHeightOffset;
};

#endif /* D_A_MTOGE_H */
