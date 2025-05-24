#ifndef DYNAMICLINK_H
#define DYNAMICLINK_H

#include "dolphin/os/OS.h"

class JKRArchive;
class JKRFileCache;
class mDoDvdThd_callback_c;

struct DynamicModuleControlBase {
    /* 0x00 */ u16 mLinkCount;
    /* 0x02 */ u16 mDoLinkCount;
    /* 0x04 */ DynamicModuleControlBase* mPrev;
    /* 0x08 */ DynamicModuleControlBase* mNext;

    /* 0x0C */ /*vtable*/
    virtual ~DynamicModuleControlBase();
    virtual const char* getModuleName() const { return NULL; }
    virtual int getModuleSize() const { return 0; }
    virtual const char* getModuleTypeString() const { return "Base"; }
#if VERSION == VERSION_DEMO
    static void dump();
#else
#if __MWERKS__ && __MWERKS__ < 0x4200
    // This is illegal function overloading, but MWCC for GC allows it. MWCC for Wii does not.
    virtual void dump();
#endif
    static void dump();
    virtual void dump2() {}
#endif
    virtual bool do_load() { return true; }
    virtual BOOL do_load_async() { return TRUE; }
    virtual bool do_unload() { return true; }
    virtual BOOL do_link() { return TRUE; }
    virtual bool do_unlink() { return true; }
    DynamicModuleControlBase();
    BOOL link();
    BOOL unlink();
    BOOL load_async();
    bool force_unlink();

    static inline DynamicModuleControlBase* getFirstClass() { return mFirst; }
    inline DynamicModuleControlBase* getNextClass() { return mNext; }
    bool isLinked() const { return mLinkCount != 0; }

    static DynamicModuleControlBase* mFirst;
    static DynamicModuleControlBase* mLast;
};

struct DynamicModuleControl : DynamicModuleControlBase {
    virtual ~DynamicModuleControl() {}
    virtual const char* getModuleName() const { return mName; }
    virtual int getModuleSize() const;
    virtual const char* getModuleTypeString() const;
#if VERSION != VERSION_DEMO
    virtual void dump2();
#endif
    virtual bool do_load();
    virtual BOOL do_load_async();
    virtual bool do_unload();
    virtual BOOL do_link();
    virtual bool do_unlink();
    DynamicModuleControl(char const*);
    static JKRArchive* mountCallback(void*);
    static void mountCreate();
    static bool initialize();
    static bool callback(void*);

    /* 0x10 */ OSModuleHeader* mModule;
    /* 0x14 */ void* mBss;
    /* 0x18 */ u32 unk_24;
    /* 0x1c */ const char* mName;
    /* 0x20 */ u8 mResourceType;
    /* 0x21 */ u8 unk_33;
    /* 0x22 */ u16 mChecksum;
#if VERSION != VERSION_DEMO
    /* 0x24 */ s32 mSize;
#endif
    /* 0x28 */ mDoDvdThd_callback_c* mAsyncLoadCallback;

    static u32 sAllocBytes;
    static JKRArchive* sArchive;
    static JKRFileCache* sFileCache;
};  // Size: 0x2C

#endif /* DYNAMICLINK_H */
