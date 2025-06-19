#ifndef J3DSYS_H
#define J3DSYS_H

#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/gx/GX.h"
#include "dolphin/types.h"

// Perhaps move to a new J3DEnum.h?
enum J3DError {
    J3DErrType_Success = 0,
    J3DErrType_Locked = 2,
    J3DErrType_OutOfMemory = 4,
};

enum J3DSysDrawBuffer {
    /* 0x0 */ OPA_BUFFER,
    /* 0x1 */ XLU_BUFFER
};

class J3DMtxCalc;
class J3DModel;
class J3DMatPacket;
class J3DShapePacket;
class J3DShape;
class J3DDrawBuffer;
class J3DTexture;

struct J3DTexCoordScaleInfo {
    /* 0x0 */ u16 field_0x00;
    /* 0x2 */ u16 field_0x02;
    /* 0x4 */ u16 field_0x04;
    /* 0x6 */ u16 field_0x06;
};

enum J3DSysFlag {
    J3DSysFlag_UNK2        = 0x00000002,
    J3DSysFlag_SkinPosCpu  = 0x00000004,
    J3DSysFlag_SkinNrmCpu  = 0x00000008,
    J3DSysFlag_PostTexMtx  = 0x40000000,
    J3DSysFlag_UNK80000000 = 0x80000000,
};

struct J3DSys {
public:
    enum DrawMode {
        /* 0x3 */ OPA_TEX_EDGE = 3,
        /* 0x4 */ XLU,
    };

    MtxP getViewMtx() { return mViewMtx; }
    void setViewMtx(Mtx m) { MTXCopy(m, mViewMtx); }

    void setDrawModeOpaTexEdge() { mDrawMode = OPA_TEX_EDGE; }

    void setDrawModeXlu() { mDrawMode = XLU; }

    void* getVtxPos() { return mVtxPos; }
    void setVtxPos(void* pVtxPos) { mVtxPos = pVtxPos; }

    void* getVtxNrm() { return mVtxNrm; }
    void setVtxNrm(void* pVtxNrm) { mVtxNrm = pVtxNrm; }

    void* getVtxCol() { return mVtxCol; }
    void setVtxCol(GXColor* pVtxCol) { mVtxCol = pVtxCol; }

    void setModel(J3DModel* pModel) {
        J3D_ASSERT(200, pModel, "Error : null pointer.");
        mModel = pModel;
    }
    void setShapePacket(J3DShapePacket* pPacket) { mShapePacket = pPacket; }
    void setMatPacket(J3DMatPacket* pPacket) { mMatPacket = pPacket; }
    J3DMatPacket* getMatPacket() { return mMatPacket; }
    void setMaterialMode(u32 mode) { mMaterialMode = mode; }

    void setCurrentMtxCalc(J3DMtxCalc * pCalc) { mCurrentMtxCalc = pCalc; }
    J3DMtxCalc * getCurrentMtxCalc() { return mCurrentMtxCalc; }

    void setTexture(J3DTexture* pTex) { mTexture = pTex; }
    J3DTexture* getTexture() { return mTexture; }

    void setNBTScale(Vec* scale) { mNBTScale = scale; }

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) { return (mFlags & flag) ? true : false; }

    void setModelDrawMtx(Mtx* pMtxArr) {
        mModelDrawMtx = pMtxArr;
        GXSetArray(GX_POS_MTX_ARRAY, mModelDrawMtx, sizeof(*mModelDrawMtx));
    }

    void setModelNrmMtx(Mtx33* pMtxArr) {
        mModelNrmMtx = pMtxArr;
        GXSetArray(GX_NRM_MTX_ARRAY, mModelNrmMtx, sizeof(*mModelNrmMtx));
    }

    // Type 0: Opa Buffer
    // Type 1: Xlu Buffer
    void setDrawBuffer(J3DDrawBuffer* buffer, int type) {
        J3D_ASSERT(114, type >= 0 && type < 2, "Error : range over.");
        J3D_ASSERT(115, buffer, "Error : null pointer.");
        mDrawBuffer[type] = buffer;
    }

    // Type 0: Opa Buffer
    // Type 1: Xlu Buffer
    J3DDrawBuffer* getDrawBuffer(int type) {
        J3D_ASSERT(121, type >= 0 && type < 2, "Error : range over.");
        return mDrawBuffer[type];
    }

    Mtx& getModelDrawMtx(u16 no) { return mModelDrawMtx[no]; }
    J3DShapePacket* getShapePacket() { return mShapePacket; }

    J3DModel* getModel() { return mModel; }
    Vec* getNBTScale() { return mNBTScale; }

    static Mtx mCurrentMtx;
    static Vec mCurrentS;
    static Vec mParentS;
    static J3DTexCoordScaleInfo sTexCoordScaleTable[8];

    /* 0x000 */ Mtx mViewMtx;
    /* 0x030 */ J3DMtxCalc* mCurrentMtxCalc;
    /* 0x034 */ u32 mFlags;
    /* 0x038 */ J3DModel* mModel;
    /* 0x03C */ J3DMatPacket* mMatPacket;
    /* 0x040 */ J3DShapePacket* mShapePacket;
    /* 0x044 */ J3DShape* mShape;
    /* 0x048 */ J3DDrawBuffer* mDrawBuffer[2];
    /* 0x050 */ u32 mDrawMode;
    /* 0x054 */ u32 mMaterialMode;
    /* 0x058 */ J3DTexture* mTexture;
    /* 0x05C */ u8 field_0x5c[0x04];
    /* 0x060 */ u32 mTexCacheRegionNum;
    /* 0x064 */ GXTexRegion mTexCacheRegion[8];
    /* 0x0E4 */ u8 field_0xe4[0x20];
    /* 0x104 */ void* field_0x104;
    /* 0x108 */ Mtx* mModelDrawMtx;
    /* 0x10C */ Mtx33* mModelNrmMtx;
    /* 0x110 */ void* mVtxPos;
    /* 0x114 */ void* mVtxNrm;
    /* 0x118 */ GXColor* mVtxCol;
    /* 0x11C */ void* field_0x11c;
    /* 0x120 */ void* field_0x120;
    /* 0x124 */ Vec* mNBTScale;

    J3DSys();
    void loadPosMtxIndx(int, u16) const;
    void loadNrmMtxIndx(int, u16) const;
    void setTexCacheRegion(GXTexCacheSize);
    void drawInit();
    void reinitGX();
    void reinitGenMode();
    void reinitLighting();
    void reinitTransform();
    void reinitTexture();
    void reinitTevStages();
    void reinitIndStages();
    void reinitPixelProc();
};

extern u32 j3dDefaultViewNo;
extern J3DSys j3dSys;

#endif /* J3DSYS_H */
