#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_name.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_controller_pad.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "stdio.h"

/* 80215E38-80215F64       .text __ct__9dNm_HIO_cFv */
dNm_HIO_c::dNm_HIO_c() {
    field_0x42 = -150;
    field_0x44 = 350;
    field_0x46 = 490;
    field_0x48 = 120;
    field_0x6 = 6;
    field_0x7 = 6;
    field_0x8 = 6;
    field_0x9 = 6;
    field_0xa = 6;
    field_0xb = 6;
    field_0xc = 6;
    field_0xd = 6;
    field_0xe = 0;
    field_0xf = 0;
    field_0x10 = 0;
    field_0x11 = 0;
    field_0x12 = 2;
    field_0x13 = 4;
    field_0x14 = 4;
#if VERSION == VERSION_USA
    field_0x15 = 6;
#else
    field_0x15 = 8;
#endif
    field_0x1f = 14;
    field_0x20 = 140;
    field_0x21 = 70;
    field_0x1b = 15;
    field_0x1d = 255;
    field_0x1e = 64;
    field_0x1c = 31;
    field_0x28 = 0;
    field_0x26 = 0;
    field_0x16 = 7;
    field_0x17 = 160;
    field_0x18 = 80;
    field_0x19 = 14;
    field_0x1a = 0;

    field_0x2a[0] = 0;
    field_0x2a[1] = 1;
    field_0x2a[2] = 1;

    field_0x30[0] = 0;
    field_0x30[1] = 0;
    field_0x30[2] = 0;

    field_0x36[0] = 0;
    field_0x36[1] = -1;
    field_0x36[2] = -1;

    field_0x3c[0] = 0;
    field_0x3c[1] = 0;
    field_0x3c[2] = 0;

    field_0x23 = 5;
    field_0x22 = 20;
    field_0x5 = 0;
}

dNm_HIO_c g_nmHIO;

typedef void (dName_c::*selProcFunc)(void);
static selProcFunc SelProc[] = {
    &dName_c::MojiSelect,
    &dName_c::MenuSelect,
    &dName_c::MenuButtonAnime,
    &dName_c::EndWait
};

/* 80215F64-80216190       .text _create__7dName_cFv */
void dName_c::_create() {
    nameIn.NameInScr = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(208, 208, 212, 212), nameIn.NameInScr != NULL);

    stick = new STControl(5, 2, 3, 2);
    JUT_ASSERT(VERSION_SELECT(212, 212, 216, 216), stick != NULL);
    stick->setWaitParm(5, 2, 3, 2, 0.9f, 0.5f, 0, 0x800);

    archive = dComIfGp_getNameResArchive();
    nameIn.NameInScr->set("name_input.blo", archive);
    nameIn.font = mDoExt_getMesgFont();
    JUT_ASSERT(VERSION_SELECT(222, 222, 226, 226), nameIn.font != NULL);

    g_nmHIO.id = mDoHIO_createChild("名前登録画面", &g_nmHIO);

    screenSet();
    *nextNameStr = 0;
#if VERSION_JPN
    displayInit();
#endif
    paneTransInit();
}

/* 80216190-802161C4       .text initial__7dName_cFv */
void dName_c::initial() {
    displayInit();
    paneTransInit();
}

void dName_c::_deleteSp() {
    mDoHIO_deleteChild(g_nmHIO.id);
}

/* 802161C4-80216248       .text _delete__7dName_cFv */
void dName_c::_delete() {
    delete nameIn.NameInScr;
    mDoExt_removeMesgFont();
    delete stick;
    archive->removeResourceAll();
    mDoHIO_deleteChild(g_nmHIO.id);  // supposed to be _deleteSp?
}

/* 80216248-80216268       .text _move__7dName_cFv */
void dName_c::_move() {
    NameInMain();
}

/* 80216268-802162A4       .text nameCheck__7dName_cFv */
int dName_c::nameCheck() {
    for (int i = 8, len = 7; i > 0; i--) {
#if VERSION <= VERSION_JPN
        // '　' (full-width space)
        if (chrInfo[len].character != ' ' && chrInfo[len].character != '\x81\x40')
#else
        if (chrInfo[len].character != ' ')
#endif
        {
            return len + 1;
        }
        len--;
    }

    return 0;
}

/* 802162A4-802162F8       .text playNameSet__7dName_cFi */
void dName_c::playNameSet(int nameLength) {
    char* str = inputStr;

    for (int i = 0; i < nameLength; i++) {
#if VERSION <= VERSION_USA
        if (chrInfo[i].set == MOJI_EIGO) {
            *str = chrInfo[i].character;
            str += 1;
        } else {
            *(u16*)str = chrInfo[i].character;
            str += 2;
        }
#else
        *str = chrInfo[i].character;
        str += 1;
#endif
    }

    *str = 0;
}

/* 802162F8-80216670       .text _open__7dName_cFv */
bool dName_c::_open() {
    BOOL base0_rt = PaneTranceBase0(paneTransTimer - g_nmHIO.field_0x10, g_nmHIO.field_0x8, g_nmHIO.field_0x46, 0.0f, 1, 0);
    BOOL title_rt = PaneTranceTitle(paneTransTimer - g_nmHIO.field_0xe, g_nmHIO.field_0x6, g_nmHIO.field_0x42, 0.0f, 1, 0);
    BOOL name_rt = PaneTranceName(paneTransTimer - g_nmHIO.field_0xf, g_nmHIO.field_0x7, g_nmHIO.field_0x44, 0.0f, 1, 0);
    BOOL base_rt = PaneTranceBase(paneTransTimer - g_nmHIO.field_0x10, g_nmHIO.field_0x8, g_nmHIO.field_0x46, 0.0f, 1, 0);
    BOOL kata_rt = PaneTranceKata(paneTransTimer - g_nmHIO.field_0x12, g_nmHIO.field_0xa, g_nmHIO.field_0x48, 0.0f, 1, 0);
    BOOL hira_rt = PaneTranceHira(paneTransTimer - g_nmHIO.field_0x11, g_nmHIO.field_0x9, g_nmHIO.field_0x48, 0.0f, 1, 0);
#if VERSION <= VERSION_USA
    BOOL eisu_rt = PaneTranceEisu(paneTransTimer - g_nmHIO.field_0x13, g_nmHIO.field_0xb, g_nmHIO.field_0x48, 0.0f, 1, 0);
#endif
    BOOL arw_rt = PaneTranceArrow(paneTransTimer - g_nmHIO.field_0x14, g_nmHIO.field_0xc, g_nmHIO.field_0x48, 0.0f, 1, 0);
    BOOL end_rt = PaneTranceEnd(paneTransTimer - g_nmHIO.field_0x15, g_nmHIO.field_0x15, g_nmHIO.field_0x48, 0.0f, 1, 0);

    paneTransTimer++;

    if (base0_rt == TRUE
        && title_rt == TRUE
        && name_rt == TRUE
        && base_rt == TRUE
        && kata_rt == TRUE
        && hira_rt == TRUE
#if VERSION <= VERSION_USA
        && eisu_rt == TRUE
#endif
        && arw_rt == TRUE
        && end_rt == TRUE)
    {
        paneTransTimer = 0;
        return true;
    }

    return false;
}

/* 80216670-802169E0       .text _close__7dName_cFv */
bool dName_c::_close() {
    BOOL base0_rt = PaneTranceBase0(paneTransTimer - g_nmHIO.field_0x10, g_nmHIO.field_0x8, 0.0f, g_nmHIO.field_0x46, 0, 1);
    BOOL title_rt = PaneTranceTitle(paneTransTimer - g_nmHIO.field_0xe, g_nmHIO.field_0x6, 0.0f, g_nmHIO.field_0x42, 0, 1);
    BOOL name_rt = PaneTranceName(paneTransTimer - g_nmHIO.field_0xf, g_nmHIO.field_0x7, 0.0f, g_nmHIO.field_0x44, 0, 1);
    BOOL base_rt = PaneTranceBase(paneTransTimer - g_nmHIO.field_0x10, g_nmHIO.field_0x8, 0.0f, g_nmHIO.field_0x46, 0, 1);
    BOOL kata_rt = PaneTranceKata(paneTransTimer - g_nmHIO.field_0x12, g_nmHIO.field_0xa, 0.0f, g_nmHIO.field_0x48, 0, 1);
    BOOL hira_rt = PaneTranceHira(paneTransTimer - g_nmHIO.field_0x11, g_nmHIO.field_0x9, 0.0f, g_nmHIO.field_0x48, 0, 1);
#if VERSION <= VERSION_USA
    BOOL eisu_rt = PaneTranceEisu(paneTransTimer - g_nmHIO.field_0x13, g_nmHIO.field_0xb, 0.0f, g_nmHIO.field_0x48, 0, 1);
#endif
    BOOL arw_rt = PaneTranceArrow(paneTransTimer - g_nmHIO.field_0x14, g_nmHIO.field_0xc, 0.0f, g_nmHIO.field_0x48, 0, 1);
    BOOL end_rt = PaneTranceEnd(paneTransTimer - g_nmHIO.field_0x15, g_nmHIO.field_0x15, 0.0f, g_nmHIO.field_0x48, 0, 1);

    paneTransTimer++;

    if (base0_rt == TRUE
        && title_rt == TRUE
        && name_rt == TRUE
        && base_rt == TRUE
        && kata_rt == TRUE
        && hira_rt == TRUE
#if VERSION <= VERSION_USA
        && eisu_rt == TRUE
#endif
        && arw_rt == TRUE
        && end_rt == TRUE)
    {
        return true;
    }

    return false;
}

