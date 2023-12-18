
#ifndef D_MSG_H
#define D_MSG_H

#include "d/d_drawlist.h"

class msg_class;
class sub_msg_class;

class dDlst_2DMSG_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMSG_c();
    virtual void draw();
    void outFontDraw();

    msg_class* field_0x4;
};

class dDlst_2Dtact_c : public dDlst_base_c {
public:
    virtual ~dDlst_2Dtact_c();
    virtual void draw();

    u8 field_0x4[4];
    void* field_0x8;
};

extern JKRHeap* dMsg_getAgbWorkArea();

#endif /* D_MSG_H */
