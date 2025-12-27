/**
 * d_msg.cpp
 * Textboxes (normal gameplay) (talking, item collection, etc.)
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_file_error.h"
#include "d/d_meter.h"
#include "d/d_msg.h"
#include "d/d_s_play.h"
#include "f_op/f_op_msg_mng.h"
#include "d/actor/d_a_npc_bs1.h"
#include "d/d_priority.h"
#include "d/d_procname.h"
#include "dolphin/types.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_lib.h"
#include <stdio.h>

extern dMeter_info_c dMeter_Info;

class J2DTextBox;
struct fopMsgM_pane_class;

J2DPicture* button_icon[8];
J2DPicture* button_kage[8];
s16 buttonTimer[8];
J2DTextBox* numberPane[3];

MyScreen* sScreen;
static J2DScreen* sScreen2;
JUTFont* textFont;
JUTFont* rubyFont;
J2DPicture* arrowPane;
J2DPicture* maskPane;
f32 talkPosX;
f32 talkPosY;
s16 textOffsetY;
bool dMsg_font_flag;
JKRHeap* agb_work_area;
static dDlst_2DMSG_c message;
dDlst_2Dtact_c capture;
dDlst_2DM_c multiTex;

char* mLayout[] = {
    "hukidashi_14_1.blo",
    "hukidashi_14_1.blo",
    "hukidashi_14_3.blo",
    "hukidashi_14_5.blo",
    "hukidashi_14_6.blo",
    "hukidashi_14_6.blo",
    "hukidashi_14_0_1.blo",
    "hukidashi_14_0_2.blo"
};

const u8 mBeatNum[] = {0x03, 0x04, 0x04, 0x06, 0x06, 0x03, 0x03, 0x04};

void dMsg_textPosition(sub_msg_class*);
void dMsg_mesgOutPos(sub_msg_class*);
void dMsg_setCloseSound(sub_msg_class*, u8);
void dMsg_setCancelMode(sub_msg_class*);

/* 8020A620-8020A628       .text dMsg_getAgbWorkArea__Fv */
JKRHeap* dMsg_getAgbWorkArea() {
    return agb_work_area;
}

/* 8020A628-8020A950       .text draw__13dDlst_2DMSG_cFv */
void dDlst_2DMSG_c::draw() {
    /* Nonmatching */
    fopMsgM_msgDataProc_c* temp_r3;
    sub_msg_class* pmVar3;
    sub_msg_class* pmVar2;
    sub_msg_class* pmVar4;
    f32 dVar3;

    pmVar4 = field_0x4;
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    sScreen->draw(0.0f, 0.0f, graf);
    if (sScreen2 != NULL) {
        sScreen2->draw(0.0f, 0.0f, graf);
    }
    outFontDraw();
    if (pmVar4->mStatus == fopMsgStts_SELECT_YOKO_e) {
        pmVar3 = field_0x4;
        temp_r3 = &pmVar3->mMsgDataProc;
        temp_r3->selectArrow(arrowPane, temp_r3->field_0x26C, temp_r3->field_0x270, temp_r3->field_0x278, temp_r3->field_0x274);
    } else if (pmVar4->mStatus == fopMsgStts_INPUT_e) {
        pmVar2 = field_0x4;
        if ((pmVar2->mMesgEntry.mTextboxType == 0) || (pmVar2->mMesgEntry.mTextboxType == 10)) {
            f32 f1 = (numberPane[0]->mBounds.f.x - numberPane[0]->mBounds.i.x);
            dVar3 = (f1 + numberPane[0]->getCharSpace());
            if (pmVar4->mMsgNo == 0x1cfa) {
                f32 f3;
                f32 f4;
                f4 = maskPane->mBounds.f.y - maskPane->mBounds.i.y;
                f3 = maskPane->mBounds.f.x - maskPane->mBounds.i.x;
                maskPane->draw(pmVar2->m10EC + (dVar3 * (2 - pmVar4->mSelectNum)), pmVar2->m10F0, f3, f4, false, false, false);
                f4 = numberPane[2]->mBounds.f.x - numberPane[2]->mBounds.i.x;
                f3 = numberPane[2]->mBounds.f.y - numberPane[2]->mBounds.i.y;
                numberPane[2]->draw(field_0x4->m10EC, field_0x4->m10F0 + f3, f4, HBIND_CENTER);
                f4 = numberPane[1]->mBounds.f.x - numberPane[1]->mBounds.i.x;
                f3 = numberPane[1]->mBounds.f.y - numberPane[1]->mBounds.i.y;
                numberPane[1]->draw((field_0x4->m10EC + dVar3), field_0x4->m10F0 + f3, f4, HBIND_CENTER);
                f4 = numberPane[0]->mBounds.f.x - numberPane[0]->mBounds.i.x;
                f3 = numberPane[0]->mBounds.f.y - numberPane[0]->mBounds.i.y;
                numberPane[0]->draw(field_0x4->m10EC + (dVar3 * 2.0f), field_0x4->m10F0 + f3, f4, HBIND_CENTER);
            } else {
                numberPane[2]->hide();
                f32 f3;
                f32 f4;
                f4 = maskPane->mBounds.f.y - maskPane->mBounds.i.y;
                f3 = maskPane->mBounds.f.x - maskPane->mBounds.i.x;
                maskPane->draw(field_0x4->m10EC + (dVar3 * (1 - pmVar4->mSelectNum)), field_0x4->m10F0, f3, f4, false, false, false);
                f4 = numberPane[1]->mBounds.f.x - numberPane[1]->mBounds.i.x;
                f3 = numberPane[1]->mBounds.f.y - numberPane[1]->mBounds.i.y;
                numberPane[1]->draw(field_0x4->m10EC, field_0x4->m10F0 + f3, f4, HBIND_CENTER);
                f4 = numberPane[0]->mBounds.f.x - numberPane[0]->mBounds.i.x;
                f3 = numberPane[0]->mBounds.f.y - numberPane[0]->mBounds.i.y;
                numberPane[0]->draw((field_0x4->m10EC + dVar3), field_0x4->m10F0 + f3, f4, HBIND_CENTER);
            }
        }
    }
}

/* 8020A950-8020AC40       .text outFontDraw__13dDlst_2DMSG_cFv */
void dDlst_2DMSG_c::outFontDraw() {
    /* Nonmatching */
    f32 dVar1;
    u8 cVar2;
    J2DScreen* pJVar3;
    sub_msg_class* pdVar4;
    int uVar4;
    int uVar5;
    u8 bVar6;
    int iVar7;
    f32 local_38;
    f32 local_30;
    f32 local_28;

    for (s32 i = 0; i < 8; i++) {
        pdVar4 = (sub_msg_class*)this->field_0x4;
        cVar2 = pdVar4->mMsgDataProc.field_0x281[i];
        fopMsgM_msgDataProc_c* tmp = &pdVar4->mMsgDataProc;
        iVar7 = tmp->field_0x1A4[i];
        uVar5 = tmp->field_0x1E0[i];
        if ((((cVar2 != 0xFF) && (cVar2 != 0x14)) && (cVar2 != 0x15)) && (cVar2 != 0x16)) {
            pJVar3 = (J2DScreen*)pdVar4->m0544[0].pane;
            local_38 = tmp->field_0x168[i];
            dVar1 = local_38;
            if (pdVar4->mMesgEntry.mTextboxType == 5) {
                local_30 = g_msgHIO.field_0x5e * iVar7;
                local_38 = pdVar4->m1104 * (2 - pdVar4->m1108);
                iVar7 = (int)((local_30) + (local_38) + pJVar3->mBounds.i.y);
                bVar6 = pdVar4->m0544[0].mNowAlpha;
            } else if (pdVar4->mMesgEntry.mTextboxType == 0xe) {
                local_28 = g_msgHIO.field_0x5e * iVar7;
                local_30 = pdVar4->m1104;
                iVar7 = (int)((local_28) + (local_30) + pJVar3->mBounds.i.y);
                bVar6 = pdVar4->m0544[0].mNowAlpha;
            } else {
                if (pdVar4->m110C > (int)uVar5) {
                    if (pdVar4->m1108 > 1) {
                        uVar4 = uVar5 - pdVar4->m110C;
                        iVar7 = ((int)uVar4 / 2) + (int)(((pdVar4->m1104 * ((3 - iVar7) - (pdVar4->m1108 + -2))) + pJVar3->mBounds.i.y) - (int)(uVar5 / 2));
                    } else {
                        iVar7 = (int)(((pdVar4->m1104 << 2) + pJVar3->mBounds.i.y) - (int)(uVar5 / 2));
                    }
                } else {
                    local_28 = g_msgHIO.field_0x5e * iVar7;
                    local_30 = pdVar4->m1104 * (3 - pdVar4->m1108);
                    iVar7 = (int)((local_28) + (local_30) + pJVar3->mBounds.i.y);
                }
                bVar6 = pdVar4->m0544[0].mNowAlpha;
            }
            fopMsgM_outFontDraw(button_icon[i], button_kage[i], (int)(dVar1 + pJVar3->mBounds.i.x), iVar7, uVar5, &buttonTimer[i], bVar6, cVar2);
        }
    }
}

/* 8020AC40-8020AD3C       .text draw__14dDlst_2Dtact_cFv */
void dDlst_2Dtact_c::draw() {
    /* Nonmatching */
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    GXBool uVar1;
    f32 temp_r27;
    f32 temp_r28;
    f32 temp_r29;
    f32 temp_r30;

    graf->setPort();
    temp_r30 = -9.0f;
    temp_r29 = -21.0f;
    temp_r28 = 383.04376f;
    temp_r27 = 78.600006f;
    GXSetScissor((s32)temp_r30, (s32)temp_r29, (s32)temp_r28, (s32)temp_r27);
    sScreen->draw(0.0f, 0.0f, graf);
    GXSetTexCopySrc((s32)temp_r30, (s32)temp_r29, (s32)temp_r28, (s32)temp_r27);
    GXSetTexCopyDst((s32)temp_r28, (s32)temp_r27, GX_TF_RGB565, GX_FALSE);
    if (REG1_S(6) != 0) {
        uVar1 = GX_FALSE;
    } else {
        uVar1 = GX_TRUE;
    }
    GXCopyTex(field_0x8, uVar1);
}

/* 8020AD3C-8020ADD8       .text dMsg_msg_pane_parts_set__FP18fopMsgM_pane_classUc */
void dMsg_msg_pane_parts_set(fopMsgM_pane_class* pPane, u8 param_2) {
    f32 tmp;
    switch (param_2) {
    case 1:
        pPane->mPosTopLeft.y = (480.0f - (pPane->mPosTopLeftOrig.y + pPane->mSizeOrig.y)) + -26.0f;
        break;
    case 2:
        tmp = 0.5f;
        pPane->mPosTopLeft.y = 240.0f - pPane->mSizeOrig.y * tmp;
        break;
    default:
        pPane->mPosTopLeft.y = pPane->mPosTopLeftOrig.y + 32.0f;
        break;
    }
    tmp = 0.5f;
    pPane->mPosCenter.x = pPane->mPosTopLeft.x + pPane->mSizeOrig.x * tmp;
    pPane->mPosCenter.y = pPane->mPosTopLeft.y + pPane->mSizeOrig.y * tmp;
}

/* 8020ADD8-8020AE28       .text dMsg_arw_pane_parts_set__FP18fopMsgM_pane_classP18fopMsgM_pane_class */
void dMsg_arw_pane_parts_set(fopMsgM_pane_class* pDst, fopMsgM_pane_class* pSrc) {
    f32 tmp = 0.5f;
    pDst->mPosTopLeft.y = (pSrc->mPosTopLeft.y + pDst->mPosTopLeftOrig.y) - pSrc->mPosTopLeftOrig.y;
    pDst->mPosCenter.y = pDst->mPosTopLeft.y + pDst->mSizeOrig.y * tmp;
    fopMsgM_cposMove(pDst);
}

/* 8020AE28-8020B958       .text dMsg_screenDataSetTalk__FP13sub_msg_class */
void dMsg_screenDataSetTalk(sub_msg_class* i_Msg) {
    sScreen = new MyScreen();
    sScreen->set("hukidashi_00.blo", dComIfGp_getMsgArchive());
    fopMsgM_setPaneData(&i_Msg->m049C, sScreen->search('ms00'));
    fopMsgM_setPaneData(&i_Msg->mPane_Arrow, sScreen->search('yz00'));
    fopMsgM_setPaneData(&i_Msg->m050C, sScreen->search('dt00'));
    fopMsgM_setPaneData(&i_Msg->m0544[0], sScreen->search('tx02'));
    fopMsgM_setPaneData(&i_Msg->m0544[1], sScreen->search('tx03'));
    fopMsgM_setPaneData(&i_Msg->m0544[2], sScreen->search('txt0'));
    fopMsgM_setPaneData(&i_Msg->m0544[3], sScreen->search('tx01'));
    fopMsgM_setPaneData(&i_Msg->m011C[0], sScreen->search('txc2'));
    fopMsgM_setPaneData(&i_Msg->m011C[1], sScreen->search('tec3'));
    fopMsgM_setPaneData(&i_Msg->m011C[2], sScreen->search('txc0'));
    fopMsgM_setPaneData(&i_Msg->m011C[3], sScreen->search('txc1'));
    fopMsgM_setPaneData(&i_Msg->m01FC, sScreen->search('cur1'));
    fopMsgM_setPaneData(&i_Msg->m0234, sScreen->search('cur2'));
    fopMsgM_setPaneData(&i_Msg->m026C[0], sScreen->search('mc00'));
    fopMsgM_setPaneData(&i_Msg->m026C[1], sScreen->search('mc01'));
    fopMsgM_setPaneData(&i_Msg->m026C[2], sScreen->search('mc02'));
    fopMsgM_setPaneData(&i_Msg->m026C[3], sScreen->search('mc03'));
    fopMsgM_setPaneData(&i_Msg->m026C[4], sScreen->search('mc04'));
    fopMsgM_setPaneData(&i_Msg->m026C[5], sScreen->search('mc05'));
    fopMsgM_setPaneData(&i_Msg->m026C[6], sScreen->search('mc06'));
    fopMsgM_setPaneData(&i_Msg->m026C[7], sScreen->search('mc07'));
    fopMsgM_setPaneData(&i_Msg->m026C[8], sScreen->search('mc08'));
    fopMsgM_setPaneData(&i_Msg->m026C[9], sScreen->search('mc09'));
    for (s32 i = 0; i < 10; i++) {
        i_Msg->m026C[i].mInitAlpha = 0xaa;
    }
    ((J2DPicture*)i_Msg->m049C.pane)->setWhite(g_msgHIO.field_0x5);
    ((J2DPicture*)i_Msg->m049C.pane)->setBlack(g_msgHIO.field_0x9);
    ((J2DPicture*)i_Msg->m026C[0].pane)->setWhite(0);
    ((J2DPicture*)i_Msg->m026C[0].pane)->setBlack(0);
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m011C[0].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m011C[1].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m011C[2].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m011C[3].pane)->setFont(rubyFont);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFont(textFont);
    }
    textOffsetY = 2;
    J2DTextBox::TFontSize size;
    size.mSizeX = g_msgHIO.field_0x70;
    size.mSizeY = g_msgHIO.field_0x70;
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m011C[0].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m011C[2].pane)->setFontSize(size);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFontSize(size);
        numberPane[i]->resize(size.mSizeX, size.mSizeY);
    }
    maskPane->resize(size.mSizeX, size.mSizeY);
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m011C[0].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m011C[1].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m011C[2].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m011C[3].pane)->setCharSpace(g_msgHIO.field_0x5c);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setCharSpace(g_msgHIO.field_0x5a);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m011C[0].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m011C[2].pane)->setLineSpace(g_msgHIO.field_0x5e);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setLineSpace(g_msgHIO.field_0x5e);
    }
    fopMsgM_blendInit(&i_Msg->m01FC, "cursor_00_02.bti");
    fopMsgM_blendInit(&i_Msg->m0234, "cursor_00_02.bti");
    J2DTextBox::TFontSize size2;
    ((J2DTextBox*)i_Msg->m0544[0].pane)->getFontSize(size);
    i_Msg->m110C = (int)size.mSizeX;
    i_Msg->m1110 = (int)size2.mSizeX;
    i_Msg->m10BC.set(((J2DPicture*)i_Msg->m050C.pane)->getBlack());
    i_Msg->m10C4.set(((J2DPicture*)i_Msg->m050C.pane)->getWhite());
    i_Msg->m026C[0].mUserArea = 0;
}

/* 8020B958-8020CC6C       .text dMsg_screenDataSetItem__FP13sub_msg_class */
void dMsg_screenDataSetItem(sub_msg_class* i_Msg) {
    ResTIMG* pRVar6;
    f32 dVar12;

    sScreen = new MyScreen();
    sScreen->set("hukidashi_09.blo", dComIfGp_getMsgArchive());
    fopMsgM_setPaneData(&i_Msg->m049C, sScreen->search('ms90'));
    fopMsgM_setPaneData(&i_Msg->mPane_Arrow, sScreen->search('yz90'));
    fopMsgM_setPaneData(&i_Msg->m050C, sScreen->search('dt90'));
    fopMsgM_setPaneData(&i_Msg->m0544[0], sScreen->search('tx92'));
    fopMsgM_setPaneData(&i_Msg->m0544[1], sScreen->search('tx93'));
    fopMsgM_setPaneData(&i_Msg->m0544[2], sScreen->search('tx90'));
    fopMsgM_setPaneData(&i_Msg->m0544[3], sScreen->search('tx91'));
    fopMsgM_setPaneData(&i_Msg->m0624[8], sScreen->search('item'));
    fopMsgM_setPaneData(&i_Msg->m0624[9], sScreen->search('rin1'));
    fopMsgM_setPaneData(&i_Msg->m0624[0], sScreen->search('lig1'));
    fopMsgM_setPaneData(&i_Msg->m0624[1], sScreen->search('lig2'));
    fopMsgM_setPaneData(&i_Msg->m0624[2], sScreen->search('lig3'));
    fopMsgM_setPaneData(&i_Msg->m0624[3], sScreen->search('lig4'));
    fopMsgM_setPaneData(&i_Msg->m0624[4], sScreen->search('lig5'));
    fopMsgM_setPaneData(&i_Msg->m0624[5], sScreen->search('lig6'));
    fopMsgM_setPaneData(&i_Msg->m0624[6], sScreen->search('lig7'));
    fopMsgM_setPaneData(&i_Msg->m0624[7], sScreen->search('lig8'));
    pRVar6 = (ResTIMG*)i_Msg->mpHeap->alloc(0xc00, 0x20);
    i_Msg->buffer_p = pRVar6;
    JUT_ASSERT(661, i_Msg->buffer_p != NULL);
    if ((i_Msg->mMesgEntry.mTextboxType == 9) && (dItem_data::getTexture(i_Msg->mMsgNo - 101) != NULL)) {
        JKRArchive* archive = dComIfGp_getItemIconArchive();
        JKRArchive::readTypeResource(i_Msg->buffer_p, 0xc00, 'TIMG', dItem_data::getTexture(i_Msg->mMsgNo - 101), archive);
        ((J2DPicture*)i_Msg->m0624[8].pane)->changeTexture(i_Msg->buffer_p, 0);
    } else {
        for (s32 i = 0; i < 10; i++) {
            i_Msg->m0624[i].pane->hide();
        }
        i_Msg->m0624[8].mUserArea = 1;
        dVar12 = (i_Msg->m049C.mPosCenterOrig.x - i_Msg->m0544[0].mPosCenterOrig.x);
        for (s32 i = 0; i < 4; i++) {
            i_Msg->m0544[i].mSize.x = 486.0f;
            fopMsgM_paneTrans(&i_Msg->m0544[i], dVar12, 0.0f);
            i_Msg->m0544[i].mPosTopLeftOrig.x = i_Msg->m0544[i].mPosTopLeft.x;
            i_Msg->m0544[i].mPosCenterOrig.x = i_Msg->m0544[i].mPosCenter.x;
            i_Msg->m0544[i].mSizeOrig.x = i_Msg->m0544[i].mSize.x;
        }
    }
    if (i_Msg->mMsgNo == 0x66) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x0A280A00));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0x28FF28FF));
    } else if (i_Msg->mMsgNo == 0x67) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x1414A000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0x32C8FFFF));
    } else if (i_Msg->mMsgNo == 0x68) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x50500000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFFFF00FF));
    } else if (i_Msg->mMsgNo == 0x69) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x50282800));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFF5050FF));
    } else if (i_Msg->mMsgNo == 0x6a) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x501E8200));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xBE78FFFF));
    } else if (i_Msg->mMsgNo == 0x6b) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x50280000));
        ;
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFF8C00FF));
    } else if (i_Msg->mMsgNo == 0x74) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFFFFFFFF));
    } else if (i_Msg->mMsgNo == 0x7f) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x50500000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFFFF00FF));
    } else if ((((i_Msg->mMsgNo == 0x118) || (i_Msg->mMsgNo == 0x119)) || (i_Msg->mMsgNo == 0x11a)) || (i_Msg->mMsgNo == 0x11b || (i_Msg->mMsgNo == 0x11c))) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x501E8200));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xBE78FFFF));
    } else if (i_Msg->mMsgNo == 0x11d) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x50280000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFF8C00FF));
    } else if (i_Msg->mMsgNo == 0xd2) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0x50FFFFFF));
    } else if (i_Msg->mMsgNo == 0xd3) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xAAAAFFFF));
    } else if (i_Msg->mMsgNo == 0xd4) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFFC800FF));
    } else if (i_Msg->mMsgNo == 0xd5) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFF5050FF));
    } else if (i_Msg->mMsgNo == 0xd6) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xDC96FFFF));
    } else if (i_Msg->mMsgNo == 0xd7) {
        ((J2DPicture*)i_Msg->m0624[8].pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m0624[8].pane)->setWhite(JUtility::TColor(0xFFFFFFFF));
    }
    if (i_Msg->mMsgNo == 0xc6) {
        i_Msg->m0624[8].mSize.x = 32.0f;
        i_Msg->m0624[8].mSize.y = 32.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 199) {
        i_Msg->m0624[8].mSize.x = 48.0f;
        i_Msg->m0624[8].mSize.y = 40.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 200) {
        i_Msg->m0624[8].mSize.x = 32.0f;
        i_Msg->m0624[8].mSize.y = 32.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 0xc9) {
        i_Msg->m0624[8].mSize.x = 32.0f;
        i_Msg->m0624[8].mSize.y = 32.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 0xca) {
        i_Msg->m0624[8].mSize.x = 16.0f;
        i_Msg->m0624[8].mSize.y = 40.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 0xcb) {
        i_Msg->m0624[8].mSize.x = 56.0f;
        i_Msg->m0624[8].mSize.y = 32.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 0xcc) {
        i_Msg->m0624[8].mSize.x = 40.0f;
        i_Msg->m0624[8].mSize.y = 32.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    } else if (i_Msg->mMsgNo == 0xcd) {
        i_Msg->m0624[8].mSize.x = 40.0f;
        i_Msg->m0624[8].mSize.y = 40.0f;
        fopMsgM_paneTrans(&i_Msg->m0624[8], 0.0f, 0.0f);
    }
    if (i_Msg->mMesgEntry.mTextboxType == 1) {
        ((J2DPicture*)i_Msg->m049C.pane)->setBlack(JUtility::TColor(0x00000000));
        ((J2DPicture*)i_Msg->m049C.pane)->setWhite(JUtility::TColor(0xFFFFFFFF));
        ((J2DPicture*)i_Msg->m049C.pane)
            ->setCornerColor(JUtility::TColor(0x3232B4FF), JUtility::TColor(0x3232B4FF), JUtility::TColor(0x3232B496), JUtility::TColor(0x646478FF));
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFont(rubyFont);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFont(textFont);
    }
    textOffsetY = 2;
    J2DTextBox::TFontSize size;
    size.mSizeX = g_msgHIO.field_0x70;
    size.mSizeY = g_msgHIO.field_0x70;
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFontSize(size);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFontSize(size);
        numberPane[i]->resize(size.mSizeX, size.mSizeY);
    }
    maskPane->resize(size.mSizeX, size.mSizeY);
    J2DTextBox::TFontSize size2;
    size2.mSizeX = g_msgHIO.field_0x68;
    size2.mSizeY = g_msgHIO.field_0x68;
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFontSize(size2);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFontSize(size2);
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setCharSpace(g_msgHIO.field_0x5c);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setCharSpace(g_msgHIO.field_0x5a);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setLineSpace(g_msgHIO.field_0x5e);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setLineSpace(g_msgHIO.field_0x5e);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->getFontSize(size);
    i_Msg->m110C = (int)size.mSizeX;
    i_Msg->m1110 = (int)size2.mSizeX;
    i_Msg->m10BC.set(((J2DPicture*)i_Msg->m050C.pane)->getBlack());
    i_Msg->m10C4.set(((J2DPicture*)i_Msg->m050C.pane)->getWhite());
    i_Msg->m026C[0].mUserArea = 0;
}

