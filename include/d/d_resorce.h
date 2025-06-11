#ifndef D_D_RESORCE_H
#define D_D_RESORCE_H

#include "JSystem/JKernel/JKRArchive.h"
#include "dolphin/types.h"
#include "global.h"

class JKRArchive;
class JKRHeap;
class JKRSolidHeap;
class mDoDvdThd_mountArchive_c;

class dRes_info_c {
public:
    dRes_info_c();
    ~dRes_info_c();
    int set(char const*, char const*, u8, JKRHeap*);
    int loadResource();
    int setRes(JKRArchive*, JKRHeap*);
    int setRes();
    static void dump_long(dRes_info_c*, int);
    static void dump(dRes_info_c*, int);

    void* getRes(s32 i_index) { return mRes[i_index]; }
    int getResNum() { return mpArchive->countFile(); }
    int getCount() { return mCount; }
    char* getArchiveName() { return mArchiveName; }
    mDoDvdThd_mountArchive_c* getDMCommand() { return mpDMCommand; }
    JKRArchive* getArchive() { return mpArchive; }
    void incCount() { mCount++; }
    u16 decCount() {
        return --mCount;
    }

    // Debug only
    void dump(char*, dRes_info_c*, int) {}
    void getSize() {}

private:
    /* 0x00 */ char mArchiveName[14];
    /* 0x0E */ u16 mCount;
    /* 0x10 */ mDoDvdThd_mountArchive_c* mpDMCommand;
    /* 0x14 */ JKRArchive* mpArchive;
    /* 0x18 */ JKRHeap* mpParentHeap;
    /* 0x1C */ JKRSolidHeap* mDataHeap;
    /* 0x20 */ void** mRes;
};  // Size: 0x24

STATIC_ASSERT(sizeof(dRes_info_c) == 0x24);

class dRes_control_c {
public:
    dRes_control_c() {}
    ~dRes_control_c();
    static BOOL setRes(char const*, dRes_info_c*, int, char const*, u8, JKRHeap*);
    static int syncRes(char const*, dRes_info_c*, int);
    static int deleteRes(char const*, dRes_info_c*, int);
    static void* getRes(char const*, char const*, dRes_info_c*, int);
    static dRes_info_c* getResInfo(char const*, dRes_info_c*, int);
    static dRes_info_c* newResInfo(dRes_info_c*, int);
    static dRes_info_c* getResInfoLoaded(char const*, dRes_info_c*, int);
    static void* getRes(char const*, s32, dRes_info_c*, int);
    static void* getIDRes(char const*, u16, dRes_info_c*, int);
    static int syncAllRes(dRes_info_c*, int);
    BOOL setStageRes(char const*, JKRHeap*);
    void dump();
    int getObjectResName2Index(char const*, char const*);

    BOOL setObjectRes(const char* name, u8 direction, JKRHeap* heap) {
        return setRes(name, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo), "/res/Object/", direction, heap);
    }

    void* getObjectRes(const char* arcName, const char* resName) {
        return getRes(arcName, resName, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    void* getObjectRes(const char* arcName, s32 index) {
        return getRes(arcName, index, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    void* getObjectIDRes(const char* arcName, u16 id) {
        return getIDRes(arcName, id, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    int syncObjectRes(const char* name) {
        return syncRes(name, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    int syncStageRes(const char* name) {
        return syncRes(name, &mStageInfo[0], ARRAY_SIZE(mStageInfo));
    }

    int syncAllObjectRes() { return syncAllRes(&mObjectInfo[0], ARRAY_SIZE(mObjectInfo)); }

    int deleteObjectRes(const char* name) {
        return deleteRes(name, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    int deleteStageRes(const char* name) {
        return deleteRes(name, &mStageInfo[0], ARRAY_SIZE(mStageInfo));
    }

    void* getStageRes(const char* arcName, const char* resName) {
        return getRes(arcName, resName, &mStageInfo[0], ARRAY_SIZE(mStageInfo));
    }

    void* getStageRes(const char* arcName, s32 index) {
        return getRes(arcName, index, &mStageInfo[0], ARRAY_SIZE(mStageInfo));
    }

    dRes_info_c* getObjectResInfo(const char* arcName) {
        return getResInfo(arcName, &mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    }

    dRes_info_c* getStageResInfo(const char* arcName) {
        return getResInfo(arcName, &mStageInfo[0], ARRAY_SIZE(mStageInfo));
    }

    /* 0x0000 */ dRes_info_c mObjectInfo[64];
    /* 0x1200 */ dRes_info_c mStageInfo[64];
};  // Size: 0x1B00

#endif /* D_D_RESORCE_H */
