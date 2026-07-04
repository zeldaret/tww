#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_menu_save.h"
#include "d/d_file_error.h"
#include "d/d_meter.h"
#include "m_Do/m_Do_Reset.h"
#include "m_Do/m_Do_MemCard.h"
#include "m_Do/m_Do_controller_pad.h"

/* 801D5DB8-801D5E8C       .text __ct__9dMs_HIO_cFv */
dMs_HIO_c::dMs_HIO_c() {
    field_0x5 = 5;
    field_0x6 = 0;
    field_0x7 = 0;
    field_0x8 = 5;
    field_0xc = -500;
    field_0xe = 200;
    field_0x9 = 0;
    field_0xa = 0;
    field_0xb = 3;
    field_0x10 = 5;
    field_0x11 = 8;
    field_0x12 = 5;
    field_0x13 = 0;
    field_0x14 = -100;
    field_0x16 = 150;
    field_0x18 = 5;
    field_0x19 = 8;
    field_0x1a = 5;
    field_0x1b = 6;
    field_0x1c = 2;
    field_0x1e = 200;
    field_0x20 = 12;
    field_0x21 = 140;
    field_0x22 = 70;
    field_0x23 = 6;
    field_0x24 = 8;
    field_0x25 = 0;
    field_0x26 = 3;
    field_0x28 = 90;
    field_0x29 = 10;
    field_0x2a = 0;
    field_0x2c = -60;
    field_0x2e = 0;
}

dMs_HIO_c g_msHIO;

/* 801D5E8C-801D6140       .text _create__12dMenu_save_cFv */
void dMenu_save_c::_create() {
    MenuSave.Scr = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(165, 165, 165, 165), MenuSave.Scr != NULL);

    stick = new STControl(5, 2, 3, 2);
    JUT_ASSERT(VERSION_SELECT(170, 170, 170, 170), stick != NULL);

    archive = dComIfGp_getSaveResArchive();
    JUT_ASSERT(VERSION_SELECT(174, 174, 174, 174), archive != NULL);

    MenuSave.Scr->set("menu_save.blo", archive);

    MenuSave.font = mDoExt_getMesgFont();
    JUT_ASSERT(VERSION_SELECT(180, 180, 180, 180), MenuSave.font != NULL);

    dFe_c = new dFile_error_c();
    JUT_ASSERT(VERSION_SELECT(184, 184, 184, 184), dFe_c != NULL);
    dFe_c->_create();

    g_msHIO.id = mDoHIO_createChild("セーブ画面", &g_msHIO);

    screenSet();
    displayInit();
    paneTransInit();
}

typedef void (dMenu_save_c::*menuProcFunc)();
menuProcFunc MenuSaveProc[] = {
    &dMenu_save_c::saveQuestion,
    &dMenu_save_c::memCardCheck,
    &dMenu_save_c::openSaveMenu,
    &dMenu_save_c::closeSaveMenu,
    &dMenu_save_c::memCardErrMsgWaitKey,
    &dMenu_save_c::memCardErrMsgWaitKey2,
    &dMenu_save_c::memCardErrMsgWaitKey3,
    &dMenu_save_c::memCardErrGoIPLSel,
    &dMenu_save_c::memCardErrGoIPLSel2,
    &dMenu_save_c::memCardErrMsgWaitFormatSel,
    &dMenu_save_c::memCardErrMsgWaitFormatSel2,
    &dMenu_save_c::memCardFormat,
    &dMenu_save_c::memCardFormatCheck,
    &dMenu_save_c::memCardMakeGameFileSel,
    &dMenu_save_c::memCardMakeGameFile,
    &dMenu_save_c::memCardMakeGameFileCheck,
    &dMenu_save_c::memCardDataLoadWait,
    &dMenu_save_c::memCardDataLoadWait2,
    &dMenu_save_c::memCardDataSave,
    &dMenu_save_c::memCardDataSaveUpMenu,
    &dMenu_save_c::memCardDataSaveSel,
    &dMenu_save_c::memCardDataSaveDownMenu,
    &dMenu_save_c::memCardDataSaveWait,
    &dMenu_save_c::msgWait,
    &dMenu_save_c::msgWait2,
    &dMenu_save_c::saveEndWait,
    &dMenu_save_c::saveWait,
    &dMenu_save_c::canNotSave,
    &dMenu_save_c::canNotSave2,
    &dMenu_save_c::gameContinue,
    &dMenu_save_c::gameContinue2,
    &dMenu_save_c::gameContinue3,
#if VERSION >= VERSION_JPN
    &dMenu_save_c::gameContinue4,
#endif
    &dMenu_save_c::endingNoSave,
    &dMenu_save_c::endingNoSave2,
    &dMenu_save_c::endingNoSave3,
    &dMenu_save_c::endingDataCheck,
    &dMenu_save_c::noSave,
    &dMenu_save_c::noSave2,
};

/* 801D6140-801D6174       .text initialize__12dMenu_save_cFv */
void dMenu_save_c::initialize() {
    displayInit();
    paneTransInit();
}

/* 801D6174-801D61A0       .text _open__12dMenu_save_cFv */
bool dMenu_save_c::_open() {
    return openNormal();
}

/* 801D61A0-801D62CC       .text openNormal__12dMenu_save_cFv */
BOOL dMenu_save_c::openNormal() {
    BOOL rt;
    switch (useType) {
    case 1:
        rt = openForCollect();
        break;
    case 0:
        rt = openForItem();
        break;
    case 2:
        rt = openForGameover();
        break;
    case 3:
        if (field_0x53c != 0) {
            if (field_0x53d == 2) {
                rt = openForEnding2();
            } else {
                rt = TRUE;
            }
        } else {
            rt = openForEnding();
        }
        break;
    }

    field_0x544++;
    if (rt == TRUE) {
        field_0x544 = 0;
        field_0x394.pane->show();

        if (useType == 3) {
            if (field_0x53c != 0) {
                if (field_0x53d == 2) {
                    field_0x53a = 0;
                    field_0x535 = 1;
                    proc = PROC_CAN_NOT_SAVE;
                } else {
                    field_0x53a = 1;
                    proc = PROC_MEMCARD_CHECK;
                }
            } else {
                field_0x53a = 0;
                proc = PROC_SAVE_QUESTION;
            }
        } else {
            field_0x53a = 0;
            proc = PROC_SAVE_QUESTION;
        }

        saveStatus = 2;
        return TRUE;
    }

    return FALSE;
}

/* 801D62CC-801D62F8       .text _close__12dMenu_save_cFv */
bool dMenu_save_c::_close() {
    return closeNormal();
}

/* 801D62F8-801D63A4       .text closeNormal__12dMenu_save_cFv */
BOOL dMenu_save_c::closeNormal() {
    BOOL rt;
    switch (useType) {
    case 1:
        rt = closeForCollect();
        break;
    case 0:
        rt = closeForItem();
        break;
    case 2:
        rt = closeForGameover();
        break;
    case 3:
        rt = closeForEnding();
        break;
    }

    field_0x544++;
    if (rt == TRUE) {
        proc = PROC_SAVE_WAIT;
        saveStatus = 0;
        field_0x544 = 0;
        field_0x53a = 1;
        return TRUE;
    }

    return FALSE;
}