/* 8020CC6C-8020D160       .text dMsg_screenDataSetDemo__FP13sub_msg_class */
void dMsg_screenDataSetDemo(sub_msg_class* i_Msg) {
    sScreen = new MyScreen();
    sScreen->set("hukidashi_05.blo", dComIfGp_getMsgArchive());
    fopMsgM_setPaneData(&i_Msg->m0544[0], sScreen->search('tx82'));
    fopMsgM_setPaneData(&i_Msg->m0544[1], sScreen->search('tx83'));
    fopMsgM_setPaneData(&i_Msg->m0544[2], sScreen->search('tx80'));
    fopMsgM_setPaneData(&i_Msg->m0544[3], sScreen->search('tx81'));
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFont(rubyFont);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFont(textFont);
    }
    textOffsetY = 2;
    J2DTextBox::TFontSize size;
    size.mSizeX = g_msgHIO.field_0x70;
    size.mSizeY = g_msgHIO.field_0x70;
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFontSize(size);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFontSize(size);
        numberPane[i]->resize(size.mSizeX, size.mSizeY);
    }
    maskPane->resize(size.mSizeX, size.mSizeY);
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setCharSpace(g_msgHIO.field_0x5c);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setCharSpace(g_msgHIO.field_0x5a);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setLineSpace(g_msgHIO.field_0x5e);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setLineSpace(g_msgHIO.field_0x5e);
    }
    J2DTextBox::TFontSize size2;
    i_Msg->m110C = (int)size.mSizeX;
    i_Msg->m1110 = (int)size2.mSizeY;
    i_Msg->m026C[0].mUserArea = 0;
}

/* 8020D160-8020DAC0       .text dMsg_screenDataSetTact__FP13sub_msg_class */
void dMsg_screenDataSetTact(sub_msg_class* i_Msg) {
    static const u32 ar_t[] = {'ar01', 'ar02', 'ar03', 'ar04', 'ar05', 'ar06'};
    static const u32 wn_t[] = {'wn01', 'wn02', 'wn03', 'wn04', 'wn05', 'wn06'};
    static const u32 bs_t[] = {'bs01', 'bs02', 'bs03', 'bs04', 'bs05', 'bs06'};
    static const u32 i0_t[] = {'i011', 'i021', 'i031', 'i041', 'i051', 'i061'};

    sScreen = new MyScreen();
    sScreen->set("hukidashi_14.blo", dComIfGp_getMsgArchive());
    if ((i_Msg->mMsgNo >= 0x5ac) && (i_Msg->mMsgNo <= 0x5b2)) {
        fopMsgM_setPaneData(&i_Msg->m049C, sScreen, 'm141');
        fopMsgM_setPaneData(&i_Msg->m0544[0], sScreen, 't141');
        fopMsgM_setPaneData(&i_Msg->m0544[1], sScreen, 'r141');
        fopMsgM_setPaneData(&i_Msg->m0544[2], sScreen, 'k141');
        fopMsgM_setPaneData(&i_Msg->m0544[3], sScreen, 'b141');
        sScreen->search('m142')->hide();
        sScreen->search('t142')->hide();
        sScreen->search('r142')->hide();
        sScreen->search('k142')->hide();
        sScreen->search('b142')->hide();
    } else {
        fopMsgM_setPaneData(&i_Msg->m049C, sScreen, 'm142');
        fopMsgM_setPaneData(&i_Msg->m0544[0], sScreen, 't142');
        fopMsgM_setPaneData(&i_Msg->m0544[1], sScreen, 'r142');
        fopMsgM_setPaneData(&i_Msg->m0544[2], sScreen, 'k142');
        fopMsgM_setPaneData(&i_Msg->m0544[3], sScreen, 'b142');
        sScreen->search('m141')->hide();
        sScreen->search('t141')->hide();
        sScreen->search('r141')->hide();
        sScreen->search('k141')->hide();
        sScreen->search('b141')->hide();
    }
    if ((i_Msg->mMsgNo == 0x5b3) || (i_Msg->mMsgNo == 0x5b4)) {
        JUT_ASSERT(1036, dComIfGp_getMelodyNum() <= 7);
        sScreen2 = new J2DScreen();
        sScreen2->set(mLayout[dComIfGp_getMelodyNum()], dComIfGp_getMsgArchive());
        for (s32 i = 0; i < mBeatNum[dComIfGp_getMelodyNum()]; i++) {
            fopMsgM_setPaneData(&i_Msg->m08C4[i], sScreen2, ar_t[i]);
            fopMsgM_setPaneData(&i_Msg->m0A14[i], sScreen2, wn_t[i]);
            fopMsgM_setPaneData(&i_Msg->m0B64[i], sScreen2, bs_t[i]);
            if (dComIfGp_getMelodyNum() >= 5) {
                fopMsgM_setPaneData(&i_Msg->m0CB4[i], sScreen2, i0_t[i]);
            }
        }
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFont(rubyFont);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFont(textFont);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFont(rubyFont);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFont(textFont);
    }
    textOffsetY = 2;
    J2DTextBox::TFontSize size;
    size.mSizeX = g_msgHIO.field_0x70;
    size.mSizeY = g_msgHIO.field_0x70;
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setFontSize(size);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setFontSize(size);
        numberPane[i]->resize(size.mSizeX, size.mSizeY);
    }
    maskPane->resize(size.mSizeX, size.mSizeY);
    J2DTextBox::TFontSize size2;
    size2.mSizeX = g_msgHIO.field_0x68;
    size2.mSizeY = g_msgHIO.field_0x68;
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setFontSize(size2);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setFontSize(size2);
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setCharSpace(g_msgHIO.field_0x5c);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setCharSpace(g_msgHIO.field_0x5a);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setCharSpace(g_msgHIO.field_0x5c);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setCharSpace(g_msgHIO.field_0x5a);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setLineSpace(g_msgHIO.field_0x5e);
    for (s32 i = 0; i < 3; i++) {
        numberPane[i]->setLineSpace(g_msgHIO.field_0x5e);
    }
    ((J2DTextBox*)i_Msg->m0544[0].pane)->getFontSize(size);
    i_Msg->m110C = (int)size.mSizeX;
    i_Msg->m1110 = (int)size2.mSizeX;
    i_Msg->m1168 = mDoAud_tact_getBeat();
    i_Msg->m1144 = 0;
    i_Msg->buffer_p = (ResTIMG*)i_Msg->mpHeap->alloc(0x1a280, 0x20);
    JUT_ASSERT(1128, i_Msg->buffer_p != NULL);
}

/* 8020DAC0-8020DC78       .text dMsg_screenDataSet__FP13sub_msg_class */
void dMsg_screenDataSet(sub_msg_class* i_Msg) {
    sScreen2 = NULL;
    if (fopMsgM_hyrule_language_check(i_Msg->mMsgNo)) {
        textFont = mDoExt_getRubyFont();
        JUT_ASSERT(1162, textFont != NULL);
        dMsg_font_flag = 1;
    } else {
        textFont = mDoExt_getMesgFont();
        JUT_ASSERT(1167, textFont != NULL);
        dMsg_font_flag = 0;
    }
    rubyFont = textFont;
    for (s32 i = 0; i < 3; i++) {
        numberPane[i] = new J2DTextBox("rock_24_20_4i_usa.bfn", "0");
    }
    maskPane = new J2DPicture("black.bti");
    switch (i_Msg->mMesgEntry.mTextboxType) {
    case 5:
        dMsg_screenDataSetDemo(i_Msg);
        break;
    case 1:
    case 9:
        dMsg_screenDataSetItem(i_Msg);
        break;
    case 0xe:
        dMsg_screenDataSetTact(i_Msg);
        break;
    default:
        dMsg_screenDataSetTalk(i_Msg);
        break;
    }
}

/* 8020DC78-8020DD10       .text dMsg_messagePaneShow__FP13sub_msg_class */
void dMsg_messagePaneShow(sub_msg_class* i_Msg) {
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m0544[i].pane->show();
        fopMsgM_setInitAlpha(&i_Msg->m0544[i]);
    }
    if ((i_Msg->mMesgEntry.mTextboxType == 9) || (i_Msg->mMesgEntry.mTextboxType == 1)) {
        for (s32 i = 0; i < 10; i++) {
            fopMsgM_setInitAlpha(&i_Msg->m0624[i]);
        }
    }
}

/* 8020DD10-8020DE1C       .text dMsg_messagePaneHide__FP13sub_msg_class */
void dMsg_messagePaneHide(sub_msg_class* i_Msg) {
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m0544[i].pane->hide();
    }
    if ((i_Msg->mMesgEntry.mTextboxType == 9) || (i_Msg->mMesgEntry.mTextboxType == 1)) {
        for (s32 i = 0; i < 10; i++) {
            fopMsgM_setNowAlphaZero(&i_Msg->m0624[i]);
        }
    } else if ((i_Msg->mMesgEntry.mTextboxType == 0xe) && (i_Msg->mMsgNo == 0x5b3 || (i_Msg->mMsgNo == 0x5b4))) {
        for (s32 i = 0; i < mBeatNum[dComIfGp_getMelodyNum()]; i++) {
            fopMsgM_setNowAlphaZero(&i_Msg->m08C4[i]);
            fopMsgM_setNowAlphaZero(&i_Msg->m0A14[i]);
            fopMsgM_setNowAlphaZero(&i_Msg->m0B64[i]);
            if (dComIfGp_getMelodyNum() >= 5) {
                fopMsgM_setNowAlphaZero(&i_Msg->m0CB4[i]);
            }
        }
    }
}

/* 8020DE1C-8020DEDC       .text dMsg_outFontHide__FP13sub_msg_class */
void dMsg_outFontHide(sub_msg_class*) {
    for (s32 i = 0; i < 8; i++) {
        button_icon[i]->hide();
        button_kage[i]->hide();
        button_icon[i]->rotate(0.0f);
        button_kage[i]->rotate(0.0f);
        buttonTimer[i] = -1;
    }
}

/* 8020DEDC-8020E1D0       .text dMsg_ScreenDataValueInitTalk__FP13sub_msg_class */
void dMsg_ScreenDataValueInitTalk(sub_msg_class* i_Msg) {
    int iVar1;
    int iVar2;
    char* pcVar4;
    char* pcVar5;
    char* pcVar7;
    char* pcVar8;
    cXyz VStack_3c;
    cXyz local_48;

    iVar1 = (int)((J2DTextBox*)i_Msg->m0544[0].pane)->getCharSpace();
    iVar2 = (int)((J2DTextBox*)i_Msg->m0544[1].pane)->getCharSpace();
    VStack_3c.setall(0.0f);
    if (i_Msg->mPos == VStack_3c) {
        i_Msg->m10E0.x = i_Msg->m049C.mPosCenterOrig.x;
        i_Msg->m10E0.y = i_Msg->m049C.mPosCenterOrig.y;
    } else {
        mDoLib_project(&i_Msg->mPos, &i_Msg->m10E0);
    }
    dMsg_mesgOutPos(i_Msg);
    i_Msg->m10D8 = (int)i_Msg->m049C.mPosCenter.x;
    i_Msg->m10DC = (int)i_Msg->m049C.mPosCenter.y;
    f32 tmp = 0.5f;
    i_Msg->m1104 = (int)(((J2DTextBox*)i_Msg->m0544[0].pane)->mLineSpace * tmp);
    i_Msg->m10C0 = i_Msg->m10BC;
    i_Msg->m10C8 = i_Msg->m10C4;
    local_48.setall(0.0f);
    if ((i_Msg->mPos != local_48) && (i_Msg->mMesgEntry.mTextboxType != 10)) {
        i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x;
        i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y;
    } else {
        i_Msg->m10E0.x = i_Msg->m049C.mPosCenter.x;
        i_Msg->m10E0.y = i_Msg->m049C.mPosCenter.y;
    }
    i_Msg->m049C.mSize.x = 100.0f;
    i_Msg->m049C.mSize.y = (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x) * 100.0f;
    fopMsgM_cposMove(&i_Msg->m049C);
    i_Msg->mMsgDataProc.dataInit();
    i_Msg->mMsgDataProc.field_0x25C = i_Msg->m1164;
    i_Msg->mMsgDataProc.field_0x10 = (int)&i_Msg->mPos;
    i_Msg->mMsgDataProc.field_0x3C = (char*)i_Msg->mpMesgStr;
    pcVar8 = i_Msg->output_rubSdw;
    pcVar7 = i_Msg->output_textSdw;
    pcVar5 = i_Msg->output_rub;
    pcVar4 = i_Msg->output_text;
    i_Msg->mMsgDataProc.field_0x60 = pcVar4;
    i_Msg->mMsgDataProc.field_0x40 = pcVar4;
    i_Msg->mMsgDataProc.field_0x64 = pcVar5;
    i_Msg->mMsgDataProc.field_0x44 = pcVar5;
    i_Msg->mMsgDataProc.field_0x68 = pcVar7;
    i_Msg->mMsgDataProc.field_0x48 = pcVar7;
    i_Msg->mMsgDataProc.field_0x6C = pcVar8;
    i_Msg->mMsgDataProc.field_0x4C = pcVar8;
    pcVar4 = i_Msg->select_rubSdw;
    pcVar5 = i_Msg->select_textSdw;
    pcVar7 = i_Msg->select_rub;
    i_Msg->mMsgDataProc.field_0x50[0] = i_Msg->select_text;
    i_Msg->mMsgDataProc.field_0x50[1] = pcVar7;
    i_Msg->mMsgDataProc.field_0x50[2] = pcVar5;
    i_Msg->mMsgDataProc.field_0x50[3] = pcVar4;
    i_Msg->mMsgDataProc.font[0] = textFont;
    i_Msg->mMsgDataProc.font[1] = rubyFont;
    i_Msg->mMsgDataProc.field_0x11C = iVar1;
    i_Msg->mMsgDataProc.field_0x124 = iVar2;
    i_Msg->mMsgDataProc.field_0x120 = (int)((J2DTextBox*)i_Msg->m0544[0].pane)->getLineSpace();
    i_Msg->mMsgDataProc.field_0x0C = &i_Msg->mMesgEntry;
    i_Msg->mMsgDataProc.field_0x144 = i_Msg->m110C;
    i_Msg->mMsgDataProc.field_0x14C = i_Msg->m1110;
    i_Msg->mMsgDataProc.field_0x128 = 0x1f7;
    i_Msg->mMsgDataProc.field_0x12C = 0x1e6;
    i_Msg->mMsgDataProc.field_0x160 = g_msgHIO.field_0x82;
    i_Msg->mMsgDataProc.field_0x15C = 2;
    if (g_msgHIO.field_0x83 != 0) {
        i_Msg->mMsgDataProc.field_0x29C = 1;
    } else {
        i_Msg->mMsgDataProc.field_0x29C = 0;
    }
    i_Msg->m10D0 = (i_Msg->m10D8) - i_Msg->m049C.mPosCenter.x;
    i_Msg->m10D4 = (i_Msg->m10DC) - i_Msg->m049C.mPosCenter.y;
}

/* 8020E1D0-8020E690       .text dMsg_ScreenDataValueInitItem__FP13sub_msg_class */
void dMsg_ScreenDataValueInitItem(sub_msg_class* i_Msg) {
    int uVar1;
    int iVar2;
    int iVar9;
    int fVar3;
    int fVar4;
    char* pcVar5;
    char* pcVar6;
    char* pcVar7;
    char* pcVar8;

    fVar3 = (int)((J2DTextBox*)i_Msg->m0544[0].pane)->getCharSpace();
    fVar4 = (int)((J2DTextBox*)i_Msg->m0544[1].pane)->getCharSpace();
    dMsg_msg_pane_parts_set(&i_Msg->m049C, 1);
    if (i_Msg->mMesgEntry.mTextboxPosition != 1) {
        i_Msg->m049C.mPosCenter.y += 225.0f;
        i_Msg->m049C.mPosTopLeft.y += 225.0f;
    }
    dMsg_arw_pane_parts_set(&i_Msg->mPane_Arrow, &i_Msg->m049C);
    dMsg_arw_pane_parts_set(&i_Msg->m050C, &i_Msg->m049C);
    i_Msg->m1114 = (int)(i_Msg->mPane_Arrow.mPosTopLeft.y + i_Msg->mPane_Arrow.mSizeOrig.y);
    uVar1 = (int)i_Msg->m0544[0].mPosTopLeftOrig.x;
    iVar2 = (int)(480.0f - (i_Msg->m0544[0].mPosTopLeftOrig.y + i_Msg->m0544[0].mSizeOrig.y));
    iVar9 = iVar2 + -0x13;
    if (i_Msg->mMesgEntry.mTextboxPosition != 1) {
        i_Msg->m10F8 = uVar1;
        i_Msg->m10FC = iVar9 + 0xE1;
    } else {
        i_Msg->m10F8 = uVar1;
        i_Msg->m10FC = iVar9;
    }
    i_Msg->m0544[0].pane->move(uVar1, (iVar9 - g_msgHIO.field_0x62) - (int)textOffsetY);
    i_Msg->m0544[1].pane->move(uVar1, (iVar9 - g_msgHIO.field_0x60) - (int)textOffsetY);
    i_Msg->m0544[2].pane->move(uVar1 + 2, (iVar9 - g_msgHIO.field_0x62) - (int)textOffsetY + 2);
    i_Msg->m0544[3].pane->move(uVar1 + 2, (iVar9 - g_msgHIO.field_0x60) - (int)textOffsetY + 2);
    i_Msg->m10D8 = (int)i_Msg->m049C.mPosCenter.x;
    i_Msg->m10DC = (int)i_Msg->m049C.mPosCenter.y;
    f32 tmp = 0.5f;
    i_Msg->m1104 = (int)(((J2DTextBox*)i_Msg->m0544[0].pane)->mLineSpace * tmp);
    i_Msg->m10C0 = i_Msg->m10BC;
    i_Msg->m10C8 = i_Msg->m10C4;
    i_Msg->m10E0.x = i_Msg->m049C.mPosCenter.x;
    i_Msg->m10E0.y = i_Msg->m049C.mPosCenter.y;
    i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x;
    i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y;
    i_Msg->m049C.mSize.x = 100.0f;
    i_Msg->m049C.mSize.y = (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x) * 100.0f;
    fopMsgM_cposMove(&i_Msg->m049C);
    i_Msg->mMsgDataProc.dataInit();
    i_Msg->mMsgDataProc.field_0x10 = (int)&i_Msg->mPos;
    i_Msg->mMsgDataProc.field_0x3C = (char*)i_Msg->mpMesgStr;
    pcVar8 = i_Msg->output_rubSdw;
    pcVar7 = i_Msg->output_textSdw;
    pcVar6 = i_Msg->output_rub;
    pcVar5 = i_Msg->output_text;
    i_Msg->mMsgDataProc.field_0x60 = pcVar5;
    i_Msg->mMsgDataProc.field_0x40 = pcVar5;
    i_Msg->mMsgDataProc.field_0x64 = pcVar6;
    i_Msg->mMsgDataProc.field_0x44 = pcVar6;
    i_Msg->mMsgDataProc.field_0x68 = pcVar7;
    i_Msg->mMsgDataProc.field_0x48 = pcVar7;
    i_Msg->mMsgDataProc.field_0x6C = pcVar8;
    i_Msg->mMsgDataProc.field_0x4C = pcVar8;
    pcVar5 = i_Msg->select_rubSdw;
    pcVar6 = i_Msg->select_textSdw;
    pcVar7 = i_Msg->select_rub;
    i_Msg->mMsgDataProc.field_0x50[0] = i_Msg->select_text;
    i_Msg->mMsgDataProc.field_0x50[1] = pcVar7;
    i_Msg->mMsgDataProc.field_0x50[2] = pcVar6;
    i_Msg->mMsgDataProc.field_0x50[3] = pcVar5;
    i_Msg->mMsgDataProc.font[0] = textFont;
    i_Msg->mMsgDataProc.font[1] = rubyFont;
    i_Msg->mMsgDataProc.field_0x11C = (int)fVar3;
    i_Msg->mMsgDataProc.field_0x124 = (int)fVar4;
    i_Msg->mMsgDataProc.field_0x0C = &i_Msg->mMesgEntry;
    i_Msg->mMsgDataProc.field_0x144 = i_Msg->m110C;
    i_Msg->mMsgDataProc.field_0x14C = i_Msg->m1110;
    if ((i_Msg->mMesgEntry.mTextboxType == 9) && (i_Msg->m0624[8].mUserArea == 0)) {
        i_Msg->mMsgDataProc.field_0x128 = 0x1a3;
        i_Msg->mMsgDataProc.field_0x12C = 0x192;
    } else {
        i_Msg->mMsgDataProc.field_0x128 = 0x1f7;
        i_Msg->mMsgDataProc.field_0x12C = 0x1e6;
    }
    i_Msg->mMsgDataProc.field_0x160 = g_msgHIO.field_0x82;
    i_Msg->mMsgDataProc.field_0x15C = 2;
    if (g_msgHIO.field_0x83 != 0) {
        i_Msg->mMsgDataProc.field_0x29C = 1;
    } else {
        i_Msg->mMsgDataProc.field_0x29C = 0;
    }
    i_Msg->m10D0 = (i_Msg->m10D8) - i_Msg->m049C.mPosCenter.x;
    i_Msg->m10D4 = (i_Msg->m10DC) - i_Msg->m049C.mPosCenter.y;
    i_Msg->m0624[9].mUserArea = 0;
    i_Msg->m0624[0].mUserArea = 0;
    i_Msg->m049C.mUserArea = 0;
}

