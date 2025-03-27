#ifndef D_A_SHIP_H
#define D_A_SHIP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_msg.h"

class camera_class;
class daGrid_c;
class daTornado_c;
class daPy_FLG1;
class daBomb_c;

class daShip_c : public fopAc_ac_c {
public:
    enum daSHIP_SFLG {
        daSFLG_UNK1_e         = 0x00000001,
        daSFLG_UNK2_e         = 0x00000002,
        daSFLG_UNK4_e         = 0x00000004,
        daSFLG_UNK8_e         = 0x00000008,
        daSFLG_UNK10_e        = 0x00000010,
        daSFLG_UNK20_e        = 0x00000020,
        daSFLG_UNK40_e        = 0x00000040,
        daSFLG_UNK80_e        = 0x00000080,
        daSFLG_UNK100_e       = 0x00000100,
        daSFLG_UNK200_e       = 0x00000200,
        daSFLG_UNK400_e       = 0x00000400,
        daSFLG_UNK800_e       = 0x00000800,
        daSFLG_UNK1000_e      = 0x00001000,
        daSFLG_UNK2000_e      = 0x00002000,
        daSFLG_UNK4000_e      = 0x00004000,
        daSFLG_UNK8000_e      = 0x00008000,
        daSFLG_UNK10000_e     = 0x00010000,
        daSFLG_UNK20000_e     = 0x00020000,
        daSFLG_UNK40000_e     = 0x00040000,
        daSFLG_UNK80000_e     = 0x00080000,
        daSFLG_UNK100000_e    = 0x00100000,
        daSFLG_HEAD_NO_DRAW_e = 0x00200000,
        daSFLG_UNK400000_e    = 0x00400000,
        daSFLG_UNK800000_e    = 0x00800000,
        daSFLG_UNK1000000_e   = 0x01000000,
        daSFLG_UNK2000000_e   = 0x02000000,
        daSFLG_UNK4000000_e   = 0x04000000,
        daSFLG_UNK8000000_e   = 0x08000000,
        daSFLG_UNK10000000_e  = 0x10000000,
        daSFLG_UNK20000000_e  = 0x20000000,
        daSFLG_UNK40000000_e  = 0x40000000,
        daSFLG_UNK80000000_e  = 0x80000000
    };

    enum daShip_c__ShipMode {
        Idle = 0,
        Sailing = 1,
        UsingCannon = 2,
        UsingSalvageArm = 3,
    };

    typedef BOOL (daShip_c::*ProcFunc)();
    
    bool checkStateFlg(daSHIP_SFLG flag) const { return mStateFlag & flag; }
    bool checkHeadNoDraw() const { return checkStateFlg(daSFLG_HEAD_NO_DRAW_e); }
    
    int getTactWarpPosNum() const { return mTactWarpPosNum; }
    void setTactWarpPosNum(int num) { mTactWarpPosNum = num; }
    u32 getTactWarpID() { return mTactWarpID; }
    void setTactWarpID(u32 warpID) { mTactWarpID = warpID; }
        
    void checkCraneMode() const {}
    void checkCraneUpEnd() const {}
    BOOL checkForceMove() const { return getTornadoActor() || getWhirlActor(); }
    void checkJumpOkFlg() const {}
    void checkRopeCntMax() const {}
    void checkRopeDownStart() const {}
    void checkSalvageDemo() const {}
    void checkShootCannon() const {}
    void checkTornadoFlg() const {}
    void checkTornadoUp() const {}
    void getBeltSpeed() const {}
    void getBodyMtx() {}
    s16 getCannonAngleX() const { return this->shape_angle.x + this->m0396 - 0x4000; }
    void getCannonAngleY() const {}
    void getCraneAngle() const {}
    void getCraneBaseAngle() const {}
    void getCraneHookAngleY() const {}
    void getCraneRipplePosX() const {}
    void getCraneRipplePosY() const {}
    void getCraneRipplePosZ() const {}
    void getCraneTop() {}
    void getFlyFlg() {}
    void getHeadJntMtx() {}
    void getJumpFlg() const {}
    void getJumpRate() {}
    void getLandFlg() const {}
    void getPart() const {}
    void getRopeCnt() const {}
    void getSailAngle() {}
    void getSailOn() {}
    void getTactJntMtx() {}
    void getTillerAngleRate() {}
    void getTillerTopPosP() {}
    daTornado_c* getTornadoActor() const { return mTornadoActor; }
    fopAc_ac_c* getWhirlActor() const { return mWhirlActor; }
    void offCraneHookFlg() {}
    void offFantomGanonBattle() {}
    void offStateFlg(daSHIP_SFLG flag) { mStateFlag &= ~flag;}
    void offTornadoFlg() {
        mTornadoID = fpcM_ERROR_PROCESS_ID_e;
        mTornadoActor = NULL;
    }
    void offWhirlFlg() {
        mWhirlID = fpcM_ERROR_PROCESS_ID_e;
        mWhirlActor = NULL;
    }

