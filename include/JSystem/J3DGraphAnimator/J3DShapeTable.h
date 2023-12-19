#ifndef J3DSHAPETABLE_H
#define J3DSHAPETABLE_H

#include "JSystem/J3DGraphBase/J3DShape.h"
#include "dolphin/types.h"

class JUTNameTab;

class J3DShapeTable {
public:
    inline void clear() {
        mShapeNum = 0;
        mShapeNodePointer = NULL;
    }

    u16 getShapeNum() const { return mShapeNum; }
    J3DShape* getShapeNodePointer(u16 idx) const { return mShapeNodePointer[idx]; }

private:
    friend class J3DModelLoader;
    friend class J3DModelData;

    /* 0x0 */ u16 mShapeNum;
    /* 0x4 */ J3DShape** mShapeNodePointer;
};  // Size: 0x08

#endif /* J3DSHAPETABLE_H */
