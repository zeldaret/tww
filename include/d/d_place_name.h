
#ifndef D_PLACE_NAME_H
#define D_PLACE_NAME_H

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"

class J2DScreen;

class dPlace_name_c : public dDlst_base_c {
public:
    virtual ~dPlace_name_c() {}
    void setScreen(const char*, JKRArchive*);
    BOOL _openAnime();
    BOOL _closeAnime();
    virtual void draw();

public:
    /* 0x04 */ J2DScreen * scrn;
    /* 0x08 */ fopMsgM_pane_class pane;
};

#endif /* D_PLACE_NAME_H */
