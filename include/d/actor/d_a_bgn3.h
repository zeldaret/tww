#ifndef D_A_BGN3_H
#define D_A_BGN3_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

struct bgn3_ke_s {
    /* 0x00 */ cXyz m00[5];
    /* 0x3C */ cXyz m3C[5];
    /* 0x78 */ cXyz m78;
};

struct part_s3 {
    /* 0x0000 */ J3DModel* m0000;
    /* 0x0004 */ mDoExt_J3DModelPacketS m0004;
    /* 0x0018 */ dKy_tevstr_c m0018;
    /* 0x00C8 */ s16 m00C8;
    /* 0x00CA */ u8 m00CA[0x00CC - 0x00CA];
    /* 0x00CC */ f32 m00CC;
    /* 0x00D0 */ s16 m00D0;
    /* 0x00D2 */ u8 m00D2[0x00D4 - 0x00D2];
    /* 0x00D4 */ cXyz m00D4;
    /* 0x00E0 */ s16 m00E0;
    /* 0x00E2 */ s16 m00E2;
    /* 0x00E4 */ u8 m00E4[0x00E8 - 0x00E4];
    /* 0x00E8 */ cXyz m00E8;
    /* 0x00F4 */ f32 m00F4;
    /* 0x00F8 */ dCcD_Sph m00F8;
    /* 0x0224 */ u8 m0224[0x0230 - 0x0224];
    /* 0x0230 */ JPABaseEmitter* m0230;
    /* 0x0234 */ JPABaseEmitter* m0234;
    /* 0x0238 */ s16 m0238;
    /* 0x023A */ u8 m023A[0x023C - 0x023A];
    /* 0x023C */ bgn3_ke_s mHairs[40];
    /* 0x16DC */ mDoExt_3DlineMat0_c mLineMat;
};

struct bgn3_class {
    /* 0x00000 */ fopEn_enemy_c actor;
    /* 0x002AC */ request_of_phase_process_class m002AC;
    /* 0x002B4 */ mDoExt_McaMorf* m002B4;
    /* 0x002B8 */ mDoExt_J3DModelPacketS m002B8;
    /* 0x002CC */ J3DModel* m002CC;
    /* 0x002D0 */ mDoExt_J3DModelPacketS m002D0;
    /* 0x002E4 */ bgn3_ke_s mHairs[40];
    /* 0x01784 */ mDoExt_3DlineMat0_c mLineMat;
    /* 0x017A0 */ mDoExt_J3DModelPacketS m017A0;
    /* 0x017B4 */ J3DModel* m017B4;
    /* 0x017B8 */ J3DModel* m017B8;
    /* 0x017BC */ J3DModel* m017BC;
    /* 0x017BC */ mDoExt_brkAnm* m017C0;
    /* 0x017BC */ mDoExt_brkAnm* m017C4;
    /* 0x017C8 */ u8 m017C8[0x017CC - 0x017C8];
    /* 0x017CC */ part_s3 mParts[10];
    /* 0x0FD7C */ cXyz m0FD7C;
    /* 0x0FD88 */ s16 m0FD88;
    /* 0x0FD8A */ s16 m0FD8A;
    /* 0x0FD8C */ s16 m0FD8C;
    /* 0x0FD8E */ s16 m0FD8E;
    /* 0x0FD90 */ s16 m0FD90;
    /* 0x0FD92 */ s16 m0FD92;
    /* 0x0FD94 */ s16 m0FD94;
    /* 0x0FD96 */ s16 m0FD96;
    /* 0x0FD98 */ f32 m0FD98;
    /* 0x0FD9C */ s16 m0FD9C;
    /* 0x0FD9E */ s16 m0FD9E;
    /* 0x0FDA0 */ JPABaseEmitter* m0FDA0;
    /* 0x0FDA4 */ JPABaseEmitter* m0FDA4;
    /* 0x0FDA8 */ s16 m0FDA8;
    /* 0x0FDAA */ s16 m0FDAA[2];
    /* 0x0FDAE */ s16 m0FDAE;
    /* 0x0FDB0 */ s16 m0FDB0;
    /* 0x0FDB2 */ u8 m0FDB2[0x0FDB4 - 0x0FDB2];
    /* 0x0FDB4 */ s16 m0FDB4;
    /* 0x0FDB6 */ s16 m0FDB6;
    /* 0x0FDB8 */ f32 m0FDB8;
    /* 0x0FDBC */ f32 m0FDBC;
    /* 0x0FDC0 */ dCcD_Stts m0FDC0;
    /* 0x0FDFC */ dCcD_Sph m0FDFC;
    /* 0x0FF28 */ dCcD_Sph m0FF28;
    /* 0x10054 */ cXyz m10054;
    /* 0x10060 */ f32 m10060;
    /* 0x10064 */ mDoExt_3DlineMat1_c m10064;
    /* 0x100A0 */ f32 m100A0;
    /* 0x100A4 */ u8 m100A4[0x100A8 - 0x100A4];
    /* 0x100A8 */ s16 m100A8;
    /* 0x100AA */ u8 m100AA[0x100AC - 0x100AA];
    /* 0x100AC */ s32 m100AC;
    /* 0x100B0 */ u8 m100B0;
    /* 0x100B1 */ u8 m100B1[0x100B4 - 0x100B1];
}; // Size: 0x100B4

#endif /* D_A_BGN3_H */
