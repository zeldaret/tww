#ifndef D_WATER_MARK_H
#define D_WATER_MARK_H

#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
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
    int setMatrix();
    inline cPhs_State create();

public:
    static s16 m_circle_cnt;
    static cBgS_GndChk m_ground_check;
    static s16 m_player_foot_now_id;
    /* 0x0F8 */ JKRSolidHeap* heap;
    /* 0x0FC */ dWaterMark_modelInfo_c mModelInfo;
    /* 0x12C */ short sh1;
    /* 0x12E */ short sh2;
    /* 0x130 */ short sh3;
    /* 0x132 */ short sh4;
    /* 0x134 */ short sh5;
};

#endif /* D_WATER_MARK_H */
