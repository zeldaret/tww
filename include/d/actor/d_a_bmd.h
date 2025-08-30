#ifndef D_A_BMD_H
#define D_A_BMD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

struct bmd_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2BC */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2C0 */ mDoExt_McaMorf* m2C0;
    /* 0x2C4 */ mDoExt_McaMorf* m2C4;
    /* 0x2C8 */ mDoExt_McaMorf* m2C8;
    /* 0x2CC */ J3DModel* m2CC;
    /* 0x2D0 */ J3DModel* m2D0;
    /* 0x2D4 */ mDoExt_brkAnm* m2D4;
    /* 0x2D8 */ f32 m2D8;
    /* 0x2DC */ s8 m2DC;
    /* 0x2DD */ u8 m2DD[0x2E0 - 0x2DD];
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ u8 m2EC[0x2FA - 0x2EC];
    /* 0x2FA */ s16 m2FA;
    /* 0x2FC */ u8 m2FC[0x2FE - 0x2FC];
    /* 0x2FE */ s16 m2FE;
    /* 0x300 */ s16 mMode;
    /* 0x302 */ s16 m302;
    /* 0x304 */ s16 m304;
    /* 0x306 */ s16 m306;
    /* 0x308 */ s16 m308[4];
    /* 0x310 */ s16 m310;
    /* 0x312 */ s16 m312;
    /* 0x314 */ s16 m314;
    /* 0x316 */ u8 m316[0x318 - 0x316];
    /* 0x318 */ cXyz m318;
    /* 0x324 */ f32 m324;
    /* 0x328 */ f32 m328;
    /* 0x32C */ u8 m32C[0x330 - 0x32C];
    /* 0x330 */ u8 m330;
    /* 0x331 */ s8 m331;
    /* 0x332 */ s8 m332;
    /* 0x333 */ u8 m333[0x334 - 0x333];
    /* 0x334 */ s16 m334;
    /* 0x336 */ s16 m336;
    /* 0x338 */ f32 m338;
    /* 0x33C */ dBgS_AcchCir mAcchCir;
    /* 0x37C */ dBgS_ObjAcch mAcch;
    /* 0x540 */ dCcD_Stts mStts;
    /* 0x57C */ dCcD_Sph mBodySph;
    /* 0x6A8 */ dCcD_Sph mCoreSph;
    /* 0x7D4 */ dCcD_Cyl mCoCyl;
    /* 0x904 */ s16 m904;
    /* 0x906 */ u8 m906[0x908 - 0x906];
    /* 0x908 */ f32 m908;
    /* 0x90C */ csXyz m90C[2];
    /* 0x918 */ s16 m918;
    /* 0x91A */ u8 m91A[0x91C - 0x91A];
    /* 0x91C */ f32 m91C;
    /* 0x920 */ f32 m920;
    /* 0x924 */ cXyz m924;
    /* 0x930 */ cXyz m930;
    /* 0x93C */ s16 m93C;
    /* 0x93E */ s16 m93E;
    /* 0x940 */ s16 m940;
    /* 0x942 */ s8 m942;
    /* 0x943 */ u8 m943[0x944 - 0x943];
    /* 0x944 */ Mtx m944[5];
    /* 0xA34 */ Mtx mA34;
    /* 0xA64 */ dBgW* pm_bgw[6];
    /* 0xA7C */ JPABaseEmitter* mA7C[3];
    /* 0xA88 */ s16 mA88[2];
    /* 0xA8C */ s16 mA8C;
    /* 0xA8E */ u8 mA8E[0xA90 - 0xA8E];
    /* 0xA90 */ dPa_smokeEcallBack mA90[7];
    /* 0xB70 */ u8 mB70;
    /* 0xB71 */ s8 mB71;
    /* 0xB72 */ s16 mB72;
    /* 0xB74 */ s16 mB74;
    /* 0xB76 */ s16 mB76;
    /* 0xB78 */ s16 mB78;
    /* 0xB7A */ u8 mB7A[0xB7C - 0xB7A];
    /* 0xB7C */ cXyz mB7C;
    /* 0xB88 */ cXyz mB88;
    /* 0xB94 */ s16 mB94;
    /* 0xB96 */ s16 mB96;
    /* 0xB98 */ u8 mB98[0xB9C - 0xB98];
    /* 0xB9C */ f32 mB9C;
    /* 0xBA0 */ f32 mBA0;
    /* 0xBA4 */ f32 mBA4;
    /* 0xBA8 */ f32 mBA8;
    /* 0xBAC */ WIND_INFLUENCE mWindInfluence;
    /* 0xBD8 */ f32 mBD8;
    /* 0xBDC */ f32 mBDC;
    /* 0xBE0 */ u8 mBE0;
    /* 0xBE1 */ u8 mBE1[0xBE4 - 0xBE1];
}; // Size: 0xBE4

#endif /* D_A_BMD_H */
