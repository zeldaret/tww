#ifndef D_A_PLAYER
#define D_A_PLAYER

#include "JSystem/J3DGraphAnimator/J3DMaterialAnm.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_d.h"

class daPy_matAnm_c : public J3DMaterialAnm {
public:
    daPy_matAnm_c() { init(); }

    void init();

    virtual ~daPy_matAnm_c();
    virtual void calc(J3DMaterial*) const;
};

class daPy_mtxFollowEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    void end();
    void makeEmitter(u16, MtxP, const cXyz*, const cXyz*);
    void makeEmitterColor(u16, MtxP, const cXyz*, const GXColor*, const GXColor*);
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) { mpEmitter = emitter; }

    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ MtxP mpMtx;
};

class daPy_HIO_c {
public:
};

class daPy_demo_c {
public:
    void setDemoType(u16 pType) { mDemoType = pType; }
    int getDemoType() const { return mDemoType; }
    void setDemoMode(u32 mode) { mDemoMode = mode; }
    u32 getDemoMode() const { return mDemoMode; }
    int getParam1() const { return mParam1; }
    void setTimer(s16 time) { mTimer = time; }
    void decTimer() { mTimer--; }
    void setOriginalDemoType() { setDemoType(3); }
    void setSpecialDemoType() { setDemoType(5); }
    void setSystemDemoType() { setDemoType(2); }
    void setStick(f32 stick) { mStick = stick; }
    void setMoveAngle(s16 angle) { mDemoMoveAngle = angle; }
    s16 getMoveAngle() const { return mDemoMoveAngle; }
    f32 getStick() { return mStick; }
    int getParam0() const { return mParam0; }
    void setParam0(int value) { mParam0 = value; }
    void setParam1(int value) { mParam1 = value; }
    void setParam2(int value) { mParam2 = value; }

private:
    /* 0x00 */ u16 mDemoType;
    /* 0x02 */ s16 mDemoMoveAngle;
    /* 0x04 */ s16 mTimer;
    /* 0x06 */ s16 mParam2;
    /* 0x08 */ int mParam0;
    /* 0x0C */ int mParam1;
    /* 0x10 */ u32 mDemoMode;
    /* 0x14 */ f32 mStick;
};  // Size: 0x18

class daPy_py_c : public fopAc_ac_c {
public:
    enum daPy_PROC {};
    
    enum daPy_FLG0 {
        daPyFlg0_CUT_AT_FLG        = 0x00000040,
        daPyFlg0_PUSH_PULL_KEEP    = 0x00000800,
        daPyFlg0_UNK1000           = 0x00001000,
        daPyFlg0_UNK200000         = 0x00200000,
        daPyFlg0_EQUIP_HEAVY_BOOTS = 0x02000000,
        daPyFlg0_NO_DRAW           = 0x08000000,
        daPyFlg0_HEAVY_STATE       = 0x40000000,
    };
    
    enum daPy_FLG1 {
        daPy_FLG1_EQUIP_DRAGON_SHIELD  = 0x00000001,
        daPy_FLG1_NPC_CALL_COMMAND     = 0x00000002,
        daPy_FLG1_FORCE_VOMIT_JUMP     = 0x00000010,
        daPy_FLG1_NPC_NOT_CHANGE       = 0x00000040,
        daPy_FLG1_CONFUSE              = 0x00000100,
        daPy_FLG1_SHIP_TACT            = 0x00001000,
        daPy_FLG1_USE_ARROW_EFFECT     = 0x00002000,
        daPy_FLG1_LETTER_READ_EYE_MOVE = 0x00004000,
        daPy_FLG1_UNK8000              = 0x00008000,
        daPy_FLG1_FOREST_WATER_USE     = 0x00020000,
        daPy_FLG1_WATER_DROP           = 0x00080000,
        daPy_FLG1_VINE_CATCH           = 0x02000000,
        daPy_FLG1_LAST_COMBO_WAIT      = 0x20000000,
    };
    
    /* 0x290 */ u8 mAttackState;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292[0x294 - 0x292];
    /* 0x294 */ s16 mDamageWaitTimer;
    /* 0x296 */ s16 mQuakeTimer;
    /* 0x298 */ int field_0x298;
    /* 0x29C */ u32 mNoResetFlg0;
    /* 0x2A0 */ u32 mNoResetFlg1;
    /* 0x2A4 */ u32 field_0x2a4;
    /* 0x2A8 */ f32 field_0x2a8;
    /* 0x2AC */ u8 field_0x2AC[0x2B0 - 0x2AC];
    /* 0x2B0 */ f32 field_0x2b0;
    /* 0x2B4 */ csXyz mBodyAngle;
    /* 0x2BA */ u8 field_0x2BA[0x2BC - 0x2BA];
    /* 0x2BC */ cXyz mHeadTopPos;
    /* 0x2C8 */ cXyz mSwordTopPos;
    /* 0x2D4 */ cXyz field_0x2d4;
    /* 0x2E0 */ cXyz field_0x2e0;
    /* 0x2EC */ cXyz mRopePos;
    /* 0x2F8 */ cXyz field_0x2f8;
    /* 0x304 */ daPy_demo_c mDemo;

    u8 getCutType() const { return mAttackState; }
    s16 getDamageWaitTimer() const { return mDamageWaitTimer; }
    s16 getBodyAngleX() { return mBodyAngle.x; }
    s16 getBodyAngleY() { return mBodyAngle.y; }
    void changeDemoMoveAngle(s16 angle) { mDemo.setMoveAngle(angle); }

