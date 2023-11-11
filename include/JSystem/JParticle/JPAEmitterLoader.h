#ifndef JPAEMITTERLOADER_H
#define JPAEMITTERLOADER_H

#include "dolphin/gx/GX.h"

class JPADataBlockLinkInfo;
class JPAEmitterResource;
class JPATextureResource;
class JKRHeap;

class JPAEmitterArchiveLoaderDataBase {
public:
    static void load(const u8*, JKRHeap*, JPAEmitterResource**, JPATextureResource**);
};

struct JPAEmitterData {
public:
    JPAEmitterData() : pLinkInfoArray(NULL) {}
    JPADataBlockLinkInfo** getLinkInfo() { return pLinkInfoArray; }
    void setUserIndex(u16 v) { userIndex = v; }
    u16 getUserIndex() { return userIndex; }

public:
    /* 0x00 */ JPADataBlockLinkInfo** pLinkInfoArray;
    /* 0x04 */ u16 infoNum;
    /* 0x06 */ u16 userIndex;
};

#endif /* JPAEMITTERLOADER_H */
