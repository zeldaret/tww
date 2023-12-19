#ifndef J3DMODELLOADER_H
#define J3DMODELLOADER_H

#include "dolphin/types.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"

inline u32 getBdlFlag_MaterialType(u32 i_flags) {
    return i_flags & 0x3000;
}

struct J3DModelBlock {
    /* 0x00 */ u32 mBlockType;
    /* 0x04 */ u32 mBlockSize;

    const J3DModelBlock* getNext() const {
        return reinterpret_cast<const J3DModelBlock*>(reinterpret_cast<const u8*>(this) + mBlockSize);
    }
};

struct J3DModelFileData {
    /* 0x00 */ u32 mMagic1;
    /* 0x04 */ u32 mMagic2;
    /* 0x08 */ u8 field_0x08[4];
    /* 0x0C */ u32 mBlockNum;
    /* 0x10 */ u8 field_0x10[0x10];
    /* 0x20 */ J3DModelBlock mBlocks[1];
};

struct J3DModelInfoBlock : public J3DModelBlock {
    /* 0x08 */ u16 mFlags;
    /* 0x0C */ u32 mPacketNum;
    /* 0x10 */ u32 mVtxNum;
    /* 0x14 */ void* mpHierarchy;
};  // Size: 0x18

struct J3DVertexBlock : public J3DModelBlock {
    /* 0x08 */ void* mpVtxAttrFmtList;
    /* 0x0C */ void* mpVtxPosArray;
    /* 0x10 */ void* mpVtxNrmArray;
    /* 0x14 */ void* mpVtxNBTArray;
    /* 0x18 */ void* mpVtxColorArray[2];
    /* 0x20 */ void* mpVtxTexCoordArray[8];
};  // Size: 0x40

struct J3DEnvelopBlock : public J3DModelBlock {
    /* 0x08 */ u16 mWEvlpMtxNum;
    /* 0x0C */ void* mpWEvlpMixMtxNum;
    /* 0x10 */ void* mpWEvlpMixIndex;
    /* 0x14 */ void* mpWEvlpMixWeight;
    /* 0x18 */ void* mpInvJointMtx;
};  // Size: 0x1C

struct J3DDrawBlock : public J3DModelBlock {
    /* 0x08 */ u16 mMtxNum;
    /* 0x0C */ void* mpDrawMtxFlag;
    /* 0x10 */ void* mpDrawMtxIndex;
};  // Size: 0x14

struct J3DJointBlock;

struct J3DMaterialBlock : public J3DModelBlock {
    /* 0x08 */ u16 mMaterialNum;
    /* 0x0C */ void* mpMaterialInitData;
    /* 0x10 */ void* mpMaterialID;
    /* 0x14 */ void* mpNameTable;
    /* 0x18 */ void* mpIndInitData;
    /* 0x1C */ void* mpCullMode;
    /* 0x20 */ void* mpMatColor;
    /* 0x24 */ void* mpColorChanNum;
    /* 0x28 */ void* mpColorChanInfo;
    /* 0x2C */ void* mpAmbColor;
    /* 0x30 */ void* mpLightInfo;
    /* 0x34 */ void* mpTexGenNum;
    /* 0x38 */ void* mpTexCoordInfo;
    /* 0x3C */ void* mpTexCoord2Info;
    /* 0x40 */ void* mpTexMtxInfo;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ void* mpTexNo;
    /* 0x4C */ void* mpTevOrderInfo;
    /* 0x50 */ void* mpTevColor;
    /* 0x54 */ void* mpTevKColor;
    /* 0x58 */ void* mpTevStageNum;
    /* 0x5C */ void* mpTevStageInfo;
    /* 0x60 */ void* mpTevSwapModeInfo;
    /* 0x64 */ void* mpTevSwapModeTableInfo;
    /* 0x68 */ void* mpFogInfo;
    /* 0x6C */ void* mpAlphaCompInfo;
    /* 0x70 */ void* mpBlendInfo;
    /* 0x74 */ void* mpZModeInfo;
    /* 0x78 */ void* mpZCompLoc;
    /* 0x7C */ void* mpDither;
    /* 0x80 */ void* mpNBTScaleInfo;
};

struct J3DMaterialBlock_v21 : public J3DModelBlock {
    /* 0x08 */ u16 mMaterialNum;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* mpNameTable;
    /* more */
};

