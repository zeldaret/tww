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
    mLineWidth = 0.0f;
    mIconNum = 0;
    mPosTopLeftY = 0.0f;
    mPosTopLeftX = 0.0f;
    mLineCount = 0;
    mpTextDst = NULL;

    if (mpTextBox != NULL) {
        mpTextBox->show();
#if VERSION >= VERSION_USA
        mpTextBox->getFontSize(mFontSize);
        mFontSizeX = mFontSize.mSizeX;
#else
        J2DTextBox::TFontSize fontSize;
        mpTextBox->getFontSize(fontSize);
        mFontSizeX = fontSize.mSizeX;
#endif
        mCharSpace = mpTextBox->getCharSpace();
        mpTextDst = mpTextBuf;
    }

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            mIconPosY[i] = 0.0f;
            mIconPosX[i] = 0.0f;
            mIconAnmOffsY[i] = 0.0f;
            mIconAnmOffsX[i] = 0.0f;
            
            mpPic[i]->hide();
            mpPic[i]->rotate(0.0f, 0.0f, ROTATE_Z, 0.0f);
            
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mpPic[i]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mpPic[i]->resize(mFontSizeX, mFontSizeX);
            }

            mIconTimer[i] = 0;
            mIconNo[i] = fopMsgM_Icon_A_BUTTON_e;
            mIconLine[i] = -1;
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

    mpTextBuf = NULL;
    initial();

    for (int i = 0; i < 3; i++) {
        if (mpPic[i] != NULL) {
            mpPic[i]->changeTexture("font_07_02.bti", 0);
            mpPic[i]->append("font_07_02.bti", 1.0f);
        }
    }
}

/* 800C976C-800C9844       .text setPaneEx__17dDlst_2DOutFont_cFP7JUTFontP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classP18fopMsgM_pane_classPc */
void dDlst_2DOutFont_c::setPaneEx(JUTFont* i_font, fopMsgM_pane_class* i_textPane, fopMsgM_pane_class* i_pic1, fopMsgM_pane_class* i_pic2, fopMsgM_pane_class* i_pic3, char* i_textBuf) {
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

    mpTextBuf = i_textBuf;
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
f32 dDlst_2DOutFont_c::charWidth(int i_charCode) {
    f32 width = mpFont->getWidth(i_charCode);
    f32 scale = mFontSizeX / mpFont->getCellWidth();
    return mCharSpace + (width * scale);
}

/* 800C9908-800C99C0       .text rubyCharWidth__17dDlst_2DOutFont_cFi */
f32 dDlst_2DOutFont_c::rubyCharWidth(int i_charCode) {
    J2DTextBox::TFontSize fontSize;
    mpRubyTextBox->getFontSize(fontSize);

    f32 width = mpRubyFont->getWidth(i_charCode);
    f32 scale = fontSize.mSizeX / mpRubyFont->getCellWidth();
    return mCharSpace + (width * scale);
}

/* 800C99C0-800C9D5C       .text iconset__17dDlst_2DOutFont_cFiPPc */
f32 dDlst_2DOutFont_c::iconset(int i_iconNo, char** o_dst) {
    f32 width = 0.0f;

    if (mIconNum < 3) {
        mIconPosX[mIconNum] = mLineWidth;
        mpPic[mIconNum]->show();
        mpPic[mIconNum]->remove();
        mpPic[mIconNum]->append(fopMsgM_outFontTex(i_iconNo), 1.0f);
        mpPic[mIconNum]->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        mpPic[mIconNum]->setWhite(fopMsgM_outFontColorWhite(i_iconNo));
        mpPic[mIconNum]->setBlack(0);
        mIconNo[mIconNum] = i_iconNo;
        mIconLine[mIconNum] = mLineCount;

        switch (i_iconNo) {
        case fopMsgM_Icon_ARROW_LEFT_e:
            mIconPosX[mIconNum] += mFontSizeX;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 270.0f);
            break;
        case fopMsgM_Icon_ARROW_RIGHT_e:
            mIconPosY[mIconNum] += mFontSizeX;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 90.0f);
            break;
        case fopMsgM_Icon_ARROW_UP_e:
            mIconPosX[mIconNum] += mFontSizeX;
            mIconPosY[mIconNum] += mFontSizeX;
            mpPic[mIconNum]->rotate(0.0f, 0.0f, ROTATE_Z, 180.0f);
            break;
        }

#if VERSION >= VERSION_PAL
        width = 0.5f + (mFontSizeX + mCharSpace);

        char buffer[16];
        sprintf(buffer, "\x1B""CR[%d]", (int)width);
#else
        width = mFontSizeX + mCharSpace;

        char buffer[16];
        sprintf(buffer, "\x1B""CR[%d]", (int)(width + 0.5f));
#endif

        char c;
        for (char* p = buffer; c = *p, c != 0; p++) {
            char* dst = *o_dst;
            *o_dst = *o_dst + 1;
            *dst = c;
        }

        mIconNum++;
    }

    return width;
}

