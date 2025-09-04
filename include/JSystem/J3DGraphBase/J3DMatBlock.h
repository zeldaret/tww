#ifndef J3DMATBLOCK_H
#define J3DMATBLOCK_H

#include "JSystem/J3DGraphBase/J3DGD.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/J3DGraphBase/J3DTevs.h"
#include "JSystem/J3DGraphBase/J3DTexture.h"
#include "dolphin/gx/GXEnum.h"

struct J3DGXColorS10 {
    J3DGXColorS10() {}
    J3DGXColorS10(const GXColorS10& other) { mColor = other; }
    J3DGXColorS10(const J3DGXColorS10& other) { mColor = other.mColor; }
    J3DGXColorS10& operator=(const J3DGXColorS10& other) {
        mColor = other.mColor;
        return *this;
    }
    J3DGXColorS10& operator=(const GXColorS10& color) {
        mColor = color;
        return *this;
    }

    GXColorS10 mColor;
};

struct J3DGXColor {
    J3DGXColor() {}
    J3DGXColor(const GXColor& other) { mColor = other; }
    J3DGXColor(const J3DGXColor& other) { mColor = other.mColor; }
    J3DGXColor& operator=(const J3DGXColor& other) {
        mColor = other.mColor;
        return *this;
    }
    J3DGXColor& operator=(const GXColor& color) {
        mColor = color;
        return *this;
    }

    GXColor mColor;
};

class J3DTexGenBlock {
public:
    virtual void reset(J3DTexGenBlock*) {}
    virtual void calc(const Mtx) = 0;
    virtual void load() = 0;
    virtual void patch() = 0;
    virtual void diff(u32) = 0;
    virtual void diffTexMtx() = 0;
    virtual void diffTexGen() = 0;
    virtual s32 countDLSize() { return 0; }
    virtual u32 getType() = 0;
    virtual void setTexGenNum(u32 const*) {}
    virtual void setTexGenNum(u32) {}
    virtual u32 getTexGenNum() const { return 0; }
    virtual void setTexCoord(u32, J3DTexCoord const*) {}
    virtual J3DTexCoord* getTexCoord(u32) { return NULL; }
    virtual void setTexMtx(u32, J3DTexMtx*) {}
    virtual J3DTexMtx* getTexMtx(u32) { return NULL; }
    virtual void setNBTScale(J3DNBTScale const*) {}
    virtual void setNBTScale(J3DNBTScale) {}
    virtual J3DNBTScale* getNBTScale() { return NULL; }
    virtual u32 getTexMtxOffset() const { return 0; }
    virtual void setTexMtxOffset(u32) {}
    virtual ~J3DTexGenBlock() {}
};

class J3DTexGenBlockPatched : public J3DTexGenBlock {
public:
    J3DTexGenBlockPatched() { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void calc(const Mtx);
    virtual void load() {}
    virtual void patch();
    virtual void diff(u32);
    virtual void diffTexMtx();
    virtual void diffTexGen();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'TGPT'; }
    virtual void setTexGenNum(u32 const* pNum) { mTexGenNum = *pNum; }
    virtual void setTexGenNum(u32 num) { mTexGenNum = num; }
    virtual u32 getTexGenNum() const { return mTexGenNum; }
    virtual void setTexCoord(u32 idx, J3DTexCoord const* pCoord) { mTexCoord[idx] = *pCoord; }
    virtual J3DTexCoord* getTexCoord(u32 idx) { return &mTexCoord[idx]; }
    virtual void setTexMtx(u32 idx, J3DTexMtx* pMtx) { mTexMtx[idx] = pMtx; }
    virtual J3DTexMtx* getTexMtx(u32 idx) { return mTexMtx[idx]; }
    virtual u32 getTexMtxOffset() const { return mTexMtxOffset; }
    virtual void setTexMtxOffset(u32 offs) { mTexMtxOffset = offs; }
    virtual ~J3DTexGenBlockPatched() {}

protected:
    /* 0x04 */ u32 mTexGenNum;
    /* 0x08 */ J3DTexCoord mTexCoord[8];
    /* 0x28 */ J3DTexMtx* mTexMtx[8];
    /* 0x48 */ u32 mTexMtxOffset;
};  // Size: 0x4C

class J3DTexGenBlockBasic : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlockBasic() : mNBTScale(j3dDefaultNBTScaleInfo) { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'TGBC'; }
    virtual void setNBTScale(J3DNBTScale const* pScale) { mNBTScale = *pScale; }
    virtual void setNBTScale(J3DNBTScale scale) { mNBTScale = scale; }
    virtual J3DNBTScale* getNBTScale() { return &mNBTScale; }
    virtual ~J3DTexGenBlockBasic() {}

private:
    /* 0x4C */ J3DNBTScale mNBTScale;
};  // Size: 0x5C

class J3DTexGenBlock4 : public J3DTexGenBlockPatched {
public:
    J3DTexGenBlock4() : mNBTScale(j3dDefaultNBTScaleInfo) { initialize(); }
    void initialize();

    virtual void reset(J3DTexGenBlock*);
    virtual void load();
    virtual void patch();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'TGB4'; }
    virtual void setNBTScale(J3DNBTScale const* pScale) { mNBTScale = *pScale; }
    virtual void setNBTScale(J3DNBTScale scale) { mNBTScale = scale; }
    virtual J3DNBTScale* getNBTScale() { return &mNBTScale; }
    virtual ~J3DTexGenBlock4() {}

private:
    /* 0x4C */ J3DNBTScale mNBTScale;
};  // Size: 0x5C

class J3DTexGenBlockNull : public J3DTexGenBlock {
public:
    virtual void calc(const Mtx) {}
    virtual void load() {}
    virtual void patch() {}
    virtual void diff(u32) {}
    virtual void diffTexMtx() {}
    virtual void diffTexGen() {}
    virtual u32 getType() { return 'TGNL'; }
    virtual ~J3DTexGenBlockNull() {}
};

