#ifndef D_A_STEAM_TAG_H
#define D_A_STEAM_TAG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_point_wind.h"
#include "f_op/f_op_actor_mng.h"

class JPABaseEmitter;

struct daSteamTag_mData {
    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 create_time_range;
    /* 0x06 */ s16 create_time_min;
    /* 0x08 */ s16 emit_time_min;
    /* 0x0A */ s16 emit_time_range;
    /* 0x0C */ u8  steam_alpha;
    /* 0x0D */ u8  field_0x0D;
    /* 0x0E */ s16  field_0x0E;
};

class daSteamTag_c : public fopAc_ac_c {
public:
    ~daSteamTag_c();
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

    const daSteamTag_mData* getData();
    s32 CreateInit();
    BOOL createEmitter();
    bool endEmitter();

    static void init();

    static daSteamTag_mData mData;

public:
    /* 0x290 */ JPABaseEmitter* mpEmitter;
    /* 0x294 */ u8 m294[0x296 - 0x294];
    /* 0x296 */ s16 mEmitTimer;
    /* 0x298 */ s16 mCreateTimer;
    /* 0x29A */ u8 m29A;
    /* 0x29B */ u8 m29B;
    /* 0x29C */ dCcD_Stts mGStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dCcD_Cps mCps;
    /* 0x540 */ cM3dGCpsS mPntWindCpsS;
    /* 0x55C */ dPointWind_c mPointWind;

public:
    static u8 mEmitterNum;
};

namespace daSteamTag_prm {
    inline u8 getSchBit(daSteamTag_c* item) { return (fopAcM_GetParam(item) >> 2) & 0xFF; }
};

#endif /* D_A_STEAM_TAG_H */