/* 800C9D5C-800CA8A8       .text messageSet__17dDlst_2DOutFont_cFUl */
void dDlst_2DOutFont_c::messageSet(u32 i_msgNo) {
    fopMsgM_itemMsgGet_c msgGet;
    mesg_header* head_p = msgGet.getMesgHeader(i_msgNo);
    JUT_ASSERT(DEMO_SELECT(615, 619), head_p);
    const char* message = msgGet.getMessage(head_p);

    char lineBuf[100];
    char rubyLineBuf[100];
    char rubyStr[52];
    char* dst = lineBuf;

    f32 rubyWidth = 0.0f;
    f32 rubyLinePos = 0.0f;
    f32 rubyBasePos = 0.0f;
    int rubyBaseLeft = 0;

    initial();
    mText[0] = 0;
    rubyLineBuf[0] = 0;
    mRubyText[0] = 0;

    while (*message != '\0') {
        u8 c = *message;
        if (c == 0x1A) {
            u32 code = *(u32*)(++message) & 0xFFFFFF;
            if (code == (0xFF0000 | MsgSpclCode_COLOR)) {
                char colorTag[28];
                sprintf(colorTag, "\x1b""CC[%08x]\x1bGM[0]", fopMsgM_getColorTable(message[4]));

                for (char* p = colorTag; *p != '\0'; p++) {
                    *(dst++) = *p;
                }
            } else if (code == (0xFF0000 | MsgSpclCode_RUBY)) {
                if (mpRubyFont != NULL) {
                    u8 tagLen = *(u8*)message;
                    if (tagLen != 5) {
                        int rubyLen = tagLen - 6;
                        int i = 0;

                        const char* rubySrc = message + 5;
                        char* rubyDst = rubyStr;
                        *rubyStr = 0;
                        rubyWidth = 0.0f;
                        rubyBasePos = mLineWidth;
                        rubyBaseLeft = (u8)message[4];

                        for (; i < rubyLen; i += 2) {
                            int hi = (rubyDst[0] = rubySrc[0]);
                            int lo = (rubyDst[1] = rubySrc[1]);

                            rubySrc += 2;
                            rubyDst += 2;
                            rubyWidth += rubyCharWidth(((u8)hi << 8) | (u8)lo);
                        }

                        *rubyDst = 0;
                    }
                }
            } else if (code == MsgCtrlCode_A_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_A_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_B_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_B_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_C_STICK) {
                mLineWidth += iconset(fopMsgM_Icon_C_STICK_e, &dst);
            } else if (code == MsgCtrlCode_L_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_L_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_R_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_R_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_X_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_X_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_Y_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_Y_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_Z_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_Z_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_DPAD) {
                mLineWidth += iconset(fopMsgM_Icon_DPAD_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_e, &dst);
            } else if (code == MsgCtrlCode_ARROW_LEFT) {
                mLineWidth += iconset(fopMsgM_Icon_ARROW_LEFT_e, &dst);
            } else if (code == MsgCtrlCode_ARROW_RIGHT) {
                mLineWidth += iconset(fopMsgM_Icon_ARROW_RIGHT_e, &dst);
            } else if (code == MsgCtrlCode_ARROW_UP) {
                mLineWidth += iconset(fopMsgM_Icon_ARROW_UP_e, &dst);
            } else if (code == MsgCtrlCode_ARROW_DOWN) {
                mLineWidth += iconset(fopMsgM_Icon_ARROW_DOWN_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_UP) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_UP_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_DOWN) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_DOWN_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_LEFT) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_LEFT_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_RIGHT) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_RIGHT_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_UP_DOWN) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_UP_DOWN_e, &dst);
            } else if (code == MsgCtrlCode_MAIN_STICK_LEFT_RIGHT) {
                mLineWidth += iconset(fopMsgM_Icon_MAIN_STICK_LEFT_RIGHT_e, &dst);
            } else if (code == MsgCtrlCode_FLASHING_A_BUTTON) {
                mLineWidth += iconset(fopMsgM_Icon_FLASHING_A_BUTTON_e, &dst);
            } else if (code == MsgCtrlCode_HEART) {
                mLineWidth += iconset(fopMsgM_Icon_HEART_e, &dst);
            } else if (code == MsgCtrlCode_MUSIC_NOTE) {
                mLineWidth += iconset(fopMsgM_Icon_MUSIC_NOTE_e, &dst);
            }

            message += *message - 1;
        } else {
#if VERSION < VERSION_PAL
            int hi_nibble = (c >> 4) & 0xF;
            if (hi_nibble == 8 || hi_nibble == 9) {
                int hi = (*(dst++) = *message++);
                int lo = (*(dst++) = *message++);

                mLineWidth += charWidth(((u8)hi << 8) | (u8)lo);

                if (rubyBaseLeft != 0) {
                    rubyBaseLeft--;
                    if (rubyBaseLeft == 0) {
                        char shiftTag[16];

                        f32 center = rubyBasePos + ((mLineWidth - rubyBasePos) / 2);
                        f32 rubyPos = center - (rubyWidth / 2);
                        if (rubyLinePos < rubyPos) {
                            f32 shift = rubyPos - rubyLinePos;
                            sprintf(shiftTag, "\x1b""CR[%d]", (int)(shift + 0.5f));
                            strcat(rubyLineBuf, shiftTag);
                            rubyLinePos += shift;
                        } else if (rubyLinePos > rubyPos) {
                            f32 shift = rubyLinePos - rubyPos;
                            sprintf(shiftTag, "\x1b""CL[%d]", (int)(shift + 0.5f));
                            strcat(rubyLineBuf, shiftTag);
                            rubyLinePos -= shift;
                        }

                        rubyLinePos += rubyWidth;
                        strcat(rubyLineBuf, rubyStr);
                    }
                }
            } else
#endif
            {
                char ch = *message++;
                *(dst++) = ch;

                if (ch == '\n') {
#if VERSION >= VERSION_PAL
                    // PAL: message 0x5F is kept on one line
                    if (i_msgNo != 0x5F)
#endif
                    {
                        char indentTag[16];
                        *dst = 0;

                        int indent = (mpTextBox->getWidth() - mLineWidth) / 2;
                        if (indent > 0) {
                            sprintf(indentTag, "\x1b""CR[%d]", indent);

                            for (int i = 0; i < 3; i++) {
                                if (mLineCount == mIconLine[i]) {
                                    mIconPosX[i] += indent;
                                }
                            }
                        } else {
                            *indentTag = 0;
                        }

                        strcat(mText, indentTag);
                        strcat(mText, lineBuf);
                        mLineCount++;
                        mLineWidth = 0.0f;
                        rubyLinePos = 0.0f;

                        dst = lineBuf;

                        if (mpRubyFont != NULL) {
                            strcat(mRubyText, indentTag);
                            strcat(mRubyText, rubyLineBuf);
                            strcat(mRubyText, "\n");
                            *rubyLineBuf = 0;
                        }
                    }
#if VERSION >= VERSION_PAL
                    else {
                        dst--;
                    }
#endif
                } else {
                    mLineWidth += charWidth(ch);
                }
            }
        }
    }

    *dst = 0;

    #if VERSION >= VERSION_PAL
    f32 offsetY = ((mpTextBox->getHeight() - mFontSize.mSizeY) - mLineCount * mpTextBox->getLineSpace()) / 2;
    #elif VERSION >= VERSION_USA
    f32 offsetY = 0.0f;
    if (mFitToBox == 0) {
        offsetY = ((mpTextBox->getHeight() - mFontSizeX) - mLineCount * mpTextBox->getLineSpace()) / 2;
    }
    #else
    f32 offsetY = ((mpTextBox->getHeight() - mFontSizeX) - mLineCount * mpTextBox->getLineSpace()) / 2;
    #endif

    char indentTag[16];
    int indent = (mpTextBox->getWidth() - mLineWidth) / 2;
    if (indent > 0) {
        sprintf(indentTag, "\x1b""CR[%d]", indent);

        for (int i = 0; i < 3; i++) {
            if (mLineCount == mIconLine[i]) {
                mIconPosX[i] += indent;
            }

            if (mIconLine[i] != -1) {
                mIconPosY[i] += offsetY + (mIconLine[i] * mpTextBox->getLineSpace());
            }
        }
    } else {
        *indentTag = 0;
    }

    strcat(mText, indentTag);
    strcat(mText, lineBuf);
    mpTextBox->shiftSet(0.0f, offsetY);

    if (mpTextDst == NULL) {
        mpTextBox->setString(mText);
    } else {
        strcpy(mpTextDst, mText);
    }

    if (mpRubyTextBox != NULL) {
        mpRubyTextBox->shiftSet(0.0f, offsetY);
        strcat(mRubyText, indentTag);
        strcat(mRubyText, rubyLineBuf);

        if (mpRubyTextDst == NULL) {
            mpRubyTextBox->setString(mRubyText);
        } else {
            strcpy(mpRubyTextDst, mRubyText);
        }
    }

    #if VERSION >= VERSION_PAL
    if (mFitToBox) {
        if (mpTextBox->getWidth() - 5.0f < mLineWidth) {
            f32 ratio = (mpTextBox->getWidth() - 5.0f) / mLineWidth;
            int sizeX = ratio * mFontSize.mSizeX;
            mCharSpace = (int)(ratio * mpTextBox->getCharSpace());
            mpTextBox->setCharSpace(mCharSpace);
            mFontSize.mSizeX = mFontSizeX = sizeX;

            J2DTextBox::TFontSize fontSize = mFontSize;
            mpTextBox->setFontSize(fontSize);
            messageSet(i_msgNo);
        }
    }
    #elif VERSION >= VERSION_USA
    if (mFitToBox) {
        if (mpTextBox->getWidth() < mLineWidth) {
            mFontSize.mSizeX = (int)(mFontSize.mSizeX * (mpTextBox->getWidth() / mLineWidth));

            J2DTextBox::TFontSize fontSize = mFontSize;
            mpTextBox->setFontSize(fontSize);
            messageSet(i_msgNo);
        }
    }
    #endif
}

