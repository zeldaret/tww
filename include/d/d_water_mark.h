#ifndef D_WATER_MARK_H
#define D_WATER_MARK_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s_gnd_chk.h"
#include "f_op/f_op_kankyo.h"
#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_kankyo_mng.h"

class JKRSolidHeap;
class J3DModel;

class dWaterMark_c : public kankyo_class {
public:
    inline BOOL draw();
    inline BOOL execute();
    inline BOOL wm_delete();
    BOOL setMatrix();
    inline cPhs_State create();

public:
    
    static s16 m_circle_cnt;
    static s16 m_player_foot_now_id;
    static dBgS_ObjGndChk m_ground_check;
    
    
public:
    /* 0x0F8 */ JKRSolidHeap* mpHeap;
    /* 0x0FC */ J3DModel* mpModel;
    /* 0x100 */ mDoExt_brkAnm mBrkAnm;
    /* 0x118 */ mDoExt_btpAnm mBtpAnm;
    /* 0x12C */ s16 sh1;
    /* 0x12E */ s16 sh2;
    /* 0x130 */ s16 sh3;
    /* 0x132 */ s16 sh4;
    /* 0x134 */ s16 sh5;
};

#endif /* D_WATER_MARK_H */
