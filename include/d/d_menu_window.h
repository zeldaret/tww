#ifndef D_MENU_WINDOW_H
#define D_MENU_WINDOW_H

#include "dolphin/types.h"

class JKRExpHeap;

class sub_ms_screen_class {
public:
    u8 field_0x00[0xFC - 0x00];
    JKRHeap* parentHeap_0xfc;
    JKRHeap* childHeap;
    u8 field_0x104[0x1B6 - 0x104];
    u8 mButtonsPressed;
};

class dMw_HIO_c {
public:
    dMw_HIO_c();
};

class dMw_DHIO_c {
public:
    dMw_DHIO_c();
};

#endif /* D_MENU_WINDOW_H */