    void onCb1Ride() {}
    void onCraneHookFlg() {}
    void onCrashFlg() {}
    void onFantomGanonBattle() {}
    void onJumpRideFlg() {}
    void onLinkSit() {}
    void onSceneChange() {}
    void onShortHitFlg() {}
    void onStateFlg(daSHIP_SFLG flag) { mStateFlag |= flag; }
    void onTornadoFlg(u32 tornadoID) { mTornadoID = tornadoID; }
    void onWhirlFlg(unsigned long, short) {}
    void onWhirlFlgDirect(unsigned long, short) {}
    void setAtnPos(const cXyz*) {}
    void setCannon() {}
    void setCrane() {}
    void setGetOffFirst() {}
    void setGetOffSecond() {}
    void setPaddleMove() {}
    void setReadyFirst() {}
    void setReadySecond() {}
    void setStartModeThrow() {}
    void setStartModeWarp() {}
    void setSteerMove() {}
    void setTactWarp() {}

    BOOL bodyJointCallBack(int);
    BOOL cannonJointCallBack(int);
    BOOL craneJointCallBack();
    BOOL headJointCallBack0();
    BOOL headJointCallBack1(int);
    BOOL draw();
    BOOL checkForceMessage();
    void setInitMessage();
    BOOL setNextMessage(msg_class*);
    void seStart(u32, cXyz*);
    void setSailAngle();
    void setControllAngle(s16);
    void getMaxWaterY(cXyz*);
    void setWaveAngle(s16*, s16*);
    f32 getWaterY();
    void setYPos();
    BOOL checkOutRange();
    void decrementShipSpeed(f32);
    void firstDecrementShipSpeed(f32);
    s16 getAimControllAngle(s16);
    void setMoveAngle(s16);
    void changeDemoEndProc();
    void setCrashData(s16);
    BOOL checkNextMode(int);
    void setPartOnAnime(u8);
    void setPartOffAnime();
    void setPartAnimeInit(u8);
    void setSelfMove(int);
    BOOL procWait_init();
    BOOL procWait();
    BOOL procReady_init();
    BOOL procReady();
    BOOL procGetOff_init();
    BOOL procGetOff();
    BOOL procPaddleMove_init();
    BOOL procPaddleMove();
    BOOL procSteerMove_init();
    BOOL procSteerMove();
    BOOL procCannonReady_init();
    BOOL procCannonReady();
    BOOL procCannon_init();
    BOOL procCannon();
    BOOL procCraneReady_init();
    BOOL procCraneReady();
    BOOL procCrane_init();
    BOOL procCrane();
    BOOL procCraneUp_init();
    BOOL procCraneUp();
    BOOL procToolDemo_init();
    BOOL procToolDemo();
    BOOL procZevDemo_init();
    BOOL procZevDemo();
    BOOL procTalkReady_init();
    BOOL procTalkReady();
    BOOL procTalk_init();
    BOOL procTalk();
    BOOL procTurn_init();
    BOOL procTurn();
    BOOL procTornadoUp_init();
    BOOL procTornadoUp();
    BOOL procStartModeWarp_init();
    BOOL procStartModeWarp();
    BOOL procTactWarp_init();
    BOOL procTactWarp();
    BOOL procWhirlDown_init();
    BOOL procWhirlDown();
    BOOL procStartModeThrow_init();
    BOOL procStartModeThrow();
    void setEffectData(f32, s16);
    void setRoomInfo();
    void incRopeCnt(int, int);
    void setRopePos();
    f32 getAnglePartRate();
    void setTornadoActor();
    void setWhirlActor();
    void setHeadAnm();
    BOOL execute();
    BOOL shipDelete();
    BOOL createHeap();
    cPhs_State create();
    void initStartPos(cXyz const*, s16);

