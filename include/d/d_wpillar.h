#ifndef D_WPILLAR_H
#define D_WPILLAR_H

#include "dolphin/types.h"

class dWpillar_c {
public:
    void jointCallBack(int);
    void draw();
    void execute();
    void wp_delete();
    void create();
};

#endif /* D_WPILLAR_H */
