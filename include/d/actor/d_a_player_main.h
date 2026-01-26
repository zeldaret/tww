#ifndef D_A_PLAYER_MAIN
#define D_A_PLAYER_MAIN

#include "JAZelAudio/JAIZelBasic.h"
#include "d/d_attention.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_bg_w.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/res/res_link.h" // IWYU pragma: export
#include "d/res/res_lkanm.h"

class mDoExt_MtxCalcOldFrame;

class daPy_anmHeap_c {
public:
    /* 0x0 */ u16 mIdx;
    /* 0x2 */ u16 field_0x2;
    /* 0x4 */ u16 field_0x4;
    /* 0x6 */ u16 field_0x6;
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
    bool getLockFlg() { return mLockFlag; }
    void onLockFlg() {
        mLockFlag = true;
        mFrame = 0;
    }
    void offLockFlg() { mLockFlag = false; }
    void setPos(const cXyz* i_pos) { mPos = *i_pos; }
    void setSightTex(void* sightTex) { mpSightTex = sightTex; }
    void setLockTex(void* lockTex) { mpLockTex = lockTex; }
    void setImage(ResTIMG* image) { mpImg = image; }
    bool checkSEFrame() {
        // This implementation might be incomplete, debug map says it's 0x18 bytes but this line is only 0x10 bytes.
        return mFrame == 0;
    }
    void incFrame() {
        mFrame++;
        if(mFrame == 26) {
            mFrame = 0;
        }
    }

private:
    /* 0x04 */ bool mDrawFlag;
    /* 0x05 */ bool mLockFlag;
    /* 0x06 */ u8 mFrame;
    /* 0x07 */ u8 mLockAlpha;
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ Mtx mMtx;
    /* 0x44 */ ResTIMG* mpImg;
    /* 0x48 */ void* mpLockTex;
    /* 0x4C */ void* mpSightTex;
};

class daPy_actorKeep_c {
public:
    daPy_actorKeep_c() {}

    void setActor();
    void setData(fopAc_ac_c*);
    void clearData();

    fpc_ProcID getID() const { return mID; }
    fopAc_ac_c* getActor() { return mActor; }

private:
    /* 0x0 */ fpc_ProcID mID;
    /* 0x4 */ fopAc_ac_c* mActor;
};  // Size: 0x8

class daPy_footEffect_c {
public:
    ~daPy_footEffect_c() {}
    daPy_footEffect_c() {}
    
    dPa_smokeEcallBack* getSmokeCallBack() { return &mSmokeCb; }
    dPa_followEcallBack* getOtherCallBack() { return &mFollowCb; }

    void setID(s32 id) { mId = id; }
    s32 getID() const { return mId; }
    void setAngle(csXyz* angle) { mAngle = *angle; }
    csXyz& getAngle() { return mAngle; }
    void setPos(const cXyz* pos) { mPos = *pos; }
    cXyz& getPos() { return mPos; }

private:
    /* 0x00 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x20 */ dPa_followEcallBack mFollowCb;
    /* 0x34 */ cXyz mPos;
    /* 0x40 */ csXyz mAngle;
    /* 0x48 */ s32 mId;
};

class daPy_fanSwingEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    ~daPy_fanSwingEcallBack_c() {}
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) {
        emitter->becomeImmortalEmitter();
        mpEmitter = emitter;
        mAlphaOutFlg = FALSE;
    }
    
    void onAlphaOutFlg() { mAlphaOutFlg = TRUE; }
    JPABaseEmitter* getEmitter() { return mpEmitter; }
    
    void deleteCallBack() {
        if(mpEmitter) {
            mpEmitter->quitImmortalEmitter();
            mpEmitter->setEmitterCallBackPtr(NULL);
            mpEmitter = NULL;
        }
    }
    
protected:
    /* 0x4 */ BOOL mAlphaOutFlg;
    /* 0x8 */ JPABaseEmitter* mpEmitter;
};  // Size: 0xC

class daPy_waterDropPcallBack_c : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    void execute(JPABaseEmitter*, JPABaseParticle*);
    ~daPy_waterDropPcallBack_c() {}

    void offWaterMark() { mbWaterMark = FALSE; }
    void onWaterMark() { mbWaterMark = TRUE; }

protected:
    /* 0x4 */ BOOL mbWaterMark;
    /* 0x8 */ dBgS_ObjGndChk mGndChk;
};

class daPy_swimTailEcallBack_c : public dPa_levelEcallBack {
public:
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void getMaxWaterY(JGeometry::TVec3<f32>*);
    void remove();
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    ~daPy_swimTailEcallBack_c() {}
    daPy_swimTailEcallBack_c() {}
    
    void onEnd() {
        mbEnd = true;
        field_0x20 = NULL;
    }
    bool getEnd() { return mbEnd; }

    void onRightFlg() { field_0x05 = true; }

    JPABaseEmitter* getEmitter() { return mpEmitter; }
    cXyz& getPos() { return mPos; }
    void setPos(cXyz& pos) { mPos = pos; }

    void setSpeedRate(f32 rate) { mSpeedRate = rate; }
    void setWaterY(f32 y) { mWaterY = y; }
    void setWaterFlatY(f32 y) { mWaterFlatY = y; }

protected:
    /* 0x04 */ bool mbEnd;
    /* 0x05 */ bool field_0x05;
    /* 0x08 */ f32 mSpeedRate;
    /* 0x0C */ f32 mWaterY;
    /* 0x10 */ f32 mWaterFlatY;
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ const csXyz* field_0x20;
    /* 0x24 */ JPABaseEmitter* mpEmitter;
};  // Size: 0x28

STATIC_ASSERT(sizeof(daPy_swimTailEcallBack_c) == 0x28);

class daPy_followEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();
    ~daPy_followEcallBack_c() {}

    JPABaseEmitter* getEmitter() { return mpEmitter; }
    cXyz& getPos() { return mPos; }
    void setPos(const cXyz* pos) { mPos = *pos; }
    void setAngle(s16 x, s16 y, s16 z) { mAngle.set(x, y, z); }

protected:
    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ csXyz mAngle;
};  // Size: 0x1C

class daPy_waterDropEcallBack_c : public daPy_followEcallBack_c {
public:
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();
    daPy_waterDropEcallBack_c() {}
    ~daPy_waterDropEcallBack_c() {}

    BOOL checkReady() { return field_0x1C; }
    void onReady() { field_0x1C = TRUE; }
    void offReady() { field_0x1C = FALSE; }

    static daPy_waterDropPcallBack_c* getPcallBack() { return &m_pcallback; }

protected:
    static daPy_waterDropPcallBack_c m_pcallback;

    /* 0x1C */ BOOL field_0x1C;
};  // Size: 0x20

class daPy_dmEcallBack_c : public daPy_mtxFollowEcallBack_c {
public:
    void execute(JPABaseEmitter*);
    ~daPy_dmEcallBack_c() {}
    daPy_dmEcallBack_c() {}
    
    static s16 getTimer() { return m_timer; }
    static void setTimer(s16 timer) { m_timer = timer; }
    static void decTimer() { m_timer--; }
    
    static bool checkFlame() { return m_type == 0; }
    static bool checkCurse() { return m_type == 1; }
    static bool checkElec() { return m_type == 2; }
    static void setType(u16 type) { m_type = type; }
    static void setFlame(s16 timer) {
        setType(0);
        setTimer(timer);
    }
    static void setCurse(s16 timer) {
        setType(1);
        setTimer(timer);
    }
    static void setElec(s16 timer) {
        setType(2);
        setTimer(timer);
    }

private:
    static s16 m_timer;
    static u16 m_type;
};  // Size: 0x0C

class daPy_mtxPosFollowEcallBack_c : public daPy_mtxFollowEcallBack_c {
public:
    void makeEmitterColor(u16, MtxP, const cXyz*, const csXyz*, const GXColor*, const GXColor*);
    void execute(JPABaseEmitter*);
    daPy_mtxPosFollowEcallBack_c() {}
    ~daPy_mtxPosFollowEcallBack_c() {}

protected:
    /* 0xC */ const csXyz* mpAngle;
};  // Size: 0x10

class daPy_matAnm_c : public J3DMaterialAnm {
public:
    daPy_matAnm_c();

    virtual ~daPy_matAnm_c() {}
    virtual void calc(J3DMaterial*) const;
    
    static u8 m_maba_timer;
    static u8 m_maba_flg;
    static u8 m_eye_move_flg;
    static u8 m_morf_frame;

    static void onMabaFlg() { m_maba_flg = 1; }
    static void offMabaFlg() {
        m_maba_flg = 0;
        m_maba_timer = 1;
    }
    static void decMabaTimer() { cLib_calcTimer(&m_maba_timer); }
    static void decMorfFrame() { cLib_calcTimer(&m_morf_frame); }
    static u8 getEyeMoveFlg() { return m_eye_move_flg; }
    static u8 getMabaFlg() { return m_maba_flg; }
    static u8 getMabaTimer() { return m_maba_timer; }
    static u8 getMorfFrame() { return m_morf_frame; }
    static void offEyeMoveFlg() { m_eye_move_flg = 0; }
    static void onEyeMoveFlg() { m_eye_move_flg = 1; }
    static void setMabaTimer(u8 timer) { m_maba_timer = timer; }
    static void setMorfFrame(u8 frame) { m_morf_frame = frame; }

    // TODO:
    void getNowOffsetXP() {}
    void getNowOffsetYP() {}
    void setNowOffsetX(f32 x) { mEyePos.x = x; }
    void setNowOffsetY(f32 y) { mEyePos.y = y; }

public:
    /* 0x6C */ cXy mEyePosOld;
    /* 0x74 */ cXy mEyePos;
};  // Size: 0x7C

class daPy_swBlur_c : public J3DPacket {
public:
    enum BlurColorType {
        NORMAL_SLASH_BLUR,
        ELIXIR_SOUP_SLASH_BLUR,
        PARRYING_SLASH_BLUR,
    };

    void initSwBlur(MtxP, int, f32, int);
    void copySwBlur(MtxP, int);
    void draw();
    ~daPy_swBlur_c() {}

public:
    /* 0x010 */ ResTIMG* mpTex;
    /* 0x014 */ int field_0x014;
    /* 0x018 */ int field_0x018;
    /* 0x01C */ int mBlurColorType;
    /* 0x020 */ f32 mBlurTopRate;
    /* 0x024 */ Vec* mpPosBuffer;
    /* 0x028 */ cXyz field_0x028;
    /* 0x034 */ cXyz field_0x034[60];
    /* 0x304 */ cXyz field_0x304[60];
};

class daPy_footData_c {
public:
    ~daPy_footData_c();
    daPy_footData_c();

public:
    /* 0x000 */ u8 field_0x000;
    /* 0x001 */ u8 field_0x001;
    /* 0x002 */ s16 field_0x002;
    /* 0x004 */ s16 field_0x004;
    /* 0x006 */ s16 field_0x006;
    /* 0x008 */ s16 field_0x008;
    /* 0x00A */ s16 field_0x00A;
    /* 0x00C */ cXyz field_0x00C;
    /* 0x018 */ cXyz field_0x018;
    /* 0x024 */ cXyz field_0x024;
    /* 0x030 */ f32 field_0x030;
    /* 0x034 */ dBgS_LinkGndChk field_0x034;
    /* 0x088 */ Mtx field_0x088[3];
};  // Size: 0x118

class daPy_aura_c {
public:
    void setModel(J3DModel* model) { mpYaura00Model = model; }
    J3DModel* getModel() { return mpYaura00Model; }
    void setFrame(f32 frame) { mFrame = frame; }
    f32 getFrame() { return mFrame; }

private:
    /* 0x00 */ J3DModel* mpYaura00Model;
    /* 0x04 */ f32 mFrame;
};  // Size: 0x08

class daPy_anmIndex_c {
public:
    /* 0x00 */ u16 mUnderBckIdx;
    /* 0x02 */ u16 mUpperBckIdx;
};

class daPy_HIO_c {
public:
    daPy_HIO_c();

public:
    daPy_HIO_basic_c0 mBasic;
    daPy_HIO_move_c0 mMove;
    daPy_HIO_atnMove_c0 mAtnMove;
    daPy_HIO_atnMoveB_c0 mAtnMoveB;
    daPy_HIO_turn_c0 mTurn;
    daPy_HIO_cut_c0 mCut;
    daPy_HIO_roll_c0 mRoll;
    daPy_HIO_backJump_c0 mBackJump;
    daPy_HIO_slip_c0 mSlip;
    daPy_HIO_slide_c0 mSlide;
    daPy_HIO_autoJump_c0 mAutoJump;
    daPy_HIO_fall_c0 mFall;
    daPy_HIO_swim_c0 mSwim;
    daPy_HIO_battle_c0 mBattle;
    daPy_HIO_wall_c0 mWall;
    daPy_HIO_smallJump_c0 mSmallJump;
    daPy_HIO_wallCatch_c0 mWallCatch;
    daPy_HIO_hang_c0 mHang;
    daPy_HIO_guard_c0 mGuard;
    daPy_HIO_nockback_c0 mNockback;
    daPy_HIO_iceSlip_c0 mIceSlip;
    daPy_HIO_dam_c0 mDam;
    daPy_HIO_slowJump_c0 mSlowJump;
    daPy_HIO_sideStep_c0 mSideStep;
    daPy_HIO_grab_c0 mGrab;
    daPy_HIO_ladder_c0 mLadder;
    daPy_HIO_crouch_c0 mCrouch;
    daPy_HIO_pushpull_c0 mPushpull;
    daPy_HIO_item_c0 mItem;
    daPy_HIO_ship_c0 mShip;
    daPy_HIO_restart_c0 mRestart;
    daPy_HIO_holdup_c0 mHoldup;
    daPy_HIO_vomit_c0 mVomit;
    daPy_HIO_warp_c0 mWarp;
    u8 pad[0x3F - 0x22];
};  // Size: 0x3F

