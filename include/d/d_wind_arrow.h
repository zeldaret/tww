#ifndef D_WIND_ARROW_H
#define D_WIND_ARROW_H

#include "dolphin/types.h"
#include "f_op/f_op_kankyo.h"
#include "m_Do/m_Do_ext.h"

class JKRSolidHeap;
class J3DModel;

class dWindArrow_modelInfo_c {
public:
    /* 0x0FC */ J3DModel* mpModel;
    /* 0x100 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x108 */ mDoExt_btkAnm mBtkAnm;
};

class dWindArrow_c : public kankyo_class {
public:
    inline ~dWindArrow_c();
    inline cPhs_State create();
    inline BOOL execute();
    BOOL createHeap();
    void adjustHeap();
    inline BOOL draw();

public:
    /* 0x0F8 */ JKRSolidHeap* heap;
    /* 0x0FC */ dWindArrow_modelInfo_c mModelInfo;
};

#endif /* D_WIND_ARROW_H */
