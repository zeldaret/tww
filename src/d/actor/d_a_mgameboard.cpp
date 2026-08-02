/**
 * d_a_mgameboard.cpp
 * Squid-Hunt/"Sploosh Kaboom" Minigame
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mgameboard.h"
#include "d/d_2dnumber.h"
#include "m_Do/m_Do_controller_pad.h"

#if VERSION == VERSION_DEMO
#include "JSystem/JUtility/JUTReport.h"
#endif

#if VERSION == VERSION_DEMO
#include "res/Object/Kaisen.h"
#elif VERSION == VERSION_JPN
// # include
#elif VERSION == VERSION_USA
#include "res/Object/Kaisen_e.h"
#elif VERSION == VERSION_PAL
// #include
#endif

char daMgBoard_c::m_arcname[9] = {};

u8 daMgBoard_c::m_bullet_num = 24;

const cXyz daMgBoard_c::m_cur_table[8][8] = {
    {
        cXyz(-87.5f, -87.5f, 0.0f),
        cXyz(-62.5f, -87.5f, 0.0f),
        cXyz(-37.5f, -87.5f, 0.0f),
        cXyz(-12.5f, -87.5f, 0.0f),
        cXyz(12.5f, -87.5f, 0.0f),
        cXyz(37.5f, -87.5f, 0.0f),
        cXyz(62.5f, -87.5f, 0.0f),
        cXyz(87.5f, -87.5f, 0.0f),
    },
    {
        cXyz(-87.5f, -62.5f, 0.0f),
        cXyz(-62.5f, -62.5f, 0.0f),
        cXyz(-37.5f, -62.5f, 0.0f),
        cXyz(-12.5f, -62.5f, 0.0f),
        cXyz(12.5f, -62.5f, 0.0f),
        cXyz(37.5f, -62.5f, 0.0f),
        cXyz(62.5f, -62.5f, 0.0f),
        cXyz(87.5f, -62.5f, 0.0f),
    },
    {
        cXyz(-87.5f, -37.5f, 0.0f),
        cXyz(-62.5f, -37.5f, 0.0f),
        cXyz(-37.5f, -37.5f, 0.0f),
        cXyz(-12.5f, -37.5f, 0.0f),
        cXyz(12.5f, -37.5f, 0.0f),
        cXyz(37.5f, -37.5f, 0.0f),
        cXyz(62.5f, -37.5f, 0.0f),
        cXyz(87.5f, -37.5f, 0.0f),
    },
    {
        cXyz(-87.5f, -12.5f, 0.0f),
        cXyz(-62.5f, -12.5f, 0.0f),
        cXyz(-37.5f, -12.5f, 0.0f),
        cXyz(-12.5f, -12.5f, 0.0f),
        cXyz(12.5f, -12.5f, 0.0f),
        cXyz(37.5f, -12.5f, 0.0f),
        cXyz(62.5f, -12.5f, 0.0f),
        cXyz(87.5f, -12.5f, 0.0f),
    },
    {
        cXyz(-87.5f, 12.5f, 0.0f),
        cXyz(-62.5f, 12.5f, 0.0f),
        cXyz(-37.5f, 12.5f, 0.0f),
        cXyz(-12.5f, 12.5f, 0.0f),
        cXyz(12.5f, 12.5f, 0.0f),
        cXyz(37.5f, 12.5f, 0.0f),
        cXyz(62.5f, 12.5f, 0.0f),
        cXyz(87.5f, 12.5f, 0.0f),
    },
    {
        cXyz(-87.5f, 37.5f, 0.0f),
        cXyz(-62.5f, 37.5f, 0.0f),
        cXyz(-37.5f, 37.5f, 0.0f),
        cXyz(-12.5f, 37.5f, 0.0f),
        cXyz(12.5f, 37.5f, 0.0f),
        cXyz(37.5f, 37.5f, 0.0f),
        cXyz(62.5f, 37.5f, 0.0f),
        cXyz(87.5f, 37.5f, 0.0f),
    },
    {
        cXyz(-87.5f, 62.5f, 0.0f),
        cXyz(-62.5f, 62.5f, 0.0f),
        cXyz(-37.5f, 62.5f, 0.0f),
        cXyz(-12.5f, 62.5f, 0.0f),
        cXyz(12.5f, 62.5f, 0.0f),
        cXyz(37.5f, 62.5f, 0.0f),
        cXyz(62.5f, 62.5f, 0.0f),
        cXyz(87.5f, 62.5f, 0.0f),
    },
    {
        cXyz(-87.5f, 87.5f, 0.0f),
        cXyz(-62.5f, 87.5f, 0.0f),
        cXyz(-37.5f, 87.5f, 0.0f),
        cXyz(-12.5f, 87.5f, 0.0f),
        cXyz(12.5f, 87.5f, 0.0f),
        cXyz(37.5f, 87.5f, 0.0f),
        cXyz(62.5f, 87.5f, 0.0f),
        cXyz(87.5f, 87.5f, 0.0f),
    },
};

const cXyz daMgBoard_c::m_sink_table[3] = {
    cXyz(162.5f, 87.5f, 0.0f),
    cXyz(162.5f, 62.5f, 0.0f),
    cXyz(162.5f, 37.5f, 0.0f),

};

const cXyz daMgBoard_c::m_bullet_table[3][8] = {
    {
        cXyz(-150.0f, 90.0f, 0.0f),
        cXyz(-150.0f, 70.0f, 0.0f),
        cXyz(-150.0f, 50.0f, 0.0f),
        cXyz(-150.0f, 30.0f, 0.0f),
        cXyz(-150.0f, 10.0f, 0.0f),
        cXyz(-150.0f, -10.0f, 0.0f),
        cXyz(-150.0f, -30.0f, 0.0f),
        cXyz(-150.0f, -50.0f, 0.0f),
    },
    {
        cXyz(-170.0f, 90.0f, 0.0f),
        cXyz(-170.0f, 70.0f, 0.0f),
        cXyz(-170.0f, 50.0f, 0.0f),
        cXyz(-170.0f, 30.0f, 0.0f),
        cXyz(-170.0f, 10.0f, 0.0f),
        cXyz(-170.0f, -10.0f, 0.0f),
        cXyz(-170.0f, -30.0f, 0.0f),
        cXyz(-170.0f, -50.0f, 0.0f),
    },
    {
        cXyz(-190.0f, 90.0f, 0.0f),
        cXyz(-190.0f, 70.0f, 0.0f),
        cXyz(-190.0f, 50.0f, 0.0f),
        cXyz(-190.0f, 30.0f, 0.0f),
        cXyz(-190.0f, 10.0f, 0.0f),
        cXyz(-190.0f, -10.0f, 0.0f),
        cXyz(-190.0f, -30.0f, 0.0f),
        cXyz(-190.0f, -50.0f, 0.0f),
    },
};

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daMgBoard_c*)i_this)->CreateHeap();
}

cPhs_State daMgBoard_c::_create() {
    fopAcM_ct(this, daMgBoard_c);
    strcpy(m_arcname, "Kaisen_e");
    cPhs_State result = dComIfG_resLoad(&mPhase, m_arcname);
    if (result == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x4E000)) {
            result = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }
    return result;
}

/* 0000010C-000007BC       .text CreateHeap__11daMgBoard_cFv */
BOOL daMgBoard_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AKBOD_e, 0, dRes_INDEX_KAISEN_E_BDL_AKBOD_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x126, 0x133), modelData != NULL);

    mpBoardModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpBoardModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AKCSR_e, 0, dRes_INDEX_KAISEN_E_BDL_AKCSR_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x136, 0x143), modelData != NULL);

    mpCursorModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpCursorModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AKATR_e, 0, dRes_INDEX_KAISEN_E_BDL_AKATR_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x146, 0x153), modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpHitModel); ++i) {
        mpHitModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpHitModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AKHZR_e, 0, dRes_INDEX_KAISEN_E_BDL_AKHZR_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x158, 0x165), modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpMissModel); ++i) {
        mpMissModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpMissModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AK2SH_e, 0, dRes_INDEX_KAISEN_E_BDL_AK2SH_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x16A, 0x177), modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpShip2Model); ++i) {
        mpShip2Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip2Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AK3SH_e, 0, dRes_INDEX_KAISEN_E_BDL_AK3SH_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x17C, 0x189), modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpShip3Model); ++i) {
        mpShip3Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip3Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)
        dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BDL_AK4SH_e, 0, dRes_INDEX_KAISEN_E_BDL_AK4SH_e, 0)); // TODO: JPN and PAL
    JUT_ASSERT(DEMO_SELECT(0x18E, 0x19B), modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpShip4Model); ++i) {
        mpShip4Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip4Model[i] == NULL) {
            return FALSE;
        }
    }

    mpNumber0 = new dDlst_2DNumber_c();
    if (mpNumber0 == NULL) {
        return FALSE;
    }
    mpNumber0->init(4, 0x1d6, 0x4b, 0x18, 0x18, 0);

    mpNumber1 = new dDlst_2DNumber_c();
    if (mpNumber1 == NULL) {
        return FALSE;
    }

    mpNumber1->init(4, 100, 0x50, 0x18, 0x18, 0);
    for (int i = 0; i < (int)ARRAY_SIZE(mpSquidIcon); ++i) {
        mpSquidIcon[i] = new dDlst_2DObject_c();
        if (mpSquidIcon[i] == NULL) {
            return FALSE;
        }

        mpSquidIcon[i]->init(
            (ResTIMG*)dComIfG_getObjectRes(
                m_arcname,
                VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_SHIP_NODAMAGE_e, 0, dRes_INDEX_KAISEN_E_BTI_KAISEN_IKA_01_e, 0)
            ), // TODO: JPN and PAL
            (ResTIMG*)dComIfG_getObjectRes(
                m_arcname,
                VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_HUNE_DAMAGE_e, 0, dRes_INDEX_KAISEN_E_BTI_KAISEN_IKA_02_e, 0)
            ) // TODO: JPN and PAL
        );
    }

    const int rows = 3;
    const int cols = 8;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const int idx = j + i * cols;
            mpBombIcons[idx] = new dDlst_2DObject_c();

            if (!mpBombIcons[idx])
                return FALSE;

            mpBombIcons[idx]->init(
                (ResTIMG*)dComIfG_getObjectRes(
                    m_arcname,
                    VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_BOMB_01_e, 0, dRes_INDEX_KAISEN_E_BTI_GAME_BOMB_01_e, 0)
                ), // TODO: JPN and PAL
                (ResTIMG*)dComIfG_getObjectRes(
                    m_arcname,
                    VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_BOMB_02_e, 0, dRes_INDEX_KAISEN_E_BTI_GAME_BOMB_02_e, 0)
                ) // TODO: JPN and PAL
            );
        }
    }

    mpMinigameDList = new dDlst_2DMinigame_c();
    if (mpMinigameDList == NULL) {
        return FALSE;
    }

    mpMinigameDList->init(
        (ResTIMG*)dComIfG_getObjectRes(
            m_arcname,
            VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_BEST_RECORD_e, 0, dRes_INDEX_KAISEN_E_BTI_GAME_BEST_RECORD_e, 0)
        ), // TODO: JPN and PAL
        (ResTIMG*)
            dComIfG_getObjectRes(m_arcname, VERSION_SELECT(dRes_INDEX_KAISEN_BTI_GAME_PAPER_e, 0, dRes_INDEX_KAISEN_E_BTI_GAME_PAPER_e, 0)) // TODO: JPN and PAL
    );
    set_2dposition();

    return TRUE;
}

