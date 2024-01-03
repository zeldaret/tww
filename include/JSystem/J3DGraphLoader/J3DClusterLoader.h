#ifndef J3DCLUSTERLOADER_H
#define J3DCLUSTERLOADER_H

#include "global.h"

class J3DDeformData;

// TODO: move these into a new header
struct JSystemBlockHeader { // actual name unknown
    /* 0x0 */ u32 mType;
    /* 0x4 */ u32 mNextOffset;

    const JSystemBlockHeader* getNext() const {
        return reinterpret_cast<const JSystemBlockHeader*>(reinterpret_cast<const u8*>(this) + mNextOffset);
    }
};  // Size = 0x8

struct JSystemFileHeader { // actual name unknown
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ u32 mType;
    /* 0x08 */ u32 mFileSize;
    /* 0x0C */ u32 mBlockNum;
    /* 0x10 */ u8 _10[0x20 - 0x10];
    /* 0x20 */ JSystemBlockHeader mFirst;
};

class J3DClusterBlock : public JSystemBlockHeader {
private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x08 */ u16 m08;
    /* 0x0A */ u16 m0A;
    /* 0x0C */ u16 m0C;
    /* 0x0E */ u16 m0E;
    /* 0x10 */ u16 m10;
    /* 0x12 */ u16 m12;
    /* 0x14 */ const void* m14;
    /* 0x18 */ const void* m18;
    /* 0x1C */ const void* m1C;
    /* 0x20 */ const void* m20;
    /* 0x24 */ const void* m24;
    /* 0x28 */ const void* m28;
    /* 0x2C */ const void* m2C;
};

struct J3DClusterLoaderDataBase {
    static void* load(const void*);
};

class J3DClusterLoader {
public:
    virtual void* load(const void*) = 0;
    virtual ~J3DClusterLoader() {}
};

class J3DClusterLoader_v15 : public J3DClusterLoader {
public:
    J3DClusterLoader_v15();
    ~J3DClusterLoader_v15();
    void* load(const void*);
    void readCluster(const J3DClusterBlock*);

private:
    /* 0x04 */ J3DDeformData* mpDeformData;
};

#endif /* J3DCLUSTERLOADER_H */
