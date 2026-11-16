/**
 * d_a_mgameboard.cpp
 * Squid-Hunt/"Sploosh Kaboom" Minigame
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mgameboard.h"
#include "d/d_2dnumber.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Kaisen_e.h"

char daMgBoard_c::m_arcname[9] = "";
u8 daMgBoard_c::m_bullet_num = 24;

cXyz daMgBoard_c::m_cur_table[8][8] = {
    {cXyz(-87.5f, -87.5f, 0.0f), cXyz(-62.5f, -87.5f, 0.0f), cXyz(-37.5f, -87.5f, 0.0f), cXyz(-12.5f, -87.5f, 0.0f), cXyz(12.5f, -87.5f, 0.0f), cXyz(37.5f, -87.5f, 0.0f), cXyz(62.5f, -87.5f, 0.0f), cXyz(87.5f, -87.5f, 0.0f)},
    {cXyz(-87.5f, -62.5f, 0.0f), cXyz(-62.5f, -62.5f, 0.0f), cXyz(-37.5f, -62.5f, 0.0f), cXyz(-12.5f, -62.5f, 0.0f), cXyz(12.5f, -62.5f, 0.0f), cXyz(37.5f, -62.5f, 0.0f), cXyz(62.5f, -62.5f, 0.0f), cXyz(87.5f, -62.5f, 0.0f)},
    {cXyz(-87.5f, -37.5f, 0.0f), cXyz(-62.5f, -37.5f, 0.0f), cXyz(-37.5f, -37.5f, 0.0f), cXyz(-12.5f, -37.5f, 0.0f), cXyz(12.5f, -37.5f, 0.0f), cXyz(37.5f, -37.5f, 0.0f), cXyz(62.5f, -37.5f, 0.0f), cXyz(87.5f, -37.5f, 0.0f)},
    {cXyz(-87.5f, -12.5f, 0.0f), cXyz(-62.5f, -12.5f, 0.0f), cXyz(-37.5f, -12.5f, 0.0f), cXyz(-12.5f, -12.5f, 0.0f), cXyz(12.5f, -12.5f, 0.0f), cXyz(37.5f, -12.5f, 0.0f), cXyz(62.5f, -12.5f, 0.0f), cXyz(87.5f, -12.5f, 0.0f)},
    {cXyz(-87.5f, 12.5f, 0.0f), cXyz(-62.5f, 12.5f, 0.0f), cXyz(-37.5f, 12.5f, 0.0f), cXyz(-12.5f, 12.5f, 0.0f), cXyz(12.5f, 12.5f, 0.0f), cXyz(37.5f, 12.5f, 0.0f), cXyz(62.5f, 12.5f, 0.0f), cXyz(87.5f, 12.5f, 0.0f)},
    {cXyz(-87.5f, 37.5f, 0.0f), cXyz(-62.5f, 37.5f, 0.0f), cXyz(-37.5f, 37.5f, 0.0f), cXyz(-12.5f, 37.5f, 0.0f), cXyz(12.5f, 37.5f, 0.0f), cXyz(37.5f, 37.5f, 0.0f), cXyz(62.5f, 37.5f, 0.0f), cXyz(87.5f, 37.5f, 0.0f)},
    {cXyz(-87.5f, 62.5f, 0.0f), cXyz(-62.5f, 62.5f, 0.0f), cXyz(-37.5f, 62.5f, 0.0f), cXyz(-12.5f, 62.5f, 0.0f), cXyz(12.5f, 62.5f, 0.0f), cXyz(37.5f, 62.5f, 0.0f), cXyz(62.5f, 62.5f, 0.0f), cXyz(87.5f, 62.5f, 0.0f)},
    {cXyz(-87.5f, 87.5f, 0.0f), cXyz(-62.5f, 87.5f, 0.0f), cXyz(-37.5f, 87.5f, 0.0f), cXyz(-12.5f, 87.5f, 0.0f), cXyz(12.5f, 87.5f, 0.0f), cXyz(37.5f, 87.5f, 0.0f), cXyz(62.5f, 87.5f, 0.0f), cXyz(87.5f, 87.5f, 0.0f)},
};

cXyz daMgBoard_c::m_sink_table[3] = {
    cXyz(162.5f, 87.5f, 0.0f), cXyz(162.5f, 62.5f, 0.0f), cXyz(162.5f, 37.5f, 0.0f),
};

cXyz daMgBoard_c::m_bullet_table[24] = {
    cXyz(-150.0f, 90.0f, 0.0f), cXyz(-150.0f, 70.0f, 0.0f), cXyz(-150.0f, 50.0f, 0.0f), cXyz(-150.0f, 30.0f, 0.0f), cXyz(-150.0f, 10.0f, 0.0f), cXyz(-150.0f, -10.0f, 0.0f), cXyz(-150.0f, -30.0f, 0.0f), cXyz(-150.0f, -50.0f, 0.0f),
    cXyz(-170.0f, 90.0f, 0.0f), cXyz(-170.0f, 70.0f, 0.0f), cXyz(-170.0f, 50.0f, 0.0f), cXyz(-170.0f, 30.0f, 0.0f), cXyz(-170.0f, 10.0f, 0.0f), cXyz(-170.0f, -10.0f, 0.0f), cXyz(-170.0f, -30.0f, 0.0f), cXyz(-170.0f, -50.0f, 0.0f),
    cXyz(-190.0f, 90.0f, 0.0f), cXyz(-190.0f, 70.0f, 0.0f), cXyz(-190.0f, 50.0f, 0.0f), cXyz(-190.0f, 30.0f, 0.0f), cXyz(-190.0f, 10.0f, 0.0f), cXyz(-190.0f, -10.0f, 0.0f), cXyz(-190.0f, -30.0f, 0.0f), cXyz(-190.0f, -50.0f, 0.0f),
};

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daMgBoard_c*)i_this)->CreateHeap();
}

/* 0000010C-000007BC       .text CreateHeap__11daMgBoard_cFv */
BOOL daMgBoard_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AKBOD_e);
    JUT_ASSERT(0x133, modelData != NULL);
    mpBoardModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpBoardModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AKCSR_e);
    JUT_ASSERT(0x143, modelData != NULL);
    mpCursorModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpCursorModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AKATR_e);
    JUT_ASSERT(0x153, modelData != NULL);
    for (int i = 0; i < ARRAY_SSIZE(mpHitModel); i++) {
        mpHitModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpHitModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AKHZR_e);
    JUT_ASSERT(0x165, modelData != NULL);
    for (int i = 0; i < ARRAY_SSIZE(mpMissModel); i++) {
        mpMissModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpMissModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AK2SH_e);
    JUT_ASSERT(0x177, modelData != NULL);
    for (int i = 0; i < ARRAY_SSIZE(mpShip2Model); i++) {
        mpShip2Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip2Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AK3SH_e);
    JUT_ASSERT(0x189, modelData != NULL);
    for (int i = 0; i < ARRAY_SSIZE(mpShip3Model); i++) {
        mpShip3Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip3Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BDL_AK4SH_e);
    JUT_ASSERT(0x19B, modelData != NULL);
    for (int i = 0; i < ARRAY_SSIZE(mpShip4Model); i++) {
        mpShip4Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip4Model[i] == NULL) {
            return FALSE;
        }
    }

    mpNumber0 = new dDlst_2DNumber_c();
    if (mpNumber0 == NULL) {
        return FALSE;
    }
    mpNumber0->init(4, 470, 75, 24, 24, 0);

    mpNumber1 = new dDlst_2DNumber_c();
    if (mpNumber1 == NULL) {
        return FALSE;
    }
    mpNumber1->init(4, 100, 80, 24, 24, 0);

    for (int i = 0; i < ARRAY_SSIZE(mpSquidIcon); i++) {
        mpSquidIcon[i] = new dDlst_2DObject_c();
        if (mpSquidIcon[i] == NULL) {
            return FALSE;
        }
        mpSquidIcon[i]->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_KAISEN_IKA_01_e), (ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_KAISEN_IKA_02_e));
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            int idx = j + i * 8;
            mpBombIcon[idx] = new dDlst_2DObject_c();
            if (mpBombIcon[idx] == NULL) {
                return FALSE;
            }
            mpBombIcon[idx]->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_GAME_BOMB_01_e), (ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_GAME_BOMB_02_e));
        }
    }

    mpMinigameDList = new dDlst_2DMinigame_c();
    if (mpMinigameDList == NULL) {
        return FALSE;
    }
    mpMinigameDList->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_GAME_BEST_RECORD_e), (ResTIMG*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_KAISEN_E_BTI_GAME_PAPER_e));
    set_2dposition();
    return TRUE;
}

