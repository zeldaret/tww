#ifndef D_MESSAGE_H
#define D_MESSAGE_H

#include "dolphin/types.h"

class sub_msg2_class;

class dDlst_2DMSG2_c {
public:
    void setActorP(sub_msg2_class*) {}
    
    void draw();
    void outFontDraw();
};

class dDlst_2DCopy_c {
public:
    void draw();
};

#endif /* D_MESSAGE_H */
