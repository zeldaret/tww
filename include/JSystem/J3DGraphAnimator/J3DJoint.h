#ifndef J3DJOINT_H
#define J3DJOINT_H

#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"

class J3DAnmTransform;
class J3DJoint;
class J3DMaterial;
class J3DMtxBuffer;

class J3DMtxCalc {
public:
    static void setMtxBuffer(J3DMtxBuffer*);

    virtual ~J3DMtxCalc();
    virtual void init(Vec const& param_0, const Mtx&) = 0;
    virtual void recursiveCalc(J3DNode *);
    virtual void calc() = 0;
    virtual void calcTransform(u16, J3DTransformInfo const &) = 0;

    static J3DMtxBuffer* getMtxBuffer() { return mMtxBuffer; }
    static J3DJoint* getJoint() { return mJoint; }
    static void setJoint(J3DJoint* joint) { mJoint = joint; }

    static J3DMtxBuffer* mMtxBuffer;
    static J3DJoint* mJoint;
};  // Size: 0x4

class J3DMtxCalcNoAnmBase : public J3DMtxCalc {
public:
    virtual ~J3DMtxCalcNoAnmBase();
};

template <class A, class B>
class J3DMtxCalcNoAnm : public J3DMtxCalcNoAnmBase, public A, public B {
public:
    J3DMtxCalcNoAnm() {}
    virtual ~J3DMtxCalcNoAnm() {}
    virtual void init(Vec const& param_0, f32 const (&param_1)[3][4]);
    virtual void calc();
};

class J3DJoint : public J3DNode {
public:
    J3DJoint();
    void entryIn();
    void recursiveCalc();

    J3DMaterial* getMesh() { return mMesh; }
    u16 getJntNo() const { return mJntNo; }
    u8 getScaleCompensate() const { return mScaleCompensate; }
    void setCurrentMtxCalc(J3DMtxCalc* pMtxCalc) { mCurrentMtxCalc = pMtxCalc; }
    J3DTransformInfo& getTransformInfo() { return mTransformInfo; }
    Vec* getMax() { return &mMax; }
    Vec* getMin() { return &mMin; }
    void setMtxCalc(J3DMtxCalc* i_mtxCalc) { mMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getMtxCalc() { return mMtxCalc; }
    void setOldMtxCalc(J3DMtxCalc* i_mtxCalc) { mOldMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getOldMtxCalc() { return mOldMtxCalc; }
    J3DMtxCalc* getCurrentMtxCalc() { return mCurrentMtxCalc; };

    static J3DMtxCalc* mCurrentMtxCalc;

private:
    friend struct J3DJointFactory;
    friend class J3DJointTree;

    /* 0x14 */ u16 mJntNo;
    /* 0x1A */ u8 mKind;
    /* 0x1B */ u8 mScaleCompensate;
    /* 0x1C */ J3DTransformInfo mTransformInfo;
    /* 0x3C */ f32 mBoundingSphereRadius;
    /* 0x40 */ Vec mMin;
    /* 0x4C */ Vec mMax;
    /* 0x58 */ J3DMtxCalc* mMtxCalc;
    /* 0x5C */ J3DMtxCalc* mOldMtxCalc;
    /* 0x60 */ J3DMaterial* mMesh;
};  // Size: 0x54

struct J3DMtxCalcJ3DSysInitMaya {
    static void init(Vec const&, f32 const (&)[3][4]);
};

struct J3DMtxCalcJ3DSysInitBasic {
    static void init(Vec const&, f32 const (&)[3][4]);
};

struct J3DMtxCalcCalcTransformSoftimage {
    static void calcTransform(J3DTransformInfo const&);
};

struct J3DMtxCalcCalcTransformMaya {
    static void calcTransform(J3DTransformInfo const&);
};

struct J3DMtxCalcCalcTransformBasic {
    static void calcTransform(J3DTransformInfo const&);
};

#endif /* J3DJOINT_H */
