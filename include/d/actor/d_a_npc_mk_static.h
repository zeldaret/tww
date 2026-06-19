#ifndef D_A_NPC_MK_STATIC_H
#define D_A_NPC_MK_STATIC_H

#include "d/actor/d_a_player_main.h"
#include "d/d_npc.h"
#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"

class daNpc_Mk_Static_c {
public:
    void aroundWalk(fopAc_ac_c*, fopAc_ac_c*, u8);
    u32 turnPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    BOOL chkPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    BOOL walkPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    f32 getSpeedF(f32, f32);
    void init(u8, u16);
    u8 goFarLink_3(fopAc_ac_c*, dNpc_PathRun_c*);
    u8 goFarLink_2(fopAc_ac_c*, dNpc_PathRun_c*);
    void runaway_com2(dNpc_PathRun_c*, u8);
    u8 runAwayProc(fopAc_ac_c*, dNpc_PathRun_c*, dCcD_Cyl*, s16*);
    bool chkGameSet();
    void setRndPathPos(fopAc_ac_c*, dNpc_PathRun_c*);
    bool chkPointPass(cXyz*, cXyz*, cXyz*);

    /* 0x00 */ u8 m0;
    /* 0x04 */ f32 m4;
    /* 0x08 */ u16 m8;
    /* 0x0A */ u16 ma;
    /* 0x0C */ u8 mPointIndex1;
    /* 0x0D */ bool md;
    /* 0x0E */ u8 me;
    /* 0x0F */ u8 mPointIndex2;
};

#endif /* D_A_NPC_MK_STATIC_H */
