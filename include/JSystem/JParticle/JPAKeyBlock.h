#ifndef JPAKEYBLOCK_H
#define JPAKEYBLOCK_H

#include "dolphin/types.h"

struct JPAKeyBlockData {
    /* 0x00 */ u8 mID;
    /* 0x01 */ u8 m01[0x04 - 0x01];
    /* 0x04 */ u8 mNumber;
    /* 0x05 */ u8 m05[0x06 - 0x05];
    /* 0x06 */ u8 mbLoopEnable;
};

class JPAKeyBlock {
public:
    virtual ~JPAKeyBlock() {}
    virtual u8 getID() = 0;
    virtual bool isLoopEnable() = 0;
    virtual u8 getNumber() = 0;
    virtual const f32* getKeyDataPtr() = 0;
};

class JPAKeyBlockArc : public JPAKeyBlock {
public:
    JPAKeyBlockArc(const u8*);
    virtual ~JPAKeyBlockArc() {}
    virtual u8 getID() { return mpData->mID; }
    virtual bool isLoopEnable() { return mpData->mbLoopEnable != 0; }
    virtual u8 getNumber() { return mpData->mNumber; }
    virtual const f32* getKeyDataPtr() { return mpKeyData; }

public:
    /* 0x04 */ const JPAKeyBlockData* mpData;
    /* 0x08 */ const f32* mpKeyData;
};

#endif /* JPAKEYBLOCK_H */
