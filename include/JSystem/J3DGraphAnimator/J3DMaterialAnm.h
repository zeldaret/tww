#ifndef J3DMATERIALANM_H
#define J3DMATERIALANM_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

typedef struct _GXColor GXColor;
typedef struct _GXColorS10 GXColorS10;

class J3DMatColorAnm {
public:
    ~J3DMatColorAnm() {}
    J3DMatColorAnm() {}
    J3DMatColorAnm(J3DAnmColor * pAnm, u16 materialIdx) {
        mAnmColor = pAnm;
        mMaterialIdx = materialIdx;
    }

    void operator=(J3DMatColorAnm const& other) {
        mAnmColor = other.mAnmColor;
        mMaterialIdx = other.mMaterialIdx;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void calc(_GXColor* pColor) const { mAnmColor->getColor(mMaterialIdx, pColor); }

private:
    /* 0x0 */ u16 mMaterialIdx;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmColor* mAnmColor;
};  // Size: 0x8

class J3DTexNoAnm {
public:
    ~J3DTexNoAnm() {};
    J3DTexNoAnm() {};
    virtual void calc(u16* param_0) const { mAnmTexPattern->getTexNo(field_0x4, param_0); }

    void operator=(J3DTexNoAnm const& other) {
        mAnmTexPattern = other.mAnmTexPattern;
        field_0x4 = other.field_0x4;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    J3DAnmTexPattern* getAnmTexPattern() { return mAnmTexPattern; }

private:
    /* 0x4 */ u16 field_0x4;
    /* 0x6 */ u16 mAnmFlag;
    /* 0x8 */ J3DAnmTexPattern* mAnmTexPattern;
};  // Size: 0xC

class J3DTexMtxAnm {
public:
    ~J3DTexMtxAnm() {}
    J3DTexMtxAnm() {}
    J3DTexMtxAnm(J3DAnmTextureSRTKey * pAnm, u16 materialIdx) {
        mAnmTransform = pAnm;
        mMaterialIdx = materialIdx;
    }

    void operator=(J3DTexMtxAnm const& other) {
        mAnmTransform = other.mAnmTransform;
        mMaterialIdx = other.mMaterialIdx;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    void calc(J3DTextureSRTInfo* pSRTInfo) const {
        mAnmTransform->getTransform(mMaterialIdx, pSRTInfo);
    }
    bool getAnmFlag() const { return mAnmFlag; }

private:
    /* 0x0 */ u16 mMaterialIdx;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmTextureSRTKey* mAnmTransform;
};  // Size: 0x8

class J3DTevKColorAnm {
public:
    ~J3DTevKColorAnm() {}
    J3DTevKColorAnm() {}
    J3DTevKColorAnm(J3DAnmTevRegKey * pAnm, u16 materialIdx) {
        mAnmTevReg = pAnm;
        mMaterialIdx = materialIdx;
    }

    void operator=(J3DTevKColorAnm const& other) {
        mAnmTevReg = other.mAnmTevReg;
        mMaterialIdx = other.mMaterialIdx;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void calc(_GXColor* pColor) const { mAnmTevReg->getTevKonstReg(mMaterialIdx, pColor); }

private:
    /* 0x0 */ u16 mMaterialIdx;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmTevRegKey* mAnmTevReg;
};  // Size: 0x8

class J3DTevColorAnm {
public:
    ~J3DTevColorAnm() {}
    J3DTevColorAnm() {}
    J3DTevColorAnm(J3DAnmTevRegKey * pAnm, u16 materialIdx) {
        mAnmTevReg = pAnm;
        mMaterialIdx = materialIdx;
    }

    void operator=(J3DTevColorAnm const& other) {
        mAnmTevReg = other.mAnmTevReg;
        mMaterialIdx = other.mMaterialIdx;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void calc(_GXColorS10* pColor) const { mAnmTevReg->getTevColorReg(mMaterialIdx, pColor); }

private:
    /* 0x0 */ u16 mMaterialIdx;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmTevRegKey* mAnmTevReg;
};  // Size: 0x8

class J3DMaterialAnm {
public:
    J3DMaterialAnm() { initialize(); }

    void initialize();
    inline void setMatColorAnm(int i, J3DMatColorAnm* pAnm) { mMatColorAnm[i] = pAnm; }
    inline void setTexMtxAnm(int i, J3DTexMtxAnm* pAnm) { mTexMtxAnm[i] = pAnm; }
    inline void setTexNoAnm(int i, J3DTexNoAnm* pAnm) { mTexNoAnm[i] = pAnm; }
    inline void setTevColorAnm(int i, J3DTevColorAnm* pAnm) { mTevColorAnm[i] = pAnm; }
    inline void setTevKColorAnm(int i, J3DTevKColorAnm* pAnm) { mTevKColorAnm[i] = pAnm; }

    virtual ~J3DMaterialAnm() {};
    virtual void calc(J3DMaterial*) const;

    const J3DTexMtxAnm& getTexMtxAnm(int i) const { return *mTexMtxAnm[i]; }

private:
    /* 0x04 */ J3DMatColorAnm * mMatColorAnm[2];
    /* 0x14 */ J3DTexMtxAnm * mTexMtxAnm[8];
    /* 0x54 */ J3DTexNoAnm * mTexNoAnm[8];
    /* 0xB4 */ J3DTevColorAnm * mTevColorAnm[4];
    /* 0xD4 */ J3DTevKColorAnm * mTevKColorAnm[4];
};  // Size: 0xF4

#endif /* J3DMATERIALANM_H */
