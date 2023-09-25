#ifndef J3DMATBLOCK_H
#define J3DMATBLOCK_H

#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/J3DGraphBase/J3DTevs.h"
#include "JSystem/J3DGraphBase/J3DTexture.h"
#include "dolphin/types.h"

struct J3DGXColorS10 : public GXColorS10 {
    J3DGXColorS10() {}
};

struct J3DGXColor : public GXColor {
    J3DGXColor() {}
};

struct J3DNBTScale : public J3DNBTScaleInfo {
    J3DNBTScale() {}
    J3DNBTScale(J3DNBTScaleInfo const& info) {
        mbHasScale = info.mbHasScale;
        mScale = info.mScale;
    }
    Vec* getScale() { return &mScale; }
};

extern const J3DNBTScaleInfo j3dDefaultNBTScaleInfo;

class J3DTexGenBlock {
public:
    virtual void reset(J3DTexGenBlock*);
    virtual void calc(f32 const (*)[4]) = 0;
    virtual void load() = 0;
    virtual void patch() = 0;
    virtual void diff(u32) = 0;
    virtual void diffTexMtx() = 0;
    virtual void diffTexGen() = 0;
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setTexGenNum(u32 const*);
    virtual void setTexGenNum(u32);
    virtual u32 getTexGenNum() const;
    virtual void setTexCoord(u32, J3DTexCoord const*);
    virtual J3DTexCoord* getTexCoord(u32);
    virtual void setTexMtx(u32, J3DTexMtx*);
    virtual J3DTexMtx* getTexMtx(u32);
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual u32 getTexMtxOffset() const;
    virtual void setTexMtxOffset(u32);
    virtual ~J3DTexGenBlock();
};

class J3DTexGenBlockPatched : public J3DTexGenBlock {
public:
    J3DTexGenBlockPatched() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void calc(f32 const (*)[4]);
    virtual void calcWithoutViewMtx(f32 const (*)[4]);
    virtual void calcPostTexMtx(f32 const (*)[4]);
    virtual void calcPostTexMtxWithoutViewMtx(f32 const (*)[4]);
    virtual void load();
    virtual void patch();
    virtual void diff(u32);
    virtual void diffTexMtx();
    virtual void diffTexGen();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setTexGenNum(u32 const*);
    virtual void setTexGenNum(u32);
    virtual u32 getTexGenNum() const;
    virtual void setTexCoord(u32, J3DTexCoord const*);
    virtual J3DTexCoord* getTexCoord(u32);
    virtual void setTexMtx(u32, J3DTexMtx*);
    virtual J3DTexMtx* getTexMtx(u32);
    virtual u32 getTexMtxOffset() const;
    virtual void setTexMtxOffset(u32);
    virtual ~J3DTexGenBlockPatched();

protected:
    /* 0x04 */ u32 mTexGenNum;
    /* 0x08 */ J3DTexCoord mTexCoord[8];
    /* 0x38 */ J3DTexMtx* mTexMtx[8];
    /* 0x58 */ u32 mTexMtxOffset;
};  // Size: 0x5C

class J3DTexGenBlockBasic : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlockBasic() : mNBTScale(j3dDefaultNBTScaleInfo) {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual ~J3DTexGenBlockBasic();

private:
    /* 0x5C */ J3DNBTScale mNBTScale;
};  // Size: 0x6C

class J3DTexGenBlock4 : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlock4() : mNBTScale(j3dDefaultNBTScaleInfo) {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setNBTScale(J3DNBTScale const*);
    virtual void setNBTScale(J3DNBTScale);
    virtual J3DNBTScale* getNBTScale();
    virtual ~J3DTexGenBlock4();

private:
    /* 0x5C */ J3DNBTScale mNBTScale;
};  // Size: 0x6C

class J3DTevBlock {
public:
    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diff(u32);
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex() = 0;
    virtual void indexToPtr() = 0;
    virtual u32 getType() = 0;
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual _GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual _GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32, u8 const*);
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevKAlphaSel(u32, u8 const*);
    virtual void setTevKAlphaSel(u32, u8);
    virtual u8 getTevKAlphaSel(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo const*);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable const*);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable);
    virtual J3DTevSwapModeTable * getTevSwapModeTable(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const;
    virtual void setTexNoOffset(u32);
    virtual void setTevRegOffset(u32);
    virtual ~J3DTevBlock();

protected:
    void indexToPtr_private(u32);

    /* 0x4 */ u32 mTexNoOffset;
};

