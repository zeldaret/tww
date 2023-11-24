#ifndef D_A_AM2_H
#define D_A_AM2_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

class am2_class : public fopAc_ac_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ JntHit_c* mEyeJntHit;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ u8 m2BC[0x2C0 - 0x2BC];
    /* 0x2C0 */ mDoExt_btkAnm* m2C0;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ u8 mType;
    /* 0x2C9 */ u8 mPrmAreaRadius;
    /* 0x2CA */ u8 m2CA;
    /* 0x2CB */ u8 mSwitch;
    /* 0x2CC */ u8 mAction;
    /* 0x2CD */ u8 mState;
    /* 0x2CE */ u8 m2CE;
    /* 0x2CF */ bool mIsWeakBeingHit;
    /* 0x2D0 */ bool m2D0;
    /* 0x2D1 */ bool m2D1;
    /* 0x2D2 */ u8 m2D2;
    /* 0x2D3 */ u8 m2D3[0x2E0 - 0x2D3];
    /* 0x2E0 */ cXyz mWaistPos;
    /* 0x2EC */ cXyz mJawPos;
    /* 0x2F8 */ cXyz mMouthPos;
    /* 0x304 */ cXyz m304;
    /* 0x310 */ cXyz m310;
    /* 0x31C */ cXyz m31C;
    /* 0x328 */ cXyz m328;
    /* 0x334 */ s16 mCountDownTimers[5];
    /* 0x33E */ s16 mCountUpTimers[4];
    /* 0x346 */ s16 m346;
    /* 0x348 */ s16 m348;
    /* 0x34A */ u8 m34A[0x34C - 0x34A];
    /* 0x34C */ int mCurrBckIdx;
    /* 0x350 */ f32 m350;
    /* 0x354 */ f32 mAreaRadius;
    /* 0x358 */ f32 m358;
    /* 0x35C */ f32 m35C;
    /* 0x360 */ dBgS_AcchCir mAcchCir;
    /* 0x3A0 */ dBgS_ObjAcch mAcch;
    /* 0x564 */ dCcD_Stts mStts;
    /* 0x5A0 */ dCcD_Cyl mBodyCyl;
    /* 0x6D0 */ dCcD_Cyl mNeedleCyl;
    /* 0x800 */ dCcD_Sph mEyeSph;
    /* 0x92C */ dCcD_Sph mWeakSph;
    /* 0xA58 */ dPa_smokeEcallBack mA58;
    /* 0xA78 */ dPa_rippleEcallBack mA78;
    /* 0xA8C */ enemyice mEnemyIce;
};

#endif /* D_A_AM2_H */
