#ifndef D_WPILLAR_H
#define D_WPILLAR_H

#include "f_op/f_op_kankyo.h"
#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_kankyo_mng.h"

class dWpillar_c : public kankyo_class {
public:
    int jointCallBack(int);
    BOOL draw();
    BOOL execute();
    BOOL wp_delete();
    cPhs_State create();

public:
    /* 0x0F8 */ J3DModel* mpModel;
    /* 0x0FC */ mDoExt_bckAnm mBck;
    /* 0x10C */ mDoExt_btkAnm mBtk;
    /* 0x120 */ JKRSolidHeap* mpHeap;
    /* 0x124 */ dKy_tevstr_c mTevstr;
    /* 0x1D4 */ f32 mHeight;
};

#endif /* D_WPILLAR_H */
