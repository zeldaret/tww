#ifndef J3DTEVS_H
#define J3DTEVS_H

#include "dolphin/types.h"

struct J3DTevStageInfo {
    /* 0x0 */ u8 mTevMode;
    /* 0x1 */ u8 mTevColorOp;
    /* 0x2 */ u8 mTevColorAB;
    /* 0x3 */ u8 mTevColorCD;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 mTevAlphaOp;
    /* 0x6 */ u8 mTevAlphaAB;
    /* 0x7 */ u8 mTevSwapModeInfo;
};

struct J3DTevStage : public J3DTevStageInfo {
    J3DTevStage();
    void setTevStageInfo(J3DTevStageInfo const&);
    J3DTevStage(J3DTevStageInfo const&);
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

    /* 0x0 */ u32 mInfo;
};

struct J3DTevOrderInfo {
    /* 0x0 */ u8 mTexCoord __attribute__((aligned(2)));
    /* 0x1 */ u8 mTexMap;
    /* 0x2 */ u8 mColorChan;
};

struct J3DTevOrder : public J3DTevOrderInfo {
    J3DTevOrder();

    u8 getTexMap() { return mTexMap; }
};

struct J3DTevSwapModeTable {
    J3DTevSwapModeTable();

    /* 0x0 */ u8 field_0x0;
};  // Size: 0x1

struct J3DTevSwapModeInfo {
    /* 0x0 */ u8 field_0x0;
};

struct J3DNBTScale;
void loadNBTScale(J3DNBTScale& param_0);

#endif /* J3DTEVS_H */
