#ifndef D_A_HITOBJ_H
#define D_A_HITOBJ_H

#include "f_op/f_op_actor.h"
#include "dolphin/types.h"
#include "d/d_com_inf_game.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_cc_s.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"

class hitobj_class : public fopAc_ac_c {
public:
    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ u8 mUnusedParam;
    /* 0x029A */ s16 mTimer;
    /* 0x029C */ dCcD_Stts mStts;
    /* 0x02D8 */ dCcD_Sph mSph;
}; // Size: 0x0404

#endif /* D_A_HITOBJ_H */
