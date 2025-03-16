#ifndef D_A_NPC_PHOTO_H
#define D_A_NPC_PHOTO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

struct sPhotoAnmDat {
    
};

class daNpcPhoto_c : public fopAc_ac_c {
public:
    void getPhaseP() {}
    void incMsgTbl() {}
    void isDate() {}
    void nullMsgTbl() {}
    void setMsgTbl(unsigned long*, signed char*) {}
    void setPosFlag(unsigned char) {}
    void setResFlag(unsigned char) {}

    daNpcPhoto_c();
    s32 _create();
    void createHeap();
    void createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
    void executeWait();
    void executeTalk();
    void executeWalk();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventSeSetInit(int);
    void eventPosSetInit();
    void eventGetItemInit();
    void eventGetItem();
    void eventSetAngleInit();
    void eventSetEyeInit();
    void eventSetEye();
    void eventTurnToPlayerInit();
    void eventTurnToPlayer();
    void eventClrHanmeInit();
    void eventGetPhotoInit();
    void eventGetPhoto();
    void eventMesSetUbInit(int);
    void eventMesSetUb();
    void eventLookUb();
    void talk2(int);
    void setMsgCamera();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmRailID();
    void getPrmArg0();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool, int);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sPhotoAnmDat*);
    void XyCheckCB(int);
    void XyEventCB(int);
    void isPhotoOk();
    void isPhotoDxOk();
    void setCollision(dCcD_Cyl*, cXyz, float, float);

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_PHOTO_H */