class J3DTevBlock {
public:
    virtual void reset(J3DTevBlock*) {}
    virtual void load() {}
    virtual void diff(u32);
    virtual void diffTexNo() {}
    virtual void diffTevReg() {}
    virtual void diffTexCoordScale() {}
    virtual void diffTevStage() {}
    virtual void diffTevStageIndirect() {}
    virtual void patch() {}
    virtual void patchTexNo() {}
    virtual void patchTevReg() {}
    virtual void patchTexNoAndTexCoordScale() {}
    virtual void ptrToIndex() = 0;
    virtual void indexToPtr() = 0;
    virtual u32 getType() = 0;
    virtual s32 countDLSize() { return 0; }
    virtual void setTexNo(u32, u16 const*) {}
    virtual void setTexNo(u32, u16) {}
    virtual u16 getTexNo(u32) const { return -1; }
    virtual void setTevOrder(u32, J3DTevOrder const*) {}
    virtual void setTevOrder(u32, J3DTevOrder) {}
    virtual J3DTevOrder* getTevOrder(u32) { return NULL; }
    virtual void setTevColor(u32, J3DGXColorS10 const*) {}
    virtual void setTevColor(u32, J3DGXColorS10) {}
    virtual J3DGXColorS10* getTevColor(u32) { return NULL; }
    virtual void setTevKColor(u32, J3DGXColor const*) {}
    virtual void setTevKColor(u32, J3DGXColor) {}
    virtual J3DGXColor* getTevKColor(u32) { return NULL; }
    virtual void setTevKColorSel(u32 idx, const u8* pNum) {}
    virtual void setTevKColorSel(u32, u8) {}
    virtual u8 getTevKColorSel(u32) { return 0; }
    virtual void setTevKAlphaSel(u32 idx, const u8* pNum) {}
    virtual void setTevKAlphaSel(u32, u8) {}
    virtual u8 getTevKAlphaSel(u32) { return 0; }
    virtual void setTevStageNum(u8 const*) {}
    virtual void setTevStageNum(u8) {}
    virtual u8 getTevStageNum() const { return 1; }
    virtual void setTevStage(u32, J3DTevStage const*) {}
    virtual void setTevStage(u32, J3DTevStage) {}
    virtual J3DTevStage* getTevStage(u32) { return NULL; }
    virtual void setTevSwapModeInfo(u32 idx, const J3DTevSwapModeInfo* pInfo) {}
    virtual void setTevSwapModeInfo(u32 idx, J3DTevSwapModeInfo info) {}
    virtual void setTevSwapModeTable(u32 idx, const J3DTevSwapModeTable* pTable) {}
    virtual void setTevSwapModeTable(u32, J3DTevSwapModeTable) {}
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32) { return NULL; }
    virtual void setIndTevStage(u32, J3DIndTevStage const*) {}
    virtual void setIndTevStage(u32, J3DIndTevStage) {}
    virtual J3DIndTevStage* getIndTevStage(u32) { return NULL; }
    virtual u32 getTexNoOffset() const { return 0; }
    virtual u32 getTevRegOffset() const { return 0; }
    virtual void setTexNoOffset(u32 offs) { mTexNoOffset = offs; }
    virtual void setTevRegOffset(u32 offs) {}
    virtual ~J3DTevBlock() {}

protected:
    void indexToPtr_private(u32);

    /* 0x4 */ u32 mTexNoOffset;
};

class J3DTevBlockPatched : public J3DTevBlock {
public:
    J3DTevBlockPatched() { initialize(); }
    void initialize();

    virtual void reset(J3DTevBlock*);
    virtual void load() {}
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
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVPT'; }
    virtual s32 countDLSize();
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTexNo(u32 idx, const u16* pNo) { mTexNo[idx] = *pNo; }
    virtual void setTexNo(u32 idx, u16 no) { mTexNo[idx] = no; }
    virtual u16 getTexNo(u32 idx) const {
        J3D_ASSERT(1353, idx < 8, "Error : range over.");
        return mTexNo[idx];
    }
    virtual void setTevOrder(u32 idx, const J3DTevOrder* pOrder) { mTevOrder[idx] = *pOrder; }
    virtual void setTevOrder(u32 idx, J3DTevOrder order) { mTevOrder[idx] = order; }
    virtual J3DTevOrder* getTevOrder(u32 idx) { return &mTevOrder[idx]; }
    virtual void setTevStage(u32 idx, const J3DTevStage* pStage) { mTevStage[idx] = *pStage; }
    virtual void setTevStage(u32 idx, J3DTevStage stage) { mTevStage[idx] = stage; }
    virtual J3DTevStage* getTevStage(u32 idx) { return &mTevStage[idx]; }
    virtual void setIndTevStage(u32 idx, const J3DIndTevStage* pStage) { mIndTevStage[idx] = *pStage; }
    virtual void setIndTevStage(u32 idx, J3DIndTevStage stage) { mIndTevStage[idx] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 idx) { return &mIndTevStage[idx]; }
    virtual void setTevColor(u32 idx, const J3DGXColorS10* pColor) { mTevColor[idx] = *pColor; }
    virtual void setTevColor(u32 idx, J3DGXColorS10 color) { mTevColor[idx] = color; }
    virtual J3DGXColorS10* getTevColor(u32 idx) { return &mTevColor[idx]; }
    virtual void setTevKColor(u32 idx, const J3DGXColor* pColor) { mTevKColor[idx] = *pColor; }
    virtual void setTevKColor(u32 idx, J3DGXColor color) { mTevKColor[idx] = color; }
    virtual J3DGXColor* getTevKColor(u32 idx) { return &mTevKColor[idx]; }
    virtual void setTevKColorSel(u32 idx, const u8* pSel) { mTevKColorSel[idx] = *pSel; }
    virtual void setTevKColorSel(u32 idx, u8 sel) { mTevKColorSel[idx] = sel; }
    virtual u8 getTevKColorSel(u32 idx) { return mTevKColorSel[idx]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }

    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlockPatched() {}

private:
    /* 0x08 */ u16 mTexNo[8];
    /* 0x18 */ J3DTevOrder mTevOrder[8];
    /* 0x38 */ J3DTevStage mTevStage[8];
    /* 0x78 */ J3DIndTevStage mIndTevStage[8];
    /* 0x98 */ J3DGXColorS10 mTevColor[4];
    /* 0xB8 */ J3DGXColor mTevKColor[4];
    /* 0xC8 */ u8 mTevKColorSel[8];
    /* 0xD0 */ u8 mTevStageNum;
    /* 0xD4 */ u32 mTevRegOffset;
};  // Size: 0xD8

class J3DTevBlockNull : public J3DTevBlock {
public:
    J3DTevBlockNull() { initialize(); }
    virtual void reset(J3DTevBlock*) {}
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVNL'; }
    virtual ~J3DTevBlockNull() {}

    void initialize();
};

