#ifndef D_A_DAIOCTA_H
#define D_A_DAIOCTA_H

#include "f_op/f_op_actor.h"

class J3DNode;
class dCcD_SrcSph;
class dCcD_SrcCps;

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
    bool _execute();
    void drawAwa();
    void drawSuikomi();
    void drawDebug();
    bool _draw();
    void getArg();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const dCcD_SrcSph m_sph_src;
    static const dCcD_SrcCps m_cps_src;

public:
    /* 0x290 */ u8 field_0x290[0x574 - 0x290];
    /* 0x574 */ u8 mSwitchNo;
};

class daDaiocta_HIO_c {
public:
    daDaiocta_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_DAIOCTA_H */
