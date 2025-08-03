#ifndef D_A_MAJUU_FLAG_H
#define D_A_MAJUU_FLAG_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daMajuu_Flag_packet_c {
public:
    void changeCurrentPos() {}
    void getImageTexObj() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void getToonTexObj() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setNrmMtx();
    void setBackNrm();
    void setNrmVtx(cXyz*, int);
    void draw();
};

class daMajuu_Flag_c : public fopAc_ac_c {
public:
    void setBaseScale(float scale) { mFlagScale = scale; }
    void setOtherMatrix(Mtx* mtx) { mpParentMtx = *mtx; }
    void setOtherOffset(cXyz* pos) { mpParentPos = pos; }

public:
    /* 0x290 */ u8 m290[0x2A0 - 0x290];
    /* 0x2A0 */ daMajuu_Flag_packet_c mPacket;
    /* 0x2A4 */ u8 mA3D[0xA40 - 0x2A4];
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
};

#endif /* D_A_MAJUU_FLAG_H */
