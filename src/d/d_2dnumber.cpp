#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_2dnumber.h"
#include "d/d_meter.h"
#include "d/d_com_inf_game.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include <stdio.h>

/* 800C8498-800C84B4       .text __ct__16dDlst_2DNumber_cFv */
dDlst_2DNumber_c::dDlst_2DNumber_c() {}

/* 800C84B4-800C8510       .text __dt__16dDlst_2DNumber_cFv */
dDlst_2DNumber_c::~dDlst_2DNumber_c() {}

/* 800C8510-800C8644       .text init__16dDlst_2DNumber_cFissssUc */
bool dDlst_2DNumber_c::init(int digitNum, s16 x, s16 y, s16 w, s16 h, u8 flag) {
    mDigitNum = digitNum;
    mFlag = flag;
    mWidth = w;
    mHeight = h;

    for (s32 i = 0; i < mDigitNum; i++) {
        mNum[i] = new J2DPicture("rupy_num_00.bti");
        if (mNum[i] == NULL)
            return false;

        mPos[i].x = x - w * i;
        mPos[i].y = y;
    }

    return true;
}

/* 800C8644-800C874C       .text draw__16dDlst_2DNumber_cFv */
void dDlst_2DNumber_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    s32 value = mValue;
    
    graf->setPort();
    if (mFlag & 2)
        return;

    for (s32 i = 0; i < mDigitNum; i++) {
        if (i != 0 && value == 0 && !(mFlag & 1))
            break;

        s32 digit = value % 10;
        value /= 10;

        char buf[16];
        sprintf(buf, "rupy_num_%02d.bti", digit);
        mNum[i]->changeTexture(buf, 0);
        mNum[i]->draw(mPos[i].x, mPos[i].y, mWidth, mHeight, false, false, false);
    }
}

/* 800C874C-800C8944       .text init__18dDlst_2DMinigame_cFP7ResTIMGP7ResTIMG */
bool dDlst_2DMinigame_c::init(ResTIMG* title, ResTIMG* score) {
    mTitle = new J2DPicture(title);
    if (mTitle == NULL)
        return false;

    mScore = new J2DPicture(score);
    if (mScore == NULL)
        return false;

    mScoreShadow = new J2DPicture(score);
    if (mScoreShadow == NULL)
        return false;

    mTitleSize.x = title->width * 1.33f;
    mTitleSize.y = title->height * 1.33f;
    mScoreSize.x = score->width * 1.16f;
    mScoreSize.y = score->height * 1.16f;

    mScoreShadow->setCornerColor(0x000000FF);
    return true;
}

/* 800C8944-800C8A00       .text draw__18dDlst_2DMinigame_cFv */
void dDlst_2DMinigame_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    mScoreShadow->draw(mScorePos.x + 4.0f, mScorePos.y + 4.0f, mScoreSize.x, mScoreSize.y, false, false, false);
    mScore->draw(mScorePos.x, mScorePos.y, mScoreSize.x, mScoreSize.y, false, false, false);
    mTitle->draw(mTitlePos.x, mTitlePos.y, mTitleSize.x, mTitleSize.y, false, false, false);
}

/* 800C8A00-800C8FAC       .text init__17dDlst_2DBattery_cFP7ResTIMGP7ResTIMGP7ResTIMGP7ResTIMG */
BOOL dDlst_2DBattery_c::init(ResTIMG* rule, ResTIMG* battery, ResTIMG* batteryBase, ResTIMG* degree) {
    mRule = new J2DPicture(rule);
    if (mRule == NULL)
        return FALSE;

    mRuleSize.x = rule->width;
    mRuleSize.y = rule->height;

    mBattery = new J2DPicture(battery);
    if (mBattery == NULL)
        return FALSE;

    mBatterySize.x = battery->width;
    mBatterySize.y = battery->height;

    mBatteryBase = new J2DPicture(batteryBase);
    if (mBatteryBase == NULL)
        return FALSE;

    mBatteryBaseSize.x = batteryBase->width;
    mBatteryBaseSize.y = batteryBase->height;

    for (s32 i = 0; i < 2; i++) {
        mNum[0][i] = new J2DPicture(degree);
        if (mNum[0][i] == NULL)
            return FALSE;

        mNum[1][i] = new J2DPicture("rupy_num_00.bti");
        if (mNum[1][i] == NULL)
            return FALSE;

        mNum[2][i] = new J2DPicture("rupy_num_00.bti");
        if (mNum[2][i] == NULL)
            return FALSE;
    }

    mBattery->setAlpha(200);

    mNumSize.x = degree->width;
    mNumSize.y = degree->height;

    mPicturePos.x = mPicturePos.y = 0.0f;
    mNumPos.x = 551.0f;
    mNumPos.y = mBatteryBaseSize.y / 2.0f + 399.0f;

    mRule->setAlpha(128);
    mRule->setWhite(0xFFFFFFFF);
    mRule->setBlack(0xFFFFFF00);

    mNum[0][0]->setWhite(0xFFC800FF);
    mNum[0][1]->setCornerColor(0x000000FF);
    mNum[0][1]->setAlpha(80);

    mNum[1][0]->setWhite(0xFFC800FF);
    mNum[1][1]->setCornerColor(0x000000FF);
    mNum[1][1]->setAlpha(80);

    mNum[2][0]->setWhite(0xFFC800FF);
    mNum[2][1]->setCornerColor(0x000000FF);
    mNum[2][1]->setAlpha(80);

    mRotation = 20.0f;
    return TRUE;
}

