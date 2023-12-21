#ifndef JPABASESHAPE_H
#define JPABASESHAPE_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "dolphin/gx/GX.h"

class JKRHeap;

class JPABaseShape {
public:
    enum Type {
        /*  0 */ JPAType_Point,
        /*  1 */ JPAType_Line,
        /*  2 */ JPAType_Billboard,
        /*  3 */ JPAType_Direction,
        /*  4 */ JPAType_DirectionCross,
        /*  5 */ JPAType_Stripe,
        /*  6 */ JPAType_StripeCross,
        /*  7 */ JPAType_Rotation,
        /*  8 */ JPAType_RotationCross,
        /*  9 */ JPAType_DirBillboard,
        /* 10 */ JPAType_YBillboard,
    };

    static GXBlendMode stBlendMode[4];
    static GXBlendFactor stBlendFactor[10];
    static GXLogicOp stLogicOp[16];
    static GXCompare stCompare[8];
    static GXAlphaOp stAlphaOp[4];

    virtual ~JPABaseShape() {}
    virtual u8 getType() = 0;
    virtual u8 getDirType() = 0;
    virtual u8 getRotType() = 0;
    virtual u8 getBasePlaneType() = 0;
    virtual f32 getBaseSizeX() = 0;
    virtual f32 getBaseSizeY() = 0;
    virtual s16 getLoopOffset() = 0;
    virtual s16 getColLoopOffset() = 0;
    virtual s16 getTexLoopOffset() = 0;
    virtual BOOL isEnableGlobalColAnm() = 0;
    virtual BOOL isEnableGlobalTexAnm() = 0;
    virtual u32 getListOrder() = 0;
    virtual u32 getChildOrder() = 0;
    virtual GXTevColorArg* getTevColorArg() = 0;
    virtual GXTevAlphaArg* getTevAlphaArg() = 0;
    virtual GXBool isEnableAlphaUpdate() = 0;
    virtual GXBlendMode getBlendMode1() = 0;
    virtual GXBlendFactor getSrcBlendFactor1() = 0;
    virtual GXBlendFactor getDstBlendFactor1() = 0;
    virtual GXLogicOp getBlendOp1() = 0;
    virtual GXBool isEnableZCmp() = 0;
    virtual GXCompare getZCmpFunction() = 0;
    virtual GXBool isEnableZCmpUpdate() = 0;
    virtual GXBool getZCompLoc() = 0;
    virtual GXCompare getAlphaCmpComp0() = 0;
    virtual GXCompare getAlphaCmpComp1() = 0;
    virtual GXAlphaOp getAlphaCmpOp() = 0;
    virtual u8 getAlphaCmpRef0() = 0;
    virtual u8 getAlphaCmpRef1() = 0;
    virtual u32 isEnableAnmTone() = 0;
    virtual u32 isEnableProjection() = 0;
    virtual u32 isClipOn() = 0;
    virtual BOOL isEnableTextureAnm() = 0;
    virtual BOOL textureIsEmpty() = 0;
    virtual u8 getTextureAnmType() = 0;
    virtual u8 getTextureAnmKeyNum() = 0;
    virtual u8 getTextureIndex() = 0;
    virtual u8 getTextureIndex(u8 idx) = 0;
    virtual BOOL isEnablePrm() = 0;
    virtual BOOL isEnableEnv() = 0;
    virtual BOOL isEnablePrmAnm() = 0;
    virtual BOOL isEnableEnvAnm() = 0;
    virtual GXColor getPrmColor() = 0;
    virtual GXColor getEnvColor() = 0;
    virtual GXColor getPrmColor(s16) = 0;
    virtual GXColor getEnvColor(s16) = 0;
    virtual u8 getColorRegAnmType() = 0;
    virtual s32 getColorRegAnmMaxFrm() = 0;
    virtual u32 isEnableTexScrollAnm() = 0;
    virtual f32 getTilingX() = 0;
    virtual f32 getTilingY() = 0;
    virtual f32 getTexStaticTransX() = 0;
    virtual f32 getTexStaticTransY() = 0;
    virtual f32 getTexStaticScaleX() = 0;
    virtual f32 getTexStaticScaleY() = 0;
    virtual f32 getTexScrollTransX() = 0;
    virtual f32 getTexScrollTransY() = 0;
    virtual f32 getTexScrollScaleX() = 0;
    virtual f32 getTexScrollScaleY() = 0;
    virtual f32 getTexScrollRotate() = 0;
};

