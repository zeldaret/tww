//
// Generated by dtk
// Translation Unit: JAISoundTable.cpp
//

#include "JSystem/JAudio/JAISoundTable.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

u8 JAInter::SoundTable::mVersion;
u8 JAInter::SoundTable::mCategotyMax;
u16* JAInter::SoundTable::mSoundMax;
u32 JAInter::SoundTable::mDatasize;
SoundInfo** JAInter::SoundTable::mPointerCategory;
u8* JAInter::SoundTable::mAddress;

/* 8029B570-8029B6FC       .text init__Q27JAInter10SoundTableFPUcUl */
void JAInter::SoundTable::init(u8* param_1, u32 param_2) {
    /* Nonmatching - operand swap */
    mAddress = param_1;
    mDatasize = param_2;
    mVersion = param_1[3];
    mSoundMax = new (JAIBasic::getCurrentJAIHeap(), 4) u16[18];
    mPointerCategory = new (JAIBasic::getCurrentJAIHeap(), 4) SoundInfo*[18];
    for (u8 i = 0; i < 18; i++) {
        mSoundMax[i] = reinterpret_cast<u16*>(&mAddress[6])[i*2];
        u32 temp = reinterpret_cast<u16*>(&mAddress[8])[i*2];
        mPointerCategory[i] = &(reinterpret_cast<SoundInfo*>(&mAddress[0x50])[temp]);
        
        if (i < 16 && mSoundMax[i] != 0) {
            mCategotyMax = i + 1;
        }
    }
}

/* 8029B6FC-8029B8CC       .text getInfoPointer__Q27JAInter10SoundTableFUl */
SoundInfo* JAInter::SoundTable::getInfoPointer(u32 param_1) {
    JUT_ASSERT_MSG(52, mAddress, "getInfoPointer サウンドテーブルがありません\n");
    SoundInfo* r31 = NULL;
    u32 _category;
    switch (param_1 & JAISoundID_TypeMask) {
    case JAISoundID_Type_Se:
        _category = param_1 >> 12 & 0xff;
        JUT_ASSERT_MSG(61, (_category<JAIGlobalParameter::getParamSeCategoryMax()), "getInfoPointer 登録されていないSEカテゴリーナンバーが指定されました。\n");
        break;
    case JAISoundID_Type_Sequence:
        _category = 16;
        break;
    case JAISoundID_Type_Stream:
        _category = 17;
        break;
    default:
        JUT_ASSERT_MSG(70, 0, "getInfoPointer サウンドカテゴリービットが異常です。\n");
        break;
    }
    u32 tmp = param_1 & 0x3ff;
    if (mAddress && tmp < mSoundMax[_category]) {
        r31 = &mPointerCategory[_category][tmp];
    }
    return r31;
}

/* 8029B8CC-8029B99C       .text getInfoFormat__Q27JAInter10SoundTableFUl */
u8 JAInter::SoundTable::getInfoFormat(u32 param_1) {
    u8 r31 = 0;
    switch (param_1 & JAISoundID_TypeMask) {
    case JAISoundID_Type_Se:
        r31 = mAddress[0];
        break;
    case JAISoundID_Type_Sequence:
        r31 = mAddress[1];
        break;
    case JAISoundID_Type_Stream:
        r31 =  mAddress[2];
        break;
    default:
        JUT_ASSERT_MSG(101, 0, "getInfoFormat サウンドカテゴリービットが異常です。\n");
        break;
    }
    return r31;
}

/* 8029B99C-8029B9A4       .text getCategotyMax__Q27JAInter10SoundTableFv */
u8 JAInter::SoundTable::getCategotyMax() {
    return mCategotyMax;
}
