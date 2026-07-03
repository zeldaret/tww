#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_auction_screen.h"
#include "d/d_meter.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"

void dAs_timerCalc();

/* 8015F550-8015F560       .text __ct__9dAs_HIO_cFv */
dAs_HIO_c::dAs_HIO_c() {}

dAs_HIO_c g_asHIO;

static u8 talkmode;
static u8 talkFlag;
static u8 slotShow;
static u8 gaugeShow;
static u8 gaugeTrans;
static s16 gaugeTransTimer;

/* 8015F560-8015F8D8       .text screenSet__17dAuction_screen_cFv */
void dAuction_screen_c::screenSet() {
    fopMsgM_setPaneData(&field_0xc, scrn1->search('clip'));

    fopMsgM_setPaneData(&field_0x44[0], scrn1->search('nm00'));
    fopMsgM_setPaneData(&field_0x44[1], scrn1->search('nm01'));
    fopMsgM_setPaneData(&field_0x44[2], scrn1->search('nm02'));
    
    fopMsgM_setPaneData(&field_0xec[0], scrn1->search('nm03'));
    fopMsgM_setPaneData(&field_0xec[1], scrn1->search('nm04'));
    fopMsgM_setPaneData(&field_0xec[2], scrn1->search('nm05'));

    fopMsgM_setPaneData(&field_0x194, scrn2->search('icon'));

    fopMsgM_setPaneData(&field_0x1cc[0], scrn2->search('gd00'));
    fopMsgM_setPaneData(&field_0x1cc[1], scrn2->search('gd01'));
    fopMsgM_setPaneData(&field_0x1cc[2], scrn2->search('gd02'));
    fopMsgM_setPaneData(&field_0x1cc[3], scrn2->search('gd03'));
    fopMsgM_setPaneData(&field_0x1cc[4], scrn2->search('gd04'));
    fopMsgM_setPaneData(&field_0x1cc[5], scrn2->search('gd05'));

    fopMsgM_setPaneData(&field_0x31c[0], scrn2->search('ip00'));
    fopMsgM_setPaneData(&field_0x31c[1], scrn2->search('ip01'));
    fopMsgM_setPaneData(&field_0x31c[2], scrn2->search('ip02'));
    fopMsgM_setPaneData(&field_0x31c[3], scrn2->search('ip03'));

    fopMsgM_setPaneData(&field_0x3fc, scrn2->search('met1'));
    fopMsgM_setPaneData(&field_0x434, scrn2->search('met2'));

    ((J2DPicture*)field_0xc.pane)->setWhite(0xFFFFFF00);
}

/* 8015F8D8-8015F910       .text initPosSet__17dAuction_screen_cFP18fopMsgM_pane_classff */
void dAuction_screen_c::initPosSet(fopMsgM_pane_class* i_pane, f32 i_posX, f32 i_posY) {
    i_pane->mPosCenterOrig.x = i_posX + (i_pane->mPosTopLeftOrig.x + (i_pane->mSizeOrig.x / 2));
    i_pane->mPosCenterOrig.y = i_posY + (i_pane->mPosTopLeftOrig.y + (i_pane->mSizeOrig.y / 2));
}

/* 8015F910-8015F9DC       .text gaugeMove__17dAuction_screen_cFv */
void dAuction_screen_c::gaugeMove() {
    if (dComIfGp_getAuctionGauge() <= 100) {
        field_0x434.mSize.x = field_0x3fc.mSizeOrig.x * dComIfGp_getAuctionGauge() / 100.0f;
        field_0x434.mPosCenter.x = field_0x434.mPosTopLeftOrig.x + (field_0x434.mSize.x / 2);
    }

    dAs_timerCalc();

    f32 var_f31 = fopMsgM_valueIncrease(7, 7 - gaugeTransTimer, 0) * 55.0f;
    field_0x3fc.mPosCenter.y = field_0x3fc.mPosCenterOrig.y + var_f31;
    field_0x434.mPosCenter.y = field_0x434.mPosCenterOrig.y + var_f31;
    fopMsgM_cposMove(&field_0x3fc);
    fopMsgM_cposMove(&field_0x434);
}

/* 8015F9DC-8015FA68       .text nowRupeeSet__17dAuction_screen_cFv */
void dAuction_screen_c::nowRupeeSet() {
    s16 n1 = field_0x472 / 100;
    s16 n2 = (field_0x472 % 100) / 10;
    s16 n3 = field_0x472 % 10;

    changeNumberTexture(field_0x44[0].pane, n1);
    changeNumberTexture(field_0x44[1].pane, n2);
    changeNumberTexture(field_0x44[2].pane, n3);
}

