#ifndef JPARESOURCEMANAGER_H
#define JPARESOURCEMANAGER_H

#include "dolphin/gx/GX.h"
#include "JSystem/JParticle/JPATexture.h"

class JKRHeap;
class JPATexture;
struct JPAEmitterData;
struct ResTIMG;

class JPATextureResource {
public:
    JPATextureResource(u32, JKRHeap*);
    void registration(JPATexture*);

    inline void load(u16 id, GXTexMapID texMap) {
        pTexResArray[id]->load(texMap);
    }

    inline void loadDefaultTexture(GXTexMapID texMap) {
        defaultTex.load(texMap);
    }

public:
    /* 0x00 */ JPADefaultTexture defaultTex;
    /* 0x24 */ u32 registNum;
    /* 0x28 */ u32 maxNum;
    /* 0x2C */ JPATexture** pTexResArray;
};

class JPAEmitterResource {
public:
    JPAEmitterResource(u32, JKRHeap*);
    void registration(JPAEmitterData*, u16);
    JPAEmitterData * getByUserIndex(u16);
    BOOL checkUserIndexDuplication(u16);

public:
    /* 0x00 */ u32 registNum;
    /* 0x04 */ u32 maxNum;
    /* 0x08 */ JPAEmitterData** pEmtrResArray;
};

class JPAResourceManager {
public:
    JPAResourceManager(const void*, JKRHeap*);
    const ResTIMG* swapTexture(const ResTIMG*, const char*);
    JPATextureResource * getTextureResource() { return pTexRes; }
    JPAEmitterResource * getEmitterResource() { return pEmtrRes; }

public:
    /* 0x00 */ JKRHeap * pHeap;
    /* 0x04 */ JPAEmitterResource * pEmtrRes;
    /* 0x08 */ JPATextureResource * pTexRes;
};

#endif /* JPARESOURCEMANAGER_H */
