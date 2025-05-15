#ifndef D_A_KITA_H
#define D_A_KITA_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

class kita_class : public fopAc_ac_c {
public: // Methods
    kita_class() {};

public: // Attributes
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ short mMoveCounter;
    /* 0x29A */ short field_29A;
    /* 0x29C */ J3DModel* mModel;
    /* 0x2A0 */ u8 field_2A0;
    /* 0x2A1 */ u8 field_2A1;
    /* 0x2A4 */ cXyz mPosRel;
    /* 0x2A8 */ cXyz field_2B0;
    /* 0x2B4 */ cXyz field_2BC;
    /* 0x2C8 */ csXyz field_2C8;
    /* 0x2D0 */ float mHeight;
    /* 0x2D4 */ fpc_ProcID field_2D4[4];
    /* 0x2E4 */ u8 field_2E4[4];
    /* 0x2E8 */ cXyz field_2E8[4];
    /* 0x318 */ u8 field_318[4];
    /* 0x31C */ short mRotY;
    /* 0x31E */ short mRotX;
    /* 0x320 */ float field_320;
    /* 0x324 */ int unused_324;
    /* 0x328 */ Mtx mBgwMtx;
    /* 0x358 */ dBgW* pm_bgw;
    /* 0x35C */ float field_35C;
    /* 0x360 */ u8 field_360;
    /* 0x362 */ short mPlayerAngle;
    /* 0x364 */ float field_364;
    /* 0x368 */ float mAngleYSpeed;
    /* 0x36C */ float field_36C;
    /* 0x370 */ float field_370;
    /* 0x374 */ short field_374;
    /* 0x376 */ short mExecuteCount;
    /* 0x378 */ JPABaseEmitter* mBaseEmitter;
    /* 0x37C */ dCcD_Stts mStts;
    /* 0x3B8 */ dCcD_Sph mSph;
    /* 0x4E4 */ dBgS_AcchCir mAcchCir;
    /* 0x524 */ dBgS_ObjAcch mAcch;
};

#endif /* D_A_KITA_H */