/* 802169E0-80216C08       .text NameInMain__7dName_cFv */
void dName_c::NameInMain() {
    stick->checkTrigger();
    (this->*SelProc[selProc])();

#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
    if (CPad_CHECK_TRIG_Y(0)) {
        mDoAud_seStart(JA_SE_NAME_PUSH_BUTTON, NULL, 0, 0);
        prevMojiSet = mojiSet;
        mojiSet++;
#if VERSION <= VERSION_JPN
        if (mojiSet > MOJI_EIGO) {
#else
        if (mojiSet > MOJI_KATA) {
#endif
            mojiSet = MOJI_HIRA;
        }
        mojiListChange(prevMojiSet);
    } else
#endif

#if VERSION <= VERSION_JPN
    if (CPad_CHECK_TRIG_X(0)) {
        if (curPos != 0) {
            if (mojiChange(curPos - 1) == 1) {
                mDoAud_seStart(JA_SE_NAME_STR_SWITCH, NULL, 0, 0);
            } else {
                mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
            }
        }
    } else
#endif

    if (CPad_CHECK_TRIG_RIGHT(0)) {
        if (curPos != 8) {
            mDoAud_seStart(JA_SE_NAME_NAME_CURSOR, NULL, 0, 0);
            curPos++;
            nameCursorMove();
        }
    } else if (CPad_CHECK_TRIG_LEFT(0)) {
        if (curPos != 0) {
            mDoAud_seStart(JA_SE_NAME_NAME_CURSOR, NULL, 0, 0);
            curPos--;
            nameCursorMove();
        }
    } else if (CPad_CHECK_TRIG_B(0)) {
        if (curPos == 0) {
            mDoAud_seStart(JA_SE_MSEL_CANCEL_1, NULL, 0, 0);
            field_0x97c[0].pane->hide();
            selProc = PROC_END_WAIT;
            isInputEnd_ = 2;
        } else {
            backSpace();
        }
    } else if (CPad_CHECK_TRIG_START(0)) {
        if (selProc != PROC_MENU_BUTTON_ANIME && (selProc != PROC_MENU_SELECT || selMenu != MENU_END)) {
            mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
            selProc = PROC_MENU_SELECT;
            selMenu = MENU_END;
            menuCursorMove();

            for (int i = 0; i < 3; i++) {
                field_0x8d4[i].pane->hide();
            }

            field_0x97c[0].pane->show();
            selectCursorMove();
        }
    }

    nameCursorAnime();
}

/* 80216C08-80216D14       .text nameCursorAnime__7dName_cFv */
// NONMATCHING - one float reg swap
void dName_c::nameCursorAnime() {
    f32 var_f1 = fopMsgM_valueIncrease(g_nmHIO.field_0x1f, field_0x1c4c.mUserArea, 0);
    if (field_0x2906 != 0) {
        var_f1 = 1.0f - var_f1;
    }

    field_0x1c4c.mNowAlpha = (f32)g_nmHIO.field_0x1e + (u32)((g_nmHIO.field_0x1d - g_nmHIO.field_0x1e) * var_f1);
    fopMsgM_setAlpha(&field_0x1c4c);

    if (field_0x1c4c.mUserArea == 0) {
        field_0x2906 ^= 1;
        field_0x1c4c.mUserArea = g_nmHIO.field_0x1b;
    } else {
        field_0x1c4c.mUserArea--;
    }
}

/* 80216D14-80216D18       .text EndWait__7dName_cFv */
void dName_c::EndWait() {}

/* 80216D18-80216F14       .text MojiSelect__7dName_cFv */
void dName_c::MojiSelect() {
    if (CPad_CHECK_TRIG_A(0)) {
        selectMojiSet();
    } else if (stick->checkRightTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        charColumn++;
        if (charColumn > 12) {
            charColumn = 0;
        }
        selectCursorMove();
    } else if (stick->checkLeftTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        if (charColumn == 0) {
            charColumn = 12;
        } else {
            charColumn--;
        }
        selectCursorMove();
    }
    
    if (stick->checkUpTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        if (charRow == 0) {
            selProc = PROC_MENU_SELECT;
            menuCursorPosSet();
        } else {
            charRow--;
        }
        selectCursorMove();
    } else if (stick->checkDownTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        charRow++;
        if (charRow > 4) {
            charRow = 4;
            selProc = PROC_MENU_SELECT;
            menuCursorPosSet();
        }
        selectCursorMove();
    }

    selectCursorAnime();
}

/* 80216F14-80217284       .text mojiChange__7dName_cFUc */
int dName_c::mojiChange(u8 idx) {
    if (chrInfo[idx].field_0x3 == 0 || chrInfo[idx].set == MOJI_EIGO || chrInfo[idx].character == SJIS('　', 0x8140U)) {
        return 0;
    }

    if (chrInfo[idx].column == 4 || chrInfo[idx].column == 6 || chrInfo[idx].column == 8 || chrInfo[idx].column == 9) {
        return 0;
    }

    switch (chrInfo[idx].column) {
    case 0:
    case 10: {
        if (chrInfo[idx].character == SJIS('ウ', 0x8345U) || chrInfo[idx].character == SJIS('ゥ', 0x8344U) ||
            chrInfo[idx].character == SJIS('ヴ', 0x8394U))
        {
            chrInfo[idx].character++;

            if (chrInfo[idx].character == SJIS('ェ', 0x8346U)) {
                chrInfo[idx].character = SJIS('ヴ', 0x8394U);
            }

            if (chrInfo[idx].character == SJIS('ヵ', 0x8395U)) {
                chrInfo[idx].character = SJIS('ゥ', 0x8344U);
            }
        } else {
            int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('ァ', 0x8340U) : SJIS('ぁ', 0x829fU);

            if ((chrInfo[idx].character - c) % 2) {
                --chrInfo[idx].character;
            } else {
                ++chrInfo[idx].character;
            }
        }
        break;
    }
    case 1: {
        int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('カ', 0x834aU) : SJIS('か', 0x82a9U);
        c = ((chrInfo[idx].character - c) % 2);

        int c2 = c + 1;
        chrInfo[idx].character = (chrInfo[idx].character - c) + (c2 & 1);
        break;
    }
    case 2: {
        int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('サ', 0x8354U) : SJIS('さ', 0x82b3U);
        c = ((chrInfo[idx].character - c) % 2);

        int c2 = c + 1;
        chrInfo[idx].character = (chrInfo[idx].character - c) + (c2 & 1);
        break;
    }
    case 3:
    case 12: {
        if (chrInfo[idx].character != (u32)0x815b) {
            if (chrInfo[idx].character <= (chrInfo[idx].set != MOJI_HIRA ? SJIS('ヂ', 0x8361U) : SJIS('ぢ', 0x82c0U))) {
                int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('タ', 0x835eU) : SJIS('た', 0x82bdU);
                c = ((chrInfo[idx].character - c) % 2);

                int c2 = c + 1;
                chrInfo[idx].character = (chrInfo[idx].character - c) + (c2 & 1);
            } else if (chrInfo[idx].character <=
                           (chrInfo[idx].set != MOJI_HIRA ? SJIS('ド', 0x8368U) : SJIS('ど', 0x82c7U)) &&
                       chrInfo[idx].character >=
                           (chrInfo[idx].set != MOJI_HIRA ? SJIS('テ', 0x8365U) : SJIS('て', 0x82c4U)))
            {
                int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('テ', 0x8365U) : SJIS('て', 0x82c4U);
                c = ((chrInfo[idx].character - c) % 2);

                int c2 = c + 1;
                chrInfo[idx].character = (chrInfo[idx].character - c) + (c2 & 1);
            } else {
                int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('ッ', 0x8362U) : SJIS('っ', 0x82c1U);
                int c2 = (chrInfo[idx].character - c) % 3;

                int ivar2 = c2 + 1;
                if (ivar2 > 2) {
                    ivar2 = 0;
                }

                chrInfo[idx].character = ivar2 + (chrInfo[idx].character - c2);
            }
        }
        break;
    }
    case 5: {
        int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('ハ', 0x836eU) : SJIS('は', 0x82cdU);
        int c2 = (chrInfo[idx].character - c) % 3;

        int ivar2 = c2 + 1;
        if (ivar2 > 2) {
            ivar2 = 0;
        }

        chrInfo[idx].character = ivar2 + (chrInfo[idx].character - c2);
        break;
    }
    case 7:
    case 11: {
        int c = chrInfo[idx].set != MOJI_HIRA ? SJIS('ャ', 0x8383U) : SJIS('ゃ', 0x82e1U);
        c = ((chrInfo[idx].character - c) % 2);

        int c2 = c + 1;
        chrInfo[idx].character = (chrInfo[idx].character - c) + (c2 & 1);
        break;
    }
    }

    setNameText();
    return 1;
}

/* 80217284-802172CC       .text selectMojiSet__7dName_cFv */
void dName_c::selectMojiSet() {
#if VERSION <= VERSION_JPN
    int moji = getMoji();
    if (moji != -1) {
        if (moji == '゛' || moji == '゜') {
            if (curPos != 0) {
                if (checkDakuon(moji, curPos - 1) == 1) {
                    mDoAud_seStart(JA_SE_NAME_INPUT, NULL, 0, 0);
                    setDakuon(moji, curPos - 1);
                } else {
                    mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
                }
            }
        } else {
            setMoji(moji);
        }
    }
#else
    setMoji(getMoji());
#endif
    setNameText();
    nameCursorMove();

}

#if VERSION <= VERSION_JPN
BOOL dName_c::checkDakuon(int param_0, u8 param_1) {
    if (chrInfo[param_1].set == MOJI_EIGO) {
        return 0;
    }

    if (param_1 == 0 && chrInfo[param_1].field_0x3 == 0) {
        return 0;
    }

    if (param_0 == '゜' && chrInfo[param_1].column != 5) {
        return 0;
    }

    if (param_0 == '゛' &&
        (chrInfo[param_1].character == 'ウ' || chrInfo[param_1].character == 'ヴ'))
    {
        return 1;
    }

    if (param_0 == '゛' && chrInfo[param_1].column != 1 && chrInfo[param_1].column != 2 &&
        chrInfo[param_1].column != 3 && chrInfo[param_1].column != 5)
    {
        return 0;
    }

    return 1;
}

BOOL dName_c::setDakuon(int param_1, u8 param_2) {
    int c;

    if (param_1 == '゛') {
        switch (chrInfo[param_2].column) {
        case 0: {
            c = -1;
            if (chrInfo[param_2].character == 'ウ' || chrInfo[param_2].character == 'ヴ') {
                c = 4;
                chrInfo[param_2].character = 'ヴ';
            }
            break;
        }
        case 1: {
            int c2 = chrInfo[param_2].set != MOJI_HIRA ? 'カ' : 'か';
            c = (chrInfo[param_2].character - c2) % 2;
            break;
        }
        case 2: {
            int c2 = chrInfo[param_2].set != MOJI_HIRA ? 'サ' : 'さ';
            c = (chrInfo[param_2].character - c2) % 2;
            break;
        }
        case 3: {
            int c2;
            if (chrInfo[param_2].character <=
                ((chrInfo[param_2].set != MOJI_HIRA ? 'ヂ' : 'ぢ')))
            {
                c2 = chrInfo[param_2].set != MOJI_HIRA ? 'タ' : 'た';
                c = (chrInfo[param_2].character - c2) % 2;
            } else {
                if (chrInfo[param_2].character <= (chrInfo[param_2].set != 0 ? 'ド' : 'ど'))
                {
                    if (chrInfo[param_2].character >=
                        (chrInfo[param_2].set != 0 ? 'テ' : 'て'))
                    {
                        c2 = chrInfo[param_2].set != MOJI_HIRA ? 'テ' : 'て';
                        c = (chrInfo[param_2].character - c2) % 2;
                        break;
                    }
                }

                c2 = chrInfo[param_2].set != MOJI_HIRA ? 'ッ' : 'っ';
                c = (chrInfo[param_2].character - c2) % 3;
                if (c == 2) {
                    c = 1;
                } else if (c == 1) {
                    c = 0;
                } else if (c == 0) {
                    c = 3;
                }
            }
            break;
        }
        case 5: {
            int c2 = chrInfo[param_2].set != MOJI_HIRA ? 'ハ' : 'は';
            c = (chrInfo[param_2].character - c2) % 3;
            break;
        }
        }

        if (c != 1) {
            if (c == 2) {
                chrInfo[param_2].character -= 1;
            } else if (c == 0) {
                chrInfo[param_2].character += 1;
            } else if (c == 3) {
                chrInfo[param_2].character += 2;
            }

            setNameText();

            return 1;
        }
    } else if (param_1 == '゜') {
        int c2 = chrInfo[param_2].set != MOJI_HIRA ? 'ハ' : 'は';
        c = (chrInfo[param_2].character - c2) % 3;
        if (c != 2) {
            chrInfo[param_2].character = chrInfo[param_2].character + (2 - c);
            setNameText();

            return 1;
        }
    }

    return 0;
}
#endif

/* 802172CC-802173E8       .text getMoji__7dName_cFv */
// NONMATCHING - reg alloc
int dName_c::getMoji() {
    int result = -1;
    const char* moji;

    fopMsgM_pane_class* pane;
    switch (mojiSet) {
    case MOJI_HIRA:
        pane = &hiraMojiPanes[charColumn];
        break;
    case MOJI_KATA:
        pane = &kataMojiPanes[charColumn];
        break;
#if VERSION <= VERSION_USA
    case MOJI_EIGO:
        pane = &eisuMojiPanes[charColumn];
        break;
#endif
    }

    moji = ((J2DTextBox*)(pane->pane))->getStringPtr();
    int i = 0;
    while (*moji != 0) {
        if (*moji == '\n') {
            moji++;
            continue;
        }

#if VERSION <= VERSION_USA
        if (*(u8*)moji >> 4 == 0x8 || *(u8*)moji >> 4 == 0x9) {
            if (i == charRow) {
                result = *(u16*)moji;
                break;
            }
            moji += 2;
            i++;
        } else {
            if (i == charRow) {
                result = *(u8*)moji;
                break;
            }
            moji++;
            i++;
        }
#else
        if (i == charRow) {
            result = *moji;
            break;
        }
        moji++;
        i++;
#endif
    }

    return result;
}

/* 802173E8-80217610       .text setMoji__7dName_cFi */
void dName_c::setMoji(int moji) {
    if (curPos == 8 || nameCheck() == 8) {
        mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
    } else {
        mDoAud_seStart(JA_SE_NAME_INPUT, NULL, 0, 0);

        s32 notEmpty = false;
        for (int i = curPos; i < 8; i++) {
#if VERSION <= VERSION_JPN
            // '　' (full-width space)
            if (chrInfo[i].character != '\x81\x40')
#else
            if (chrInfo[i].character != ' ')
#endif
            {
                notEmpty = true;
                break;
            }
        }

        if (notEmpty) {
#if VERSION <= VERSION_JPN
            // '　' (full-width space)
            if (chrInfo[7].character == '\x81\x40')
#else
            if (chrInfo[7].character == ' ')
#endif
            {
                for (int i = 6; i >= curPos; i--) {
                    chrInfo[i + 1] = chrInfo[i];
                }

                chrInfo[curPos].column = charColumn;
                chrInfo[curPos].row = charRow;
                chrInfo[curPos].set = mojiSet;
                chrInfo[curPos].field_0x3 = 1;
#if VERSION <= VERSION_USA
                chrInfo[curPos].character = moji;
#else
                chrInfo[curPos].character = moji & 0xFF;
#endif

                if (curPos != 8) {
                    curPos++;
                }
            }
        } else {
            chrInfo[curPos].column = charColumn;
            chrInfo[curPos].row = charRow;
            chrInfo[curPos].set = mojiSet;
            chrInfo[curPos].field_0x3 = 1;
#if VERSION <= VERSION_USA
            chrInfo[curPos].character = moji;
#else
            chrInfo[curPos].character = moji & 0xFF;
#endif

            if (curPos != 8) {
                curPos++;
            }
        }
    }
}

/* 80217610-802177E4       .text setNameText__7dName_cFv */
// NONMATCHING - some float math issues
void dName_c::setNameText() {
    f32 var_f31 = ((J2DTextBox*)namePane.pane)->mFontSizeX;
    f32 ratio = var_f31 / nameIn.font->getCellWidth();
    *pNameTxt = 0;

    for (int i = 0; i < 8; i++) {
        if (chrInfo[i].field_0x3 != 0) {
            JUTFont::TWidth twidth;
            nameIn.font->getWidthEntry(chrInfo[i].character, &twidth);

            int sp50 = (int)twidth.field_0x1 * ratio * 10000.0f;

            f32 fvar4 = sp50 / 10000.0f;
            f32 fvar5 = (var_f31 - fvar4) * 0.5f;
            f32 fvar6 = var_f31 - (fvar4 + fvar5);

            int ivar2 = fvar5;

            int ivar7 = ivar2 + (int)fvar4 + (int)fvar6;
            if (ivar7 < (int)var_f31) {
                fvar6 += (int)var_f31 - ivar7;
            }

            char spC[320];

#if VERSION <= VERSION_JPN
            if (chrInfo[i].set == MOJI_EIGO)
#endif
            {
                sprintf(spC,
                    "\x1b"
                    "CR[%d]%c\x1b"
                    "CR[%d]\x1b"
                    "CR[%d]",
                    ivar2,
                    (u8)chrInfo[i].character,
                    (int)fvar6,
                    2
                );
            }
#if VERSION <= VERSION_JPN
            else {
                sprintf(spC,
                    "\x1b"
                    "CR[%d]%c%c\x1b"
                    "CR[%d]\x1b"
                    "CR[%d]",
                    ivar2,
                    (u8)((chrInfo[i].character & 0xFF00) >> 8),
                    (u8)chrInfo[i].character,
                    (int)fvar6,
                    2
                );
            }
#endif
            strcat(pNameTxt, spC);
        }
    }
}

/* 802177E4-80217870       .text nameCursorMove__7dName_cFv */
void dName_c::nameCursorMove() {
    fopMsgM_paneTrans(&field_0x1c4c, (f32)g_nmHIO.field_0x28 + curPos * g_nmHIO.field_0x1c, g_nmHIO.field_0x26);
}

/* 80217870-802179BC       .text selectCursorMove__7dName_cFv */
void dName_c::selectCursorMove() {
    int idx;
#if VERSION == VERSION_PAL
    if (charColumn < 3) {
        idx = 0;
    } else if (charColumn < 6) {
        idx = 1;
    } else if (charColumn < 8) {
        idx = 4;
    } else if (charColumn < 10) {
        idx = 2;
    } else if (charColumn >= 10) {
        idx = 3;
    }
#else

#if VERSION <= VERSION_JPN
    if (charColumn < 3) {
        idx = 0;
    } else if (charColumn < 6) {
        idx = 1;
    } else if (charColumn < 8) {
        idx = 2;
    } else
#endif
    if (charColumn < 10) {
        idx = 3;
    } else if (charColumn >= 10) {
        idx = 4;
    }

#endif

    field_0x2ab0[idx][0] = charColumn;
    field_0x2ab0[idx][1] = charRow;
    field_0x2ab0[idx][2] = 1;

    for (int i = 0; i < 2; i++) {
        fopMsgM_paneTrans(&field_0x8d4[i], charColumn * 39.0f, charRow * 40.0f);
    }

    fopMsgM_paneTrans(&field_0x8d4[2], charColumn * 39.0f, charRow * 40.0f);
    selectCursorTxtChange();
}

/* 802179BC-80217A28       .text selectCursorTxtChange__7dName_cFv */
void dName_c::selectCursorTxtChange() {
    int moji = getMoji();
    if (moji > 0xFF) {
        pCurTxt[0] = (moji >> 8) & 0xFF;
        pCurTxt[1] = moji;
        pCurTxt[2] = 0;
    } else {
        pCurTxt[0] = moji;
        pCurTxt[1] = 0;
    }
}

/* 80217A28-80217D44       .text selectCursorAnime__7dName_cFv */
// NONMATCHING - one float reg swap
void dName_c::selectCursorAnime() {
    f32 sp14[3] = {0.0f, -3.0f, 4.0f};
    f32 sp8[3] = {0.0f, 4.0f, -3.0f};

    if (field_0x8d4[0].mUserArea == 0) {
        field_0x8d4[0].mUserArea = g_nmHIO.field_0x16;

        fopMsgM_paneTrans(&field_0x8d4[0],
            (f32)charColumn * 39.0f + (f32)g_nmHIO.field_0x2a[field_0x2905],
            (f32)charRow * 40.0f + (f32)g_nmHIO.field_0x30[field_0x2905]);

        fopMsgM_paneTrans(&field_0x8d4[1],
            (f32)charColumn * 39.0f + (f32)g_nmHIO.field_0x36[field_0x2905],
            (f32)charRow * 40.0f + (f32)g_nmHIO.field_0x3c[field_0x2905]);

        field_0x8d4[0].pane->rotate(field_0x2ac8 + sp14[field_0x2905]);
        field_0x8d4[1].pane->rotate(field_0x2acc + sp8[field_0x2905]);

        field_0x2905++;
        if (field_0x2905 > 2) {
            field_0x2905 = 0;
        }
    } else {
        field_0x8d4[0].mUserArea--;
    }

    if (field_0x8d4[2].mUserArea == 0) {
        f32 temp_f1 = fopMsgM_valueIncrease(g_nmHIO.field_0x19, field_0x8d4[1].mUserArea, 0);
        if (field_0x2909) {
            temp_f1 = 1.0f - temp_f1;
        }

        u32 temp = (g_nmHIO.field_0x17 - g_nmHIO.field_0x18) * temp_f1;
        field_0x8d4[0].mNowAlpha = g_nmHIO.field_0x18 + temp;
        field_0x8d4[1].mNowAlpha = g_nmHIO.field_0x18 + temp;
        fopMsgM_setAlpha(&field_0x8d4[0]);
        fopMsgM_setAlpha(&field_0x8d4[1]);

        if (field_0x8d4[1].mUserArea == 0) {
            field_0x8d4[1].mUserArea = g_nmHIO.field_0x19;
            field_0x2909 ^= 1;
        } else {
            field_0x8d4[1].mUserArea--;
        }

        field_0x8d4[2].mUserArea = g_nmHIO.field_0x1a;
    } else {
        field_0x8d4[2].mUserArea--;
    }
}

/* 80217D44-80217DC8       .text menuCursorPosSet__7dName_cFv */
void dName_c::menuCursorPosSet() {
#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
    if (charColumn < 3) {
        selMenu = MENU_HIRA;
    } else if (charColumn < 6) {
        selMenu = MENU_KATA;
    }
#if VERSION != VERSION_PAL
    else if (charColumn < 8) {
        selMenu = MENU_EIGO;
    }
#endif
    else
#endif
    if (charColumn < 10) {
        selMenu = MENU_BACKSPACE;
    } else if (charColumn >= 10) {
        selMenu = MENU_END;
    }

    menuCursorMove();

    for (int i = 0; i < 3; i++) {
        field_0x8d4[i].pane->hide();
    }

    field_0x97c[0].pane->show();
}

/* 80217DC8-802180E4       .text MenuSelect__7dName_cFv */
void dName_c::MenuSelect() {
    if (stick->checkRightTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        selMenu++;
        if (selMenu > MENU_END) {
            #if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
            selMenu = MENU_HIRA;
            #else
            selMenu = MENU_BACKSPACE;
            #endif
        }
        menuCursorMove();
    } else if (stick->checkLeftTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
        if (selMenu == MENU_HIRA)
#else
        if (selMenu == MENU_BACKSPACE)
#endif
        {
            selMenu = MENU_END;
        } else {
            selMenu--;
        }
        menuCursorMove();
    } else if (stick->checkUpTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        selProc = PROC_MOJI_SELECT;
        selectCursorPosSet(4);
    } else if (stick->checkDownTrigger()) {
        mDoAud_seStart(JA_SE_NAME_CURSOR, NULL, 0, 0);
        selProc = PROC_MOJI_SELECT;
        selectCursorPosSet(0);
    } else if (CPad_CHECK_TRIG_A(0)) {
        if (selMenu == MENU_END) {
            if (nameCheck() != 0) {
                mDoAud_seStart(inputCompleteSound, NULL, 0, 0);
            } else {
                mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
            }
        } else {
            mDoAud_seStart(JA_SE_NAME_PUSH_BUTTON, NULL, 0, 0);
        }
        field_0x97c[0].pane->hide();
        paneTransTimer = 0;
        selProc = PROC_MENU_BUTTON_ANIME;
    } else if (CPad_CHECK_TRIG_START(0)) {
        if (selMenu == MENU_END) {
            if (nameCheck() != 0) {
                mDoAud_seStart(inputCompleteSound, NULL, 0, 0);
            } else {
                mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
            }
            field_0x97c[0].pane->hide();
            paneTransTimer = 0;
            selProc = PROC_MENU_BUTTON_ANIME;
        }
    }

    menuCursorAnime();
}

/* 802180E4-80218228       .text MenuButtonAnime__7dName_cFv */
void dName_c::MenuButtonAnime() {
    field_0x2ac4 = g_nmHIO.field_0x22 * fopMsgM_valueIncrease(g_nmHIO.field_0x23, paneTransTimer, 5);

    switch (selMenu) {
    case MENU_HIRA:
        fopMsgM_paneTrans(&field_0x1afc[0], 0.0f, field_0x2ac4);
        break;
    case MENU_KATA:
        fopMsgM_paneTrans(&field_0x177c[0], 0.0f, field_0x2ac4);
        break;
#if VERSION <= VERSION_USA
    case MENU_EIGO:
        fopMsgM_paneTrans(&field_0x13fc[0], 0.0f, field_0x2ac4);
        break;
#endif
    case MENU_BACKSPACE:
        fopMsgM_paneTrans(&field_0x107c[0], 0.0f, field_0x2ac4);
        break;
    case MENU_END:
        fopMsgM_paneTrans(&field_0xcfc[0], 0.0f, field_0x2ac4);
        break;
    }

    paneTransTimer++;
    if (paneTransTimer > g_nmHIO.field_0x23) {
        field_0x97c[0].pane->show();
        menuAbtnSelect();
        selProc = PROC_MENU_SELECT;
        paneTransTimer = 0;
    }
}

/* 80218228-802182FC       .text menuAbtnSelect__7dName_cFv */
void dName_c::menuAbtnSelect() {
    switch (selMenu) {
    case MENU_HIRA:
    case MENU_KATA:
#if VERSION <= VERSION_USA
    case MENU_EIGO:
#endif
        if (selMenu != mojiSet) {
            prevMojiSet = mojiSet;
            mojiSet = selMenu;
            mojiListChange(prevMojiSet);
        }
        break;
    case MENU_BACKSPACE:
        backSpace();
        break;
    case MENU_END:
        int namelen = nameCheck();
        if (namelen != 0) {
            field_0x97c[0].pane->hide();
            playNameSet(namelen);
            isInputEnd_ = 1;
        } else {
            mDoAud_seStart(JA_SE_NAME_INPUT_LIMIT, NULL, 0, 0);
        }
        break;
    }
}

/* 802182FC-80218428       .text backSpace__7dName_cFv */
void dName_c::backSpace() {
    if (curPos != 0) {
        mDoAud_seStart(JA_SE_NAME_DELETE, NULL, 0, 0);

#if VERSION <= VERSION_JPN
        // '　' (full-width space)
        if (curPos == 8 && chrInfo[7].character != '\x81\x40')
#else
        if (curPos == 8 && chrInfo[7].character != ' ')
#endif
        {
            chrInfo[7].column = 7;
            chrInfo[7].row = 1;
#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
            chrInfo[7].set = MOJI_HIRA;
#else
            chrInfo[7].set = MOJI_EIGO;
#endif
            chrInfo[7].field_0x3 = 1;
#if VERSION <= VERSION_JPN
            chrInfo[7].character = '\x81\x40';
#else
            chrInfo[7].character = ' ';
#endif
        } else {
            for (int i = curPos - 1; i < 7; i++) {
                chrInfo[i] = chrInfo[i + 1];
            }
            chrInfo[7].column = 7;
            chrInfo[7].row = 1;
#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
            chrInfo[7].set = MOJI_HIRA;
#else
            chrInfo[7].set = MOJI_EIGO;
#endif
            chrInfo[7].field_0x3 = 1;
#if VERSION <= VERSION_JPN
            chrInfo[7].character = '\x81\x40';
#else
            chrInfo[7].character = ' ';
#endif
        }
        
        curPos--;
        setNameText();
        nameCursorMove();
    }
}

/* 80218428-802184EC       .text mojiListChange__7dName_cFUc */
void dName_c::mojiListChange(u8 i_prevSet) {
    fopMsgM_pane_class* prevMojiPanes;
    switch (i_prevSet) {
    case MOJI_HIRA:
        prevMojiPanes = hiraMojiPanes;
        break;
    case MOJI_KATA:
        prevMojiPanes = kataMojiPanes;
        break;
#if VERSION <= VERSION_USA
    case MOJI_EIGO:
        prevMojiPanes = eisuMojiPanes;
        break;
#endif
    }

    fopMsgM_pane_class* newMojiPanes;
    switch (mojiSet) {
    case MOJI_HIRA:
        newMojiPanes = hiraMojiPanes;
        break;
    case MOJI_KATA:
        newMojiPanes = kataMojiPanes;
        break;
#if VERSION <= VERSION_USA
    case MOJI_EIGO:
        newMojiPanes = eisuMojiPanes;
        break;
#endif
    }

    for (int i = 0; i < 13; i++) {
        prevMojiPanes[i].pane->hide();
        newMojiPanes[i].pane->show();
    }

    selectCursorTxtChange();
}

/* 802184EC-80218818       .text menuCursorMove__7dName_cFv */
void dName_c::menuCursorMove() {
    field_0x97c[0].mNowAlpha = 0;
    field_0x97c[0].mUserArea = 0;
    field_0x97c[1].mUserArea = 0;
    field_0x2908 = 0;
    fopMsgM_setAlpha(&field_0x97c[0]);

    for (int i = 0; i < 5; i++) {
        field_0x97c[i].mInitAlpha = field_0x97c[i].pane->getAlpha();
        field_0x97c[i].mPosTopLeft.x = field_0x97c[i].mPosTopLeftOrig.x;
        field_0x97c[i].mPosTopLeft.y = field_0x97c[i].mPosTopLeftOrig.y;
        field_0x97c[i].mPosCenter.x = field_0x97c[i].mPosCenterOrig.x;
        field_0x97c[i].mPosCenter.y = field_0x97c[i].mPosCenterOrig.y;
        field_0x97c[i].mSize.x = field_0x97c[i].mSizeOrig.x;
        field_0x97c[i].mSize.y = field_0x97c[i].mSizeOrig.y;
        fopMsgM_cposMove(&field_0x97c[i]);
    }

    static f32 PosData[] = {
    #if VERSION <= VERSION_USA
        -117.0f,
        0.0f,
        117.0f,
        194.0f,
        272.0f,
    #else
        -130.0f,
        0.0f,
        130.0f,
        260.0f,
    #endif
    };

    switch (selMenu) {
    case MENU_HIRA:
    case MENU_KATA:
        ((J2DPicture*)field_0x97c[1].pane)->setMirror((J2DMirror)3);
        ((J2DPicture*)field_0x97c[3].pane)->setMirror((J2DMirror)0);

        fopMsgM_paneTrans(&field_0x97c[0], PosData[selMenu], 0.0f);
        break;
#if VERSION <= VERSION_USA
    case MENU_EIGO:
#endif
    case MENU_BACKSPACE:
        ((J2DPicture*)field_0x97c[1].pane)->setMirror((J2DMirror)3);
        ((J2DPicture*)field_0x97c[3].pane)->setMirror((J2DMirror)0);

        fopMsgM_paneTrans(&field_0x97c[0], PosData[selMenu], 0.0f);
#if VERSION <= VERSION_USA
        fopMsgM_paneScaleX(&field_0x97c[1], 0.45f);
        fopMsgM_paneScaleX(&field_0x97c[3], 0.45f);
        fopMsgM_paneScaleX(&field_0x97c[4], 0.45f);

        field_0x97c[1].pane->move(field_0x97c[0].mSizeOrig.x, field_0x97c[1].mPosTopLeft.y);
        field_0x97c[3].pane->move(field_0x97c[0].mSizeOrig.x, field_0x97c[3].mPosTopLeft.y);
        field_0x97c[4].pane->move(field_0x97c[0].mSizeOrig.x, field_0x97c[4].mPosTopLeft.y);
        field_0x97c[2].pane->move(field_0x97c[0].mSizeOrig.x + field_0x97c[1].mSize.x, field_0x97c[2].mPosTopLeft.y);
#endif
        break;
    case MENU_END:
        ((J2DPicture*)field_0x97c[1].pane)->setMirror(J2DMirror_Y);
        ((J2DPicture*)field_0x97c[3].pane)->setMirror(J2DMirror_X);

        fopMsgM_paneTrans(&field_0x97c[0], PosData[selMenu], 2.0f);
        fopMsgM_paneTrans(&field_0x97c[1], PosData[selMenu], -2.0f);
        fopMsgM_paneTrans(&field_0x97c[3], PosData[selMenu], -2.0f);
        fopMsgM_paneTrans(&field_0x97c[4], PosData[selMenu], -2.0f);
        fopMsgM_paneTrans(&field_0x97c[2], PosData[selMenu], -5.0f);

        for (int i = 1; i < 5; i++) {
            field_0x97c[i].mPosCenter.x = field_0x97c[i].mPosCenterOrig.x;
            field_0x97c[i].mPosTopLeft.x = field_0x97c[i].mPosCenter.x - (field_0x97c[i].mSize.x / 2);
            field_0x97c[i].pane->move(field_0x97c[i].mPosTopLeft.x, field_0x97c[i].mPosTopLeft.y);
        }
        break;
    }
}

/* 80218818-80218944       .text selectCursorPosSet__7dName_cFi */
void dName_c::selectCursorPosSet(int row) {
    if (field_0x2ab0[selMenu][2] == 1) {
        charColumn = field_0x2ab0[selMenu][0];
        charRow = row;
    } else {
        switch (selMenu) {
        case MENU_HIRA:
            charColumn = 0;
            break;
        case MENU_KATA:
            charColumn = 3;
            break;
#if VERSION <= VERSION_USA
        case MENU_EIGO:
            charColumn = 6;
            break;
#endif
        case MENU_BACKSPACE:
            charColumn = 8;
            break;
        case MENU_END:
            charColumn = 10;
            break;
        }

        charRow = row;
        field_0x2ab0[selMenu][0] = charColumn;
        field_0x2ab0[selMenu][1] = charRow;
        field_0x2ab0[selMenu][2] = 1;
    }

    for (int i = 0; i < 3; i++) {
        field_0x8d4[i].pane->show();
    }

    selectCursorMove();
    field_0x97c[0].pane->hide();
}

/* 80218944-80218A48       .text menuCursorAnime__7dName_cFv */
// NONMATCHING - one float reg swap
void dName_c::menuCursorAnime() {
    f32 var_f1 = fopMsgM_valueIncrease(g_nmHIO.field_0x1f, field_0x97c[0].mUserArea, 0);
    if (field_0x2908 != 0) {
        var_f1 = 1.0f - var_f1;
    }

    field_0x97c[0].mNowAlpha = (f32)g_nmHIO.field_0x21 + (u32)((g_nmHIO.field_0x20 - g_nmHIO.field_0x21) * var_f1);
    fopMsgM_setAlpha(&field_0x97c[0]);

    if (field_0x97c[0].mUserArea == 0) {
        field_0x97c[0].mUserArea = g_nmHIO.field_0x1f;
        field_0x2908 ^= 1;
    } else {
        field_0x97c[0].mUserArea--;
    }
}

/* 80218A48-80218A84       .text _draw__7dName_cFv */
void dName_c::_draw() {
    dComIfGd_set2DOpa(&nameIn);
}

/* 80218A84-8021937C       .text screenSet__7dName_cFv */
// NONMATCHING - some reg alloc at the end
void dName_c::screenSet() {
    fopMsgM_setPaneData(&field_0x14, nameIn.NameInScr->search('cc00'));

    for (int i = 0; i < 13; i++) {
#if VERSION <= VERSION_USA
        static u32 l_Eisu[] = {
            'ena', 'enb', 'enc',
            'end', 'ene', 'enf',
            'eng', 'enh', 'eni',
            'enj', 'enk', 'enl',
            'enm',
        };
        fopMsgM_setPaneData(&eisuMojiPanes[i], nameIn.NameInScr->search(l_Eisu[i]));
#endif

        static u32 l_Kata[] = {
            'jka', 'jkk', 'jks',
            'jkt', 'jkn', 'jkh',
            'jkm', 'jky', 'jkr',
            'jkw', 'jkxa', 'jkxy',
            'jkxt',
        };
        fopMsgM_setPaneData(&kataMojiPanes[i], nameIn.NameInScr->search(l_Kata[i]));

        static u32 l_Hira[] = {
            'jha', 'jhk', 'jhs',
            'jht', 'jhn', 'jhh',
            'jhm', 'jhy', 'jhr',
            'jhw', 'jhxa', 'jhxy',
            'jhxt',
        };
        fopMsgM_setPaneData(&hiraMojiPanes[i], nameIn.NameInScr->search(l_Hira[i]));

#if VERSION <= VERSION_USA
        ((J2DTextBox*)eisuMojiPanes[i].pane)->setFont(nameIn.font);
#endif
        ((J2DTextBox*)kataMojiPanes[i].pane)->setFont(nameIn.font);
        ((J2DTextBox*)hiraMojiPanes[i].pane)->setFont(nameIn.font);

#if VERSION == VERSION_PAL
        static char str01[13][10] = {
            "A\nN\n\xC0\n\xCF\n1",
            "B\nO\n\xC1\n\xD0\n2",
            "C\nP\n\xC2\n\xD1\n3",
            "D\nQ\n\xC4\n\xD2\n4",
            "E\nR\n\xC6\n\xD3\n5",
            "F\nS\n\xC7\n\xD4\n6",
            "G\nT\n\xC8\n\xD6\n7",
            "H\nU\n\xC9\n\x8C\n8",
            "I\nV\n\xCA\n\xD9\n9",
            "J\nW\n\xCB\n\xDA\n0",
            "K\nX\n\xCC\n\xDB\n,",
            "L\nY\n\xCD\n\xDC\n.",
            "M\nZ\n\xCE\n-\n ",
        };

        static char str02[13][10] = {
            "a\nn\n\xE0\n\xEF\n1",
            "b\no\n\xE1\n\xF0\n2",
            "c\np\n\xE2\n\xF1\n3",
            "d\nq\n\xE4\n\xF2\n4",
            "e\nr\n\xE6\n\xF3\n5",
            "f\ns\n\xE7\n\xF4\n6",
            "g\nt\n\xE8\n\xF6\n7",
            "h\nu\n\xE9\n\x9C\n8",
            "i\nv\n\xEA\n\xF9\n9",
            "j\nw\n\xEB\n\xFA\n0",
            "k\nx\n\xEC\n\xFB\n,",
            "l\ny\n\xED\n\xFC\n.",
            "m\nz\n\xEE\n\xDF\n ",
        };

        ((J2DTextBox*)hiraMojiPanes[i].pane)->setString(str01[i]);
        ((J2DTextBox*)kataMojiPanes[i].pane)->setString(str02[i]);
#endif
    }

    fopMsgM_setPaneData(&titlePane, nameIn.NameInScr->search('dtle'));
    char msg[32];
    if (strcmp(dComIfGp_getStartStageName(), "Name") != 0) {
#if VERSION <= VERSION_JPN
        ((J2DTextBox*)titlePane.pane)->setString("合言葉入力");
#elif VERSION == VERSION_USA
        ((J2DTextBox*)titlePane.pane)->setString("Enter the password!");
#else
        switch (dComIfGs_getPalLanguage()) {
        case 0:
            ((J2DTextBox*)titlePane.pane)->setString("Enter the password!");
            break;
        case 1:
            ((J2DTextBox*)titlePane.pane)->setString("Paroleneingabe");
            break;
        case 2:
            ((J2DTextBox*)titlePane.pane)->setString("Saisissez le mot de passe.");
            break;
        case 3: {
            strcpy(msg, "Ingresar contrasena");
            msg[17] = 0xF1;
            ((J2DTextBox*)titlePane.pane)->setString(msg);
            break;
        }
        case 4:
            ((J2DTextBox*)titlePane.pane)->setString("Inserisci la parola d\'ordine");
            break;
        }
#endif
    } else {
        fopMsgM_messageGet(msg, 0x28);
        ((J2DTextBox*)titlePane.pane)->setString(msg);
    }

    fopMsgM_setPaneData(&hiraBtnPane, nameIn.NameInScr->search('hira'));
    ((J2DTextBox*)hiraBtnPane.pane)->setFont(nameIn.font);

    fopMsgM_setPaneData(&kanaBtnPane, nameIn.NameInScr->search('kana'));
    ((J2DTextBox*)kanaBtnPane.pane)->setFont(nameIn.font);

#if VERSION <= VERSION_USA
    fopMsgM_setPaneData(&englBtnPane, nameIn.NameInScr->search('engl'));
    ((J2DTextBox*)englBtnPane.pane)->setFont(nameIn.font);
#endif

    fopMsgM_setPaneData(&yazBtnPane, nameIn.NameInScr->search('yaz'));
    #if VERSION <= VERSION_JPN
    ((J2DTextBox*)yazBtnPane.pane)->setFont(nameIn.font);
    #endif

    fopMsgM_setPaneData(&finBtnPane, nameIn.NameInScr->search('fin'));
    ((J2DTextBox*)finBtnPane.pane)->setFont(nameIn.font);

    fopMsgM_setPaneData(&namePane, nameIn.NameInScr->search('name'));
    ((J2DTextBox*)namePane.pane)->setFont(nameIn.font);
#if VERSION == VERSION_PAL
    for (int i = 0; i < 8; i++) {}
    field_0x2ae8 = ((J2DTextBox*)finBtnPane.pane)->getStringPtr();
#endif
    ((J2DTextBox*)namePane.pane)->setCharSpace(0.0f);

    for (int i = 0; i < 320; i++) {
        nameBuffer[i] = 'A';
    }
    nameBuffer[320 - 1] = 0;
    ((J2DTextBox*)namePane.pane)->setString(nameBuffer);

    pNameTxt = ((J2DTextBox*)namePane.pane)->getStringPtr();
    *pNameTxt = 0;
    JUT_ASSERT(VERSION_SELECT(1774, 1776, 2052, 2057), pNameTxt != NULL);

    fopMsgM_setPaneData(&field_0x8d4[0], nameIn.NameInScr->search('1cu1'));
    fopMsgM_setPaneData(&field_0x8d4[1], nameIn.NameInScr->search('1cu2'));
    fopMsgM_setPaneData(&field_0x8d4[2], nameIn.NameInScr->search('4cu'));
    ((J2DTextBox*)field_0x8d4[2].pane)->setFont(nameIn.font);

    pCurTxt = ((J2DTextBox*)field_0x8d4[2].pane)->getStringPtr();
    JUT_ASSERT(VERSION_SELECT(1781, 1783, 2059, 2064), pCurTxt != NULL);

    field_0x8d4[0].mNowAlpha = g_nmHIO.field_0x17;
    field_0x8d4[1].mNowAlpha = g_nmHIO.field_0x18;

    field_0x8d4[0].mUserArea = g_nmHIO.field_0x16;
    field_0x8d4[1].mUserArea = g_nmHIO.field_0x19;
    field_0x8d4[2].mUserArea = g_nmHIO.field_0x1a;

    field_0x2909 = 0;
    field_0x2905 = 0;
    field_0x2ac8 = field_0x8d4[0].pane->getRotate();
    field_0x2acc = field_0x8d4[1].pane->getRotate();
    fopMsgM_setAlpha(&field_0x8d4[0]);
    fopMsgM_setAlpha(&field_0x8d4[1]);

    u32 var_r22 = '2cu1';
    u32 var_r27 = 'nk51';
    u32 var_r26 = 'nk41';
    u32 var_r25 = 'nk31';
    u32 var_r24 = 'nk21';
    u32 var_r23 = 'nk11';
    for (int i = 0; i < 5; i++) {
        fopMsgM_setPaneData(&field_0x97c[i], nameIn.NameInScr->search(var_r22));
        fopMsgM_setPaneData(&field_0xcfc[i], nameIn.NameInScr->search(var_r27));
        fopMsgM_setPaneData(&field_0x107c[i], nameIn.NameInScr->search(var_r26));
#if VERSION <= VERSION_USA
        fopMsgM_setPaneData(&field_0x13fc[i], nameIn.NameInScr->search(var_r25));
#endif
        fopMsgM_setPaneData(&field_0x177c[i], nameIn.NameInScr->search(var_r24));
        fopMsgM_setPaneData(&field_0x1afc[i], nameIn.NameInScr->search(var_r23));

        static u32 l_NameNt[] = {'d007', 'd008', 'd009', 'd010', 'd011'};
        fopMsgM_setPaneData(&field_0x1c84[i], nameIn.NameInScr->search(l_NameNt[i]));

        static u32 l_MenuNmB[] = {'c007', 'c008', 'c009', 'c010', 'c011'};
        fopMsgM_setPaneData(&field_0x20e4[i], nameIn.NameInScr->search(l_MenuNmB[i]));

        var_r22++;
        var_r27++;
        var_r26++;
        var_r25++;
        var_r24++;
        var_r23++;
    }

    for (int i = 0; i < 10; i++) {
        static u32 l_endB[] = {
            'n501', 'n502', 'n503', 'n504', 'n505',
            'n506', 'n507', 'n508', 'n509', 'n510',
        };
        fopMsgM_setPaneData(&field_0xacc[i], nameIn.NameInScr->search(l_endB[i]));

        static u32 l_ArwB[] = {
            'n401', 'n402', 'n403', 'n404', 'n405',
            'n406', 'n407', 'n408', 'n409', 'n410',
        };
        fopMsgM_setPaneData(&field_0xe4c[i], nameIn.NameInScr->search(l_ArwB[i]));

        static u32 l_EisuB[] = {
            'n301', 'n302', 'n303', 'n304', 'n305',
            'n306', 'n307', 'n308', 'n309', 'n310',
        };

#if VERSION <= VERSION_USA
        fopMsgM_setPaneData(&field_0x11cc[i], nameIn.NameInScr->search(l_EisuB[i]));
#endif

        static u32 l_KataB[] = {
            'n201', 'n202', 'n203', 'n204', 'n205',
            'n206', 'n207', 'n208', 'n209', 'n210',
        };
        fopMsgM_setPaneData(&field_0x154c[i], nameIn.NameInScr->search(l_KataB[i]));

        static u32 l_HiraB[] = {
            'n101', 'n102', 'n103', 'n104', 'n105',
            'n106', 'n107', 'n108', 'n109', 'n110',
        };
        fopMsgM_setPaneData(&field_0x18cc[i], nameIn.NameInScr->search(l_HiraB[i]));
    }

    fopMsgM_setPaneData(&field_0x1c4c, nameIn.NameInScr->search('3cu1'));
    fopMsgM_paneTrans(&field_0x1c4c, g_nmHIO.field_0x28, g_nmHIO.field_0x26);
    field_0x2906 = 0;
    field_0x1c4c.mUserArea = g_nmHIO.field_0x1b;
    field_0x1c4c.mNowAlpha = g_nmHIO.field_0x1d;
    fopMsgM_setAlpha(&field_0x1c4c);

    u32 var_r21 = 'd000';
    u32 var_r22_2 = 'dk00';
    u32 var_r23_2 = 'c000';
    u32 var_r24_2 = 'ck00';
    for (int i = 0; i < 7; i++) {
        fopMsgM_setPaneData(&field_0x1d9c[i], nameIn.NameInScr->search(var_r21));
        fopMsgM_setPaneData(&field_0x1f24[i], nameIn.NameInScr->search(var_r22_2));
        fopMsgM_setPaneData(&field_0x21fc[i], nameIn.NameInScr->search(var_r23_2));
        fopMsgM_setPaneData(&field_0x2384[i], nameIn.NameInScr->search(var_r24_2));

        var_r21++;
        var_r22_2++;
        var_r23_2++;
        var_r24_2++;
    }

    u32 var_r21_2 = 'b000';
    u32 var_r22_3 = 'bk00';
    for (int i = 0; i < 9; i++) {
        fopMsgM_setPaneData(&field_0x250c[i], nameIn.NameInScr->search(var_r21_2));
        fopMsgM_setPaneData(&field_0x2704[i], nameIn.NameInScr->search(var_r22_3));

        var_r21_2++;
        var_r22_3++;
    }
}

/* 8021937C-8021960C       .text paneTransInit__7dName_cFv */
void dName_c::paneTransInit() {
    paneTransTimer = 0;

    PaneTranceBase0(paneTransTimer, g_nmHIO.field_0x8, g_nmHIO.field_0x46, 0.0f, 1, 0);
    PaneTranceTitle(paneTransTimer, g_nmHIO.field_0x6, g_nmHIO.field_0x42, 0.0f, 1, 0);
    PaneTranceName(paneTransTimer, g_nmHIO.field_0x7, g_nmHIO.field_0x44, 0.0f, 1, 0);
    PaneTranceBase(paneTransTimer, g_nmHIO.field_0x8, g_nmHIO.field_0x46, 0.0f, 1, 0);
    PaneTranceKata(paneTransTimer, g_nmHIO.field_0x9, g_nmHIO.field_0x48, 0.0f, 1, 0);
    PaneTranceHira(paneTransTimer, g_nmHIO.field_0xa, g_nmHIO.field_0x48, 0.0f, 1, 0);
#if VERSION <= VERSION_USA
    PaneTranceEisu(paneTransTimer, g_nmHIO.field_0xb, g_nmHIO.field_0x48, 0.0f, 1, 0);
#endif
    PaneTranceArrow(paneTransTimer, g_nmHIO.field_0xc, g_nmHIO.field_0x48, 0.0f, 1, 0);
    PaneTranceEnd(paneTransTimer, g_nmHIO.field_0xd, g_nmHIO.field_0x48, 0.0f, 1, 0);
}

/* 8021960C-802197A0       .text PaneTranceTitle__7dName_cFsUcffUci */
int dName_c::PaneTranceTitle(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&titlePane, 0.0f, param_2 + temp_f0);

    for (i = 0; i < 5; i++) {
        fopMsgM_paneTrans(&field_0x20e4[i], 0.0f, param_2 + temp_f0);
    }

    fopMsgM_paneTrans(&field_0x21fc[0], 0.0f, param_2 + temp_f0);
    fopMsgM_paneTrans(&field_0x2384[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&titlePane, ratio);
        fopMsgM_setAlpha(&titlePane);

        for (i = 0; i < 5; i++) {
            fopMsgM_setNowAlpha(&field_0x20e4[i], ratio);
            fopMsgM_setAlpha(&field_0x20e4[i]);
        }

        fopMsgM_setNowAlpha(&field_0x21fc[0], ratio);
        fopMsgM_setNowAlpha(&field_0x2384[0], ratio);
        fopMsgM_setAlpha(&field_0x21fc[0]);
        fopMsgM_setAlpha(&field_0x2384[0]);
    }

    return 0;
}

