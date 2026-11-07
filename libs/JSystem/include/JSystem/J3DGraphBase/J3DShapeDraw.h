#ifndef J3DSHAPEDRAW_H
#define J3DSHAPEDRAW_H

#include "dolphin/types.h"

class J3DShapeDraw {
public:
    J3DShapeDraw(u8 const*, u32);
    void draw() const;

    virtual ~J3DShapeDraw() {}

    u8* getDisplayList() const { return (u8*)mDisplayList; }
    u32 getDisplayListSize() const { return mDisplayListSize; }
    void setDisplayListSize(u32 size) { mDisplayListSize = size; }

private:
    /* 0x04 */ u32 mDisplayListSize;
    /* 0x08 */ void* mDisplayList;
};

#endif /* J3DSHAPEDRAW_H */
