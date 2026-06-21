#ifndef D_A_OBJ_STAIR_H
#define D_A_OBJ_STAIR_H

#include "d/d_bg_s_movebg_actor.h"

class daObj_Stair_c : public dBgS_MoveBgActor {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    inline void set_mtx();

    virtual BOOL CreateHeap();
    virtual BOOL Create();
    virtual BOOL Execute(Mtx**);
    virtual BOOL Draw();
    virtual BOOL Delete();

    static const char M_arcname[6];

public:
    /* 0x2C8 */ cXyz field_0x2C8;
    /* 0x2D4 */ cXyz field_0x2D4;
    /* 0x2E0 */ int field_0x2E0;
    /* 0x2E4 */ int field_0x2E4;
    /* 0x2E8 */ f32 field_0x2E8;
    /* 0x2EC */ f32 field_0x2EC;
    /* 0x2F0 */ request_of_phase_process_class mPhs;
    /* 0x2F8 */ J3DModel* mpModel;
    /* 0x2FC */ Mtx field_0x2FC;
    /* 0x32C */ dCcD_Stts mStts;
    /* 0x368 */ dCcD_Cps mCps;
    /* 0x4A0 */ Quaternion field_0x4A0;
    /* 0x4B0 */ Quaternion field_0x4B0;
    /* 0x4C0 */ cXyz field_0x4C0;
};  // Size: 0x4CC

#endif /* D_A_OBJ_STAIR_H */
