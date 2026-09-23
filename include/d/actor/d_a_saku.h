#ifndef D_A_SAKU_H
#define D_A_SAKU_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

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

    static dCcD_SrcCyl m_cyl_src;
    static GXColor dust_color;
    static s32 m_fade_time;
    static s32 m_saku_alpha_out_time;
    static const s32 m_alpha_start_time;
    static u8 m_smoke_alpha;

    static const char* m_arcname[3];
    static const dCcD_SrcCyl m_at_cyl_src;
    static const f32 m_saku_height;
    static const u16 m_alpha_spd;
    static const s32 m_max_particle_timer;
    static const u8 m_start_alpha;

    /* 0x290 */ dPa_smokeEcallBack field_0x290[2];
    /* 0x2D0 */ dCcD_Stts mStts;
    /* 0x30C */ dCcD_Cyl field_0x30C[2][3];
    /* 0xA2C */ cXyz mPos[2][3];
    /* 0xA74 */ dCcD_Cyl field_0xA74[3];
    /* 0xE04 */ request_of_phase_process_class field_0xE04;
    /* 0xE0C */ request_of_phase_process_class field_0xE0C;
    /* 0xE14 */ JKRSolidHeap* m_heap[2][2];
    /* 0xE24 */ J3DModel* mModels[2][2];
    /* 0xE34 */ dBgW* field_0xE34[2][2];
    /* 0xE44 */ dBgW* field_0xE44[2];
    /* 0xE4C */ Mtx mMtx[2];
    /* 0xEAC */ u32 field_0xEAC[2];
    /* 0xEB4 */ f32 field_0xEB4[2];
    /* 0xEBC */ s32 mParticleTimers[2];
    /* 0xEC4 */ cXyz field_0xEC4[2];
    /* 0xEDC */ u8 field_0xEDC[2][2];
    /* 0xEE0 */ s32 field_0xEE0[3];
    /* 0xEEC */ s32 field_0xEEC;
    /* 0xEF0 */ u8 field_0xEF0[2];
    /* 0xEF2 */ u8 mType;
    /* 0xEF3 */ u8 field_0xEF3[0xEF4 - 0xEF3];
    /* 0xEF4 */ u8 field_0xEF4;
    /* 0xEF5 */ u8 field_0xEF5[0xEF8 - 0xEF5];
    /* 0xEF8 */ s32 field_0xEF8[2];
    /* 0xF00 */ u32 mBottomHalfDestroyedSwitch;
    /* 0xF04 */ u32 mTopHalfDestroyedSwitch;
}; // Size: 0xF08

class sakuHIO_c : public JORReflexible {
public:
    sakuHIO_c() {
        field_0x04 = -1;
        field_0x06 = 0x46;
        field_0x08 = 0x46;
        field_0x0A = 0x41;
        field_0x0C = 7;
        field_0x0E = 1;
        field_0x0F = 1;
        field_0x10 = 5;
        field_0x12 = 0xB4;
        dustColor.r = 0x69;
        dustColor.g = 0x5b;
        dustColor.b = 0x30;
        dustColor.a = 100;
    };

    virtual ~sakuHIO_c() {};

    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ u8 field_0x0E;
    /* 0x0F */ u8 field_0x0F;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ GXColor dustColor;
    /* 0x17 */ u8 field_0x17;
}; // Size: 0x18

namespace daSaku_prm {
inline u8 getType(daSaku_c* ac) {
    return (fopAcM_GetParam(ac) >> 4) & 0xf;
}
inline u8 getSwitchNo(daSaku_c* ac) {
    return (fopAcM_GetParam(ac) >> 8) & 0xFF;
}
inline u8 getSwitchNo2(daSaku_c* ac) {
    return (fopAcM_GetParam(ac) >> 16) & 0xFF;
}

inline u8 checkSaku2(daSaku_c* ac) {
    return fopAcM_GetParam(ac) & 0xf;
}
}; // namespace daSaku_prm
#endif /* D_A_SAKU_H */
