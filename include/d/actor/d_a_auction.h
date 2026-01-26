#ifndef D_A_AUCTION_H
#define D_A_AUCTION_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "d/d_particle.h"
#include "d/d_timer.h"
#include "m_Do/m_Do_hostIO.h"

class daAuction_c : public fopNpc_npc_c {
public:
    typedef void(daAuction_c::*ProcFunc_t)();

    struct ItemData {
        /* 0x00 */ s16 mItemID;
        /* 0x02 */ s16 mNameMsgID;
        /* 0x04 */ s16 mStartingBid;
        /* 0x06 */ u16 mObtainedEventBit;
    };  // Size: 0x08

    daAuction_c();

    void chkNpcExec(int) {}
    void getAnmNpcNo() {}
    u8 getAucMdlNo(u8 idx) { return mAucMdlNo[idx]; }
    void getAucNpcNo(unsigned char) {}
    void getBetNpcNo() {}
    void getKind(unsigned char) {}
    void getNpcNo() {}
    void isAucBet() {}
    void isAucBet2() {}
    void isAucBetA() {}
    void isAucGet() {}
    void isAucJikkyou() {}
    void offCamera() { // Might be incorrect
        m835 |= 2;
        m835 &= 0xFE;
    }
    void onCamera(unsigned char) {}
    void onCameraOld(unsigned char) {}
    void setAucMdlNo(u8 idx, u8 mdlNo) { mAucMdlNo[idx] = mdlNo; }
    void setItemNo(unsigned char) {}
    void setKind(unsigned char, unsigned char) {}
    void setNpcID(int, fpc_ProcID) {}
    void setStart(unsigned char) {}

    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
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
    bool eventMesSet();
    bool eventMesEnd();
    void eventStartInit();
    bool eventStart();
    void eventMainInit();
    bool eventMain();
    void eventMainKai();
    void eventMainUri();
    void eventMainMsgSet();
    void eventMainMsgEnd();
    void eventMainMsgBikonC();
    void eventMainMsgBikonW();
    void eventGetItemInit();
    bool eventGetItem();
    void eventCameraOffInit();
    void eventGetItemNpcInit(int staffIdx);
    void eventGetItemMesInit();
    bool eventCameraOffNpc();
    void eventEndInit();
    bool eventEnd();
    void eventCameraTestInit();
    bool eventCameraTest();
    u16 next_msgStatus(u32* pMsgNo);
    void setMessage(u32);
    void setMessage2(u32);
    void setMtx();
    u8 getItemNo();
    fopAc_ac_c* getNpcActorP(int idx);
    void setCameraNpc(int, s16);
    void setLinkAnm(u8 linkAnm);
    f32 getPiconDispOfs(u8 param);
    void nextBet();
    int getRand(int);

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ dNpc_EventCut_c mNpcEvtInfo;
    /* 0x738 */ fpc_ProcID m738[8];
    /* 0x758 */ fpc_ProcID mCurrAuctionItemPID;
    /* 0x75C */ fpc_ProcID mTimerID;
    /* 0x760 */ fpc_ProcID mGaugeID;
    /* 0x764 */ dTimer_c* mpTimer;
    /* 0x768 */ LIGHT_INFLUENCE mLight;
    /* 0x788 */ J3DModel* mpModel;
    /* 0x78C */ cXyz m78C;
    /* 0x798 */ cXyz m798;
    /* 0x7A4 */ JPABaseEmitter* mpEmitter;
    /* 0x7A8 */ cXyz m7A8;
    /* 0x7B4 */ u8 m7B4[0x7BC - 0x7B4];
    /* 0x7BC */ f32 mAlpha;
    /* 0x7C0 */ f32 mBlend;
    /* 0x7C4 */ f32 m7C4[7]; // Npc wait timer?
    /* 0x7E0 */ f32 m7E0;
    /* 0x7E4 */ f32 m7E4;
    /* 0x7E8 */ u8 m7E8[0x7EC - 0x7E8];
    /* 0x7EC */ int m7EC;
    /* 0x7F0 */ int m7F0;
    /* 0x7F4 */ s16 mEvtStartIdx;
    /* 0x7F6 */ s16 mEvtGetItemIdx;
    /* 0x7F8 */ s16 mEvtNoItemIdx;
    /* 0x7FA */ s16 mEvtStart2Idx;
    /* 0x7FC */ s16 mEvtEnd2Idx;
    /* 0x7FE */ s16 mCurrBid;
    /* 0x800 */ s16 m800;
    /* 0x802 */ s16 mTimer;
    /* 0x804 */ u16 m804;
    /* 0x806 */ s16 m806;
    /* 0x808 */ s16 m808;
    /* 0x80A */ s16 m80A;
    /* 0x80C */ u8 m80C[8];
    /* 0x814 */ u8 mAucMdlNo[8];
    /* 0x81C */ u8 m81C;
    /* 0x81D */ u8 m81D;
    /* 0x81E */ u8 mMoveState;
    /* 0x81F */ u8 m81F;
    /* 0x820 */ u8 m820;
    /* 0x821 */ u8 m821;
    /* 0x822 */ u8 m822;
    /* 0x823 */ u8 mCurrAuctionItemIndex;
    /* 0x824 */ u8 m824;
    /* 0x825 */ u8 m825;
    /* 0x826 */ u8 m826;
    /* 0x827 */ u8 m827;
    /* 0x828 */ u8 m828;
    /* 0x829 */ u8 m829;
    /* 0x82A */ u8 m82A;
    /* 0x82B */ u8 m82B;
    /* 0x82C */ u8 m82C;
    /* 0x82D */ u8 mCurLinkAnm;
    /* 0x82E */ u8 m82E;
    /* 0x82F */ u8 m82F;
    /* 0x830 */ u8 m830;
    /* 0x831 */ u8 m831;
    /* 0x832 */ u8 m832;
    /* 0x833 */ u8 mFace;
    /* 0x834 */ u8 m834;
    /* 0x835 */ u8 m835;
    /* 0x836 */ u8 m836;
    /* 0x837 */ u8 mFlags;  /* Just a guess */
    /* 0x838 */ s8 m838;
    /* 0x839 */ s8 mAction;
    /* 0x83A */ u8 field_83A[0x83C - 0x83A];
};

/* Inferred from debug map */
class daAuction_HIO_c : public JORReflexible  {
public:
    daAuction_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

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