class J3DTevBlock4 : public J3DTevBlock {
public:
    J3DTevBlock4() { initialize(); }
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
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB4'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 idx, const u16* pNo) { mTexNo[idx] = *pNo; }
    virtual void setTexNo(u32 idx, u16 no) { mTexNo[idx] = no; }
    virtual u16 getTexNo(u32 idx) const {
        J3D_ASSERT(2019, idx < 4, "Error : range over.");
        return mTexNo[idx];
    }
    virtual void setTevOrder(u32 idx, const J3DTevOrder* pOrder) { mTevOrder[idx] = *pOrder; }
    virtual void setTevOrder(u32 idx, J3DTevOrder order) { mTevOrder[idx] = order; }
    virtual J3DTevOrder* getTevOrder(u32 idx) { return &mTevOrder[idx]; }
    virtual void setTevColor(u32 idx, const J3DGXColorS10* pColor) { mTevColor[idx] = *pColor; }
    virtual void setTevColor(u32 idx, J3DGXColorS10 color) { mTevColor[idx] = color; }
    virtual J3DGXColorS10* getTevColor(u32 idx) { return &mTevColor[idx]; }
    virtual void setTevKColor(u32 idx, const J3DGXColor* pColor) { mTevKColor[idx] = *pColor; }
    virtual void setTevKColor(u32 idx, J3DGXColor color) { mTevKColor[idx] = color; }
    virtual J3DGXColor* getTevKColor(u32 idx) { return &mTevKColor[idx]; }
    virtual void setTevKColorSel(u32 idx, const u8* pNum) { mTevKColorSel[idx] = *pNum; }
    virtual void setTevKColorSel(u32 idx, u8 num) { mTevKColorSel[idx] = num; }
    virtual u8 getTevKColorSel(u32 idx) { return mTevKColorSel[idx]; }
    virtual void setTevKAlphaSel(u32 idx, const u8* pNum) { mTevKAlphaSel[idx] = *pNum; }
    virtual void setTevKAlphaSel(u32 idx, u8 num) { mTevKAlphaSel[idx] = num; }
    virtual u8 getTevKAlphaSel(u32 idx) { return mTevKAlphaSel[idx]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 idx, const J3DTevStage* pStage) { mTevStage[idx] = *pStage; }
    virtual void setTevStage(u32 idx, J3DTevStage stage) { mTevStage[idx] = stage; }
    virtual J3DTevStage* getTevStage(u32 idx) { return &mTevStage[idx]; }
    virtual void setTevSwapModeInfo(u32 idx, const J3DTevSwapModeInfo* pInfo) { mTevStage[idx].setTevSwapModeInfo(*pInfo); }
    virtual void setTevSwapModeInfo(u32 idx, J3DTevSwapModeInfo info) { mTevStage[idx].setTevSwapModeInfo(info); }
    virtual void setTevSwapModeTable(u32 idx, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[idx] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 idx, J3DTevSwapModeTable table) {
        mTevSwapModeTable[idx] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 idx) { return &mTevSwapModeTable[idx]; }
    virtual void setIndTevStage(u32 idx, const J3DIndTevStage* pStage) { mIndTevStage[idx] = *pStage; }
    virtual void setIndTevStage(u32 idx, J3DIndTevStage stage) { mIndTevStage[idx] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 idx) { return &mIndTevStage[idx]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock4() {}

private:
    /* 0x08 */ u16 mTexNo[4];
    /* 0x10 */ J3DTevOrder mTevOrder[4];
    /* 0x20 */ u8 mTevStageNum;
    /* 0x21 */ J3DTevStage mTevStage[4];
    /* 0x42 */ J3DGXColorS10 mTevColor[4];
    /* 0x62 */ J3DGXColor mTevKColor[4];
    /* 0x72 */ u8 mTevKColorSel[4];
    /* 0x76 */ u8 mTevKAlphaSel[4];
    /* 0x7A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x80 */ J3DIndTevStage mIndTevStage[4];
    /* 0x90 */ u32 mTevRegOffset;
};  // Size: 0x94

class J3DTevBlock2 : public J3DTevBlock {
public:
    J3DTevBlock2() { initialize(); }
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
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB2'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 idx, const u16* pNo) { mTexNo[idx] = *pNo; }
    virtual void setTexNo(u32 idx, u16 no) { mTexNo[idx] = no; }
    virtual u16 getTexNo(u32 idx) const {
        J3D_ASSERT(1730, idx < 2, "Error : range over.");
        return mTexNo[idx];
    }
    virtual void setTevOrder(u32 idx, const J3DTevOrder* pOrder) { mTevOrder[idx] = *pOrder; }
    virtual void setTevOrder(u32 idx, J3DTevOrder order) { mTevOrder[idx] = order; }
    virtual J3DTevOrder* getTevOrder(u32 idx) { return &mTevOrder[idx]; }
    virtual void setTevColor(u32 idx, const J3DGXColorS10* pColor) { mTevColor[idx] = *pColor; }
    virtual void setTevColor(u32 idx, J3DGXColorS10 color) { mTevColor[idx] = color; }
    virtual J3DGXColorS10* getTevColor(u32 idx) { return &mTevColor[idx]; }
    virtual void setTevKColor(u32 idx, const J3DGXColor* pColor) { mTevKColor[idx] = *pColor; }
    virtual void setTevKColor(u32 idx, J3DGXColor color) { mTevKColor[idx] = color; }
    virtual J3DGXColor* getTevKColor(u32 idx) { return &mTevKColor[idx]; }
    virtual void setTevKColorSel(u32 idx, const u8* pNum) { mTevKColorSel[idx] = *pNum; }
    virtual void setTevKColorSel(u32 idx, u8 num) { mTevKColorSel[idx] = num; }
    virtual u8 getTevKColorSel(u32 idx) { return mTevKColorSel[idx]; }
    virtual void setTevKAlphaSel(u32 idx, const u8* pNum) { mTevKAlphaSel[idx] = *pNum; }
    virtual void setTevKAlphaSel(u32 idx, u8 num) { mTevKAlphaSel[idx] = num; }
    virtual u8 getTevKAlphaSel(u32 idx) { return mTevKAlphaSel[idx]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 idx, const J3DTevStage* pStage) { mTevStage[idx] = *pStage; }
    virtual void setTevStage(u32 idx, J3DTevStage stage) { mTevStage[idx] = stage; }
    virtual J3DTevStage* getTevStage(u32 idx) { return &mTevStage[idx]; }
    virtual void setTevSwapModeInfo(u32 idx, const J3DTevSwapModeInfo* pInfo) { mTevStage[idx].setTevSwapModeInfo(*pInfo); }
    virtual void setTevSwapModeInfo(u32 idx, J3DTevSwapModeInfo info) { mTevStage[idx].setTevSwapModeInfo(info); }
    virtual void setTevSwapModeTable(u32 idx, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[idx] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 idx, J3DTevSwapModeTable table) {
        mTevSwapModeTable[idx] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 idx) { return &mTevSwapModeTable[idx]; }
    virtual void setIndTevStage(u32 idx, const J3DIndTevStage* pStage) { mIndTevStage[idx] = *pStage; }
    virtual void setIndTevStage(u32 idx, J3DIndTevStage stage) { mIndTevStage[idx] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 idx) { return &mIndTevStage[idx]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock2() {}

private:
    /* 0x08 */ u16 mTexNo[2];
    /* 0x0C */ J3DTevOrder mTevOrder[2];
    /* 0x14 */ J3DGXColorS10 mTevColor[4];
    /* 0x34 */ u8 mTevStageNum;
    /* 0x35 */ J3DTevStage mTevStage[2];
    /* 0x45 */ J3DGXColor mTevKColor[4];
    /* 0x55 */ u8 mTevKColorSel[2];
    /* 0x57 */ u8 mTevKAlphaSel[2];
    /* 0x59 */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x60 */ J3DIndTevStage mIndTevStage[2];
    /* 0x68 */ u32 mTevRegOffset;
};  // Size: 0x6C

class J3DTevBlock16 : public J3DTevBlock {
public:
    J3DTevBlock16() { initialize(); }
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
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TV16'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 idx, const u16* pNo) { mTexNo[idx] = *pNo; }
    virtual void setTexNo(u32 idx, u16 no) { mTexNo[idx] = no; }
    virtual u16 getTexNo(u32 idx) const {
        J3D_ASSERT(2308, idx < 8, "Error : range over.");
        return mTexNo[idx];
    }
    virtual void setTevOrder(u32 idx, const J3DTevOrder* pOrder) { mTevOrder[idx] = *pOrder; }
    virtual void setTevOrder(u32 idx, J3DTevOrder order) { mTevOrder[idx] = order; }
    virtual J3DTevOrder* getTevOrder(u32 idx) { return &mTevOrder[idx]; }
    virtual void setTevColor(u32 idx, const J3DGXColorS10* pColor) { mTevColor[idx] = *pColor; }
    virtual void setTevColor(u32 idx, J3DGXColorS10 color) { mTevColor[idx] = color; }
    virtual J3DGXColorS10* getTevColor(u32 idx) { return &mTevColor[idx]; }
    virtual void setTevKColor(u32 idx, const J3DGXColor* pColor) { mTevKColor[idx] = *pColor; }
    virtual void setTevKColor(u32 idx, J3DGXColor color) { mTevKColor[idx] = color; }
    virtual J3DGXColor* getTevKColor(u32 idx) { return &mTevKColor[idx]; }
    virtual void setTevKColorSel(u32 idx, const u8* pNum) { mTevKColorSel[idx] = *pNum; }
    virtual void setTevKColorSel(u32 idx, u8 num) { mTevKColorSel[idx] = num; }
    virtual u8 getTevKColorSel(u32 idx) { return mTevKColorSel[idx]; }
    virtual void setTevKAlphaSel(u32 idx, const u8* pNum) { mTevKAlphaSel[idx] = *pNum; }
    virtual void setTevKAlphaSel(u32 idx, u8 num) { mTevKAlphaSel[idx] = num; }
    virtual u8 getTevKAlphaSel(u32 idx) { return mTevKAlphaSel[idx]; }
    virtual void setTevStageNum(const u8* pNum) { mTevStageNum = *pNum; }
    virtual void setTevStageNum(u8 num) { mTevStageNum = num; }
    virtual u8 getTevStageNum() const { return mTevStageNum; }
    virtual void setTevStage(u32 idx, const J3DTevStage* pStage) { mTevStage[idx] = *pStage; }
    virtual void setTevStage(u32 idx, J3DTevStage stage) { mTevStage[idx] = stage; }
    virtual J3DTevStage* getTevStage(u32 idx) { return &mTevStage[idx]; }
    virtual void setTevSwapModeInfo(u32 idx, const J3DTevSwapModeInfo* pInfo) { mTevStage[idx].setTevSwapModeInfo(*pInfo); }
    virtual void setTevSwapModeInfo(u32 idx, J3DTevSwapModeInfo info) { mTevStage[idx].setTevSwapModeInfo(info); }
    virtual void setTevSwapModeTable(u32 idx, const J3DTevSwapModeTable* pTable) {
        mTevSwapModeTable[idx] = *pTable;
    }
    virtual void setTevSwapModeTable(u32 idx, J3DTevSwapModeTable table) {
        mTevSwapModeTable[idx] = table;
    }
    virtual J3DTevSwapModeTable* getTevSwapModeTable(u32 idx) { return &mTevSwapModeTable[idx]; }
    virtual void setIndTevStage(u32 idx, const J3DIndTevStage* pStage) { mIndTevStage[idx] = *pStage; }
    virtual void setIndTevStage(u32 idx, J3DIndTevStage stage) { mIndTevStage[idx] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 idx) { return &mIndTevStage[idx]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual u32 getTevRegOffset() const { return mTevRegOffset; }
    virtual void setTevRegOffset(u32 offs) { mTevRegOffset = offs; }
    virtual ~J3DTevBlock16() {}

    // private:
    /* 0x008 */ u16 mTexNo[8];
    /* 0x018 */ J3DTevOrder mTevOrder[16];
    /* 0x058 */ u8 mTevStageNum;
    /* 0x059 */ J3DTevStage mTevStage[16];
    /* 0x0DA */ J3DGXColorS10 mTevColor[4];
    /* 0x0FA */ J3DGXColor mTevKColor[4];
    /* 0x10A */ u8 mTevKColorSel[16];
    /* 0x11A */ u8 mTevKAlphaSel[16];
    /* 0x12A */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x130 */ J3DIndTevStage mIndTevStage[16];
    /* 0x170 */ u32 mTevRegOffset;
};  // Size: 0x174

STATIC_ASSERT(offsetof(J3DTevBlock16, mTexNo) == 0x008);
STATIC_ASSERT(offsetof(J3DTevBlock16, mTevStage) == 0x059);

class J3DTevBlock1 : public J3DTevBlock {
public:
    J3DTevBlock1() { initialize(); }
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
    virtual void ptrToIndex() {}
    virtual void indexToPtr() { indexToPtr_private(mTexNoOffset); }
    virtual u32 getType() { return 'TVB1'; }
    virtual s32 countDLSize();
    virtual void setTexNo(u32 idx, const u16* pNo) { mTexNo[idx] = *pNo; }
    virtual void setTexNo(u32 idx, u16 no) { mTexNo[idx] = no; }
    virtual u16 getTexNo(u32 idx) const {
        J3D_ASSERT(1574, idx < 1, "Error : range over.");
        return mTexNo[idx];
    }
    virtual void setTevOrder(u32 idx, const J3DTevOrder* pOrder) { mTevOrder[idx] = *pOrder; }
    virtual void setTevOrder(u32 idx, J3DTevOrder order) { mTevOrder[idx] = order; }
    virtual J3DTevOrder* getTevOrder(u32 idx) { return &mTevOrder[idx]; }
    virtual void setTevStageNum(const u8* pNum) {}
    virtual void setTevStageNum(u8 num) {}
    virtual u8 getTevStageNum() const { return 1; }
    virtual void setTevStage(u32 idx, const J3DTevStage* pStage) { mTevStage[idx] = *pStage; }
    virtual void setTevStage(u32 idx, J3DTevStage stage) { mTevStage[idx] = stage; }
    virtual J3DTevStage* getTevStage(u32 idx) { return &mTevStage[idx]; }
    virtual void setIndTevStage(u32 idx, const J3DIndTevStage* pStage) { mIndTevStage[idx] = *pStage; }
    virtual void setIndTevStage(u32 idx, J3DIndTevStage stage) { mIndTevStage[idx] = stage; }
    virtual J3DIndTevStage* getIndTevStage(u32 idx) { return &mIndTevStage[idx]; }
    virtual u32 getTexNoOffset() const { return mTexNoOffset; }
    virtual ~J3DTevBlock1() {}

private:
    /* 0x08 */ u16 mTexNo[1];
    /* 0x0A */ J3DTevOrder mTevOrder[1];
    /* 0x0E */ J3DTevStage mTevStage[1];
    /* 0x18 */ J3DIndTevStage mIndTevStage[1];
};  // Size: 0x1C

inline u16 calcZModeID(u8 param_0, u8 param_1, u8 param_2) {
    return (param_1 * 2) + (param_0 * 0x10) + param_2;
}

extern u8 j3dZModeTable[96];

struct J3DZMode {
    J3DZMode() { mZModeID = j3dDefaultZModeID; }
    explicit J3DZMode(const J3DZModeInfo& info) { setZModeInfo(info); }

