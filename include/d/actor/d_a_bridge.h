#ifndef D_A_BRIDGE_H
#define D_A_BRIDGE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class dBgWSv;
class JPABaseEmitter;

struct br_s {
    /* 0x000 */ J3DModel* mpModel;
    /* 0x004 */ J3DLightObj mLight;
    /* 0x078 */ u8 m078[0xB4 - 0x78];
    /* 0x0B4 */ J3DModel* mpModelRope1;
    /* 0x0B8 */ J3DModel* mpModelRope0;
    /* 0x0BC */ mDoExt_3DlineMat1_c mLineMat1;
    /* 0x0F8 */ cXyz m0F8[3];
    /* 0x11C */ cXyz m11C[3];
    /* 0x140 */ dCcD_Cyl mCyl[2];
    /* 0x3A0 */ s16 m3A0[2];
    /* 0x3A4 */ s8 m3A4;
    /* 0x3A5 */ s8 m3A5;
    /* 0x3A6 */ u8 m3A6[0x3A8 - 0x3A6];
    /* 0x3A8 */ cXyz m3A8[2];
    /* 0x3C0 */ s16 m3C0;
    /* 0x3C2 */ s16 m3C2;
    /* 0x3C4 */ JPABaseEmitter* m3C4;
    /* 0x3C8 */ JPABaseEmitter* m3C8;
    /* 0x3CC */ cXyz m3CC;
    /* 0x3D8 */ cXyz mPosition;
    /* 0x3E4 */ csXyz mRotation;
    /* 0x3EA */ s16 mRotationYExtra;
    /* 0x3EC */ f32 m3EC;
    /* 0x3F0 */ f32 m3F0;
    /* 0x3F4 */ f32 m3F4;
    /* 0x3F8 */ f32 m3F8;
    /* 0x3FC */ f32 m3FC;
    /* 0x400 */ s16 m400;
    /* 0x402 */ s16 m402;
    /* 0x404 */ s16 m404;
    /* 0x406 */ u8 m406;
    /* 0x407 */ u8 m407;
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409[0x40C - 0x409];
    /* 0x40C */ cXyz mScale;
    /* 0x418 */ s16 m418;
    /* 0x41A */ u8 m41A[0x41C - 0x41A];
};  // Size: 0x41C
STATIC_ASSERT(sizeof(br_s) == 0x41C);

struct bridge_class {
    /* 0x0000 */ fopAc_ac_c actor;
    /* 0x0290 */ request_of_phase_process_class mPhase;
    /* 0x0298 */ s16 mMoveProcMode;
    /* 0x029A */ u8 m029A[0x029C - 0x029A];
    /* 0x029C */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x02D8 */ u8 mTypeBits;
    /* 0x02D9 */ u8 m02D9;
    /* 0x02DA */ u8 mPathId;
    /* 0x02DB */ u8 mPathIdP;
    /* 0x02DC */ s8 mBrCount;
    /* 0x02DD */ s8 m02DD;
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
    /* 0x02FC */ f32 m02FC;
    /* 0x0300 */ s16 m0300;
    /* 0x0302 */ s16 m0302;
    /* 0x0304 */ s32 m0304;
    /* 0x0308 */ s32 m0308;
    /* 0x030C */ s32 m030C;
    /* 0x0310 */ u8 m0310[0x0312 - 0x0310];
    /* 0x0312 */ s16 m0312;
    /* 0x0314 */ cXyz mEndPos;
    /* 0x0320 */ cXyz m0320;
    /* 0x032C */ cXyz m032C;
    /* 0x0338 */ bridge_class* mpAite;
    /* 0x033C */ s8 m033C;
    /* 0x033D */ u8 m033D[0x0340 - 0x033D];
    /* 0x0340 */ br_s mBr[50];
    /* 0xD0B8 */ s8 mbStopDraw;
    /* 0xD0B9 */ u8 mD0B9[0xD0BC - 0xD0B9];
    /* 0xD0BC */ dCcD_Stts mStts;
}; // size = 0xD0F8

#endif /* D_A_BRIDGE_H */
