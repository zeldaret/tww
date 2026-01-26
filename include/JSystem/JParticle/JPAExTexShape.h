#ifndef JPAEXTEXSHAPE_H
#define JPAEXTEXSHAPE_H

#include "dolphin/gx/GX.h"

struct JPAExTexShapeData {
    /* 0x00 */ u32 mFlags;
    /* 0x04 */ Mtx23 mIndTexMtx;
    /* 0x1C */ s8 mExpScale;
    /* 0x1D */ u8 field_0x1d[3];
    /* 0x20 */ u8 mIndTextureID;
    /* 0x21 */ u8 mSubTextureID;
    /* 0x22 */ u8 mSecondTextureID;
};  // Size: 0x24

class JPAExTexShape {
public:
    virtual ~JPAExTexShape() {}
    virtual u32 getIndTexMode() = 0;
    virtual GXIndTexMtxID getIndTexMtxID() = 0;
    virtual const Mtx23* getIndTexMtx() = 0;
    virtual s8 getExpScale() = 0;
    virtual u8 getIndTextureID() = 0;
    virtual u8 getSubTextureID() = 0;
    virtual BOOL isEnableSecondTex() = 0;
    virtual u8 getSecondTexIndex() = 0;
};

class JPAExTexShapeArc : public JPAExTexShape {
public:
    JPAExTexShapeArc(const u8*);
    virtual ~JPAExTexShapeArc() {}
    virtual u32 getIndTexMode() { return (mpData->mFlags >> 0) & 0x03; }
    virtual GXIndTexMtxID getIndTexMtxID() { return indMtxID[(mpData->mFlags >> 2) & 0x03]; }
    virtual const Mtx23* getIndTexMtx() { return &mpData->mIndTexMtx; }
    virtual s8 getExpScale() { return mpData->mExpScale; }
    virtual u8 getIndTextureID() { return mpData->mIndTextureID; }
    virtual u8 getSubTextureID() { return mpData->mSubTextureID; }
    virtual BOOL isEnableSecondTex() { return (mpData->mFlags & 0x100); }
    virtual u8 getSecondTexIndex() { return mpData->mSecondTextureID; }

public:
    static GXIndTexMtxID indMtxID[4];

    /* 0x04 */ const JPAExTexShapeData* mpData;
};

#endif /* JPAEXTEXSHAPE_H */