    u8 getCompareEnable() const { return j3dZModeTable[mZModeID * 3 + 0]; }
    u8 getFunc() const { return j3dZModeTable[mZModeID * 3 + 1]; }
    u8 getUpdateEnable() const { return j3dZModeTable[mZModeID * 3 + 2]; }

    void setZModeInfo(const J3DZModeInfo& info) {
        mZModeID = calcZModeID(info.mCompareEnable, info.mFunc, info.mUpdateEnable);
    }

    void load() const {
        J3DGDSetZMode(getCompareEnable(), GXCompare(getFunc()), getUpdateEnable());
    }

    void setCompareEnable(u8 i_compare) {
        mZModeID = calcZModeID(i_compare, j3dZModeTable[mZModeID * 3 + 1], j3dZModeTable[mZModeID * 3 + 2]);
    }

    void setUpdateEnable(u8 i_enable) {
        mZModeID = calcZModeID(j3dZModeTable[mZModeID * 3], j3dZModeTable[mZModeID * 3 + 1], i_enable);
    }

    /* 0x0 */ u16 mZModeID;
};

struct J3DBlend : public J3DBlendInfo {
    J3DBlend() { *(J3DBlendInfo*)this = j3dDefaultBlendInfo; }
    explicit J3DBlend(const J3DBlendInfo& info) { *(J3DBlendInfo*)this = info; }
    void setBlendInfo(const J3DBlendInfo& info) { *(J3DBlendInfo*)this = info; }

