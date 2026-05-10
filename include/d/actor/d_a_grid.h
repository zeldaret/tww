#ifndef D_A_GRID_H
#define D_A_GRID_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daHo_packet_c : public J3DMatPacket {
public:
    daHo_packet_c() {
        setShapePacket(&mShapePacket);
        m189C = 0;
        m189E = 0;
        m18A0 = 0;
        mActiveBuffer = 0;
        mAlpha = 0xFF;
    }

    Mtx* getMtx() { return &mMtx; }
    void setTevStr(dKy_tevstr_c* tevStr) { mTevStr = tevStr; }
    cXyz* getPos() { return mPos[mActiveBuffer]; }
    cXyz* getNrm() { return mNrm[mActiveBuffer]; }
    cXyz* getBackNrm() { return mBackNrm[mActiveBuffer]; }

    void setBackNrm();
    void setNrmMtx(cXyz&);
    void setNrmVtx(cXyz*, int, int);
    void setTopNrmVtx(cXyz*);
    virtual void draw();
    virtual ~daHo_packet_c() {}

public:
    /* 0x003C */ J3DShapePacket mShapePacket;
    /* 0x0080 */ Mtx mMtx;
    /* 0x00B0 */ dKy_tevstr_c* mTevStr;
    /* 0x00B4 */ cXyz mPos[2][0x55];
    /* 0x08AC */ cXyz mNrm[2][0x55];
    /* 0x10A4 */ cXyz mBackNrm[2][0x55];
    /* 0x189C */ s16 m189C;
    /* 0x189E */ s16 m189E;
    /* 0x18A0 */ s16 m18A0;
    /* 0x18A2 */ u8 mActiveBuffer;
    /* 0x18A3 */ u8 mAlpha;
};

class daGrid_c : public fopAc_ac_c {
public:
    void force_calc_wind_rel_angle(short param_1) {
        mForceWindRelAngle = param_1;
        mForceWindRelAngleFlag = 1;
    }

    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x0290 */ request_of_phase_process_class mClothPhase;
    /* 0x0298 */ request_of_phase_process_class mShipPhase;
    /* 0x02A0 */ daHo_packet_c mPacket;
    /* 0x1B44 */ u32 m1B44;
    /* 0x1B48 */ s8 mRoomNo;
    /* 0x1B49 */ u8 m1B49;
    /* 0x1B4A */ s16 m1B4A;
    /* 0x1B4C */ s16 m1B4C;
    /* 0x1B4E */ s16 m1B4E;
    /* 0x1B50 */ u8 m1B50[0x1B54 - 0x1B50];
    /* 0x1B54 */ f32 m1B54[0x55];
    /* 0x1CA8 */ cXyz m1CA8[0x55];
    /* 0x20A4 */ u8 m20A4[0x2200 - 0x20A4];
    /* 0x2200 */ f32 m2200;
    /* 0x2204 */ f32 m2204;
    /* 0x2208 */ f32 m2208;
    /* 0x220C */ u8 m220C[0x2210 - 0x220C];
    /* 0x2210 */ s16 m2210;
    /* 0x2212 */ s16 m2212;
    /* 0x2214 */ s16 m2214;
    /* 0x2216 */ s16 mForceWindRelAngle;
    /* 0x2218 */ u8 mForceWindRelAngleFlag;
    /* 0x2219 */ u8 m2219[0x221C - 0x2219];
};

class daHo_HIO_c : public JORReflexible {
public:
    daHo_HIO_c();
    virtual ~daHo_HIO_c() { mNo = -1; }

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ u8 m08;
    /* 0x09 */ u8 m09[0x0C - 0x09];
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 mScaleX;
    /* 0x28 */ f32 mScaleY;
    /* 0x2C */ f32 mScaleZ;
    /* 0x30 */ u8 mFarAlpha;
    /* 0x31 */ u8 mNearAlpha;
    /* 0x32 */ u8 m32[0x34 - 0x32];
    /* 0x34 */ f32 mAlphaDist;
    /* 0x38 */ u8 mStopMove;
    /* 0x39 */ u8 mUseHioRates;
    /* 0x3A */ u8 m3A[0x3C - 0x3A];
    /* 0x3C */ f32 mDepthRate[0x0D];
    /* 0x70 */ f32 mWaveRate[0x0D];
};

STATIC_ASSERT(sizeof(daHo_packet_c) == 0x18A4);
STATIC_ASSERT(sizeof(daGrid_c) == 0x221C);
STATIC_ASSERT(sizeof(daHo_HIO_c) == 0xA4);

#endif /* D_A_GRID_H */
