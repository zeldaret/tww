#ifndef D_A_FGANON_H
#define D_A_FGANON_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;
class mDoExt_btkAnm;

class fganon_class : public fopAc_ac_c {
public:
    /* 0x290 */ f32 m290;
    /* 0x294 */ f32 m294;
    /* 0x298 */ f32 m298;
    /* 0x29C */ f32 m29C;
    /* 0x2A0 */ f32 m2A0;
    /* 0x2A4 */ f32 f2A4;
    /* 0x2A8 */ f32 f2A8;
    /* 0x2AC */ request_of_phase_process_class mPhs1;
    /* 0x2B4 */ request_of_phase_process_class mPhs2;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 mSwitchNo;
    /* 0x2BF */ u8 m2BF;
    /* 0x2C0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2C4 */ mDoExt_brkAnm* mpBrkAnm1;
    /* 0x2C8 */ J3DModel* NpcModel;
    /* 0x2CC */ mDoExt_brkAnm* mpBrkAnm2;
    /* 0x2D0 */ s8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2D4 - 0x2D1];
    /* 0x2D4 */ dKy_tevstr_c mTevStr;
    /* 0x384 */ s16 m384;
    /* 0x386 */ s16 m386;
    /* 0x388 */ s16 m388;
    /* 0x38A */ s16 m38A;
    /* 0x38C */ cXyz m38C;
    /* 0x398 */ f32 m398;
    /* 0x39C */ f32 m39C;
    /* 0x3A0 */ f32 m3A0;
    /* 0x3A4 */ u8 m3A4[0x3AE - 0x3A4];
    /* 0x3AE */ s16 m3AE;
    /* 0x3B0 */ f32 m3B0;
    /* 0x3B4 */ s16 m3B4;
    /* 0x3B6 */ s16 m3B6;
    /* 0x3B8 */ s16 m3B8;
    /* 0x3BA */ u8 m3BA[0x3BC - 0x3BA];
    /* 0x3BC */ f32 m3BC;
    /* 0x3C0 */ u8 m3C0[0x3C4 - 0x3C0];
    /* 0x3C4 */ JPABaseEmitter* mEmitters1[2];
    /* 0x3CC */ JPABaseEmitter* mEmitters2[4];
    /* 0x3DC */ u32 m3DC;
    /* 0x3E0 */ Vec m3E0;
    /* 0x3EC */ u8 m3EC[0x408 - 0x3EC];
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409[0x40C - 0x409];
    /* 0x40C */ dCcD_Sph mBallTgSph;
    /* 0x538 */ dCcD_Sph mBallAtSph;
    /* 0x664 */ u8 m664[0x671 - 0x664];
    /* 0x671 */ s8 m671;
    /* 0x672 */ u8 m672[0x674 - 0x672];
    /* 0x674 */ J3DModel* EnergySphereModel;
    /* 0x678 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x67C */ mDoExt_brkAnm* mpBrkAnm3;
    /* 0x680 */ u8 m680[0x68A - 0x680];
    /* 0x684 */ s8 m684;
    /* 0x685 */ s8 m685;
    /* 0x686 */ s8 m686;
    /* 0x687 */ u8 m687[0x68A - 0x687];
    /* 0x68A */ s8 m68A;
    /* 0x68B */ s8 m68B;
    /* 0x68C */ s8 m68C;
    /* 0x68D */ bool mbIsMaterialized; // Flag for PG's appearance state, set to `FALSE` when he disappears, `TRUE` when he appears
    /* 0x68E */ s8 m68E;
    /* 0x68F */ u8 m68F;
    /* 0x690 */ u8 m690;
    /* 0x691 */ u8 m691[0x6A2 - 0x691];
    /* 0x6A2 */ s16 m6A2;
    /* 0x6A4 */ u8 m6A4[0x6A6 - 0x6A4];
    /* 0x6A6 */ s16 m6A6;
    /* 0x6A8 */ u8 m6A8[0x6AC - 0x6A8];
    /* 0x6AC */ s8 m6AC;
    /* 0x6AD */ u8 m6AD[0x6B4 - 0x6AD];
    /* 0x6B4 */ fpc_ProcID mCapeID;
    /* 0x6B8 */ dBgS_AcchCir mAcchCir;
    /* 0x6F8 */ dBgS_Acch mAcch;
    /* 0x8BC */ dCcD_Stts mStts;
    /* 0x8F8 */ dCcD_Cyl mCyl;
    /* 0xA28 */ dCcD_Sph mWeponSph;
    /* 0xB54 */ u8 mB54[0xB88 - 0xB54];
    /* 0xB88 */ u8 mB88;
    /* 0xB89 */ s8 mB89;
    /* 0xB8A */ u8 mB8A;
    /* 0xB8B */ u8 mB8B;
};

class daFganon_HIO_c {
public:
    daFganon_HIO_c();
    virtual ~daFganon_HIO_c(){}

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
