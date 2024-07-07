#ifndef D_A_TITLE_H
#define D_A_TITLE_H

#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor.h"

class daTitle_proc_c : public dDlst_base_c {
public:
    daTitle_proc_c();
    ~daTitle_proc_c();
    void proc_init3D();
    void proc_init2D();
    void setEnterMode();
    void set_mtx();
    void calc_2d_alpha();
    void proc_execute();
    void model_draw();
    void proc_draw();
    void draw();

    static void daTitle_Kirakira_Sound_flag_on();

    static bool daTitle_Kirakira_Sound_flag;
};

class daTitle_c : public fopAc_ac_c {
public:
    ~daTitle_c() {
        if (mpTitleProc != NULL) {
            delete mpTitleProc;
        }
        dComIfG_resDelete(&mPhs, "TlogoE");
    }

    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ daTitle_proc_c* mpTitleProc;
    /* 0x29C */ u8 m29C;
};

#endif /* D_A_TITLE_H */
