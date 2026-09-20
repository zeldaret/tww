#include "d/dolzel.h" // IWYU pragma: keep
#include "JSystem/J2DGraph/J2DPane.h"
#include "d/d_s_open.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter.h"
#include "f_op/f_op_msg_mng.h"
#include "f_op/f_op_overlap_mng.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JUtility/JUTAssert.h"

s8 dScnOpen_message_timer_table[22] = {
    7, 6, 7, 6,
    6, 7, 9, 8,
    9, 6, 7, 5,
    8, 6, 8, 7,
    7, 9, 10, 10,
    7, 7,
};

/* 80232EFC-8023334C       .text set_message__18dScnOpen_message_cFUli */
void dScnOpen_message_c::set_message(u32 i_msgNo, int param_1) {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);
    fopMsgM_msgGet_c msgGet;

    mesgStatus = fopMsgStts_MSG_TYPING_e;
    if (i_msgNo == 0) {
        mProc = 4;
        msgNo = 0x579;
    } else {
        mProc = 0;
        msgNo = i_msgNo;
    }

    if (param_1 != 0) {
        field_0x22ec = param_1 - 1;
    }

    alpha = 0.0f;
    mTimer = 0;
    mTimerMax = dScnOpen_message_timer_table[msgNo - 0x579] * 30;
    field_0x22e8 = 0;

    strcpy(msg1, "");
    strcpy(msg2, "");
    strcpy(msg3, "");
    strcpy(msg4, "");

#if VERSION >= VERSION_USA
    J2DTextBox::TFontSize fontSize;
    fontSize.mSizeX = g_msgHIO.field_0x70;
    fontSize.mSizeY = g_msgHIO.field_0x70;

    tTextBox->setLineSpace(28.0f);
    rTextBox->setLineSpace(28.0f);
    tTextBox->setFontSize(fontSize);
#else
    J2DTextBox::TFontSize tFontSize;
    tTextBox->getFontSize(tFontSize);
    f32 fontSize = tFontSize.mSizeX;
#endif

    J2DTextBox::TFontSize rFontSize;
    rTextBox->getFontSize(rFontSize);
    f32 rubyFontSize = rFontSize.mSizeX;

    mesg_header* head_p = msgGet.getMesgHeader(msgNo);
    JUT_ASSERT(VERSION_SELECT(84, 85, 93, 93), head_p);

    const char* message = msgGet.getMessage(head_p);
    msgEntry = msgGet.getMesgEntry(head_p);
    msgDataProc.dataInit();
    msgDataProc.bmgData = message;
    msgDataProc.setOutMessage(msg1, msg2, msg3, msg4);
    msgDataProc.setFont(tFont);
    msgDataProc.setRubyFont(rFont);
    msgDataProc.setCharSpace(tTextBox->getCharSpace());
    msgDataProc.setRubyCharSpace(rTextBox->getCharSpace());
    msgDataProc.setLineSpace(tTextBox->getLineSpace());
    msgDataProc.setMesgEntry(&msgEntry);
#if VERSION >= VERSION_USA
    msgDataProc.setFontSize(fontSize.mSizeX);
#else
    msgDataProc.setFontSize(fontSize);
#endif
    msgDataProc.setRubyFontSize(rubyFontSize);
    msgDataProc.setLineWidth(tTextBox->getWidth());
    msgDataProc.setCenterLineWidth(486);
    msgDataProc.setSendSpeed(2);
    msgDataProc.setSpaceTimer(0);
    msgDataProc.stringLength();
    msgDataProc.stringShift();

    s16 temp_r3 = msgDataProc.getLineCount();
    msgDataProc.setLineCount(0);

    f32 temp_f1 = ((msgEntry.field_0x16 - temp_r3) - 1) * (tTextBox->getLineSpace() / 2);
    tTextBox->shiftSet(0.0f, temp_f1);
    rTextBox->shiftSet(0.0f, temp_f1 - 1.0f);

    mDoExt_setCurrentHeap(old_heap);
}

/* 8023334C-80233524       .text exec__18dScnOpen_message_cFv */
void dScnOpen_message_c::exec() {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);

    if (mesgStatus != fopMsgStts_CLOSE_WAIT_e && mesgStatus != fopMsgStts_MSG_DISPLAYED_e) {
        msgDataProc.stringSet();
        mesgStatus = msgDataProc.mesgStatus;
        tTextBox->setString(msg1);
        rTextBox->setString(msg2);

        #if VERSION >= VERSION_USA
        rTextBox->hide();
        #endif
    }

    switch (mProc) {
    case 0:
        if (alpha >= 1.0f) {
            mTimer = 0;
            mProc = 1;
            alpha = 1.0f;
        } else {
            alpha += 0.1f;
        }
        break;
    case 1:
        if (mTimer >= mTimerMax) {
            mTimer = 0;
            mProc = 2;
            alpha = 1.0f;
        } else {
            mTimer++;
        }
        break;
    case 2:
        if (alpha <= 0.0f) {
            mTimer = 0;
            alpha = 0.0f;

            if (field_0x22ec == 0) {
                field_0x22e8 = 1;
                mProc = 4;
            } else {
                mProc = 3;
                field_0x22ec--;
            }
        } else {
            alpha -= 0.1f;
        }
        break;
    case 3:
        if (mTimer >= 45) {
            set_message(msgNo + 1, 0);
            mProc = 0;
            mTimer = 0;
        } else {
            mTimer++;
        }
        break;
    case 4:
        break;
    }

    mDoExt_setCurrentHeap(old_heap);
}

