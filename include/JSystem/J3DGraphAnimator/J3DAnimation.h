#ifndef J3DANIMATION_H
#define J3DANIMATION_H

#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "JSystem/JUtility/JUTDataHeader.h"

struct J3DAnmKeyTableBase {
    /* 0x00 */ u16 mMaxFrame;
    /* 0x02 */ u16 mOffset;
    /* 0x04 */ u16 mType;
};  // Size = 0x6

struct J3DAnmColorKeyTable {
    enum Color {
        RED   = 0,
        GREEN = 1,
        BLUE  = 2,
        ALPHA = 3,
    };
    /* 0x00 */ J3DAnmKeyTableBase mColorInfo[4];
};  // Size = 0x18

struct J3DAnmColorFullTable {
    /* 0x00 */ u16 mRMaxFrame;
    /* 0x02 */ u16 mROffset;
    /* 0x04 */ u16 mGMaxFrame;
    /* 0x06 */ u16 mGOffset;
    /* 0x08 */ u16 mBMaxFrame;
    /* 0x0A */ u16 mBOffset;
    /* 0x0C */ u16 mAMaxFrame;
    /* 0x0E */ u16 mAOffset;
};  // Size = 0x10

struct J3DAnmVisibilityFullTable {
    u16 mMaxFrame;
    u16 mOffset;
};  // Size = 0x4

struct J3DAnmTransformKeyTable {
    /* 0x00 */ J3DAnmKeyTableBase mScale;
    /* 0x06 */ J3DAnmKeyTableBase mRotation;
    /* 0x0C */ J3DAnmKeyTableBase mTranslate;
};  // Size = 0x12

struct J3DAnmTransformFullTable {
    /* 0x00 */ u16 mScaleMaxFrame;
    /* 0x02 */ u16 mScaleOffset;
    /* 0x04 */ u16 mRotationMaxFrame;
    /* 0x06 */ u16 mRotationOffset;
    /* 0x08 */ u16 mTranslateMaxFrame;
    /* 0x0A */ u16 mTranslateOffset;
};  // Size = 0xC

struct J3DAnmTexPatternFullTable {
    /* 0x00 */ u16 mMaxFrame;
    /* 0x02 */ u16 mOffset;
    /* 0x04 */ u8 mTexNo;
    /* 0x06 */ u16 _6;
};  // Size = 0x8

struct J3DAnmCRegKeyTable {
    /* 0x00 */ J3DAnmKeyTableBase mRTable;
    /* 0x06 */ J3DAnmKeyTableBase mGTable;
    /* 0x0C */ J3DAnmKeyTableBase mBTable;
    /* 0x12 */ J3DAnmKeyTableBase mATable;
    /* 0x18 */ u8 mColorId;
    u8 padding[3];
};  // Size = 0x1C

struct J3DAnmKRegKeyTable {
    /* 0x00 */ J3DAnmKeyTableBase mRTable;
    /* 0x06 */ J3DAnmKeyTableBase mGTable;
    /* 0x0C */ J3DAnmKeyTableBase mBTable;
    /* 0x12 */ J3DAnmKeyTableBase mATable;
    /* 0x18 */ u8 mColorId;
    u8 padding[3];
};  // Size = 0x1C

struct J3DAnmClusterFullTable {
    u16 mMaxFrame;
    u16 mOffset;
};

struct J3DAnmClusterKeyTable {
    /* 0x00 */ J3DAnmKeyTableBase mWeightTable;
};

struct J3DAnmVtxColorFullData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;  // padding?
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 mAnmTableNum[2];
    /* 0x10 */ u16 mIndexNum[2];
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ s32 mTableOffsets[2];
    /* 0x20 */ s32 mVtxColorIndexDataOffsets[2];
    /* 0x28 */ s32 mVtxColorIndexPointerOffsets[2];
    /* 0x30 */ s32 mRValuesOffset;
    /* 0x34 */ s32 mGValuesOffset;
    /* 0x38 */ s32 mBValuesOffset;
    /* 0x3C */ s32 mAValuesOffset;
};  // Size = 0x40

STATIC_ASSERT(sizeof(J3DAnmVtxColorFullData) == 0x40);

struct J3DAnmVisibilityFullData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;  // padding?
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 field_0xc;
    /* 0x0E */ u16 field_0xe;
    /* 0x10 */ s32 mTableOffset;
    /* 0x14 */ s32 mValuesOffset;
};  // Size = 0x18

