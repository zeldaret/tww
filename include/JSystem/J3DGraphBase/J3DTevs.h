#ifndef J3DTEVS_H
#define J3DTEVS_H

#include "JSystem/J3DGraphBase/J3DGD.h"

extern u8 j3dTevSwapTableTable[1024];

struct J3DTevStageInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 field_0x9;
    /* 0xA */ u8 field_0xa;
    /* 0xB */ u8 field_0xb;
    /* 0xC */ u8 field_0xc;
    /* 0xD */ u8 field_0xd;
    /* 0xE */ u8 field_0xe;
    /* 0xF */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};

STATIC_ASSERT(sizeof(J3DTevStageInfo) == 0x14);

struct J3DTevStageTevSwapModeInfo {
    u8 field_0x0_29 : 2;
    u8 field_0x0_31 : 2;
};

struct J3DTevStage {
    J3DTevStage() {
        // TODO
        // setTevStageInfo(j3dDefaultTevStageInfo);
        mTevSwapModeInfo.field_0x0_29 = 0;
        mTevSwapModeInfo.field_0x0_31 = 0;
    }
    J3DTevStage(const J3DTevStageInfo& info) {
        setTevStageInfo(info);
        mTevSwapModeInfo.field_0x0_29 = 0;
        mTevSwapModeInfo.field_0x0_31 = 0;
    }
    J3DTevStage& operator=(const J3DTevStage& other) {
        this->field_0x1 = other.field_0x1;
        this->field_0x2 = other.field_0x2;
        this->field_0x3 = other.field_0x3;
        this->field_0x5 = other.field_0x5;
        this->field_0x6 = other.field_0x6;
        this->mTevSwapModeInfo = other.mTevSwapModeInfo;
        return *this;
    }

    void setTevStageInfo(const J3DTevStageInfo&);

    void load(u32) const {
        J3DGDWriteBPCmd(*(u32*)&field_0x0);
        J3DGDWriteBPCmd(*(u32*)&field_0x4);
    }

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x1 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ J3DTevStageTevSwapModeInfo mTevSwapModeInfo;
};

struct J3DIndTevStageInfo {
    /* 0x0 */ u8 mIndStage;
    /* 0x1 */ u8 mIndFormat;
    /* 0x2 */ u8 mBiasSel;
    /* 0x3 */ u8 mMtxSel;
    /* 0x4 */ u8 mWrapS;
    /* 0x5 */ u8 mWrapT;
    /* 0x6 */ u8 mPrev;
    /* 0x7 */ u8 mLod;
    /* 0x8 */ u8 mAlphaSel;
};

struct J3DIndTevStage {
    J3DIndTevStage();

    void load(u32 param_1) {
        J3DGDWriteBPCmd(mInfo | (param_1 + 16) << 24);
    }

    /* 0x0 */ u32 mInfo;
};

struct J3DTevOrderInfo {
    /* 0x0 */ u8 mTexCoord __attribute__((aligned(2)));
    /* 0x1 */ u8 mTexMap;
    /* 0x2 */ u8 mColorChan;
};

struct J3DTevOrder : public J3DTevOrderInfo {
    J3DTevOrder();

    J3DTevOrderInfo& getTevOrderInfo() { return *this; }
    u8 getTexMap() { return mTexMap; }
};

struct J3DTevSwapModeTable {
    J3DTevSwapModeTable();

    u8 getR() { return j3dTevSwapTableTable[field_0x0 * 4]; }
    u8 getG() { return j3dTevSwapTableTable[field_0x0 * 4 + 1]; }
    u8 getB() { return j3dTevSwapTableTable[field_0x0 * 4 + 2]; }
    u8 getA() { return j3dTevSwapTableTable[field_0x0 * 4 + 3]; }

    /* 0x0 */ u8 field_0x0;
};  // Size: 0x1

struct J3DTevSwapModeInfo {
    /* 0x0 */ u8 field_0x0;
};

struct J3DNBTScale;
class J3DTexCoord;
void loadTexCoordGens(u32, J3DTexCoord*);
void loadNBTScale(J3DNBTScale& param_0);

#endif /* J3DTEVS_H */
