/**
 * d_minigame_starter.cpp
 * Boating Course - "3-2-1 GO!" text
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_minigame_starter.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "d/d_meter.h"
#include "stdio.h"

static s16 cdFrame0 = 7;
static s16 cdFrame1 = 3;
static s16 tmFrame = 5;
static s16 cdFrame2 = 15;
static s16 cdFrame3 = 5;
static s16 cdFrame4 = 7;
static s16 cdFrame5 = 3;
static s16 cdFrame6 = 4;
static s16 cdFrame7 = 4;
static s16 cdFrame8 = 6;

#if VERSION > VERSION_JPN
static s16 dMinigame_Starter_tex_number = 3;
#endif

/* 80205FE8-80206124       .text _create__19dMinigame_Starter_cFv */
// NONMATCHING - missing b
int dMinigame_Starter_c::_create() {
    if (dComIfG_resLoad(&mPhase, "Mgst") == cPhs_COMPLEATE_e) {
        dRes_info_c* resInfo = dComIfG_getObjectResInfo("Mgst");
        JUT_ASSERT(VERSION_SELECT(80, 80, 86, 86), resInfo != NULL);

        mHeap = mDoExt_createSolidHeapFromGameToCurrent(VERSION_SELECT(0x13E0, 0x13E0, 0x14C0, 0x1AC0), 0x20);
        if (mHeap != NULL) {
            mStarterScrn = new dDlst_StarterScrnDraw_c();

#if VERSION == VERSION_PAL
            char resname[32];
            sprintf(resname, "ship_race1_%d.blo", dComIfGs_getPalLanguage());
            mStarterScrn->setScreen(resname, resInfo->getArchive());
#else
            mStarterScrn->setScreen("ship_race1.blo", resInfo->getArchive());
#endif
            mDoExt_restoreCurrentHeap();
            mDoExt_adjustSolidHeap(mHeap);
        } else {
            return cPhs_ERROR_e;
        }

        mStatus = 0;
        mTimer = 0;
        field_0x10e = 3;
    }

    return cPhs_COMPLEATE_e;
}

/* 80206124-8020629C       .text _execute__19dMinigame_Starter_cFv */
// NONMATCHING - instruction ordering
int dMinigame_Starter_c::_execute() {
    int var_r30 = (cdFrame0 + cdFrame1 + tmFrame + cdFrame2 + cdFrame3) - 30;
    int var_r29 = (cdFrame4 + cdFrame5 + cdFrame6 + cdFrame7 + cdFrame8) - 23;

    if (!mStatus) {
        return 0;
    }

    int var_r31 = var_r30 * 3;

    if (mTimer < (var_r31 + var_r29) + 137) {
        mTimer++;
        if (mTimer >= (var_r31 + var_r29) + 89) {
            mStatus = 2;
        }
    } else {
        mStatus = 3;
    }

    if (mTimer <= var_r30 + 30) {
        mStarterScrn->anime1(2);
    }

    if (mTimer >= var_r30 + 28 && mTimer <= (var_r30 * 2) + 57) {
        mStarterScrn->anime1(1);
    }

    if (mTimer >= (var_r30 * 2) + 55 && mTimer <= var_r31 + 84) {
        mStarterScrn->anime1(0);
    }

    if (mTimer >= var_r31 + 84 && mTimer <= (var_r31 + var_r29) + 107) {
        mStarterScrn->anime2();
    }

    return 1;
}

/* 8020629C-802062DC       .text _draw__19dMinigame_Starter_cFv */
int dMinigame_Starter_c::_draw() {
    dComIfGd_set2DOpa(mStarterScrn);
    return 1;
}

/* 802062DC-80206328       .text _delete__19dMinigame_Starter_cFv */
int dMinigame_Starter_c::_delete() {
    if (mHeap != NULL) {
        mDoExt_destroySolidHeap(mHeap);
    }

    dComIfG_resDelete(&mPhase, "Mgst");
    return 1;
}

/* 80206328-8020634C       .text startCheck__19dMinigame_Starter_cFv */
BOOL dMinigame_Starter_c::startCheck() {
    return mStatus == 3 || mStatus == 2;
}

/* 8020634C-80206360       .text deleteCheck__19dMinigame_Starter_cFv */
BOOL dMinigame_Starter_c::deleteCheck() {
    return mStatus == 3;
}

