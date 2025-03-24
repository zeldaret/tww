#ifndef D_A_SALVAGE_TBOX_H
#define D_A_SALVAGE_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class daSTBox_shadowEcallBack_c : public dPa_levelEcallBack {
public:
    void deleteCallBack() {}
    void getEmitter() {}
    void setDepth(float) {}
    void setIndirectTexData(float, float) {}
    void setPos(cXyz&) {}
    void setWaterFlatY(float) {}
    void setWaterY(float) {}
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char) {}

    void getMaxWaterY(JGeometry::TVec3<float>*);
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
};

class daSTBox_c : public fopAc_ac_c {
public:
    inline bool _draw();

    bool _delete();
    void CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void initWait(int);
    void initWait02(int);
    void initWaitGetItem(int);
    void initWaitDummy(int);
    void initDrop(int);
    void actWait(int);
    void actDrop(int);
    void actWait02(int);
    void actWaitGetItem(int);
    void actWaitDummy(int);

public:
    /* Place member variables here */
};

#endif /* D_A_SALVAGE_TBOX_H */
