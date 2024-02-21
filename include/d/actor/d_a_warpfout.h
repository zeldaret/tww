#ifndef D_A_WARPFOUT_H
#define D_A_WARPFOUT_H

#include "f_op/f_op_actor.h"

class daWarpfout_c : public fopAc_ac_c {
public:
    typedef void (daWarpfout_c::*EventActionInitFunc)(int evtStaffId);
    typedef BOOL (daWarpfout_c::*EventActionFunc)(int evtStaffId);

    inline BOOL _draw();

    bool _delete();
    void CreateInit();
    s32 _create();
    bool _execute();
    void checkOrder();
    void eventOrder();
    void demo_proc();
    void initWarp1(int);
    BOOL actWarp1(int);
    void initWarp2(int);
    BOOL actWarp2(int);
    void initWarp3(int);
    BOOL actWarp3(int);
    void initWarp4(int);
    BOOL actWarp4(int);
    void initEnd(int);
    BOOL actEnd(int);
    void set_effect_wind01(cXyz, short);
    csXyz get_effect_angle();

public:
    /* 0x290 */ int unk0;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mStaffId;
    /* 0x29C */ s16 unknownInitFlag;
};

#endif /* D_A_WARPFOUT_H */