/* 801D63A4-801D65C0       .text openForCollect__12dMenu_save_cFv */
BOOL dMenu_save_c::openForCollect() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_IN, NULL);
    }

    dMenu_setPushMenuButton(0);

    BOOL var_r29 = FALSE;
    BOOL alphaMask_rt = PaneAlphaMask(field_0x544 - g_msHIO.field_0x6, g_msHIO.field_0x5, 1, 0);
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 40.0f, 1, 0);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0x9 + g_msHIO.field_0x8), g_msHIO.field_0x8, 40.0f, 0.0f, 4, 2);
    }
    BOOL alphaWipe_rt = PaneScaleAlphaWipe(field_0x544 - g_msHIO.field_0x24, g_msHIO.field_0x23, g_msHIO.field_0x26, 1, 0);
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    BOOL menu_rt = menuUp();

    if (alphaMask_rt == TRUE
        && base_rt == TRUE
        && var_r29 == TRUE
        && alphaWipe_rt == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D65C0-801D67DC       .text openForItem__12dMenu_save_cFv */
BOOL dMenu_save_c::openForItem() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_IN, NULL);
    }

    dMenu_setPushMenuButton(0);

    BOOL var_r29 = FALSE;
    BOOL alphaMask_rt = PaneAlphaMask(field_0x544 - g_msHIO.field_0x6, g_msHIO.field_0x5, 1, 0);
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 40.0f, 1, 0);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0x9 + g_msHIO.field_0x8), g_msHIO.field_0x8, 40.0f, 0.0f, 4, 2);
    }
    BOOL alphaWipe_rt = PaneScaleAlphaWipe(field_0x544 - g_msHIO.field_0x24, g_msHIO.field_0x23, g_msHIO.field_0x26, 1, 0);
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    BOOL menu_rt = menuUp();

    if (alphaMask_rt == TRUE
        && base_rt == TRUE
        && var_r29 == TRUE
        && alphaWipe_rt == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D67DC-801D69F8       .text closeForCollect__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForCollect() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_OUT, NULL);
    }

    BOOL var_r29 = FALSE;
    dMenu_setPushMenuButton(2);
    
    BOOL alphaMask_rt = PaneAlphaMask(field_0x544 - g_msHIO.field_0x7, g_msHIO.field_0x5, 0, 1);
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0xa, g_msHIO.field_0x8, 0.0f, 40.0f, 4, 2);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0xa + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, g_msHIO.field_0xc, 0, 1);
    }
    BOOL alphaWipe_rt = PaneScaleAlphaWipe(field_0x544 - g_msHIO.field_0x25, g_msHIO.field_0x23, 1.0f, 0, 1);
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x12, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x14, 0, 1);
    BOOL menu_rt;
    if (field_0x535 != 0) {
        menu_rt = TRUE;
    } else {
        menu_rt = menuDown();
    }

    if (alphaMask_rt == TRUE
        && base_rt == TRUE
        && var_r29 == TRUE
        && alphaWipe_rt == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D69F8-801D6C14       .text closeForItem__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForItem() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_OUT, NULL);
    }

    BOOL var_r29 = FALSE;
    dMenu_setPushMenuButton(1);
    
    BOOL alphaMask_rt = PaneAlphaMask(field_0x544 - g_msHIO.field_0x7, g_msHIO.field_0x5, 0, 1);
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0xa, g_msHIO.field_0x8, 0.0f, 40.0f, 4, 2);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0xa + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, g_msHIO.field_0xc, 0, 1);
    }
    BOOL alphaWipe_rt = PaneScaleAlphaWipe(field_0x544 - g_msHIO.field_0x25, g_msHIO.field_0x23, 1.0f, 0, 1);
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x12, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x14, 0, 1);
    BOOL menu_rt;
    if (field_0x535 != 0) {
        menu_rt = TRUE;
    } else {
        menu_rt = menuDown();
    }

    if (alphaMask_rt == TRUE
        && base_rt == TRUE
        && var_r29 == TRUE
        && alphaWipe_rt == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D6C14-801D6E68       .text openForGameover__12dMenu_save_cFv */
// NONMATCHING - instruction order
BOOL dMenu_save_c::openForGameover() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_IN, NULL);
    }

    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 0.0f, 1, 0);

    s16 temp_r0 = field_0x544 - (g_msHIO.field_0x9 + (g_msHIO.field_0x8 - 2));
    if (temp_r0 == 0 && field_0x539) {
        for (int i = 0; i < 4; i++) {
            static const f32 x[] = {-180.0f, -70.0f, 70.0f, 180.0f};

            cXyz pos(x[i], 170.0f, 0.0f);
            dComIfGp_particle_set2DmenuFore(0x2E, &pos);
        }

        field_0x539 = 0;
    }

    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0x9 + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, -20.0f, 5, 2);
    }

    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    BOOL menu_rt = menuUp();

    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D6E68-801D6EAC       .text closeForGameover__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForGameover() {
    switch (endStatus) {
    case 1: return closeForGameover_1();
    case 0: return closeForGameover_2();
    }
}

/* 801D6EAC-801D704C       .text closeForGameover_1__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForGameover_1() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_OUT, NULL);
    }

    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0xa, g_msHIO.field_0x8, 0.0f, 40.0f, 4, 2);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0xa + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, g_msHIO.field_0xc, 0, 1);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x12, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x14, 0, 1);
    BOOL menu_rt;
    if (field_0x535 != 0) {
        menu_rt = TRUE;
    } else {
        menu_rt = menuDown();
    }

    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D704C-801D755C       .text closeForGameover_2__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForGameover_2() {
    BOOL var_r28 = FALSE;
    BOOL var_r27 = FALSE;
    BOOL var_r26 = FALSE;
    BOOL var_r25 = FALSE;
    
    BOOL var_r23 = PaneTranceTitle(field_0x544 - g_msHIO.field_0x13, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x2c, 1, 2);
    PaneRotate(field_0x544 - g_msHIO.field_0x13, g_msHIO.field_0x10, &field_0x324, 73.5f, field_0x324.mSizeOrig.y / 2, 7.0f, 0);
    if (var_r23 == TRUE) {
        var_r28 = PaneTranceTitle(field_0x544 - (g_msHIO.field_0x13 + g_msHIO.field_0x10), g_msHIO.field_0x10, g_msHIO.field_0x2c, g_msHIO.field_0x16, 0, 1);
    }

    var_r23 = PaneTranceBase(field_0x544 - g_msHIO.field_0xb, g_msHIO.field_0x8, 0.0f, g_msHIO.field_0x2c, 1, 2);
    PaneRotate(field_0x544 - g_msHIO.field_0xb, g_msHIO.field_0x10, &field_0x20c[0], 257.0f, 0.0f, -7.0f, 0);
    if (var_r23 == TRUE) {
        var_r27 = PaneTranceBase(field_0x544 - (g_msHIO.field_0xb + g_msHIO.field_0x8), g_msHIO.field_0x8, g_msHIO.field_0x2c, g_msHIO.field_0xe, 0, 1);
    }

    var_r23 = PaneTranceMenu(field_0x544 - g_msHIO.field_0x1b, g_msHIO.field_0x18, &field_0x3cc, 0.0f, g_msHIO.field_0x2c, 1, 2);
    PaneRotate(field_0x544 - g_msHIO.field_0x1b, g_msHIO.field_0x10, &field_0x3cc, 30.0f, 32.0f, -7.0f, 0);
    if (var_r23 == TRUE) {
        var_r26 = PaneTranceMenu(field_0x544 - (g_msHIO.field_0x1b + g_msHIO.field_0x18), g_msHIO.field_0x18, &field_0x3cc, g_msHIO.field_0x2c, g_msHIO.field_0x1e, 0, 1);
    }

    var_r23 = PaneTranceMenu(field_0x544 - (g_msHIO.field_0x1b + g_msHIO.field_0x1c), g_msHIO.field_0x18, &field_0x474, 0.0f, g_msHIO.field_0x2c, 1, 2);
    PaneRotate(field_0x544 - (g_msHIO.field_0x1b + g_msHIO.field_0x1c), g_msHIO.field_0x10, &field_0x474, 30.0f, 32.0f, 7.0f, 0);
    if (var_r23 == TRUE) {
        var_r25 = PaneTranceMenu(field_0x544 - (g_msHIO.field_0x1b + g_msHIO.field_0x1c + g_msHIO.field_0x18), g_msHIO.field_0x18, &field_0x474, g_msHIO.field_0x2c, g_msHIO.field_0x1e, 0, 1);
    }

    if (var_r28 == TRUE
        && var_r27 == TRUE
        && var_r26 == TRUE
        && var_r25 == TRUE)
    {
        PaneRotate(0, g_msHIO.field_0x10, &field_0x324, 73.5f, field_0x324.mSizeOrig.y / 2, 0.0f, 0);
        PaneRotate(0, g_msHIO.field_0x10, &field_0x20c[0], 250.5f, 0.0f, 0.0f, 0);
        PaneRotate(0, g_msHIO.field_0x10, &field_0x3cc, 30.0f, 32.0f, 0.0f, 0);
        PaneRotate(0, g_msHIO.field_0x10, &field_0x474, 30.0f, 32.0f, 0.0f, 0);
        return TRUE;
    }

    return FALSE;
}

/* 801D755C-801D76E0       .text openForEnding__12dMenu_save_cFv */
BOOL dMenu_save_c::openForEnding() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_IN, NULL);
    }

    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 0.0f, 1, 0);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0x9 + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, -20.0f, 5, 2);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    BOOL menu_rt = menuUp();

    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D76E0-801D7850       .text openForEnding2__12dMenu_save_cFv */
