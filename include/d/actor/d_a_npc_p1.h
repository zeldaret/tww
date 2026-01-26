#ifndef D_A_NPC_P1_H
#define D_A_NPC_P1_H

#include "f_op/f_op_actor.h"

class daNpc_P1_c : public fopAc_ac_c {
public:
    void checkAction(int (daNpc_P1_c::*)(void*)) {}
    void setAction(int (daNpc_P1_c::*)(void*), void*, int) {}

    void setAnimFromMsg();
    void setAnm(int, float);
    void normalAction(void*);
    void confuseAction(void*);
    void talkAction(void*);
    void p1c_speakAction(void*);
    void speakAction(void*);
    void explainAction(void*);
    void getNextMsgNo(int);
    void playTexPatternAnm();
    void demo_end_init();
    void demo_move();
    void event_move();
    void evn_setAnm_init(int);
    void evn_talk_init(int);
    void evn_talk();
    void minigameExplainCut();
    void privateCut();
    void setAttentionPos(cXyz*);
    cPhs_State _create();
    void CreateHeap();
    BOOL _delete();
    void getKajiID();
    void kaji_anm();
    BOOL _execute();
    BOOL _draw();
    void lookBack();

public:
    /* Place member variables here */
};

class daNpc_P1_HIO_c {
public:
    daNpc_P1_HIO_c();

public:
    /* Place member variables here */
};

class daNpc_P1_childHIO_c {
public:
    daNpc_P1_childHIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_P1_H */
