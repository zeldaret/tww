#ifndef D_A_BST_H
#define D_A_BST_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class mDoExt_McaMorf;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

class bst_class : public fopAc_ac_c {
public:
    /* 0x0290 */ u8 field_0x0290[0x02AC - 0x0290];
    /* 0x02AC */ request_of_phase_process_class mPhs;
    /* 0x02B4 */ u8 field_0x02B4;
    /* 0x02B5 */ u8 field_0x02B5[0x02B8 - 0x02B5];
    /* 0x02B8 */ mDoExt_McaMorf* field_0x02B8;
    /* 0x02BC */ mDoExt_btkAnm* mpTexMtxAnimator;
    /* 0x02C0 */ mDoExt_brkAnm* mpTevRegAnimator;
    /* 0x02C4 */ s8 field_0x02C4;
    /* 0x02C5 */ u8 field_0x02C5[0x02C8 - 0x02C5];
    /* 0x02C8 */ J3DModel* field_0x02C8;
    /* 0x02CC */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x02D0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x02D4 */ s8 field_0x02D4;
    /* 0x02D5 */ u8 field_0x02D5[0x02D8 - 0x02D5];
    /* 0x02D8 */ dKy_tevstr_c mEnvLight;
    /* 0x0388 */ J3DModel* field_0x0388;
    /* 0x038C */ u32 mShadowID;
    /* 0x0390 */ J3DModel* field_0x0390[10];
    /* 0x03B8 */ cXyz field_0x03B8[10];
    /* 0x0430 */ cXyz field_0x0430[10];
    /* 0x04A8 */ csXyz field_0x04A8[10];
    /* 0x04E4 */ s8 field_0x04E4[10];
    /* 0x04EE */ u8 field_0x04EE[0x04F0 - 0x04EE];
    /* 0x04F0 */ dCcD_Sph mCcD_beams[10];
    /* 0x10A8 */ f32 field_0x10A8[10];
    /* 0x10D0 */ f32 field_0x10D0;
    /* 0x10D4 */ s16 field_0x10D4;
    /* 0x10D6 */ s16 field_0x10D6;
    /* 0x10D8 */ s16 field_0x10D8;
    /* 0x10DA */ s16 mDamage;
    /* 0x10DC */ cXyz mTargetPos;
    /* 0x10E8 */ s16 field_0x10E8;
    /* 0x10EA */ u8 field_0x10EA[0x10EC - 0x10EA];
    /* 0x10EC */ cXyz field_0x10EC;
    /* 0x10F8 */ f32 field_0x10F8;
    /* 0x10FC */ s16 field_0x10FC[5];
    /* 0x1106 */ s16 mDamageTimer;
    /* 0x1108 */ s16 mState;
    /* 0x110A */ s16 mStateTimer;
    /* 0x110C */ u8 field_0x110C[0x1110 - 0x110C];
    /* 0x1110 */ f32 field_0x1110;
    /* 0x1114 */ f32 field_0x1114;
    /* 0x1118 */ f32 field_0x1118;
    /* 0x111C */ s16 field_0x111C;
    /* 0x111E */ u8 field_0x111E[0x1120 - 0x111E];
    /* 0x1120 */ f32 mHeadHurtSpeed;
    /* 0x1124 */ s16 mHurtRecoilAngle1;
    /* 0x1126 */ s16 mHurtRecoilAngle2;
    /* 0x1128 */ s16 mHeadHurtAngle;
    /* 0x112A */ s16 field_0x112A;
    /* 0x112C */ s16 field_0x112C;
    /* 0x112E */ u8 field_0x112E[0x1130 - 0x112E];
    /* 0x1130 */ dBgS_AcchCir mBgS_AcchCir;
    /* 0x1170 */ dBgS_ObjAcch mBgS_Acch;
    /* 0x1334 */ dCcD_Stts mCcD_Stts;
    /* 0x1370 */ dCcD_Cyl mHeadHurtCollisionCcD_Cyl;
    /* 0x14A0 */ dCcD_Cyl mHandHurtCollisionCcD_Cyl;
    /* 0x15D0 */ dCcD_Sph mCcD_fingers[19];
    /* 0x2C14 */ dCcD_Sph mBstEyeCcD_Spheres[2];
    /* 0x2E6C */ u8 field_0x2E6C[0x2E6E - 0x2E6C];
    /* 0x2E6E */ s16 field_0x2E6E;
    /* 0x2E70 */ s16 mFacingDir;
    /* 0x2E72 */ s8 mEyeHealth[2];
    /* 0x2E74 */ s16 field_0x2E74[2];
    /* 0x2E78 */ s16 field_0x2E78[2];
    /* 0x2E7C */ s8 field_0x2E7C;
    /* 0x2E7D */ u8 field_0x2E7D[0x2E7E - 0x2E7D];
    /* 0x2E7E */ s16 field_0x2E7E[3];
    /* 0x2E84 */ s16 field_0x2E84;
    /* 0x2E86 */ u8 field_0x2E86[0x2E88 - 0x2E86];
    /* 0x2E88 */ fpc_ProcID mBombId;
    /* 0x2E8C */ fpc_ProcID mCreatedItemId;
    /* 0x2E90 */ fpc_ProcID field_0x2E90[2];
    /* 0x2E98 */ s16 field_0x2E98;
    /* 0x2E9A */ s8 field_0x2E9A;
    /* 0x2E9B */ u8 field_0x2E9B[0x2E9C - 0x2E9B];
    /* 0x2E9C */ s16 msFrameCount;
    /* 0x2E9E */ s8 field_0x2E9E;
    /* 0x2E9F */ u8 field_0x2E9F[0x2EA0 - 0x2E9F];
    /* 0x2EA0 */ cXyz field_0x2EA0;
    /* 0x2EAC */ cXyz field_0x2EAC;
    /* 0x2EB8 */ u8 field_0x2EB8[0x2EC4 - 0x2EB8];
    /* 0x2EC4 */ f32 field_0x2EC4;
    /* 0x2EC8 */ f32 field_0x2EC8;
    /* 0x2ECC */ f32 field_0x2ECC;
    /* 0x2ED0 */ f32 field_0x2ED0;
    /* 0x2ED4 */ s8 mRoomState;
    /* 0x2ED5 */ u8 field_0x2ED5[0x2ED8 - 0x2ED5];
    /* 0x2ED8 */ JPABaseEmitter* field_0x2ED8[2];
    /* 0x2EE0 */ u8 field_0x2EE0[0x2EF4 - 0x2EE0];
    /* 0x2EF4 */ JPABaseEmitter* field_0x2EF4;
    /* 0x2EF8 */ u8 field_0x2EF8[0x2F00 - 0x2EF8];
    /* 0x2F00 */ dPa_smokeEcallBack mPa_smokeEcallBack;
    /* 0x2F20 */ dKy_tevstr_c field_0x2F20;
    /* 0x2FD0 */ J3DModel* field_0x2FD0;
    /* 0x2FD4 */ mDoExt_btkAnm* field_0x2FD4;
    /* 0x2FD8 */ mDoExt_brkAnm* field_0x2FD8;
    /* 0x2FDC */ J3DModel* field_0x2FDC;
    /* 0x2FE0 */ mDoExt_brkAnm* field_0x2FE0;
    /* 0x2FE4 */ s8 field_0x2FE4;
    /* 0x2FE5 */ u8 mHioSet;
    /* 0x2FE6 */ u8 field_0x2FE6[0x2FE8 - 0x2FE6];
};  // Size: 0x2FE8

#endif /* D_A_BST_H */
