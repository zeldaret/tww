#ifndef D_S_OPEN
#define D_S_OPEN

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "f_op/f_op_scene.h"

class J2DScreen;
class J2DTextBox;

class dScnOpen_message_c {
public:
    dScnOpen_message_c(JKRExpHeap*);
    virtual ~dScnOpen_message_c();
    void set_message(u32, int);
    void exec();

public:
    /* 0x0000 */ u8 field_0x00[0x2000];
    /* 0x2004 */ fopMsgM_msgDataProc_c mMsgDataProc;
    /* 0x22A4 */ u8 field_0x22a4[0x22c0 - 0x22a4];
    /* 0x22C0 */ u32 field_0x22c0;
    /* 0x22C4 */ J2DTextBox* field_0x22c4;
    /* 0x22C8 */ J2DTextBox* field_0x22c8;
    /* 0x22CC */ JUTFont* tFont;
    /* 0x22D0 */ JUTFont* rFont;
    /* 0x22D4 */ JKRExpHeap* exp_heap;
    /* 0x22D8 */ f32 field_0x22d8;
    /* 0x22DC */ u32 field_0x22dc;
    /* 0x22E0 */ u32 field_0x22e0;
    /* 0x22E4 */ u32 field_0x22e4;
    /* 0x22E8 */ u8 field_0x22e8;
    /* 0x22EC */ u32 field_0x22ec;
    /* 0x22F0 */ u32 field_0x22f0;
};

class dScnOpen_proc_c : public dDlst_base_c {
public:
    dScnOpen_proc_c();
    virtual ~dScnOpen_proc_c();
    void proc_execute();
    void proc_draw();
    virtual void draw();

    /* 0x004 */ JKRExpHeap* exp_heap;
    /* 0x008 */ dScnOpen_message_c* m_message;
    /* 0x00C */ J2DScreen* m_Screen;
    /* 0x010 */ J2DPane* d1;
    /* 0x014 */ J2DPane* d2;
    /* 0x018 */ J2DPane* d3;
    /* 0x01C */ J2DPane* d4;
    /* 0x020 */ J2DPane* d42;
    /* 0x024 */ J2DPane* d5;
    /* 0x028 */ J2DPane* d6;
    /* 0x02C */ J2DPane* mak1;
    /* 0x030 */ J2DPane* mak2;
    /* 0x034 */ J2DTextBox* tx1;
    /* 0x038 */ J2DTextBox* tx2;
    /* 0x03C */ fopMsgM_pane_class pane[11];
    /* 0x2A4 */ f32 mPosX;
    /* 0x2A8 */ f32 mAlpha;
    /* 0x2AC */ s32 mTimer;
    /* 0x2B0 */ s32 mState;
    /* 0x2B4 */ f32 mScale;
    /* 0x010 */ u8 pad2[0x014];
};

class dScnOpen_c : public scene_class {
public:
    ~dScnOpen_c();
    void changeGameScene();
    s32 create();
    BOOL draw();
    BOOL execute();

    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ JKRSolidHeap* solid_heap;
    /* 0x1D0 */ dScnOpen_proc_c* mpProc;
    /* 0x1D4 */ u8 field_0x1d4;
};

#endif /* D_S_OPEN */
