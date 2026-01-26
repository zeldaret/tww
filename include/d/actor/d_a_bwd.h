#ifndef D_A_BWD_H
#define D_A_BWD_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct sita_s {
    /* 0x00 */ J3DModel* m00;
    /* 0x04 */ cXyz m04;
    /* 0x20 */ u8 m1C[0x14 - 0x10];
}; // Size: 0x14

struct bwd_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhaseBwd;
    /* 0x02B4 */ request_of_phase_process_class mPhaseBwds;
    /* 0x02BC */ u8 m02BC;
    /* 0x02BD */ u8 m02BD[0x02BF - 0x02BD];
    /* 0x02C0 */ mDoExt_McaMorf* m02C0;
    /* 0x02C4 */ mDoExt_brkAnm* m02C4;
    /* 0x02C8 */ f32 m02C8;
    /* 0x02CC */ J3DModel* m02CC;
    /* 0x02D0 */ u8 m02D0[0x02D4 - 0x02D0];
    /* 0x02D4 */ J3DModel* m02D4[20];
    /* 0x0324 */ J3DModel* m0324[20];
    /* 0x0374 */ mDoExt_brkAnm* m0374[20];
    /* 0x0374 */ f32 m03C4[20];
    /* 0x0414 */ s32 m0414;
    /* 0x0418 */ cXyz m0418[20];
    /* 0x0508 */ cXyz m0508[256];
    /* 0x1108 */ csXyz m1108[256];
    /* 0x1708 */ s32 m1708;
    /* 0x170C */ s32 m170C;
    /* 0x1710 */ s8 m1710;
    /* 0x1711 */ u8 m1711[0x1714 - 0x1711];
    /* 0x1714 */ dKy_tevstr_c m1714;
    /* 0x17C4 */ u8 m17C4;
    /* 0x17C5 */ u8 m17C5[0x17C8 - 0x17C5];
    /* 0x17C8 */ cXyz m17C8;
    /* 0x17D4 */ f32 m17D4;
    /* 0x17D8 */ s16 m17D8;
    /* 0x17DA */ u8 m17DA[0x17DC - 0x17DA];
    /* 0x17DC */ f32 m17DC;
    /* 0x17E0 */ f32 m17E0;
    /* 0x17E4 */ s8 m17E4[2];
    /* 0x17E6 */ s16 m17E6[2];
    /* 0x17EA */ u8 m17EA[0x17EC - 0x17EA];
    /* 0x17EC */ J3DModel* m17EC[2];
    /* 0x17F4 */ mDoExt_btkAnm* m17F4[2];
    /* 0x17FC */ Mtx m17FC[2];
    /* 0x185C */ dBgW* m185C[2];
    /* 0x1864 */ s8 m1864;
    /* 0x1865 */ s8 m1865;
    /* 0x1866 */ u8 m1866[0x1868 - 0x1866];
    /* 0x1868 */ J3DModel* m1868;
    /* 0x186C */ Mtx m186C;
    /* 0x189C */ dBgW* m189C;
    /* 0x18A0 */ cXyz m18A0;
    /* 0x18AC */ s16 m18AC;
    /* 0x18AE */ s16 m18AE;
    /* 0x18B0 */ s16 m18B0;
    /* 0x18B2 */ u8 m18B2[0x18B4 - 0x18B2];
    /* 0x18B4 */ cXyz m18B4;
    /* 0x18C0 */ u8 m18C0[0x18C4 - 0x18C0];
    /* 0x18C4 */ f32 m18C4;
    /* 0x18C8 */ f32 m18C8;
    /* 0x18CC */ s16 m18CC[2];
    /* 0x18D0 */ s16 m18D0;
    /* 0x18D2 */ u8 m18D2[0x18D6 - 0x18D2];
    /* 0x18D6 */ s16 m18D6;
    /* 0x18D8 */ u8 m18D8;
    /* 0x18D9 */ u8 m18D9[0x18DC - 0x18D9];
    /* 0x18DC */ f32 m18DC;
    /* 0x18E0 */ fpc_ProcID m18E0;
    /* 0x18E4 */ cXyz m18E4;
    /* 0x18F0 */ cXyz m18F0;
    /* 0x18FC */ s16 m18FC;
    /* 0x18FE */ s16 m18FE;
    /* 0x1900 */ s16 m1900;
    /* 0x1902 */ s16 m1902;
    /* 0x1904 */ s32 m1904;
    /* 0x1908 */ sita_s m1908[32];
    /* 0x1B88 */ cXyz m1B88;
    /* 0x1B94 */ cXyz m1B94;
    /* 0x1BA0 */ f32 m1BA0;
    /* 0x1BA4 */ f32 m1BA4;
    /* 0x1BA8 */ f32 m1BA8;
    /* 0x1BAC */ f32 m1BAC;
    /* 0x1BB0 */ s8 m1BB0;
    /* 0x1BB1 */ s8 m1BB1;
    /* 0x1BB2 */ s8 m1BB2;
    /* 0x1BB3 */ s8 m1BB3;
    /* 0x1BB4 */ s8 m1BB4;
    /* 0x1BB5 */ s8 m1BB5;
    /* 0x1BB6 */ s8 m1BB6;
    /* 0x1BB7 */ u8 m1BB7[0x1BB8 - 0x1BB7];
    /* 0x1BB8 */ f32 m1BB8;
    /* 0x1BBC */ fpc_ProcID m1BBC;