class daPy_lk_c : public daPy_py_c {
public:
    enum daPy_PROC {
        daPyProc_SCOPE_e = 0x00,
        daPyProc_SUBJECTIVITY_e = 0x01,
        daPyProc_CALL_e = 0x02,
        daPyProc_CONTROLL_WAIT_e = 0x03,
        daPyProc_WAIT_e = 0x04,
        daPyProc_FREE_WAIT_e = 0x05,
        daPyProc_MOVE_e = 0x06,
        daPyProc_ATN_MOVE_e = 0x07,
        daPyProc_ATN_ACTOR_WAIT_e = 0x08,
        daPyProc_ATN_ACTOR_MOVE_e = 0x09,
        daPyProc_SIDE_STEP_e = 0x0A,
        daPyProc_SIDE_STEP_LAND_e = 0x0B,
        daPyProc_CROUCH_DEFENSE_e = 0x0C,
        daPyProc_CROUCH_DEFENSE_SLIP_e = 0x0D,
        daPyProc_CROUCH_e = 0x0E,
        daPyProc_CRAWL_START_e = 0x0F,
        daPyProc_CRAWL_MOVE_e = 0x10,
        daPyProc_CRAWL_AUTO_MOVE_e = 0x11,
        daPyProc_CRAWL_END_e = 0x12,
        daPyProc_WHIDE_READY_e = 0x13,
        daPyProc_WHIDE_WAIT_e = 0x14,
        daPyProc_WHIDE_MOVE_e = 0x15,
        daPyProc_WHIDE_PEEP_e = 0x16,
        daPyProc_WAIT_TURN_e = 0x17,
        daPyProc_MOVE_TURN_e = 0x18,
        daPyProc_SLIP_e = 0x19,
        daPyProc_SLIDE_FRONT_e = 0x1A,
        daPyProc_SLIDE_BACK_e = 0x1B,
        daPyProc_SLIDE_FRONT_LAND_e = 0x1C,
        daPyProc_SLIDE_BACK_LAND_e = 0x1D,
        daPyProc_FRONT_ROLL_e = 0x1E,
        daPyProc_FRONT_ROLL_CRASH_e = 0x1F,
        daPyProc_NOCK_BACK_END_e = 0x20,
        daPyProc_SIDE_ROLL_e = 0x21,
        daPyProc_BACK_JUMP_e = 0x22,
        daPyProc_BACK_JUMP_LAND_e = 0x23,
        daPyProc_AUTO_JUMP_e = 0x24,
        daPyProc_LAND_e = 0x25,
        daPyProc_LAND_DAMAGE_e = 0x26,
        daPyProc_FALL_e = 0x27,
        daPyProc_SLOW_FALL_e = 0x28,
        daPyProc_SMALL_JUMP_e = 0x29,
        daPyProc_VERTICAL_JUMP_e = 0x2A,
        daPyProc_HANG_START_e = 0x2B,
        daPyProc_HANG_FALL_START_e = 0x2C,
        daPyProc_HANG_UP_e = 0x2D,
        daPyProc_HANG_WAIT_e = 0x2E,
        daPyProc_HANG_MOVE_e = 0x2F,
        daPyProc_HANG_CLIMB_e = 0x30,
        daPyProc_HANG_WALL_CATCH_e = 0x31,
        daPyProc_PUSH_PULL_WAIT_e = 0x32,
        daPyProc_PUSH_MOVE_e = 0x33,
        daPyProc_PULL_MOVE_e = 0x34,
        daPyProc_SWIM_UP_e = 0x35,
        daPyProc_SWIM_WAIT_e = 0x36,
        daPyProc_SWIM_MOVE_e = 0x37,
        daPyProc_LADDER_UP_START_e = 0x38,
        daPyProc_LADDER_UP_END_e = 0x39,
        daPyProc_LADDER_DOWN_START_e = 0x3A,
        daPyProc_LADDER_DOWN_END_e = 0x3B,
        daPyProc_LADDER_MOVE_e = 0x3C,
        daPyProc_CLIMB_UP_START_e = 0x3D,
        daPyProc_CLIMB_DOWN_START_e = 0x3E,
        daPyProc_CLIMB_MOVE_UP_DOWN_e = 0x3F,
        daPyProc_CLIMB_MOVE_SIDE_e = 0x40,
        daPyProc_CUT_A_e = 0x41,
        daPyProc_CUT_F_e = 0x42,
        daPyProc_CUT_R_e = 0x43,
        daPyProc_CUT_L_e = 0x44,
        daPyProc_CUT_EA_e = 0x45,
        daPyProc_CUT_EB_e = 0x46,
        daPyProc_CUT_EX_A_e = 0x47,
        daPyProc_CUT_EX_B_e = 0x48,
        daPyProc_CUT_EX_MJ_e = 0x49,
        daPyProc_CUT_KESA_e = 0x4A,
        daPyProc_WEAPON_NORMAL_SWING_e = 0x4B,
        daPyProc_WEAPON_SIDE_SWING_e = 0x4C,
        daPyProc_WEAPON_FRONT_SWING_READY_e = 0x4D,
        daPyProc_WEAPON_FRONT_SWING_e = 0x4E,
        daPyProc_WEAPON_FRONT_SWING_END_e = 0x4F,
        daPyProc_WEAPON_THROW_e = 0x50,
        daPyProc_HAMMER_SIDE_SWING_e = 0x51,
        daPyProc_HAMMER_FRONT_SWING_READY_e = 0x52,
        daPyProc_HAMMER_FRONT_SWING_e = 0x53,
        daPyProc_HAMMER_FRONT_SWING_END_e = 0x54,
        daPyProc_CUT_TURN_e = 0x55,
        daPyProc_CUT_ROLL_e = 0x56,
        daPyProc_CUT_ROLL_END_e = 0x57,
        daPyProc_CUT_TURN_CHARGE_e = 0x58,
        daPyProc_CUT_TURN_MOVE_e = 0x59,
        daPyProc_CUT_REVERSE_e = 0x5A,
        daPyProc_JUMP_CUT_e = 0x5B,
        daPyProc_JUMP_CUT_LAND_e = 0x5C,
        daPyProc_BT_JUMP_e = 0x5D,
        daPyProc_BT_JUMP_CUT_e = 0x5E,
        daPyProc_BT_SLIDE_e = 0x5F,
        daPyProc_BT_ROLL_e = 0x60,
        daPyProc_BT_ROLL_CUT_e = 0x61,
        daPyProc_BT_VERTICAL_JUMP_e = 0x62,
        daPyProc_BT_VERTICAL_JUMP_CUT_e = 0x63,
        daPyProc_BT_VERTICAL_JUMP_LAND_e = 0x64,
        daPyProc_GUARD_CRASH_e = 0x65,
        daPyProc_DAMAGE_e = 0x66,
        daPyProc_POLY_DAMAGE_e = 0x67,
        daPyProc_LARGE_DAMAGE_e = 0x68,
        daPyProc_LARGE_DAMAGE_UP_e = 0x69,
        daPyProc_LARGE_DAMAGE_WALL_e = 0x6A,
        daPyProc_LAVA_DAMAGE_e = 0x6B,
        daPyProc_ELEC_DAMAGE_e = 0x6C,
        daPyProc_GUARD_SLIP_e = 0x6D,
        daPyProc_GRAB_READY_e = 0x6E,
        daPyProc_GRAB_UP_e = 0x6F,
        daPyProc_GRAB_MISS_e = 0x70,
        daPyProc_GRAB_THROW_e = 0x71,
        daPyProc_GRAB_PUT_e = 0x72,
        daPyProc_GRAB_WAIT_e = 0x73,
        daPyProc_GRAB_HEAVY_WAIT_e = 0x74,
        daPyProc_GRAB_REBOUND_e = 0x75,
        daPyProc_ROPE_SUBJECT_e = 0x76,
        daPyProc_ROPE_READY_e = 0x77,
        daPyProc_ROPE_SWING_e = 0x78,
        daPyProc_ROPE_HANG_WAIT_e = 0x79,
        daPyProc_ROPE_UP_e = 0x7A,
        daPyProc_ROPE_DOWN_e = 0x7B,
        daPyProc_ROPE_SWING_START_e = 0x7C,
        daPyProc_ROPE_MOVE_e = 0x7D,
        daPyProc_ROPE_THROW_CATCH_e = 0x7E,
        daPyProc_ROPE_UP_HANG_e = 0x7F,
        daPyProc_BOOMERANG_SUBJECT_e = 0x80,
        daPyProc_BOOMERANG_MOVE_e = 0x81,
        daPyProc_BOOMERANG_CATCH_e = 0x82,
        daPyProc_HOOKSHOT_SUBJECT_e = 0x83,
        daPyProc_HOOKSHOT_MOVE_e = 0x84,
        daPyProc_HOOKSHOT_FLY_e = 0x85,
        daPyProc_SHIP_READY_e = 0x86,
        daPyProc_SHIP_JUMP_RIDE_e = 0x87,
        daPyProc_SHIP_STEER_e = 0x88,
        daPyProc_SHIP_PADDLE_e = 0x89,
        daPyProc_SHIP_SCOPE_e = 0x8A,
        daPyProc_SHIP_BOOMERANG_e = 0x8B,
        daPyProc_SHIP_HOOKSHOT_e = 0x8C,
        daPyProc_SHIP_BOW_e = 0x8D,
        daPyProc_SHIP_CANNON_e = 0x8E,
        daPyProc_SHIP_CRANE_e = 0x8F,
        daPyProc_SHIP_GET_OFF_e = 0x90,
        daPyProc_SHIP_RESTART_e = 0x91,
        daPyProc_FAN_SWING_e = 0x92,
        daPyProc_FAN_GLIDE_e = 0x93,
        daPyProc_BOW_SUBJECT_e = 0x94,
        daPyProc_BOW_MOVE_e = 0x95,
        daPyProc_VOMIT_READY_e = 0x96,
        daPyProc_VOMIT_WAIT_e = 0x97,
        daPyProc_VOMIT_JUMP_e = 0x98,
        daPyProc_VOMIT_LAND_e = 0x99,
        daPyProc_TACT_WAIT_e = 0x9A,
        daPyProc_TACT_PLAY_e = 0x9B,
        daPyProc_TACT_PLAY_END_e = 0x9C,
        daPyProc_TACT_PLAY_ORIGINAL_e = 0x9D,
        daPyProc_ICE_SLIP_FALL_e = 0x9E,
        daPyProc_ICE_SLIP_FALL_UP_e = 0x9F,
        daPyProc_ICE_SLIP_ALMOST_FALL_e = 0xA0,
        daPyProc_BOOTS_EQUIP_e = 0xA1,
        daPyProc_NOT_USE_e = 0xA2,
        daPyProc_BOTTLE_DRINK_e = 0xA3,
        daPyProc_BOTTLE_OPEN_e = 0xA4,
        daPyProc_BOTTLE_SWING_e = 0xA5,
        daPyProc_BOTTLE_GET_e = 0xA6,
        daPyProc_FOOD_THROW_e = 0xA7,
        daPyProc_FOOD_SET_e = 0xA8,
        daPyProc_DEMO_TOOL_e = 0xA9,
        daPyProc_DEMO_TALK_e = 0xAA,
        daPyProc_DEMO_DAMAGE_e = 0xAB,
        daPyProc_DEMO_HOLDUP_e = 0xAC,
        daPyProc_DEMO_OPEN_TREASURE_e = 0xAD,
        daPyProc_DEMO_GET_ITEM_e = 0xAE,
        daPyProc_DEMO_UNEQUIP_e = 0xAF,
        daPyProc_DEMO_LAVA_DAMAGE_e = 0xB0,
        daPyProc_DEMO_FREEZE_DAMAGE_e = 0xB1,
        daPyProc_DEMO_DEAD_e = 0xB2,
        daPyProc_DEMO_LOOK_AROUND_e = 0xB3,
        daPyProc_DEMO_SALUTE_e = 0xB4,
        daPyProc_DEMO_LOOK_AROUND2_e = 0xB5,
        daPyProc_DEMO_TALISMAN_PICKUP_e = 0xB6,
        daPyProc_DEMO_TALISMAN_WAIT_e = 0xB7,
        daPyProc_DEMO_SURPRISED_e = 0xB8,
        daPyProc_DEMO_TURN_BACK_e = 0xB9,
        daPyProc_DEMO_LOOK_UP_e = 0xBA,
        daPyProc_DEMO_QUAKE_WAIT_e = 0xBB,
        daPyProc_DEMO_DANCE_e = 0xBC,
        daPyProc_DEMO_CAUGHT_e = 0xBD,
        daPyProc_DEMO_LOOK_WAIT_e = 0xBE,
        daPyProc_DEMO_PUSH_PULL_WAIT_e = 0xBF,
        daPyProc_DEMO_PUSH_MOVE_e = 0xC0,
        daPyProc_DEMO_DOOR_OPEN_e = 0xC1,
        daPyProc_DEMO_NOD_e = 0xC2,
        daPyProc_DEMO_PRESENT_e = 0xC3,
        daPyProc_DEMO_WIND_CHANGE_e = 0xC4,
        daPyProc_DEMO_STAND_ITEM_PUT_e = 0xC5,
        daPyProc_DEMO_VORCANO_FAIL_e = 0xC6,
        daPyProc_DEMO_SLIGHT_SURPRISED_e = 0xC7,
        daPyProc_DEMO_SMILE_e = 0xC8,
        daPyProc_DEMO_BOSS_WARP_e = 0xC9,
        daPyProc_DEMO_AGB_USE_e = 0xCA,
        daPyProc_DEMO_LOOK_TURN_e = 0xCB,
        daPyProc_DEMO_LETTER_OPEN_e = 0xCC,
        daPyProc_DEMO_LETTER_READ_e = 0xCD,
        daPyProc_DEMO_REDEAD_STOP_e = 0xCE,
        daPyProc_DEMO_REDEAD_CATCH_e = 0xCF,
        daPyProc_DEMO_GET_DANCE_e = 0xD0,
        daPyProc_DEMO_BOTTLE_OPEN_FAIRY_e = 0xD1,
        daPyProc_DEMO_WARP_SHORT_e = 0xD2,
        daPyProc_DEMO_OPEN_SALVAGE_TREASURE_e = 0xD3,
        daPyProc_DEMO_SURPRISED_WAIT_e = 0xD4,
        daPyProc_DEMO_POWER_UP_WAIT_e = 0xD5,
        daPyProc_DEMO_POWER_UP_e = 0xD6,
        daPyProc_DEMO_SHIP_SIT_e = 0xD7,
        daPyProc_DEMO_LAST_COMBO_e = 0xD8,
        daPyProc_DEMO_HAND_UP_e = 0xD9,
        daPyProc_DEMO_ICE_SLIP_e = 0xDA,
    };