BOOL dMenu_save_c::openForEnding2() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_IN, NULL);
    }

    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 0.0f, 1, 0);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0x9 + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, -20.0f, 5, 2);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);

    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D7850-801D79F0       .text closeForEnding__12dMenu_save_cFv */
BOOL dMenu_save_c::closeForEnding() {
    if (field_0x544 == 0) {
        mDoAud_seStart(JA_SE_SAVE_PANEL_OUT, NULL);
    }

    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0xa, g_msHIO.field_0x8, 0.0f, 40.0f, 4, 2);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase(field_0x544 - (g_msHIO.field_0xa + g_msHIO.field_0x8), g_msHIO.field_0x8, 0.0f, g_msHIO.field_0xc, 0, 1);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x12, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x14, 0, 1);
    BOOL menu_rt;
    if (field_0x535 != 0) {
        menu_rt = TRUE;
    } else {
        menu_rt = menuDown();
    }

    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

/* 801D79F0-801D7A9C       .text _delete__12dMenu_save_cFv */
void dMenu_save_c::_delete() {
   delete MenuSave.Scr;
   mDoExt_removeMesgFont();
   delete stick;
   dFe_c->_delete();
   delete dFe_c;
   archive->removeResourceAll();
   mDoHIO_deleteChild(g_msHIO.id);
}

/* 801D7A9C-801D7B68       .text _move__12dMenu_save_cFv */
void dMenu_save_c::_move() {
#if VERSION > VERSION_DEMO
    if (!mDoRst::isReset())
#endif
    {
        if ((mDoMemCd_getProbeStat() == 0 || mDoMemCd_getProbeStat() == 1)
#if VERSION > VERSION_DEMO
            && !mDoRst::isReset()
#endif
           )
        {
            if (field_0x53b == 0 && dFe_c->getStatus() == 1) {
                dFe_c->closeMessage();
                field_0x533 = 0xFF;
                field_0x52d = PROC_MEMCARD_CHECK;
                proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY3;
            }
            mDoMemCd_clearProbeStat();
        }

        dFe_c->_move();
        (this->*MenuSaveProc[proc])();
    }
}

/* 801D7B68-801D7BB8       .text noSave__12dMenu_save_cFv */
void dMenu_save_c::noSave() {
    field_0x533 = 0xFF;
    dFe_c->setErrMessage(0x65, 0);
    proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY3;
    field_0x52d = PROC_NO_SAVE2;
}

/* 801D7BB8-801D7BCC       .text noSave2__12dMenu_save_cFv */
void dMenu_save_c::noSave2() {
    proc = PROC_SAVE_WAIT;
    saveStatus = 3;
}

/* 801D7BCC-801D7CE8       .text saveQuestion__12dMenu_save_cFv */
void dMenu_save_c::saveQuestion() {
    BOOL temp_r3;
    if (useType == 2 || useType == 3) {
        temp_r3 = YesNoSelect2(0);
    } else {
        temp_r3 = YesNoSelect(0);
    }

    if (temp_r3) {
        if (field_0x52f == 0) {
            *field_0x51c[field_0x536 ^ 1] = 0;
            proc = PROC_MEMCARD_CHECK;
        } else if (field_0x52f == 2) {
            proc = PROC_SAVE_WAIT;
            saveStatus = 3;
        } else {
            field_0x544 = 0;
            switch (useType) {
            case 0:
            case 1:
            case 2:
                fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x40);
                proc = PROC_GAME_CONTINUE;
                break;
            case 3:
                fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x4D);
                proc = PROC_ENDING_NO_SAVE;
                break;
            }
        }
    }
}

/* 801D7CE8-801D7E30       .text memCardCheck__12dMenu_save_cFv */
void dMenu_save_c::memCardCheck() {
    switch (mDoMemCd_getStatus(0)) {
    case mDoMemCd_Ctrl_c::CARD_STAT_WAIT:
        field_0x532 = 0x29;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        break;
    case 8:
        field_0x532 = 0x2A;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        break;
    case 9:
        field_0x532 = 0x2B;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        break;
    case mDoMemCd_Ctrl_c::CARD_STAT_WRONG_DEVICE:
        field_0x532 = 0x2C;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        break;
    case mDoMemCd_Ctrl_c::CARD_STAT_ENCODING:
    case mDoMemCd_Ctrl_c::CARD_STAT_ERROR:
        field_0x532 = 0x2d;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_FORMAT;
        break;
    case 11:
    case mDoMemCd_Ctrl_c::CARD_STAT_IOERROR:
        field_0x532 = 0x2E;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_ERR_MSG_WAIT_KEY2;
        field_0x533 = 0x62;
        field_0x52e = 7;
        break;
    case mDoMemCd_Ctrl_c::CARD_STAT_CREATE:
        mDoMemCd_setPictDataPtr(NULL);
        mDoMemCd_Load();
        proc = PROC_MEMCARD_DATA_LOAD_WAIT;
        break;
    case mDoMemCd_Ctrl_c::CARD_STAT_RESTORE:
        field_0x532 = 0x34;
        proc = PROC_CLOSE_SAVE_MENU;
        field_0x52d = PROC_MEMCARD_MAKE_GAME_FILE_SEL;
        break;
    }
}

/* 801D7E30-801D7E88       .text openSaveMenu__12dMenu_save_cFv */
void dMenu_save_c::openSaveMenu() {
    if (openSave() == TRUE) {
        field_0x53a = 0;
        field_0x394.pane->show();
        CursorAlphaInit();
        proc = PROC_SAVE_QUESTION;
    }
}

/* 801D7E88-801D7F30       .text closeSaveMenu__12dMenu_save_cFv */
void dMenu_save_c::closeSaveMenu() {
    BOOL rt;
    if (field_0x53a == 1) {
        rt = TRUE;
    } else {
        rt = closeSave();
    }

    if (rt == TRUE) {
        field_0x53a = 1;
        if (useType == 3) {
            fopMsgM_messageGet(field_0x51c[field_0x536], 0x4C);
        } else {
            fopMsgM_messageGet(field_0x51c[field_0x536], 0x39);
        }

        dFe_c->setErrMessage(field_0x532, 0);
        proc = field_0x52d;
    }
}

/* 801D7F30-801D7F4C       .text memCardErrMsgWaitKey__12dMenu_save_cFv */
void dMenu_save_c::memCardErrMsgWaitKey() {
    if (dFe_c->getStatus() == 2) {
        proc = PROC_OPEN_SAVE_MENU;
    }
}

/* 801D7F4C-801D7FC0       .text memCardErrMsgWaitKey2__12dMenu_save_cFv */
void dMenu_save_c::memCardErrMsgWaitKey2() {
    if (dFe_c->getStatus() == 2) {
        if (field_0x533 != 0xFF) {
            dFe_c->setErrMessage(field_0x533, 0);
            field_0x533 = 0xFF;
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY2;
        } else {
            dFe_c->setErrMessage(99, 0);
            proc = field_0x52e;
        }
    }
}

/* 801D7FC0-801D801C       .text memCardErrMsgWaitKey3__12dMenu_save_cFv */
void dMenu_save_c::memCardErrMsgWaitKey3() {
    if (dFe_c->getStatus() == 2) {
        if (field_0x533 != 0xFF) {
            dFe_c->setErrMessage(field_0x533, 0);
            field_0x533 = 0xFF;
        }

        proc = field_0x52d;
    }
}

/* 801D801C-801D8084       .text memCardErrGoIPLSel__12dMenu_save_cFv */
void dMenu_save_c::memCardErrGoIPLSel() {
    if (dFe_c->getStatus() == 2) {
        if (dFe_c->getYesNo() != 0) {
            dFe_c->setErrMessage(100, 0);
            proc = PROC_MEMCARD_ERR_GO_IPL_SEL2;
        } else {
            proc = PROC_OPEN_SAVE_MENU;
        }
    }
}

/* 801D8084-801D80DC       .text memCardErrGoIPLSel2__12dMenu_save_cFv */
void dMenu_save_c::memCardErrGoIPLSel2() {
    if (dFe_c->getStatus() == 2) {
        if (dFe_c->getYesNo() != 0) {
            OSResetSystem(1, 1, TRUE);
        } else {
            proc = PROC_OPEN_SAVE_MENU;
        }
    }
}

