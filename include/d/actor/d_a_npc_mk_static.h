#ifndef D_A_NPC_MK_STATIC_H
#define D_A_NPC_MK_STATIC_H

#include "dolphin/types.h"

class fopAc_ac_c;
class dNpc_PathRun_c;
class dCcD_Cyl;
class cXyz;

class daNpc_Mk_Static_c {
public:
    void aroundWalk(fopAc_ac_c*, fopAc_ac_c*, u8);
    void turnPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    void chkPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    void walkPath(fopAc_ac_c*, dNpc_PathRun_c*, u8);
    void getSpeedF(f32, f32);
    void init(u8, u16);
    void goFarLink_3(fopAc_ac_c*, dNpc_PathRun_c*);
    void goFarLink_2(fopAc_ac_c*, dNpc_PathRun_c*);
    void runaway_com2(dNpc_PathRun_c*, u8);
    void runAwayProc(fopAc_ac_c*, dNpc_PathRun_c*, dCcD_Cyl*, s16*);
    void chkGameSet();
    void setRndPathPos(fopAc_ac_c*, dNpc_PathRun_c*);
    void chkPointPass(cXyz*, cXyz*, cXyz*);
};

#endif /* D_A_NPC_MK_STATIC_H */
