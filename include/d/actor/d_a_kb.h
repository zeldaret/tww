#ifndef D_A_KB_H
#define D_A_KB_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;
class J3DTexNoAnm;
class J3DMaterialTable;

class kb_class : public fopAc_ac_c {
public:
    void taura_pos_set(cXyz pos) {
        m450 = pos;
        m408 = 1;
    }

public:
    /* 0x290 */ dKy_tevstr_c mTevStr;
    /* 0x340 */ dKy_tevstr_c m340;
    /* 0x3F0 */ u32 mShadowId;
    /* 0x3F4 */ request_of_phase_process_class mPhs;
    /* 0x3FC */ mDoExt_McaMorf* mpMorf;
    /* 0x400 */ u8 mShapeType;
    /* 0x401 */ u8 m401;
    /* 0x402 */ u8 mbCanBeBigPig;
    /* 0x403 */ u8 m403;
    /* 0x404 */ u8 m404;
    /* 0x405 */ u8 m405;
    /* 0x406 */ u8 m406;
    /* 0x407 */ u8 m407;
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409;
    /* 0x40A */ u8 m40A;
    /* 0x40B */ u8 m40B;
    /* 0x40C */ dPath* mpPath;
    /* 0x410 */ u8 m410[0x41D - 0x410];
    /* 0x41D */ u8 m41D;
    /* 0x41E */ s16 m41E;
    /* 0x420 */ s16 m420;
    /* 0x422 */ s16 m422;
    /* 0x424 */ s16 m424;
    /* 0x426 */ s16 m426[8];
    /* 0x436 */ s16 m436;
    /* 0x438 */ s16 m438;
    /* 0x43A */ s16 m43A;
    /* 0x42C */ u8 m43C[0x440 - 0x43C];
    /* 0x440 */ s16 m440;
    /* 0x442 */ s16 m442;
    /* 0x444 */ s16 m444;
    /* 0x446 */ s16 m446;
    /* 0x448 */ s16 m448;
    /* 0x44A */ s16 m44A;
    /* 0x44C */ s16 m44C;
    /* 0x44E */ s16 m44E;
    /* 0x450 */ cXyz m450;
    /* 0x45C */ cXyz m45C;
    /* 0x468 */ cXyz field_0x468[2];
    /* 0x480 */ cXyz field_0x480[2];
    /* 0x498 */ cXyz field_0x498;
    /* 0x4A4 */ cXyz m4A4;
    /* 0x4B0 */ f32 m4B0;
    /* 0x4B4 */ f32 m4B4;
    /* 0x4B8 */ f32 m4B8;
    /* 0x4BC */ f32 m4BC;
    /* 0x4C0 */ f32 m4C0;
    /* 0x4C4 */ f32 m4C4;
    /* 0x4C8 */ f32 m4C8;
    /* 0x4CC */ f32 m4CC;
    /* 0x4D0 */ u8 m4D0[0x4D4 - 0x4D0];
    /* 0x4D4 */ f32 m4D4;
    /* 0x4D8 */ fpc_ProcID m4D8;
    /* 0x4DC */ cXyz m4DC;
    /* 0x4E8 */ cXyz m4E8;
    /* 0x4F4 */ csXyz m4F4;
    /* 0x4FA */ csXyz m4FA;
    /* 0x500 */ J3DAnmTexPattern* m500;
    /* 0x504 */ J3DTexNoAnm* mpTexNoAnm;
    /* 0x508 */ u8 m508;
    /* 0x509 */ u8 m509;
    /* 0x50A */ u8 m50A;
    /* 0x50C */ int m50C;
    /* 0x510 */ u8 m510[0x514 - 0x510];
    /* 0x514 */ cXyz m514;
    /* 0x520 */ cXyz m520;
    /* 0x52C */ u8 m52C[0x53C - 0x52C];
    /* 0x53C */ f32 m53C;
    /* 0x540 */ dPa_rippleEcallBack m540;
    /* 0x554 */ dPa_smokeEcallBack m554;
    /* 0x574 */ dPa_smokeEcallBack m574;
    /* 0x594 */ dPa_followEcallBack m594;
    /* 0x5A8 */ dPa_followEcallBack m5A8[2];
    /* 0x5D0 */ f32 m5D0;
    /* 0x5D4 */ cXyz m5D4[2];
    /* 0x5EC */ csXyz m5EC[2];
    /* 0x5F8 */ J3DMaterialTable* mpMaterialTable;
    /* 0x5FC */ dBgS_AcchCir mAcchCir;
    /* 0x63C */ dBgS_ObjAcch mAcch;
    /* 0x800 */ dCcD_Stts mStts;
    /* 0x83C */ dCcD_Sph mSph;
    /* 0x968 */ dCcD_Sph m968;
};

#endif /* D_A_KB_H */
