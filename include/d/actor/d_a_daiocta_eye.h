#ifndef D_A_DAIOCTA_EYE_H
#define D_A_DAIOCTA_EYE_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daDaiocta_Eye_c : public fopAc_ac_c {
public:
    void rndRotEye() {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void _coHit(fopAc_ac_c*);
    void setMtx();
    void checkTgHit();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDeathInit();
    void modeDeath();
    void modeProcCall();
    BOOL _execute();
    BOOL _draw();
    void createInit();
    s32 _create();
    BOOL _delete();

public:
    /* Place member variables here */
};

#endif /* D_A_DAIOCTA_EYE_H */
