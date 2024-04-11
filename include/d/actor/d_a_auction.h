#ifndef D_A_AUCTION_H
#define D_A_AUCTION_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

class daAuction_c : public fopAc_ac_c {
public:
    daAuction_c();

    void chkNpcExec(int) {}
    void getAnmNpcNo() {}
    void getAucMdlNo(unsigned char) {}
    void getAucNpcNo(unsigned char) {}
    void getBetNpcNo() {}
    void getKind(unsigned char) {}
    void getNpcNo() {}
    void isAucBet() {}
    void isAucBet2() {}
    void isAucBetA() {}
    void isAucGet() {}
    void isAucJikkyou() {}
    void offCamera() {}
    void onCamera(unsigned char) {}
    void onCameraOld(unsigned char) {}
    void setAucMdlNo(unsigned char, unsigned char) {}
    void setItemNo(unsigned char) {}
    void setKind(unsigned char, unsigned char) {}
    void setNpcID(int, uint) {}
    void setStart(unsigned char) {}

    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeWait();
    void executeNormal();
    void executeStart();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventTalkInit(int);
    void eventMesSet();
    void eventMesEnd();
    void eventStartInit();
    void eventStart();
    void eventMainInit();
    void eventMain();
    void eventMainKai();
    void eventMainUri();
    void eventMainMsgSet();
    void eventMainMsgEnd();
    void eventMainMsgBikonC();
    void eventMainMsgBikonW();
    void eventGetItemInit();
    void eventGetItem();
    void eventCameraOffInit();
    void eventGetItemNpcInit(int);
    void eventGetItemMesInit();
    void eventCameraOffNpc();
    void eventEndInit();
    void eventEnd();
    void eventCameraTestInit();
    void eventCameraTest();
    void next_msgStatus(unsigned long*);
    void setMessage(unsigned long);
    void setMessage2(unsigned long);
    void setMtx();
    void getItemNo();
    void getNpcActorP(int);
    void setCameraNpc(int, short);
    void setLinkAnm(unsigned char);
    void getPiconDispOfs(unsigned char);
    void nextBet();
    void getRand(int);

public:
    /* 0x290 */ u8 m290[0x6C4 - 0x290];
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ dNpc_EventCut_c mNpcEvtInfo;
    /* 0x730 */ u8 m730[0x788 - 0x730];
    /* 0x788 */ J3DModel* mpModel;
    /* 0x78C */ u8 m78C[0x7A4 - 0x78C];
    /* 0x7A4 */ int m7A4;
    /* 0x7A8 */ u8 m7A8[0x7EC - 0x7A8];
    /* 0x7EC */ int m7EC;
    /* 0x7F0 */ int m7F0;
    /* 0x7F4 */ u16 mEvtStartIdx;
    /* 0x7F6 */ u16 mEvtGetItemIdx;
    /* 0x7F8 */ u16 mEvtNoItemIdx;
    /* 0x7FA */ u16 mEvtStart2Idx;
    /* 0x7FC */ u16 mEvtEnd2Idx;
    /* 0x7FE */ u16 mCurrItemNameMsgNo;
    /* 0x800 */ u8 m800[0x81C - 0x800];
    /* 0x81C */ u8 m81C;
    /* 0x81D */ u8 m81D;
    /* 0x81E */ u8 m81E;
    /* 0x81F */ u8 m81F[0x820 - 0x81F];
    /* 0x820 */ u8 m820;
    /* 0x821 */ u8 m821;
    /* 0x822 */ u8 m822;
    /* 0x823 */ u8 mCurrAuctionItemIndex;
    /* 0x824 */ u8 m824;
    /* 0x825 */ u8 m825[0x826 - 0x825];
    /* 0x826 */ u8 m826;
    /* 0x827 */ u8 m827[0x82D - 0x827];
    /* 0x82D */ u8 mCurLinkAnm;
    /* 0x82E */ u8 m82E[0x832 - 0x82E];
    /* 0x832 */ u8 m832;
    /* 0x833 */ u8 m833[0x836 - 0x833];
    /* 0x836 */ u8 m836;
    /* 0x837 */ u8 m837[0x838 - 0x837];
    /* 0x838 */ u8 m838;
    /* 0x839 */ u8 m839[0x83C - 0x839];
};

#endif /* D_A_AUCTION_H */