class J3DTevBlockPatched : public J3DTevBlock {
public:
    J3DTevBlockPatched() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr();
    virtual u32 getType();
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32, u8 const*);
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const;
    virtual void setTevRegOffset(u32);
    virtual ~J3DTevBlockPatched();

private:
    /* 0x08 */ u16 mTexNo[8];
    /* 0x18 */ J3DTevOrder mTevOrder[8];
    /* 0x38 */ J3DTevStage mTevStage[8];
    /* 0x78 */ J3DIndTevStage mIndTevStage[8];
    /* 0x98 */ GXColorS10 mTevColor[4];
    /* 0xB8 */ GXColor mTevKColor[4];
    /* 0xC8 */ u8 mTevKColorSel[8];
    /* 0xD0 */ u8 mTevStageNum;
    /* 0xD4 */ u32 mTevRegOffset;
};  // Size: 0xD8

class J3DTevBlockNull : public J3DTevBlock {
    void initialize();
};

class J3DTevBlock4 : public J3DTevBlock {
public:
    J3DTevBlock4() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr();
    virtual u32 getType();
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32, u8 const*);
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevKAlphaSel(u32, u8 const*);
    virtual void setTevKAlphaSel(u32, u8);
    virtual u8 getTevKAlphaSel(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo const*);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable const*);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable);
    virtual J3DTevSwapModeTable * getTevSwapModeTable(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const;
    virtual void setTevRegOffset(u32);
    virtual ~J3DTevBlock4();

private:
    /* 0x08 */ u16 mTexNo[4];
    /* 0x10 */ J3DTevOrder mTevOrder[4];
    /* 0x20 */ u8 mTevStageNum;
    /* 0x21 */ J3DTevStage mTevStage[4];
    /* 0x42 */ GXColorS10 mTevColor[4];
    /* 0x62 */ GXColor mTevKColor[4];
    /* 0x72 */ u8 mTevKColorSel[4];
    /* 0x76 */ u8 mTevKAlphaSel[4];
    /* 0x7A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x80 */ J3DIndTevStage mIndTevStage[4];
    /* 0x90 */ u32 mTevRegOffset;
};  // Size: 0x94

class J3DTevBlock2 : public J3DTevBlock {
public:
    J3DTevBlock2() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr();
    virtual u32 getType();
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32, u8 const*);
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevKAlphaSel(u32, u8 const*);
    virtual void setTevKAlphaSel(u32, u8);
    virtual u8 getTevKAlphaSel(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo const*);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable const*);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable);
    virtual J3DTevSwapModeTable * getTevSwapModeTable(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const;
    virtual void setTevRegOffset(u32);
    virtual ~J3DTevBlock2();

private:
    /* 0x08 */ u16 mTexNo[2];
    /* 0x0C */ J3DTevOrder mTevOrder[2];
    /* 0x14 */ GXColorS10 mTevColor[4];
    /* 0x34 */ u8 mTevStageNum;
    /* 0x35 */ J3DTevStage mTevStage[2];
    /* 0x45 */ GXColor mTevKColor[4];
    /* 0x55 */ u8 mTevKColorSel[2];
    /* 0x57 */ u8 mTevKAlphaSel[2];
    /* 0x59 */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x60 */ J3DIndTevStage mIndTevStage[2];
    /* 0x68 */ u32 mTevRegOffset;
};  // Size: 0x6C