    enum daPy_ANM {
        ANM_WAITS = 0x00,
        ANM_WALK = 0x01,
        ANM_DASH = 0x02,
        ANM_DASHKAZE = 0x03,
        ANM_WALKHBOOTS = 0x04,
        ANM_WALKHBOOTSKAZE = 0x05,
        ANM_WALKSLOPE = 0x06,
        ANM_ATNLS = 0x07,
        ANM_ATNRS = 0x08,
        ANM_ATNWLS = 0x09,
        ANM_ATNWRS = 0x0A,
        ANM_ATNDLS = 0x0B,
        ANM_ATNDRS = 0x0C,
        ANM_JMPEDS = 0x0D,
        ANM_ATNWB = 0x0E,
        ANM_ATNDB = 0x0F,
        ANM_ATNJL = 0x10,
        ANM_ATNJR = 0x11,
        ANM_ATNJLLAND = 0x12,
        ANM_ATNJRLAND = 0x13,
        ANM_ROT = 0x14,
        ANM_CUTREL = 0x15,
        ANM_DIFENCE = 0x16,
        ANM_DIFENCEA = 0x17,
        ANM_CUTTURNP = 0x18,
        ANM_CUTTURNPWFB = 0x19,
        ANM_CUTTURNPWLR = 0x1A,
        ANM_TALKA = 0x1B,
        ANM_WAITB = 0x1C,
        ANM_WAITATOB = 0x1D,
        ANM_CUTA = 0x1E,
        ANM_CUTF = 0x1F,
        ANM_CUTR = 0x20,
        ANM_CUTL = 0x21,
        ANM_CUTEA = 0x22,
        ANM_CUTEB = 0x23,
        ANM_EXCA1 = 0x24,
        ANM_EXCB1 = 0x25,
        ANM_CUTBOKO = 0x26,
        ANM_CUTRER = 0x27,
        ANM_CUTTURN = 0x28,
        ANM_CUTTURNC = 0x29,
        ANM_CUTTURNB = 0x2A,
        ANM_JATTACK = 0x2B,
        ANM_JATTCKP = 0x2C,
        ANM_JATTCKCUT = 0x2D,
        ANM_JATTCKCUTHAM = 0x2E,
        ANM_JATTACKLAND = 0x2F,
        ANM_LANDDAMA = 0x30,
        ANM_LANDDAMAST = 0x31,
        ANM_ROLLF = 0x32,
        ANM_ROLLFMIS = 0x33,
        ANM_SLIP = 0x34,
        ANM_SLIDEF = 0x35,
        ANM_SLIDEFLAND = 0x36,
        ANM_SLIDEB = 0x37,
        ANM_SLIDEBLAND = 0x38,
        ANM_ATNGAL = 0x39,
        ANM_ATNGAR = 0x3A,
        ANM_ATNGAHAM = 0x3B,
        ANM_JMPST = 0x3C,
        ANM_ROLLB = 0x3D,
        ANM_ROLLBLAND = 0x3E,
        ANM_CROUCH = 0x3F,
        ANM_LIE = 0x40,
        ANM_LIEFORWARD = 0x41,
        ANM_WALL = 0x42,
        ANM_WALLDW = 0x43,
        ANM_WALLWL = 0x44,
        ANM_WALLWR = 0x45,
        ANM_WALLWLDW = 0x46,
        ANM_WALLWRDW = 0x47,
        ANM_WALLPL = 0x48,
        ANM_WALLPR = 0x49,
        ANM_WALLPLDW = 0x4A,
        ANM_WALLPRDW = 0x4B,
        ANM_VJMP = 0x4C,
        ANM_VJMPCHA = 0x4D,
        ANM_VJMPCHB = 0x4E,
        ANM_VJMPCL = 0x4F,
        ANM_HANGING = 0x50,
        ANM_HANGUP = 0x51,
        ANM_HANGMOVEL = 0x52,
        ANM_HANGMOVER = 0x53,
        ANM_DAM = 0x54,
        ANM_DAML = 0x55,
        ANM_DAMR = 0x56,
        ANM_DAMF = 0x57,
        ANM_DAMB = 0x58,
        ANM_DAMFL = 0x59,
        ANM_DAMFR = 0x5A,
        ANM_DAMFF = 0x5B,
        ANM_DAMFB = 0x5C,
        ANM_DAMFLUP = 0x5D,
        ANM_DAMFRUP = 0x5E,
        ANM_DAMFFUP = 0x5F,
        ANM_DAMFBUP = 0x60,
        ANM_LAVADAM = 0x61,
        ANM_DIELONG = 0x62,
        ANM_SHIPDIE = 0x63,
        ANM_SWIMDIE = 0x64,
        ANM_GRABP = 0x65,
        ANM_GRABUP = 0x66,
        ANM_GRABNG = 0x67,
        ANM_GRABWAIT = 0x68,
        ANM_GRABWAITB = 0x69,
        ANM_GRABTHROW = 0x6A,
        ANM_GRABRE = 0x6B,
        ANM_MJMP = 0x6C,
        ANM_MJMPC = 0x6D,
        ANM_MROLLL = 0x6E,
        ANM_MROLLR = 0x6F,
        ANM_MROLLLC = 0x70,
        ANM_MROLLRC = 0x71,
        ANM_MSTEPOVER = 0x72,
        ANM_MSTEPOVERA = 0x73,
        ANM_MSTEPOVERLAND = 0x74,
        ANM_ROPECATCH = 0x75,
        ANM_ROPESWINGF = 0x76,
        ANM_ROPESWINGB = 0x77,
        ANM_ROPEWAIT = 0x78,
        ANM_ROPECLIMB = 0x79,
        ANM_ROPEDOWN = 0x7A,
        ANM_ROPETHROWCATCH = 0x7B,
        ANM_BOOMCATCH = 0x7C,
        ANM_VOYAGE1 = 0x7D,
        ANM_WAITPUSHPULL = 0x7E,
        ANM_WALKPUSH = 0x7F,
        ANM_WALKPULL = 0x80,
        ANM_SWIMP = 0x81,
        ANM_SWIMWAIT = 0x82,
        ANM_SWIMING = 0x83,
        ANM_LADDERUPST = 0x84,
        ANM_LADDERUPEDR = 0x85,
        ANM_LADDERUPEDL = 0x86,
        ANM_LADDERDWST = 0x87,
        ANM_LADDERDWEDR = 0x88,
        ANM_LADDERDWEDL = 0x89,
        ANM_LADDERRTOL = 0x8A,
        ANM_LADDERLTOR = 0x8B,
        ANM_FCLIMBSLIDELUP = 0x8C,
        ANM_FCLIMBSLIDERUP = 0x8D,
        ANM_BOXOPENLINK = 0x8E,
        ANM_BOXOPENSHORTLINK = 0x8F,
        ANM_ITEMGET = 0x90,
        ANM_HOLDUP = 0x91,
        ANM_WALLHOLDUP = 0x92,
        ANM_WALLHOLDUPDW = 0x93,
        ANM_COMEOUT = 0x94,
        ANM_WALKBARREL = 0x95,
        ANM_SALTATION = 0x96,
        ANM_WHO = 0x97,
        ANM_PICKUP = 0x98,
        ANM_WAITPICKUP = 0x99,
        ANM_SURPRISED = 0x9A,
        ANM_TURNBACK = 0x9B,
        ANM_LOOKUP = 0x9C,
        ANM_WAITQ = 0x9D,
        ANM_GLAD = 0x9E,
        ANM_SHIP_JUMP1 = 0x9F,
        ANM_SHIP_JUMP2 = 0xA0,
        ANM_USEFANA = 0xA1,
        ANM_USEFANB = 0xA2,
        ANM_USEFANB2 = 0xA3,
        ANM_MOGAKU1 = 0xA4,
        ANM_FM_BATA = 0xA5,
        ANM_HOOKSHOTJMP = 0xA6,
        ANM_VOMITJMP = 0xA7,
        ANM_WAITTAKT = 0xA8,
        ANM_SLIPICE = 0xA9,
        ANM_HAMSWINGA = 0xAA,
        ANM_HAMSWINGBPRE = 0xAB,
        ANM_HAMSWINGBHIT = 0xAC,
        ANM_HAMSWINGBEND = 0xAD,
        ANM_SETBOOTS = 0xAE,
        ANM_DOOROPENALINK = 0xAF,
        ANM_DOOROPENBLINK = 0xB0,
        ANM_SEYYES = 0xB1,
        ANM_PRESENTATIONA = 0xB2,
        ANM_WINDL = 0xB3,
        ANM_WINDR = 0xB4,
        ANM_PRESENTATIONB = 0xB5,
        ANM_BINDRINKPRE = 0xB6,
        ANM_BINDRINKING = 0xB7,
        ANM_BINDRINKAFTER = 0xB8,
        ANM_BINOPENPRE = 0xB9,
        ANM_BINOPENA = 0xBA,
        ANM_BINOPENB = 0xBB,
        ANM_BINSWINGS = 0xBC,
        ANM_BINSWINGU = 0xBD,
        ANM_BINGET = 0xBE,
        ANM_SURPRISEDB = 0xBF,
        ANM_RISE = 0xC0,
        ANM_USETCEIVER = 0xC1,
        ANM_YOBU = 0xC2,
        ANM_NENRIKI = 0xC3,
        ANM_ESAMAKI = 0xC4,
        ANM_SETHYOINOMI = 0xC5,
        ANM_GETLETTER = 0xC6,
        ANM_WAITLETTER = 0xC7,
        ANM_LINK_FREEZ = 0xC8,
        ANM_LINK_MOGAKI = 0xC9,
        ANM_TAKTDGE = 0xCA,
        ANM_DAMBIRI = 0xCB,
        ANM_SALVLR = 0xCC,
        ANM_SALVRWAIT = 0xCD,
        ANM_SALVLWAIT = 0xCE,
        ANM_SALVRBAD = 0xCF,
        ANM_SALVLBAD = 0xD0,
        ANM_SALVRGOOD = 0xD1,
        ANM_SALVLGOOD = 0xD2,
        ANM_MSTEPOVER_JMPED = 0xD3,
        ANM_BOXOPENSLINK = 0xD4,
        ANM_SEARESET = 0xD5,
        ANM_WARPIN = 0xD6,
        ANM_WARPOUT = 0xD7,
        ANM_SURPRISEDWAIT = 0xD8,
        ANM_PRESENTATIONAWAIT = 0xD9,
        ANM_POWUPWAIT = 0xDA,
        ANM_POWUP = 0xDB,
        ANM_KOSHIKAKE = 0xDC,
        ANM_COMBO_LINK = 0xDD,
        ANM_CUTKESA = 0xDE,
        ANM_WARPOUTFIRST = 0xDF,
        ANM_WAITAUCTION = 0xE0,
        ANM_FREEA = 0xE1,
        ANM_FREEB = 0xE2,
        ANM_FREED = 0xE3,
        ANM_TAKTKAZE = 0xE4,
        ANM_TAKTSIPPU = 0xE5,
        ANM_TAKTCHUYA = 0xE6,
        ANM_TAKTFUJIN = 0xE7,
        ANM_TAKTAYATSURI = 0xE8,
        ANM_TAKTCHISIN = 0xE9,
    };

