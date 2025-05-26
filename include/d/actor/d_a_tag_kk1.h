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
    /* 0x6C4 */ u8   padding_0x6C4;
    /* 0x6C5 */ bool mTagSet;
    /* 0x6C6 */ bool mNameIsWrong;
};  // Size: 0x6C8


class daTag_Kk1_HIO_c : public JORReflexible{

    public:
        daTag_Kk1_HIO_c();
        virtual ~daTag_Kk1_HIO_c(){};

    public:
        struct hio_prm_c {
        /* 0x08  */    f32 mHorizontalDistance;
        /* 0x0C  */    f32 mVerticalDistance;
        /* 0x10  */    u8  field_0x10;
        };

        /* 0x04  */ s8  mNo;
        /* 0x08  */ hio_prm_c prm;
};

#endif /* D_A_TAG_KK1_H */
