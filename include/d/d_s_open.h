#ifndef D_S_OPEN
#define D_S_OPEN

#include "d/d_drawlist.h"
#include "f_op/f_op_scene.h"

class J2DScreen;


class dScnOpen_message_c {
public:
    dScnOpen_message_c(JKRExpHeap*);
    virtual ~dScnOpen_message_c();
    void set_message(u32, int);
    void exec();
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
    /* 0x010 */ u8 pad[0x2a0];
    /* 0x2B0 */ s32 field_0x2b0;
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