/* 802197A0-802199F4       .text PaneTranceName__7dName_cFsUcffUci */
int dName_c::PaneTranceName(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&namePane, param_2 + temp_f0, 0.0f);
    fopMsgM_paneTrans(&field_0x1f24[0], param_2 + temp_f0, 0.0f);
    fopMsgM_paneTrans(&field_0x1c4c, (g_nmHIO.field_0x28 + (param_2 + temp_f0)) + (curPos * g_nmHIO.field_0x1c), g_nmHIO.field_0x26);

    for (i = 0; i < 5; i++) {
        fopMsgM_paneTrans(&field_0x1c84[i], param_2 + temp_f0, 0.0f);
    }

    for (i = 0; i < 7; i++) {
        fopMsgM_paneTrans(&field_0x1d9c[i], param_2 + temp_f0, 0.0f);
    }

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&namePane, ratio);
        fopMsgM_setNowAlpha(&field_0x1f24[0], ratio);
        fopMsgM_setAlpha(&namePane);
        fopMsgM_setAlpha(&field_0x1f24[0]);

        fopMsgM_setNowAlpha(&field_0x1c4c, ratio);
        fopMsgM_setAlpha(&field_0x1c4c);

        for (i = 0; i < 5; i++) {
            fopMsgM_setNowAlpha(&field_0x1c84[i], ratio);
            fopMsgM_setAlpha(&field_0x1c84[i]);
        }

        for (i = 0; i < 7; i++) {
            fopMsgM_setNowAlpha(&field_0x1d9c[i], ratio);
            fopMsgM_setAlpha(&field_0x1d9c[i]);
        }
    }

    return 0;
}