/* 800C8FAC-800C90F0       .text setRotate__17dDlst_2DBattery_cFf */
void dDlst_2DBattery_c::setRotate(f32 rot) {
    // calculate the angle text
    f32 angle = ((rot - 22.5f) / 22.5f) * 35.0f + 15.0f;
    char buf[16];
    sprintf(buf, "rupy_num_%02d.bti", (int)(angle + 0.5f) / 10);
    mNum[2][0]->changeTexture(buf, 0);
    mNum[2][1]->changeTexture(buf, 0);
    sprintf(buf, "rupy_num_%02d.bti", (int)(angle + 0.5f) % 10);
    mNum[1][0]->changeTexture(buf, 0);
    mNum[1][1]->changeTexture(buf, 0);

    // calculate the visual angle
    if (rot < 20.0f) {
        rot = 345.0f;
    } else if (rot > 45.0f) {
        rot = 310.0f;
    } else {
        rot = 360.0f - ((rot - 20.0f) * 1.4f + 15.0f);
    }
    mRotation = rot;
}

/* 800C90F0-800C9348       .text draw__17dDlst_2DBattery_cFv */
void dDlst_2DBattery_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    mBattery->rotate(mBatterySize.x, mBatterySize.y / 2.0f, ROTATE_Z, mRotation);

    mRule->draw(mPicturePos.x + 519.0f, mPicturePos.y + 367.0f, mRuleSize.x, mRuleSize.y, false, false, false);
    mBattery->draw(mPicturePos.x + 498.0f, mPicturePos.y + 397.0f, mBatterySize.x, mBatterySize.y, false, false, false);
    mBatteryBase->draw(mPicturePos.x + 551.0f, mPicturePos.y + 399.0f, mBatteryBaseSize.x, mBatteryBaseSize.y, false, false, false);

    const f32 shadowOffs = 4.0f;

    mNum[2][1]->draw(mNumPos.x + shadowOffs + 10.0f, mNumPos.y + shadowOffs, mNumSize.x, mNumSize.y, false, false, false);
    mNum[1][1]->draw(mNumPos.x + mNumSize.x + shadowOffs + 5.0f, mNumPos.y + shadowOffs, mNumSize.x, mNumSize.y, false, false, false);
    mNum[0][1]->draw(mNumPos.x + mNumSize.x * 2.0f + shadowOffs, mNumPos.y + shadowOffs, mNumSize.x, mNumSize.y, false, false, false);

    mNum[2][0]->draw(mNumPos.x + 10.0f, mNumPos.y, mNumSize.x, mNumSize.y, false, false, false);
    mNum[1][0]->draw(mNumPos.x + mNumSize.x + 5.0f, mNumPos.y, mNumSize.x, mNumSize.y, false, false, false);
    mNum[0][0]->draw(mNumPos.x + mNumSize.x * 2.0f, mNumPos.y, mNumSize.x, mNumSize.y, false, false, false);
}