STATIC_ASSERT(sizeof(J3DAnmVisibilityFullData) == 0x18);

struct J3DAnmTransformFullData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 field_0xc;
    /* 0x0E */ u8 field_0xe[0x14 - 0xe];
    /* 0x14 */ s32 mTableOffset;
    /* 0x18 */ s32 mScaleValOffset;
    /* 0x1C */ s32 mRotValOffset;
    /* 0x20 */ s32 mTransValOffset;
};  // Size = 0x24

STATIC_ASSERT(sizeof(J3DAnmTransformFullData) == 0x24);

struct J3DAnmColorKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9[3];
    /* 0x0C */ s16 mFrameMax;
    /* 0x0E */ u16 mUpdateMaterialNum;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ s32 mTableOffset;
    /* 0x1C */ s32 mUpdateMaterialIDOffset;
    /* 0x20 */ s32 mNameTabOffset;
    /* 0x24 */ s32 mRValOffset;
    /* 0x28 */ s32 mGValOffset;
    /* 0x2C */ s32 mBValOffset;
    /* 0x30 */ s32 mAValOffset;
};  // Size = 0x34

STATIC_ASSERT(sizeof(J3DAnmColorKeyData) == 0x34);

struct J3DAnmTextureSRTKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ s16 field_0xa;
    /* 0x0C */ u16 field_0xc;
    /* 0x0E */ u16 field_0xe;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ s32 mTableOffset;
    /* 0x18 */ s32 mUpdateMatIDOffset;
    /* 0x1C */ s32 mNameTab1Offset;
    /* 0x20 */ s32 mUpdateTexMtxIDOffset;
    /* 0x24 */ s32 unkOffset;
    /* 0x28 */ s32 mScaleValOffset;
    /* 0x2C */ s32 mRotValOffset;
    /* 0x30 */ s32 mTransValOffset;
    /* 0x34 */ u16 field_0x34;
    /* 0x36 */ u16 field_0x36;
    /* 0x38 */ u16 field_0x38;
    /* 0x3A */ u16 field_0x3a;
    /* 0x3C */ s32 mInfoTable2Offset;
    /* 0x40 */ s32 field_0x40;
    /* 0x44 */ u32 mNameTab2Offset;
    /* 0x48 */ s32 field_0x48;
    /* 0x4C */ s32 field_0x4c;
    /* 0x50 */ s32 field_0x50;
    /* 0x54 */ s32 field_0x54;
    /* 0x58 */ s32 field_0x58;
    /* 0x5C */ s32 field_0x5c;
};  // Size = 0x60

STATIC_ASSERT(sizeof(J3DAnmTextureSRTKeyData) == 0x60);

struct J3DAnmVtxColorKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 mAnmTableNum[2];
    /* 0x10 */ u32 mIndexNum[2];
    /* 0x18 */ s32 mTableOffsets[2];
    /* 0x20 */ s32 mVtxColorIndexDataOffsets[2];
    /* 0x28 */ s32 mVtxColorIndexPointerOffsets[2];
    /* 0x30 */ s32 mRValuesOffset;
    /* 0x34 */ s32 mGValuesOffset;
    /* 0x38 */ s32 mBValuesOffset;
    /* 0x3C */ s32 mAValuesOffset;
};  // Size = 0x40

STATIC_ASSERT(sizeof(J3DAnmVtxColorKeyData) == 0x40);

struct J3DAnmTexPatternFullData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 field_0xc;
    /* 0x0E */ u16 field_0xe;
    /* 0x10 */ s32 mTableOffset;
    /* 0x14 */ s32 mValuesOffset;
    /* 0x18 */ s32 mUpdateMaterialIDOffset;
    /* 0x1C */ s32 mNameTabOffset;
};  // Size = 0x20

STATIC_ASSERT(sizeof(J3DAnmTexPatternFullData) == 0x20);

