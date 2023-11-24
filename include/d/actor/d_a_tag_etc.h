#ifndef D_A_TAG_ETC_H
#define D_A_TAG_ETC_H

#include "f_op/f_op_actor.h"

class daTag_Etc_c : public fopAc_ac_c {
public:
    void draw() {}
    void execute() {}
    void setActio(unsigned char) {}

    void getEventNo();
    void getType2();
    void rangeCheck(fopAc_ac_c*);
    void otherCheck(fopAc_ac_c*);
    void demoProc();
    void demoInitProc();
    void create();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_ETC_H */
