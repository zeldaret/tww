#ifndef D_OVLP_FADE2_H
#define D_OVLP_FADE2_H

#include "d/d_drawlist.h"
#include "f_op/f_op_overlap_mng.h"

class dOvlpFd2_dlst_c : public dDlst_base_c {
public:
    ~dOvlpFd2_dlst_c() {}
    void draw();
};

class dOvlpFd2_c : public overlap_task_class {
public:
    dOvlpFd2_c();
    void execFirstSnap();
    void execFadeOut();
    void execNextSnap();
    void execFadeIn();

    /* 0x0CC */ void (dOvlpFd2_c::*field_0xcc)();
    /* 0x0D8 */ dDlst_snapShot_c field_0xd8;
    /* 0x0DC */ dOvlpFd2_dlst_c field_0xdc;
    /* 0x0E0 */ u8 field_0xe0[0x11D - 0xE0];
    /* 0x11D */ u8 field_0x11d;
};

#endif /* D_OVLP_FADE2_H */
