#ifndef D_A_FGANON_H
#define D_A_FGANON_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"

class camera_class;
class mant_class;
class daBoko_c;
class daPy_py_c;
class mDoExt_McaMorf;
class mDoExt_brkAnm;
class mDoExt_btkAnm;

class fganon_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs1;
    /* 0x2B4 */ request_of_phase_process_class mPhs2;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 mSwitchNo;
    /* 0x2BF */ u8 m2BF;
    /* 0x2C0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2C4 */ mDoExt_brkAnm* mpBrkAnm1;
    /* 0x2C8 */ J3DModel* mpKenModel;
    /* 0x2CC */ mDoExt_brkAnm* mpBrkAnm2;
    /* 0x2D0 */ s8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2D4 - 0x2D1];
    /* 0x2D4 */ dKy_tevstr_c mKenTevStr;
    /* 0x384 */ s16 m384;
    /* 0x386 */ s16 mAction;
    /* 0x388 */ s16 mMode;
    /* 0x38A */ s16 m38A;
    /* 0x38C */ cXyz m38C;
    /* 0x398 */ s16 m398;
    /* 0x39A */ s16 m39A;
    /* 0x39C */ f32 m39C;
    /* 0x3A0 */ f32 m3A0;
    /* 0x3A4 */ s16 m3A4[5];
    /* 0x3AE */ s16 m3AE;
    /* 0x3B0 */ f32 m3B0;
    /* 0x3B4 */ s16 m3B4;
    /* 0x3B6 */ s16 m3B6;
    /* 0x3B8 */ s16 m3B8;
    /* 0x3BA */ u8 m3BA[0x3BC - 0x3BA];
    /* 0x3BC */ f32 m3BC;
    /* 0x3C0 */ f32 m3C0;
    /* 0x3C4 */ JPABaseEmitter* mEmitters1[2];
    /* 0x3CC */ JPABaseEmitter* mEmitters2[2];
    /* 0x3D4 */ JPABaseEmitter* mEmitters3[2];
    /* 0x3DC */ u32 m3DC;
    /* 0x3E0 */ cXyz m3E0;
    /* 0x3EC */ cXyz m3EC;
    /* 0x3F8 */ cXyz m3F8;
    /* 0x404 */ f32 m404;
    /* 0x408 */ s8 m408;
    /* 0x409 */ s8 m409;
    /* 0x40A */ s8 m40A;
    /* 0x40B */ s8 m40B;
    /* 0x40C */ dCcD_Sph mBallTgSph;
    /* 0x538 */ dCcD_Sph mBallAtSph;
    /* 0x664 */ cXyz m664;
    /* 0x670 */ s8 m670;
    /* 0x671 */ s8 m671;
    /* 0x672 */ u8 m672;
    /* 0x673 */ s8 m673;
    /* 0x674 */ J3DModel* mpEnergySphereModel;
    /* 0x678 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x67C */ mDoExt_brkAnm* mpBrkAnm3;
    /* 0x680 */ f32 m680;
    /* 0x684 */ s8 m684;
    /* 0x685 */ s8 m685;
    /* 0x686 */ s8 m686;
    /* 0x687 */ s8 m687;
    /* 0x688 */ s8 m688;
    /* 0x689 */ s8 m689;
    /* 0x68A */ s8 m68A;
    /* 0x68B */ s8 m68B;
    /* 0x68C */ s8 m68C;
    /* 0x68D */ s8 mbIsMaterialized; // Flag for PG's appearance state, set to `FALSE` when he disappears, `TRUE` when he appears
    /* 0x68E */ s8 m68E;
    /* 0x68F */ u8 m68F;
    /* 0x690 */ s8 m690;
    /* 0x691 */ u8 m691[0x694 - 0x691];
    /* 0x694 */ f32 m694;
    /* 0x698 */ f32 m698;
    /* 0x69C */ f32 m69C;
    /* 0x6A0 */ s16 m6A0;
    /* 0x6A2 */ s16 m6A2;
    /* 0x6A4 */ s16 m6A4;
    /* 0x6A6 */ s16 m6A6;
    /* 0x6A8 */ u32 m6A8;
    /* 0x6AC */ s8 m6AC;
    /* 0x6AD */ u8 m6AD[0x6B0 - 0x6AD];
    /* 0x6B0 */ fpc_ProcID mBokoID;
    /* 0x6B4 */ fpc_ProcID mCapeID;
    /* 0x6B8 */ dBgS_AcchCir mAcchCir;
    /* 0x6F8 */ dBgS_ObjAcch mAcch;
    /* 0x8BC */ dCcD_Stts mStts;
    /* 0x8F8 */ dCcD_Cyl mCyl;
    /* 0xA28 */ dCcD_Sph mWeponSph;
    /* 0xB54 */ s16 mB54;
    /* 0xB56 */ s16 mB56;
    /* 0xB58 */ u8 mB58[0xB5C - 0xB58];
    /* 0xB5C */ cXyz mB5C;
    /* 0xB68 */ cXyz mB68;
    /* 0xB74 */ s16 mB74;
    /* 0xB76 */ s16 mB76;
    /* 0xB78 */ u8 mB78[0xB80 - 0xB78];
    /* 0xB80 */ f32 mB80;
    /* 0xB84 */ f32 mB84;
    /* 0xB88 */ u8 mB88;
    /* 0xB89 */ s8 mB89;
    /* 0xB8A */ u8 mB8A;
    /* 0xB8B */ u8 mB8B;
};

class daFganon_HIO_c {
public:
    daFganon_HIO_c();
    virtual ~daFganon_HIO_c() {}

public:
    /* 0x00 */ // vtable  
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ s16 m40;
    /* 0x42 */ s16 m42;
    /* 0x44 */ f32 m44;
    /* 0x4A */ s16 m48;
};

#endif /* D_A_FGANON_H */
