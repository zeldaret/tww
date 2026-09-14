#ifndef D_MESSAGE_PAPER_H
#define D_MESSAGE_PAPER_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"

#if VERSION < VERSION_PAL
struct sub_msg3_class : public msg_class {
    /* 0x0FC */ u8 m0FC[0xEE8 - 0x0FC];
};

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
#endif

#if VERSION == VERSION_PAL
struct dMessage_Paper_c : public msg_class {
    /* 0x0FC */ u8 m0FC[0x104 - 0x0FC];
};
#endif

#endif /* D_MESSAGE_PAPER_H */