struct J3DAnmTevRegKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;  // maybe padding
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 mCRegUpdateMaterialNum;
    /* 0x0E */ u16 mKRegUpdateMaterialNum;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 field_0x1a;
    /* 0x1C */ u16 field_0x1c;
    /* 0x1E */ u16 field_0x1e;
    /* 0x20 */ s32 mCRegTableOffset;
    /* 0x24 */ s32 mKRegTableOffset;
    /* 0x28 */ s32 mCRegUpdateMaterialIDOffset;
    /* 0x2C */ s32 mKRegUpdateMaterialIDOffset;
    /* 0x30 */ s32 mCRegNameTabOffset;
    /* 0x34 */ s32 mKRegNameTabOffset;
    /* 0x38 */ s32 mCRValuesOffset;
    /* 0x3C */ s32 mCGValuesOffset;
    /* 0x40 */ s32 mCBValuesOffset;
    /* 0x44 */ s32 mCAValuesOffset;
    /* 0x48 */ s32 mKRValuesOffset;
    /* 0x4C */ s32 mKGValuesOffset;
    /* 0x50 */ s32 mKBValuesOffset;
    /* 0x54 */ s32 mKAValuesOffset;
};  // Size = 0x58

STATIC_ASSERT(sizeof(J3DAnmTevRegKeyData) == 0x58);

struct J3DAnmColorFullData { /* PlaceHolder Structure */
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9[3];
    /* 0x0C */ s16 mFrameMax;
    /* 0x0E */ u16 mUpdateMaterialNum;
    /* 0x10 */ u8 field_0x10[0x18 - 0x10];
    /* 0x18 */ s32 mTableOffset;
    /* 0x1C */ s32 mUpdateMaterialIDOffset;
    /* 0x20 */ s32 mNameTabOffset;
    /* 0x24 */ s32 mRValuesOffset;
    /* 0x28 */ s32 mGValuesOffset;
    /* 0x2C */ s32 mBValuesOffset;
    /* 0x30 */ s32 mAValuesOffset;
};  // Size = 0x34

STATIC_ASSERT(sizeof(J3DAnmColorFullData) == 0x34);

struct J3DAnmClusterFullData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ s32 field_0xc;
    /* 0x10 */ s32 mTableOffset;
    /* 0x14 */ s32 mWeightOffset;
};

struct J3DAnmTransformKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 mAttribute;
    /* 0x09 */ u8 mDecShift;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ s32 mTableOffset;
    /* 0x18 */ s32 mScaleOffset;
    /* 0x1c */ s32 mRotOffset;
    /* 0x20 */ s32 mTransOffset;
};

struct J3DAnmClusterKeyData {
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ s32 field_0xc;
    /* 0x10 */ s32 mTableOffset;
    /* 0x14 */ s32 mWeightOffset;
};

class J3DAnmBase {
public:
    J3DAnmBase(s16 i_frameMax) {
        mFrame = 0.0f;
        mFrameMax = i_frameMax;
    }

    virtual ~J3DAnmBase() {}

    u8 getAttribute() const { return mAttribute; }
    s16 getFrameMax() const { return mFrameMax; }
    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }
    s32 getKind() const { return mKind; }

protected:
    /* 0x4 */ u8 mAttribute;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ s16 mFrameMax;
    /* 0x8 */ f32 mFrame;
    /* 0xC */ s32 mKind;
};  // Size: 0x10

class J3DAnmTransform : public J3DAnmBase {
public:
    J3DAnmTransform(s16 i_frameMax, f32* scaleData, s16* rotData, f32* transData) : J3DAnmBase(i_frameMax) {
        mScaleData = scaleData;
        mRotData = rotData;
        mTransData = transData;
        mKind = 0;
    }

    virtual ~J3DAnmTransform() {}
    virtual void getTransform(u16, J3DTransformInfo*) const {}

protected:
    /* 0x10 */ f32* mScaleData;
    /* 0x14 */ s16* mRotData;
    /* 0x18 */ f32* mTransData;
    /* 0x1C */ s16 field_0x1c;
    /* 0x1E */ s16 field_0x1e;
    /* 0x20 */ u16 field_0x20;
    /* 0x22 */ u16 field_0x22;
};  // Size: 0x24

// BCK
class J3DAnmTransformKey : public J3DAnmTransform {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmTransformKey() : J3DAnmTransform(0, NULL, NULL, NULL) {
        mDecShift = 0;
        mAnmTable = NULL;
    }

    virtual void calcTransform(f32, u16, J3DTransformInfo*) const;

    virtual ~J3DAnmTransformKey() {}
    virtual void getTransform(u16 idx, J3DTransformInfo* dst) const { calcTransform(getFrame(), idx, dst); }

private:
    /* 0x24 */ int mDecShift;
    /* 0x28 */ J3DAnmTransformKeyTable* mAnmTable;
};  // Size: 0x2C

