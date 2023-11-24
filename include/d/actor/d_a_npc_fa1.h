#ifndef D_A_NPC_FA1_H
#define D_A_NPC_FA1_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "JSystem/JParticle/JPAEmitter.h"

class daNpc_Fa1_c : public fopAc_ac_c {
public:
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
    void createInit();
    void _draw();
    void _execute();
    void checkBinCatch();
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
    void _delete();
    void _create();
    void CreateHeap();
    void setMtx();

public:
    /* 0x6C4 */ u8 m6C4[0x6D0 - 0x6C4];
    /* 0x6D0 */ daNpc_Fa1_McaMorfCallBack1_c mMcaMorfCallback1;
    /* 0x6D8 */ dPa_followEcallBack mSparklePtclCallback;
    /* 0x6EC */ JPABaseEmitter* mpEmitter;
    /* 0x6F0 */ dBgS_GndChk mGndChk;
    /* 0x744 */ u8 m744[0x784 - 0x744];
    /* 0x784 */ f32 mGroundYPos;
    /* 0x788 */ s16 m788;
    /* 0x78A */ u8 m78A[0x794 - 0x78A];
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 m795[0x7A4 - 0x795];
};

#endif /* D_A_NPC_FA1_H */
