#ifndef D_A_MAJUU_FLAG_H
#define D_A_MAJUU_FLAG_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

class daMajuu_Flag_packet_c : public J3DPacket {
public:
    daMajuu_Flag_packet_c() {
        mCurArr = 0;
        mRotateY = 0;
        m798 = 0;
        m796 = 0;
        m79B = 1;
    }
    virtual ~daMajuu_Flag_packet_c() {}

    void changeCurrentPos() {
        mCurArr ^= 1;
    }
    Mtx* getMtx() { return &mPosMtx; }
    GXTexObj* getToonTexObj() { return &mToonTex; }
    GXTexObj* getImageTexObj() { return &mFlagTex; }
    cXyz* getPos() { return mpPosArr[mCurArr]; }
    cXyz* getNrm() { return mpNrmArr[mCurArr]; }
    cXyz* getBackNrm() { return mpNrmArrBack[mCurArr]; }
    cXyz* getOffsetVec() { return mSpeed; }

    void setTevStr(dKy_tevstr_c* tevStr) { mpTevStr = tevStr; }
    void setNrmMtx();
    void setBackNrm();
    void setNrmVtx(cXyz*, int);
    
    virtual void draw();

public:
    /* 0x010 */ Mtx mPosMtx;
    /* 0x040 */ dKy_tevstr_c* mpTevStr;
    /* 0x044 */ GXTexObj mToonTex;
    /* 0x064 */ GXTexObj mFlagTex;
    /* 0x084 */ u8 m084[0x0A0 - 0x084];
    /* 0x0A0 */ cXyz mpPosArr[2][21];
    /* 0x298 */ u8 m298[0x2A0 - 0x298];
    /* 0x2A0 */ cXyz mpNrmArr[2][21];
    /* 0x498 */ u8 m498[0x4A0 - 0x498];
    /* 0x4A0 */ cXyz mpNrmArrBack[2][21];
    /* 0x698 */ cXyz mSpeed[21];
    /* 0x794 */ s16 mRotateY;
    /* 0x796 */ s16 m796;
    /* 0x798 */ s16 m798;
    /* 0x79A */ u8 mCurArr;
    /* 0x79B */ u8 m79B;
}; // size = 0x79C

class daMajuu_Flag_c : public fopAc_ac_c {
public:
    void setBaseScale(float scale) { mFlagScale = scale; }
    void setOtherMatrix(Mtx* mtx) { mpParentMtx = *mtx; }
    void setOtherOffset(cXyz* pos) { mpParentPos = pos; }

public:
    /* 0x290 */ u8 m290[0x2A0 - 0x290];
    /* 0x2A0 */ daMajuu_Flag_packet_c mPacket;
    /* 0xA3C */ u8 mA3C[0xA40 - 0xA3C];
    /* 0xA40 */ request_of_phase_process_class mPhsCloth;
    /* 0xA48 */ request_of_phase_process_class mPhsFlag;
    /* 0xA50 */ u8 mA50[0xA58 - 0xA50];
    /* 0xA58 */ s16 mWave;
    /* 0xA5A */ u8 mA5A[0xA60 - 0xA5A];
    /* 0xA60 */ f32 mFlagScale;
    /* 0xA64 */ u8 mFlagType;
    /* 0xA65 */ u8 mTexType;
    /* 0xA66 */ u8 mbUsePlayerTevStr;
    /* 0xA67 */ u8 mA67[0xA68 - 0xA67];
    /* 0xA68 */ Mtx mMtx;
    /* 0xA98 */ MtxP mpParentMtx;
    /* 0xA9C */ cXyz* mpParentPos;
}; // size = 0xAA0

#endif /* D_A_MAJUU_FLAG_H */
