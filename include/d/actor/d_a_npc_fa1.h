#ifndef D_A_NPC_FA1_H
#define D_A_NPC_FA1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Fa1_McaMorfCallBack1_c : public mDoExt_McaMorfCallBack1_c {
public:
    daNpc_Fa1_McaMorfCallBack1_c();
    bool execute(unsigned short, J3DTransformInfo*);

public:
    /* 0x04 */ s16 m04;
    /* 0x06 */ u16 m06;
};

class daNpc_Fa1_c : public fopNpc_npc_c {
public:

    enum ActionType_e {
        ActionType_NORMAL_MOVE_e = 0,
        ActionType_PLAYER_MOVE_e = 1,
        ActionType_ESCAPE_MOVE_e = 2,
        ActionType_BOTTLE_APPEAR_MOVE_e = 3,
        ActionType_BOTTLE_BABA_WAIT_e = 4,
        ActionType_BOTTLE_BABA_MOVE_e = 5,
        ActionType_BOTTLE_BABA_MOVE2_e = 6,
        ActionType_BIGELF_CHANGE_e = 7,
        ActionType_HOVER_MOVE_e = 8,
    };

    enum MoveType_e {
        MoveType_STRAIGHT_e = 0,
        MoveType_TURN_e = 1,
        MoveType_UP_e = 2,
        MoveType_AREAOUTMOVE_e = 3,
    };

    void checkStatus(unsigned char) {}
    void countTime2() {}
    void countTimer() {}
    void getAngSpeed() {}
    void getGroundY() {}
    void getMode() {}
    void getPlayerR() {}
    void getSubMode() {}
    void getTimer() {}
    void getpLocalPos() {}
    void isBabaMode() {}
    void isLinkMode() {}
    void isTypeArea() {}
    void isTypeBaba() {}
    void isTypeHover() {}
    void isTypeLink() {}
    void isTypeLinkDown() {}
    void isTypeTimer() {}
    void setAngSpeed(short) {}
    void setGroundY(float) {}
    void setLocalPos(float) {}
    void setMode(unsigned char) {}
    void setPlayerR(float) {}
    void setStatus(unsigned char) {}
    void setSubMode(unsigned char) {}
    void setTime2(unsigned char) {}
    void setTimer(unsigned short) {}
    void setTypeNormal() {}

    void setPointLightParam();
    int createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL checkBinCatch();
    void position_move(float, float);
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
    /* 0x780 */ f32 m780;
    /* 0x784 */ f32 mGroundYPos;
    /* 0x788 */ u16 mTimer;
    /* 0x78A */ s16 m78A;
    /* 0x78C */ s16 m78C;
    /* 0x78E */ s16 m78E;
    /* 0x790 */ u8 mActionType;
    /* 0x791 */ u8 mMoveTimer;
    /* 0x792 */ u8 mMoveType;
    /* 0x793 */ s8 m793;
    /* 0x794 */ s8 m794;
    /* 0x795 */ u8 m795[0x798 - 0x795];
    /* 0x798 */ s16 m798;
    /* 0x79A */ s16 m79A;
    /* 0x79C */ f32 m79C;
    /* 0x7A0 */ f32 m7A0;
};

class daNpc_Fa1_HIO3_c {
public:
    struct hio_prm_c {
        // Note: Offsets are relative to daNpc_Fa1_HIO3_c instead of hio_prm_c for convenience.
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ s16 m18;
    };

    daNpc_Fa1_HIO3_c();
    virtual ~daNpc_Fa1_HIO3_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
};

class daNpc_Fa1_HIO2_c {
public:
    struct hio_prm_c {
        // Note: Offsets are relative to daNpc_Fa1_HIO2_c instead of hio_prm_c for convenience.
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ s16 m20;
        /* 0x22 */ s16 m22;
        /* 0x24 */ s16 m24;
    };

    daNpc_Fa1_HIO2_c();
    virtual ~daNpc_Fa1_HIO2_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
};

class daNpc_Fa1_HIO_c : public JORReflexible {
public:
    struct hio_prm_c {
        // Note: Offsets are relative to daNpc_Fa1_HIO_c instead of hio_prm_c for convenience.
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ s16 m3C;
        /* 0x3E */ s16 m3E;
        /* 0x40 */ s16 m40;
        /* 0x42 */ s16 m42;
        /* 0x44 */ s16 m44;
        /* 0x46 */ s16 m46;
        /* 0x48 */ s16 m48;
        /* 0x4A */ s16 m4A;
        /* 0x4C */ s16 m4C;
        /* 0x4E */ s16 m4E;
    };

    daNpc_Fa1_HIO_c();
    virtual ~daNpc_Fa1_HIO_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
    /* 0x50 */ daNpc_Fa1_HIO2_c m50;
    /* 0x78 */ daNpc_Fa1_HIO3_c m78;
};

#endif /* D_A_NPC_FA1_H */
