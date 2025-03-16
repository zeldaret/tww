#ifndef D_A_OBJ_CANON_H
#define D_A_OBJ_CANON_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daObj_Canon_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void modeProcInit(int) {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void setEffect(unsigned short);
    void checkTgHit();
    void attackCannon();
    void lockonCannon();
    void setAttention();
    void setCollision();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeAttackInit();
    void modeAttack();
    void modeDeleteInit();
    void modeDelete();
    void modeSwWaitInit();
    void modeSwWait();
    void modeAppearInit();
    void modeAppear();
    void modeProc(Proc_e, int);
    bool _execute();
    void debugDraw();
    bool _draw();
    void createInit();
    void getArg();
    s32 _create();
    bool _delete();

public:
    /* Place member variables here */
};

class daObj_Canon_HIO_c {
public:
    daObj_Canon_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_CANON_H */