    enum daPy_HEAP_TYPE {
        HEAP_TYPE_UNDER_UPPER_e = 0,
        HEAP_TYPE_TEXTURE_ANIME_e = 1,
        HEAP_TYPE_TEXTURE_SCROLL_e = 2,
        HEAP_TYPE_ITEM_ANIME_e = 3,
    };

    enum daPy_UNDER {
        UNDER_MOVE0_e = 0,
        UNDER_MOVE1_e = 1,
    };

    enum daPy_UPPER {
        UPPER_MOVE0_e = 0,
        UPPER_MOVE1_e = 1,
        UPPER_MOVE2_e = 2,
    };

    enum {
        PART_UNDER_e = 0,
        PART_UPPER_e = 1,
    };
    
    enum {
        ModeFlg_00000001 = 0x00000001,
        ModeFlg_MIDAIR   = 0x00000002,
        ModeFlg_00000004 = 0x00000004,
        ModeFlg_DAMAGE   = 0x00000008,
        ModeFlg_WHIDE    = 0x00000010,
        ModeFlg_HANG     = 0x00000020,
        ModeFlg_00000040 = 0x00000040,
        ModeFlg_00000080 = 0x00000080,
        ModeFlg_00000100 = 0x00000100,
        ModeFlg_HOOKSHOT = 0x00000200,
        ModeFlg_00000400 = 0x00000400,
        ModeFlg_ROPE     = 0x00000800,
        ModeFlg_00001000 = 0x00001000,
        ModeFlg_IN_SHIP  = 0x00002000,
        ModeFlg_00004000 = 0x00004000,
        ModeFlg_00008000 = 0x00008000,
        ModeFlg_CLIMB    = 0x00010000,
        ModeFlg_00020000 = 0x00020000,
        ModeFlg_SWIM     = 0x00040000,
        ModeFlg_00080000 = 0x00080000,
        ModeFlg_GRAB     = 0x00100000,
        ModeFlg_PUSHPULL = 0x00200000,
        ModeFlg_LADDER   = 0x00400000,
        ModeFlg_CROUCH   = 0x00800000,
        ModeFlg_CRAWL    = 0x01000000,
        ModeFlg_02000000 = 0x02000000,
        ModeFlg_04000000 = 0x04000000,
        ModeFlg_08000000 = 0x08000000,
        ModeFlg_CAUGHT   = 0x10000000,
        ModeFlg_SUBJECT  = 0x20000000,
        ModeFlg_40000000 = 0x40000000,
        ModeFlg_PARRY    = 0x80000000,
    };
    
    enum {
        daPyItem_NONE_e = 0x100,
        daPyItem_BOKO_e = 0x101,
        daPyItem_UNK102_e = 0x102,
        daPyItem_SWORD_e = 0x103,
        daPyItem_UNK104_e = 0x104,
        daPyItem_DRINK_BOTTLE_e = 0x105,
        daPyItem_OPEN_BOTTLE_e = 0x106,
        daPyItem_ESA_e = 0x107,
        daPyItem_BOW_e = 0x108,
        daPyItem_PHOTOBOX_e = 0x109,
        daPyItem_UNK10A_e = 0x10A,
        daPyItem_UNK10B_e = 0x10B,
    };
    
    enum daPy_lk_ITEM_BTN {
        /* 0x01 */ BTN_A = (1 << 0),
        /* 0x02 */ BTN_B = (1 << 1),
        /* 0x04 */ BTN_X = (1 << 2),
        /* 0x08 */ BTN_Y = (1 << 3),
        /* 0x10 */ BTN_Z = (1 << 4),
        /* 0x20 */ BTN_L = (1 << 5),
        /* 0x40 */ BTN_R = (1 << 6),
    };
    
    /**
     * Moving direction calculated from an angle
     */
    enum daPy_lk_DIR {
        /* 0x0 */ DIR_FORWARD,
        /* 0x1 */ DIR_BACKWARD,
        /* 0x2 */ DIR_LEFT,
        /* 0x3 */ DIR_RIGHT,
        /* 0x4 */ DIR_NONE,
    };
    
    typedef BOOL (daPy_lk_c::*ProcFunc)();
    
