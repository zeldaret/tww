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
    struct info2_s {
        u8 field_0x0[0x24 - 0x00];
        u8* field_0x24;
    };

    struct info1_s {
        u8 field_0x0;
        info2_s* field_0x4;
    };

    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ mDoDvdThd_toMainRam_c* command;
    /* 0x1D0 */ mDoDvdThd_toMainRam_c* fontCommand;
    /* 0x1D4 */ info1_s* info;
    /* 0x1D8 */ ResFONT* field_0x1d8;
    /* 0x1DC */ myFontClass* field_0x1dc;
    /* 0x1E0 */ u8 field_0x1e0;
    /* 0x1E1 */ u8 field_0x1e1;
    /* 0x1E2 */ u8 field_0x1e2;
};

#endif /* D_S_MENU */
