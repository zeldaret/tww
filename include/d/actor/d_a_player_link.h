#ifndef D_A_PLAYER_LINK
#define D_A_PLAYER_LINK

#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_attention.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_drawlist.h"
#include "d/d_bg_w.h"
#include "d/actor/d_a_player.h"

class mDoExt_MtxCalcOldFrame;

class daPy_anmHeap_c {
public:
    /* 0x0 */ u16 mIdx;
    /* 0x2 */ u16 field_0x2;
    /* 0x4 */ u32 field_0x4;
    /* 0x8 */ void* m_buffer;
    /* 0xC */ JKRSolidHeap* mpAnimeHeap;
};

class daPy_sightPacket_c : public dDlst_base_c {
public:
    daPy_sightPacket_c() {}
    virtual void draw();
    virtual ~daPy_sightPacket_c() {}

    void setSight();
    void setSightImage(ResTIMG*);

    bool getDrawFlg() { return mDrawFlag; }
    void onDrawFlg() { mDrawFlag = true; }
    void offDrawFlg() { mDrawFlag = false; }
    void setPos(const cXyz* i_pos) { mPos = *i_pos; }

private:
    /* 0x04 */ bool mDrawFlag;
    /* 0x05 */ u8 field_0x5[3];
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ Mtx field_0x14;
    /* 0x44 */ ResTIMG* mpImg;
    /* 0x48 */ u8* mpData;
    /* 0x4C */ void* field_0x4c;
};

class daPy_actorKeep_c {
public:
    daPy_actorKeep_c() {}

    void setActor();
    void setData(fopAc_ac_c*);
    void clearData();

    u32 getID() const { return mID; }
    fopAc_ac_c* getActor() { return mActor; }

private:
    /* 0x0 */ u32 mID;
    /* 0x4 */ fopAc_ac_c* mActor;
};  // Size: 0x8

class daPy_footEffect_c {
public:
    ~daPy_footEffect_c() {}
    daPy_footEffect_c() {}
    
    /* 0x00 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x20 */ dPa_followEcallBack mFollowCb;
    /* 0x34 */ u8 field_0x34[0x4C - 0x34];
};

class daPy_fanSwingEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    ~daPy_fanSwingEcallBack_c() {}
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) {
        emitter->becomeImmortalEmitter();
        mpEmitter = emitter;
        field_0x4 = 0;
    }
    
    /* 0x4 */ int field_0x4;
    /* 0x8 */ JPABaseEmitter* mpEmitter;
};  // Size: 0xC

class daPy_waterDropPcallBack_c : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    void execute(JPABaseEmitter*, JPABaseParticle*);
    ~daPy_waterDropPcallBack_c() {}
    
    /* 0x4 */ u8 field_0x4[0x4];
    /* 0x8 */ dBgS_ObjGndChk field_0x8;
};

class daPy_swimTailEcallBack_c : public dPa_levelEcallBack {
public:
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void getMaxWaterY(JGeometry::TVec3<float>*);
    void remove();
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    ~daPy_swimTailEcallBack_c() {}
    daPy_swimTailEcallBack_c() {}

    /* 0x4 */ u8 field_0x4[0x24];
};  // Size: 0x28

STATIC_ASSERT(sizeof(daPy_swimTailEcallBack_c) == 0x28);

class daPy_followEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();
    ~daPy_followEcallBack_c() {}

    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ cXyz field_0x08;
    /* 0x14 */ u8 field_0x14[0x1C - 0x14];
};  // Size: 0x1C

class daPy_waterDropEcallBack_c : public daPy_followEcallBack_c {
public:
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();
    daPy_waterDropEcallBack_c() {}
    ~daPy_waterDropEcallBack_c() {}

    /* 0x1C */ u8 field_0x1C[0x4];
};  // Size: 0x20

class daPy_dmEcallBack_c : public daPy_mtxFollowEcallBack_c {
public:
    void execute(JPABaseEmitter*);
    ~daPy_dmEcallBack_c() {}
    daPy_dmEcallBack_c() {}
};  // Size: 0x0C

class daPy_mtxPosFollowEcallBack_c : public daPy_mtxFollowEcallBack_c {
public:
    void makeEmitterColor(u16, MtxP, const cXyz*, const csXyz*, const GXColor*, const GXColor*);
    void execute(JPABaseEmitter*);
    daPy_mtxPosFollowEcallBack_c() {}
    ~daPy_mtxPosFollowEcallBack_c() {}

    /* 0xC */ u8 field_0xC[0x4];
};  // Size: 0x10

class daPy_swBlur_c : public J3DPacket {
public:
    void initSwBlur(MtxP, int, float, int);
    void copySwBlur(MtxP, int);
    void draw();
    ~daPy_swBlur_c() {}

    /* 0x010 */ u8 field_0x010[0x014 - 0x010];
    /* 0x014 */ int field_0x014;
    /* 0x018 */ int field_0x018;
    /* 0x01C */ int mBlurColorType;
    /* 0x020 */ f32 field_0x020;
    /* 0x024 */ void* mpBlurPos;
    /* 0x028 */ cXyz field_0x028;
    /* 0x034 */ cXyz field_0x034[60];
    /* 0x304 */ cXyz field_0x304[60];
};

class daPy_footData_c {
public:
    ~daPy_footData_c();
    daPy_footData_c();
    
    /* 0x000 */ u8 field_0x000[0x034 - 0x000];
    /* 0x034 */ dBgS_LinkGndChk field_0x034;
    /* 0x088 */ u8 field_0x088[0x118 - 0x088];
};

struct daPy_aura_c {
    J3DModel* mpYaura00Model;
    f32 mFrame;
    
    void setModel(J3DModel* model) { mpYaura00Model = model; }
    J3DModel* getModel() { return mpYaura00Model; }
    void setFrame(f32 frame) { mFrame = frame; }
    f32 getFrame() { return mFrame; }
};

class daPy_anmIndex_c;

class daPy_lk_c : public daPy_py_c {
public:
    enum daPy_PROC {};

    enum daPy_HEAP_TYPE {};

    enum daPy_ANM {};

    enum daPy_UPPER {};

    enum {
        PART_UNDER_e = 0,
        PART_UPPER_e = 1,
    };

    enum {
        UNDER_MOVE0_e = 0,
    };

