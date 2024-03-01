#ifndef D_WATER_MARK_H
#define D_WATER_MARK_H

#include "dolphin/types.h"

class dWaterMark_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    inline BOOL wm_delete();
    void setMatrix();
    void create();
};

#endif /* D_WATER_MARK_H */