struct J3DMaterialDLBlock : public J3DModelBlock {
    /* 0x08 */ u16 mMaterialNum;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* field_0x14;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ void* field_0x1c;
    /* 0x20 */ void* mpNameTable;
    /* more */
};

struct J3DShapeBlock;

struct J3DTextureBlock : public J3DModelBlock {
    /* 0x08 */ u16 mTextureNum;
    /* 0x0C */ void* mpTextureRes;
    /* 0x10 */ void* mpNameTable;
};

class J3DModelLoaderDataBase {
public:
    static J3DModelData* load(void const*, u32);
    static J3DModelData* loadBinaryDisplayList(void const*, u32);
    static J3DMaterialTable* loadMaterialTable(void const*);
};

class J3DModelLoader {
public:
    J3DModelLoader() :
        mpModelData(NULL),
        mpMaterialTable(NULL),
        mpShapeBlock(NULL),
        mpMaterialBlock(NULL),
        mpModelHierarchy(NULL),
        field_0x18(0) {}

    virtual J3DModelData* load(const void*, u32);
    virtual J3DMaterialTable* loadMaterialTable(const void*);
    virtual J3DModelData* loadBinaryDisplayList(const void*, u32);
    virtual u32 calcLoadSize(const void*, u32);
    virtual u32 calcLoadMaterialTableSize(const void*);
    virtual u32 calcLoadBinaryDisplayListSize(const void*, u32);
    virtual u16 countMaterialNum(const void*);
    virtual void setupBBoardInfo();
    virtual ~J3DModelLoader() {}
    virtual void readMaterial(const J3DMaterialBlock*, u32) {}
    virtual void readMaterial_v21(const J3DMaterialBlock_v21*, u32) {}
    virtual void readMaterialTable(const J3DMaterialBlock*, u32) {}
    virtual void readMaterialTable_v21(const J3DMaterialBlock_v21*, u32) {}
    virtual u32 calcSizeMaterial(const J3DMaterialBlock*, u32) { return 0; }
    virtual u32 calcSizeMaterialTable(const J3DMaterialBlock*, u32) { return 0; }
    
    void readInformation(const J3DModelInfoBlock*, u32);
    void readVertex(const J3DVertexBlock*);
    void readEnvelop(const J3DEnvelopBlock*);
    void readDraw(const J3DDrawBlock*);
    void readJoint(const J3DJointBlock*);
    void readShape(const J3DShapeBlock*, u32);
    void readTexture(const J3DTextureBlock*);
    void readTextureTable(const J3DTextureBlock*);
    void readPatchedMaterial(const J3DMaterialBlock*, u32);
    void readMaterialDL(const J3DMaterialDLBlock*, u32);
    void modifyMaterial(u32);
    u32 calcSizeInformation(const J3DModelInfoBlock*, u32);
    u32 calcSizeJoint(const J3DJointBlock*);
    u32 calcSizeShape(const J3DShapeBlock*, u32);
    u32 calcSizeTexture(const J3DTextureBlock*);
    u32 calcSizeTextureTable(const J3DTextureBlock*);
    u32 calcSizePatchedMaterial(const J3DMaterialBlock*, u32);
    u32 calcSizeMaterialDL(const J3DMaterialDLBlock*, u32);

protected:
    /* 0x04 */ J3DModelData* mpModelData;
    /* 0x08 */ J3DMaterialTable* mpMaterialTable;
    /* 0x0C */ const J3DShapeBlock* mpShapeBlock;
    /* 0x10 */ const J3DMaterialBlock* mpMaterialBlock;
    /* 0x14 */ J3DModelHierarchy* mpModelHierarchy;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
};

class J3DModelLoader_v21 : public J3DModelLoader {
public:
    ~J3DModelLoader_v21() {}
    void readMaterial_v21(const J3DMaterialBlock_v21*, u32);
    void readMaterialTable_v21(const J3DMaterialBlock_v21*, u32);
};

class J3DModelLoader_v26 : public J3DModelLoader {
public:
    ~J3DModelLoader_v26() {}
    void readMaterial(const J3DMaterialBlock*, u32);
    void readMaterialTable(const J3DMaterialBlock*, u32);
    u32 calcSizeMaterial(const J3DMaterialBlock*, u32);
    u32 calcSizeMaterialTable(const J3DMaterialBlock*, u32);
};

#endif /* J3DMODELLOADER_H */