/* 8020E690-8020EAC4       .text dMsg_ScreenDataValueInitTact__FP13sub_msg_class */
void dMsg_ScreenDataValueInitTact(sub_msg_class* i_Msg) {
    int uVar1;
    int iVar2;
    char* pcVar3;
    char* pcVar4;
    char* pcVar5;
    char* pcVar6;
    f32 dVar7;
    f32 dVar8;

    dVar7 = ((J2DTextBox*)i_Msg->m0544[0].pane)->getCharSpace();
    dVar8 = ((J2DTextBox*)i_Msg->m0544[1].pane)->getCharSpace();
    uVar1 = (int)i_Msg->m0544[0].mPosTopLeftOrig.x;
    iVar2 = (int)i_Msg->m0544[0].mPosTopLeftOrig.y;
    i_Msg->m10F8 = uVar1;
    i_Msg->m10FC = iVar2;
    i_Msg->m0544[0].pane->move(uVar1, (iVar2 - g_msgHIO.field_0x62) - (int)textOffsetY);
    i_Msg->m0544[1].pane->move(uVar1, (iVar2 - g_msgHIO.field_0x60) - (int)textOffsetY);
    i_Msg->m0544[2].pane->move(uVar1 + 2, (iVar2 - g_msgHIO.field_0x62) - (int)textOffsetY + 2);
    i_Msg->m0544[3].pane->move(uVar1 + 2, (iVar2 - g_msgHIO.field_0x60) - (int)textOffsetY + 2);
    i_Msg->m10D8 = (int)i_Msg->m049C.mPosCenter.x;
    i_Msg->m10DC = (int)i_Msg->m049C.mPosCenter.y;
    i_Msg->m1104 = 0;
    i_Msg->m10C0 = i_Msg->m10BC;
    i_Msg->m10C8 = i_Msg->m10C4;
    i_Msg->m10E0.x = i_Msg->m049C.mPosCenter.x;
    i_Msg->m10E0.y = i_Msg->m049C.mPosCenter.y;
    i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x;
    i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y;
    i_Msg->m049C.mSize.x = 100.0f;
    i_Msg->m049C.mSize.y = (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x) * 100.0f;
    fopMsgM_cposMove(&i_Msg->m049C);
    i_Msg->mMsgDataProc.dataInit();
    i_Msg->mMsgDataProc.field_0x10 = (int)&i_Msg->mPos;
    i_Msg->mMsgDataProc.field_0x3C = (char*)i_Msg->mpMesgStr;
    pcVar6 = i_Msg->output_rubSdw;
    pcVar5 = i_Msg->output_textSdw;
    pcVar4 = i_Msg->output_rub;
    pcVar3 = i_Msg->output_text;
    i_Msg->mMsgDataProc.field_0x60 = pcVar3;
    i_Msg->mMsgDataProc.field_0x40 = pcVar3;
    i_Msg->mMsgDataProc.field_0x64 = pcVar4;
    i_Msg->mMsgDataProc.field_0x44 = pcVar4;
    i_Msg->mMsgDataProc.field_0x68 = pcVar5;
    i_Msg->mMsgDataProc.field_0x48 = pcVar5;
    i_Msg->mMsgDataProc.field_0x6C = pcVar6;
    i_Msg->mMsgDataProc.field_0x4C = pcVar6;
    pcVar3 = i_Msg->select_rubSdw;
    pcVar4 = i_Msg->select_textSdw;
    pcVar5 = i_Msg->select_rub;
    i_Msg->mMsgDataProc.field_0x50[0] = i_Msg->select_text;
    i_Msg->mMsgDataProc.field_0x50[1] = pcVar5;
    i_Msg->mMsgDataProc.field_0x50[2] = pcVar4;
    i_Msg->mMsgDataProc.field_0x50[3] = pcVar3;
    i_Msg->mMsgDataProc.font[0] = textFont;
    i_Msg->mMsgDataProc.font[1] = rubyFont;
    i_Msg->mMsgDataProc.field_0x11C = (int)dVar7;
    i_Msg->mMsgDataProc.field_0x124 = (int)dVar8;
    i_Msg->mMsgDataProc.field_0x0C = &i_Msg->mMesgEntry;
    i_Msg->mMsgDataProc.field_0x144 = i_Msg->m110C;
    i_Msg->mMsgDataProc.field_0x14C = i_Msg->m1110;
    if ((i_Msg->mMesgEntry.mTextboxType == 9) && (i_Msg->m0624[8].mUserArea == 0)) {
        i_Msg->mMsgDataProc.field_0x128 = 0x1a3;
        i_Msg->mMsgDataProc.field_0x12C = 0x192;
    } else {
        i_Msg->mMsgDataProc.field_0x128 = 0x1f7;
        i_Msg->mMsgDataProc.field_0x12C = 0x1e6;
    }
    i_Msg->mMsgDataProc.field_0x160 = g_msgHIO.field_0x82;
    i_Msg->mMsgDataProc.field_0x15C = 2;
    if (g_msgHIO.field_0x83 != 0) {
        i_Msg->mMsgDataProc.field_0x29C = 1;
    } else {
        i_Msg->mMsgDataProc.field_0x29C = 0;
    }
    i_Msg->m10D0 = (i_Msg->m10D8) - i_Msg->m049C.mPosCenter.x;
    i_Msg->m10D4 = (i_Msg->m10DC) - i_Msg->m049C.mPosCenter.y;
    i_Msg->m0624[9].mUserArea = 0;
    i_Msg->m0624[0].mUserArea = 0;
    i_Msg->m0624[1].mUserArea = 0;
    i_Msg->m049C.mUserArea = 0;
}

/* 8020EAC4-8020EC28       .text dMsg_ScreenDataValueInitDemo__FP13sub_msg_class */
void dMsg_ScreenDataValueInitDemo(sub_msg_class* i_Msg) {
    char* pcVar1;
    char* pcVar2;
    char* pcVar4;
    char* pcVar5;
    f32 dVar6;
    f32 dVar7;

    dVar6 = ((J2DTextBox*)i_Msg->m0544[0].pane)->getCharSpace();
    dVar7 = ((J2DTextBox*)i_Msg->m0544[1].pane)->getCharSpace();
    f32 tmp = 0.5f;
    i_Msg->m1104 = (((J2DTextBox*)i_Msg->m0544[0].pane)->mLineSpace * tmp);
    i_Msg->mMsgDataProc.dataInit();
    i_Msg->mMsgDataProc.field_0x3C = (char*)i_Msg->mpMesgStr;
    pcVar5 = i_Msg->output_rubSdw;
    pcVar4 = i_Msg->output_textSdw;
    pcVar2 = i_Msg->output_rub;
    pcVar1 = i_Msg->output_text;
    i_Msg->mMsgDataProc.field_0x60 = pcVar1;
    i_Msg->mMsgDataProc.field_0x40 = pcVar1;
    i_Msg->mMsgDataProc.field_0x64 = pcVar2;
    i_Msg->mMsgDataProc.field_0x44 = pcVar2;
    i_Msg->mMsgDataProc.field_0x68 = pcVar4;
    i_Msg->mMsgDataProc.field_0x48 = pcVar4;
    i_Msg->mMsgDataProc.field_0x6C = pcVar5;
    i_Msg->mMsgDataProc.field_0x4C = pcVar5;
    pcVar1 = i_Msg->select_rubSdw;
    pcVar2 = i_Msg->select_textSdw;
    pcVar4 = i_Msg->select_rub;
    i_Msg->mMsgDataProc.field_0x50[0] = i_Msg->select_text;
    i_Msg->mMsgDataProc.field_0x50[1] = pcVar4;
    i_Msg->mMsgDataProc.field_0x50[2] = pcVar2;
    i_Msg->mMsgDataProc.field_0x50[3] = pcVar1;
    i_Msg->mMsgDataProc.font[0] = textFont;
    i_Msg->mMsgDataProc.font[1] = rubyFont;
    i_Msg->mMsgDataProc.field_0x11C = dVar6;
    i_Msg->mMsgDataProc.field_0x124 = dVar7;
    i_Msg->mMsgDataProc.field_0x0C = &i_Msg->mMesgEntry;
    i_Msg->mMsgDataProc.field_0x144 = i_Msg->m110C;
    i_Msg->mMsgDataProc.field_0x14C = i_Msg->m1110;
    i_Msg->mMsgDataProc.field_0x128 = 0x1f7;
    i_Msg->mMsgDataProc.field_0x12C = 0x1e6;
    i_Msg->mMsgDataProc.field_0x160 = g_msgHIO.field_0x82;
    i_Msg->mMsgDataProc.field_0x15C = 2;
    if (g_msgHIO.field_0x83 != 0) {
        i_Msg->mMsgDataProc.field_0x29C = 1;
    } else {
        i_Msg->mMsgDataProc.field_0x29C = 0;
    }
}

/* 8020EC28-8020ED14       .text dMsg_value_init__FP13sub_msg_class */
void dMsg_value_init(sub_msg_class* i_Msg) {
    char acStack_30[28];
    char acStack_4c[28];
    char acStack_68[28];

    // clang-format off
    sprintf(acStack_30, "\x1b" "CC[%08x]" "\x1b" "GM[0]",i_Msg->m1164);
    sprintf(acStack_4c, "\x1b" "CC[FFFFFFFF]" "\x1b" "GM[0]");
    sprintf(acStack_68,"\x1b" "CC[000000FF]" "\x1b" "GM[0]");
    // clang-format on
    strcpy(i_Msg->output_text, acStack_30);
    strcpy(i_Msg->output_rub, acStack_4c);
    strcpy(i_Msg->output_textSdw, acStack_68);
    strcpy(i_Msg->output_rubSdw, acStack_68);
    strcpy(i_Msg->select_text, acStack_30);
    strcpy(i_Msg->select_rub, acStack_4c);
    strcpy(i_Msg->select_textSdw, acStack_68);
    strcpy(i_Msg->select_rubSdw, acStack_68);
    i_Msg->mMsgDataProc.field_0x25C = i_Msg->m1164;
    dMsg_outFontHide(i_Msg);
    i_Msg->m1108 = 0;
}

/* 8020ED14-8020EDE0       .text dMsg_setString__FP13sub_msg_class */
void dMsg_setString(sub_msg_class* i_Msg) {
    ((J2DTextBox*)i_Msg->m0544[0].pane)->setString(i_Msg->output_text);
    ((J2DTextBox*)i_Msg->m0544[1].pane)->setString(i_Msg->output_rub);
    ((J2DTextBox*)i_Msg->m0544[2].pane)->setString(i_Msg->output_textSdw);
    ((J2DTextBox*)i_Msg->m0544[3].pane)->setString(i_Msg->output_rubSdw);
    if ((((i_Msg->mMesgEntry.mTextboxType != 9) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) && (i_Msg->mMesgEntry.mTextboxType != 1)) &&
        (i_Msg->mMesgEntry.mTextboxType != 5))
    {
        ((J2DTextBox*)i_Msg->m011C[0].pane)->setString(i_Msg->select_text);
        ((J2DTextBox*)i_Msg->m011C[1].pane)->setString(i_Msg->select_rub);
        ((J2DTextBox*)i_Msg->m011C[2].pane)->setString(i_Msg->select_textSdw);
        ((J2DTextBox*)i_Msg->m011C[3].pane)->setString(i_Msg->select_rubSdw);
    }
}

/* 8020EDE0-8020EE38       .text dMsg_yose_select__FP13sub_msg_class */
void dMsg_yose_select(sub_msg_class* i_Msg) {
    i_Msg->mMsgDataProc.stringLength();
    i_Msg->m1108 = i_Msg->mMsgDataProc.field_0x130;
    i_Msg->mMsgDataProc.field_0x130 = 0;
    i_Msg->mMsgDataProc.stringShift();
    i_Msg->mMsgDataProc.iconIdxRefresh();
    dMsg_textPosition(i_Msg);
}

/* 8020EE38-8020F080       .text dMsg_frame_openTalk__FP13sub_msg_class */
void dMsg_frame_openTalk(sub_msg_class* i_Msg) {
    i_Msg->m1100++;
    if (i_Msg->m1100 >= 0xd) {
        i_Msg->m049C.mPosCenter.x = i_Msg->m10D8;
        i_Msg->m049C.mPosCenter.y = i_Msg->m10DC;
        fopMsgM_paneScaleXY(&i_Msg->m049C, 1.0f);
        fopMsgM_setInitAlpha(&i_Msg->m049C);
    } else {
        if (i_Msg->m1100 < 10) {
            f32 temp_f31 = 100.0f * (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x);
            f32 temp_f30 = i_Msg->m049C.mSizeOrig.x - 100.0f;
            f32 temp_f29 = i_Msg->m049C.mSizeOrig.y - temp_f31;
            f32 temp_f1 = fopMsgM_valueIncrease(0xA, i_Msg->m1100, 0U);
            i_Msg->m049C.mSize.x = 100.0f + (temp_f30 * temp_f1);
            i_Msg->m049C.mSize.y = temp_f31 + (temp_f29 * temp_f1);
            i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x + (i_Msg->m10D0 * temp_f1);
            i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y + (i_Msg->m10D4 * temp_f1);
            fopMsgM_cposMove(&i_Msg->m049C);
        } else {
            f32 temp_f2_2 = 480.0f / (i_Msg->m049C.mSizeOrig.x - 100.0f);
            f32 temp_f1_2 = ((temp_f2_2 * i_Msg->m10D0) - i_Msg->m10D0);
            f32 temp_f1_3 = ((temp_f2_2 * i_Msg->m10D4) - i_Msg->m10D4);
            f32 temp_f1_4 = ((580.0f * (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x)) - i_Msg->m049C.mSizeOrig.y);
            f32 f0_2 = (0x10000 / 6.0f);
            f32 f0 = (i_Msg->m1100 - 10.0f);
            f32 temp_f3_2 = cM_ssin(f0 * f0_2);
            i_Msg->m049C.mSize.x = i_Msg->m049C.mSizeOrig.x + ((580.0f - i_Msg->m049C.mSizeOrig.x) * temp_f3_2);
            i_Msg->m049C.mSize.y = i_Msg->m049C.mSizeOrig.y + (temp_f1_4 * temp_f3_2);
            i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x + i_Msg->m10D0 + (temp_f1_2 * temp_f3_2);
            i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y + i_Msg->m10D4 + (temp_f1_3 * temp_f3_2);
            fopMsgM_cposMove(&i_Msg->m049C);
        }
        fopMsgM_setNowAlpha(&i_Msg->m049C, fopMsgM_valueIncrease(0xd, i_Msg->m1100, 0));
    }
}

/* 8020F080-8020F1C0       .text dMsg_frame_openItem__FP13sub_msg_class */
void dMsg_frame_openItem(sub_msg_class* i_Msg) {
    f32 dVar2;

    i_Msg->m1100++;
    if (i_Msg->m1100 >= 8) {
        i_Msg->m049C.mPosCenter.x = i_Msg->m10D8;
        i_Msg->m049C.mPosCenter.y = i_Msg->m10DC;
        fopMsgM_paneScaleXY(&i_Msg->m049C, 1.0f);
        fopMsgM_setInitAlpha(&i_Msg->m049C);
    } else {
        if (i_Msg->m1100 <= 5) {
            dVar2 = fopMsgM_valueIncrease(5, i_Msg->m1100, 0);
            i_Msg->m049C.mPosCenter.x = i_Msg->m10E0.x + (i_Msg->m10D0 * dVar2);
            i_Msg->m049C.mPosCenter.y = i_Msg->m10E0.y + (i_Msg->m10D4 * dVar2);
            fopMsgM_paneScaleXY(&i_Msg->m049C, (dVar2 * 0.5f) + 0.6f);
            fopMsgM_setNowAlpha(&i_Msg->m049C, dVar2);
        } else {
            dVar2 = fopMsgM_valueIncrease(3, i_Msg->m1100 + -5, 0);
            fopMsgM_paneScaleXY(&i_Msg->m049C, (dVar2 * -0.100000024f) + 1.1f);
            fopMsgM_setInitAlpha(&i_Msg->m049C);
        }
    }
}

/* 8020F1C0-8020F324       .text dMsg_frame_close__FP13sub_msg_class */
void dMsg_frame_close(sub_msg_class* i_Msg) {
    f32 dVar3;

    dMsg_messagePaneHide(i_Msg);
    dMsg_outFontHide(i_Msg);
    i_Msg->m1100++;
    if (i_Msg->m1100 == 10) {
        fopMsgM_setNowAlphaZero(&i_Msg->m049C);
        JKRFileLoader::removeResource(i_Msg->head_p, NULL);
        i_Msg->mStatus = fopMsgStts_BOX_CLOSED_e;
        i_Msg->m049C.pane->hide();
    } else {
        f32 f1 = fopMsgM_valueIncrease(10, i_Msg->m1100, 0);
        f32 tmp2 = 620.0f - i_Msg->m049C.mSizeOrig.x;
        f32 f29 = (i_Msg->m049C.mSizeOrig.y / i_Msg->m049C.mSizeOrig.x) * 620.0f - i_Msg->m049C.mSizeOrig.y;
        i_Msg->m049C.mSize.x = i_Msg->m049C.mSizeOrig.x + f1 * tmp2;
        i_Msg->m049C.mSize.y = i_Msg->m049C.mSizeOrig.y + f1 * f29;
        i_Msg->m049C.mPosCenter.x = i_Msg->m10D8;
        i_Msg->m049C.mPosCenter.y = i_Msg->m10DC;
        fopMsgM_cposMove(&i_Msg->m049C);
        dVar3 = fopMsgM_valueIncrease(10, 10 - i_Msg->m1100, 0);
        if (dVar3 < (i_Msg->m049C.mNowAlpha / 255.0f)) {
            fopMsgM_setNowAlpha(&i_Msg->m049C, dVar3);
        }
        if (i_Msg->m1100 == 1) {
            dMsg_setCloseSound(i_Msg, 0);
        }
    }
}

/* 8020F324-8020F3F8       .text dMsg_textPosition__FP13sub_msg_class */
void dMsg_textPosition(sub_msg_class* i_Msg) {
    int uVar2;
    J2DTextBox* pJVar6;
    J2DTextBox* pJVar3;
    J2DTextBox* pJVar4;
    J2DTextBox* pJVar5;

    switch (i_Msg->mMesgEntry.mTextboxType) {
    case 5:
        uVar2 = i_Msg->m1104 * (2 - i_Msg->m1108);
        break;
    case 0xE:
        uVar2 = 0;
        break;
    default:
        uVar2 = i_Msg->m1104 * (3 - i_Msg->m1108);
        break;
    }
    pJVar3 = (J2DTextBox*)i_Msg->m0544[0].pane;
    pJVar3->field_0xd8 = 0.0f;
    pJVar3->field_0xdc = uVar2;
    pJVar4 = (J2DTextBox*)i_Msg->m0544[1].pane;
    pJVar4->field_0xd8 = 0.0f;
    pJVar4->field_0xdc = uVar2;
    pJVar5 = (J2DTextBox*)i_Msg->m0544[2].pane;
    pJVar5->field_0xd8 = 0.0f;
    pJVar5->field_0xdc = uVar2;
    pJVar6 = (J2DTextBox*)i_Msg->m0544[3].pane;
    pJVar6->field_0xd8 = 0.0f;
    pJVar6->field_0xdc = uVar2;
}

