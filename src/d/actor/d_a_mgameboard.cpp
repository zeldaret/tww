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

char daMgBoard_c::m_arcname[] = "mgameboard";

/* 0000010C-000007BC       .text CreateHeap__11daMgBoard_cFv */
BOOL daMgBoard_c::CreateHeap() {
    /* Nonmatching */
    /*
           6] CreateHeap__11daMgBoard_cFv (func,global) found in d_a_mgameboard.o 
>>> SYMBOL NOT FOUND: _savegpr_16
        7] dComIfG_getObjectRes__FPCci (func,weak) found in d_a_mgameboard.o 
>>> SYMBOL NOT FOUND: getObjectRes__14dRes_control_cFPCcl
>>> SYMBOL NOT FOUND: getSDevice__12JUTAssertionFv
>>> SYMBOL NOT FOUND: showAssert__12JUTAssertionFUlPCciPCc
>>> SYMBOL NOT FOUND: mDoExt_J3DModel__create__FP12J3DModelDataUlUl
>>> SYMBOL NOT FOUND: __nw__FUl
>>> SYMBOL NOT FOUND: __ct__16dDlst_2DNumber_cFv
>>> SYMBOL NOT FOUND: init__16dDlst_2DNumber_cFissssUc
        7] __ct__16dDlst_2DObject_cFv (func,weak) found in d_a_mgameboard.o 
         8] __ct__12dDlst_base_cFv (func,weak) found in d_a_mgameboard.o 
          9] __vt__12dDlst_base_c (object,weak) found in d_a_mgameboard.o 
           10] draw__12dDlst_base_cFv (func,weak) found in d_a_mgameboard.o 
           10] __dt__12dDlst_base_cFv (func,weak) found in d_a_mgameboard.o 
>>> SYMBOL NOT FOUND: __vt__16dDlst_2DObject_c
>>> SYMBOL NOT FOUND: init__16dDlst_2DObject_cFP7ResTIMGP7ResTIMG
        7] __ct__18dDlst_2DMinigame_cFv (func,weak) found in d_a_mgameboard.o 
>>> SYMBOL NOT FOUND: __vt__18dDlst_2DMinigame_c
>>> SYMBOL NOT FOUND: init__18dDlst_2DMinigame_cFP7ResTIMGP7ResTIMG
>>> SYMBOL NOT FOUND: _restgpr_16
>>> SYMBOL NOT FOUND: fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl
    */
    J3DModelData* modelData;
    J3DModel* pJVar3;
    BOOL uVar4;
    dDlst_2DNumber_c* pdVar5;
    dDlst_2DObject_c* puVar6;
    ResTIMG* pRVar7;
    ResTIMG* pRVar8;
    dDlst_2DObject_c* pdVar9;
    dDlst_2DMinigame_c* pdVar10;

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 8);
    JUT_ASSERT(0x133, modelData != NULL);

    pJVar3 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    mpBoardModel = pJVar3;
    if (mpBoardModel == NULL) {
        uVar4 = FALSE;
    } else {

        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 9);
        JUT_ASSERT(0x143, modelData != NULL);

        pJVar3 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        mpCursorModel = pJVar3;
        if (this->mpCursorModel == NULL) {
            uVar4 = FALSE;
        } else {
            modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 7);
            JUT_ASSERT(0x153, modelData != NULL);

            for (int i = 0; i < (int)ARRAY_SIZE(mpHitModel); ++i) {
                pJVar3 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
                mpHitModel[i] = pJVar3;
                if (mpHitModel[i] == NULL) {
                    return TRUE;
                }
            }
            modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 10);
            JUT_ASSERT(0x165, modelData != NULL);

            for (int i = 0; i < (int)ARRAY_SIZE(mpMissModel); ++i) {
                mpMissModel[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);;
                if (mpMissModel[i] == NULL) {
                    return FALSE;
                }
            }

            modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 4);
            JUT_ASSERT(0x177, modelData != NULL);

            for (int i = 0; i < (int)ARRAY_SIZE(mpShip2Model); ++i) {
                mpShip2Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);;
                if (mpShip2Model[i] == NULL) {
                    return FALSE;
                }
            }

            modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 5);
            JUT_ASSERT(0x189, modelData != NULL);

            for (int i = 0; i < (int)ARRAY_SIZE(mpShip3Model); ++i) {
                mpShip3Model[i] =  mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);;
                if (mpShip3Model[i] == NULL) {
                    return FALSE;
                }
            }

            modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 6);
            JUT_ASSERT(0x19b, modelData != NULL);

            for (int i = 0; i < (int)ARRAY_SIZE(mpShip4Model); ++i) {
                mpShip4Model[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);;
                if (mpShip4Model[i] == NULL) {
                    return FALSE;
                }
            }

            pdVar5 = new dDlst_2DNumber_c(); // maybe split allocation and construction?

            mpNumber0 = pdVar5;
            if (mpNumber0 == NULL) {
                uVar4 = 0;
            } else {
                mpNumber0->init(4, 0x1d6, 0x4b, 0x18, 0x18, 0);
                pdVar5 = new dDlst_2DNumber_c(); // maybe split allocation and construction?
                mpNumber1 = pdVar5;
                if (mpNumber1 == NULL) {
                    uVar4 = 0;
                } else {
                    mpNumber1->init(4, 100, 0x50, 0x18, 0x18, 0);
                    for (int i = 0; i < (int)ARRAY_SIZE(mpSquidIcon); ++i) {
                        puVar6 = new dDlst_2DObject_c(); // maybe split allocation and construction?
                        mpSquidIcon[i] = puVar6;
                        if (mpSquidIcon[i] == NULL) {
                            return FALSE;
                        }

                        pRVar7 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x13);
                        pRVar8 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x12);
                        mpSquidIcon[i]->init(pRVar8, pRVar7);
                    }

                    for (int i = 0; i < (int)ARRAY_SIZE(mpBombIcons); ++i) // ghidra implies this could be a double array?
                    {
                        pdVar9 = new dDlst_2DObject_c(); // maybe split allocation and construction?
                        mpBombIcons[i] = pdVar9;
                        if (mpBombIcons[i] == NULL) {
                            return FALSE;
                        }
                        pRVar7 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x10);
                        pRVar8 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0xF);
                        mpBombIcons[i]->init(pRVar8, pRVar7);
                    }

                    pdVar10 = new dDlst_2DMinigame_c(); // maybe split allocation and construction?

                    mpMinigameDList = pdVar10;
                    if (mpMinigameDList == NULL) {
                        uVar4 = 0;
                    } else {
                        pRVar7 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0x11);
                        pRVar8 = (ResTIMG*)dComIfG_getObjectRes(m_arcname, 0xE);
                        mpMinigameDList->init(pRVar8, pRVar7);
                        set_2dposition();
                        uVar4 = TRUE;
                    }
                }
            }
        }
    }
    return uVar4;
}

/* 00000804-00000904       .text set_2dposition__11daMgBoard_cFv */
void daMgBoard_c::set_2dposition() {
    /* Nonmatching */
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
void daMgBoard_c::execGameMain() {
    /* Nonmatching */
}

/* 00001040-00001060       .text execEndGame__11daMgBoard_cFv */
void daMgBoard_c::execEndGame() {
    /* Nonmatching */
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
static BOOL daMgBoard_Delete(void*) {
    /* Nonmatching */
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