    void seStartOnlyReverb(u32);
    void seStartMapInfo(u32);
    void seStartSwordCut(u32);
    BOOL itemButton() const;
    BOOL itemTrigger() const;
    int getReadyItem();
    BOOL checkGroupItem(int, int);
    BOOL checkSetItemTrigger(int, int);
    BOOL auraJointCB0(int);
    BOOL jointBeforeCB(int, J3DTransformInfo*, Quaternion*);
    BOOL jointAfterCB(int, J3DTransformInfo*, Quaternion*);
    BOOL jointCB0(int);
    BOOL jointCB1();
    JKRHeap* setAnimeHeap(JKRSolidHeap*);
    JKRHeap* setItemHeap();
    void setBlurPosResource(u16);
    J3DAnmTransform* getItemAnimeResource(u16);
    J3DAnmTransform* getAnimeResource(daPy_anmHeap_c*, u16, u32);
    void getUnderUpperAnime(daPy_anmIndex_c const*, J3DAnmTransform**, J3DAnmTransform**, int, u32);
    void setTextureAnimeResource(J3DAnmTexPattern*, int);
    J3DAnmTexPattern* loadTextureAnimeResource(u32, BOOL);
    BOOL checkBossBgm();
    BOOL checkMabaAnimeBtp(int);
    u16 checkNormalFace();
    void setTextureAnime(u16, int);
    void setPriTextureAnime(u16, int);
    void resetPriTextureAnime();
    void setDemoTextureAnime(u16, u16, int, u16);
    void resetDemoTextureAnime();
    void setTextureScrollResource(J3DAnmTextureSRTKey*, int);
    J3DAnmTextureSRTKey* loadTextureScrollResource(u32, BOOL);
    void playTextureAnime();
    BOOL checkSightLine(f32, cXyz*);
    void setBootsModel(J3DModel**);
    s32 setItemModel();
    BOOL checkUpperReadyAnime() const;
    BOOL checkUpperReadyThrowAnime() const;
    BOOL checkNoCollisionCorret();
    s32 setDrawHandModel();
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
    BOOL setTalkStatus();
    int setHintActor();
    void setDoStatusBasic();
    void setDoStatus();
    int getDirectionFromAngle(s16);
    int getDirectionFromShapeAngle();
    int getDirectionFromCurrentAngle();
    void setNormalSpeedF(f32, f32, f32, f32);
    void posMoveFromFootPos();
    void posMove();
    void setShapeAngleToAtnActor();
    BOOL cancelItemUpperReadyAnime();
    s16 checkBodyAngleX(s16);
    BOOL setBodyAngleToCamera();
    void setBodyAngleXReadyAnime();
    void setSpeedAndAngleNormal(s16);
    void setSpeedAndAngleAtn();
    void setSpeedAndAngleAtnBack();
    void setSpeedAndAngleAtnActor();
    void setFrameCtrl(J3DFrameCtrl*, u8, s16, s16, f32, f32);
    BOOL checkAtnWaitAnime();
    void setBlendMoveAnime(f32);
    void setBlendAtnBackMoveAnime(f32);
    void setBlendAtnMoveAnime(f32);
    void setAnimeEquipSword(BOOL);
    void setAnimeEquipSingleItem(u16);
    void setAnimeEquipItem();
    void setAnimeUnequipSword();
    void setAnimeUnequipItem(u16);
    void setAnimeUnequip();
    BOOL checkBossGomaStage();
    BOOL checkSingleItemEquipAnime() const;
    BOOL checkItemEquipAnime() const;
    BOOL checkEquipAnime() const;
    void deleteEquipItem(BOOL);
    void setFallVoice();
    void keepItemData();
    void returnKeepItemData();
    void makeItemType();
    void setScopeModel();
    void setPhotoBoxModel();
    BOOL changeDragonShield(int);
    BOOL checkNewItemChange(u8);
    BOOL checkItemChangeFromButton();
    void checkItemAction();
    cM3dGPla* getSlidePolygon();
    BOOL checkJumpCutFromButton();
    int orderTalk();
    BOOL checkNextActionFromButton();
    void setShieldGuard();
    BOOL checkItemModeActorPointer();
    void checkNextActionItemFly();
    BOOL checkNextMode(int);
    BOOL checkIceSlipFall();
    void setFrontWallType();
    BOOL changeFrontWallTypeProc();
    int changeSlideProc();
    BOOL changeWaitProc();
    BOOL changeLandProc(f32);
    BOOL setDamagePoint(f32);
    BOOL checkNormalDamage(int);
    void setDashDamage();
    BOOL checkAtHitEnemy(dCcD_GObjInf*);
    BOOL checkElecReturnDamage(dCcD_GObjInf*, cXyz*);
    s32 checkWallAtributeDamage(dBgS_AcchCir*);
    BOOL changeDamageProc();
    BOOL changeAutoJumpProc();
    BOOL changeDemoProc();
    BOOL changeDeadProc();
    cXyz* getDamageVec(dCcD_GObjInf*);
    void setOldRootQuaternion(s16, s16, s16);
    BOOL checkRestHPAnime();
    BOOL checkHeavyStateOn();
    BOOL checkBottleItem(int) const;
    BOOL checkDrinkBottleItem(int) const;
    BOOL checkOpenBottleItem(int) const;
    BOOL checkBowItem(int) const;
    BOOL checkPhotoBoxItem(int) const;
    BOOL checkScopeEnd();
    void setSubjectMode();
    BOOL checkMaskDraw();
    BOOL checkSubjectEnd(BOOL);
    BOOL checkGuardAccept();
    void cancelNoDamageMode();
    BOOL commonProcInit(daPy_PROC proc);
    BOOL procScope_init(int);
    BOOL procScope();
    BOOL procSubjectivity_init(BOOL);
    BOOL procSubjectivity();
    BOOL procCall_init();
    BOOL procCall();
    BOOL procControllWait_init();
    BOOL procControllWait();
    BOOL procWait_init();
    BOOL procWait();
    BOOL procFreeWait_init();
    BOOL procFreeWait();
    BOOL procMove_init();
    BOOL procMove();
    BOOL procAtnMove_init();
    BOOL procAtnMove();
    BOOL procAtnActorWait_init();
    BOOL procAtnActorWait();
    BOOL procAtnActorMove_init();
    BOOL procAtnActorMove();
    BOOL procSideStep_init(int);
    BOOL procSideStep();
    BOOL procSideStepLand_init();
    BOOL procSideStepLand();
    BOOL procCrouchDefense_init();
    BOOL procCrouchDefense();
    BOOL procCrouchDefenseSlip_init();
    BOOL procCrouchDefenseSlip();
    BOOL procCrouch_init();
    BOOL procCrouch();
    BOOL procWaitTurn_init();
    BOOL procWaitTurn();
    BOOL procMoveTurn_init(int);
    BOOL procMoveTurn();
    BOOL procSlip_init();
    BOOL procSlip();
    BOOL procSlideFront_init(s16);
    BOOL procSlideFront();
    BOOL procSlideBack_init(s16);
    BOOL procSlideBack();
    BOOL procSlideFrontLand_init();
    BOOL procSlideFrontLand();
    BOOL procSlideBackLand_init();
    BOOL procSlideBackLand();
    BOOL procFrontRoll_init(f32);
    BOOL procFrontRoll();
    BOOL procFrontRollCrash_init();
    BOOL procFrontRollCrash();
    BOOL procNockBackEnd_init();
    BOOL procNockBackEnd();
    BOOL procSideRoll_init();
    BOOL procSideRoll();
    BOOL procBackJump_init();
    BOOL procBackJump();
    BOOL procBackJumpLand_init();
    BOOL procBackJumpLand();
    int checkAutoJumpFlying() const;
    BOOL procAutoJump_init();
    BOOL procAutoJump();
    BOOL procLand_init(f32, int);
    BOOL procLand();
    BOOL procLandDamage_init(int);
    BOOL procLandDamage();
    BOOL procFall_init(int, f32);
    BOOL procFall();
    BOOL procSlowFall_init();
    BOOL procSlowFall();
    BOOL procSmallJump_init(int);
    BOOL procSmallJump();
    BOOL procVerticalJump_init();
    BOOL procVerticalJump();
    BOOL procGuardCrash();
    BOOL procDamage_init();
    BOOL procDamage();
    BOOL procPolyDamage_init();
    BOOL procPolyDamage();
    BOOL procLargeDamage_init(int, int, s16, s16);
    BOOL procLargeDamage();
    BOOL procLargeDamageUp_init(int, int, s16, s16);
    BOOL procLargeDamageUp();
    BOOL procLargeDamageWall_init(int, int, s16, s16);
    BOOL procLargeDamageWall();
    BOOL procLavaDamage_init();
    BOOL procLavaDamage();
    BOOL procElecDamage_init(cXyz const*);
    BOOL procElecDamage();
    BOOL procGuardSlip_init();
    BOOL procGuardSlip();
    BOOL procIceSlipFall_init();
    BOOL procIceSlipFall();
    BOOL procIceSlipFallUp_init(int, s16, s16);
    BOOL procIceSlipFallUp();
    BOOL procIceSlipAlmostFall_init();
    BOOL procIceSlipAlmostFall();
    BOOL procBootsEquip_init(u16);
    BOOL procBootsEquip();
    BOOL procNotUse_init(int);
    BOOL procNotUse();
    s16 getGroundAngle(cBgS_PolyInfo*, s16);
    int setLegAngle(f32, int, s16*, s16*);
    void footBgCheck();
    void setWaterY();
    void autoGroundHit();
    BOOL checkAttentionPosAngle(fopAc_ac_c*, cXyz**);
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
    f32 getBlurTopRate();
    void setCollision();
    void setAttentionPos();
    int setRoomInfo();
    void setDemoData();
    void setStickData();
    void setBgCheckParam();
    u32 setParamData(int, int, int, int);
    BOOL checkLavaFace(cXyz*, int);
    void checkFallCode();
    BOOL startRestartRoom(u32, int, f32, int);
    BOOL checkSuccessGuard(int);
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
    int setMoveAnime(f32, f32, f32, daPy_ANM, daPy_ANM, int, f32);
    BOOL setSingleMoveAnime(daPy_ANM, f32, f32, s16, f32);
    BOOL setActAnimeUpper(u16, daPy_UPPER, f32, f32, s16, f32);
    BOOL resetActAnimeUpper(daPy_UPPER, f32);
    void animeUpdate();
    void simpleAnmPlay(J3DAnmBase*);
    void setHandModel(daPy_ANM);
    const daPy_anmIndex_c* getAnmData(daPy_ANM) const;
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
    fopAc_ac_c* getDemoLookActor();
    void setTinkleCeiverModel();
    void setTalismanModel();
    void setLetterModel();
    BOOL checkCaughtShapeHide();
    void setShapeAngleToTalkActor();
    BOOL checkEndMessage(u32);
    int setTalkStartBack();
    BOOL dProcTool_init();
    BOOL dProcTool();
    BOOL dProcTalk_init();
    BOOL dProcTalk();
    BOOL dProcDamage_init();
    BOOL dProcDamage();
    BOOL dProcHoldup_init();
    BOOL dProcHoldup();
    BOOL dProcOpenTreasure_init();
    BOOL dProcOpenTreasure();
    void setGetItemSound(u16, int);
#if VERSION > VERSION_DEMO
    BOOL setGetDemo();
#endif
    BOOL dProcGetItem_init();
    BOOL dProcGetItem();
    BOOL dProcUnequip_init();
    BOOL dProcUnequip();
    void dProcLavaDamage_init_sub();
    BOOL dProcLavaDamage_init();
    BOOL dProcLavaDamage();
    void dProcFreezeDamage_init_sub(int);
    BOOL dProcFreezeDamage_init();
    BOOL dProcFreezeDamage();
    void dProcDead_init_sub();
    void dProcDead_init_sub2();
    BOOL checkGameOverStart();
    BOOL dProcDead_init();
    BOOL dProcDead();
    BOOL dProcLookAround_init();
    BOOL dProcLookAround();
    BOOL dProcSalute_init();
    BOOL dProcSalute();
    BOOL dProcLookAround2_init();
    BOOL dProcLookAround2();
    BOOL dProcTalismanPickup_init();
    BOOL dProcTalismanPickup();
    BOOL dProcTalismanWait_init();
    BOOL dProcTalismanWait();
    BOOL dProcSurprised_init();
    BOOL dProcSurprised();
    BOOL dProcTurnBack_init();
    BOOL dProcTurnBack();
    BOOL dProcLookUp_init();
    BOOL dProcLookUp();
    BOOL dProcQuakeWait_init();
    BOOL dProcQuakeWait();
    BOOL dProcDance_init();
    BOOL dProcDance();
    BOOL dProcCaught_init();
    BOOL dProcCaught();
    BOOL dProcLookWait_init();
    BOOL dProcLookWait();
    BOOL dProcPushPullWait_init();
    BOOL dProcPushPullWait();
    BOOL dProcPushMove_init();
    BOOL dProcPushMove();
    BOOL dProcDoorOpen_init();
    BOOL dProcDoorOpen();
    BOOL dProcNod_init();
    BOOL dProcNod();
    void dProcPresent_init_sub();
    BOOL dProcPresent_init();
    BOOL dProcPresent();
    BOOL dProcWindChange_init();
    BOOL dProcWindChange();
    BOOL dProcStandItemPut_init();
    BOOL dProcStandItemPut();
    BOOL dProcVorcanoFail_init();
    BOOL dProcVorcanoFail();
    BOOL dProcSlightSurprised_init();
    BOOL dProcSlightSurprised();
    BOOL dProcSmile_init();
    BOOL dProcSmile();
    BOOL dProcBossWarp_init();
    BOOL dProcBossWarp();
    BOOL dProcAgbUse_init();
    BOOL dProcAgbUse();
    BOOL dProcLookTurn_init();
    BOOL dProcLookTurn();
    BOOL dProcLetterOpen_init();
    BOOL dProcLetterOpen();
    BOOL dProcLetterRead_init();
    BOOL dProcLetterRead();
    BOOL dProcRedeadStop_init();
    BOOL dProcRedeadStop();
    BOOL dProcRedeadCatch_init();
    BOOL dProcRedeadCatch();
    BOOL dProcGetDance_init();
    BOOL dProcGetDance();
    BOOL dProcBottleOpenFairy_init();
    BOOL dProcBottleOpenFairy();
    BOOL dProcWarpShort_init();
    BOOL dProcWarpShort();
    BOOL dProcOpenSalvageTreasure_init();
    BOOL dProcOpenSalvageTreasure();
    BOOL dProcSurprisedWait_init();
    BOOL dProcSurprisedWait();
    BOOL dProcPowerUpWait_init();
    BOOL dProcPowerUp_init();
    BOOL dProcPowerUp();
    BOOL dProcShipSit_init();
    BOOL dProcShipSit();
    BOOL dProcLastCombo_init();
    BOOL dProcLastCombo();
    BOOL dProcHandUp_init();
    BOOL dProcHandUp();
    BOOL dProcIceSlip_init();
    BOOL dProcIceSlip();
    f32 getLadderMoveAnmSpeed();
    void setLadderFootSe();
    int changeLadderMoveProc(int);
    int setMoveBGLadderCorrect();
    void procLadderUpStart_init_sub();
    BOOL procLadderUpStart_init();
    BOOL procLadderUpStart();
    BOOL procLadderUpEnd_init(int);
    BOOL procLadderUpEnd();
    void procLadderDownStart_init_sub();
    BOOL procLadderDownStart_init();
    BOOL procLadderDownStart();
    BOOL procLadderDownEnd_init(int);
    BOOL procLadderDownEnd();
    BOOL procLadderMove_init(int, int, cXyz*);
    BOOL procLadderMove();
    f32 getHangMoveAnmSpeed();
    int getHangDirectionFromAngle();
    BOOL changeHangMoveProc(int);
    int changeHangEndProc(int);
    void setHangShapeOffset();
    BOOL procHangStart_init();
    BOOL procHangStart();
    BOOL procHangFallStart_init(cM3dGPla*);
    BOOL procHangFallStart();
    BOOL procHangUp_init(int);
    BOOL procHangUp();
    BOOL procHangWait_init();
    BOOL procHangWait();
    BOOL procHangMove_init(int);
    BOOL procHangMove();
    BOOL procHangClimb_init(f32);
    BOOL procHangClimb();
    BOOL procHangWallCatch_init();
    BOOL procHangWallCatch();
    f32 getClimbMoveAnmSpeed();
    void setClimbShapeOffset();
    int getClimbDirectionFromAngle();
    void changeClimbMoveProc(int);
    BOOL setMoveBGCorrectClimb();
    void checkBgCorrectClimbMove(cXyz*, cXyz*);
    void checkBgClimbMove();
    void procClimbUpStart_init_sub();
    BOOL procClimbUpStart_init();
    BOOL procClimbUpStart();
    BOOL procClimbDownStart_init(s16);
    BOOL procClimbDownStart();
    BOOL procClimbMoveUpDown_init(int);
    BOOL procClimbMoveUpDown();
    BOOL procClimbMoveSide_init(int);
    BOOL procClimbMoveSide();
    void setBlendWHideMoveAnime(f32);
    cM3dGPla* getWHideModePolygon(cXyz*, cXyz*, cXyz*, int);
    void getWHideBasePos(cXyz*);
    void getWHideNextPos(cXyz*, cXyz*);
    BOOL checkWHideBackWall(cXyz*);
    BOOL checkWHideFrontFloor(cXyz*);
    int checkWHideModeChange(cXyz*);
    int changeWHideEndProc(cXyz*);
    BOOL procWHideReady_init(cM3dGPla*, cXyz*);
    BOOL procWHideReady();
    BOOL procWHideWait_init();
    BOOL procWHideWait();
    BOOL procWHideMove_init();
    BOOL procWHideMove();
    BOOL procWHidePeep_init();
    BOOL procWHidePeep();
    f32 getCrawlMoveAnmSpeed();
    f32 getCrawlMoveSpeed();
    void setCrawlMoveDirectionArrow();
    BOOL changeCrawlAutoMoveProc(cXyz*);
    int getCrawlMoveVec(cXyz*, cXyz*, cXyz*);
    void crawlBgCheck(cXyz*, cXyz*);
    BOOL checkCrawlSideWall(cXyz*, cXyz*, cXyz*, cXyz*, s16*, s16*);
    void setDoStatusCrawl();
    BOOL procCrawlStart_init();
    BOOL procCrawlStart();
    BOOL checkNotCrawlStand(cXyz*);
    BOOL checkNotCrawlStand(cXyz*, cXyz*);
    BOOL procCrawlMove_init(s16, s16);
    BOOL procCrawlMove();
    BOOL procCrawlAutoMove_init(int, cXyz*);
    BOOL procCrawlAutoMove();
    BOOL procCrawlEnd_init(int, s16, s16);
    BOOL procCrawlEnd();
    BOOL checkGrabSpecialHeavyState();
    void setWeaponBlur();
    BOOL checkGrabBarrelSearch(int);
    void setGrabItemPos();
    void freeGrabItem();
    BOOL checkNextActionGrab();
    void initGrabNextMode();
    BOOL procGrabReady_init();
    BOOL procGrabReady();
    BOOL procGrabUp_init();
    BOOL procGrabUp();
    BOOL procGrabMiss_init();
    BOOL procGrabMiss();
    BOOL procGrabThrow_init(int);
    BOOL procGrabThrow();
    BOOL procGrabPut_init();
    BOOL procGrabPut();
    BOOL procGrabWait_init();
    BOOL procGrabWait();
    BOOL procGrabHeavyWait_init();
    BOOL procGrabHeavyWait();
    BOOL procGrabRebound_init();
    BOOL procGrabRebound();
    void setSpeedAndAngleSwim();
    BOOL checkNextModeSwim();
    BOOL changeSwimProc();
    BOOL changeSwimUpProc();
    void swimOutAfter(BOOL);
    BOOL checkSwimFallCheck();
    BOOL changeSwimOutProc();
    void setSwimMoveAnime(daPy_ANM);
    f32 getSwimTimerRate();
    void setSwimTimerStartStop();
    BOOL procSwimUp_init(BOOL);
    BOOL procSwimUp();
    BOOL procSwimWait_init(BOOL);
    BOOL procSwimWait();
    BOOL procSwimMove_init(BOOL);
    BOOL procSwimMove();
    void setSpecialBattle(BOOL);
    BOOL changeSpecialBattle();
    BOOL procBtJump_init(fopEn_enemy_c*);
    BOOL procBtJump();
    BOOL procBtJumpCut_init(cXyz*);
    BOOL procBtJumpCut();
    BOOL procBtSlide();
    BOOL procBtRoll_init(fopEn_enemy_c*);
    BOOL procBtRoll();
    BOOL procBtRollCut_init(cXyz*);
    BOOL procBtRollCut();
    BOOL procBtVerticalJump_init(fopEn_enemy_c*);
    BOOL procBtVerticalJump();
    BOOL procBtVerticalJumpCut_init();
    BOOL procBtVerticalJumpCut();
    BOOL procBtVerticalJumpLand_init();
    BOOL procBtVerticalJumpLand();
    BOOL shipSpecialDemoStart();
    BOOL checkJumpRideShip();
    BOOL checkShipNotNormalMode();
    void setShipRideArmAngle(int, J3DTransformInfo*);
    int checkShipRideUseItem(int);
    void initShipRideUseItem(int, int);
    void setShipRidePosUseItem();
    void setShipRidePos(int);
    void setShipAttentionAnmSpeed(f32);
    void setShipAttnetionBodyAngle();
    BOOL changeShipEndProc();
    void initShipBaseAnime();
    void initShipCraneAnime();
    BOOL procShipReady_init();
    BOOL procShipReady();
    BOOL procShipJumpRide_init();
    BOOL procShipJumpRide();
    BOOL procShipSteer_init();
    BOOL procShipSteer();
    BOOL procShipPaddle_init();
    BOOL procShipPaddle();
    BOOL procShipScope_init(int);
    BOOL procShipScope();
    BOOL procShipBoomerang_init();
    BOOL procShipBoomerang();
    BOOL procShipHookshot_init();
    BOOL procShipHookshot();
    BOOL procShipBow_init();
    BOOL procShipBow();
    BOOL procShipCannon_init();
    BOOL procShipCannon();
    BOOL procShipCrane_init();
    BOOL procShipCrane();
    BOOL procShipGetOff_init();
    BOOL procShipGetOff();
    BOOL procShipRestart_init();
    BOOL procShipRestart();
    BOOL checkRopeAnime() const;
    void freeRopeItem();
    f32 checkRopeRoofHit(s16);
    int changeRopeSwingProc();
    int changeRopeEndProc(int);
    BOOL checkSpecialRope();
    int changeRopeToHangProc();
    BOOL checkRopeSwingWall(cXyz*, cXyz*, s16*, f32*);
    void setBlendRopeMoveAnime(int);
    int throwRope();
    BOOL checkNextActionRopeReady();
    BOOL checkNextRopeMode();
    BOOL checkHangRopeActorNull();
    BOOL procRopeSubject_init();
    BOOL procRopeSubject();
    BOOL procRopeReady_init();
    BOOL procRopeReady();
    BOOL procRopeSwing_init(fopAc_ac_c*, s16);
    BOOL procRopeSwing();
    BOOL procRopeHangWait_init(int);
    BOOL procRopeHangWait();
    int specialRopeHangUp();
    BOOL procRopeUp_init();
    BOOL procRopeUp();
    BOOL procRopeDown_init();
    BOOL procRopeDown();
    BOOL procRopeSwingStart_init();
    BOOL procRopeSwingStart();
    BOOL procRopeMove_init();
    BOOL procRopeMove();
    BOOL procRopeThrowCatch_init();
    BOOL procRopeThrowCatch();
    BOOL procRopeUpHang_init();
    BOOL procRopeUpHang();
    BOOL checkBoomerangAnime() const;
    void throwBoomerang();
    int returnBoomerang();
    BOOL checkNextActionBoomerangReady();
    void checkNextActionBoomerangFly();
    BOOL checkNextBoomerangMode();
    BOOL changeBoomerangCatchProc();
    BOOL procBoomerangSubject_init();
    BOOL procBoomerangSubject();
    BOOL procBoomerangMove_init();
    BOOL procBoomerangMove();
    BOOL procBoomerangCatch_init();
    BOOL procBoomerangCatch();
    BOOL bowJointCB(int);
    BOOL bowButton() const;
    BOOL checkBowReadyAnime() const;
    BOOL checkBowAnime() const;
    void makeArrow();
    void deleteArrow();
    void setBowReadyAnime();
    void setBowReloadAnime();
    BOOL checkNextActionBowReady();
    void checkNextActionBowFly();
    BOOL checkNextBowMode();
    void setBowModel();
    BOOL procBowSubject_init();
    BOOL procBowSubject();
    BOOL procBowMove_init();
    BOOL procBowMove();
    BOOL checkHookshotReturn();
    void setHookshotModel();
    void setHookshotSight();
    void freeHookshotItem();
    BOOL checkNextActionHookshotReady();
    BOOL checkNextHookshotMode();
    BOOL procHookshotSubject_init();
    BOOL procHookshotSubject();
    BOOL procHookshotMove_init();
    BOOL procHookshotMove();
    BOOL procHookshotFly_init();
    BOOL procHookshotFly();
    BOOL fanWindEffectDraw();
    BOOL fanWindCrashEffectDraw();
    BOOL fanJointCB(int);
    BOOL parachuteJointCB(int);
    int setShapeFanLeaf();
    BOOL checkFanGlideProc(int);
    void setFanModel();
    void setSmallFanModel();
    void setParachuteFanModel(f32);
    BOOL procFanSwing_init();
    BOOL procFanSwing();
    BOOL procFanGlide_init(int);
    BOOL procFanGlide();
    u32 getDayNightParamData();
    void setTactModel();
    BOOL checkNpcStatus();
    u16 getTactPlayRightArmAnm(s32);
    u16 getTactPlayLeftArmAnm(s32);
    BOOL checkEndTactMusic() const;
    f32 getTactMetronomeRate();
    BOOL checkTactLastInput();
    BOOL getTactTopPos(cXyz*);
    BOOL getTactNormalWait() const;
    BOOL checkTactPlayMelody();
    void resetTactCount();
    BOOL procTactWait_init(int);
    BOOL procTactWait();
    BOOL procTactPlay_init(s32, int, int);
    BOOL procTactPlay();
    BOOL procTactPlayEnd_init(int);
    BOOL procTactPlayEnd();
    BOOL procTactPlayOriginal_init();
    BOOL procTactPlayOriginal();
    BOOL checkJumpFlower();
    BOOL procVomitReady_init(s16, f32);
    BOOL procVomitReady();
    BOOL procVomitWait_init();
    BOOL procVomitWait();
    BOOL procVomitJump_init(int);
    BOOL procVomitJump();
    BOOL procVomitLand_init();
    BOOL procVomitLand();
    void setHammerModel();
    void setHammerQuake(cBgS_PolyInfo*, cXyz const*, int);
    void setHammerWaterSplash();
    BOOL procHammerSideSwing_init();
    BOOL procHammerSideSwing();
    BOOL procHammerFrontSwingReady_init();
    BOOL procHammerFrontSwingReady();
    BOOL procHammerFrontSwing_init();
    BOOL procHammerFrontSwing();
    BOOL procHammerFrontSwingEnd_init();
    BOOL procHammerFrontSwingEnd();
    BOOL setPushPullKeepData(dBgW::PushPullLabel);
    BOOL procPushPullWait_init(int);
    BOOL procPushPullWait();
    BOOL procPushMove_init();
    BOOL procPushMove();
    BOOL procPullMove_init();
    BOOL procPullMove();
    int changeBottleDrinkFace(int);
    void setBottleModel(u16);
    fopAc_ac_c* makeFairy(cXyz*, u32);
    BOOL procBottleDrink_init(u16);
    BOOL procBottleDrink();
    BOOL procBottleOpen_init(u16);
    BOOL procBottleOpen();
    BOOL procBottleSwing_init(int);
    BOOL procBottleSwing();
    BOOL procBottleGet_init();
    BOOL procBottleGet();
    void setEnemyWeaponAtParam(BOOL);
    BOOL procWeaponNormalSwing_init();
    BOOL procWeaponNormalSwing();
    BOOL procWeaponSideSwing_init();
    BOOL procWeaponSideSwing();
    BOOL procWeaponFrontSwingReady_init();
    BOOL procWeaponFrontSwingReady();
    BOOL procWeaponFrontSwing_init();
    BOOL procWeaponFrontSwing();
    BOOL procWeaponFrontSwingEnd_init();
    BOOL procWeaponFrontSwingEnd();
    BOOL procWeaponThrow_init();
    BOOL procWeaponThrow();
    void setHyoiModel();
    BOOL procFoodThrow_init();
    BOOL procFoodThrow();
    BOOL procFoodSet_init();
    BOOL procFoodSet();
#if VERSION == VERSION_DEMO
    void setSwordModel();
#else
    void setSwordModel(BOOL);
#endif
    void setLightSaver();
#if VERSION == VERSION_DEMO
    BOOL checkLastDemoSwordNoDraw(int);
#else
    BOOL checkDemoShieldNoDraw();
    BOOL checkDemoSwordNoDraw(BOOL);
#endif
    BOOL checkChanceMode();
    BOOL checkCutRollChange() const;
    int getSwordBlurColor();
    void setNormalCutAtParam(u8);
    void setFinishCutAtParam(u8);
    void setExtraCutAtParam(u8);
    void setExtraFinishCutAtParam(u8);
    void setJumpCutAtParam();
    int getCutDirection();
    int changeCutProc();
    int changeCutReverseProc(daPy_ANM);
    BOOL procCutA_init(s16);
    BOOL procCutA();
    BOOL procCutF_init(s16);
    BOOL procCutF();
    BOOL procCutR_init(s16);
    BOOL procCutR();
    BOOL procCutL_init(s16);
    BOOL procCutL();
    BOOL procCutEA_init();
    BOOL procCutEA();
    BOOL procCutEB_init();
    BOOL procCutEB();
    BOOL procCutExA_init();
    BOOL procCutExA();
    BOOL procCutExB_init();
    BOOL procCutExB();
    BOOL procCutTurn_init(int);
    BOOL procCutTurn();
    BOOL procCutRoll_init();
    BOOL procCutRoll();
    BOOL procCutRollEnd_init();
    BOOL procCutRollEnd();
    BOOL procCutTurnCharge_init();
    BOOL procCutTurnCharge();
    BOOL procCutTurnMove_init();
    BOOL procCutTurnMove();
    BOOL procCutReverse_init(daPy_ANM);
    BOOL procCutReverse();
    BOOL procJumpCut_init(int);
    BOOL procJumpCut();
    BOOL procJumpCutLand_init();
    BOOL procJumpCutLand();
    BOOL procCutExMJ_init(int);
    BOOL procCutExMJ();
    BOOL procCutKesa_init();
    BOOL procCutKesa();
    
