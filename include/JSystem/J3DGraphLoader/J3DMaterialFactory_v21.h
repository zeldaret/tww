#ifndef J3DMATERIALFACTORY_V21_H
#define J3DMATERIALFACTORY_V21_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "JSystem/J3DGraphBase/J3DMatBlock.h"

class J3DMaterial;
struct J3DMaterialBlock_v21;
class J3DMaterialInitData_v21;
class J3DIndInitData;
class J3DColorChanInfo;
class J3DLightInfo;
class J3DTexCoordInfo;
class J3DTexCoord2Info;
class J3DTexMtxInfo;
class J3DTevOrderInfo;
class J3DTevStageInfo;
class J3DTevSwapModeInfo;
class J3DTevSwapModeTableInfo;
class J3DFogInfo;
class J3DAlphaCompInfo;
class J3DBlendInfo;
class J3DZModeInfo;
class J3DNBTScaleInfo;
class J3DDisplayListInit;
class J3DPatchingInfo;
class J3DCurrentMtxInfo;

struct J3DMaterialInitData_v21 {
    /* 0x000 */ u8 mMaterialMode;
    /* 0x001 */ u8 mCullModeIdx;
    /* 0x002 */ u8 mColorChanNumIdx;
    /* 0x003 */ u8 mTexGenNumIdx;
    /* 0x004 */ u8 mTevStageNumIdx;
    /* 0x005 */ u8 mZCompLocIdx;
    /* 0x006 */ u8 mZModeIdx;
    /* 0x007 */ u8 mDitherIdx;
    /* 0x008 */ u16 mMatColorIdx[2];
    /* 0x00C */ u16 mColorChanIdx[4];
    /* 0x014 */ u16 mTexCoordIdx[8];
    /* 0x024 */ u8 field_0x024[16];
    /* 0x034 */ u16 mTexMtxIdx[8];
    /* 0x044 */ u8 field_0x044[44];
    /* 0xXXX */ u16 mTexNoIdx[8];
    /* 0xXXX */ u16 mTevKColorIdx[4];
    /* 0xXXX */ u8 mTevKColorSel[16];
    /* 0xXXX */ u8 mTevKAlphaSel[16];
    /* 0xXXX */ u16 mTevOrderIdx[16];
    /* 0xXXX */ u16 mTevColorIdx[4];
    /* 0xXXX */ u16 mTevStageIdx[16];
    /* 0xXXX */ u16 mTevSwapModeIdx[16];
    /* 0xXXX */ u16 mTevSwapModeTableIdx[4];
    /* 0xXXX */ u8 field_0x12c[24];
    /* 0xXXX */ u16 mFogIdx;
    /* 0xXXX */ u16 mAlphaCompIdx;
    /* 0xXXX */ u16 mBlendIdx;
    /* 0xXXX */ u16 mNBTScaleIdx;
};

class J3DMaterialFactory_v21 {
public:
    J3DMaterialFactory_v21(const J3DMaterialBlock_v21&);
    u16 countUniqueMaterials();
    u32 countTexGens(int) const;
    u32 countStages(int) const;
    J3DMaterial* create(J3DMaterial*, int, unsigned long) const;
    J3DGXColor newMatColor(int, int) const;
    u8 newColorChanNum(int) const;
    J3DColorChan newColorChan(int, int) const;
    u32 newTexGenNum(int) const;
    J3DTexCoord newTexCoord(int, int) const;
    J3DTexMtx* newTexMtx(int, int) const;
    u8 newCullMode(int) const;
    u16 newTexNo(int, int) const;
    J3DTevOrder newTevOrder(int, int) const;
    J3DGXColorS10 newTevColor(int, int) const;
    J3DGXColor newTevKColor(int, int) const;
    u8 newTevStageNum(int) const;
    J3DTevStage newTevStage(int, int) const;
    J3DTevSwapModeTable newTevSwapModeTable(int, int) const;
    J3DFog* newFog(int) const;
    J3DAlphaComp newAlphaComp(int) const;
    J3DBlend newBlend(int) const;
    J3DZMode newZMode(int) const;
    u8 newZCompLoc(int) const;
    u8 newDither(int) const;
    J3DNBTScale newNBTScale(int) const;

    u16 getMaterialID(int idx) const { return mpMaterialID[idx]; }
    u8 getMaterialMode(int idx) const { return mpMaterialInitData[getMaterialID(idx)].mMaterialMode; }

    /* 0x00 */ u16 mMaterialNum;
    /* 0x04 */ J3DMaterialInitData_v21* mpMaterialInitData;
    /* 0x08 */ u16* mpMaterialID;
    /* 0x0C */ GXColor* mpMatColor;
    /* 0x10 */ u8* mpColorChanNum;
    /* 0x14 */ J3DColorChanInfo* mpColorChanInfo;
    /* 0x18 */ u8* mpTexGenNum;
    /* 0x1C */ J3DTexCoordInfo* mpTexCoordInfo;
    /* 0x20 */ J3DTexCoord2Info* mpTexCoord2Info;
    /* 0x24 */ J3DTexMtxInfo* mpTexMtxInfo;
    /* 0x28 */ J3DTexMtxInfo* field_0x28;
    /* 0x2C */ u16* mpTexNo;
    /* 0x30 */ GXCullMode* mpCullMode;
    /* 0x34 */ J3DTevOrderInfo* mpTevOrderInfo;
    /* 0x38 */ GXColorS10* mpTevColor;
    /* 0x3C */ GXColor* mpTevKColor;
    /* 0x40 */ u8* mpTevStageNum;
    /* 0x44 */ J3DTevStageInfo* mpTevStageInfo;
    /* 0x48 */ J3DTevSwapModeInfo* mpTevSwapModeInfo;
    /* 0x4C */ J3DTevSwapModeTableInfo* mpTevSwapModeTableInfo;
    /* 0x50 */ J3DFogInfo* mpFogInfo;
    /* 0x54 */ J3DAlphaCompInfo* mpAlphaCompInfo;
    /* 0x58 */ J3DBlendInfo* mpBlendInfo;
    /* 0x5C */ J3DZModeInfo* mpZModeInfo;
    /* 0x60 */ u8* mpZCompLoc;
    /* 0x64 */ u8* mpDither;
    /* 0x68 */ J3DNBTScaleInfo* mpNBTScaleInfo;
    /* 0x6C */ u16 field_0x68;
    /* 0x6E */ u8 field_0x69;
    /* 0x6F */ u8 field_0x6a;
};

#endif /* J3DMATERIALFACTORY_V21_H */