/* 802199F4-80219ADC       .text PaneTranceBase0__7dName_cFsUcffUci */
int dName_c::PaneTranceBase0(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x14, 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&field_0x14, ratio);
        fopMsgM_setAlpha(&field_0x14);
    }

    return 0;
}

/* 80219ADC-80219D04       .text PaneTranceBase__7dName_cFsUcffUci */
int dName_c::PaneTranceBase(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    fopMsgM_pane_class* pane;
    switch (mojiSet) {
    case MOJI_HIRA:
        pane = hiraMojiPanes;
        break;
    case MOJI_KATA:
        pane = kataMojiPanes;
        break;
#if VERSION <= VERSION_USA
    case MOJI_EIGO:
        pane = eisuMojiPanes;
        break;
#endif
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x250c[0], 0.0f, param_2 + temp_f0);
    fopMsgM_paneTrans(&field_0x2704[0], 0.0f, param_2 + temp_f0);

    for (i = 0; i < 3; i++) {
        fopMsgM_paneTrans(&field_0x8d4[i], 0.0f, param_2 + temp_f0);
    }

    for (i = 0; i < 13; i++) {
        fopMsgM_paneTrans(&hiraMojiPanes[i], 0.0f, param_2 + temp_f0);
        fopMsgM_paneTrans(&kataMojiPanes[i], 0.0f, param_2 + temp_f0);
#if VERSION <= VERSION_USA
        fopMsgM_paneTrans(&eisuMojiPanes[i], 0.0f, param_2 + temp_f0);
#endif
    }

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&field_0x250c[0], ratio);
        fopMsgM_setNowAlpha(&field_0x2704[0], ratio);
        fopMsgM_setAlpha(&field_0x250c[0]);
        fopMsgM_setAlpha(&field_0x2704[0]);

        for (i = 0; i < 3; i++) {
            fopMsgM_setNowAlpha(&field_0x8d4[i], ratio);
            fopMsgM_setAlpha(&field_0x8d4[i]);
        }

        for (i = 0; i < 13; i++) {
            fopMsgM_setNowAlpha(&pane[i], ratio);
            fopMsgM_setAlpha(&pane[i]);
        }
    }

    return 0;
}