    static cXyz l_rope_base_vec;

public:
    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ mDoExt_McaMorf* m0298;
    /* 0x029C */ mDoExt_McaMorf* m029C;
    /* 0x02A0 */ J3DTexMtx* m02A0;
    /* 0x02A4 */ J3DTexMtx* m02A4;
    /* 0x02A8 */ Mtx m02A8;
    /* 0x02D8 */ u8 m02D8[0x02E8 - 0x02D8];
    /* 0x02E8 */ J3DAnmTransform* mAnmTransform;
    /* 0x02EC */ J3DFrameCtrl mFrameCtrl;
    /* 0x0300 */ J3DModel* mpCannonModel;
    /* 0x0304 */ J3DModel* mpSalvageArmModel;
    /* 0x0308 */ J3DModel* mpLinkModel;
    /* 0x030C */ mDoExt_3DlineMat1_c mRopeLine;
    /* 0x0348 */ u8 m0348[0x034A - 0x0348];
    /* 0x034A */ s8 m034A;
    /* 0x034B */ u8 m034B;
    /* 0x034C */ u8 m034C;
    /* 0x034D */ u8 m034D;
    /* 0x034E */ u8 mShipMode;
    /* 0x034F */ u8 m034F;
    /* 0x0350 */ u8 m0350;
    /* 0x0351 */ u8 m0351;
    /* 0x0352 */ u8 m0352;
    /* 0x0353 */ u8 m0353;
    /* 0x0354 */ int mEvtStaffId;
    /* 0x0358 */ fpc_ProcID mStateFlag;
    /* 0x035C */ fpc_ProcID mNextMessageID;
    /* 0x0360 */ fpc_ProcID mShadowId;
    /* 0x0364 */ s16 m0364;
    /* 0x0366 */ s16 m0366;
    /* 0x0368 */ u8 m0368[0x036C - 0x0368];
    /* 0x036C */ s16 m036C;
    /* 0x036E */ s16 m036E;
    /* 0x0370 */ s16 m0370;
    /* 0x0372 */ s16 m0372;
    /* 0x0374 */ s16 m0374;
    /* 0x0376 */ s16 m0376;
    /* 0x0378 */ s16 m0378;
    /* 0x037A */ s16 m037A;
    /* 0x037C */ s16 m037C;
    /* 0x037E */ s16 m037E;
    /* 0x0380 */ s16 m0380;
    /* 0x0382 */ s16 m0382;
    /* 0x0384 */ s16 m0384;
    /* 0x0386 */ s16 m0386;
    /* 0x0388 */ s16 m0388;
    /* 0x038A */ u16 m038A;
    /* 0x038C */ s16 m038C;
    /* 0x038E */ s16 m038E;
    /* 0x0390 */ u16 m0390;
    /* 0x0392 */ u16 m0392;
    /* 0x0394 */ s16 m0394;
    /* 0x0396 */ s16 m0396;
    /* 0x0398 */ s16 m0398;
    /* 0x039A */ s16 m039A;
    /* 0x039C */ s16 m039C;
    /* 0x039E */ s16 mCurrentRopeSegmentIndex;
    /* 0x03A0 */ s16 m03A0;
    /* 0x03A2 */ s16 m03A2;
    /* 0x03A4 */ s16 mStickMAng;
    /* 0x03A6 */ s16 m03A6;
    /* 0x03A8 */ s16 m03A8;
    /* 0x03AA */ s16 m03AA;
    /* 0x03AC */ s16 m03AC;
    /* 0x03AE */ s16 m03AE;
    /* 0x03B0 */ s16 m03B0;
    /* 0x03B2 */ s16 m03B2;
    /* 0x03B4 */ u16 m03B4;
    /* 0x03B6 */ s16 m03B6;
    /* 0x03B8 */ s16 m03B8;
    /* 0x03BA */ s16 m03BA;
    /* 0x03BC */ csXyz m03BC;
    /* 0x03C2 */ s16 m03C2;
    /* 0x03C4 */ int m03C4;
    /* 0x03C8 */ int mTactWarpPosNum;
    /* 0x03CC */ int m03CC;
    /* 0x03D0 */ f32 m03D0;
    /* 0x03D4 */ f32 m03D4;
    /* 0x03D8 */ f32 m03D8;
    /* 0x03DC */ f32 m03DC;
    /* 0x03E0 */ f32 m03E0;
    /* 0x03E4 */ f32 m03E4;
    /* 0x03E8 */ f32 m03E8;
    /* 0x03EC */ f32 mStickMVal;
    /* 0x03F0 */ u8 m03F0[0x03F4 - 0x03F0];
    /* 0x03F4 */ f32 m03F4;
    /* 0x03F8 */ f32 m03F8;
    /* 0x03FC */ f32 mFwdVel;
    /* 0x0400 */ f32 m0400;
    /* 0x0404 */ f32 m0404;
    /* 0x0408 */ f32 m0408;
    /* 0x040C */ f32 m040C;
    /* 0x0410 */ fpc_ProcID mGridID;
    /* 0x0414 */ daGrid_c* mpGrid;
    /* 0x0418 */ fpc_ProcID mTornadoID;
    /* 0x041C */ daTornado_c* mTornadoActor;
    /* 0x0420 */ fpc_ProcID mWhirlID;
    /* 0x0424 */ fopAc_ac_c* mWhirlActor;
    /* 0x0428 */ cXyz* m0428;
    /* 0x042C */ fpc_ProcID mTactWarpID;
    /* 0x0430 */ s32 m0430;
    /* 0x0434 */ cXyz* m0434;
    /* 0x0438 */ cXyz m0438;
    /* 0x0444 */ cXyz m0444;
    /* 0x0450 */ cXyz m0450;
    /* 0x045C */ cXyz m045C;
    /* 0x0468 */ cXyz mRopeLineSegments[250];
    /* 0x1020 */ cXyz m1020;
    /* 0x102C */ cXyz m102C;
    /* 0x1038 */ cXyz m1038;
    /* 0x1044 */ cXyz m1044;
    /* 0x1050 */ cXyz m1050;
    /* 0x105C */ cXyz mEffPos;
    /* 0x1068 */ cXyz m1068;
    /* 0x1074 */ cXyz m1074;
    /* 0x1080 */ dBgS_AcchCir mAcchCir[4];
    /* 0x1180 */ dBgS_ObjAcch mAcch;
    /* 0x1344 */ dCcD_Stts mStts;
    /* 0x1380 */ dCcD_Cyl mCyl[3];
    /* 0x1710 */ dCcD_Sph mSph;
    /* 0x183C */ dPa_waveEcallBack mWaveR;
    /* 0x18A0 */ dPa_waveEcallBack mWaveL;
    /* 0x1904 */ dPa_splashEcallBack mSplash;
    /* 0x1920 */ dPa_trackEcallBack mTrack;
    /* 0x1970 */ dPa_rippleEcallBack mRipple;
    /* 0x1984 */ dPa_followEcallBack m1984;
    /* 0x1998 */ dPa_followEcallBack m1998;
    /* 0x19AC */ dPa_followEcallBack m19AC;
    /* 0x19C0 */ dPa_rippleEcallBack m19C0;
    /* 0x19D4 */ ProcFunc mProc;
};

