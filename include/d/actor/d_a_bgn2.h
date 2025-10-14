#ifndef D_A_BGN2_H
#define D_A_BGN2_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct bgn2_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class m02AC;
    /* 0x02B4 */ mDoExt_McaMorf* m02B4;
    /* 0x02B8 */ mDoExt_J3DModelPacketS m02B8;
    /* 0x02CC */ mDoExt_McaMorf* m02CC;
    /* 0x02D0 */ mDoExt_J3DModelPacketS m02D0;
    /* 0x02E4 */ mDoExt_J3DModelPacketS m02E4;
    /* 0x02F8 */ J3DModel* m02F8[3];
    /* 0x0304 */ mDoExt_brkAnm* m0304;
    /* 0x0308 */ mDoExt_brkAnm* m0308;
    /* 0x030C */ u8 m030C[0x0310 - 0x030C];
    /* 0x0310 */ s16 m0310;
    /* 0x0312 */ s16 m0312;
    /* 0x0314 */ s16 m0314;
    /* 0x0316 */ u8 m0316[0x0318 - 0x0316];
    /* 0x0318 */ cXyz m0318;
    /* 0x0324 */ u8 m0324[0x0330 - 0x0324];
    /* 0x0330 */ s16 m0330[2];
    /* 0x0334 */ u8 m0334[0x033A - 0x0334];
    /* 0x033A */ s16 m033A;
    /* 0x033C */ s16 m033C;
    /* 0x0334 */ u8 m033E[0x0340 - 0x033E];
    /* 0x0340 */ cXyz m0340;
    /* 0x034C */ cXyz m034C;
    /* 0x0358 */ s16 m0358;
    /* 0x035A */ u8 m035A[0x0360 - 0x035A];
    /* 0x037C */ dCcD_Stts m0360;
    /* 0x039C */ dCcD_Sph m039C;
    /* 0x04C8 */ dCcD_Sph m04C8[2];
    /* 0x0720 */ dCcD_Sph m0720[30];
    /* 0x2A48 */ dCcD_Sph m2A48;
    /* 0x2B74 */ cXyz m2B74;
    /* 0x2B80 */ cXyz m2B80[2];
    /* 0x2B98 */ cXyz m2B98[30];
    /* 0x2D00 */ s16 m2D00[32];
    /* 0x2D40 */ u8 m2D40[0x2D60 - 0x2D40];
    /* 0x2D60 */ s16 m2D60;
    /* 0x2D62 */ u8 m2D62[0x2D64 - 0x2D62];
    /* 0x2D64 */ f32 m2D64;
    /* 0x2D68 */ s16 m2D68;
    /* 0x2D6A */ s16 m2D6A;
    /* 0x2D6C */ JPABaseEmitter* m2D6C[32];
    /* 0x2DEC */ JPABaseEmitter* m2DEC[32];
    /* 0x2E6C */ cXyz m2E6C;
    /* 0x2E78 */ s8 m2E78;
    /* 0x2E79 */ s8 m2E79;
    /* 0x2E7A */ u8 m2E7A[0x2E7C - 0x2E7A];
    /* 0x2E7C */ f32 m2E7C;
    /* 0x2E80 */ s16 m2E80;
    /* 0x2E82 */ s16 m2E82;
    /* 0x2E84 */ u8 m2E84[0x2E88 - 0x2E84];
    /* 0x2E88 */ mDoExt_3DlineMat1_c m2E88;
    /* 0x2EC4 */ f32 m2EC4;
    /* 0x2EC8 */ JPABaseEmitter* m2EC8[2];
    /* 0x2ED0 */ s8 m2ED0;
    /* 0x2ED1 */ u8 m2ED1[0x2ED2 - 0x2ED1];
    /* 0x2ED2 */ s16 m2ED2;
    /* 0x2ED4 */ dBgS_AcchCir m2ED4;
    /* 0x2F14 */ dBgS_ObjAcch m2F14;
    /* 0x30D8 */ u8 m30D8;
    /* 0x30D9 */ u8 m30D9[0x30DC - 0x30D9];
}; // Size: 0x30DC

#endif /* D_A_BGN2_H */