/* 80219D04-80219E14       .text PaneTranceHira__7dName_cFsUcffUci */
int dName_c::PaneTranceHira(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x1afc[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&hiraBtnPane, ratio);
        fopMsgM_setNowAlpha(&field_0x1afc[0], ratio);
        fopMsgM_setNowAlpha(&field_0x18cc[0], ratio);
        fopMsgM_setAlpha(&hiraBtnPane);
        fopMsgM_setAlpha(&field_0x1afc[0]);
        fopMsgM_setAlpha(&field_0x18cc[0]);
    }

    return 0;
}

/* 80219E14-80219F24       .text PaneTranceKata__7dName_cFsUcffUci */
int dName_c::PaneTranceKata(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x177c[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&kanaBtnPane, ratio);
        fopMsgM_setNowAlpha(&field_0x154c[0], ratio);
        fopMsgM_setNowAlpha(&field_0x177c[0], ratio);
        fopMsgM_setAlpha(&kanaBtnPane);
        fopMsgM_setAlpha(&field_0x154c[0]);
        fopMsgM_setAlpha(&field_0x177c[0]);
    }

    return 0;
}

/* 80219F24-8021A034       .text PaneTranceEisu__7dName_cFsUcffUci */
int dName_c::PaneTranceEisu(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x13fc[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&englBtnPane, ratio);
        fopMsgM_setNowAlpha(&field_0x11cc[0], ratio);
        fopMsgM_setNowAlpha(&field_0x13fc[0], ratio);
        fopMsgM_setAlpha(&englBtnPane);
        fopMsgM_setAlpha(&field_0x11cc[0]);
        fopMsgM_setAlpha(&field_0x13fc[0]);
    }

    return 0;
}