    J3DAnmTevRegKey* getBombBrk() { return mpBombBrk; }
    J3DAnmTextureSRTKey* getIceArrowBtk() { return mpIceArrowBtk; }
    J3DAnmTextureSRTKey* getLightArrowBtk() { return mpLightArrowBtk; }
    
    BOOL checkUpperAnime(u16 i_idx) const { return m_anm_heap_upper[UPPER_MOVE2_e].mIdx == i_idx; }
    BOOL checkNoUpperAnime() const { return m_anm_heap_upper[UPPER_MOVE2_e].mIdx == 0xFFFF; }
    
    BOOL checkGrabAnime() const { return checkGrabAnimeLight() || checkGrabAnimeHeavy(); };
    BOOL checkGrabAnimeLight() const { return checkUpperAnime(LKANM_BCK_GRABWAIT); };
    BOOL checkGrabAnimeHeavy() const { return checkUpperAnime(LKANM_BCK_GRABWAITB); };
    BOOL checkBoomerangCatchAnime() const { return checkUpperAnime(LKANM_BCK_BOOMCATCH); };
    BOOL checkBoomerangThrowAnime() const { return checkUpperAnime(LKANM_BCK_BOOMTHROW); };
    BOOL checkBoomerangReadyAnime() const { return checkUpperAnime(LKANM_BCK_BOOMWAIT); };
    BOOL checkHookshotReadyAnime() const { return checkUpperAnime(LKANM_BCK_HOOKSHOTWAIT); }
    BOOL checkDashDamageAnime() const { return checkUpperAnime(LKANM_BCK_DAMDASH); }
    BOOL checkBowReloadAnime() const { return checkUpperAnime(LKANM_BCK_ARROWRELORD); }
    BOOL checkBowShootAnime() const { return checkUpperAnime(LKANM_BCK_ARROWSHOOT); }
    BOOL checkBowWaitAnime() const { return checkUpperAnime(LKANM_BCK_BOWWAIT); }
    BOOL checkGuardSlip() const {
        return mCurProc == daPyProc_GUARD_SLIP_e ||
            mCurProc == daPyProc_CROUCH_DEFENSE_SLIP_e;
    }
    BOOL checkUpperGuardAnime() const {
        return checkUpperAnime(LKANM_BCK_ATNG) ||
            checkUpperAnime(LKANM_BCK_ATNGHAM);
    }
    
    s16 checkTinkleShield() const { return mTinkleShieldTimer; }
    void setTinkleShield(s16 time) { mTinkleShieldTimer = time; }
    BOOL checkNoDamageMode() const { return checkEquipDragonShield() || checkTinkleShield() != 0; }
    s16 checkTinkleHover() const { return mTinkleHoverTimer; }
    void setHoverBoots(s16 time) {
        onNoResetFlg0(daPyFlg0_HOVER_BOOTS);
        mTinkleHoverTimer = time;
    }
    void onShipTact() { onNoResetFlg1(daPyFlg1_SHIP_TACT); }
    void offShipTact() { offNoResetFlg1(daPyFlg1_SHIP_TACT); }
    BOOL checkShipGetOff() { return mCurProc == daPyProc_SHIP_GET_OFF_e; }
    void onShipDrop(s16 param_1) {
        onNoResetFlg0(daPyFlg0_SHIP_DROP);
        m3550 = param_1;
    }
    BOOL checkCarryActionNow() const {
        return mCurProc == daPyProc_GRAB_PUT_e ||
            mCurProc == daPyProc_GRAB_UP_e ||
            mCurProc == daPyProc_GRAB_THROW_e;
    }
    BOOL checkNoControll() const { return dComIfGp_getPlayer(0) != this; }
    void exchangeGrabActor(fopAc_ac_c* actor) { mActorKeepGrab.setData(actor); }
    void getDekuLeafWindPos() const {}
    void getBoomerangCatchPos() const {}
    void getLineTopPos() {}
    cXyz getHookshotRootPos() const { return mHookshotRootPos; }
    void getIceParticleBtk() {}
    void getIceWaterParticleBtk() {}
    void getShadowID() const {}
    void npcStartRestartRoom() { startRestartRoom(5, 0xC9, -1.0f, 0); }
    void setDaiokutaEnd() {}
    void setWhirlId(fpc_ProcID id) { mWhirlId = id; }
    void decrementBombCnt() {
        if (mActivePlayerBombs != 0) {
            mActivePlayerBombs--;
        }
    }
    BOOL checkSwordEquip() const {
        return dComIfGs_getSelectEquip(0) != dItem_NONE_e || checkSwordMiniGame();
    }
    
