#ifndef D_A_NPC_MD_H
#define D_A_NPC_MD_H

#include "d/actor/d_a_player_npc.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_npc.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_drawlist.h"

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

class daNpc_Md_HIO_c : public JORReflexible {
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
    /* 0x08C */ dNpc_HIO_c mNpc;
    /* 0x0B4 */ fopAc_ac_c* mpActor;
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
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();

    JPABaseEmitter* getEmitter() { return mpEmitter; }
    cXyz& getPos() { return mPos; }
    void setAngle(s16 x, s16 y, s16 z) { mAngle.set(x, y, z); }

public:
    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ csXyz mAngle;
};  // Size: 0x1C

class daNpc_Md_c : public daPy_npc_c {
public:
    enum ActionStatus {
        ACTION_STARTING  = 0,
        ACTION_ONGOING_1 = 1,
        ACTION_ONGOING_2 = 2,
        ACTION_ONGOING_3 = 3,
        ACTION_ENDING    = -1,
    };
    
    typedef BOOL (daNpc_Md_c::*ActionFunc)(void*);
    typedef void (daNpc_Md_c::*EventActionInitFunc)(int evtStaffId);
    typedef BOOL (daNpc_Md_c::*EventActionFunc)(int evtStaffId);
    
    BOOL chkPlayerAction(ActionFunc func) { return mCurrPlayerActionFunc == func; }
    BOOL chkNpcAction(ActionFunc func) { return mCurrNpcActionFunc == func; }
    
    bool checkStatusFly() { return cLib_checkBit(m30F0, 0x10UL); }
    void onBitCamTagIn() { cLib_onBit(m30F0, 0x20UL); }
    void offBitCamTagIn() { cLib_offBit(m30F0, 0x20UL); }
    bool checkStatusCamTagIn() { return cLib_checkBit(m30F0, 0x20UL); }
    void onXYTalk() { cLib_onBit(m30F0, 0x100UL); }
    void offXYTalk() { cLib_offBit(m30F0, 0x100UL); }
    bool isXYTalk() { return cLib_checkBit(m30F0, 0x100UL); }
    void noCarryAction() { cLib_onBit(m30F0, 0x800UL); }
    void offNoCarryAction() { cLib_offBit(m30F0, 0x800UL); }
    bool isNoCarryAction() { return cLib_checkBit(m30F0, 0x800UL); }
    void onShipRide() { cLib_onBit(m30F0, 0x1000UL); }
    void offShipRide() { cLib_offBit(m30F0, 0x1000UL); }
    bool isShipRide() { return cLib_checkBit(m30F0, 0x1000UL); }
    void onLightHit() { cLib_onBit(m30F0, 0x2000UL); }
    void offLightHit() { cLib_offBit(m30F0, 0x2000UL); }
    bool isLightHit() { return cLib_checkBit(m30F0, 0x2000UL); }
    void onLightBodyHit() { cLib_onBit(m30F0, 0x8000UL); }
    void offLightBodyHit() { cLib_offBit(m30F0, 0x8000UL); }
    bool isLightBodyHit() { return cLib_checkBit(m30F0, 0x8000UL); }
    bool isOldLightBodyHit() { return cLib_checkBit(m30F0, 0x8000UL); }
    void onDefaultTalkXY() { cLib_onBit(m30F0, 0x10000UL); }
    void offDefaultTalkXY() { cLib_offBit(m30F0, 0x10000UL); }
    bool isDefaultTalkXY() { return cLib_checkBit(m30F0, 0x10000UL); }
    
    void setOldLightBodyHit() {} // 0x20000?
    
    void setTypeEdaichi() { mType = 4; }
    void setTypeM_Dai() { mType = 5; }
    void setTypeM_DaiB() { mType = 6; }
    void setTypeShipRide() { mType = 7; }
    bool isTypeAtorizk() { return mType == 0; }
    bool isTypeAdanmae() { return mType == 1; }
    bool isTypeM_Dra09() { return mType == 2; }
    bool isTypeSea() { return mType == 3; }
    bool isTypeEdaichi() { return mType == 4; }
    bool isTypeM_Dai() { return mType == 5; }
    bool isTypeM_DaiB() { return mType == 6; }
    bool isTypeShipRide() { return mType == 7; }
    
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    s16 getWaistRotX() { return m3114; }
    s16 getWaistRotY() { return m3116; }
    
    s8 getArmRJntNum() { return m_armR_jnt_num; }
    s8 getArmRlocJntNum() { return m_armRloc_jnt_num; }
    s8 getArmLJntNum() { return m_armL_jnt_num; }
    s8 getArmLlocJntNum() { return m_armLloc_jnt_num; }
    s8 getHairJntNum(int i) { return m_hair_jnt_nums[i]; }
    
