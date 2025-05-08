
#ifndef D_PLACE_NAME_H
#define D_PLACE_NAME_H

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"

class J2DScreen;
class mDoDvdThd_toMainRam_c;

class dPlace_name_c : public dDlst_base_c {
public:
    virtual ~dPlace_name_c() {}
    void setScreen(const char*, JKRArchive*);
    BOOL _openAnime();
    BOOL _closeAnime();
    virtual void draw();

    void addCounter() {}
    void decCounter() {}
    void getCounter() {}
    void changeTexture(const ResTIMG*) {}
    void deleteScreen() {}

public:
    /* 0x04 */ J2DScreen * scrn;
    /* 0x08 */ fopMsgM_pane_class pane;
};

class dPn_c : public msg_class {
public:
    cPhs_State _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();

public:
    /* 0x0FC */ JKRExpHeap * mpHeap;
    /* 0x100 */ request_of_phase_process_class mPhs;
    /* 0x108 */ dPlace_name_c * dPn_scrn;
    /* 0x11C */ mDoDvdThd_toMainRam_c * dvd;
    /* 0x114 */ ResTIMG * mpTIMG;
    /* 0x118 */ u8 mState;
    /* 0x119 */ u8 pad[3];
};

#endif /* D_PLACE_NAME_H */
