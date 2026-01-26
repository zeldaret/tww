#ifndef D_A_FM_H
#define D_A_FM_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"

class daFm_c : public fopEn_enemy_c {
public:
    enum Proc_e {
        
    };

    void isBodyAppear() {}
    void isHoleAppear() {}
    void modeProcInit(int) {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void holeCreateHeap();
    void bodyCreateHeap();
    void jntHitCreateHeap();
    void _pathMove(cXyz*, cXyz*, cXyz*);
    void searchNearOtherActor(fopAc_ac_c*);
    void searchNearFm(fopAc_ac_c*);
    void moveRndBack();
    void moveRndEscape();
    void spAttackVJump();
    void spAttackJump();
    void spAttackNone();
    void iceProc();
    void bodySetMtx();
    void holeSetMtx();
    void setCollision();
    void setAttention();
    void checkTgHit();
    void setGrabPos();
    void getOffsetPos();
    void checkPlayerGrabBomb();
    void checkPlayerGrabNpc();
    void checkPlayerGrabTarget();
    void isGrabPos();
    void isGrab();
    void isGrabFoot();
    void modeSwWaitInit();
    void modeSwWait();
    void modeHideInit();
    void modeHide();
    void modeUnderFootInit();
    void modeUnderFoot();
    void modePathMoveInit();
    void modePathMove();
    void modeGoalKeeperInit();
    void modeGoalKeeper();
    void modeAppearInit();
    void modeAppear();
    void modeDisappearInit();
    void modeDisappear();
    void modeWaitInit();
    void modeWait();
    void modeAttackInit();
    void modeAttack();
    void modeThrowInit();
    void modeThrow();
    void modeGrabFootDemoInit();
    void modeGrabFootDemo();
    void modeParalysisInit();
    void modeParalysis();
    void modeDamageInit();
    void modeDamage();
    void modeGrabInit();
    void modeGrab();
    void modeGrabDemoInit();
    void modeGrabDemo();
    void modeDeathInit();
    void modeDeath();
    void modePrepareItemInit();
    void modePrepareItem();
    void modeGrabNpcDemoInit();
    void modeGrabNpcDemo();
    void modePlayerStartDemoInit();
    void modePlayerStartDemo();
    void modeDeleteInit();
    void modeDelete();
    void modeBikubikuInit();
    void modeBikubiku();
    void modeProc(Proc_e, int);
    void setAnm(signed char, bool);
    void cancelGrab();
    void calcInvKine(fopAc_ac_c*);
    void resetInvKine();
    void grabBomb();
    void grabTsubo();
    void grabPlayer();
    void grabNPC();
    void searchTarget();
    void setBaseTarget();
    void turnToBaseTarget();
    void isNpc(fopAc_ac_c*);
    void checkHeight(fopAc_ac_c*);
    void isLink(fopAc_ac_c*);
    void isLinkControl();
    void areaCheck();
    void lineCheck(cXyz*, cXyz*);
    void setRnd(int, int);
    void setHoleEffect();
    void holeExecute();
    void setHoleScale(float, float, float);
    bool _execute();
    void MtxToRot(Mtx, csXyz*);
    void debugDraw();
    void holeDraw();
    void bodyDraw();
    bool _draw();
    void getArg();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const dCcD_SrcSph m_sph_src;
    static const dCcD_SrcCyl m_cyl_src;

public:
    /* 0x2AC */ u8 m2AC[0x2C5 - 0x2AC];
    /* 0x2C5 */ s8 m2C5;
    /* 0x2C6 */ u8 m2C6[0x2E4 - 0x2C6];
    /* 0x2E4 */ u8 m2E4;
    /* 0x2E5 */ u8 m2E5[0x400 - 0x2E5];
    /* 0x400 */ mDoExt_McaMorf* mpMcaMorf;
    /* 0x404 */ u8 m404[0x608 - 0x404];
    /* 0x608 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x610 */ u8 m610[0x9CC - 0x610];
    /* 0x9CC */ fopAc_ac_c* mBaseTarget;
    /* 0x9D0 */ u8 m9D0[0xAE4 - 0x9D0];
    /* 0xAE4 */ u8 mAE4;
    /* 0xAE5 */ u8 mAE5;
    /* 0xAE6 */ u8 mAE6[0xAE8 - 0xAE6];
    /* 0xAE8 */ enemyice mEnemyIce;
};

class daFm_HIO_c {
public:
    daFm_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_FM_H */