class J3DTevBlock16 : public J3DTevBlock {
public:
    J3DTevBlock16() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr();
    virtual u32 getType();
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevColor(u32, J3DGXColorS10 const*);
    virtual void setTevColor(u32, J3DGXColorS10);
    virtual GXColorS10* getTevColor(u32);
    virtual void setTevKColor(u32, J3DGXColor const*);
    virtual void setTevKColor(u32, J3DGXColor);
    virtual GXColor* getTevKColor(u32);
    virtual void setTevKColorSel(u32, u8 const*);
    virtual void setTevKColorSel(u32, u8);
    virtual u8 getTevKColorSel(u32);
    virtual void setTevKAlphaSel(u32, u8 const*);
    virtual void setTevKAlphaSel(u32, u8);
    virtual u8 getTevKAlphaSel(u32);
    virtual void setTevStageNum(u8);
    virtual void setTevStageNum(u8 const*);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo const*);
    virtual void setTevSwapModeInfo(u32, J3DTevSwapModeInfo);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable const*);
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable);
    virtual J3DTevSwapModeTable * getTevSwapModeTable(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual u32 getTevRegOffset() const;
    virtual void setTevRegOffset(u32);
    virtual ~J3DTevBlock16();

private:
    /* 0x008 */ u16 mTexNo[8];
    /* 0x018 */ J3DTevOrder mTevOrder[16];
    /* 0x058 */ u8 mTevStageNum;
    /* 0x059 */ J3DTevStage mTevStage[16];
    /* 0x0DA */ GXColorS10 mTevColor[4];
    /* 0x0FA */ GXColor mTevKColor[4];
    /* 0x10A */ u8 mTevKColorSel[16];
    /* 0x11A */ u8 mTevKAlphaSel[16];
    /* 0x12A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x130 */ J3DIndTevStage mIndTevStage[16];
    /* 0x170 */ u32 mTevRegOffset;
};  // Size: 0x174

class J3DTevBlock1 : public J3DTevBlock {
public:
    J3DTevBlock1() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load();
    virtual void diffTexNo();
    virtual void diffTevReg();
    virtual void diffTexCoordScale();
    virtual void diffTevStage();
    virtual void diffTevStageIndirect();
    virtual void patch();
    virtual void patchTexNo();
    virtual void patchTevReg();
    virtual void patchTexNoAndTexCoordScale();
    virtual void ptrToIndex();
    virtual void indexToPtr();
    virtual u32 getType();
    virtual s32 countDLSize();
    virtual void setTexNo(u32, u16 const*);
    virtual void setTexNo(u32, u16);
    virtual u16 getTexNo(u32) const;
    virtual void setTevOrder(u32, J3DTevOrder const*);
    virtual void setTevOrder(u32, J3DTevOrder);
    virtual J3DTevOrder* getTevOrder(u32);
    virtual void setTevStageNum(u8 const*);
    virtual void setTevStageNum(u8);
    virtual u8 getTevStageNum() const;
    virtual void setTevStage(u32, J3DTevStage const*);
    virtual void setTevStage(u32, J3DTevStage);
    virtual J3DTevStage * getTevStage(u32);
    virtual void setIndTevStage(u32, J3DIndTevStage const*);
    virtual void setIndTevStage(u32, J3DIndTevStage);
    virtual J3DIndTevStage * getIndTevStage(u32);
    virtual u32 getTexNoOffset() const;
    virtual ~J3DTevBlock1();

private:
    /* 0x08 */ u16 mTexNo[1];
    /* 0x0A */ J3DTevOrder mTevOrder[1];
    /* 0x0E */ J3DTevStage mTevStage[1];
    /* 0x18 */ J3DIndTevStage mIndTevStage[1];
};  // Size: 0x1C

extern const u16 j3dDefaultZModeID;

inline u16 calcZModeID(u8 param_0, u8 param_1, u8 param_2) {
    return ((param_1 * 2) & 0x1FE) + (param_0 * 0x10) + param_2;
}

struct J3DZModeInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
};

struct J3DZMode {
    J3DZMode() {
        mZModeID = j3dDefaultZModeID;
    }

    void setZModeInfo(const J3DZModeInfo& info) {
        mZModeID = calcZModeID(info.field_0x0, info.field_0x1, info.field_0x2);
    }

    /* 0x0 */ u16 mZModeID;
};

struct J3DBlendInfo {
    /* 0x0 */ u8 mType;
    /* 0x1 */ u8 mSrcFactor;
    /* 0x2 */ u8 mDstFactor;
    /* 0x3 */ u8 mOp;
};

