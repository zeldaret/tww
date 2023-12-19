#ifndef J3DJOINT_H
#define J3DJOINT_H

#include "JSystem/J3DGraphAnimator/J3DNode.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"

class J3DAnmTransform;
class J3DJoint;
class J3DMaterial;
class J3DMtxBuffer;

class J3DMtxCalc {
public:
    virtual void init(const Vec&, const Mtx&) {}
    virtual void recursiveCalc(J3DNode*) {}
    virtual void calcTransform(u16, const J3DTransformInfo&) {}
    virtual void calc(u16) {}

    void initAnm() {
        for (int i = 0; i < 4; i++) {
            mOne[i] = 0;
            mTwo[i] = 0.0f;
        }
    }
    void setAnmTransform(J3DAnmTransform* mAnmTransform) { mOne[0] = mAnmTransform; }

public:
    J3DAnmTransform* mOne[4];
    f32 mTwo[4];
};

class J3DMtxCalcAnm : public virtual J3DMtxCalc {
public:
    J3DMtxCalcAnm(J3DAnmTransform* mAnmTransform) : J3DMtxCalc() {
        initAnm();
        setAnmTransform(mAnmTransform);
    }
    virtual ~J3DMtxCalcAnm() { initAnm(); }
    virtual void calc(u16);
};

class J3DMtxCalcBasic : public virtual J3DMtxCalc {
private:
    Mtx mBackupMtx;
    Vec mBackupS;
    Vec mBackupParentS;

public:
    J3DMtxCalcBasic();
    // TODO: vtable is in wrong order, but fixing it breaks J3DUMotion
    virtual void recursiveCalc(J3DNode*);
    virtual void calcTransform(u16, const J3DTransformInfo&);
    virtual void calc(u16);
    virtual ~J3DMtxCalcBasic() {}
    virtual void init(const Vec& vec, const Mtx& mtx);

    Mtx& getBackupMtx() { return mBackupMtx; }
    Vec& getBackupS() { return mBackupS; }
    Vec& getBackupParentS() { return mBackupParentS; }

    void setBackupS(const Vec& vec) { mBackupS = vec; }
    void setBackupParentS(const Vec& vec) { mBackupParentS = vec; }
};

class J3DMtxCalcSoftimage : public J3DMtxCalcBasic {
public:
    J3DMtxCalcSoftimage() : J3DMtxCalc() {}
    virtual void calcTransform(u16, const J3DTransformInfo&);
    virtual ~J3DMtxCalcSoftimage();
    virtual void init(const Vec& vec, const Mtx& mtx);
};

class J3DMtxCalcMaya : public J3DMtxCalcBasic {
public:
    J3DMtxCalcMaya() : J3DMtxCalcBasic() {}
    virtual ~J3DMtxCalcMaya() {}
    virtual void init(const Vec& vec, const Mtx& mtx) {
        // TODO: This breaks some TUs by adding extra data ({0x3F800000, 0x3F800000, 0x3F800000})
        // J3DSys::mParentS = (Vec){1.0f, 1.0f, 1.0f};
        J3DSys::mCurrentS = vec;
        J3DSys::mCurrentMtx[0][0] = mtx[0][0] * J3DSys::mCurrentS.x;
        J3DSys::mCurrentMtx[0][1] = mtx[0][1] * J3DSys::mCurrentS.y;
        J3DSys::mCurrentMtx[0][2] = mtx[0][2] * J3DSys::mCurrentS.z;
        J3DSys::mCurrentMtx[0][3] = mtx[0][3];
        J3DSys::mCurrentMtx[1][0] = mtx[1][0] * J3DSys::mCurrentS.x;
        J3DSys::mCurrentMtx[1][1] = mtx[1][1] * J3DSys::mCurrentS.y;
        J3DSys::mCurrentMtx[1][2] = mtx[1][2] * J3DSys::mCurrentS.z;
        J3DSys::mCurrentMtx[1][3] = mtx[1][3];
        J3DSys::mCurrentMtx[2][0] = mtx[2][0] * J3DSys::mCurrentS.x;
        J3DSys::mCurrentMtx[2][1] = mtx[2][1] * J3DSys::mCurrentS.y;
        J3DSys::mCurrentMtx[2][2] = mtx[2][2] * J3DSys::mCurrentS.z;
        J3DSys::mCurrentMtx[2][3] = mtx[2][3];
    }
    virtual void calcTransform(u16, const J3DTransformInfo&);
};

class J3DMtxCalcMayaAnm : public J3DMtxCalcMaya, public J3DMtxCalcAnm {
public:
    J3DMtxCalcMayaAnm(J3DAnmTransform* pAnmTransform)
        : J3DMtxCalcMaya(), J3DMtxCalcAnm(pAnmTransform) {}
    virtual ~J3DMtxCalcMayaAnm() {}
    virtual void calc(u16 v) { J3DMtxCalcAnm::calc(v); }
};

enum J3DJointMtxType {
    J3DJntMtxType_Normal,
    J3DJntMtxType_BBoard,
    J3DJntMtxType_YBBoard,
    J3DJntMtxType_Multi,
};

class J3DJoint : public J3DNode {
public:
    void initialize();
    void addMesh(J3DMaterial*);
    void calcIn();
    void calcOut();
    void entryIn();
    u32 getType() const { return 'NJNT'; }
    void recursiveCalc();

    J3DJoint() { initialize(); }
    ~J3DJoint() {}

    J3DMaterial* getMesh() { return mMesh; }
    u16 getJntNo() const { return mJntNo; }
    u8 getKind() const { return mKind & 0x0F; }
    u8 getMtxType() const { return (mKind >> 4) & 0x0F; }
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
    void setMtxType(u8 type) { mKind = (mKind & ~0xf0) | (type << 4); }

    static J3DMtxCalc* mCurrentMtxCalc;

private:
    friend struct J3DJointFactory;
    friend class J3DJointTree;

    /* 0x18 */ u16 mJntNo;
    /* 0x1A */ u8 mKind;
    /* 0x1B */ u8 mScaleCompensate;
    /* 0x1C */ J3DTransformInfo mTransformInfo;
    /* 0x3C */ f32 mRadius;
    /* 0x40 */ Vec mMin;
    /* 0x4C */ Vec mMax;
    /* 0x58 */ J3DMtxCalc* mMtxCalc;
    /* 0x5C */ J3DMtxCalc* mOldMtxCalc;
    /* 0x60 */ J3DMaterial* mMesh;
};  // Size: 0x64

#endif /* J3DJOINT_H */