/* 00000804-00000904       .text set_2dposition__11daMgBoard_cFv */
void daMgBoard_c::set_2dposition() {
    f32 pos_y = 115.0f;
    for (int i = 0; i < 3; i++) {
        mpSquidIcon[i]->setPosition(523.0f, pos_y);
        pos_y += 47.0f;
    }

    f32 x = 95.0f;
    f32 y = 120.0f;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            mpBombIcon[j + i * 8]->setPosition(x, y);
            y += 35.0f;
        }
        x -= 35.0f;
        y = 120.0f;
    }

    mpMinigameDList->setTitlePos(282.0f, 70.0f);
    mpMinigameDList->setScorePos(440.0f, 60.0f);
    mpMinigameDList->setTitleAlpha(0xFF);
    f32 alpha = 80.5f;
    mpMinigameDList->setScoreAlpha(alpha);
}

/* 00000904-000009E0       .text CreateInit__11daMgBoard_cFv */
void daMgBoard_c::CreateInit() {
    fopAcM_SetMtx(this, mpBoardModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -600.0f, -300.0f, -500.0f, 600.0f, 300.0f, 100.0f);
    mState = 0;
    mMinigameStartIdx = dComIfGp_evmng_getEventIdx("MINIGAME_START", 0xFF);
    mMinigameEndIdx = dComIfGp_evmng_getEventIdx("MINIGAME_END", 0xFF);
    mStickControl.setWaitParm(5, 2, 3, 2, 0.9f, 0.5f, 0, 0x800);
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
    fopAc_ac_c* npc_p = fopAcM_SearchByName(fpcNm_NPC_KG1_e);
    if (npc_p != NULL) {
        mNPCPos = npc_p->current.pos;
    }
    set_mtx();
    for (int i = 0; i < ARRAY_SSIZE(mpSquidIcon); i++) {
        mpSquidIcon[i]->onBeforeTex();
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            mpBombIcon[i * 8 + j]->onBeforeTex();
        }
    }
}

