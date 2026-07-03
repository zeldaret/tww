#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_message.h"
#include "d/d_meter.h"
#include "d/d_kankyo.h"
#include "d/d_s_play.h"
#include "f_op/f_op_msg.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "m_Do/m_Do_controller_pad.h"
#include "stdio.h"

void dMsg2_messageDataInit(sub_msg2_class* i_Msg, int);
void dMsg2_textPosition(sub_msg2_class* i_Msg, u8 i_index);
void dMsg2_yose_select(sub_msg2_class* i_Msg, u8 i_index);
void dMsg2_setCharAlpha(sub_msg2_class* i_Msg, u8 i_index);
u8 dMsg2_aimBrightness();

static int dMsg2_popSpeed;
static J2DScreen* sScreen2[3];
static J2DPicture* bbutton_icon[8][3];
static J2DPicture* bbutton_kage[8][3];
static s16 bbuttonTimer[8][3];
static dDlst_2DMSG2_c message;
static dDlst_2Dm_c board;
static dDlst_2DCopy_c capture;

static u8 dMsg2_tex_i4_color[] = {
    0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x02, 0x02, 0x02, 0x03, 0x04, 0x06, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x12, 0x16, 0x1c, 0x22, 0x2a, 0x32, 0x39,
    0x41, 0x4b, 0x54, 0x5e, 0x67, 0x72, 0x7c, 0x87, 0x8f, 0x98, 0xa2, 0xac, 0xb3, 0xbb, 0xc2, 0xca, 0xd0, 0xd8, 0xdd, 0xe1, 0xe7, 0xea, 0xee, 0xf1,
    0xf3, 0xf5, 0xf7, 0xf9, 0xfb, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd,
    0xfd, 0xfb, 0xfb, 0xf9, 0xf7, 0xf5, 0xf3, 0xf1, 0xee, 0xea, 0xe7, 0xe1, 0xdd, 0xd8, 0xd0, 0xc9, 0xc2, 0xbc, 0xb3, 0xab, 0xa2, 0x99, 0x8f, 0x87,
    0x7c, 0x72, 0x68, 0x5e, 0x54, 0x4a, 0x41, 0x3a, 0x32, 0x2a, 0x22, 0x1d, 0x15, 0x12, 0x0f, 0x0d, 0x0b, 0x09, 0x07, 0x05, 0x04, 0x04, 0x03, 0x02,
};

/* 801E73B4-801E74F4       .text dMsg2_value_init__FP14sub_msg2_classUc */
// NONMATCHING - weird stuff with color OR'ing
void dMsg2_value_init(sub_msg2_class* i_Msg, u8 i_index) {
    static const u32 colorTable[] = {
        0x00000000,
        0xB4000000,
        0x82828200,
        0x0000AA00,
        0xF0F01E00,
        0x82FFFF00,
        0x6400FF00,
        0x50505000,
        0xFFB40000,
    };

    char text_buf[32];
    char textSdw_buf[32];
    char ruby_buf[32];
    char rubySdw_buf[32];

    const u32 color = colorTable[i_Msg->colorNo];
    int i = i_index;

    int temp_r5 = i_Msg->msgDataProc[i].getRGradAlpha();
    int temp_r6 = i_Msg->msgDataProc[i].getRCharAlpha();
    int var_r30 = i_Msg->msgDataProc[i].getGradAlpha();
    int var_r29 = i_Msg->msgDataProc[i].getCharAlpha();

    u32 temp_a = color | temp_r5;
    u32 temp_b = color | temp_r6;
    u32 temp_c = color | var_r30;
    u32 temp_d = color | var_r29;

    sprintf(text_buf, "\x1b""CC[%08x]\x1bGC[%08x]", temp_a, temp_b);
    sprintf(ruby_buf, "\x1b""CC[%08x]\x1bGC[%08x]", temp_c, temp_d);
    sprintf(textSdw_buf, "\x1b""CC[%08x]\x1bGC[%08x]", temp_r5, temp_r6);
    sprintf(rubySdw_buf, "\x1b""CC[%08x]\x1bGC[%08x]", var_r30, var_r29);

    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

    strcpy(i_Msg->output_text[i], text_buf);
    strcpy(i_Msg->output_ruby[i], ruby_buf);
    strcpy(i_Msg->output_textSdw[i], textSdw_buf);
    strcpy(i_Msg->output_rubySdw[i], rubySdw_buf);

    mDoExt_setCurrentHeap(heap);
}

/* 801E74F4-801E75A8       .text dMsg2_setString__FP14sub_msg2_classUc */
void dMsg2_setString(sub_msg2_class* i_Msg, u8 i_index) {
    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setString(i_Msg->output_text[i_index]);
    ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->setString(i_Msg->output_ruby[i_index]);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setString(i_Msg->output_textSdw[i_index]);
    ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->setString(i_Msg->output_rubySdw[i_index]);

    mDoExt_setCurrentHeap(heap);
}

/* 801E75A8-801E75CC       .text dMsg2_messagePaneShow__FP14sub_msg2_classUc */
void dMsg2_messagePaneShow(sub_msg2_class* i_Msg, u8 i_index) {
    i_Msg->text_pane[i_index].pane->show();
    i_Msg->ruby_pane[i_index].pane->show();
}

/* 801E75CC-801E75F0       .text dMsg2_messagePaneHide__FP14sub_msg2_classUc */
void dMsg2_messagePaneHide(sub_msg2_class* i_Msg, u8 i_index) {
    i_Msg->text_pane[i_index].pane->hide();
    i_Msg->ruby_pane[i_index].pane->hide();
}

/* 801E75F0-801E76DC       .text dMsg2_outFontHide__FP14sub_msg2_classUc */
void dMsg2_outFontHide(sub_msg2_class* i_Msg, u8 i_index) {
    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

    for (int i = 0; i < 8; i++) {
        bbutton_icon[i][i_index]->hide();
        bbutton_kage[i][i_index]->hide();

        bbutton_icon[i][i_index]->rotate(0.0f);
        bbutton_kage[i][i_index]->rotate(0.0f);

        bbuttonTimer[i][i_index] = -1;
    }

    mDoExt_setCurrentHeap(heap);
}

/* 801E76DC-801E7714       .text dMsg2_arrowUpShow__FP14sub_msg2_class */
void dMsg2_arrowUpShow(sub_msg2_class* i_Msg) {
    fopMsgM_setInitAlpha(&i_Msg->field_0xbb0);
    fopMsgM_setInitAlpha(&i_Msg->field_0xbe8);
}

/* 801E7714-801E774C       .text dMsg2_arrowUpHide__FP14sub_msg2_class */
void dMsg2_arrowUpHide(sub_msg2_class* i_Msg) {
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xbb0);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xbe8);
}

/* 801E774C-801E7784       .text dMsg2_arrowDownShow__FP14sub_msg2_class */
void dMsg2_arrowDownShow(sub_msg2_class* i_Msg) {
    fopMsgM_setInitAlpha(&i_Msg->field_0xc20);
    fopMsgM_setInitAlpha(&i_Msg->field_0xc58);
}

/* 801E7784-801E77BC       .text dMsg2_arrowDownHide__FP14sub_msg2_class */
void dMsg2_arrowDownHide(sub_msg2_class* i_Msg) {
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc20);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc58);
}

/* 801E77BC-801E77F4       .text dMsg2_dotShow__FP14sub_msg2_class */
void dMsg2_dotShow(sub_msg2_class* i_Msg) {
    fopMsgM_setInitAlpha(&i_Msg->field_0xc90);
    fopMsgM_setInitAlpha(&i_Msg->field_0xcc8);
}

/* 801E77F4-801E782C       .text dMsg2_dotHide__FP14sub_msg2_class */
void dMsg2_dotHide(sub_msg2_class* i_Msg) {
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc90);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xcc8);
}