/* 800CA8A8-800CAB5C       .text outFontStickAnime1__17dDlst_2DOutFont_cFUc */
void dDlst_2DOutFont_c::outFontStickAnime1(u8 i_idx) {
    s16 cycle = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    if (mIconTimer[i_idx] < cycle) {
        outFontStickAnimePiece(i_idx, 0);
        #if VERSION >= VERSION_USA
        if (mFitToBox) {
            mIconAnmOffsX[i_idx] = 0.0f;
            mIconAnmOffsY[i_idx] = 0.0f;
            mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
        } else
        #endif
        {
            mIconAnmOffsX[i_idx] = 0.0f;
            mIconAnmOffsY[i_idx] = 0.0f;
        }
    } else if (mIconTimer[i_idx] < cycle * 2) {
        outFontStickAnimePiece(i_idx, 1);
        #if VERSION >= VERSION_USA
        if (mFitToBox) {
            mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
            mIconAnmOffsY[i_idx] = 0.0f;
            mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
        } else
        #endif
        {
            mIconAnmOffsX[i_idx] = mFontSizeX;
            mIconAnmOffsY[i_idx] = 0.0f;
        }
    } else if (mIconTimer[i_idx] < cycle * 3) {
        outFontStickAnimePiece(i_idx, 2);
        #if VERSION >= VERSION_USA
        if (mFitToBox) {
            mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
            mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
            mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
        } else
        #endif
        {
            mIconAnmOffsX[i_idx] = mFontSizeX;
            mIconAnmOffsY[i_idx] = mFontSizeX;
        }
    } else if (mIconTimer[i_idx] < cycle * 4) {
        outFontStickAnimePiece(i_idx, 3);
        #if VERSION >= VERSION_USA
        if (mFitToBox) {
            mIconAnmOffsX[i_idx] = 0.0f;
            mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
            mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
        } else
        #endif
        {
            mIconAnmOffsX[i_idx] = 0.0f;
            mIconAnmOffsY[i_idx] = mFontSizeX;
        }
    }

    if ((mIconTimer[i_idx] % cycle) == 0) {
        mpPic[i_idx]->rotate(0.0f, 0.0f, ROTATE_Z, (mIconTimer[i_idx] / cycle) * -90.0f);
    }

    mIconTimer[i_idx]++;
    if (mIconTimer[i_idx] >= cycle * 4) {
        mIconTimer[i_idx] = 0;
    }
}

