#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_menu_item.h"
#include "d/d_2dnumber.h"
#include "d/d_item_data.h"
#include "d/d_lib.h"
#include "d/d_meter.h"
#include "d/d_menu_save.h"
#include "m_Do/m_Do_controller_pad.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"

dMi_HIO_c g_miHIO;

/* 801C7B4C-801C7C7C       .text __ct__9dMi_HIO_cFv */
dMi_HIO_c::dMi_HIO_c() {
    field_0x08 = 0.8f;
    field_0x0C = 15;

    for (int i = 0; i < ARR_SIZE; i++) {
        arr_0x0E[i] = 0;
        arr_0x1A[i] = 10;
    }

    field_0x18 = 0;
    field_0x24 = 1;
    field_0x26 = -100;
    field_0x28 = -100;
    field_0x2A = -45;
    field_0x2C = 50;
    field_0x2E = 30;
    field_0x30 = -3;
    field_0x32 = 10;
    field_0x34 = 7;
    field_0x36 = 14;
    field_0x38 = 5;
    field_0x3A = 12;
    field_0x3C = 10;
    field_0x40 = 320;
    field_0x42 = 240;
    field_0x3E = 200;
    field_0x46 = 0;
    field_0x48 = 20;
    field_0x44 = -120;

    // Light Yellow-Green
    mClothColor.r = 0xE3;
    mClothColor.g = 0xFF;
    mClothColor.b = 0xB3;
    mClothColor.a = 0xDC;

    // Transparent
    mShadowColor.r = 0x00;
    mShadowColor.g = 0x00;
    mShadowColor.b = 0x00;
    mShadowColor.a = 0x00;

    field_0x5C = 130;

    mBlackColor.set(0x00, 0x00, 0x00, 0xFF); // Black
    // mWhiteColor stays as default.
}

/* 801C7C7C-801C7DC4       .text initialize__12dMenu_Item_cFv */
void dMenu_Item_c::initialize() {
    itemBitCheck(true);
    timer = 0;

    field_0x858.mUserArea = 10;
    field_0xa18[0].mUserArea = 0;
    field_0x2422 = 0;

    noteInit();
    outFontInit();
    checkMove();
    itemNumberSet();

    field_0x970.mInitAlpha = g_miHIO.field_0x5C;
    field_0x23fa = 0;
    field_0x23fc = 0;

    ((J2DWindow*)field_0x14d0.pane)->getContentsColor(field_0x2320);

    field_0x231c->insertChild(field_0x1460.pane, field_0xa18[3].pane);
    field_0x231c->insertChild(field_0xa18[3].pane, field_0xa18[2].pane);
    field_0x231c->insertChild(field_0xa18[2].pane, field_0xa18[1].pane);
    field_0x231c->insertChild(field_0xa18[1].pane, field_0xa18[0].pane);
}

/* 801C7DC4-801C8724       .text screenSet__12dMenu_Item_cFv */
// NONMATCHING
void dMenu_Item_c::screenSet() {
    field_0x231c = scrn->search('ROOT');

    static const u32 l_ft[] = {
        'ft00', 'ft01', 'ft02', 'ft03',
        'ft04', 'ft05', 'ft06', 'ft07',
        'ft08', 'ft09', 'ft10', 'ft11',
        'ft12', 'ft13', 'ft14',
    };

    static const u32 l_no[] = {
        'no23', 'no13',
        'no22', 'no12',
        'no21', 'no11',
    };

    static const u32 l_car[] = {
        'car1', 'car2', 'car3', 'car4',
    };

    static const u32 l_sin_01[] = {
        '2401', '2501', '2801', '2601',
        '2701', '2901', '3001', '3101',
    };

    static const u32 l_sin_10[] = {
        '2410', '2510', '2810', '2610',
        '2710', '2910', '3010', '3110',
    };

    static const u32 l_sit[] = {
        'it21', 'it22', 'it25', 'it23',
        'it24', 'it26', 'it27', 'it28',
        'it29',
    };

    static const u32 l_sik[] = {
        'ik21', 'ik22', 'ik25', 'ik23',
        'ik24', 'ik26', 'ik27', 'ik28',
        'ik29',
    };

    static const u32 l_sb[] = {
        'sb00', 'sb01', 'sb02', 'sb03',
        'sb04', 'sb05', 'sb06', 'sb07',
        'sb08',
    };

    static const u32 l_it[] = {
        'it00', 'it01', 'it02', 'it03', 'it04',
        'it05', 'it06', 'it07', 'it08', 'it09',
        'it10', 'it11', 'it12', 'it13', 'it14',
        'it15', 'it16', 'it17', 'it18', 'it19',
        'it20',
    };

    static const u32 l_ik[] = {
        'ik00', 'ik01', 'ik02', 'ik03', 'ik04',
        'ik05', 'ik06', 'ik07', 'ik08', 'ik09',
        'ik10', 'ik11', 'ik12', 'ik13', 'ik14',
        'ik15', 'ik16', 'ik17', 'ik18', 'ik19',
        'ik20',
    };

    static const u32 l_ip[] = {
        'ip01', 'ip03', 'ip05',
        'ip07', 'ip09', 'ip11',
    };

    static const u32 l_fd[] = {
        'fd00', 'fd01', 'fd02', 'fd03',
        'fd04', 'fd05', 'fd06', 'fd07',
        'fd08', 'fd09', 'fd10', 'fd11',
        'fd12', 'fd13', 'fd14',
    };

    fopMsgM_setPaneData(&field_0x8, scrn, 'ft15');
    fopMsgM_setPaneData(&field_0x40, scrn, 'ft16');
    fopMsgM_setPaneData(&field_0x78, scrn, 'ft17');

    for (int i = 0; i < 15; i++) {
        fopMsgM_setPaneData(&field_0xb0[i], scrn->search(l_ft[i]));
        fopMsgM_setPaneData(&field_0x3f8[i], scrn->search(l_fd[i]));

        field_0xb0[i].mUserArea = -1;
    }

    fopMsgM_setPaneData(&field_0x740, scrn, 'str0');
    fopMsgM_setPaneData(&field_0x778, scrn, 'st00');
    if (dComIfGs_getOptRuby()) {
        fopMsgM_paneTrans(&field_0x778, 0.0f, -4.0f);
    }

    fopMsgM_setPaneData(&field_0x7b0, scrn, 'nt00');
    fopMsgM_setPaneData(&field_0x7e8, scrn, 'nk00');
    fopMsgM_setPaneData(&field_0x820, scrn, 'no11');
    field_0x820.mUserArea = field_0x820.pane->getRotate();

    ((J2DTextBox*)field_0x740.pane)->setFont(font[1]);
    ((J2DTextBox*)field_0x778.pane)->setFont(font[0]);

    ((J2DTextBox*)field_0x740.pane)->setWhite(0xFFFFFFFF);
    ((J2DTextBox*)field_0x740.pane)->setCharColor(0x000000FF);
    ((J2DTextBox*)field_0x740.pane)->setGradColor(0x000000FF);

    ((J2DTextBox*)field_0x778.pane)->setWhite(0xFFFFFFFF);
    ((J2DTextBox*)field_0x778.pane)->setCharColor(0x000000FF);
    ((J2DTextBox*)field_0x778.pane)->setGradColor(0x000000FF);

    fopMsgM_setPaneData(&field_0x858, scrn, 'wd');
    field_0x858.pane->show();
    ((J2DTextBox*)field_0x858.pane)->setFont(font[0]);
    outFont->setPane(font[0], &field_0x858, &field_0x8, &field_0x40, &field_0x78);

    fopMsgM_setPaneData(&field_0x890[0], scrn, 'nm00');
    ((J2DTextBox*)field_0x890[0].pane)->setFont(font[0]);

    fopMsgM_setPaneData(&field_0x890[1], scrn, 'nm01');
    ((J2DTextBox*)field_0x890[1].pane)->setFont(font[0]);

    fopMsgM_setPaneData(&field_0x900, scrn, 'itnm');
    fopMsgM_setPaneData(&field_0x938, scrn, 'itnk');
    fopMsgM_setPaneData(&field_0x970, scrn, 'msk0');
    fopMsgM_setPaneData(&field_0x9a8, scrn, 'tl00');
    fopMsgM_setPaneData(&field_0x9e0, scrn, 'tk00');

    for (int i = 0; i < 4; i++) {
        fopMsgM_setPaneData(&field_0xa18[i], scrn, l_car[i]);
    }

    for (int i = 0; i < 8; i++) {
        fopMsgM_setPaneData(&field_0xaf8[i], scrn, l_sin_01[i]);
        fopMsgM_setPaneData(&field_0xcb8[i], scrn, l_sin_10[i]);
        fopMsgM_setPaneData(&field_0xe78[i], scrn, l_sit[i]);
        fopMsgM_setPaneData(&field_0x1070[i], scrn, l_sik[i]);
    }

    fopMsgM_setPaneData(&field_0x1038, scrn, 'it29');
    fopMsgM_setPaneData(&field_0x1230, scrn, 'ik29');

    for (int i = 0; i < 9; i++) {
        fopMsgM_setPaneData(&field_0x1268[i], scrn, l_sb[i]);
    }

    fopMsgM_setPaneData(&field_0x1460, scrn, 'blak');
    fopMsgM_setPaneData(&field_0x1498, scrn, 'wdsv');
    fopMsgM_setPaneData(&field_0x14d0, scrn, 'wk01');
    fopMsgM_setPaneData(&field_0x1508, scrn, 'wk00');
    fopMsgM_setPaneData(&field_0x1540, scrn, '0301');
    fopMsgM_setPaneData(&field_0x1578, scrn, '1301');
    fopMsgM_setPaneData(&field_0x15b0, scrn, '1310');
    fopMsgM_setPaneData(&field_0x15e8, scrn, '1401');
    fopMsgM_setPaneData(&field_0x1620, scrn, '1410');

    for (int i = 0; i < 21; i++) {
        fopMsgM_setPaneData(&field_0x1658[i], scrn, l_it[i]);
        fopMsgM_setPaneData(&field_0x1af0[i], scrn, l_ik[i]);
    }

    fopMsgM_setPaneData(&field_0x1f88[0], scrn, 'bwl1');
    fopMsgM_setPaneData(&field_0x1f88[1], scrn, 'bwl2');
    fopMsgM_setPaneData(&field_0x1f88[2], scrn, 'bwl3');
    field_0x1f88[0].pane->hide();
    field_0x1f88[1].pane->hide();
    field_0x1f88[2].pane->hide();

    fopMsgM_setPaneData(&field_0x2030[0], scrn, 'chk1');
    fopMsgM_setPaneData(&field_0x2030[1], scrn, 'chk2');
    fopMsgM_setPaneData(&field_0x2030[2], scrn, 'chk3');

    for (int i = 0; i < 6; i++) {
        fopMsgM_setPaneData(&field_0x20d8[i], scrn, l_ip[i]);
    }

    fopMsgM_setPaneData(&field_0x2228, scrn, 'cc35');
    fopMsgM_setPaneData(&field_0x2260, scrn, 'cc22');
    fopMsgM_setPaneData(&field_0x2298, scrn, 'cc11');
    fopMsgM_setPaneData(&field_0x22d0, scrn, 'cc00');

    #if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() != 0) {
        char timg_name[20];
        sprintf(timg_name, "title_item_%d.bti", dComIfGs_getPalLanguage());
        JKRReadTypeResource(field_0x23bc_pal, 0x1000, 'TIMG', timg_name, archive);
        ((J2DPicture*)scrn->search('tlit'))->changeTexture(field_0x23bc_pal, 0);

        sprintf(timg_name, "word_save2_%d.bti", dComIfGs_getPalLanguage());
        JKRReadTypeResource(field_0x23b8_pal, 0xC00, 'TIMG', timg_name, archive);
        ((J2DPicture*)scrn->search('wdsv'))->changeTexture(field_0x23b8_pal, 0);
    }
    #endif

    for (int i = 0; i < 21; i++) {
        u8 item = dComIfGs_getItem(i);
        if (item != dItemNo_NONE_e) {
            if (item == dItemNo_MAGIC_ARROW_e) {
                field_0x1f88[0].pane->show();
                field_0x1f88[1].pane->show();
                field_0x1f88[2].pane->hide();
                item = dItemNo_BOW_e;
            } else if (item == dItemNo_LIGHT_ARROW_e) {
                field_0x1f88[0].pane->show();
                field_0x1f88[1].pane->show();
                field_0x1f88[2].pane->show();
                item = dItemNo_BOW_e;
            }

            JKRReadTypeResource(itemTexBuffer[i], 0xC00, 'TIMG', dItem_data::getTexture(item), dComIfGp_getItemIconArchive());
            DCStoreRangeNoSync(itemTexBuffer[i], 0xC00);

            ((J2DPicture*)field_0x1658[i].pane)->changeTexture(itemTexBuffer[i], 0);
            ((J2DPicture*)field_0x1af0[i].pane)->changeTexture(itemTexBuffer[i], 0);
        }
    }

    for (int i = 0; i < 8; i++) {
        u8 item = dComIfGs_getItemBeast((u8)i);
        if (item != dItemNo_NONE_e) {
            JKRReadTypeResource(subItemTexBuffer[i], 0xC00, 'TIMG', dItem_data::getTexture(item), dComIfGp_getItemIconArchive());
            DCStoreRangeNoSync(subItemTexBuffer[i], 0xC00);

            ((J2DPicture*)field_0xe78[i].pane)->changeTexture(subItemTexBuffer[i], 0);
            ((J2DPicture*)field_0x1070[i].pane)->changeTexture(subItemTexBuffer[i], 0);
        }
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() != 0) {
        char timg_name[20];
        sprintf(timg_name, "cover_return_%d.bti", dComIfGs_getPalLanguage());
        JKRReadTypeResource(field_0x23b4, 0xC00, 'TIMG', timg_name, dComIfGp_getItemIconArchive());
    } else
#endif
    {
        JKRReadTypeResource(field_0x23b4, 0xC00, 'TIMG', "cover_return.bti", dComIfGp_getItemIconArchive());
        DCStoreRangeNoSync(field_0x23b4, 0xC00);
    }

    ((J2DPicture*)field_0x1038.pane)->changeTexture(field_0x23b4, 0);
    ((J2DPicture*)field_0x1230.pane)->changeTexture(field_0x23b4, 0);
}