/* 801E782C-801E79B4       .text dMsg2_multiTexInit__FP14sub_msg2_class */
void dMsg2_multiTexInit(sub_msg2_class* i_Msg) {
    JKRReadTypeResource(i_Msg->Tex[0], 0x11800, 'TIMG', "hukidashi_0212.bti", dComIfGp_getMsgArchive());
#if VERSION <= VERSION_JPN
        DCFlushRangeNoSync(i_Msg->Tex[0], 0x11800);
#else
        DCStoreRangeNoSync(i_Msg->Tex[0], 0x11800);
#endif

    if (i_Msg->mesgEntry.mTextboxType == 6) {
        JKRReadTypeResource(i_Msg->Tex[1], 0x11800, 'TIMG', "hukidashi_06.bti", dComIfGp_getMsgArchive());
#if VERSION <= VERSION_JPN
        DCFlushRangeNoSync(i_Msg->Tex[1], 0x11800);
#else
        DCStoreRangeNoSync(i_Msg->Tex[1], 0x11800);
#endif
        board.init(i_Msg->Tex[0], i_Msg->Tex[1], 1.0f, 1.0f);
    } else if (i_Msg->mesgEntry.mTextboxType == 7) {
        JKRReadTypeResource(i_Msg->Tex[1], 0x11800, 'TIMG', "hukidashi_07.bti", dComIfGp_getMsgArchive());
#if VERSION <= VERSION_JPN
        DCFlushRangeNoSync(i_Msg->Tex[1], 0x11800);
#else
        DCStoreRangeNoSync(i_Msg->Tex[1], 0x11800);
#endif
        board.init(i_Msg->Tex[0], i_Msg->Tex[1], 1.0f, 1.0f);
    } else {
        JKRReadTypeResource(i_Msg->Tex[1], 0x11800, 'TIMG', "hukidashi_02.bti", dComIfGp_getMsgArchive());
#if VERSION <= VERSION_JPN
        DCFlushRangeNoSync(i_Msg->Tex[1], 0x11800);
#else
        DCStoreRangeNoSync(i_Msg->Tex[1], 0x11800);
#endif
        board.init(i_Msg->Tex[0], i_Msg->Tex[1], 1.0f, 1.0f);
    }
}

/* 801E79B4-801E7A74       .text dMsg2_fontdataInit__FP14sub_msg2_class */
void dMsg2_fontdataInit(sub_msg2_class* i_Msg) {
    i_Msg->mx = mDoExt_getMesgFont();
    JUT_ASSERT(VERSION_SELECT(555, 555, 555, 555), i_Msg->mx != NULL);

    i_Msg->rx = mDoExt_getRubyFont();
    JUT_ASSERT(VERSION_SELECT(557, 557, 558, 558), i_Msg->rx != NULL);
}

/* 801E7A74-801E7AB8       .text dMsg2_screenDataSet__FP14sub_msg2_classUc */
void dMsg2_screenDataSet(sub_msg2_class* i_Msg, u8 i_index) {
    dMsg2_value_init(i_Msg, i_index);
    dMsg2_setString(i_Msg, i_index);
}

/* 801E7AB8-801E8154       .text dMsg2_screenDataInit__FP14sub_msg2_classUc */
// NONMATCHING - some reg alloc
void dMsg2_screenDataInit(sub_msg2_class* i_Msg, u8 i_index) {
    fopMsgM_setPaneData(&i_Msg->text_pane[i_index], sScreen2[i_index]->search('tx23'));
    fopMsgM_setPaneData(&i_Msg->ruby_pane[i_index], sScreen2[i_index]->search('tx29'));
    fopMsgM_setPaneData(&i_Msg->textSdw_pane[i_index], sScreen2[i_index]->search('tx20'));
    fopMsgM_setPaneData(&i_Msg->rubySdw_pane[i_index], sScreen2[i_index]->search('tx26'));

    i_Msg->textSdw_pane[i_index].pane->hide();
    i_Msg->rubySdw_pane[i_index].pane->hide();

#if VERSION >= VERSION_USA
    i_Msg->text_pane[i_index].mSizeOrig.y += 10.0f;
    i_Msg->text_pane[i_index].mSize.y = i_Msg->text_pane[i_index].mSizeOrig.y;
    fopMsgM_cposMove(&i_Msg->text_pane[i_index]);

    i_Msg->textSdw_pane[i_index].mSizeOrig.y += 10.0f;
    i_Msg->textSdw_pane[i_index].mSize.y = i_Msg->textSdw_pane[i_index].mSizeOrig.y;
    fopMsgM_cposMove(&i_Msg->textSdw_pane[i_index]);
#endif

    fopMsgM_setPaneData(&i_Msg->field_0xd00[i_index], sScreen2[i_index]->search('ms22'));
    fopMsgM_setPaneData(&i_Msg->field_0xda8[i_index], sScreen2[i_index]->search('ms20'));

    sScreen2[i_index]->search('tx24')->hide();
    sScreen2[i_index]->search('tx30')->hide();
    sScreen2[i_index]->search('tx21')->hide();
    sScreen2[i_index]->search('tx27')->hide();

    ((J2DPicture*)i_Msg->field_0xd00[i_index].pane)->setWhite(0);
    ((J2DPicture*)i_Msg->field_0xda8[i_index].pane)->setWhite(0);

    if (i_index == 0) {
        fopMsgM_setPaneData(&i_Msg->field_0xbb0, sScreen2[i_index]->search('yz21'));
        fopMsgM_setPaneData(&i_Msg->field_0xc20, sScreen2[i_index]->search('yz20'));
        fopMsgM_setPaneData(&i_Msg->field_0xc90, sScreen2[i_index]->search('dt20'));
        fopMsgM_setPaneData(&i_Msg->field_0xbe8, sScreen2[i_index]->search('yz23'));
        fopMsgM_setPaneData(&i_Msg->field_0xc58, sScreen2[i_index]->search('yz22'));
        fopMsgM_setPaneData(&i_Msg->field_0xcc8, sScreen2[i_index]->search('dt21'));

        ((J2DPicture*)i_Msg->field_0xbe8.pane)->setWhite(0x000000FF);
        ((J2DPicture*)i_Msg->field_0xc58.pane)->setWhite(0x000000FF);
        ((J2DPicture*)i_Msg->field_0xcc8.pane)->setWhite(0x000000FF);
    } else {
        sScreen2[i_index]->search('yz21')->hide();
        sScreen2[i_index]->search('yz20')->hide();
        sScreen2[i_index]->search('dt20')->hide();
        sScreen2[i_index]->search('yz23')->hide();
        sScreen2[i_index]->search('yz22')->hide();
        sScreen2[i_index]->search('dt21')->hide();
    }

    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setFont(i_Msg->mx);
    ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->setFont(i_Msg->rx);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setFont(i_Msg->mx);
    ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->setFont(i_Msg->rx);

    f32 var_f31;
    J2DTextBox::TFontSize size;
#if VERSION <= VERSION_JPN
    if (!g_msgDHIO.field_0x08) {
        size.mSizeX = (int)g_messageHIO.field_0x32;
        size.mSizeY = (int)g_messageHIO.field_0x32;

        J2DTextBox::TFontSize size2;
        size2.mSizeX = g_msgHIO.field_0x68;
        size2.mSizeY = g_msgHIO.field_0x68;

        ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setFontSize(size);
        ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->setFontSize(size2);
        ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setFontSize(size);
        ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->setFontSize(size2);
    } else {
        size.mSizeX = g_msgHIO.field_0x70;
        size.mSizeY = g_msgHIO.field_0x70;

        ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setFontSize(size);
        ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setFontSize(size);
    }
#else
    size.mSizeX = g_msgHIO.field_0x70;
    size.mSizeY = g_msgHIO.field_0x70;

    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setFontSize(size);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setFontSize(size);
#endif

    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setCharSpace(0.0f);
    ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->setCharSpace(0.0f);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setCharSpace(0.0f);
    ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->setCharSpace(0.0f);

#if VERSION <= VERSION_JPN
    if (!g_msgDHIO.field_0x08) {
        ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setLineSpace(42.0f);
        ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->setLineSpace(42.0f);
        ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setLineSpace(42.0f);
        ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->setLineSpace(42.0f);
    } else {
        ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setLineSpace(g_msgHIO.field_0x5e);
        ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setLineSpace(g_msgHIO.field_0x5e);
    }
#else
    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->setLineSpace(g_msgHIO.field_0x5e);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->setLineSpace(g_msgHIO.field_0x5e);
#endif

    i_Msg->field_0xeb4 = size.mSizeX;
    i_Msg->field_0xeb8 = var_f31;
}