    int getStartRoomNo() { return fopAcM_GetParam(this) & 0x3F; }
    int getStartMode() { return (fopAcM_GetParam(this) >> 0x0C) & 0xF; }
    static int getStartModeFromParam(u32 param) { return (param >> 0x0C) & 0xF; }
    int getStartEvent() { return (fopAcM_GetParam(this) >> 0x18) & 0xFF; }
    
    void onModeFlg(u32 flag) { mModeFlg |= flag; }
    void offModeFlg(u32 flag) { mModeFlg &= ~flag; }
    u32 checkModeFlg(u32 flag) const { return mModeFlg & flag; }
    void clearDamageWait() { offModeFlg(ModeFlg_DAMAGE); }
    
    request_of_phase_process_class* getPhase() { return &mPhase; }
    
    J3DAnmTransform* getNowAnmPackUnder(daPy_UNDER idx) { return mAnmRatioUnder[idx].getAnmTransform(); }
    J3DAnmTransform* getNowAnmPackUpper(daPy_UPPER idx) { return mAnmRatioUpper[idx].getAnmTransform(); }
    
    BOOL doButton() const { return mItemButton & BTN_A; }
    BOOL swordButton() const { return mItemButton & BTN_B; }
    BOOL itemButtonX() const { return mItemButton & BTN_X; }
    BOOL itemButtonY() const { return mItemButton & BTN_Y; }
    BOOL itemButtonZ() const { return mItemButton & BTN_Z; }
    BOOL spActionButton() const { return mItemButton & BTN_R; }
    
    BOOL doTrigger() const { return mItemTrigger & BTN_A; }
    BOOL talkTrigger() const { return mItemTrigger & BTN_A; }
    BOOL spBattleTrigger() const {return mItemTrigger & BTN_A; }
    BOOL swordTrigger() const { return mItemTrigger & BTN_B; }
    BOOL cancelTrigger() const { return mItemTrigger & BTN_B; }
    BOOL itemTriggerX() const { return mItemTrigger & BTN_X; }
    BOOL itemTriggerY() const { return mItemTrigger & BTN_Y; }
    BOOL itemTriggerZ() const { return mItemTrigger & BTN_Z; }
    BOOL spLTrigger() const { return mItemTrigger & BTN_L; }
    BOOL spActionTrigger() const { return mItemTrigger & BTN_R; }
    BOOL allTrigger() const { return mItemTrigger & (BTN_A | BTN_B | BTN_X | BTN_Y | BTN_Z); }
    void otherWeaponTrigger() const {}
    
    BOOL checkPlayerDemoMode() const { return mDemo.getDemoType() != 0; }
    void checkSpecialDemoMode() const {}
    
    f32 getAnmSpeedStickRate(f32 param_0, f32 param_1) {
        return param_0 + (mStickDistance * (param_1 - param_0));
    }
    void seStartSystem(u32 i_seNum) { mDoAud_seStart(i_seNum); }
    BOOL checkAttentionLock() { return mpAttention->Lockon(); }
    void checkBoomerangRock() {}
    
    void checkBothItemEquipAnime() const {}
    void checkCrawlWaterIn() {}
    void checkDoubleItemEquipAnime() const {}
    void checkFaceTypeNot() const {}
    void checkIsland() const {}
    void checkMirrorShieldEquip() const {}
    void checkPowerGloveEquip() const {}
    void checkRopeThrowAnime() const {}
    void checkShieldEquip() const {}
    void checkSwordEquipAnime() const {}
    void getBombWaterPillarBrk() {} // mpGwp00BrkData?
    void getBombWaterPillarBtk() {} // mpGwp00BtkData?
    void getTactLeftHandPos() const {}
    void setFootEffectPosType(u8) {}
    void setSpeedAndAngleBoomerang() {}
    void setSpeedAndAngleBow() {}
    void setSpeedAndAngleHookshot() {}
    void setSpeedAndAngleRope() {}
    
    virtual void setPlayerPosAndAngle(cXyz*, s16);
    virtual void setPlayerPosAndAngle(cXyz*, csXyz*);
    virtual void setPlayerPosAndAngle(MtxP);
    virtual BOOL setThrowDamage(cXyz*, s16, f32, f32, int);
    virtual void changeTextureAnime(u16, u16, int);
    
    virtual f32 getGroundY() { return mAcch.GetGroundH(); }
    virtual MtxP getLeftHandMatrix() { return mpCLModel->getAnmMtx(0x08); } // cl_LhandA joint
    virtual MtxP getRightHandMatrix() { return mpCLModel->getAnmMtx(0x0C); } // cl_RhandA joint
    virtual s32 getTactMusic() const;
    virtual int getTactTimerCancel() const;
    virtual BOOL checkPlayerGuard() const;
    virtual fopAc_ac_c* getGrabMissActor();
    virtual u32 checkPlayerFly() const {
        // Note: These flags combine into 0x10452822.
        return checkModeFlg(
            ModeFlg_MIDAIR |
            ModeFlg_HANG |
            ModeFlg_ROPE |
            ModeFlg_IN_SHIP |
            ModeFlg_CLIMB |
            ModeFlg_SWIM |
            ModeFlg_LADDER |
            ModeFlg_CAUGHT
        );
    }
    virtual BOOL checkFrontRoll() const { return mCurProc == daPyProc_FRONT_ROLL_e; }
    virtual BOOL checkBottleSwing() const { return mCurProc == daPyProc_BOTTLE_SWING_e; }
    virtual BOOL checkCutCharge() const { return mCurProc == daPyProc_CUT_TURN_MOVE_e; }
    virtual BOOL getBokoFlamePos(cXyz*);
    virtual BOOL checkTactWait() const { return mCurProc == daPyProc_TACT_WAIT_e; }
    virtual void setTactZev(fpc_ProcID, int, char*);
    virtual void onDekuSpReturnFlg(u8 i_point);
    virtual f32 getBaseAnimeFrameRate() { return mFrameCtrlUnder[UNDER_MOVE0_e].getRate(); }
    virtual f32 getBaseAnimeFrame() { return mFrameCtrlUnder[UNDER_MOVE0_e].getFrame(); }
    virtual fpc_ProcID getItemID() const { return mActorKeepEquip.getID(); }
    virtual fpc_ProcID getThrowBoomerangID() const { return mActorKeepThrow.getID(); }
    virtual fpc_ProcID getGrabActorID() const { return mActorKeepGrab.getID(); }
    virtual BOOL checkGrabBarrel() { return checkGrabBarrelSearch(1); }
    virtual u32 checkPlayerNoDraw() { return dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 2) || checkNoResetFlg0(daPyFlg0_NO_DRAW); }
    virtual BOOL checkRopeTag() { return mActorKeepEquip.getActor() == NULL; }
    virtual BOOL checkRopeReadyAnime() const { return checkUpperAnime(LKANM_BCK_ROPETHROWWAIT); }
    virtual void voiceStart(u32);
    virtual void setOutPower(f32, s16, int);
    virtual void onFrollCrashFlg(u32 param_1) { m3620 = param_1; onNoResetFlg0(daPyFlg0_UNK8); }
    virtual MtxP getModelJointMtx(u16 idx) { return mpCLModel->getAnmMtx(idx); }
    virtual f32 getOldSpeedY() { return mOldSpeed.y; }
    virtual BOOL setHookshotCarryOffset(fpc_ProcID, const cXyz*);
    virtual BOOL checkComboCutTurn() const { return mCurProc == daPyProc_CUT_TURN_e && mProcVar0.m3570 != 0; }
    virtual void cancelChangeTextureAnime() { resetDemoTextureAnime(); }