/* 801C8724-801C8B14       .text cursorAnime__12dMenu_Item_cFv */
void dMenu_Item_c::cursorAnime() {
    u8 temp_r5 = nowItem;
    if (temp_r5 == 21) {
        field_0xa18[0].mPosCenterOrig.x = field_0x1498.mPosCenter.x - field_0x1498.mSize.x / 2;
        field_0xa18[0].mPosCenterOrig.y = field_0x1498.mPosCenter.y + field_0x1498.mSize.y / 2;
        field_0xa18[1].mPosCenterOrig.x = field_0x1498.mPosCenter.x + field_0x1498.mSize.x / 2;
        field_0xa18[1].mPosCenterOrig.y = field_0x1498.mPosCenter.y + field_0x1498.mSize.y / 2;
        field_0xa18[2].mPosCenterOrig.x = field_0x1498.mPosCenter.x - field_0x1498.mSize.x / 2;
        field_0xa18[2].mPosCenterOrig.y = field_0x1498.mPosCenter.y - field_0x1498.mSize.y / 2;
        field_0xa18[3].mPosCenterOrig.x = field_0x1498.mPosCenter.x + field_0x1498.mSize.x / 2;
        field_0xa18[3].mPosCenterOrig.y = field_0x1498.mPosCenter.y - field_0x1498.mSize.y / 2;
    } else if (temp_r5 >= 24) {
        if (temp_r5 == 0xFF) {
            temp_r5 = 8;
        } else {
            temp_r5 = temp_r5 - field_0x2400;
        }

        for (int i = 0; i < 4; i++) {
            field_0xa18[i].mPosCenterOrig.x = field_0xe78[temp_r5].mPosCenter.x + field_0x23c0[i];
            field_0xa18[i].mPosCenterOrig.y = field_0xe78[temp_r5].mPosCenter.y + field_0x23d0[i];
        }
    } else {
        for (int i = 0; i < 4; i++) {
            field_0xa18[i].mPosCenterOrig.x = field_0x1658[temp_r5].mPosCenter.x + field_0x23c0[i];
            field_0xa18[i].mPosCenterOrig.y = field_0x1658[temp_r5].mPosCenter.y + field_0x23d0[i];
        }
    }

    s16 var_r30;
    s16 var_r29;
    if (field_0xa18[0].mUserArea < g_miHIO.field_0x32) {
        for (int i = 0; i < 4; i++) {
            ((J2DPicture*)field_0xa18[i].pane)->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
        }

        var_r30 = g_miHIO.field_0x34;
        var_r29 = g_miHIO.field_0x34;
    } else if (field_0xa18[0].mUserArea < g_miHIO.field_0x32 * 2) {
        for (int i = 0; i < 4; i++) {
            ((J2DPicture*)field_0xa18[i].pane)->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        }

        var_r30 = g_miHIO.field_0x36;
        var_r29 = g_miHIO.field_0x36;
    }

    fopMsgM_paneTrans(&field_0xa18[0], -var_r30, var_r29);
    fopMsgM_paneTrans(&field_0xa18[1], var_r30, var_r29);
    fopMsgM_paneTrans(&field_0xa18[2], -var_r30, -var_r29);
    fopMsgM_paneTrans(&field_0xa18[3], var_r30, -var_r29);

    field_0xa18[0].mUserArea++;
    if (field_0xa18[0].mUserArea >= g_miHIO.field_0x32 * 2) {
        field_0xa18[0].mUserArea = 0;
    }
}

/* 801C8B14-801C8CA0       .text cursorMainMove__12dMenu_Item_cFv */
void dMenu_Item_c::cursorMainMove() {
    stick->checkTrigger();
    u8 var_r31 = nowItem;

    if (stick->checkRightTrigger()) {
        if (nowItem != 21) {
            if (nowItem % 7 == 6) {
                nowItem -= 6;
            } else {
                nowItem++;
            }
        }
    } else if (stick->checkLeftTrigger()) {
        if (nowItem != 21) {
            if (nowItem % 7 == 0) {
                nowItem += 6;
            } else {
                nowItem--;
            }
        }
    }

    if (stick->checkUpTrigger()) {
        if (nowItem == 21) {
            nowItem = 14;
        } else if (nowItem > 6) {
            nowItem -= 7;
        }
    } else if (stick->checkDownTrigger()) {
        if (nowItem < 14) {
            nowItem += 7;
        } else if (nowItem >= 14 && nowItem <= 20) {
            nowItem = 21;
        }
    }

    if (nowItem != var_r31) {
        field_0x858.mUserArea = 0;
        itemnameSet();
        mDoAud_seStart(JA_SE_ITM_MENU_CURSOR);
    }
}

/* 801C8CA0-801C8E60       .text cursorSubMove__12dMenu_Item_cFv */
void dMenu_Item_c::cursorSubMove() {
    s16 var_r31 = g_menuHIO.field_0x82;
    
    u8 temp_r30;
    if (nowItem == 0xFF) {
        temp_r30 = 8;
    } else {
        temp_r30 = nowItem - field_0x2400;
    }

    stick->checkTrigger();

    if (stick->checkRightTrigger()) {
        if (temp_r30 % 3 != 2) {
            if (temp_r30 <= var_r31 - 1) {
                temp_r30++;
            }
        }
    } else if (stick->checkLeftTrigger()) {
        if (temp_r30 % 3 != 0) {
            temp_r30--;
        }
    }

    if (stick->checkUpTrigger()) {
        if (temp_r30 >= 3) {
            temp_r30 -= 3;
        }
    } else if (stick->checkDownTrigger()) {
        if ((u8)(temp_r30 + 3) <= var_r31) {
            temp_r30 += 3;
        }
    }

    if (temp_r30 != (u8)(nowItem - field_0x2400)) {
        if (temp_r30 == 8) {
            if (nowItem != 0xFF) {
                nowItem = 0xFF;
                mDoAud_seStart(JA_SE_ITM_MENU_CURSOR);
            }
        } else {
            nowItem = temp_r30 + field_0x2400;
            mDoAud_seStart(JA_SE_ITM_MENU_CURSOR);
        }

        field_0x858.mUserArea = 0;
        itemnameSet();
    }
}

/* 801C8E60-801C9124       .text checkMove__12dMenu_Item_cFv */
void dMenu_Item_c::checkMove() {
    for (int i = 0; i < 3; i++) {
        u8 select_item = dComIfGs_getSelectItem(i);
        if (select_item != 0xFF) {
            field_0x2030[i].pane->show();

            if (dMeter_subWinFlag()) {
                if (select_item >= 0x30) {
                    if (field_0x2405 == 2) {
                        select_item = select_item - 0x30;
                        field_0x2030[i].mPosCenter.x = field_0xe78[select_item].mPosCenter.x;
                        field_0x2030[i].mPosCenter.y = field_0xe78[select_item].mPosCenter.y;
                        field_0x231c->insertChild(field_0x1230.pane, field_0x2030[i].pane);
                    } else {
                        select_item = fopMsgM_itemNum(dItemNo_DELIVERY_BAG_e);
                        field_0x2030[i].mPosCenter.x = field_0x1658[select_item].mPosCenterOrig.x;
                        field_0x2030[i].mPosCenter.y = field_0x1658[select_item].mPosCenterOrig.y;
                        field_0x231c->insertChild(field_0x1af0[20].pane, field_0x2030[i].pane);
                    }
                } else if (select_item >= 0x24) {
                    if (field_0x2405 == 1) {
                        select_item = select_item - 0x24;
                        field_0x2030[i].mPosCenter.x = field_0xe78[select_item].mPosCenter.x;
                        field_0x2030[i].mPosCenter.y = field_0xe78[select_item].mPosCenter.y;
                        field_0x231c->insertChild(field_0x1230.pane, field_0x2030[i].pane);
                    } else {
                        select_item = fopMsgM_itemNum(dItemNo_BAIT_BAG_e);
                        field_0x2030[i].mPosCenter.x = field_0x1658[select_item].mPosCenterOrig.x;
                        field_0x2030[i].mPosCenter.y = field_0x1658[select_item].mPosCenterOrig.y;
                        field_0x231c->insertChild(field_0x1af0[20].pane, field_0x2030[i].pane);
                    }
                } else if (select_item >= 0x18) {
                    if (field_0x2405 == 0) {
                        select_item = select_item - 0x18;
                        field_0x2030[i].mPosCenter.x = field_0xe78[select_item].mPosCenter.x;
                        field_0x2030[i].mPosCenter.y = field_0xe78[select_item].mPosCenter.y;
                        field_0x231c->insertChild(field_0x1230.pane, field_0x2030[i].pane);
                    } else {
                        select_item = fopMsgM_itemNum(dItemNo_SPOILS_BAG_e);
                        field_0x2030[i].mPosCenter.x = field_0x1658[select_item].mPosCenterOrig.x;
                        field_0x2030[i].mPosCenter.y = field_0x1658[select_item].mPosCenterOrig.y;
                        field_0x231c->insertChild(field_0x1af0[20].pane, field_0x2030[i].pane);
                    }
                } else {
                    field_0x2030[i].mPosCenter.x = field_0x1658[select_item].mPosCenterOrig.x;
                    field_0x2030[i].mPosCenter.y = field_0x1658[select_item].mPosCenterOrig.y;
                    field_0x231c->insertChild(field_0x1af0[20].pane, field_0x2030[i].pane);
                }
            } else {
                if (select_item >= 0x30) {
                    select_item = fopMsgM_itemNum(dItemNo_DELIVERY_BAG_e);
                } else if (select_item >= 0x24) {
                    select_item = fopMsgM_itemNum(dItemNo_BAIT_BAG_e);
                } else if (select_item >= 0x18) {
                    select_item = fopMsgM_itemNum(dItemNo_SPOILS_BAG_e);
                }

                field_0x2030[i].mPosCenter.x = field_0x1658[select_item].mPosCenterOrig.x;
                field_0x2030[i].mPosCenter.y = field_0x1658[select_item].mPosCenterOrig.y;
                field_0x231c->insertChild(field_0x1af0[20].pane, field_0x2030[i].pane);
            }

            field_0x2030[i].mPosCenterOrig.x = field_0x2030[i].mPosCenter.x;
            field_0x2030[i].mPosCenterOrig.y = field_0x2030[i].mPosCenter.y;
            fopMsgM_cposMove(&field_0x2030[i]);
        } else {
            field_0x2030[i].pane->hide();
        }
    }
}

