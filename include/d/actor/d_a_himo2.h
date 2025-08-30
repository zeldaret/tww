#ifndef D_A_HIMO2_H
#define D_A_HIMO2_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

struct himo2_s {
    /* 0x00 */ u8 m00[0x0C - 0x00];
    /* 0x0C */ f32 m0C;
    /* 0x10 */ cXyz m10;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ u8 m20[0x24 - 0x20];
}; // Size: 0x24

class himo2_class : public fopAc_ac_c {
public:
    BOOL setTargetPos(cXyz*, float*, float*);

public:
    /* 0x0290 */ u8 m0290[0x029C - 0x0290];
    /* 0x029C */ s16 m029C;
    /* 0x029E */ s16 m029E;
    /* 0x02A0 */ s16 m02A0;
    /* 0x02A2 */ s16 m02A2;
    /* 0x02A2 */ s16 m02A4;
    /* 0x02A6 */ u8 m02A6[0x02B4 - 0x02A6];
    /* 0x02B4 */ cXyz m02B4;
    /* 0x02C0 */ u8 m02C0[0x02CC - 0x02C0];
    /* 0x02CC */ s32 m02CC;
    /* 0x02D0 */ u8 m02D0[0x02D8 - 0x02D0];
    /* 0x02D8 */ u32 m02D8;
    /* 0x02DC */ s32 m02DC;
    /* 0x02E0 */ s8 m02E0;
    /* 0x02E1 */ u8 m02E1[0x02E4 - 0x02E1];
    /* 0x02E4 */ f32 m02E4;
    /* 0x02E8 */ u8 m02E8[0x02EC - 0x02E8];
    /* 0x02EC */ cXyz m02EC[2];
    /* 0x0304 */ u8 m0304[0x0308 - 0x0304];
    /* 0x0308 */ s16 m0308;
    /* 0x030A */ u8 m030A[0x0310 - 0x030A];
    /* 0x0310 */ himo2_s m0310[100];
    /* 0x1120 */ himo2_s m1120[100];
    /* 0x1F30 */ mDoExt_3DlineMat1_c m1F30;
    /* 0x1F6C */ s32 m1F6C;
    /* 0x1F70 */ f32 m1F70;
    /* 0x1F74 */ u8 m1F74[0x1F84 - 0x1F74];
    /* 0x1F84 */ cXyz m1F84;
    /* 0x1F90 */ s16 m1F90;
    /* 0x1F92 */ s16 m1F92;
    /* 0x1F94 */ s16 m1F94;
    /* 0x1F96 */ u8 m1F96[0x1F98 - 0x1F96];
    /* 0x1F98 */ mDoExt_3DlineMat1_c m1F98;
    /* 0x1FD4 */ f32 m1FD4;
    /* 0x1FD8 */ mDoExt_3DlineMat1_c m1FD8;
    /* 0x2014 */ dCcD_Stts m2014;
    /* 0x2050 */ dCcD_Sph m2050;
    /* 0x217C */ fopAc_ac_c* m217C;
    /* 0x2180 */ fpc_ProcID m2180;
    /* 0x2184 */ f32 m2184;
    /* 0x2188 */ f32 m2188;
    /* 0x218C */ fopAc_ac_c* m218C;
    /* 0x2190 */ u8 m2190[0x24AC - 0x2190];
    /* 0x24AC */ u8 m24AC;
    /* 0x24AD */ u8 m24AD[0x24B0 - 0x24AD];
    /* 0x24B0 */ J3DModel* m24B0;
    /* 0x24B4 */ f32 m24B4;
    /* 0x24B8 */ f32 m24B8;
    /* 0x24BC */ s32 m24BC;
    /* 0x24C0 */ s32 m24C0;
    /* 0x24C4 */ f32 m24C4;
    /* 0x24C8 */ s16 m24C8;
    /* 0x24CA */ s16 m24CA;
    /* 0x24CC */ cXyz m24CC;
    /* 0x24D8 */ s8 m24D8;
    /* 0x24D9 */ s8 m24D9;
    /* 0x24DA */ u8 m24DA[0x24DC - 0x24DA];
    /* 0x24DC */ cXyz m24DC;
    /* 0x24E8 */ cXyz m24E8;
    /* 0x24F4 */ f32 m24F4;
    /* 0x24F8 */ f32 m24F8;
    /* 0x24FC */ f32 m24FC;
    /* 0x2500 */ f32 m2500;
    /* 0x2504 */ cXyz m2504;
    /* 0x2510 */ s16 m2510;
    /* 0x2512 */ s16 m2512;
    /* 0x2514 */ f32 m2514;
    /* 0x2518 */ f32 m2518;
    /* 0x251C */ s8 m251C;
    /* 0x251C */ u8 m251D[0x2520 - 0x251D];
    /* 0x2520 */ f32 m2520;
    /* 0x2524 */ cXyz m2524;
    /* 0x2530 */ f32 m2530;
    /* 0x2534 */ dBgS_AcchCir m2534;
    /* 0x2574 */ dBgS_ObjAcch m2574;
}; // Size: 0x2738

#endif /* D_A_HIMO2_H */
