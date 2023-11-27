#ifndef D_A_STEAM_TAG_H
#define D_A_STEAM_TAG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_point_wind.h"

class JPABaseEmitter;

class daSteamTag_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

    void getData();
    void CreateInit();
    void createEmitter();
    void endEmitter();

public:
    /* 0x290 */ JPABaseEmitter* mpEmitter;
    /* 0x294 */ u8 m294[0x296 - 0x294];
    /* 0x296 */ s16 mEmitTimer;
    /* 0x298 */ s16 mCreateTimer;
    /* 0x29A */ u8 m29A[0x29B - 0x29A];
    /* 0x29B */ u8 m29B;
    /* 0x29C */ dCcD_Stts mGStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dCcD_Cps mCps;
    /* 0x540 */ cM3dGCpsS mPntWindCpsS;
    /* 0x55C */ dPointWind_c mPointWind;
};

#endif /* D_A_STEAM_TAG_H */