/* 801C9124-801C95FC       .text itemplaceCheck__12dMenu_Item_cFi */
bool dMenu_Item_c::itemplaceCheck(int i_type) {
    switch (i_type) {
    case 0:
        for (int i = 0; i < 4; i++) {
            static const int event[] = {0, 1, 2, 3};
            if (dComIfGs_getItem(event[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++) {
            static const int attack[] = {7, 8, 9, 10};
            if (dComIfGs_getItem(attack[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++) {
            static const int bottle[] = {14, 15, 16, 17};
            if (dComIfGs_getItem(bottle[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++) {
            static const int bag[] = {4, 11, 18};
            if (dComIfGs_getItem(bag[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    case 4:
        for (int i = 0; i < 3; i++) {
            static const int wepon1[] = {5, 12, 19};
            if (dComIfGs_getItem(wepon1[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    case 5:
        for (int i = 0; i < 3; i++) {
            static const int wepon2[] = {6, 13, 20};
            if (dComIfGs_getItem(wepon2[i]) != dItemNo_NONE_e) {
                return true;
            }
        }
        break;
    }

    return false;
}

/* 801C95FC-801C9DF4       .text itemDecide__12dMenu_Item_cFv */
void dMenu_Item_c::itemDecide() {
    if (field_0x2404 != 3) {
        dComIfGs_setSelectItem(field_0x2404, field_0x2401);
        dComIfGp_setSelectItem(field_0x2404);
        field_0x2404 = 3;

        if (field_0x2403 != 3) {
            dComIfGs_setSelectItem(field_0x2403, field_0x2402);
            dComIfGp_setSelectItem(field_0x2403);
            field_0x2403 = 3;
        }

        mDoAud_seStart(JA_SE_ITM_MENU_SET);
    }

    if (CPad_CHECK_TRIG_X(0)) {
        field_0x2404 = 0;
    } else if (CPad_CHECK_TRIG_Y(0)) {
        field_0x2404 = 1;
    } else if (CPad_CHECK_TRIG_Z(0)) {
        field_0x2404 = 2;
    }

    if (dComIfGs_getItem(nowItem) == dItemNo_SPOILS_BAG_e) {
        field_0x2405 = 0;
        subWindowInit();
        field_0x2404 = 3;
        field_0x2403 = 3;
        mDoAud_seStart(JA_SE_ITM_MENU_DECIDE);
    } else if (dComIfGs_getItem(nowItem) == dItemNo_BAIT_BAG_e) {
        field_0x2405 = 1;
        subWindowInit();
        field_0x2404 = 3;
        field_0x2403 = 3;
        mDoAud_seStart(JA_SE_ITM_MENU_DECIDE);
    } else if (dComIfGs_getItem(nowItem) == dItemNo_DELIVERY_BAG_e) {
        field_0x2405 = 2;
        subWindowInit();
        field_0x2404 = 3;
        field_0x2403 = 3;
        mDoAud_seStart(JA_SE_ITM_MENU_DECIDE);
    } else {
        u8 var_r29;
        u8 var_r30;
        
        if (field_0x2404 == 0) {
            var_r29 = 1;
            var_r30 = 2;
        } if (field_0x2404 == 1) {
            var_r29 = 2;
            var_r30 = 0;
        } else if (field_0x2404 == 2) {
            var_r29 = 0;
            var_r30 = 1;
        }

        if (nowItem == dComIfGs_getSelectItem(var_r29)) {
            field_0x2403 = var_r29;
            field_0x2402 = dComIfGs_getSelectItem(field_0x2404);

            if (dMeter_subWinFlag()) {
                subWindowDelete();
            }
        } else if (nowItem == dComIfGs_getSelectItem(var_r30)) {
            field_0x2403 = var_r30;
            field_0x2402 = dComIfGs_getSelectItem(field_0x2404);

            if (dMeter_subWinFlag()) {
                subWindowDelete();
            }
        }

        field_0x2401 = nowItem;
        dMeter_itemMoveSet(&field_0x1658[field_0x2401], field_0x2404, field_0x2401);
        mDoAud_seStart(JA_SE_ITM_MENU_DECIDE);
    }
}

/* 801C9DF4-801CA18C       .text itemMove__12dMenu_Item_cFv */
void dMenu_Item_c::itemMove() {
    if (dMeter_itemMoveFlagCheck() == 2) {
        dComIfGs_setSelectItem(field_0x2404, field_0x2401);
        dComIfGp_setSelectItem(field_0x2404);
        field_0x2404 = 3;

        if (field_0x2403 != 3) {
            dComIfGs_setSelectItem(field_0x2403, field_0x2402);
            dComIfGp_setSelectItem(field_0x2403);
            field_0x2403 = 3;
        }

        mDoAud_seStart(JA_SE_ITM_MENU_SET);
    }
}

/* 801CA18C-801CA3F4       .text itemScale__12dMenu_Item_cFv */
// NONMATCHING - regalloc
void dMenu_Item_c::itemScale() {
    if (nowItem == 0x15) {
        for (int i = 0; i < 21; i++) {
            fopMsgM_paneScaleXY(&field_0x1658[i], 1.0f);
            fopMsgM_paneScaleXY(&field_0x1af0[i], 1.0f);
        }

        for (int i = 0; i < 8; i++) {
            fopMsgM_paneScaleXY(&field_0xe78[i], 1.0f);
            fopMsgM_paneScaleXY(&field_0x1070[i], 1.0f);
        }
    } else {
        int var_r27;
        if (nowItem >= 0x30) {
            var_r27 = 0x30;
        } else if (nowItem >= 0x24) {
            var_r27 = 0x2C;
        } else if (nowItem >= 0x18) {
            var_r27 = 0x24;
        } else {
            var_r27 = nowItem;
        }

        for (int i = 0; i < 21; i++) {
            if (i == var_r27 && field_0x2404 == 3) {
                fopMsgM_paneScaleXY(&field_0x1658[i], g_menuHIO.field_0x8);
                fopMsgM_paneScaleXY(&field_0x1af0[i], g_menuHIO.field_0x8);

                if (var_r27 == 0xC) {
                    for (int j = 0; j < 3; j++) {
                        field_0x1f88[j].mPosCenter.x = field_0x1658[i].mPosCenter.x + g_menuHIO.field_0x8 * (field_0x1f88[j].mPosCenterOrig.x - field_0x1658[i].mPosCenterOrig.x);
                        field_0x1f88[j].mPosCenter.y = field_0x1658[i].mPosCenter.y + g_menuHIO.field_0x8 * (field_0x1f88[j].mPosCenterOrig.y - field_0x1658[i].mPosCenterOrig.y);
                    }
                }
            } else {
                fopMsgM_paneScaleXY(&field_0x1658[i], 1.0f);
                fopMsgM_paneScaleXY(&field_0x1af0[i], 1.0f);
            }
        }

        if (nowItem == 0xFF) {
            for (int i = 0; i < 8; i++) {
                fopMsgM_paneScaleXY(&field_0xe78[i], 1.0f);
                fopMsgM_paneScaleXY(&field_0x1070[i], 1.0f);
            }
        } else if (nowItem >= 0x15) {
            int var_r27 = nowItem - field_0x2400;

            for (int i = 0; i < 8; i++) {
                if (i == var_r27 && field_0x2404 == 3) {
                    fopMsgM_paneScaleXY(&field_0xe78[i], g_menuHIO.field_0x8);
                    fopMsgM_paneScaleXY(&field_0x1070[i], g_menuHIO.field_0x8);
                } else {
                    fopMsgM_paneScaleXY(&field_0xe78[i], 1.0f);
                    fopMsgM_paneScaleXY(&field_0x1070[i], 1.0f);
                }
            }
        }
    }
}

/* 801CA3F4-801CAA04       .text subWindowInit__12dMenu_Item_cFv */
void dMenu_Item_c::subWindowInit() {
    dMeter_subWinFlagOn();
    int var_r29 = 0;
    field_0x858.mUserArea = var_r29;

    if (field_0x2405 == 0) {
        field_0x2400 = 0x18;
        nowItem = field_0x2400;

        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getItemBeast((u8)i) != 0xFF) {
                field_0xe78[i].mUserArea = 1;

                JKRReadTypeResource(subItemTexBuffer[i], 0xC00, 'TIMG', dItem_data::getTexture(dComIfGs_getItemBeast((u8)i)), dComIfGp_getItemIconArchive());
                
                #if VERSION >= VERSION_USA
                DCStoreRangeNoSync(subItemTexBuffer[i], 0xC00);
                #else
                DCFlushRangeNoSync(subItemTexBuffer[i], 0xC00);
                #endif

                ((J2DPicture*)field_0xe78[i].pane)->changeTexture(subItemTexBuffer[i], 0);
                ((J2DPicture*)field_0x1070[i].pane)->changeTexture(subItemTexBuffer[i], 0);

                field_0xe78[i].pane->show();
                field_0x1070[i].pane->show();
                field_0xcb8[i].pane->show();
                field_0xaf8[i].pane->show();
            } else {
                field_0xe78[i].mUserArea = 0;

                field_0xe78[i].pane->hide();
                field_0x1070[i].pane->hide();
                field_0xcb8[i].pane->hide();
                field_0xaf8[i].pane->hide();
            }

            int num = dComIfGs_getBeastNum(equipBeastItem(i));
            if (num == 0) {
                numberColor(field_0xcb8[i].pane, 2);
                numberColor(field_0xaf8[i].pane, 2);
            } else if (num == 99) {
                numberColor(field_0xcb8[i].pane, 1);
                numberColor(field_0xaf8[i].pane, 1);
            } else {
                numberColor(field_0xcb8[i].pane, 0);
                numberColor(field_0xaf8[i].pane, 0);
            }

            if (num < 10) {
                field_0xcb8[i].pane->hide();
            } else {
                numberSet(field_0xcb8[i].pane, num / 10);
            }

            numberSet(field_0xaf8[i].pane, num % 10);
        }
    } else if (field_0x2405 == 1) {
        field_0x2400 = 0x24;
        nowItem = field_0x2400 + 3;

        for (int i = 0; i < 8; i++) {
            field_0xcb8[i].pane->hide();

            if (dComIfGs_getItemBait((u8)i) != 0xFF) {
                field_0xe78[i].mUserArea = 1;

                JKRReadTypeResource(subItemTexBuffer[i], 0xC00, 'TIMG', dItem_data::getTexture(dComIfGs_getItemBait((u8)i)), dComIfGp_getItemIconArchive());

                #if VERSION >= VERSION_USA
                DCStoreRangeNoSync(subItemTexBuffer[i], 0xC00);
                #else
                DCFlushRangeNoSync(subItemTexBuffer[i], 0xC00);
                #endif

                ((J2DPicture*)field_0xe78[i].pane)->changeTexture(subItemTexBuffer[i], 0);
                ((J2DPicture*)field_0x1070[i].pane)->changeTexture(subItemTexBuffer[i], 0);

                field_0xe78[i].pane->show();
                field_0x1070[i].pane->show();

                if (dComIfGs_getItemBait((u8)i) == 0x82) {
                    field_0xaf8[i].pane->show();
                } else {
                    field_0xaf8[i].pane->hide();
                }
            } else {
                field_0xe78[i].mUserArea = 0;

                field_0xe78[i].pane->hide();
                field_0x1070[i].pane->hide();
                field_0xaf8[i].pane->hide();
            }

            int num = dComIfGs_getBaitNum(i);
            if (num == 0) {
                numberColor(field_0xcb8[i].pane, 2);
                numberColor(field_0xaf8[i].pane, 2);
            } else if (num == 3) {
                numberColor(field_0xcb8[i].pane, 1);
                numberColor(field_0xaf8[i].pane, 1);
            } else {
                numberColor(field_0xcb8[i].pane, 0);
                numberColor(field_0xaf8[i].pane, 0);
            }

            numberSet(field_0xaf8[i].pane, num % 10);
        }
    } else {
        field_0x2400 = 0x30;
        nowItem = field_0x2400 + 6;

        for (int i = 0; i < 8; i++) {
            field_0xcb8[i].pane->hide();
            field_0xaf8[i].pane->hide();

            if (dComIfGs_getItemReserve((u8)i) != 0xFF) {
                field_0xe78[i].mUserArea = 1;

                JKRReadTypeResource(subItemTexBuffer[i], 0xC00, 'TIMG', dItem_data::getTexture(dComIfGs_getItemReserve((u8)i)), dComIfGp_getItemIconArchive());

                #if VERSION >= VERSION_USA
                DCStoreRangeNoSync(subItemTexBuffer[i], 0xC00);
                #else
                DCFlushRangeNoSync(subItemTexBuffer[i], 0xC00);
                #endif

                ((J2DPicture*)field_0xe78[i].pane)->changeTexture(subItemTexBuffer[i], 0);
                ((J2DPicture*)field_0x1070[i].pane)->changeTexture(subItemTexBuffer[i], 0);

                field_0xe78[i].pane->show();
                field_0x1070[i].pane->show();
            } else {
                field_0xe78[i].mUserArea = 0;

                field_0xe78[i].pane->hide();
                field_0x1070[i].pane->hide();
            }
        }
    }

    itemnameSet();

    for (int i = 0; i < 8; i++) {
        fopMsgM_paneScaleXY(&field_0xe78[i], 1.0f);
        fopMsgM_paneScaleXY(&field_0x1070[i], 1.0f);
    }

    for (int i = 0; i < 8; i++) {
        fopMsgM_setInitAlpha(&field_0xaf8[i]);
        fopMsgM_setInitAlpha(&field_0xcb8[i]);
        fopMsgM_setInitAlpha(&field_0xe78[i]);
        fopMsgM_setInitAlpha(&field_0x1070[i]);
    }

    fopMsgM_setInitAlpha(&field_0x1038);
    fopMsgM_setInitAlpha(&field_0x1230);

    for (int i = 0; i < 9; i++) {
        fopMsgM_setInitAlpha(&field_0x1268[i]);
    }

    fopMsgM_setInitAlpha(&field_0x1460);

    field_0x231c->insertChild(field_0xcb8[7].pane, field_0xa18[3].pane);
    field_0x231c->insertChild(field_0xa18[3].pane, field_0xa18[2].pane);
    field_0x231c->insertChild(field_0xa18[2].pane, field_0xa18[1].pane);
    field_0x231c->insertChild(field_0xa18[1].pane, field_0xa18[0].pane);
}

/* 801CAA04-801CAB48       .text subWindowDelete__12dMenu_Item_cFv */
void dMenu_Item_c::subWindowDelete() {
    field_0x858.mUserArea = 0;

    if (field_0x2405 == 0) {
        nowItem = fopMsgM_itemNum(0x24);
    } else if (field_0x2405 == 1) {
        nowItem = fopMsgM_itemNum(0x2C);
    } else {
        nowItem = fopMsgM_itemNum(0x30);
    }

    itemnameSet();
    itemScale();
    dMeter_subWinFlagOff();

    for (int i = 0; i < 8; i++) {
        fopMsgM_setNowAlphaZero(&field_0xaf8[i]);
        fopMsgM_setNowAlphaZero(&field_0xcb8[i]);
        fopMsgM_setNowAlphaZero(&field_0xe78[i]);
        fopMsgM_setNowAlphaZero(&field_0x1070[i]);
    }

    fopMsgM_setNowAlphaZero(&field_0x1038);
    fopMsgM_setNowAlphaZero(&field_0x1230);

    for (int i = 0; i < 9; i++) {
        fopMsgM_setNowAlphaZero(&field_0x1268[i]);
    }

    fopMsgM_setNowAlphaZero(&field_0x1460);

    field_0x231c->insertChild(field_0x1460.pane, field_0xa18[3].pane);
    field_0x231c->insertChild(field_0xa18[3].pane, field_0xa18[2].pane);
    field_0x231c->insertChild(field_0xa18[2].pane, field_0xa18[1].pane);
    field_0x231c->insertChild(field_0xa18[1].pane, field_0xa18[0].pane);
}

/* 801CAB48-801CB020       .text subItemDecide__12dMenu_Item_cFv */
void dMenu_Item_c::subItemDecide() {
    if (field_0x2404 != 3) {
        dComIfGs_setSelectItem(field_0x2404, field_0x2401);
        dComIfGp_setSelectItem(field_0x2404);
        field_0x2404 = 3;

        if (field_0x2403 != 3) {
            dComIfGs_setSelectItem(field_0x2403, field_0x2402);
            dComIfGp_setSelectItem(field_0x2403);
            field_0x2403 = 3;
        }

        mDoAud_seStart(JA_SE_ITM_MENU_SET);
    }

    if (CPad_CHECK_TRIG_X(0)) {
        field_0x2404 = 0;
    } else if (CPad_CHECK_TRIG_Y(0)) {
        field_0x2404 = 1;
    } else if (CPad_CHECK_TRIG_Z(0)) {
        field_0x2404 = 2;
    }

    u8 var_r29;
    u8 var_r30;
    if (field_0x2404 == 0) {
        var_r29 = 1;
        var_r30 = 2;
    } else if (field_0x2404 == 1) {
        var_r29 = 2;
        var_r30 = 0;
    } else if (field_0x2404 == 2) {
        var_r29 = 0;
        var_r30 = 1;
    }

    if (nowItem == dComIfGs_getSelectItem(var_r29)) {
        field_0x2403 = var_r29;
        field_0x2402 = dComIfGs_getSelectItem(field_0x2404);
    } else if (nowItem == dComIfGs_getSelectItem(var_r30)) {
        field_0x2403 = var_r30;
        field_0x2402 = dComIfGs_getSelectItem(field_0x2404);
    }

    field_0x2401 = nowItem;
    dMeter_itemMoveSet(&field_0xe78[field_0x2401 - field_0x2400], field_0x2404, field_0x2401);
    mDoAud_seStart(JA_SE_ITM_MENU_DECIDE);

    if (dMeter_subWinFlag()) {
        subWindowDelete();
    }
}

/* 801CB020-801CB168       .text itemnameMove__12dMenu_Item_cFv */
// NONMATCHING - instruction ordering
void dMenu_Item_c::itemnameMove() {
    field_0x858.mUserArea++;
    if (field_0x858.mUserArea > 130) {
        field_0x858.mUserArea = 11;
    }

    if (field_0x858.mUserArea <= 10) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x858.mUserArea, 0);
        fopMsgM_setNowAlpha(&field_0x890[0], temp_f1);
        fopMsgM_setNowAlpha(&field_0x890[1], 1.0f - temp_f1);
        fopMsgM_setNowAlphaZero(&field_0x858);
    } else if (field_0x858.mUserArea <= 60) {
        fopMsgM_setInitAlpha(&field_0x890[0]);
        fopMsgM_setNowAlphaZero(&field_0x858);
    } else if (field_0x858.mUserArea <= 70) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x858.mUserArea - 60, 0);
        fopMsgM_setNowAlpha(&field_0x890[0], 1.0f - temp_f1);
        fopMsgM_setNowAlpha(&field_0x858, temp_f1);
    } else if (field_0x858.mUserArea <= 120) {
        fopMsgM_setNowAlphaZero(&field_0x890[0]);
        fopMsgM_setInitAlpha(&field_0x858);
    } else if (field_0x858.mUserArea <= 130) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x858.mUserArea - 120, 0);
        fopMsgM_setNowAlpha(&field_0x890[0], temp_f1);
        fopMsgM_setNowAlpha(&field_0x858, 1.0f - temp_f1);
    }

    outFont->move();
}

/* 801CB168-801CB7C0       .text itemnameSet__12dMenu_Item_cFv */
// NONMATCHING - stack ordering / missing instruction
void dMenu_Item_c::itemnameSet() {
    fopMsgM_itemMsgGet_c msgGet;
    u32 msgNo = 0;
    int r30 = 0;
    int i = 0;

    J2DTextBox::TFontSize copiedFontSize;
    J2DTextBox::TFontSize initialFontSize;

    initialFontSize.mSizeX = 29.0f;
    initialFontSize.mSizeY = 29.0f;
    ((J2DTextBox*)field_0x858.pane)->setFontSize(initialFontSize);
    ((J2DTextBox*)field_0x890[0].pane)->getFontSize(copiedFontSize);
    ((J2DTextBox*)field_0x890[1].pane)->setFontSize(copiedFontSize);

    ((J2DTextBox*)field_0x890[1].pane)->setCharSpace(((J2DTextBox*)field_0x890[0].pane)->getCharSpace());

    while (name[0][i] != 0) {
        name[1][i] = name[0][i];
        i++;
    }
    name[1][i] = 0;
    ((J2DTextBox*)field_0x890[1].pane)->setString(name[1]);
    strcpy(name[0], "");

    if (nowItem == 0x15) {
        msgNo = 0x1F8;
    } else if (dComIfGs_getItem(nowItem) != 0xFF) {
        msgNo = dItem_data::getItemMesgNum(dComIfGs_getItem(nowItem));
        if (msgNo == 0) {
            msgNo = 0x19C;
        }
    } else {
        return;
    }

    mesg_header* head_p = msgGet.getMesgHeader(msgNo);
    JUT_ASSERT(VERSION_SELECT(1381, 1381, 1381, 1381), head_p);

    J2DTextBox::TFontSize fontSize;
    ((J2DTextBox*)field_0x890[0].pane)->getFontSize(fontSize);
    fontSize.mSizeX = fontSize.mSizeY;

    char* src;
    f32 strWidth;
    char* mesg = (char*)msgGet.getMessage(head_p);
    bool first = false;
    f32 scale = fontSize.mSizeY / font[0]->getCellWidth();
    src = mesg;

    while ((s8)*src != 0) {
        char charStr[3];
        int byte = 0;
        charStr[2] = byte;
        charStr[1] = byte;
        charStr[0] = byte;

        u32 c = (u8)(*(u8*)src);
        if (c == 0x1A) {
            src++;
            src += (s8)*src - 1;
        } else {
            int charCode;
            int hi_nibble = (c >> 4) & 0xF;
            if (hi_nibble == 8 || hi_nibble == 9) {
                byte = (u8)src[0];
                c = (u8)src[1];
                charCode = c;
                charCode |= byte << 8;
                charStr[0] = byte;
                charStr[1] = c;
                charStr[2] = 0;
                src += 2;
            } else {
                charCode = c;
                charStr[0] = c;
                charStr[1] = byte;
                src += 1;
            }

            int width = font[0]->getWidth(charCode);
            strcat(name[0], charStr);
            if (!first) {
                strWidth = scale * (width + font[0]->getOffset(charCode));
                first = true;
            } else {
                strWidth += width * scale;
            }
        }
    }

    if (((J2DTextBox*)field_0x890[0].pane)->getWidth() < strWidth) {
        fontSize.mSizeX = (int)(fontSize.mSizeX * ((J2DTextBox*)field_0x890[0].pane)->getWidth() / strWidth);
    }

    ((J2DTextBox*)field_0x890[0].pane)->setFontSize(fontSize);
    ((J2DTextBox*)field_0x890[0].pane)->setCharSpace((f32)r30);
    ((J2DTextBox*)field_0x890[0].pane)->setString(name[0]);

    if (nowItem == 0x15) {
        outFont->messageSet(0x1FC);
    } else if (nowItem == 4 || nowItem == 0xB || nowItem == 0x12) {
        outFont->messageSet(0x1F5);
    } else {
        outFont->messageSet(0x1F9);
    }

    outFont->setLeftUpPos(field_0x858.mPosTopLeft.x, field_0x858.mPosTopLeft.y);
}

/* 801CB7C0-801CBEBC       .text itemnoteSet__12dMenu_Item_cFv */
// NONMATCHING - small reg swap
void dMenu_Item_c::itemnoteSet() {
    fopMsgM_itemMsgGet_c msgGet;
    fopMsgM_msgDataProc_c msgDataProc;
    u32 msgNo = 0;

    strcpy(note[0], "");
    strcpy(note[1], "");
    strcpy(dummy[0], "");
    strcpy(dummy[1], "");

    outFontInit();

    if (dComIfGs_getOptRuby()) {
        field_0x740.pane->hide();
    } else {
        field_0x740.pane->show();
    }

    f32 rubySize = ((J2DTextBox*)field_0x740.pane)->mFontSizeX;
#if VERSION <= VERSION_JPN
    f32 fontSizeX = ((J2DTextBox*)field_0x778.pane)->mFontSizeX;
#else
    J2DTextBox::TFontSize fontSize;
    fontSize.mSizeX = g_msgHIO.field_0x70;
    fontSize.mSizeY = g_msgHIO.field_0x70;
    ((J2DTextBox*)field_0x778.pane)->setFontSize(fontSize);
    ((J2DTextBox*)field_0x778.pane)->setLineSpace(g_msgHIO.field_0x5e);
#endif

    if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
        msgNo = dItem_data::getItemMesgNum(dComIfGs_getItem(nowItem));
        if (msgNo == 0) {
            msgNo = 0x264;
        } else {
            msgNo += 200;
        }
    } else {
        return;
    }

    mesg_header* head_p = msgGet.getMesgHeader(msgNo);
    JUT_ASSERT(VERSION_SELECT(1737, 1808, 1521, 1521), head_p);

    const char* mesg = msgGet.getMessage(head_p);
    JMSMesgEntry_c msg_entry;
    msg_entry = msgGet.getMesgEntry(head_p);

    msgDataProc.dataInit();
    msgDataProc.setBmgData((char*)mesg);
    msgDataProc.setOutMessage(note[0], note[1], dummy[0], dummy[1]);
    msgDataProc.setFont(font[0]);
    msgDataProc.setRubyFont(font[1]);
    msgDataProc.setCharSpace(((J2DTextBox*)field_0x778.pane)->getCharSpace());
    msgDataProc.setRubyCharSpace(((J2DTextBox*)field_0x740.pane)->getCharSpace());
    msgDataProc.setLineSpace(((J2DTextBox*)field_0x778.pane)->getLineSpace());
    msgDataProc.setMesgEntry(&msg_entry);
#if VERSION <= VERSION_JPN
    msgDataProc.setFontSize(fontSizeX);
#else
    msgDataProc.setFontSize(fontSize.mSizeX);
#endif
    msgDataProc.setRubyFontSize(rubySize);
    msgDataProc.setLineWidth(510);
    msgDataProc.setCenterLineWidth(486);
    msgDataProc.setSendSpeed(2);
    msgDataProc.setSpaceTimer(0);
    msgDataProc.shortCut();
    msgDataProc.setSpaceFlagOff();

    msgDataProc.stringLength();
    msgDataProc.stringShift();
    msgDataProc.iconIdxRefresh();

    s16 lineCount = msgDataProc.getLineCount();
    msgDataProc.setLineCount(0);
    f32 lineSpace = ((J2DTextBox*)field_0x778.pane)->getLineSpace();
    int unusedLines = VERSION_SELECT(2, 2, 3, 3) - lineCount;
    f32 shiftY = unusedLines * (lineSpace / 2.0f);
    ((J2DTextBox*)field_0x740.pane)->shiftSet(0.0f, shiftY);
    ((J2DTextBox*)field_0x778.pane)->shiftSet(0.0f, shiftY);
    msgDataProc.stringSet();

    ((J2DTextBox*)field_0x778.pane)->setString(note[0]);
    ((J2DTextBox*)field_0x740.pane)->setString(note[1]);

    int halfSpace = ((J2DTextBox*)field_0x778.pane)->getLineSpace() / 2.0f;
    for (int i = 0; i < 15; i++) {
        u8 iconNo = msgDataProc.getIconNum(i);
#if VERSION > VERSION_DEMO
        u32 color = msgDataProc.getIconColor(i);
        if (color == 0xFFFFFFFF) {
            color = 0xFF;
        }
#endif
        if (iconNo == 0xFF) {
            continue;
        }
        if (field_0xb0[i].mUserArea != -1) {
            continue;
        }
        if (iconNo == fopMsgM_Icon_INPUT_e) {
            continue;
        }
        field_0xb0[i].mPosTopLeft.x = (f32)msgDataProc.getIconPosX(i);
        field_0xb0[i].mPosTopLeft.y = (f32)(halfSpace * (unusedLines + msgDataProc.getIconPosY(i) * 2));
        field_0xb0[i].mPosTopLeftOrig.y = (f32)iconNo;

        fopMsgM_outFontSet((J2DPicture*)field_0xb0[i].pane, &field_0xb0[i].mUserArea, DEMO_SELECT(msgDataProc.getIconColor(i), color), iconNo);
    }
}

/* 801CBEBC-801CBF44       .text outFontInit__12dMenu_Item_cFv */
void dMenu_Item_c::outFontInit() {
    for (int i = 0; i < 15; i++) {
        field_0xb0[i].mUserArea = -1;
        field_0xb0[i].pane->rotate(0.0f);
        fopMsgM_setNowAlphaZero(&field_0xb0[i]);
    }
}

/* 801CBF44-801CC030       .text outFontMove__12dMenu_Item_cFv */
void dMenu_Item_c::outFontMove() {
    for (int i = 0; i < 15; i++) {
        if (field_0xb0[i].mUserArea != -1) {
            field_0x3f8[i].mPosTopLeft.x = field_0xb0[i].mPosTopLeft.x + (field_0x778.mPosTopLeft.x + (field_0x820.mPosTopLeft.x + field_0x7b0.mPosTopLeft.x));
            field_0x3f8[i].mPosTopLeft.y = field_0xb0[i].mPosTopLeft.y + (field_0x778.mPosTopLeft.y + (field_0x820.mPosTopLeft.y + field_0x7b0.mPosTopLeft.y));

            f32 x = field_0x820.mPosCenter.x - field_0x3f8[i].mPosTopLeft.x;
            f32 y = field_0x820.mPosCenter.y - field_0x3f8[i].mPosTopLeft.y;
            field_0x3f8[i].pane->rotate(x, y, ROTATE_Z, field_0x820.pane->getRotate());
        } else {
            fopMsgM_setNowAlphaZero(&field_0xb0[i]);
        }
    }
}

/* 801CC030-801CC0F8       .text outFontDraw__12dMenu_Item_cFv */
void dMenu_Item_c::outFontDraw() {
    for (int i = 0; i < 15; i++) {
        if (field_0xb0[i].mUserArea != -1) {
            field_0xb0[i].mNowAlpha = field_0x778.pane->getAlpha();
            fopMsgM_outFontDraw2(
                (J2DPicture*)field_0xb0[i].pane,
                (J2DPicture*)field_0x3f8[i].pane,
                field_0x3f8[i].mPosTopLeft.x,
                field_0x3f8[i].mPosTopLeft.y,
#if VERSION >= VERSION_USA
                g_msgHIO.field_0x70,
                g_msgHIO.field_0x70,
#else
                29,
                29,
#endif
                &field_0xb0[i].mUserArea,
                field_0xb0[i].mNowAlpha,
                field_0xb0[i].mPosTopLeftOrig.y);
        } else {
            fopMsgM_setAlpha(&field_0xb0[i]);
        }
    }
}

/* 801CC0F8-801CC10C       .text noteCheck__12dMenu_Item_cFv */
u8 dMenu_Item_c::noteCheck() {
    return field_0x7e8.mUserArea == 1;
}

/* 801CC10C-801CC1AC       .text noteInit__12dMenu_Item_cFv */
void dMenu_Item_c::noteInit() {
    field_0x7e8.mUserArea = 0;
    field_0x7b0.mUserArea = 0;
    field_0x820.pane->rotate(field_0x820.mSizeOrig.x / 2, field_0x820.mSizeOrig.y / 2, ROTATE_Z, field_0x820.mUserArea);
    fopMsgM_paneTrans(&field_0x820, 0.0f, 0.0f);
}

/* 801CC1AC-801CC278       .text noteAppear__12dMenu_Item_cFv */
void dMenu_Item_c::noteAppear() {
    s16 var_r6 = g_miHIO.field_0x38 + g_miHIO.field_0x3A;

    if (field_0x7e8.mUserArea == 1) {
        if (field_0x7b0.mUserArea <= var_r6) {
            noteOpen();
        } else if (field_0x7b0.mUserArea > var_r6 + 1) {
            noteClose();
        } else {
            field_0x970.mInitAlpha = field_0x970.mNowAlpha = g_miHIO.field_0x5C;
            if (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0)) {
                field_0x7b0.mUserArea++;
                mDoAud_seStart(JA_SE_ITM_MENU_EXP_OUT);
            }
        }
    }
}

/* 801CC278-801CC4F8       .text noteOpen__12dMenu_Item_cFv */
// NONMATCHING - instruction order / reg alloc
void dMenu_Item_c::noteOpen() {
    s16 var_r28 = g_miHIO.field_0x30;
    s16 var_r30 = g_miHIO.field_0x38 + g_miHIO.field_0x3A;
    f32 fVar2 = g_miHIO.field_0x40 - field_0x820.mPosCenterOrig.x;
    f32 fVar3 = g_miHIO.field_0x42 - field_0x820.mPosCenterOrig.y;
    f32 fVar1 = 1.0f - fopMsgM_valueIncrease(var_r30, var_r30 - field_0x7b0.mUserArea, 0);
    
    if (field_0x7b0.mUserArea >= var_r30) {
        fopMsgM_setInitAlpha(&field_0x970);
        fopMsgM_setInitAlpha(&field_0x740);
        fopMsgM_setInitAlpha(&field_0x778);
        mDoAud_seStart(JA_SE_ITM_MENU_EXP_IN);
    } else {
        fopMsgM_setNowAlpha(&field_0x970, fVar1);
        fopMsgM_setNowAlpha(&field_0x740, fVar1);
        fopMsgM_setNowAlpha(&field_0x778, fVar1);
    }
    
    field_0x820.pane->rotate(field_0x820.mSize.x / 2.0f, field_0x820.mSize.y / 2.0f, ROTATE_Z, field_0x820.mUserArea + fVar1 * (f32)(var_r28 - field_0x820.mUserArea));

    if (field_0x7b0.mUserArea < g_miHIO.field_0x38) {
        fVar1 = (field_0x7b0.mUserArea * g_miHIO.field_0x08) / g_miHIO.field_0x38;
    } else {
        f32 temp_f29 = 1.0f - g_miHIO.field_0x08;
        fVar1 = (1.0f - fopMsgM_valueIncrease(g_miHIO.field_0x3A, var_r30 - var_r28, 0)) * temp_f29 + g_miHIO.field_0x08;
    }

    fopMsgM_paneTrans(&field_0x820, fVar2 * fVar1, fVar3 * fVar1);
    field_0x7b0.mUserArea++;
}

/* 801CC4F8-801CC7D4       .text noteClose__12dMenu_Item_cFv */
// NONMATCHING - instruction ordering
void dMenu_Item_c::noteClose() {
    const s16 temp_r27 = g_miHIO.field_0x30;
    const s16 temp_r31 = g_miHIO.field_0x44;
    s16 temp_r0 = g_miHIO.field_0x38 + g_miHIO.field_0x3A;
    s16 temp_r29 = g_miHIO.field_0x3C;

    f32 temp_f3 = g_miHIO.field_0x40;
    f32 temp_f4 = g_miHIO.field_0x42;
    f32 temp0 = ((temp_f3 * 2.0f) - field_0x820.mPosCenterOrig.x);
    f32 temp1 = ((temp_f4 * 2.0f) - field_0x820.mPosCenterOrig.y);
    f32 out_x = temp0 - temp_f3;
    f32 out_y = temp1 - temp_f4;
    f32 x = temp_f3 - field_0x820.mPosCenterOrig.x;
    f32 y = temp_f4 - field_0x820.mPosCenterOrig.y;
    
    f32 alpha = fopMsgM_valueIncrease(temp_r29, field_0x7b0.mUserArea - (temp_r0 + 1), 0);
    f32 f26 = (alpha * (temp_r31 - temp_r27)) + temp_r27;
    fopMsgM_paneTrans(&field_0x820, (out_x * alpha) + x, (out_y * alpha) + y);

    field_0x820.pane->rotate(
        field_0x820.mSize.x / 2.0f,
        field_0x820.mSize.y / 2.0f,
        ROTATE_Z,
        f26
    );

    field_0x7b0.mUserArea++;

    s16 temp_r0_2 = (s16)(temp_r0 + (temp_r29 + 1));
    if (field_0x7b0.mUserArea > temp_r0_2) {
        fopMsgM_setInitAlpha(&field_0x7b0);
        fopMsgM_setInitAlpha(&field_0x7e8);
        fopMsgM_setInitAlpha(&field_0x820);
        fopMsgM_setNowAlphaZero(&field_0x970);
        fopMsgM_setNowAlphaZero(&field_0x740);
        fopMsgM_setNowAlphaZero(&field_0x778);

        field_0x7e8.mUserArea = 0;
        field_0x7b0.mUserArea = 0;

        field_0x820.pane->rotate(
            field_0x820.mSize.x / 2.0f,
            field_0x820.mSize.y / 2.0f,
            ROTATE_Z,
            field_0x820.mUserArea
        );

        fopMsgM_paneTrans(&field_0x820, 0.0f, 0.0f);
    } else {
        fopMsgM_setNowAlpha(&field_0x7b0, 1.0f - alpha);
        fopMsgM_setNowAlpha(&field_0x7e8, 1.0f - alpha);
        fopMsgM_setNowAlpha(&field_0x820, 1.0f - alpha);
        fopMsgM_setNowAlpha(&field_0x970, 1.0f - alpha);
        fopMsgM_setNowAlpha(&field_0x740, 1.0f - alpha);
        fopMsgM_setNowAlpha(&field_0x778, 1.0f - alpha);
    }
}

/* 801CC7D4-801CC9D8       .text mainTrans__12dMenu_Item_cFff */
void dMenu_Item_c::mainTrans(f32 i_transX, f32 i_transY) {
    fopMsgM_paneTrans(&field_0x1498, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x14d0, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x1508, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x1540, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x1578, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x15b0, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x15e8, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x1620, i_transX, i_transY);

    for (int i = 0; i < 21; i++) {
        fopMsgM_paneTrans(&field_0x1658[i], i_transX, i_transY);
        fopMsgM_paneTrans(&field_0x1af0[i], i_transX, i_transY);
    }

    for (int i = 0; i < 3; i++) {
        fopMsgM_paneTrans(&field_0x1f88[i], i_transX, i_transY);
    }

    for (int i = 0; i < 6; i++) {
        fopMsgM_paneTrans(&field_0x20d8[i], i_transX, i_transY);
    }

    fopMsgM_paneTrans(&field_0x2228, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x2260, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x2298, i_transX, i_transY);
    fopMsgM_paneTrans(&field_0x22d0, i_transX, i_transY);

    for (int i = 0; i < 4; i++) {
        fopMsgM_paneTrans(&field_0xa18[i], i_transX, i_transY);
    }

    for (int i = 0; i < 3; i++) {
        if (dComIfGp_getSelectItem(i) != dItemNo_NONE_e) {
            fopMsgM_paneTrans(&field_0x2030[i], i_transX, i_transY);
        }
    }
}

/* 801CC9D8-801CC9FC       .text titleTrans__12dMenu_Item_cFff */
void dMenu_Item_c::titleTrans(f32 i_posX, f32 i_posY) {
    fopMsgM_paneTrans(&field_0x9e0, i_posX, i_posY);
}

/* 801CC9FC-801CCA88       .text noteRotate__12dMenu_Item_cFff */
void dMenu_Item_c::noteRotate(f32 i_posY, f32 i_angle) {
    fopMsgM_paneTrans(&field_0x820, 0.0f, i_posY);
    field_0x820.pane->rotate(field_0x820.mSize.x / 2, field_0x820.mSize.y / 2, ROTATE_Z, i_angle);
}

/* 801CCA88-801CCB3C       .text nameTrans__12dMenu_Item_cFff */
void dMenu_Item_c::nameTrans(f32 i_posX, f32 i_posY) {
    fopMsgM_paneTrans(&field_0x858, i_posX, i_posY);
    outFont->setLeftUpPos(field_0x858.mPosTopLeft.x, field_0x858.mPosTopLeft.y);
    outFont->move();

    fopMsgM_paneTrans(&field_0x890[0], i_posX, i_posY);
    fopMsgM_paneTrans(&field_0x890[1], i_posX, i_posY);
    fopMsgM_paneTrans(&field_0x900, i_posX, i_posY);
    fopMsgM_paneTrans(&field_0x938, i_posX, i_posY);
}

/* 801CCB3C-801CCD74       .text mainOpenProc__12dMenu_Item_cFsss */
void dMenu_Item_c::mainOpenProc(s16 param_0, s16 param_1, s16 param_2) {
    if (param_1 >= param_0) {
        f32 temp_f31 = fopMsgM_valueIncrease(param_1, param_0, 0);
        mainTrans(param_2 * fopMsgM_valueIncrease(param_1, param_1 - param_0, 0), 0.0f);

        fopMsgM_setNowAlpha(&field_0x1498, temp_f31);
        fopMsgM_setNowAlpha(&field_0x14d0, temp_f31);
        fopMsgM_setNowAlpha(&field_0x1508, temp_f31);
        fopMsgM_setNowAlpha(&field_0x1540, temp_f31);
        fopMsgM_setNowAlpha(&field_0x1578, temp_f31);
        fopMsgM_setNowAlpha(&field_0x15b0, temp_f31);
        fopMsgM_setNowAlpha(&field_0x15e8, temp_f31);
        fopMsgM_setNowAlpha(&field_0x1620, temp_f31);

        for (int i = 0; i < 21; i++) {
            fopMsgM_setNowAlpha(&field_0x1658[i], temp_f31);
            fopMsgM_setNowAlpha(&field_0x1af0[i], temp_f31);
        }

        for (int i = 0; i < 6; i++) {
            if (itemplaceCheck(i)) {
                fopMsgM_setNowAlpha(&field_0x20d8[i], temp_f31);
            }
        }

        fopMsgM_setNowAlpha(&field_0x2228, temp_f31);
        fopMsgM_setNowAlpha(&field_0x2260, temp_f31);
        fopMsgM_setNowAlpha(&field_0x2298, temp_f31);
        fopMsgM_setNowAlpha(&field_0x22d0, temp_f31);

        for (int i = 0; i < 4; i++) {
            fopMsgM_setNowAlpha(&field_0xa18[i], temp_f31);
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setNowAlpha(&field_0x1f88[i], temp_f31);
            fopMsgM_setNowAlpha(&field_0x2030[i], temp_f31);

            if (dComIfGp_getSelectItem(i) != dItemNo_NONE_e) {
                field_0x2030[i].pane->show();
            } else {
                field_0x2030[i].pane->hide();
            }
        }
    }
}

/* 801CCD74-801CCE5C       .text titleOpenProc__12dMenu_Item_cFss */
void dMenu_Item_c::titleOpenProc(s16 param_0, s16 param_1) {
    const s16 temp_r29 = g_miHIO.field_0x28;
    if (param_1 >= param_0) {
        fopMsgM_valueIncrease(param_1, param_0, 0);
        titleTrans(0.0f, temp_r29 * fopMsgM_valueIncrease(param_1, param_1 - param_0, 0));

        fopMsgM_setInitAlpha(&field_0x9a8);
        fopMsgM_setInitAlpha(&field_0x9e0);

        if (param_0 == 1) {
            mDoAud_seStart(JA_SE_ITM_MENU_PANEL_IN);
        }
    }
}

/* 801CCE5C-801CCF50       .text noteOpenProc__12dMenu_Item_cFss */
void dMenu_Item_c::noteOpenProc(s16 param_0, s16 param_1) {
    s16 temp_r29 = g_miHIO.field_0x2A;
    s16 temp_r28 = g_miHIO.field_0x3E;
    if (param_1 >= param_0) {
        fopMsgM_valueIncrease(param_1, param_0, 0);
        f32 temp_f1 = fopMsgM_valueIncrease(param_1, param_1 - param_0, 0);
        noteRotate(temp_r28 * temp_f1, field_0x820.mUserArea + (temp_f1 * (temp_r29 - field_0x820.mUserArea)));

        for (int i = 0; i < 6; i++) {
            fopMsgM_setInitAlpha(&field_0x7b0);
            fopMsgM_setInitAlpha(&field_0x7e8);
        }
    }
}

/* 801CCF50-801CD004       .text nameOpenProc__12dMenu_Item_cFss */
void dMenu_Item_c::nameOpenProc(s16 param_0, s16 param_1) {
    const s16 temp_r29 = g_miHIO.field_0x2C;
    if (param_1 >= param_0) {
        fopMsgM_valueIncrease(param_1, param_0, 0);
        nameTrans(0.0f, temp_r29 * fopMsgM_valueIncrease(param_1, param_1 - param_0, 0));

        fopMsgM_setInitAlpha(&field_0x890[0]);
        fopMsgM_setInitAlpha(&field_0x900);
        fopMsgM_setInitAlpha(&field_0x938);
    }
}

/* 801CD004-801CD04C       .text numberSet__12dMenu_Item_cFP7J2DPaneUc */
void dMenu_Item_c::numberSet(J2DPane* i_pic, u8 i_no) {
    static const char* number[] = {
        "count_num_0.bti",
        "count_num_1.bti",
        "count_num_2.bti",
        "count_num_3.bti",
        "count_num_4.bti",
        "count_num_5.bti",
        "count_num_6.bti",
        "count_num_7.bti",
        "count_num_8.bti",
        "count_num_9.bti",
    };

    if (i_no >= 10) {
        i_no = 0;
    }
    ((J2DPicture*)i_pic)->changeTexture(number[i_no], 0);
}

/* 801CD04C-801CD194       .text numberColor__12dMenu_Item_cFP7J2DPaneUc */
void dMenu_Item_c::numberColor(J2DPane* i_pic, u8 param_1) {
    switch (param_1) {
    case 1:
        ((J2DPicture*)i_pic)->setWhite(0xFFC832FF);
        ((J2DPicture*)i_pic)->setBlack(0x1E1E1E00);
        break;
    case 2:
        ((J2DPicture*)i_pic)->setWhite(0xB4B4B4FF);
        ((J2DPicture*)i_pic)->setBlack(0x1E1E1E00);
        break;
    default:
        ((J2DPicture*)i_pic)->setWhite(0xFFFFFFFF);
        ((J2DPicture*)i_pic)->setBlack(0x00000000);
        break;
    }
}

/* 801CD194-801CD3FC       .text itemNumberSet__12dMenu_Item_cFv */
void dMenu_Item_c::itemNumberSet() {
    numberSet(field_0x1540.pane, dComIfGs_getPictureNum());
    if (dComIfGs_getPictureNum() == 0) {
        numberColor(field_0x1540.pane, 2);
    } else if (dComIfGs_getPictureNum() == 3) {
        numberColor(field_0x1540.pane, 1);
    } else {
        numberColor(field_0x1540.pane, 0);
    }
    field_0x241e = dComIfGs_getPictureNum();

    if (dComIfGs_getArrowNum() == 0) {
        numberColor(field_0x1578.pane, 2);
        numberColor(field_0x15b0.pane, 2);
    } else if (dComIfGs_getArrowNum() == dComIfGs_getArrowMax()) {
        numberColor(field_0x1578.pane, 1);
        numberColor(field_0x15b0.pane, 1);
    } else {
        numberColor(field_0x1578.pane, 0);
        numberColor(field_0x15b0.pane, 0);
    }

    if (dComIfGs_getArrowNum() < 10) {
        field_0x15b0.pane->hide();
    } else {
        numberSet(field_0x15b0.pane, dComIfGs_getArrowNum() / 10);
    }
    numberSet(field_0x1578.pane, dComIfGs_getArrowNum() % 10);
    field_0x241f = dComIfGs_getArrowNum();

    if (dComIfGs_getBombNum() == 0) {
        numberColor(field_0x15e8.pane, 2);
        numberColor(field_0x1620.pane, 2);
    } else if (dComIfGs_getBombNum() == dComIfGs_getBombMax()) {
        numberColor(field_0x15e8.pane, 1);
        numberColor(field_0x1620.pane, 1);
    } else {
        numberColor(field_0x15e8.pane, 0);
        numberColor(field_0x1620.pane, 0);
    }

    if (dComIfGs_getBombNum() < 10) {
        field_0x1620.pane->hide();
    } else {
        numberSet(field_0x1620.pane, dComIfGs_getBombNum() / 10);
    }
    numberSet(field_0x15e8.pane, dComIfGs_getBombNum() % 10);
    field_0x2420 = dComIfGs_getBombNum();
}

/* 801CD3FC-801CDA14       .text itemCheck__12dMenu_Item_cFi */
// NONMATCHING - comparison chain not getting optimized?
void dMenu_Item_c::itemCheck(int param_0) {
    u8 var_r28 = dComIfGs_getItem(param_0);
    if (var_r28 != 0xFF) {
        if (recollectBossCheck() && (var_r28 == 0x56 || var_r28 == 0x58 || var_r28 == 0x59)) {
            field_0x1658[param_0].pane->hide();
            field_0x1af0[param_0].pane->hide();
        }

        if (var_r28 == 0x35) {
            field_0x1f88[0].pane->show();
            field_0x1f88[1].pane->show();
            field_0x1f88[2].pane->hide();
            var_r28 = 0x27;
        } else if (var_r28 == 0x36) {
            field_0x1f88[0].pane->show();
            field_0x1f88[1].pane->show();
            field_0x1f88[2].pane->show();
            var_r28 = 0x27;
        } else if (var_r28 == 0x59 && (!recollectBossCheck() || (var_r28 != 0x56 && var_r28 != 0x58 && var_r28 != 0x59))) {
            cXyz sp18(field_0x1658[param_0].mPosCenter.x - 320.0f, field_0x1658[param_0].mPosCenter.y - 240.0f, 0.0f);

            if (field_0x23b8[0] == NULL) {
                field_0x23b8[0] = dComIfGp_particle_set2DmenuFore(0x2D, &sp18);
            }

            if (field_0x23b8[1] == NULL) {
                field_0x23b8[1] = dComIfGp_particle_set2DmenuFore(0x2D, &sp18);
            }
        }

        JKRReadTypeResource(itemTexBuffer[param_0], 0xC00, 'TIMG', dItem_data::getTexture(var_r28), dComIfGp_getItemIconArchive());

        #if VERSION >= VERSION_USA
        DCStoreRangeNoSync(itemTexBuffer[param_0], 0xC00);
        #else
        DCFlushRangeNoSync(itemTexBuffer[param_0], 0xC00);
        #endif

        ((J2DPicture*)field_0x1658[param_0].pane)->changeTexture(itemTexBuffer[param_0], 0);
        ((J2DPicture*)field_0x1af0[param_0].pane)->changeTexture(itemTexBuffer[param_0], 0);

        if (param_0 == 8) {
            if (dComIfGs_getItem(param_0) == dItemNo_PICTO_BOX_e) {
                field_0x1658[param_0].pane->show();
                field_0x1af0[param_0].pane->show();
                field_0x1540.pane->show();
            } else if (dComIfGs_getItem(param_0) == dItemNo_DELUXE_PICTO_BOX_e) {
                field_0x1658[param_0].pane->show();
                field_0x1af0[param_0].pane->show();
                field_0x1540.pane->show();
            } else {
                field_0x1658[param_0].pane->hide();
                field_0x1af0[param_0].pane->hide();
                field_0x1540.pane->hide();
            }
        }

        field_0x2406[param_0] = dComIfGs_getItem(param_0);
    } else {
        field_0x1658[param_0].pane->hide();
        field_0x1af0[param_0].pane->hide();

        if (param_0 == 8) {
            field_0x1540.pane->hide();
        } else if (param_0 == 12) {
            field_0x1578.pane->hide();
            field_0x15b0.pane->hide();
        } else if (param_0 == 13) {
            field_0x15e8.pane->hide();
            field_0x1620.pane->hide();
        }
    }
}

/* 801CDA14-801CDB14       .text itemBitCheck__12dMenu_Item_cFb */
void dMenu_Item_c::itemBitCheck(bool param_0) {
    for (int i = 0; i < 21; i++) {
        if (field_0x2406[i] != dComIfGs_getItem(i) || param_0) {
            itemCheck(i);
        }
    }
}

/* 801CDB14-801CDC34       .text arrowLightAnime__12dMenu_Item_cFv */
void dMenu_Item_c::arrowLightAnime() {
    field_0x1f88[0].mUserArea++;
    if (field_0x1f88[0].mUserArea >= 120) {
        field_0x1f88[0].mUserArea = 0;
    }

    f32 temp_f1;
    if (field_0x1f88[0].mUserArea < 60) {
        temp_f1 = fopMsgM_valueIncrease(60, field_0x1f88[0].mUserArea, 0);
    } else {
        temp_f1 = fopMsgM_valueIncrease(60, 120 - field_0x1f88[0].mUserArea, 0);
    }
    f32 temp_f30 = 1.0f - (temp_f1 * 0.39999998f);
    f32 temp_f31 = field_0x1f88[0].mInitAlpha - (field_0x1f88[0].mInitAlpha - 50.0f) * temp_f1;

    for (int i = 0; i < 3; i++) {
        fopMsgM_paneScaleXY(&field_0x1f88[i], temp_f30);
        field_0x1f88[i].mNowAlpha = temp_f31;
    }
}

/* 801CDC34-801CDCF0       .text bottleFwaterCheck__12dMenu_Item_cFv */
// NONMATCHING
int dMenu_Item_c::bottleFwaterCheck() {
    for (int i = 0; i < 4; i++) {
        if (dComIfGs_getItem((u8)(i + 14)) == dItemNo_FOREST_WATER_e) {
            return i;
        }
    }

    return 0;
}

/* 801CDCF0-801CDDC0       .text recollectBossCheck__12dMenu_Item_cFv */
BOOL dMenu_Item_c::recollectBossCheck() {
    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_BOSS_e) {
        if (strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0
            || strcmp(dComIfGp_getStartStageName(), "Xboss1") == 0
            || strcmp(dComIfGp_getStartStageName(), "Xboss2") == 0
            || strcmp(dComIfGp_getStartStageName(), "Xboss3") == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/* 801CDDC0-801CF08C       .text cornerMove__12dMenu_Item_cFv */
void dMenu_Item_c::cornerMove() {
    J2DWindow::TContentsColor sp30;
    JUtility::TColor sp1C;

    field_0x23fa++;
    if (field_0x23fa >= 240) {
        field_0x23fa = 0;
    }

    f32 temp_f1 = fopMsgM_valueIncrease(60, field_0x23fa % 60, 2);
    if (field_0x23fa < 60) {
        sp30.mTL.r = field_0x2320.mTL.r + (temp_f1 * (field_0x2320.mBL.r - field_0x2320.mTL.r));
        sp30.mTL.g = field_0x2320.mTL.g + (temp_f1 * (field_0x2320.mBL.g - field_0x2320.mTL.g));
        sp30.mTL.b = field_0x2320.mTL.b + (temp_f1 * (field_0x2320.mBL.b - field_0x2320.mTL.b));
        sp30.mTL.a = field_0x2320.mTL.a + (temp_f1 * (field_0x2320.mBL.a - field_0x2320.mTL.a));

        sp30.mTR.r = field_0x2320.mTR.r + (temp_f1 * (field_0x2320.mTL.r - field_0x2320.mTR.r));
        sp30.mTR.g = field_0x2320.mTR.g + (temp_f1 * (field_0x2320.mTL.g - field_0x2320.mTR.g));
        sp30.mTR.b = field_0x2320.mTR.b + (temp_f1 * (field_0x2320.mTL.b - field_0x2320.mTR.b));
        sp30.mTR.a = field_0x2320.mTR.a + (temp_f1 * (field_0x2320.mTL.a - field_0x2320.mTR.a));

        sp30.mBL.r = field_0x2320.mBL.r + (temp_f1 * (field_0x2320.mBR.r - field_0x2320.mBL.r));
        sp30.mBL.g = field_0x2320.mBL.g + (temp_f1 * (field_0x2320.mBR.g - field_0x2320.mBL.g));
        sp30.mBL.b = field_0x2320.mBL.b + (temp_f1 * (field_0x2320.mBR.b - field_0x2320.mBL.b));
        sp30.mBL.a = field_0x2320.mBL.a + (temp_f1 * (field_0x2320.mBR.a - field_0x2320.mBL.a));

        sp30.mBR.r = field_0x2320.mBR.r + (temp_f1 * (field_0x2320.mTR.r - field_0x2320.mBR.r));
        sp30.mBR.g = field_0x2320.mBR.g + (temp_f1 * (field_0x2320.mTR.g - field_0x2320.mBR.g));
        sp30.mBR.b = field_0x2320.mBR.b + (temp_f1 * (field_0x2320.mTR.b - field_0x2320.mBR.b));
        sp30.mBR.a = field_0x2320.mBR.a + (temp_f1 * (field_0x2320.mTR.a - field_0x2320.mBR.a));
    } else if (field_0x23fa < 120) {
        sp30.mTR.r = field_0x2320.mTL.r + (temp_f1 * (field_0x2320.mBL.r - field_0x2320.mTL.r));
        sp30.mTR.g = field_0x2320.mTL.g + (temp_f1 * (field_0x2320.mBL.g - field_0x2320.mTL.g));
        sp30.mTR.b = field_0x2320.mTL.b + (temp_f1 * (field_0x2320.mBL.b - field_0x2320.mTL.b));
        sp30.mTR.a = field_0x2320.mTL.a + (temp_f1 * (field_0x2320.mBL.a - field_0x2320.mTL.a));

        sp30.mBR.r = field_0x2320.mTR.r + (temp_f1 * (field_0x2320.mTL.r - field_0x2320.mTR.r));
        sp30.mBR.g = field_0x2320.mTR.g + (temp_f1 * (field_0x2320.mTL.g - field_0x2320.mTR.g));
        sp30.mBR.b = field_0x2320.mTR.b + (temp_f1 * (field_0x2320.mTL.b - field_0x2320.mTR.b));
        sp30.mBR.a = field_0x2320.mTR.a + (temp_f1 * (field_0x2320.mTL.a - field_0x2320.mTR.a));

        sp30.mTL.r = field_0x2320.mBL.r + (temp_f1 * (field_0x2320.mBR.r - field_0x2320.mBL.r));
        sp30.mTL.g = field_0x2320.mBL.g + (temp_f1 * (field_0x2320.mBR.g - field_0x2320.mBL.g));
        sp30.mTL.b = field_0x2320.mBL.b + (temp_f1 * (field_0x2320.mBR.b - field_0x2320.mBL.b));
        sp30.mTL.a = field_0x2320.mBL.a + (temp_f1 * (field_0x2320.mBR.a - field_0x2320.mBL.a));

        sp30.mBL.r = field_0x2320.mBR.r + (temp_f1 * (field_0x2320.mTR.r - field_0x2320.mBR.r));
        sp30.mBL.g = field_0x2320.mBR.g + (temp_f1 * (field_0x2320.mTR.g - field_0x2320.mBR.g));
        sp30.mBL.b = field_0x2320.mBR.b + (temp_f1 * (field_0x2320.mTR.b - field_0x2320.mBR.b));
        sp30.mBL.a = field_0x2320.mBR.a + (temp_f1 * (field_0x2320.mTR.a - field_0x2320.mBR.a));
    } else if (field_0x23fa < 180) {
        sp30.mBR.r = field_0x2320.mTL.r + (temp_f1 * (field_0x2320.mBL.r - field_0x2320.mTL.r));
        sp30.mBR.g = field_0x2320.mTL.g + (temp_f1 * (field_0x2320.mBL.g - field_0x2320.mTL.g));
        sp30.mBR.b = field_0x2320.mTL.b + (temp_f1 * (field_0x2320.mBL.b - field_0x2320.mTL.b));
        sp30.mBR.a = field_0x2320.mTL.a + (temp_f1 * (field_0x2320.mBL.a - field_0x2320.mTL.a));

        sp30.mBL.r = field_0x2320.mTR.r + (temp_f1 * (field_0x2320.mTL.r - field_0x2320.mTR.r));
        sp30.mBL.g = field_0x2320.mTR.g + (temp_f1 * (field_0x2320.mTL.g - field_0x2320.mTR.g));
        sp30.mBL.b = field_0x2320.mTR.b + (temp_f1 * (field_0x2320.mTL.b - field_0x2320.mTR.b));
        sp30.mBL.a = field_0x2320.mTR.a + (temp_f1 * (field_0x2320.mTL.a - field_0x2320.mTR.a));

        sp30.mTR.r = field_0x2320.mBL.r + (temp_f1 * (field_0x2320.mBR.r - field_0x2320.mBL.r));
        sp30.mTR.g = field_0x2320.mBL.g + (temp_f1 * (field_0x2320.mBR.g - field_0x2320.mBL.g));
        sp30.mTR.b = field_0x2320.mBL.b + (temp_f1 * (field_0x2320.mBR.b - field_0x2320.mBL.b));
        sp30.mTR.a = field_0x2320.mBL.a + (temp_f1 * (field_0x2320.mBR.a - field_0x2320.mBL.a));

        sp30.mTL.r = field_0x2320.mBR.r + (temp_f1 * (field_0x2320.mTR.r - field_0x2320.mBR.r));
        sp30.mTL.g = field_0x2320.mBR.g + (temp_f1 * (field_0x2320.mTR.g - field_0x2320.mBR.g));
        sp30.mTL.b = field_0x2320.mBR.b + (temp_f1 * (field_0x2320.mTR.b - field_0x2320.mBR.b));
        sp30.mTL.a = field_0x2320.mBR.a + (temp_f1 * (field_0x2320.mTR.a - field_0x2320.mBR.a));
    } else {
        sp30.mBL.r = field_0x2320.mTL.r + (temp_f1 * (field_0x2320.mBL.r - field_0x2320.mTL.r));
        sp30.mBL.g = field_0x2320.mTL.g + (temp_f1 * (field_0x2320.mBL.g - field_0x2320.mTL.g));
        sp30.mBL.b = field_0x2320.mTL.b + (temp_f1 * (field_0x2320.mBL.b - field_0x2320.mTL.b));
        sp30.mBL.a = field_0x2320.mTL.a + (temp_f1 * (field_0x2320.mBL.a - field_0x2320.mTL.a));

        sp30.mTL.r = field_0x2320.mTR.r + (temp_f1 * (field_0x2320.mTL.r - field_0x2320.mTR.r));
        sp30.mTL.g = field_0x2320.mTR.g + (temp_f1 * (field_0x2320.mTL.g - field_0x2320.mTR.g));
        sp30.mTL.b = field_0x2320.mTR.b + (temp_f1 * (field_0x2320.mTL.b - field_0x2320.mTR.b));
        sp30.mTL.a = field_0x2320.mTR.a + (temp_f1 * (field_0x2320.mTL.a - field_0x2320.mTR.a));

        sp30.mBR.r = field_0x2320.mBL.r + (temp_f1 * (field_0x2320.mBR.r - field_0x2320.mBL.r));
        sp30.mBR.g = field_0x2320.mBL.g + (temp_f1 * (field_0x2320.mBR.g - field_0x2320.mBL.g));
        sp30.mBR.b = field_0x2320.mBL.b + (temp_f1 * (field_0x2320.mBR.b - field_0x2320.mBL.b));
        sp30.mBR.a = field_0x2320.mBL.a + (temp_f1 * (field_0x2320.mBR.a - field_0x2320.mBL.a));

        sp30.mTR.r = field_0x2320.mBR.r + (temp_f1 * (field_0x2320.mTR.r - field_0x2320.mBR.r));
        sp30.mTR.g = field_0x2320.mBR.g + (temp_f1 * (field_0x2320.mTR.g - field_0x2320.mBR.g));
        sp30.mTR.b = field_0x2320.mBR.b + (temp_f1 * (field_0x2320.mTR.b - field_0x2320.mBR.b));
        sp30.mTR.a = field_0x2320.mBR.a + (temp_f1 * (field_0x2320.mTR.a - field_0x2320.mBR.a));
    }

    ((J2DWindow*)field_0x14d0.pane)->setContentsColor(sp30);

    field_0x23fc++;
    if (field_0x23fc >= 40) {
        field_0x23fc = 0;
    }

    f32 temp_f1_2;
    if (field_0x23fc < 20) {
        temp_f1_2 = fopMsgM_valueIncrease(20, field_0x23fc, 0);
    } else {
        temp_f1_2 = fopMsgM_valueIncrease(20, 40 - field_0x23fc, 0);
    }

    sp1C.set(0xFF, 128.0f - (temp_f1_2 * -42.0f), 0x00, 0xFF);
    ((J2DWindow*)field_0x14d0.pane)->setWhite(sp1C);
}

/* 801CF08C-801CF12C       .text equipBeastItem__12dMenu_Item_cFi */
int dMenu_Item_c::equipBeastItem(int param_0) {
    u8 beast_item = dComIfGs_getItemBeast(param_0);
    u8 var_r3 = 0;

    switch (beast_item) {
    case 0x45:
        var_r3 = 0;
        break;
    case 0x46:
        var_r3 = 1;
        break;
    case 0x47:
        var_r3 = 2;
        break;
    case 0x48:
        var_r3 = 3;
        break;
    case 0x49:
        var_r3 = 4;
        break;
    case 0x4A:
        var_r3 = 5;
        break;
    case 0x4B:
        var_r3 = 6;
        break;
    case 0x1F:
        var_r3 = 7;
        break;
    }

    return var_r3;
}

/* 801CF12C-801CF510       .text _create__12dMenu_Item_cFv */
void dMenu_Item_c::_create() {
    scrn = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(2569, 2574, 2647, 2647), scrn != NULL);
    scrn->set("menu_item_02.blo", archive);

    stick = new STControl(5, 2, 3, 2);
    JUT_ASSERT(VERSION_SELECT(2573, 2578, 2651, 2651), stick != NULL);
    stick->setWaitParm(5, 2, 3, 2, 0.9f, 0.5f, 0, 0x800);

    outFont = new dDlst_2DOutFont_c();
    JUT_ASSERT(VERSION_SELECT(2577, 2582, 2655, 2655), outFont != NULL);
    #if VERSION >= VERSION_USA
    outFont->m74 = 1;
    #endif

    dMs_c = new dMenu_save_c();
    JUT_ASSERT(VERSION_SELECT(2580, 2585, 2659, 2659), dMs_c != NULL);
    dMs_c->setUseType(0);
    dMs_c->_create();

    itemMode = 0;
    field_0x23b8[0] = NULL;
    field_0x23b8[1] = NULL;

    screenSet();
    initialize();

    g_miHIO.mNo = mDoHIO_createChild("アイテム画面", &g_miHIO); // "Item Screen"

    for (int i = 0; i < 4; i++) {
        ((J2DPicture*)field_0xa18[i].pane)->append("cursor_00_02.bti", 1.0f);
        field_0x23c0[i] = field_0xa18[i].mPosCenterOrig.x - field_0x1658[0].mPosCenterOrig.x;
        field_0x23d0[i] = field_0xa18[i].mPosCenterOrig.y - field_0x1658[0].mPosCenterOrig.y;
    }

    for (int i = 0; i < 15; i++) {
        ((J2DPicture*)field_0xb0[i].pane)->changeTexture("font_07_02.bti", 0);
        fopMsgM_blendInit(&field_0xb0[i], "font_00.bti");
    }

    field_0x2400 = 0;
    field_0x2401 = 0;
    field_0x2402 = 0;
    field_0x2420 = 0;
    field_0x241f = 0;
    field_0x241e = 0;
    field_0x2404 = 3;
    field_0x2403 = 3;
    field_0x2405 = 3;

    for (int i = 0; i < 21; i++) {
        itemCheck(i);
    }

    cursorAnime();
}

/* 801CF510-801CF618       .text _delete__12dMenu_Item_cFv */
void dMenu_Item_c::_delete() {
    for (int i = 0; i < 2; i++) {
        if (field_0x23b8[i] != NULL) {
            field_0x23b8[i]->becomeInvalidEmitter();
            field_0x23b8[i]->quitImmortalEmitter();
            field_0x23b8[i] = NULL;
        }
    }

    delete scrn;
    delete stick;

    if (outFont != NULL) {
        delete outFont;
    }
    
    dMs_c->_delete();
    delete dMs_c;

    archive->removeResourceAll();
    mDoHIO_deleteChild(g_miHIO.mNo);
}

/* 801CF618-801D0524       .text _move__12dMenu_Item_cFv */
// NONMATCHING - weird branch flow
void dMenu_Item_c::_move() {
    u8 var_r30 = nowItem;
    itemBitCheck(false);

    if (itemMode == 0) {
        if (!noteCheck()) {
            if (!CPad_CHECK_TRIG_START(0) && !mDoCPd_R_LOCK_BUTTON(0) && !mDoCPd_L_LOCK_BUTTON(0)) {
                if (CPad_CHECK_TRIG_A(0)) {
                    if (dMeter_subWinFlag() && nowItem == 0xFF) {
                        subWindowDelete();
                        mDoAud_seStart(JA_SE_ITM_MENU_CANCEL);
                    } else if (nowItem == 0x15) {
                        itemMode = 1;
                        dMs_c->initialize();
                        mDoAud_seStart(JA_SE_ITM_MENU_OPT_IN);
                    } else if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
                        if (!recollectBossCheck() || 
                            (dComIfGs_getItem(nowItem) != dItemNo_WATER_BOTTLE_e
                                && dComIfGs_getItem(nowItem) != dItemNo_FIREFLY_BOTTLE_e
                                && dComIfGs_getItem(nowItem) != dItemNo_FOREST_WATER_e))
                        {
                            fopMsgM_setInitAlpha(&field_0x740);
                            fopMsgM_setInitAlpha(&field_0x778);
                            fopMsgM_setInitAlpha(&field_0x7b0);
                            fopMsgM_setInitAlpha(&field_0x7e8);
                            fopMsgM_setInitAlpha(&field_0x820);
                            field_0x7e8.mUserArea = 1;
                            field_0x7b0.mUserArea = 1;
                            itemnoteSet();
                            mDoAud_seStart(JA_SE_ITEM_EXP_OPEN);
                        }
                    }
                } else if (CPad_CHECK_TRIG_B(0)) {
                    if (dMeter_subWinFlag()) {
                        subWindowDelete();
                        mDoAud_seStart(JA_SE_ITM_MENU_CANCEL);
                    }
                } else if (CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0) || CPad_CHECK_TRIG_Z(0)) {
                    if (dMeter_subWinFlag() && nowItem == 0xFF) {
                        subWindowDelete();
                        mDoAud_seStart(JA_SE_ITM_MENU_CANCEL);
                    } else if (nowItem != 0x15) {
                        if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
                            if (dMeter_subWinFlag()) {
                                if (nowItem == 0xFF) {
                                    subWindowDelete();
                                    mDoAud_seStart(JA_SE_ITM_MENU_CANCEL);
                                } else {
                                    subItemDecide();
                                }
                            } else if (!recollectBossCheck() || 
                                (dComIfGs_getItem(nowItem) != dItemNo_WATER_BOTTLE_e
                                    && dComIfGs_getItem(nowItem) != dItemNo_FIREFLY_BOTTLE_e
                                    && dComIfGs_getItem(nowItem) != dItemNo_FOREST_WATER_e))
                            {
                                itemDecide();
                            }
                        }
                    }
                } else {
                    if (dMeter_subWinFlag()) {
                        cursorSubMove();
                    } else {
                        cursorMainMove();
                    }

                    itemScale();

                    if (nowItem != var_r30 && var_r30 == 0xC) {
                        for (int i = 0; i < 3; i++) {
                            fopMsgM_paneTrans(&field_0x1f88[i], 0.0f, 0.0f);
                        }
                    }
                }
            }
        } else {
            noteAppear();
        }

        if (field_0x2404 != 3) {
            itemMove();
        }

        if (nowItem == 0x15) {
            itemnameMove();
        } else if (dComIfGs_getItem(nowItem) != 0xFF) {
            if (!recollectBossCheck() || 
                (dComIfGs_getItem(nowItem) != dItemNo_WATER_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FIREFLY_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FOREST_WATER_e))
            {
                itemnameMove();
            } else {
                fopMsgM_setNowAlphaZero(&field_0x890[0]);
                fopMsgM_setNowAlphaZero(&field_0x890[1]);
                fopMsgM_setNowAlphaZero(&field_0x858);
            }
        }

        outFontMove();
        cursorAnime();
        cornerMove();

        if (dComIfGs_getItem(12) == dItemNo_MAGIC_ARROW_e || dComIfGs_getItem(12) == dItemNo_LIGHT_ARROW_e) {
            arrowLightAnime();
        }

        checkMove();

        int temp_r3 = bottleFwaterCheck();
        if (temp_r3 != 0) {
            for (int i = 0; i < 2; i++) {
                if (field_0x23b8[i] != NULL) {
                    cXyz sp8(
                        field_0x1658[temp_r3].mPosCenterOrig.x - 320.0f,
                        field_0x1658[temp_r3].mPosCenterOrig.y - 240.0f,
                        0.0f
                    );
                    field_0x23b8[i]->setGlobalTranslation(sp8);
                    field_0x23b8[i]->playDrawParticle();
                    field_0x23b8[i]->setGlobalAlpha(0xFF);
                }
            }
        }
    } else if (itemMode == 1) {
        switch (dMs_c->getSaveStatus()) {
        case 0:
            itemMode = 0;
            break;
        case 1:
            dMs_c->_open();
            break;
        case 2:
            dMs_c->_move();
            break;
        case 3:
            dMs_c->_close();
            break;
        }

        if (bottleFwaterCheck()) {
            for (int i = 0; i < 2; i++) {
                if (field_0x23b8[i] != NULL) {
                    field_0x23b8[i]->setGlobalAlpha(0);
                }
            }
        }

        dComIfGp_setAStatusForce(7);
    }

    if (nowItem != 0x15) {
        if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
            dComIfGp_setDoStatusForce(0x21);
        } else {
            dComIfGp_setDoStatusForce(0);
            dComIfGp_setDoStatus(0);
        }
    } else {
        dComIfGp_setDoStatusForce(0x17);
    }
}

/* 801D0524-801D0F50       .text _draw__12dMenu_Item_cFv */
void dMenu_Item_c::_draw() {
    if (field_0x2422 == 0) {
        fopMsgM_setAlpha(&field_0x740);
        fopMsgM_setAlpha(&field_0x778);
        fopMsgM_setAlpha(&field_0x7b0);
        fopMsgM_setAlpha(&field_0x7e8);
        fopMsgM_setAlpha(&field_0x820);
        outFont->setAlpha(field_0x858.mNowAlpha);
        fopMsgM_setAlpha(&field_0x890[0]);
        fopMsgM_setAlpha(&field_0x890[1]);
        fopMsgM_setAlpha(&field_0x900);
        fopMsgM_setAlpha(&field_0x938);
        fopMsgM_setAlpha(&field_0x970);
        fopMsgM_setAlpha(&field_0x9a8);
        fopMsgM_setAlpha(&field_0x9e0);

        for (int i = 0; i < 4; i++) {
            fopMsgM_setAlpha(&field_0xa18[i]);
        }

        for (int i = 0; i < 8; i++) {
            fopMsgM_setAlpha(&field_0xaf8[i]);
            fopMsgM_setAlpha(&field_0xcb8[i]);
            fopMsgM_setAlpha(&field_0xe78[i]);
            fopMsgM_setAlpha(&field_0x1070[i]);
        }

        fopMsgM_setAlpha(&field_0x1038);
        fopMsgM_setAlpha(&field_0x1230);

        for (int i = 0; i < 9; i++) {
            fopMsgM_setAlpha(&field_0x1268[i]);
        }

        fopMsgM_setAlpha(&field_0x1460);
        fopMsgM_setAlpha(&field_0x1498);
        fopMsgM_setAlpha(&field_0x14d0);
        fopMsgM_setAlpha(&field_0x1508);
        fopMsgM_setAlpha(&field_0x1540);
        fopMsgM_setAlpha(&field_0x1578);
        fopMsgM_setAlpha(&field_0x15b0);
        fopMsgM_setAlpha(&field_0x15e8);
        fopMsgM_setAlpha(&field_0x1620);

        for (int i = 0; i < 21; i++) {
            fopMsgM_setAlpha(&field_0x1658[i]);
            fopMsgM_setAlpha(&field_0x1af0[i]);
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setAlpha(&field_0x1f88[i]);
            fopMsgM_setAlpha(&field_0x2030[i]);
        }

        for (int i = 0; i < 6; i++) {
            fopMsgM_setAlpha(&field_0x20d8[i]);
        }

        fopMsgM_setAlpha(&field_0x2228);
        fopMsgM_setAlpha(&field_0x2260);
        fopMsgM_setAlpha(&field_0x2298);
        fopMsgM_setAlpha(&field_0x22d0);
    } else {
        f32 temp_f1 = fopMsgM_valueIncrease(10, timer, 0);
        if (triggerInfo != 1 && triggerInfo != 2) {
            field_0x740.pane->setAlpha(field_0x740.mNowAlpha * temp_f1);
            field_0x778.pane->setAlpha(field_0x778.mNowAlpha * temp_f1);
            field_0x7b0.pane->setAlpha(field_0x7b0.mNowAlpha * temp_f1);
            field_0x7e8.pane->setAlpha(field_0x7e8.mNowAlpha * temp_f1);
            field_0x820.pane->setAlpha(field_0x820.mNowAlpha * temp_f1);
            outFont->setAlpha(field_0x858.mNowAlpha * temp_f1);
            field_0x890[0].pane->setAlpha(field_0x890[0].mNowAlpha * temp_f1);
            field_0x890[1].pane->setAlpha(field_0x890[1].mNowAlpha * temp_f1);
            field_0x900.pane->setAlpha(field_0x900.mNowAlpha * temp_f1);
            field_0x938.pane->setAlpha(field_0x938.mNowAlpha * temp_f1);
            field_0x9a8.pane->setAlpha(field_0x9a8.mNowAlpha * temp_f1);
            field_0x9e0.pane->setAlpha(field_0x9e0.mNowAlpha * temp_f1);
        }

        field_0x970.pane->setAlpha(field_0x970.mNowAlpha * temp_f1);

        for (int i = 0; i < 4; i++) {
            field_0xa18[i].pane->setAlpha(field_0xa18[i].mNowAlpha * temp_f1);
        }

        for (int i = 0; i < 8; i++) {
            field_0xaf8[i].pane->setAlpha(field_0xaf8[i].mNowAlpha * temp_f1);
            field_0xcb8[i].pane->setAlpha(field_0xcb8[i].mNowAlpha * temp_f1);
            field_0xe78[i].pane->setAlpha(field_0xe78[i].mNowAlpha * temp_f1);
            field_0x1070[i].pane->setAlpha(field_0x1070[i].mNowAlpha * temp_f1);
        }

        field_0x1038.pane->setAlpha(field_0x1038.mNowAlpha * temp_f1);
        field_0x1230.pane->setAlpha(field_0x1230.mNowAlpha * temp_f1);

        for (int i = 0; i < 9; i++) {
            field_0x1268[i].pane->setAlpha(field_0x1268[i].mNowAlpha * temp_f1);
        }

        field_0x1460.pane->setAlpha(field_0x1460.mNowAlpha * temp_f1);
        field_0x1498.pane->setAlpha(field_0x1498.mNowAlpha * temp_f1);
        field_0x14d0.pane->setAlpha(field_0x14d0.mNowAlpha * temp_f1);
        field_0x1508.pane->setAlpha(field_0x1508.mNowAlpha * temp_f1);
        field_0x1540.pane->setAlpha(field_0x1540.mNowAlpha * temp_f1);
        field_0x1578.pane->setAlpha(field_0x1578.mNowAlpha * temp_f1);
        field_0x15b0.pane->setAlpha(field_0x15b0.mNowAlpha * temp_f1);
        field_0x15e8.pane->setAlpha(field_0x15e8.mNowAlpha * temp_f1);
        field_0x1620.pane->setAlpha(field_0x1620.mNowAlpha * temp_f1);

        for (int i = 0; i < 21; i++) {
            field_0x1658[i].pane->setAlpha(field_0x1658[i].mNowAlpha * temp_f1);
            field_0x1af0[i].pane->setAlpha(field_0x1af0[i].mNowAlpha * temp_f1);
        }

        for (int i = 0; i < 3; i++) {
            field_0x1f88[i].pane->setAlpha(field_0x1f88[i].mNowAlpha * temp_f1);
            field_0x2030[i].pane->setAlpha(field_0x2030[i].mNowAlpha * temp_f1);
        }

        for (int i = 0; i < 6; i++) {
            field_0x20d8[i].pane->setAlpha(field_0x20d8[i].mNowAlpha * temp_f1);
        }

        field_0x2228.pane->setAlpha(field_0x2228.mNowAlpha * temp_f1);
        field_0x2260.pane->setAlpha(field_0x2260.mNowAlpha * temp_f1);
        field_0x2298.pane->setAlpha(field_0x2298.mNowAlpha * temp_f1);
        field_0x22d0.pane->setAlpha(field_0x22d0.mNowAlpha * temp_f1);
    }

    outFontDraw();

    J2DOrthoGraph* port = dComIfGp_getCurrentGrafPort();
    port->setPort();
    scrn->draw(0.0f, 0.0f, port);

    dMs_c->_draw();
}

/* 801D0F50-801D1438       .text _open__12dMenu_Item_cFv */
// NONMATCHING - small branching issue
bool dMenu_Item_c::_open() {
    const s16 var_r29 = g_miHIO.field_0x26;
    bool rt = false;

    if (timer == 0) {
        for (int i = 0; i < 2; i++) {
            strcpy(name[i], "");
            strcpy(note[i], "");
            ((J2DTextBox*)field_0x890[i].pane)->setString(name[i]);
        }

        ((J2DTextBox*)field_0x778.pane)->setString(note[0]);
        ((J2DTextBox*)field_0x740.pane)->setString(note[1]);

        itemnameSet();

        if (nowItem != 0x15) {
            if (!recollectBossCheck() || 
                (dComIfGs_getItem(nowItem) != dItemNo_WATER_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FIREFLY_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FOREST_WATER_e))
            {
                itemnoteSet();

                if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
                    dComIfGp_setDoStatusForce(0x21);
                } else {
                    dComIfGp_setDoStatusForce(0);
                    dComIfGp_setDoStatus(0);
                }
            }
        } else {
            dComIfGp_setDoStatusForce(0x17);
        }
    }

    timer++;
    if (timer <= 10 && timer > 0) {
        if (triggerInfo == 2) {
            mainOpenProc(timer, 10, var_r29);
        } else {
            mainOpenProc(timer, 10, -var_r29);
        }

        titleOpenProc(timer, 10);
        noteOpenProc(timer, 10);
        nameOpenProc(timer, 10);
    }

    if (timer >= 10) {
        rt = true;
        mDoAud_seStart(JA_SE_ITM_MENU_ITEMS_IN);
    }

    return rt;
}

/* 801D1438-801D1CD4       .text _close__12dMenu_Item_cFv */
bool dMenu_Item_c::_close() {
    bool var_r30 = false;
    timer--;

    f32 temp_f29 = g_miHIO.field_0x26 * fopMsgM_valueIncrease(10, 10 - timer, 0);
    f32 temp_f28 = g_miHIO.field_0x28 * fopMsgM_valueIncrease(10, 10 - timer, 0);
    f32 temp_f30 = g_miHIO.field_0x2C * fopMsgM_valueIncrease(10, 10 - timer, 0);
    f32 temp_f31 = fopMsgM_valueIncrease(10, 10 - timer, 0);

    f32 temp_f0 = fopMsgM_valueIncrease(10, timer, 0);
    for (int i = 0; i < 2; i++) {
        if (field_0x23b8[i] != NULL) {
            field_0x23b8[i]->setGlobalAlpha(255.0f * temp_f0);
        }
    }

    f32 angle;
    f32 rotation;
    if (triggerInfo == 2) {
        mainTrans(-temp_f29, 0.0f);
        titleTrans(0.0f, temp_f28);

        angle = field_0x820.mUserArea + (g_miHIO.field_0x2A - field_0x820.mUserArea) * temp_f31;
        rotation = g_miHIO.field_0x3E * temp_f31;

        noteRotate(rotation, angle);
        nameTrans(0.0f, temp_f30);
    } else if (triggerInfo == 1) {
        mainTrans(temp_f29, 0.0f);
        titleTrans(0.0f, temp_f28);

        angle = field_0x820.mUserArea + (g_miHIO.field_0x2A - field_0x820.mUserArea) * temp_f31;
        rotation = g_miHIO.field_0x3E * temp_f31;

        noteRotate(rotation, angle);
        nameTrans(0.0f, temp_f30);
    }

    if (timer > 0) {
        field_0x2422 = 1;
    } else {
        var_r30 = true;
        field_0x2422 = 0;

        for (int i = 0; i < 15; i++) {
            fopMsgM_setNowAlphaZero(&field_0xb0[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x740);
        fopMsgM_setNowAlphaZero(&field_0x778);
        fopMsgM_setNowAlphaZero(&field_0x7b0);
        fopMsgM_setNowAlphaZero(&field_0x7e8);
        fopMsgM_setNowAlphaZero(&field_0x820);
        fopMsgM_setNowAlphaZero(&field_0x858);
        fopMsgM_setNowAlphaZero(&field_0x890[0]);
        fopMsgM_setNowAlphaZero(&field_0x890[1]);
        fopMsgM_setNowAlphaZero(&field_0x900);
        fopMsgM_setNowAlphaZero(&field_0x938);
        fopMsgM_setNowAlphaZero(&field_0x970);
        fopMsgM_setNowAlphaZero(&field_0x9a8);
        fopMsgM_setNowAlphaZero(&field_0x9e0);

        for (int i = 0; i < 4; i++) {
            fopMsgM_setNowAlphaZero(&field_0xa18[i]);
        }

        for (int i = 0; i < 8; i++) {
            fopMsgM_setNowAlphaZero(&field_0xaf8[i]);
            fopMsgM_setNowAlphaZero(&field_0xcb8[i]);
            fopMsgM_setNowAlphaZero(&field_0xe78[i]);
            fopMsgM_setNowAlphaZero(&field_0x1070[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x1038);
        fopMsgM_setNowAlphaZero(&field_0x1230);

        for (int i = 0; i < 9; i++) {
            fopMsgM_setNowAlphaZero(&field_0x1268[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x1460);
        fopMsgM_setNowAlphaZero(&field_0x1498);
        fopMsgM_setNowAlphaZero(&field_0x14d0);
        fopMsgM_setNowAlphaZero(&field_0x1508);
        fopMsgM_setNowAlphaZero(&field_0x1540);
        fopMsgM_setNowAlphaZero(&field_0x1578);
        fopMsgM_setNowAlphaZero(&field_0x15b0);
        fopMsgM_setNowAlphaZero(&field_0x15e8);
        fopMsgM_setNowAlphaZero(&field_0x1620);

        for (int i = 0; i < 21; i++) {
            fopMsgM_setNowAlphaZero(&field_0x1658[i]);
            fopMsgM_setNowAlphaZero(&field_0x1af0[i]);
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setNowAlphaZero(&field_0x2030[i]);
        }

        for (int i = 0; i < 6; i++) {
            fopMsgM_setNowAlphaZero(&field_0x20d8[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x2228);
        fopMsgM_setNowAlphaZero(&field_0x2260);
        fopMsgM_setNowAlphaZero(&field_0x2298);
        fopMsgM_setNowAlphaZero(&field_0x22d0);

        if (field_0x2404 != 3) {
            dComIfGs_setSelectItem(field_0x2404, field_0x2401);
            dComIfGp_setSelectItem(field_0x2404);
            field_0x2404 = 3;

            if (field_0x2403 != 3) {
                dComIfGs_setSelectItem(field_0x2403, field_0x2402);
                dComIfGp_setSelectItem(field_0x2403);
                field_0x2403 = 3;
            }

            mDoAud_seStart(JA_SE_ITM_MENU_SET);
        }

        if (dMeter_subWinFlag()) {
            subWindowDelete();
        }
    }

    return var_r30;
}

/* 801D1CD4-801D21A0       .text _open2__12dMenu_Item_cFv */
// NONMATCHING - small branching issues
bool dMenu_Item_c::_open2() {
    const s16 var_r28 = g_miHIO.field_0x26;
    const s16 var_r30 = g_menuHIO.field_0x92;
    bool var_r29 = false;

    if (timer == 0) {
        for (int i = 0; i < 2; i++) {
            strcpy(name[i], "");
            strcpy(note[i], "");
            ((J2DTextBox*)field_0x890[i].pane)->setString(name[i]);
        }

        ((J2DTextBox*)field_0x778.pane)->setString(note[0]);
        ((J2DTextBox*)field_0x740.pane)->setString(note[1]);

        itemnameSet();

        if (nowItem != 0x15) {
            if (!recollectBossCheck() || 
                (dComIfGs_getItem(nowItem) != dItemNo_WATER_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FIREFLY_BOTTLE_e
                    && dComIfGs_getItem(nowItem) != dItemNo_FOREST_WATER_e))
            {
                itemnoteSet();

                if (dComIfGs_getItem(nowItem) != dItemNo_NONE_e) {
                    dComIfGp_setDoStatusForce(0x21);
                } else {
                    dComIfGp_setDoStatusForce(0);
                    dComIfGp_setDoStatus(0);
                }
            }
        } else {
            dComIfGp_setDoStatusForce(0x17);
        }
    }

    timer++;
    if (timer <= var_r30 && timer > 0) {
        if (triggerInfo == 2) {
            mainOpenProc(timer, var_r30, var_r28);
        } else {
            mainOpenProc(timer, var_r30, -var_r28);
        }

        titleOpenProc(timer, var_r30);
        noteOpenProc(timer, var_r30);
        nameOpenProc(timer, var_r30);
    }

    if (timer >= var_r30) {
        var_r29 = true;
    }

    return var_r29;
}

/* 801D21A0-801D2A4C       .text _close2__12dMenu_Item_cFv */
bool dMenu_Item_c::_close2() {
    bool var_r30 = false;
    timer--;

    f32 temp_f29 = g_miHIO.field_0x26 * fopMsgM_valueIncrease(g_menuHIO.field_0x92, g_menuHIO.field_0x92 - timer, 0);
    f32 temp_f28 = g_miHIO.field_0x28 * fopMsgM_valueIncrease(g_menuHIO.field_0x92, g_menuHIO.field_0x92 - timer, 0);
    f32 temp_f30 = g_miHIO.field_0x2C * fopMsgM_valueIncrease(g_menuHIO.field_0x92, g_menuHIO.field_0x92 - timer, 0);
    f32 temp_f31 = fopMsgM_valueIncrease(g_menuHIO.field_0x92, g_menuHIO.field_0x92 - timer, 0);

    f32 temp_f0 = fopMsgM_valueIncrease(g_menuHIO.field_0x92, timer, 0);
    for (int i = 0; i < 2; i++) {
        if (field_0x23b8[i] != NULL) {
            field_0x23b8[i]->setGlobalAlpha(255.0f * temp_f0);
        }
    }

    f32 angle;
    f32 rotation;
    if (triggerInfo == 2) {
        mainTrans(-temp_f29, 0.0f);
        titleTrans(0.0f, temp_f28);

        angle = field_0x820.mUserArea + (g_miHIO.field_0x2A - field_0x820.mUserArea) * temp_f31;
        rotation = g_miHIO.field_0x3E * temp_f31;

        noteRotate(rotation, angle);
        nameTrans(0.0f, temp_f30);
    } else if (triggerInfo == 1) {
        mainTrans(temp_f29, 0.0f);
        titleTrans(0.0f, temp_f28);

        angle = field_0x820.mUserArea + (g_miHIO.field_0x2A - field_0x820.mUserArea) * temp_f31;
        rotation = g_miHIO.field_0x3E * temp_f31;

        noteRotate(rotation, angle);
        nameTrans(0.0f, temp_f30);
    }

    if (timer > 0) {
        field_0x2422 = 1;
    } else {
        var_r30 = true;
        field_0x2422 = 0;

        for (int i = 0; i < 15; i++) {
            fopMsgM_setNowAlphaZero(&field_0xb0[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x740);
        fopMsgM_setNowAlphaZero(&field_0x778);
        fopMsgM_setNowAlphaZero(&field_0x7b0);
        fopMsgM_setNowAlphaZero(&field_0x7e8);
        fopMsgM_setNowAlphaZero(&field_0x820);
        fopMsgM_setNowAlphaZero(&field_0x858);
        fopMsgM_setNowAlphaZero(&field_0x890[0]);
        fopMsgM_setNowAlphaZero(&field_0x890[1]);
        fopMsgM_setNowAlphaZero(&field_0x900);
        fopMsgM_setNowAlphaZero(&field_0x938);
        fopMsgM_setNowAlphaZero(&field_0x970);
        fopMsgM_setNowAlphaZero(&field_0x9a8);
        fopMsgM_setNowAlphaZero(&field_0x9e0);

        for (int i = 0; i < 4; i++) {
            fopMsgM_setNowAlphaZero(&field_0xa18[i]);
        }

        for (int i = 0; i < 8; i++) {
            fopMsgM_setNowAlphaZero(&field_0xaf8[i]);
            fopMsgM_setNowAlphaZero(&field_0xcb8[i]);
            fopMsgM_setNowAlphaZero(&field_0xe78[i]);
            fopMsgM_setNowAlphaZero(&field_0x1070[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x1038);
        fopMsgM_setNowAlphaZero(&field_0x1230);

        for (int i = 0; i < 9; i++) {
            fopMsgM_setNowAlphaZero(&field_0x1268[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x1460);
        fopMsgM_setNowAlphaZero(&field_0x1498);
        fopMsgM_setNowAlphaZero(&field_0x14d0);
        fopMsgM_setNowAlphaZero(&field_0x1508);
        fopMsgM_setNowAlphaZero(&field_0x1540);
        fopMsgM_setNowAlphaZero(&field_0x1578);
        fopMsgM_setNowAlphaZero(&field_0x15b0);
        fopMsgM_setNowAlphaZero(&field_0x15e8);
        fopMsgM_setNowAlphaZero(&field_0x1620);

        for (int i = 0; i < 21; i++) {
            fopMsgM_setNowAlphaZero(&field_0x1658[i]);
            fopMsgM_setNowAlphaZero(&field_0x1af0[i]);
        }

        for (int i = 0; i < 3; i++) {
            fopMsgM_setNowAlphaZero(&field_0x1f88[i]);
            fopMsgM_setNowAlphaZero(&field_0x2030[i]);
        }

        for (int i = 0; i < 6; i++) {
            fopMsgM_setNowAlphaZero(&field_0x20d8[i]);
        }

        fopMsgM_setNowAlphaZero(&field_0x2228);
        fopMsgM_setNowAlphaZero(&field_0x2260);
        fopMsgM_setNowAlphaZero(&field_0x2298);
        fopMsgM_setNowAlphaZero(&field_0x22d0);

        if (field_0x2404 != 3) {
            dComIfGs_setSelectItem(field_0x2404, field_0x2401);
            dComIfGp_setSelectItem(field_0x2404);
            field_0x2404 = 3;

            if (field_0x2403 != 3) {
                dComIfGs_setSelectItem(field_0x2403, field_0x2402);
                dComIfGp_setSelectItem(field_0x2403);
                field_0x2403 = 3;
            }

            mDoAud_seStart(JA_SE_ITM_MENU_SET);
        }

        if (dMeter_subWinFlag()) {
            subWindowDelete();
        }
    }

    return var_r30;
}
