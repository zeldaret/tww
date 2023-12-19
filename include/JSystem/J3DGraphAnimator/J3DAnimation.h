#ifndef J3DANIMATION_H
#define J3DANIMATION_H

#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "global.h"

typedef struct _GXColor GXColor;
typedef struct _GXColorS10 GXColorS10;

struct J3DAnmKeyTableBase {
    /* 0x00 */ u16 mMaxFrame;
    /* 0x02 */ u16 mOffset;
    /* 0x04 */ u16 mType;
};  // Size = 0x6

struct J3DAnmColorKeyTable {
    J3DAnmKeyTableBase mRInfo;
    J3DAnmKeyTableBase mGInfo;
    J3DAnmKeyTableBase mBInfo;
    J3DAnmKeyTableBase mAInfo;
};  // Size = 0x18

struct J3DAnmVtxColorIndexData;

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
    J3DAnmKeyTableBase mScaleInfo;
    J3DAnmKeyTableBase mRotationInfo;
    J3DAnmKeyTableBase mTranslateInfo;
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

struct J3DAnmDataBlockHeader {  // actual name unknown
    /* 0x0 */ u32 mType;
    /* 0x4 */ u32 mNextOffset;
};  // Size = 0x8

struct J3DAnmDataHeader {  // actual name unknown
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ u32 mType;
    /* 0x08 */ u8 _8[4];
    /* 0x0C */ u32 mCount;
    /* 0x10 */ u8 _10[0x20 - 0x10];
    /* 0x20 */ J3DAnmDataBlockHeader mFirst;
};

struct J3DAnmVtxColorFullData {
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;  // padding?
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 mAnmTableNum[2];
    /* 0x10 */ u8 field_0x10[0x18 - 0x10];
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9[3];
    /* 0x0C */ s16 mFrameMax;
    /* 0x0E */ u16 mUpdateMaterialNum;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ s32 mTableOffset; /* Created by retype action */
    /* 0x1C */ s32 mUpdateMaterialIDOffset;
    /* 0x20 */ s32 mNameTabOffset; /* Created by retype action */
    /* 0x24 */ s32 mRValOffset;
    /* 0x28 */ s32 mGValOffset;
    /* 0x2C */ s32 mBValOffset;
    /* 0x30 */ s32 mAValOffset;
};  // Size = 0x34

STATIC_ASSERT(sizeof(J3DAnmColorKeyData) == 0x34);

struct J3DAnmTextureSRTKeyData {
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ s16 mFrameMax;
    /* 0x0C */ u16 mAnmTableNum[2];
    /* 0x10 */ u8 field_0x10[0x18 - 0x10];
    /* 0x18 */ s32 mTableOffsets[2];
    /* 0x20 */ s32 mVtxColoIndexDataOffset[2];
    /* 0x28 */ s32 mVtxColoIndexPointerOffset[2];
    /* 0x30 */ s32 mRValOffset;
    /* 0x34 */ s32 mGValOffset;
    /* 0x38 */ s32 mBValOffset;
    /* 0x3C */ s32 mAValOffset;
};  // Size = 0x40

STATIC_ASSERT(sizeof(J3DAnmVtxColorKeyData) == 0x40);

struct J3DAnmTexPatternFullData {
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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
    /* 0x00 */ J3DAnmDataBlockHeader mHeader;
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

private:
    /* 0x4 */ u8 mAttribute;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ s16 mFrameMax;
    /* 0x8 */ f32 mFrame;
};  // Size: 0xC

class J3DAnmTransform : public J3DAnmBase {
public:
    J3DAnmTransform(s16 i_frameMax, f32* p1, s16* p2, f32* p3) : J3DAnmBase(i_frameMax) {
        field_0x10 = p2;
        field_0x14 = p3;
        field_0x18 = 0;
        field_0xc = p1;
    }

    virtual ~J3DAnmTransform() {}
    virtual void getTransform(u16, J3DTransformInfo*) const = 0;

private:
    /* 0x0C */ f32* field_0xc;
    /* 0x10 */ s16* field_0x10;
    /* 0x14 */ f32* field_0x14;
    /* 0x18 */ s32 field_0x18;
    /* 0x1C */ s16 field_0x1a;
    /* 0x1E */ s16 field_0x1c;
    /* 0x20 */ s16 field_0x1e;
};  // Size: 0x22