/* 80206360-802064DC       .text setScreen__23dDlst_StarterScrnDraw_cFPCcP10JKRArchive */
void dDlst_StarterScrnDraw_c::setScreen(const char* i_layoutName, JKRArchive* i_archive) {
    mpScrn = new J2DScreen();
    mpScrn->set(i_layoutName, i_archive);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 2) {
        dMinigame_Starter_tex_number = 7;
        for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
            static u32 label_t_fr[] = {
                'gog',
                'goo',
                'goex',
                'got',
                'goe2',
                'goz',
                'goe3',
            };
            fopMsgM_setPaneData(&field_0x008[i], mpScrn, label_t_fr[i]);
        }
    } else if (dComIfGs_getPalLanguage() == 0) {
        dMinigame_Starter_tex_number = 3;
        for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
            static u32 label_t_uk[] = {
                'gog',
                'goo',
                'goex',
            };
            fopMsgM_setPaneData(&field_0x008[i], mpScrn, label_t_uk[i]);
        }
    } else {
        dMinigame_Starter_tex_number = 4;
        for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
            static u32 label_t[] = {
                'gog',
                'goo',
                'goex',
                'goe2',
            };
            fopMsgM_setPaneData(&field_0x008[i], mpScrn, label_t[i]);
        }
    }
#elif VERSION == VERSION_USA
    for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
        static u32 label_t[] = {
            'gog',
            'goo',
            'goex',
        };
        fopMsgM_setPaneData(&field_0x008[i], mpScrn, label_t[i]);
    }
#else
    fopMsgM_setPaneData(&field_0x008[0], mpScrn, 'gog');
    fopMsgM_setPaneData(&field_0x008[1], mpScrn, 'goo');
    fopMsgM_setPaneData(&field_0x008[2], mpScrn, 'goex');
#endif

    fopMsgM_setPaneData(&field_0x190, mpScrn, 'dmgo');
    fopMsgM_setPaneData(&field_0x1c8[0], mpScrn, 'go1');
    fopMsgM_setPaneData(&field_0x1c8[1], mpScrn, 'go2');
    fopMsgM_setPaneData(&field_0x1c8[2], mpScrn, 'go3');
    fopMsgM_setPaneData(&field_0x270[0], mpScrn, 'go12');
    fopMsgM_setPaneData(&field_0x270[1], mpScrn, 'go22');
    fopMsgM_setPaneData(&field_0x270[2], mpScrn, 'go32');
}

/* 802064DC-80206908       .text anime1__23dDlst_StarterScrnDraw_cFi */
// NONMATCHING - a lot of float math stuff
BOOL dDlst_StarterScrnDraw_c::anime1(int i_no) {
    f32 temp_f1 = -8.0f;
    int rt = 0;

    s16 var_r30 = cdFrame0;
    s16 var_r31 = cdFrame0 + cdFrame1;
    s16 temp_r6 = cdFrame0 + cdFrame1 + tmFrame;
    s16 var_r27 = cdFrame2 + temp_r6;
    s16 temp_r7 = cdFrame3 + var_r27;

    field_0x1c8[i_no].mUserArea++;

    s16 temp_r0 = field_0x1c8[i_no].mUserArea;
    if (temp_r0 <= var_r30) {
        fopMsgM_paneScaleXY(&field_0x270[i_no], ((f32)field_0x1c8[i_no].mUserArea * (f32)field_0x1c8[i_no].mUserArea) / ((f32)var_r31 * (f32)var_r31) * 0.3f + 0.7f);
        fopMsgM_setNowAlpha(&field_0x270[i_no], ((f32)field_0x1c8[i_no].mUserArea * (f32)field_0x1c8[i_no].mUserArea) / ((f32)var_r30 * (f32)var_r30));
    } else if (temp_r0 <= var_r31) {
        f32 var_f31 = ((f32)(temp_r0 - var_r30) * (f32)(temp_r0 - var_r30)) / ((f32)(var_r31 - var_r30) * (f32)(var_r31 - var_r30));
        fopMsgM_paneScaleXY(&field_0x1c8[i_no], var_f31 * 0.3f + 0.7f);
        fopMsgM_setNowAlpha(&field_0x1c8[i_no], var_f31);

        fopMsgM_paneScaleXY(&field_0x270[i_no], ((f32)field_0x1c8[i_no].mUserArea * (f32)field_0x1c8[i_no].mUserArea) / ((f32)var_r31 * (f32)var_r31) * 0.3f + 0.7f);
        fopMsgM_setNowAlpha(&field_0x270[i_no], 1.0f - var_f31);

        if (field_0x1c8[i_no].mUserArea == var_r31) {
            mDoAud_seStart(JA_SE_SGAME_COUNTDOWN, NULL);
        }
    } else if (temp_r6 > temp_r0) {
        if (temp_r0 <= var_r27) {
            if (((temp_r6 - temp_r0) / ((var_r27 - temp_r0) / 4)) % 2)
                temp_f1 *= -1.0f;
            setRotate(&field_0x1c8[i_no], temp_f1);
        } else if (temp_r0 < temp_r7) {
            f32 var_f31 = temp_r0 - var_r27;
            fopMsgM_paneScaleXY(&field_0x1c8[i_no], ((((f32)temp_r0 - var_r27) * ((f32)temp_r0 - var_r27)) / var_f31) * 2.0f + 1.0f);

            f32 temp_f1_2 = ((f32)(field_0x1c8[i_no].mUserArea - var_r27) * (f32)(field_0x1c8[i_no].mUserArea - var_r27)) / var_f31;
            fopMsgM_setNowAlpha(&field_0x1c8[i_no], 1.0f - temp_f1_2);
        } else {
            fopMsgM_paneScaleXY(&field_0x1c8[i_no], 3.0f);
            fopMsgM_setNowAlphaZero(&field_0x1c8[i_no]);
            rt = 1;
        }
    }

    return rt;
}

