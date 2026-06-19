#ifndef D_WATER_MARK_H
#define D_WATER_MARK_H

#include "SSystem/SComponent/c_phase.h"
#include "dolphin/types.h"
#include "f_op/f_op_kankyo.h"

class dWaterMark_c : public kankyo_class {
public:
    inline BOOL draw();
    inline BOOL execute();
    inline BOOL wm_delete();
    void setMatrix();
    inline cPhs_State create();

public:
    /* Place member variables here */
};

#endif /* D_WATER_MARK_H */