class J3DAnmTransformKey : public J3DAnmTransform {
public:
    J3DAnmTransformKey() : J3DAnmTransform(0, NULL, NULL, NULL) {
        field_0x24 = 0;
        field_0x28 = 0;
    }

    virtual void calcTransform(f32, u16, J3DTransformInfo*) const;

    virtual ~J3DAnmTransformKey() {}
    virtual void getTransform(u16 param_1, J3DTransformInfo* param_2) const { calcTransform(getFrame(), param_1, param_2); }

private:
    /* 0x24 */ int field_0x24;
    /* 0x28 */ int field_0x28;
};  // Size: 0x2C

class J3DAnmTransformFull : public J3DAnmTransform {
public:
    virtual ~J3DAnmTransformFull();
    virtual void getTransform(u16, J3DTransformInfo*) const;

private:
    /* 0x20 */ int field_0x20;
};  // Size: 0x24

struct J3DTextureSRTInfo;
class J3DModelData;
class J3DMaterialTable;

class J3DAnmTextureSRTKey : public J3DAnmBase {
public:
    J3DAnmTextureSRTKey();
    void calcTransform(f32, u16, J3DTextureSRTInfo*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTextureSRTKey();
    virtual s32 getKind() const;

    void getTransform(u16 param_0, J3DTextureSRTInfo* pSRTInfo) const {
        calcTransform(getFrame(), param_0, pSRTInfo);
    }

    u16 getUpdateMaterialID(u16 idx) const { return mUpdateMaterialID[idx]; }
    u16 getUpdateMaterialNum() const { return mTrackNum / 3; }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }
    u16 getUpdateTexMtxID(u16 idx) const { return mUpdateTexMtxID[idx]; }

    u16 getPostUpdateMaterialID(u16 idx) const { return mPostUpdateMaterialID[idx]; }
    u16 getPostUpdateMaterialNum() const { return mPostTrackNum / 3; }
    JUTNameTab * getPostUpdateMaterialName() { return &mPostUpdateMaterialName; }
    u16 getPostUpdateTexMtxID(u16 idx) const { return mPostUpdateTexMtxID[idx]; }

    u32 getTexMtxCalcType() const { return mTexMtxCalcType; }
    Vec& getSRTCenter(u16 idx) const { return mSRTCenter[idx]; }

private:
    /* 0x0C */ void* field_0xc;
    /* 0x10 */ int mDecShift;
    /* 0x14 */ u16 mTrackNum;
    /* 0x18 */ void* mAnmTable;
    /* 0x1C */ u16 mScaleNum;
    /* 0x1E */ u16 mRotNum;
    /* 0x20 */ u16 mTransNum;
    /* 0x24 */ f32* mScaleData;
    /* 0x28 */ f32* mRotData;
    /* 0x2C */ f32* mTransData;
    /* 0x30 */ u8* mUpdateTexMtxID;
    /* 0x34 */ u16* mUpdateMaterialID;
    /* 0x38 */ JUTNameTab mUpdateMaterialName;
    /* 0x48 */ Vec* mSRTCenter;
    /* 0x4C */ void * field_0x4c;
    /* 0x50 */ void * mPostAnmTable;
    /* 0x54 */ void * field_0x54;
    /* 0x58 */ void * field_0x58;
    /* 0x5C */ void * field_0x5c;
    /* 0x60 */ u16 mPostTrackNum;
    /* 0x64 */ void * field_0x60;
    /* 0x68 */ u8* mPostUpdateTexMtxID;
    /* 0x6C */ u16* mPostUpdateMaterialID;
    /* 0x70 */ JUTNameTab mPostUpdateMaterialName;
    /* 0x80 */ Vec* mPostSRTCenter;
    /* 0x84 */ u32 mTexMtxCalcType;
};  // Size: 0x88

STATIC_ASSERT(sizeof(J3DAnmTextureSRTKey) == 0x88);

class J3DAnmVisibilityFull : public J3DAnmBase {
public:
    J3DAnmVisibilityFull();
    void getVisibility(u16, u8*) const;

    virtual ~J3DAnmVisibilityFull();
    virtual s32 getKind() const;

    J3DAnmVisibilityFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x0C */ void* field_0xc;
    /* 0x10 */ u16 mUpdateMaterialNum;
    /* 0x14 */ J3DAnmVisibilityFullTable * mAnmTable;
    /* 0x18 */ u8* mVisibility;
    /* 0x1C */ JUTNameTab field_0x1c;
};  // Size: 0x2C

