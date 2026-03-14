#ifndef D_MENU_WINDOW_H
#define D_MENU_WINDOW_H

#include "dolphin/types.h"

class JKRExpHeap;

class sub_ms_screen_class : public msg_class {
public:
    /* 0x00FC */ JKRHeap* parentHeap_0xfc;
    /* 0x0100 */ JKRHeap* childHeap;
    /* 0x0104 */ JKRArchive* arc;
    /* 0x0108 */ fpc_ProcID mMsgID;
    /* 0x010C */ char* name[2];
    /* 0x0114 */ char* note[2];
    /* 0x011C */ char* dummy[2];
    /* 0x0124 */ u8 field_0x124[0x128 - 0x124];
    /* 0x0128 */ void* buffer_p[33];
    /* 0x01AC */ u8 field_0x1AC[0x1B0 - 0x1AC];
    /* 0x01B0 */ u16 field_0x1B0;
    /* 0x01B2 */ u8 field_0x1B2;
    /* 0x01B3 */ u8 field_0x1B3[0x1B6 - 0x1B3];
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
