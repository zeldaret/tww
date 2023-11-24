#ifndef D_A_PH_H
#define D_A_PH_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "c/c_damagereaction.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

class ph_class : public fopAc_ac_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhs;
    /* 0x02B4 */ u8 m02B4[0x02B8 - 0x02B4];
    /* 0x02B8 */ mDoExt_McaMorf* mpPropellerMorf;
    /* 0x02BC */ mDoExt_McaMorf* mpBodyMorf;
    /* 0x02C0 */ cXyz m02C0;
    /* 0x02CC */ cXyz m02CC;
    /* 0x02D8 */ cXyz m02D8;
    /* 0x02E4 */ cXyz m02E4;
    /* 0x02F0 */ cXyz m02F0;
    /* 0x02FC */ cXyz m02FC;
    /* 0x0308 */ cXyz m0308;
    /* 0x0314 */ cXyz m0314;
    /* 0x0320 */ u8 m0320[0x032C - 0x0320];
    /* 0x032C */ cXyz m032C;
    /* 0x0338 */ u8 m0338[0x033A - 0x0338];
    /* 0x033A */ s16 m033A;
    /* 0x033C */ u8 m033C[0x033E - 0x033C];
    /* 0x033E */ daPH__BehaviorTypes mType;
    /* 0x033F */ u8 m033F;
    /* 0x0340 */ u8 m0340;
    /* 0x0341 */ u8 m0341;
    /* 0x0342 */ u8 m0342[0x0344 - 0x0342];
    /* 0x0344 */ u8 m0344;
    /* 0x0345 */ u8 m0345[0x0346 - 0x0345];
    /* 0x0346 */ s16 m0346;
    /* 0x0348 */ s16 m0348;
    /* 0x034A */ s16 m034A;
    /* 0x034C */ s16 m034C;
    /* 0x034E */ u8 m034E[0x0350 - 0x034E];
    /* 0x0350 */ s16 m0350;
    /* 0x0352 */ u8 m0352[0x0356 - 0x0352];
    /* 0x0356 */ s16 m0356;
    /* 0x0358 */ s16 m0358;
    /* 0x035A */ s16 m035A;
    /* 0x035C */ u8 m035C[0x036C - 0x035C];
    /* 0x036C */ s16 m036C;
    /* 0x036E */ u8 m036E[0x0370 - 0x036E];
    /* 0x0370 */ s16 m0370;
    /* 0x0372 */ u8 m0372[0x0374 - 0x0372];
    /* 0x0374 */ int m0374;
    /* 0x0378 */ u8 m0378[0x037C - 0x0378];
    /* 0x037C */ f32 m037C;
    /* 0x0380 */ f32 m0380;
    /* 0x0384 */ u8 m0384[0x038C - 0x0384];
    /* 0x038C */ f32 m038C;
    /* 0x0390 */ f32 m0390;
    /* 0x0394 */ f32 m0394;
    /* 0x0398 */ f32 m0398;
    /* 0x039C */ f32 m039C;
    /* 0x03A0 */ f32 m03A0;
    /* 0x03A4 */ dBgS_AcchCir mAcchCir;
    /* 0x03E4 */ dBgS_Acch mAcch;
    /* 0x05A8 */ dPa_rippleEcallBack mParticleCallBack;
    /* 0x05BC */ cXyz m05BC;
    /* 0x05C8 */ u8 m05C8[0x05D0 - 0x05C8];
    /* 0x05D0 */ dCcD_Stts mStts;
    /* 0x060C */ dCcD_Sph mBodySph;
    /* 0x0738 */ dCcD_Cyl mAtCyl;
    /* 0x0868 */ dCcD_Cyl mTgCyl;
    /* 0x0998 */ enemyice mEnemyIce;
    /* 0x0D50 */ enemyfire mBodyEnemyFire;
    /* 0x0F78 */ enemyfire mPropellerEnemyFire;
    /* 0x11A0 */ mDoExt_invisibleModel mPropellerInvisibleModel;
    /* 0x11A8 */ mDoExt_invisibleModel mBodyInvisibleModel;
    /* 0x11B0 */ JntHit_c* mpJntHit;
};

#endif /* D_A_PH_H */
