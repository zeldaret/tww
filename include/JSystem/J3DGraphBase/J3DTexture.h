#ifndef J3DTEXTURE_H
#define J3DTEXTURE_H

#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"

class J3DTexture {
private:
    /* 0x0 */ u16 mNum;
    /* 0x4 */ ResTIMG* mpRes;

public:
    void loadGX(u16, _GXTexMapID) const;
    void entryNum(u16);
    void addResTIMG(u16, ResTIMG const*);
    virtual ~J3DTexture();

    u16 getNum() const { return mNum; }
    ResTIMG* getResTIMG(u16 entry) const { return &mpRes[entry]; }
    void setResTIMG(u16 entry, const ResTIMG& timg) {
        mpRes[entry] = timg;
        mpRes[entry].imageOffset = ((mpRes[entry].imageOffset + (u32)&timg - (u32)(mpRes + entry)));
        mpRes[entry].paletteOffset = ((mpRes[entry].paletteOffset + (u32)&timg - (u32)(mpRes + entry)));
    }
};

class J3DTexMtx {
public:
    J3DTexMtx(const J3DTexMtxInfo& info) {
        mTexMtxInfo = info;
    }
    void load(u32) const;
    void calc(f32 const (*)[4]);
    void calcTexMtx(f32 const (*)[4]);
    void calcPostTexMtx(f32 const (*)[4]);
    void loadTexMtx(u32) const;
    void loadPostTexMtx(u32) const;

    J3DTexMtxInfo& getTexMtxInfo() { return mTexMtxInfo; }
    Mtx& getMtx() { return mMtx; }
    void setEffectMtx(Mtx effectMtx) { mTexMtxInfo.setEffectMtx(effectMtx); }

private:
    /* 0x00 */ J3DTexMtxInfo mTexMtxInfo;
    /* 0x64 */ Mtx mMtx;
};  // Size: 0x94

struct J3DTexCoordInfo {
    /* 0x0 */ u8 mTexGenType;
    /* 0x1 */ u8 mTexGenSrc;
    /* 0x2 */ u8 mTexGenMtx;
};

struct J3DTexCoord : public J3DTexCoordInfo {
    J3DTexCoord();

    void setTexCoordInfo(J3DTexCoordInfo *param_1) {
        *(J3DTexCoordInfo*)this = *param_1;
    }

    u8 getTexGenMtx() { return mTexGenMtx & 0xff; }
    u16 getTexMtxReg() { return mTexMtxReg & 0xff; }

    void setTexGenMtx(u8 v) { mTexGenMtx = v; }

    void resetTexMtxReg() {
        mTexMtxReg = mTexGenMtx;
    }

    /* 0x4 */ u8 mTexMtxReg;
};  // Size: 0x6

struct J3DDefaultTexCoordInfo {
    /* 0x0 */ u8 mTexGenType;
    /* 0x1 */ u8 mTexGenSrc;
    /* 0x2 */ u8 mTexGenMtx;
    /* 0x3 */ u8 pad;
};

#endif /* J3DTEXTURE_H */