/* 801E8154-801E8260       .text dMsg2_ScreenDataValueInit__FP14sub_msg2_class */
void dMsg2_ScreenDataValueInit(sub_msg2_class* i_Msg) {
    J2DPane* pane = i_Msg->text_pane[0].pane;
    i_Msg->field_0xeb0 = ((J2DTextBox*)pane)->getLineSpace() / 2;
    i_Msg->field_0xe94 = pane->getHeight() + g_messageHIO.field_0x3c;

    fopMsgM_paneTrans(&i_Msg->text_pane[0], 0.0f, 0.0f);
    fopMsgM_paneTrans(&i_Msg->text_pane[1], 0.0f, i_Msg->field_0xe94);
    fopMsgM_paneTrans(&i_Msg->text_pane[2], 0.0f, -i_Msg->field_0xe94);

    fopMsgM_setNowAlphaZero(&i_Msg->field_0xbb0);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xbe8);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc20);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc58);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xc90);
    fopMsgM_setNowAlphaZero(&i_Msg->field_0xcc8);

    for (int i = 0; i < 3; i++) {
        dMsg2_messageDataInit(i_Msg, i);
    }
}

/* 801E8260-801E82B8       .text dMsg2_stickInfoInit__FP14sub_msg2_class */
void dMsg2_stickInfoInit(sub_msg2_class* i_Msg) {
    if (CPad_GET_STICK_POS_Y(0) > 0.7f || CPad_GET_STICK_POS_Y(3) > 0.7f) {
        i_Msg->field_0xedd = 1;
    } else if (CPad_GET_STICK_POS_Y(0) < 0.7f || CPad_GET_STICK_POS_Y(3) < 0.7f) {
        i_Msg->field_0xedd = 2;
    } else {
        i_Msg->field_0xedd = 0;
    }
}

/* 801E82B8-801E833C       .text dMsg2_stickInfoCheck__FP14sub_msg2_class */
void dMsg2_stickInfoCheck(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xedd == 1) {
        if (CPad_GET_STICK_POS_Y(0) <= 0.0f || CPad_GET_STICK_POS_Y(3) <= 0.0f) {
            i_Msg->field_0xedd = 0;
        }
    } else if (i_Msg->field_0xedd == 2) {
        if (CPad_GET_STICK_POS_Y(0) >= 0.0f || CPad_GET_STICK_POS_Y(3) >= 0.0f) {
            i_Msg->field_0xedd = 0;
        }
    }
}

/* 801E833C-801E84E8       .text dMsg2_multiTexDraw__FP14sub_msg2_classssss */
void dMsg2_multiTexDraw(sub_msg2_class* i_Msg, s16 param_1, s16 param_2, s16 param_3, s16 param_4) {
    f32 var_f31 = (i_Msg->field_0xeac * g_messageHIO.field_0x5b) / 255.0f;
    
    board.setPos(param_1, param_2, param_1 + param_3, param_2 + param_4);

    if (i_Msg->mesgEntry.mTextboxType == 7) {
        board.setBlackColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        board.setWhiteColor((GXColor){0x00, 0x00, 0x00, 0x00});
    } else {
        board.setBlackColor((GXColor){0xF0, 0xF0, 0xF0, 0xDC});
        board.setWhiteColor((GXColor){0x78, 0x78, 0x8C, 0x00});
    }

    board.setAlpha(var_f31);
    board.setScroll(0, 0, 0);
    board.setScroll(1, 0, i_Msg->field_0xec8);
    dComIfGd_set2DOpa(&board);
}

/* 801E84E8-801E8668       .text dMsg2_messageOut__FP14sub_msg2_classUci */
void dMsg2_messageOut(sub_msg2_class* i_Msg, u8 i_index, int i_aimLine) {
    i_Msg->field_0xecc[i_index] = 0;
    dMsg2_messagePaneShow(i_Msg, i_index);
    dMsg2_messageDataInit(i_Msg, i_index);

    i_Msg->msgDataProc[i_index].setCount(0);
    i_Msg->msgDataProc[i_index].resetNowLine();
    i_Msg->msgDataProc[i_index].setAimLine(i_aimLine);
    dMsg2_yose_select(i_Msg, i_index);
    i_Msg->msgDataProc[i_index].shortCut();
    dMsg2_setCharAlpha(i_Msg, i_index);
    i_Msg->msgDataProc[i_index].stringSet();

    for (int i = 0; i < 8; i++) {
        u8 var_r30 = i_Msg->msgDataProc[i_index].getIconNum(i);
        u32 var_r29 = i_Msg->msgDataProc[i_index].get_0x220(i);

        if (var_r30 != 0xFF && bbuttonTimer[i][i_index] == -1) {
            JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

            if ((var_r30 == 10 || var_r30 == 11 || var_r30 == 12 || var_r30 == 13 || var_r30 == 0x15 || var_r30 == 0x17) && var_r29 == 0) {
                var_r29 = -1;
            }

            fopMsgM_outFontSet(bbutton_icon[i][i_index], bbutton_kage[i][i_index], &bbuttonTimer[i][i_index], var_r29, var_r30);

            mDoExt_setCurrentHeap(heap);
        }
    }

    dMsg2_setString(i_Msg, i_index);
}

/* 801E8668-801E86E8       .text dMsg2_yose_select__FP14sub_msg2_classUc */
void dMsg2_yose_select(sub_msg2_class* i_Msg, u8 i_index) {
    i_Msg->msgDataProc[i_index].count = i_Msg->msgDataProc[i_index].stringLength();
    i_Msg->field_0xecc[i_index] = i_Msg->msgDataProc[i_index].lineCount;
    i_Msg->msgDataProc[i_index].lineCount = 0;
    i_Msg->msgDataProc[i_index].stringShift();
    dMsg2_textPosition(i_Msg, i_index);
}

/* 801E86E8-801E8798       .text dMsg2_textPosition__FP14sub_msg2_classUc */
// NONMATCHING - small reg alloc
void dMsg2_textPosition(sub_msg2_class* i_Msg, u8 i_index) {
    int r7 = 0;
    int temp_r0 = i_Msg->field_0xeb0 * (3 - i_Msg->field_0xecc[i_index]);
    ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->shiftSet(r7, temp_r0);
    ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->shiftSet(r7, temp_r0);
    ((J2DTextBox*)i_Msg->textSdw_pane[i_index].pane)->shiftSet(r7, temp_r0);
    ((J2DTextBox*)i_Msg->rubySdw_pane[i_index].pane)->shiftSet(r7, temp_r0);
}

/* 801E8798-801E880C       .text dMsg2_rubySet__FP14sub_msg2_class */
void dMsg2_rubySet(sub_msg2_class* i_Msg) {
    if (i_Msg->msg.mStatus == 5 || i_Msg->msg.mStatus == 6 || i_Msg->msg.mStatus == 7 || i_Msg->msg.mStatus == 10) {
        for (int i = 0; i < 3; i++) {
            if (!g_messageHIO.field_0x4b) {
                i_Msg->ruby_pane[i].pane->hide();
            } else {
                i_Msg->ruby_pane[i].pane->show();
            }
        }
    }
}

