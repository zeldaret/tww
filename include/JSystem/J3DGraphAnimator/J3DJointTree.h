#ifndef J3DJOINTTREE_H
#define J3DJOINTTREE_H

#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "dolphin/types.h"
#include "global.h"

class JUTNameTab;

struct J3DModelHierarchy {
    /* 0x0 */ u16 mType; // TODO enum
    /* 0x2 */ u16 mValue;

    inline u16 getValue() const { return mValue; }
};

class J3DMaterialTable;

struct J3DDrawMtxData {
    J3DDrawMtxData();
    ~J3DDrawMtxData();

    /* 0x0 */ u16 mEntryNum;
    /* 0x2 */ u16 mDrawFullWgtMtxNum;
    /* 0x4 */ u8* mDrawMtxFlag;
    /* 0x8 */ u16* mDrawMtxIndex;
};  // Size: 0xC

class J3DShapeTable;
class J3DShape;

class J3DJointTree {
public:
    J3DJointTree() { clear(); }
    void clear();
    void makeHierarchy(J3DNode*, const J3DModelHierarchy**, J3DMaterialTable*, J3DShape**);

    virtual ~J3DJointTree() {}

    J3DDrawMtxData * getDrawMtxData() { return &mDrawMtxData; }
    u16 getWEvlpMtxNum() const { return mWEvlpMtxNum; }
    u8 getWEvlpMixMtxNum(u16 idx) const { return mWEvlpMixMtxNum[idx]; }
    u16 * getWEvlpMixIndex() const { return mWEvlpMixIndex; }
    f32 * getWEvlpMixWeight() { return mWEvlpMixWeight; }
    u16 getDrawFullWgtMtxNum() const { return mDrawMtxData.mDrawFullWgtMtxNum; }
    u16 getJointNum() const { return mJointNum; }
    u16 getDrawMtxNum() const { return mDrawMtxData.mEntryNum; }
    u8 getDrawMtxFlag(u16 idx) const { return mDrawMtxData.mDrawMtxFlag[idx]; }
    u16 getDrawMtxIndex(u16 idx) const { return mDrawMtxData.mDrawMtxIndex[idx]; }
    JUTNameTab* getJointName() const { return mJointName; }
    const J3DModelHierarchy* getHierarchy() const { return mHierarchy; }
    void setHierarchy(J3DModelHierarchy* hierarchy) { mHierarchy = hierarchy; }
    void setBasicMtxCalc(J3DMtxCalc* calc) { mBasicMtxCalc = calc; }
    J3DJoint* getRootNode() { return mRootNode; }
    J3DJoint* getJointNodePointer(u16 idx) const { return mJointNodePointer[idx]; }
    J3DMtxCalc* getBasicMtxCalc() { return mBasicMtxCalc; }
    Mtx& getInvJointMtx(int idx) { return mInvJointMtx[idx]; }
    u32 getModelDataType() const { return mModelDataType; }
    void setModelDataType(u32 type) { mModelDataType = type; }
    bool checkFlag(u32 flag) { return mFlags & flag; }
    void setFlag(u32 flag) { mFlags = flag; }

    // TODO
    void getWEvlpMixMtxIndex() {}

private:
    friend class J3DModelLoader;

    /* 0x04 */ J3DModelHierarchy* mHierarchy;
    /* 0x08 */ u32 mFlags;
    /* 0x0C */ u32 mModelDataType;
    /* 0x10 */ J3DJoint* mRootNode;
    /* 0x14 */ J3DMtxCalc* mBasicMtxCalc;
    /* 0x18 */ u16 mJointNum;
    /* 0x1C */ J3DJoint** mJointNodePointer;
    /* 0x20 */ u16 mWEvlpMtxNum;
    /* 0x24 */ u8* mWEvlpMixMtxNum;
    /* 0x28 */ u16* mWEvlpMixIndex;
    /* 0x2C */ f32* mWEvlpMixWeight;
    /* 0x30 */ Mtx* mInvJointMtx;
    /* 0x34 */ J3DDrawMtxData mDrawMtxData;
    /* 0x40 */ u32 field_0x40;
    /* 0x44 */ JUTNameTab* mJointName;
};  // Size: 0x48

STATIC_ASSERT(sizeof(J3DJointTree) == 0x48);

#endif /* J3DJOINTTREE_H */
