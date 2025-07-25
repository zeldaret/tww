#ifndef D_A_DR2_H
#define D_A_DR2_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class dBgW;
class mDoExt_McaMorf;
class mDoExt_btkAnm;
class mDoExt_brkAnm;
class btd_class;

struct iwa_hahen_s {
    iwa_hahen_s() {}
    ~iwa_hahen_s() {}

    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ bool unk_04;
    /* 0x08 */ cXyz unk_08;
    /* 0x14 */ cXyz unk_14;
    /* 0x20 */ csXyz unk_20;
}; // size = 0x28

class dr2_class {
public:
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf1;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf2;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2C0 */ iwa_hahen_s mRockFragments[6];
    /* 0x3B0 */ cXyz unk_3B0;
    /* 0x3BC */ s16 unk_3BC[12];
    /* 0x3D4 */ s16 unk_3D4[12];
    /* 0x3EC */ f32 unk_3EC;
    /* 0x3F0 */ f32 unk_3F0;
    /* 0x3F4 */ f32 unk_3F4;
    /* 0x3F8 */ f32 unk_3F8;
    /* 0x3FC */ fpc_ProcID unk_3FC;
    /* 0x400 */ s16 unk_400[5];
    /* 0x40A */ u8 unk_40A;
    /* 0x40C */ f32 unk_40C;
    /* 0x410 */ f32 unk_410;
    /* 0x414 */ f32 unk_414;
    /* 0x418 */ J3DModel* unk_418;
    /* 0x41C */ J3DModel* unk_41C;
    /* 0x420 */ mDoExt_btkAnm* unk_420;
    /* 0x424 */ s16 unk_424;
    /* 0x428 */ J3DModel* unk_428;
    /* 0x42C */ J3DModel* unk_42C;
    /* 0x430 */ mDoExt_btkAnm* unk_430;
    /* 0x434 */ mDoExt_btkAnm* unk_434;
    /* 0x438 */ mDoExt_brkAnm* unk_438;
    /* 0x43C */ bool unk_43C;
    /* 0x440 */ Mtx unk_440;
    /* 0x470 */ Mtx unk_470;
    /* 0x4A0 */ dBgW* mpBgW1;
    /* 0x4A4 */ dBgW* mpBgW2;
    /* 0x4A8 */ cXyz unk_4A8;
    /* 0x4B6 */ csXyz unk_4B4;
    /* 0x4BA */ s16 unk_4BA;
    /* 0x4BC */ u8 field_0x4BC[0x4C0 - 0x4BC];
    /* 0x4C0 */ f32 unk_4C0;
    /* 0x4C4 */ u8 unk_4C4;
    /* 0x4C6 */ s16 unk_4C6;
    /* 0x4C8 */ s16 unk_4C8;
    /* 0x4CA */ s16 unk_4CA;
    /* 0x4CC */ s16 unk_4CC;
    /* 0x4CE */ s16 unk_4CE;
    /* 0x4D0 */ f32 unk_4D0;
#if VERSION == VERSION_DEMO
    /* 0x4D4 */ JPABaseEmitter* unk_4D4_demo;
#endif
    /* 0x4D4 */ JPABaseEmitter* unk_4D4;
    /* 0x4D8 */ dPa_followEcallBack unk_4D8;
    /* 0x4EC */ dPa_smokeEcallBack unk_4EC;
    /* 0x50C */ bool unk_50C;
    /* 0x50D */ u8 unk_50D;
    /* 0x50E */ u8 unk_50E;
    /* 0x510 */ s16 unk_510;
    /* 0x514 */ btd_class* unk_514;
}; // size = 0x518

#endif /* D_A_DR2_H */
