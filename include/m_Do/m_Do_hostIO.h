#ifndef M_DO_M_DO_HOSTIO_H
#define M_DO_M_DO_HOSTIO_H

#include "dolphin/types.h"

// move JOR stuff later
class JOREventListener {
public:

};

class JORReflexible : public JOREventListener {
public:
#ifdef DEBUG
    virtual ~JORReflexible() {}
#endif
};

class mDoHIO_child_c {
public:
    mDoHIO_child_c() {
        field_0x18 = 0;
        mReflexible = NULL;
    }

    ~mDoHIO_child_c() {}

    /* 0x00 */ char mName[24];
    /* 0x18 */ u8 field_0x18;
    /* 0x1C */ JORReflexible* mReflexible;
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
    
    s8 mDoHIO_createChild(const char* name, JORReflexible* hio) {
        return m_subroot.createChild(name, hio);
    }
    void mDoHIO_deleteChild(s8 childID) {
        m_subroot.deleteChild(childID);
    }

    /* 0x0 */ mDoHIO_subRoot_c m_subroot;
};

class mDoHIO_entry_c : public JORReflexible {
public:
    virtual ~mDoHIO_entry_c() {}
};

extern mDoHIO_root_c mDoHIO_root;

#endif /* M_DO_M_DO_HOSTIO_H */
