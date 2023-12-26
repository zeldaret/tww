#ifndef J3DTEVS_H
#define J3DTEVS_H

#include "JSystem/J3DGraphBase/J3DGD.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"

extern u8 j3dTevSwapTableTable[1024];

extern const J3DLightInfo j3dDefaultLightInfo;
extern const J3DTexCoordInfo j3dDefaultTexCoordInfo[8];
extern const J3DTexMtxInfo j3dDefaultTexMtxInfo;
extern const J3DIndTexMtxInfo j3dDefaultIndTexMtxInfo;
extern const J3DTevStageInfo j3dDefaultTevStageInfo;
extern const J3DIndTevStageInfo j3dDefaultIndTevStageInfo;
extern const J3DFogInfo j3dDefaultFogInfo;
extern const J3DNBTScaleInfo j3dDefaultNBTScaleInfo;

extern const GXColor j3dDefaultColInfo;
extern const GXColor j3dDefaultAmbInfo;
extern const u8 j3dDefaultColorChanNum;
extern const J3DTevOrderInfo j3dDefaultTevOrderInfoNull;
extern const J3DIndTexOrderInfo j3dDefaultIndTexOrderNull;
extern const GXColorS10 j3dDefaultTevColor;
extern const J3DIndTexCoordScaleInfo j3dDefaultIndTexCoordScaleInfo;
extern const GXColor j3dDefaultTevKColor;
extern const J3DTevSwapModeInfo j3dDefaultTevSwapMode;
extern const J3DTevSwapModeTableInfo j3dDefaultTevSwapModeTable;
extern const J3DBlendInfo j3dDefaultBlendInfo;
extern const J3DColorChanInfo j3dDefaultColorChanInfo;
extern const u8 j3dDefaultTevSwapTableID;
extern const u16 j3dDefaultAlphaCmpID;
extern const u16 j3dDefaultZModeID;

struct J3DTevStage {
    J3DTevStage() {
        setTevStageInfo(j3dDefaultTevStageInfo);
        setTevSwapModeInfo(j3dDefaultTevSwapMode);
    }
    explicit J3DTevStage(const J3DTevStageInfo& info) {
        setTevStageInfo(info);
        setTevSwapModeInfo(j3dDefaultTevSwapMode);
    }
    J3DTevStage& operator=(const J3DTevStage& other) {
        this->mTevColorOp = other.mTevColorOp;
        this->mTevColorAB = other.mTevColorAB;
        this->mTevColorCD = other.mTevColorCD;
        this->mTevAlphaOp = other.mTevAlphaOp;
        this->mTevAlphaAB = other.mTevAlphaAB;
        this->mTevSwapModeInfo = other.mTevSwapModeInfo;
        return *this;
    }

    void setTevColorOp(u8 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5) {
        mTevColorOp = mTevColorOp & ~(0x01 << 2) | param_1 << 2;
        if (param_1 <= 1) {
            mTevColorOp = mTevColorOp & ~(0x03 << 4) | param_3 << 4;
            mTevColorOp = mTevColorOp & ~0x03 | param_2;
        } else {
            mTevColorOp = mTevColorOp & ~(0x03 << 4) | (param_1 >> 1 & 3) << 4;
            mTevColorOp = mTevColorOp & ~0x03 | 3;
        }
        mTevColorOp = mTevColorOp & ~(0x01 << 3) | param_4 << 3;
        mTevColorOp = mTevColorOp & ~(0x03 << 6) | param_5 << 6;
    }
    void setTevColorAB(u8 a, u8 b) { mTevColorAB = a << 4 | b; }
    void setTevColorCD(u8 c, u8 d) { mTevColorCD = c << 4 | d; }
    void setAlphaA(u8 a) { mTevAlphaAB = mTevAlphaAB & ~(0x07 << 5) | a << 5; }
    void setAlphaB(u8 b) { mTevAlphaAB = mTevAlphaAB & ~(0x07 << 2) | b << 2; }
    void setAlphaC(u8 c) {
        mTevAlphaAB = mTevAlphaAB & ~0x03 | c >> 1;
        mTevSwapModeInfo = mTevSwapModeInfo & ~(0x01 << 7) | c << 7;
    }
    void setAlphaD(u8 d) { mTevSwapModeInfo = mTevSwapModeInfo & ~(0x07 << 4) | d << 4; }
    void setAlphaABCD(u8 a, u8 b, u8 c, u8 d) {
        setAlphaA(a);
        setAlphaB(b);
        setAlphaC(c);
        setAlphaD(d);
    }
    void setTevAlphaOp(u8 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5) {
        mTevAlphaOp = mTevAlphaOp & ~(0x01 << 2) | param_1 << 2;
        if (param_1 <= 1) {
            mTevAlphaOp = mTevAlphaOp & ~0x03 | param_2;
            mTevAlphaOp = mTevAlphaOp & ~(0x03 << 4) | param_3 << 4;
        } else {
            mTevAlphaOp = mTevAlphaOp & ~(0x03 << 4) | (param_1 >> 1 & 3) << 4;
            mTevAlphaOp = mTevAlphaOp & ~0x03 | 3;
        }
        mTevAlphaOp = mTevAlphaOp & ~(0x01 << 3) | param_4 << 3;
        mTevAlphaOp = mTevAlphaOp & ~(0x03 << 6) | param_5 << 6;
    }
    void setTevStageInfo(const J3DTevStageInfo& info) {
        setTevColorOp(info.field_0x5, info.field_0x6, info.field_0x7, info.field_0x8, info.field_0x9);
        setTevColorAB(info.field_0x1, info.field_0x2);
        setTevColorCD(info.field_0x3, info.field_0x4);
        setAlphaABCD(info.field_0xa, info.field_0xb, info.field_0xc, info.field_0xd);
        setTevAlphaOp(info.field_0xe, info.field_0xf, info.field_0x10, info.field_0x11, info.field_0x12);
    }