/* 00000804-00000904       .text set_2dposition__11daMgBoard_cFv */
void daMgBoard_c::set_2dposition() {
    f32 float_one = 115.0;

    for (int i = 0; i < (int)ARRAY_SIZE(mpSquidIcon); ++i) {
        mpSquidIcon[i]->setPosition(523.0, float_one);
        float_one += 47.0f;
    }

    float_one = 95.0;
    f32 float_two = 120.0;

    const int rows = 3;
    const int cols = 8;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const int idx = j + i * cols;
            mpBombIcons[idx]->setPosition(float_one, float_two);
            float_two += 35.0f;
        }
        float_one -= 35.0f;
        float_two = 120.0f;
    }

    mpMinigameDList->setTitlePos(282.0, 70.0);
    mpMinigameDList->setScorePos(440.0, 60.0);
    mpMinigameDList->setTitleAlpha(0xFF);

    f32 shadow_alpha = 80.5f; // alpha is a u8 but this is needed to match ???
    mpMinigameDList->setScoreAlpha(shadow_alpha);
}

/* 00000904-000009E0       .text CreateInit__11daMgBoard_cFv */
void daMgBoard_c::CreateInit() {
    fopAcM_SetMtx(this, mpBoardModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -600, -300, -500, 600, 300, 100);
    mState = 0;
    mMinigameStartIdx = dComIfGp_evmng_getEventIdx("MINIGAME_START", 0xFF);
    mMinigameEndIdx = dComIfGp_evmng_getEventIdx("MINIGAME_END", 0xFF);
    mStickControl.setWaitParm(5, 2, 3, 2, 0.9, 0.5, 0, 0x800);
    MiniGameInit();
}