/* 8020F3F8-8020F4E0       .text dMsg_rubySet__FP13sub_msg_class */
void dMsg_rubySet(sub_msg_class* i_Msg) {
    J2DScreen* pJVar2;

    if (dComIfGs_getOptRuby()) {
        i_Msg->m0544[1].pane->hide();
        i_Msg->m0544[3].pane->hide();
        if (i_Msg->mMesgEntry.mTextboxType == 9) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 0xe) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 1) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 5) {
            return;
        }
        i_Msg->m011C[1].pane->hide();
        i_Msg->m011C[3].pane->hide();
    } else {
        pJVar2 = (J2DScreen*)i_Msg->m0544[1].pane;
        if (pJVar2->isVisible()) {
            pJVar2->show();
        }
        pJVar2 = (J2DScreen*)i_Msg->m0544[3].pane;
        if (pJVar2->isVisible()) {
            pJVar2->show();
        }
        if (i_Msg->mMesgEntry.mTextboxType == 9) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 0xe) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 1) {
            return;
        }
        if (i_Msg->mMesgEntry.mTextboxType == 5) {
            return;
        }
        pJVar2 = (J2DScreen*)i_Msg->m011C[1].pane;
        if (pJVar2->isVisible()) {
            pJVar2->show();
        }
        pJVar2 = (J2DScreen*)i_Msg->m011C[3].pane;
        if (!pJVar2->isVisible()) {
            return;
        }
        pJVar2->show();
    }
}

/* 8020F4E0-8020F7EC       .text dMsg_mesgOutPos__FP13sub_msg_class */
void dMsg_mesgOutPos(sub_msg_class* i_Msg) {
    s32 uVar1;
    u8 bVar2;
    u8 bVar4;
    int iVar3;
    cXyz local_68;
    f32 local_58;

    bVar4 = i_Msg->mMesgEntry.mTextboxPosition;
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (bVar4 == 0) {
        mDoLib_project(&player->eyePos, &local_68);
        talkPosX = (local_68.x + i_Msg->m10E0.x) * 0.5f;
        talkPosY = (local_68.y + i_Msg->m10E0.y) * 0.5f;
        local_58 = (int)g_msgHIO.field_0x6e;
        if (talkPosY < local_58) {
            bVar4 = 3;
        } else {
            bVar4 = 1;
        }
    }
    dMsg_msg_pane_parts_set(&i_Msg->m049C, bVar4);
    bVar2 = i_Msg->mMesgEntry.mTextboxType;
    if ((bVar2 != 5) && (bVar2 != 0xe)) {
        dMsg_arw_pane_parts_set(&i_Msg->mPane_Arrow, &i_Msg->m049C);
        dMsg_arw_pane_parts_set(&i_Msg->m050C, &i_Msg->m049C);
        i_Msg->m1114 = (int)((i_Msg->mPane_Arrow).mPosTopLeft.y + (i_Msg->mPane_Arrow).mSizeOrig.y);
    }
    uVar1 = i_Msg->m0544[0].mPosTopLeftOrig.x;
    if (bVar4 == 1) {
        iVar3 = (int)(480.0f - (i_Msg->m0544[0].mPosTopLeftOrig.y + i_Msg->m0544[0].mSizeOrig.y)) + -0x13;
    } else if (bVar4 == 2) {
        f32 tmp = 0.5f;
        iVar3 = (int)(240.0f - i_Msg->m0544[0].mSizeOrig.y * tmp);
    } else {
        iVar3 = (int)i_Msg->m0544[0].mPosTopLeftOrig.y + 0x20;
    }
    i_Msg->m10F8 = uVar1;
    i_Msg->m10FC = iVar3;
    i_Msg->m0544[0].pane->move((uVar1), ((iVar3 - g_msgHIO.field_0x62) - (int)textOffsetY));
    i_Msg->m0544[1].pane->move((uVar1), ((iVar3 - g_msgHIO.field_0x60) - (int)textOffsetY));
    i_Msg->m0544[2].pane->move((uVar1 + 2), (((iVar3 - g_msgHIO.field_0x62) - (int)textOffsetY) + 2));
    i_Msg->m0544[3].pane->move((uVar1 + 2), (((iVar3 - g_msgHIO.field_0x60) - (int)textOffsetY) + 2));
}

/* 8020F7EC-8020F844       .text dMsg_arrowInit__FP13sub_msg_class */
void dMsg_arrowInit(sub_msg_class* i_Msg) {
    fopMsgM_setNowAlphaZero(&i_Msg->mPane_Arrow);
    i_Msg->mPane_Arrow.mPosCenter.x = i_Msg->mPane_Arrow.mPosCenterOrig.x;
    i_Msg->mPane_Arrow.mPosCenter.y = i_Msg->mPane_Arrow.mPosCenterOrig.y;
    i_Msg->mPane_Arrow.mSize.x = i_Msg->mPane_Arrow.mSizeOrig.x;
    i_Msg->mPane_Arrow.mSize.y = i_Msg->mPane_Arrow.mSizeOrig.y;
    i_Msg->m1100 = 0;
}

static void unused_5874() {
    static const Vec frameScale = {0.6f, 1.1f, 1.0f};
};

/* 8020F844-8020FC10       .text dMsg_arrowMove__FP13sub_msg_class */
void dMsg_arrowMove(sub_msg_class* i_Msg) {
    /* Nonmatching */
    static const s32 time[] = {0x00, 0x3C, 0x07, 0x04, 0x03, 0x02};
    static const f32 scaleX[] = {1.0f, 1.3f, 0.8f, 1.2f, 1.0f};
    static const f32 scaleY[] = {1.0f, 0.3f, 1.1f, 0.8f, 1.0f};
    f32 fVar1;
    f32 fVar2;
    f32 dVar4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r9;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r12;
    s32 temp_r30;

    temp_r9 = time[1];
    temp_r8 = time[2];
    temp_r10 = temp_r9 + temp_r8;
    temp_r7 = time[3];
    temp_r11 = temp_r10 + temp_r7;
    temp_r6 = time[4];
    temp_r12 = temp_r11 + temp_r6;
    temp_r5 = time[5];
    temp_r30 = temp_r12 + temp_r5;
    i_Msg->m1100++;
    if ((i_Msg->mPane_Arrow).mNowAlpha < (i_Msg->mPane_Arrow).mInitAlpha) {
        dVar4 = fopMsgM_valueIncrease(10, i_Msg->m1100, 0);
        fopMsgM_setNowAlpha(&i_Msg->mPane_Arrow, (f32)dVar4);
        if (i_Msg->m1100 == 10) {
            i_Msg->m1100 = 0;
        }
    } else {
        if (i_Msg->m1100 <= temp_r9) {
            fVar1 = 1.0f;
            fVar2 = fVar1;
        } else if (i_Msg->m1100 <= temp_r10) {
            fVar1 = (f32)(i_Msg->m1100) - temp_r9;
            fVar2 = (fVar1 * fVar1) / ((f32)temp_r8 * (f32)temp_r8);
            fVar1 = scaleX[0] + (fVar2 * (scaleX[1] - scaleX[0]));
            fVar2 = scaleY[0] + (fVar2 * (scaleY[1] - scaleY[0]));
        } else if (i_Msg->m1100 <= temp_r11) {
            fVar1 = (f32)(i_Msg->m1100) - temp_r10;
            fVar2 = (fVar1 * fVar1) / ((f32)temp_r7 * (f32)temp_r7);
            fVar1 = scaleX[1] + (fVar2 * (scaleX[2] - scaleX[1]));
            fVar2 = scaleY[1] + (fVar2 * (scaleY[2] - scaleY[1]));
        } else if (i_Msg->m1100 <= temp_r12) {
            fVar1 = (f32)(i_Msg->m1100) - temp_r11;
            fVar2 = (fVar1 * fVar1) / ((f32)temp_r6 * (f32)temp_r6);
            fVar1 = scaleX[2] + (fVar2 * (scaleX[3] - scaleX[2]));
            fVar2 = scaleY[2] + (fVar2 * (scaleY[3] - scaleY[2]));
        } else if (i_Msg->m1100 <= temp_r30) {
            fVar1 = (f32)(i_Msg->m1100) - temp_r12;
            fVar2 = (fVar1 * fVar1) / ((f32)temp_r5 * (f32)temp_r5);
            fVar1 = scaleX[3] + (fVar2 * (scaleX[4] - scaleX[3]));
            fVar2 = scaleY[3] + (fVar2 * (scaleY[4] - scaleY[3]));
        } else {
            fVar1 = 1.0f;
            fVar2 = fVar1;
            i_Msg->m1100 = 0;
        }
        (i_Msg->mPane_Arrow).mSize.x = (i_Msg->mPane_Arrow).mSizeOrig.x * fVar1;
        (i_Msg->mPane_Arrow).mSize.y = (i_Msg->mPane_Arrow).mSizeOrig.y * fVar2;
        (i_Msg->mPane_Arrow).mPosCenter.y = (f32)((int)g_msgHIO.field_0x66) + ((f32)(i_Msg->m1114) - (i_Msg->mPane_Arrow).mSize.y * 0.5f);
        fopMsgM_cposMove(&i_Msg->mPane_Arrow);
    }
}

/* 8020FC10-8021010C       .text dMsg_dotMove__FP13sub_msg_class */
void dMsg_dotMove(sub_msg_class* i_Msg) {
    /* Nonmatching */
    int iVar4;
    f32 dVar5;

    i_Msg->m1100++;
    if ((i_Msg->m050C).mNowAlpha < (i_Msg->m050C).mInitAlpha) {
        dVar5 = fopMsgM_valueIncrease(10, i_Msg->m1100, 0);
        fopMsgM_setNowAlpha(&i_Msg->m050C, (f32)dVar5);
        if (i_Msg->m1100 == 10) {
            i_Msg->m1100 = 0;
        }
    } else {
        iVar4 = i_Msg->m1100;
        if (iVar4 >= 0x3C) {
            i_Msg->m10C0 = i_Msg->m10BC;
            i_Msg->m10C8 = i_Msg->m10C4;
            fopMsgM_setInitAlpha(&i_Msg->m050C);
            i_Msg->m1100 = 0;
        } else {
            if (iVar4 > 0x1E) {
                dVar5 = fopMsgM_valueIncrease(0x1e, 0x3c - iVar4, 0);
                i_Msg->m10C0.r = (u8)(int)((f32)(i_Msg->m10BC.r) + (f32)((150.0f - (f32)(i_Msg->m10BC.r)) * dVar5));
                i_Msg->m10C0.g = (u8)(int)((f32)(i_Msg->m10BC.g) + (f32)((150.0f - (f32)(i_Msg->m10BC.g)) * dVar5));
                i_Msg->m10C0.b = (u8)(int)((f32)(i_Msg->m10BC.b) + (f32)((150.0f - (f32)(i_Msg->m10BC.b)) * dVar5));
                i_Msg->m10C8.r = (u8)(int)((f32)(i_Msg->m10C4.r) + (f32)((255.0f - (f32)(i_Msg->m10C4.r)) * dVar5));
                i_Msg->m10C8.g = (u8)(int)((f32)(i_Msg->m10C4.g) + (f32)((255.0f - (f32)(i_Msg->m10C4.g)) * dVar5));
                i_Msg->m10C8.b = (u8)(int)((f32)(i_Msg->m10C4.b) + (f32)((220.0f - (f32)(i_Msg->m10C4.b)) * dVar5));
                i_Msg->m050C.mNowAlpha = (u8)(int)((f32)(i_Msg->m050C.mInitAlpha) + (f32)((255.0f - (f32)(i_Msg->m050C.mInitAlpha)) * dVar5));
            } else {
                dVar5 = fopMsgM_valueIncrease(0x1e, iVar4, 0);
                i_Msg->m10C0.r = (u8)(int)((f32)(i_Msg->m10BC.r) + (f32)((150.0f - (f32)(i_Msg->m10BC.r)) * dVar5));
                i_Msg->m10C0.g = (u8)(int)((f32)(i_Msg->m10BC.g) + (f32)((150.0f - (f32)(i_Msg->m10BC.g)) * dVar5));
                i_Msg->m10C0.b = (u8)(int)((f32)(i_Msg->m10BC.b) + (f32)((150.0f - (f32)(i_Msg->m10BC.b)) * dVar5));
                i_Msg->m10C8.r = (u8)(int)((f32)(i_Msg->m10C4.r) + (f32)((255.0f - (f32)(i_Msg->m10C4.r)) * dVar5));
                i_Msg->m10C8.g = (u8)(int)((f32)(i_Msg->m10C4.g) + (f32)((255.0f - (f32)(i_Msg->m10C4.g)) * dVar5));
                i_Msg->m10C8.b = (u8)(int)((f32)(i_Msg->m10C4.b) + (f32)((220.0f - (f32)(i_Msg->m10C4.b)) * dVar5));
                i_Msg->m050C.mNowAlpha = (u8)(int)((f32)(i_Msg->m050C.mInitAlpha) + (f32)((255.0f - (f32)(i_Msg->m050C.mInitAlpha)) * dVar5));
            }
        }
        ((J2DPicture*)i_Msg->m050C.pane)->setBlack(JUtility::TColor(i_Msg->m10C0));
        ((J2DPicture*)i_Msg->m050C.pane)->setWhite(JUtility::TColor(i_Msg->m10C8));
    }
}

/* 8021010C-80210194       .text dMsg_ringMove__FP13sub_msg_class */
void dMsg_ringMove(sub_msg_class* i_Msg) {
    int iVar1;
    f32 dVar2;

    i_Msg->m0624[9].mUserArea++;
    if (i_Msg->m0624[9].mUserArea >= 0x78) {
        i_Msg->m0624[9].mUserArea = 0;
    }
    iVar1 = (int)i_Msg->m0624[9].mUserArea;
    if (iVar1 < 0x3c) {
        dVar2 = fopMsgM_valueIncrease(0x3c, iVar1, 0);
    } else {
        dVar2 = fopMsgM_valueIncrease(0x3c, 0x78 - iVar1, 0);
    }
    fopMsgM_setNowAlpha(i_Msg->m0624 + 9, (dVar2 * 0.25f) + 0.25f);
}

/* 80210194-802103D4       .text dMsg_lightMove__FP13sub_msg_class */
void dMsg_lightMove(sub_msg_class* i_Msg) {
    i_Msg->m0624[0].mUserArea++;
    if (i_Msg->m0624[0].mUserArea >= 800) {
        i_Msg->m0624[0].mUserArea = 0;
    }
    f32 f31 = (i_Msg->m0624[0].mUserArea / 800.0f) * 360.0f;
    i_Msg->m0624[0].pane->rotate(i_Msg->m0624[0].mSize.x, 0.0f, ROTATE_Z, -f31);
    i_Msg->m0624[1].pane->rotate(0.0f, 0.0f, ROTATE_Z, -f31);
    i_Msg->m0624[2].pane->rotate(i_Msg->m0624[2].mSize.x, i_Msg->m0624[2].mSize.y, ROTATE_Z, -f31);
    i_Msg->m0624[3].pane->rotate(0.0f, i_Msg->m0624[3].mSize.y, ROTATE_Z, -f31);
    i_Msg->m0624[4].pane->rotate(i_Msg->m0624[4].mSize.x, 0.0f, ROTATE_Z, f31);
    i_Msg->m0624[5].pane->rotate(0.0f, 0.0f, ROTATE_Z, f31);
    i_Msg->m0624[6].pane->rotate(i_Msg->m0624[6].mSize.x, i_Msg->m0624[6].mSize.y, ROTATE_Z, f31);
    i_Msg->m0624[7].pane->rotate(0.0f, i_Msg->m0624[7].mSize.y, ROTATE_Z, f31);
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_setInitAlpha(&i_Msg->m0624[i]);
    }
}

/* 802103D4-802109A0       .text dMsg_cornerMove__FP13sub_msg_class */
void dMsg_cornerMove(sub_msg_class* param_1) {
    static const u8 cc_r[] = {200, 0, 0, 0};
    static const u8 cc_g[] = {128, 0, 0, 0};
    static const u8 cc_b[] = {255, 0, 255, 0};
    static const u8 cc2_r[] = {50, 50, 100, 50};
    static const u8 cc2_g[] = {50, 50, 100, 50};
    static const u8 cc2_b[] = {180, 180, 120, 180};
    static const u8 cc2_a[] = {255, 150, 255, 255};

    param_1->m049C.mUserArea++;
    if (param_1->m049C.mUserArea >= 240) {
        param_1->m049C.mUserArea = 0;
    }
    f32 tmp = fopMsgM_valueIncrease(0x3c, param_1->m049C.mUserArea % 0x3c, 2);
    GXColor local_68[4];
    if (param_1->mMesgEntry.mTextboxType == 1) {
        for (int i = 0; i < 4; i++) {
            int r9 = i + 1;
            if (r9 >= 4) {
                r9 = 0;
            }
            local_68[i].r = cc2_r[i] + tmp * (cc2_r[r9] - cc2_r[i]);
            local_68[i].g = cc2_g[i] + tmp * (cc2_g[r9] - cc2_g[i]);
            local_68[i].b = cc2_b[i] + tmp * (cc2_b[r9] - cc2_b[i]);
            local_68[i].a = cc2_a[i] + tmp * (cc2_a[r9] - cc2_a[i]);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            int r9 = i + 1;
            if (r9 >= 4) {
                r9 = 0;
            }
            local_68[i].r = cc_r[i] + tmp * (cc_r[r9] - cc_r[i]);
            local_68[i].g = cc_g[i] + tmp * (cc_g[r9] - cc_g[i]);
            local_68[i].b = cc_b[i] + tmp * (cc_b[r9] - cc_b[i]);
            local_68[i].a = 255;
        }
    }
    if (param_1->m049C.mUserArea < 0x3c) {
        ((J2DPicture*)param_1->m049C.pane)
            ->setCornerColor(
                *(JUtility::TColor*)&local_68[0], *(JUtility::TColor*)&local_68[1], *(JUtility::TColor*)&local_68[3], *(JUtility::TColor*)&local_68[2]
            );
    } else if (param_1->m049C.mUserArea < 0x78) {
        ((J2DPicture*)param_1->m049C.pane)
            ->setCornerColor(
                *(JUtility::TColor*)&local_68[1], *(JUtility::TColor*)&local_68[2], *(JUtility::TColor*)&local_68[0], *(JUtility::TColor*)&local_68[3]
            );
    } else if (param_1->m049C.mUserArea < 0xB4) {
        ((J2DPicture*)param_1->m049C.pane)
            ->setCornerColor(
                *(JUtility::TColor*)&local_68[2], *(JUtility::TColor*)&local_68[3], *(JUtility::TColor*)&local_68[1], *(JUtility::TColor*)&local_68[0]
            );
    } else {
        ((J2DPicture*)param_1->m049C.pane)
            ->setCornerColor(
                *(JUtility::TColor*)&local_68[3], *(JUtility::TColor*)&local_68[0], *(JUtility::TColor*)&local_68[2], *(JUtility::TColor*)&local_68[1]
            );
    }
}

/* 802109A0-80210AA0       .text dMsg_tactGuideShow__FP13sub_msg_classUc */
void dMsg_tactGuideShow(sub_msg_class* i_Msg, u8 param_2) {
    for (s32 i = 0; i < mBeatNum[dComIfGp_getMelodyNum()]; i++) {
        if (i < param_2) {
            if (dComIfGp_getMelodyNum() < 5) {
                fopMsgM_setInitAlpha(&i_Msg->m08C4[i]);
                fopMsgM_setNowAlpha(&i_Msg->m0A14[i], 0.5f);
                fopMsgM_setNowAlphaZero(&i_Msg->m0B64[i]);
            } else {
                fopMsgM_setInitAlpha(&i_Msg->m0B64[i]);
                fopMsgM_setNowAlpha(&i_Msg->m0A14[i], 0.5f);
                fopMsgM_setNowAlpha(&i_Msg->m08C4[i], 0.5f);
                fopMsgM_setNowAlpha(&i_Msg->m0CB4[i], 0.5f);
            }
        } else {
            i_Msg->m08C4[i].pane->hide();
            i_Msg->m0A14[i].pane->hide();
            i_Msg->m0B64[i].pane->hide();
            if (dComIfGp_getMelodyNum() >= 5) {
                i_Msg->m0CB4[i].pane->hide();
            }
        }
    }
}

