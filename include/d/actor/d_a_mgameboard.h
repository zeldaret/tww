#ifndef D_A_MGAMEBOARD_H
#define D_A_MGAMEBOARD_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_seafightgame.h"
#include "d/d_lib.h"

class dDlst_2DNumber_c;
class dDlst_2DMinigame_c;
class dDlst_2DObject_c;

class daMgBoard_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    void reqClearGame() {}
    void set_mtx(); // weak but not inlined?

    bool checkClearGame();
    u8 getScore();
    void reqStartGame();
    bool checkEndGame();
    void setGInfoDraw();
    void clrGInfoDraw();
    void CreateHeap();
    void set_2dposition();
    void CreateInit();
    void MiniGameInit();
    bool _execute();
    void execGameMain();
    void execEndGame();
    void MinigameMain();
    void CursorMove();

    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpBoardModel;
    /* 0x29C */ J3DModel* mpCursorModel;
    /* 0x2A0 */ J3DModel* mpHitModel[20];
    /* 0x2F0 */ J3DModel* mpMissModel[32];
    /* 0x370 */ J3DModel* mpShip2Model[2];
    /* 0x378 */ J3DModel* mpShip3Model[2];
    /* 0x380 */ J3DModel* mpShip4Model;
    /* 0x384 */ u8 field_0x384[0x468 - 0x384];
    /* 0x468 */ u8 mBoardPosX;
    /* 0x469 */ u8 mBoardPosY;
    /* 0x46A */ u8 field_0x46A[0x46C - 0x46A];
    /* 0x46C */ int mLastFirePosX;
    /* 0x470 */ int mLastFirePosY;
    /* 0x474 */ u8 field_0x474[0x47C - 0x474];
    /* 0x47C */ dSeaFightGame_info_c mSeaFightGame;
    /* 0x57C */ u8 field_0x57C[0x580 - 0x57C];
    /* 0x580 */ int mMissModelCount;
    /* 0x584 */ int mHitModelCount;
    /* 0x588 */ s16 mMinigameStartIdx;
    /* 0x58A */ s16 mMinigameEndIdx;
    /* 0x58C */ STControl mStickControl;
    /* 0x5B4 */ cXyz mNPCPos;
    /* 0x5C0 */ dDlst_2DNumber_c* mpNumber0;
    /* 0x5C4 */ dDlst_2DNumber_c* mpNumber1;
    /* 0x5C8 */ dDlst_2DMinigame_c* mpMinigameDList;
    /* 0x5CC */ dDlst_2DObject_c* mpSquidIcon[3];
    /* 0x5D8 */ u8 mpBombIcons;
    /* 0x5D9 */ u8 field_0x5D9[0x638 - 0x5D9];
    /* 0x638 */ int mState;
    /* 0x63C */ u8 mbDraw;
    /* 0x63D */ u8 mbStartGame;
    /* 0x63E */ u8 mbEndGame;
    /* 0x63F */ u8 mbForceEnd;
    /* 0x640 */ u8 mTimer;
};

#endif /* D_A_MGAMEBOARD_H */
