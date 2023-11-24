#ifndef D_A_MTOGE_H
#define D_A_MTOGE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class daMtoge_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char) {}

    void getSwbit();
    void CreateHeap();
    void calcMtx();
    void CreateInit();
    s32 create();

public:
    /* 0x290 */ request_of_phase_process_class mPhaseProcReq;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ s8 mState;
    /* 0x2A1 */ s8 m2A1;
    /* 0x2A2 */ s8 m2A2;
    /* 0x2A3 */ s8 m2A3;
    /* 0x2A4 */ f32 mHeightOffset;
};

#endif /* D_A_MTOGE_H */
