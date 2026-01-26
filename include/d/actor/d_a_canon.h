#ifndef D_A_CANON_H
#define D_A_CANON_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class dDlst_2DObject_c;
class dDlst_2DBattery_c;

class daCanon_c : public fopAc_ac_c {
    typedef void (daCanon_c::*Func)();

public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    bool checkProcess(Func func) { return m290 == func; }
    void getCanonPtr() {}
    void setProcess(Func func) { m290 = func; }

    void set_mtx();
    void bul_set_mtx(cXyz*);
    cXyz getGridPos(int, int);
    cXyz getBulEndPos(short, short);
    BOOL createCheck(int, int, int);
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
    BOOL CreateHeap();
    void GameInfo2DDraw();
    
    static daCanon_c* canon_p;
    static const char M_arcname[];

public:
    /* 0x290 */ Func m290;
    /* 0x29C */ dCcD_Stts mStts1;
    /* 0x2D8 */ dCcD_Cyl mCyl1;
    /* 0x408 */ dCcD_Stts mStts2;
    /* 0x444 */ dCcD_Cyl mCyl2;
    /* 0x574 */ request_of_phase_process_class mPhase;
    /* 0x57C */ J3DModel* mpModel1;
    /* 0x580 */ J3DModel* mpModel2;
    /* 0x584 */ dDlst_2DObject_c* m584[10];
    /* 0x5AC */ dDlst_2DObject_c* m5AC[5];
    /* 0x5C0 */ dDlst_2DBattery_c* m5C0;
    /* 0x5C4 */ Mtx m5C4;
    /* 0x5F4 */ u8 m5F4[10];
    /* 0x600 */ fpc_ProcID m600[5];
    /* 0x614 */ cXyz m614;
    /* 0x620 */ cXyz m620;
    /* 0x62C */ cXyz m62C;
    /* 0x638 */ f32 m638;
    /* 0x63C */ cXyz m63C;
    /* 0x648 */ csXyz m648;
    /* 0x64E */ s16 m64E;
    /* 0x650 */ s16 m650;
    /* 0x652 */ s16 m652;
    /* 0x654 */ s16 m654;
    /* 0x656 */ s16 m656;
    /* 0x658 */ u8 field_658[0x65A - 0x658];
    /* 0x65A */ s16 m65A;
    /* 0x65C */ s16 m65C;
    /* 0x65E */ s16 m65E;
    /* 0x660 */ s16 m660;
    /* 0x662 */ u8 field_662[0x664 - 0x662];
    /* 0x664 */ bool m664;
}; // size = 0x668

#endif /* D_A_CANON_H */
