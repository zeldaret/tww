#ifndef D_A_GND_H
#define D_A_GND_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct gnd_ke_s {
    /* 0x000 */ cXyz m000[20];
    /* 0x0F0 */ cXyz m0F0[20];
}; // Size: 0x1E0

struct gnd_class {
    enum Move_Type_e {
        Move_Type_MOVE0_e = 0,
        Move_Type_ATTACK0_e = 1,
        Move_Type_ATTACK1_e = 2,
        Move_Type_ATTACK2_e = 3,
        Move_Type_ATTACKPZ_e = 4,
        Move_Type_ATTACK_LAST_e = 5,
        Move_Type_DEFENCE0_e = 10,
        Move_Type_DAMAGE_e = 11,
        Move_Type_DEMOWAIT_e = 20,
        Move_Type_YAWAIT_e = 21,
        Move_Type_FINISH_e = 30,
    };

    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ u8 m02B4;
    /* 0x02B5 */ u8 m02B5[0x02B8 - 0x02B5];
    /* 0x02B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x02BC */ mDoExt_btkAnm* m02BC;
    /* 0x02C0 */ mDoExt_brkAnm* m02C0;
    /* 0x02C4 */ mDoExt_btpAnm* m02C4;
    /* 0x02C8 */ u32 m02C8;
    /* 0x02CC */ s16 m02CC;
    /* 0x02CE */ s16 mMoveType;
    /* 0x02D0 */ s16 mAnmType;
    /* 0x02D2 */ u8 m02D2[0x02D4 - 0x02D2];
    /* 0x02D4 */ cXyz m02D4;
    /* 0x02E0 */ cXyz m02E0;
    /* 0x02EC */ u8 m02EC[0x02F0 - 0x02EC];
    /* 0x02F0 */ f32 m02F0;
    /* 0x02F4 */ f32 m02F4;
    /* 0x02F8 */ f32 m02F8;
    /* 0x02FC */ u8 m02FC[0x0302 - 0x02FC];
    /* 0x0302 */ s16 m0302[2]; // 0 = mDamageTimer
    /* 0x0306 */ u8 m0306[0x30C - 0x0306];
    /* 0x030C */ s16 mDamageInvulnerabilityTimer1;
    /* 0x030E */ s16 mDamageInvulnerabilityTimer2;
    /* 0x0310 */ f32 m0310;
    /* 0x0314 */ s16 m0314;
    /* 0x0316 */ u8 m0316[0x0318 - 0x0316];
    /* 0x0318 */ s16 m0318;
    /* 0x031A */ s16 m031A;
    /* 0x031C */ s8 m031C;
    /* 0x031D */ u8 m031D[0x0320 - 0x031D];
    /* 0x0320 */ dKy_tevstr_c m0320;
    /* 0x03D0 */ u8 m03A6[0x03D4 - 0x03D0];
    /* 0x03D4 */ s8 m03D4;
    /* 0x03D5 */ s8 mBlockHitCount;
    /* 0x03D6 */ s8 mBlockHit;
    /* 0x03D7 */ s8 m03D7;
    /* 0x03D8 */ s8 m03D8;
    /* 0x03D9 */ s8 m03D9;
    /* 0x03DA */ s8 m03DA;
    /* 0x03DB */ s8 m03DB;
    /* 0x03DC */ s8 m03DC;
    /* 0x03DD */ u8 m03DD[0x03DE - 0x03DD];
    /* 0x03DE */ s16 m03DE;
    /* 0x03E0 */ f32 m03E0;
    /* 0x03E4 */ gnd_ke_s m03E4[4];
    /* 0x0B64 */ mDoExt_3DlineMat0_c m0B64;
    /* 0x0B80 */ dBgS_AcchCir mAcchCir;
    /* 0x0BC0 */ dBgS_ObjAcch mAcch;
    /* 0x0D84 */ dCcD_Stts mStts;
    /* 0x0DC0 */ dCcD_Cyl mDamageCyl;
    /* 0x0EF0 */ dCcD_Sph mHeadSph;
    /* 0x101C */ dCcD_Sph mChestSph;
    /* 0x1148 */ dCcD_Sph mSwordSphs[2];
    /* 0x13A0 */ cXyz m13A0[2];
    /* 0x13B8 */ s8 m13B8[2];
    /* 0x13B8 */ u8 m13BA[0x13BC - 0x13BA];
    /* 0x13BC */ s32 m13BC[2];
    /* 0x13C4 */ f32 m13C4[2];
    /* 0x13CC */ s8 m13CC[2];
    /* 0x13CE */ s8 m13CE;
    /* 0x13CF */ u8 mNextParryOpeningType;
    /* 0x13D0 */ s8 mParryTimer;
    /* 0x13D1 */ s8 m13D1;
    /* 0x13D2 */ u8 m13D2[0x13D4 - 0x13D2];
    /* 0x13D4 */ JPABaseEmitter* mpAttackEffEmitter[5];
    /* 0x13E8 */ u8 m13E8[0x13EC - 0x13E8];
    /* 0x13EC */ JPABaseEmitter* m13EC;
    /* 0x13F0 */ JPABaseEmitter* m13F0[2];
    /* 0x13F8 */ s16 m13F8[2];
    /* 0x13FC */ u8 m13FC[0x1426 - 0x13FC];
    /* 0x1426 */ s16 m1426;
    /* 0x1428 */ f32 m1428;
    /* 0x142C */ s16 m142C;
    /* 0x142E */ s16 m142E;
    /* 0x1430 */ JPABaseEmitter* m1430[2];
    /* 0x1438 */ u8 m1438[0x14A8 - 0x1438];
    /* 0x14A8 */ cXyz m14A8[15];
    /* 0x155C */ s16 m155C;
    /* 0x155E */ s16 m155E;
    /* 0x1560 */ s16 m1560;
    /* 0x1562 */ s8 m1562;
    /* 0x1563 */ u8 m1563[0x1564 - 0x1563];
    /* 0x1564 */ cXyz m1564;
    /* 0x1570 */ cXyz m1570;
    /* 0x157C */ cXyz m157C;
    /* 0x1588 */ cXyz m1588;
    /* 0x1594 */ u8 m1594[0x15A0 - 0x1594];
    /* 0x15A0 */ f32 m15A0;
    /* 0x15A4 */ f32 m15A4;
    /* 0x15A8 */ f32 m15A8;
    /* 0x15AC */ f32 m15AC;
    /* 0x15B0 */ u8 m15B0;
    /* 0x15B0 */ u8 m15B1[0x15B4 - 0x15B1];
    /* 0x15B4 */ dPa_rippleEcallBack m15B4;
    /* 0x15C8 */ cXyz m15C8[2];
    /* 0x15E0 */ u8 m15E0;
    /* 0x15E1 */ u8 m15E1[0x15E4 - 0x15E1];
}; // Size: 0x15E4

#endif /* D_A_GND_H */
