#ifndef D_A_OQ_H
#define D_A_OQ_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct oq_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x02B8 */ u8 m02B8[0x02BC - 0x02B8];
    /* 0x02BC */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x02C0 */ u8 m02C0;
    /* 0x02C1 */ u8 m02C1[0x02C2 - 0x02C1];
    /* 0x02C2 */ u8 m02C2;
    /* 0x02C3 */ u8 mAction;
    /* 0x02C4 */ u8 mMode;
    /* 0x02C5 */ u8 mHitType;
    /* 0x02C6 */ u8 m02C6[0x02C7 - 0x02C6];
    /* 0x02C7 */ u8 m02C7;
    /* 0x02C8 */ u8 m02C8;
    /* 0x02C9 */ u8 m02C9;
    /* 0x02CA */ s16 mTimers[6];
    /* 0x02D6 */ s16 m02D6[6];
    /* 0x02E2 */ s16 mTargetAngle;
    /* 0x02E4 */ s16 m02E4;
    /* 0x02E6 */ s16 m02E6;
    /* 0x02E8 */ s16 m02E8;
    /* 0x02EA */ u8 m02EA[0x02EC - 0x02EA];
    /* 0x02EC */ fpc_ProcID m02EC[6];
    /* 0x0304 */ int mCurrBckIdx;
    /* 0x0308 */ u8 m0308[0x030C - 0x0308];
    /* 0x030C */ f32 m030C;
    /* 0x0310 */ f32 m0310;
    /* 0x0314 */ f32 m0314;
    /* 0x0318 */ f32 m0318;
    /* 0x031C */ f32 m031C;
    /* 0x0320 */ f32 m0320;
    /* 0x0324 */ fpc_ProcID m0324;
    /* 0x0328 */ cXyz m0328;
    /* 0x0334 */ cXyz m0334;
    /* 0x0340 */ cXyz m0340;
    /* 0x034C */ csXyz m034C;
    /* 0x0352 */ u8 m0352[0x0354 - 0x0352];
    /* 0x0354 */ dPa_rippleEcallBack mRippleCb;
#if VERSION > VERSION_DEMO
    /* 0x0368 */ dPa_followEcallBack mFollowCb;
#endif
    /* 0x037C */ cXyz m037C;
#if VERSION == VERSION_DEMO
    /* 0x0374 */ u8 m0374[0x037C - 0x0374];
    /* 0x037C */ JPABaseEmitter* m037C_demo;
#else
    /* 0x0388 */ u8 m0388[0x0390 - 0x0388];
#endif
    /* 0x0390 */ dBgS_AcchCir mAcchCir;
    /* 0x03D0 */ dBgS_ObjAcch mAcch;
    /* 0x0594 */ dCcD_Stts mStts;
    /* 0x05D0 */ dCcD_Cyl mBodyCoCyl;
    /* 0x0700 */ dCcD_Cyl mBodyAtCyl;
    /* 0x0830 */ dCcD_Sph mTamaAtCoSph;
    /* 0x095C */ dCcD_Sph mTamaTgCoSph;
    /* 0x0A88 */ enemyice mEnemyIce;
    /* 0x0E40 */ enemyfire mEnemyFire;
    /* 0x1068 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x1070 */ JntHit_c* mpJntHit_c;
}; // Size: 0x1074

#endif /* D_A_OQ_H */
