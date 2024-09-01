#ifndef D_A_OBJ_VGNFD_H
#define D_A_OBJ_VGNFD_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DModel;
class dBgW;

class daObjVgnfd_c : public fopAc_ac_c {
public:
    void check_boss(int) {}
    BOOL check_ev_init(int); // weak but not inlined?
    void on_door_ev(int) {}

    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_bdl_brk(int);
    BOOL create_heap();
    s32 _create();
    bool _delete();
    s32 get_start_demo_idx();
    BOOL check_fin();
    void on_fin();
    void init_mtx();
    void set_timer();
    bool _execute();
    bool _draw();

public:
    static const s32 M_bdl_table[];
    static const s32 M_brk_table[];
    static const s32 M_door_bdl_table[];
    static const u16 M_door_ev_table[];
    static const u16 M_boss_ev_table[];
    static const char M_arcname[];

public:
    /* 0x290 */ J3DModel* mModel[5];
    /* 0x2A4 */ J3DModel* mModel2[2];
    /* 0x2AC */ mDoExt_btkAnm mBtkAnm;
    /* 0x2C0 */ request_of_phase_process_class mPhs;
    /* 0x2C8 */ mDoExt_brkAnm mBrkAnm[5];
    /* 0x340 */ dPa_smokeEcallBack mSmoke;
    /* 0x360 */ s32 mStaffId;
    /* 0x364 */ s32 mTimer;
    /* 0x368 */ s32 M_demo_idx;
    /* 0x36C */ s32 mCurModel;
    /* 0x370 */ s16 mEventIdx;
    /* 0x372 */ u8 mState;
    /* 0x373 */ bool mInit;
    /* 0x374 */ dBgW* M_bgw;
};

#endif /* D_A_OBJ_VGNFD_H */