/* 80210AA0-80210CA4       .text dMsg_numberInput__FP13sub_msg_class */
void dMsg_numberInput(sub_msg_class* i_Msg) {
    static char* num_str[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    u8 uVar2;

    for (s32 i = 0; i < 8; i++) {
        if (i_Msg->mMsgDataProc.field_0x281[i] == 0x16) {
            i_Msg->m10EC = ((i_Msg->m0544[0].pane)->mBounds.i.x + i_Msg->mMsgDataProc.field_0x168[i]);
            i_Msg->m10F0 = ((i_Msg->m0544[0].pane)->mBounds.i.y + (i_Msg->m1104 * (s32)((3 - i_Msg->m1108) + (i_Msg->mMsgDataProc.field_0x1A4[i]) * 2)));
        }
    }
    if (i_Msg->mMsgNo == 0x1cfa) {
        uVar2 = i_Msg->mMsgDataProc.inputNumber(3);
        i_Msg->mSelectNum = uVar2;
    } else {
        uVar2 = i_Msg->mMsgDataProc.inputNumber(2);
        i_Msg->mSelectNum = uVar2;
    }
    i_Msg->mMsgDataProc.colorAnime(maskPane);
    numberPane[2]->setString(num_str[dComIfGp_getMessageSetNumber() / 100]);
    numberPane[1]->setString(num_str[(dComIfGp_getMessageSetNumber() % 100) / 10]);
    numberPane[0]->setString(num_str[dComIfGp_getMessageSetNumber() % 10]);
    daNpc_Bs1_c::m_tag_buy_item = dComIfGp_getMessageSetNumber();
    if (((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) || (fopMsgM_checkMessageSend())) {
        dMsg_setCancelMode(i_Msg);
    } else {
        dMeter_Info.field_0x0[0] = 3;
    }
}

static void dummy() {
    OSReport("hukidashi_021.bti");
    OSReport("texture != 0");
};

/* 80210CA4-80210F28       .text dMsg_tactInput__FP13sub_msg_class */
void dMsg_tactInput(sub_msg_class* i_Msg) {
    s16 sVar1;
    f32 alpha;
    int iVar3;
    s32 melody_no;
    f32 dVar5;
    s32 local_38;

    melody_no = dComIfGp_getMelodyNum();
    if (i_Msg->m1100 < mBeatNum[melody_no]) {
        if ((mBeatNum[melody_no] != mDoAud_tact_getBeat()) || (i_Msg->m1168 != mDoAud_tact_getBeat())) {
            i_Msg->m1100 = 0;
            i_Msg->m0624[0].mUserArea = 0;
            i_Msg->m1168 = mDoAud_tact_getBeat();
            dMsg_tactGuideShow(i_Msg, mBeatNum[melody_no]);
        }
        if (daPy_getPlayerActorClass()->checkTactInput()) {
            sVar1 = daPy_getPlayerLinkActorClass()->m34D6;
            mDoAud_tact_getMelodyPattern(melody_no, i_Msg->m1100, &local_38);
            i_Msg->m1100++;
            if ((sVar1 == local_38) && (mBeatNum[melody_no] == mDoAud_tact_getBeat())) {
                iVar3 = (int)i_Msg->m0624[0].mUserArea;
                if (iVar3 == i_Msg->m1100 + -1) {
                    i_Msg->m0B64[iVar3].mUserArea = 1;
                    i_Msg->m0624[0].mUserArea++;
                }
            }
            if ((i_Msg->m1100 >= (mDoAud_tact_getBeat())) && (!daPy_getPlayerLinkActorClass()->checkTactLastInput())) {
                i_Msg->m1100 = 0;
                i_Msg->m0624[0].mUserArea = 0;
                dMsg_tactGuideShow(i_Msg, mBeatNum[melody_no]);
            }
        } else {
            if (((((melody_no != 1) && (melody_no != 5)) && (melody_no != 6)) && (melody_no != 7)) && (CPad_CHECK_TRIG_B(0) || (fopMsgM_checkMessageSend()))) {
                dMsg_setCancelMode(i_Msg);
            }
        }
    }
    for (s32 i = 0; i < mBeatNum[melody_no]; i++) {
        sVar1 = i_Msg->m0B64[i].mUserArea;
        if ((sVar1 > 0) && (sVar1 <= 5)) {
            dVar5 = fopMsgM_valueIncrease(5, (int)sVar1, 0);
            alpha = (dVar5 * 0.5f) + 0.5f;
            dVar5 = alpha;
            if (dComIfGp_getMelodyNum() < 5) {
                fopMsgM_setNowAlpha(&i_Msg->m0A14[i], alpha);
                fopMsgM_setNowAlpha(&i_Msg->m0B64[i], dVar5);
            } else {
                fopMsgM_setNowAlpha(&i_Msg->m0A14[i], alpha);
                fopMsgM_setNowAlpha(&i_Msg->m08C4[i], dVar5);
                fopMsgM_setNowAlpha(&i_Msg->m0CB4[i], dVar5);
            }
            if (i_Msg->m0B64[mBeatNum[melody_no] - 1].mUserArea == 5) {
                i_Msg->mStatus = fopMsgStts_MSG_DISPLAYED_e;
                i_Msg->m1100 = 0;
            }
            i_Msg->m0B64[i].mUserArea++;
        }
    }
}

/* 80210F28-80210F50       .text dMsg_tactInput2__FP13sub_msg_class */
void dMsg_tactInput2(sub_msg_class*) {
    if (!CPad_CHECK_TRIG_B(0)) {
        return;
    }
    dComIfGp_setMesgCancelButton(1);
}

/* 80210F50-80210FF8       .text dMsg_subTextScale__FP13sub_msg_classf */
void dMsg_subTextScale(sub_msg_class* i_Msg, f32 param_2) {
    for (s32 i = 1; i < 10; i++) {
        i_Msg->m026C[i].pane->move(i_Msg->m026C[i].mPosTopLeft.x * param_2, i_Msg->m026C[i].mPosTopLeft.y * param_2);
        i_Msg->m026C[i].pane->resize(i_Msg->m026C[i].mSize.x * param_2, i_Msg->m026C[i].mSize.y * param_2);
    }
}

/* 80210FF8-8021172C       .text dMsg_subTextSizeSet__FP13sub_msg_class */
void dMsg_subTextSizeSet(sub_msg_class* i_Msg) {
    /* Nonmatching */
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    f32 fVar5;
    int uVar6;
    int iVar7;
    f32 dVar10;
    f32 dVar11;
    f32 local_78;
    f32 local_68;

    iVar7 = (int)((J2DTextBox*)i_Msg->m0544[0].pane)->getLineSpace();
    if (i_Msg->mStatus == fopMsgStts_SELECT_2_e) {
        local_78 = iVar7 + i_Msg->m110C;
    } else if (i_Msg->mStatus == fopMsgStts_SELECT_3_e) {
        local_78 = i_Msg->m110C + iVar7 * 2;
    }
    fVar1 = i_Msg->m049C.mPosCenter.y;
    if (fVar1 >= 240.0f) {
        local_78 = (int)g_msgHIO.field_0x7c;
        fVar1 = (local_78) + (fVar1 - i_Msg->m049C.mSize.y * 0.5f);
    } else {
        fVar1 = (fVar1 + i_Msg->m049C.mSize.y * 0.5f) - ((int)g_msgHIO.field_0x7c);
    }
    local_68 = (int)g_msgHIO.field_0x78;
    fVar3 = (local_68) + ((g_msgHIO.field_0x7e) * 2.0f + (i_Msg->mMsgDataProc.field_0x21C) - i_Msg->m011C[0].mSizeOrig.x);
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m011C[i].mSize.x = i_Msg->m011C[i].mSizeOrig.x + fVar3;
    }
    i_Msg->m026C[5].mSize.x = i_Msg->m026C[5].mSizeOrig.x + fVar3;
    i_Msg->m026C[8].mSize.x = i_Msg->m026C[8].mSizeOrig.x + fVar3;
    i_Msg->m026C[9].mSize.x = i_Msg->m026C[9].mSizeOrig.x + fVar3;
    fVar3 = ((int)g_msgHIO.field_0x7a) + (local_78 - i_Msg->m011C[0].mSizeOrig.y);
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m011C[i].mSize.y = i_Msg->m011C[i].mSizeOrig.y + fVar3;
    }
    i_Msg->m026C[6].mSize.y = i_Msg->m026C[6].mSizeOrig.y + fVar3;
    i_Msg->m026C[7].mSize.y = i_Msg->m026C[7].mSizeOrig.y + fVar3;
    i_Msg->m026C[9].mSize.y = i_Msg->m026C[9].mSizeOrig.y + fVar3;
    fVar3 = (i_Msg->m026C[9].mSizeOrig.x - i_Msg->m026C[9].mSize.x) * 0.5f;
    i_Msg->m026C[0].mPosCenter.x = i_Msg->m026C[0].mPosCenterOrig.x + fVar3;
    i_Msg->m026C[1].mPosCenter.x = i_Msg->m026C[1].mPosCenterOrig.x + fVar3;
    i_Msg->m026C[2].mPosCenter.x = i_Msg->m026C[2].mPosCenterOrig.x - fVar3;
    i_Msg->m026C[3].mPosCenter.x = i_Msg->m026C[3].mPosCenterOrig.x + fVar3;
    i_Msg->m026C[4].mPosCenter.x = i_Msg->m026C[4].mPosCenterOrig.x - fVar3;
    i_Msg->m026C[6].mPosCenter.x = i_Msg->m026C[6].mPosCenterOrig.x + fVar3;
    i_Msg->m026C[7].mPosCenter.x = i_Msg->m026C[7].mPosCenterOrig.x - fVar3;
    fVar3 = (i_Msg->m011C[0].mSizeOrig.x - i_Msg->m011C[0].mSize.x) * 0.5f;
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m011C[i].mPosCenter.x = ((g_msgHIO.field_0x7e) + i_Msg->m011C[i].mPosCenterOrig.x) + fVar3;
    }
    fVar5 = (i_Msg->m026C[9].mSizeOrig.y - i_Msg->m026C[9].mSize.y) * 0.5f;
    fVar2 = i_Msg->m026C[0].mPosCenterOrig.y;
    i_Msg->m026C[0].mPosCenter.y = fVar1;
    i_Msg->m026C[1].mPosCenter.y = i_Msg->m026C[1].mPosCenterOrig.y - fVar5;
    i_Msg->m026C[2].mPosCenter.y = i_Msg->m026C[2].mPosCenterOrig.y - fVar5;
    i_Msg->m026C[3].mPosCenter.y = i_Msg->m026C[3].mPosCenterOrig.y + fVar5;
    i_Msg->m026C[4].mPosCenter.y = i_Msg->m026C[4].mPosCenterOrig.y + fVar5;
    i_Msg->m026C[5].mPosCenter.y = i_Msg->m026C[5].mPosCenterOrig.y - fVar5;
    i_Msg->m026C[8].mPosCenter.y = i_Msg->m026C[8].mPosCenterOrig.y + fVar5;
    for (s32 i = 0; i < 4; i++) {
        i_Msg->m011C[i].mPosCenter.y = i_Msg->m011C[i].mPosCenterOrig.y + (fVar1 - fVar2);
    }
    i_Msg->m01FC.mPosCenterOrig.x = fVar3 + i_Msg->m01FC.mPosTopLeftOrig.x + i_Msg->m01FC.mSizeOrig.x * 0.5f;
    i_Msg->m0234.mPosCenterOrig.x = (g_msgHIO.field_0x7e) * 2.0f + i_Msg->m01FC.mPosCenterOrig.x + i_Msg->m01FC.mSizeOrig.x + (i_Msg->mMsgDataProc.field_0x21C);
    i_Msg->m01FC.mPosCenterOrig.y = fVar5 + i_Msg->m01FC.mPosTopLeftOrig.y + i_Msg->m01FC.mSizeOrig.y * 0.5f;
    i_Msg->m0234.mPosCenterOrig.y = fVar5 + i_Msg->m0234.mPosTopLeftOrig.y + i_Msg->m0234.mSizeOrig.y * 0.5f;
    for (s32 i = 0; i < 4; i++) {
        fopMsgM_cposMove(&i_Msg->m011C[i]);
    }
    for (s32 i = 0; i < 10; i++) {
        fopMsgM_cposMove(&i_Msg->m026C[i]);
    }
    if (i_Msg->m026C[9].mSize.x >= 282.0f) {
        fVar1 = 2.0f;
    } else {
        fVar1 = 3.0f;
    }
    dVar11 = fVar1;
    fVar3 = i_Msg->m026C[0].mSize.y * 0.5f;
    i_Msg->m026C[0].pane->rotate(i_Msg->m026C[0].mSize.x * 0.5f, fVar3, ROTATE_Z, fVar1);
    dVar10 = 0.5f;
    for (s32 i = 0; i < 4; i++) {
        fVar1 = i_Msg->m011C[i].mSize.y * dVar10;
        fVar3 = fVar1 + i_Msg->m026C[0].mPosCenter.y;
        fVar2 = fVar3 - i_Msg->m011C[i].mPosCenter.y;
        i_Msg->m011C[i].pane->rotate(
            ((i_Msg->m011C[i].mSize.x * dVar10) + i_Msg->m026C[0].mPosCenter.x) - i_Msg->m011C[i].mPosCenter.x, fVar2, ROTATE_Z, dVar11
        );
    }
    fVar1 = i_Msg->m026C[9].mSize.x;
    uVar6 = (int)g_msgHIO.field_0x74;
    if ((uVar6) <= fVar1) {
        fVar1 = 1.0f;
    } else {
        fVar1 = ((int)(fVar1 / (uVar6)) + 0.5f);
    }
    fVar3 = i_Msg->m026C[9].mSize.y;
    uVar6 = (int)g_msgHIO.field_0x74;
    local_78 = uVar6;
    if ((local_78) <= fVar3) {
        fVar3 = 1.0f;
    } else {
        fVar3 = ((int)(fVar3 / (uVar6)) + 0.5f);
    }
    ((MyPicture*)i_Msg->m026C[5].pane)->m134 = 1;
    ((MyPicture*)i_Msg->m026C[5].pane)->m124 = 0.0f;
    ((MyPicture*)i_Msg->m026C[5].pane)->m128 = 0.0f;
    ((MyPicture*)i_Msg->m026C[5].pane)->m12C = fVar1;
    ((MyPicture*)i_Msg->m026C[5].pane)->m130 = 1.0f;
    ((MyPicture*)i_Msg->m026C[6].pane)->m134 = 1;
    ((MyPicture*)i_Msg->m026C[6].pane)->m124 = 0.0f;
    ((MyPicture*)i_Msg->m026C[6].pane)->m128 = 0.0f;
    ((MyPicture*)i_Msg->m026C[6].pane)->m12C = fVar3;
    ((MyPicture*)i_Msg->m026C[6].pane)->m130 = 1.0f;
    ((MyPicture*)i_Msg->m026C[7].pane)->m134 = 1;
    ((MyPicture*)i_Msg->m026C[7].pane)->m124 = 0.0f;
    ((MyPicture*)i_Msg->m026C[7].pane)->m128 = 0.0f;
    ((MyPicture*)i_Msg->m026C[7].pane)->m12C = fVar3;
    ((MyPicture*)i_Msg->m026C[7].pane)->m130 = 1.0f;
    ((MyPicture*)i_Msg->m026C[8].pane)->m134 = 1;
    ((MyPicture*)i_Msg->m026C[8].pane)->m124 = 0.0f;
    ((MyPicture*)i_Msg->m026C[8].pane)->m128 = 0.0f;
    ((MyPicture*)i_Msg->m026C[8].pane)->m12C = fVar1;
    ((MyPicture*)i_Msg->m026C[8].pane)->m130 = 1.0f;
    i_Msg->m026C[9].mUserArea = 0;
}

/* 8021172C-802118D8       .text dMsg_subTextOpen__FP13sub_msg_class */
void dMsg_subTextOpen(sub_msg_class* i_Msg) {
    static const Vec frameScale = {1.5f, 0.96f, 1.0f};
    f32 fVar1;
    int iVar2;
    int iVar3;
    f32 dVar4;
    f32 dVar5;

    s32 tmp = g_msgHIO.field_0x44 + g_msgHIO.field_0x46;
    i_Msg->m026C[9].mUserArea++;
    dVar4 = fopMsgM_valueIncrease(tmp, (int)i_Msg->m026C[9].mUserArea, 0);
    iVar3 = (int)i_Msg->m026C[9].mUserArea;
    iVar2 = (int)g_msgHIO.field_0x44;
    if (iVar3 < iVar2) {
        dVar5 = fopMsgM_valueIncrease(iVar2, iVar3, 0);
        fVar1 = (dVar5 * (frameScale.y - frameScale.x)) + frameScale.x;
    } else {
        dVar5 = fopMsgM_valueIncrease((int)g_msgHIO.field_0x46, iVar3 - iVar2, 0);
        fVar1 = (dVar5 * (frameScale.z - frameScale.y)) + frameScale.y;
    }
    dMsg_subTextScale(i_Msg, (fVar1));
    for (s32 i = 0; i < 10; i++) {
        fopMsgM_setNowAlpha(&i_Msg->m026C[i], dVar4);
    }
    dVar5 = (1.0f - ((1.0f - (g_msgHIO.field_0x81) / 255.0f) * dVar4));
    fopMsgM_setNowAlpha(&i_Msg->m049C, 1.0f - ((1.0f - (g_msgHIO.field_0x80) / 255.0f) * dVar4));
    fopMsgM_setNowAlpha(&i_Msg->m0544[0], dVar5);
    fopMsgM_setNowAlpha(&i_Msg->m0544[1], dVar5);
    fopMsgM_setNowAlpha(&i_Msg->m0544[2], dVar5);
    fopMsgM_setNowAlpha(&i_Msg->m0544[3], dVar5);
}

/* 802118D8-80211A8C       .text dMsg_subTextClose__FP13sub_msg_class */
void dMsg_subTextClose(sub_msg_class* i_Msg) {
    int iVar1;
    int iVar2;
    f32 dVar3;
    f32 dVar4;

    i_Msg->m026C[9].mUserArea++;
    iVar1 = (int)i_Msg->m026C[9].mUserArea;
    iVar2 = (int)g_msgHIO.field_0x48;
    if (iVar1 <= iVar2) {
        dVar3 = fopMsgM_valueIncrease(iVar2, iVar2 - iVar1, 0);
        dVar4 = fopMsgM_valueIncrease((int)g_msgHIO.field_0x48, (int)i_Msg->m026C[9].mUserArea, 0);
        dMsg_subTextScale(i_Msg, (((g_msgHIO.field_0x40 - 1.0f) * dVar4) + 1.0f));
        for (s32 i = 0; i < 10; i++) {
            fopMsgM_setNowAlpha(&i_Msg->m026C[i], dVar3);
        }
        fopMsgM_setNowAlphaZero(&i_Msg->m01FC);
        fopMsgM_setNowAlphaZero(&i_Msg->m0234);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[0]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[1]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[2]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[3]);
    } else {
        dVar3 = fopMsgM_valueIncrease((int)g_msgHIO.field_0x76, (int)g_msgHIO.field_0x76 - (iVar1 - iVar2), 0);
        dVar4 = (1.0f - (1.0f - ((g_msgHIO.field_0x81) / 255.0f)) * dVar3);
        fopMsgM_setNowAlpha(&i_Msg->m049C, 1.0f - ((1.0f - (g_msgHIO.field_0x80) / 255.0f) * dVar3));
        fopMsgM_setNowAlpha(&i_Msg->m0544[0], dVar4);
        fopMsgM_setNowAlpha(&i_Msg->m0544[1], dVar4);
        fopMsgM_setNowAlpha(&i_Msg->m0544[2], dVar4);
        fopMsgM_setNowAlpha(&i_Msg->m0544[3], dVar4);
    }
}

/* 80211A8C-80211B34       .text dMsg_setCloseSound__FP13sub_msg_classUc */
void dMsg_setCloseSound(sub_msg_class* i_Msg, u8 param_2) {
    mDoAud_talkOut();
    if ((dComIfGp_getDoStatusForce() == dActStts_CANCEL_e) || (param_2 != 0)) {
        mDoAud_seStart(JA_SE_TALK_SEL_CANCEL);
    } else {
        mDoAud_seStart(JA_SE_TALK_WIN_CLOSE);
    }
}

/* 80211B34-80211BCC       .text dMsg_setCancelMode__FP13sub_msg_class */
void dMsg_setCancelMode(sub_msg_class* i_Msg) {
    i_Msg->mStatus = fopMsgStts_MSG_DISPLAYED_e;
    i_Msg->m1100 = 0;
    if (CPad_CHECK_TRIG_B(0)) {
        i_Msg->m1169 = 1;
        dComIfGp_setMesgCancelButton(1);
    } else {
        i_Msg->m1169 = 0;
    }
    dMsg_setCloseSound(i_Msg, 0);
    mDoAud_talkOut();
    i_Msg->m116A++;
    dComIfGp_setMesgSendButton(i_Msg->m116A);
}

/* 80211BCC-80211DA0       .text dMsg_messageShow__FP13sub_msg_class */
void dMsg_messageShow(sub_msg_class* i_Msg) {
    u8 cVar2;
    u32 iVar1;

    fopMsgM_paneScaleXY(&i_Msg->m049C, 1.0f);
    fopMsgM_setInitAlpha(&i_Msg->m049C);
    dMsg_messagePaneShow(i_Msg);
    dMsg_yose_select(i_Msg);
    if (i_Msg->mMesgEntry.mInitialSound != 0) {
        mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
    }
    i_Msg->mMsgDataProc.field_0x299 = 1;
    i_Msg->mMsgDataProc.stringSet();
    for (s32 i = 0; i < 8; i++) {
        cVar2 = i_Msg->mMsgDataProc.field_0x281[i];
        iVar1 = i_Msg->mMsgDataProc.field_0x220[i];
        u32 var_r6 = iVar1;
        if (((((u8)(cVar2 - 10U) <= 3) || (cVar2 == 0x15)) || (cVar2 == 0x17)) && (iVar1 == 0)) {
            var_r6 = -1;
        }
        if (((cVar2 != 0xFF) && (buttonTimer[i] == -1)) && (cVar2 != 0x14 && (cVar2 != 0x15 && (cVar2 != 0x16)))) {
            fopMsgM_outFontSet(button_icon[i], button_kage[i], &buttonTimer[i], var_r6, cVar2);
        }
    }
    dMsg_setString(i_Msg);
    i_Msg->m1100 = 0;
    for (s32 i = 0; i < mBeatNum[dComIfGp_getMelodyNum()]; i++) {
        i_Msg->m0B64[i].mUserArea = 0;
        if (dComIfGp_getMelodyNum() < 5) {
            fopMsgM_setNowAlpha(&i_Msg->m0A14[i], 0.5f);
            fopMsgM_setNowAlphaZero(&i_Msg->m0B64[i]);
        } else {
            fopMsgM_setNowAlpha(&i_Msg->m0A14[i], 0.5f);
            fopMsgM_setNowAlpha(&i_Msg->m08C4[i], 0.5f);
            fopMsgM_setNowAlpha(&i_Msg->m0CB4[i], 0.5f);
        }
    }
}

