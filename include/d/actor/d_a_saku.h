#ifndef D_A_SAKU_H
#define D_A_SAKU_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

class dCcD_SrcCyl;
class dBgW;

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
    int saku_draw_sub(int);
    BOOL mode_break_none(int);
    BOOL mode_break_fire(int);
    BOOL mode_break_throw_obj(int);
    BOOL RecreateHeap(int, int);
    BOOL CreateHeap(int, int);
    int GetDzbId(int);
    BOOL CreateDummyHeap(int);
    BOOL loadMoveBG(int, int, int);
    BOOL loadModel(int, int, int);
    BOOL burn();
    BOOL broken(int);
    BOOL changeCollision(int);
    void setMtx();
    void setMoveBGMtx();
    void checkCol();
    void setCol();
    BOOL MoveBGResist(int, int);
    BOOL setEffFire(int);
    BOOL setEffBreak(int);

    static const dCcD_SrcCyl m_cyl_src;
    static GXColor dust_color;
    static u8 m_smoke_alpha;
    static const char* m_arcname[3];
    static s32 m_alpha_start_time;
    static s32 m_saku_alpha_out_time;
    static s32 m_fade_time;
    static const s32 m_max_particle_timer;
    static const u8 m_start_alpha;
    static const u16 m_alpha_spd;
    static const f32 m_saku_height;
    static const dCcD_SrcCyl m_at_cyl_src;

public:
    /* 0x290 */ dPa_smokeEcallBack field_0x290[2];
    /* 0x2D0 */ dCcD_Stts mStts;
    /* 0x30C */ dCcD_Cyl field_0x30c[2][3];
    /* 0xA2C */ cXyz field_0xa2c[2][3];
    /* 0xA74 */ dCcD_Cyl field_0xa74[3];
    /* 0xE04 */ request_of_phase_process_class field_0xe04[2];
    /* 0xE14 */ JKRSolidHeap* m_heap[2][2];
    /* 0xE24 */ J3DModel* mpModel[2][2];
    /* 0xE34 */ dBgW* field_0xe34[2][2];
    /* 0xE44 */ dBgW* field_0xe44[2];
    /* 0xE4C */ Mtx field_0xe4c[2];
    /* 0xEAC */ s32 field_0xeac[2];
    /* 0xEB4 */ f32 field_0xeb4[2];
    /* 0xEBC */ s32 field_0xebc[2];
    /* 0xEC4 */ cXyz field_0xec4[2];
    /* 0xEDC */ u8 field_0xedc[2][2];
    /* 0xEE0 */ s32 field_0xee0[2];
    /* 0xEE8 */ s32 field_0xee8;
    /* 0xEEC */ s32 field_0xeec;
    /* 0xEF0 */ u8 field_0xef0[2];
    /* 0xEF2 */ u8 mSturdinessType;
    /* 0xEF3 */ u8 field_0xef3;
    /* 0xEF4 */ u8 field_0xef4;
    /* 0xEF5 */ u8 field_0xef5[0xEF8 - 0xEF5];
    /* 0xEF8 */ s32 field_0xef8[2];
    /* 0xF00 */ u32 mBottomHalfDestroyedSwitch;
    /* 0xF04 */ u32 mTopHalfDestroyedSwitch;
};

namespace daSaku_prm {
    inline u8 getType(daSaku_c* actor) {
        return fopAcM_GetParamBit(fopAcM_GetParam(actor), 4, 4);
    }

    inline u8 getSwitchNo(daSaku_c* actor) {
        return fopAcM_GetParamBit(fopAcM_GetParam(actor), 8, 8);
    }

    inline u8 getSwitchNo2(daSaku_c* actor) {
        return fopAcM_GetParamBit(fopAcM_GetParam(actor), 16, 8);
    }

    inline BOOL checkSaku2(daSaku_c* actor) {
        return fopAcM_GetParamBit(fopAcM_GetParam(actor), 0, 4) != 0;
    }
}

#endif /* D_A_SAKU_H */
