#ifndef J3DMATERIALFACTORY_V21_H
#define J3DMATERIALFACTORY_V21_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

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

class J3DMaterialFactory_v21 {
public:
    J3DMaterialFactory_v21(const J3DMaterialBlock_v21&);
    u16 countUniqueMaterials();
    void countTexGens(int) const;
    void countStages(int) const;
    J3DMaterial* create(J3DMaterial*, int, unsigned long) const;
    void newMatColor(int, int) const;
    void newColorChanNum(int) const;
    void newColorChan(int, int) const;
    void newTexGenNum(int) const;
    void newTexCoord(int, int) const;
    void newTexMtx(int, int) const;
    void newCullMode(int) const;
    void newTexNo(int, int) const;
    void newTevOrder(int, int) const;
    void newTevColor(int, int) const;
    void newTevKColor(int, int) const;
    void newTevStageNum(int) const;
    void newTevStage(int, int) const;
    void newTevSwapModeTable(int, int) const;
    void newFog(int) const;
    void newAlphaComp(int) const;
    void newBlend(int) const;
    void newZMode(int) const;
    void newZCompLoc(int) const;
    void newDither(int) const;
    void newNBTScale(int) const;

    u16 getMaterialID(int idx) const { return mpMaterialID[idx]; }
    void getMaterialMode(int) const {}

    /* 0x00 */ u16 mMaterialNum;
    /* 0x04 */ J3DMaterialInitData_v21* field_0x04;
    /* 0x08 */ u16* mpMaterialID;
    /* 0x0C */ GXColor* field_0x0c;
    /* 0x10 */ u8* field_0x10;
    /* 0x14 */ J3DColorChanInfo* field_0x14;
    /* 0x18 */ u8* field_0x18;
    /* 0x1C */ J3DTexCoordInfo* field_0x1c;
    /* 0x20 */ J3DTexCoord2Info* field_0x20;
    /* 0x24 */ J3DTexMtxInfo* field_0x24;
    /* 0x28 */ J3DTexMtxInfo* field_0x28;
    /* 0x2C */ u16* field_0x2c;
    /* 0x30 */ GXCullMode* field_0x30;
    /* 0x34 */ J3DTevOrderInfo* field_0x34;
    /* 0x38 */ GXColorS10* field_0x38;
    /* 0x3C */ GXColor* field_0x3c;
    /* 0x40 */ u8* field_0x40;
    /* 0x44 */ J3DTevStageInfo* field_0x44;
    /* 0x48 */ J3DTevSwapModeTableInfo* field_0x48;
    /* 0x4C */ J3DFogInfo* field_0x4c;
    /* 0x50 */ J3DAlphaCompInfo* field_0x50;
    /* 0x54 */ J3DBlendInfo* field_0x54;
    /* 0x58 */ J3DZModeInfo* field_0x58;
    /* 0x5C */ u8* field_0x5c;
    /* 0x60 */ u8* field_0x60;
    /* 0x64 */ J3DNBTScaleInfo* field_0x64;
    /* 0x68 */ u16 field_0x68;
    /* 0x69 */ u8 field_0x69;
    /* 0x6A */ u8 field_0x6a;
};

#endif /* J3DMATERIALFACTORY_V21_H */
