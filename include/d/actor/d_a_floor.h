#ifndef D_A_FLOOR_H
#define D_A_FLOOR_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"

class daFloor_c : public dBgS_MoveBgActor {
public:
    virtual BOOL Delete();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    cPhs_State _create();
    void set_mtx();
    void set_effect();
    virtual BOOL Draw();
    virtual BOOL Execute(Mtx**);

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ s32 mSwitchNo;
    /* 0x2D8 */ u8 field_0x2d8;
    /* 0x2D9 */ u8 field_0x2d9;
    /* 0x2DA */ u8 field_0x2da;
    /* 0x2DB */ u8 field_0x2db;
    /* 0x2DC */ dPa_smokeEcallBack mSmokeCallBack;

    static const char m_arcname[6];
};

#endif /* D_A_FLOOR_H */
