#ifndef D_A_MACHINE_H
#define D_A_MACHINE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_ext.h"
#include "d/actor/d_a_windmill.h"
#include "d/d_path.h"

class daMachine_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    void path_move();
    void set_next_pnt();
    daWindMill_c* search_wind_mill();
    f32 set_speed();
    cPhs_State _create();
    daMachine_c();
    void set_mtx();
    bool _execute();
    void attack();
    void set_cube();
    void set_body();
    void set_at();
    bool _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2d8 */ dCcD_Sph mSph;
    /* 0x404 */ dCcD_Sph field_0x404[3];
    /* 0x788 */ dCcD_Sph field_0x788;
    /* 0x8b4 */ dBgS_Acch field_0x84b;
    /* 0xa78 */ dBgS_AcchCir field_0xa78;
    /* 0xab8 */ dCcD_GObjInf field_0xab8;

    /* 0xbb0 */ u8 field_0xbb0[0xbd0 - 0xbb0]; //Filler

    /* 0xbd0 */ cM3dGCps field_0xbd0;
    /* 0xbf0 */ cM3dGSph field_0xbf0;
    /* 0xc04 */ mDoExt_bckAnm field_0xc04;
    /* 0xc14 */ u8 field_0xc14;
    /* 0xc15 */ s8 field_0xc15;
    /* 0xc16 */ s8 field_0xc16;
    /* 0xc17 */ s8 field_0xc17;
    /* 0xc18 */ dPath* field_0xc18;
    /* 0xc1c */ cXyz field_0xc1c;
    /* 0xc28 */ cXyz field_0xc28;

    /* 0xc34 */ u8 field_0xc34[0xc3c - 0xc34]; //Filler

    /* 0xc3c */ Mtx field_0xc3c;
    /* 0xc6c */ cXyz field_0xc6c;
    /* 0xc78 */ u8 field_0xc78;

    /* 0xC79 */ u8 field_0xC79[0xC94 - 0xC79]; //Filler
};  // Size: 0xc94

#endif /* D_A_MACHINE_H */