/* 801E880C-801E8994       .text dMsg2_arrowMove__FP14sub_msg2_class */
void dMsg2_arrowMove(sub_msg2_class* i_Msg) {
    i_Msg->field_0xebc++;
    if (i_Msg->field_0xebc > 12) {
        i_Msg->field_0xebc -= 12;
    }

    i_Msg->field_0xc20.pane->move(i_Msg->field_0xc20.mPosTopLeftOrig.x, (i_Msg->field_0xc20.mPosTopLeftOrig.y - DEMO_SELECT(0.0f, 3.0f)) - abs(6 - i_Msg->field_0xebc));
    i_Msg->field_0xc58.pane->move(i_Msg->field_0xc20.mPosTopLeftOrig.x, (i_Msg->field_0xc20.mPosTopLeftOrig.y - DEMO_SELECT(0.0f, 3.0f)) - abs(6 - i_Msg->field_0xebc));
    i_Msg->field_0xbb0.pane->move(i_Msg->field_0xbb0.mPosTopLeftOrig.x, (i_Msg->field_0xbb0.mPosTopLeftOrig.y - DEMO_SELECT(0.0f, 3.0f)) + abs(6 - i_Msg->field_0xebc));
    i_Msg->field_0xbe8.pane->move(i_Msg->field_0xbb0.mPosTopLeftOrig.x, (i_Msg->field_0xbb0.mPosTopLeftOrig.y - DEMO_SELECT(0.0f, 3.0f)) + abs(6 - i_Msg->field_0xebc));
}

/* 801E8994-801E8A70       .text dMsg2_aimAlphaSqare__FP14sub_msg2_classii */
// NONMATCHING - float reg alloc
void dMsg2_aimAlphaSqare(sub_msg2_class* i_Msg, int param_0, int param_1) {
    if (param_1 < 0) {
        param_1 = 0;
    } else if (param_1 > param_0) {
        param_1 = param_0;
    }

    i_Msg->field_0xea8 = 255.0f - (255.0f - dMsg2_aimBrightness()) * (((f32)param_1 * (f32)param_1) / ((f32)param_0 * (f32)param_0));
}

/* 801E8A70-801E8B90       .text dMsg2_aimAlphaSqrt__FP14sub_msg2_classii */
void dMsg2_aimAlphaSqrt(sub_msg2_class* i_Msg, int param_0, int param_1) {
    if (param_1 < 0) {
        param_1 = 0;
    } else if (param_1 > param_0) {
        param_1 = param_0;
    }

    i_Msg->field_0xea8 = 255.0f - (255.0f - dMsg2_aimBrightness()) * std::sqrtf((f32)param_1 / (f32)param_0);
}

/* 801E8B90-801E8C2C       .text dMsg2_kankyoBrightness__Fv */
u8 dMsg2_kankyoBrightness() {
    GXColorS10* difcol = dKy_Get_DifCol();
    return (difcol->r * 0.299f) + (difcol->g * 0.587f) + (difcol->b * 0.114f);
}

/* 801E8C2C-801E8C78       .text dMsg2_aimBrightness__Fv */
// NONMATCHING
u8 dMsg2_aimBrightness() {
    u32 brightness = dMsg2_kankyoBrightness();
    return g_messageHIO.field_0x29 <= brightness ? 0xFF : 0xFF - (brightness - g_messageHIO.field_0x29);
}

/* 801E8C78-801E9054       .text dMsg2_setCharAlpha__FP14sub_msg2_classUc */
// NONMATCHING - some float issues
void dMsg2_setCharAlpha(sub_msg2_class* i_Msg, u8 i_index) {
    int temp_r6 = ((J2DTextBox*)i_Msg->text_pane[0].pane)->getLineSpace();
    f32 temp_f1 = i_Msg->field_0xd00[0].mPosTopLeftOrig.y - i_Msg->field_0xda8[0].mPosTopLeftOrig.y;

    int var_r31 = i_index;
    f32 temp_f2 = temp_f1 + i_Msg->text_pane[var_r31].mPosTopLeft.y + (i_Msg->field_0xeb0 * (2 - i_Msg->field_0xecc[i_index]));

    int temp_r27 = (temp_r6 * i_Msg->field_0xecc[i_index]);
    int var_r26 = (int)temp_f2 + temp_r27;
    int var_r30 = (int)(temp_f2 - g_messageHIO.field_0x38);
    int var_r29 = var_r30 + temp_r27;

    if (var_r26 < 58) {
        int temp_r3 = var_r26 + i_Msg->mx->getHeight();
        if (var_r26 >= 0) {
            i_Msg->field_0xedf[0][var_r31] = dMsg2_tex_i4_color[var_r26];
        } else {
            i_Msg->field_0xedf[0][var_r31] = 0;
        }

        if (temp_r3 >= 0) {
            i_Msg->field_0xedf[1][var_r31] = dMsg2_tex_i4_color[temp_r3];
        } else {
            i_Msg->field_0xedf[1][var_r31] = 0;
        }
    } else if (temp_r27 > 187) {
        int temp_r3 = temp_r27 + i_Msg->mx->getHeight();
        if (temp_r27 <= 239) {
            i_Msg->field_0xedf[0][var_r31] = dMsg2_tex_i4_color[temp_r27];
        } else {
            i_Msg->field_0xedf[0][var_r31] = 0;
        }

        if (temp_r3 <= 239) {
            i_Msg->field_0xedf[1][var_r31] = dMsg2_tex_i4_color[temp_r3];
        } else {
            i_Msg->field_0xedf[1][var_r31] = 0;
        }
    } else {
        i_Msg->field_0xedf[0][var_r31] = 0xFF;
        i_Msg->field_0xedf[1][var_r31] = 0xFF;
    }

    if (var_r29 < 58) {
        int temp_r3 = var_r29 + i_Msg->rx->getHeight();
        if (var_r29 >= 0) {
            i_Msg->field_0xedf[2][var_r31] = dMsg2_tex_i4_color[var_r29];
        } else {
            i_Msg->field_0xedf[2][var_r31] = 0;
        }

        if (temp_r3 >= 0) {
            i_Msg->field_0xedf[3][var_r31] = dMsg2_tex_i4_color[temp_r3];
        } else {
            i_Msg->field_0xedf[3][var_r31] = 0;
        }
    } else if (var_r30 > 187) {
        int temp_r3 = var_r30 + i_Msg->rx->getHeight();
        if (var_r30 <= 239) {
            i_Msg->field_0xedf[2][var_r31] = dMsg2_tex_i4_color[var_r30];
        } else {
            i_Msg->field_0xedf[2][var_r31] = 0;
        }

        if (temp_r3 <= 239) {
            i_Msg->field_0xedf[3][var_r31] = dMsg2_tex_i4_color[temp_r3];
        } else {
            i_Msg->field_0xedf[3][var_r31] = 0;
        }
    } else {
        i_Msg->field_0xedf[2][var_r31] = 0xFF;
        i_Msg->field_0xedf[3][var_r31] = 0xFF;
    }

    if (i_Msg->field_0xedf[0][var_r31] > (u8)i_Msg->field_0xeac) {
        i_Msg->field_0xedf[0][var_r31] = i_Msg->field_0xeac;
    }

    if (i_Msg->field_0xedf[1][var_r31] > (u8)i_Msg->field_0xeac) {
        i_Msg->field_0xedf[1][var_r31] = i_Msg->field_0xeac;
    }

    if (i_Msg->field_0xedf[2][var_r31] > (u8)i_Msg->field_0xeac) {
        i_Msg->field_0xedf[2][var_r31] = i_Msg->field_0xeac;
    }

    if (i_Msg->field_0xedf[3][var_r31] > (u8)i_Msg->field_0xeac) {
        i_Msg->field_0xedf[3][var_r31] = i_Msg->field_0xeac;
    }

    i_Msg->msgDataProc[var_r31].setCharAlpha(i_Msg->field_0xedf[0][var_r31],
                                              i_Msg->field_0xedf[1][var_r31],
                                              i_Msg->field_0xedf[2][var_r31],
                                              i_Msg->field_0xedf[3][var_r31]);
}