/* 8015FA68-8015FAFC       .text nextRupeeSet__17dAuction_screen_cFs */
void dAuction_screen_c::nextRupeeSet(s16 i_rupees) {
    s16 r5 = i_rupees / 100;
    s16 r31 = (i_rupees % 100) / 10;
    s16 r30 = i_rupees % 10;
    changeNumberTexture(field_0xec[0].pane, r5);
    changeNumberTexture(field_0xec[1].pane, r31);
    changeNumberTexture(field_0xec[2].pane, r30);
}

/* 8015FAFC-8015FB48       .text changeNumberTexture__17dAuction_screen_cFP7J2DPanei */
void dAuction_screen_c::changeNumberTexture(J2DPane* i_pane, int i_number) {
    if (i_number < 0 || i_number >= 10) {
        i_number = 0;
    }

    static const char* number[] = {
        "rupy_num_00.bti",
        "rupy_num_01.bti",
        "rupy_num_02.bti",
        "rupy_num_03.bti",
        "rupy_num_04.bti",
        "rupy_num_05.bti",
        "rupy_num_06.bti",
        "rupy_num_07.bti",
        "rupy_num_08.bti",
        "rupy_num_09.bti",
    };

    ((J2DPicture*)i_pane)->changeTexture(number[i_number], 0);
}

/* 8015FB48-8015FE40       .text rupeeCountTrans__17dAuction_screen_cFv */
void dAuction_screen_c::rupeeCountTrans() {
    f32 var_f31;
    f32 var_f30;
    f32 var_f29 = 1.0f;

    if (talkmode) {
        if (field_0x194.mUserArea >= 10) {
            field_0x194.mUserArea = 10;
            var_f31 = 0.0f;
            var_f30 = 223.0f;
        } else {
            field_0x194.mUserArea++;
            if (field_0x194.mUserArea < 5) {
                var_f30 = var_f31 = 0.0f;
                var_f29 = fopMsgM_valueIncrease(5, 5 - field_0x194.mUserArea, 0);
            } else {
                var_f31 = 0.0f;
                var_f30 = 223.0f;
                var_f29 = fopMsgM_valueIncrease(5, field_0x194.mUserArea - 5, 0);
            }
        }

        fopMsgM_setNowAlpha(&field_0xc, var_f29);

        fopMsgM_setNowAlpha(&field_0x44[0], var_f29);
        fopMsgM_setNowAlpha(&field_0x44[1], var_f29);
        fopMsgM_setNowAlpha(&field_0x44[2], var_f29);

        fopMsgM_setNowAlpha(&field_0xec[0], var_f29);
        fopMsgM_setNowAlpha(&field_0xec[1], var_f29);
        fopMsgM_setNowAlpha(&field_0xec[2], var_f29);

        fopMsgM_setNowAlpha(&field_0x194, var_f29);

        fopMsgM_setNowAlpha(&field_0x1cc[0], var_f29);
        fopMsgM_setNowAlpha(&field_0x1cc[1], var_f29);
        fopMsgM_setNowAlpha(&field_0x1cc[2], var_f29);
        fopMsgM_setNowAlpha(&field_0x1cc[3], var_f29);
        fopMsgM_setNowAlpha(&field_0x1cc[4], var_f29);
        fopMsgM_setNowAlpha(&field_0x1cc[5], var_f29);

        fopMsgM_setNowAlpha(&field_0x31c[0], var_f29);
        fopMsgM_setNowAlpha(&field_0x31c[1], var_f29);
        fopMsgM_setNowAlpha(&field_0x31c[2], var_f29);
        fopMsgM_setNowAlpha(&field_0x31c[3], var_f29);
    } else {
        if (field_0x194.mUserArea <= 0) {
            field_0x194.mUserArea = 0;
        } else {
            field_0x194.mUserArea--;
        }

        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x194.mUserArea, 0);
        var_f31 = 0.0f;
        var_f30 = temp_f1 * 223.0f;
    }

    initPosSet(&field_0xc, var_f31, var_f30);
    initPosSet(&field_0x194, var_f31, var_f30);

    for (int i = 0; i < 6; i++) {
        initPosSet(&field_0x1cc[i], var_f31, var_f30);
    }

    for (int i = 0; i < 4; i++) {
        initPosSet(&field_0x31c[i], var_f31, var_f30);
    }

    fopMsgM_paneTrans(&field_0xc, 0.0f, 0.0f);
    fopMsgM_paneTrans(&field_0x194, 0.0f, 0.0f);

    for (int i = 0; i < 6; i++) {
        fopMsgM_paneTrans(&field_0x1cc[i], 0.0f, 0.0f);
    }

    for (int i = 0; i < 4; i++) {
        fopMsgM_paneTrans(&field_0x31c[i], 0.0f, 0.0f);
    }
}