/* 801D80DC-801D8150       .text memCardErrMsgWaitFormatSel__12dMenu_save_cFv */
void dMenu_save_c::memCardErrMsgWaitFormatSel() {
    if (dFe_c->getStatus() == 2) {
        if (dFe_c->getYesNo() != 0) {
            dFe_c->setErrMessage(0x30, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_FORMAT_SEL;
        } else {
            dFe_c->setErrMessage(0x2F, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        }
    }
}

/* 801D8150-801D81DC       .text memCardErrMsgWaitFormatSel2__12dMenu_save_cFv */
void dMenu_save_c::memCardErrMsgWaitFormatSel2() {
    if (dFe_c->getStatus() == 2) {
        if (dFe_c->getYesNo() != 0) {
            mDoMemCd_Format();
            dFe_c->setErrMessage(0x31, 1);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_FORMAT_SEL2;
            field_0x53b = 1;
        } else {
            dFe_c->setErrMessage(0x2F, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        }
    }
}

/* 801D81DC-801D8230       .text memCardFormat__12dMenu_save_cFv */
void dMenu_save_c::memCardFormat() {
    field_0x540 = mDoMemCd_FormatSync();
    if (field_0x540 != 0) {
        dFe_c->closeMessage();
        proc = PROC_MEMCARD_FORMAT_CHECK;
    }
}

/* 801D8230-801D82C8       .text memCardFormatCheck__12dMenu_save_cFv */
void dMenu_save_c::memCardFormatCheck() {
    if (dFe_c->getStatus() == 2) {
        if (field_0x540 == 2) {
            dFe_c->setErrMessage(0x33, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY3;
            field_0x52d = PROC_MEMCARD_CHECK;
        } else if (field_0x540 == 1) {
            dFe_c->setErrMessage(0x32, 0);
            dFe_c->setTimeCountDownMode();
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY3;
            field_0x52d = PROC_MEMCARD_CHECK;
        }

        field_0x53b = 0;
    }
}

/* 801D82C8-801D83C0       .text memCardMakeGameFileSel__12dMenu_save_cFv */
void dMenu_save_c::memCardMakeGameFileSel() {
    if (dFe_c->getStatus() == 2) {
        if (dFe_c->getYesNo() != 0) {
            dComIfGs_setInitDataToCard(dataBuf, 0);
            mDoMemCdRWm_SetCheckSumGameData(dataBuf, 0);

            dComIfGs_setInitDataToCard(dataBuf, 1);
            mDoMemCdRWm_SetCheckSumGameData(dataBuf, 1);

            dComIfGs_setInitDataToCard(dataBuf, 2);
            mDoMemCdRWm_SetCheckSumGameData(dataBuf, 2);

            mDoMemCd_Save(dataBuf, sizeof(dataBuf), 0);

            dFe_c->setErrMessage(0x36, 1);
            proc = PROC_MEMCARD_MAKE_GAME_FILE;
            field_0x53b = 1;
        } else {
            dFe_c->setErrMessage(0x35, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        }
    }
}

/* 801D83C0-801D8414       .text memCardMakeGameFile__12dMenu_save_cFv */
void dMenu_save_c::memCardMakeGameFile() {
    field_0x540 = mDoMemCd_SaveSync();
    if (field_0x540 != 0) {
        dFe_c->closeMessage();
        proc = PROC_MEMCARD_MAKE_GAME_FILE_CHECK;
    }
}

/* 801D8414-801D84AC       .text memCardMakeGameFileCheck__12dMenu_save_cFv */
void dMenu_save_c::memCardMakeGameFileCheck() {
    if (dFe_c->getStatus() == 2) {
        if (field_0x540 == 2) {
            dFe_c->setErrMessage(0x37, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY3;
            field_0x52d = PROC_MEMCARD_CHECK;
        } else if (field_0x540 == 1) {
            dComIfGs_setNewFile(1);
            dFe_c->setErrMessage(0x38, 0);
            proc = PROC_MEMCARD_ERR_MSG_WAIT_KEY;
        }

        field_0x53b = 0;
    }
}

/* 801D84AC-801D8548       .text memCardDataLoadWait__12dMenu_save_cFv */
void dMenu_save_c::memCardDataLoadWait() {
    int rt = mDoMemCd_LoadSync(dataBuf, sizeof(dataBuf), 0);
    if (rt == 0)
        return;

    if (rt == 2) {
        proc = PROC_MEMCARD_CHECK;
    } else if (rt == 1) {
        if (field_0x53a == 1) {
            proc = PROC_OPEN_SAVE_MENU;
        } else if (useType == 3) {
            proc = PROC_ENDING_DATA_CHECK;
        } else {
            proc = PROC_MEMCARD_DATA_LOAT_WAIT2;
        }
    }
}

/* 801D8548-801D85D8       .text memCardDataLoadWait2__12dMenu_save_cFv */
void dMenu_save_c::memCardDataLoadWait2() {
    BOOL menu_rt = menuDown();
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    
    field_0x544++;
    if (menu_rt == TRUE && alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 1;
        proc = PROC_MEMCARD_DATA_SAVE;
    }
}

/* 801D85D8-801D8798       .text memCardDataSave__12dMenu_save_cFv */
void dMenu_save_c::memCardDataSave() {
    bool temp_r0;
    if (dComIfGs_getNewFile() == 1) {
        temp_r0 = true;
    } else if (dComIfGs_getNoFile() != 0) {
        temp_r0 = false;
    } else if (dComIfGs_getMemCardCheckID() != mDoMemCd_getCardSerialNo()) {
        temp_r0 = false;
    } else {
        temp_r0 = true;
    }

    if (temp_r0) {
        dComIfGs_exchangePlayerRecollectionData();
        dComIfGs_putSave(dStage_stagInfo_GetSaveTbl(dComIfGp_getStage().getStagInfo()));
        dComIfGs_setGameStartStage();

        BOOL test = mDoMemCdRWm_TestCheckSumGameData(&dataBuf[dComIfGs_getDataNum() * (sizeof(dSv_save_c) - 8)]);
        if (test) {
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3C);
            dataWrite();
            proc = PROC_MEMCARD_DATA_SAVE_WAIT;
        } else {
            mDoAud_seStart(JA_SE_ALERT_DATA, NULL);
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3B);
            proc = PROC_MEMCARD_DATA_SAVE_UP_MENU;
        }
    } else {
        mDoAud_seStart(JA_SE_ALERT_DATA, NULL);
        fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3A);
        proc = PROC_CAN_NOT_SAVE;
    }
}

/* 801D8798-801D8848       .text memCardDataSaveUpMenu__12dMenu_save_cFv */
void dMenu_save_c::memCardDataSaveUpMenu() {
    BOOL menu_rt = menuUp();
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    
    field_0x544++;
    if (menu_rt == TRUE && alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 0;
        CursorAlphaInit();
        field_0x52f = 1;
        CursorMove();
        field_0x394.pane->show();
        proc = PROC_MEMCARD_DATA_SAVE_SEL;
    }
}

/* 801D8848-801D88E8       .text memCardDataSaveSel__12dMenu_save_cFv */
void dMenu_save_c::memCardDataSaveSel() {
    if (YesNoSelect(0) != 0) {
        if (field_0x52f == 0) {
            #if VERSION == VERSION_PAL
            if (mDoMemCd_getStatus(0) != 2) {
                proc = PROC_MEMCARD_CHECK;
                return;
            }
            #endif
            proc = PROC_MEMCARD_DATA_SAVE_DOWN_MENU;
        } else {
            CursorAlphaInit();
            field_0x52f = 0;
            CursorMove();
            field_0x394.pane->show();
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x39);
            proc = PROC_MSG_WAIT;
            field_0x52d = PROC_SAVE_QUESTION;
        }
    }
}

/* 801D88E8-801D8964       .text memCardDataSaveDownMenu__12dMenu_save_cFv */
void dMenu_save_c::memCardDataSaveDownMenu() {
    BOOL menu_rt = menuDown();
    BOOL temp_r5 = TRUE;
    
    field_0x544++;
    if (menu_rt == TRUE && temp_r5 == TRUE) {
        field_0x544 = 0;
        field_0x535 = 1;
        fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3C);
        dataWrite();
        proc = PROC_MEMCARD_DATA_SAVE_WAIT;
    }
}

/* 801D8964-801D8A18       .text dataWrite__12dMenu_save_cFv */
void dMenu_save_c::dataWrite() {
    int res = dComIfGs_setMemoryToCard(dataBuf, dComIfGs_getDataNum());
    JUT_ASSERT(VERSION_SELECT(1789, 1792, 1792, 1803), res != -1);

    mDoMemCdRWm_SetCheckSumGameData(dataBuf, dComIfGs_getDataNum());
    mDoMemCd_Save(dataBuf, sizeof(dataBuf), 0);

#if VERSION >= VERSION_USA
    field_0x540 = mDoMemCd_SaveSync();
#endif
}

/* 801D8A18-801D8BB8       .text memCardDataSaveWait__12dMenu_save_cFv */
void dMenu_save_c::memCardDataSaveWait() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    field_0x544++;

#if VERSION <= VERSION_JPN
    int res = mDoMemCd_SaveSync();
#else
    if (field_0x540 == 0) {
        field_0x540 = mDoMemCd_SaveSync();
    }
#endif

#if VERSION <= VERSION_JPN
    if (res != 0 && alphaMsg_rt == TRUE)
#else
    if (field_0x540 != 0 && alphaMsg_rt == TRUE)
#endif
    {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x534 = g_msHIO.field_0x28;

#if VERSION <= VERSION_JPN
        if (res == 1)
#else
        if (field_0x540 == 1)
#endif
        {
            mDoAud_seStart(JA_SE_SAVE_FINISH, NULL);
            dComIfGs_exchangePlayerRecollectionData();
            dComIfGs_setMemCardCheckID(mDoMemCd_getCardSerialNo());
            dComIfGs_setNewFile(0);
            dComIfGs_setNoFile(0);
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3E);
            proc = PROC_MSG_WAIT;
            field_0x52d = PROC_SAVE_END_WAIT;
        }
#if VERSION <= VERSION_JPN
        else if (res == 2)
#else
        else if (field_0x540 == 2)
#endif
        {
            mDoAud_seStart(JA_SE_ALERT_DATA, NULL);
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3D);
            proc = PROC_MSG_WAIT2;
            field_0x52d = PROC_MEMCARD_CHECK;
        }
    }
}