struct JPABaseShapeData {
    /* 0x00 */ u32 mFlags;
    /* 0x04 */ s16 mPrmAnimDataOffs;
    /* 0x06 */ s16 mEnvAnimDataOffs;
    /* 0x08 */ f32 mBaseSizeX;
    /* 0x0c */ f32 mBaseSizeY;
    /* 0x10 */ s16 mLoopOffset;
    /* 0x12 */ u16 mBlendFlags;
    /* 0x14 */ u8 mAlphaFlags;
    /* 0x15 */ u8 mAlphaCmpRef0;
    /* 0x16 */ u8 mAlphaCmpRef1;
    /* 0x17 */ u8 mZFlags;
    /* 0x18 */ u8 mTextureFlags;
    /* 0x19 */ u8 mTextureAnmKeyNum;
    /* 0x1a */ u8 mTextureIndex;
    /* 0x1b */ u8 mColorFlags;
    /* 0x1c */ u8 prmAnmKeyNum;
    /* 0x1d */ u8 envAnmKeyNum;
    /* 0x1e */ s16 mColorRegAnmMaxFrm;
    /* 0x20 */ GXColor mPrmColor;
    /* 0x24 */ GXColor mEnvColor;
    /* 0x28 */ f32 mTilingX;
    /* 0x2c */ f32 mTilingY;
    /* 0x30 */ f32 mTexStaticTransX;
    /* 0x34 */ f32 mTexStaticTransY;
    /* 0x38 */ f32 mTexStaticScaleX;
    /* 0x3c */ f32 mTexStaticScaleY;
    /* 0x40 */ f32 mTexScrollTransX;
    /* 0x44 */ f32 mTexScrollTransY;
    /* 0x48 */ f32 mTexScrollScaleX;
    /* 0x4c */ f32 mTexScrollScaleY;
    /* 0x50 */ f32 mTexScrollRotate;
};

class JPABaseShapeArc : public JPABaseShape {
public:
    static GXTevColorArg stTevColorArg[6][4];
    static GXTevAlphaArg stTevAlphaArg[2][4];