/* 00000AE8-00000DEC       .text set_mtx__11daMgBoard_cFv */
inline void daMgBoard_c::set_mtx() {
    J3DModel* model = mpBoardModel;
    int ship_num;
    u8 y;
    u8 x;
    int i;
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    model = mpCursorModel;
    mDoMtx_stack_c::transS(current.pos.x + m_cur_table[mBoardPosY][mBoardPosX].x, current.pos.y + m_cur_table[mBoardPosY][mBoardPosX].y, current.pos.z + m_cur_table[mBoardPosY][mBoardPosX].z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    mMissModelCount = 0;
    mHitModelCount = 0;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            int cell = mSeaFightGame.mGrid[y][x];
            model = NULL;
            if (cell == 3) {
                model = mpHitModel[mHitModelCount];
                mHitModelCount++;
            } else if (cell == 1) {
                model = mpMissModel[mMissModelCount];
                mMissModelCount++;
            }
            if (model != NULL) {
                mDoMtx_stack_c::transS(current.pos.x + m_cur_table[x][y].x, current.pos.y + m_cur_table[x][y].y, current.pos.z + m_cur_table[x][y].z);
                mDoMtx_stack_c::YrotM(current.angle.y);
                model->setBaseTRMtx(mDoMtx_stack_c::get());
            }
        }
    }

    ship_num = mSeaFightGame.mAliveShipNum;
    for (i = 0; i < ship_num; i++) {
        switch (mSeaFightGame.mShips[i].field_0x8) {
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
            u8 bb = mSeaFightGame.mShips[i].field_0xb;
            u8 c = mSeaFightGame.mShips[i].field_0xc;
            mDoMtx_stack_c::transS(current.pos.x + m_cur_table[c][bb].x, current.pos.y + m_cur_table[c][bb].y, current.pos.z + m_cur_table[c][bb].z);
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

static f32 dummy_0_8(f32 x) {
    return x * 0.8f;
}

static void dummy_0_75(cXyz* p) {
    cXyz tmp(0.75f, -0.75f, 0.0f);
    *p = tmp;
}

/* 00000E28-00000FD8       .text _execute__11daMgBoard_cFv */
bool daMgBoard_c::_execute() {
    u8 reg = dComIfGs_getEventReg(0xBEFF);
    u8 score = mSeaFightGame.mScore;
    mpNumber0->setValue(reg);
    mpNumber1->setValue(score);
    set_2dposition();
    if (mbForceEnd) {
        execEndGame();
        mbEndGame = false;
        mbForceEnd = false;
    }

    switch (mState) {
    case 0:
        mState = 1;
        mbStartGame = false;
        break;
    case 1:
        if (mbStartGame) {
            mState = 2;
        }
        break;
    case 2:
        mState = 3;
    case 3:
        execGameMain();
        if (mbEndGame) {
            mTimer = 30;
            mState = 4;
        }
        break;
    case 4:
        if (cLib_calcTimer(&mTimer) == 0) {
            mState = 0;
            if (mSeaFightGame.mAliveShipNum != 0) {
                mDoAud_seStart(0x8AC, &mNPCPos);
            } else {
                mDoAud_seStart(0x8AB, &mNPCPos);
            }
        }
        break;
    }
    return true;
}

/* 00000FD8-00001040       .text execGameMain__11daMgBoard_cFv */
bool daMgBoard_c::execGameMain() {
    MinigameMain();
    bool end = false;
    if (mSeaFightGame.mAliveShipNum == 0 || mSeaFightGame.mBulletNum == 0) {
        end = true;
    }
    if (end) {
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
    if (mDoAud_checkSePlaying(0x8A8)) {
        return TRUE;
    }

    CursorMove();
    int bullet_num = mSeaFightGame.mBulletNum;
    int prev_alive = mSeaFightGame.mAliveShipNum;
    if (CPad_CHECK_TRIG_A(0) && bullet_num > 0) {
        int ret = mSeaFightGame.attack(mBoardPosX, mBoardPosY);
        int alive = mSeaFightGame.mAliveShipNum;
        int dead = mSeaFightGame.mDeadShipNum;
        int score = mSeaFightGame.mScore;
        mLastFirePosX = (s8)mBoardPosX;
        mLastFirePosY = (s8)mBoardPosY;
        if (ret >= 0) {
            mDoAud_seStart(0x69A2, &mNPCPos);
            if (prev_alive != alive && alive != 0) {
                mDoAud_seStart(0x8AA, &mNPCPos);
            }
            dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        } else if (ret == -1) {
            mDoAud_seStart(0x69A3, &mNPCPos);
        }
        if (dead > 0) {
            mpSquidIcon[dead - 1]->offBeforeTex();
        }
        if (score > 0) {
            mpBombIcon[score - 1]->offBeforeTex();
        }
    }
    set_mtx();
    return TRUE;
}

/* 00001250-000013C4       .text CursorMove__11daMgBoard_cFv */
void daMgBoard_c::CursorMove() {
    s8 prev_x = mBoardPosX;
    s8 prev_y = mBoardPosY;
    mStickControl.checkTrigger();
    if (mStickControl.checkLeftTrigger()) {
        mBoardPosX--;
    } else if (mStickControl.checkRightTrigger()) {
        mBoardPosX++;
    }
    if (mStickControl.checkUpTrigger()) {
        mBoardPosY++;
    } else if (mStickControl.checkDownTrigger()) {
        mBoardPosY--;
    }
    if ((s8)mBoardPosX > 7) {
        mBoardPosX = 7;
    }
    if ((s8)mBoardPosX < 0) {
        mBoardPosX = 0;
    }
    if ((s8)mBoardPosY > 7) {
        mBoardPosY = 7;
    }
    if ((s8)mBoardPosY < 0) {
        mBoardPosY = 0;
    }
    if ((s8)mBoardPosX != (s8)prev_x || (s8)mBoardPosY != (s8)prev_y) {
        mDoAud_seStart(0x8A9);
    }
}

inline cPhs_State daMgBoard_c::_create() {
    fopAcM_ct(this, daMgBoard_c);
    strcpy(m_arcname, "Kaisen_e");
    cPhs_State state = dComIfG_resLoad(&mPhase, m_arcname);
    if (state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x4E000)) {
            state = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }
    return state;
}

/* 000013C4-000014C8       .text daMgBoard_Create__FPv */
static cPhs_State daMgBoard_Create(void* i_this) {
    return ((daMgBoard_c*)i_this)->_create();
}

inline bool daMgBoard_c::_delete() {
    dComIfG_resDelete(&mPhase, m_arcname);
    mDoAud_seDeleteObject(&mNPCPos);
    return true;
}

/* 000014C8-00001518       .text daMgBoard_Delete__FPv */
static BOOL daMgBoard_Delete(void* i_this) {
    return ((daMgBoard_c*)i_this)->_delete();
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
    if (!mbDraw) {
        return true;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpCursorModel, &tevStr);
    dComIfGd_setListMaskOff();
    mDoExt_modelUpdateDL(mpCursorModel);
    dComIfGd_setList();

    dComIfGd_setListMaskOff();
    for (int i = 0; i < mHitModelCount; i++) {
        g_env_light.setLightTevColorType(mpHitModel[i], &tevStr);
        mDoExt_modelUpdateDL(mpHitModel[i]);
    }
    for (int i = 0; i < mMissModelCount; i++) {
        g_env_light.setLightTevColorType(mpMissModel[i], &tevStr);
        mDoExt_modelUpdateDL(mpMissModel[i]);
    }
    dComIfGd_setList();

    for (int i = 0; i < 3; i++) {
        u8 size = mSeaFightGame.mShips[i].field_0x8;
        bool end = false;
        if ((mSeaFightGame.mBulletNum == 0) | (mSeaFightGame.mAliveShipNum == 0)) {
            end = true;
        }
        if (end) {
            J3DModel* ship_model;
            switch (size) {
            case 2:
                ship_model = mpShip2Model[0];
                break;
            case 3:
                ship_model = mpShip3Model[0];
                break;
            case 4:
                ship_model = mpShip4Model[0];
                break;
            default:
                ship_model = NULL;
                break;
            }
            if (ship_model != NULL) {
                g_env_light.setLightTevColorType(ship_model, &tevStr);
                dComIfGd_setListMaskOff();
                mDoExt_modelUpdateDL(ship_model);
                dComIfGd_setList();
            }
        }
    }

    dComIfGd_set2DOpa(mpMinigameDList);
    dComIfGd_set2DOpa(mpNumber0);
    dComIfGd_set2DOpa(mpNumber1);
    for (int i = 0; i < 24; i++) {
        dComIfGd_set2DOpa(mpBombIcon[i]);
    }
    for (int i = 0; i < ARRAY_SSIZE(mpSquidIcon); i++) {
        dComIfGd_set2DOpa(mpSquidIcon[i]);
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
