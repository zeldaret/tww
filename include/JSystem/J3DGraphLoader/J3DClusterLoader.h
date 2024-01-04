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

    /* 0x08 */ u16 mClusterNum;
    /* 0x0A */ u16 mClusterKeyNum;
    /* 0x0C */ u16 mClusterVertexNum;
    /* 0x0E */ u16 mVtxPosNum;
    /* 0x10 */ u16 mVtxNrmNum;
    /* 0x14 */ void* mClusterPointer;
    /* 0x18 */ void* mClusterKeyPointer;
    /* 0x1C */ void* mClusterVertex;
    /* 0x20 */ void* mVtxPos;
    /* 0x24 */ void* mVtxNrm;
    /* 0x28 */ void* mClusterName;
    /* 0x2C */ void* mClusterKeyName;
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
