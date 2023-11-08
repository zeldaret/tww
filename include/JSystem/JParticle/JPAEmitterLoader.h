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
    JPAEmitterData() : pLinkInfoArray(NULL) {}
    /* 0x00 */ JPADataBlockLinkInfo** pLinkInfoArray;
    /* 0x04 */ u16 infoNum;
    /* 0x06 */ u16 userIndex;
};

#endif /* JPAEMITTERLOADER_H */
