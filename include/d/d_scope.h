#ifndef D_SCOPE_H
#define D_SCOPE_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"

class sub_scp_class : public msg_class {
public:
    /* Place member variables here */
};

class dDlst_2DSCP_c {
public:
    void setActorP(sub_scp_class*) {}
    
    void draw();
    void outFontDraw();
};

#endif /* D_SCOPE_H */
