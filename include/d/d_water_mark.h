#ifndef D_WATER_MARK_H
#define D_WATER_MARK_H

#include "SSystem/SComponent/c_phase.h"
#include "dolphin/types.h"
#include "f_op/f_op_kankyo.h"
#include "m_Do/m_Do_ext.h"

class JKRSolidHeap;
class J3DModel;

class dWaterMark_modelInfo_c {
public:
    /* 0x0FC */ J3DModel* mpModel;
    /* 0x100 */ mDoExt_brkAnm mBrkAnm;
    /* 0x118 */ mDoExt_btpAnm mBtpAnm;
};


class dWaterMark_c : public kankyo_class {
public:
    inline BOOL draw();
    inline BOOL execute();
    inline BOOL wm_delete();
    void setMatrix();
    inline cPhs_State create();

public:
    /* 0x0F8 */ JKRSolidHeap* heap;
    /* 0x0FC */ dWaterMark_modelInfo_c mModelInfo;
    static s16 m_circle_cnt;
};

#endif /* D_WATER_MARK_H */
