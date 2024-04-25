#ifndef D_A_MOVIE_PLAYER_H
#define D_A_MOVIE_PLAYER_H

#include "f_op/f_op_actor.h"
#include "d/d_drawlist.h"

class daMP_c : public fopAc_ac_c {
public:
    void daMP_c_Get_arg_data();
    void daMP_c_Init();
    void daMP_c_Finish();
    void daMP_c_Main();
    void daMP_c_Draw();
    static int daMP_c_Callback_Init(fopAc_ac_c*);
    static int daMP_c_Callback_Finish(daMP_c*);
    static int daMP_c_Callback_Main(daMP_c*);
    static int daMP_c_Callback_Draw(daMP_c*);

public:
    /* 0x290 */ u32 (*mpCallBack1)();
    /* 0x294 */ u32 (*mpCallBack2)(f32);
};

class daMP_Dlst_base_c : public dDlst_base_c {
    void draw();
};

struct daMP_THPReadBuffer {
    
};

struct THPVideoInfo {
    
};

struct THPAudioInfo {
    
};

#endif /* D_A_MOVIE_PLAYER_H */
