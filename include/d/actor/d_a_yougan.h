#ifndef D_A_YOUGAN_H
#define D_A_YOUGAN_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class yg_awa_data {
public:
        ~yg_awa_data() {}
public:
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ J3DModel* field_0x04;
    /* 0x08 */ mDoExt_bckAnm field_0x08;
    /* 0x18 */ mDoExt_btkAnm field_0x18;
    /* 0x2C */ cXyz field_0x2C;
    /* 0x38 */ cXyz field_0x38;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daYougan_c : public fopAc_ac_c {
public:
    BOOL _daYougan_draw();
    BOOL _daYougan_execute();
    BOOL _daYougan_isdelete();
    BOOL _daYougan_delete();
    BOOL useHeapInit();
    cPhs_State _daYougan_create();

    static char m_arcname[];
public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ yg_awa_data field_0x298[16];
};  // Size: 0x758

#endif /* D_A_YOUGAN_H */