extern const J3DBlendInfo j3dDefaultBlendInfo;

struct J3DBlend : public J3DBlendInfo {
    J3DBlend() {
        *(J3DBlendInfo*)this = j3dDefaultBlendInfo;
    }
};

extern const J3DFogInfo j3dDefaultFogInfo;

struct J3DFog : public J3DFogInfo {
    J3DFog() {
        *getFogInfo() = j3dDefaultFogInfo;
    }
    J3DFogInfo* getFogInfo() { return (J3DFogInfo*)this; }
};

struct J3DAlphaCompInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 mRef0;
    /* 0x3 */ u8 mRef1;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
};

extern const u16 j3dDefaultAlphaCmpID;

inline u32 calcAlphaCmpID(u32 param_1, u32 param_2, u32 param_3) {
    return ((param_1 & 0xff) << 5) + ((param_2 & 0xff) << 3) + (param_3 & 0xff);
}

struct J3DAlphaComp {
    J3DAlphaComp() {
        field_0x0 = j3dDefaultAlphaCmpID;
        mRef0 = 0;
        mRef1 = 0;
    }

    void setAlphaCompInfo(const J3DAlphaCompInfo& param_1) {
        mRef0 = param_1.field_0x1;
        mRef1 = param_1.field_0x4;
        u32 p1_mref1 = param_1.mRef1;
        field_0x0 = calcAlphaCmpID(param_1.field_0x0, param_1.mRef0, p1_mref1);

        // this matches for `dKy_bg_MAxx_proc` but causes `addWarpMaterial` to fail,
        // while the above matches for `addWarpMaterial` but causes `dKy_bg_MAxx_proc` to fail?
        // field_0x0 = calcAlphaCmpID(param_1.field_0x0, param_1.mRef0, param_1.mRef1);
    }

    /* 0x00 */ u16 field_0x0;
    /* 0x02 */ u8 mRef0;
    /* 0x03 */ u8 mRef1;
};  // Size: 0x4

class J3DPEBlock {
public:
    virtual void reset(J3DPEBlock*);
    virtual void load() = 0;
    virtual void patch();
    virtual void diff(u32);
    virtual void diffFog();
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setFog(J3DFog*);
    virtual J3DFog* getFog();
    virtual void setAlphaComp(J3DAlphaComp const*);
    virtual void setAlphaComp(J3DAlphaComp);
    virtual J3DAlphaComp* getAlphaComp();
    virtual void setBlend(J3DBlend const*);
    virtual void setBlend(J3DBlend);
    virtual J3DBlend* getBlend();
    virtual void setZMode(J3DZMode const*);
    virtual void setZMode(J3DZMode);
    virtual J3DZMode* getZMode();
    virtual void setZCompLoc(u8 const*);
    virtual void setZCompLoc(u8);
    virtual u8 getZCompLoc() const;
    virtual void setDither(u8 const*);
    virtual void setDither(u8);
    virtual u8 getDither() const;
    virtual u32 getFogOffset() const;
    virtual void setFogOffset(u32);
    virtual ~J3DPEBlock();
};

class J3DPEBlockXlu : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockXlu();
};

class J3DPEBlockTexEdge : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockTexEdge();
};

class J3DPEBlockOpa : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual ~J3DPEBlockOpa();
};

class J3DPEBlockFull : public J3DPEBlock {
public:
    J3DPEBlockFull() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void patch();
    virtual void diff(u32);
    virtual void diffFog();
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setFog(J3DFog*);
    virtual J3DFog* getFog();
    virtual void setAlphaComp(J3DAlphaComp const*);
    virtual void setAlphaComp(J3DAlphaComp);
    virtual J3DAlphaComp* getAlphaComp();
    virtual void setBlend(J3DBlend const*);
    virtual void setBlend(J3DBlend);
    virtual J3DBlend* getBlend();
    virtual void setZMode(J3DZMode const*);
    virtual void setZMode(J3DZMode);
    virtual J3DZMode* getZMode();
    virtual void setZCompLoc(u8 const*);
    virtual void setZCompLoc(u8);
    virtual u8 getZCompLoc() const;
    virtual void setDither(u8 const*);
    virtual void setDither(u8);
    virtual u8 getDither() const;
    virtual u32 getFogOffset() const;
    virtual void setFogOffset(u32);
    virtual ~J3DPEBlockFull();

private:
    /* 0x04 */ J3DFog * mFog;
    /* 0x08 */ J3DAlphaComp mAlphaComp;
    /* 0x0C */ J3DBlend mBlend;
    /* 0x10 */ J3DZMode mZMode;
    /* 0x14 */ u8 mZCompLoc;
    /* 0x15 */ u8 mDither;
    /* 0x18 */ u32 mFogOffset;
};  // Size: 0x1C

