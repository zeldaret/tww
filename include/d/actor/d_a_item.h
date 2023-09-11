#ifndef D_A_ITEM_H
#define D_A_ITEM_H

#include "d/actor/d_a_itembase.h"

class daItem_c : public daItemBase_c {
public:
    float getYOffset();
    void set_mtx();
    void set_mtx_base(J3DModel*, cXyz, csXyz);
    void CreateInit();
    s32 _daItem_create();
    s32 _daItem_execute();
    void mode_proc_call();
    void execInitNormalDirection();
    void execMainNormalDirection();
    void execInitGetDemoDirection();
    void execWaitGetDemoDirection();
    void execMainGetDemoDirection();
    void execBringNezumi();
    void execWaitMain();
    void execWaitMainFromBoss();
    void scaleAnimFromBossItem();
    s32 _daItem_draw();
    void setTevStr();
    s32 _daItem_delete();
    void itemGetExecute();
    void itemDefaultRotateY();
    bool checkItemDisappear();
    void setItemTimer(int);
    bool checkPlayerGet();
    void itemActionForRupee();
    void itemActionForHeart();
    void itemActionForKey();
    void itemActionForEmono();
    void itemActionForSword();
    void itemActionForArrow();
    void checkWall();
    void set_bound_se();
    s32 checkGetItem();
    void timeCount();
    void mode_wait_init();
    void mode_water_init();
    void mode_wait();
    void mode_water();
    void initAction();
    s32 _daItem_isdelete();

public:
    u8 temp1[0x20];
    /* 0x668 */ u8 mItemAction;
    /* 0x669 */ u8 mStatusFlags;
    /* 0x66A */ u8 mMode;
    /* 0x66B */ u8 mCurAction;
    u8 temp2[0x54];
};

#endif /* D_A_ITEM_H */