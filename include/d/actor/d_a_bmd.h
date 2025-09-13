#ifndef D_A_BMD_H
#define D_A_BMD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class bmd_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
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
    /* 0x2DC */ u8 m2DC;
    /* 0x2DD */ u8 m2DD[0x2E0 - 0x2DD];
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ u8 m2EC[0x2FE - 0x2EC];
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
    /* 0x324 */ u32 m324;
    /* 0x328 */ f32 m328;
    /* 0x32C */ u8 m32C[0x330 - 0x32C];
    /* 0x330 */ u8 m330;
    /* 0x331 */ s8 m331;
    /* 0x332 */ s8 m332;
    /* 0x333 */ u8 m333[0x334 - 0x333];
    /* 0x334 */ s16 m334;
    /* 0x336 */ s16 m336;
    /* 0x338 */ u8 m338[0x33C - 0x338];
    /* 0x33C */ dBgS_AcchCir mAcchCir;
    /* 0x37C */ dBgS_Acch mAcch;
    /* 0x540 */ dCcD_Stts mStts;
    /* 0x57C */ dCcD_Sph mBodySph;
    /* 0x6A8 */ dCcD_Sph mCoreSph;
    /* 0x7D4 */ dCcD_Cyl mCoCyl;
    /* 0x904 */ s16 m904;
    /* 0x906 */ u8 m906[0x908 - 0x906];
    /* 0x908 */ f32 m908;
    /* 0x90C */ u8 m90C[0x90E - 0x90C];
    /* 0x90E */ s16 m90E;
    /* 0x910 */ u8 m910[0x91C - 0x910];
    /* 0x91C */ f32 m91C;
    /* 0x920 */ f32 m920;
    /* 0x924 */ cXyz m924;
    /* 0x930 */ cXyz m930;
    /* 0x93C */ s16 m93C;
    /* 0x93E */ s16 m93E;
    /* 0x940 */ s16 m940;
    /* 0x942 */ u8 m942[0x944 - 0x942];
    /* 0x944 */ Mtx m944[5];
    /* 0xA34 */ Mtx mA34;
    /* 0xA64 */ dBgW* mpBgW[6];
    /* 0xA7C */ u8 mA7C[0xA8A - 0xA7C];
    /* 0xA8A */ s16 mA8A;
    /* 0xA8C */ u8 mA8C[0xA90 - 0xA8C];
    /* 0xA90 */ dPa_smokeEcallBack mA90[7];
    /* 0xB70 */ u8 mB70;
    /* 0xB71 */ u8 mB71;
    /* 0xB72 */ s16 mB72;
    /* 0xB74 */ s16 mB74;
    /* 0xB76 */ s16 mB76;
    /* 0xB78 */ s16 mB78;
    /* 0xB7A */ u8 mB7A[0xB7C - 0xB7A];
    /* 0xB7C */ cXyz mB7C;
    /* 0xB88 */ cXyz mB88;
    /* 0xB94 */ u8 mB94[0xB9C - 0xB94];
    /* 0xB9C */ f32 mB9C;
    /* 0xBA0 */ u8 mBA0[0xBA8 - 0xBA0];
    /* 0xBA8 */ f32 mBA8;
    /* 0xBAC */ WIND_INFLUENCE mWindInfluence;
    /* 0xBD8 */ f32 mBD8;
    /* 0xBDC */ f32 mBDC;
    /* 0xBE0 */ u8 mBE0;
    /* 0xBE1 */ u8 mBE1[0xBE4 - 0xBE1];
};

class daBmd_HIO_c {
public:
    daBmd_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BMD_H */
