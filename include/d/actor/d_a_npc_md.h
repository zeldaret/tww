#ifndef D_A_NPC_MD_H
#define D_A_NPC_MD_H

#include "d/actor/d_a_player_npc.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_npc.h"
#include "d/d_bg_s_lin_chk.h"

class daNpc_Md_HIO2_c {
public:
    daNpc_Md_HIO2_c();
    virtual ~daNpc_Md_HIO2_c() {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ s16 m20;
    /* 0x22 */ s16 m22;
    /* 0x24 */ s16 m24;
    /* 0x26 */ s16 m26;
    /* 0x28 */ s16 m28;
    /* 0x2A */ s16 m2A;
};

class daNpc_Md_HIO3_c {
public:
    daNpc_Md_HIO3_c();
    virtual ~daNpc_Md_HIO3_c() {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ s16 m18;
    /* 0x1A */ s16 m1A;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ s16 m20;
    /* 0x22 */ s16 m22;
    /* 0x24 */ s16 m24;
    /* 0x26 */ u8 field_26[0x28 - 0x26];
};

class daNpc_Md_HIO4_c {
public:
    daNpc_Md_HIO4_c();
    virtual ~daNpc_Md_HIO4_c() {}

public:
    /* 0x4 */ f32 m4;
    /* 0x8 */ s16 m8;
    /* 0xA */ u8 field_A[0xC - 0xA];
};

class daNpc_Md_HIO5_c {
public:
    daNpc_Md_HIO5_c();
    virtual ~daNpc_Md_HIO5_c() {}

public:
    /* 0x4 */ f32 m4;
    /* 0x8 */ f32 m8;
};

class daNpc_Md_HIO6_c {
public:
    daNpc_Md_HIO6_c();
    virtual ~daNpc_Md_HIO6_c() {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ s16 m0E;
    /* 0x10 */ s16 m10;
    /* 0x12 */ s16 m12;
    /* 0x14 */ s16 m14;
    /* 0x16 */ s16 m16;
};

class daNpc_Md_HIO_c {
public:
    daNpc_Md_HIO_c();
    virtual ~daNpc_Md_HIO_c() {}

public:
    /* 0x004 */ s8 mChildID;
    /* 0x005 */ u8 m005[0x008 - 0x005];
    /* 0x008 */ daNpc_Md_HIO2_c m008;
    /* 0x034 */ daNpc_Md_HIO3_c m034;
    /* 0x05C */ daNpc_Md_HIO4_c m05C;
    /* 0x068 */ daNpc_Md_HIO5_c m068;
    /* 0x074 */ daNpc_Md_HIO6_c m074;
    /* 0x08C */ dNpc_HIO_c m08C;
    /* 0x0B4 */ int m0B4;
    /* 0x0B8 */ f32 m0B8;
    /* 0x0BC */ f32 m0BC;
    /* 0x0C0 */ f32 m0C0;
    /* 0x0C4 */ f32 m0C4;
    /* 0x0C8 */ f32 m0C8;
    /* 0x0CC */ f32 m0CC;
    /* 0x0D0 */ f32 m0D0;
    /* 0x0D4 */ f32 m0D4;
    /* 0x0D8 */ f32 m0D8;
    /* 0x0DC */ f32 m0DC;
    /* 0x0E0 */ f32 m0E0;
    /* 0x0E4 */ f32 m0E4;
    /* 0x0E8 */ f32 m0E8;
    /* 0x0EC */ f32 m0EC;
    /* 0x0F0 */ f32 m0F0;
    /* 0x0F4 */ f32 m0F4;
    /* 0x0F8 */ f32 m0F8;
    /* 0x0FC */ f32 m0FC;
    /* 0x100 */ f32 m100;
    /* 0x104 */ f32 m104;
    /* 0x108 */ f32 m108;
    /* 0x10C */ f32 m10C;
    /* 0x110 */ f32 m110;
    /* 0x114 */ f32 m114;
    /* 0x118 */ f32 m118;
    /* 0x11C */ f32 m11C;
    /* 0x120 */ f32 m120;
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ f32 m12C;
    /* 0x130 */ f32 m130;
    /* 0x134 */ f32 m134;
    /* 0x138 */ f32 m138;
    /* 0x13C */ f32 m13C;
    /* 0x140 */ f32 m140;
    /* 0x144 */ f32 m144;
    /* 0x148 */ f32 m148;
    /* 0x14C */ f32 m14C;
    /* 0x150 */ f32 m150;
    /* 0x154 */ f32 m154;
    /* 0x158 */ f32 m158;
    /* 0x15C */ f32 m15C;
    /* 0x160 */ f32 m160;
    /* 0x164 */ f32 m164;
    /* 0x168 */ f32 m168;
    /* 0x16C */ f32 m16C;
    /* 0x170 */ f32 m170;
    /* 0x174 */ f32 m174;
    /* 0x178 */ f32 m178;
    /* 0x17C */ f32 m17C;
    /* 0x180 */ f32 m180;
    /* 0x184 */ f32 m184;
    /* 0x188 */ f32 m188;
    /* 0x18C */ f32 m18C;
    /* 0x190 */ f32 m190;
    /* 0x194 */ f32 m194;
    /* 0x198 */ f32 m198;
    /* 0x19C */ f32 m19C;
    /* 0x1A0 */ f32 m1A0;
    /* 0x1A4 */ f32 m1A4;
    /* 0x1A8 */ f32 m1A8;
    /* 0x1AC */ f32 m1AC;
    /* 0x1B0 */ f32 m1B0;
    /* 0x1B4 */ s16 m1B4;
    /* 0x1B6 */ u16 m1B6;
    /* 0x1B8 */ u16 m1B8;
    /* 0x1BA */ u16 m1BA;
    /* 0x1BC */ u16 m1BC;
    /* 0x1BE */ u16 m1BE;
    /* 0x1C0 */ u16 m1C0;
    /* 0x1C2 */ u16 m1C2;
    /* 0x1C4 */ s16 m1C4;
    /* 0x1C6 */ u8 m1C6;
    /* 0x1C7 */ u8 m1C7;
    /* 0x1C8 */ u8 m1C8;
    /* 0x1C9 */ u8 field_1C9[0x1CC - 0x1C9];
};

class daNpc_Md_followEcallBack_c : public dPa_levelEcallBack {
public:
    ~daNpc_Md_followEcallBack_c() {}
    
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
    void end();

public:
    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ csXyz mAngle;
};  // Size: 0x1C

class daNpc_Md_c : public daPy_npc_c {
public:
    daNpc_Md_c() {}
    ~daNpc_Md_c();
    