    GXBlendMode getType() const { return (GXBlendMode)mBlendMode; }
    void setType(u8 i_type) { mBlendMode = i_type; }
    GXBlendFactor getSrcFactor() const { return (GXBlendFactor)mSrcFactor; }
    void setSrcFactor(u8 i_src) { mSrcFactor = i_src; }
    GXBlendFactor getDstFactor() const { return (GXBlendFactor)mDstFactor; }
    void setDstFactor(u8 i_dst) { mDstFactor = i_dst; }
    GXLogicOp getOp() const { return (GXLogicOp)mLogicOp; }

    void load(u8 ditherEnable) {
        J3DGDSetBlendMode(getType(), getSrcFactor(), getDstFactor(), getOp(), ditherEnable);
    }

    // void operator=(const J3DBlend&) {}
    // void operator==(J3DBlend&) {}
};

extern const J3DFogInfo j3dDefaultFogInfo;

struct J3DFog : public J3DFogInfo {
    // J3DFog() { *getFogInfo() = j3dDefaultFogInfo; } // Produces the wrong codegen for mDoExt_backupMatBlock_c's constructor
    J3DFog() { J3DFogInfo::operator=(j3dDefaultFogInfo); }
    explicit J3DFog(const J3DFogInfo& info) { J3DFogInfo::operator=(info); }
    ~J3DFog() {}
    J3DFogInfo* getFogInfo() { return (J3DFogInfo*)this; }

    void load() const {
        J3DGDSetFog(GXFogType(mType), mStartZ, mEndZ, mNearZ, mFarZ, mColor);
        J3DGDSetFogRangeAdj(mAdjEnable, mCenter, (GXFogAdjTable*)mFogAdjTable);
    }
    void setType(u8 type) { mType = type; }
};

struct J3DAlphaCompInfo {
    /* 0x0 */ u8 mComp0;
    /* 0x1 */ u8 mRef0;
    /* 0x2 */ u8 mOp;
    /* 0x3 */ u8 mComp1;
    /* 0x4 */ u8 mRef1;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
};

inline u16 calcAlphaCmpID(u8 comp0, u8 op, u8 comp1) {
    return (comp0 << 5) + (op << 3) + (comp1);
}

extern u8 j3dAlphaCmpTable[768];

struct J3DAlphaComp {
    J3DAlphaComp() {
        mAlphaCmpID = j3dDefaultAlphaCmpID;
        mRef0 = 0;
        mRef1 = 0;
    }

    J3DAlphaComp(u16 id) : mAlphaCmpID(id), mRef0(0), mRef1(0) {}

    explicit J3DAlphaComp(const J3DAlphaCompInfo& info) {
        mAlphaCmpID = calcAlphaCmpID(info.mComp0, info.mOp, info.mComp1);
        mRef0 = info.mRef0;
        mRef1 = info.mRef1;
    }

    GXCompare getComp0() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3]); }
    GXAlphaOp getOp() const { return GXAlphaOp(j3dAlphaCmpTable[mAlphaCmpID * 3 + 1]); }
    GXCompare getComp1() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3 + 2]); }
    u8 getRef0() const { return mRef0; }
    u8 getRef1() const { return mRef1; }

    void setAlphaCompInfo(const J3DAlphaCompInfo& info) {
        mAlphaCmpID = calcAlphaCmpID(info.mComp0, info.mOp, info.mComp1);
        mRef0 = info.mRef0;
        mRef1 = info.mRef1;
    }

    void load() {
        J3DGDSetAlphaCompare(getComp0(), getRef0(), getOp(), getComp1(), getRef1());
    }

    /* 0x00 */ u16 mAlphaCmpID;
    /* 0x02 */ u8 mRef0;
    /* 0x03 */ u8 mRef1;
};  // Size: 0x4

class J3DPEBlock {
public:
    virtual void reset(J3DPEBlock*) {}
    virtual void load() = 0;
    virtual void patch() {}
    virtual void diff(u32) {}
    virtual void diffFog() {}
    virtual void diffBlend() {}
    virtual s32 countDLSize() { return 0; }
    virtual u32 getType() = 0;
    virtual void setFog(J3DFog*) {}
    virtual J3DFog* getFog() { return NULL; }
    virtual void setAlphaComp(J3DAlphaComp const*) {}
    virtual void setAlphaComp(J3DAlphaComp) {}
    virtual J3DAlphaComp* getAlphaComp() { return NULL; }
    virtual void setBlend(J3DBlend const*) {}
    virtual void setBlend(J3DBlend) {}
    virtual J3DBlend* getBlend() { return NULL; }
    virtual void setZMode(J3DZMode const*) {}
    virtual void setZMode(J3DZMode) {}
    virtual J3DZMode* getZMode() { return NULL; }
    virtual void setZCompLoc(u8 const*) {}
    virtual void setZCompLoc(u8) {}
    virtual u8 getZCompLoc() const { return 0; }
    virtual void setDither(u8 const*) {}
    virtual void setDither(u8) {}
    virtual u8 getDither() const { return 0; }
    virtual u32 getFogOffset() const { return 0; }
    virtual void setFogOffset(u32) {}
    virtual ~J3DPEBlock() {}
};

class J3DPEBlockXlu : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEXL'; }
    virtual ~J3DPEBlockXlu() {}
};

class J3DPEBlockTexEdge : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEED'; }
    virtual ~J3DPEBlockTexEdge() {}
};

class J3DPEBlockOpa : public J3DPEBlock {
public:
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEOP'; }
    virtual ~J3DPEBlockOpa() {}
};

