#ifndef D_A_SBOX_H
#define D_A_SBOX_H

#include "f_op/f_op_actor.h"

class daSbox_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char) {}
    void setFlag(unsigned short) {}

    void CreateHeap();
    void calcMtx();
    void shipMtx();
    void volmProc();
    void darkProc();
    void lightProc();
    void lightInit();
    void CreateInit();
    s32 create();
    void demoInitWait();
    void demoProcWait();
    void demoInitOpen();
    void demoProcOpen();
    void demoInitDelete();
    void demoProcDelete();
    void demoInitCom();
    void demoProcCom();
    void getNowEventAction();
    void demoProc();
    void actionWait();

public:
    /* Place member variables here */
};

#endif /* D_A_SBOX_H */
