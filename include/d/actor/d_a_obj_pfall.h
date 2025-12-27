#ifndef D_A_OBJ_PFALL_H
#define D_A_OBJ_PFALL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"

class mDoExt_McaMorf;

class daObj_Pfall_c : public fopAc_ac_c {
public:
    void setAnm();
    void set_mtx();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _delete();
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
    bool _execute();
    void nz_draw();
    bool _draw();
    


public:
    /* 0x290 */ void* field_0x290;
    /* 0x294 */ cXyz field_0x294[10];
    /* 0x30C */ cXyz field_0x30C[10];
    /* 0x384 */ cXyz field_0x384[2];
    /* 0x39C */ u8 field_0x39C[0x3A8 - 0x39C];
    /* 0x3A8 */ int field_0x3A8;
    /* 0x3AC */ int mTimer;
    /* 0x3B0 */ int field_0x3B0;
    /* 0x3B4 */ s16 field_0x3B4;
    /* 0x3B6 */ u8 field_0x3B6[0x3B8 - 0x3B6];
    /* 0x3B8 */ int field_0x3B8;
    /* 0x3BC */ request_of_phase_process_class mPhsPfall;
    /* 0x3C4 */ J3DModel* field_0x3C4;
    /* 0x3C8 */ dBgW* mpBgW;
    /* 0x3CC */ Mtx field_0x3CC;
    /* 0x3FC */ J3DModel* field_0x3FC;
    /* 0x400 */ dBgW* mpBgW2;
    /* 0x404 */ Mtx field_0x404;
    /* 0x434 */ J3DModel* mpHimoModel;
    /* 0x438 */ f32 field_0x438;
    /* 0x43C */ mDoExt_McaMorf* mpMorf;
    /* 0x440 */ u8 field_0x440[0x444 - 0x440];
    /* 0x444 */ mDoExt_3DlineMat1_c field_0x444;
    /* 0x480 */ s8 mBckIdx;
    /* 0x481 */ s8 field_0x481;
    /* 0x482 */ s8 mOldAnmPrmIdx;
    /* 0x483 */ bool field_0x483;
};  // Size: 0x484

class daObj_PfallHIO_c {
public:
    daObj_PfallHIO_c();
    virtual ~daObj_PfallHIO_c() {mNo = -1;}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ bool field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ s16 field_0x0C;
};

#endif /* D_A_OBJ_PFALL_H */
