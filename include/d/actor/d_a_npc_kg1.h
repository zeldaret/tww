#ifndef D_A_NPC_KG1_H
#define D_A_NPC_KG1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Kg1_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
    void getAttentionBasePos() {}
    void getEyePos() {}
    void setAction(void (daNpc_Kg1_c::*)()) {}

    void lookBack();
    void chkAttention();
    void initTexPatternAnm(int, bool);
    void playTexPatternAnm();
    void set_mtx();
    void CreateHeap();
    void CreateInit();
    void eventOrder();
    void checkOrder();
    void kg1_talk_camera();
    void wait_action_init();
    void wait_action();
    void clr_seq_flag();
    void getMsg();
    void next_msgStatus(u32*);
    void anmAtr(u16);
    void setAnm();

    static const u8 m_highscore;

public:
    /* 0x6C4 */ J3DModel* m6C4;
    /* 0x6C8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6DC */ request_of_phase_process_class mPhs;
    /* 0x6E4 */ u8 m6E4[0x6F8 - 0x6E4];
    /* 0x6F8 */ mDoExt_btpAnm m6F8;
    /* 0x70C */ mDoExt_btpAnm m70C;
    /* 0x720 */ u8 m720;
    /* 0x721 */ u8 m721[0x72C - 0x721];
    /* 0x72C */ s16 m72C;
    /* 0x72E */ s16 m72E;
    /* 0x730 */ u8 m730;
    /* 0x731 */ u8 m731;
    /* 0x732 */ u8 m732;
    /* 0x733 */ u8 m733[0x74D - 0x733];
    /* 0x74D */ u8 m74D;
    /* 0x74E */ u8 m74E[0x750 - 0x74E];
    /* 0x750 */ u8 m750;
    /* 0x751 */ u8 m751;
    /* 0x752 */ u8 m752[0x773 - 0x752];
    /* 0x773 */ u8 mbDidClearGame;
    /* 0x774 */ u8 mbGameEnd;
    /* 0x775 */ u8 m775[0x778 - 0x775];
    /* 0x778 */ u8 m778;
    /* 0x779 */ u8 m779;
    /* 0x77A */ u8 mGameBoardScore;
    /* 0x77B */ u8 mEndGameTimer;
    /* 0x77C */ u8 m77C[0x780 - 0x77C];
    /* 0x780 */ int mWaitMode;
    /* 0x784 */ s16 m784;
    /* 0x786 */ u8 m786[0x788 - 0x786];
    /* 0x788 */ s16 m788;
    /* 0x78A */ u8 m78A[0x78C - 0x78A];
};

class daNpc_Kg1_HIO_c {
public:
    daNpc_Kg1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KG1_H */
