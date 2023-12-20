#ifndef JPATEXTURE_H
#define JPATEXTURE_H

#include "JSystem/JUtility/JUTTexture.h"
#include "dolphin/gx/GX.h"
#include "dolphin/types.h"

class JKRHeap;

struct JPATextureData {
    // Probably magic / size / flags up top here, but they're unused.
    /* 0x00 */ char field_0x00[0x0C];
    /* 0x0C */ char mName[0x14];
    /* 0x20 */ ResTIMG mResTIMG;
};

class JPATexture {
public:
    virtual ~JPATexture() {}
    virtual const char* getName() const = 0;
    virtual void load(GXTexMapID) = 0;
    virtual JUTTexture* getJUTTexture() = 0;
};

class JPATextureArc : public JPATexture {
public:
    JPATextureArc(u8 const*);
    virtual ~JPATextureArc() {}

    virtual const char* getName() const { return mpData->mName; }
    virtual void load(GXTexMapID texMapID) { mTexture.load(texMapID); }
    virtual JUTTexture* getJUTTexture() { return &mTexture; }

public:
    /* 0x00 */ JUTTexture mTexture;
    /* 0x40 */ const JPATextureData* mpData;
};

struct JPADefaultTexture {
public:
    JPADefaultTexture() : imgBuf(NULL) {}
    void initialize(JKRHeap *);

    inline void load(GXTexMapID texMap) {
        GXLoadTexObj(&mTexObj, texMap);
    }

public:
    /* 0x00 */ u8 * imgBuf;
    /* 0x04 */ GXTexObj mTexObj;
};

#endif /* JPATEXTURE_H */
