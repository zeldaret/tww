#ifndef D_A_BRIDGE_H
#define D_A_BRIDGE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class bridge_class : public fopAc_ac_c {
public:
    /* 0x0290 */ request_of_phase_process_class mPhsBridge;
    /* 0x0298 */ s16 mMoveProcMode;
    /* 0x029A */ u8 m029A[0x029C - 0x029A];
    /* 0x029C */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x02D8 */ u8 mTypeBits;
    /* 0x02D9 */ u8 mUnk_2;
    /* 0x02DA */ u8 mPathId;
    /* 0x02DB */ u8 mPathIdP;
    /* 0x02DC */ s8 mBrCount;
    /* 0x02DD */ u8 m02DD;
    /* 0x02DE */ u8 m02DE[0x02E0 - 0x02DE];
    /* 0x02E0 */ f32 m02E0;
    /* 0x02E4 */ f32 m02E4;
    /* 0x02E8 */ dBgWSv* mpBgW;
    /* 0x02EC */ s16 m02EC;
    /* 0x02EE */ s16 m02EE;
    /* 0x02F0 */ s16 m02F0;
    /* 0x02F2 */ s16 m02F2;
    /* 0x02F4 */ f32 m02F4;
    /* 0x02F8 */ f32 m02F8;
    /* 0x02FC */ u8 m02FC[0x0300 - 0x02FC];
    /* 0x0300 */ s16 m0300;
    /* 0x0302 */ s16 m0302;
    /* 0x0304 */ int m0304;
    /* 0x0308 */ u8 m0308[0x030C - 0x0308];
    /* 0x030C */ int m030C;
    /* 0x0310 */ u8 m0310[0x0312 - 0x0310];
    /* 0x0312 */ s16 m0312;
    /* 0x0314 */ cXyz mEndPos;
    /* 0x0320 */ cXyz m0320;
    /* 0x032C */ cXyz m032C;
    /* 0x0338 */ bridge_class* mpAite;
    /* 0x033C */ u8 m033C;
    /* 0x033D */ u8 m033D[0x0340 - 0x033D];
    /* 0x0340 */ br_s mBr[50];
    /* 0xD0B8 */ u8 mbStopDraw;
    /* 0xD0B9 */ u8 mD0B9[0xD0BC - 0xD0B9];
    /* 0xD0BC */ dCcD_Stts mStts;
};

#endif /* D_A_BRIDGE_H */
