#ifndef D_A_MACHINE_H
#define D_A_MACHINE_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_windmill.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_ext.h"

class dPath;

class daMachine_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    void path_move();
    void set_next_pnt();
    daWindMill_c* search_wind_mill();
    void set_speed();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void attack();
    void set_cube();
    void set_body();
    void set_at();
    bool _draw();

    static const char m_arcname[8];
public:
    daMachine_c();

    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Sph mCollider;
    /* 0x404 */ dCcD_Sph mColColliders[3];
    /* 0x788 */ dCcD_Sph mUnkCollider;
    /* 0x8B4 */ dBgS_ObjAcch mAcch;
    /* 0xA78 */ dBgS_AcchCir mAcchCir;
    /* 0xAB8 */ dCcD_GObjInf field_0xAB8;
    /* 0xBB0 */ u8 field_0xBB0[0xBD0 - 0xBB0];
    /* 0xBD0 */ cXyz mCubeCorner1;
    /* 0xBDC */ cXyz mCubeCorner2;
    /* 0xBE8 */ u8 field_0xBE8[0xBEC - 0xBE8];
    /* 0xBEC */ f32 field_0xBEC;
    /* 0xBF0 */ cM3dGSph field_0xBF0;
    /* 0xC04 */ mDoExt_bckAnm mBckAnm;
    /* 0xC14 */ u8 mPathId;
    /* 0xC15 */ s8 mCurrPathPoint;
    /* 0xC16 */ u8 mPathPointDir;
    /* 0xC17 */ u8 field_0xC17[0xC18 - 0xC17];
    /* 0xC18 */ dPath* mPath;
    /* 0xC1C */ cXyz mTargetPos;
    /* 0xC28 */ cXyz field_0xC28;
    /* 0xC34 */ u8 field_0xC34[0xC3C - 0xC34];
    /* 0xC3C */ Mtx mJointMatrix;
    /* 0xC6C */ u8 field_0xC6C[0xC78 - 0xC6C];
    /* 0xC78 */ u8 field_0xC78;
    /* 0xC79 */ u8 field_0xC79[0xC94 - 0xC79];
};

#endif /* D_A_MACHINE_H */
