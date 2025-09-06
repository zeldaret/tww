#ifndef D_A_BDK_H
#define D_A_BDK_H

#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

struct bdk_tail_s {
    /* 0x000 */ J3DModel* m000[0x9];
    /* 0x024 */ cXyz m024[0xA];
    /* 0x09C */ csXyz m09C[0xA];
    /* 0x0D8 */ cXyz m0D8[0xA];
    /* 0x150 */ cXyz m0150[0x2];
    /* 0x168 */ csXyz m0168;
    /* 0x170 */ cXyz m0170;
}; // Size: 0x17C

struct bdk_eff_s {
    /* 0x000 */ s8 m000;
    /* 0x001 */ s8 m001;
    /* 0x004 */ cXyz m004;
    /* 0x010 */ cXyz m010;
    /* 0x01C */ f32 m01C;
    /* 0x020 */ f32 m020;
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ csXyz m030;
    /* 0x036 */ csXyz m036;
    /* 0x03C */ s16 m03C;
    /* 0x03E */ s16 m03E;
    /* 0x040 */ s8 m040;
    /* 0x044 */ J3DModel* m044;
    /* 0x048 */ dCcD_Sph m048;
};  // Size:0x174

class bdk_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ u8 m2B4;
    /* 0x02B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x02BC */ J3DModel* mp2BC;
    /* 0x02C0 */ s32 m2C0;
    /* 0x02C4 */ s16 m2C4;
    /* 0x02C6 */ s16 mAction;
    /* 0x02C8 */ s16 mState;
    /* 0x02CA */ s16 m2CA;
    /* 0x02CC */ cXyz m2CC;
    /* 0x02D8 */ s16 m2D8;
    /* 0x02DC */ f32 m2DC;
    /* 0x02E0 */ f32 m2E0;
    /* 0x02E4 */ f32 m2E4;
    /* 0x02E8 */ f32 m2E8;
    /* 0x02EC */ s16 m2EC[5];
    /* 0x02F6 */ s16 m2F6;
    /* 0x02F8 */ s16 m2F8;
    /* 0x02FA */ s16 m2FA;
    /* 0x02FC */ u8 m2FC;
    /* 0x0300 */ bdk_tail_s m300[4];
    /* 0x08F0 */ J3DModel* mp8F0;
    /* 0x08F4 */ mDoExt_bvaAnm* bva;
    /* 0x08F8 */ u8 m8F8;
    /* 0x08FC */ J3DModel* m8FC[4];
    /* 0x090C */ s8 m90C[4];
    /* 0x0910 */ cXyz m910[4];
    /* 0x0940 */ cXyz m940[4];
    /* 0x0970 */ cXyz m970[4];
    /* 0x09A0 */ csXyz m9A0[4];
    /* 0x09B8 */ csXyz m9B8[4];
    /* 0x09D0 */ csXyz m9D0[4];
    /* 0x09E8 */ s8 m9E8[4];
    /* 0x09EC */ f32 m9EC[4];
    /* 0x09FC */ f32 m9FC[4];
    /* 0x0A0C */ s16 mA0C[4];
    /* 0x0A14 */ dCcD_Stts mA14;
    /* 0x0A50 */ dCcD_Sph mA50[4];
    /* 0x0F00 */ f32 mF00[4];
    /* 0x0F10 */ u8 mF10;
    /* 0x0F12 */ s16 mF12;
    /* 0x0F14 */ s16 mF14;
    /* 0x0F18 */ f32 mF18;
    /* 0x0F1C */ dBgS_AcchCir mAcchCir;
    /* 0x0F5C */ dBgS_ObjAcch mAcch;
    /* 0x1120 */ s16 m1120;
    /* 0x1122 */ s16 m1122;
    /* 0x1124 */ s16 m1124;
    /* 0x1126 */ s16 m1126;
    /* 0x1128 */ s16 m1128;
    /* 0x112A */ s16 m112A;
    /* 0x112C */ s16 m112C;
    /* 0x112E */ s16 m112E;
    /* 0x1130 */ s16 m1130;
    /* 0x1132 */ s16 m1132;
    /* 0x1134 */ s16 m1134;
    /* 0x1136 */ s16 m1136;
    /* 0x1138 */ s16 m1138;
    /* 0x113A */ s8 m113A;
    /* 0x113C */ f32 m113C;
    /* 0x1140 */ f32 m1140;
    /* 0x1144 */ cXyz m1144;
    /* 0x1150 */ cXyz m1150;
    /* 0x115C */ cXyz m115C;
    /* 0x1168 */ cXyz m1168;
    /* 0x1174 */ cXyz m1174[2];
    /* 0x118C */ dCcD_Stts mStts;
    /* 0x11C8 */ dCcD_Sph mHeadAtSph;
    /* 0x12F4 */ dCcD_Sph mHeadTgSph;
    /* 0x1420 */ dCcD_Sph mTosakaTgSph;
    /* 0x154C */ dCcD_Sph mBodyCCSph;
    /* 0x1678 */ dCcD_Sph mFootCCSph[2];
    /* 0x18D0 */ dCcD_Sph mWindAtSph[0xA];
    /* 0x2488 */ u8 m2488[0xA];
    /* 0x2494 */ cXyz m2494[0xA];
    /* 0x250C */ cXyz m250C[0xA];
    /* 0x2584 */ u8 m2584;
    /* 0x2585 */ u8 m2585;
    /* 0x2586 */ s8 m2586;
    /* 0x2588 */ s32 m2588;
    /* 0x258C */ s32 m258C;
    /* 0x2590 */ u8 m2590;
    /* 0x2591 */ u8 m2591;
    /* 0x2592 */ s8 m2592;
    /* 0x2593 */ s8 m2593;
    /* 0x2594 */ s8 m2594;
    /* 0x2598 */ fopAc_ac_c* mp2598;
    /* 0x259C */ u8 m259C[0x259E - 0x259C];
    /* 0x259E */ s16 m259E;
    /* 0x25A0 */ s16 m25A0;
    /* 0x25A2 */ s8 m25A2;
    /* 0x25A4 */ s16 m25A4;
    /* 0x25A6 */ s16 m25A6;
    /* 0x25A8 */ cXyz m25A8;
    /* 0x25B4 */ cXyz m25B4;
    /* 0x25C0 */ csXyz m25C0;
    /* 0x25C8 */ f32 m25C8;
    /* 0x25CC */ f32 m25CC;
    /* 0x25D0 */ f32 m25D0;
    /* 0x25D4 */ f32 m25D4;
    /* 0x25D8 */ s8 m25D8;
    /* 0x25DC */ cXyz m25DC;
    /* 0x25E8 */ cXyz m25E8;
    /* 0x25F4 */ cXyz m25F4;
    /* 0x2600 */ u8 m2600[0x2608-0x2600];
    /* 0x2608 */ f32 m2608;
    /* 0x260C */ cXyz m260C;
    /* 0x2618 */ s8 m2618;
    /* 0x2619 */ s8 m2619;
    /* 0x261A */ s8 m261A;
    /* 0x261C */ bdk_eff_s m261C[0x28];
    /* 0x603C */ dCcD_Stts m603C;
    /* 0x6078 */ s16 m6078[4];
    /* 0x6080 */ dPa_smokeEcallBack m6080[4];
    /* 0x6100 */ JPABaseEmitter* m6100[2];
    /* 0x6108 */ u8 m6108[0x6108-0x6100];
    /* 0x6110 */ dPa_smokeEcallBack m6110;
    /* 0x6130 */ dPa_smokeEcallBack m6130[4]; //FUTA SMOKE
    /* 0x61B0 */ dPa_followEcallBack m61B0;
    /* 0x61C4 */ dPa_followEcallBack m61C4[4];
    /* 0x6214 */ JPABaseEmitter* mp6214[4];
    /* 0x6224 */ dKy_tevstr_c m6224;
    /* 0x62D4 */ f32 m62D4;
    /* 0x62D8 */ J3DModel* mp62D8;
    /* 0x62DC */ Mtx m62DC;
    /* 0x630C */ dBgW* pm_bgw;
    /* 0x6310 */ J3DModel* mp6310[3]; //SHATTERMODEL
    /* 0x631C */ f32 m631C;
    /* 0x6320 */ f32 m6320;
    /* 0x6324 */ f32 m6324;
    /* 0x6328 */ u8 m6328[0x6320 - 0x631C];
    /* 0x632C */ Mtx m632C[3];
    /* 0x63BC */ dBgW* mp63BC[3];
    /* 0x63C8 */ JntHit_c* mp63C8;
}; // Size:0x63CC

class daBdk_HIO_c : public JORReflexible {
public:
    daBdk_HIO_c();
    virtual ~daBdk_HIO_c() {}
    void genMessage(JORMContext* ctx);
public:
    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 m005;
    /* 0x006 */ s16 m006;
    /* 0x008 */ f32 m008;
    /* 0x00C */ f32 m00C;
    /* 0x010 */ f32 m010;
    /* 0x014 */ u8 m014;
    /* 0x018 */ f32 m018;
    /* 0x01C */ f32 m01C;
    /* 0x020 */ f32 m020;
    /* 0x024 */ f32 m024;
    /* 0x028 */ s16 m028;
}; // Size: 0x2C

#endif /* D_A_BDK_H */
