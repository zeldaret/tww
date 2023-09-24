#ifndef J3DSHAPETABLE_H
#define J3DSHAPETABLE_H

#include "JSystem/J3DGraphBase/J3DShape.h"
#include "dolphin/types.h"

class JUTNameTab;

class J3DShapeTable {
public:
    J3DShapeTable() {
        mShapeNum = 0;
        mShapeNodePointer = NULL;
    }

    void hide();
    void show();
    void initShapeNodes(J3DDrawMtxData*, J3DVertexData*);
    void sortVcdVatCmd();

    virtual ~J3DShapeTable();

    u16 getShapeNum() const { return mShapeNum; }
    J3DShape* getShapeNodePointer(u16 idx) const { return mShapeNodePointer[idx]; }

private:
    /* 0x4 */ u16 mShapeNum;
    /* 0x8 */ J3DShape** mShapeNodePointer;
};  // Size: 0x0C

#endif /* J3DSHAPETABLE_H */
