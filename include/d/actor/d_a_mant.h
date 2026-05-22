#ifndef D_A_MANT_H
#define D_A_MANT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_bg_s.h"
#include "d/d_bg_s.h"

struct mant_j_s {
    /* 0x000 */ cXyz field_0x00[9];
    /* 0x06C */ cXyz field_0x6C[9];
    /* 0x0D8 */ csXyz mAngle;
    /* 0x0DE */ u8 pad_0xDE[0x110 - 0xDE];
};

class daMant_packet_c : public J3DPacket {
public:
    daMant_packet_c() {
        mTexNo = 0;
    }
    virtual ~daMant_packet_c() {}

    /* 0x10 */ Mtx mMtx1;
    /* 0x40 */ Mtx mMtx2;
    /* 0x70 */ dKy_tevstr_c* mpTevStr;
    /* 0x74 */ u8 mTexNo;
    /* 0x75 */ u8 mArg0;
    /* 0x76 */ u8 pad_0x76[2];
    /* 0x78 */ cXyz mVertexPos[0xA2];
    /* 0x810 */ cXyz mVertexNrm[0xA2];

    MtxP getMtx() { return mMtx1; }
    MtxP getMtx2() { return mMtx2; }
    cXyz* getNrm() { return mVertexNrm; }
    cXyz* getPos() { return mVertexPos; }
    u8 getTexNo() { return mTexNo; }
    void setTevStr(dKy_tevstr_c* pTevStr) { mpTevStr = pTevStr; }
    void setTexNo(unsigned char texNo) { mTexNo = texNo; }
    void setarg0(unsigned char arg0) { mArg0 = arg0; }
    void draw();
};

class mant_class : public fopAc_ac_c {
public:
    mant_class() {}

    /* 0x290 */ u8 pad_0x290[0x298 - 0x290];
    /* 0x298 */ daMant_packet_c mPacket;
    /* 0x1240 */ u8 mState;
    /* 0x1241 */ u8 mType2;
    /* 0x1242 */ u8 pad_0x1242[2];
    /* 0x1244 */ u8 mType;
    /* 0x1245 */ u8 pad_0x1245[3];
    /* 0x1248 */ u32 mCounter;
    /* 0x124C */ u8 pad_0x124C[0x1250 - 0x124C];
    /* 0x1250 */ mant_j_s mJoint[9];
    /* 0x1BE0 */ cXyz m1BE0_arr[2];
#define m1BE0 m1BE0_arr[0]
#define m1BEC m1BE0_arr[1]
    /* 0x1BF8 */ f32 mWindStr;
    /* 0x1BFC */ f32 mDamping;
    /* 0x1C00 */ f32 m1C00;
    /* 0x1C04 */ f32 m1C04;
    /* 0x1C08 */ f32 m1C08;
    /* 0x1C0C */ s16 m1C0C;
    /* 0x1C0E */ s16 m1C0E;
    /* 0x1C10 */ dCcD_Stts mStts;
    /* 0x1C4C */ dCcD_Sph mWindSph;
    /* 0x1D78 */ dCcD_Sph mMeshSph[9];
    /* 0x2804 */ Mtx mCullMtx;
    /* 0x2834 */ s8 field_0x2834;
    /* 0x2836 */ s16 field_0x2836;
    /* 0x2838 */ s16 field_0x2838;
    /* 0x283A */ u8 pad_0x283A[0x283C - 0x283A];
};

#endif /* D_A_MANT_H */