/* 80211DA0-8021209C       .text dMsg_stopProc__FP13sub_msg_class */
s32 dMsg_stopProc(sub_msg_class* i_Msg) {
    u8 bVar1;
    u32 uVar2;

    if (i_Msg->mMsgDataProc.field_0x297 != 0) {
        uVar2 = (int)i_Msg->mMsgDataProc.field_0x158 > 0 ? i_Msg->mMsgDataProc.field_0x158 - 1 : 0;
        i_Msg->mMsgDataProc.field_0x158 = uVar2;
        if (uVar2 == 0) {
            i_Msg->mMsgDataProc.field_0x297 = 0;
            i_Msg->mMsgDataProc.field_0x296 = 0;
            i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
            dMsg_value_init(i_Msg);
            dMsg_yose_select(i_Msg);
            dMsg_setString(i_Msg);
            bVar1 = i_Msg->mMesgEntry.mTextboxType;
            if ((bVar1 != 5) && (bVar1 != 0xe)) {
                dMsg_arrowInit(i_Msg);
            }
            dMeter_Info.field_0x0[0] = 2;
            if (dComIfGp_getDoStatusForce() == dActStts_CANCEL_e) {
                mDoAud_seStart(JA_SE_TALK_SEL_CANCEL);
            } else {
                mDoAud_seStart(JA_SE_TALK_NEXT);
            }
            i_Msg->m116A++;
            dComIfGp_setMesgSendButton(i_Msg->m116A);
        } else {
            bVar1 = i_Msg->mMesgEntry.mTextboxType;
            if ((bVar1 != 5) && (bVar1 != 0xe)) {
                dMsg_arrowMove(i_Msg);
            }
            dMeter_Info.field_0x0[0] = 1;
        }
    } else {
        if (((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) && (!dComIfGp_checkMesgBgm())) {
            i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
            dMsg_value_init(i_Msg);
            dMsg_yose_select(i_Msg);
            dMsg_setString(i_Msg);
            if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
                dMsg_arrowInit(i_Msg);
            }
            dMeter_Info.field_0x0[0] = 2;
            if (dComIfGp_getDoStatusForce() == dActStts_CANCEL_e) {
                mDoAud_seStart(JA_SE_TALK_SEL_CANCEL);
            } else {
                mDoAud_seStart(JA_SE_TALK_NEXT);
            }
            if (((i_Msg->mMesgEntry.mDrawType == 0) && (CPad_CHECK_TRIG_B(0))) && (!dComIfGp_checkMesgBgm())) {
                if (i_Msg->mMsgDataProc.field_0x296 == 0) {
                    i_Msg->mMsgDataProc.field_0x299 = 1;
                }
                if (((i_Msg->mMsgDataProc.field_0x297 == 0) && (i_Msg->mMsgDataProc.field_0x298 == 0)) && ((s32)i_Msg->mMsgDataProc.field_0x158 != 0)) {
                    i_Msg->mMsgDataProc.field_0x158 = 0;
                    i_Msg->mMsgDataProc.field_0x296 = 0;
                }
            }
            i_Msg->m116A++;
            dComIfGp_setMesgSendButton(i_Msg->m116A);
        } else {
            if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
                dMsg_arrowMove(i_Msg);
            }
            dMeter_Info.field_0x0[0] = 1;
        }
    }
    return TRUE;
}

/* 8021209C-802128B0       .text dMsg_selectProc__FP13sub_msg_class */
s32 dMsg_selectProc(sub_msg_class* i_Msg) {
    int uVar1;
    s16 sVar3;
    u8 cVar6;
    u8 uVar7;
    J2DTextBox* pJVar8;
    u8 uVar9;
    int iVar10;
    int iVar11;
    J2DPicture* pJVar14;

    pJVar8 = (J2DTextBox*)i_Msg->m0544[0].pane;
    iVar10 = (int)pJVar8->mBounds.i.x;
    iVar11 = (int)pJVar8->mBounds.i.y;
    uVar1 = pJVar8->getLineSpace();
    sVar3 = i_Msg->m026C[0].mUserArea;
    if (sVar3 == 0) {
        if ((i_Msg->mStatus == fopMsgStts_SELECT_2_e) || (i_Msg->mStatus == fopMsgStts_SELECT_3_e)) {
            if (((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) || (fopMsgM_checkMessageSend())) {
                dMsg_subTextSizeSet(i_Msg);
                i_Msg->m026C[0].mUserArea = 1;
                mDoAud_seStart(JA_SE_TALK_SEL_WIN_OPEN);
                goto end;
            }
            if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
                dMsg_arrowMove(i_Msg);
            }
            dMeter_Info.field_0x0[0] = 1;
        } else {
            if (i_Msg->mStatus == fopMsgStts_SELECT_YOKO_e) {
                i_Msg->m026C[0].mUserArea = 2;
            }
        }
        goto end;
    }
    if (sVar3 == 1) {
        if ((int)i_Msg->m026C[9].mUserArea < (int)g_msgHIO.field_0x44 + (int)g_msgHIO.field_0x46) {
            dMsg_subTextOpen(i_Msg);
            goto end;
        }
        fopMsgM_setInitAlpha(&i_Msg->m01FC);
        fopMsgM_setInitAlpha(&i_Msg->m0234);
        fopMsgM_setInitAlpha(&i_Msg->m011C[0]);
        fopMsgM_setInitAlpha(&i_Msg->m011C[1]);
        fopMsgM_setInitAlpha(&i_Msg->m011C[2]);
        fopMsgM_setInitAlpha(&i_Msg->m011C[3]);
        i_Msg->m026C[9].mUserArea = 0;
        fopMsgM_paneTrans(&i_Msg->m01FC, 0.0f, 0.0f);
        fopMsgM_paneTrans(&i_Msg->m0234, 0.0f, 0.0f);
        i_Msg->m026C[0].mUserArea = 2;
        if ((i_Msg->mMesgEntry.mTextboxType == 5) || (i_Msg->mMesgEntry.mTextboxType == 0xe)) {
            goto end;
        }
        dMsg_arrowInit(i_Msg);
        goto end;
    }
    if (sVar3 != 2) {
        goto end;
    }
    if (i_Msg->mStatus == fopMsgStts_SELECT_2_e) {
        uVar7 = i_Msg->mMsgDataProc.selectCheck2(arrowPane, iVar10, iVar11 + uVar1 + ((int)uVar1 / 2), uVar1);
        i_Msg->mSelectNum = uVar7;
        i_Msg->m026C[8].mUserArea++;
        if (i_Msg->m026C[8].mUserArea >= 0x14) {
            i_Msg->m026C[8].mUserArea = 0;
        }
        sVar3 = i_Msg->m026C[8].mUserArea;
        if (sVar3 < 10) {
            pJVar14 = (J2DPicture*)i_Msg->m01FC.pane;
            pJVar14->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
            pJVar14 = (J2DPicture*)i_Msg->m0234.pane;
            pJVar14->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
        } else if (sVar3 < 0x14) {
            pJVar14 = (J2DPicture*)i_Msg->m01FC.pane;
            pJVar14->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
            pJVar14 = (J2DPicture*)i_Msg->m0234.pane;
            pJVar14->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        }
        fopMsgM_paneTrans(&i_Msg->m01FC, 0.0f, i_Msg->mSelectNum * uVar1);
        fopMsgM_paneTrans(&i_Msg->m0234, 0.0f, i_Msg->mSelectNum * uVar1);
    } else if (i_Msg->mStatus == fopMsgStts_SELECT_3_e) {
        uVar7 = i_Msg->mMsgDataProc.selectCheck3(arrowPane, iVar10, iVar11, uVar1);
        i_Msg->mSelectNum = uVar7;
        i_Msg->m026C[8].mUserArea++;
        if (i_Msg->m026C[8].mUserArea >= 0x14) {
            i_Msg->m026C[8].mUserArea = 0;
        }
        sVar3 = i_Msg->m026C[8].mUserArea;
        if (sVar3 < 10) {
            pJVar14 = (J2DPicture*)i_Msg->m01FC.pane;
            pJVar14->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
            pJVar14 = (J2DPicture*)i_Msg->m0234.pane;
            pJVar14->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
        } else if (sVar3 < 0x14) {
            pJVar14 = (J2DPicture*)i_Msg->m01FC.pane;
            pJVar14->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
            pJVar14 = (J2DPicture*)i_Msg->m0234.pane;
            pJVar14->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        }
        fopMsgM_paneTrans(&i_Msg->m01FC, 0.0f, i_Msg->mSelectNum * uVar1);
        fopMsgM_paneTrans(&i_Msg->m0234, 0.0f, i_Msg->mSelectNum * uVar1);
    } else if (i_Msg->mStatus == fopMsgStts_SELECT_YOKO_e) {
        s32 var_r5 = 0;
        s32 var_r6 = 0;
        s32 var_r11 = 0;
        for (s32 i = 0; i < 8; i++) {
            cVar6 = i_Msg->mMsgDataProc.field_0x281[i];
            if (cVar6 == 0x14) {
                var_r5 = (int)(i_Msg->m0544[0].pane->mBounds.i.x + ((int)i_Msg->mMsgDataProc.field_0x168[i]));
                var_r6 = (int)(i_Msg->m0544[0].pane->mBounds.i.y + (int)(i_Msg->m1104 * ((2 - i_Msg->m1108) + (i_Msg->mMsgDataProc.field_0x1A4[i] * 2))));
            } else if (cVar6 == 0x15) {
                var_r11 = (int)(i_Msg->m0544[0].pane->mBounds.i.x + ((int)i_Msg->mMsgDataProc.field_0x168[i]));
            }
        }
        i_Msg->mSelectNum = i_Msg->mMsgDataProc.selectCheckYoko(arrowPane, var_r5, var_r6, var_r11 - var_r5);
    }
    if (!CPad_CHECK_TRIG_A(0)) {
        if (((!CPad_CHECK_TRIG_B(0)) || (dComIfGp_getAStatus() != dActStts_CANCEL_e)) && (!fopMsgM_checkMessageSend())) {
            goto end;
        }
    }
    if ((i_Msg->mStatus == fopMsgStts_SELECT_2_e) || (i_Msg->mStatus == fopMsgStts_SELECT_3_e)) {
        i_Msg->m026C[0].mUserArea = 3;
        fopMsgM_setNowAlphaZero(&i_Msg->m01FC);
        fopMsgM_setNowAlphaZero(&i_Msg->m0234);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[0]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[1]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[2]);
        fopMsgM_setNowAlphaZero(&i_Msg->m011C[3]);
    } else {
        i_Msg->m026C[0].mUserArea = 0;
    }
    i_Msg->m1100 = 0;
    i_Msg->m026C[9].mUserArea = 0;
    if (CPad_CHECK_TRIG_B(0)) {
        i_Msg->m1169 = 1;
        dComIfGp_setMesgCancelButton(1);
    } else {
        i_Msg->m1169 = 0;
    }
    if (i_Msg->mMesgEntry.mNextMsgNo == 1) {
        if (i_Msg->mSelectNum == 0) {
            uVar9 = 1;
        } else {
            uVar9 = 0;
        }
    } else if (i_Msg->mMesgEntry.mNextMsgNo == 2) {
        uVar9 = 0;
    } else {
        if (((i_Msg->mStatus == fopMsgStts_SELECT_2_e) && (i_Msg->mSelectNum == 1)) || (i_Msg->mStatus == fopMsgStts_SELECT_3_e && (i_Msg->mSelectNum == 2))) {
            uVar9 = 1;
        } else {
            uVar9 = 0;
        }
    }
    dMsg_setCloseSound(i_Msg, uVar9);
    i_Msg->mStatus = fopMsgStts_MSG_DISPLAYED_e;
    i_Msg->m116A++;
    dComIfGp_setMesgSendButton(i_Msg->m116A);
end:
    return TRUE;
}

/* 802128B0-80212910       .text dMsg_inputProc__FP13sub_msg_class */
s32 dMsg_inputProc(sub_msg_class* i_Msg) {
    if (i_Msg->mMesgEntry.mTextboxType == 0xe) {
        if (fopMsgM_tactMsgFlagCheck()) {
            dMsg_tactInput(i_Msg);
        } else {
            dMsg_tactInput2(i_Msg);
        }
    } else {
        dMsg_numberInput(i_Msg);
    }
    return TRUE;
}

/* 80212910-80212DC0       .text dMsg_demoProc__FP13sub_msg_class */
s32 dMsg_demoProc(sub_msg_class* i_Msg) {
    s16 sVar1;
    u8 cVar3;
    u32 iVar2;
    int iVar4;
    s32 melody_no;
    f32 dVar9;
    f32 fVar10;
    s32 lStack_68;
    f32 local_64[7];

    if (i_Msg->m116B == 0) {
        melody_no = dComIfGp_getMelodyNum();
        static bool flag = 0;
        static s16 cnt = 0;
        local_64[0] = 0.0f;
        for (s32 i = 0; i < mBeatNum[melody_no]; i++) {
            local_64[i + 1] = mDoAud_tact_getMelodyPattern((u8)melody_no, i, &lStack_68);
            local_64[i + 1] += local_64[i];
        }
        if (i_Msg->m1100 == 0) {
            cnt = 0;
            mDoAud_tact_melodyPlay(melody_no);
        }
        if (i_Msg->m1100 < (s16)local_64[mBeatNum[melody_no]]) {
            i_Msg->m1100++;
            if (i_Msg->m1100 >= (s16)local_64[cnt]) {
                i_Msg->m0B64[cnt].mUserArea = 1;
                cnt++;
            }
        }
        for (s32 i = 0; i < mBeatNum[melody_no]; i++) {
            sVar1 = i_Msg->m0B64[i].mUserArea;
            iVar4 = (int)sVar1;
            if ((sVar1 > 0) && (iVar4 <= 0x23)) {
                if (iVar4 < 5) {
                    dVar9 = fopMsgM_valueIncrease(5, iVar4, 0);
                    fVar10 = (dVar9 * 0.5f) + 0.5f;
                    dVar9 = fVar10;
                    if (dComIfGp_getMelodyNum() < 5) {
                        fopMsgM_setNowAlpha(&i_Msg->m0A14[i], fVar10);
                        fopMsgM_setNowAlpha(&i_Msg->m0B64[i], dVar9);
                    } else {
                        fopMsgM_setNowAlpha(&i_Msg->m0A14[i], fVar10);
                        fopMsgM_setNowAlpha(&i_Msg->m08C4[i], dVar9);
                        fopMsgM_setNowAlpha(&i_Msg->m0CB4[i], dVar9);
                    }
                } else {
                    fopMsgM_setInitAlpha(&i_Msg->m0A14[i]);
                    fopMsgM_setInitAlpha(&i_Msg->m0B64[i]);
                    if (dComIfGp_getMelodyNum() >= 5) {
                        fopMsgM_setInitAlpha(&i_Msg->m0CB4[i]);
                    }
                }
                i_Msg->m0B64[i].mUserArea++;
                if (i_Msg->m0B64[mBeatNum[melody_no] - 1].mUserArea > 0x23) {
                    if (flag != 0) {
                        dMsg_messagePaneShow(i_Msg);
                        dMsg_yose_select(i_Msg);
                        if (i_Msg->mMesgEntry.mInitialSound != 0) {
                            mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
                        }
                        i_Msg->mMsgDataProc.field_0x299 = 1;
                        i_Msg->mMsgDataProc.stringSet();
                        for (s32 j = 0; j < 8; j++) {
                            cVar3 = i_Msg->mMsgDataProc.field_0x281[j];
                            iVar2 = i_Msg->mMsgDataProc.field_0x220[j];
                            u32 var_r6 = iVar2;
                            if (((((u8)(cVar3 - 10U) <= 3) || (cVar3 == 0x15)) || (cVar3 == 0x17)) && (iVar2 == 0)) {
                                var_r6 = -1;
                            }
                            if (((cVar3 != 0xFF) && (buttonTimer[j] == -1)) && (cVar3 != 0x14 && (cVar3 != 0x15 && (cVar3 != 0x16)))) {
                                fopMsgM_outFontSet(button_icon[j], button_kage[j], &buttonTimer[j], var_r6, cVar3);
                            }
                        }
                        dMsg_setString(i_Msg);
                        fopMsgM_setNowAlphaZero(&i_Msg->m0544[0]);
                        fopMsgM_setNowAlphaZero(&i_Msg->m0544[1]);
                        fopMsgM_setNowAlphaZero(&i_Msg->m0544[2]);
                        fopMsgM_setNowAlphaZero(&i_Msg->m0544[3]);
                        i_Msg->m116B = 1;
                        flag = 0;
                    } else {
                        flag += 1;
                    }
                    i_Msg->m1100 = 0;
                    for (s32 j = 0; j < mBeatNum[melody_no]; j++) {
                        i_Msg->m0B64[j].mUserArea = 0;
                        if (dComIfGp_getMelodyNum() < 5) {
                            fopMsgM_setNowAlpha(&i_Msg->m0A14[j], 0.5f);
                            fopMsgM_setNowAlphaZero(&i_Msg->m0B64[j]);
                        } else {
                            fopMsgM_setNowAlpha(&i_Msg->m0A14[j], 0.5f);
                            fopMsgM_setNowAlpha(&i_Msg->m08C4[j], 0.5f);
                            fopMsgM_setNowAlpha(&i_Msg->m0CB4[j], 0.5f);
                        }
                    }
                }
            }
        }
    } else {
        dVar9 = fopMsgM_valueIncrease(5, i_Msg->m116B, 0);
        fopMsgM_setNowAlpha(&i_Msg->m0544[0], dVar9);
        fopMsgM_setNowAlpha(&i_Msg->m0544[1], dVar9);
        fopMsgM_setNowAlpha(&i_Msg->m0544[2], dVar9);
        fopMsgM_setNowAlpha(&i_Msg->m0544[3], dVar9);
        if (i_Msg->m116B >= 5) {
            i_Msg->mStatus = fopMsgStts_INPUT_e;
        } else {
            i_Msg->m116B++;
        }
    }
    return TRUE;
}

