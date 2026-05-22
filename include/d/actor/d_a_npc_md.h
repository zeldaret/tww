#ifndef D_A_NPC_MD_H
#define D_A_NPC_MD_H

#include "d/actor/d_a_player_npc.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_npc.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_drawlist.h"

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
    
    enum daNpc_Md_StatusBit_e {
        daMdStts_UNK1            = 0x00000001,
        daMdStts_UNK2            = 0x00000002,
        daMdStts_UNK4            = 0x00000004,
        daMdStts_UNK8            = 0x00000008,
        daMdStts_FLY             = 0x00000010,
        daMdStts_CAM_TAG_IN      = 0x00000020,
        daMdStts_UNK40           = 0x00000040,
        daMdStts_UNK80           = 0x00000080,
        daMdStts_XY_TALK         = 0x00000100,
        daMdStts_UNK200          = 0x00000200,
        daMdStts_UNK400          = 0x00000400,
        daMdStts_CARRY_ACTION    = 0x00000800,
        daMdStts_SHIP_RIDE       = 0x00001000,
        daMdStts_LIGHT_HIT       = 0x00002000,
        daMdStts_UNK4000         = 0x00004000,
        daMdStts_LIGHT_BODY_HIT  = 0x00008000,
        daMdStts_DEFAULT_TALK_XY = 0x00010000,
        daMdStts_UNK20000        = 0x00020000,
    };
    
    typedef BOOL (daNpc_Md_c::*ActionFunc)(void*);
    typedef void (daNpc_Md_c::*EventActionInitFunc)(int evtStaffId);
    typedef BOOL (daNpc_Md_c::*EventActionFunc)(int evtStaffId);
    
    BOOL chkPlayerAction(ActionFunc func) { return mCurrPlayerActionFunc == func; }
    BOOL chkNpcAction(ActionFunc func) { return mCurrNpcActionFunc == func; }
    
    void setBitStatus(u32 status) { cLib_onBit<u32>(m30F0, status); }
    void clearStatus(u32 status) { cLib_offBit<u32>(m30F0, status); }
    bool checkStatus(u32 status) { return cLib_checkBit<u32>(m30F0, status); }
    void setStatus(u32 status) { m30F0 = status; }
    void clearStatus() { m30F0 = 0; }
    bool checkStatusFly() { return cLib_checkBit<u32>(m30F0, daMdStts_FLY); }
    void onBitCamTagIn() { cLib_onBit<u32>(m30F0, daMdStts_CAM_TAG_IN); }
    void offBitCamTagIn() { cLib_offBit<u32>(m30F0, daMdStts_CAM_TAG_IN); }
    bool checkStatusCamTagIn() { return cLib_checkBit<u32>(m30F0, daMdStts_CAM_TAG_IN); }
    void onXYTalk() { cLib_onBit<u32>(m30F0, daMdStts_XY_TALK); }
    void offXYTalk() { cLib_offBit<u32>(m30F0, daMdStts_XY_TALK); }
    bool isXYTalk() { return cLib_checkBit<u32>(m30F0, daMdStts_XY_TALK); }
    void noCarryAction() { cLib_onBit<u32>(m30F0, daMdStts_CARRY_ACTION); }
    void offNoCarryAction() { cLib_offBit<u32>(m30F0, daMdStts_CARRY_ACTION); }
    bool isNoCarryAction() { return cLib_checkBit<u32>(m30F0, daMdStts_CARRY_ACTION); }
    void onShipRide() { cLib_onBit<u32>(m30F0, daMdStts_SHIP_RIDE); }
    void offShipRide() { cLib_offBit<u32>(m30F0, daMdStts_SHIP_RIDE); }
    bool isShipRide() { return cLib_checkBit<u32>(m30F0, daMdStts_SHIP_RIDE); }
    void onLightHit() { cLib_onBit<u32>(m30F0, daMdStts_LIGHT_HIT); }
    void offLightHit() { cLib_offBit<u32>(m30F0, daMdStts_LIGHT_HIT); }
    bool isLightHit() { return cLib_checkBit<u32>(m30F0, daMdStts_LIGHT_HIT); }
    void onLightBodyHit() { cLib_onBit<u32>(m30F0, daMdStts_LIGHT_BODY_HIT); }
    void offLightBodyHit() { cLib_offBit<u32>(m30F0, daMdStts_LIGHT_BODY_HIT); }
    bool isLightBodyHit() { return cLib_checkBit<u32>(m30F0, daMdStts_LIGHT_BODY_HIT); }
    void onDefaultTalkXY() { cLib_onBit<u32>(m30F0, daMdStts_DEFAULT_TALK_XY); }
    void offDefaultTalkXY() { cLib_offBit<u32>(m30F0, daMdStts_DEFAULT_TALK_XY); }
    bool isDefaultTalkXY() { return cLib_checkBit<u32>(m30F0, daMdStts_DEFAULT_TALK_XY); }
    
    bool isOldLightBodyHit() { return mOldLightBodyHit; }
    void setOldLightBodyHit() { mOldLightBodyHit = isLightBodyHit(); }
    
    void setTypeEdaichi() { mType = 4; }
    void setTypeM_Dai() { mType = 5; }
    void setTypeM_DaiB() { mType = 6; }
    void setTypeShipRide() { mType = 7; }
    BOOL isTypeAtorizk() { return mType == 0; }
    BOOL isTypeAdanmae() { return mType == 1; }
    BOOL isTypeM_Dra09() { return mType == 2; }
    BOOL isTypeSea() { return mType == 3; }
    BOOL isTypeEdaichi() { return mType == 4; }
    BOOL isTypeM_Dai() { return mType == 5; }
    BOOL isTypeM_DaiB() { return mType == 6; }
    BOOL isTypeShipRide() { return mType == 7; }
    
    s16 getHead_x() { return mJntCtrl.mAngles[0][0]; }
    s16 getHead_y() { return mJntCtrl.mAngles[0][1]; }
    s16 getBackbone_x() { return mJntCtrl.mAngles[1][0]; }
    s16 getBackbone_y() { return mJntCtrl.mAngles[1][1]; }
    s16 getWaistRotX() { return m3114; }
    s16 getWaistRotY() { return m3116; }
    void clearJntAng() {     
        mJntCtrl.mAngles[0][1] = 0; // Head_y
        mJntCtrl.mAngles[0][0] = 0; // Head_x
        mJntCtrl.mAngles[1][1] = 0; // BackBone_y
        mJntCtrl.mAngles[1][0] = 0; // BackBone_x
    }
    
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
    
    void setRunRate(f32 rate) {
        mRunRate = rate;
        mpMorf->setAnmRate(mRunRate);
        mpArmMorf->setAnmRate(mRunRate);
    }
    
    s16 getFlyingTimer() { return m_flyingTimer; }
    void setFlyingTimer(s16 value) {  m_flyingTimer = value; }
    void calcFlyingTimer() { cLib_calcTimer(&m_flyingTimer); }
    u8 checkBitEffectStatus(u8 bit) { return m3135 & bit; }
    u8 getTalkType() { return mType; }
    void setTalkType(u8 type) { mType = type; }
    void setBitEffectStatus(u8 bit) { cLib_onBit<u8>(m3135, bit); }
    void setEffectStatus(u8 status) { m3135 = status; }
    void setPiyo2TalkCNT(u8 cnt) { m313C = cnt; }
    
    ~daNpc_Md_c();
    
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    cPhs_State create();
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
    BOOL chkAdanmaeDemoOrder();
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
    s16 windProc();
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
    f32 checkForwardGroundY(s16);
    f32 checkWallJump(s16);
    BOOL routeCheck(f32, s16*);
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
    bool chkAttention(cXyz, s16, int);
    bool chkArea(cXyz*);
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
    s32 lookBackWaist(s16, f32);
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
    /* 0x30AC */ cXyz m30AC;
    /* 0x30B8 */ cXyz m30B8;
    /* 0x30C4 */ cXyz m30C4;
    /* 0x30D0 */ f32 m30D0;
    /* 0x30D4 */ ActionFunc mCurrPlayerActionFunc;
    /* 0x30E0 */ ActionFunc mCurrNpcActionFunc;
    /* 0x30EC */ u32 mMsgNo;
    /* 0x30F0 */ u32 m30F0;
    /* 0x30F4 */ u32 m30F4;
    /* 0x30F8 */ f32 m30F8;
    /* 0x30FC */ f32 mRunRate;
    /* 0x3100 */ int m3100;
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
    /* 0x312F */ u8 m312F;
    /* 0x3130 */ u8 m3130;
    /* 0x3131 */ u8 m3131;
    /* 0x3132 */ s8 mActionStatus;
    /* 0x3133 */ u8 m3133;
    /* 0x3134 */ u8 m3134;
    /* 0x3135 */ u8 m3135;
    /* 0x3136 */ u8 m3136;
    /* 0x3137 */ u8 m3137;
    /* 0x3138 */ u8 mType;
    /* 0x3139 */ s8 mCurEvent;
    /* 0x313A */ u8 m313A;
    /* 0x313B */ u8 m313B[0x313C - 0x313B];
    /* 0x313C */ u8 m313C;
    /* 0x313D */ u8 m313D;
    /* 0x313E */ u8 m313E;
    /* 0x313F */ s8 m313F;
    /* 0x3140 */ bool mOldLightBodyHit;
    /* 0x3141 */ u8 m3141[0x3144 - 0x3141];
    /* 0x3144 */ s16 m3144;
    /* 0x3146 */ s16 m3146;
    /* 0x3148 */ s16 m3148;
    /* 0x314A */ s16 m314A;
    /* 0x314C */ s16 m314C;
    /* 0x314E */ s16 m314E;
    /* 0x3150 */ f32 m3150;
    /* 0x3154 */ f32 m3154;
    /* 0x3158 */ s16 mEventIdxTable[10];
    /* 0x316C */ s8 m_hair_jnt_nums[8];
    /* 0x3174 */ cXyz m3174[8];
    /* 0x31D4 */ cXyz m31D4[8];
    /* 0x3234 */ cXyz m3234[4];
    /* 0x3264 */ f32 m3264[8];
    /* 0x3284 */ char mModelArcName[3];
    /* 0x3287 */ u8 m3287[0x3298 - 0x3287];
    /* 0x3298 */ cXyz m3298;
    /* 0x32A4 */ cXyz m32A4;
    /* 0x32B0 */ cBgS_PolyInfo mPolyInfo;
};

#endif /* D_A_NPC_MD_H */
