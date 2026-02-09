#ifndef D_MENU_WINDOW_H
#define D_MENU_WINDOW_H

#include "dolphin/types.h"

class JKRExpHeap;

class sub_ms_screen_class : public msg_class {
public:
    /* 0x00FC */ JKRHeap* parentHeap_0xfc;
    /* 0x0100 */ JKRHeap* childHeap;
    /* 0x0104 */ u8 field_0x104[0x108 - 0x104];
    /* 0x0108 */ s32 field_0x108;
    /* 0x010C */ u8 field_0x10C[0x1B0 - 0x10C];
    /* 0x01B0 */ s16 field_0x1B0;
    /* 0x01B2 */ u8 field_0x1B2[0x1B6 - 0x1B2];
    /* 0x01B6 */ u8 mButtonsPressed;
};

class dMw_HIO_c : public JORReflexible {
public:
    dMw_HIO_c();
    virtual ~dMw_HIO_c() {}

    /* 0x0004*/ s8 mNo;
};

class dMw_DHIO_c : public JORReflexible {
public:
    dMw_DHIO_c();
    virtual ~dMw_DHIO_c() {}

    /* 0x0004*/ s8 mNo;
};

extern dMw_HIO_c g_mwHIO;
extern dMw_DHIO_c g_mwDHIO;

#endif /* D_MENU_WINDOW_H */
