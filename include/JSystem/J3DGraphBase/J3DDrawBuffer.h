#ifndef J3DDRAWBUFFER_H
#define J3DDRAWBUFFER_H

#include "JSystem/J3DGraphBase/J3DSys.h"
#include "dolphin/types.h"

class J3DDrawBuffer;
class J3DPacket;
class J3DDrawPacket;
class J3DMatPacket;
class J3DShapePacket;
class J3DCallBackPacket;

class J3DDrawBuffer {
public:
    typedef int (J3DDrawBuffer::*sortFunc)(J3DMatPacket*);
    typedef void (J3DDrawBuffer::*drawFunc)() const;

    enum EDrawType {
        DRAW_HEAD,
        DRAW_TAIL,
    };

    enum ESortType {
        SORT_MAT,
        SORT_MAT_ANM,
        SORT_Z,
        SORT_MODEL,
        SORT_INVALID,
        SORT_NON,
    };

    J3DDrawBuffer() { initialize(); }
    J3DDrawBuffer(u32 size) { initialize(); allocBuffer(size); }
    ~J3DDrawBuffer();
    void initialize();
    J3DError allocBuffer(u32);
    void frameInit();
    int entryMatSort(J3DMatPacket*);
    int entryMatAnmSort(J3DMatPacket*);
    int entryZSort(J3DMatPacket*);
    int entryModelSort(J3DMatPacket*);
    int entryInvalidSort(J3DMatPacket*);
    int entryNonSort(J3DMatPacket*);
    int entryImm(J3DPacket* pPacket, u16 index);
    void draw() const;
    void drawHead() const;
    void drawTail() const;
    void setCallBackPacket(J3DCallBackPacket* pPacket);

    J3DPacket* getEntryPacket(u16 i) { return mpBuffer[i]; }
    u32 getEntryTableSize() { return mEntryTableSize; } // Unused in TWW, but exists in TP
    int getSortMode() { return mSortMode; }
    void setNonSort() { mSortMode = SORT_NON; }
    void setZSort() { mSortMode = SORT_Z; }
    void setInvalidSort() { mSortMode = SORT_INVALID; }
    void setZMtx(MtxP mtx) { mpZMtx = mtx; }
    void calcZRatio() {
        mZRatio = (mZFar - mZNear) / (f32)mEntryTableSize;
    }

    static sortFunc sortFuncTable[6];
    static drawFunc drawFuncTable[2];
    static int entryNum;

private:
    /* 0x00 */ J3DPacket** mpBuffer;
    /* 0x04 */ u32 mEntryTableSize;
    /* 0x08 */ u32 mDrawMode;
    /* 0x0C */ u32 mSortMode;
    /* 0x10 */ f32 mZNear;
    /* 0x14 */ f32 mZFar;
    /* 0x18 */ f32 mZRatio;
    /* 0x1C */ MtxP mpZMtx;
    /* 0x20 */ J3DPacket* mpCallBackPacket;
};

#endif /* J3DDRAWBUFFER_H */
