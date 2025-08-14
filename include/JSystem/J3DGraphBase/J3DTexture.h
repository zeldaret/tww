#ifndef J3DTEXTURE_H
#define J3DTEXTURE_H

#include "JSystem/J3DGraphBase/J3DGD.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/J3DGraphBase/J3DTevs.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"

inline void J3DGDLoadTexMtxImm(Mtx pMtx, u32 i, GXTexMtxType mType) {
    u16 cmd = i * 4;
    u8 len = mType == GX_MTX2x4 ? 8 : 12;
    J3DGDWriteXFCmdHdr(cmd, len);
    J3DGDWrite_f32(pMtx[0][0]);
    J3DGDWrite_f32(pMtx[0][1]);
    J3DGDWrite_f32(pMtx[0][2]);
    J3DGDWrite_f32(pMtx[0][3]);
    J3DGDWrite_f32(pMtx[1][0]);
    J3DGDWrite_f32(pMtx[1][1]);
    J3DGDWrite_f32(pMtx[1][2]);
    J3DGDWrite_f32(pMtx[1][3]);
    if (mType == GX_MTX3x4) {
        J3DGDWrite_f32(pMtx[2][0]);
        J3DGDWrite_f32(pMtx[2][1]);
        J3DGDWrite_f32(pMtx[2][2]);
        J3DGDWrite_f32(pMtx[2][3]);
    }
}

class J3DTexture {
private:
    /* 0x0 */ u16 mNum;
    /* 0x4 */ ResTIMG* mpRes;

public:
    J3DTexture(u16 num, ResTIMG* res) : mNum(num), mpRes(res) {}
    virtual ~J3DTexture() {}

    void loadGX(u16, GXTexMapID) const;
    void entryNum(u16);
    void addResTIMG(u16, ResTIMG const*);

    u16 getNum() const { return mNum; }
    ResTIMG* getResTIMG(u16 entry) const {
        J3D_ASSERT(72, entry < mNum, "Error : range over.");
        return &mpRes[entry];   
    }
    void setResTIMG(u16 entry, const ResTIMG& timg) {
        mpRes[entry] = timg;
        mpRes[entry].imageOffset = ((mpRes[entry].imageOffset + (u32)&timg - (u32)(mpRes + entry)));
        mpRes[entry].paletteOffset = ((mpRes[entry].paletteOffset + (u32)&timg - (u32)(mpRes + entry)));
    }
};

class J3DTexMtx {
public:
    J3DTexMtx() { mTexMtxInfo = j3dDefaultTexMtxInfo; }
    J3DTexMtx(const J3DTexMtxInfo& info) {
        mTexMtxInfo = info;
    }
    ~J3DTexMtx() {}
    void load(u32 texMtxID) const {
        GDOverflowCheck(53);
        J3DGDLoadTexMtxImm((Mtx&)mMtx, GX_TEXMTX0 + texMtxID * 3, (GXTexMtxType)mTexMtxInfo.mProjection);
    };
    void calc();

    J3DTexMtxInfo& getTexMtxInfo() { return mTexMtxInfo; }
    Mtx& getMtx() { return mMtx; }
    void setEffectMtx(Mtx effectMtx) { mTexMtxInfo.setEffectMtx(effectMtx); }
    Mtx& getViewMtx() { return mViewMtx; }
    void setViewMtx(const Mtx viewMtx) { MTXCopy(viewMtx, mViewMtx); }
    void setTranslationX(f32 translationX){ mTexMtxInfo.mSRT.mTranslationX = translationX; } // Fakematch

    J3DTextureSRTInfo& getTextureSRT() { return mTexMtxInfo.mSRT;}

private:
    /* 0x00 */ J3DTexMtxInfo mTexMtxInfo;
    /* 0x64 */ Mtx mMtx;
    /* 0x94 */ Mtx mViewMtx;
};  // Size: 0xC4

struct J3DTexCoord : public J3DTexCoordInfo {
    J3DTexCoord() { *(J3DTexCoordInfo*)this = j3dDefaultTexCoordInfo[0]; }
    J3DTexCoord(const J3DTexCoordInfo& info) { *(J3DTexCoordInfo*)this = info; }

    u8 getTexGenType() const { return mTexGenType; }
    u8 getTexGenSrc() const { return mTexGenSrc; }
    u8 getTexGenMtx() const { return mTexGenMtx; }
    void setTexGenMtx(u8 v) { mTexGenMtx = v; }
};  // Size: 0x4

#endif /* J3DTEXTURE_H */