/* 800C9348-800C946C       .text init__16dDlst_2DObject_cFP7ResTIMGP7ResTIMG */
BOOL dDlst_2DObject_c::init(ResTIMG* img1, ResTIMG* img2) {
    mPicture[0] = new J2DPicture(img1);
    if (mPicture[0] == NULL)
        return FALSE;
    mSize[0].x = img1->width;
    mSize[0].y = img1->height;

    mPicture[1] = new J2DPicture(img2);
    if (mPicture[1] == NULL)
        return FALSE;
    mSize[1].x = img2->width;
    mSize[1].y = img2->height;
    mScale = 1.0f;
    mCurrentNo = 0;

    return TRUE;
}

/* 800C946C-800C9520       .text draw__16dDlst_2DObject_cFv */
void dDlst_2DObject_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    if (mCurrentNo == 0) {
        mPicture[0]->draw(mPos.x, mPos.y, mSize[0].x * mScale, mSize[0].y * mScale, false, false, false);
    } else {
        mPicture[1]->draw(mPos.x, mPos.y, mSize[1].x * mScale, mSize[1].y * mScale, false, false, false);
    }
}

/* 800C9520-800C9690       .text initial__17dDlst_2DOutFont_cFv */
void dDlst_2DOutFont_c::initial() {
    m68 = 0.0f;
    mIconNum = 0;
    mPosTopLeftY = 0.0f;
    mPosTopLeftX = 0.0f;
    m82 = 0;
    m28 = NULL;

    if (mpTextBox != NULL) {
        mpTextBox->show();
#if VERSION >= VERSION_USA
        mpTextBox->getFontSize(mFontSize);
        m6C = mFontSize.mSizeX;
#else
        J2DTextBox::TFontSize fontSize;
        mpTextBox->getFontSize(fontSize);
        m6C = fontSize.mSizeX;
#endif
        mCharSpace = mpTextBox->getCharSpace();
        m28 = m24;
    }

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            m44[i] = 0.0f;
            m38[i] = 0.0f;
            m5C[i] = 0.0f;
            m50[i] = 0.0f;
            
            mpPic[i]->hide();
            mpPic[i]->rotate(0.0f, 0.0f, ROTATE_Z, 0.0f);
            
            #if VERSION >= VERSION_USA
            if (m74) {
                mpPic[i]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mpPic[i]->resize(m6C, m6C);
            }

            m7C[i] = 0;
            mIconNo[i] = fopMsgM_Icon_A_BUTTON_e;
            m76[i] = -1;
        }
    }
}

/* 800C9690-800C976C       .text setPane__17dDlst_2DOutFont_cFP7JUTFontP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_class */
void dDlst_2DOutFont_c::setPane(JUTFont* i_font, fopMsgM_pane_class* i_textPane, fopMsgM_pane_class* i_pic1, fopMsgM_pane_class* i_pic2, fopMsgM_pane_class* i_pic3) {
    mpFont = i_font;
    mpTextBox = (J2DTextBox*)i_textPane->pane;

    mpPic[0] = NULL;
    mpPic[1] = NULL;
    mpPic[2] = NULL;
    if (i_pic1 != NULL) {
        mpPic[0] = (J2DPicture*)i_pic1->pane;
    }
    if (i_pic2 != NULL) {
        mpPic[1] = (J2DPicture*)i_pic2->pane;
    }
    if (i_pic3 != NULL) {
        mpPic[2] = (J2DPicture*)i_pic3->pane;
    }

    m24 = NULL;
    initial();

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            mpPic[i]->changeTexture("font_07_02.bti", 0);
            mpPic[i]->append("font_07_02.bti", 1.0f);
        }
    }
}

/* 800C976C-800C9844       .text setPaneEx__17dDlst_2DOutFont_cFP7JUTFontP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classPc */
void dDlst_2DOutFont_c::setPaneEx(JUTFont* i_font, fopMsgM_pane_class* i_textPane, fopMsgM_pane_class* i_pic1, fopMsgM_pane_class* i_pic2, fopMsgM_pane_class* i_pic3, char* param_5) {
    mpFont = i_font;
    mpTextBox = (J2DTextBox*)i_textPane->pane;

    mpPic[0] = NULL;
    mpPic[1] = NULL;
    mpPic[2] = NULL;
    if (i_pic1 != NULL) {
        mpPic[0] = (J2DPicture*)i_pic1->pane;
    }
    if (i_pic2 != NULL) {
        mpPic[1] = (J2DPicture*)i_pic2->pane;
    }
    if (i_pic3 != NULL) {
        mpPic[2] = (J2DPicture*)i_pic3->pane;
    }

    m24 = param_5;
    initial();

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            mpPic[i]->changeTexture("font_07_02.bti", 0);
            mpPic[i]->append("font_07_02.bti", 1.0f);
        }
    }
}