/* 801E9054-801E9108       .text dMsg2_messageShow__FP14sub_msg2_class */
void dMsg2_messageShow(sub_msg2_class* i_Msg) {
    for (u8 i = 0; i < 3; i++) {
        dMsg2_screenDataSet(i_Msg, i);
    }

    if (i_Msg->field_0xec4 > 0) {
        dMsg2_messageOut(i_Msg, i_Msg->field_0xe9c, i_Msg->field_0xec4 - i_Msg->mesgEntry.field_0x16);
    }

    dMsg2_messageOut(i_Msg, i_Msg->field_0xe9d, i_Msg->field_0xec4);

    if (i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus() == 7) {
        dMsg2_messageOut(i_Msg, i_Msg->field_0xe9e, i_Msg->field_0xec4 + i_Msg->mesgEntry.field_0x16);
    }
}

/* 801E9108-801E9254       .text dMsg2_messageDataInit__FP14sub_msg2_classi */
void dMsg2_messageDataInit(sub_msg2_class* i_Msg, int i_index) {
    f32 char_space = ((J2DTextBox*)i_Msg->text_pane[i_index].pane)->getCharSpace();
    f32 ruby_space = ((J2DTextBox*)i_Msg->ruby_pane[i_index].pane)->getCharSpace();

    i_Msg->msgDataProc[i_index].dataInit();
    i_Msg->msgDataProc[i_index].setBmgData(i_Msg->message);

    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);
    i_Msg->msgDataProc[i_index].setOutMessage(i_Msg->output_text[i_index], i_Msg->output_ruby[i_index], i_Msg->output_textSdw[i_index], i_Msg->output_rubySdw[i_index]);
    mDoExt_setCurrentHeap(heap);

    i_Msg->msgDataProc[i_index].setFont(i_Msg->mx);
    i_Msg->msgDataProc[i_index].setRubyFont(i_Msg->rx);
    i_Msg->msgDataProc[i_index].setCharSpace(char_space);
    i_Msg->msgDataProc[i_index].setRubyCharSpace(ruby_space);
    i_Msg->msgDataProc[i_index].setLineSpace(((J2DTextBox*)i_Msg->text_pane[i_index].pane)->getLineSpace());
    i_Msg->msgDataProc[i_index].setMesgEntry(&i_Msg->mesgEntry);
    i_Msg->msgDataProc[i_index].setFontSize(i_Msg->field_0xeb4);
    i_Msg->msgDataProc[i_index].setRubyFontSize(i_Msg->field_0xeb8);
    i_Msg->msgDataProc[i_index].setLineWidth(503);
    i_Msg->msgDataProc[i_index].setCenterLineWidth(486);
    i_Msg->msgDataProc[i_index].setSpaceFlagOff();
}

/* 801E9254-801E93B4       .text dMsg2_stopProc__FP14sub_msg2_class */
int dMsg2_stopProc(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xedd == 0) {
        if (CPad_GET_STICK_POS_Y(0) > 0.7f || CPad_GET_STICK_POS_Y(3) > 0.7f) {
            if (i_Msg->field_0xec4 != 0) {
                u8 r4 = i_Msg->field_0xe9e;
                i_Msg->field_0xedd = 1;
                dMsg2_screenDataSet(i_Msg, r4);
                i_Msg->field_0xec0 = 3;
                i_Msg->field_0xec4 -= i_Msg->mesgEntry.field_0x16;
                i_Msg->msg.mStatus = 5;
                mDoAud_seStart(JA_SE_SCROLL_1, NULL);
            }
        } else if (CPad_CHECK_TRIG_A(0) || CPad_GET_STICK_POS_Y(0) < -0.7f || CPad_GET_STICK_POS_Y(3) < -0.7f) {
            u8 r4 = i_Msg->field_0xe9c;
            i_Msg->field_0xedd = 2;
            dMsg2_screenDataSet(i_Msg, r4);
            i_Msg->field_0xec0 = 1;
            i_Msg->field_0xec4 += i_Msg->mesgEntry.field_0x16;
            i_Msg->msg.mStatus = 5;
            mDoAud_seStart(JA_SE_SCROLL_1, NULL);
        }
#if VERSION > VERSION_DEMO
        else {
            dMeter_Info.field_0x0 = 1;
        }
#endif
    } else {
        dMsg2_stickInfoCheck(i_Msg);
    }

    return 1;
}

/* 801E93B4-801E94F0       .text dMsg2_closewaitProc__FP14sub_msg2_class */
int dMsg2_closewaitProc(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xedd == 0) {
        if (CPad_GET_STICK_POS_Y(0) > 0.7f || CPad_GET_STICK_POS_Y(3) > 0.7f) {
            if (i_Msg->field_0xec4 != 0) {
                u8 r4 = i_Msg->field_0xe9e;
                i_Msg->field_0xedd = 1;
                dMsg2_screenDataSet(i_Msg, r4);
                i_Msg->field_0xec0 = 3;
                i_Msg->field_0xec4 -= i_Msg->mesgEntry.field_0x16;
                i_Msg->msg.mStatus = 5;
                mDoAud_seStart(JA_SE_SCROLL_1, NULL);
            }
        } else if (CPad_CHECK_TRIG_A(0) || CPad_GET_STICK_POS_Y(0) < -0.7f || CPad_GET_STICK_POS_Y(3) < -0.7f) {
            i_Msg->field_0xedd = 2;
            mDoAud_seStart(JA_SE_TALK_WIN_CLOSE, NULL);
            i_Msg->msg.mStatus = 16;
        }
#if VERSION > VERSION_DEMO
        else {
            dMeter_Info.field_0x0 = 4;
        }
#endif
    } else {
        dMsg2_stickInfoCheck(i_Msg);
    }

    return 1;
}

/* 801E94F0-801E9660       .text dMsg2_openProc__FP14sub_msg2_class */
int dMsg2_openProc(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xe98 == 0) {
        dMsg2_messageOut(i_Msg, i_Msg->field_0xe9d, i_Msg->field_0xec4);
        if (i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus() == 7) {
            dMsg2_messageOut(i_Msg, i_Msg->field_0xe9e, i_Msg->field_0xec4 + i_Msg->mesgEntry.field_0x16);
        }
    } else if (i_Msg->field_0xe98 == dMsg2_popSpeed) {
        i_Msg->msg.mStatus = i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus();
    }

    i_Msg->field_0xeac = fopMsgM_valueIncrease(dMsg2_popSpeed, i_Msg->field_0xe98, 0) * 255.0f;
    if (i_Msg->field_0xe98 != 0) {
        dMsg2_messageShow(i_Msg);
    }

    if (i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus() == 7) {
        i_Msg->field_0xc20.mNowAlpha = i_Msg->field_0xeac;
        i_Msg->field_0xc58.mNowAlpha = i_Msg->field_0xeac;
    } else {
        i_Msg->field_0xc90.mNowAlpha = i_Msg->field_0xeac;
        i_Msg->field_0xcc8.mNowAlpha = i_Msg->field_0xeac;
    }

    dMsg2_aimAlphaSqrt(i_Msg, dMsg2_popSpeed, i_Msg->field_0xe98);
    dComIfG_setBrightness(i_Msg->field_0xea8);
    i_Msg->field_0xe98++;
    return 1;
}

