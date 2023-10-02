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
    J3DTevStage(const J3DTevStageInfo& info) {
        setTevStageInfo(info);
        setTevSwapModeInfo(j3dDefaultTevSwapMode);
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

    void setTexSel(u8 param_0) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x0C | param_0 << 2; }
    void setRasSel(u8 param_0) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x03 | param_0; }
    void setTevSwapModeInfo(const J3DTevSwapModeInfo& info) {
        setTexSel(info.field_0x1);
        setRasSel(info.field_0x0);
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
    /* 0x7 */ u8 mTevSwapModeInfo;
};

struct J3DIndTevStage {
    J3DIndTevStage() {
        mInfo = 0;
        setIndTevStageInfo(j3dDefaultIndTevStageInfo);
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

    J3DTevOrderInfo& getTevOrderInfo() { return *this; }
    u8 getTexMap() { return mTexMap; }
};

struct J3DTevSwapModeTable {
    J3DTevSwapModeTable() { field_0x0 = j3dDefaultTevSwapTableID; }

    u8 getR() { return j3dTevSwapTableTable[field_0x0 * 4]; }
    u8 getG() { return j3dTevSwapTableTable[field_0x0 * 4 + 1]; }
    u8 getB() { return j3dTevSwapTableTable[field_0x0 * 4 + 2]; }
    u8 getA() { return j3dTevSwapTableTable[field_0x0 * 4 + 3]; }

    /* 0x0 */ u8 field_0x0;
};  // Size: 0x1

class J3DLightObj {
public:
    /* 80018C0C */ J3DLightObj() { mInfo = j3dDefaultLightInfo; }
    /* 80323590 */ void load(u32) const;

    J3DLightInfo& getLightInfo() { return mInfo; }
    J3DLightObj& operator=(J3DLightObj const& other) {
        mInfo = other.mInfo;
        return *this;
    }

    /* 0x00 */ J3DLightInfo mInfo;
    /* 0x34 */ u8 field_0x34[64];
};  // Size = 0x74

struct J3DNBTScale : public J3DNBTScaleInfo {
    J3DNBTScale() {}
    J3DNBTScale(J3DNBTScaleInfo const& info) {
        mbHasScale = info.mbHasScale;
        mScale = info.mScale;
    }
    Vec* getScale() { return &mScale; }
};

class J3DTexCoord;
void loadTexCoordGens(u32, J3DTexCoord*);
void loadNBTScale(J3DNBTScale& param_0);

#endif /* J3DTEVS_H */
