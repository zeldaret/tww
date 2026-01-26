#ifndef D_KY_THUNDER_H
#define D_KY_THUNDER_H

#include "f_op/f_op_kankyo.h"
#include "m_Do/m_Do_ext.h"

class dThunder_modelInfo_c {
public:
    // Offsets are relative to dThunder_c instead of dThunder_modelInfo_c
    /* 0x0FC */ J3DModel * mpModel;
    /* 0x100 */ mDoExt_invisibleModel mInvisModel;
    /* 0x108 */ mDoExt_btkAnm mBtk;
    /* 0x11C */ mDoExt_brkAnm mBrk;
};

class dThunder_c : public kankyo_class {
public:
    inline ~dThunder_c();
    BOOL createHeap();
    void adjustHeap();
    cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* 0x0F8 */ JKRSolidHeap * solid_heap;
    /* 0x0FC */ dThunder_modelInfo_c mModelInfo;
#if VERSION == VERSION_DEMO
    /* 0x134 */ cXyz mPos;
    /* 0x140 */ f32 mBtkTime;
    /* 0x144 */ cXyz mScale;
    /* 0x150 */ f32 mRot;
#else
    /* 0x134 */ cXyz mScale;
    /* 0x140 */ cXyz mPos;
    /* 0x14C */ cXyz mPosNeg;
    /* 0x158 */ f32 mRot;
    /* 0x15C */ f32 mBtkTime;
#endif
};

#endif /* D_KY_THUNDER_H */
