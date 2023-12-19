#ifndef D_A_AGB_H
#define D_A_AGB_H

#include "d/d_bg_s.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"
#include "global.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class daAgb_HIO_c : public mDoHIO_entry_c {
public:
    daAgb_HIO_c();
    virtual ~daAgb_HIO_c() {}

    /* 0x04 */ J3DGXColorS10 field_0x04[2];
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
};

class msg_class;
class dMsgCtrl_c {
public:
    int init(u16);
    int execute();
    ~dMsgCtrl_c() {}

    /* 0x00 */ u16 field_0x0;
    /* 0x04 */ u32 mMsgID;
    /* 0x08 */ msg_class* mpMsg;
};

class daAgb_c : public fopAc_ac_c {
public:
    // daAgb_BmRp_c struct?

    void NameConv();
    int uploadInitCheck();
    int uploadPortCheckWait();
    int uploadSelect();
    int uploadJoyboot1();
    int uploadJoyboot2();
    int uploadMessageLoad();
    int uploadMessageLoad2();
    int uploadConnect();
    int uploadMessageSend();
    int uploadRetryWait();
    int uploadMsgEndWait();
    int uploadMsgEndTimer();
    void modeLoad();
    void modeLookAttention();
    u8 DungeonNoGet();
    void MapNoSet(u8, u8, u8);
    void onFree();
    void onHold();
    void offHold();
    void resetCursor(bool);
    bool FlashCheck();
    void FlagsRecv();
    void SwitchOn();
    void GbaItemUse();
    void Shopping();
    void FlagsSend(u32);
    void CursorMove(fopAc_ac_c*, u32);
    void modeMove();
    void modeDelete();
    int createHeap();

    daAgb_c();

    inline void modeProcCall();
    
    BOOL isMsgSend() { return mIsMsgSend; }
    BOOL isActive() { return mIsActive; }
    void onActive() { mIsActive = true; }
    void offActive() { mIsActive = false; }
    void onBombDeny() { mBombDeny = true; }
    void offBombDeny() { mBombDeny = false; }
    void setDenyMessage(u16 msg) { mDenyMessage = msg; }
    BOOL isFree() { return mIsFree; }
    void offFree() {}
    void isHold() {}
    s32 getFollowTarget() { return mFollowTarget; }
    void setFollowTarget(bool) {}
    void getTargetID() {}
    void setTargetID(unsigned int) {}

    struct daAgb_ItemBuy {
        /* 0x0 */ u8 field_0x0;
        /* 0x1 */ u8 field_0x1;
    } ALIGN_DECL(4);

    struct daAgb_GbaFlg {
        /* 0x0 */ u16 field_0x0;
        /* 0x2 */ struct {
            u8 m7 : 1;
            u8 m6 : 1;
            u8 m5 : 1;
            u8 m4 : 1;
            u8 m3 : 1;
            u8 m2 : 1;
            u8 m1 : 1;
            u8 m0 : 1;
        } field_0x2;
        /* 0x3 */ u8 field_0x3;
        /* 0x4 */ u16 field_0x4;
        /* 0x6 */ u16 field_0x6;
    };

    struct daAgb_Switch {
        /* 0x0 */ u8 field_0x0;
        /* 0x1 */ u8 field_0x1;
        /* 0x1 */ u8 field_0x2;
        /* 0x3 */ u8 field_0x3;
        /* 0x4 */ u8 field_0x4;
        u8 field_0x5[0x8 - 0x5];
    };

    struct daAgb_Item {
        /* 0x0 */ u8 field_0x0;
        /* 0x1 */ u8 field_0x1;
    } ALIGN_DECL(4);

    struct daAgb_Shop {
        /* 0x0 */ u8 field_0x0;
        /* 0x1 */ u8 field_0x1;
        /* 0x2 */ u8 field_0x2;
    } ALIGN_DECL(4);

    static int mEffect;
    static daAgb_ItemBuy mItemBuy;
    static daAgb_GbaFlg mGbaFlg;
    static daAgb_Switch mSwitch;
    static daAgb_Item mItem;
    static daAgb_Shop mShop;
    static u8 DungeonNoTable[];