/* 800CAB5C-800CADEC       .text outFontStickAnime2__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnime2(u8 i_idx, u8 i_dir) {
    s16 cycle = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    if (mIconTimer[i_idx] < cycle) {
        outFontStickAnimePiece(i_idx, 0);
        
        switch (i_dir) {
        case 0:
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = 0.0f;
                mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = 0.0f;
            }
            break;
        case 1:
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
                mIconAnmOffsY[i_idx] = 0.0f;
                mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = mFontSizeX;
                mIconAnmOffsY[i_idx] = 0.0f;
            }
            break;
        case 2:
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
                mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
                mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = mFontSizeX;
                mIconAnmOffsY[i_idx] = mFontSizeX;
            }
            break;
        case 3:
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
                mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = mFontSizeX;
            }
            break;
        }
    }

    mpPic[i_idx]->rotate(0.0f, 0.0f, ROTATE_Z, i_dir * -90.0f);

    mIconTimer[i_idx]++;
    if (mIconTimer[i_idx] >= cycle) {
        mIconTimer[i_idx] = 0;
    }
}

/* 800CADEC-800CB0C0       .text outFontStickAnime3__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnime3(u8 i_idx, u8 i_axis) {
    s16 cycle = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;

    int dir;
    if (i_axis == 0) {
        if (mIconTimer[i_idx] < cycle) {
            outFontStickAnimePiece(i_idx, 0);
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
                mIconAnmOffsY[i_idx] = 0.0f;
                mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = mFontSizeX;
                mIconAnmOffsY[i_idx] = 0.0f;
            }
            dir = 1;
        } else if (mIconTimer[i_idx] < cycle * 2) {
            outFontStickAnimePiece(i_idx, 1);
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
                mpPic[i_idx]->resize(mFontSize.mSizeY, mFontSize.mSizeX);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = mFontSizeX;
            }
            dir = 3;
        }
    } else {
        if (mIconTimer[i_idx] < cycle) {
            outFontStickAnimePiece(i_idx, 0);
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = 0.0f;
                mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = 0.0f;
                mIconAnmOffsY[i_idx] = 0.0f;
            }
            dir = 0;
        } else if (mIconTimer[i_idx] < cycle * 2) {
            outFontStickAnimePiece(i_idx, 1);
            #if VERSION >= VERSION_USA
            if (mFitToBox) {
                mIconAnmOffsX[i_idx] = mFontSize.mSizeX;
                mIconAnmOffsY[i_idx] = mFontSize.mSizeY;
                mpPic[i_idx]->resize(mFontSize.mSizeX, mFontSize.mSizeY);
            } else
            #endif
            {
                mIconAnmOffsX[i_idx] = mFontSizeX;
                mIconAnmOffsY[i_idx] = mFontSizeX;
            }
            dir = 2;
        }
    }

    mpPic[i_idx]->rotate(0.0f, 0.0f, ROTATE_Z, dir * -90.0f);

    mIconTimer[i_idx]++;
    if (mIconTimer[i_idx] >= cycle * 2) {
        mIconTimer[i_idx] = 0;
    }
}

/* 800CB0C0-800CB2E0       .text outFontStickAnimePiece__17dDlst_2DOutFont_cFUcUc */
void dDlst_2DOutFont_c::outFontStickAnimePiece(u8 i_idx, u8 i_step) {
    s16 cycle = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    s16 fadeInStart = g_msgHIO.field_0x88 + (cycle * i_step);
    s16 fadeInEnd = g_msgHIO.field_0x87 + fadeInStart;
    s16 fadeOutStart = g_msgHIO.field_0x89 + fadeInEnd;
    s16 fadeOutEnd = g_msgHIO.field_0x87 + fadeOutStart;

    if (mIconTimer[i_idx] < fadeInStart) {
        mpPic[i_idx]->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
    } else if (mIconTimer[i_idx] < fadeInEnd) {
        f32 ratio = fopMsgM_valueIncrease(cycle, mIconTimer[i_idx] - fadeInStart, 0);
        mpPic[i_idx]->setBlendRatio(ratio, 1.0f - ratio, 1.0f, 1.0f);
    } else if (mIconTimer[i_idx] < fadeOutStart) {
        mpPic[i_idx]->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
    } else if (mIconTimer[i_idx] < fadeOutEnd) {
        f32 ratio = fopMsgM_valueIncrease(cycle, mIconTimer[i_idx] - fadeOutStart, 0);
        mpPic[i_idx]->setBlendRatio(1.0f - ratio, ratio, 1.0f, 1.0f);
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
            mpPic[i]->move(mPosTopLeftX + mIconPosX[i] + mIconAnmOffsX[i], (mPosTopLeftY + mIconPosY[i] + mIconAnmOffsY[i]) - 1.0f);
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
