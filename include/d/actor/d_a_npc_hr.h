#ifndef D_A_NPC_HR_H
#define D_A_NPC_HR_H

#include "f_op/f_op_actor.h"

class daNpc_Wind_Eff : public fopAc_ac_c {
public:
    void init();
    void remove();
    void create(cXyz*);
    void end();
    void proc();
    void setspd();
    void move();

public:
    /* 0x00 */ int m00;
    /* 0x04 */ u8 m04[0x14 - 0x04];
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ cXyz mVel;
    /* 0x2C */ cXyz* m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ u8 m34;
    /* 0x35 */ u8 m35[0x38 - 0x35];
};

#endif /* D_A_NPC_HR_H */