// BCA
class J3DAnmTransformFull : public J3DAnmTransform {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmTransformFull() : J3DAnmTransform(0, NULL, NULL, NULL) {
        mAnmTable = NULL;
    }

    virtual ~J3DAnmTransformFull() {}
    virtual void getTransform(u16, J3DTransformInfo*) const;

private:
    /* 0x24 */ J3DAnmTransformFullTable* mAnmTable;
};  // Size: 0x28

struct J3DTextureSRTInfo;
class J3DModelData;
class J3DMaterialTable;

// BTK
class J3DAnmTextureSRTKey : public J3DAnmBase {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmTextureSRTKey() : J3DAnmBase(0) {
        mDecShift = 0;
        mTransNum = 0;
        mRotNum = 0;
        mScaleNum = 0;
        mTrackNum = 0;
        mAnmTable = NULL;
        mTransData = NULL;
        mScaleData = NULL;
        mRotData = NULL;
        field_0x50 = 0;
        field_0x4e = 0;
        field_0x4c = 0;
        mPostTrackNum = 0;
        field_0x64 = NULL;
        field_0x5c = NULL;
        field_0x54 = NULL;
        field_0x58 = NULL;
        mTexMtxCalcType = 0;
        mKind = 4;
    }
    void calcTransform(f32, u16, J3DTextureSRTInfo*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTextureSRTKey() {}

    void getTransform(u16 idx, J3DTextureSRTInfo* pSRTInfo) const {
        calcTransform(getFrame(), idx, pSRTInfo);
    }

    u16 getUpdateMaterialID(u16 idx) const {
        J3D_ASSERT(1029, idx < mTrackNum / 3, "Error : range over.");
        return mUpdateMaterialID[idx];
    }
    u16 getUpdateMaterialNum() const { return mTrackNum / 3; }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }
    u16 getUpdateTexMtxID(u16 idx) const {
        J3D_ASSERT(1017, idx < (mTrackNum / 3), "Error : range over.");
        return mUpdateTexMtxID[idx];
    }

    u16 getPostUpdateMaterialID(u16 idx) const { return mPostUpdateMaterialID[idx]; }
    u16 getPostUpdateMaterialNum() const { return mPostTrackNum / 3; }
    JUTNameTab * getPostUpdateMaterialName() { return &mPostUpdateMaterialName; }
    u16 getPostUpdateTexMtxID(u16 idx) const { return mPostUpdateTexMtxID[idx]; }

    u32 getTexMtxCalcType() { return mTexMtxCalcType; }
    Vec& getSRTCenter(u16 idx) {
        J3D_ASSERT(1047, idx < mTrackNum / 3, "Error : range over.");
        return mSRTCenter[idx];
    }

private:
    /* 0x10 */ int mDecShift;
    /* 0x14 */ u16 mTrackNum;
    /* 0x18 */ J3DAnmTransformKeyTable* mAnmTable;
    /* 0x1C */ u16 mScaleNum;
    /* 0x1E */ u16 mRotNum;
    /* 0x20 */ u16 mTransNum;
    /* 0x24 */ f32* mScaleData;
    /* 0x28 */ s16* mRotData;
    /* 0x2C */ f32* mTransData;
    /* 0x30 */ u8* mUpdateTexMtxID;
    /* 0x34 */ u16* mUpdateMaterialID;
    /* 0x38 */ JUTNameTab mUpdateMaterialName;
    /* 0x48 */ Vec* mSRTCenter;
    /* 0x4C */ short field_0x4c;
    /* 0x4E */ short field_0x4e;
    /* 0x50 */ short field_0x50;
    /* 0x54 */ void * field_0x54;
    /* 0x58 */ void * field_0x58;
    /* 0x5C */ void * field_0x5c;
    /* 0x60 */ u16 mPostTrackNum;
    /* 0x64 */ void * field_0x64;
    /* 0x68 */ u8* mPostUpdateTexMtxID;
    /* 0x6C */ u16* mPostUpdateMaterialID;
    /* 0x70 */ JUTNameTab mPostUpdateMaterialName;
    /* 0x80 */ Vec* mPostSRTCenter;
    /* 0x84 */ u32 mTexMtxCalcType;
};  // Size: 0x88

STATIC_ASSERT(sizeof(J3DAnmTextureSRTKey) == 0x88);

