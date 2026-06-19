#ifndef D_A_NPC_PHOTO_H
#define D_A_NPC_PHOTO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"

struct sPhotoAnmDat {
    /* 0x00 */ u8 field_0x00;
    /* 0x01 */ u8 field_0x01;
    /* 0x02 */ u8 field_0x02;
};

class daNpcPhoto_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_RAIL_ID_W = 0x8,
        PRM_RAIL_ID_S = 0x10,

        PRM_ARG0_W = 0x8,
        PRM_ARG0_S = 0x0,
    };

    request_of_phase_process_class* getPhaseP() { return &mPhs1; }
    void incMsgTbl() {}
    bool isDate() { return field_0x9C1 == 4; }
    void nullMsgTbl() {}
    void setMsgTbl(unsigned long*, signed char*) {}
    void setPosFlag(unsigned char) {}
    void setResFlag(unsigned char) {}

    daNpcPhoto_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    bool executeCommon();
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
    bool eventMesSet();
    void eventSeSetInit(int);
    void eventPosSetInit();
    void eventGetItemInit();
    bool eventGetItem();
    void eventSetAngleInit();
    void eventSetEyeInit();
    bool eventSetEye();
    void eventTurnToPlayerInit();
    bool eventTurnToPlayer();
    void eventClrHanmeInit();
    void eventGetPhotoInit();
    bool eventGetPhoto();
    void eventMesSetUbInit(int);
    bool eventMesSetUb();
    bool eventLookUb();
    u16 talk2(int);
    void setMsgCamera();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmRailID();
    u8 getPrmArg0();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool, int);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sPhotoAnmDat*);
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    BOOL isPhotoOk();
    BOOL isPhotoDxOk();
    void setCollision(dCcD_Cyl*, cXyz, float, float);

    static const char m_arcname[4];

public:
    typedef void(daNpcPhoto_c::*MoveFunc_t)();

    /* 0x6C4 */ request_of_phase_process_class mPhs1;
    /* 0x6CC */ request_of_phase_process_class mPhs2;
    /* 0x6D4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u32 mShadowId;
    /* 0x6F0 */ dNpc_PathRun_c mPathRun;
    /* 0x6F8 */ dCcD_Cyl field_0x6F8[2];
    /* 0x958 */ cXyz field_0x958;
    /* 0x964 */ cXyz mLookAtPos;
    /* 0x970 */ cXyz mEyePos;
    /* 0x97C */ sPhotoAnmDat* mpAnmDat;
    /* 0x980 */ u32* field_0x980;
    /* 0x984 */ f32 field_0x984;
    /* 0x988 */ f32 field_0x988;
    /* 0x98C */ f32 field_0x98C;
    /* 0x990 */ int mMsgNno;
    /* 0x994 */ bool field_0x994;
    /* 0x996 */ s16 mPhotoLinkBackEventIdx;
    /* 0x998 */ s16 mPhotoGetItemEventIdx;
    /* 0x99A */ s16 mPhotoGetItem2EventIdx;
    /* 0x99C */ s16 mPhotoGetPhotoEventIdx;
    /* 0x99E */ s16 mPhotoGalleryEventIdx;
    /* 0x9A0 */ s16 mPhotoCounterTalk0EventIdx;
    /* 0x9A2 */ s16 mPhotoCounterTalk1EventIdx;
    /* 0x9A4 */ s16 mPhotoDateUB4EventIdx;
    /* 0x9A6 */ s16 field_0x9A6;
    /* 0x9A8 */ s16 field_0x9A8;
    /* 0x9AA */ u8 field_0x9AA[0x9AC - 0x9AA];
    /* 0x9AC */ s16 field_0x9AC;
    /* 0x9AE */ s16 field_0x9AE;
    /* 0x9B0 */ s16 field_0x9B0;
    /* 0x9B2 */ s16 field_0x9B2;
    /* 0x9B4 */ s16 mTimer;
    /* 0x9B6 */ s16 field_0x9B6;
    /* 0x9B8 */ s16 field_0x9B8;
    /* 0x9BA */ s16 field_0x9BA;
    /* 0x9BC */ bool field_0x9BC;
    /* 0x9BD */ bool field_0x9BD;
    /* 0x9BE */ u8 field_0x9BE;
    /* 0x9BF */ u8 mFrame;
    /* 0x9C0 */ u8 field_0x9C0;
    /* 0x9C1 */ u8 field_0x9C1;
    /* 0x9C2 */ bool field_0x9C2;
    /* 0x9C3 */ u8 field_0x9C3;
    /* 0x9C4 */ u8 field_0x9C4[0x9C5 - 0x9C4];
    /* 0x9C5 */ u8 mItemNo;
    /* 0x9C6 */ u8 field_0x9C6;
    /* 0x9C7 */ bool field_0x9C7;
    /* 0x9C8 */ u8 field_0x9C8;
    /* 0x9C9 */ u8 field_0x9C9;
    /* 0x9CA */ s8 field_0x9CA;
    /* 0x9CB */ s8 mActIdx;
    /* 0x9CC */ bool field_0x9CC;
    /* 0x9CD */ bool field_0x9CD;
    /* 0x9D0 */ u8* field_0x9D0;
    /* 0x9D4 */ bool field_0x9D4;
    /* 0x9D5 */ u8 field_0x9D5;
    /* 0x9D6 */ s8 field_0x9D6;
    /* 0x9D7 */ bool field_0x9D7;
    /* 0x9D8 */ bool field_0x9D8;
};  // Size: 0x9DC

#endif /* D_A_NPC_PHOTO_H */