    void onNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 |= flag; }
    void offNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 &= ~flag; }
    bool checkNoResetFlg0(daPy_FLG0 flag) const { return mNoResetFlg0 & flag; }
    bool getCutAtFlg() const { return checkNoResetFlg0(daPyFlg0_CUT_AT_FLG); }
    void onPushPullKeep() { onNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    void offPushPullKeep() { offNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    bool checkEquipHeavyBoots() const { return checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS); }
    void onPlayerNoDraw() { onNoResetFlg0(daPyFlg0_NO_DRAW); }
    void offPlayerNoDraw() { offNoResetFlg0(daPyFlg0_NO_DRAW); }
    void onHeavyState() { onNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    void offHeavyState() { offNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    
    void onNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 |= flag; }
    void offNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 &= ~flag; }
    bool checkNoResetFlg1(daPy_FLG1 flag) const { return mNoResetFlg1 & flag; }
    bool checkEquipDragonShield() const { return checkNoResetFlg1(daPy_FLG1_EQUIP_DRAGON_SHIELD); }
    void onNpcCall() { onNoResetFlg1(daPy_FLG1_NPC_CALL_COMMAND); }
    void offNpcCallCommand() { offNoResetFlg1(daPy_FLG1_NPC_CALL_COMMAND); }
    bool checkNpcCallCommand() const { return checkNoResetFlg1(daPy_FLG1_NPC_CALL_COMMAND); }
    void onForceVomitJump() { onNoResetFlg1(daPy_FLG1_FORCE_VOMIT_JUMP); }
    void onNpcNotChange() { onNoResetFlg1(daPy_FLG1_NPC_NOT_CHANGE); }
    void offNpcNotChange() { offNoResetFlg1(daPy_FLG1_NPC_NOT_CHANGE); }
    void onConfuse() { onNoResetFlg1(daPy_FLG1_CONFUSE); }
    void offConfuse() { offNoResetFlg1(daPy_FLG1_CONFUSE); }
    bool checkConfuse() const { return checkNoResetFlg1(daPy_FLG1_CONFUSE); }
    void onShipTact() { onNoResetFlg1(daPy_FLG1_SHIP_TACT); }
    void offShipTact() { offNoResetFlg1(daPy_FLG1_SHIP_TACT); }
    void onUseArrowEffect() { onNoResetFlg1(daPy_FLG1_USE_ARROW_EFFECT); }
    void offUseArrowEffect() { offNoResetFlg1(daPy_FLG1_USE_ARROW_EFFECT); }
    void onLetterReadEyeMove() { onNoResetFlg1(daPy_FLG1_LETTER_READ_EYE_MOVE); }
    bool checkForestWaterUse() const { return checkNoResetFlg1(daPy_FLG1_FOREST_WATER_USE); }
    void onWaterDrop() { onNoResetFlg1(daPy_FLG1_WATER_DROP); }
    void onVineCatch() { onNoResetFlg1(daPy_FLG1_VINE_CATCH); }
    bool checkLastComboWait() const { return checkNoResetFlg1(daPy_FLG1_LAST_COMBO_WAIT); }
    
    virtual MtxP getLeftHandMatrix() = 0;
    virtual MtxP getRightHandMatrix() = 0;
    virtual void getGroundY() = 0;
    virtual void getTactMusic() const;
    virtual void getTactTimerCancel() const;
    virtual BOOL checkPlayerGuard() const;
    virtual void getGrabMissActor();
    virtual u32 checkPlayerFly() const;
    virtual void checkFrontRoll() const;
    virtual void checkBottleSwing() const;
    virtual void checkCutCharge() const;
    virtual void getBokoFlamePos(cXyz*);
    virtual void checkTactWait() const;
    virtual void setTactZev(unsigned int, int, char*);
    virtual void onDekuSpReturnFlg(u8);
    virtual void checkComboCutTurn() const;
    virtual f32 getBaseAnimeFrameRate() = 0;
    virtual void getBaseAnimeFrame() = 0;
    virtual void getItemID() const;
    virtual void getThrowBoomerangID() const;
    virtual u32 getGrabActorID() const;
    virtual void checkGrabBarrel();
    virtual void checkPlayerNoDraw();
    virtual void checkRopeTag();
    virtual void checkRopeReadyAnime() const;
    virtual void voiceStart(u32);
    virtual void setOutPower(f32, s16, int);
    virtual void onFrollCrashFlg(u32);
    virtual void getModelJointMtx(u16);
    virtual void getOldSpeedY();
    virtual void setHookshotCarryOffset(unsigned int, const cXyz*);
    virtual void setPlayerPosAndAngle(cXyz*, s16);
    virtual void setPlayerPosAndAngle(cXyz*, csXyz*);
    virtual void setPlayerPosAndAngle(MtxP);
    virtual void setThrowDamage(cXyz*, s16, f32, f32, int);
    virtual void changeTextureAnime(u16, u16, int);
    virtual void cancelChangeTextureAnime();
    
    void getSwordTopPos() const;
    void getLeftHandPos() const;
    void getRopeJumpLand() const;
    void checkRopeForceEnd() const;
    cXyz getHeadTopPos() const { return mHeadTopPos; }
    void changePlayer(fopAc_ac_c*);
    void objWindHitCheck(dCcD_Cyl*);
    void setDoButtonQuake();
    void stopDoButtonQuake(int);
    void getRopePos() const;
};

#endif /* D_A_PLAYER */
