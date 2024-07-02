#ifndef D_S_MENU
#define D_S_MENU

#include "JSystem/JUtility/JUTResFont.h"
#include "f_op/f_op_scene.h"

class mDoDvdThd_toMainRam_c;

class myFontClass : public JUTResFont {
public:
    myFontClass(const ResFONT* pFont, JKRHeap* pHeap) : JUTResFont(pFont, pHeap) {}
    ~myFontClass();
    f32 drawChar_scale(f32, f32, f32, f32, int, bool);
};

class menu_of_scene_class : public scene_class {
public:
    struct room_inf {
        char name[0x20];
        u8 field_0x20;
        char stageName[0x08];
        s8 roomNo;
        u8 startCode;
        s8 layerNo;
    };

    struct stage_inf {
        char name[0x20];
        u8 field_0x20;
        u8 roomNum;
        u8 field_0x22;
        u8 field_0x23;
        room_inf* roomPtr;
    };

    struct menu_inf {
        u8 num;
        stage_inf* stage;
    };

    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ mDoDvdThd_toMainRam_c* command;
    /* 0x1D0 */ mDoDvdThd_toMainRam_c* fontCommand;
    /* 0x1D4 */ menu_inf* info;
    /* 0x1D8 */ ResFONT* fontRes;
    /* 0x1DC */ myFontClass* font;
    /* 0x1E0 */ u8 startCode;
    /* 0x1E1 */ u8 field_0x1e1;
    /* 0x1E2 */ u8 field_0x1e2;
};

#endif /* D_S_MENU */
