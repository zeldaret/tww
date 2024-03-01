#ifndef D_WPOT_WATER_H
#define D_WPOT_WATER_H

#include "dolphin/types.h"
#include "d/d_particle.h"

class dWpotWater_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();
};

class dWpotWater_EcallBack {
public:
    void execute(JPABaseEmitter*) {}
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8) {}
    
    void draw(JPABaseEmitter*);
};

#endif /* D_WPOT_WATER_H */