    J3DModel* getModel() { return mpMorf->getModel(); }
    cXyz& getAttentionBasePos() { return m3094; }
    cXyz& getEyePos() { return m3088; }
    cXyz* getPHairPos(int i) { return &m3174[i]; }
    cXyz* getPHairVec(int i) { return &m31D4[i]; }
    f32* getPHairDist(int i) { return &m3264[i]; }
    cXyz* getPHairWall() { return m3234; }
    
    void incAttnSetCount() {
        if (m312B != 0xFF) {
            m312B++;
        }
    }
    
    u8 checkBitHairMode(u8 bit) { return m3134 & bit; }
    void setBitHairMode(u8 bit) { m3134 |= bit; }
    
    u8 getPiyo2TalkCNT() { return m313C & 0xFF; } // TODO: fakematch?
    void countPiyo2TalkCNT() {
        m313C++;
        if (m313C >= 3) {
            m313C = 0;
        }
    }
    
    void getFlyingTimer() {}
    void setFlyingTimer(s16) {}
    void calcFlyingTimer() {}
    void checkBitEffectStatus(u8) {}
    void checkStatus(u32) {}
    void setStatus(u32) {}
    void clearJntAng() {}
    void clearStatus() {}
    void clearStatus(u32) {}
    void getTalkType() {}
    void setTalkType(u8) {}
    void setBitEffectStatus(u8) {}
    void setBitStatus(u32) {}
    void setEffectStatus(u8) {}
    void setPiyo2TalkCNT(u8) {}
    void setRunRate(f32) {}
    
    daNpc_Md_c() {}
    ~daNpc_Md_c();
    
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    s32 create();
    BOOL createHeap();
    BOOL setAction(ActionFunc*, ActionFunc, void*);
    void npcAction(void*);
    void setNpcAction(ActionFunc, void* = NULL);
    void playerAction(void*);
    void setPlayerAction(ActionFunc, void* = NULL);
    s16 getStickAngY(int);
    int calcStickPos(s16, cXyz*);
    BOOL flyCheck();
    BOOL mirrorCancelCheck();
    void setWingEmitter();
    void setHane02Emitter();
    void deleteHane02Emitter();
    void setHane03Emitter();
    void deleteHane03Emitter();
    void returnLinkPlayer();
    BOOL shipRideCheck();
    BOOL isFallAction();
    BOOL returnLinkCheck();
    BOOL lightHitCheck();
    int wallHitCheck();
    void NpcCall(int*);
    BOOL checkCollision(int);
    void restartPoint(s16);
    void setMessageAnimation(u8);
    void waitGroundCheck();
    void chkAdanmaeDemoOrder();
    BOOL waitNpcAction(void*);
    BOOL harpWaitNpcAction(void*);
    BOOL XYTalkCheck();
    BOOL talkNpcAction(void*);
    BOOL shipTalkNpcAction(void*);
    BOOL kyohiNpcAction(void*);
    BOOL shipNpcAction(void*);
    BOOL mwaitNpcAction(void*);
    BOOL squatdownNpcAction(void*);
    BOOL sqwait01NpcAction(void*);
    void changeCaught02();
    BOOL carryNpcAction(void*);
    BOOL throwNpcAction(void*);
    BOOL glidingNpcAction(void*);
    void windProc();
    BOOL fallNpcAction(void*);
    BOOL fall02NpcAction(void*);
    BOOL wallHitNpcAction(void*);
    BOOL land01NpcAction(void*);
    BOOL land02NpcAction(void*);
    BOOL land03NpcAction(void*);
    BOOL piyo2NpcAction(void*);
    BOOL deleteNpcAction(void*);
    BOOL demoFlyNpcAction(void*);
    void routeAngCheck(cXyz&, s16*);
    void routeWallCheck(cXyz&, cXyz&, s16*);
    void checkForwardGroundY(s16);
    void checkWallJump(s16);
    void routeCheck(f32, s16*);
    BOOL searchNpcAction(void*);
    BOOL hitNpcAction(void*);
    void setNormalSpeedF(f32, f32, f32, f32, f32);
    void setSpeedAndAngleNormal(f32, s16);
    void walkProc(f32, s16);
    BOOL jumpNpcAction(void*);
    BOOL escapeNpcAction(void*);
    BOOL waitPlayerAction(void*);
    BOOL walkPlayerAction(void*);
    BOOL hitPlayerAction(void*);
    BOOL jumpPlayerAction(void*);
    BOOL flyPlayerAction(void*);
    BOOL landPlayerAction(void*);
    BOOL mkamaePlayerAction(void*);
    BOOL carryPlayerAction(void*);
    BOOL eventProc();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialWaitEvent(int);
    BOOL actionWaitEvent(int);
    void initialLetterEvent(int);
    void initialMsgSetEvent(int);
    BOOL actionMsgSetEvent(int);
    BOOL actionMsgEndEvent(int);
    void initialMovePosEvent(int);
    void initialFlyEvent(int);
    BOOL actionFlyEvent(int);
    void initialGlidingEvent(int);
    BOOL actionGlidingEvent(int);
    void initialLandingEvent(int);
    BOOL actionLandingEvent(int);
    void initialWalkEvent(int);
    BOOL actionWalkEvent(int);
    BOOL actionDashEvent(int);
    void initialEndEvent(int);
    BOOL actionTactEvent(int);
    void initialTakeOffEvent(int);
    BOOL actionTakeOffEvent(int);
    void initialOnetimeEvent(int);
    BOOL actionOnetimeEvent(int);
    void initialQuake(int);
    void setHarpPlayNum(int);
    void initialHarpPlayEvent(int);
    BOOL actionHarpPlayEvent(int);
    void initialOffLinkEvent(int);
    void initialOnLinkEvent(int);
    void initialTurnEvent(int);
    BOOL actionTurnEvent(int);
    void initialSetAnmEvent(int);
    void initialLookDown(int);
    void initialLookUp(int);
    BOOL actionLookDown(int);
    BOOL talk_init();
    BOOL talk(int);
    int getAnmType(u8);
    BOOL initTexPatternAnm(u8, bool);
    void playTexPatternAnm();
    BOOL initLightBtkAnm(bool);
    void playLightBtkAnm();
    BOOL setAnm(int);
    bool dNpc_Md_setAnm(mDoExt_McaMorf2*, f32, int, f32, f32, char*, char*, const char*);
    bool dNpc_Md_setAnm(mDoExt_McaMorf*, int, f32, f32, char*, const char*);
    void chkAttention(cXyz, s16, int);
    void chkArea(cXyz*);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void setAttention(bool);
    void lookBack(int, int, int);
    void lookBack(cXyz*, int, int);
    void lookBackWaist(s16, f32);
    void setBaseMtx();
    void deletePiyoPiyo();
    BOOL init();
    BOOL draw();
    void animationPlay();
    void checkPlayerRoom();
    BOOL execute();
    void particle_set(JPABaseEmitter**, u16);
    void emitterTrace(JPABaseEmitter*, MtxP, csXyz*);
    void emitterDelete(JPABaseEmitter**);
    
