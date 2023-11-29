#ifndef D_A_LAMP_H
#define D_A_LAMP_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_cc_d.h"
#include "global.h"

class lamp_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 mParameters;
    /* 0x299 padding */
    /* 0x29a */ s16 mCycleCtr;
    /* 0x29c */ J3DModel* mModel;
    /* 0x2a0 */ dPa_followEcallBack mPa;
    /* 0x2b4 */ u8 mParticleInit;
    /* 0x2b5-2b7 padding */
    /* 0x2b8 */ cXyz mPos;
    /* 0x2c4 */ dCcD_Stts mStts;
    /* 0x300 */ dCcD_Sph mSph;
    /* 0x42c */ s8 mOto;
    /* 0x42d-42f padding */
    /* 0x430 */ float mLength;
    /* 0x434 */ s8 mHitTimeoutLeft;
    /* 0x435-437 padding */
    /* 0x438 */ float mHitReactCurZ;
    /* 0x43c */ s16 mHitAngle;
    /* 0x440 */ LIGHT_INFLUENCE mInf;
    /* 0x460 */ float mParticlePower;
};
STATIC_ASSERT(sizeof(lamp_class) == 0x464);

#endif /* D_A_LAMP_H */
