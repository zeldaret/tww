#ifndef D_A_NPC_TC_H
#define D_A_NPC_TC_H

#include "f_op/f_op_actor.h"

class daNpc_Tc_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void getEyePos() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Tc_c::*)(void*), void*) {}

    void _searchTower(fopAc_ac_c*);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void smoke_set(float, float, float, float, float);
    void setAnm();
    void setTexAnm();
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void existTcMonument();
    void anmAtr(unsigned short);
    void stopTower();
    void startTower();
    void next_msgStatusBlue(unsigned long*);
    void next_msgStatusNormal(unsigned long*);
    void next_msgStatus(unsigned long*);
    void setFirstMsg(bool*, unsigned long, unsigned long);
    void getMsgNormal();
    void getMsgBlue();
    void getMsg();
    void getArg();
    void createInit();
    void searchStoolPos(void*, void*);
    void setAttention();
    void calcMove();
    void lookBack();
    void statusWait();
    void statusSit();
    void statusJump();
    void statusWalkToJail();
    void statusTalkNearJail();
    void statusWaitNearJail();
    void statusWalkToStool();
    void statusSitToStool();
    void statusTalk();
    void statusPayRupee();
    void statusDemoPayRupee();
    void statusGetRupee();
    void statusDemoGetRupee();
    void statusMonumentComplete();
    void statusDemoMonumentComplete();
    void statusDemoJump();
    void statusDemoRescue();
    void statusDemoTalk();
    void help_action(void*);
    void wait_action(void*);
    void calc_sitpos();
    void set_mtx();
    BOOL _draw();
    void setTower();
    BOOL _execute();
    BOOL _delete();
    void isCreate();
    cPhs_State _create();
    void _createHeap();
    void next_msgStatusNormal2(unsigned long*);
    void getMsgNormal2();
    void setRupeeSizeMsg();
    void existUnknownCollectMap();
    void analysisCollectMap();
    void existKnownCollectMap();
    void next_msgStatusWhite(unsigned long*);
    void getMsgWhite();
    void next_msgStatusRed(unsigned long*);
    void setFinishMsg();
    void getMsgRed();
    void checkMonumentFee(unsigned short, unsigned short);
    void checkAllMonumentFee();
    void checkAllMonumentPay();
    void checkMonumentPay(unsigned short, unsigned short);
    void cutProc();
    void cutSitToJumpStart(int);
    void cutSitToJumpProc(int);
    void cutPresentStart(int);
    void cutPresentProc(int);
    void cutSetAnmStart(int);
    void cutSetAnmProc(int);
    void cutBackJumpStart(int);
    void cutBackJumpProc(int);
    void cutEffectStart(int);
    void cutEffectProc(int);
    void cutDoorOpenStart(int);
    void cutDoorOpenProc(int);
    void cutDoorCloseStart(int);
    void cutDoorCloseProc(int);
    void cutDoorClose2Start(int);
    void cutDoorClose2Proc(int);
    void cutPayStart(int);
    void cutPayProc(int);

public:
    /* Place member variables here */
};

class daNpc_Tc_HIO_c {
public:
    daNpc_Tc_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_TC_H */
