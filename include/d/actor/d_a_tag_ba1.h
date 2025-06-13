#ifndef D_A_TAG_BA1_H
#define D_A_TAG_BA1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daTag_Ba1_c : public fopAc_ac_c {
public:
    BOOL XyCheck_cB(int i_itemBtn);
    int XyEvent_cB(int);
    BOOL createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* 0x290 */ s16 field_0x290;
    /* 0x292 */ s16 field_0x292;
};  // Size: 0x294

class daTag_Ba1_HIO_c : public JORReflexible {
    struct hio_prm_c {
        u8 field_0x00;
        //Size: 0x01
    };
public:
    daTag_Ba1_HIO_c();
    virtual ~daTag_Ba1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x05;
    /* 0x06 */ s8 field_0x06;
    /* 0x07 */ s8 field_0x07;
    /* 0x08 */ int mRefCount;
    /* 0x0C */ int field_0x0C;
    //Size: 0x10
};

#endif /* D_A_TAG_BA1_H */
