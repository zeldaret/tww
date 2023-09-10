#ifndef M_DO_M_DO_HOSTIO_H
#define M_DO_M_DO_HOSTIO_H

#include "dolphin/types.h"

struct JORReflexible;

class mDoHIO_child_c {
public:
    char mName[24];
    u8 field1_0x18;
    u8 field2_0x19;
    u8 field3_0x1a;
    u8 field4_0x1b;
    JORReflexible* mReflexible;
};

class mDoHIO_subRoot_c {
public:
    virtual ~mDoHIO_subRoot_c() {}

private:
    mDoHIO_child_c mChild[64];
};

class mDoHIO_root_c : public mDoHIO_subRoot_c {
public:
    virtual ~mDoHIO_root_c() {}

    void update();
};

class mDoHIO_entry_c {
public:
    virtual ~mDoHIO_entry_c() {}
};

extern mDoHIO_root_c mDoHIO_root;

#endif /* M_DO_M_DO_HOSTIO_H */
