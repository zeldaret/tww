#ifndef D_A_OBJ_TRAP_H
#define D_A_OBJ_TRAP_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class dPath;

class daObjTrap_c : public fopAc_ac_c {
public:
    void check_shine() const {}
    void start_shine() {}
    void stop_shine() {}

    void solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void set_co_pos();
    void get_ground();
    void circle_search();
    void set_move_info();
    void check_arrival();
    void check_wall();
    void check_block_target_pos(cXyz*);
    void check_block(cXyz);
    void set_vib_mode();
    void vibrate();
    void bound();
    void set_shine();
    void shine_move();
    bool _execute();
    bool _draw();

    static const char M_arcname[];

public:
    /* Place member variables here */
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2A8 */ request_of_phase_process_class mPhase;
    /* 0x2B0 */ dCcD_Stts mCcStts;
    /* 0x2EC */ dCcD_Cyl mCcCyl;
    /* 0x41C */ dBgS_ObjGndChk mGndChk;
    /* 0x470 */ f32 mGroundY;
    /* 0x474 */ dPath* mpPath;
    /* 0x478 */ cXyz mNextPathPos;
    /* 0x484 */ cXyz mPathPos;
    /* 0x490 */ cXyz mPathDirection;
    /* 0x49C */ cXyz mPathOffset;
    /* 0x4A8 */ cXyz mPathStep;
    /* 0x4B4 */ cXyz mPathTarget;
    /* 0x4C0 */ u8 mPad4C0[0x0C];
    /* 0x4CC */ f32 mPathLength;
    /* 0x4D0 */ u8 mPad4D0[0x0C];
    /* 0x4DC */ u8 mPathPoint;
    /* 0x4DD */ u8 mPathId;
    /* 0x4DE */ u8 mPathDirectionSign;
    /* 0x4DF */ u8 mPad4DF[2];
    /* 0x4E1 */ u8 mSpeedType;
    /* 0x4E2 */ u8 mPad4E2[2];
    /* 0x4E4 */ f32 mSpeed;
    /* 0x4E8 */ f32 mPathSpeed;
    /* 0x4EC */ cBgW *mpcBgW;
};

STATIC_ASSERT(sizeof(daObjTrap_c) == 0x4F0);

#endif /* D_A_OBJ_TRAP_H */
