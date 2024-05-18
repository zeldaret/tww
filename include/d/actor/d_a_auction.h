#ifndef D_A_AUCTION_H
#define D_A_AUCTION_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_com_inf_game.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"

class daAuction_c : public fopNpc_npc_c {
public:
    typedef void(daAuction_c::*ProcFunc_t)();

    struct ItemData {
        /* 0x00 */ u16 mItemID;
        /* 0x02 */ u16 mNameMsgID;
        /* 0x04 */ u16 mStartingBid;
        /* 0x06 */ u16 mObtainedEventBit;
    };  // Size: 0x08

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
    BOOL createHeap();
    s32 createInit();
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
    u16 next_msgStatus(u32* pMsgNo);
    void setMessage(unsigned long);
    void setMessage2(unsigned long);
    void setMtx();
    void getItemNo();
    void getNpcActorP(int);
    void setCameraNpc(int, short);
    void setLinkAnm(unsigned char);
    void getPiconDispOfs(unsigned char);
    void nextBet();
    int getRand(int);

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ dNpc_EventCut_c mNpcEvtInfo;
    //* 0x730 */ u8 m730[0x738 - 0x730];
    /* 0x738 */ u32 m738[8];
    /* 0x758 */ u8 m758[0x764 - 0x758];
    /* 0x764 */ dTimer_c* mpTimer;
    /* 0x768 */ LIGHT_INFLUENCE mLight;
    /* 0x788 */ J3DModel* mpModel;
    /* 0x78C */ cXyz m78C;
    /* 0x798 */ cXyz m798;
    /* 0x7A4 */ JPABaseEmitter* mpEmitter;
    /* 0x7A8 */ u8 m7A8[0x7BC - 0x7A8];
    /* 0x7BC */ f32 mAlpha;
    /* 0x7C0 */ f32 mBlend;
    /* 0x7C4 */ f32 m7C4;
    /* 0x7C8 */ u8 m7C8[0x7EC - 0x7C8];
    /* 0x7EC */ int m7EC;
    /* 0x7F0 */ int m7F0;
    /* 0x7F4 */ s16 mEvtStartIdx;
    /* 0x7F6 */ s16 mEvtGetItemIdx;
    /* 0x7F8 */ s16 mEvtNoItemIdx;
    /* 0x7FA */ s16 mEvtStart2Idx;
    /* 0x7FC */ s16 mEvtEnd2Idx;
    /* 0x7FE */ u16 mCurrItemNameMsgNo;
    /* 0x800 */ u8 m800[0x802 - 0x800];
    /* 0x802 */ s16 mTimer;
    /* 0x804 */ u8 m804[0x808 - 0x804];
    /* 0x808 */ u16 m808;
    /* 0x80A */ s16 m80A;
    /* 0x80C */ u8 m80C[8];
    /* 0x814 */ u8 m814[8];
    /* 0x81C */ u8 m81C;
    /* 0x81D */ u8 m81D;
    /* 0x81E */ u8 mMoveState;
    /* 0x81F */ u8 m81F[0x820 - 0x81F];
    /* 0x820 */ u8 m820;
    /* 0x821 */ u8 m821;
    /* 0x822 */ u8 m822;
    /* 0x823 */ u8 mCurrAuctionItemIndex;
    /* 0x824 */ u8 m824;
    /* 0x825 */ u8 m825[0x826 - 0x825];
    /* 0x826 */ u8 m826;
    /* 0x827 */ u8 m827[0x82A - 0x827];
    /* 0x82A */ u8 m82A;
    /* 0x82B */ u8 m82B[0x82C - 0x82B];
    /* 0x82C */ u8 m82C;
    /* 0x82D */ u8 mCurLinkAnm;
    /* 0x82E */ u8 m82E[0x832 - 0x82E];
    /* 0x832 */ u8 m832;    /* Might be mode index */
    /* 0x833 */ u8 m833[0x836 - 0x833];
    /* 0x836 */ u8 m836;
    /* 0x837 */ u8 mFlags;  /* Just a guess */
    /* 0x838 */ s8 m838;
    /* 0x839 */ u8 mAction;
    /* 0x83A */ u8 field_83A[0x83C - 0x83A];
};

/* Inferred from debug map */
class daAuction_HIO_c : public JORReflexible  {
public:
    daAuction_HIO_c() {}

public:
    /* Place member variables here */
};

/* Inferred from debug map */
class daAuction_Npc_HIO_c {
public:
    daAuction_Npc_HIO_c() {}

public:
    /* Place member variables here */
};

#endif /* D_A_AUCTION_H */
