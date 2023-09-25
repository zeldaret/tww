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

class daPy_mtxFollowEcallBack_c {
public:
    void execute(JPABaseEmitter*);
    void end();
    void makeEmitter(unsigned short, float(*)[4], const cXyz*, const cXyz*);
    void makeEmitterColor(unsigned short, float(*)[4], const cXyz*, const _GXColor*, const _GXColor*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);

    /* 0x0 */ u8 field_0x0[0xC];
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

    /* 0x290 */ u8 mAttackState;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292[0x294 - 0x292];
    /* 0x294 */ s16 field_0x294;
    /* 0x296 */ s16 mQuakeTimer;
    /* 0x298 */ int field_0x298;
    /* 0x29C */ u32 field_0x29c;
    /* 0x2A0 */ u32 field_0x2a0;
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
    /* 0x2F8 */ f32 field_0x2f8;
    /* 0x2FC */ u8 field_0x2FC[0x300 - 0x2FC];
    /* 0x300 */ f32 field_0x300;
    /* 0x304 */ daPy_demo_c mDemo;

    s16 getBodyAngleX() { return mBodyAngle.x; }
    s16 getBodyAngleY() { return mBodyAngle.y; }

    virtual MtxP getLeftHandMatrix() = 0;
    virtual MtxP getRightHandMatrix() = 0;
    virtual void getGroundY() = 0;
    virtual void getTactMusic() const;
    virtual void getTactTimerCancel() const;
    virtual void checkPlayerGuard() const;
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
    virtual void getGrabActorID() const;
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
    virtual void setPlayerPosAndAngle(float (*)[4]);
    virtual void setThrowDamage(cXyz*, s16, f32, f32, int);
    virtual void changeTextureAnime(u16, u16, int);
    virtual void cancelChangeTextureAnime();
    
    void getSwordTopPos() const;
    void getLeftHandPos() const;
    void getRopeJumpLand() const;
    void checkRopeForceEnd() const;
    cXyz getHeadTopPos() const;
    void changePlayer(fopAc_ac_c*);
    void objWindHitCheck(dCcD_Cyl*);
    void setDoButtonQuake();
    void stopDoButtonQuake(int);
    void getRopePos() const;

    BOOL checkConfuse() { return field_0x2a0 & 0x100; }
};

#endif /* D_A_PLAYER */
