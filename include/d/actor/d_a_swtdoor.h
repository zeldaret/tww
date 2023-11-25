#ifndef D_A_SWTDOOR_H
#define D_A_SWTDOOR_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class swtdoor_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * model;
    /* 0x29C */ u8 field_0x29c;
    /* 0x29D */ u8 mSwitchNo;
};

#endif /* D_A_SWTDOOR_H */
