#ifndef D_MESSAGE_PAPER_H
#define D_MESSAGE_PAPER_H

#include "dolphin/types.h"

class sub_msg3_class;

class dmsg3_3d_c {
public:
    dmsg3_3d_c();
    ~dmsg3_3d_c();
    void setDummyTexture();
    void set_mtx();
    void exec();
    void draw();
};

class dDlst_2DMSG3_c {
public:
    void setActorP(sub_msg3_class*) {}
    
    void draw();
    void outFontDraw();
};

#endif /* D_MESSAGE_PAPER_H */