/* 8015FE40-8015FFD4       .text rupeeCountUp__17dAuction_screen_cFv */
void dAuction_screen_c::rupeeCountUp() {
    f32 var_f31 = field_0x44[0].mPosCenterOrig.y - field_0xec[0].mPosCenterOrig.y;

    if (field_0x470 >= 3) {
        field_0x470 = 0;
    }

    field_0x470++;
    if (field_0x470 >= 3) {
        field_0x470 = 0;
        field_0x472++;
        nowRupeeSet();
        nextRupeeSet(field_0x472 + 1);
        mDoAud_seStart(JA_SE_AUC_PRICE_INC, NULL);
    }

    f32 temp = fopMsgM_valueIncrease(3, field_0x470, 2);

    fopMsgM_paneTrans(&field_0x44[2], 0.0f, var_f31 * temp);
    fopMsgM_paneTrans(&field_0xec[2], 0.0f, var_f31 * temp);

    if ((field_0x472 % 10) == 9 || field_0x470 == 0) {
        fopMsgM_paneTrans(&field_0x44[1], 0.0f, var_f31 * temp);
        fopMsgM_paneTrans(&field_0xec[1], 0.0f, var_f31 * temp);
    }

    if ((field_0x472 % 100) == 99 || field_0x470 == 0) {
        fopMsgM_paneTrans(&field_0x44[0], 0.0f, var_f31 * temp);
        fopMsgM_paneTrans(&field_0xec[0], 0.0f, var_f31 * temp);
    }
}

/* 8015FFD4-8016013C       .text rupeeCountDown__17dAuction_screen_cFv */
void dAuction_screen_c::rupeeCountDown() {
    f32 var_f31 = field_0x44[0].mPosCenterOrig.y - field_0xec[0].mPosCenterOrig.y;

    if (field_0x470 <= 0) {
        field_0x470 = 3;
    }

    field_0x470--;
    if (field_0x470 <= 0) {
        field_0x470 = 3;
        field_0x472--;
        nowRupeeSet();
    }

    nextRupeeSet(field_0x472 + 1);

    f32 temp = fopMsgM_valueIncrease(3, 3 - field_0x470, 2);

    fopMsgM_paneTrans(&field_0x44[2], 0.0f, -var_f31 * temp);
    fopMsgM_paneTrans(&field_0xec[2], 0.0f, -var_f31 * temp);

    if ((field_0x472 % 10) == 0 || field_0x470 == 3) {
        fopMsgM_paneTrans(&field_0x44[1], 0.0f, -var_f31 * temp);
        fopMsgM_paneTrans(&field_0xec[1], 0.0f, -var_f31 * temp);
    }

    if ((field_0x472 % 100) == 0 || field_0x470 == 3) {
        fopMsgM_paneTrans(&field_0x44[0], 0.0f, -var_f31 * temp);
        fopMsgM_paneTrans(&field_0xec[0], 0.0f, -var_f31 * temp);
    }
}