    virtual BOOL isTagCheckOK();
    virtual f32 getGroundY() { return mAcch.GetGroundH(); }
    virtual MtxP getLeftHandMatrix() { return cullMtx; }
    virtual MtxP getRightHandMatrix() { return cullMtx; }
    virtual f32 getBaseAnimeFrameRate() { return 1.0f; }
    virtual f32 getBaseAnimeFrame() { return 0.0f; }
    
    static bool m_flying;
    static bool m_mirror;
    static bool m_seaTalk;
    static s16 m_flyingTimer;
    static bool m_playerRoom;
    
    static bool isFlying() { return m_flying; }
    static void onFlying() { m_flying = true; }
    static void offFlying() { m_flying = false; }
    static bool isMirror() { return m_mirror; }
    static void onMirror() { m_mirror = true; }
    static void offMirror() { m_mirror = false; }
    static bool isSeaTalk() { return m_seaTalk; }
    static void onSeaTalk() { m_seaTalk = true; }
    static void offSeaTalk() { m_seaTalk = false; }
    static s16 getMaxFlyingTimer();
    static bool isPlayerRoom() { return m_playerRoom; }
    static void onPlayerRoom() { m_playerRoom = true; }
    static void offPlayerRoom() { m_playerRoom = false; }
    
public:
    /* 0x04EC */ request_of_phase_process_class mPhase;
    /* 0x04F4 */ J3DModel* mpHarpModel;
    /* 0x04F8 */ J3DModel* mpHarpLightModel;
    /* 0x04FC */ mDoExt_McaMorf2* mpMorf;
    /* 0x0500 */ mDoExt_McaMorf2* mpArmMorf;
    /* 0x0504 */ mDoExt_McaMorf* mpWingMorf;
    /* 0x0508 */ JPABaseEmitter* m0508[6];
    /* 0x0520 */ mDoExt_btpAnm m0520;
    /* 0x0534 */ mDoExt_btkAnm mLightBtkAnm;
    /* 0x0548 */ u32 mShadowId;
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
    /* 0x3088 */ cXyz m3088;
    /* 0x3094 */ cXyz m3094;
    /* 0x30A0 */ cXyz m30A0;
    /* 0x30AC */ u8 m30AC[0x30D0 - 0x30AC];
    /* 0x30D0 */ f32 m30D0;
    /* 0x30D4 */ ActionFunc mCurrPlayerActionFunc;
    /* 0x30E0 */ ActionFunc mCurrNpcActionFunc;
    /* 0x30EC */ u32 mMsgNo;
    /* 0x30F0 */ u32 m30F0;
    /* 0x30F4 */ u8 m30F4[0x30F8 - 0x30F4];
    /* 0x30F8 */ f32 m30F8;
    /* 0x30FC */ f32 m30FC;
    /* 0x3100 */ u8 m3100[0x3104 - 0x3100];
    /* 0x3104 */ int m3104;
    /* 0x3108 */ f32 m3108;
    /* 0x310C */ f32 m310C;
    /* 0x3110 */ s16 m3110;
    /* 0x3112 */ s16 m3112;
    /* 0x3114 */ s16 m3114;
    /* 0x3116 */ s16 m3116;
    /* 0x3118 */ s16 m3118;
    /* 0x311A */ s16 m311A;
    /* 0x311C */ s8 m_backbone1_jnt_num;
    /* 0x311D */ s8 m_backbone2_jnt_num;
    /* 0x311E */ s8 m_armR_jnt_num;
    /* 0x311F */ s8 m_armL_jnt_num;
    /* 0x3120 */ s8 m_armRloc_jnt_num;
    /* 0x3121 */ s8 m_armLloc_jnt_num;
    /* 0x3122 */ s8 m_wingRloc_jnt_num;
    /* 0x3123 */ s8 m_wingLloc_jnt_num;
    /* 0x3124 */ s8 m_neck_jnt_num;
    /* 0x3125 */ s8 m_wingR2_jnt_num;
    /* 0x3126 */ s8 m_wingL2_jnt_num;
    /* 0x3127 */ s8 m_wingR3_jnt_num;
    /* 0x3128 */ s8 m_wingL3_jnt_num;
    /* 0x3129 */ s8 m_handL_jnt_num;
    /* 0x312A */ s8 m312A;
    /* 0x312B */ u8 m312B;
    /* 0x312C */ u8 m312C;
    /* 0x312D */ s8 m312D;
    /* 0x312E */ s8 mCurEventMode;
    /* 0x312F */ u8 m312F[0x3131 - 0x312F];
    /* 0x3131 */ u8 m3131;
    /* 0x3132 */ s8 mActionStatus;
    /* 0x3133 */ u8 m3133;
    /* 0x3134 */ u8 m3134;
    /* 0x3135 */ u8 m3135[0x3136 - 0x3135];
    /* 0x3136 */ u8 m3136;
    /* 0x3137 */ u8 m3137;
    /* 0x3138 */ u8 mType;
    /* 0x3139 */ s8 mCurEvent;
    /* 0x313A */ u8 m313A;
    /* 0x313B */ u8 m313B[0x313C - 0x313B];
    /* 0x313C */ u8 m313C;
    /* 0x313D */ u8 m313D;
    /* 0x313E */ u8 m313E[0x3140 - 0x313E];
    /* 0x3140 */ bool m3140;
    /* 0x3141 */ u8 m3141[0x3144 - 0x3141];
    /* 0x3144 */ s16 m3144;
    /* 0x3146 */ s16 m3146;
    /* 0x3148 */ s16 m3148;
    /* 0x314A */ s16 m314A;
    /* 0x314C */ s16 m314C;
    /* 0x314E */ u8 m314E[0x3150 - 0x314E];
    /* 0x3150 */ f32 m3150;
    /* 0x3154 */ u8 m3154[0x3158 - 0x3154];
    /* 0x3158 */ s16 mEventIdxTable[10];
    /* 0x316C */ s8 m_hair_jnt_nums[8];
    /* 0x3174 */ cXyz m3174[8];
    /* 0x31D4 */ cXyz m31D4[8];
    /* 0x3234 */ cXyz m3234[4];
    /* 0x3264 */ f32 m3264[8];
    /* 0x3284 */ char mModelArcName[3];
    /* 0x3287 */ u8 m3287[0x32A4 - 0x3287];
    /* 0x32A4 */ cXyz m32A4;
    /* 0x32B0 */ cBgS_PolyInfo mPolyInfo;
};

#endif /* D_A_NPC_MD_H */