/* 801D8BB8-801D8C24       .text msgWait__12dMenu_save_cFv */
void dMenu_save_c::msgWait() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    
    field_0x544++;
    if (alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        proc = field_0x52d;
    }
}

/* 801D8C24-801D8D08       .text msgWait2__12dMenu_save_cFv */
void dMenu_save_c::msgWait2() {
    if (field_0x534 != 0) {
        field_0x534--;
    }

    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);

    if (alphaMsg_rt == TRUE) {
        if (CPad_CHECK_TRIG_A(0)
            || CPad_CHECK_TRIG_B(0)
            || CPad_CHECK_TRIG_X(0)
            || CPad_CHECK_TRIG_Y(0)
            || CPad_CHECK_TRIG_L(0)
            || CPad_CHECK_TRIG_R(0)
            || CPad_CHECK_TRIG_Z(0)
            || CPad_CHECK_TRIG_START(0)
            || field_0x534 == 0)
        {
            field_0x536 ^= 1;
            field_0x544 = 0;
            proc = field_0x52d;
        }
    } else {
        field_0x544++;
    }
}

/* 801D8D08-801D8DCC       .text saveEndWait__12dMenu_save_cFv */
void dMenu_save_c::saveEndWait() {
    if (field_0x534 != 0) {
        field_0x534--;
    }

    if (CPad_CHECK_TRIG_A(0)
        || CPad_CHECK_TRIG_B(0)
        || CPad_CHECK_TRIG_X(0)
        || CPad_CHECK_TRIG_Y(0)
        || CPad_CHECK_TRIG_L(0)
        || CPad_CHECK_TRIG_R(0)
        || CPad_CHECK_TRIG_Z(0)
        || CPad_CHECK_TRIG_START(0)
        || field_0x534 == 0)
    {
        field_0x544 = 0;
        fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x40);
        proc = PROC_GAME_CONTINUE;
    }
}

/* 801D8DCC-801D8ED8       .text canNotSave__12dMenu_save_cFv */
void dMenu_save_c::canNotSave() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    if (alphaMsg_rt == FALSE) {
        field_0x544++;
    }

    if (alphaMsg_rt == TRUE) {
        if (CPad_CHECK_TRIG_A(0)
            || CPad_CHECK_TRIG_B(0)
            || CPad_CHECK_TRIG_X(0)
            || CPad_CHECK_TRIG_Y(0)
            || CPad_CHECK_TRIG_L(0)
            || CPad_CHECK_TRIG_R(0)
            || CPad_CHECK_TRIG_Z(0)
            || CPad_CHECK_TRIG_START(0))
        {
            field_0x536 ^= 1;
            field_0x544 = 0;

            if (useType == 3) {
                fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x4C);
            } else {
                fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x39);
            }

            proc = PROC_CAN_NOT_SAVE2;
        }
    }
}

/* 801D8ED8-801D8F9C       .text canNotSave2__12dMenu_save_cFv */
void dMenu_save_c::canNotSave2() {
    BOOL menu_rt;
    if (field_0x535) {
        menu_rt = menuUp();
    } else {
        menu_rt = TRUE;
    }

    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    
    field_0x544++;
    if (menu_rt == TRUE && alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 0;
        CursorAlphaInit();
        field_0x52f = 0;
        CursorMove();
        field_0x394.pane->show();
        proc = PROC_SAVE_QUESTION;
    }
}

/* 801D8F9C-801D9060       .text gameContinue__12dMenu_save_cFv */
void dMenu_save_c::gameContinue() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);
    
    BOOL menu_rt;
    if (field_0x535) {
        menu_rt = menuUp();
    } else {
        menu_rt = TRUE;
    }
    
    field_0x544++;
    if (alphaMsg_rt == TRUE && menu_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 0;
        CursorAlphaInit();
        field_0x52f = 0;
        CursorMove();
        field_0x394.pane->show();
        proc = PROC_GAME_CONTINUE2;
    }
}

/* 801D9060-801D914C       .text gameContinue2__12dMenu_save_cFv */
void dMenu_save_c::gameContinue2() {
    BOOL rt;
    if (useType == 2 || useType == 3) {
        rt = YesNoSelect2(1);
    } else {
        rt = YesNoSelect(2);
    }

    if (rt) {
        if (field_0x52f == 0) {
            switch (useType) {
            case 0:
            case 1:
                break;
            case 2:
                endStatus = 1;
                break;
            }

            proc = PROC_SAVE_WAIT;
            saveStatus = 3;
        } else if (useType == 2) {
#if VERSION == VERSION_DEMO
            proc = PROC_SAVE_WAIT;
            saveStatus = 3;
            endStatus = 0;
#else
            field_0x534 = 15;
            proc = PROC_GAME_CONTINUE4;
#endif
        } else if (field_0x52f == 2) {
            proc = PROC_SAVE_WAIT;
            saveStatus = 3;
        } else {
            field_0x544 = 0;
            field_0x534 = 30;
            proc = PROC_GAME_CONTINUE3;
        }
    }
}

/* 801D914C-801D91E8       .text gameContinue3__12dMenu_save_cFv */
void dMenu_save_c::gameContinue3() {
    BOOL alphaWipe_rt = PaneScaleAlphaWipe(field_0x544, g_msHIO.field_0x23, 1.0f, 0, 1);
    BOOL close_rt = closeForGameover_2();

    field_0x544++;
    if (alphaWipe_rt == TRUE && close_rt == TRUE) {
        if (field_0x534 != 0) {
            field_0x534--;
        } else {
            mDoRst::onReset();
        }
    }
}

/* 801D91E8-801D921C       .text gameContinue4__12dMenu_save_cFv */
void dMenu_save_c::gameContinue4() {
    if (field_0x534 != 0) {
        field_0x534--;
    } else {
        proc = PROC_SAVE_WAIT;
        saveStatus = 3;
        endStatus = 0;
    }
}

/* 801D921C-801D92B0       .text endingNoSave__12dMenu_save_cFv */
void dMenu_save_c::endingNoSave() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);

    field_0x544++;
    if (alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 0;
        CursorAlphaInit();
        field_0x52f = 1;
        CursorMove();
        field_0x394.pane->show();
        proc = PROC_ENDING_NO_SAVE2;
    }
}

