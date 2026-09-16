#ifndef D_A_SAKU_H
#define D_A_SAKU_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_cc_d.h"

class cCcD_Stts__vtbl;

class daSaku_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned char) {}
    void setFlag(unsigned char) {}

    inline cPhs_State _daSaku_create();
    inline BOOL _daSaku_delete();
    inline BOOL _daSaku_draw();
    inline BOOL _daSaku_execute();
    inline BOOL _daSaku_isdelete();

    void CreateInit();
    void saku_draw_sub(int);
    void mode_break_none(int);
    void mode_break_fire(int);
    void mode_break_throw_obj(int);
    void RecreateHeap(int, int);
    void CreateHeap(int, int);
    void GetDzbId(int);
    void CreateDummyHeap(int);
    void loadMoveBG(int, int, int);
    void loadModel(int, int, int);
    void burn();
    void broken(int);
    void changeCollision(int);
    void setMtx();
    void setMoveBGMtx();
    void checkCol();
    void setCol();
    void MoveBGResist(int, int);
    int setEffFire(int);
    void setEffBreak(int);

    static const dCcD_SrcCyl m_cyl_src;
    static u8 m_smoke_alpha;
    static f32 _m_saku_alpha_out_time;

    /* 0x290 */ dPa_smokeEcallBack field_0x290[2];
    /* 0x2D0 */ u8 field_0x2D0[0x2E8 - 0x2D0];
    /* 0x2E8 */ cCcD_Stts__vtbl* field_0x2E8;
    /* 0x2EC */ dCcD_GStts field_0x2EC;
    /* 0x30C */ dCcD_Cyl field_0x30C[6];
    /* 0xA2C */ cXyz field_0xA2C[6];
    /* 0xA74 */ dCcD_Cyl field_0xA74[3];
    /* 0xE04 */ request_of_phase_process_class field_0xE04;
    /* 0xE0C */ request_of_phase_process_class field_0xE0C;
    /* 0xE14 */ u8 field_0xE14[0xE24 - 0xE14];
    /* 0xE24 */ J3DModel* mModels0[2];
    /* 0xE2C */ J3DModel* mModels1[2];
    /* 0xE34 */ u8 field_0xE34[0xE4C - 0xE34];
    /* 0xE4C */ Mtx mMtx0;
    /* 0xE7C */ Mtx mMtx1;
    /* 0xEAC */ u8 field_0xEAC[0xEBC - 0xEAC];
    /* 0xEBC */ u32 field_0xEBC;
    /* 0xEC0 */ u32 field_0xEC0;
    /* 0xEC4 */ u8 field_0xEC4[0xEF2 - 0xEC4];
    /* 0xEF2 */ u8 mSturdinessType;
    /* 0xEF3 */ u8 field_0xEF3[0xEF8 - 0xEF3];
    /* 0xEF8 */ u32 field_0xEF8;
    /* 0xEFC */ s32 field_0xEFC;
    /* 0xF00 */ uint mBottomHalfDestroyedSwitch;
    /* 0xF04 */ uint mTopHalfDestroyedSwitch;
};  // Size: 0xF08

#endif /* D_A_SAKU_H */
