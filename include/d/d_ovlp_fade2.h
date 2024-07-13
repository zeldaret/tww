#ifndef D_OVLP_FADE2_H
#define D_OVLP_FADE2_H

#include "d/d_drawlist.h"
#include "f_op/f_op_overlap_mng.h"

class dOvlpFd2_dlst_c : public dDlst_base_c {
public:
    ~dOvlpFd2_dlst_c() {}
    void draw();

    inline void entry();
    inline MtxP getMtx() { return mtx; }

public:
    /* 0x04 */ Mtx mtx;
};

class dOvlpFd2_c : public overlap_task_class {
public:
    dOvlpFd2_c();
    inline void draw();
    void execFirstSnap();
    void execFadeOut();
    void execNextSnap();
    void execFadeIn();

    /* 0x0CC */ void (dOvlpFd2_c::*mProc)();
    /* 0x0D8 */ dDlst_snapShot_c dSnap_dlst;
    /* 0x0DC */ dOvlpFd2_dlst_c dOvlpFd2_dlst;
    /* 0x110 */ s16 field_0x110;
    /* 0x112 */ s16 field_0x112;
    /* 0x114 */ s16 rotZ;
    /* 0x118 */ f32 scale;
    /* 0x11C */ u8 mHasSnap;
    /* 0x11D */ s8 mTimer;
    /* 0x11E */ u8 field_0x11e;
};

#endif /* D_OVLP_FADE2_H */
