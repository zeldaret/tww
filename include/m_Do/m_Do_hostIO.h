#ifndef M_DO_M_DO_HOSTIO_H
#define M_DO_M_DO_HOSTIO_H

#include "JSystem/JHostIO/JORReflexible.h"
#include "dolphin/types.h"
#include <string.h>

#if VERSION == VERSION_DEMO
#define HIO(name) l_HIO.name
#else
#define HIO(name) L_HIO::name
#endif

class mDoHIO_child_c {
public:
    mDoHIO_child_c() {
        field_0x18 = 0;
        mPt = NULL;
    }
    ~mDoHIO_child_c() {}

    const char* getName() { return mName; }
    void setName(const char* i_name) { strncpy(mName, i_name, sizeof(mName)); }
    JORReflexible* getPt() { return mPt; }
    void setPt(JORReflexible* i_pt) { mPt = i_pt; }

    /* 0x00 */ char mName[24];
    /* 0x18 */ u8 field_0x18;
    /* 0x1C */ JORReflexible* mPt;
};

class mDoHIO_subRoot_c : public JORReflexible {
public:
    virtual ~mDoHIO_subRoot_c() {}

    void updateChild(s8);
    void deleteChild(s8);
    s8 createChild(const char*, JORReflexible*);

    void genMessage(JORMContext*);

private:
    /* 0x4 */ mDoHIO_child_c mChildren[64];
};

class mDoHIO_root_c : public JORReflexible {
public:
    mDoHIO_root_c() {}
    virtual ~mDoHIO_root_c() {}

    void update();
    void updateChild(s8);
    void deleteChild(s8 childID) {
        mSub.deleteChild(childID);
    }
    s8 createChild(const char* name, JORReflexible* hio) {
        return mSub.createChild(name, hio);
    }
    void genMessage(JORMContext*);

    /* 0x0 */ mDoHIO_subRoot_c mSub;
};

class mDoHIO_entry_c : public JORReflexible {
public:
#if VERSION == VERSION_DEMO
    /* 0x00 */ s8 mNo;
    /* 0x01 */ u8 mCount;
    /* 0x04 */ /* vtable */

    mDoHIO_entry_c();
    virtual ~mDoHIO_entry_c();
    void entryHIO(const char*);
    void removeHIO();
#else
    virtual ~mDoHIO_entry_c() {}
#endif
};

extern mDoHIO_root_c mDoHIO_root;

inline s8 mDoHIO_createChild(const char* name, JORReflexible* hio) {
    return mDoHIO_root.createChild(name, hio);
}

inline void mDoHIO_deleteChild(s8 childID) {
    mDoHIO_root.deleteChild(childID);
}

#endif /* M_DO_M_DO_HOSTIO_H */
