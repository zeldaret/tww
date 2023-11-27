#ifndef D_A_OBJ_PFALL_H
#define D_A_OBJ_PFALL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_McaMorf;

class daObj_Pfall_c : public fopAc_ac_c {
public:
    void setAnm();
    void set_mtx();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    BOOL _delete();
    void cutProc();
    void cutWaitStart(int);
    void cutWaitProc(int);
    void cutOpenStart(int);
    void cutOpenProc(int);
    void cutHikuStart(int);
    void cutHikuProc(int);
    void mode_wait_init();
    void mode_wait();
    void mode_event_init();
    void mode_event();
    void mode_proc_call();
    BOOL _execute();
    void nz_draw();
    BOOL _draw();

public:
    /* 0x290 */ void* m290;
    /* 0x294 */ cXyz m294[10];
    /* 0x30C */ cXyz m30C[10];
    /* 0x384 */ cXyz m384[2];
    /* 0x39C */ void* m39C;
    /* 0x3A0 */ void* m3A0;
    /* 0x3A4 */ void* m3A4;
    /* 0x3A8 */ void* m3A8;
    /* 0x3AC */ void* m3AC;
    /* 0x3B0 */ void* m3B0;
    /* 0x3B4 */ void* m3B4;
    /* 0x3B8 */ u8 m3B8[0x3BC - 0x3B8];
    /* 0x3BC */ request_of_phase_process_class mPhsPfall;
    /* 0x3C4 */ J3DModel* m3C4;
    /* 0x3C8 */ dBgW* m3C8;
    /* 0x3CC */ Mtx m3CC;
    /* 0x3FC */ J3DModel* m3FC;
    /* 0x400 */ dBgW* m400;
    /* 0x404 */ Mtx m404;
    /* 0x434 */ J3DModel* m434;
    /* 0x438 */ u8 m438[0x43C - 0x438];
    /* 0x43C */ mDoExt_McaMorf* m43C;
    /* 0x440 */ u8 m440[0x444 - 0x440];
    /* 0x444 */ void* vtbl;
    /* 0x448 */ u8 m448[0x481 - 0x448];
    /* 0x481 */ u8 mState;
    /* 0x482 */ u8 m482[0x484 - 0x482];
};

#endif /* D_A_OBJ_PFALL_H */
