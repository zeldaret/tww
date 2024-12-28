#ifndef D_S_OPEN
#define D_S_OPEN

#include "JSystem/J2DGraph/J2DPane.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "f_op/f_op_scene.h"

class J2DScreen;
class J2DTextBox;

class dScnOpen_message_c {
public:
    dScnOpen_message_c(JKRExpHeap*);
    virtual ~dScnOpen_message_c();
    inline void set_pane_pointer(J2DPane* tx1, J2DPane* tx2);
    void set_message(u32, int);
    void exec();

public:
    /* 0x0004 */ char msg1[0x800];
    /* 0x0804 */ char msg2[0x800];
    /* 0x1004 */ char msg3[0x800];
    /* 0x1804 */ char msg4[0x800];
    /* 0x2004 */ fopMsgM_msgDataProc_c mMsgDataProc;
    /* 0x22A4 */ u8 field_0x22a4[0x22bc - 0x22a4];
    /* 0x22BC */ u8 field_0x22bc;
    /* 0x22BD */ u8 field_0x22bd;
    /* 0x22BE */ u8 field_0x22be;
    /* 0x22BF */ u8 field_0x22bf;
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
    /* 0x010 */ J2DPane* pane2d[11];
    /* 0x03C */ fopMsgM_pane_class pane[11];
    /* 0x2A4 */ f32 mPosX;
    /* 0x2A8 */ f32 mAlpha;
    /* 0x2AC */ s32 mTimer;
    /* 0x2B0 */ s32 mState;
    /* 0x2B4 */ f32 mScale;
    /* 0x2B8 */ u8 pad2[0x010];
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