/* 800C9844-800C9854       .text setRuby__17dDlst_2DOutFont_cFP7JUTFontP18fopMsgM_pane_class */
void dDlst_2DOutFont_c::setRuby(JUTFont* font, fopMsgM_pane_class* pane) {
    mpRubyFont = font;
    mpRubyTextBox = (J2DTextBox*)pane->pane;
}

/* 800C9854-800C9864       .text setRubyEx__17dDlst_2DOutFont_cFP7JUTFontP18fopMsgM_pane_classPc */
void dDlst_2DOutFont_c::setRubyEx(JUTFont* font, fopMsgM_pane_class* pane, char*) {
    mpRubyFont = font;
    mpRubyTextBox = (J2DTextBox*)pane->pane;
}

/* 800C9864-800C9908       .text charWidth__17dDlst_2DOutFont_cFi */
f32 dDlst_2DOutFont_c::charWidth(int param_0) {
    f32 f1 = mpFont->getWidth(param_0);
    f32 f0 = m6C / mpFont->getCellWidth();
    return mCharSpace + (f1 * f0);
}

/* 800C9908-800C99C0       .text rubyCharWidth__17dDlst_2DOutFont_cFi */
f32 dDlst_2DOutFont_c::rubyCharWidth(int param_0) {
    J2DTextBox::TFontSize fontSize;
    mpRubyTextBox->getFontSize(fontSize);

    f32 f30 = mpRubyFont->getWidth(param_0);
    f32 f0 = fontSize.mSizeX / mpRubyFont->getCellWidth();
    return mCharSpace + (f30 * f0);
}

/* 800C99C0-800C9D5C       .text iconset__17dDlst_2DOutFont_cFiPPc */
f32 dDlst_2DOutFont_c::iconset(int i_iconNo, char** param_1) {
    f32 var_f31 = 0.0f;

    if (mIconNum < 3) {
        m38[mIconNum] = m68;
        mpPic[mIconNum]->show();
        mpPic[mIconNum]->remove();
        mpPic[mIconNum]->append(fopMsgM_outFontTex(i_iconNo), 1.0f);
        mpPic[mIconNum]->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        mpPic[mIconNum]->setWhite(fopMsgM_outFontColorWhite(i_iconNo));
        mpPic[mIconNum]->setBlack(0);
        mIconNo[mIconNum] = i_iconNo;
        m76[mIconNum] = m82;

        switch (i_iconNo) {
        case fopMsgM_Icon_ARROW_LEFT_e:
            m38[mIconNum] += m6C;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 270.0f);
            break;
        case fopMsgM_Icon_ARROW_RIGHT_e:
            m44[mIconNum] += m6C;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 90.0f);
            break;
        case fopMsgM_Icon_ARROW_UP_e:
            m38[mIconNum] += m6C;
            m44[mIconNum] += m6C;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 180.0f);
            break;
        }

        var_f31 = m6C + mCharSpace;

        char buffer[16];
        sprintf(buffer, "\x1B""CR[%d]", (int)(var_f31 + 0.5f));

        char c;
        for (char* var_r5 = buffer; c = *var_r5, c != 0; var_r5++) {
            char* temp_r3 = *param_1;
            *param_1 = *param_1 + 1;
            *temp_r3 = c;
        }

        mIconNum++;
    }

    return var_f31;
}