    void getBoomerangCatchPos() const;
    void getLineTopPos();
    void getHookshotRootPos() const;
    void seStartOnlyReverb(u32);
    void seStartMapInfo(u32);
    void seStartSwordCut(u32);
    void itemButton() const;
    void itemTrigger() const;
    void getReadyItem();
    void checkGroupItem(int, int);
    void checkSetItemTrigger(int, int);
    void auraJointCB0(int);
    void jointBeforeCB(int, J3DTransformInfo*, Quaternion*);
    void jointAfterCB(int, J3DTransformInfo*, Quaternion*);
    void jointCB0(int);
    void jointCB1();
    void setAnimeHeap(JKRSolidHeap*);
    void setItemHeap();
    void setBlurPosResource(u16);
    void getItemAnimeResource(u16);
    void getAnimeResource(daPy_anmHeap_c*, u16, u32);
    void getUnderUpperAnime(daPy_anmIndex_c const*, J3DAnmTransform**, J3DAnmTransform**, int, u32);
    void setTextureAnimeResource(J3DAnmTexPattern*, int);
    void loadTextureAnimeResource(u32, int);
    void checkBossBgm();
    void checkMabaAnimeBtp(int);
    void checkNormalFace();
    void setTextureAnime(u16, int);
    void setPriTextureAnime(u16, int);
    void resetPriTextureAnime();
    void setDemoTextureAnime(u16, u16, int, u16);
    void resetDemoTextureAnime();
    void setTextureScrollResource(J3DAnmTextureSRTKey*, int);
    void loadTextureScrollResource(u32, int);
    void playTextureAnime();
    void checkSightLine(f32, cXyz*);
    void setBootsModel(J3DModel**);
    void setItemModel();
    void checkUpperReadyAnime() const;
    void checkUpperReadyThrowAnime() const;
    void checkNoCollisionCorret();
    void setDrawHandModel();
    void entryDLSetLight(J3DModel*, u32);
    void updateDLSetLight(J3DModel*, u32);
    void hideHatAndBackle(J3DMaterial*);
    void drawMirrorLightModel();
    void drawShadow();
    void offBodyEffect();
    void onBodyEffect();
    BOOL draw();
    void setAtnList();
    void setActorPointer();
    void setTalkStatus();
    void setHintActor();
    void setDoStatusBasic();
    void setDoStatus();
    void getDirectionFromAngle(s16);
    void getDirectionFromShapeAngle();
    void getDirectionFromCurrentAngle();
    void setNormalSpeedF(f32, f32, f32, f32);
    void posMoveFromFootPos();
    void posMove();
    void setShapeAngleToAtnActor();
    void cancelItemUpperReadyAnime();
    void checkBodyAngleX(s16);
    void setBodyAngleToCamera();
    void setBodyAngleXReadyAnime();
    void setSpeedAndAngleNormal(s16);
    void setSpeedAndAngleAtn();
    void setSpeedAndAngleAtnBack();
    void setSpeedAndAngleAtnActor();
    void setFrameCtrl(J3DFrameCtrl*, u8, s16, s16, f32, f32);
    void checkAtnWaitAnime();
    void setBlendMoveAnime(f32);
    void setBlendAtnBackMoveAnime(f32);
    void setBlendAtnMoveAnime(f32);
    void setAnimeEquipSword(int);
    void setAnimeEquipSingleItem(u16);
    void setAnimeEquipItem();
    void setAnimeUnequipSword();
    void setAnimeUnequipItem(u16);
    void setAnimeUnequip();
    void checkBossGomaStage();
    void checkSingleItemEquipAnime() const;
    void checkItemEquipAnime() const;
    void checkEquipAnime() const;
    void deleteEquipItem(int);
    void setFallVoice();
    void keepItemData();
    void returnKeepItemData();
    void makeItemType();
    void setScopeModel();
    void setPhotoBoxModel();
    void changeDragonShield(int);
    void checkNewItemChange(u8);
    void checkItemChangeFromButton();
    void checkItemAction();
    void getSlidePolygon();
    void checkJumpCutFromButton();
    void orderTalk();
    void checkNextActionFromButton();
    void setShieldGuard();
    void checkItemModeActorPointer();
    void checkNextActionItemFly();
    void checkNextMode(int);
    void checkIceSlipFall();
    void setFrontWallType();
    void changeFrontWallTypeProc();
    void changeSlideProc();
    void changeWaitProc();
    void changeLandProc(f32);
    void setDamagePoint(f32);
    void checkNormalDamage(int);
    void setDashDamage();
    void checkAtHitEnemy(dCcD_GObjInf*);
    void checkElecReturnDamage(dCcD_GObjInf*, cXyz*);
    void checkWallAtributeDamage(dBgS_AcchCir*);
    void changeDamageProc();
    void changeAutoJumpProc();
    void changeDemoProc();
    void changeDeadProc();
    void getDamageVec(dCcD_GObjInf*);
    void setOldRootQuaternion(s16, s16, s16);
    void checkRestHPAnime();
    void checkHeavyStateOn();
    void checkBottleItem(int) const;
    void checkDrinkBottleItem(int) const;
    void checkOpenBottleItem(int) const;
    void checkBowItem(int) const;
    void checkPhotoBoxItem(int) const;
    void checkScopeEnd();
    void setSubjectMode();
    void checkMaskDraw();
    void checkSubjectEnd(int);
    BOOL checkGuardAccept();
    void cancelNoDamageMode();
    void commonProcInit(daPy_lk_c::daPy_PROC procID);
    void procScope_init(int);
    void procScope();
    void procSubjectivity_init(int);
    void procSubjectivity();
    void procCall_init();
    void procCall();
    void procControllWait_init();
    void procControllWait();
    void procWait_init();
    void procWait();
    void procFreeWait_init();
    void procFreeWait();
    void procMove_init();
    void procMove();
    void procAtnMove_init();
    void procAtnMove();
    void procAtnActorWait_init();
    void procAtnActorWait();
    void procAtnActorMove_init();
    void procAtnActorMove();
    void procSideStep_init(int);
    void procSideStep();
    void procSideStepLand_init();
    void procSideStepLand();
    void procCrouchDefense_init();
    void procCrouchDefense();
    void procCrouchDefenseSlip_init();
    void procCrouchDefenseSlip();
    void procCrouch_init();
    void procCrouch();
    void procWaitTurn_init();
    void procWaitTurn();
    void procMoveTurn_init(int);
    void procMoveTurn();
    void procSlip_init();
    void procSlip();
    void procSlideFront_init(s16);
    void procSlideFront();
    void procSlideBack_init(s16);
    void procSlideBack();
    void procSlideFrontLand_init();
    void procSlideFrontLand();
    void procSlideBackLand_init();
    void procSlideBackLand();
    void procFrontRoll_init(f32);
    void procFrontRoll();
    void procFrontRollCrash_init();
    void procFrontRollCrash();
    void procNockBackEnd_init();
    void procNockBackEnd();
    void procSideRoll_init();
    void procSideRoll();
    void procBackJump_init();
    void procBackJump();
    void procBackJumpLand_init();
    void procBackJumpLand();
    void checkAutoJumpFlying() const;
    void procAutoJump_init();
    void procAutoJump();
    void procLand_init(f32, int);
    void procLand();
    void procLandDamage_init(int);
    void procLandDamage();
    void procFall_init(int, f32);
    void procFall();
    void procSlowFall_init();
    void procSlowFall();
    void procSmallJump_init(int);
    void procSmallJump();
    void procVerticalJump_init();
    void procVerticalJump();
    void procGuardCrash();
    void procDamage_init();
    void procDamage();
    void procPolyDamage_init();
    void procPolyDamage();
    void procLargeDamage_init(int, int, s16, s16);
    void procLargeDamage();
    void procLargeDamageUp_init(int, int, s16, s16);
    void procLargeDamageUp();
    void procLargeDamageWall_init(int, int, s16, s16);
    void procLargeDamageWall();
    void procLavaDamage_init();
    void procLavaDamage();
    void procElecDamage_init(cXyz const*);
    void procElecDamage();
    void procGuardSlip_init();
    void procGuardSlip();
    void procIceSlipFall_init();
    void procIceSlipFall();
    void procIceSlipFallUp_init(int, s16, s16);
    void procIceSlipFallUp();
    void procIceSlipAlmostFall_init();
    void procIceSlipAlmostFall();
    void procBootsEquip_init(u16);
    void procBootsEquip();
    void procNotUse_init(int);
    void procNotUse();
    void getGroundAngle(cBgS_PolyInfo*, s16);
    void setLegAngle(f32, int, s16*, s16*);
    void footBgCheck();
    void setWaterY();
    void autoGroundHit();
    void checkAttentionPosAngle(fopAc_ac_c*, cXyz**);
    void setNeckAngle();
    void checkOriginalHatAnimation();
    void setHatAngle();
    void setMoveSlantAngle();
    void setWaistAngle();
    void setWorldMatrix();
    void setAtParam(u32, int, dCcG_At_Spl, u8, u8, u8, f32);
    void resetCurse();
    void checkLightHit();
    void setSwordAtCollision();
    void getBlurTopRate();
    void setCollision();
    void setAttentionPos();
    void setRoomInfo();
    void setDemoData();
    void setStickData();
    void setBgCheckParam();
    u32 setParamData(int, int, int, int);
    void checkLavaFace(cXyz*, int);
    void checkFallCode();
    BOOL startRestartRoom(u32, int, f32, int);
    void checkSuccessGuard(int);
    void setShapeAngleOnGround();
    void setStepsOffset();
    void setBeltConveyerPower();
    void setWindAtPower();
    void checkRoofRestart();
    BOOL execute();
    BOOL playerDelete();
    void initTextureAnime();
    void initTextureScroll();
    BOOL createHeap();
    void createAnimeHeap(JKRSolidHeap**, daPy_HEAP_TYPE);
    J3DModelData* initModel(J3DModel**, int, u32);
    J3DAnmTextureSRTKey* entryBtk(J3DModelData*, int);
    J3DAnmTevRegKey* entryBrk(J3DModelData*, int);
    void playerInit();
    daPy_lk_c();
    int makeBgWait();
    void setSeAnime(daPy_anmHeap_c const*, J3DFrameCtrl*);
    void initSeAnime();
    void resetSeAnime();
    void setMoveAnime(f32, f32, f32, daPy_lk_c::daPy_ANM, daPy_lk_c::daPy_ANM, int, f32);
    void setSingleMoveAnime(daPy_lk_c::daPy_ANM, float, float, short, float);
    void setActAnimeUpper(u16, daPy_lk_c::daPy_UPPER, f32, f32, s16, f32);
    void resetActAnimeUpper(daPy_lk_c::daPy_UPPER, float);
    void animeUpdate();
    void simpleAnmPlay(J3DAnmBase*);
    void setHandModel(daPy_lk_c::daPy_ANM);
    void getAnmData(daPy_lk_c::daPy_ANM) const;
    BOOL checkGrabWeapon(int);
    void endDemoMode();
    void setAuraEffect();
    void setWaterRipple();
    void setFootEffectType(int, cXyz*, int, int);
    void setFootMark(cXyz*);
    void setFootEffect();
    void resetFootEffect();
    void setSwimTail();
    void setCutWaterSplash();
    void setSwimWaterDrop(daPy_waterDropEcallBack_c*);
    void setWaterDrop();
    void setDamageFlameEmitter();
    void setDamageCurseEmitter();
    void setDamageElecEmitter();
    void setDamageEmitter();
    void endFlameDamageEmitter();
    void endDamageEmitter();
    static u32 setItemWaterEffect(fopAc_ac_c*, int, int);
    void getDemoLookActor();
    void setTinkleCeiverModel();
    void setTalismanModel();
    void setLetterModel();
    void checkCaughtShapeHide();
    void setShapeAngleToTalkActor();
    void checkEndMessage(u32);
    void setTalkStartBack();
    void dProcTool_init();
    void dProcTool();
    void dProcTalk_init();
    void dProcTalk();
    void dProcDamage_init();
    void dProcDamage();
    void dProcHoldup_init();
    void dProcHoldup();
    void dProcOpenTreasure_init();
    void dProcOpenTreasure();
    void setGetItemSound(u16, int);
    void setGetDemo();
    void dProcGetItem_init();
    void dProcGetItem();
    void dProcUnequip_init();
    void dProcUnequip();
    void dProcLavaDamage_init_sub();
    void dProcLavaDamage_init();
    void dProcLavaDamage();
    void dProcFreezeDamage_init_sub(int);
    void dProcFreezeDamage_init();
    void dProcFreezeDamage();
    void dProcDead_init_sub();
    void dProcDead_init_sub2();
    BOOL checkGameOverStart();
    void dProcDead_init();
    void dProcDead();
    void dProcLookAround_init();
    void dProcLookAround();
    void dProcSalute_init();
    void dProcSalute();
    void dProcLookAround2_init();
    void dProcLookAround2();
    void dProcTalismanPickup_init();
    void dProcTalismanPickup();
    void dProcTalismanWait_init();
    void dProcTalismanWait();
    void dProcSurprised_init();
    void dProcSurprised();
    void dProcTurnBack_init();
    void dProcTurnBack();
    void dProcLookUp_init();
    void dProcLookUp();
    void dProcQuakeWait_init();
    void dProcQuakeWait();
    void dProcDance_init();
    void dProcDance();
    void dProcCaught_init();
    void dProcCaught();
    void dProcLookWait_init();
    void dProcLookWait();
    void dProcPushPullWait_init();
    void dProcPushPullWait();
    void dProcPushMove_init();
    void dProcPushMove();
    void dProcDoorOpen_init();
    void dProcDoorOpen();
    void dProcNod_init();
    void dProcNod();
    void dProcPresent_init_sub();
    void dProcPresent_init();
    void dProcPresent();
    void dProcWindChange_init();
    void dProcWindChange();
    void dProcStandItemPut_init();
    void dProcStandItemPut();
    void dProcVorcanoFail_init();
    void dProcVorcanoFail();
    void dProcSlightSurprised_init();
    void dProcSlightSurprised();
    void dProcSmile_init();
    void dProcSmile();
    void dProcBossWarp_init();
    void dProcBossWarp();
    void dProcAgbUse_init();
    void dProcAgbUse();
    void dProcLookTurn_init();
    void dProcLookTurn();
    void dProcLetterOpen_init();
    void dProcLetterOpen();
    void dProcLetterRead_init();
    void dProcLetterRead();
    void dProcRedeadStop_init();
    void dProcRedeadStop();
    void dProcRedeadCatch_init();
    void dProcRedeadCatch();
    void dProcGetDance_init();
    void dProcGetDance();
    void dProcBottleOpenFairy_init();
    void dProcBottleOpenFairy();
    void dProcWarpShort_init();
    void dProcWarpShort();
    void dProcOpenSalvageTreasure_init();
    void dProcOpenSalvageTreasure();
    void dProcSurprisedWait_init();
    void dProcSurprisedWait();
    void dProcPowerUpWait_init();
    void dProcPowerUp_init();
    void dProcPowerUp();
    void dProcShipSit_init();
    void dProcShipSit();
    void dProcLastCombo_init();
    void dProcLastCombo();
    void dProcHandUp_init();
    void dProcHandUp();
    void dProcIceSlip_init();
    void dProcIceSlip();
    void getLadderMoveAnmSpeed();
    void setLadderFootSe();
    void changeLadderMoveProc(int);
    void setMoveBGLadderCorrect();
    void procLadderUpStart_init_sub();
    void procLadderUpStart_init();
    void procLadderUpStart();
    void procLadderUpEnd_init(int);
    void procLadderUpEnd();
    void procLadderDownStart_init_sub();
    void procLadderDownStart_init();
    void procLadderDownStart();
    void procLadderDownEnd_init(int);
    void procLadderDownEnd();
    void procLadderMove_init(int, int, cXyz*);
    void procLadderMove();
    void getHangMoveAnmSpeed();
    void getHangDirectionFromAngle();
    void changeHangMoveProc(int);
    void changeHangEndProc(int);
    void setHangShapeOffset();
    void procHangStart_init();
    void procHangStart();
    void procHangFallStart_init(cM3dGPla*);
    void procHangFallStart();
    void procHangUp_init(int);
    void procHangUp();
    void procHangWait_init();
    void procHangWait();
    void procHangMove_init(int);
    void procHangMove();
    void procHangClimb_init(f32);
    void procHangClimb();
    void procHangWallCatch_init();
    void procHangWallCatch();
    void getClimbMoveAnmSpeed();
    void setClimbShapeOffset();
    void getClimbDirectionFromAngle();
    void changeClimbMoveProc(int);
    void setMoveBGCorrectClimb();
    void checkBgCorrectClimbMove(cXyz*, cXyz*);
    void checkBgClimbMove();
    void procClimbUpStart_init_sub();
    void procClimbUpStart_init();
    void procClimbUpStart();
    void procClimbDownStart_init(s16);
    void procClimbDownStart();
    void procClimbMoveUpDown_init(int);
    void procClimbMoveUpDown();
    void procClimbMoveSide_init(int);
    void procClimbMoveSide();
    void setBlendWHideMoveAnime(f32);
    void getWHideModePolygon(cXyz*, cXyz*, cXyz*, int);
    void getWHideBasePos(cXyz*);
    void getWHideNextPos(cXyz*, cXyz*);
    void checkWHideBackWall(cXyz*);
    void checkWHideFrontFloor(cXyz*);
    void checkWHideModeChange(cXyz*);
    void changeWHideEndProc(cXyz*);
    void procWHideReady_init(cM3dGPla*, cXyz*);
    void procWHideReady();
    void procWHideWait_init();
    void procWHideWait();
    void procWHideMove_init();
    void procWHideMove();
    void procWHidePeep_init();
    void procWHidePeep();
    void getCrawlMoveAnmSpeed();
    void getCrawlMoveSpeed();
    void setCrawlMoveDirectionArrow();
    void changeCrawlAutoMoveProc(cXyz*);
    void getCrawlMoveVec(cXyz*, cXyz*, cXyz*);
    void crawlBgCheck(cXyz*, cXyz*);
    void checkCrawlSideWall(cXyz*, cXyz*, cXyz*, cXyz*, s16*, s16*);
    void setDoStatusCrawl();
    void procCrawlStart_init();
    void procCrawlStart();
    void checkNotCrawlStand(cXyz*);
    void checkNotCrawlStand(cXyz*, cXyz*);
    void procCrawlMove_init(s16, s16);
    void procCrawlMove();
    void procCrawlAutoMove_init(int, cXyz*);
    void procCrawlAutoMove();
    void procCrawlEnd_init(int, s16, s16);
    void procCrawlEnd();
    void checkGrabSpecialHeavyState();
    void setWeaponBlur();
    BOOL checkGrabBarrelSearch(int);
    void setGrabItemPos();
    void freeGrabItem();
    void checkNextActionGrab();
    void initGrabNextMode();
    void procGrabReady_init();
    void procGrabReady();
    void procGrabUp_init();
    void procGrabUp();
    void procGrabMiss_init();
    void procGrabMiss();
    void procGrabThrow_init(int);
    void procGrabThrow();
    void procGrabPut_init();
    void procGrabPut();
    void procGrabWait_init();
    void procGrabWait();
    void procGrabHeavyWait_init();
    void procGrabHeavyWait();
    void procGrabRebound_init();
    void procGrabRebound();
    void setSpeedAndAngleSwim();
    void checkNextModeSwim();
    void changeSwimProc();
    void changeSwimUpProc();
    void swimOutAfter(int);
    void checkSwimFallCheck();
    void changeSwimOutProc();
    void setSwimMoveAnime(daPy_lk_c::daPy_ANM);
    void getSwimTimerRate();
    void setSwimTimerStartStop();
    void procSwimUp_init(int);
    void procSwimUp();
    void procSwimWait_init(int);
    void procSwimWait();
    void procSwimMove_init(int);
    void procSwimMove();
    void setSpecialBattle(int);
    void changeSpecialBattle();
    void procBtJump_init(fopEn_enemy_c*);
    void procBtJump();
    void procBtJumpCut_init(cXyz*);
    void procBtJumpCut();
    void procBtSlide();
    void procBtRoll_init(fopEn_enemy_c*);
    void procBtRoll();
    void procBtRollCut_init(cXyz*);
    void procBtRollCut();
    void procBtVerticalJump_init(fopEn_enemy_c*);
    void procBtVerticalJump();
    void procBtVerticalJumpCut_init();
    void procBtVerticalJumpCut();
    void procBtVerticalJumpLand_init();
    void procBtVerticalJumpLand();
    void shipSpecialDemoStart();
    void checkJumpRideShip();
    void checkShipNotNormalMode();
    void setShipRideArmAngle(int, J3DTransformInfo*);
    void checkShipRideUseItem(int);
    void initShipRideUseItem(int, int);
    void setShipRidePosUseItem();
    void setShipRidePos(int);
    void setShipAttentionAnmSpeed(f32);
    void setShipAttnetionBodyAngle();
    void changeShipEndProc();
    void initShipBaseAnime();
    void initShipCraneAnime();
    void procShipReady_init();
    void procShipReady();
    void procShipJumpRide_init();
    void procShipJumpRide();
    void procShipSteer_init();
    void procShipSteer();
    void procShipPaddle_init();
    void procShipPaddle();
    void procShipScope_init(int);
    void procShipScope();
    void procShipBoomerang_init();
    void procShipBoomerang();
    void procShipHookshot_init();
    void procShipHookshot();
    void procShipBow_init();
    void procShipBow();
    void procShipCannon_init();
    void procShipCannon();
    void procShipCrane_init();
    void procShipCrane();
    void procShipGetOff_init();
    void procShipGetOff();
    void procShipRestart_init();
    void procShipRestart();
    void checkRopeAnime() const;
    void freeRopeItem();
    void checkRopeRoofHit(s16);
    void changeRopeSwingProc();
    void changeRopeEndProc(int);
    void checkSpecialRope();
    void changeRopeToHangProc();
    void checkRopeSwingWall(cXyz*, cXyz*, s16*, f32*);
    void setBlendRopeMoveAnime(int);
    void throwRope();
    void checkNextActionRopeReady();
    void checkNextRopeMode();
    void checkHangRopeActorNull();
    void procRopeSubject_init();
    void procRopeSubject();
    void procRopeReady_init();
    void procRopeReady();
    void procRopeSwing_init(fopAc_ac_c*, s16);
    void procRopeSwing();
    void procRopeHangWait_init(int);
    void procRopeHangWait();
    void specialRopeHangUp();
    void procRopeUp_init();
    void procRopeUp();
    void procRopeDown_init();
    void procRopeDown();
    void procRopeSwingStart_init();
    void procRopeSwingStart();
    void procRopeMove_init();
    void procRopeMove();
    void procRopeThrowCatch_init();
    void procRopeThrowCatch();
    void procRopeUpHang_init();
    void procRopeUpHang();
    void checkBoomerangAnime() const;
    void throwBoomerang();
    void returnBoomerang();
    void checkNextActionBoomerangReady();
    void checkNextActionBoomerangFly();
    void checkNextBoomerangMode();
    void changeBoomerangCatchProc();
    void procBoomerangSubject_init();
    void procBoomerangSubject();
    void procBoomerangMove_init();
    void procBoomerangMove();
    void procBoomerangCatch_init();
    void procBoomerangCatch();
    void bowJointCB(int);
    void bowButton() const;
    void checkBowReadyAnime() const;
    BOOL checkBowAnime() const;
    void makeArrow();
    void deleteArrow();
    void setBowReadyAnime();
    void setBowReloadAnime();
    void checkNextActionBowReady();
    void checkNextActionBowFly();
    void checkNextBowMode();
    void setBowModel();
    void procBowSubject_init();
    void procBowSubject();
    void procBowMove_init();
    void procBowMove();
    void checkHookshotReturn();
    void setHookshotModel();
    void setHookshotSight();
    void freeHookshotItem();
    void checkNextActionHookshotReady();
    void checkNextHookshotMode();
    void procHookshotSubject_init();
    void procHookshotSubject();
    void procHookshotMove_init();
    void procHookshotMove();
    void procHookshotFly_init();
    void procHookshotFly();
    void fanWindEffectDraw();
    void fanWindCrashEffectDraw();
    void fanJointCB(int);
    void parachuteJointCB(int);
    void setShapeFanLeaf();
    void checkFanGlideProc(int);
    void setFanModel();
    void setSmallFanModel();
    void setParachuteFanModel(f32);
    void procFanSwing_init();
    void procFanSwing();
    void procFanGlide_init(int);
    void procFanGlide();
    u32 getDayNightParamData();
    void setTactModel();
    void checkNpcStatus();
    void getTactPlayRightArmAnm(s32);
    void getTactPlayLeftArmAnm(s32);
    void checkEndTactMusic() const;
    void getTactMetronomeRate();
    void checkTactLastInput();
    void getTactTopPos(cXyz*);
    void getTactNormalWait() const;
    void checkTactPlayMelody();
    void resetTactCount();
    void procTactWait_init(int);
    void procTactWait();
    void procTactPlay_init(s32, int, int);
    void procTactPlay();
    void procTactPlayEnd_init(int);
    void procTactPlayEnd();
    void procTactPlayOriginal_init();
    void procTactPlayOriginal();
    void checkJumpFlower();
    void procVomitReady_init(s16, f32);
    void procVomitReady();
    void procVomitWait_init();
    void procVomitWait();
    void procVomitJump_init(int);
    void procVomitJump();
    void procVomitLand_init();
    void procVomitLand();
    void setHammerModel();
    void setHammerQuake(cBgS_PolyInfo*, cXyz const*, int);
    void setHammerWaterSplash();
    void procHammerSideSwing_init();
    void procHammerSideSwing();
    void procHammerFrontSwingReady_init();
    void procHammerFrontSwingReady();
    void procHammerFrontSwing_init();
    void procHammerFrontSwing();
    void procHammerFrontSwingEnd_init();
    void procHammerFrontSwingEnd();
    void setPushPullKeepData(dBgW::PushPullLabel);
    void procPushPullWait_init(int);
    void procPushPullWait();
    void procPushMove_init();
    void procPushMove();
    void procPullMove_init();
    void procPullMove();
    void changeBottleDrinkFace(int);
    void setBottleModel(u16);
    void makeFairy(cXyz*, u32);
    void procBottleDrink_init(u16);
    void procBottleDrink();
    void procBottleOpen_init(u16);
    void procBottleOpen();
    void procBottleSwing_init(int);
    void procBottleSwing();
    void procBottleGet_init();
    void procBottleGet();
    void setEnemyWeaponAtParam(int);
    void procWeaponNormalSwing_init();
    void procWeaponNormalSwing();
    void procWeaponSideSwing_init();
    void procWeaponSideSwing();
    void procWeaponFrontSwingReady_init();
    void procWeaponFrontSwingReady();
    void procWeaponFrontSwing_init();
    void procWeaponFrontSwing();
    void procWeaponFrontSwingEnd_init();
    void procWeaponFrontSwingEnd();
    void procWeaponThrow_init();
    void procWeaponThrow();
    void setHyoiModel();
    void procFoodThrow_init();
    void procFoodThrow();
    void procFoodSet_init();
    void procFoodSet();
    void setSwordModel(int);
    void setLightSaver();
    void checkDemoShieldNoDraw();
    void checkDemoSwordNoDraw(int);
    void checkChanceMode();
    void checkCutRollChange() const;
    void getSwordBlurColor();
    void setNormalCutAtParam(u8);
    void setFinishCutAtParam(u8);
    void setExtraCutAtParam(u8);
    void setExtraFinishCutAtParam(u8);
    void setJumpCutAtParam();
    void getCutDirection();
    void changeCutProc();
    void changeCutReverseProc(daPy_lk_c::daPy_ANM);
    void procCutA_init(s16);
    void procCutA();
    void procCutF_init(s16);
    void procCutF();
    void procCutR_init(s16);
    void procCutR();
    void procCutL_init(s16);
    void procCutL();
    void procCutEA_init();
    void procCutEA();
    void procCutEB_init();
    void procCutEB();
    void procCutExA_init();
    void procCutExA();
    void procCutExB_init();
    void procCutExB();
    void procCutTurn_init(int);
    void procCutTurn();
    void procCutRoll_init();
    void procCutRoll();
    void procCutRollEnd_init();
    void procCutRollEnd();
    void procCutTurnCharge_init();
    void procCutTurnCharge();
    void procCutTurnMove_init();
    void procCutTurnMove();
    void procCutReverse_init(daPy_lk_c::daPy_ANM);
    void procCutReverse();
    void procJumpCut_init(int);
    void procJumpCut();
    void procJumpCutLand_init();
    void procJumpCutLand();
    void procCutExMJ_init(int);
    void procCutExMJ();
    void procCutKesa_init();
    void procCutKesa();
    void checkNoControll() const;
    
