#ifndef D_A_MOVIE_PLAYER_H
#define D_A_MOVIE_PLAYER_H

#include "f_op/f_op_actor.h"

class daMP_c : public fopAc_ac_c {
public:
    void daMP_c_Get_arg_data();
    void daMP_c_Init();
    void daMP_c_Finish();
    void daMP_c_Main();
    void daMP_c_Draw();
    void daMP_c_Callback_Init(fopAc_ac_c*);
    void daMP_c_Callback_Finish(daMP_c*);
    void daMP_c_Callback_Main(daMP_c*);
    void daMP_c_Callback_Draw(daMP_c*);

public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ int m294;
};

#endif /* D_A_MOVIE_PLAYER_H */