// BVA
class J3DAnmVisibilityFull : public J3DAnmBase {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmVisibilityFull() : J3DAnmBase(0) {
        mUpdateMaterialNum = 0;
        mAnmTable = NULL;
        field_0x12 = 0;
        mVisibility = NULL;
        mKind = 6;
    }
    void getVisibility(u16, u8*) const;

    virtual ~J3DAnmVisibilityFull() {}

    J3DAnmVisibilityFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x10 */ u16 mUpdateMaterialNum;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ J3DAnmVisibilityFullTable * mAnmTable;
    /* 0x18 */ u8* mVisibility;
};  // Size: 0x1C

// BTP
class J3DAnmTexPattern : public J3DAnmBase {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmTexPattern() : J3DAnmBase(0) {
        mTextureIndex = NULL;
        mAnmTable = NULL;
        mKind = 2;
        mUpdateMaterialNum = 0;
        mUpdateMaterialID = NULL;
    }
    void getTexNo(u16, u16*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    u16 getUpdateMaterialID(u16 idx) const {
        J3D_ASSERT(2288, idx < mUpdateMaterialNum, "Error : range over.");
        return mUpdateMaterialID[idx];
    }
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }

    J3DAnmTexPatternFullTable * getAnmTable() const { return mAnmTable; }

    virtual ~J3DAnmTexPattern() {}

private:
    /* 0x10 */ u16* mTextureIndex;
    /* 0x14 */ J3DAnmTexPatternFullTable* mAnmTable;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 mUpdateMaterialNum;
    /* 0x1C */ u16* mUpdateMaterialID;
    /* 0x20 */ JUTNameTab mUpdateMaterialName;
};  // Size: 0x2C

// BRK
class J3DAnmTevRegKey : public J3DAnmBase {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmTevRegKey() : J3DAnmBase(0) {
        mKRegUpdateMaterialNum = 0;
        mCRegUpdateMaterialNum = 0;
        mCRegDataCountA = 0;
        mCRegDataCountB = 0;
        mCRegDataCountG = 0;
        mCRegDataCountR = 0;
        mKRegDataCountA = 0;
        mKRegDataCountB = 0;
        mKRegDataCountG = 0;
        mKRegDataCountR = 0;
        mKRegUpdateMaterialID = NULL;
        mCRegUpdateMaterialID = NULL;
        mAnmCRegDataA = NULL;
        mAnmCRegDataB = NULL;
        mAnmCRegDataG = NULL;
        mAnmCRegDataR = NULL;
        mAnmKRegDataA = NULL;
        mAnmKRegDataB = NULL;
        mAnmKRegDataG = NULL;
        mAnmKRegDataR = NULL;
        mKind = 5;
    }
    void getTevColorReg(u16, GXColorS10*) const;
    void getTevKonstReg(u16, GXColor*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTevRegKey() {}

    u16 getCRegUpdateMaterialNum() const { return mCRegUpdateMaterialNum; }
    u16 getKRegUpdateMaterialNum() const { return mKRegUpdateMaterialNum; }

    u16 getCRegUpdateMaterialID(u16 idx) const {
        J3D_ASSERT(2100, idx < mCRegUpdateMaterialNum, "Error : range over.");
        return mCRegUpdateMaterialID[idx];
    }
    u16 getKRegUpdateMaterialID(u16 idx) const {
        J3D_ASSERT(2140, idx < mKRegUpdateMaterialNum, "Error : range over.");
        return mKRegUpdateMaterialID[idx];
    }

    JUTNameTab * getCRegUpdateMaterialName() { return &mCRegUpdateMaterialName; }
    JUTNameTab * getKRegUpdateMaterialName() { return &mKRegUpdateMaterialName; }

    J3DAnmCRegKeyTable * getAnmCRegKeyTable() const { return mAnmCRegKeyTable; }
    J3DAnmKRegKeyTable * getAnmKRegKeyTable() const { return mAnmKRegKeyTable; }

private:
    /* 0x10 */ u16 mCRegUpdateMaterialNum;
    /* 0x12 */ u16 mKRegUpdateMaterialNum;
    /* 0x14 */ u16 mCRegDataCountR;
    /* 0x16 */ u16 mCRegDataCountG;
    /* 0x18 */ u16 mCRegDataCountB;
    /* 0x1A */ u16 mCRegDataCountA;
    /* 0x1C */ u16 mKRegDataCountR;
    /* 0x1E */ u16 mKRegDataCountG;
    /* 0x20 */ u16 mKRegDataCountB;
    /* 0x22 */ u16 mKRegDataCountA;
    /* 0x24 */ u16* mCRegUpdateMaterialID;
    /* 0x28 */ JUTNameTab mCRegUpdateMaterialName;
    /* 0x38 */ u16* mKRegUpdateMaterialID;
    /* 0x3C */ JUTNameTab mKRegUpdateMaterialName;
    /* 0x4C */ J3DAnmCRegKeyTable* mAnmCRegKeyTable;
    /* 0x50 */ J3DAnmKRegKeyTable* mAnmKRegKeyTable;
    /* 0x54 */ s16 * mAnmCRegDataR;
    /* 0x58 */ s16 * mAnmCRegDataG;
    /* 0x5C */ s16 * mAnmCRegDataB;
    /* 0x60 */ s16 * mAnmCRegDataA;
    /* 0x64 */ s16 * mAnmKRegDataR;
    /* 0x68 */ s16 * mAnmKRegDataG;
    /* 0x6C */ s16 * mAnmKRegDataB;
    /* 0x70 */ s16 * mAnmKRegDataA;
};  // Size: 0x74

// BPK
class J3DAnmColor : public J3DAnmBase {
public:
    J3DAnmColor() : J3DAnmBase(0) {
        field_0x16 = 0;
        field_0x14 = 0;
        field_0x12 = 0;
        field_0x10 = 0;
        mUpdateMaterialNum = 0;
        mUpdateMaterialID = 0;
        mKind = 1;
    }
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmColor() {}
    virtual void getColor(u16, GXColor*) const {}

    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    bool isValidUpdateMaterialID(u16 id) const { return mUpdateMaterialID[id] != 0xFFFF; }
    u16 getUpdateMaterialID(u16 idx) const {
        J3D_ASSERT(1578, idx < mUpdateMaterialNum, "Error : range over.");
        return mUpdateMaterialID[idx];
    }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }

protected:
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ u16 mUpdateMaterialNum;
    /* 0x1C */ u16* mUpdateMaterialID;
    /* 0x20 */ JUTNameTab mUpdateMaterialName;
};  // Size: 0x30