    J3DAnmTevRegKey* getBombBrk() { return mpBombBrk; }
    J3DAnmTextureSRTKey* getIceArrowBtk() { return mpIceArrowBtk; }
    J3DAnmTextureSRTKey* getLightArrowBtk() { return mpLightArrowBtk; }

    virtual MtxP getLeftHandMatrix() { return mpCLModel->getAnmMtx(0x08); } // cl_LhandA joint
    virtual MtxP getRightHandMatrix() { return mpCLModel->getAnmMtx(0x0C); } // cl_RhandA joint
    virtual f32 getGroundY() { return mAcch.GetGroundH(); }
    virtual int getTactMusic() const;
    virtual int getTactTimerCancel() const;
    virtual BOOL checkPlayerGuard() const;
    virtual fopAc_ac_c* getGrabMissActor();
    virtual BOOL checkPlayerFly() const { return field_0x3618 & 0x10452822; } // TODO add enum
    virtual BOOL checkFrontRoll() const { return mCurProc == 0x1E; } // TODO add enum
    virtual BOOL checkBottleSwing() const { return mCurProc == 0xA5; }
    virtual BOOL checkCutCharge() const { return mCurProc == 0x59; }
    virtual BOOL getBokoFlamePos(cXyz*);
    virtual BOOL checkTactWait() const { return mCurProc == 0x9A; }
    virtual void setTactZev(unsigned int, int, char*);
    virtual void onDekuSpReturnFlg(u8);
    virtual bool checkComboCutTurn() const;
    virtual f32 getBaseAnimeFrameRate() { return mFrameCtrlUnder[0].getRate(); }
    virtual f32 getBaseAnimeFrame() { return mFrameCtrlUnder[0].getFrame(); }
    virtual u32 getItemID() const { return mActorKeepEquip.getID(); }
    virtual u32 getThrowBoomerangID() const { return mActorKeepThrow.getID(); }
    virtual u32 getGrabActorID() const { return mActorKeepGrab.getID(); }
    virtual BOOL checkGrabBarrel() { return checkGrabBarrelSearch(1); }
    virtual BOOL checkPlayerNoDraw();
    virtual BOOL checkRopeTag() { return mActorKeepEquip.getActor() == NULL; }
    virtual BOOL checkRopeReadyAnime() const;
    virtual void voiceStart(u32);
    virtual void setOutPower(f32, s16, int);
    virtual void onFrollCrashFlg(u32);
    virtual MtxP getModelJointMtx(u16);
    virtual f32 getOldSpeedY();
    virtual BOOL setHookshotCarryOffset(unsigned int, const cXyz*);
    virtual void setPlayerPosAndAngle(cXyz*, s16);
    virtual void setPlayerPosAndAngle(cXyz*, csXyz*);
    virtual void setPlayerPosAndAngle(float (*)[4]);
    virtual BOOL setThrowDamage(cXyz*, s16, f32, f32, int);
    virtual void changeTextureAnime(u16, u16, int);
    virtual void cancelChangeTextureAnime();

