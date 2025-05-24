#ifndef D_A_WINDMILL_H
#define D_A_WINDMILL_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class dBgW;

class daWindMill_c : public fopAc_ac_c {
public:
    void getMaxRotSpeed() const {}
    void getRotSpeed() const {}
    void getType() const {}

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    void search_wind();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void hane_move();
    void set_at();
    void set_co();
    bool _draw();
    
    static const s16 m_max_rot_speed[];
    static const char* m_arcname[];

public:
    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ J3DModel* mpModel;
    /* 0x029C */ dCcD_Stts mStts;
    /* 0x02D8 */ dCcD_Sph mSph[9];
    /* 0x06D4 */ dCcD_Cps mCps[4];
    /* 0x1244 */ f32 m1244[28];
    /* 0x12B4 */ dBgW* mpBgW;
    /* 0x12B8 */ Mtx mMtx;
    /* 0x12E8 */ dCcD_Cyl mCyl;
    /* 0x1418 */ u8 mType;
    /* 0x141A */ s16 mAngle[3];
    /* 0x1420 */ u32 mWindTagId;
};

#endif /* D_A_WINDMILL_H */