class J3DAnmColorKey : public J3DAnmColor {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmColorKey() {
        mColorR = NULL;
        mColorG = NULL;
        mColorB = NULL;
        mColorA = NULL;
        mTable = NULL;
    }

    virtual ~J3DAnmColorKey() {}
    virtual void getColor(u16, GXColor*) const;

private:
    /* 0x30 */ s16* mColorR;
    /* 0x34 */ s16* mColorG;
    /* 0x38 */ s16* mColorB;
    /* 0x3C */ s16* mColorA;
    /* 0x40 */ J3DAnmColorKeyTable* mTable;
};

class J3DAnmColorFull : public J3DAnmColor {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmColorFull() {
        mColorR = NULL;
        mColorG = NULL;
        mColorB = NULL;
        mColorA = NULL;
        mAnmTable = NULL;
    }

    virtual ~J3DAnmColorFull() {}
    virtual void getColor(u16, GXColor*) const;

    J3DAnmColorFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x30 */ u8 * mColorR;
    /* 0x34 */ u8 * mColorG;
    /* 0x38 */ u8 * mColorB;
    /* 0x3C */ u8 * mColorA;
    /* 0x40 */ J3DAnmColorFullTable * mAnmTable;
};

class J3DAnmVtxColorIndexData {
public:
    /* 0x00 */ u16 mNum;
    /* 0x04 */ void* mpData;
};

class J3DAnmVtxColor : public J3DAnmBase {
public:
    J3DAnmVtxColor() : J3DAnmBase(0) {
        mKind = 7;
        for (int i = 0; i < 2; i++) {
            mAnmTableNum[i] = 0;
        }
        for (int i = 0; i < 2; i++) {
            mAnmVtxColorIndexData[i] = NULL;
        }
    }

    virtual ~J3DAnmVtxColor() {}
    virtual void getColor(u8, u16, GXColor*) const {}

protected:
    /* 0x10 */ u16 mAnmTableNum[2];
    /* 0x14 */ J3DAnmVtxColorIndexData* mAnmVtxColorIndexData[2];
};  // Size: 0x1C