    /* 0x0320 */ request_of_phase_process_class mPhsLoad;
    /* 0x0328 */ J3DModelData* mpCLModelData;
    /* 0x032C */ J3DModel* mpCLModel;
    /* 0x0330 */ J3DModel* mpKatsuraModel;
    /* 0x0334 */ J3DModel* mpYamuModel;
    /* 0x0338 */ u8 field_0x0338[0x035C - 0x0338];
    /* 0x035C */ J3DAnmTexPattern* field_0x035c;
    /* 0x0360 */ u8 field_0x0360[0x0364 - 0x0360];
    /* 0x0364 */ J3DAnmTextureSRTKey* mpTexScrollResData;
    /* 0x0368 */ J3DTexMtxAnm* mpTexMtxAnm;
    /* 0x036C */ daPy_matAnm_c* mpTexEyeScroll[2];
    /* 0x0374 */ J3DShape* mpZOffBlendShape[4];
    /* 0x0384 */ J3DShape* mpZOffNoneShape[4];
    /* 0x0394 */ J3DShape* mpZOnShape[4];
    /* 0x03A4 */ J3DShape* field_0x03a4;
    /* 0x03A8 */ J3DShape* field_0x03a8;
    /* 0x03AC */ dBgS_AcchCir mAcchCir[3];
    /* 0x046C */ dBgS_LinkAcch mAcch;
    /* 0x0630 */ dBgS_LinkLinChk mLinkLinChk;
    /* 0x069C */ dBgS_RopeLinChk mRopeLinChk;
    /* 0x0708 */ dBgS_BoomerangLinChk mBoomerangLinChk;
    /* 0x0774 */ dBgS_LinkGndChk mGndChk;
    /* 0x07C8 */ dBgS_LinkRoofChk mRoofChk;
    /* 0x0814 */ dBgS_ArrowLinChk mArrowLinChk;
    /* 0x0880 */ dBgS_MirLightLinChk mMirLightLinChk;
    /* 0x08EC */ dBgS_ObjGndChk_Spl field_0x08EC;
    /* 0x0940 */ cBgS_PolyInfo mPolyInfo;
    /* 0x0950 */ daPy_HIO_c* m_HIO;
    /* 0x0954 */ J3DModel* mpHandsModel;
    /* 0x0958 */ J3DModel* mpEquippedSwordModel;
    /* 0x095C */ J3DModel* mpSwgripaModel;
    /* 0x0960 */ J3DModel* mpSwgripmsModel;
    /* 0x0964 */ mDoExt_bckAnm mSwgripmsabBckAnim;
    /* 0x0974 */ J3DAnmTevRegKey* mpTswgripmsabBrk;
    /* 0x0978 */ J3DAnmTextureSRTKey* mpTswgripmsBtk;
    /* 0x097C */ J3DModel* mpPodmsModel;
    /* 0x0980 */ J3DModel* mpEquippedShieldModel;
    /* 0x0984 */ J3DModel* mpShaModel;
    /* 0x0988 */ J3DModel* mpShmsModel;
    /* 0x098C */ mDoExt_bckAnm mAtngshaBck;
    /* 0x099C */ J3DAnmTextureSRTKey* mpTshmsBtk;
    /* 0x09A0 */ dDlst_mirrorPacket mMirrorPacket;
    /* 0x2E7C */ J3DModel* mpYmsls00Model;
    /* 0x2E80 */ J3DAnmTextureSRTKey* mpYmsls00Btk;
    /* 0x2E84 */ J3DModel* mpHbootsModelRightFoot;
    /* 0x2E88 */ J3DModel* mpHbootsModelLeftFoot;
    /* 0x2E8C */ J3DModel* mpPringModel;
    /* 0x2E90 */ JKRSolidHeap* mpItemHeaps[2];
    /* 0x2E98 */ J3DModel* mpHeldItemModel;
    /* 0x2E9C */ mDoExt_bckAnm mSwordAnim;
    /* 0x2EAC */ u8 field_0x2EAC[0x2EB0 - 0x2EAC];
    /* 0x2EB0 */ J3DAnmTevRegKey* mpBombBrk;
    /* 0x2EB4 */ J3DAnmTevRegKey* mpGwp00BrkData;
    /* 0x2EB8 */ J3DAnmTextureSRTKey* mpGwp00BtkData;
    /* 0x2EBC */ J3DAnmTextureSRTKey* mpGicer00Btk;
    /* 0x2EC0 */ J3DAnmTextureSRTKey* mpIceArrowBtk;
    /* 0x2EC4 */ J3DAnmTextureSRTKey* mpLightArrowBtk;
    /* 0x2EC8 */ J3DAnmTextureSRTKey* mpGicer01Btk;
    /* 0x2ECC */ JKRSolidHeap* field_0x2ECC;
    /* 0x2ED0 */ void* m_item_bck_buffer;
    /* 0x2ED4 */ J3DAnmTextureSRTKey* mpHeldItemModelAnimTexEx;
    /* 0x2ED8 */ J3DAnmTextureSRTKey* mpSwordAnimBTK;
    /* 0x2EDC */ J3DAnmTevRegKey* mpHeldItemAnimBRK;
    /* 0x2EE0 */ J3DModel* mpBottleContentsModel;
    /* 0x2EE4 */ J3DModel* mpBottleCapModel;
    /* 0x2EE8 */ J3DModel* mpSwordModel1;
    /* 0x2EEC */ u8 field_0x2EEC[0x2EF0 - 0x2EEC];
    /* 0x2EF0 */ J3DAnmColor* field_0x2ef0;
    /* 0x2EF4 */ J3DAnmTextureSRTKey* field_0x2ef4;
    /* 0x2EF8 */ J3DAnmTevRegKey* field_0x2ef8;
    /* 0x2EFC */ mDoExt_brkAnm field_0x2efc;
    /* 0x2F14 */ J3DModel* mpSuimenMunyaModel;
    /* 0x2F18 */ J3DAnmTextureSRTKey* mpSuimenMunyaBtk;
    /* 0x2F1C */ J3DModel* mpYuchw00Model;
    /* 0x2F20 */ mDoExt_bckAnm mYuchw00Bck;
    /* 0x2F30 */ J3DAnmTextureSRTKey* mpYuchw00Btk;
    /* 0x2F34 */ J3DAnmTevRegKey* mpYuchw00Brk;
    /* 0x2F38 */ J3DModel* mpYbafo00Model;
    /* 0x2F3C */ J3DAnmTextureSRTKey* mpYbafo00Btk;
    /* 0x2F40 */ daPy_aura_c mMagicArmorAuraEntries[6];
    /* 0x2F70 */ mDoExt_brkAnm mYaura00rBrk;
    /* 0x2F88 */ J3DAnmTextureSRTKey* mpYaura00Btk;
    /* 0x2F8C */ J3DModel* mpYmgcs00Model;
    /* 0x2F90 */ mDoExt_brkAnm mYmgcs00Brk;
    /* 0x2FA8 */ J3DAnmTextureSRTKey* mpYmgcs00Btk;
    /* 0x2FAC */ mDoExt_MtxCalcAnmBlendTblOld* m_pbCalc[2];
    /* 0x2FB4 */ mDoExt_AnmRatioPack mAnmRatioUnder[2];
    /* 0x2FC4 */ mDoExt_AnmRatioPack mAnmRatioUpper[3];
    /* 0x2FDC */ daPy_anmHeap_c m_anm_heap_under[2];
    /* 0x2FFC */ daPy_anmHeap_c m_anm_heap_upper[3];
    /* 0x302C */ J3DFrameCtrl mFrameCtrlUnder[2];
    /* 0x3054 */ J3DFrameCtrl mFrameCtrlUpper[3];
    /* 0x3090 */ daPy_sightPacket_c mSightPacket;
    /* 0x30E0 */ JAIZelAnime mJAIZelAnime;
    /* 0x3178 */ void* m_sanm_buffer;
    /* 0x317C */ daPy_actorKeep_c mActorKeepEquip;
    /* 0x3184 */ daPy_actorKeep_c mActorKeepThrow;
    /* 0x318C */ daPy_actorKeep_c mActorKeepGrab;
    /* 0x3194 */ daPy_actorKeep_c mActorKeepRope;
    /* 0x319C */ fopAc_ac_c* mpAttnActorLockOn;
    /* 0x31A0 */ fopAc_ac_c* mpAttnActorAction;
    /* 0x31A4 */ fopAc_ac_c* mpAttnActorA;
    /* 0x31A8 */ fopAc_ac_c* mpAttnActorX;
    /* 0x31AC */ fopAc_ac_c* mpAttnActorY;
    /* 0x31B0 */ fopAc_ac_c* mpAttnActorZ;
    /* 0x31B4 */ mDoExt_MtxCalcOldFrame* m_old_fdata;
    /* 0x31B8 */ s16 mTexAnimeResIdx;
    /* 0x31BA */ s16 field_0x31ba;
    /* 0x31BC */ s16 field_0x31bc;
    /* 0x31BE */ u8 field_0x31BE[0x31C0 - 0x31BE];
    /* 0x31C0 */ void* mpTextureAnimeResData;
    /* 0x31C4 */ JKRSolidHeap* mpTextureAnimeResHeap;
    /* 0x31C8 */ u16 mTexScrollResIdx;
    /* 0x31CA */ s16 field_0x31ca;
    /* 0x31CC */ s16 field_0x31cc;
    /* 0x31CE */ s16 field_0x31ce;
    /* 0x31D0 */ void* mpTextureScrollResData;
    /* 0x31D4 */ JKRSolidHeap* mpTextureScrollResHeap;
    /* 0x31D8 */ int mCurProc;
    /* 0x31DC */ int (daPy_lk_c::*field_0x31dc)();
    /* 0x31E8 */ daPy_footEffect_c field_0x31e8[2];
    /* 0x3280 */ dPa_rippleEcallBack field_0x3280;
    /* 0x3294 */ daPy_swimTailEcallBack_c mSwimTailEcallBack[2];
    /* 0x32E4 */ daPy_mtxFollowEcallBack_c field_0x32e4;
    /* 0x32F0 */ daPy_mtxFollowEcallBack_c field_0x32f0;
    /* 0x32FC */ dPa_smokeEcallBack mSmokeEcallBack;
    /* 0x331C */ dPa_cutTurnEcallBack_c field_0x331C;
    /* 0x332C */ dPa_cutTurnEcallBack_c field_0x332C;
    /* 0x333C */ dPa_cutTurnEcallBack_c field_0x333C;
    /* 0x334C */ daPy_waterDropEcallBack_c field_0x334C;
    /* 0x336C */ daPy_waterDropEcallBack_c field_0x336C;
    /* 0x338C */ daPy_followEcallBack_c field_0x338c;
    /* 0x33A8 */ daPy_mtxPosFollowEcallBack_c field_0x33a8;
    /* 0x33B8 */ daPy_dmEcallBack_c field_0x33b8[4];
    /* 0x33E8 */ daPy_mtxFollowEcallBack_c field_0x33E8;
    /* 0x33F4 */ daPy_fanSwingEcallBack_c mFanSwingCb;
    /* 0x3400 */ daPy_mtxPosFollowEcallBack_c field_0x3400;
    /* 0x3410 */ daPy_followEcallBack_c field_0x3410;
    /* 0x342C */ daPy_mtxFollowEcallBack_c field_0x342C;
    /* 0x3438 */ daPy_followEcallBack_c field_0x3438;
    /* 0x3454 */ daPy_mtxFollowEcallBack_c field_0x3454;
    /* 0x3460 */ daPy_mtxPosFollowEcallBack_c field_0x3460[2];
    /* 0x3480 */ dAttention_c* mpAttention;
    /* 0x3484 */ dAttList_c* mpAttnEntryA;
    /* 0x3488 */ dAttList_c* mpAttnEntryX;
    /* 0x348C */ dAttList_c* mpAttnEntryY;
    /* 0x3490 */ dAttList_c* mpAttnEntryZ;
    /* 0x3494 */ u8 field_0x3494[0x3498 - 0x3494];
    /* 0x3498 */ LIGHT_INFLUENCE field_0x3498;
    /* 0x34B8 */ u8 field_0x34B8[0x34B9 - 0x34B8];
    /* 0x34B9 */ u8 mFrontWallType;
    /* 0x34BA */ u8 field_0x34BA[0x34BB - 0x34BA];
    /* 0x34BB */ u8 mCurrItemHeapIdx;
    /* 0x34BC */ u8 field_0x34BC[0x34BD - 0x34BC];
    /* 0x34BD */ u8 mLastUsedEquipItem;
    /* 0x34BE */ u8 field_0x34BE[0x34C0 - 0x34BE];
    /* 0x34C0 */ u8 field_0x34c0;
    /* 0x34C1 */ u8 field_0x34c1;
    /* 0x34C2 */ u8 field_0x34c2;
    /* 0x34C3 */ u8 field_0x34c3;
    /* 0x34C4 */ u8 field_0x34c4;
    /* 0x34C5 */ u8 field_0x34c5;
    /* 0x34C6 */ u8 field_0x34C6[0x34C7 - 0x34C6];
    /* 0x34C7 */ u8 mActivePlayerBombs;
    /* 0x34C8 */ u8 mPressedButtonsBitfield;
    /* 0x34C9 */ u8 field_0x34C9[0x34CB - 0x34C9];
    /* 0x34CB */ u8 field_0x34CB;
    /* 0x34CC */ u8 field_0x34D0[0x34D0 - 0x34CC];
    /* 0x34D0 */ s16 field_0x34d0;
    /* 0x34D2 */ s16 field_0x34d2;
    /* 0x34D4 */ s16 field_0x34d4;
    /* 0x34D6 */ u16 field_0x34d6;
    /* 0x34D8 */ s16 field_0x34d8;
    /* 0x34DA */ s16 field_0x34da;
    /* 0x34DC */ u8 field_0x34DC[0x34DE - 0x34DC];
    /* 0x34DE */ s16 field_0x34de;
    /* 0x34E0 */ u8 field_0x34E0[0x34E2 - 0x34E0];
    /* 0x34E2 */ s16 field_0x34e2;
    /* 0x34E4 */ u8 field_0x34E4[0x34E6 - 0x34E4];
    /* 0x34E6 */ s16 field_0x34e6;
    /* 0x34E8 */ u8 field_0x34E8[0x3522 - 0x34E8];
    /* 0x3522 */ s16 field_0x3522;
    /* 0x3524 */ u8 field_0x3524[0x352C - 0x3524];
    /* 0x352C */ s16 field_0x352c;
    /* 0x352E */ s16 field_0x352e;
    /* 0x3530 */ s16 field_0x3530;
    /* 0x3532 */ s16 field_0x3532;
    /* 0x3534 */ u8 field_0x3534[0x3544 - 0x3534];
    /* 0x3544 */ s16 field_0x3544;
    /* 0x3546 */ u8 field_0x3546[0x354C - 0x3546];
    /* 0x354C */ s16 field_0x354c;
    /* 0x354E */ s16 field_0x354e;
    /* 0x3550 */ u8 field_0x3550[0x3554 - 0x3550];
    /* 0x3554 */ s16 field_0x3554;
    /* 0x3556 */ u8 field_0x3556[0x355E - 0x3556];
    /* 0x355E */ u16 field_0x355e;
    /* 0x3560 */ u16 mHeldItemType;
    /* 0x3562 */ u8 field_0x3562[0x3564 - 0x3562];
    /* 0x3564 */ s16 field_0x3564;
    /* 0x3566 */ s16 field_0x3566;
    /* 0x3568 */ s16 field_0x3568;
    /* 0x356A */ u8 field_0x356A[0x356C - 0x356A];
    /* 0x356C */ int mCameraInfoIdx;
    /* 0x3570 */ int field_0x3570;
    /* 0x3574 */ int field_0x3574;
    /* 0x3578 */ u8 field_0x3578[0x3580 - 0x3578];
    /* 0x3580 */ int field_0x3580;
    /* 0x3584 */ int mCurrentGroundAttributeCode;
    /* 0x3588 */ u8 field_0x3588[0x358C - 0x3588];
    /* 0x358C */ int mStaffIdx;
    /* 0x3590 */ int field_0x3590;
    /* 0x3594 */ int field_0x3594;
    /* 0x3598 */ u8 field_0x3598[0x35A0 - 0x3598];
    /* 0x35A0 */ f32 field_0x35a0;
    /* 0x35A4 */ f32 field_0x35a4;
    /* 0x35A8 */ u8 field_0x35A8[0x35BC - 0x35A8];
    /* 0x35BC */ f32 mVelocity;
    /* 0x35C0 */ u8 field_0x35C0[0x35C8 - 0x35C0];
    /* 0x35C8 */ f32 field_0x35c8;
    /* 0x35CC */ u8 field_0x35CC[0x35D0 - 0x35CC];
    /* 0x35D0 */ f32 field_0x35d0;
    /* 0x35D4 */ u8 field_0x35D4[0x35D8 - 0x35D4];
    /* 0x35D8 */ f32 field_0x35d8;
    /* 0x35DC */ u8 field_0x35DC[0x35E4 - 0x35DC];
    /* 0x35E4 */ f32 field_0x35e4;
    /* 0x35E8 */ f32 field_0x35e8;
    /* 0x35EC */ f32 field_0x35ec;
    /* 0x35F0 */ u8 field_0x35F0[0x35FC - 0x35F0];
    /* 0x35FC */ f32 field_0x35fc;
    /* 0x3600 */ f32 field_0x3600;
    /* 0x3604 */ u8 field_0x3604[0x3610 - 0x3604];
    /* 0x3610 */ f32 field_0x3610;
    /* 0x3614 */ int field_0x3614;
    /* 0x3618 */ u32 field_0x3618;
    /* 0x361C */ u8 field_0x361C[0x3624 - 0x361C];
    /* 0x3624 */ int field_0x3624;
    /* 0x3628 */ int field_0x3628;
    /* 0x362C */ u8 field_0x362C[0x3630 - 0x362C];
    /* 0x3630 */ int field_0x3630;
    /* 0x3634 */ int field_0x3634;
    /* 0x3638 */ u8 field_0x3638[0x3644 - 0x3638];
    /* 0x3644 */ f32 field_0x3644;
    /* 0x3648 */ u8 field_0x3648[0x3668 - 0x3648];
    /* 0x3668 */ J3DTransformInfo field_0x3668;
    /* 0x3688 */ u8 field_0x3688[0x3694 - 0x3688];
    /* 0x3694 */ cXyz mOldSpeed;
    /* 0x36A0 */ cXyz field_0x36a0;
    /* 0x36AC */ cXyz field_0x36ac;
    /* 0x36B8 */ u8 field_0x36B8[0x36C4 - 0x36B8];
    /* 0x36C4 */ cXyz field_0x36c4;
    /* 0x36D0 */ u8 field_0x36D0[0x3700 - 0x36D0];
    /* 0x3700 */ cXyz field_0x3700;
    /* 0x370C */ cXyz field_0x370c;
    /* 0x3718 */ u8 field_0x3718[0x3724 - 0x3718];
    /* 0x3724 */ cXyz field_0x3724;
    /* 0x3730 */ u8 field_0x3730[0x3748 - 0x3730];
    /* 0x3748 */ cXyz field_0x3748;
    /* 0x3754 */ u8 field_0x3754[0x37E4 - 0x3754];
    /* 0x37E4 */ daPy_swBlur_c mSwBlur;
    /* 0x3DB8 */ daPy_footData_c mFootData[2];
    /* 0x3FE8 */ dCcD_Stts field_0x3fe8;
    /* 0x4024 */ dCcD_Cyl field_0x4024;
    /* 0x4154 */ dCcD_Cyl field_0x4154;
    /* 0x4284 */ dCcD_Cyl field_0x4284;
    /* 0x43B4 */ dCcD_Cyl field_0x43b4;
    /* 0x44E4 */ dCcD_Cps field_0x44e4[3];
    /* 0x488C */ dCcD_Cps field_0x488c;
    /* 0x49C4 */ dCcD_Sph field_0x49c4;
    /* 0x4AF0 */ dCcD_Cps field_0x4af0;
};  // Size: 0x4C28

