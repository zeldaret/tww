#ifndef D_A_BST_H
#define D_A_BST_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class bst_class : public fopAc_ac_c {
public:
    /* 0x0000 */ f32 z;
    /* 0x0004 */ u8 m0004[0x00F8 - 0x0004];
    /* 0x00F8 */ u16 m00F8;
    /* 0x00FA */ u16 m00FA;
    /* 0x00FC */ u8 m00FC[0x01C4 - 0x00FC];
    /* 0x01C4 */ u32 m01C4;
    /* 0x01C8 */ u8 m01C8[0x01D0 - 0x01C8];
    /* 0x01D0 */ f32 m01D0;
    /* 0x01D4 */ f32 m01D4;
    /* 0x01D8 */ f32 m01D8;
    /* 0x01DC */ s16 m01DC;
    /* 0x01DE */ s16 m01DE;
    /* 0x01E0 */ s16 m01E0;
    /* 0x01E2 */ u8 m01E2[0x01F8 - 0x01E2];
    /* 0x01F8 */ f32 m01F8;
    /* 0x01FC */ f32 m01FC;
    /* 0x0200 */ f32 m0200;
    /* 0x0204 */ u8 m0204[0x020A - 0x0204];
    /* 0x020A */ s8 m020A;
    /* 0x020B */ u8 m020B[0x020C - 0x020B];
    /* 0x020C */ s16 m020C;
    /* 0x020E */ s16 m020E;
    /* 0x0210 */ s16 m0210;
    /* 0x0212 */ u8 m0212[0x0214 - 0x0212];
    /* 0x0214 */ u32 m0214;
    /* 0x0218 */ u32 m0218;
    /* 0x021C */ u32 m021C;
    /* 0x0220 */ u8 m0220[0x0254 - 0x0220];
    /* 0x0254 */ u32 m0254;
    /* 0x0258 */ u8 m0258[0x0260 - 0x0258];
    /* 0x0260 */ u32 m0260;
    /* 0x0264 */ u32 m0264;
    /* 0x0268 */ u32 m0268;
    /* 0x026C */ u8 m026C[0x0274 - 0x026C];
    /* 0x0274 */ u32 m0274;
    /* 0x0278 */ u32 m0278;
    /* 0x027C */ u32 m027C;
    /* 0x0280 */ u32 m0280;
    /* 0x0284 */ u8 m0284[0x0285 - 0x0284];
    /* 0x0285 */ s8 m0285;
    /* 0x0286 */ u8 m0286[0x02B4 - 0x0286];
    /* 0x02B4 */ s8 m02B4;
    /* 0x02B5 */ u8 m02B5[0x02B8 - 0x02B5];
    /* 0x02B8 */ mDoExt_McaMorf* m02B8;
    /* 0x02BC */ mDoExt_baseAnm* m02BC;
    /* 0x02C0 */ mDoExt_baseAnm* m02C0;
    /* 0x02C4 */ s8 m02C4;
    /* 0x02C5 */ u8 m02C5[0x02C8 - 0x02C5];
    /* 0x02C8 */ int m02C8;
    /* 0x02CC */ mDoExt_baseAnm* m02CC;
    /* 0x02D0 */ mDoExt_baseAnm* m02D0;
    /* 0x02D4 */ s8 m02D4;
    /* 0x02D5 */ u8 m02D5[0x0388 - 0x02D5];
    /* 0x0388 */ int m0388;
    /* 0x038C */ u32 m038C;
    /* 0x0390 */ u8 m0390[0x2E9C - 0x0390];
    /* 0x2E9C */ u8 msFrameCount;
    /* 0x2E9D */ u8 m2E9D[0x2FE4 - 0x2E9D];
};

#endif /* D_A_BST_H */
