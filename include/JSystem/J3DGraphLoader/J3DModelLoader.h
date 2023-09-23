#ifndef J3DMODELLOADER_H
#define J3DMODELLOADER_H

#include "dolphin/types.h"

class J3DModelData;
class J3DMaterialTable;

class J3DModelLoaderDataBase {
public:
    static J3DModelData* load(void const*, u32);
    static J3DModelData* loadBinaryDisplayList(void const*, u32);
    static J3DMaterialTable* loadMaterialTable(void const*);
};

#endif /* J3DMODELLOADER_H */