/* 80233524-80233620       .text __ct__18dScnOpen_message_cFP10JKRExpHeap */
dScnOpen_message_c::dScnOpen_message_c(JKRExpHeap* heap) {
    exp_heap = heap;
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);

    tFont = mDoExt_getMesgFont();
    JUT_ASSERT(VERSION_SELECT(191, 192, 205, 205), tFont != NULL);

    rFont = mDoExt_getRubyFont();
    JUT_ASSERT(VERSION_SELECT(193, 194, 208, 208), rFont != NULL);

    mDoExt_setCurrentHeap(old_heap);
}

/* 80233620-80233698       .text __dt__18dScnOpen_message_cFv */
dScnOpen_message_c::~dScnOpen_message_c() {
    mDoExt_removeMesgFont();
    mDoExt_removeRubyFont();
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);
    mDoExt_setCurrentHeap(old_heap);
}

void dScnOpen_message_c::set_pane_pointer(J2DPane* tx1, J2DPane* tx2) {
    tTextBox = (J2DTextBox*)tx1;
    rTextBox = (J2DTextBox*)tx2;
    tTextBox->setFont(tFont);
    rTextBox->setFont(rFont);
    rTextBox->setLineSpace(tTextBox->getLineSpace());
}

enum {
    PANE_d1,
    PANE_d2,
    PANE_d3,
    PANE_d4,
    PANE_d42,
    PANE_d5,
    PANE_d6,
    PANE_mak1,
    PANE_mak2,
    PANE_tx1,
    PANE_tx2,
};

/* 80233698-80233B0C       .text __ct__15dScnOpen_proc_cFv */
dScnOpen_proc_c::dScnOpen_proc_c() {
    exp_heap = fopMsgM_createExpHeap(0x20000);
    JUT_ASSERT(VERSION_SELECT(206, 207, 226, 226), exp_heap != NULL);

    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);

    m_Screen = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(211, 212, 231, 231), m_Screen != NULL);

    m_message = new dScnOpen_message_c(exp_heap);
    JUT_ASSERT(VERSION_SELECT(213, 214, 233, 233), m_message != NULL);

    dRes_info_c* resInfo = dComIfG_getObjectResInfo("Opening");
    JUT_ASSERT(VERSION_SELECT(215, 216, 235, 235), resInfo != NULL);

    m_Screen->set("Opening.blo", resInfo->getArchive());
    pane2d[PANE_d1] = m_Screen->search('\0\0d1');
    pane2d[PANE_d2] = m_Screen->search('\0\0d2');
    pane2d[PANE_d3] = m_Screen->search('\0\0d3');
    pane2d[PANE_d4] = m_Screen->search('\0\0d4');
    pane2d[PANE_d42] = m_Screen->search('\0d42');
    pane2d[PANE_d5] = m_Screen->search('\0\0d5');
    pane2d[PANE_d6] = m_Screen->search('\0\0d6');
    pane2d[PANE_mak1] = m_Screen->search('mak1');
    pane2d[PANE_mak2] = m_Screen->search('mak2');
    pane2d[PANE_tx1] = m_Screen->search('\0tx1');
    pane2d[PANE_tx2] = m_Screen->search('\0tx2');

    #if VERSION >= VERSION_USA
    pane2d[PANE_tx1]->move(pane2d[PANE_tx1]->getBounds().i.x, 376.0f);
    #endif

    m_message->set_pane_pointer(pane2d[PANE_tx1], pane2d[PANE_tx2]);

    for (s32 i = 0; i < (s32)ARRAY_SIZE(pane); i++) {
        fopMsgM_setPaneData(&pane[i], pane2d[i]);
        fopMsgM_setNowAlpha(&pane[i], 0.0f);
        fopMsgM_setAlpha(&pane[i]);
    }

    for (s32 i = 7; i < 9; i++) {
        fopMsgM_setNowAlpha(&pane[i], 1.0f);
        fopMsgM_setAlpha(&pane[i]);
    }

    m_message->set_message(0, 0);
    mState = 0;
    mDoExt_setCurrentHeap(old_heap);
}