class J3DPEBlockFull : public J3DPEBlock {
public:
    J3DPEBlockFull() { initialize(); }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void patch();
    virtual void diff(u32);
    virtual void diffFog();
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEFL'; }
    virtual void setFog(J3DFog* pFog) { mFog = pFog; }
    virtual J3DFog* getFog() { return mFog; }
    virtual void setAlphaComp(const J3DAlphaComp* pAlphaComp) { mAlphaComp = *pAlphaComp; }
    virtual void setAlphaComp(J3DAlphaComp alphaComp) { mAlphaComp = alphaComp; }
    virtual J3DAlphaComp* getAlphaComp() { return &mAlphaComp; }
    virtual void setBlend(const J3DBlend* pBlend) { mBlend = *pBlend; }
    virtual void setBlend(J3DBlend blend) { mBlend = blend; }
    virtual J3DBlend* getBlend() { return &mBlend; }
    virtual void setZMode(const J3DZMode* pZMode) { mZMode = *pZMode; }
    virtual void setZMode(J3DZMode zMode) { mZMode = zMode; }
    virtual J3DZMode* getZMode() { return &mZMode; }
    virtual void setZCompLoc(const u8* pZCompLoc) { mZCompLoc = *pZCompLoc; }
    virtual void setZCompLoc(u8 zCompLoc) { mZCompLoc = zCompLoc; }
    virtual u8 getZCompLoc() const { return mZCompLoc; }
    virtual void setDither(const u8* pDither) { mDither = *pDither; }
    virtual void setDither(u8 dither) { mDither = dither; }
    virtual u8 getDither() const { return mDither; }
    virtual u32 getFogOffset() const { return mFogOffset; }
    virtual void setFogOffset(u32 offs) { mFogOffset = offs; }
    virtual ~J3DPEBlockFull() {}

private:
    /* 0x04 */ J3DFog* mFog;
    /* 0x08 */ J3DAlphaComp mAlphaComp;
    /* 0x0C */ J3DBlend mBlend;
    /* 0x10 */ J3DZMode mZMode;
    /* 0x14 */ u8 mZCompLoc;
    /* 0x15 */ u8 mDither;
    /* 0x18 */ u32 mFogOffset;
};  // Size: 0x1C

class J3DPEBlockFogOff : public J3DPEBlock {
public:
    J3DPEBlockFogOff() { initialize(); }
    void initialize();

    virtual void reset(J3DPEBlock*);
    virtual void load();
    virtual void diff(u32 flag) {
        if ((flag & 0x20000000) != 0)
            diffBlend();
    }
    virtual void diffBlend();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'PEFG'; }
    virtual void setAlphaComp(const J3DAlphaComp* pAlphaComp) { mAlphaComp = *pAlphaComp; }
    virtual void setAlphaComp(J3DAlphaComp alphaComp) { mAlphaComp = alphaComp; }
    virtual J3DAlphaComp* getAlphaComp() { return &mAlphaComp; }
    virtual void setBlend(const J3DBlend* pBlend) { mBlend = *pBlend; }
    virtual void setBlend(J3DBlend blend) { mBlend = blend; }
    virtual J3DBlend* getBlend() { return &mBlend; }
    virtual void setZMode(const J3DZMode* pZMode) { mZMode = *pZMode; }
    virtual void setZMode(J3DZMode zMode) { mZMode = zMode; }
    virtual J3DZMode* getZMode() { return &mZMode; }
    virtual void setZCompLoc(const u8* pZCompLoc) { mZCompLoc = *pZCompLoc; }
    virtual void setZCompLoc(u8 zCompLoc) { mZCompLoc = zCompLoc; }
    virtual u8 getZCompLoc() const { return mZCompLoc; }
    virtual void setDither(const u8* pDither) { mDither = *pDither; }
    virtual void setDither(u8 dither) { mDither = dither; }
    virtual u8 getDither() const { return mDither; }
    virtual ~J3DPEBlockFogOff() {}

private:
    /* 0x04 */ J3DAlphaComp mAlphaComp;
    /* 0x08 */ J3DBlend mBlend;
    /* 0x0C */ J3DZMode mZMode;
    /* 0x0E */ u8 mZCompLoc;
    /* 0x0F */ u8 mDither;
};  // Size: 0x10

class J3DPEBlockNull : public J3DPEBlock {
public:
    virtual void load() {}
    virtual u32 getType() { return 'PENL'; }
    virtual ~J3DPEBlockNull() {}
};

struct J3DIndTexCoordScale : public J3DIndTexCoordScaleInfo {
    J3DIndTexCoordScale() { *(J3DIndTexCoordScaleInfo*)this = j3dDefaultIndTexCoordScaleInfo; }
    explicit J3DIndTexCoordScale(const J3DIndTexCoordScaleInfo& info) {*(J3DIndTexCoordScaleInfo*)this = info; }
    ~J3DIndTexCoordScale() {}

    u8 getScaleS() { return mScaleS; }
    u8 getScaleT() { return mScaleT; }
};

struct J3DIndTexMtx : public J3DIndTexMtxInfo {
    J3DIndTexMtx() {*(J3DIndTexMtxInfo*)this = j3dDefaultIndTexMtxInfo; }
    explicit J3DIndTexMtx(const J3DIndTexMtxInfo& info) { *(J3DIndTexMtxInfo*)this = info; }
    ~J3DIndTexMtx() {}

    void load(u32 id) const {
        J3DGDSetIndTexMtx(GXIndTexMtxID(id + GX_ITM_0), (Mtx3P)mOffsetMtx, mScaleExp);
    }

    Mtx3P getOffsetMtx() {
        return mOffsetMtx;
    }

    s8 getScaleExp() {
        return mScaleExp;
    }

    void setScaleExp(s8 i_scaleExp) {
        mScaleExp = i_scaleExp;
    }
};  // Size: 0x1C

struct J3DIndTexOrder : public J3DIndTexOrderInfo {
    J3DIndTexOrder() { *(J3DIndTexOrderInfo*)this = j3dDefaultIndTexOrderNull; }
    explicit J3DIndTexOrder(const J3DIndTexOrderInfo& info) { *(J3DIndTexOrderInfo*)this = info; }

    u8 getCoord() const { return mCoord; }
    u8 getMap() const { return mMap; }
    void setCoord(u8 coord) { mCoord = coord; }
    void setMap(u8 map) { mMap = map; }
};

class J3DIndBlock {
public:
    virtual void reset(J3DIndBlock*) {}
    virtual void diff(u32) = 0;
    virtual void load() = 0;
    virtual s32 countDLSize() { return 0; }
    virtual u32 getType() = 0;
    virtual void setIndTexStageNum(u8) {}
    virtual u8 getIndTexStageNum() const { return 0; }
    virtual void setIndTexOrder(u32, J3DIndTexOrder) {}
    virtual void setIndTexOrder(u32, J3DIndTexOrder const*) {}
    virtual J3DIndTexOrder* getIndTexOrder(u32) { return NULL; }
    virtual void setIndTexMtx(u32, J3DIndTexMtx const*) {}
    virtual void setIndTexMtx(u32, J3DIndTexMtx) {}
    virtual J3DIndTexMtx* getIndTexMtx(u32) { return NULL; }
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale const*) {}
    virtual void setIndTexCoordScale(u32, J3DIndTexCoordScale) {}
    virtual J3DIndTexCoordScale* getIndTexCoordScale(u32) { return NULL; }
    virtual ~J3DIndBlock() {}
};

class J3DIndBlockFull : public J3DIndBlock {
public:
    J3DIndBlockFull() { initialize(); }
    void initialize();

