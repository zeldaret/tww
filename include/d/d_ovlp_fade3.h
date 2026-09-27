#ifndef D_OVLP_FADE3_H
#define D_OVLP_FADE3_H

#include "d/d_drawlist.h"
#include "f_op/f_op_overlap_mng.h"

class dOvlpFd3_c : public overlap_task_class {
public:
    dOvlpFd3_c();
    BOOL execFirstSnap();
    BOOL execFadeOut();

    inline BOOL draw();
    inline BOOL execute();

    typedef BOOL (dOvlpFd3_c::*executeFn)();
    void setExecute(executeFn i_func) { mExecuteFn = i_func; }

    /* 0x0CC */ executeFn mExecuteFn;
    /* 0x0D8 */ dDlst_snapShot_c mSnapshot_c;
    /* 0x0DC */ dDlst_2DT2_c field_0xdc;
    /* 0x120 */ dDlst_2DT2_c field_0x120;
    /* 0x164 */ u8 field_0x164;
};

#endif /* D_OVLP_FADE3_H */
