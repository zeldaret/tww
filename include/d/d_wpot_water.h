#ifndef D_WPOT_WATER_H
#define D_WPOT_WATER_H

#include "d/d_particle.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_kankyo.h"

class dWpotWater_EcallBack : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*) {}
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8) {}
    
    void draw(JPABaseEmitter*);
};

class dWpotWater_c : public kankyo_class {
public:
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();

public:
    static dWpotWater_EcallBack mEcallback;

public:
    /* 0x0F8 */ JPABaseEmitter* emtr;
    /* 0x0FC */ dDlst_alphaVolPacket mPacket;
};

#endif /* D_WPOT_WATER_H */