/* 8021A034-8021A144       .text PaneTranceArrow__7dName_cFsUcffUci */
int dName_c::PaneTranceArrow(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0x107c[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&yazBtnPane, ratio);
        fopMsgM_setNowAlpha(&field_0xe4c[0], ratio);
        fopMsgM_setNowAlpha(&field_0x107c[0], ratio);
        fopMsgM_setAlpha(&yazBtnPane);
        fopMsgM_setAlpha(&field_0xe4c[0]);
        fopMsgM_setAlpha(&field_0x107c[0]);
    }

    return 0;
}

/* 8021A144-8021A254       .text PaneTranceEnd__7dName_cFsUcffUci */
int dName_c::PaneTranceEnd(s16 i_value, u8 i_max, f32 param_2, f32 param_3, u8 i_mode, int param_5) {
    int i;

    if (i_value < 0) {
        return 0;
    }

    if (i_value > i_max) {
        return 1;
    }

    f32 ratio = fopMsgM_valueIncrease(i_max, i_value, i_mode);
    f32 temp_f0 = ratio * (param_3 - param_2);
    fopMsgM_paneTrans(&field_0xcfc[0], 0.0f, param_2 + temp_f0);

    if (param_5 != 2) {
        if (param_5 == 1) {
            ratio = 1.0f - ratio;
        }

        fopMsgM_setNowAlpha(&finBtnPane, ratio);
        fopMsgM_setNowAlpha(&field_0xacc[0], ratio);
        fopMsgM_setNowAlpha(&field_0xcfc[0], ratio);
        fopMsgM_setAlpha(&finBtnPane);
        fopMsgM_setAlpha(&field_0xacc[0]);
        fopMsgM_setAlpha(&field_0xcfc[0]);
    }

    return 0;
}

