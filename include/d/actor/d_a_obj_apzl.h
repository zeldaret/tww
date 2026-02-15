#ifndef D_A_OBJ_APZL_H
#define D_A_OBJ_APZL_H

#include "f_op/f_op_actor.h"
#include "d/d_lib.h"

class daObjApzl_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    u8 getblank() { return mPiecePos[mBlankIdx]; }

    bool move_piece();
    void check_arrow_draw();
    u8 search_piece(u8);
    void swap_piece(u8, u8);
    void randamize_piece();
    void save_piece();
    bool check_clear();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    u16 talk(int);
    void privateCut();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();
    
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpPieceModel[16];
    /* 0x2D8 */ J3DModel* mpArrowModel[4];
    /* 0x2E8 */ J3DModel* mpScoreboardModel[16];
    /* 0x328 */ mDoExt_btpAnm mScoreboardBtpAnm[16];
    /* 0x468 */ u8 mPuzzleNo;
    /* 0x46C */ STControl* stick;
    /* 0x470 */ u8 mType;
    /* 0x471 */ u8 mBlankIdx;
    /* 0x472 */ u8 mSwappedPieceIdx;
    /* 0x473 */ u8 mMoveTimer;
    /* 0x474 */ u8 mMoveDirection;
    /* 0x475 */ bool mShowBlankPiece;
    /* 0x476 */ u8 mPiecePos[16];
    /* 0x486 */ u8 mState;
    /* 0x487 */ bool mDrawArrow[4];
    /* 0x48C */ s16 mEventIdx[3];
    /* 0x492 */ s8 mActIdx;
    /* 0x493 */ bool mQuitGame;
    /* 0x494 */ bool mGameStarted;
    /* 0x495 */ bool mGameCleared;
    /* 0x496 */ bool mGaveReward;
    /* 0x497 */ bool mShownRewardMessage;
    /* 0x498 */ bool mPlayedStartSound;
    /* 0x49C */ fpc_ProcID mRupeeIds[30];
    /* 0x514 */ int mGivenRupeeCount;
    /* 0x518 */ u32 mMsgNo;
    /* 0x51C */ u32 mCurrMsgId;
    /* 0x520 */ msg_class* mpCurrMsg;
    /* 0x524 */ int mRewardTimer;
};  // Size: 0x528

namespace daObjApzl_prm {
    inline u8 getType(daObjApzl_c* i_this) { return (fopAcM_GetParam(i_this) >> 8); }
}

#endif /* D_A_OBJ_APZL_H */