public:
    /* 0x0320 */ request_of_phase_process_class mPhase;
    /* 0x0328 */ J3DModelData* mpCLModelData;
    /* 0x032C */ J3DModel* mpCLModel;
    /* 0x0330 */ J3DModel* mpKatsuraModel;
    /* 0x0334 */ J3DModel* mpYamuModel;
    /* 0x0338 */ ResTIMG* mpCurrLinktex;
    /* 0x033C */ ResTIMG mOtherLinktex;
    /* 0x035C */ J3DAnmTexPattern* mpAnmTexPatternData;
    /* 0x0360 */ J3DTexNoAnm* m_texNoAnms;
    /* 0x0364 */ J3DAnmTextureSRTKey* mpTexScrollResData;
    /* 0x0368 */ J3DTexMtxAnm* m_texMtxAnm;
    /* 0x036C */ daPy_matAnm_c* m_tex_eye_scroll[2];
    /* 0x0374 */ J3DShape* mpZOffBlendShape[4];
    /* 0x0384 */ J3DShape* mpZOffNoneShape[4];
    /* 0x0394 */ J3DShape* mpZOnShape[4];
    /* 0x03A4 */ J3DShape* mpLhandShape;
    /* 0x03A8 */ J3DShape* mpRhandShape;
    /* 0x03AC */ dBgS_AcchCir mAcchCir[3];
    /* 0x046C */ dBgS_LinkAcch mAcch;
    /* 0x0630 */ dBgS_LinkLinChk mLinkLinChk;
    /* 0x069C */ dBgS_RopeLinChk mRopeLinChk;
    /* 0x0708 */ dBgS_BoomerangLinChk mBoomerangLinChk;
    /* 0x0774 */ dBgS_LinkGndChk mGndChk;
    /* 0x07C8 */ dBgS_LinkRoofChk mRoofChk;
    /* 0x0814 */ dBgS_ArrowLinChk mArrowLinChk;
    /* 0x0880 */ dBgS_MirLightLinChk mMirLightLinChk;
    /* 0x08EC */ dBgS_ObjGndChk_Spl mLavaGndChk;
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
    /* 0x2E84 */ J3DModel* mpHbootsModels[2];
    /* 0x2E8C */ J3DModel* mpPringModel;
    /* 0x2E90 */ JKRSolidHeap* mpItemHeaps[2];
    /* 0x2E98 */ J3DModel* mpEquipItemModel;
    /* 0x2E9C */ mDoExt_bckAnm mSwordAnim;
    /* 0x2EAC */ mDoExt_McaMorf* mpParachuteFanMorf;
    /* 0x2EB0 */ J3DAnmTevRegKey* mpBombBrk;
    /* 0x2EB4 */ J3DAnmTevRegKey* mpGwp00BrkData;
    /* 0x2EB8 */ J3DAnmTextureSRTKey* mpGwp00BtkData;
    /* 0x2EBC */ J3DAnmTextureSRTKey* mpGicer00Btk;
    /* 0x2EC0 */ J3DAnmTextureSRTKey* mpIceArrowBtk;
    /* 0x2EC4 */ J3DAnmTextureSRTKey* mpLightArrowBtk;
    /* 0x2EC8 */ J3DAnmTextureSRTKey* mpGicer01Btk;
    /* 0x2ECC */ JKRSolidHeap* mpItemAnimeHeap;
    /* 0x2ED0 */ void* m_item_bck_buffer;
    /* 0x2ED4 */ J3DAnmTextureSRTKey* mpEquipItemBtk;
    /* 0x2ED8 */ J3DAnmTextureSRTKey* mpSwordBtk;
    /* 0x2EDC */ J3DAnmTevRegKey* mpEquipItemBrk;
    /* 0x2EE0 */ J3DModel* mpBottleContentsModel;
    /* 0x2EE4 */ J3DModel* mpBottleCapModel;
    /* 0x2EE8 */ J3DModel* mpSwordModel1;
    /* 0x2EEC */ J3DModel* mpSwordTipStabModel;
    /* 0x2EF0 */ J3DAnmColor* mpCutfBpk;
    /* 0x2EF4 */ J3DAnmTextureSRTKey* mpCutfBtk;
    /* 0x2EF8 */ J3DAnmTevRegKey* mpCutfBrk;
    /* 0x2EFC */ mDoExt_brkAnm m2EFC;
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
    /* 0x31B8 */ daPy_anmHeap_c m_tex_anm_heap;
    /* 0x31C8 */ daPy_anmHeap_c m_tex_scroll_heap;
    /* 0x31D8 */ int mCurProc;
    /* 0x31DC */ ProcFunc mCurProcFunc;
    /* 0x31E8 */ daPy_footEffect_c mFootEffect[2];
    /* 0x3280 */ dPa_rippleEcallBack m3280;
    /* 0x3294 */ daPy_swimTailEcallBack_c mSwimTailEcallBack[2];
    /* 0x32E4 */ daPy_mtxFollowEcallBack_c m32E4;
    /* 0x32F0 */ daPy_mtxFollowEcallBack_c m32F0;
    /* 0x32FC */ dPa_smokeEcallBack mSmokeEcallBack;
    /* 0x331C */ dPa_cutTurnEcallBack_c m331C;
    /* 0x332C */ dPa_cutTurnEcallBack_c m332C;
    /* 0x333C */ dPa_cutTurnEcallBack_c m333C;
    /* 0x334C */ daPy_waterDropEcallBack_c m334C;
    /* 0x336C */ daPy_waterDropEcallBack_c m336C;
    /* 0x338C */ daPy_followEcallBack_c m338C;
    /* 0x33A8 */ daPy_mtxPosFollowEcallBack_c m33A8;
    /* 0x33B8 */ daPy_dmEcallBack_c mDmEcallBack[4];
    /* 0x33E8 */ daPy_mtxFollowEcallBack_c m33E8;
    /* 0x33F4 */ daPy_fanSwingEcallBack_c mFanSwingCb;
    /* 0x3400 */ daPy_mtxPosFollowEcallBack_c m3400;
    /* 0x3410 */ daPy_followEcallBack_c m3410;
    /* 0x342C */ daPy_mtxFollowEcallBack_c m342C;
    /* 0x3438 */ daPy_followEcallBack_c m3438;
    /* 0x3454 */ daPy_mtxFollowEcallBack_c m3454;
    /* 0x3460 */ daPy_mtxPosFollowEcallBack_c m3460[2];
    /* 0x3480 */ dAttention_c* mpAttention;
    /* 0x3484 */ dAttList_c* mpAttnEntryA;
    /* 0x3488 */ dAttList_c* mpAttnEntryX;
    /* 0x348C */ dAttList_c* mpAttnEntryY;
    /* 0x3490 */ dAttList_c* mpAttnEntryZ;
    /* 0x3494 */ char* m3494;
    /* 0x3498 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x34B8 */ u8 mDirection;
    /* 0x34B9 */ u8 mFrontWallType;
    /* 0x34BA */ u8 m34BA;
    /* 0x34BB */ u8 mCurrItemHeapIdx;
    /* 0x34BC */ u8 m34BC;
    /* 0x34BD */ u8 mReadyItemBtn; // Which of the three item buttons the player last used.
    /* 0x34BE */ u8 m34BE;
    /* 0x34BF */ s8 mReverb;
    /* 0x34C0 */ u8 mLeftHandIdx;
    /* 0x34C1 */ u8 mRightHandIdx;
    /* 0x34C2 */ u8 m34C2;
    /* 0x34C3 */ u8 m34C3;
    /* 0x34C4 */ u8 m34C4;
    /* 0x34C5 */ u8 m34C5;
    /* 0x34C6 */ u8 m34C6;
    /* 0x34C7 */ u8 mActivePlayerBombs;
    /* 0x34C8 */ u8 mItemTrigger;
    /* 0x34C9 */ u8 mItemButton;
    /* 0x34CA */ u8 m34CA;
    /* 0x34CB */ u8 mDekuSpRestartPoint;
    /* 0x34CC */ u8 m34CC;
    /* 0x34CD */ u8 m34CD;
    /* 0x34CE */ u8 m34CE;
    /* 0x34D0 */ s16 m34D0;
    /* 0x34D2 */ s16 m34D2;
    /* 0x34D4 */ s16 m34D4;
    /* 0x34D6 */ s16 m34D6;
    /* 0x34D8 */ s16 m34D8;
    /* 0x34DA */ s16 m34DA;
    /* 0x34DC */ s16 m34DC;
    /* 0x34DE */ s16 m34DE;
    /* 0x34E0 */ s16 m34E0;
    /* 0x34E2 */ s16 m34E2;
    /* 0x34E4 */ s16 m34E4;
    /* 0x34E6 */ s16 m34E6;
    /* 0x34E8 */ s16 m34E8;
    /* 0x34EA */ s16 m34EA;
    /* 0x34EC */ s16 m34EC;
    /* 0x34EE */ u16 mSeAnmIdx;
    /* 0x34F0 */ u16 m34F0;
    /* 0x34F2 */ s16 m34F2;
    /* 0x34F4 */ s16 m34F4;
    /* 0x34F6 */ s16 m34F6;
    /* 0x34F8 */ s16 m34F8;
    /* 0x34FA */ s16 m34FA;
    /* 0x34FC */ s16 m34FC;
    /* 0x34FE */ s16 m34FE;
    /* 0x3500 */ s16 m3500;
    /* 0x3502 */ s16 m3502;
    /* 0x3504 */ s16 m3504;
    /* 0x3506 */ s16 m3506;
    /* 0x3508 */ s16 m3508;
    /* 0x350A */ s16 m350A;
    /* 0x350C */ s16 m350C;
    /* 0x350E */ s16 m350E;
    /* 0x3510 */ s16 m3510;
    /* 0x3512 */ s16 m3512;
    /* 0x3514 */ s16 m3514;
    /* 0x3516 */ s16 m3516;
    /* 0x3518 */ s16 m3518;
    /* 0x351A */ s16 m351A;
    /* 0x351C */ s16 m351C;
    /* 0x351E */ s16 m351E;
    /* 0x3520 */ u8 m3520[0x3522 - 0x3520];
    /* 0x3522 */ s16 m3522;
    /* 0x3524 */ s16 m3524;
    /* 0x3526 */ s16 m3526;
    /* 0x3528 */ s16 m3528;
    /* 0x352A */ s16 m352A;
    /* 0x352C */ s16 m352C;
    /* 0x352E */ s16 m352E;
    /* 0x3530 */ u16 m3530;
    /* 0x3532 */ u16 m3532;
    /* 0x3534 */ s16 m3534;
    /* 0x3536 */ s16 m3536;
    /* 0x3538 */ s16 m3538;
    /* 0x353A */ s16 m353A;
    /* 0x353C */ s16 m353C;
    /* 0x353E */ s16 m353E;
    /* 0x3540 */ s16 m3540;
    /* 0x3542 */ s16 m3542;
    /* 0x3544 */ s16 m3544;
    /* 0x3546 */ s16 mShieldFrontRangeYAngle;
    /* 0x3548 */ s16 m3548;
    /* 0x354A */ u8 m354A[0x354C - 0x354A];
    /* 0x354C */ s16 mTinkleHoverTimer;
    /* 0x354E */ s16 mTinkleShieldTimer;
    /* 0x3550 */ s16 m3550;
    /* 0x3552 */ u16 mKeepItem; // The item Link was previously holding in his hand, and is now temporarily put away.
    /* 0x3554 */ s16 m3554;
    /* 0x3556 */ u8 m3556[0x3558 - 0x3556];
    /* 0x3558 */ s16 m3558;
    /* 0x355A */ s16 m355A;
    /* 0x355C */ s16 m355C;
    /* 0x355E */ s16 m355E;
    /* 0x3560 */ u16 mEquipItem; // The item Link is currently holding in his hand.
    /* 0x3562 */ u16 m3562;
    /* 0x3564 */ s16 m3564;
    /* 0x3566 */ s16 m3566;
    /* 0x3568 */ s16 m3568;
    /* 0x356C */ int mCameraInfoIdx;
    // `mProcVar`'s are variables that are context dependent for each `PROC` action.
    // (The exact setup may need to be simplified later)
    union {
        s32 m3570;
        daPy_ANM mDamageAnm;
        int mBottleItem;
    } /* 0x3570  */ mProcVar0;
    /* 0x3574 */ s32 m3574;
    /* 0x3578 */ int m3578;
    /* 0x357C */ int m357C;
    /* 0x3580 */ int m3580;
    /* 0x3584 */ int mCurrAttributeCode;
    /* 0x3588 */ int m3588;
    /* 0x358C */ int mStaffIdx;
    /* 0x3590 */ int mEventIdx;
    /* 0x3594 */ int mRestartPoint;
    /* 0x3598 */ f32 m3598;
    /* 0x359C */ f32 m359C;
    /* 0x35A0 */ f32 m35A0;
    /* 0x35A4 */ f32 m35A4;
    /* 0x35A8 */ f32 m35A8;
    /* 0x35AC */ f32 m35AC;
    /* 0x35B0 */ f32 mStickDistance;
    /* 0x35B4 */ f32 m35B4;
    /* 0x35B8 */ f32 m35B8;
    /* 0x35BC */ f32 mVelocity;
    /* 0x35C0 */ u8 m35C0[0x35C4 - 0x35C0];
    /* 0x35C4 */ f32 m35C4;
    /* 0x35C8 */ f32 m35C8;
    /* 0x35CC */ f32 m35CC;
    /* 0x35D0 */ f32 m35D0;
    /* 0x35D4 */ f32 m35D4;
    /* 0x35D8 */ f32 m35D8;
    /* 0x35DC */ f32 mHangGroundH;
    /* 0x35E0 */ f32 m35E0;
    /* 0x35E4 */ f32 m35E4;
    /* 0x35E8 */ f32 m35E8;
    /* 0x35EC */ f32 m35EC;
    /* 0x35F0 */ f32 m35F0;
    /* 0x35F4 */ f32 m35F4;
    /* 0x35F8 */ f32 m35F8;
    /* 0x35FC */ f32 m35FC;
    /* 0x3600 */ f32 m3600;
    /* 0x3604 */ f32 m3604;
    /* 0x3608 */ f32 m3608;
    /* 0x360C */ f32 mSeAnmRate;
    /* 0x3610 */ f32 m3610;
    /* 0x3614 */ int mShadowId;
    /* 0x3618 */ u32 mModeFlg;
    /* 0x361C */ u32 mMtrlSndId;
    /* 0x3620 */ u32 m3620;
    /* 0x3624 */ u32 m3624;
    /* 0x3628 */ fpc_ProcID m3628;
    /* 0x362C */ fpc_ProcID mTactZevPartnerId;
    /* 0x3630 */ fpc_ProcID m3630;
    /* 0x3634 */ fpc_ProcID mWhirlId;
#if VERSION > VERSION_DEMO
    /* 0x3638 */ fpc_ProcID mMsgId;
#endif
    /* 0x363C */ J3DFrameCtrl* mpSeAnmFrameCtrl;
    /* 0x3640 */ s16 m3640;
    /* 0x3644 */ f32 m3644;
    /* 0x3648 */ Quaternion m3648;
    /* 0x3658 */ Quaternion m3658;
    /* 0x3668 */ J3DTransformInfo m3668;
    /* 0x3688 */ cXyz m3688;
    /* 0x3694 */ cXyz mOldSpeed;
    /* 0x36A0 */ cXyz m36A0;
    /* 0x36AC */ cXyz m36AC;
    /* 0x36B8 */ cXyz m36B8;
    /* 0x36C4 */ cXyz m36C4;
    /* 0x36D0 */ cXyz m36D0;
    /* 0x36DC */ cXyz m36DC;
    /* 0x36E8 */ cXyz mHookshotRootPos;
    /* 0x36F4 */ cXyz m36F4;
    /* 0x3700 */ cXyz m3700;
    /* 0x370C */ cXyz m370C;
    /* 0x3718 */ cXyz m3718;
    /* 0x3724 */ cXyz m3724;
    /* 0x3730 */ cXyz m3730;
    /* 0x373C */ cXyz m373C;
    /* 0x3748 */ cXyz m3748;
    /* 0x3754 */ u8 m3754[0x37B4 - 0x3754];
    /* 0x37B4 */ Mtx m37B4;
    /* 0x37E4 */ daPy_swBlur_c mSwBlur;
    /* 0x3DB8 */ daPy_footData_c mFootData[2];
    /* 0x3FE8 */ dCcD_Stts mStts;
    /* 0x4024 */ dCcD_Cyl mCyl;
    /* 0x4154 */ dCcD_Cyl mWindCyl;
    /* 0x4284 */ dCcD_Cyl mAtCyl;
    /* 0x43B4 */ dCcD_Cyl mLightCyl;
    /* 0x44E4 */ dCcD_Cps mAtCps[3];
    /* 0x488C */ dCcD_Cps mFanWindCps;
    /* 0x49C4 */ dCcD_Sph mFanWindSph;
    /* 0x4AF0 */ dCcD_Cps mFanLightCps;
    
    struct ProcInitTableEntry {
        /* 0x00 */ ProcFunc mProcFunc;
        /* 0x0C */ u32 mProcFlags;
    };  // Size: 0x10
    static ProcInitTableEntry mProcInitTable[];
    
    static ProcFunc mDemoProcInitFuncTable[];
    
    struct TexAnmTableEntry {
        /* 0x00 */ u16 mBtpIdx;
        /* 0x02 */ u16 mBtkIdx;
    };  // Size: 0x04
    static const TexAnmTableEntry mTexAnmIndexTable[];
    
    static const daPy_anmIndex_c mSwordAnmIndexTable[];
    static const daPy_anmIndex_c mBokoAnmIndexTable[];
    static const daPy_anmIndex_c mHammerAnmIndexTable[];
    
    struct AnmDataTableEntry {
        /* 0x00 */ daPy_anmIndex_c mAnmIdx;
        /* 0x04 */ u8 mLeftHandIdx;
        /* 0x05 */ u8 mRightHandIdx;
        /* 0x06 */ u16 mTexAnmIdx;
    };  // Size: 0x08
    static const AnmDataTableEntry mAnmDataTable[];
};  // Size: 0x4C28

inline daPy_lk_c* daPy_getPlayerLinkActorClass() {
    return (daPy_lk_c*)dComIfGp_getLinkPlayer();
}

#endif /* D_A_PLAYER_MAIN */
