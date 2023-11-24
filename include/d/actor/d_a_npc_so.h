#ifndef D_A_NPC_SO_H
#define D_A_NPC_SO_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"

class daNpc_So_c : public fopAc_ac_c {
public:
    void cutAppearProc() {}
    void cutAppearStart() {}
    void cutDisappearProc() {}
    void cutDisappearStart() {}
    void cutDiveProc() {}
    void cutDiveStart() {}
    void cutEatesaFirstProc() {}
    void cutEatesaFirstStart() {}
    void cutEatesaProc() {}
    void cutEatesaStart() {}
    void cutEffectProc() {}
    void cutEffectStart() {}
    void cutEquipProc() {}
    void cutEquipStart() {}
    void cutJumpMapopenProc() {}
    void cutJumpMapopenStart() {}
    void cutJumpProc() {}
    void cutJumpStart() {}
    void cutMiniGameEndProc() {}
    void cutMiniGameEndStart() {}
    void cutMiniGamePlTurnProc() {}
    void cutMiniGamePlTurnStart() {}
    void cutMiniGamePlUpProc() {}
    void cutMiniGamePlUpStart() {}
    void cutMiniGameProc() {}
    void cutMiniGameReturnProc() {}
    void cutMiniGameReturnStart() {}
    void cutMiniGameStart() {}
    void cutMiniGameWaitProc() {}
    void cutMiniGameWaitStart() {}
    void cutMiniGameWarpProc() {}
    void cutMiniGameWarpStart() {}
    void cutPartnerShipProc() {}
    void cutPartnerShipStart() {}
    void cutProc() {}
    void cutSetAnmProc() {}
    void cutSetAnmStart() {}
    void cutSwimProc() {}
    void cutSwimStart() {}
    void cutTurnProc() {}
    void cutTurnStart() {}
    void cutUnequipProc() {}
    void cutUnequipStart() {}
    void getMiniGameRestArrow() {}
    void initCam() {}
    void isAnm(signed char) {}
    void modeProcInit(int) {}
    void moveCam() {}

    void _searchEsa(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    void _searchTagSo(fopAc_ac_c*);
    void _searchMinigameTagSo(fopAc_ac_c*);
    void XyCheckCB(int);
    void XyEventCB(int);
    void _createHeap();
    void jntHitCreateHeap();
    void checkTgHit();
    void offsetZero();
    void offsetDive();
    void offsetSwim();
    void offsetAppear();
    void getMsg();
    void next_msgStatus(unsigned long*);
    void lookBack();
    void setAttention();
    void setAnm(signed char, bool);
    void setAnmSwimSpeed();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeHideInit();
    void modeHide();
    void modeJumpInit();
    void modeJump();
    void modeSwimInit();
    void modeSwim();
    void modeNearSwimInit();
    void modeNearSwim();
    void modeEventFirstWaitInit();
    void modeEventFirstWait();
    void modeEventFirstInit();
    void modeEventFirst();
    void modeEventFirstEndInit();
    void modeEventFirstEnd();
    void modeEventEsaInit();
    void modeEventEsa();
    void modeEventMapopenInit();
    void modeEventMapopen();
    void modeEventBowInit();
    void modeEventBow();
    void modeTalkInit();
    void modeTalk();
    void modeDisappearInit();
    void modeDisappear();
    void modeDebugInit();
    void modeDebug();
    void modeGetRupeeInit();
    void modeGetRupee();
    void modeEventTriForceInit();
    void modeEventTriForce();
    void modeProc(daNpc_So_c::Proc_e, int);
    void eventOrder();
    void checkOrder();
    void setScale();
    void _execute();
    void debugDraw();
    void hudeDraw();
    void _draw();
    void createInit();
    void getArg();
    void _create();
    void _delete();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_SO_H */
