#ifndef D_A_SAIL_H
#define D_A_SAIL_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_phase.h"

class daSail_packet_c : public J3DPacket {
public:
    daSail_packet_c() {
        m1C3A = 0;
        m1C34 = 0;
        m1C38 = 0;
        m1C36 = 0;
        m1C3B = 1;
    }

    Mtx* getMtx() { return &mMtx; }
    cXyz* getNrm() { return m0C74 + (0x54 * m1C3A); }
    cXyz* getPos() { return m00A4 + (0x54 * m1C3A); }
    cXyz* getPosSpd() { return m0884; }
    Mtx* getStickMtx() { return &mStickMtx; }
    Mtx* getTexMtx() { return &mTexMtx; }
    void setTevStr(dKy_tevstr_c* tevStr) { mTevStr = tevStr; }

    void setCorrectNrmAngle(s16, f32);
    void setNrmMtx();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    virtual void draw();
    virtual ~daSail_packet_c() {}

public:
    /* 0x0010 */ Mtx mMtx;
    /* 0x0040 */ Mtx mTexMtx;
    /* 0x0070 */ Mtx mStickMtx;
    /* 0x00A0 */ dKy_tevstr_c* mTevStr;
    /* 0x00A4 */ cXyz m00A4[0x54 * 2];
    /* 0x0884 */ cXyz m0884[0x54];
    /* 0x0C74 */ cXyz m0C74[0x54 * 2];
    /* 0x1454 */ cXyz m1454[0x54 * 2];
    /* 0x1C34 */ s16 m1C34;
    /* 0x1C36 */ s16 m1C36;
    /* 0x1C38 */ s16 m1C38;
    /* 0x1C3A */ u8 m1C3A;
    /* 0x1C3B */ u8 m1C3B;
    /* 0x1C3C */ J3DModel* mStickModel;
    /* 0x1C40 */ s32 m1C40;
    /* 0x1C44 */ f32 m1C44;
    /* 0x1C48 */ f32 m1C48;
    /* 0x1C4C */ f32 m1C4C;
    /* 0x1C50 */ s16 m1C50;
    /* 0x1C52 */ s16 m1C52;
};

class sail_class : public fopAc_ac_c {
public:
    sail_class() {}

public:
    /* 0x0290 */ request_of_phase_process_class mClothPhase;
    /* 0x0298 */ request_of_phase_process_class mKaizokusenPhase;
    /* 0x02A0 */ daSail_packet_c mSailPacket;
};

class daSail_HIO_c : public JORReflexible {
public:
    daSail_HIO_c() {
        mChildID = -1;
        m05 = 1;
        m06 = 1;
        m10 = 0.0f;
        m07 = 0;
    }
    virtual ~daSail_HIO_c() {
        mChildID = -1;
    }

public:
    /* 0x04 */ s8 mChildID;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ u8 m08;
    /* 0x09 */ u8 m09[0x0C - 0x09];
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
};

#endif /* D_A_SAIL_H */