class J3DPEBlockFogOff : public J3DPEBlock {
public:
    J3DPEBlockFogOff() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void diff(u32);
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setAlphaComp(J3DAlphaComp const*);
    virtual void setAlphaComp(J3DAlphaComp);
    virtual J3DAlphaComp* getAlphaComp();
    virtual void setBlend(J3DBlend const*);
    virtual void setBlend(J3DBlend);
    virtual J3DBlend* getBlend();
    virtual void setZMode(J3DZMode const*);
    virtual void setZMode(J3DZMode);
    virtual J3DZMode* getZMode();
    virtual void setZCompLoc(u8 const*);
    virtual void setZCompLoc(u8);
    virtual u8 getZCompLoc() const;
    virtual void setDither(u8 const*);
    virtual void setDither(u8);
    virtual u8 getDither() const;
    virtual ~J3DPEBlockFogOff();

private:
    /* 0x04 */ J3DAlphaComp mAlphaComp;
    /* 0x08 */ J3DBlend mBlend;
    /* 0x0C */ J3DZMode mZMode;
    /* 0x0E */ u8 mZCompLoc;
    /* 0x0F */ u8 mDither;
};  // Size: 0x10

struct J3DIndTexCoordScale {
    ~J3DIndTexCoordScale();
    J3DIndTexCoordScale();

    /* 0x0 */ u8 mScaleS __attribute__((aligned(4)));
    /* 0x1 */ u8 mScaleT;
};

struct J3DIndTexMtx {
    ~J3DIndTexMtx();
    J3DIndTexMtx();

    /* 0x00 */ Mtx23 mOffsetMtx;
    /* 0x18 */ u8 mScaleExp;
};  // Size: 0x1C

struct J3DIndTexOrder {
    J3DIndTexOrder();

    /* 0x0 */ u8 mMap;
    /* 0x1 */ u8 mCoord;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
};

class J3DIndBlock {
public:
    virtual void reset(J3DIndBlock*);
    virtual void diff(u32) = 0;
    virtual void load() = 0;
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setIndTexStageNum(u8);
    virtual u8 getIndTexStageNum() const;
    virtual void setIndTexOrder(u32, J3DIndTexOrder);
    virtual void setIndTexOrder(u32, J3DIndTexOrder const*);
    virtual J3DIndTexOrder * getIndTexOrder(u32);
    virtual void setIndTexMtx(u32, J3DIndTexMtx const*);
    virtual void setIndTexMtx(u32, J3DIndTexMtx);
    virtual J3DIndTexMtx * getIndTexMtx(u32);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale const*);
    virtual J3DIndTexCoordScale * getIndTexCoordScale(u32);
    virtual ~J3DIndBlock() {}
};

class J3DIndBlockFull : public J3DIndBlock {
public:
    J3DIndBlockFull() {
        initialize();
    }
    void initialize();

    virtual void reset(J3DIndBlock*);
    virtual void diff(u32);
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setIndTexStageNum(u8);
    virtual u8 getIndTexStageNum() const;
    virtual void setIndTexOrder(u32, J3DIndTexOrder);
    virtual void setIndTexOrder(u32, J3DIndTexOrder const*);
    virtual J3DIndTexOrder * getIndTexOrder(u32);
    virtual void setIndTexMtx(u32, J3DIndTexMtx const*);
    virtual void setIndTexMtx(u32, J3DIndTexMtx);
    virtual J3DIndTexMtx * getIndTexMtx(u32);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale const*);
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale);
    virtual J3DIndTexCoordScale * getIndTexCoordScale(u32);
    virtual ~J3DIndBlockFull();