/* 8021A254-8021A43C       .text displayInit__7dName_cFv */
void dName_c::displayInit() {
    int i;

    field_0x290d = 1;

    for (i = 0; i < 5; i++) {
        field_0x2ab0[i][2] = 0;
    }

    charColumn = 0;
    charRow = 0;
    field_0x2ab0[0][0] = 0;
    field_0x2ab0[0][1] = 0;
    field_0x2ab0[0][2] = 1;
    curPos = 0;

    *pNameTxt = 0;
    
    for (i = 0; i < 8; i++) {
        chrInfo[i].column = 7;
        chrInfo[i].row = 1;
#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
        chrInfo[i].set = MOJI_HIRA;
#else
        chrInfo[i].set = MOJI_EIGO;
#endif
        chrInfo[i].field_0x3 = 1;
#if VERSION <= VERSION_JPN
        chrInfo[i].character = '\x81\x40';
#else
        chrInfo[i].character = ' ';
#endif
    }

    inputCompleteSound = JA_SE_TALK_WIN_CLOSE;

    if (strcmp(dComIfGp_getStartStageName(), "Name") == 0) {
        field_0x14.pane->hide();
        if (nextNameStr[0] != 0) {
            NameStrSet();
        }

#if VERSION == VERSION_PAL
        char msg[32];
        fopMsgM_messageGet(msg, 0x28);
        ((J2DTextBox*)titlePane.pane)->setString(msg);
#endif

        inputCompleteSound = JA_SE_MSEL_ENTER_GAME;
    }

#if VERSION == VERSION_PAL
    switch (dComIfGs_getPalLanguage()) {
    case 0:
        strcpy(field_0x2ae8, "END");
        break;
    case 1:
        strcpy(field_0x2ae8, "O.K.");
        break;
    case 2:
        strcpy(field_0x2ae8, "FIN");
        break;
    case 3:
        strcpy(field_0x2ae8, "FIN");
        break;
    case 4:
        strcpy(field_0x2ae8, "FINE");
        break;
    }
#endif

#if VERSION <= VERSION_JPN || VERSION == VERSION_PAL
    selMenu = MENU_HIRA;
    mojiSet = MOJI_HIRA;
#else
    selMenu = MENU_BACKSPACE;
    mojiSet = MOJI_EIGO;

    field_0x1afc[0].pane->hide();
    field_0x177c[0].pane->hide();
    field_0x13fc[0].pane->hide();
#endif

    selProc = PROC_MOJI_SELECT;

    for (i = 0; i < 13; i++) {
        fopMsgM_setInitAlpha(&hiraMojiPanes[i]);
#if VERSION <= VERSION_USA
        fopMsgM_setInitAlpha(&eisuMojiPanes[i]);
#endif
        fopMsgM_setInitAlpha(&kataMojiPanes[i]);
        fopMsgM_setAlpha(&hiraMojiPanes[i]);
#if VERSION <= VERSION_USA
        fopMsgM_setAlpha(&eisuMojiPanes[i]);
#endif
        fopMsgM_setAlpha(&kataMojiPanes[i]);

#if VERSION <= VERSION_JPN
        hiraMojiPanes[i].pane->show();
        eisuMojiPanes[i].pane->hide();
        kataMojiPanes[i].pane->hide();
#elif VERSION == VERSION_USA
        hiraMojiPanes[i].pane->hide();
        eisuMojiPanes[i].pane->show();
        kataMojiPanes[i].pane->hide();
#else
        hiraMojiPanes[i].pane->show();
        kataMojiPanes[i].pane->hide();
#endif
    }

    field_0x97c[0].pane->hide();

    for (i = 0; i < 3; i++) {
        field_0x8d4[i].pane->show();
    }

    selectCursorTxtChange();
    isInputEnd_ = 0;
}