    virtual void diff(u32);
    virtual void reset(J3DIndBlock*);
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'IBLF'; }
    virtual void setIndTexStageNum(u8 num) { mIndTexStageNum = num; }
    virtual u8 getIndTexStageNum() const { return mIndTexStageNum; }
    virtual void setIndTexOrder(u32 idx, J3DIndTexOrder const* pOrder) { mIndTexOrder[idx] = *pOrder; }
    virtual void setIndTexOrder(u32 idx, J3DIndTexOrder order) { mIndTexOrder[idx] = order; }
    virtual J3DIndTexOrder* getIndTexOrder(u32 idx) { return &mIndTexOrder[idx]; }
    virtual void setIndTexMtx(u32 idx, J3DIndTexMtx const* pMtx) { mIndTexMtx[idx] = *pMtx; }
    virtual void setIndTexMtx(u32 idx, J3DIndTexMtx mtx) { mIndTexMtx[idx] = mtx; }
    virtual J3DIndTexMtx* getIndTexMtx(u32 idx) { return &mIndTexMtx[idx]; }
    virtual void setIndTexCoordScale(u32 idx, J3DIndTexCoordScale const* pScale) { mIndTexCoordScale[idx] = *pScale; }
    virtual void setIndTexCoordScale(u32 idx, J3DIndTexCoordScale scale) { mIndTexCoordScale[idx] = scale; }
    virtual J3DIndTexCoordScale* getIndTexCoordScale(u32 idx) { return &mIndTexCoordScale[idx]; }
    virtual ~J3DIndBlockFull() {}

private:
    /* 0x04 */ u8 mIndTexStageNum;
    /* 0x05 */ J3DIndTexOrder mIndTexOrder[4];
    /* 0x18 */ J3DIndTexMtx mIndTexMtx[3];
    /* 0x6C */ J3DIndTexCoordScale mIndTexCoordScale[4];
};  // Size: 0x7C

class J3DIndBlockNull : public J3DIndBlock {
public:
    virtual void diff(u32) {}
    virtual void load() {}
    virtual void reset(J3DIndBlock*) {}
    virtual u32 getType() { return 'IBLN'; }
    virtual ~J3DIndBlockNull() {}
};

inline u16 calcColorChanID(u16 enable, u8 matSrc, u8 lightMask, u8 diffuseFn, u8 attnFn, u8 ambSrc) {
    u32 reg = 0;
    reg = (reg & ~0x0002) | enable << 1;
    reg = (reg & ~0x0001) | matSrc;
    reg = (reg & ~0x0040) | ambSrc << 6;
    reg = (reg & ~0x0004) | bool(lightMask & 0x01) << 2;
    reg = (reg & ~0x0008) | bool(lightMask & 0x02) << 3;
    reg = (reg & ~0x0010) | bool(lightMask & 0x04) << 4;
    reg = (reg & ~0x0020) | bool(lightMask & 0x08) << 5;
    reg = (reg & ~0x0800) | bool(lightMask & 0x10) << 11;
    reg = (reg & ~0x1000) | bool(lightMask & 0x20) << 12;
    reg = (reg & ~0x2000) | bool(lightMask & 0x40) << 13;
    reg = (reg & ~0x4000) | bool(lightMask & 0x80) << 14;
    reg = (reg & ~0x0180) | (attnFn == GX_AF_SPEC ? 0 : diffuseFn) << 7;
    reg = (reg & ~0x0200) | (attnFn != GX_AF_NONE) << 9;
    reg = (reg & ~0x0400) | (attnFn != GX_AF_SPEC) << 10;
    return reg;
}

static inline u32 setChanCtrlMacro(u8 enable, GXColorSrc ambSrc, GXColorSrc matSrc, u32 lightMask,
                                   GXDiffuseFn diffuseFn, GXAttnFn attnFn) {
    return matSrc << 0 | enable << 1 | (lightMask & 0x0F) << 2 | ambSrc << 6 |
           ((attnFn == GX_AF_SPEC) ? GX_DF_NONE : diffuseFn) << 7 | (attnFn != GX_AF_NONE) << 9 |
           (attnFn != GX_AF_SPEC) << 10 | (lightMask >> 4 & 0x0F) << 11;
}

struct J3DColorChan {
    J3DColorChan() { setColorChanInfo(j3dDefaultColorChanInfo); }
    J3DColorChan(const J3DColorChanInfo& info) {
        u32 ambSrc = info.mAmbSrc == 0xFF ? 0 : info.mAmbSrc;
        mChanCtrl = calcColorChanID(info.mEnable, info.mMatSrc, info.mLightMask,
            info.mDiffuseFn, info.mAttnFn, ambSrc);
    }
    void setColorChanInfo(const J3DColorChanInfo& info) {
        // Bug: It compares info.mAmbSrc (an 8 bit integer) with 0xFFFF instead of 0xFF.
        // This inline is only called by the default constructor J3DColorChan().
        // The J3DColorChan(const J3DColorChanInfo&) constructor does not call this inline, and instead duplicates the
        // same logic but without the bug.
        // See J3DMaterialFactory::newColorChan - both the bugged and correct behavior are present there, as it calls
        // both constructors.
        u32 ambSrc = info.mAmbSrc == 0xFFFF ? 0 : info.mAmbSrc;
        mChanCtrl = calcColorChanID(info.mEnable, info.mMatSrc, info.mLightMask,
            info.mDiffuseFn, info.mAttnFn, ambSrc);
    }
    J3DColorChan(u16 id) : mChanCtrl(id) {}
    u8 getAttnFn() const {
#ifdef DECOMPCTX // Hack, see comment in dolzel.pch for details
        return 0;
#else
        u8 attnFnTbl[] = { GX_AF_NONE, GX_AF_SPEC, GX_AF_NONE, GX_AF_SPOT };
        return attnFnTbl[(u32)(mChanCtrl & (3 << 9)) >> 9];
#endif
    }
    u8 getDiffuseFn() const { return ((u32)(mChanCtrl & (3 << 7)) >> 7); }
    u8 getLightMask() const { return ((mChanCtrl >> 2) & 0x0f) | ((mChanCtrl >> 11) & 0x0f) << 4; }
    void setLightMask(u8 mask) {
        mChanCtrl = (mChanCtrl & ~0x003c) | ((mask & 0x0F) << 2);
        mChanCtrl = (mChanCtrl & ~0x7800) | ((mask & 0xF0) << 7);
    }
    u8 getMatSrc() const { return (GXColorSrc)(mChanCtrl & 1); }
    u8 getAmbSrc() const { return (GXColorSrc)((u32)(mChanCtrl & (1 << 6)) >> 6); }
    u8 getEnable() const { return (u32)(mChanCtrl & 0x2) >> 1; }
    void load() const {
        J3DGDWrite_u32(setChanCtrlMacro(getEnable(), (GXColorSrc)getAmbSrc(), (GXColorSrc)getMatSrc(), getLightMask(),
                                        (GXDiffuseFn)getDiffuseFn(), (GXAttnFn)getAttnFn()));
    }

    /* 0x0 */ u16 mChanCtrl;
};