/* 80212DC0-80213650       .text dMsg_continueProc__FP13sub_msg_class */
s32 dMsg_continueProc(sub_msg_class* i_Msg) {
    int iVar1;
    int iVar2;
    f32 dVar3;
    f32 fVar5;
    char* pcVar9;
    char* pcVar10;
    char* pcVar12;
    fopAc_ac_c* pActor;
    char* pcVar13;

    iVar1 = (int)((J2DTextBox*)i_Msg->m0544[0].pane)->getCharSpace();
    iVar2 = (int)((J2DTextBox*)i_Msg->m0544[1].pane)->getCharSpace();
    if (((((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) || (i_Msg->mMsgDataProc.field_0x294 != 0)) ||
         (fopMsgM_checkMessageSend() || (i_Msg->mMsgNo == 0x5ac && (dComIfGp_checkMesgCancelButton())))) &&
        (!dComIfGp_checkMesgBgm()))
    {
        i_Msg->mMsgDataProc.field_0x294 = 0;
        i_Msg->m1100 = 0;
        JKRFileLoader::removeResource(i_Msg->head_p, NULL);
        if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
            dMsg_arrowInit(i_Msg);
        }
        if (CPad_CHECK_TRIG_B(0)) {
            i_Msg->m1169 = 1;
            dComIfGp_setMesgCancelButton(1);
        }
        if (i_Msg->m1169 != 0) {
            i_Msg->mMsgNo = i_Msg->field_0xf0;
            i_Msg->m1169 = 0;
        }
        i_Msg->head_p = i_Msg->mMsgGet.getMesgHeader(i_Msg->mMsgNo);
        JUT_ASSERT(4002, i_Msg->head_p);
        pcVar9 = (char*)i_Msg->mMsgGet.getMessage(i_Msg->head_p);
        i_Msg->mpMesgStr = (char*)pcVar9;
        i_Msg->mMesgEntry = i_Msg->mMsgGet.getMesgEntry(i_Msg->head_p);
        i_Msg->mMsgID = i_Msg->mMsgGet.mGroupID << 8 | i_Msg->mMsgGet.mResMsgNo;
        i_Msg->m116A = 0;
        i_Msg->m1164 = -1;
        dMsg_value_init(i_Msg);
        i_Msg->mMsgDataProc.dataInit();
        i_Msg->mMsgDataProc.field_0x25C = i_Msg->m1164;
        i_Msg->mMsgDataProc.field_0x3C = (char*)i_Msg->mpMesgStr;
        pcVar13 = i_Msg->output_rubSdw;
        pcVar12 = i_Msg->output_textSdw;
        pcVar10 = i_Msg->output_rub;
        pcVar9 = i_Msg->output_text;
        i_Msg->mMsgDataProc.field_0x60 = pcVar9;
        i_Msg->mMsgDataProc.field_0x40 = pcVar9;
        i_Msg->mMsgDataProc.field_0x64 = pcVar10;
        i_Msg->mMsgDataProc.field_0x44 = pcVar10;
        i_Msg->mMsgDataProc.field_0x68 = pcVar12;
        i_Msg->mMsgDataProc.field_0x48 = pcVar12;
        i_Msg->mMsgDataProc.field_0x6C = pcVar13;
        i_Msg->mMsgDataProc.field_0x4C = pcVar13;
        pcVar10 = i_Msg->select_rubSdw;
        pcVar12 = i_Msg->select_textSdw;
        pcVar9 = i_Msg->select_rub;
        i_Msg->mMsgDataProc.field_0x50[0] = i_Msg->select_text;
        i_Msg->mMsgDataProc.field_0x50[1] = pcVar9;
        i_Msg->mMsgDataProc.field_0x50[2] = pcVar12;
        i_Msg->mMsgDataProc.field_0x50[3] = pcVar10;
        i_Msg->mMsgDataProc.font[0] = textFont;
        i_Msg->mMsgDataProc.font[1] = rubyFont;
        i_Msg->mMsgDataProc.field_0x11C = iVar1;
        i_Msg->mMsgDataProc.field_0x124 = iVar2;
        i_Msg->mMsgDataProc.field_0x0C = &i_Msg->mMesgEntry;
        i_Msg->mMsgDataProc.field_0x144 = i_Msg->m110C;
        i_Msg->mMsgDataProc.field_0x14C = i_Msg->m1110;
        if ((i_Msg->mMesgEntry.mTextboxType == 9) && (i_Msg->m0624[8].mUserArea == 0)) {
            i_Msg->mMsgDataProc.field_0x128 = 0x1a3;
            i_Msg->mMsgDataProc.field_0x12C = 0x192;
        } else {
            i_Msg->mMsgDataProc.field_0x128 = 0x1f7;
            i_Msg->mMsgDataProc.field_0x12C = 0x1e6;
        }
        i_Msg->mMsgDataProc.field_0x160 = g_msgHIO.field_0x82;
        i_Msg->mMsgDataProc.field_0x15C = 2;
        if (g_msgHIO.field_0x83 != 0) {
            i_Msg->mMsgDataProc.field_0x29C = 1;
        } else {
            i_Msg->mMsgDataProc.field_0x29C = 0;
        }
        dMsg_yose_select(i_Msg);
        if (i_Msg->mMesgEntry.mInitialSound != 0) {
            mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
        }
        dMsg_setString(i_Msg);
        dMeter_Info.field_0x0[0] = 2;
        if (dComIfGp_getDoStatusForce() == dActStts_CANCEL_e) {
            mDoAud_seStart(JA_SE_TALK_SEL_CANCEL);
        } else {
            mDoAud_seStart(JA_SE_TALK_NEXT);
        }
        i_Msg->m116A++;
        dComIfGp_setMesgSendButton(i_Msg->m116A);
        dComIfGp_setMesgCancelButton(0);
        dComIfGp_setMesgAnimeAttrInfo(i_Msg->mMesgEntry.mInitialAnimation);
        u8 temp_r4_2 = i_Msg->mMesgEntry.mInitialCamera;
        dComIfGp_setMesgCameraAttrInfo(i_Msg->mMesgEntry.mInitialCamera);
        dComIfGp_setMessageRupee(i_Msg->mMesgEntry.mItemPrice);
        if ((((i_Msg->mMesgEntry.mInitialCamera == 1) || (i_Msg->mMesgEntry.mInitialCamera == 2)) || (i_Msg->mMesgEntry.mInitialCamera == 3)) ||
            (i_Msg->mMesgEntry.mInitialCamera == 4 || (i_Msg->mMesgEntry.mInitialCamera == 5)))
        {
            dComIfG_MesgCamInfo_c* aMsgCamInfo_p = dComIfGp_getMesgCameraInfo();
            pActor = aMsgCamInfo_p->mActor[temp_r4_2 - 1];
            if (pActor != NULL) {
                dComIfGp_event_setTalkPartner(pActor);
            }
        }
        if (i_Msg->mMesgEntry.mTextboxType == 1) {
            dMsg_msg_pane_parts_set(&i_Msg->m049C, 1);
            if (i_Msg->mMesgEntry.mTextboxPosition != 1) {
                f32 tmp = 225.0f;
                i_Msg->m049C.mPosCenter.y += tmp;
                i_Msg->m049C.mPosTopLeft.y += tmp;
            }
            dMsg_arw_pane_parts_set(&i_Msg->mPane_Arrow, &i_Msg->m049C);
            dMsg_arw_pane_parts_set(&i_Msg->m050C, &i_Msg->m049C);
            i_Msg->m1114 = i_Msg->mPane_Arrow.mPosTopLeft.y + i_Msg->mPane_Arrow.mSizeOrig.y;
            cXyz tmp;
            dVar3 = (int)i_Msg->m0544[0].mPosTopLeftOrig.x;
            tmp.x = dVar3;
            fVar5 = ((int)(480.0f - (i_Msg->m0544[0].mPosTopLeftOrig.y + i_Msg->m0544[0].mSizeOrig.y)) - 0x13);
            tmp.y = fVar5;
            if (i_Msg->mMesgEntry.mTextboxPosition != 1) {
                i_Msg->m10F8 = (int)tmp.x;
                i_Msg->m10FC = (int)(tmp.y + 225.0f);
            } else {
                i_Msg->m10F8 = (int)tmp.x;
                i_Msg->m10FC = (int)(tmp.y);
            }
            i_Msg->m0544[0].pane->move(tmp.x, tmp.y - (f32)g_msgHIO.field_0x62 - (f32)textOffsetY);
            i_Msg->m0544[1].pane->move(tmp.x, tmp.y - (f32)g_msgHIO.field_0x60 - (f32)textOffsetY);
            i_Msg->m0544[2].pane->move(tmp.x + 2.0f, (tmp.y - (f32)g_msgHIO.field_0x62 - (f32)textOffsetY) + 2.0f);
            i_Msg->m0544[3].pane->move(tmp.x + 2.0f, (tmp.y - (f32)g_msgHIO.field_0x60 - (f32)textOffsetY) + 2.0f);
            i_Msg->m10D8 = i_Msg->m049C.mPosCenter.x;
            i_Msg->m10DC = i_Msg->m049C.mPosCenter.y;
            fopMsgM_cposMove(&i_Msg->m049C);
        } else if (i_Msg->mMesgEntry.mTextboxType != 0xe) {
            dMsg_mesgOutPos(i_Msg);
            i_Msg->m10D8 = (int)i_Msg->m049C.mPosCenter.x;
            i_Msg->m10DC = (int)i_Msg->m049C.mPosCenter.y;
        }
        if (((i_Msg->mMesgEntry.mDrawType == 0) && (CPad_CHECK_TRIG_B(0))) && (!dComIfGp_checkMesgBgm())) {
            if (i_Msg->mMsgDataProc.field_0x296 == 0) {
                i_Msg->mMsgDataProc.field_0x299 = 1;
            }
            if (((i_Msg->mMsgDataProc.field_0x297 == 0) && (i_Msg->mMsgDataProc.field_0x298 == 0)) && ((s32)i_Msg->mMsgDataProc.field_0x158 != 0)) {
                i_Msg->mMsgDataProc.field_0x158 = 0;
                i_Msg->mMsgDataProc.field_0x296 = 0;
            }
        }
        i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
    } else {
        if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
            dMsg_arrowMove(i_Msg);
        }
        dMeter_Info.field_0x0[0] = 1;
    }
    return TRUE;
}

/* 80213650-80213830       .text dMsg_closewaitProc__FP13sub_msg_class */
s32 dMsg_closewaitProc(sub_msg_class* i_Msg) {
    u8 bVar1;
    u32 uVar3;

    if (i_Msg->mMsgDataProc.field_0x297 != 0) {
        uVar3 = (int)i_Msg->mMsgDataProc.field_0x158 > 0 ? i_Msg->mMsgDataProc.field_0x158 - 1 : 0;
        i_Msg->mMsgDataProc.field_0x158 = uVar3;
        if ((uVar3 == 0) || (fopMsgM_checkMessageSend())) {
            i_Msg->mMsgDataProc.field_0x297 = 0;
            i_Msg->mMsgDataProc.field_0x296 = 0;
            i_Msg->mStatus = fopMsgStts_BOX_CLOSING_e;
            i_Msg->m1100 = 0;
            i_Msg->mMsgDataProc.field_0x158 = 0;
            i_Msg->m116A++;
            dComIfGp_setMesgSendButton(i_Msg->m116A);
        }
    } else {
        if (i_Msg->mMsgDataProc.field_0x298 != 0) {
            uVar3 = (int)i_Msg->mMsgDataProc.field_0x158 > 0 ? i_Msg->mMsgDataProc.field_0x158 - 1 : 0;
            i_Msg->mMsgDataProc.field_0x158 = uVar3;
            if (uVar3 != 0) {
                if ((((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) || (fopMsgM_checkMessageSend())) && (!dComIfGp_checkMesgBgm())) {
                    i_Msg->mMsgDataProc.field_0x298 = 0;
                    i_Msg->mStatus = fopMsgStts_BOX_CLOSING_e;
                    bVar1 = i_Msg->mMesgEntry.mTextboxType;
                    if ((bVar1 != 5) && (bVar1 != 0xe)) {
                        fopMsgM_setNowAlphaZero(&i_Msg->m050C);
                    }
                    i_Msg->m1100 = 0;
                    dMeter_Info.field_0x0[0] = 0;
                    i_Msg->m116A++;
                    dComIfGp_setMesgSendButton(i_Msg->m116A);
                } else {
                    bVar1 = i_Msg->mMesgEntry.mTextboxType;
                    if ((bVar1 != 5) && (bVar1 != 0xe)) {
                        dMsg_dotMove(i_Msg);
                    }
                    dMeter_Info.field_0x0[0] = 4;
                }
            } else {
                i_Msg->mMsgDataProc.field_0x298 = 0;
                i_Msg->mStatus = fopMsgStts_BOX_CLOSING_e;
                bVar1 = i_Msg->mMesgEntry.mTextboxType;
                if ((bVar1 != 5) && (bVar1 != 0xe)) {
                    fopMsgM_setNowAlphaZero(&i_Msg->m050C);
                }
                i_Msg->m1100 = 0;
                dMeter_Info.field_0x0[0] = 0;
                i_Msg->m116A++;
                dComIfGp_setMesgSendButton(i_Msg->m116A);
            }
        }
    }
    return TRUE;
}

/* 80213830-80213960       .text dMsg_finishProc__FP13sub_msg_class */
s32 dMsg_finishProc(sub_msg_class* i_Msg) {
    if ((((((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) || (i_Msg->mMsgDataProc.field_0x294 != 0)) || (fopMsgM_checkMessageSend())) ||
         (i_Msg->mMsgNo == 0x5ac && (dComIfGp_checkMesgCancelButton()))) &&
        (!dComIfGp_checkMesgBgm()))
    {
        i_Msg->mMsgDataProc.field_0x294 = 0;
        i_Msg->mStatus = fopMsgStts_BOX_CLOSING_e;
        if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
            fopMsgM_setNowAlphaZero(&i_Msg->m050C);
        }
        i_Msg->m1100 = 0;
        dMeter_Info.field_0x0[0] = 0;
        i_Msg->m116A++;
        dComIfGp_setMesgSendButton(i_Msg->m116A);
        if (i_Msg->mMsgNo == 0x1072) {
            mDoAud_bgmStop(0x3c);
        }
    } else {
        if ((i_Msg->mMesgEntry.mTextboxType != 5) && (i_Msg->mMesgEntry.mTextboxType != 0xe)) {
            dMsg_dotMove(i_Msg);
        }
        dMeter_Info.field_0x0[0] = 4;
    }
    return TRUE;
}

/* 80213960-802139F0       .text dMsg_openTalkProc__FP13sub_msg_class */
s32 dMsg_openTalkProc(sub_msg_class* i_Msg) {
    if (i_Msg->m1100 == 0xd) {
        i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
        dMsg_messagePaneShow(i_Msg);
        dMsg_yose_select(i_Msg);
        if (i_Msg->mMesgEntry.mInitialSound != 0) {
            mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
        }
        dMsg_setString(i_Msg);
        dMeter_Info.field_0x0[0] = 2;
    } else {
        dMsg_frame_openTalk(i_Msg);
    }
    return TRUE;
}

/* 802139F0-80213C20       .text dMsg_openItemProc__FP13sub_msg_class */
s32 dMsg_openItemProc(sub_msg_class* i_Msg) {
    cXyz local_1c;
    cXyz local_28;

    if (i_Msg->m1100 == 8) {
        i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
        dMsg_messagePaneShow(i_Msg);
        dMsg_yose_select(i_Msg);
        if (i_Msg->mMesgEntry.mInitialSound != 0) {
            mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
        }
        dMsg_setString(i_Msg);
        if ((i_Msg->mMsgNo == 0x74) || (i_Msg->mMsgNo == 0xbe)) {
            f32 tmp = 0.5f;
            f32 y = (i_Msg->m0624[8].mSize.y * tmp + i_Msg->m0624[8].pane->getGlbBounds().i.y) - 240.0f;
            f32 x = (i_Msg->m0624[8].mSize.x * tmp + i_Msg->m0624[8].pane->getGlbBounds().i.x) - 320.0f;
            local_1c.set(x, y, 0.0f);
            i_Msg->m10B4[0] = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_002D, &local_1c);
            if (i_Msg->mMsgNo == 0xbe) {
                i_Msg->m10B4[1] = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_002D, &local_1c);
            }
        } else if (i_Msg->mMsgNo == 0x9a) {
            f32 tmp = 0.5f;
            f32 y = ((i_Msg->m0624[8].mSize.y * tmp + i_Msg->m0624[8].pane->getGlbBounds().i.y) - 240.0f) - 10.0f;
            f32 x = ((i_Msg->m0624[8].mSize.x * tmp + i_Msg->m0624[8].pane->getGlbBounds().i.x) - 320.0f) + 10.0f;
            local_28.set(x, y, 0.0f);
            i_Msg->m10B4[0] = dComIfGp_particle_set2Dfore(dPa_name::ID_COMMON_02E1, &local_28);
        }
        dMeter_Info.field_0x0[0] = 2;
    } else {
        dMsg_frame_openItem(i_Msg);
    }
    return TRUE;
}

/* 80213C20-80213E28       .text dMsg_openTactProc__FP13sub_msg_class */
s32 dMsg_openTactProc(sub_msg_class* i_Msg) {
    u8 uVar2;
    u8 cVar4;
    u32 iVar3;

    if (i_Msg->mMsgNo == 0x5ac) {
        i_Msg->mStatus = fopMsgStts_INPUT_e;
    } else if ((i_Msg->mMsgNo == 0x5b3) || (i_Msg->mMsgNo == 0x5b4)) {
        uVar2 = dComIfGp_getMelodyNum();
        if (((s32)uVar2 != 1) && ((s32)uVar2 != 5)) {
            dMsg_tactGuideShow(i_Msg, mBeatNum[uVar2]);
            i_Msg->mStatus = fopMsgStts_DEMO_e;
            i_Msg->m116B = 0;
        } else {
            dMsg_tactGuideShow(i_Msg, mBeatNum[uVar2]);
            dMsg_messageShow(i_Msg);
            i_Msg->mStatus = fopMsgStts_INPUT_e;
            i_Msg->m1168 = mDoAud_tact_getBeat();
            return TRUE;
        }
    } else {
        i_Msg->mStatus = fopMsgStts_TACT_e;
    }
    fopMsgM_paneScaleXY(&i_Msg->m049C, 1.0f);
    fopMsgM_setInitAlpha(&i_Msg->m049C);
    if (i_Msg->mStatus != fopMsgStts_DEMO_e) {
        dMsg_messagePaneShow(i_Msg);
        dMsg_yose_select(i_Msg);
        if (i_Msg->mMesgEntry.mInitialSound != 0) {
            mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
        }
        i_Msg->mMsgDataProc.field_0x299 = 1;
        i_Msg->mMsgDataProc.stringSet();
        for (s32 i = 0; i < 8; i++) {
            cVar4 = i_Msg->mMsgDataProc.field_0x281[i];
            iVar3 = i_Msg->mMsgDataProc.field_0x220[i];
            u32 var_r6 = iVar3;
            if (((((u8)(cVar4 - 10U) <= 3) || (cVar4 == 0x15)) || (cVar4 == 0x17)) && (iVar3 == 0)) {
                var_r6 = -1;
            }
            if (((cVar4 != 0xFF) && (buttonTimer[i] == -1)) && (cVar4 != 0x14 && (cVar4 != 0x15 && (cVar4 != 0x16)))) {
                fopMsgM_outFontSet(button_icon[i], button_kage[i], &buttonTimer[i], var_r6, cVar4);
            }
        }
        dMsg_setString(i_Msg);
    }
    i_Msg->m1100 = 0;
    return TRUE;
}

/* 80213E28-80213E9C       .text dMsg_openDemoProc__FP13sub_msg_class */
s32 dMsg_openDemoProc(sub_msg_class* i_Msg) {
    i_Msg->mStatus = fopMsgStts_MSG_TYPING_e;
    dMsg_yose_select(i_Msg);
    if (i_Msg->mMesgEntry.mInitialSound != 0) {
        mDoAud_messageSePlay(i_Msg->mMesgEntry.mInitialSound, NULL, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
    }
    dMsg_setString(i_Msg);
    dMsg_messagePaneShow(i_Msg);
    return TRUE;
}

/* 80213E9C-80213EC0       .text dMsg_closeProc__FP13sub_msg_class */
s32 dMsg_closeProc(sub_msg_class* i_Msg) {
    dMsg_frame_close(i_Msg);
    return TRUE;
}

/* 80213EC0-80213F00       .text dMsg_closeProc2__FP13sub_msg_class */
s32 dMsg_closeProc2(sub_msg_class* i_Msg) {
    i_Msg->mStatus = fopMsgStts_BOX_CLOSED_e;
    dMsg_messagePaneHide(i_Msg);
    dMsg_outFontHide(i_Msg);
    return TRUE;
}

/* 80213F00-802140CC       .text dMsg_initProc__FP13sub_msg_class */
s32 dMsg_initProc(sub_msg_class* i_Msg) {
    const char* pcVar3;
    char acStack_28[24];

    if ((dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4) != 0) || (fopMsgM_demoMsgFlagCheck())) {
        pcVar3 = i_Msg->mpMesgStr;
        if (((u8)pcVar3[0] == 0x1A) && ((u8)pcVar3[2] == 0x02)) {
            dComIfGp_setMesgCameraTagInfo((s32)(u16)((((u8)pcVar3[3] << 8) & ~0xFFFF00FF) | (((u8)pcVar3[4]) & ~0xFF00)));
            i_Msg->mpMesgStr = (char*)pcVar3 + pcVar3[1];
            i_Msg->mMesgCameraTagInfo = dComIfGp_getMesgCameraTagInfo();
        } else if (((((u8)pcVar3[0] == 0x1A) && ((u8)pcVar3[2] == 0xFF)) && ((u8)pcVar3[3] == 0x00)) && ((u8)pcVar3[4] == 0x00)) {
            if ((pcVar3[5] >= 0x00) && (pcVar3[5] <= 0x08)) {
                i_Msg->m1164 = fopMsgM_getColorTable(pcVar3[5]);
                // clang-format off
                sprintf(acStack_28,"\x1b" "CC[%08x]" "\x1b" "GM[0]", i_Msg->m1164);
                // clang-format on
                strcat(i_Msg->output_text, acStack_28);
            }
            i_Msg->mpMesgStr = i_Msg->mpMesgStr + (s8)i_Msg->mpMesgStr[1];
        } else {
            switch (i_Msg->mMesgEntry.mTextboxType) {
            case 5:
                dMsg_ScreenDataValueInitDemo(i_Msg);
                break;
            case 1:
            case 9:
                dMsg_ScreenDataValueInitItem(i_Msg);
                break;
            case 0xe:
                dMsg_ScreenDataValueInitTact(i_Msg);
                break;
            default:
                dMsg_ScreenDataValueInitTalk(i_Msg);
                break;
            }
            i_Msg->mStatus = fopMsgStts_BOX_OPENING_e;
            mDoAud_talkIn();
            mDoAud_seStart(JA_SE_TALK_WIN_OPEN);
        }
    }
    return TRUE;
}

/* 802140CC-8021411C       .text dMsg_tactProc__FP13sub_msg_class */
s32 dMsg_tactProc(sub_msg_class* i_Msg) {
    if (fopMsgM_checkMessageSend()) {
        i_Msg->mMsgDataProc.field_0x297 = 1;
        i_Msg->mMsgDataProc.field_0x158 = 0x1e;
        i_Msg->mStatus = fopMsgStts_CLOSE_WAIT_e;
    }
    return TRUE;
}