    JPABaseShapeArc(const u8 * pData, JKRHeap * pHeap);
    virtual ~JPABaseShapeArc() {}
    virtual u8 getType() { return pBsd->mFlags & 0x0F; }
    virtual u8 getDirType() { return (pBsd->mFlags >> 4) & 0x07; }
    virtual u8 getRotType() { return (pBsd->mFlags >> 7) & 0x07; }
    virtual u8 getBasePlaneType() { return (pBsd->mFlags >> 10) & 0x01; }
    virtual f32 getBaseSizeX() { return pBsd->mBaseSizeX; }
    virtual f32 getBaseSizeY() { return pBsd->mBaseSizeY; }
    virtual s16 getLoopOffset() { return pBsd->mLoopOffset; }
    virtual s16 getColLoopOffset() { return mColLoopOffset; }
    virtual s16 getTexLoopOffset() { return mTexLoopOffset; }
    virtual BOOL isEnableGlobalColAnm() { return mGlobalAnmFlags & 0x02; }
    virtual BOOL isEnableGlobalTexAnm() { return mGlobalAnmFlags & 0x01; }
    virtual u32 getListOrder() { return pBsd->mFlags & 0x200000; }
    virtual u32 getChildOrder() { return pBsd->mFlags & 0x400000; }
    virtual GXTevColorArg* getTevColorArg() { return stTevColorArg[(pBsd->mFlags >> 15) & 0x07]; }
    virtual GXTevAlphaArg* getTevAlphaArg() { return stTevAlphaArg[(pBsd->mFlags >> 18) & 0x01]; }
    virtual GXBlendMode getBlendMode1() { return stBlendMode[(pBsd->mBlendFlags >> 0) & 0x03]; }
    virtual GXBlendFactor getSrcBlendFactor1() { return stBlendFactor[(pBsd->mBlendFlags >> 2) & 0x0F]; }
    virtual GXBlendFactor getDstBlendFactor1() { return stBlendFactor[(pBsd->mBlendFlags >> 6) & 0x0F]; }
    virtual GXLogicOp getBlendOp1() { return stLogicOp[(pBsd->mBlendFlags >> 10) & 0x0F]; }
    virtual GXBool isEnableAlphaUpdate() { return (pBsd->mBlendFlags >> 14) & 0x01; }
    virtual GXBool isEnableZCmp() { return (pBsd->mZFlags >> 0) & 0x01; }
    virtual GXCompare getZCmpFunction() { return stCompare[(pBsd->mZFlags >> 1) & 0x07]; }
    virtual GXBool isEnableZCmpUpdate() { return (pBsd->mZFlags >> 4) & 0x01; }
    virtual GXBool getZCompLoc() { return (pBsd->mZFlags >> 5) & 0x01; }
    virtual GXCompare getAlphaCmpComp0() { return stCompare[(pBsd->mAlphaFlags >> 0) & 0x07]; }
    virtual GXCompare getAlphaCmpComp1() { return stCompare[(pBsd->mAlphaFlags >> 5) & 0x07]; }
    virtual GXAlphaOp getAlphaCmpOp() { return stAlphaOp[(pBsd->mAlphaFlags >> 3) & 0x03]; }
    virtual u8 getAlphaCmpRef0() { return pBsd->mAlphaCmpRef0; }
    virtual u8 getAlphaCmpRef1() { return pBsd->mAlphaCmpRef1; }
    virtual u32 isEnableAnmTone() { return pBsd->mFlags & 0x80000; }
    virtual u32 isEnableProjection() { return pBsd->mFlags & 0x100000; }
    virtual u32 isClipOn() { return pBsd->mFlags & 0x800000; }
    virtual BOOL isEnableTextureAnm() { return pBsd->mTextureFlags & 0x01; }
    virtual BOOL textureIsEmpty() { return !(pBsd->mTextureFlags & 0x02); }
    virtual u8 getTextureAnmType() { return (pBsd->mTextureFlags >> 2) & 0x07; }
    virtual u8 getTextureAnmKeyNum() { return pBsd->mTextureAnmKeyNum; }
    virtual u8 getTextureIndex() { return pBsd->mTextureIndex; }
    virtual u8 getTextureIndex(u8 idx) { return mpTexAnmIdxArr[idx]; }
    virtual BOOL isEnablePrm() { return pBsd->mColorFlags & 0x01; }
    virtual BOOL isEnableEnv() { return pBsd->mColorFlags & 0x04; }
    virtual BOOL isEnablePrmAnm() { return pBsd->mColorFlags & 0x02; }
    virtual BOOL isEnableEnvAnm() { return pBsd->mColorFlags & 0x08; }
    virtual GXColor getPrmColor() { return pBsd->mPrmColor; }
    virtual GXColor getEnvColor() { return pBsd->mEnvColor; }
    virtual GXColor getPrmColor(s16 idx) { return mpPrmColorArr[idx]; }
    virtual GXColor getEnvColor(s16 idx) { return mpEnvColorArr[idx]; }
    virtual u8 getColorRegAnmType() { return (pBsd->mColorFlags >> 4) & 0x07; }
    virtual s32 getColorRegAnmMaxFrm() { return pBsd->mColorRegAnmMaxFrm; }
    virtual u32 isEnableTexScrollAnm() { return pBsd->mFlags & 0x1000000; }
    virtual f32 getTilingX() { return pBsd->mTilingX; }
    virtual f32 getTilingY() { return pBsd->mTilingY; }
    virtual f32 getTexStaticTransX() { return pBsd->mTexStaticTransX; }
    virtual f32 getTexStaticTransY() { return pBsd->mTexStaticTransY; }
    virtual f32 getTexStaticScaleX() { return pBsd->mTexStaticScaleX; }
    virtual f32 getTexStaticScaleY() { return pBsd->mTexStaticScaleY; }
    virtual f32 getTexScrollTransX() { return pBsd->mTexScrollTransX; }
    virtual f32 getTexScrollTransY() { return pBsd->mTexScrollTransY; }
    virtual f32 getTexScrollScaleX() { return pBsd->mTexScrollScaleX; }
    virtual f32 getTexScrollScaleY() { return pBsd->mTexScrollScaleY; }
    virtual f32 getTexScrollRotate() { return pBsd->mTexScrollRotate; }

    /* 0x04 */ const JPABaseShapeData* pBsd;
    /* 0x08 */ const u8 * mpTexAnmIdxArr;
    /* 0x0C */ const GXColor * mpPrmColorArr;
    /* 0x10 */ const GXColor * mpEnvColorArr;
    /* 0x14 */ s16 mColLoopOffset;
    /* 0x16 */ s16 mTexLoopOffset;
    /* 0x18 */ u8 mGlobalAnmFlags;
};

#endif /* JPABASESHAPE_H */