/* 80233B0C-80233BE4       .text __dt__15dScnOpen_proc_cFv */
dScnOpen_proc_c::~dScnOpen_proc_c() {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);

    delete m_Screen;
    m_Screen = NULL;

    delete m_message;
    m_message = NULL;

    mDoExt_setCurrentHeap(old_heap);
    fopMsgM_destroyExpHeap(exp_heap);
}

/* 80233BE4-802344D8       .text proc_execute__15dScnOpen_proc_cFv */
void dScnOpen_proc_c::proc_execute() {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);
    m_message->exec();

    switch (mState) {
    case 0:
        #if VERSION == VERSION_DEMO
        mDoAud_bgmStreamPrepare(JA_STRM_DEMO_01_01);
        #endif
        mTimer = 0;
        mState = 1;
    case 1:
        if (mTimer >= 90)
            mState = 2;
        else
            mTimer++;

        #if VERSION != VERSION_DEMO
        if (mTimer == 40 && ! fopOvlpM_IsPeek())
            mDoAud_bgmStreamPrepare(JA_STRM_DEMO_01_01);
        #endif
        break;
    case 2:
        mDoAud_bgmStreamPlay();
        m_message->set_message(0x58e, 1);
        fopMsgM_paneTrans(&pane[9], 0.0f, -190.0f);
        fopMsgM_paneTrans(&pane[10], 0.0f, -190.0f);
        mState = 3;
    case 3:
        if (m_message->field_0x22e8 != 0)
            mState = 4;
        break;
    case 4:
        fopMsgM_paneTrans(&pane[9], 0.0f, 0.0f);
        fopMsgM_paneTrans(&pane[10], 0.0f, 0.0f);
        mTimer = 0;
        mState = 5;
    case 5:
        if (mTimer >= 60)
            mState = 6;
        else
            mTimer++;
        break;
    case 6:
        fopMsgM_setNowAlpha(&pane[0], 0.0f);
        mPosX = 0.0f;
        mAlpha = 0.0f;
        mState = 7;
    case 7:
        mPosX -= 0.5719626f;
        mAlpha += 0.067f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 8;
        }
        fopMsgM_paneTrans(&pane[0], 0.0f, mPosX);
        fopMsgM_setNowAlpha(&pane[0], mAlpha);
        break;
    case 8:
        m_message->set_message(0x579, 2);
        fopMsgM_setNowAlpha(&pane[0], 1.0f);
        mState = 9;
    case 9:
        mPosX -= 0.5719626f;
        if (m_message->field_0x22e8 != 0)
            mState = 10;
        fopMsgM_paneTrans(&pane[0], 0.0f, mPosX);
        break;
    case 10:
        fopMsgM_setNowAlpha(&pane[0], 1.0f);
        fopMsgM_setNowAlpha(&pane[1], 0.0f);
        mAlpha = 0;
        mState = 11;
    case 11:
        mPosX -= 0.5719626f;
        mAlpha += 0.0223f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 12;
        }
        fopMsgM_paneTrans(&pane[0], 0.0f, mPosX);
        fopMsgM_setNowAlpha(&pane[0], 1.0f - mAlpha);
        fopMsgM_setNowAlpha(&pane[1], mAlpha);
        break;
    case 12:
        m_message->set_message(0x57b, 3);
        mState = 13;
    case 13:
        if (m_message->field_0x22e8 != 0)
            mState = 14;
        break;
    case 14:
        mAlpha = 1.0f;
        mState = 15;
    case 15:
        mAlpha -= 0.067f;
        if (mAlpha <= 0.0f) {
            mAlpha = 0.0f;
            mState = 16;
        }
        fopMsgM_setNowAlpha(&pane[1], mAlpha);
        break;
    case 16:
        mAlpha = 0.0f;
        mState = 17;
    case 17:
        mAlpha += 0.067f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 18;
        }
        fopMsgM_setNowAlpha(&pane[2], mAlpha);
        break;
    case 18:
        m_message->set_message(0x57e, 2);
        fopMsgM_setNowAlpha(&pane[2], 1.0f);
        mState = 19;
    case 19:
        if (m_message->field_0x22e8 != 0)
            mState = 20;
        break;
    case 20:
        mAlpha = 1.0f;
        mState = 21;
    case 21:
        mAlpha -= 0.067f;
        if (mAlpha <= 0.0f) {
            mAlpha = 0.0f;
            mState = 22;
        }
        fopMsgM_setNowAlpha(&pane[2], mAlpha);
        break;
    case 22:
        mPosX = 0.0f;
        mAlpha = 0.0f;
        mState = 23;
    case 23:
        mPosX -= 0.47482014f;
        mAlpha += 0.067f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 24;
        }
        fopMsgM_paneTrans(&pane[3], mPosX, 0.0f);
        fopMsgM_setNowAlpha(&pane[3], mAlpha);
        fopMsgM_setNowAlpha(&pane[4], mAlpha);
        break;
    case 24:
        m_message->set_message(0x580, 5);
        fopMsgM_setNowAlpha(&pane[3], 1.0f);
        fopMsgM_setNowAlpha(&pane[4], 1.0f);
        mState = 25;
    case 25:
        mPosX -= 0.47482014f;
        if (m_message->field_0x22e8 != 0)
            mState = 26;
        fopMsgM_paneTrans(&pane[3], mPosX, 0.0f);
        break;
    case 26:
        fopMsgM_setNowAlpha(&pane[3], 1.0f);
        fopMsgM_setNowAlpha(&pane[4], 1.0f);
        fopMsgM_setNowAlpha(&pane[5], 0.0f);
        mAlpha = 0.0f;
        mState = 27;
    case 27:
        mPosX -= 0.47482014f;
        mAlpha += 0.0223f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 28;
        }
        fopMsgM_paneTrans(&pane[3], mPosX, 0.0f);
        fopMsgM_setNowAlpha(&pane[3], 1.0f - mAlpha);
        fopMsgM_setNowAlpha(&pane[4], 1.0f - mAlpha);
        fopMsgM_setNowAlpha(&pane[5], mAlpha);
        break;
    case 28:
        m_message->set_message(0x585, 4);
        fopMsgM_setNowAlpha(&pane[5], 1.0f);
        mState = 29;
    case 29:
        if (m_message->field_0x22e8 != 0)
            mState = 30;
        break;
    case 30:
        mAlpha = 1.0f;
        mState = 31;
    case 31:
        mAlpha -= 0.067f;
        if (mAlpha <= 0.0f) {
            mAlpha = 0.0f;
            mState = 32;
        }
        fopMsgM_setNowAlpha(&pane[5], mAlpha);
        break;
    case 32:
        mTimer = 0;
        mState = 33;
    case 33:
        if (mTimer >= 90)
            mState = 34;
        else
            mTimer++;
        break;
    case 34:
        m_message->set_message(0x589, 1);
        fopMsgM_paneTrans(&pane[9], 0.0f, -190.0f);
        fopMsgM_paneTrans(&pane[10], 0.0f, -190.0f);
        mState = 35;
    case 35:
        if (m_message->field_0x22e8 != 0)
            mState = 36;
        break;
    case 36:
        fopMsgM_paneTrans(&pane[9], 0.0f, 0.0f);
        fopMsgM_paneTrans(&pane[10], 0.0f, 0.0f);
        mTimer = 0;
        mState = 37;
    case 37:
        if (mTimer >= 60)
            mState = 38;
        else
            mTimer++;
        break;
    case 38:
        mScale = 2.0f;
        mAlpha = 0.0f;
        mState = 39;
    case 39:
        mScale -= 0.0007633588f;
        mAlpha += 0.067f;
        if (mAlpha >= 1.0f) {
            mAlpha = 1.0f;
            mState = 40;
        }
        fopMsgM_setNowAlpha(&pane[6], mAlpha);
        fopMsgM_paneScaleXY(&pane[6], mScale);
        break;
    case 40:
        m_message->set_message(0x58a, 4);
        fopMsgM_setNowAlpha(&pane[6], 1.0f);
        mState = 41;
    case 41:
        mScale -= 0.0007633588f;
        if (mScale < 1.0f)
            mScale = 1.0f;
        fopMsgM_paneScaleXY(&pane[6], mScale);
        if (m_message->field_0x22e8 != 0)
            mState = 42;
        break;
    case 42:
        mAlpha = 1.0f;
        mState = 43;
    case 43:
        mAlpha -= 0.067f;
        if (mAlpha <= 0.0f) {
            mAlpha = 0.0f;
            mState = 44;
        }
        fopMsgM_setNowAlpha(&pane[6], mAlpha);
        break;
    case 44:
        break;
    }

    f32 alpha = m_message->alpha;
    fopMsgM_setNowAlpha(&pane[9], alpha);
    fopMsgM_setNowAlpha(&pane[10], alpha);

    for (s32 i = 0; i < (s32)ARRAY_SIZE(pane); i++)
        fopMsgM_setAlpha(&pane[i]); 

    mDoExt_setCurrentHeap(old_heap);
}

/* 802344D8-80234550       .text proc_draw__15dScnOpen_proc_cFv */
void dScnOpen_proc_c::proc_draw() {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(exp_heap);
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    m_Screen->draw(0.0f, 0.0f, graf);
    mDoExt_setCurrentHeap(old_heap);
}

/* 80234550-80234570       .text draw__15dScnOpen_proc_cFv */
void dScnOpen_proc_c::draw() {
    proc_draw();
}
