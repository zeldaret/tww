#ifndef M_DO_M_DO_HOSTIO_H
#define M_DO_M_DO_HOSTIO_H

#include "dolphin/types.h"
#include <string.h>

// move JOR stuff later
class JOREventListener;
class JORPropertyEvent;
class JORNodeEvent;
class JORGenEvent;
class JOREvent;
class JORServer;

#if VERSION == VERSION_DEMO
#define HIO(name) l_HIO.name
#else
#define HIO(name) L_HIO::name
#endif

class JORMContext {
public:
    void genCheckBox(const char* param_1, u8* param_2, u8 param_3, u32 param_4, JOREventListener* param_5, u16 param_6, u16 param_7, u16 param_8, u16 param_9) {
        genCheckBoxSub(0x108, param_1, (u32)param_2, param_4, *param_2, param_3, param_5, param_6, param_7, param_8, param_9);
    }
    void genCheckBoxSub(u32, const char*, u32, u32, u16, u16, JOREventListener*, u16, u16, u16, u16);
};

class JOREventListener {
public:
#ifdef DEBUG
    virtual void listenPropertyEvent(const JORPropertyEvent*) = 0;
#endif
};

class JORReflexible : public JOREventListener {
public:
#ifdef DEBUG
    JORReflexible() {}
    static JORServer* getJORServer();

    virtual void listenPropertyEvent(const JORPropertyEvent*) {}
    virtual void listen(u32, const JOREvent*) {}
    virtual void genObjectInfo(const JORGenEvent*) {}
    virtual void genMessage(JORMContext*) = 0;
    virtual void listenNodeEvent(const JORNodeEvent*) {}
#endif
};

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

class mDoHIO_subRoot_c {
public:
    virtual ~mDoHIO_subRoot_c() {}

    s8 createChild(const char*, JORReflexible*);
    void deleteChild(s8);

    void updateChild(s8) {}

private:
    /* 0x4 */ mDoHIO_child_c mChild[64];
};

class mDoHIO_root_c {
public:
    virtual ~mDoHIO_root_c() {}

    void update();
    
    s8 createChild(const char* name, JORReflexible* hio) {
        return m_subroot.createChild(name, hio);
    }
    void deleteChild(s8 childID) {
        m_subroot.deleteChild(childID);
    }

    /* 0x0 */ mDoHIO_subRoot_c m_subroot;
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
