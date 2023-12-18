#ifndef D_SALVAGE_H
#define D_SALVAGE_H

#include "SSystem/SComponent/c_xyz.h"

class JPABaseEmitter;
class fopAc_ac_c;

class dSalvage_control_c {
public:
    void init();
    void init_end();
    void entry(fopAc_ac_c*, JPABaseEmitter*);
    void init_room(s8);
    void init_one(int);
    void init_one_sub(int);
    void calcDistanceXZ();
    void getPos(int);
    void getPosP(int);
    void getScale(int);
    void getR(int);
    void getH(int);
    void getRoomNo(int);
    void getItemNo(int);
    void getSwitchNo(int);
    void getSaveNo(int);
    void getType(int);
    void getKind(int);
    void getDistance(int);
    void getAlphaPtr(int);
    void getDrawMode(int);
    void checkRegist(int);
    void checkUsed(int);
    void setPos(int, cXyz);
    void setFlag(int, u8);
    void clrFlag(int, u8);
    void setNowAlpha(int, u8);
    void setDrawMode(int, int);
};

#endif /* D_SALVAGE_H */