/* 801D92B0-801D9334       .text endingNoSave2__12dMenu_save_cFv */
void dMenu_save_c::endingNoSave2() {
    if (YesNoSelect2(1)) {
        if (field_0x52f == 0) {
            endStatus = 0;
            proc = PROC_SAVE_WAIT;
            saveStatus = 3;
        } else {
            fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x4C);
            proc = PROC_ENDING_NO_SAVE3;
        }
    }
}

/* 801D9334-801D93C8       .text endingNoSave3__12dMenu_save_cFv */
void dMenu_save_c::endingNoSave3() {
    BOOL alphaMsg_rt = PaneAlphaMsgTxt(field_0x544, g_msHIO.field_0x29);

    field_0x544++;
    if (alphaMsg_rt == TRUE) {
        field_0x536 ^= 1;
        field_0x544 = 0;
        field_0x535 = 0;
        CursorAlphaInit();
        field_0x52f = 0;
        CursorMove();
        field_0x394.pane->show();
        proc = PROC_SAVE_QUESTION;
    }
}

/* 801D93C8-801D94C0       .text endingDataCheck__12dMenu_save_cFv */
void dMenu_save_c::endingDataCheck() {
    bool temp_r0;
    if (dComIfGs_getNewFile() == 1) {
        temp_r0 = true;
    } else if (dComIfGs_getNoFile() != 0) {
        temp_r0 = false;
    } else if (dComIfGs_getMemCardCheckID() != mDoMemCd_getCardSerialNo()) {
        temp_r0 = false;
    } else {
        temp_r0 = true;
    }

    if (temp_r0) {
        proc = PROC_SAVE_WAIT;
        saveStatus = 3;
    } else {
        mDoAud_seStart(JA_SE_ALERT_DATA, NULL);
        fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3A);
        proc = PROC_CAN_NOT_SAVE;
    }
}

/* 801D94C0-801D94C4       .text saveWait__12dMenu_save_cFv */
void dMenu_save_c::saveWait() {}

/* 801D94C4-801D9764       .text YesNoSelect__12dMenu_save_cFi */
BOOL dMenu_save_c::YesNoSelect(int param_0) {
    if (!field_0x394.pane->isVisible()) {
        return TRUE;
    }

    stick->checkTrigger();

    if (CPad_CHECK_TRIG_A(0)) {
        field_0x394.pane->hide();
        if (field_0x52f == 0) {
            if (param_0) {
                mDoAud_seStart(JA_SE_CONTINUE_GAME, NULL);
            } else {
                mDoAud_seStart(JA_SE_SAVE_START, NULL);
            }
        } else {
            if (param_0) {
                mDoAud_seStart(JA_SE_QUIT_GAME, NULL);
            } else {
                mDoAud_seStart(JA_SE_SAVE_CANCEL, NULL);
            }
        }
        return 1;
    } else if (CPad_CHECK_TRIG_B(0)) {
        if (param_0 == TRUE) {
            mDoAud_seStart(JA_SE_QUIT_GAME, NULL);
        } else {
#if VERSION <= VERSION_JPN
            mDoAud_seStart(JA_SE_SAVE_CANCEL, NULL);
#else
            mDoAud_seStart(JA_SE_CONTINUE_GAME, NULL);
#endif
        }

        field_0x394.pane->hide();
        field_0x52f = 2;
        return 1;
    } else if (stick->checkRightTrigger()) {
        if (field_0x52f != 1) {
            mDoAud_seStart(JA_SE_TALK_CURSOR, NULL);
            field_0x52f = 1;
            CursorMove();
        }
    } else if (stick->checkLeftTrigger()) {
        if (field_0x52f != 0) {
            mDoAud_seStart(JA_SE_TALK_CURSOR, NULL);
            field_0x52f = 0;
            CursorMove();
        }
    }

    CursorAnime();
    return 0;
}

/* 801D9764-801D9978       .text YesNoSelect2__12dMenu_save_cFi */
BOOL dMenu_save_c::YesNoSelect2(int param_0) {
    if (!field_0x394.pane->isVisible()) {
        return TRUE;
    }

    stick->checkTrigger();

    if (CPad_CHECK_TRIG_A(0)) {
        field_0x394.pane->hide();
        if (field_0x52f == 0) {
            if (param_0) {
                mDoAud_seStart(JA_SE_CONTINUE_GAME, NULL);
            } else {
                mDoAud_seStart(JA_SE_SAVE_START, NULL);
            }
        } else {
            if (param_0) {
                mDoAud_seStart(JA_SE_QUIT_GAME, NULL);
            } else {
                mDoAud_seStart(JA_SE_SAVE_CANCEL, NULL);
            }
        }
        return 1;
    } else if (stick->checkRightTrigger()) {
        if (field_0x52f != 1) {
            mDoAud_seStart(JA_SE_TALK_CURSOR, NULL);
            field_0x52f = 1;
            CursorMove();
        }
    } else if (stick->checkLeftTrigger()) {
        if (field_0x52f != 0) {
            mDoAud_seStart(JA_SE_TALK_CURSOR, NULL);
            field_0x52f = 0;
            CursorMove();
        }
    }

    CursorAnime();
    return 0;
}

/* 801D9978-801D99AC       .text CursorAlphaInit__12dMenu_save_cFv */
void dMenu_save_c::CursorAlphaInit() {
    field_0x394.mNowAlpha = 0;
    field_0x394.mUserArea = 0;
    field_0x530 = 0;
    fopMsgM_setAlpha(&field_0x394);
}

/* 801D99AC-801D99FC       .text CursorMove__12dMenu_save_cFv */
void dMenu_save_c::CursorMove() {
    fopMsgM_paneTrans(&field_0x394, field_0x52f * 139.0f, 0.0f);
}

/* 801D99FC-801D9ACC       .text CursorAnime__12dMenu_save_cFv */
// NONMATCHING - small float reg alloc
void dMenu_save_c::CursorAnime() {
    f32 temp_f1 = fopMsgM_valueIncrease(g_msHIO.field_0x20, field_0x394.mUserArea, 0);
    if (field_0x530 != 0) {
        temp_f1 = 1.0f - temp_f1;
    }

    field_0x394.mNowAlpha = g_msHIO.field_0x22 + (u32)((g_msHIO.field_0x21 - g_msHIO.field_0x22) * temp_f1);
    fopMsgM_setAlpha(&field_0x394);

    if (field_0x394.mUserArea == 0) {
        field_0x394.mUserArea = g_msHIO.field_0x20;
        field_0x530 ^= 1;
    } else {
        field_0x394.mUserArea--;
    }
}

/* 801D9ACC-801D9C28       .text openSave__12dMenu_save_cFv */
BOOL dMenu_save_c::openSave() {
    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0x9, g_msHIO.field_0x8, g_msHIO.field_0xc, 40.0f, 1, 0);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase((field_0x544 - g_msHIO.field_0x9) - g_msHIO.field_0x8, g_msHIO.field_0x8, 40.0f, 0.0f, 4, 2);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x11, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    BOOL menu_rt = menuUp();

    field_0x544++;
    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        field_0x544 = 0;
        return TRUE;
    }

    return FALSE;
}

/* 801D9C28-801D9DA4       .text closeSave__12dMenu_save_cFv */
BOOL dMenu_save_c::closeSave() {
    BOOL var_r29 = FALSE;
    BOOL base_rt = PaneTranceBase(field_0x544 - g_msHIO.field_0xa, g_msHIO.field_0x8, 0.0f, 40.0f, 4, 2);
    if (base_rt == TRUE) {
        var_r29 = PaneTranceBase((field_0x544 - g_msHIO.field_0xa) - g_msHIO.field_0x8, g_msHIO.field_0x8, 0.0f, g_msHIO.field_0xc, 0, 1);
    }
    BOOL title_rt = PaneTranceTitle(field_0x544 - g_msHIO.field_0x12, g_msHIO.field_0x10, 0.0f, g_msHIO.field_0x14, 0, 1);
    BOOL menu_rt;
    if (field_0x535 != 0) {
        menu_rt = TRUE;
    } else {
        menu_rt = menuDown();
    }

    field_0x544++;
    if (base_rt == TRUE
        && var_r29 == TRUE
        && title_rt == TRUE
        && menu_rt == TRUE)
    {
        field_0x535 = 0;
        field_0x544 = 0;
        return TRUE;
    }

    return FALSE;
}