/* 8016013C-801604A0       .text slotShowAnime__17dAuction_screen_cFv */
void dAuction_screen_c::slotShowAnime() {

    if (slotShow) {
        if (field_0xc.mUserArea <= 7) {
            field_0xc.mUserArea++;

            f32 f31 = -50.0f;
            f32 f30 = 223.0f;
            f32 temp_f1 = fopMsgM_valueIncrease(7, field_0xc.mUserArea, 0);
            f32 var_f31 = f31 * (1.0f - temp_f1);

            fopMsgM_paneTrans(&field_0xc, var_f31, f30);
            fopMsgM_paneTrans(&field_0x194, var_f31, f30);

            fopMsgM_paneTrans(&field_0x1cc[0], var_f31, f30);
            fopMsgM_paneTrans(&field_0x1cc[1], var_f31, f30);
            fopMsgM_paneTrans(&field_0x1cc[2], var_f31, f30);
            fopMsgM_paneTrans(&field_0x1cc[3], var_f31, f30);
            fopMsgM_paneTrans(&field_0x1cc[4], var_f31, f30);
            fopMsgM_paneTrans(&field_0x1cc[5], var_f31, f30);

            fopMsgM_paneTrans(&field_0x31c[0], var_f31, f30);
            fopMsgM_paneTrans(&field_0x31c[1], var_f31, f30);
            fopMsgM_paneTrans(&field_0x31c[2], var_f31, f30);
            fopMsgM_paneTrans(&field_0x31c[3], var_f31, f30);

            if (field_0xc.mUserArea > 7 && !talkFlag) {
                talkFlag = 1;
                talkmode = TRUE;
                field_0x194.mUserArea = 10;
            }
        }

        if (field_0x31c[0].mUserArea < 7) {
            field_0x31c[0].mUserArea++;

            f32 var_f31 = fopMsgM_valueIncrease(7, field_0x31c[0].mUserArea, 0);

            fopMsgM_setNowAlpha(&field_0xc, var_f31);

            fopMsgM_setNowAlpha(&field_0x44[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x44[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x44[2], var_f31);

            fopMsgM_setNowAlpha(&field_0xec[0], var_f31);
            fopMsgM_setNowAlpha(&field_0xec[1], var_f31);
            fopMsgM_setNowAlpha(&field_0xec[2], var_f31);

            fopMsgM_setNowAlpha(&field_0x194, var_f31);

            fopMsgM_setNowAlpha(&field_0x1cc[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[2], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[3], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[4], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[5], var_f31);

            fopMsgM_setNowAlpha(&field_0x31c[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[2], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[3], var_f31);
        }
    } else {
        if (field_0xc.mUserArea > 0) {
            field_0x31c[0].mUserArea--;

            f32 var_f31 = fopMsgM_valueIncrease(7, field_0x31c[0].mUserArea, 0);

            fopMsgM_setNowAlpha(&field_0xc, var_f31);

            fopMsgM_setNowAlpha(&field_0x44[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x44[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x44[2], var_f31);

            fopMsgM_setNowAlpha(&field_0xec[0], var_f31);
            fopMsgM_setNowAlpha(&field_0xec[1], var_f31);
            fopMsgM_setNowAlpha(&field_0xec[2], var_f31);

            fopMsgM_setNowAlpha(&field_0x194, var_f31);

            fopMsgM_setNowAlpha(&field_0x1cc[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[2], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[3], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[4], var_f31);
            fopMsgM_setNowAlpha(&field_0x1cc[5], var_f31);

            fopMsgM_setNowAlpha(&field_0x31c[0], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[1], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[2], var_f31);
            fopMsgM_setNowAlpha(&field_0x31c[3], var_f31);
        }
    }
}

/* 801604A0-80160558       .text gaugeShowAnime__17dAuction_screen_cFv */
void dAuction_screen_c::gaugeShowAnime() {
    if (gaugeShow) {
        if (field_0x3fc.mUserArea < 7) {
            field_0x3fc.mUserArea++;
            f32 var_f31 = fopMsgM_valueIncrease(7, field_0x3fc.mUserArea, 0);
            fopMsgM_setNowAlpha(&field_0x3fc, var_f31);
            fopMsgM_setNowAlpha(&field_0x434, var_f31);
        }
    } else {
        if (field_0x3fc.mUserArea > 0) {
            field_0x3fc.mUserArea--;
            f32 var_f31 = fopMsgM_valueIncrease(7, field_0x3fc.mUserArea, 0);
            fopMsgM_setNowAlpha(&field_0x3fc, var_f31);
            fopMsgM_setNowAlpha(&field_0x434, var_f31);
        }
    }
}

/* 80160558-801605B0       .text initialize__17dAuction_screen_cFv */
void dAuction_screen_c::initialize() {
    field_0x472 = 0;
    field_0x474 = 0;

    clearTimer();
    gaugeMove();
    nowRupeeSet();
    nextRupeeSet(field_0x472 + 1);
}

/* 801605B0-80160770       .text _create__17dAuction_screen_cFv */
void dAuction_screen_c::_create() {
    scrn1 = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(540, 540, 540, 540), scrn1 != NULL);
    scrn1->set("auction1.blo", archive);

    scrn2 = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(544, 544, 544, 544), scrn2 != NULL);
    scrn2->set("auction2.blo", archive);

    screenSet();
    initialize();
}

/* 80160770-80160854       .text _move__17dAuction_screen_cFv */
void dAuction_screen_c::_move() {
    gaugeMove();
    rupeeCountTrans();

    if (field_0x472 < dComIfGp_getAuctionRupee()) {
        if (field_0x472 == 0) {
            field_0x472 = dComIfGp_getAuctionRupee();
            nowRupeeSet();
            nextRupeeSet(field_0x472 + 1);
        } else {
            rupeeCountUp();
            if (field_0x472 == dComIfGp_getAuctionRupee()) {
                mDoAud_seStart(JA_SE_AUC_PRICE_STOP, NULL);
            }
        }
    } else if (field_0x472 > dComIfGp_getAuctionRupee()) {
        rupeeCountDown();
    }

    slotShowAnime();
    gaugeShowAnime();
}

/* 80160854-8016096C       .text _draw__17dAuction_screen_cFv */
void dAuction_screen_c::_draw() {
    fopMsgM_setAlpha(&field_0xc);

    for (int i = 0; i < 3; i++) {
        fopMsgM_setAlpha(&field_0x44[i]);
        fopMsgM_setAlpha(&field_0xec[i]);
    }

    fopMsgM_setAlpha(&field_0x194);

    for (int i = 0; i < 6; i++) {
        fopMsgM_setAlpha(&field_0x1cc[i]);
    }

    for (int i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&field_0x31c[i]);
    }

    fopMsgM_setAlpha(&field_0x3fc);
    fopMsgM_setAlpha(&field_0x434);

    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    scrn1->setScissor(true);
    scrn2->draw(0.0f, 0.0f, graf);
    scrn1->draw(0.0f, 0.0f, graf);
}

/* 8016096C-80160984       .text _open__17dAuction_screen_cFv */
bool dAuction_screen_c::_open() {
    clearTimer();
    field_0x474 = 5;
    return true;
}

/* 80160984-80160994       .text _close__17dAuction_screen_cFv */
bool dAuction_screen_c::_close() {
    field_0x474 = 0;
    return true;
}

/* 80160994-80160B18       .text _create__5dAs_cFv */
cPhs_State dAs_c::_create() {
    cPhs_State phase_state = dComIfG_resLoad(&phase, "Auction");

    dAs_scrn = NULL;
    proc = 0;
    dComIfGp_setAuctionGauge(0);
    dComIfGp_setAuctionRupee(0);

    if (phase_state == cPhs_COMPLEATE_e) {
        dRes_info_c* resInfo = dComIfG_getObjectResInfo("Auction");
        JUT_ASSERT(VERSION_SELECT(710, 710, 710, 710), resInfo != NULL);

        heap = mDoExt_createSolidHeapFromGameToCurrent(0x2960, 0x20);
        if (heap == NULL) {
            return cPhs_ERROR_e;
        }

        dAs_scrn = new dAuction_screen_c();
        JUT_ASSERT(VERSION_SELECT(720, 720, 720, 720), dAs_scrn != NULL);
        dAs_scrn->archive = resInfo->getArchive();
        dAs_scrn->_create();

        mDoExt_restoreCurrentHeap();
        mDoExt_adjustSolidHeap(heap);
    } else {
        return phase_state;
    }

    return cPhs_COMPLEATE_e;
}

/* 80160B18-80160BE8       .text _execute__5dAs_cFv */
BOOL dAs_c::_execute() {
    if (proc == 0) {
        if (dAs_scrn->_open()) {
            proc = 1;
        }
    } else if (proc == 1) {
        dAs_scrn->_move();
        if (!dMeter_isAuctionFlag()) {
            dAs_scrn->clearTimer();
            proc = 3;
        }
    } else if (proc == 2) {
        if (!dComIfGp_checkPlayerStatus0(0, 0x10)) {
            proc = 1;
        }
    } else if (proc == 3) {
        if (dAs_scrn->_close()) {
            fopMsgM_Delete(this);
        }
    }

    return TRUE;
}

/* 80160BE8-80160C2C       .text _draw__5dAs_cFv */
BOOL dAs_c::_draw() {
    if (dAs_scrn != NULL) {
        dComIfGd_set2DOpa(dAs_scrn);
    }

    return TRUE;
}

/* 80160C2C-80160C7C       .text _delete__5dAs_cFv */
BOOL dAs_c::_delete() {
    if (heap != NULL) {
        mDoExt_destroySolidHeap(heap);
    }

    dComIfG_resDeleteDemo(&phase, "Auction");
    return TRUE;
}

/* 80160C7C-80160C9C       .text dAs_Draw__FP5dAs_c */
static BOOL dAs_Draw(dAs_c* i_this) {
    return i_this->_draw();
}

/* 80160C9C-80160CBC       .text dAs_Execute__FP5dAs_c */
static BOOL dAs_Execute(dAs_c* i_this) {
    return i_this->_execute();
}

/* 80160CBC-80160CC4       .text dAs_IsDelete__FP5dAs_c */
static BOOL dAs_IsDelete(dAs_c* i_this) {
    return TRUE;
}

/* 80160CC4-80160CF8       .text dAs_Delete__FP5dAs_c */
static BOOL dAs_Delete(dAs_c* i_this) {
    dAuction_screen_delete();
    return i_this->_delete();
}

/* 80160CF8-80160D20       .text dAs_Create__FP9msg_class */
static cPhs_State dAs_Create(msg_class* msg) {
    talkFlag = FALSE;

    dAs_c* i_this = (dAs_c*)msg;
    i_this->_create();
}

/* 80160D20-80160D70       .text dAuction_screen_create__Fv */
fpc_ProcID dAuction_screen_create() {
    if (!dMeter_isAuctionFlag()) {
        dMeter_onAuctionFlag();
        return fopMsgM_create(fpcNm_AUCTION_SCREEN_e);
    }

    return fpcM_ERROR_PROCESS_ID_e;
}

/* 80160D70-80160DA8       .text dAuction_screen_delete__Fv */
BOOL dAuction_screen_delete() {
    if (dMeter_isAuctionFlag()) {
        dMeter_offAuctionFlag();
        return TRUE;
    }
    return FALSE;
}

/* 80160DA8-80160DB8       .text dAuction_screen_talkStart__Fv */
BOOL dAuction_screen_talkStart() {
    talkmode = TRUE;
    return TRUE;
}

/* 80160DB8-80160DC8       .text dAuction_screen_talkEnd__Fv */
BOOL dAuction_screen_talkEnd() {
    talkmode = FALSE;
    return TRUE;
}

/* 80160DC8-80160DD8       .text dAuction_screen_slotShow__Fv */
BOOL dAuction_screen_slotShow() {
    slotShow = TRUE;
    return TRUE;
}

/* 80160DD8-80160DE8       .text dAuction_screen_slotHide__Fv */
BOOL dAuction_screen_slotHide() {
    slotShow = FALSE;
    return TRUE;
}

/* 80160DE8-80160DF8       .text dAuction_screen_gaugeShow__Fv */
BOOL dAuction_screen_gaugeShow() {
    gaugeShow = TRUE;
    return TRUE;
}

/* 80160DF8-80160E08       .text dAuction_screen_gaugeHide__Fv */
BOOL dAuction_screen_gaugeHide() {
    gaugeShow = FALSE;
    return TRUE;
}

/* 80160E08-80160E18       .text dAuction_screen_gaugeUp__Fv */
BOOL dAuction_screen_gaugeUp() {
    gaugeTrans = TRUE;
    return TRUE;
}

/* 80160E18-80160E28       .text dAuction_screen_gaugeDown__Fv */
BOOL dAuction_screen_gaugeDown() {
    gaugeTrans = FALSE;
    return TRUE;
}

/* 80160E28-80160E64       .text dAs_timerCalc__Fv */
void dAs_timerCalc() {
    if (!gaugeTrans) {
        if (gaugeTransTimer > 0) {
            gaugeTransTimer--;
        }
    } else {
        if (gaugeTransTimer < 7) {
            gaugeTransTimer++;
        }
    }
}

static msg_method_class l_dAuction_screen_Method = {
    (process_method_func)dAs_Create,
    (process_method_func)dAs_Delete,
    (process_method_func)dAs_Execute,
    (process_method_func)dAs_IsDelete,
    (process_method_func)dAs_Draw,
};

msg_process_profile_definition g_profile_AUCTION_SCREEN = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 12,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_AUCTION_SCREEN_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dAs_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Draw Prio    */ fpcDwPi_AUCTION_SCREEN_e,
    /* Msg SubMtd   */ &l_dAuction_screen_Method,
};
