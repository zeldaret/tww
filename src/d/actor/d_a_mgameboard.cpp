/**
 * d_a_mgameboard.cpp
 * Squid-Hunt/"Sploosh Kaboom" Minigame
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mgameboard.h"
#include "d/d_2dnumber.h"

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daMgBoard_c*)i_this)->CreateHeap();
}

char daMgBoard_c::m_arcname[9] = {};

/* 0000010C-000007BC       .text CreateHeap__11daMgBoard_cFv */
BOOL daMgBoard_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 8);
    JUT_ASSERT(0x133, modelData != NULL);

    mpBoardModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpBoardModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 9);
    JUT_ASSERT(0x143, modelData != NULL);

    mpCursorModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpCursorModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 7);
    JUT_ASSERT(0x153, modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpHitModel); ++i) {
        mpHitModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpHitModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 10);
    JUT_ASSERT(0x165, modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpMissModel); ++i) {
        mpMissModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpMissModel[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 4);
    JUT_ASSERT(0x177, modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpShip2Model); ++i) {
        mpShip2Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip2Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 5);
    JUT_ASSERT(0x189, modelData != NULL);

    for (int i = 0; i < (int)ARRAY_SIZE(mpShip3Model); ++i) {
        mpShip3Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mpShip3Model[i] == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 6);
    JUT_ASSERT(0x19b, modelData != NULL);

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

        mpSquidIcon[i]->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x12), (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x13));
    }

    const int rows = 3;
    const int cols = 8;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const int idx = j + i * cols;
            mpBombIcons[idx] = new dDlst_2DObject_c();

            if (!mpBombIcons[idx])
                return FALSE;

            mpBombIcons[idx]->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, 0xF), (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x10));
        }
    }

    mpMinigameDList = new dDlst_2DMinigame_c();
    if (mpMinigameDList == NULL) {
        return FALSE;
    }

    mpMinigameDList->init((ResTIMG*)dComIfG_getObjectRes(m_arcname, 0xE), (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x11));
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
    /* Nonmatching */
}

/* 000009E0-00000AE8       .text MiniGameInit__11daMgBoard_cFv */
void daMgBoard_c::MiniGameInit() {
    /* Nonmatching */
}

/* 00000AE8-00000DEC       .text set_mtx__11daMgBoard_cFv */
void daMgBoard_c::set_mtx() {
    /* Nonmatching */
}

/* 00000E28-00000FD8       .text _execute__11daMgBoard_cFv */
bool daMgBoard_c::_execute() {
    /* Nonmatching */
}

/* 00000FD8-00001040       .text execGameMain__11daMgBoard_cFv */
bool daMgBoard_c::execGameMain() {
    MinigameMain();
    bool is_end_game = false;
    if (mSeaFightGame.mAliveShipNum == 0 || mSeaFightGame.mBulletNum == 0) {
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
void daMgBoard_c::MinigameMain() {
    /* Nonmatching */
}

/* 00001250-000013C4       .text CursorMove__11daMgBoard_cFv */
void daMgBoard_c::CursorMove() {
    /* Nonmatching */
}

/* 000013C4-000014C8       .text daMgBoard_Create__FPv */
static cPhs_State daMgBoard_Create(void*) {
    /* Nonmatching */
}

/* 000014C8-00001518       .text daMgBoard_Delete__FPv */
static BOOL daMgBoard_Delete(daMgBoard_c* i_this) {
    dComIfG_resDelete(&i_this->mPhase, daMgBoard_c::m_arcname);
    mDoAud_seDeleteObject(&i_this->mNPCPos);
    return TRUE;
}

/* 00001518-0000153C       .text daMgBoard_Draw__FPv */
static BOOL daMgBoard_Draw(void* i_this) {
    return ((daMgBoard_c*)i_this)->_draw();
}

/* 0000153C-00001850       .text _draw__11daMgBoard_cFv */
bool daMgBoard_c::_draw() {
    /* Nonmatching */
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