class daShip_HIO_c0 {
    public:
        ~daShip_HIO_c0(){}

        /* 0x00 */ static const s16 tiller_speed;
        /* 0x02 */ static const s16 cannon_no_gravity_timer;
        /* 0x04 */ static const s16 throw_start_angle_speed;
        /* 0x06 */ static const s16 throw_return_angle_speed;
        /* 0x08 */ static const f32 paddle_speed;
        /* 0x0C */ static const f32 min_speed;
        /* 0x10 */ static const f32 wind_inc_speed;
        /* 0x14 */ static const f32 r_inc_speed;
        /* 0x18 */ static const f32 r_wind_inc_speed;
        /* 0x1C */ static const f32 fly_rate;
        /* 0x20 */ static const f32 wind_rate;
        /* 0x24 */ static const f32 ef_dis_speed;
        /* 0x28 */ static const f32 ef_speed_rate;
        /* 0x2C */ static const f32 ef_front_x;
        /* 0x30 */ static const f32 ef_front_y;
        /* 0x34 */ static const f32 ef_front_z;
        /* 0x38 */ static const f32 ef_back_x;
        /* 0x3C */ static const f32 ef_back_y;
        /* 0x40 */ static const f32 ef_back_z;
        /* 0x44 */ static const f32 ef_sp_max_speed;
        /* 0x48 */ static const f32 ef_pitch;
        /* 0x4C */ static const f32 ef_ind_scroll;
        /* 0x50 */ static const f32 ef_ind_scale;
        /* 0x54 */ static const f32 cannon_speed;
        /* 0x58 */ static const f32 cannon_gravity;
        /* 0x5C */ static const f32 whirl_init_speed;
        /* 0x60 */ static const f32 whirl_inc_speed;
        /* 0x64 */ static const f32 whirl_distance;
        /* 0x68 */ static const f32 tornado_init_speed;
        /* 0x6C */ static const f32 tornado_inc_speed;
        /* 0x70 */ static const f32 tornado_distance;
        /* 0x74 */ static const f32 tornado_pull_speed;
        /* 0x78 */ static const f32 throw_start_speedF;
        /* 0x7C */ static const f32 throw_start_speed_y;
    public:
};

#endif /* D_A_SHIP_H */
