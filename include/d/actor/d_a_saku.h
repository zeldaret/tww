#ifndef D_A_SAKU_H
#define D_A_SAKU_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_cc_d.h"
#include "m_Do/m_Do_hostIO.h"

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
    int mode_break_throw_obj(int);
    void RecreateHeap(int, int);
    void CreateHeap(int, int);
    void GetDzbId(int);
    void CreateDummyHeap(int);
    void loadMoveBG(int, int, int);
    void loadModel(int, int, int);
    void burn();
    int broken(int);
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
    static const char* m_arcname[3];
    static const s32 m_alpha_start_time;
    static s32 m_fade_time;

    /* 0x290 */ dPa_smokeEcallBack field_0x290[2];
    /* 0x2D0 */ dCcD_Stts mStts;
    /* 0x30C */ dCcD_Cyl field_0x30C[3];
    /* 0x69C */ dCcD_Cyl field_0x69C[3];
    /* 0xA2C */ cXyz mPos[2][3];
    /* 0xA74 */ dCcD_Cyl field_0xA74[3];
    /* 0xE04 */ request_of_phase_process_class field_0xE04;
    /* 0xE0C */ request_of_phase_process_class field_0xE0C;
    /* 0xE14 */ JKRSolidHeap* mHeap[2][2];
    /* 0xE24 */ J3DModel* mModels[2][2];
    /* 0xE34 */ u8 field_0xE34[0xE4C - 0xE34];
    /* 0xE4C */ Mtx mMtx[2];
    /* 0xEAC */ s32 field_0xEAC[2];
    /* 0xEB4 */ f32 field_0xEB4[2];
    /* 0xEBC */ s32 field_0xEBC[2];
    /* 0xEC4 */ u8 field_0xEC4[0xEEC - 0xEC4];
    /* 0xEEC */ s32 field_0xEEC;
    /* 0xEF0 */ u8 field_0xEF0[2];
    /* 0xEF2 */ u8 mSturdinessType;
    /* 0xEF3 */ u8 field_0xEF3[0xEF8 - 0xEF3];
    /* 0xEF8 */ s32 field_0xEF8;
    /* 0xEFC */ s32 field_0xEFC;
    /* 0xF00 */ uint mBottomHalfDestroyedSwitch;
    /* 0xF04 */ uint mTopHalfDestroyedSwitch;
};  // Size: 0xF08

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
            field_0x13 = 0x69;
            field_0x14 = 0x5b;
            field_0x15 = 0x30;
            field_0x16 = 100;
        };

        virtual ~sakuHIO_c();

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
        /* 0x13 */ u8 field_0x13;
        /* 0x14 */ u8 field_0x14;
        /* 0x15 */ u8 field_0x15;
        /* 0x16 */ u8 field_0x16;
        /* 0x17 */ u8 field_0x17;
};  // Size: 0x18
#endif /* D_A_SAKU_H */