    void setTexSel(u8 param_0) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x0C | param_0 << 2; }
    void setRasSel(u8 param_0) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x03 | param_0; }
    void setTevSwapModeInfo(const J3DTevSwapModeInfo& info) {
        setTexSel(info.mTexSel);
        setRasSel(info.mRasSel);
    }

    void load(u32) const {
        J3DGDWriteBPCmd(*(u32*)&field_0x0);
        J3DGDWriteBPCmd(*(u32*)&field_0x4);
    }

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 mTevColorOp;
    /* 0x1 */ u8 mTevColorAB;
    /* 0x3 */ u8 mTevColorCD;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 mTevAlphaOp;
    /* 0x6 */ u8 mTevAlphaAB;
    /* 0x7 */ u8 mTevSwapModeInfo;
};

struct J3DIndTevStage {
    J3DIndTevStage() {
        mInfo = 0;
        setIndTevStageInfo(j3dDefaultIndTevStageInfo);
    }

    explicit J3DIndTevStage(const J3DIndTevStageInfo& info) {
        mInfo = 0;
        setIndTevStageInfo(info);
    }

    void setIndStage(u8 stage) { mInfo = mInfo & ~0x03 | stage; }
    void setIndFormat(u8 format) { mInfo = mInfo & ~0x0C | format << 2; }
    void setBiasSel(u8 sel) { mInfo = mInfo & ~0x70 | sel << 4; }
    void setAlphaSel(u8 sel) { mInfo = mInfo & ~0x0180 | sel << 7; }
    void setMtxSel(u8 sel) { mInfo = mInfo & ~0x1E00 | sel << 9; }
    void setWrapS(u8 wrap) { mInfo = mInfo & ~0xE000 | wrap << 13; }
    void setWrapT(u8 wrap) { mInfo = mInfo & ~0x070000 | wrap << 16; }
    void setLod(u8 lod) { mInfo = mInfo & ~0x080000 | lod << 19; }
    void setPrev(u8 prev) { mInfo = mInfo & ~0x100000 | prev << 20; }

    void setIndTevStageInfo(const J3DIndTevStageInfo& info) {
        setIndStage(info.mIndStage);
        setIndFormat(info.mIndFormat);
        setBiasSel(info.mBiasSel);
        setMtxSel(info.mMtxSel);
        setWrapS(info.mWrapS);
        setWrapT(info.mWrapT);
        setPrev(info.mPrev);
        setLod(info.mLod);
        setAlphaSel(info.mAlphaSel);
    }

    void load(u32 param_1) {
        J3DGDWriteBPCmd(mInfo | (param_1 + 16) << 24);
    }

    /* 0x0 */ u32 mInfo;
};

struct J3DTevOrder : public J3DTevOrderInfo {
    J3DTevOrder() { *(J3DTevOrderInfo*)this = j3dDefaultTevOrderInfoNull; }
    explicit J3DTevOrder(const J3DTevOrderInfo& info) { *(J3DTevOrderInfo*)this = info; }

    J3DTevOrderInfo& getTevOrderInfo() { return *this; }
    u8 getTexMap() { return mTexMap; }
};

static inline u8 calcTevSwapTableID(u8 r, u8 g, u8 b, u8 a) {
    return r * 64 + g * 16 + b * 4 + a;
}

struct J3DTevSwapModeTable {
    J3DTevSwapModeTable() { mIdx = j3dDefaultTevSwapTableID; }
    explicit J3DTevSwapModeTable(const J3DTevSwapModeTableInfo& info) { mIdx = calcTevSwapTableID(info.field_0x0, info.field_0x1, info.field_0x2, info.field_0x3); }

    u8 getR() { return j3dTevSwapTableTable[mIdx * 4]; }
    u8 getG() { return j3dTevSwapTableTable[mIdx * 4 + 1]; }
    u8 getB() { return j3dTevSwapTableTable[mIdx * 4 + 2]; }
    u8 getA() { return j3dTevSwapTableTable[mIdx * 4 + 3]; }

    /* 0x0 */ u8 mIdx;
};  // Size: 0x1

class J3DLightObj {
public:
    J3DLightObj() { mInfo = j3dDefaultLightInfo; }
    void load(u32) const;

    J3DLightInfo& getLightInfo() { return mInfo; }
    J3DLightObj& operator=(J3DLightObj const& other) {
        mInfo = other.mInfo;
        return *this;
    }

    /* 0x00 */ J3DLightInfo mInfo;
    /* 0x34 */ u8 field_0x34[64];
};  // Size = 0x74

struct J3DNBTScale : public J3DNBTScaleInfo {
    J3DNBTScale() { *(J3DNBTScaleInfo*)this = j3dDefaultNBTScaleInfo; }
    explicit J3DNBTScale(const J3DNBTScaleInfo& info) { *(J3DNBTScaleInfo*)this = info; }
    Vec* getScale() { return &mScale; }
};

class J3DTexCoord;
void loadTexCoordGens(u32, J3DTexCoord*);
void loadNBTScale(J3DNBTScale& param_0);

#endif /* J3DTEVS_H */
