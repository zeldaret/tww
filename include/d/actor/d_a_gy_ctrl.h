#ifndef D_A_GY_CTRL_H
#define D_A_GY_CTRL_H

#include "f_op/f_op_actor.h"

class daGy_Ctrl_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void getMode() {}
    void isTargetPlayer() {}
    void isTargetPlayerShip() {}

    void searchNearActor(fopAc_ac_c*);
    void setTarget();
    void setPathTargetPos();
    void getWaterY(cXyz&);
    void lineCheck(cXyz*, cXyz*);
    void checkPath();
    void setPathPos();
    void modeProc(Proc_e, int);
    void modeSwWaitInit();
    void modeSwWait();
    void modeCreateInit();
    void modeCreate();
    void modeWaitInit();
    void modeWait();
    void modeHideInit();
    void modeHide();
    void deadCheckGy();
    BOOL _execute();
    BOOL _draw();
    void createInitNoArer();
    void createInit();
    void getParam(unsigned long, unsigned char, unsigned char);
    void getArg();
    void checkGyCtrlExist();
    s32 _create();
    BOOL _delete();

public:
    /* Place member variables here */
};

class daGy_Ctrl_HIO_c {
public:
    daGy_Ctrl_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_GY_CTRL_H */