class J3DAnmVtxColorKey : public J3DAnmVtxColor {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmVtxColorKey() {
        for (int i = 0; i < 2; i++) {
            mpTable[i] = NULL;
        }
    }

    virtual ~J3DAnmVtxColorKey() {}
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorKeyTable * getAnmTable(u8 idx) const { return mpTable[idx]; }

protected:
    /* 0x1C */ J3DAnmColorKeyTable* mpTable[2];
    /* 0x24 */ s16* mColorR;
    /* 0x28 */ s16* mColorG;
    /* 0x2C */ s16* mColorB;
    /* 0x30 */ s16* mColorA;
};

class J3DAnmVtxColorFull : public J3DAnmVtxColor {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmVtxColorFull() {
        for (int i = 0; i < 2; i++) {
            mpTable[i] = NULL;
        }
    }

    virtual ~J3DAnmVtxColorFull() {}
    virtual void getColor(u8, u16, GXColor*) const;

    J3DAnmColorFullTable * getAnmTable(u8 idx) const { return mpTable[idx]; }

protected:
    /* 0x1C */ J3DAnmColorFullTable* mpTable[2];
    /* 0x24 */ u8* mColorR;
    /* 0x28 */ u8* mColorG;
    /* 0x2C */ u8* mColorB;
    /* 0x30 */ u8* mColorA;
};

class J3DAnmCluster : public J3DAnmBase {
public:
    J3DAnmCluster(s16 param_1, f32* param_2) : J3DAnmBase(0) {
        mWeight = param_2;
        mKind = param_1;
    }
    virtual ~J3DAnmCluster() {}
    virtual f32 getWeight(u16) const { return 1.0f; }

protected:
    /* 0x10 */ f32* mWeight;
};  // Size: 0x14

// BLA
class J3DAnmClusterFull : public J3DAnmCluster {
public:
    friend class J3DAnmFullLoader_v15;

    J3DAnmClusterFull() : J3DAnmCluster(3, 0) {
        mAnmTable = NULL;
    }
    virtual ~J3DAnmClusterFull() {}
    virtual f32 getWeight(u16) const;

    J3DAnmClusterFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x14 */ J3DAnmClusterFullTable * mAnmTable;
};

// BLK
class J3DAnmClusterKey : public J3DAnmCluster {
public:
    friend class J3DAnmKeyLoader_v15;

    J3DAnmClusterKey() : J3DAnmCluster(3, NULL) {
        mAnmTable = NULL;
    }
    virtual ~J3DAnmClusterKey() {}
    virtual f32 getWeight(u16) const;

private:
    /* 0x14 */ J3DAnmClusterKeyTable* mAnmTable;
};

class J3DFrameCtrl {
public:
    enum Attribute_e {
        /*  -1 */ EMode_NULL = -1,
        /* 0x0 */ EMode_NONE,
        /* 0x1 */ EMode_RESET,
        /* 0x2 */ EMode_LOOP,
        /* 0x3 */ EMode_REVERSE,
        /* 0x4 */ EMode_LOOP_REVERSE,
    };

    enum State_e {
        /* 0x1 */ STATE_STOP_E = 0x1,
        /* 0x2 */ STATE_LOOP_E = 0x2,
    };

    J3DFrameCtrl() { this->init(0); }
    void init(s16 end);
    BOOL checkPass(f32);
    void update();
    virtual ~J3DFrameCtrl() {}

    u8 getAttribute() const { return mAttribute; }
    void setAttribute(u8 attr) { mAttribute = attr; }
    u8 getState() const { return mState; }
    bool checkState(u8 state) const { return mState & state ? true : false; }
    s16 getStart() const { return mStart; }
    void setStart(s16 start) {
        mStart = start;
        mFrame = start;
    }
    s16 getEnd() const { return mEnd; }
    void setEnd(s16 end) { mEnd = end; }
    s32 getLoop() const { return mLoop; }
    void setLoop(s16 loop) { mLoop = loop; }
    f32 getRate() const { return mRate; }
    void setRate(f32 rate) { mRate = rate; }
    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }

private:
    /* 0x04 */ u8 mAttribute;
    /* 0x05 */ u8 mState;
    /* 0x06 */ s16 mStart;
    /* 0x08 */ s16 mEnd;
    /* 0x0A */ s16 mLoop;
    /* 0x0C */ f32 mRate;
    /* 0x10 */ f32 mFrame;
};  // Size: 0x14

#endif /* J3DANIMATION_H */
