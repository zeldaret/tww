#ifndef D_A_NZG_H
#define D_A_NZG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

struct dPath;

struct nzg_class {
public:
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ u8 m2B8;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 m2BC[0x2BE - 0x2BC];
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2[5];
    /* 0x2CC */ f32 m2CC;
    /* 0x2D0 */ f32 m2D0;
    /* 0x2D4 */ fpc_ProcID m2D4;
    /* 0x2D8 */ dPath* mpPath;
    /* 0x2DC */ u8 m2DC[0x2E9 - 0x2DC];
    /* 0x2E9 */ u8 m2E9;
    /* 0x2EC */ dCcD_Stts mStts;
    /* 0x328 */ dCcD_Cyl mCyl;
};

#endif /* D_A_NZG_H */
