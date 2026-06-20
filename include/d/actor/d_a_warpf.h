#ifndef D_A_WARPF_H
#define D_A_WARPF_H

#include "f_op/f_op_actor.h"

class dLevelSe_c;
class JPABaseEmitter;
class mDoExt_bckAnm;
class mDoExt_brkAnm;
class mDoExt_btkAnm;

class daWarpf_c : public fopAc_ac_c {
public:
    typedef void (daWarpf_c::*InitFunc)(int);
    typedef BOOL (daWarpf_c::*ActionFunc)(int);
    
    BOOL CreateHeap();
    bool _delete();
    BOOL checkEndDemo();
    void onEndDemo();
    cPhs_State CreateInit();
    cPhs_State _create();
    bool _execute();
    void eventOrder();
    void checkOrder();
    void demo_proc();
    void initWait(int);
    BOOL actWait(int);
    void initWarpStart(int);
    BOOL actWarpStart(int);
    void initWarpMode_1(int);
    BOOL actWarpMode_1(int);
    void initWarpMode_2(int);
    BOOL actWarpMode_2(int);
    void initWarpMode_3(int);
    BOOL actWarpMode_3(int);
    void initEndWait(int);
    BOOL actEndWait(int);
    BOOL check_warp_event();
    f32 get_distance();
    f32 get_earth_pos();
    void set_effect();
    void set_effect_wind00();
    csXyz get_angle_wind01();
    void anim_play();
    void setEndAnim();
    void set_se();
    void set_mtx();
    bool _draw();
    
    static const char* m_arcname[];
    static const f32 m_warp_size[];

public:
    /* 0x290 */ JPABaseEmitter* m290;
    /* 0x294 */ JPABaseEmitter* m294;
    /* 0x298 */ JPABaseEmitter* m298;
    /* 0x29C */ JPABaseEmitter* m29C;
    /* 0x2A0 */ request_of_phase_process_class mPhase;
    /* 0x2A8 */ J3DModel* m2A8;
    /* 0x2AC */ mDoExt_brkAnm* m2AC;
    /* 0x2B0 */ mDoExt_bckAnm* m2B0;
    /* 0x2B4 */ mDoExt_btkAnm* m2B4;
    /* 0x2B8 */ mDoExt_brkAnm* m2B8;
    /* 0x2BC */ mDoExt_brkAnm* m2BC;
    /* 0x2C0 */ J3DModel* m2C0;
    /* 0x2C4 */ int mStaffID;
    /* 0x2C8 */ int mWarpTimer;
    /* 0x2CC */ u8 m2CC[0x2D0 - 0x2CC];
    /* 0x2D0 */ s32 m2D0;
    /* 0x2D4 */ u8 m2D4[0x2D6 - 0x2D4];
    /* 0x2D6 */ s16 m2D6;
    /* 0x2D8 */ s32 m2D8;
    /* 0x2DC */ s32 mStageNo;
    /* 0x2E0 */ s32 m2E0;
    /* 0x2E4 */ s32 m2E4;
    /* 0x2E8 */ dLevelSe_c* m2E8;
    /* 0x2EC */ cXyz m2EC;
};  // Size: 0x2F8

#endif /* D_A_WARPF_H */