/* 8021A43C-8021A658       .text NameStrSet__7dName_cFv */
void dName_c::NameStrSet() {
    char* moji = nextNameStr;

    int i = 0;
    int j;
    BOOL found;
    while (*moji != 0) {
#if VERSION == VERSION_PAL
        chrInfo[i].character = *moji;

        found = false;
        for (j = 0; j < 13; j++) {
            if (found)
                break;

            char* upperMoji = ((J2DTextBox*)hiraMojiPanes[j].pane)->getStringPtr();
            char* lowerMoji = ((J2DTextBox*)kataMojiPanes[j].pane)->getStringPtr();

            int row = 0;
            while (*upperMoji != 0) {
                if (*upperMoji == '\n') {
                    upperMoji++;
                    continue;
                }

                if (*upperMoji == chrInfo[i].character) {
                    chrInfo[i].column = j;
                    chrInfo[i].row = row;
                    chrInfo[i].set = MOJI_HIRA;
                    found = true;
                    break;
                }

                row++;
                upperMoji++;
            }

            row = 0;
            while (*lowerMoji != 0) {
                if (*lowerMoji == '\n') {
                    lowerMoji++;
                    continue;
                }

                if (*lowerMoji == chrInfo[i].character) {
                    chrInfo[i].column = j;
                    chrInfo[i].row = row;
                    chrInfo[i].set = MOJI_KATA;
                    found = true;
                    break;
                }

                row++;
                lowerMoji++;
            }
        }
        moji++;
        i++;
#else
        if (*(u8*)moji >> 4 == 8 || *(u8*)moji >> 4 == 9) {
            chrInfo[i].character = *(u16*)moji;

            found = false;
            for (j = 0; j < 13; j++) {
                if (found)
                    break;

                char* hiraMoji = ((J2DTextBox*)hiraMojiPanes[j].pane)->getStringPtr();
                char* kataMoji = ((J2DTextBox*)kataMojiPanes[j].pane)->getStringPtr();

                int row = 0;
                while (*hiraMoji != 0) {
                    if (*hiraMoji == '\n') {
                        hiraMoji++;
                        continue;
                    }

                    if (*(u16*)hiraMoji == chrInfo[i].character) {
                        chrInfo[i].column = j;
                        chrInfo[i].row = row;
                        chrInfo[i].set = MOJI_HIRA;
                        found = true;
                        break;
                    }

                    row++;
                    hiraMoji += 2;
                }

                row = 0;
                while (*kataMoji != 0) {
                    if (*kataMoji == '\n') {
                        kataMoji++;
                        continue;
                    }

                    if (*(u16*)kataMoji == chrInfo[i].character) {
                        chrInfo[i].column = j;
                        chrInfo[i].row = row;
                        chrInfo[i].set = MOJI_KATA;
                        found = true;
                        break;
                    }

                    row++;
                    kataMoji += 2;
                }
            }
            moji += 2;
            i++;
        } else {
            chrInfo[i].character = *moji;
            chrInfo[i].set = MOJI_EIGO;

            found = false;
            for (j = 0; j < 13; j++) {
                if (found)
                    break;

                char* eisuMoji = ((J2DTextBox*)eisuMojiPanes[j].pane)->getStringPtr();

                int row = 0;
                while (*eisuMoji != 0) {
                    if (*eisuMoji == '\n') {
                        eisuMoji++;
                        continue;
                    }

                    if (*eisuMoji == chrInfo[i].character) {
                        chrInfo[i].column = j;
                        chrInfo[i].row = row;
                        found = true;
                        break;
                    }

                    row++;
                    eisuMoji++;
                }
            }
            moji++;
            i++;
        }
#endif
    }

    curPos = i;
    setNameText();
    nameCursorMove();
}

/* 8021A658-8021A6BC       .text draw__14dDlst_NameIN_cFv */
void dDlst_NameIN_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    NameInScr->draw(0.0f, 0.0f, graf);
}