/* 801E9660-801E97EC       .text dMsg2_closeProc__FP14sub_msg2_class */
int dMsg2_closeProc(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xe98 == 0) {
        for (u8 i = 0; i < 3; i++) {
            dMsg2_messagePaneHide(i_Msg, i);
            dMsg2_outFontHide(i_Msg, i);
        }

        JKRFileLoader::removeResource(i_Msg->head_p, NULL);
        i_Msg->msg.mStatus = 0x12;
    }

    i_Msg->field_0xe98--;
    if (i_Msg->field_0xe98 < 0) {
        i_Msg->field_0xe98 = 0;
    }

    i_Msg->field_0xeac = fopMsgM_valueIncrease(dMsg2_popSpeed, i_Msg->field_0xe98, 0) * 255.0f;

    if (i_Msg->field_0xbb0.mNowAlpha != 0) {
        i_Msg->field_0xbb0.mNowAlpha = i_Msg->field_0xeac;
        i_Msg->field_0xbe8.mNowAlpha = i_Msg->field_0xeac;
    }

    if (i_Msg->field_0xc20.mNowAlpha != 0) {
        i_Msg->field_0xc20.mNowAlpha = i_Msg->field_0xeac;
        i_Msg->field_0xc58.mNowAlpha = i_Msg->field_0xeac;
    }

    if (i_Msg->field_0xc90.mNowAlpha != 0) {
        i_Msg->field_0xc90.mNowAlpha = i_Msg->field_0xeac;
        i_Msg->field_0xcc8.mNowAlpha = i_Msg->field_0xeac;
    }

    dMsg2_aimAlphaSqare(i_Msg, dMsg2_popSpeed, i_Msg->field_0xe98);
    dComIfG_setBrightness(i_Msg->field_0xea8);
    return 1;
}

/* 801E97EC-801E9C44       .text dMsg2_outwaitProc__FP14sub_msg2_class */
int dMsg2_outwaitProc(sub_msg2_class* i_Msg) {
    if (i_Msg->field_0xec0 == 1 || i_Msg->field_0xec0 == 2) {
        i_Msg->field_0xec8 += 12;
    } else if (i_Msg->field_0xec0 == 3 || i_Msg->field_0xec0 == 4) {
        i_Msg->field_0xec8 -= 12;
    }

    if (i_Msg->field_0xec8 > 1020) {
        i_Msg->field_0xec8 -= 2040;
    } else if (i_Msg->field_0xec8 < -1020) {
        i_Msg->field_0xec8 += 2040;
    }

    if (i_Msg->field_0xec0 == 1) {
        int temp_r4 = i_Msg->field_0xe9c;

        for (int i = 0; i < 3; i++) {
            i_Msg->text_pane[i].mPosTopLeft.y -= 12.0f;
        }

        i_Msg->field_0xede -= 85;

        if (i_Msg->text_pane[temp_r4].mPosTopLeft.y < -i_Msg->field_0xe94) {
            i_Msg->field_0xec0 = 2;

            u8 temp_r3 = i_Msg->field_0xe9d;
            i_Msg->field_0xe9d = i_Msg->field_0xe9e;
            i_Msg->field_0xe9e = i_Msg->field_0xe9c;
            i_Msg->field_0xe9c = temp_r3;

            if (i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus() == 7) {
                dMsg2_messageOut(i_Msg, i_Msg->field_0xe9e, i_Msg->field_0xec4 + i_Msg->mesgEntry.field_0x16);
            } else {
                dMsg2_messagePaneHide(i_Msg, i_Msg->field_0xe9e);
                dMsg2_outFontHide(i_Msg, i_Msg->field_0xe9e);
            }

            i_Msg->field_0xede = 0;
            dMsg2_arrowUpHide(i_Msg);
            dMsg2_arrowDownHide(i_Msg);
            dMsg2_dotHide(i_Msg);
        }
    } else if (i_Msg->field_0xec0 == 3) {
        int temp_r4 = i_Msg->field_0xe9e;

        for (int i = 0; i < 3; i++) {
            i_Msg->text_pane[i].mPosTopLeft.y += 12.0f;
        }

        i_Msg->field_0xede -= 127;

        if (i_Msg->text_pane[temp_r4].mPosTopLeft.y > i_Msg->field_0xd00[0].mSizeOrig.y) {
            i_Msg->field_0xec0 = 4;

            u8 temp_r3 = i_Msg->field_0xe9d;
            i_Msg->field_0xe9d = i_Msg->field_0xe9c;
            i_Msg->field_0xe9c = i_Msg->field_0xe9e;
            i_Msg->field_0xe9e = temp_r3;

            if (i_Msg->field_0xec4 > 0) {
                dMsg2_messageOut(i_Msg, i_Msg->field_0xe9c, i_Msg->field_0xec4 - i_Msg->mesgEntry.field_0x16);
            } else {
                dMsg2_messagePaneHide(i_Msg, i_Msg->field_0xe9c);
                dMsg2_outFontHide(i_Msg, i_Msg->field_0xe9c);
            }

            i_Msg->field_0xede = 0;
            dMsg2_arrowUpHide(i_Msg);
            dMsg2_arrowDownHide(i_Msg);
            dMsg2_dotHide(i_Msg);
        }
    } else if (i_Msg->field_0xec0 == 2) {
        for (int i = 0; i < 3; i++) {
            i_Msg->text_pane[i].mPosTopLeft.y -= 12.0f;
        }

        i_Msg->field_0xede += 43;

        if (i_Msg->text_pane[i_Msg->field_0xe9d].mPosTopLeft.y <= i_Msg->text_pane[0].mPosTopLeftOrig.y) {
            i_Msg->text_pane[i_Msg->field_0xe9c].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y - i_Msg->field_0xe94;
            i_Msg->text_pane[i_Msg->field_0xe9d].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y;
            i_Msg->text_pane[i_Msg->field_0xe9e].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y + i_Msg->field_0xe94;

            i_Msg->field_0xec0 = 0;

            if (i_Msg->msgDataProc[i_Msg->field_0xe9d].getMesgStatus() == 7) {
                i_Msg->msg.mStatus = 7;
                dMsg2_arrowDownShow(i_Msg);
            } else {
                i_Msg->msg.mStatus = 14;
                dMsg2_dotShow(i_Msg);
            }

            i_Msg->field_0xede = 0xFF;

            if (i_Msg->field_0xec4 != 0) {
                dMsg2_arrowUpShow(i_Msg);
            }
        }

        dMsg2_messageShow(i_Msg);
    } else if (i_Msg->field_0xec0 == 4) {
        for (int i = 0; i < 3; i++) {
            i_Msg->text_pane[i].mPosTopLeft.y += 12.0f;
        }

        i_Msg->field_0xede += 37;

        if (i_Msg->text_pane[i_Msg->field_0xe9d].mPosTopLeft.y >= i_Msg->text_pane[0].mPosTopLeftOrig.y) {
            i_Msg->text_pane[i_Msg->field_0xe9c].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y - i_Msg->field_0xe94;
            i_Msg->text_pane[i_Msg->field_0xe9d].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y;
            i_Msg->text_pane[i_Msg->field_0xe9e].mPosTopLeft.y = i_Msg->text_pane[0].mPosTopLeftOrig.y + i_Msg->field_0xe94;

            i_Msg->field_0xec0 = 0;
            i_Msg->msg.mStatus = 7;
            i_Msg->field_0xede = 0xFF;
            dMsg2_arrowDownShow(i_Msg);

            if (i_Msg->field_0xec4 != 0) {
                dMsg2_arrowUpShow(i_Msg);
            }
        }

        dMsg2_messageShow(i_Msg);
    } else {
        dMsg2_messageShow(i_Msg);
    }

    return 1;
}

/* 801E9C44-801E9CDC       .text draw__14dDlst_2DMSG2_cFv */
void dDlst_2DMSG2_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    for (int i = 0; i < 3; i++) {
        sScreen2[2 - i]->setScissor(true);
        sScreen2[2 - i]->draw(0.0f, 0.0f, graf);
    }

    outFontDraw();
}