/* 000009E0-00000AE8       .text MiniGameInit__11daMgBoard_cFv */
void daMgBoard_c::MiniGameInit() {
    mBoardPosY = 0;
    mBoardPosX = 0;
    mLastFirePosY = -100;
    mLastFirePosX = -100;
    field_0x478 = 0;
    field_0x474 = 0;
    mSeaFightGame.init(m_bullet_num, 3);

    fopAc_ac_c* actor = fopAcM_SearchByName(fpcNm_NPC_KG1_e);
    if (actor != NULL) {
        mNPCPos.set(actor->current.pos);
    }

    set_mtx();

    for (int i = 0; i < (int)ARRAY_SIZE(mpSquidIcon); ++i) {
        mpSquidIcon[i]->mCurrentNo = 0;
    }

    const int rows = 3;
    const int cols = 8;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const int idx = j + i * cols;
            mpBombIcons[idx]->mCurrentNo = 0;
        }
    }
}

/* 00000AE8-00000DEC       .text set_mtx__11daMgBoard_cFv */
void daMgBoard_c::set_mtx() {
    J3DModel* model;
    J3DModel* board_model;
    J3DModel* cursor_model;

    board_model = mpBoardModel;
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    board_model->setBaseTRMtx(mDoMtx_stack_c::get());

    cursor_model = mpCursorModel;
    mDoMtx_stack_c::transS(
        m_cur_table[mBoardPosY][mBoardPosX].x + current.pos.x,
        m_cur_table[mBoardPosY][mBoardPosX].y + current.pos.y,
        m_cur_table[mBoardPosY][mBoardPosX].z + current.pos.z
    );
    mDoMtx_stack_c::YrotM(current.angle.y);
    cursor_model->setBaseTRMtx(mDoMtx_stack_c::get());

    mMissModelCount = 0;
    mHitModelCount = 0;

    for (u8 x = 0; x < 8; ++x) {
        for (u8 y = 0; y < 8; ++y) {

            u8 grid_value = mSeaFightGame.mGrid[x][y];
            model = NULL;
            if ((s32)grid_value == 3) {
                model = mpHitModel[mHitModelCount];
                mHitModelCount = mHitModelCount + 1;
            } else if ((s32)grid_value == 1) {
                model = mpMissModel[mMissModelCount];
                mMissModelCount = mMissModelCount + 1;
            }
            if (model != NULL) {
                mDoMtx_stack_c::transS(m_cur_table[y][x].x + current.pos.x, m_cur_table[y][x].y + current.pos.y, m_cur_table[y][x].z + current.pos.z);
                mDoMtx_stack_c::YrotM(current.angle.y);
                model->setBaseTRMtx(mDoMtx_stack_c::get());
            }
        }
    }

    u8 num_alive_ships = mSeaFightGame.getRest();
    for (int i = 0; i < num_alive_ships; ++i) {
        switch (mSeaFightGame.getMaxHP(i)) {
            case 2:
                model = mpShip2Model[0];
                break;
            case 3:
                model = mpShip3Model[0];
                break;
            case 4:
                model = mpShip4Model[0];
                break;
            default:
                model = NULL;
                break;
        }

        if (model != NULL) {
            u8 ship_x = mSeaFightGame.getShipStartX(i);
            u8 ship_y = mSeaFightGame.getShipStartY(i);
            mDoMtx_stack_c::transS(
                m_cur_table[ship_y][ship_x].x + current.pos.x,
                m_cur_table[ship_y][ship_x].y + current.pos.y,
                m_cur_table[ship_y][ship_x].z + current.pos.z
            );

            mDoMtx_stack_c::YrotM(current.angle.y);
            if ((s8)mSeaFightGame.mShips[i].field_0xe == 0) {
                mDoMtx_stack_c::ZrotM(0x4000);
            } else {
                mDoMtx_stack_c::ZrotM(-0x8000);
            }
            model->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
}

/* 00000E28-00000FD8       .text _execute__11daMgBoard_cFv */
bool daMgBoard_c::_execute() {
    /* Nonmatching */

#if VERSION == VERSION_DEMO
    u8 score;
    int event_reg;
#else
    u8 event_reg;
    u8 score;
#endif

    event_reg = dComIfGs_getEventReg(0xBEFF);
    score = mSeaFightGame.mScore;

    mpNumber0->set(event_reg);
    mpNumber1->set(score);
    set_2dposition();
    if (mbForceEnd != 0) {
        execEndGame();
        mbEndGame = 0;
        mbForceEnd = 0;
    }
    switch (mState) {
        case 0:
            mState = 1;
            mbStartGame = 0;
            break;
        case 1:
            if (mbStartGame != 0) {
                mState = 2;
            }
            break;
        case 2:
            mState = 3;
        case 3:
            execGameMain();
            if (mbEndGame != 0) {
                mTimer = 0x1E;
                mState = 4;
            }
            break;
        case 4:
            if (cLib_calcTimer<u8>(&mTimer) == 0) {
                mState = 0;
                if (!mSeaFightGame.isClearGame()) {
                    mDoAud_seStart(JA_SE_PLAYSPOT_END_F, &mNPCPos);
                } else {
                    mDoAud_seStart(JA_SE_PLAYSPOT_END_S, &mNPCPos);
                }
            }
            break;
    }

    return true;
}

/* 00000FD8-00001040       .text execGameMain__11daMgBoard_cFv */
bool daMgBoard_c::execGameMain() {
    MinigameMain();
    bool is_end_game = false;
    if (mSeaFightGame.getRest() == 0 || mSeaFightGame.checkRestBullet() == 0) {
        is_end_game = true;
    }

    if (is_end_game != 0) {
        mbEndGame = true;
        return true;
    }

    return false;
}

/* 00001040-00001060       .text execEndGame__11daMgBoard_cFv */
void daMgBoard_c::execEndGame() {
    MiniGameInit();
}

/* 00001060-00001250       .text MinigameMain__11daMgBoard_cFv */
BOOL daMgBoard_c::MinigameMain() {
    /* Nonmatching */
    if (mDoAud_checkSePlaying(0x8A8) != 0) {
        return TRUE;
    }

    CursorMove();
    s32 bullet_num = mSeaFightGame.checkRestBullet();
    s32 num_alive = mSeaFightGame.getRest();
    if (g_mDoCPd_cpadInfo[0].mButtonTrig.a && bullet_num > 0) {
        int attack_result = mSeaFightGame.attack(mBoardPosX, mBoardPosY);
        s32 alive = mSeaFightGame.getRest();
        int dead = mSeaFightGame.mDeadShipNum;
        s32 score = mSeaFightGame.mScore;
        mLastFirePosX = mBoardPosX;
        mLastFirePosY = mBoardPosY;
        if (attack_result >= 0) {
            mDoAud_seStart(JA_SE_PLAYSPOT_RIGHT, &mNPCPos);
            if ((num_alive != alive) && (alive != 0)) {
                mDoAud_seStart(JA_SE_PLAYSPOT_DESTROY, &mNPCPos);
            }
            dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0, 1, 0));
        } else if (attack_result == -1) {
            mDoAud_seStart(JA_SE_PLAYSPOT_WRONG, &mNPCPos);
        }

        if (dead > 0) {
            mpSquidIcon[dead + -1]->offBeforeTex();
        }
        if (score > 0) {
            mpSquidIcon[score + 2]->offBeforeTex();
        }
    }
#if VERSION == VERSION_DEMO
    s32 near_enemy = mSeaFightGame.getNearEnemy(mLastFirePosX, mLastFirePosY);
    JUTReport(0x1E0, 0x17C, "NEAR ENEMY");
    JUTReport(0x1EA, 0x190, "%d\n", near_enemy);
#endif
    set_mtx();
    return TRUE;
}

