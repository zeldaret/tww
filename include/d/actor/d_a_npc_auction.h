#ifndef D_A_NPC_AUCTION_H
#define D_A_NPC_AUCTION_H

#include "f_op/f_op_actor.h"

class daNpcAuction_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
    void getMdlNo() {}
    void getPhaseP() {}
    void getPiconOfsY() {}
    void setAction(void (daNpcAuction_c::*)()) {}
    void setBmtNo(int) {}
    void setBtpNo(int) {}
    void setMdlNo(unsigned char) {}
    void setNpcNo(unsigned char) {}

    void createHeap();
    void createInit();
    void wait_action_init();
    void wait_action();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMainInit();
    void eventMain();
    void eventMesSetInit(int);
    void eventMesSet();
    void XyCheckCB(int);
    void XyEventCB(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void setMtx();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnm2(unsigned char, int, float);
    void setAnmTbl(sAnmDat*);
    void isExecute();
    void getRand(int);
    void clrEmitter();

public:
    /* 0x290 */ u8 m290[0x6B0 - 0x290];
    /* 0x6B0 */ u8 m6B0;
    /* 0x6B1 */ u8 m6B1[0x73C - 0x6B1];
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 m73D;
    /* 0x73E */ u8 m73E;
    /* 0x73F */ u8 m73F[0x740 - 0x73F];
    /* 0x740 */ u8 m740;
    /* 0x741 */ u8 m741[0x743 - 0x741];
    /* 0x743 */ u8 m743;
    /* 0x744 */ u8 m744[0x745 - 0x744];
    /* 0x745 */ u8 m745;
    /* 0x746 */ u8 m746[0x74C - 0x746];
};

#endif /* D_A_NPC_AUCTION_H */