/* 801E9CDC-801E9FC4       .text outFontDraw__14dDlst_2DMSG2_cFv */
// NONMATCHING - a lot wrong here
void dDlst_2DMSG2_c::outFontDraw() {
    J2DPane* ppane = ((sub_msg2_class*)actorP)->field_0xd00[0].pane;
    f32 var_f31 = ppane->getGlbBounds().i.y;
    f32 var_f30 = ppane->getGlbBounds().f.y;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            sub_msg2_class* msg = (sub_msg2_class*)actorP;
            u8 iconNum = msg->msgDataProc[i].field_0x281[j];
            fopMsgM_msgDataProc_c* dataProc = msg->msgDataProc;
            int temp_r6 = dataProc->field_0x168[i];
            int temp_r4 = dataProc->field_0x1A4[i];
            int var_r22 = dataProc->field_0x1E0[i];

            if (iconNum != 0xFF) {
                J2DTextBox* pJVar3 = (J2DTextBox*)msg->text_pane[i].pane;
                int sp10 = (f32)temp_r6 + pJVar3->getGlbBounds().i.x;

                if (var_r22 > msg->field_0xeb4) {
                    if (msg->field_0xecc[i] > 1) {
                        temp_r4 = ((msg->field_0xeb0 * (3 - temp_r4)) + pJVar3->getGlbBounds().i.y);
                    } else {
                        temp_r4 = (msg->field_0xeb0 + pJVar3->getGlbBounds().i.y);
                    }
                } else {
                    temp_r4 = ((msg->field_0xeb0 * (3 - msg->field_0xecc[i])) + pJVar3->getGlbBounds().i.y);
                }

                u8 sp20 = msg->field_0xeac;
                JKRHeap* heap = mDoExt_setCurrentHeap(msg->Heap);

                if ((f32)temp_r4 > var_f31 && (f32)temp_r4 < var_f30 - (f32)var_r22) {
                    fopMsgM_outFontDraw(bbutton_icon[j][i], bbutton_kage[j][i], sp10, temp_r4, var_r22, &bbuttonTimer[j][i], sp20, iconNum);
                }

                mDoExt_setCurrentHeap(heap);
            }
        }
    }
}

/* 801E9FC4-801EA0C8       .text draw__14dDlst_2DCopy_cFv */
void dDlst_2DCopy_c::draw() {
    int r27 = 0;
    int r28 = 0;
    int r26 = 372;
    int r25 = 72;

    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    int left = r27 * 1.0296875f + -9.0f;
    int top = r28 * 1.0916667f + -21.0f;
    int width = r26 * 1.0296875f;
    int height = r25 * 1.0916667f;

    GXSetScissor(left, top, width, height);
    sScreen2[0]->draw(0.0f, 0.0f, graf);
    GXSetTexCopySrc(left, top, width, height);
    GXSetTexCopyDst(width, height, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(copyTex, REG1_S(6) == 0 ? GX_TRUE : GX_FALSE);
}

/* 801EA0C8-801EA224       .text dMsg2_Draw__FP14sub_msg2_class */
static BOOL dMsg2_Draw(sub_msg2_class* i_Msg) {
    int sp8 = (int)(i_Msg->field_0xda8[0].mPosTopLeftOrig.x + 288.0f) - 288;
    int sp10 = (int)(i_Msg->field_0xda8[0].mPosTopLeftOrig.y + 120.0f) - 120;

    for (int i = 0; i < 3; i++) {
        i_Msg->text_pane[i].mNowAlpha = i_Msg->field_0xeac;
        i_Msg->ruby_pane[i].mNowAlpha = i_Msg->field_0xeac;
        i_Msg->textSdw_pane[i].mNowAlpha = i_Msg->field_0xeac;
        i_Msg->rubySdw_pane[i].mNowAlpha = i_Msg->field_0xeac;

        fopMsgM_setAlpha(&i_Msg->text_pane[i]);
        fopMsgM_setAlpha(&i_Msg->ruby_pane[i]);
        fopMsgM_setAlpha(&i_Msg->textSdw_pane[i]);
        fopMsgM_setAlpha(&i_Msg->rubySdw_pane[i]);
    }

    fopMsgM_setAlpha(&i_Msg->field_0xbb0);
    fopMsgM_setAlpha(&i_Msg->field_0xbe8);
    fopMsgM_setAlpha(&i_Msg->field_0xc20);
    fopMsgM_setAlpha(&i_Msg->field_0xc58);
    fopMsgM_setAlpha(&i_Msg->field_0xc90);
    fopMsgM_setAlpha(&i_Msg->field_0xcc8);

    dMsg2_multiTexDraw(i_Msg, sp8, sp10, 576, 240);

    dComIfGd_set2DOpa(&message);
    return TRUE;
}

/* 801EA224-801EA7C4       .text dMsg2_Execute__FP14sub_msg2_class */
static BOOL dMsg2_Execute(sub_msg2_class* i_Msg) {
    if (i_Msg->msg.mStatus == fopMsgStts_BOX_OPENING_e) {
        dMsg2_openProc(i_Msg);
    } else if (i_Msg->msg.mStatus == 5) {
        dMsg2_outwaitProc(i_Msg);
    } else if (i_Msg->msg.mStatus == fopMsgStts_STOP_e) {
        dMsg2_stopProc(i_Msg);
    } else if (i_Msg->msg.mStatus == fopMsgStts_MSG_DISPLAYED_e) {
        dMsg2_closewaitProc(i_Msg);
    } else if (i_Msg->msg.mStatus == fopMsgStts_MSG_ENDS_e) {
        dMsg2_closeProc(i_Msg);
    } else if (i_Msg->msg.mStatus == fopMsgStts_MSG_DESTROYED_e) {
        fopMsgM_Delete(i_Msg);
    }

    dMsg2_arrowMove(i_Msg);

    int temp_r4 = 0;
    if (dComIfGs_getOptRuby()) {
        temp_r4 = -4;
    }

    for (int i = 0; i < 3; i++) {
        f32 sp64 = i_Msg->text_pane[i].mPosTopLeft.x + g_messageHIO.field_0x58;
        f32 sp74 = i_Msg->text_pane[i].mPosTopLeft.y + temp_r4;
        i_Msg->text_pane[i].pane->move((int)sp64, (int)sp74);
        i_Msg->ruby_pane[i].pane->move((int)sp64, (int)sp74 - g_messageHIO.field_0x38);

        i_Msg->textSdw_pane[i].pane->move((int)sp64 + 2, (int)sp74 + 2);
        i_Msg->rubySdw_pane[i].pane->move((int)sp64 + 2, (int)sp74 + 2 - g_messageHIO.field_0x38);
    }

    dMsg2_rubySet(i_Msg);

    for (int i = 0; i < 3; i++) {
        // fakematch casting? making the members JUtility::TColor breaks the HIO constructor
        ((J2DTextBox*)i_Msg->text_pane[i].pane)->setFontColor(*(JUtility::TColor*)&g_messageHIO.field_0x5, *(JUtility::TColor*)&g_messageHIO.field_0x5);
        ((J2DTextBox*)i_Msg->ruby_pane[i].pane)->setFontColor(*(JUtility::TColor*)&g_messageHIO.field_0x1d, *(JUtility::TColor*)&g_messageHIO.field_0x1d);
        ((J2DTextBox*)i_Msg->textSdw_pane[i].pane)->setFontColor(*(JUtility::TColor*)&g_messageHIO.field_0x11, *(JUtility::TColor*)&g_messageHIO.field_0x11);
        ((J2DTextBox*)i_Msg->rubySdw_pane[i].pane)->setFontColor(*(JUtility::TColor*)&g_messageHIO.field_0x11, *(JUtility::TColor*)&g_messageHIO.field_0x11);
    
        ((J2DTextBox*)i_Msg->text_pane[i].pane)->setWhite(*(JUtility::TColor*)&g_messageHIO.field_0x9);
        ((J2DTextBox*)i_Msg->ruby_pane[i].pane)->setWhite(*(JUtility::TColor*)&g_messageHIO.field_0x21);
        ((J2DTextBox*)i_Msg->textSdw_pane[i].pane)->setWhite(*(JUtility::TColor*)&g_messageHIO.field_0x15);
        ((J2DTextBox*)i_Msg->rubySdw_pane[i].pane)->setWhite(*(JUtility::TColor*)&g_messageHIO.field_0x15);

        ((J2DTextBox*)i_Msg->text_pane[i].pane)->setBlack(*(JUtility::TColor*)&g_messageHIO.field_0xd);
        ((J2DTextBox*)i_Msg->ruby_pane[i].pane)->setBlack(*(JUtility::TColor*)&g_messageHIO.field_0x25);
        ((J2DTextBox*)i_Msg->textSdw_pane[i].pane)->setBlack(*(JUtility::TColor*)&g_messageHIO.field_0x19);
        ((J2DTextBox*)i_Msg->rubySdw_pane[i].pane)->setBlack(*(JUtility::TColor*)&g_messageHIO.field_0x19);
    }

    for (int i = 0; i < 3; i++) {
        if (dComIfGs_getOptRuby()) {
            i_Msg->ruby_pane[i].pane->hide();
            i_Msg->rubySdw_pane[i].pane->hide();
        } else {
            if (i_Msg->ruby_pane[1].pane->isVisible()) {
                i_Msg->ruby_pane[i].pane->show();
            }

            if (i_Msg->rubySdw_pane[i].pane->isVisible()) {
                i_Msg->rubySdw_pane[i].pane->show();
            }
        }
    }

    dComIfGp_setMesgStatus(i_Msg->msg.mStatus);
    return TRUE;
}

/* 801EA7C4-801EA7CC       .text dMsg2_IsDelete__FP14sub_msg2_class */
static BOOL dMsg2_IsDelete(sub_msg2_class* i_Msg) {
    return TRUE;
}

/* 801EA7CC-801EA97C       .text dMsg2_Delete__FP14sub_msg2_class */
static BOOL dMsg2_Delete(sub_msg2_class* i_Msg) {
    dComIfGp_setMesgStatus(0);
    dComIfG_setBrightness(0xFF);

    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

    for (int i = 0; i < 3; i++) {
        delete sScreen2[i];
    }

    i_Msg->Heap->free(i_Msg->Tex[0]);
    i_Msg->Heap->free(i_Msg->Tex[1]);
    mDoExt_removeMesgFont();
    mDoExt_removeRubyFont();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            delete bbutton_icon[j][i];
            delete bbutton_kage[j][i];
        }

        i_Msg->Heap->free(i_Msg->output_text[i]);
        i_Msg->Heap->free(i_Msg->output_ruby[i]);
        i_Msg->Heap->free(i_Msg->output_textSdw[i]);
        i_Msg->Heap->free(i_Msg->output_rubySdw[i]);
    }

    dComIfGp_getMsgArchive()->removeResourceAll();
    i_Msg->Heap->freeAll();
    dComIfGp_setHeapLockFlag(0);
    mDoExt_setCurrentHeap(heap);
    return TRUE;
}