#if VERSION == VERSION_USA
    /* 0x1BC0 */ fpc_ProcID m1BC0;
#endif
    /* 0x1BC4 */ dCcD_Stts mCcD_Stts;
    /* 0x1C00 */ dCcD_Sph mDamageSpheres[19];
    /* 0x3244 */ dCcD_Sph mCcD_Sph;
    /* 0x3370 */ dCcD_Sph mCcD_Sph_Array5[5];
    /* 0x394C */ s8 m394C;
    /* 0x394D */ u8 m394D[0x3954 - 0x394D];
    /* 0x3954 */ cXyz m3954;
    /* 0x3960 */ s8 m3960;
    /* 0x3961 */ u8 m3961[0x3964 - 0x3961];
    /* 0x3964 */ JPABaseEmitter* m3964;
    /* 0x3968 */ JPABaseEmitter* m3968;
    /* 0x396C */ u8 m396C[0x3978 - 0x396C];
    /* 0x3978 */ dPa_smokeEcallBack m3978[10];
    /* 0x3AB8 */ dPa_followEcallBack m3AB8[2];
    /* 0x3AE0 */ s16 m3AE0[2];
    /* 0x3AE4 */ s16 m3AE4;
    /* 0x3AE6 */ s16 m3AE6;
    /* 0x3AE8 */ s16 m3AE8;
    /* 0x3AEA */ s16 m3AEA;
    /* 0x3AEC */ s16 m3AEC;
    /* 0x3AEE */ u8 m3AEE[0x3AF4 - 0x3AEE];
    /* 0x3AF4 */ dPa_followEcallBack m3AF4;
    /* 0x3B08 */ s8 m3B08[2];
    /* 0x3B0A */ u8 m3B0A[0x3B0C - 0x3B0A];
    /* 0x3B0C */ cXyz m3B0C[2];
    /* 0x3B24 */ mDoExt_McaMorf* m3B24[2];
    /* 0x3B34 */ mDoExt_btkAnm* m3B2C[2];
    /* 0x3B34 */ mDoExt_brkAnm* m3B34[2];
    /* 0x3B3C */ f32 m3B3C;
    /* 0x3B40 */ f32 m3B40;
    /* 0x3B44 */ f32 m3B44;
    /* 0x3B48 */ csXyz m3B48[2];
    /* 0x3B54 */ dPa_smokeEcallBack m3B54[6];
    /* 0x3C14 */ s8 m3C14;
    /* 0x3C15 */ s8 m3C15;
    /* 0x3C16 */ u8 m3C16[0x3C18 - 0x3C16];
    /* 0x3C18 */ f32 m3C18;
    /* 0x3C1C */ s16 m3C1C;
    /* 0x3C1E */ s16 m3C1E;
    /* 0x3C20 */ s16 m3C20;
    /* 0x3C22 */ s16 m3C22;
    /* 0x3C24 */ s8 m3C24;
    /* 0x3C25 */ u8 m3C25[0x3C28 - 0x3C25];
    /* 0x3C28 */ cXyz m3C28;
    /* 0x3C34 */ cXyz m3C34;
    /* 0x3C40 */ u8 m3C40[0x3C44 - 0x3C40];
    /* 0x3C44 */ f32 m3C44;
    /* 0x3C48 */ f32 m3C48;
    /* 0x3C4C */ f32 m3C4C;
    /* 0x3C50 */ s8 m3C50;
    /* 0x3C51 */ u8 m3C51;
    /* 0x3C52 */ u8 m3C52[0x3C54 - 0x3C52];
}; // Size: 0x3C54

#endif /* D_A_BWD_H */
