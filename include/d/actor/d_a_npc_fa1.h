#ifndef D_A_NPC_FA1_H
#define D_A_NPC_FA1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"
#include "SSystem/SComponent/c_lib.h"

class daNpc_Fa1_McaMorfCallBack1_c : public mDoExt_McaMorfCallBack1_c {
public:
    daNpc_Fa1_McaMorfCallBack1_c();
    bool execute(u16 jnt_no, J3DTransformInfo*);

    s16 getNeckAngle() { return mNeckAngle;}
    void setNeckAngle(s16 angle) { mNeckAngle = angle; }
    u16 getNeckJoint() { return mNeckJoint; }
    void setNeckJoint(u16 joint) { mNeckJoint = joint; }

public:
    /* 0x04 */ s16 mNeckAngle;
    /* 0x06 */ u16 mNeckJoint;
};

class daNpc_Fa1_c : public fopNpc_npc_c {
public:
    enum Type_e {
        Type_NORMAL_e = 0,
        Type_TIMER_e = 1,
        Type_LINK_e = 2,
        Type_BABA_e = 3,
        Type_AREA_e = 4,
        Type_LINK_DOWN_e = 5,
        Type_HOVER_e = 6,
    };

    enum Mode_e {
        Mode_NORMAL_MOVE_e = 0,
        Mode_PLAYER_MOVE_e = 1,
        Mode_ESCAPE_MOVE_e = 2,
        Mode_BOTTLE_APPEAR_MOVE_e = 3,
        Mode_BOTTLE_BABA_WAIT_e = 4,
        Mode_BOTTLE_BABA_MOVE_e = 5,
        Mode_BOTTLE_BABA_MOVE2_e = 6,
        Mode_BIGELF_CHANGE_e = 7,
        Mode_HOVER_MOVE_e = 8,
    };

    enum Normal_SubMode_e {
        NormalSubMode_STRAIGHT_e = 0,
        NormalSubMode_TURN_e = 1,
        NormalSubMode_AREAMOVE_e = 2,
        NormalSubMode_AREAOUTMOVE_e = 3,
    };

    enum Bottle_SubMode_e {
        BottleSubMode_UP1_e = 0,
        BottleSubMode_DOWN_e = 1,
        BottleSubMode_UP2_e = 2,
    };

    enum BottleBaba_SubMode_e {
        BottleBabaSubMode_BABADOWN_e = 0,
        BottleBabaSubMode_UP2_e = 1,
    };

    u8 getMode() { return mMode; }
    void setMode(u8 mode) { mMode = mode; }
    bool isLinkMode() { return mMode == Mode_PLAYER_MOVE_e; }
    void isBabaMode() {}
    u8 getSubMode() { return mSubMode; }
    void setSubMode(u8 submode) { mSubMode = submode; }

    bool isTypeTimer() { return mType == Type_TIMER_e; }
    bool isTypeLink() { return mType == Type_LINK_e; }
    bool isTypeBaba() { return mType == Type_BABA_e; }
    bool isTypeArea() { return mType == Type_AREA_e; }
    bool isTypeLinkDown() { return mType == Type_LINK_DOWN_e; }
    bool isTypeHover() { return mType == Type_HOVER_e; }
    void setTypeNormal() { mType = Type_NORMAL_e; }

    f32 getGroundY() { return mGroundY; }
    void setGroundY(f32 y) { mGroundY = y; }

    bool checkStatus(u8 bit) { return cLib_checkBit(mStatus, bit); }
    void setStatus(u8 status) { cLib_setBit(mStatus, status); }

    void getTimer() {}
    void setTimer(u16) {}
    void countTimer() {}
    void setTime2(u8) {}
    void countTime2() {}

    void getAngSpeed() {}
    void setAngSpeed(s16) {}
    f32 getPlayerR() { return mPlayerR; }
    void setPlayerR(f32 radius) { mPlayerR = radius; }
    void getpLocalPos() {}
    void setLocalPos(f32) {}

    void setPointLightParam();
    int createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL checkBinCatch();
    void position_move(f32, f32);
    void BGCheck();
    void init_normal_move();
    void normal_move();
    void init_straight();
    void init_straight2();
    void straight();
    void init_turn();
    void turn();
    void init_areaMove();
    void areaMove();
    void init_areaOutMove();
    void areaOutMove();
    void init_get_player_move();
    void get_player_move();
    void init_escape_move();
    void escape_move();
    void init_hover_move();
    void hover_move();
    void init_bottle_appear_move();
    void bottle_appear_move();
    void init_up1();
    void up1();
    void init_down();
    void down();
    void init_up2();
    void up2();
    void init_bottle_baba_wait();
    void bottle_baba_wait();
    void init_bottle_baba_move();
    void bottle_baba_move();
    void init_bottle_baba_move2();
    void bottle_baba_move2();
    void init_baba_down();
    void baba_down();
    void init_baba_up();
    void init_bigelf_change();
    void bigelf_change();
    void findPlayer();
    BOOL _delete();
    cPhs_State _create();
    int CreateHeap();
    void setMtx();

public:
    typedef void(daNpc_Fa1_c::*MoveFunc_t)();
    typedef void(daNpc_Fa1_c::*MoveSubFunc_t)();
    typedef void(daNpc_Fa1_c::*BottleMoveSubFunc_t)();
    typedef void(daNpc_Fa1_c::*BottleBabaSubFunc_t)();

    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ mDoExt_McaMorf* mpDoExt_McaMorf;
    /* 0x6D0 */ daNpc_Fa1_McaMorfCallBack1_c mMcaMorfCallback1;
    /* 0x6D8 */ dPa_followEcallBack mSparklePtclCallback;
    /* 0x6EC */ JPABaseEmitter* mpEmitter;
    /* 0x6F0 */ dBgS_ObjGndChk_All mGndChk;
    /* 0x744 */ LIGHT_INFLUENCE mPointLight;
    /* 0x764 */ fopAc_ac_c* m764;
    /* 0x768 */ cXyz m768;
    /* 0x774 */ cXyz m774;
    /* 0x780 */ f32 mPlayerR;
    /* 0x784 */ f32 mGroundY;
    /* 0x788 */ u16 mTimer;
    /* 0x78A */ s16 m78A;
    /* 0x78C */ s16 m78C;
    /* 0x78E */ s16 m78E;
    /* 0x790 */ u8 mMode;
    /* 0x791 */ u8 mMoveTimer;
    /* 0x792 */ u8 mSubMode;
    /* 0x793 */ u8 mStatus;
    /* 0x794 */ s8 mType;
    /* 0x795 */ u8 m795[0x798 - 0x795];
    /* 0x798 */ s16 m798;
    /* 0x79A */ s16 m79A;
    /* 0x79C */ f32 m79C;
    /* 0x7A0 */ f32 m7A0;
};

#endif /* D_A_NPC_FA1_H */
