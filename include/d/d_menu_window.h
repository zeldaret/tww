#ifndef D_MENU_WINDOW_H
#define D_MENU_WINDOW_H

#include "dolphin/types.h"

class dMCloth_c;
class JKRExpHeap;
class dMenu_FmapSv_c;

enum dMw_Status {
    MENU_STATE_NO_MENU = 0,

    // Item Screen
    MENU_STATE_ITEM_OPEN = 1,
    MENU_STATE_ITEM_OPEN_FROM_COLLECT_LEFT = 2,
    MENU_STATE_ITEM_OPEN_FROM_COLLECT_RIGHT = 3,
    MENU_STATE_ITEM_MOVE = 4,
    MENU_STATE_ITEM_CLOSE = 5,
    MENU_STATE_ITEM_TO_COLLECT_LEFT = 6,
    MENU_STATE_ITEM_TO_COLLECT_RIGHT = 7,

    // Collect Screen
    MENU_STATE_COLLECT_OPEN = 8,
    MENU_STATE_COLLECT_OPEN_LEFT = 9,
    MENU_STATE_COLLECT_OPEN_RIGHT = 10,
    MENU_STATE_COLLECT_OPEN_TACT = 11,
    MENU_STATE_COLLECT_OPEN_ALT = 12,
    MENU_STATE_COLLECT_MOVE = 13,
    MENU_STATE_COLLECT_MOVE_TACT = 14,
    MENU_STATE_COLLECT_MOVE_ALT = 15,
    MENU_STATE_COLLECT_CLOSE = 16,
    MENU_STATE_COLLECT_TO_ITEM_LEFT = 17,
    MENU_STATE_COLLECT_TO_ITEM_RIGHT = 18,
    MENU_STATE_COLLECT_CLOSE_TACT = 19,
    MENU_STATE_COLLECT_CLOSE_ALT = 20,

    // Field Map Screen
    MENU_STATE_FMAP_OPEN = 21,
    MENU_STATE_FMAP_OPEN_WARP_MODE = 22,
    MENU_STATE_FMAP_OPEN_WALLPAPER = 23,
    MENU_STATE_FMAP_OPEN_FISHMAN_MODE = 24,
    MENU_STATE_FMAP_MOVE = 25,
    MENU_STATE_FMAP_MOVE_WARP_MODE = 26,
    MENU_STATE_FMAP_MOVE_WALLPAPER = 27,
    MENU_STATE_FMAP_MOVE_FISHMAN_MODE = 28,
    MENU_STATE_FMAP_CLOSE = 29,

    // Dungeon Map Screen
    MENU_STATE_DMAP_OPEN = 30,
    MENU_STATE_DMAP_MOVE = 31,
    MENU_STATE_DMAP_CLOSE = 32,

    // Name Entry Screen
    MENU_STATE_NAME_OPEN = 33,
    MENU_STATE_NAME_MOVE = 34,
    MENU_STATE_NAME_CLOSE = 35,

    // Save Screen
    MENU_STATE_SAVE_OPEN = 36,
    MENU_STATE_SAVE_MOVE = 37,
    MENU_STATE_SAVE_CLOSE = 38,
};

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
    /* 0x01B3 */ u8 field_0x1B3[0x1B5 - 0x1B3];
    /* 0x01B5 */ u8 mMenuProc; // dMw_Status
    /* 0x01B6 */ u8 mButtonsPressed;
};

class dMw_HIO_c : public JORReflexible {
public:
    dMw_HIO_c();
    virtual ~dMw_HIO_c() {}

    /* 0x04 */ s8 mNo;
    /* 0x06 */ u16 field_0x06;
    /* 0x08 */ u16 field_0x08;
    /* 0x0A */ u8 field_0x0A;
    /* 0x0B */ u8 field_0x0B;
    /* 0x0C */ u16 field_0x0C;
    /* 0x0E */ u16 field_0x0E;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 field_0x1A;
    /* 0x1C */ u8 field_0x1C;
    /* 0x1D */ u8 field_0x1D;
    /* 0x1E */ u8 field_0x1E;
    /* 0x1F */ u8 field_0x1F;
    /* 0x20 */ u8 arr_0x20[21];
    /* 0x35 */ u8 padding_0x35[0x38 - 0x35];
    /* 0x38 */ u8 arr_0x38[21];
    /* 0x4D */ u8 padding_0x4D[0x50 - 0x4D];
    /* 0x50 */ u8 arr_0x50[8];
    /* 0x58 */ u8 arr_0x58[8];
    /* 0x60 */ u8 arr_0x60[8];
    /* 0x68 */ u8 arr_0x68[8];
    /* 0x70 */ u8 arr_0x70[8];
    /* 0x78 */ u8 arr_0x78[8];
    /* 0x80 */ u8 field_0x80;
    /* 0x81 */ u8 field_0x81;
    /* 0x82 */ u8 field_0x82;
    /* 0x83 */ u8 arr_0x83[8];
    /* 0x8B */ u8 arr_0x8B[8];
    /* 0x93 */ u8 field_0x93;
    /* 0x94 */ u8 field_0x94;
    /* 0x95 */ u8 field_0x95;
    /* 0x96 */ u8 field_0x96;
    /* 0x97 */ u8 field_0x97;
    /* 0x98 */ u8 field_0x98;
    /* 0x99 */ u8 field_0x99;
    /* 0x9A */ u8 field_0x9A;
    /* 0x9B */ u8 field_0x9B;
    /* 0x9C */ u8 field_0x9C;
    /* 0x9D */ u8 field_0x9D;
    /* 0x9E */ u8 arr_0x9E[8];
    /* 0xA6 */ u8 arr_0xA6[8];
    /* 0xAE */ u8 padding_0xAE[0xB6 - 0xAE];
    /* 0xB6 */ u8 arr_0xB6[6];
    /* 0xBC */ u8 arr_0xBC[6];
    /* 0xC2 */ u8 arr_0xC2[8];
    /* 0xCA */ u8 arr_0xCA[8];
    /* 0xD2 */ u8 arr_0xD2[3];
    /* 0xD5 */ u8 arr_0xD5[3];
    /* 0xD8 */ u8 arr_0xD8[8];
    /* 0xE0 */ u8 arr_0xE0[8];
};

class dMw_DHIO_c : public JORReflexible {
public:
    dMw_DHIO_c();
    virtual ~dMw_DHIO_c() {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 arr_0x05[0xC][0x10];
};

extern dMenu_FmapSv_c dMv_CIO_c;
extern dMw_HIO_c g_mwHIO;
extern dMw_DHIO_c g_mwDHIO;

extern dMCloth_c* cloth_c;

#endif /* D_MENU_WINDOW_H */