/* 801EA97C-801EAFC0       .text dMsg2_Create__FP9msg_class */
static cPhs_State dMsg2_Create(msg_class* i_this) {
    sub_msg2_class* i_Msg = (sub_msg2_class*)i_this;

    if (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 8) {
        return cPhs_INIT_e;
    }

    i_Msg->Heap = dComIfGp_getExpHeap2D();
    dComIfGp_setHeapLockFlag(8);
    JKRHeap* heap = mDoExt_setCurrentHeap(i_Msg->Heap);

    for (u8 i = 0; i < 3; i++) {
        sScreen2[i] = new J2DScreen();
        sScreen2[i]->set("hukidashi_02.blo", dComIfGp_getMsgArchive());
    }

    i_Msg->Tex[0] = (ResTIMG*)i_Msg->Heap->alloc(0x11800, 0x20);
    JUT_ASSERT(VERSION_SELECT(2225, 2239, 2274, 2276), i_Msg->Tex[0] != NULL);

    i_Msg->Tex[1] = (ResTIMG*)i_Msg->Heap->alloc(0x11800, 0x20);
    JUT_ASSERT(VERSION_SELECT(2227, 2241, 2276, 2278), i_Msg->Tex[1] != NULL);

    dMsg2_fontdataInit(i_Msg);

    for (u8 i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            bbutton_icon[j][i] = new J2DPicture("font_07_02.bti");
            bbutton_kage[j][i] = new J2DPicture("font_07_02.bti");
            fopMsgM_blendInit(bbutton_icon[j][i], "font_00.bti");
            fopMsgM_blendInit(bbutton_kage[j][i], "font_00.bti");
            
            bbutton_icon[j][i]->hide();
            bbutton_kage[j][i]->hide();
            bbutton_icon[j][i]->setAlpha(0);
            bbutton_kage[j][i]->setAlpha(0);

            bbuttonTimer[j][i] = -1;
        }
    }

    for (u8 i = 0; i < 3; i++) {
        i_Msg->output_text[i] = (char*)i_Msg->Heap->alloc(1001, 4);
        JUT_ASSERT(VERSION_SELECT(2250, 2264, 2299, 2301), i_Msg->output_text[i] != NULL);

        i_Msg->output_ruby[i] = (char*)i_Msg->Heap->alloc(1001, 4);
        JUT_ASSERT(VERSION_SELECT(2253, 2267, 2302, 2304), i_Msg->output_ruby[i] != NULL);

        i_Msg->output_textSdw[i] = (char*)i_Msg->Heap->alloc(1001, 4);
        JUT_ASSERT(VERSION_SELECT(2256, 2270, 2305, 2307), i_Msg->output_textSdw[i] != NULL);

        i_Msg->output_rubySdw[i] = (char*)i_Msg->Heap->alloc(1001, 4);
        JUT_ASSERT(VERSION_SELECT(2259, 2273, 2308, 2310), i_Msg->output_rubySdw[i] != NULL);
    }

    mDoExt_setCurrentHeap(heap);

    if (i_this->mMsgNo == 0x33A && dComIfGs_isEventBit(0x2D80)) {
        i_this->mMsgNo = 0x33B;
    }

    i_Msg->head_p = i_Msg->msgGet.getMesgHeader(i_this->mMsgNo);
    JUT_ASSERT(VERSION_SELECT(2275, 2289, 2324, 2326), i_Msg->head_p);

    i_Msg->message = (char*)i_Msg->msgGet.getMessage(i_Msg->head_p);
    i_Msg->mesgEntry = i_Msg->msgGet.getMesgEntry(i_Msg->head_p);
    i_Msg->mesgNumber = i_Msg->msgGet.getMesgNumber();
    i_this->mStatus = 2;

    dMsg2_multiTexInit(i_Msg);

    for (u8 i = 0; i < 3; i++) {
        dMsg2_screenDataInit(i_Msg, i);
        dMsg2_screenDataSet(i_Msg, i);
        dMsg2_messagePaneHide(i_Msg, i);
    }

    dMsg2_ScreenDataValueInit(i_Msg);
    dMsg2_stickInfoInit(i_Msg);
    i_Msg->field_0xec0 = 0;
    i_Msg->field_0xe9c = 2;
    i_Msg->field_0xe9d = 0;
    i_Msg->field_0xe9e = 1;

    dMsg2_popSpeed = g_messageHIO.field_0x3b;
    message.setActorP(i_Msg);
    dComIfGp_setMesgStatus(i_this->mStatus);
    return cPhs_COMPLEATE_e;
}

static msg_method_class l_dMsg2_Method = {
    (process_method_func)dMsg2_Create,
    (process_method_func)dMsg2_Delete,
    (process_method_func)dMsg2_Execute,
    (process_method_func)dMsg2_IsDelete,
    (process_method_func)dMsg2_Draw,
};

msg_process_profile_definition g_profile_MSG2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 12,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MSG2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sub_msg2_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Draw Prio    */ fpcDwPi_MSG2_e,
    /* Msg SubMtd   */ &l_dMsg2_Method,
};
