#ifndef J3DMATERIALFACTORY_H
#define J3DMATERIALFACTORY_H

#include "dolphin/types.h"

class J3DMaterial;
struct J3DMaterialBlock;
struct J3DMaterialDLBlock;

class J3DMaterialFactory {
public:
    enum MaterialType {
        MATERIAL_TYPE_NORMAL = 0,
        MATERIAL_TYPE_LOCKED = 1,
        MATERIAL_TYPE_PATCHED = 2,
    };

    J3DMaterialFactory(const J3DMaterialBlock&);
    J3DMaterialFactory(const J3DMaterialDLBlock&);
    u16 countUniqueMaterials();
    void countTexGens(int) const;
    void countStages(int) const;
    J3DMaterial* create(J3DMaterial*, MaterialType, int, unsigned long) const;
    void createNormalMaterial(J3DMaterial*, int, unsigned long) const;
    void createPatchedMaterial(J3DMaterial*, int, unsigned long) const;
    void modifyPatchedCurrentMtx(J3DMaterial*, int) const;
    void createLockedMaterial(J3DMaterial*, int, unsigned long) const;
    u32 calcSize(J3DMaterial*, MaterialType, int, unsigned long) const;
    u32 calcSizeNormalMaterial(J3DMaterial*, int, unsigned long) const;
    u32 calcSizePatchedMaterial(J3DMaterial*, int, unsigned long) const;
    u32 calcSizeLockedMaterial(J3DMaterial*, int, unsigned long) const;
    void newMatColor(int, int) const;
    void newColorChanNum(int) const;
    void newColorChan(int, int) const;
    void newAmbColor(int, int) const;
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
    void newIndTexStageNum(int) const;
    void newIndTexOrder(int, int) const;
    void newIndTexMtx(int, int) const;
    void newIndTevStage(int, int) const;
    void newIndTexCoordScale(int, int) const;
    void newFog(int) const;
    void newAlphaComp(int) const;
    void newBlend(int) const;
    void newZMode(int) const;
    void newZCompLoc(int) const;
    void newDither(int) const;
    void newNBTScale(int) const;

    u16 getMaterialID(int i_idx) const { return mpMaterialID[i_idx]; }
    void getMaterialMode(int) const {}

private:
    /* 0x00 */ u8 field_0x00[8];
    /* 0x08 */ u16* mpMaterialID;
    /* 0x0C */ u8 field_0x0c[0x7C];
};

#endif /* J3DMATERIALFACTORY_H */
