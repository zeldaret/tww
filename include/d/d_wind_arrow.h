#ifndef D_WIND_ARROW_H
#define D_WIND_ARROW_H

#include "dolphin/types.h"

class dWindArrow_c {
public:
    inline s32 create();
    inline BOOL execute();
    BOOL createHeap();
    void adjustHeap();
    BOOL draw();
};

#endif /* D_WIND_ARROW_H */
