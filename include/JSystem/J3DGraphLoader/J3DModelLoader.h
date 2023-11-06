#ifndef J3DMODELLOADER_H
#define J3DMODELLOADER_H

#include "dolphin/types.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"

class J3DModelData;
class J3DMaterialTable;
class J3DModelInfoBlock;
class J3DVertexBlock;
class J3DEnvelopBlock;
class J3DDrawBlock;
class J3DJointBlock;
class J3DShapeBlock;
class J3DTextureBlock;
class J3DMaterialBlock;
class J3DMaterialBlock_v21;
class J3DMaterialDLBlock;

class J3DModelLoaderDataBase {
public:
    static J3DModelData* load(void const*, u32);
    static J3DModelData* loadBinaryDisplayList(void const*, u32);
    static J3DMaterialTable* loadMaterialTable(void const*);
};

class J3DModelLoader {
public:
    virtual void load(const void*, u32);
    virtual void loadMaterialTable(const void*);
    virtual void loadBinaryDisplayList(const void*, u32);
    virtual void calcLoadSize(const void*, u32);
    virtual void calcLoadMaterialTableSize(const void*);
    virtual void calcLoadBinaryDisplayListSize(const void*, u32);
    virtual void countMaterialNum(const void*);
    virtual void setupBBoardInfo();
    virtual ~J3DModelLoader() {}
    virtual void readMaterial(const J3DMaterialBlock*, u32) {}
    virtual void readMaterial_v21(const J3DMaterialBlock_v21*, u32) {}
    virtual void readMaterialTable(const J3DMaterialBlock*, u32) {}
    virtual void readMaterialTable_v21(const J3DMaterialBlock_v21*, u32) {}
    virtual s32 calcSizeMaterial(const J3DMaterialBlock*, u32) { return 0; }
    virtual s32 calcSizeMaterialTable(const J3DMaterialBlock*, u32) { return 0; }
    
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
    void calcSizeInformation(const J3DModelInfoBlock*, u32);
    void calcSizeJoint(const J3DJointBlock*);
    void calcSizeShape(const J3DShapeBlock*, u32);
    void calcSizeTexture(const J3DTextureBlock*);
    void calcSizeTextureTable(const J3DTextureBlock*);
    void calcSizePatchedMaterial(const J3DMaterialBlock*, u32);
    void calcSizeMaterialDL(const J3DMaterialDLBlock*, u32);
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
    s32 calcSizeMaterial(const J3DMaterialBlock*, u32);
    s32 calcSizeMaterialTable(const J3DMaterialBlock*, u32);
};

#endif /* J3DMODELLOADER_H */
