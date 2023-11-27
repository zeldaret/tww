#ifndef D_A_KB_H
#define D_A_KB_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"

class mDoExt_McaMorf;
class J3DTexNoAnm;
class J3DMaterialTable;

class kb_class : public fopAc_ac_c {
public:
    void taura_pos_set(cXyz) {}

public:
    /* 0x290 */ dKy_tevstr_c mTevStr;
    /* 0x340 */ u8 m340[0x3F4 - 0x340];
    /* 0x3F4 */ request_of_phase_process_class mPhs;
    /* 0x3FC */ mDoExt_McaMorf* mpMorf;
    /* 0x400 */ u8 mShapeType;
    /* 0x401 */ u8 m401;
    /* 0x402 */ u8 mbCanBeBigPig;
    /* 0x403 */ u8 m403[0x408 - 0x403];
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409[0x40C - 0x409];
    /* 0x40C */ dPath* mpPath;
    /* 0x410 */ u8 m410[0x41D - 0x410];
    /* 0x41D */ u8 m41D;
    /* 0x41E */ u8 m41E[0x420 - 0x41E];
    /* 0x420 */ s16 m420;
    /* 0x422 */ s16 m422;
    /* 0x424 */ s16 m424;
    /* 0x426 */ s16 m426;
    /* 0x428 */ s16 m428;
    /* 0x42A */ s16 m42A;
    /* 0x42C */ u8 m42C[0x446 - 0x42C];
    /* 0x446 */ s16 m446;
    /* 0x448 */ u8 m448[0x45C - 0x448];
    /* 0x45C */ f32 m45C;
    /* 0x460 */ u8 m460[0x464 - 0x460];
    /* 0x464 */ f32 m464;
    /* 0x468 */ u8 m468[0x4A4 - 0x468];
    /* 0x4A4 */ cXyz m4A4;
    /* 0x4B0 */ u8 m4B0[0x4B4 - 0x4B0];
    /* 0x4B4 */ f32 m4B4;
    /* 0x4B8 */ f32 m4B8;
    /* 0x4BC */ u8 m4BC[0x4C4 - 0x4BC];
    /* 0x4C4 */ f32 m4C4;
    /* 0x4C8 */ u8 m4C8[0x4CC - 0x4C8];
    /* 0x4CC */ f32 m4CC;
    /* 0x4D0 */ u8 m4D0[0x4D4 - 0x4D0];
    /* 0x4D4 */ f32 m4D4;
    /* 0x4D8 */ u8 m4D8[0x4E8 - 0x4D8];
    /* 0x4E8 */ cXyz m4E8;
    /* 0x4F4 */ u8 m4F4[0x504 - 0x4F4];
    /* 0x504 */ J3DTexNoAnm* mpTexNoAnm;
    /* 0x508 */ u8 m508[0x50C - 0x508];
    /* 0x50C */ int m50C;
    /* 0x510 */ u8 m510[0x5F8 - 0x510];
    /* 0x5F8 */ J3DMaterialTable* mpMaterialTable;
    /* 0x5FC */ dBgS_AcchCir mAcchCir;
    /* 0x63C */ dBgS_Acch mAcch;
    /* 0x800 */ dCcD_Stts mStts;
    /* 0x83C */ dCcD_Sph mSph;
    /* 0x968 */ u8 m968[0xA94 - 0x968];
};

#endif /* D_A_KB_H */