class J3DAnmTexPattern : public J3DAnmBase {
public:
    J3DAnmTexPattern();
    void getTexNo(u16, u16*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    u16 getUpdateMaterialID(u16 idx) const { return mUpdateMaterialID[idx]; }
    u16 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }

    J3DAnmTexPatternFullTable * getAnmTable() const { return mAnmTable; }

    virtual ~J3DAnmTexPattern();
    virtual s32 getKind() const;

private:
    /* 0x0C */ void* field_0xc;
    /* 0x10 */ u16* mTextureIndex;
    /* 0x14 */ J3DAnmTexPatternFullTable* mAnmTable;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 mUpdateMaterialNum;
    /* 0x1C */ u16* mUpdateMaterialID;
    /* 0x20 */ JUTNameTab mUpdateMaterialName;
};  // Size: 0x2C

class J3DAnmTevRegKey : public J3DAnmBase {
public:
    J3DAnmTevRegKey();
    void getTevColorReg(u16, GXColorS10*) const;
    void getTevKonstReg(u16, GXColor*) const;
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmTevRegKey() {}
    virtual s32 getKind() const;

    u16 getCRegUpdateMaterialNum() const { return mCRegUpdateMaterialNum; }
    u16 getKRegUpdateMaterialNum() const { return mKRegUpdateMaterialNum; }

    u16 getCRegUpdateMaterialID(u16 idx) const { return mCRegUpdateMaterialID[idx]; }
    u16 getKRegUpdateMaterialID(u16 idx) const { return mKRegUpdateMaterialID[idx]; }

    JUTNameTab * getCRegUpdateMaterialName() { return &mCRegUpdateMaterialName; }
    JUTNameTab * getKRegUpdateMaterialName() { return &mKRegUpdateMaterialName; }

    J3DAnmCRegKeyTable * getAnmCRegKeyTable() const { return mAnmCRegKeyTable; }
    J3DAnmKRegKeyTable * getAnmKRegKeyTable() const { return mAnmKRegKeyTable; }

private:
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ u16 mCRegUpdateMaterialNum;
    /* 0x12 */ u16 mKRegUpdateMaterialNum;
    /* 0x14 */ u16 mCRegDataCount[4];
    /* 0x1C */ u16 mKRegDataCount[4];
    /* 0x24 */ u16* mCRegUpdateMaterialID;
    /* 0x28 */ JUTNameTab mCRegUpdateMaterialName;
    /* 0x38 */ u16* mKRegUpdateMaterialID;
    /* 0x3C */ JUTNameTab mKRegUpdateMaterialName;
    /* 0x4C */ J3DAnmCRegKeyTable* mAnmCRegKeyTable;
    /* 0x50 */ J3DAnmKRegKeyTable* mAnmKRegKeyTable;
    /* 0x54 */ s16 * mAnmCRegData[4];
    /* 0x64 */ s16 * mAnmKRegData[4];
};  // Size: 0x74

class J3DAnmColor : public J3DAnmBase {
public:
    J3DAnmColor();
    void searchUpdateMaterialID(J3DMaterialTable*);
    void searchUpdateMaterialID(J3DModelData*);

    virtual ~J3DAnmColor();
    virtual void getColor(u16, GXColor*) const;

    s32 getUpdateMaterialNum() const { return mUpdateMaterialNum; }
    bool isValidUpdateMaterialID(u16 id) const { return mUpdateMaterialID[id] != 0xFFFF; }
    u16 getUpdateMaterialID(u16 idx) const { return mUpdateMaterialID[idx]; }
    JUTNameTab * getUpdateMaterialName() { return &mUpdateMaterialName; }

private:
    /* 0x0C */ u16 field_0xc;
    /* 0x0E */ u16 field_0xe;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ u16 mUpdateMaterialNum;
    /* 0x1C */ u16* mUpdateMaterialID;
    /* 0x20 */ JUTNameTab mUpdateMaterialName;
};  // Size: 0x30

class J3DAnmColorKey : public J3DAnmColor {
public:
    J3DAnmColorKey();

    virtual ~J3DAnmColorKey();
    virtual s32 getKind() const;
    virtual void getColor(u16, GXColor*) const;

private:
    /* 0x2C */ int field_0x2c;
    /* 0x30 */ int field_0x30;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
};