/* 80206908-80206CB0       .text anime2__23dDlst_StarterScrnDraw_cFv */
// NONMATCHING - a lot of float math stuff
BOOL dDlst_StarterScrnDraw_c::anime2() {
    int rt = 0;

    s16 var_r30 = cdFrame4;
    s16 var_r31 = cdFrame4 + cdFrame5;
    s16 temp_r6 = cdFrame4 + cdFrame5 + cdFrame6;
    s16 var_r27 = cdFrame7 + temp_r6;
    s16 temp_r7 = cdFrame8 + var_r27;

    field_0x008[0].mUserArea++;

    s16 temp_r0 = field_0x008[0].mUserArea;
    if (temp_r0 <= var_r30) {
        f32 var_f31 = ((f32)field_0x008[0].mUserArea * (f32)field_0x008[0].mUserArea) / ((f32)var_r30 * (f32)var_r30);
        scaleAnime((3.0f - var_f31 * 2.2f) * g_menuHIO.field_0x14);
        setRotate(&field_0x190, 90.0f - var_f31 * 65.0f);
        fopMsgM_setNowAlpha(&field_0x008[0], var_f31);
    } else if (temp_r0 <= var_r31) {
        f32 var_f31 = ((f32)(temp_r0 - var_r30) * (f32)(temp_r0 - var_r30)) / ((f32)(var_r31 - var_r30) * (f32)(var_r31 - var_r30));
        scaleAnime((0.8f - var_f31 * -0.2f) * g_menuHIO.field_0x14);

        if (field_0x008[0].mUserArea == var_r31) {
            mDoAud_seStart(JA_SE_SGAME_COUNT_GO, NULL);
        }
    } else if (temp_r6 > temp_r0) {
        if (temp_r0 <= var_r27) {
            f32 var_f31 = ((f32)(temp_r0 - temp_r6) * (f32)(temp_r0 - temp_r6)) / ((f32)(var_r27 - temp_r6) * (f32)(var_r27 - temp_r6));
            setRotate(&field_0x190, 25.0f - var_f31 * -35.0f);
        } else if (temp_r0 < temp_r7) {
            f32 var_f31 = ((f32)(temp_r0 - var_r27) * (f32)(temp_r0 - var_r27)) / ((f32)(temp_r0 - temp_r7) * (f32)(temp_r0 - temp_r7));
            f32 var_f30 = 1.0f - var_f31;
            scaleAnime((1.0f - var_f31 * 0.5f) * g_menuHIO.field_0x14);
            setRotate(&field_0x190, 60.0f - var_f31 * -210.0f);
            fopMsgM_setNowAlpha(&field_0x008[0], var_f30);
        } else {
            scaleAnime(g_menuHIO.field_0x14 * 0.5f);
            setRotate(&field_0x190, -90.0f);
            fopMsgM_setNowAlphaZero(&field_0x008[0]);
            rt = 1;
        }
    }

    return rt;
}

