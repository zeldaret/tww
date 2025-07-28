#ifndef D_A_DEMO_KMM_H
#define D_A_DEMO_KMM_H

#include "f_op/f_op_actor.h"

class mDoExt_McaMorf;

class daDemo_Kmm_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char idx) {
        unk_29C = idx;
    }

    BOOL CreateHeap();
    void calcMtx();
    void setAnime(int, int, float, float);
    BOOL CreateInit();
    cPhs_State create();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u8 unk_29C;
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ char unk2A0[0x4];
}; // size = 0x2A4

#endif /* D_A_DEMO_KMM_H */