/* 00001250-000013C4       .text CursorMove__11daMgBoard_cFv */
void daMgBoard_c::CursorMove() {
    /* Nonmatching */
    s8 start_pos_x;
    s8 start_pos_y;

    start_pos_x = mBoardPosX;
    start_pos_y = mBoardPosY;
    mStickControl.checkTrigger();
    if (mStickControl.checkLeftTrigger() != 0) {
        mBoardPosX--;
    } else if (mStickControl.checkRightTrigger() != 0) {
        mBoardPosX++;
    }
    if (mStickControl.checkUpTrigger() != 0) {
        mBoardPosY++;
    } else if (mStickControl.checkDownTrigger() != 0) {
        mBoardPosY--;
    }
    if (mBoardPosX > 7) {
        mBoardPosX = 7;
    }
    if (mBoardPosX < 0) {
        mBoardPosX = 0;
    }
    if (mBoardPosY > 7) {
        mBoardPosY = 7;
    }
    if (mBoardPosY < 0) {
        mBoardPosY = 0;
    }

    if ((mBoardPosX != start_pos_x) || (mBoardPosY != start_pos_y)) {
        mDoAud_seStart(JA_SE_PLAYSPOT_CURSOR);
    }
}

/* 000013C4-000014C8       .text daMgBoard_Create__FPv */
static cPhs_State daMgBoard_Create(void* i_this) {
    return ((daMgBoard_c*)i_this)->_create();
}