class J3DAnmColorFull : public J3DAnmColor {
public:
    J3DAnmColorFull();

    virtual ~J3DAnmColorFull();
    virtual s32 getKind() const;
    virtual void getColor(u16, GXColor*) const;

    J3DAnmColorFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x30 */ u8 * mColorR;
    /* 0x34 */ u8 * mColorG;
    /* 0x38 */ u8 * mColorB;
    /* 0x3C */ u8 * mColorA;
    /* 0x40 */ J3DAnmColorFullTable * mAnmTable;
};

class J3DAnmVtxColor : public J3DAnmBase {
public:
    J3DAnmVtxColor();

    virtual ~J3DAnmVtxColor();
    virtual s32 getKind() const;
    virtual void getColor(u8, u16, GXColor*) const {}

private:
    /* 0x0C */ s16 mAnmTableNum[2];
    /* 0x10 */ int mAnmVtxColorIndexData[2];
};  // Size: 0x18

class J3DAnmVtxColorKey : public J3DAnmVtxColor {
public:
    J3DAnmVtxColorKey();

    virtual ~J3DAnmVtxColorKey();
    virtual s32 getKind() const;
    virtual void getColor(u8, u16, GXColor*) const;

private:
    /* 0x18 */ int field_0x18[2];
};

class J3DAnmVtxColorFull : public J3DAnmVtxColor {
    J3DAnmVtxColorFull();

    virtual ~J3DAnmVtxColorFull();
    virtual s32 getKind() const;
    virtual void getColor(u8, u16, GXColor*) const;

private:
    /* 0x18 */ int field_0x18[2];
};

class J3DAnmCluster : public J3DAnmBase {
public:
    virtual ~J3DAnmCluster() {}
    virtual s32 getKind() const;
    virtual f32 getWeight(u16) const { return 1.0f; }

private:
    /* 0x0C */ f32* field_0xc;
};  // Size: 0x10

class J3DAnmClusterFull : public J3DAnmCluster {
public:
    virtual ~J3DAnmClusterFull() {}
    virtual s32 getKind() const;
    virtual f32 getWeight(u16) const;

    J3DAnmVisibilityFullTable * getAnmTable() const { return mAnmTable; }

private:
    /* 0x10 */ f32 * mWeight;
    /* 0x14 */ J3DAnmVisibilityFullTable * mAnmTable;
};

class J3DAnmClusterKey : public J3DAnmCluster {
public:
    virtual ~J3DAnmClusterKey() {}
    virtual s32 getKind() const;
    virtual f32 getWeight(u16) const;

private:
    /* 0x10 */ int field_0x10;
};

class J3DFrameCtrl {
public:
    enum Attribute_e {
        LOOP_ONCE_e,
        LOOP_ONCE_RESET_e,
        LOOP_REPEAT_e,
        LOOP_MIRROR_ONCE_e,
        LOOP_MIRROR_REPEAT_e,
    };

    enum State_e {
        STATE_STOP_E = 0x1,
        STATE_LOOP_E = 0x2,
    };

    J3DFrameCtrl() { this->init(0); }
    void init(s16 end);
    BOOL checkPass(f32);
    void update();
    virtual ~J3DFrameCtrl() {}

    u8 getAttribute() const { return mAttribute; }
    void setAttribute(u8 attr) { mAttribute = attr; }
    u8 getState() const { return mState; }
    bool checkState(u8 state) const { return mState & state; }
    s16 getStart() const { return mStart; }
    void setStart(s16 start) {
        mStart = start;
        mFrame = start;
    }
    s16 getEnd() const { return mEnd; }
    void setEnd(s16 end) { mEnd = end; }
    s32 getLoop() { return mLoop; }
    void setLoop(s16 loop) { mLoop = loop; }
    f32 getRate() const { return mRate; }
    void setRate(f32 rate) { mRate = rate; }
    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }

public:
    /* 0x04 */ u8 mAttribute;
    /* 0x05 */ u8 mState;
    /* 0x06 */ s16 mStart;
    /* 0x08 */ s16 mEnd;
    /* 0x0A */ s16 mLoop;
    /* 0x0C */ f32 mRate;
    /* 0x10 */ f32 mFrame;
};  // Size: 0x14

#endif /* J3DANIMATION_H */
