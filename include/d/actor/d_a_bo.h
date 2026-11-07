#ifndef D_A_BO_H
#define D_A_BO_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "JSystem/JParticle/JPAEmitter.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;

class yodare_ato_PcallBack_c : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    void execute(JPABaseEmitter*, JPABaseParticle*);
    ~yodare_ato_PcallBack_c() {}

public:
    /* 0x04 */ dBgS_ObjGndChk mGndChk;
};

class bo_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_brkAnm* mpBrk;
    /* 0x2B8 */ mDoExt_McaMorf* mpUpMorf;
    /* 0x2BC */ mDoExt_McaMorf* mpDwMorf;
    /* 0x2C0 */ u8 mType;
    /* 0x2C1 */ u8 m2C1;
    /* 0x2C2 */ u8 m2C2[0x2C4 - 0x2C2];
    /* 0x2C4 */ u8 mAction;
    /* 0x2C5 */ u8 mMode;
    /* 0x2C6 */ u8 m2C6;
    /* 0x2C7 */ u8 m2C7;
    /* 0x2C8 */ u8 m2C8;
    /* 0x2C9 */ u8 m2C9;
    /* 0x2CA */ u8 m2CA;
    /* 0x2CB */ u8 m2CB;
    /* 0x2CC */ u8 m2CC;
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 m2CE;
    /* 0x2CF */ u8 m2CF;
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2D4 - 0x2D1];
    /* 0x2D4 */ int m2D4;
    /* 0x2D8 */ int m2D8;
    /* 0x2DC */ int mAnmIdx;
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ cXyz m2F8;
    /* 0x304 */ cXyz m304;
    /* 0x310 */ cXyz m310;
    /* 0x31C */ cXyz m31C;
    /* 0x328 */ cXyz m328;
    /* 0x334 */ s16 m334;
    /* 0x336 */ s16 m336;
    /* 0x338 */ s16 m338;
    /* 0x33A */ s16 m33A;
    /* 0x33C */ s16 m33C;
    /* 0x33E */ s16 m33E;
    /* 0x340 */ s16 m340;
    /* 0x342 */ s16 m342;
    /* 0x344 */ s16 m344;
    /* 0x346 */ s16 m346;
    /* 0x348 */ s16 m348;
    /* 0x34A */ s16 m34A;
    /* 0x34C */ s16 m34C;
    /* 0x34E */ s16 m34E;
    /* 0x350 */ s16 m350;
    /* 0x352 */ s16 m352;
    /* 0x354 */ s16 m354;
    /* 0x356 */ s16 m356;
    /* 0x358 */ cXyz m358;
    /* 0x364 */ s16 m364;
    /* 0x366 */ s16 m366[5];
    /* 0x370 */ s16 m370;
    /* 0x372 */ s16 m372;
    /* 0x374 */ s16 m374;
    /* 0x376 */ s16 m376;
    /* 0x378 */ s16 m378;
    /* 0x37A */ s16 m37A;
    /* 0x37C */ s16 m37C;
    /* 0x37E */ s16 m37E;
    /* 0x380 */ s16 m380;
    /* 0x382 */ s16 m382;
    /* 0x384 */ f32 m384;
    /* 0x388 */ f32 m388;
    /* 0x38C */ f32 m38C;
    /* 0x390 */ f32 m390;
    /* 0x394 */ f32 m394;
    /* 0x398 */ f32 m398;
    /* 0x39C */ cXyz m39C;
    /* 0x3A8 */ u8 m3A8[0x3B0 - 0x3A8];
    /* 0x3B0 */ dPa_smokeEcallBack mSmoke;
    /* 0x3D0 */ JPABaseEmitter* m3D0;
    /* 0x3D4 */ JPABaseEmitter* m3D4;
    /* 0x3D8 */ JPABaseEmitter* m3D8;
    /* 0x3DC */ yodare_ato_PcallBack_c m3DC;
    /* 0x434 */ dBgS_AcchCir mAcchCir;
    /* 0x474 */ dBgS_ObjAcch mAcch;
    /* 0x638 */ dCcD_Stts mStts;
    /* 0x674 */ dCcD_Sph mHeadSph;
    /* 0x7A0 */ dCcD_Sph mFootSph;
    /* 0x8CC */ dCcD_Cyl mBodyCyl;
    /* 0x9FC */ enemyice mEnemyIce;
    /* 0xDB4 */ enemyfire mEnemyFire;
    /* 0xFDC */ mDoExt_invisibleModel mInvisModel;
};

STATIC_ASSERT(sizeof(bo_class) == 0xFE4);

#endif /* D_A_BO_H */
