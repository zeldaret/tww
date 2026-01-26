#ifndef D_A_HIMO3_H
#define D_A_HIMO3_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_path.h"
#include "d/d_particle.h"

struct himo3_s {
    /* 0x00 */ cXyz m00;
    /* 0x0C */ cXyz m0C;
}; // size = 0x18

struct h3_ga_s {
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ cXyz mPos;
    /* 0x04 */ cXyz m10;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ u8 m20[0x24 - 0x20];
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ s16 m2C;
    /* 0x2E */ u8 m2E;
    /* 0x2F */ u8 m2F;
}; // size = 0x30

class himo3_class : public fopAc_ac_c {
public:
    void getPlayerMoveLength() {}

    void setActorHang(cXyz, short);

public:
    /* 0x0290 */ request_of_phase_process_class mPhase;
    /* 0x0298 */ u8 m0298;
    /* 0x0299 */ u8 m0299;
    /* 0x029A */ u8 m029A;
    /* 0x029B */ s8 m029B;
    /* 0x029C */ s8 m029C;
    /* 0x029D */ s8 m029D;
    /* 0x02A0 */ dPath* ppd;
    /* 0x02A4 */ s8 m02A4;
    /* 0x02A8 */ cXyz m02A8;
    /* 0x02B4 */ s16 m02B4[3];
    /* 0x02BA */ s16 m02BA;
    /* 0x02BC */ s16 m02BC;
    /* 0x02BE */ u8 m02BE;
    /* 0x02C0 */ himo3_s m02C0[200];
    /* 0x1580 */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x15BC */ u8 m15BC[0x15C0 - 0x15BC];
    /* 0x15C0 */ s32 m15C0;
    /* 0x15C4 */ cXyz m15C4;
    /* 0x15D0 */ f32 m15D0;
    /* 0x15D4 */ f32 m15D4;
    /* 0x15D8 */ f32 m15D8;
    /* 0x15DC */ f32 m15DC;
    /* 0x15E0 */ f32 m15E0;
    /* 0x15E4 */ f32 m15E4;
    /* 0x15E8 */ f32 m15E8;
    /* 0x15EC */ u8 m15EC[0x15F0 - 0x15EC];
    /* 0x15F0 */ f32 m15F0;
    /* 0x15F4 */ f32 m15F4;
    /* 0x15F8 */ s16 m15F8;
    /* 0x15FA */ s16 m15FA;
    /* 0x15FC */ f32 m15FC;
    /* 0x1600 */ LIGHT_INFLUENCE m1600;
    /* 0x1620 */ f32 m1620;
    /* 0x1624 */ cXyz m1624;
    /* 0x1630 */ cXyz m1630;
    /* 0x163C */ dBgS_AcchCir mAcchCir;
    /* 0x167C */ dBgS_ObjAcch mAcch;
    /* 0x1840 */ Mtx m1840;
    /* 0x1870 */ f32 m1870;
    /* 0x1874 */ u8 m1874[0x187C - 0x1878];
    /* 0x1878 */ f32 m1878;
    /* 0x187C */ f32 m187C;
    /* 0x1880 */ J3DModel* mpModel;
    /* 0x1884 */ dCcD_Stts mStts;
    /* 0x18C0 */ dCcD_Sph mSphs[5];
    /* 0x1E9C */ dCcD_Sph mSph;
    /* 0x1FC8 */ dCcD_Cyl mCyl;
    /* 0x20F8 */ f32 m20F8;
#if VERSION == VERSION_DEMO
    /* 0x20FC */ JPABaseEmitter* demo_m20FC;
#endif
    /* 0x20FC */ dPa_followEcallBack m20FC;
    /* 0x2110 */ u8 m2110;
    /* 0x2111 */ u8 m2111;
    /* 0x2114 */ h3_ga_s m2114[1];
    /* 0x2144 */ J3DLightObj m2144;
    /* 0x21B8 */ u8 m2178[0x21F4 - 0x21B8];
    /* 0x21F4 */ cXyz m21F4;
    /* 0x2200 */ s16 m2200;
}; // size = 0x2204

#endif /* D_A_HIMO3_H */