    struct daAgb_Flags {
        /* 0x0 */ u16 field_0x0;
        /* 0x2 */ u8 field_0x2;
        /* 0x3 */ u8 field_0x3_0 : 1;
        /* 0x3 */ u8 field_0x3_1 : 1;
        /* 0x3 */ u8 field_0x3_2 : 1;
        /* 0x3 */ u8 field_0x3_3 : 1;
        /* 0x3 */ u8 field_0x3_4 : 1;
        /* 0x3 */ u8 field_0x3_5 : 1;
        /* 0x3 */ u8 field_0x3_6 : 1;
        /* 0x3 */ u8 field_0x3_7 : 1;
        /* 0x4 */ u8 field_0x4;
        /* 0x5 */ u8 field_0x5_0 : 1;
        /* 0x5 */ u8 field_0x5_1 : 1;
        /* 0x5 */ u8 field_0x5_2 : 1;
        /* 0x5 */ u8 field_0x5_3 : 3;
        /* 0x5 */ u8 field_0x5_6 : 1;
        /* 0x5 */ u8 field_0x5_7 : 1;
        /* 0x6 */ u8 field_0x6;
        /* 0x7 */ u8 field_0x7;
        /* 0x8 */ u8 field_0x8;
        /* 0x9 */ u8 field_0x9;
        /* 0xA */ u8 field_0xa;
        /* 0xB */ u8 field_0xb_0 : 1;
        /* 0xB */ u8 field_0xb_3 : 5;
        /* 0xB */ u8 field_0xb_6 : 1;
        /* 0xB */ u8 field_0xb_7 : 1;
    };

    static daAgb_Flags mFlags;

    typedef int (daAgb_c::*uploadFunc)();
    static uploadFunc uploadFuncTable[];

    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_brkAnm mBrk;
    /* 0x2B4 */ GXTexObj mTexObj;
    /* 0x2D4 */ dBgS_LinkCrrPos mCrrPos;
    /* 0x424 */ dBgS_LinkAcch mAcch;
    /* 0x5E8 */ dBgS_AcchCir mAcchCir;
    /* 0x628 */ f32 field_0x628;
    /* 0x62C */ f32 field_0x62c;
    /* 0x630 */ u16 field_0x630;
    /* 0x632 */ u16 field_0x632;
#if VERSION == VERSION_JPN
    u8 jpn_padding[0x18];
#endif
    /* 0x634 */ cXyz field_0x634;
    /* 0x640 */ int field_0x640;
    /* 0x648 */ u64 mPlayerName;
    /* 0x650 */ u32 field_0x650;
    /* 0x654 */ int field_0x654;
    /* 0x658 */ u16 field_0x658;
    /* 0x65A */ u16 mPrevButtons;
    /* 0x65C */ u16 field_0x65c;
    /* 0x65E */ u16 field_0x65e;
    /* 0x660 */ u16 mDenyMessage;
    /* 0x662 */ u16 field_0x662;
    /* 0x664 */ u16 field_0x664;
    /* 0x666 */ u8 mPortNo;
    /* 0x667 */ u8 field_0x667[0x669 - 0x667];
    /* 0x669 */ u8 mMode;
    /* 0x66A */ u8 mUploadAction;
    /* 0x66B */ u8 field_0x66b;
    /* 0x66C */ u8 field_0x66c;
    /* 0x66D */ u8 field_0x66d;
    /* 0x66E */ u8 field_0x66e;
    /* 0x66F */ s8 field_0x66f;
    /* 0x670 */ u8 field_0x670;
    /* 0x671 */ bool mIsFree;
    /* 0x672 */ bool mIsActive;
    /* 0x673 */ u8 field_0x673;
    /* 0x674 */ u8 field_0x674;
    /* 0x675 */ u8 field_0x675;
    /* 0x676 */ u8 field_0x676;
    /* 0x677 */ u8 mFollowTarget;
    /* 0x678 */ bool mIsMsgSend;
    /* 0x679 */ u8 field_0x679;
    /* 0x67A */ bool field_0x67a;
    /* 0x67B */ u8 field_0x67b;
    /* 0x67C */ bool mBombDeny;
    /* 0x67D */ u8 field_0x67d;
    /* 0x67E */ u8 field_0x67e;
    /* 0x67F */ u8 field_0x67f;
    /* 0x680 */ u8 field_0x680;
    /* 0x684 */ dPa_followEcallBack field_0x684;
};

#endif /* D_A_AGB_H */