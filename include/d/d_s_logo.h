#ifndef D_S_LOGO_H
#define D_S_LOGO_H

#include "f_op/f_op_scene.h"

class dDlst_2D_c;

class dScnLogo_c : public scene_class {
public:
    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ dDlst_2D_c * nintendoImg;
    /* 0x1D0 */ dDlst_2D_c * dolbyImg;
    /* 0x1D4 */ dDlst_2D_c * progchoiceImg;
    /* 0x1D8 */ dDlst_2D_c * progyesImg;
    /* 0x1DC */ dDlst_2D_c * prognoImg;
    /* 0x1E0 */ dDlst_2D_c * progImg;
    /* 0x1E4 */ dDlst_2D_c * interImg;
    /* 0x1E8 */ u8 mAction;
    /* 0x1E9 */ u8 mInterFlag;
    /* 0x1EA */ u8 field_0x1ea;
    /* 0x1EB */ u8 field_0x1eb;
    /* 0x1EC */ u16 mTimer;
    /* 0x1EE */ u16 field_0x1ee;
    /* 0x1F0 */ u16 field_0x1f0;
    /* 0x1F2 */ u16 field_0x1f2;
    /* 0x1F4 */ u16 field_0x1f4;
    /* 0x1F8 */ void * field_0x1f8;
    /* 0x1FC */ u32 field_0x1fc;
};

#endif /* D_S_LOGO_H */
