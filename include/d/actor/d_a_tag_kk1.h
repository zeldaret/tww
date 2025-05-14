#ifndef D_A_TAG_KK1_H
#define D_A_TAG_KK1_H

#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"



class daTag_Kk1_c : public fopNpc_npc_c {
public:
    BOOL createInit();
    bool _draw();
    bool _execute();
    bool _delete();
    cPhs_State _create();

public:
    /* 0x6C4 */ u8 field_0x6C4;
    /* 0x6C5 */ bool field_0x6C5;
    /* 0x6C6 */ u8 field_0x6C6;
    /* 0x6C7 */ u8 field_0x6C7;
};  // Size: 0x6C8


class daTag_Kk1_HIO_c : public JORReflexible{


public:

    virtual void foo();
    daTag_Kk1_HIO_c();
    virtual ~daTag_Kk1_HIO_c(){};

public:
    /* 0x4  */ s8 mNo;
    /* 0x8  */ f32 field_0x8;
    /* 0xC  */ f32 field_0xC;
    /* 0x10 */ u8 field_0x10;
};



#endif /* D_A_TAG_KK1_H */