/* 000014C8-00001518       .text daMgBoard_Delete__FPv */
static BOOL daMgBoard_Delete(void* i_this) {
    daMgBoard_c* actor = (daMgBoard_c*)i_this;
    dComIfG_resDelete(&actor->mPhase, daMgBoard_c::m_arcname);
    mDoAud_seDeleteObject(&actor->mNPCPos);
    return TRUE;
}

/* 00001518-0000153C       .text daMgBoard_Draw__FPv */
static BOOL daMgBoard_Draw(void* i_this) {
    return ((daMgBoard_c*)i_this)->_draw();
}

/* 0000153C-00001850       .text _draw__11daMgBoard_cFv */
bool daMgBoard_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpBoardModel, &tevStr);
    mDoExt_modelUpdateDL(mpBoardModel);
    if (mbDraw == 0) {
        return true;
    } else {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpCursorModel, &tevStr);
        dComIfGd_setListMaskOff();
        mDoExt_modelUpdateDL(mpCursorModel);
        dComIfGd_setList();
        dComIfGd_setListMaskOff();

        for (int i = 0; i < mHitModelCount; ++i) {
            g_env_light.setLightTevColorType(mpHitModel[i], &tevStr);
            mDoExt_modelUpdateDL(mpHitModel[i]);
        }

        for (int i = 0; i < mMissModelCount; ++i) {
            g_env_light.setLightTevColorType(mpMissModel[i], &tevStr);
            mDoExt_modelUpdateDL(mpMissModel[i]);
        }

        dComIfGd_setList();

        for (int i = 0; i < 3; ++i) {
            u8 ship_max_health = mSeaFightGame.getMaxHP(i);
            u8 ship_cur_health = mSeaFightGame.getCurHP(i); // unused but inline is in the debug maps
            u8 num_bullet = mSeaFightGame.checkRestBullet();
            u8 num_alive_ships = mSeaFightGame.getRest();
            bool is_game_finished = 0;
            if ((!num_alive_ships | !num_bullet) != 0) {
                is_game_finished = 1;
            }
            if (is_game_finished) {
                J3DModel* model;
                switch (ship_max_health) {
                    case 2:
                        model = mpShip2Model[0];
                        break;
                    case 3:
                        model = mpShip3Model[0];
                        break;
                    case 4:
                        model = mpShip4Model[0];
                        break;
                    default:
                        model = NULL;
                        break;
                }
                if (model != NULL) {
                    g_env_light.setLightTevColorType(model, &tevStr);
                    dComIfGd_setListMaskOff();
                    mDoExt_modelUpdateDL(model);
                    dComIfGd_setList();
                }
            }
        }

        dComIfGd_set2DOpa(mpMinigameDList);
        dComIfGd_set2DOpa(mpNumber0);
        dComIfGd_set2DOpa(mpNumber1);

        for (int i = 0; i < (int)ARRAY_SIZE(mpBombIcons); ++i) {
            dComIfGd_set2DOpa(mpBombIcons[i]);
        }

        for (int i = 0; i < (int)ARRAY_SIZE(mpSquidIcon); ++i) {
            dComIfGd_set2DOpa(mpSquidIcon[i]);
        }
    }
    return true;
}

/* 00001850-00001874       .text daMgBoard_Execute__FPv */
static BOOL daMgBoard_Execute(void* i_this) {
    return ((daMgBoard_c*)i_this)->_execute();
}

/* 00001874-0000187C       .text daMgBoard_IsDelete__FPv */
static BOOL daMgBoard_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daMgBoardMethodTable = {
    (process_method_func)daMgBoard_Create,
    (process_method_func)daMgBoard_Delete,
    (process_method_func)daMgBoard_Execute,
    (process_method_func)daMgBoard_IsDelete,
    (process_method_func)daMgBoard_Draw,
};

actor_process_profile_definition g_profile_MGBOARD = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MGBOARD_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMgBoard_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_MGBOARD_e,
    /* Actor SubMtd */ &daMgBoardMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