class J3DColorBlock {
public:
    virtual void load() {}
    virtual void reset(J3DColorBlock*) {}
    virtual void patch() {}
    virtual void patchMatColor() {}
    virtual void patchLight() {}
    virtual void diff(u32) {}
    virtual void diffMatColor() {}
    virtual void diffLight() {}
    virtual s32 countDLSize() { return 0; }
    virtual u32 getType() = 0;
    virtual void setMatColor(u32, J3DGXColor const*) {}
    virtual void setMatColor(u32, J3DGXColor) {}
    virtual J3DGXColor* getMatColor(u32) { return NULL; }
    virtual void setAmbColor(u32, J3DGXColor const*) {}
    virtual void setAmbColor(u32, J3DGXColor) {}
    virtual J3DGXColor* getAmbColor(u32) { return NULL; }
    virtual void setColorChanNum(u8) {}
    virtual void setColorChanNum(u8 const*) {}
    virtual u8 getColorChanNum() const { return 0; }
    virtual void setColorChan(u32, J3DColorChan const&) {}
    virtual void setColorChan(u32, J3DColorChan const*) {}
    virtual J3DColorChan* getColorChan(u32) { return NULL; }
    virtual void setLight(u32, J3DLightObj*) {}
    virtual J3DLightObj* getLight(u32) { return NULL; }
    virtual void setCullMode(u8 const*) {}
    virtual void setCullMode(u8) {}
    virtual u8 getCullMode() const { return 2; }
    virtual u32 getMatColorOffset() const { return 0; }
    virtual u32 getColorChanOffset() const { return 0; }
    virtual void setMatColorOffset(u32) {}
    virtual void setColorChanOffset(u32) {}
    virtual ~J3DColorBlock() {}
};

class J3DColorBlockLightOn : public J3DColorBlock {
public:
    J3DColorBlockLightOn() { initialize(); }
    void initialize();

    virtual void reset(J3DColorBlock*);
    virtual void load();
    virtual void patch();
    virtual void patchMatColor();
    virtual void patchLight();
    virtual void diff(u32);
    virtual void diffMatColor();
    virtual void diffLight();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'CLON'; }
    virtual void setMatColor(u32 idx, J3DGXColor const* pColor) { mMatColor[idx] = *pColor; }
    virtual void setMatColor(u32 idx, J3DGXColor color) { mMatColor[idx] = color; }
    virtual J3DGXColor* getMatColor(u32 idx) { return &mMatColor[idx]; }
    virtual void setAmbColor(u32 idx, J3DGXColor const* pColor) { mAmbColor[idx] = *pColor; }
    virtual void setAmbColor(u32 idx, J3DGXColor color) { mAmbColor[idx] = color; }
    virtual J3DGXColor* getAmbColor(u32 idx) { return &mAmbColor[idx]; }
    virtual void setColorChanNum(u8 num) { mColorChanNum = num; }
    virtual void setColorChanNum(u8 const* pNum) { mColorChanNum = *pNum; }
    virtual u8 getColorChanNum() const { return mColorChanNum; }
    virtual void setColorChan(u32 idx, J3DColorChan const& chan) { mColorChan[idx] = chan; }
    virtual void setColorChan(u32 idx, J3DColorChan const* pChan) { mColorChan[idx] = *pChan; }
    virtual J3DColorChan* getColorChan(u32 idx) { return &mColorChan[idx]; }
    virtual void setLight(u32 idx, J3DLightObj* pLight) { mLight[idx] = pLight; }
    virtual J3DLightObj* getLight(u32 idx) { return mLight[idx]; }
    virtual void setCullMode(u8 const* pMode) { mCullMode = *pMode; }
    virtual void setCullMode(u8 mode) { mCullMode = mode; }
    virtual u8 getCullMode() const { return mCullMode; }
    virtual u32 getMatColorOffset() const { return mMatColorOffset; }
    virtual u32 getColorChanOffset() const { return mColorChanOffset; }
    virtual void setMatColorOffset(u32 offs) { mMatColorOffset = offs; }
    virtual void setColorChanOffset(u32 offs) { mColorChanOffset = offs; }
    virtual ~J3DColorBlockLightOn() {}

private:
    /* 0x04 */ J3DGXColor mMatColor[2];
    /* 0x0C */ J3DGXColor mAmbColor[2];
    /* 0x14 */ u8 mColorChanNum;
    /* 0x16 */ J3DColorChan mColorChan[4];
    /* 0x20 */ J3DLightObj* mLight[8];
    /* 0x40 */ u8 mCullMode;
    /* 0x44 */ u32 mMatColorOffset;
    /* 0x48 */ u32 mColorChanOffset;
};  // Size: 0x4C

class J3DColorBlockLightOff : public J3DColorBlock {
public:
    J3DColorBlockLightOff() { initialize(); }
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
    virtual u32 getType() { return 'CLOF'; }
    virtual void setMatColor(u32 idx, J3DGXColor const* pColor) { mMatColor[idx] = *pColor; }
    virtual void setMatColor(u32 idx, J3DGXColor color) { mMatColor[idx] = color; }
    virtual J3DGXColor* getMatColor(u32 idx) { return &mMatColor[idx]; }
    virtual void setColorChanNum(u8 num) { mColorChanNum = num; }
    virtual void setColorChanNum(u8 const* pNum) { mColorChanNum = *pNum;}
    virtual u8 getColorChanNum() const { return mColorChanNum; }
    virtual void setColorChan(u32 idx, J3DColorChan const& chan) { mColorChan[idx] = chan; }
    virtual void setColorChan(u32 idx, J3DColorChan const* pChan) { mColorChan[idx] = *pChan; }
    virtual J3DColorChan* getColorChan(u32 idx) { return &mColorChan[idx]; }
    virtual void setCullMode(u8 const* pMode) { mCullMode = *pMode;}
    virtual void setCullMode(u8 mode ) { mCullMode = mode; }
    virtual u8 getCullMode() const { return mCullMode; }
    virtual u32 getMatColorOffset() const { return mMatColorOffset; }
    virtual u32 getColorChanOffset() const { return mColorChanOffset; }
    virtual void setMatColorOffset(u32 offs) { mMatColorOffset = offs; }
    virtual void setColorChanOffset(u32 offs) { mColorChanOffset = offs; }
    virtual ~J3DColorBlockLightOff() {}

protected:
    /* 0x04 */ J3DGXColor mMatColor[2];
    /* 0x0C */ u8 mColorChanNum;
    /* 0x0E */ J3DColorChan mColorChan[4];
    /* 0x16 */ u8 mCullMode;
    /* 0x18 */ u32 mMatColorOffset;
    /* 0x1C */ u32 mColorChanOffset;
};  // Size: 0x20

extern int SizeOfJ3DColorBlockLightOffLoad;

class J3DColorBlockAmbientOn : public J3DColorBlockLightOff {
public:
    J3DColorBlockAmbientOn() { initialize(); }
    void initialize();

    virtual void reset(J3DColorBlock*);
    virtual void load();
    virtual s32 countDLSize();
    virtual u32 getType() { return 'CLAB'; }
    virtual void setAmbColor(u32 idx, J3DGXColor const* pColor) { mAmbColor[idx] = *pColor; }
    virtual void setAmbColor(u32 idx, J3DGXColor color) { mAmbColor[idx] = color; }
    virtual J3DGXColor* getAmbColor(u32 idx) { return &mAmbColor[idx]; }
    virtual ~J3DColorBlockAmbientOn() {}

protected:
    /* 0x20 */ J3DGXColor mAmbColor[2];
};  // Size: 0x28

class J3DColorBlockNull : public J3DColorBlock {
public:
    virtual u32 getType() { return 'CLNL'; }
    virtual ~J3DColorBlockNull() {}
};

extern int SizeOfJ3DColorBlockAmbientOnLoad;

#endif /* J3DMATBLOCK_H */