enum LINK_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    LINK_BCK_ATNGSHA=0xA,
    LINK_BCK_BOMB=0xB,
    LINK_BCK_COMBO_TATE=0xC,
    LINK_BCK_GICER01=0xD,
    LINK_BCK_GWP00=0xE,
    LINK_BCK_SWGRIPMSAB=0xF,
    LINK_BCK_YUCHW00=0x10,
    
    /* BDL */
    LINK_BDL_BINFAIRY=0x13,
    LINK_BDL_BOOMERANG=0x14,
    LINK_BDL_BOTTLECAP=0x15,
    LINK_BDL_BOW=0x16,
    LINK_BDL_CAMERA=0x17,
    LINK_BDL_CL=0x18,
    LINK_BDL_FAN=0x19,
    LINK_BDL_FANB=0x1A,
    LINK_BDL_FANSMALL=0x1B,
    LINK_BDL_HAMMER=0x1C,
    LINK_BDL_HANDS=0x1D,
    LINK_BDL_HOOKSHOT=0x1E,
    LINK_BDL_HYOINOMI=0x1F,
    LINK_BDL_KATSURA=0x20,
    LINK_BDL_LETTER=0x21,
    LINK_BDL_PODMS=0x22,
    LINK_BDL_PRING=0x23,
    LINK_BDL_SHA=0x24,
    LINK_BDL_SWA=0x25,
    LINK_BDL_SWGRIPA=0x26,
    LINK_BDL_TCEIVER=0x27,
    LINK_BDL_TETOLACH=0x28,
    LINK_BDL_YAMU=0x29,
    
    /* BDLC */
    LINK_BDL_ESA=0x2C,
    LINK_BDL_HBOOTS=0x2D,
    LINK_BDL_ROPEEND=0x2E,
    LINK_BDL_TELESCOPE=0x2F,
    
    /* BDLI */
    LINK_BDL_GARWFI00=0x32,
    LINK_BDL_GARWFI01=0x33,
    LINK_BDL_GARWG00=0x34,
    
    /* BDLM */
    LINK_BDL_ARROW=0x37,
    LINK_BDL_ARROWGLITTER=0x38,
    LINK_BDL_BINHO=0x39,
    LINK_BDL_BINLIQUID=0x3A,
    LINK_BDL_BINLIQUIDH=0x3B,
    LINK_BDL_BOMB=0x3C,
    LINK_BDL_BOTTLEEMP=0x3D,
    LINK_BDL_CUTFH=0x3E,
    LINK_BDL_CUTFM=0x3F,
    LINK_BDL_GICER00=0x40,
    LINK_BDL_GICER01=0x41,
    LINK_BDL_GWP00=0x42,
    LINK_BDL_SHMS=0x43,
    LINK_BDL_SUIMEN_MUNYA=0x44,
    LINK_BDL_SWGRIPMS=0x45,
    LINK_BDL_SWMS=0x46,
    LINK_BDL_TAKT=0x47,
    LINK_BDL_YAURA00=0x48,
    LINK_BDL_YBAFO00=0x49,
    LINK_BDL_YHSLS00=0x4A,
    LINK_BDL_YMGCS00=0x4B,
    LINK_BDL_YMSLI00=0x4C,
    LINK_BDL_YMSLS00=0x4D,
    LINK_BDL_YUCHW00=0x4E,
    
    /* BRK */
    LINK_BRK_BOMB=0x51,
    LINK_BRK_GARWFI00=0x52,
    LINK_BRK_GARWFI01=0x53,
    LINK_BRK_GARWG00=0x54,
    LINK_BRK_GWP00=0x55,
    LINK_BRK_TSWGRIPMSAB=0x56,
    LINK_BRK_YAURA00_G=0x57,
    LINK_BRK_YAURA00_R=0x58,
    LINK_BRK_YMGCS00_MS=0x59,
    LINK_BRK_YMGCS00_TS=0x5A,
    LINK_BRK_YUCHW00=0x5B,
    
    /* BTK */
    LINK_BTK_GARWFI00=0x5E,
    LINK_BTK_GARWFI01=0x5F,
    LINK_BTK_GARWG00=0x60,
    LINK_BTK_GICER00=0x61,
    LINK_BTK_GICER01=0x62,
    LINK_BTK_GWP00=0x63,
    LINK_BTK_SUIMEN_MUNYA=0x64,
    LINK_BTK_TARROWGLITTER=0x65,
    LINK_BTK_TSHMS=0x66,
    LINK_BTK_TSWGRIPMS=0x67,
    LINK_BTK_TTIPICE=0x68,
    LINK_BTK_YAURA00=0x69,
    LINK_BTK_YBAFO00=0x6A,
    LINK_BTK_YMGCS00=0x6B,
    LINK_BTK_YMSLS00=0x6C,
    LINK_BTK_YUCHW00=0x6D,
    
    /* TEX */
    LINK_BTI_BLUR=0x70,
    LINK_BTI_LINKTEXBCI4=0x71,
    LINK_BTI_ROCK_MARK=0x72,
};

#endif /* D_A_PLAYER_LINK */