    void XyCheckCB(int);
    void XyEventCB(int);
    s32 create();
    void createHeap();
    void setAction(int (daNpc_Md_c::**)(void*), int (daNpc_Md_c::*)(void*), void*);
    void npcAction(void*);
    void setNpcAction(int (daNpc_Md_c::*)(void*), void*);
    void playerAction(void*);
    void setPlayerAction(int (daNpc_Md_c::*)(void*), void*);
    void getStickAngY(int);
    void calcStickPos(short, cXyz*);
    void flyCheck();
    void mirrorCancelCheck();
    void setWingEmitter();
    void setHane02Emitter();
    void deleteHane02Emitter();
    void setHane03Emitter();
    void deleteHane03Emitter();
    void returnLinkPlayer();
    void shipRideCheck();
    void isFallAction();
    void returnLinkCheck();
    void lightHitCheck();
    void wallHitCheck();
    void NpcCall(int*);
    void checkCollision(int);
    void restartPoint(short);
    void setMessageAnimation(unsigned char);
    void waitGroundCheck();
    void chkAdanmaeDemoOrder();
    void waitNpcAction(void*);
    void harpWaitNpcAction(void*);
    void XYTalkCheck();
    void talkNpcAction(void*);
    void shipTalkNpcAction(void*);
    void kyohiNpcAction(void*);
    void shipNpcAction(void*);
    void mwaitNpcAction(void*);
    void squatdownNpcAction(void*);
    void sqwait01NpcAction(void*);
    void changeCaught02();
    void carryNpcAction(void*);
    void throwNpcAction(void*);
    void glidingNpcAction(void*);
    void windProc();
    void fallNpcAction(void*);
    void fall02NpcAction(void*);
    void wallHitNpcAction(void*);
    void land01NpcAction(void*);
    void land02NpcAction(void*);
    void land03NpcAction(void*);
    void piyo2NpcAction(void*);
    void deleteNpcAction(void*);
    void demoFlyNpcAction(void*);
    void routeAngCheck(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    void checkForwardGroundY(short);
    void checkWallJump(short);
    void routeCheck(float, short*);
    void searchNpcAction(void*);
    void hitNpcAction(void*);
    void setNormalSpeedF(float, float, float, float, float);
    void setSpeedAndAngleNormal(float, short);
    void walkProc(float, short);
    void jumpNpcAction(void*);
    void escapeNpcAction(void*);
    void waitPlayerAction(void*);
    void walkPlayerAction(void*);
    void hitPlayerAction(void*);
    void jumpPlayerAction(void*);
    void flyPlayerAction(void*);
    void landPlayerAction(void*);
    void mkamaePlayerAction(void*);
    void carryPlayerAction(void*);
    void eventProc();
    void initialDefault(int);
    void actionDefault(int);
    void initialWaitEvent(int);
    void actionWaitEvent(int);
    void initialLetterEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMsgEndEvent(int);
    void initialMovePosEvent(int);
    void initialFlyEvent(int);
    void actionFlyEvent(int);
    void initialGlidingEvent(int);
    void actionGlidingEvent(int);
    void initialLandingEvent(int);
    void actionLandingEvent(int);
    void initialWalkEvent(int);
    void actionWalkEvent(int);
    void actionDashEvent(int);
    void initialEndEvent(int);
    void actionTactEvent(int);
    void initialTakeOffEvent(int);
    void actionTakeOffEvent(int);
    void initialOnetimeEvent(int);
    void actionOnetimeEvent(int);
    void initialQuake(int);
    void setHarpPlayNum(int);
    void initialHarpPlayEvent(int);
    void actionHarpPlayEvent(int);
    void initialOffLinkEvent(int);
    void initialOnLinkEvent(int);
    void initialTurnEvent(int);
    void actionTurnEvent(int);
    void initialSetAnmEvent(int);
    void initialLookDown(int);
    void initialLookUp(int);
    void actionLookDown(int);
    void talk_init();
    void talk(int);
    void getAnmType(unsigned char);
    void initTexPatternAnm(unsigned char, bool);
    void playTexPatternAnm();
    void initLightBtkAnm(bool);
    void playLightBtkAnm();
    void setAnm(int);
    void dNpc_Md_setAnm(mDoExt_McaMorf2*, float, int, float, float, char*, char*, const char*);
    void dNpc_Md_setAnm(mDoExt_McaMorf*, int, float, float, char*, const char*);
    void chkAttention(cXyz, short, int);
    void chkArea(cXyz*);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void setAttention(bool);
    void lookBack(int, int, int);
    void lookBack(cXyz*, int, int);
    void lookBackWaist(short, float);
    void setBaseMtx();
    void deletePiyoPiyo();
    void init();
    BOOL draw();
    void animationPlay();
    void checkPlayerRoom();
    BOOL execute();
    void particle_set(JPABaseEmitter**, unsigned short);
    void emitterTrace(JPABaseEmitter*, float(*)[4], csXyz*);
    void emitterDelete(JPABaseEmitter**);
    
    virtual BOOL isTagCheckOK();
    virtual f32 getGroundY() {}
    virtual MtxP getLeftHandMatrix() {}
    virtual MtxP getRightHandMatrix() {}
    virtual f32 getBaseAnimeFrameRate() {}
    virtual f32 getBaseAnimeFrame() {}

public:
    /* 0x04EC */ request_of_phase_process_class mPhs;
    /* 0x04F4 */ u8 m04F4[0x04FC - 0x04F4];
    /* 0x04FC */ mDoExt_McaMorf2* m04FC;
    /* 0x0500 */ u8 m0500[0x0520 - 0x0500];
    /* 0x0520 */ mDoExt_btpAnm m0520;
    /* 0x0534 */ mDoExt_btkAnm m0534;
    /* 0x0548 */ u8 m0548[0x054C - 0x0548];
    /* 0x054C */ dBgS_AcchCir mAcchCir[2];
    /* 0x05CC */ dBgS_MirLightLinChk mLinChk;
    /* 0x0638 */ dCcD_Stts mStts;
    /* 0x0674 */ dCcD_Cyl mCyl1;
    /* 0x07A4 */ dCcD_Cyl mCyl2;
    /* 0x08D4 */ dCcD_Cyl mCyl3;
    /* 0x0A04 */ dCcD_Cps mCps;
    /* 0x0B3C */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x0B70 */ dDlst_mirrorPacket m0B70;
    /* 0x304C */ daPy_mtxFollowEcallBack_c m304C;
    /* 0x3058 */ daNpc_Md_followEcallBack_c m3058;
    /* 0x3074 */ dPa_rippleEcallBack m3074;
    /* 0x3088 */ u8 m3088[0x30A0 - 0x3088];
    /* 0x30A0 */ cXyz m30A0;
    /* 0x30AC */ u8 m30AC[0x30EC - 0x30AC];
    /* 0x30EC */ int mMsgId;
    /* 0x30F0 */ u32 m30F0;
    /* 0x30F4 */ u8 m30F4[0x30F8 - 0x30F4];
    /* 0x30F8 */ f32 m30F8;
    /* 0x30FC */ u8 m30FC[0x3104 - 0x30FC];
    /* 0x3104 */ int m3104;
    /* 0x3108 */ u8 m3108[0x3120 - 0x3108];
    /* 0x3120 */ u8 mArmRlocJointIdx;
    /* 0x3121 */ u8 mArmLlocJointIdx;
    /* 0x3122 */ u8 mWingRlocJointIdx;
    /* 0x3123 */ u8 mWingLlocJointIdx;
    /* 0x3124 */ u8 mNeckJointIdx;
    /* 0x3125 */ u8 mWingR2JointIdx;
    /* 0x3126 */ u8 mWingL2JointIdx;
    /* 0x3127 */ u8 mWingR3JointIdx;
    /* 0x3128 */ u8 mWingL3JointIdx;
    /* 0x3129 */ u8 mHandLJointIdx;
    /* 0x312A */ u8 m312A;
    /* 0x312B */ u8 m312B[0x312C - 0x312B];
    /* 0x312C */ u8 m312C;
    /* 0x312D */ u8 m312D[0x312E - 0x312D];
    /* 0x312E */ u8 mCurEventMode;
    /* 0x312F */ u8 m312F[0x3131 - 0x312F];
    /* 0x3131 */ u8 m3131;
    /* 0x3132 */ u8 m3132;
    /* 0x3133 */ u8 m3133[0x3138 - 0x3133];
    /* 0x3138 */ u8 m3138;
    /* 0x3139 */ u8 mCurEvent;
    /* 0x313A */ u8 m313A;
    /* 0x313B */ u8 m313B[0x3148 - 0x313B];
    /* 0x3148 */ s16 m3148;
    /* 0x314A */ s16 m314A;
    /* 0x314C */ s16 m314C;
    /* 0x314E */ u8 m314E[0x3158 - 0x314E];
    /* 0x3158 */ s16 mEventIdxTable[10];
    /* 0x316C */ u8 m316C[0x3174 - 0x316C];
    /* 0x3174 */ cXyz m3174[8];
    /* 0x31D4 */ cXyz m31D4[8];
    /* 0x3234 */ cXyz m3234[4];
    /* 0x3264 */ u8 m3264[0x3284 - 0x3264];
    /* 0x3284 */ char mModelArcName[3];
    /* 0x3287 */ u8 m3287[0x32A4 - 0x3287];
    /* 0x32A4 */ cXyz m32A4;
    /* 0x32B0 */ cBgS_PolyInfo mPolyInfo;
};

#endif /* D_A_NPC_MD_H */
