#ifndef D_A_TITLE_H
#define D_A_TITLE_H

#include "f_op/f_op_actor.h"

class daTitle_proc_c {
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
    BOOL draw();

    static void daTitle_Kirakira_Sound_flag_on();

    static bool daTitle_Kirakira_Sound_flag[];
};

class daTitle_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* Place member variables here */
};

#endif /* D_A_TITLE_H */