/* 801D9DA4-801DA118       .text screenSet__12dMenu_save_cFv */
void dMenu_save_c::screenSet() {
    int i;
    u32 var_r28 = 'wp00';
    for (i = 0; i < 8; i++) {
        fopMsgM_setPaneData(&field_0x14[i], MenuSave.Scr->search(var_r28));
        var_r28++;
    }

    fopMsgM_setPaneData(&field_0x1d4, MenuSave.Scr->search('msk0'));
    fopMsgM_setPaneData(&field_0x20c[0], MenuSave.Scr->search('cc01'));
    fopMsgM_setPaneData(&field_0x20c[1], MenuSave.Scr->search('cc12'));
    fopMsgM_setPaneData(&field_0x20c[2], MenuSave.Scr->search('cc23'));
    fopMsgM_setPaneData(&field_0x20c[3], MenuSave.Scr->search('st00'));
    fopMsgM_setPaneData(&field_0x20c[4], MenuSave.Scr->search('st01'));

    ((J2DTextBox*)field_0x20c[3].pane)->setFont(MenuSave.font);
    ((J2DTextBox*)field_0x20c[4].pane)->setFont(MenuSave.font);

#if VERSION == VERSION_PAL
    ((J2DTextBox*)field_0x20c[3].pane)->setLineSpace(28.0f);
    ((J2DTextBox*)field_0x20c[4].pane)->setLineSpace(28.0f);
#endif

    char sp8[256];
    for (int i = 0; i < 256; i++) {
        sp8[i] = 'A';
    }
    sp8[255] = 0;

    ((J2DTextBox*)field_0x20c[3].pane)->setString(sp8);
    ((J2DTextBox*)field_0x20c[4].pane)->setString(sp8);

    field_0x51c[0] = ((J2DTextBox*)field_0x20c[3].pane)->getStringPtr();
    *field_0x51c[0] = 0;

    field_0x51c[1] = ((J2DTextBox*)field_0x20c[4].pane)->getStringPtr();
    *field_0x51c[1] = 0;

    fopMsgM_setPaneData(&field_0x324, MenuSave.Scr->search('tk00'));
    fopMsgM_setPaneData(&field_0x35c, MenuSave.Scr->search('tl00'));
#if VERSION == VERSION_PAL
    fopMsgM_setPaneData(&field_0x51c_pal, MenuSave.Scr->search('tlsv'));
#endif
    fopMsgM_setPaneData(&field_0x394, MenuSave.Scr->search('cur1'));
    fopMsgM_setPaneData(&field_0x3cc, MenuSave.Scr->search('ysk0'));
    fopMsgM_setPaneData(&field_0x404, MenuSave.Scr->search('ys00'));
    fopMsgM_setPaneData(&field_0x43c, MenuSave.Scr->search('yes'));
    ((J2DTextBox*)field_0x43c.pane)->setFont(MenuSave.font);

    fopMsgM_setPaneData(&field_0x474, MenuSave.Scr->search('nok0'));
    fopMsgM_setPaneData(&field_0x4ac, MenuSave.Scr->search('no00'));
    fopMsgM_setPaneData(&field_0x4e4, MenuSave.Scr->search('no'));
    ((J2DTextBox*)field_0x4e4.pane)->setFont(MenuSave.font);

#if VERSION == VERSION_PAL
    char yestxt[4];
    switch (dComIfGs_getPalLanguage()) {
    case 0:
        ((J2DPicture*)field_0x51c_pal.pane)->changeTexture("title_save.bti", 0);
        ((J2DTextBox*)field_0x43c.pane)->setString("Yes");
        ((J2DTextBox*)field_0x4e4.pane)->setString("No");
        break;
    case 1:
        ((J2DPicture*)field_0x51c_pal.pane)->changeTexture("title_save_gm.bti", 0);
        ((J2DTextBox*)field_0x43c.pane)->setString("Ja");
        ((J2DTextBox*)field_0x4e4.pane)->setString("Nein");
        break;
    case 2:
        ((J2DPicture*)field_0x51c_pal.pane)->changeTexture("title_save_fr.bti", 0);
        ((J2DTextBox*)field_0x43c.pane)->setString("Oui");
        ((J2DTextBox*)field_0x4e4.pane)->setString("Non");
        break;
    case 3: {
        strcpy(yestxt, "Si");
        yestxt[1] = 0xED;

        ((J2DPicture*)field_0x51c_pal.pane)->changeTexture("title_save_sp.bti", 0);
        ((J2DTextBox*)field_0x43c.pane)->setString(yestxt);
        ((J2DTextBox*)field_0x4e4.pane)->setString("No");
        break;
    }
    case 4: {
        strcpy(yestxt, "Si");
        yestxt[1] = 0xEC;

        ((J2DPicture*)field_0x51c_pal.pane)->changeTexture("title_save_it.bti", 0);
        ((J2DTextBox*)field_0x43c.pane)->setString(yestxt);
        ((J2DTextBox*)field_0x4e4.pane)->setString("No");
        break;
    }
    }
#endif
}

/* 801DA118-801DA2C8       .text paneTransInit__12dMenu_save_cFv */
void dMenu_save_c::paneTransInit() {
    field_0x544 = 0;
    PaneScaleAlphaWipe(field_0x544, g_msHIO.field_0x23, g_msHIO.field_0x26, 1, 0);
    PaneAlphaMask(field_0x544, g_msHIO.field_0x5, 1, 0);
    PaneTranceBase(field_0x544, g_msHIO.field_0x8, g_msHIO.field_0xc, 0.0f, 1, 0);
    PaneTranceTitle(field_0x544, g_msHIO.field_0x10, g_msHIO.field_0x14, 0.0f, 1, 0);
    PaneTranceMenu(field_0x544, g_msHIO.field_0x18, &field_0x3cc, g_msHIO.field_0x1e, 0.0f, 1, 0);
    PaneTranceMenu(field_0x544, g_msHIO.field_0x18, &field_0x474, g_msHIO.field_0x1e, 0.0f, 1, 0);
    field_0x394.pane->hide();
}

/* 801DA2C8-801DA3C4       .text displayInit__12dMenu_save_cFv */
void dMenu_save_c::displayInit() {
    field_0x536 = 0;
    field_0x53c = 0;
    field_0x53d = 0;
    field_0x53b = 0;
    proc = PROC_SAVE_WAIT;
    saveStatus = 1;
    field_0x53a = 1;
    endStatus = 2;
    field_0x535 = 0;
    CursorAlphaInit();
    field_0x52f = 0;
    CursorMove();

    fopMsgM_setNowAlpha(&field_0x20c[3], 1.0f);
    fopMsgM_setNowAlpha(&field_0x20c[4], 0.0f);
    fopMsgM_setAlpha(&field_0x20c[3]);
    fopMsgM_setAlpha(&field_0x20c[4]);

    field_0x539 = 1;
    
    if (useType == 3) {
        fopMsgM_messageGet(field_0x51c[field_0x536], 0x4C);
    } else {
        fopMsgM_messageGet(field_0x51c[field_0x536], 0x39);
    }

    *field_0x51c[field_0x536 ^ 1] = 0;
}

/* 801DA3C4-801DA420       .text initializeEx__12dMenu_save_cFv */
void dMenu_save_c::initializeEx() {
    fopMsgM_messageGet(field_0x51c[field_0x536], 0x3A);
    fopMsgM_messageGet(field_0x51c[field_0x536 ^ 1], 0x3A);
}

/* 801DA420-801DA508       .text menuUp__12dMenu_save_cFv */
BOOL dMenu_save_c::menuUp() {
    BOOL var_r31 = PaneTranceMenu(field_0x544, g_msHIO.field_0x18, &field_0x3cc, g_msHIO.field_0x1e, 0.0f, 1, 0);
    BOOL temp_r3 = PaneTranceMenu(field_0x544 - g_msHIO.field_0x1c, g_msHIO.field_0x18, &field_0x474, g_msHIO.field_0x1e, 0.0f, 1, 0);

    if (var_r31 == true && temp_r3 == TRUE) {
        return TRUE;
    }

    return FALSE;
}

