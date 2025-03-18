#ifndef D_A_CANON_H
#define D_A_CANON_H

#include "f_op/f_op_actor.h"

class daCanon_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void checkProcess(void (daCanon_c::*)()) {}
    void getCanonPtr() {}
    void setProcess(void (daCanon_c::*)()) {}

    void set_mtx();
    void bul_set_mtx(cXyz*);
    void getGridPos(int, int);
    void getBulEndPos(short, short);
    void createCheck(int, int, int);
    void createTargetObj();
    void breakAllObj();
    void makeFireEffect(cXyz&, csXyz&, int);
    void wait_proc_init();
    void wait_proc();
    void game_start_proc_init();
    void game_start_proc();
    void game_proc_init();
    void game_proc();
    void fire_proc_init();
    void fire_proc();
    void pause_proc_init();
    void pause_proc();
    void end_proc_init();
    void end_proc();
    void PadMove();
    void CreateHeap();
    void GameInfo2DDraw();
    
    static daCanon_c* canon_p;

public:
    /* Place member variables here */
};

#endif /* D_A_CANON_H */