/* 80206CB0-80206DA4       .text scaleAnime__23dDlst_StarterScrnDraw_cFf */
void dDlst_StarterScrnDraw_c::scaleAnime(f32 i_scale) {
    field_0x190.mSize.x = field_0x190.mSizeOrig.x * i_scale;
    field_0x190.mSize.y = field_0x190.mSizeOrig.y * i_scale;

    #if VERSION > VERSION_JPN
    for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
        field_0x008[i].mSize.x = field_0x008[i].mSizeOrig.x * i_scale;
        field_0x008[i].mSize.y = field_0x008[i].mSizeOrig.y * i_scale;
    }
    #else
    field_0x008[0].mSize.x = field_0x008[0].mSizeOrig.x * i_scale;
    field_0x008[0].mSize.y = field_0x008[0].mSizeOrig.y * i_scale;
    field_0x008[1].mSize.x = field_0x008[1].mSizeOrig.x * i_scale;
    field_0x008[1].mSize.y = field_0x008[1].mSizeOrig.y * i_scale;
    field_0x008[2].mSize.x = field_0x008[2].mSizeOrig.x * i_scale;
    field_0x008[2].mSize.y = field_0x008[2].mSizeOrig.y * i_scale;
    #endif

    field_0x190.mPosCenter.x = field_0x190.mPosCenterOrig.x;
    field_0x190.mPosCenter.y = field_0x190.mPosCenterOrig.y;
    fopMsgM_cposMove(&field_0x190);

    #if VERSION > VERSION_JPN
    for (int i = 0; i < dMinigame_Starter_tex_number; i++) {
        field_0x008[i].mPosCenter.x = field_0x008[i].mPosCenterOrig.x * i_scale;
        field_0x008[i].mPosCenter.y = field_0x008[i].mPosCenterOrig.y * i_scale;
        fopMsgM_cposMove(&field_0x008[i]);
    }
    #else
    field_0x008[0].mPosCenter.x = field_0x008[0].mPosCenterOrig.x * i_scale;
    field_0x008[0].mPosCenter.y = field_0x008[0].mPosCenterOrig.y * i_scale;
    fopMsgM_cposMove(&field_0x008[0]);

    field_0x008[1].mPosCenter.x = field_0x008[1].mPosCenterOrig.x * i_scale;
    field_0x008[1].mPosCenter.y = field_0x008[1].mPosCenterOrig.y * i_scale;
    fopMsgM_cposMove(&field_0x008[1]);

    field_0x008[2].mPosCenter.x = field_0x008[2].mPosCenterOrig.x * i_scale;
    field_0x008[2].mPosCenter.y = field_0x008[2].mPosCenterOrig.y * i_scale;
    fopMsgM_cposMove(&field_0x008[2]);
    #endif
}

/* 80206DA4-80206E44       .text setRotate__23dDlst_StarterScrnDraw_cFP18fopMsgM_pane_classf */
void dDlst_StarterScrnDraw_c::setRotate(fopMsgM_pane_class* i_pane, f32 i_angle) {
    i_pane->pane->rotate((int)(i_pane->mSize.x / 2), (int)(i_pane->mSize.y / 2), ROTATE_Z, i_angle);
}

/* 80206E44-80206EDC       .text draw__23dDlst_StarterScrnDraw_cFv */
void dDlst_StarterScrnDraw_c::draw() {
    fopMsgM_setAlpha(&field_0x008[0]);

    for (int i = 0; i < 3; i++) {
        fopMsgM_setAlpha(&field_0x1c8[i]);
        fopMsgM_setAlpha(&field_0x270[i]);
    }
    
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    mpScrn->draw(0.0f, 0.0f, graf);
}

/* 80206EDC-80206EFC       .text dMinigame_Starter_Draw__FP19dMinigame_Starter_c */
static BOOL dMinigame_Starter_Draw(dMinigame_Starter_c* i_this) {
    return i_this->_draw();
}

/* 80206EFC-80206F1C       .text dMinigame_Starter_Execute__FP19dMinigame_Starter_c */
static BOOL dMinigame_Starter_Execute(dMinigame_Starter_c* i_this) {
    return i_this->_execute();
}

/* 80206F1C-80206F24       .text dMinigame_Starter_IsDelete__FP19dMinigame_Starter_c */
static BOOL dMinigame_Starter_IsDelete(dMinigame_Starter_c* i_this) {
    return TRUE;
}

/* 80206F24-80206F44       .text dMinigame_Starter_Delete__FP19dMinigame_Starter_c */
static BOOL dMinigame_Starter_Delete(dMinigame_Starter_c* i_this) {
    return i_this->_delete();
}

/* 80206F44-80206F64       .text dMinigame_Starter_Create__FP9msg_class */
static cPhs_State dMinigame_Starter_Create(msg_class* msg) {
    dMinigame_Starter_c* i_this = (dMinigame_Starter_c*)msg;
    return i_this->_create();
}

msg_method_class l_dMinigame_Starter_Method = {
    (process_method_func)dMinigame_Starter_Create,
    (process_method_func)dMinigame_Starter_Delete,
    (process_method_func)dMinigame_Starter_Execute,
    (process_method_func)dMinigame_Starter_IsDelete,
    (process_method_func)dMinigame_Starter_Draw,
};

msg_process_profile_definition g_profile_MINIGAME_STARTER = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 12,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MINIGAME_STARTER_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dMinigame_Starter_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Draw Prio    */ fpcDwPi_MINIGAME_STARTER_e,
    /* Msg SubMtd   */ &l_dMinigame_Starter_Method,
};
