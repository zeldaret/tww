#ifndef J3DMATERIALANM_H
#define J3DMATERIALANM_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

typedef struct _GXColor GXColor;
typedef struct _GXColorS10 GXColorS10;

class J3DMatColorAnm {
public:
    ~J3DMatColorAnm() {}
    J3DMatColorAnm() {
        mAnmColor = NULL;
        mAnmIndex = 0;
    }
    J3DMatColorAnm(J3DAnmColor* pAnm, u16 anmIdx) {
        mAnmColor = pAnm;
        mAnmIndex = anmIdx;
    }

    void operator=(J3DMatColorAnm const& other) {
        mAnmColor = other.mAnmColor;
        mAnmIndex = other.mAnmIndex;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmIndex(u16 index) { mAnmIndex = index; }
    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void setAnmColor(J3DAnmColor* anmColor) { mAnmColor = anmColor; }
    void calc(_GXColor* pColor) const { mAnmColor->getColor(mAnmIndex, pColor); }

private:
    /* 0x0 */ u16 mAnmIndex;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmColor* mAnmColor;
};  // Size: 0x8

class J3DTexNoAnm {
public:
    ~J3DTexNoAnm() {};
    J3DTexNoAnm() {
        mAnmTexPattern = NULL;
        mAnmIndex = 0;
    };
    virtual void calc(u16* param_0) const { mAnmTexPattern->getTexNo(mAnmIndex, param_0); }

    void operator=(J3DTexNoAnm const& other) {
        mAnmTexPattern = other.mAnmTexPattern;
        mAnmIndex = other.mAnmIndex;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmIndex(u16 index) { mAnmIndex = index; }
    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    J3DAnmTexPattern* getAnmTexPattern() { return mAnmTexPattern; }
    void setAnmTexPattern(J3DAnmTexPattern* pattern) { mAnmTexPattern = pattern; }

private:
    /* 0x4 */ u16 mAnmIndex;
    /* 0x6 */ u16 mAnmFlag;
    /* 0x8 */ J3DAnmTexPattern* mAnmTexPattern;
};  // Size: 0xC

class J3DTexMtxAnm {
public:
    ~J3DTexMtxAnm() {}
    J3DTexMtxAnm() {
        mAnmIndex = 0;
        mAnmTransform = NULL;
    }
    J3DTexMtxAnm(J3DAnmTextureSRTKey * pAnm, u16 anmIdx) {
        mAnmTransform = pAnm;
        mAnmIndex = anmIdx;
    }

    void operator=(J3DTexMtxAnm const& other) {
        mAnmTransform = other.mAnmTransform;
        mAnmIndex = other.mAnmIndex;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmIndex(u16 index) { mAnmIndex = index; }
    bool getAnmFlag() const { return mAnmFlag; }
    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    void setAnmTransform(J3DAnmTextureSRTKey* transform) { mAnmTransform = transform; }
    void calc(J3DTextureSRTInfo* pSRTInfo) const {
        mAnmTransform->getTransform(mAnmIndex, pSRTInfo);
    }

private:
    /* 0x0 */ u16 mAnmIndex;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmTextureSRTKey* mAnmTransform;
};  // Size: 0x8

class J3DTevKColorAnm {
public:
    ~J3DTevKColorAnm() {}
    J3DTevKColorAnm() {
        mAnmTevReg = NULL;
        mAnmIndex = 0;
    }
    J3DTevKColorAnm(J3DAnmTevRegKey * pAnm, u16 anmIdx) {
        mAnmTevReg = pAnm;
        mAnmIndex = anmIdx;
    }

    void operator=(J3DTevKColorAnm const& other) {
        mAnmTevReg = other.mAnmTevReg;
        mAnmIndex = other.mAnmIndex;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmIndex(u16 index) { mAnmIndex = index; }
    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void setAnmTevReg(J3DAnmTevRegKey* tevReg) { mAnmTevReg = tevReg; }
    void calc(_GXColor* pColor) const { mAnmTevReg->getTevKonstReg(mAnmIndex, pColor); }

private:
    /* 0x0 */ u16 mAnmIndex;
    /* 0x2 */ u16 mAnmFlag;
    /* 0x4 */ J3DAnmTevRegKey* mAnmTevReg;
};  // Size: 0x8

class J3DTevColorAnm {
public:
    ~J3DTevColorAnm() {}
    J3DTevColorAnm() {
        mAnmTevReg = NULL;
        mAnmIndex = 0;
    }
    J3DTevColorAnm(J3DAnmTevRegKey * pAnm, u16 anmIdx) {
        mAnmTevReg = pAnm;
        mAnmIndex = anmIdx;
    }

    void operator=(J3DTevColorAnm const& other) {
        mAnmTevReg = other.mAnmTevReg;
        mAnmIndex = other.mAnmIndex;
        mAnmFlag = other.mAnmFlag;
    }

    void setAnmIndex(u16 index) { mAnmIndex = index; }
    void setAnmFlag(bool flag) { mAnmFlag = flag; }
    bool getAnmFlag() const { return mAnmFlag; }
    void setAnmTevReg(J3DAnmTevRegKey* tevReg) { mAnmTevReg = tevReg; }
    void calc(_GXColorS10* pColor) const { mAnmTevReg->getTevColorReg(mAnmIndex, pColor); }

private:
    /* 0x0 */ u16 mAnmIndex;
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