private:
    /* 0x04 */ u8 mIndTexStageNum;
    /* 0x05 */ J3DIndTexOrder mIndTexOrder[4];
    /* 0x18 */ J3DIndTexMtx mIndTexMtx[3];
    /* 0x6C */ J3DIndTexCoordScale mIndTexCoordScale[4];
};  // Size: 0x7C

class J3DIndBlockNull : public J3DIndBlock {
public:
    virtual void reset(J3DIndBlock*);
    virtual void diff(u32);
    virtual void load();
    virtual u32 getType();
    virtual ~J3DIndBlockNull();
};

struct J3DColorChanInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
};

struct J3DColorChan {
    J3DColorChan();
    u8 getLightMask() { return (((mColorChanID & 0x7800) >> 7) | (mColorChanID & 0x3c) >> 2); }
    void setLightMask(u8 param_1) {
        mColorChanID = (mColorChanID & ~0x3c) | ((param_1 & 0xf) << 2);
        mColorChanID = (mColorChanID & ~0x7800) | ((param_1 & 0xf0) << 7);
    }

    /* 0x0 */ u16 mColorChanID;
};

class J3DColorBlock {
public:
    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType() = 0;
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setLight(u32, J3DLightObj*);
    virtual J3DLightObj* getLight(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlock();
};

class J3DColorBlockLightOn : public J3DColorBlock {
public:
    J3DColorBlockLightOn() {
        initialize();
    }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setLight(u32, J3DLightObj*);
    virtual J3DLightObj* getLight(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlockLightOn();

private:
    /* 0x04 */ GXColor mMatColor[2];
    /* 0x0C */ GXColor mAmbColor[2];
    /* 0x14 */ u8 mColorChanNum;
    /* 0x16 */ J3DColorChan mColorChan[4];
    /* 0x20 */ J3DLightObj* mLight[8];
    /* 0x40 */ u8 mCullMode;
    /* 0x44 */ u32 mMatColorOffset;
    /* 0x48 */ u32 mColorChanOffset;
};  // Size: 0x4C

class J3DColorBlockLightOff : public J3DColorBlock {
public:
    J3DColorBlockLightOff() {
        initialize();
    }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setMatColor(u32, J3DGXColor const*);
    virtual void setMatColor(u32, J3DGXColor);
    virtual GXColor* getMatColor(u32);
    virtual void setColorChanNum(u8);
    virtual void setColorChanNum(u8 const*);
    virtual u8 getColorChanNum() const;
    virtual void setColorChan(u32, J3DColorChan const&);
    virtual void setColorChan(u32, J3DColorChan const*);
    virtual J3DColorChan* getColorChan(u32);
    virtual void setCullMode(u8 const*);
    virtual void setCullMode(u8);
    virtual u8 getCullMode() const;
    virtual u32 getMatColorOffset() const;
    virtual u32 getColorChanOffset() const;
    virtual void setMatColorOffset(u32);
    virtual void setColorChanOffset(u32);
    virtual ~J3DColorBlockLightOff();

protected:
    /* 0x04 */ GXColor mMatColor[2];
    /* 0x0C */ u8 mColorChanNum;
    /* 0x0E */ J3DColorChan mColorChan[4];
    /* 0x16 */ u8 mCullMode;
    /* 0x18 */ u32 mMatColorOffset;
    /* 0x1C */ u32 mColorChanOffset;
};  // Size: 0x20

class J3DColorBlockAmbientOn : public J3DColorBlockLightOff {
public:
    J3DColorBlockAmbientOn() {
        initialize();
    }
    void initialize();

    virtual void load();
    virtual void reset(J3DColorBlock*);
    virtual s32 countDLSize();
    virtual u32 getType();
    virtual void setAmbColor(u32, J3DGXColor const*);
    virtual void setAmbColor(u32, J3DGXColor);
    virtual GXColor* getAmbColor(u32);
    virtual ~J3DColorBlockAmbientOn();

protected:
    /* 0x20 */ GXColor mAmbColor[2];
};  // Size: 0x28

#endif /* J3DMATBLOCK_H */
