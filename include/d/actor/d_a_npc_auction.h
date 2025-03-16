#ifndef D_A_NPC_AUCTION_H
#define D_A_NPC_AUCTION_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

struct sAnmDat {
    
};

class daNpcAuction_c : public fopNpc_npc_c {
public:
    daNpcAuction_c();

    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void getMdlNo() {}
    void getPhaseP() {}
    f32 getPiconOfsY() { return mPiconOfsY; }
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
    u16 next_msgStatus(u32*);
    u32 getMsg();
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
    /* 0x6C4 */ u8 m6C4[0x724 - 0x6C4];
    /* 0x724 */ f32 mPiconOfsY;
    /* 0x728 */ u8 m728[0x73B - 0x728];
    /* 0x73B */ u8 m73B;
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 m73D;
    /* 0x73E */ u8 m73E[0x73F - 0x73E];
    /* 0x73F */ u8 m73F;
    /* 0x740 */ u8 m740[0x742 - 0x740];
    /* 0x742 */ u8 m742;
    /* 0x743 */ u8 m743[0x744 - 0x743];
    /* 0x744 */ u8 m744;
    /* 0x745 */ u8 field_745[0x74B - 0x745];
};

#endif /* D_A_NPC_AUCTION_H */