/* 800C9D5C-800CA8A8       .text messageSet__17dDlst_2DOutFont_cFUl */
// NONMATCHING - various wrong instructions, reg alloc, stack issues
void dDlst_2DOutFont_c::messageSet(u32 i_msgNo) {
    fopMsgM_itemMsgGet_c msgGet;
    mesg_header* head_p = msgGet.getMesgHeader(i_msgNo);
    JUT_ASSERT(DEMO_SELECT(615, 619), head_p);
    const char* message = msgGet.getMessage(head_p);

    char sp104[100];
    char spA0[100];
    char sp6C[52];
    char* dst = sp104;

    f32 var_f31 = 0.0f;
    f32 var_f30 = 0.0f;
    f32 var_f29 = 0.0f;
    int var_r30 = 0;

    initial();
    m88[0] = 0;
    spA0[0] = 0;
    mEC[0] = 0;

    while (*message != '\0') {
        if ((u8)*message == 0x1A) {
            u32 uvar6 = *(u32*)(++message) & 0xFFFFFF;
            if (uvar6 == (0xFF0000 | MsgSpclCode_COLOR)) {
                char sp50[28];
                sprintf(sp50, "\x1b""CC[%08x]\x1bGM[0]", fopMsgM_getColorTable(message[4]));

                for (char* p = sp50; *p != '\0'; p++) {
                    *(dst++) = *p;
                }
            } else if (uvar6 == (0xFF0000 | MsgSpclCode_RUBY)) {
                if (mpRubyFont != NULL) {
                    u8 temp_r3_5 = (u8)message[0];
                    if (temp_r3_5 != 5) {
                        int var_r27 = temp_r3_5 - 6;
                        int i = 0;

                        const char* var_r25 = message + 5;
                        char* var_r24 = sp6C;
                        *sp6C = 0;
                        var_f31 = 0.0f;
                        var_f29 = m68;
                        var_r30 = (u8)message[4];

                        for (; i < var_r27; i += 2) {
                            char temp_r0_2 = var_r25[0];
                            var_r24[0] = temp_r0_2;

                            char temp_r3_6 = var_r25[1];
                            var_r24[1] = temp_r3_6;

                            var_r25 += 2;
                            var_r24 += 2;
                            var_f31 += rubyCharWidth(((u8)temp_r3_6 << 8) | (u8)temp_r0_2);
                        }

                        *var_r24 = 0;
                    }
                }
            } else if (uvar6 == MsgCtrlCode_A_BUTTON) {
                m68 += iconset(fopMsgM_Icon_A_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_B_BUTTON) {
                m68 += iconset(fopMsgM_Icon_B_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_C_STICK) {
                m68 += iconset(fopMsgM_Icon_C_STICK_e, &dst);
            } else if (uvar6 == MsgCtrlCode_L_BUTTON) {
                m68 += iconset(fopMsgM_Icon_L_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_R_BUTTON) {
                m68 += iconset(fopMsgM_Icon_R_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_X_BUTTON) {
                m68 += iconset(fopMsgM_Icon_X_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_Y_BUTTON) {
                m68 += iconset(fopMsgM_Icon_Y_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_Z_BUTTON) {
                m68 += iconset(fopMsgM_Icon_Z_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_DPAD) {
                m68 += iconset(fopMsgM_Icon_DPAD_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_e, &dst);
            } else if (uvar6 == MsgCtrlCode_ARROW_LEFT) {
                m68 += iconset(fopMsgM_Icon_ARROW_LEFT_e, &dst);
            } else if (uvar6 == MsgCtrlCode_ARROW_RIGHT) {
                m68 += iconset(fopMsgM_Icon_ARROW_RIGHT_e, &dst);
            } else if (uvar6 == MsgCtrlCode_ARROW_UP) {
                m68 += iconset(fopMsgM_Icon_ARROW_UP_e, &dst);
            } else if (uvar6 == MsgCtrlCode_ARROW_DOWN) {
                m68 += iconset(fopMsgM_Icon_ARROW_DOWN_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_UP) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_UP_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_DOWN) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_DOWN_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_LEFT) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_LEFT_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_RIGHT) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_RIGHT_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_UP_DOWN) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_UP_DOWN_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MAIN_STICK_LEFT_RIGHT) {
                m68 += iconset(fopMsgM_Icon_MAIN_STICK_LEFT_RIGHT_e, &dst);
            } else if (uvar6 == MsgCtrlCode_FLASHING_A_BUTTON) {
                m68 += iconset(fopMsgM_Icon_FLASHING_A_BUTTON_e, &dst);
            } else if (uvar6 == MsgCtrlCode_HEART) {
                m68 += iconset(fopMsgM_Icon_HEART_e, &dst);
            } else if (uvar6 == MsgCtrlCode_MUSIC_NOTE) {
                m68 += iconset(fopMsgM_Icon_MUSIC_NOTE_e, &dst);
            }

            message += *message - 1;
        } else {
#if VERSION < VERSION_PAL
            int hi_nibble = ((u8)*message >> 4) & 0xF;
            if (hi_nibble == 8 || hi_nibble == 9) {
                char temp_r4_2 = message[0];
                *(dst++) = temp_r4_2;

                char temp_r5 = message[1];
                *(dst++) = temp_r5;

                message += 2;
                m68 += charWidth(((u8)temp_r4_2 << 8) | (u8)temp_r5);

                if (var_r30 != 0) {
                    var_r30--;
                    if (var_r30 == 0) {
                        char sp34[16];

                        f32 temp_f0 = (var_f29 + ((m68 - var_f29) / 2)) - (var_f31 / 2);
                        if (var_f30 < temp_f0) {
                            f32 temp_f28 = temp_f0 - var_f30;
                            sprintf(sp34, "\x1b""CR[%d]", (int)(temp_f28 + 0.5f));
                            strcat(spA0, sp34);
                            var_f30 += temp_f28;
                        } else if (var_f30 > temp_f0) {
                            f32 temp_f28 = var_f30 - temp_f0;
                            sprintf(sp34, "\x1b""CL[%d]", (int)(temp_f28 + 0.5f));
                            strcat(spA0, sp34);
                            var_f30 -= temp_f28;
                        }

                        var_f30 += var_f31;
                        strcat(spA0, sp6C);
                    }
                }
            } else
#endif
            {
                char var_r5_2 = *message;
                *(dst++) = var_r5_2;
                message++;

                if (var_r5_2 == '\n') {
                    char sp24[16];
                    *dst = 0;

                    int temp_r24 = (mpTextBox->getWidth() - m68) / 2;
                    if (temp_r24 > 0) {
                        sprintf(sp24, "\x1b""CR[%d]", temp_r24);

                        for (int i = 0; i < 3; i++) {
                            if (m82 == m76[i]) {
                                m38[i] += temp_r24;
                            }
                        }
                    } else {
                        *sp24 = 0;
                    }

                    strcat(m88, sp24);
                    strcat(m88, sp104);
                    m82++;
                    m68 = 0.0f;
                    var_f30 = 0.0f;

                    dst = sp104;

                    if (mpRubyFont != NULL) {
                        strcat(mEC, sp24);
                        strcat(mEC, spA0);
                        strcat(mEC, "\n");
                        *spA0 = 0;
                    }
                } else {
                    m68 += charWidth(var_r5_2);
                }
            }
        }
    }

    *dst = 0;

    #if VERSION >= VERSION_USA
    var_f29 = 0.0f;
    if (m74 == 0) {
        var_f29 = ((mpTextBox->getHeight() - m6C) - m82 * mpTextBox->getLineSpace()) / 2;
    }
    #else
    var_f29 = ((mpTextBox->getHeight() - m6C) - m82 * mpTextBox->getLineSpace()) / 2;
    #endif

    char sp14[16];
    int temp_r30 = (mpTextBox->getWidth() - m68) / 2;
    if (temp_r30 > 0) {
        sprintf(sp14, "\x1b""CR[%d]", temp_r30);

        for (int i = 0; i < 3; i++) {
            if (m82 == m76[i]) {
                m38[i] += temp_r30;
            }

            if (m76[i] != -1) {
                m44[i] += var_f29 + (m76[i] * mpTextBox->getLineSpace());
            }
        }
    } else {
        *sp14 = 0;
    }

    strcat(m88, sp14);
    strcat(m88, sp104);
    mpTextBox->shiftSet(0.0f, var_f29);

    if (m28 == NULL) {
        mpTextBox->setString(m88);
    } else {
        strcpy(m28, m88);
    }

    if (mpRubyTextBox != NULL) {
        mpRubyTextBox->shiftSet(0.0f, var_f29);
        strcat(mEC, sp14);
        strcat(mEC, spA0);

        if (m2C == NULL) {
            mpRubyTextBox->setString(mEC);
        } else {
            strcpy(m2C, mEC);
        }
    }

    #if VERSION >= VERSION_USA
    if (m74) {
        if (mpTextBox->getWidth() < m68) {
            mFontSize.mSizeX = (int)(mFontSize.mSizeX * (mpTextBox->getWidth() / m68));

            J2DTextBox::TFontSize fontSize = mFontSize;
            mpTextBox->setFontSize(fontSize);
            messageSet(i_msgNo);
        }
    }
    #endif
}

/* 800CA8A8-800CAB5C       .text outFontStickAnime1__17dDlst_2DOutFont_cFUc */
void dDlst_2DOutFont_c::outFontStickAnime1(u8 param_0) {
    s16 var_r29 = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    if (m7C[param_0] < var_r29) {
        outFontStickAnimePiece(param_0, 0);
        #if VERSION >= VERSION_USA
        if (m74) {
            m50[param_0] = 0.0f;
            m5C[param_0] = 0.0f;
            mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
        } else
        #endif
        {
            m50[param_0] = 0.0f;
            m5C[param_0] = 0.0f;
        }
    } else if (m7C[param_0] < var_r29 * 2) {
        outFontStickAnimePiece(param_0, 1);
        #if VERSION >= VERSION_USA
        if (m74) {
            m50[param_0] = mFontSize.mSizeX;
            m5C[param_0] = 0.0f;
            mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
        } else
        #endif
        {
            m50[param_0] = m6C;
            m5C[param_0] = 0.0f;
        }
    } else if (m7C[param_0] < var_r29 * 3) {
        outFontStickAnimePiece(param_0, 2);
        #if VERSION >= VERSION_USA
        if (m74) {
            m50[param_0] = mFontSize.mSizeX;
            m5C[param_0] = mFontSize.mSizeY;
            mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
        } else
        #endif
        {
            m50[param_0] = m6C;
            m5C[param_0] = m6C;
        }
    } else if (m7C[param_0] < var_r29 * 4) {
        outFontStickAnimePiece(param_0, 3);
        #if VERSION >= VERSION_USA
        if (m74) {
            m50[param_0] = 0.0f;
            m5C[param_0] = mFontSize.mSizeY;
            mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
        } else
        #endif
        {
            m50[param_0] = 0.0f;
            m5C[param_0] = m6C;
        }
    }

    if ((m7C[param_0] % var_r29) == 0) {
        mpPic[param_0]->rotate(0.0f, 0.0f, ROTATE_Z, (m7C[param_0] / var_r29) * -90.0f);
    }

    m7C[param_0]++;
    if (m7C[param_0] >= var_r29 * 4) {
        m7C[param_0] = 0;
    }
}

/* 800CAB5C-800CADEC       .text outFontStickAnime2__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnime2(u8 param_0, u8 param_1) {
    s16 var_r29 = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    if (m7C[param_0] < var_r29) {
        outFontStickAnimePiece(param_0, 0);
        
        switch (param_1) {
        case 0:
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = 0.0f;
                m5C[param_0] = 0.0f;
                mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                m50[param_0] = 0.0f;
                m5C[param_0] = 0.0f;
            }
            break;
        case 1:
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = mFontSize.mSizeX;
                m5C[param_0] = 0.0f;
                mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                m50[param_0] = m6C;
                m5C[param_0] = 0.0f;
            }
            break;
        case 2:
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = mFontSize.mSizeX;
                m5C[param_0] = mFontSize.mSizeY;
                mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                m50[param_0] = m6C;
                m5C[param_0] = m6C;
            }
            break;
        case 3:
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = 0.0f;
                m5C[param_0] = mFontSize.mSizeY;
                mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                m50[param_0] = 0.0f;
                m5C[param_0] = m6C;
            }
            break;
        }
    }

    mpPic[param_0]->rotate(0.0f, 0.0f, ROTATE_Z, param_1 * -90.0f);

    m7C[param_0]++;
    if (m7C[param_0] >= var_r29) {
        m7C[param_0] = 0;
    }
}

/* 800CADEC-800CB0C0       .text outFontStickAnime3__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnime3(u8 param_0, u8 param_1) {
    s16 var_r29 = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;

    int var_r0;
    if (param_1 == 0) {
        if (m7C[param_0] < var_r29) {
            outFontStickAnimePiece(param_0, 0);
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = mFontSize.mSizeX;
                m5C[param_0] = 0.0f;
                mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                m50[param_0] = m6C;
                m5C[param_0] = 0.0f;
            }
            var_r0 = 1;
        } else if (m7C[param_0] < var_r29 * 2) {
            outFontStickAnimePiece(param_0, 1);
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = 0.0f;
                m5C[param_0] = mFontSize.mSizeY;
                mpPic[param_0]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                m50[param_0] = 0.0f;
                m5C[param_0] = m6C;
            }
            var_r0 = 3;
        }
    } else {
        if (m7C[param_0] < var_r29) {
            outFontStickAnimePiece(param_0, 0);
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = 0.0f;
                m5C[param_0] = 0.0f;
                mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                m50[param_0] = 0.0f;
                m5C[param_0] = 0.0f;
            }
            var_r0 = 0;
        } else if (m7C[param_0] < var_r29 * 2) {
            outFontStickAnimePiece(param_0, 1);
            #if VERSION >= VERSION_USA
            if (m74) {
                m50[param_0] = mFontSize.mSizeX;
                m5C[param_0] = mFontSize.mSizeY;
                mpPic[param_0]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                m50[param_0] = m6C;
                m5C[param_0] = m6C;
            }
            var_r0 = 2;
        }
    }

    mpPic[param_0]->rotate(0.0f, 0.0f, ROTATE_Z, var_r0 * -90.0f);

    m7C[param_0]++;
    if (m7C[param_0] >= var_r29 * 2) {
        m7C[param_0] = 0;
    }
}

/* 800CB0C0-800CB2E0       .text outFontStickAnimePiece__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnimePiece(u8 param_0, u8 param_1) {
    s16 temp_r0 = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    s16 temp_r0_2 = g_msgHIO.field_0x88 + (temp_r0 * param_1);
    s16 temp_r0_3 = g_msgHIO.field_0x87 + temp_r0_2;
    s16 temp_r0_4 = g_msgHIO.field_0x89 + temp_r0_3;
    s16 temp_r0_5 = g_msgHIO.field_0x87 + temp_r0_4;

    if (m7C[param_0] < temp_r0_2) {
        mpPic[param_0]->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
    } else if (m7C[param_0] < temp_r0_3) {
        f32 temp_f1 = fopMsgM_valueIncrease(temp_r0, m7C[param_0] - temp_r0_2, 0);
        mpPic[param_0]->setBlendRatio(temp_f1, 1.0f - temp_f1, 1.0f, 1.0f);
    } else if (m7C[param_0] < temp_r0_4) {
        mpPic[param_0]->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
    } else if (m7C[param_0] < temp_r0_5) {
        f32 temp_f1 = fopMsgM_valueIncrease(temp_r0, m7C[param_0] - temp_r0_4, 0);
        mpPic[param_0]->setBlendRatio(1.0f - temp_f1, temp_f1, 1.0f, 1.0f);
    }
}

/* 800CB2E0-800CB474       .text move__17dDlst_2DOutFont_cFv */
void dDlst_2DOutFont_c::move() {
    for (int i = 0; i < mIconNum; i++) {
        switch (mIconNo[i]) {
        case fopMsgM_Icon_MAIN_STICK_e:
            outFontStickAnime1(i);
            break;
        case fopMsgM_Icon_MAIN_STICK_UP_e:
            outFontStickAnime2(i, 1);
            break;
        case fopMsgM_Icon_MAIN_STICK_DOWN_e:
            outFontStickAnime2(i, 3);
            break;
        case fopMsgM_Icon_MAIN_STICK_LEFT_e:
            outFontStickAnime2(i, 0);
            break;
        case fopMsgM_Icon_MAIN_STICK_RIGHT_e:
            outFontStickAnime2(i, 2);
            break;
        case fopMsgM_Icon_MAIN_STICK_UP_DOWN_e:
            outFontStickAnime3(i, 0);
            break;
        case fopMsgM_Icon_MAIN_STICK_LEFT_RIGHT_e:
            outFontStickAnime3(i, 1);
            break;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            mpPic[i]->move(mPosTopLeftX + m38[i] + m50[i], (mPosTopLeftY + m44[i] + m5C[i]) - 1.0f);
        }
    }

    if (mpTextBox != NULL) {
        mpTextBox->move(mPosTopLeftX, mPosTopLeftY);
    }
}

/* 800CB474-800CB4B0       .text setAlpha__17dDlst_2DOutFont_cFUc */
void dDlst_2DOutFont_c::setAlpha(u8 alpha) {
    for (int i = 0; i < ARRAY_SIZE(mpPic); i++) {
        if (mpPic[i] != NULL) {
            mpPic[i]->setAlpha(alpha);
        }
    }
    if (mpTextBox != NULL) {
        mpTextBox->setAlpha(alpha);
    }
}