/* 801DA508-801DA5F0       .text menuDown__12dMenu_save_cFv */
BOOL dMenu_save_c::menuDown() {
    BOOL var_r31 = PaneTranceMenu(field_0x544, g_msHIO.field_0x18, &field_0x3cc, 0.0f, g_msHIO.field_0x1e, 0, 1);
    BOOL temp_r3 = PaneTranceMenu(field_0x544 - g_msHIO.field_0x1c, g_msHIO.field_0x18, &field_0x474, 0.0f, g_msHIO.field_0x1e, 0, 1);

    if (var_r31 == true && temp_r3 == TRUE) {
        return TRUE;
    }

    return FALSE;
}

/* 801DA5F0-801DA6B0       .text PaneAlphaMsgTxt__12dMenu_save_cFsUc */
BOOL dMenu_save_c::PaneAlphaMsgTxt(s16 param_0, u8 param_1) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, 0);
    fopMsgM_setNowAlpha(&field_0x20c[field_0x536 + 3], 1.0f - var_f31);
    fopMsgM_setNowAlpha(&field_0x20c[(field_0x536 ^ 1) + 3], var_f31);
    fopMsgM_setAlpha(&field_0x20c[0 + 3]);
    fopMsgM_setAlpha(&field_0x20c[1 + 3]);
    return FALSE;
}

/* 801DA6B0-801DA7B8       .text PaneTranceBase__12dMenu_save_cFsUcffUci */
BOOL dMenu_save_c::PaneTranceBase(s16 param_0, u8 param_1, f32 param_2, f32 param_3, u8 param_4, int param_5) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_4);
    fopMsgM_paneTrans(&field_0x20c[0], 0.0f, param_2 + (var_f31 * (param_3 - param_2)));

    if (param_5 != 2) {
        if (param_5 == 1) {
            var_f31 = 1.0f - var_f31;
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setNowAlpha(&field_0x20c[i], var_f31);
            fopMsgM_setAlpha(&field_0x20c[i]);
        }
    }

    return FALSE;
}

/* 801DA7B8-801DAA80       .text PaneScaleAlphaWipe__12dMenu_save_cFsUcfUci */
BOOL dMenu_save_c::PaneScaleAlphaWipe(s16 param_0, u8 param_1, f32 param_2, u8 param_3, int param_4) {
    int i;

    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_3);

    f32 temp_f2 = param_2 - 1.0f;
    if (temp_f2 >= 0.0f) {
        f32 temp_f0 = (1.0f - var_f31) * temp_f2;
        for (i = 0; i < 8; i++) {
            field_0x14[i].mSize.x = field_0x14[i].mSizeOrig.x * (temp_f0 + 1.0f);
            field_0x14[i].mSize.y = field_0x14[i].mSizeOrig.y * (temp_f0 + 1.0f);
            field_0x14[i].pane->resize(field_0x14[i].mSize.x, field_0x14[i].mSize.y);
        }

        field_0x14[0].mPosTopLeft.x = field_0x14[0].mPosTopLeftOrig.x - (field_0x14[0].mSize.x - field_0x14[0].mSizeOrig.x);
        field_0x14[0].pane->move(field_0x14[0].mPosTopLeft.x, field_0x14[0].mPosTopLeftOrig.y);
        field_0x14[2].mPosTopLeft.y = field_0x14[2].mPosTopLeftOrig.y - (field_0x14[2].mSize.y - field_0x14[2].mSizeOrig.y);
        field_0x14[2].pane->move(field_0x14[2].mPosTopLeftOrig.x, field_0x14[2].mPosTopLeft.y);
        field_0x14[1].mPosTopLeft.y = field_0x14[1].mPosTopLeftOrig.y - (field_0x14[1].mSize.y - field_0x14[1].mSizeOrig.y);
        field_0x14[1].mPosTopLeft.x = field_0x14[2].mSize.x;
        field_0x14[1].pane->move(field_0x14[1].mPosTopLeft.x, field_0x14[1].mPosTopLeft.y);
        field_0x14[3].mPosTopLeft.x = field_0x14[0].mSize.x;
        field_0x14[3].pane->move(field_0x14[3].mPosTopLeft.x, field_0x14[3].mPosTopLeftOrig.y);
        field_0x14[4].pane->move(field_0x14[2].mSize.x + field_0x14[1].mSize.x, -field_0x14[1].mSize.y);
        field_0x14[5].pane->move(-field_0x14[5].mSize.x, -field_0x14[2].mSize.y);
        field_0x14[6].pane->move(-(field_0x14[0].mSize.x + field_0x14[5].mSize.x), -(field_0x14[2].mSize.y + field_0x14[6].mSize.y));
        field_0x14[7].pane->move(-(field_0x14[0].mSize.x + field_0x14[5].mSize.x), field_0x14[0].mSize.y + field_0x14[7].mSize.y);
    }

    if (param_4 != 2) {
        if (param_4 == 1) {
            var_f31 = 1.0f - var_f31;
        }

        for (i = 0; i < 8; i++) {
            fopMsgM_setNowAlpha(&field_0x14[i], var_f31);
            fopMsgM_setAlpha(&field_0x14[i]);
        }
    }

    return FALSE;
}

/* 801DAA80-801DAB10       .text PaneAlphaMask__12dMenu_save_cFsUcUci */
BOOL dMenu_save_c::PaneAlphaMask(s16 param_0, u8 param_1, u8 param_2, int param_3) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_2);

    if (param_3 != 2) {
        if (param_3 == 1) {
            var_f31 = 1.0f - var_f31;
        }

        fopMsgM_setNowAlpha(&field_0x1d4, var_f31);
        fopMsgM_setAlpha(&field_0x1d4);
    }

    return FALSE;
}

/* 801DAB10-801DAC0C       .text PaneTranceTitle__12dMenu_save_cFsUcffUci */
BOOL dMenu_save_c::PaneTranceTitle(s16 param_0, u8 param_1, f32 param_2, f32 param_3, u8 param_4, int param_5) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_4);
    fopMsgM_paneTrans(&field_0x324, 0.0f, param_2 + (var_f31 * (param_3 - param_2)));

    if (param_5 != 2) {
        if (param_5 == 1) {
            var_f31 = 1.0f - var_f31;
        }

        fopMsgM_setNowAlpha(&field_0x324, var_f31);
        fopMsgM_setNowAlpha(&field_0x35c, var_f31);
        fopMsgM_setAlpha(&field_0x324);
        fopMsgM_setAlpha(&field_0x35c);
    }

    return FALSE;
}

/* 801DAC0C-801DACD0       .text PaneRotate__12dMenu_save_cFsUcP18fopMsgM_pane_classfffUc */
BOOL dMenu_save_c::PaneRotate(s16 param_0, u8 param_1, fopMsgM_pane_class* param_2, f32 param_3, f32 param_4, f32 param_5, u8 param_6) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_6);
    param_2->pane->rotate(param_3, param_4, ROTATE_Z, param_5 * var_f31);

    return FALSE;
}

/* 801DACD0-801DADD4       .text PaneTranceMenu__12dMenu_save_cFsUcP18fopMsgM_pane_classffUci */
BOOL dMenu_save_c::PaneTranceMenu(s16 param_0, u8 param_1, fopMsgM_pane_class* param_2, f32 param_3, f32 param_4, u8 param_5, int param_6) {
    if (param_0 < 0)
        return FALSE;
    if (param_0 > param_1)
        return TRUE;

    f32 var_f31 = fopMsgM_valueIncrease(param_1, param_0, param_5);
    fopMsgM_paneTrans(param_2, 0.0f, param_3 + (var_f31 * (param_4 - param_3)));

    if (param_6 != 2) {
        if (param_6 == 1) {
            var_f31 = 1.0f - var_f31;
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setNowAlpha(&param_2[i], var_f31);
            fopMsgM_setAlpha(&param_2[i]);
        }
    }

    return FALSE;
}

/* 801DADD4-801DAE20       .text _draw__12dMenu_save_cFv */
void dMenu_save_c::_draw() {
    MenuSave.Scr->draw(0.0f, 0.0f, dComIfGp_getCurrentGrafPort());
    dFe_c->draw2();
}

/* 801DAE20-801DAE6C       .text _draw2__12dMenu_save_cFv */
void dMenu_save_c::_draw2() {
    dComIfGd_set2DOpa(&MenuSave);
    dFe_c->_draw();
}

/* 801DAE6C-801DAED0       .text draw__16dDlst_MenuSave_cFv */
void dDlst_MenuSave_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    Scr->draw(0.0f, 0.0f, graf);
}
