#ifndef D_WPILLAR_H
#define D_WPILLAR_H

#include "dolphin/types.h"
#include "f_op/f_op_kankyo.h"

class dWpillar_c : public kankyo_class {
public:
    void jointCallBack(int);
    BOOL draw();
    BOOL execute();
    BOOL wp_delete();
    cPhs_State create();

public:
    /* Place member variables here */
};

#endif /* D_WPILLAR_H */
