#ifndef D_A_DAIOCTA_H
#define D_A_DAIOCTA_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daDaiocta_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    enum Mode_e {
        
    };

    u8 getSw() { return mSwitchNo; }

    void _coHit(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void createAwaHeap();
    void createSuikomiHeap();
    void createBodyHeap();
    void createArrowHitHeap();
    void setMtx();
    void setSuikomiMtx();
    void setAwaMtx();
    void initMtx();
    void setEffect(unsigned short);
    void setAwaRandom(int);
    void initAwa();
    void execAwa();
    void isLivingEye();
    void isDead();
    void isDamageEye();
    void isDamageBombEye();
    void setRotEye();
    void setCollision();
    void modeHideInit();
    void modeHide();
    void modeAppearInit();
    void modeAppear();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDamageBombInit();
    void modeDamageBomb();
    void modeDemoInit();
    void modeDemo();
    void modeDeleteInit();
    void modeDelete();
    void modeProc(Proc_e, Mode_e);
    void setAnm();
    void setWater();
    BOOL _execute();
    void drawAwa();
    void drawSuikomi();
    void drawDebug();
    BOOL _draw();
    void getArg();
    void createInit();
    s32 _create();
    BOOL _delete();

public:
    /* 0x290 */ u8 field_0x290[0x574 - 0x290];
    /* 0x574 */ u8 mSwitchNo;
};

#endif /* D_A_DAIOCTA_H */