/* 8021411C-802143A8       .text dMsg_outnowProc__FP13sub_msg_class */
s32 dMsg_outnowProc(sub_msg_class* i_Msg) {
    u16 uVar2;
    u8 cVar4;
    u32 iVar3;

    if (i_Msg->mMesgCameraTagInfo != dComIfGp_getMesgCameraTagInfo()) {
        if ((dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4) != 0) || (fopMsgM_demoMsgFlagCheck())) {
            dMsg_mesgOutPos(i_Msg);
            i_Msg->m10D8 = (int)i_Msg->m049C.mPosCenter.x;
            i_Msg->m10DC = (int)i_Msg->m049C.mPosCenter.y;
            fopMsgM_setInitAlpha(&i_Msg->m049C);
            i_Msg->mMesgCameraTagInfo = dComIfGp_getMesgCameraTagInfo();
        }
    }
    if (i_Msg->mMesgEntry.mDrawType == 0) {
        if (((CPad_CHECK_TRIG_A(0)) || (CPad_CHECK_TRIG_B(0))) && (!dComIfGp_checkMesgBgm())) {
            i_Msg->mMsgDataProc.field_0x299 = 1;
            if ((i_Msg->mMsgDataProc.field_0x297 == 0 && (i_Msg->mMsgDataProc.field_0x298 == 0)) && ((s32)i_Msg->mMsgDataProc.field_0x158 != 0)) {
                i_Msg->mMsgDataProc.field_0x158 = 0;
                i_Msg->mMsgDataProc.field_0x296 = 0;
            }
        }
    } else if ((i_Msg->mMesgEntry.mDrawType == 1) && (i_Msg->mMsgDataProc.field_0x296 == 0)) {
        i_Msg->mMsgDataProc.field_0x299 = 1;
    }
    if (((i_Msg->mMsgDataProc.field_0x297 == 0) && (i_Msg->mMsgDataProc.field_0x298 == 0)) && ((int)i_Msg->mMsgDataProc.field_0x158 != 0)) {
        i_Msg->mMsgDataProc.field_0x158 = (int)i_Msg->mMsgDataProc.field_0x158 > 0 ? i_Msg->mMsgDataProc.field_0x158 - 1 : 0;
    } else {
        i_Msg->mMsgDataProc.stringSet();
        i_Msg->m1164 = i_Msg->mMsgDataProc.field_0x25C;
        i_Msg->mStatus = (u16)i_Msg->mMsgDataProc.field_0x27C;
        for (s32 i = 0; i < 8; i++) {
            cVar4 = i_Msg->mMsgDataProc.field_0x281[i];
            iVar3 = i_Msg->mMsgDataProc.field_0x220[i];
            u32 var_r6 = iVar3;
            if (((((u8)(cVar4 - 10U) <= 3) || (cVar4 == 0x15)) || (cVar4 == 0x15)) && (iVar3 == 0)) {
                var_r6 = -1;
            }
            if (((cVar4 != 0xFF) && (buttonTimer[i] == -1)) && (cVar4 != 0x14 && (cVar4 != 0x15 && (cVar4 != 0x16)))) {
                fopMsgM_outFontSet(button_icon[i], button_kage[i], &buttonTimer[i], var_r6, cVar4);
            }
        }
        uVar2 = i_Msg->mStatus;
        if (uVar2 == 7) {
            i_Msg->m1100 = 0;
        } else if ((uVar2 == 10) && (i_Msg->mMsgDataProc.field_0x297 == 0)) {
            i_Msg->m1100 = 0;
        }
    }
    dMsg_setString(i_Msg);
    return TRUE;
}

/* 802143A8-80214560       .text dMsg_Draw__FP13sub_msg_class */
static BOOL dMsg_Draw(sub_msg_class* i_Msg) {
    if ((i_Msg->mMesgEntry.mTextboxType != 5) && (fopMsgM_setAlpha(&i_Msg->m049C), i_Msg->mMesgEntry.mTextboxType != 0xe)) {
        fopMsgM_setAlpha(&i_Msg->mPane_Arrow);
        fopMsgM_setAlpha(&i_Msg->m050C);
    }
    fopMsgM_setAlpha(&i_Msg->m0544[0]);
    fopMsgM_setAlpha(&i_Msg->m0544[1]);
    fopMsgM_setAlpha(&i_Msg->m0544[2]);
    fopMsgM_setAlpha(&i_Msg->m0544[3]);
    if ((i_Msg->mMesgEntry.mTextboxType == 9) || (i_Msg->mMesgEntry.mTextboxType == 1)) {
        for (s32 i = 0; i < 10; i++) {
            fopMsgM_setAlpha(&i_Msg->m0624[i]);
        }
    } else if (i_Msg->mMesgEntry.mTextboxType == 0xe) {
        if ((i_Msg->mMsgNo == 0x5b3) || (i_Msg->mMsgNo == 0x5b4)) {
            for (s32 i = 0; i < mBeatNum[dComIfGp_getMelodyNum()]; i++) {
                fopMsgM_setAlpha(&i_Msg->m08C4[i]);
                fopMsgM_setAlpha(&i_Msg->m0A14[i]);
                fopMsgM_setAlpha(&i_Msg->m0B64[i]);
                if (dComIfGp_getMelodyNum() >= 5) {
                    fopMsgM_setAlpha(&i_Msg->m0CB4[i]);
                }
            }
        }
    } else if (i_Msg->mMesgEntry.mTextboxType != 5) {
        for (s32 i = 0; i < 10; i++) {
            fopMsgM_setAlpha(&i_Msg->m026C[i]);
        }
        fopMsgM_setAlpha(&i_Msg->m01FC);
        fopMsgM_setAlpha(&i_Msg->m0234);
        fopMsgM_setAlpha(&i_Msg->m011C[0]);
        fopMsgM_setAlpha(&i_Msg->m011C[1]);
        fopMsgM_setAlpha(&i_Msg->m011C[2]);
        fopMsgM_setAlpha(&i_Msg->m011C[3]);
    }
    dComIfGd_set2DOpa(&message);
    return TRUE;
}

/* 80214560-802153B0       .text dMsg_Execute__FP13sub_msg_class */
static BOOL dMsg_Execute(sub_msg_class* i_Msg) {
    u8 bVar1;
    s32 fVar2;
    s32 fVar3;
    s32 fVar4;
    GXColor GVar7;
    JKRHeap* pJVar8;
    MyScreen* pJVar12;
    f32 dVar15;

    pJVar8 = mDoExt_setCurrentHeap(i_Msg->mpHeap);
    if (dComIfGp_checkMesgSendButton()) {
        dComIfGp_setMesgSendButton(0);
    }
    if ((dComIfGp_checkMesgBgm()) && (i_Msg->mMesgEntry.mTextboxType != 9 ||
                                      ((((mDoAud_checkPlayingSubBgmFlag() != JA_BGM_ITEM_GET && (mDoAud_checkPlayingSubBgmFlag() != JA_BGM_ITEM_GET_S)) &&
                                         (mDoAud_checkPlayingSubBgmFlag() != JA_BGM_GET_HEART)) &&
                                        (mDoAud_checkPlayingSubBgmFlag() != JA_BGM_GET_SONG && (mDoAud_checkPlayingSubBgmFlag() != JA_BGM_MASTER_SWORD))) &&
                                       (mDoAud_checkPlayingSubBgmFlag() != JA_BGM_GET_PEARL))))
    {
        dComIfGp_setMesgBgmOff();
    }
    if ((i_Msg->m026C[0].mUserArea == 3) || ((i_Msg->mStatus != 8 && (i_Msg->mStatus != 9)) && (i_Msg->m026C[0].mUserArea != 0))) {
        if ((int)i_Msg->m026C[9].mUserArea < (int)g_msgHIO.field_0x48 + (int)g_msgHIO.field_0x76) {
            dMsg_subTextClose(i_Msg);
        } else {
            i_Msg->m026C[9].mUserArea = 0;
            i_Msg->m026C[0].mUserArea = 0;
        }
    }
    if (i_Msg->mStatus == fopMsgStts_MSG_PREPARING_e) {
        dMsg_initProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_MSG_TYPING_e) {
        dMsg_outnowProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_STOP_e) {
        dMsg_stopProc(i_Msg);
    } else if (((i_Msg->mStatus == fopMsgStts_SELECT_2_e) || (i_Msg->mStatus == fopMsgStts_SELECT_3_e)) || (i_Msg->mStatus == fopMsgStts_SELECT_YOKO_e)) {
        dMsg_selectProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_INPUT_e) {
        dMsg_inputProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_DEMO_e) {
        dMsg_demoProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_CLOSE_WAIT_e) {
        dMsg_closewaitProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_BOX_OPENING_e) {
        switch (i_Msg->mMesgEntry.mTextboxType) {
        case 5:
            dMsg_openDemoProc(i_Msg);
            break;
        case 1:
        case 9:
            dMsg_openItemProc(i_Msg);
            break;
        case 0xe:
            dMsg_openTactProc(i_Msg);
            break;
        default:
            dMsg_openTalkProc(i_Msg);
            break;
        }
    } else if (i_Msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
        dMsg_continueProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_MSG_ENDS_e) {
        dMsg_finishProc(i_Msg);
    } else if (i_Msg->mStatus == fopMsgStts_BOX_CLOSING_e) {
        if (i_Msg->mMesgEntry.mTextboxType == 5) {
            dMsg_closeProc2(i_Msg);
        } else {
            dMsg_closeProc(i_Msg);
        }
    } else if (i_Msg->mStatus == fopMsgStts_MSG_DESTROYED_e) {
        fopMsgM_Delete(i_Msg);
        dComIfGp_clearMesgAnimeTagInfo();
        dComIfGp_clearMesgCameraTagInfo();
        dComIfGp_setMesgAnimeAttrInfo(0);
        dComIfGp_setMesgCameraAttrInfo(0);
    } else if (i_Msg->mStatus == fopMsgStts_TACT_e) {
        dMsg_tactProc(i_Msg);
    }
    bVar1 = i_Msg->mMesgEntry.mTextboxType;
    if ((bVar1 == 9) || (bVar1 == 1)) {
        if (i_Msg->m0624[8].mNowAlpha == i_Msg->m0624[8].mInitAlpha) {
            dMsg_ringMove(i_Msg);
            dMsg_lightMove(i_Msg);
            dMsg_cornerMove(i_Msg);
        }
        for (s32 i = 0; i < 2; i++) {
            if (i_Msg->m10B4[i] != NULL) {
                i_Msg->m10B4[i]->playDrawParticle();
                i_Msg->m10B4[i]->setGlobalAlpha(i_Msg->m0624[8].mNowAlpha);
            }
        }
    } else if (bVar1 == 0xe) {
        dMsg_cornerMove(i_Msg);
    }
    dMsg_rubySet(i_Msg);
    f32 fvar2_2;
    if (dComIfGs_getOptRuby()) {
        fvar2_2 = -4.0f;
    } else {
        fvar2_2 = 0.0f;
    }
    dVar15 = fvar2_2;
    fopMsgM_messageSendOff();
    GVar7 = g_msgHIO.field_0x5;
    bVar1 = i_Msg->mMesgEntry.mTextboxType;
    if (bVar1 == 5) {
        static s32 posY0 = (i_Msg->m0544[0].pane)->mBounds.i.y;
        static s32 posY1 = (i_Msg->m0544[1].pane)->mBounds.i.y;
        static s32 posY2 = (i_Msg->m0544[2].pane)->mBounds.i.y;
        static s32 posY3 = (i_Msg->m0544[3].pane)->mBounds.i.y;
        pJVar12 = (MyScreen*)i_Msg->m0544[0].pane;
        s32 fVar1 = pJVar12->mBounds.i.x;
        fVar2 = i_Msg->m0544[1].pane->mBounds.i.x;
        fVar3 = i_Msg->m0544[2].pane->mBounds.i.x;
        fVar4 = i_Msg->m0544[3].pane->mBounds.i.x;
        pJVar12->move(fVar1, posY0);
        i_Msg->m0544[1].pane->move(fVar2, posY1);
        i_Msg->m0544[2].pane->move(fVar3, posY2);
        i_Msg->m0544[3].pane->move(fVar4, posY3);
    } else if ((bVar1 == 9) || (bVar1 == 1)) {
        i_Msg->m049C.pane->move(i_Msg->m049C.mPosTopLeft.x, (i_Msg->m049C.mPosTopLeft.y + (int)g_msgHIO.field_0x66));
        i_Msg->m050C.pane->move(i_Msg->m050C.mPosTopLeft.x, (i_Msg->m050C.mPosTopLeft.y + g_msgHIO.field_0x66));
        i_Msg->m0544[0].pane->move(i_Msg->m10F8, (g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x62) - (int)textOffsetY))));
        i_Msg->m0544[1].pane->move(i_Msg->m10F8, (g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x60) - (int)textOffsetY))));
        i_Msg->m0544[2].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (((i_Msg->m10FC - (int)g_msgHIO.field_0x62) + 2) - (int)textOffsetY)))
        );
        i_Msg->m0544[3].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (((i_Msg->m10FC - (int)g_msgHIO.field_0x60) + 2) - (int)textOffsetY)))
        );
    } else if (bVar1 == 0xe) {
        i_Msg->m049C.pane->move(i_Msg->m049C.mPosTopLeft.x, (i_Msg->m049C.mPosTopLeft.y + (int)g_msgHIO.field_0x66));
        i_Msg->m0544[0].pane->move(i_Msg->m10F8, ((int)g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x62) - (int)textOffsetY))));
        i_Msg->m0544[1].pane->move(i_Msg->m10F8, ((int)g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x60) - (int)textOffsetY))));
        i_Msg->m0544[2].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (i_Msg->m10FC - ((int)g_msgHIO.field_0x62) + 2 - (int)textOffsetY)))
        );
        i_Msg->m0544[3].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (((i_Msg->m10FC - (int)g_msgHIO.field_0x60) + 2) - (int)textOffsetY)))
        );
    } else {
        ((J2DPicture*)i_Msg->m049C.pane)->setWhite(JUtility::TColor(g_msgHIO.field_0x5));
        ((J2DPicture*)i_Msg->m049C.pane)->setBlack(JUtility::TColor(g_msgHIO.field_0x9));
        i_Msg->m049C.pane->move(i_Msg->m049C.mPosTopLeft.x, (i_Msg->m049C.mPosTopLeft.y + (int)g_msgHIO.field_0x66));
        i_Msg->m050C.pane->move(i_Msg->m050C.mPosTopLeft.x, (i_Msg->m050C.mPosTopLeft.y + (int)g_msgHIO.field_0x66));
        i_Msg->m0544[0].pane->move(i_Msg->m10F8, ((int)g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x62) - (int)textOffsetY))));
        i_Msg->m0544[1].pane->move(i_Msg->m10F8, ((int)g_msgHIO.field_0x66 + (dVar15 + ((i_Msg->m10FC - (int)g_msgHIO.field_0x60) - (int)textOffsetY))));
        i_Msg->m0544[2].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (((i_Msg->m10FC - (int)g_msgHIO.field_0x62) + 2) - (int)textOffsetY)))
        );
        i_Msg->m0544[3].pane->move(
            i_Msg->m10F8 + 2, ((int)g_msgHIO.field_0x66 + (dVar15 + (((i_Msg->m10FC - (int)g_msgHIO.field_0x60) + 2) - (int)textOffsetY)))
        );
    }
    dComIfGp_setMesgStatus(i_Msg->mStatus);
    mDoExt_setCurrentHeap(pJVar8);
    return TRUE;
}

/* 802153B0-802153B8       .text dMsg_IsDelete__FP13sub_msg_class */
static BOOL dMsg_IsDelete(sub_msg_class*) {
    return TRUE;
}

/* 802153B8-80215698       .text dMsg_Delete__FP13sub_msg_class */
static BOOL dMsg_Delete(sub_msg_class* i_Msg) {
    JKRHeap* pJVar1;

    if (fopMsgM_demoMsgFlagCheck()) {
        fopMsgM_demoMsgFlagOff();
    }
    if (fopMsgM_tactMsgFlagCheck()) {
        fopMsgM_tactMsgFlagOff();
    }
    if (fopMsgM_nextMsgFlagCheck()) {
        fopMsgM_nextMsgFlagOff();
    }
    i_Msg->m116A = 0;
    dComIfGp_setMesgSendButton(i_Msg->m116A);
    dComIfGp_setMesgCancelButton(0);
    dComIfGp_setMesgStatus(0);
    if (dComIfGp_checkMesgBgm()) {
        dComIfGp_setMesgBgmOff();
    }
    pJVar1 = mDoExt_setCurrentHeap(i_Msg->mpHeap);
    for (s32 i = 0; i < 2; i++) {
        if (i_Msg->m10B4[i] != NULL) {
            i_Msg->m10B4[i]->becomeInvalidEmitter();
            i_Msg->m10B4[i]->quitImmortalEmitter();
        }
    }
    delete (MyScreen*)sScreen;
    if (sScreen2 != NULL) {
        delete (J2DScreen*)sScreen2;
    }
    if (dMsg_font_flag != 0) {
        mDoExt_removeRubyFont();
    } else {
        mDoExt_removeMesgFont();
    }
    for (s32 i = 0; i < 8; i++) {
        delete (J2DPicture*)button_icon[i];
        delete (J2DPicture*)button_kage[i];
    }
    delete (J2DPicture*)arrowPane;
    delete (J2DPicture*)maskPane;
    for (s32 i = 0; i < 3; i++) {
        delete (J2DTextBox*)numberPane[i];
    }
    i_Msg->mpHeap->free(i_Msg->output_text);
    i_Msg->mpHeap->free(i_Msg->output_rub);
    i_Msg->mpHeap->free(i_Msg->output_textSdw);
    i_Msg->mpHeap->free(i_Msg->output_rubSdw);
    i_Msg->mpHeap->free(i_Msg->select_text);
    i_Msg->mpHeap->free(i_Msg->select_rub);
    i_Msg->mpHeap->free(i_Msg->select_textSdw);
    i_Msg->mpHeap->free(i_Msg->select_rubSdw);
    agb_work_area = 0;
    if (i_Msg->buffer_p != NULL) {
        i_Msg->mpHeap->free(i_Msg->buffer_p);
    }
    dComIfGp_getMsgArchive()->removeResourceAll();
    i_Msg->mpHeap->freeAll();
    dComIfGp_offHeapLockFlag();
    mDoExt_setCurrentHeap(pJVar1);
    return TRUE;
}

/* 80215698-80215CD0       .text dMsg_Create__FP9msg_class */
static cPhs_State dMsg_Create(msg_class* i_this) {
    /* Nonmatching */
    sub_msg_class* i_Msg = (sub_msg_class*)i_this;
    JKRHeap* pJVar2;

    if ((dComIfGp_isHeapLockFlag() != 0) && (dComIfGp_isHeapLockFlag() != 7)) {
        return cPhs_INIT_e;
    }
    i_Msg->mpHeap = dComIfGp_getExpHeap2D();
    dComIfGp_setHeapLockFlag(7);
    pJVar2 = mDoExt_setCurrentHeap(i_Msg->mpHeap);
    if ((i_Msg->mMsgNo >= 0xc6) && (i_Msg->mMsgNo <= 0xcd)) {
        i_Msg->head_p = i_Msg->mMsgGet.getMesgHeader(dComIfGs_getTriforceNum() + 0xC6);
    } else {
        i_Msg->head_p = i_Msg->mMsgGet.getMesgHeader(i_Msg->mMsgNo);
    }
    JUT_ASSERT(5416, i_Msg->head_p);
    i_Msg->mpMesgStr = (char*)i_Msg->mMsgGet.getMessage(i_Msg->head_p);
    i_Msg->mMesgEntry = i_Msg->mMsgGet.getMesgEntry(i_Msg->head_p);
    i_Msg->mMsgID = i_Msg->mMsgGet.mGroupID << 8 | i_Msg->mMsgGet.mResMsgNo;
    i_Msg->mMesgCameraTagInfo = dComIfGp_getMesgCameraTagInfo();
    dMsg_screenDataSet(i_Msg);
    for (s32 i = 0; i < 8; i++) {
        button_icon[i] = new J2DPicture("font_07_02.bti");
        button_kage[i] = new J2DPicture("font_07_02.bti");
        fopMsgM_blendInit(button_icon[i], "font_00.bti");
        fopMsgM_blendInit(button_kage[i], "font_00.bti");
        button_icon[i]->hide();
        button_kage[i]->hide();
        button_icon[i]->setAlpha(0);
        button_kage[i]->setAlpha(0);
        buttonTimer[i] = -1;
    }
    arrowPane = new J2DPicture("font_10.bti");
    i_Msg->output_text = (char*)i_Msg->mpHeap->alloc(0x385, 4);
    JUT_ASSERT(5444, i_Msg->output_text != NULL);
    i_Msg->output_rub = (char*)i_Msg->mpHeap->alloc(0x385, 4);
    JUT_ASSERT(5447, i_Msg->output_rub != NULL);
    i_Msg->output_textSdw = (char*)i_Msg->mpHeap->alloc(0x385, 4);
    JUT_ASSERT(5450, i_Msg->output_textSdw != NULL);
    i_Msg->output_rubSdw = (char*)i_Msg->mpHeap->alloc(0x385, 4);
    JUT_ASSERT(5453, i_Msg->output_rubSdw != NULL);
    i_Msg->select_text = (char*)i_Msg->mpHeap->alloc(0x65, 4);
    JUT_ASSERT(5456, i_Msg->select_text != NULL);
    i_Msg->select_rub = (char*)i_Msg->mpHeap->alloc(0x65, 4);
    JUT_ASSERT(5459, i_Msg->select_rub != NULL);
    i_Msg->select_textSdw = (char*)i_Msg->mpHeap->alloc(0x65, 4);
    JUT_ASSERT(5462, i_Msg->select_textSdw != NULL);
    i_Msg->select_rubSdw = (char*)i_Msg->mpHeap->alloc(0x65, 4);
    JUT_ASSERT(5465, i_Msg->select_rubSdw != NULL);
    agb_work_area = i_Msg->mpHeap;
    JUT_ASSERT(5468, agb_work_area != NULL);
    i_Msg->mStatus = fopMsgStts_MSG_PREPARING_e;
    i_Msg->m1164 = -1;
    dMsg_value_init(i_Msg);
    dMsg_setString(i_Msg);
    i_Msg->m116A = 0;
    dComIfGp_setMesgSendButton(i_Msg->m116A);
    dComIfGp_setMesgCancelButton(0);
    mDoExt_setCurrentHeap(pJVar2);
    message.field_0x4 = i_Msg;
    dComIfGp_setMesgStatus(i_Msg->mStatus);
    return cPhs_COMPLEATE_e;
}

/* 80215CD0-80215D2C       .text __dt__14dDlst_2Dtact_cFv */
dDlst_2Dtact_c::~dDlst_2Dtact_c() {
}

/* 80215D2C-80215D88       .text __dt__13dDlst_2DMSG_cFv */
dDlst_2DMSG_c::~dDlst_2DMSG_c() {
}

static msg_method_class l_dMsg_Method = {
    (process_method_func)dMsg_Create,
    (process_method_func)dMsg_Delete,
    (process_method_func)dMsg_Execute,
    (process_method_func)dMsg_IsDelete,
    (process_method_func)dMsg_Draw
};

msg_process_profile_definition g_profile_MSG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 12,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MSG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sub_msg_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Priority     */ PRIO_MSG,
    /* Msg SubMtd   */ &l_dMsg_Method,
};
