#ifndef J3DMATERIAL_H
#define J3DMATERIAL_H

#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include "JSystem/J3DGraphBase/J3DTexture.h"
#include "dolphin/types.h"

class J3DJoint;
class J3DMaterialAnm;

class J3DMaterial {
public:
    static J3DColorBlock* createColorBlock(u32);
    static J3DTexGenBlock* createTexGenBlock(u32);
    static J3DTevBlock* createTevBlock(int);
    static J3DIndBlock* createIndBlock(int);
    static J3DPEBlock* createPEBlock(u32, u32);
    static u32 calcSizeColorBlock(u32);
    static u32 calcSizeTexGenBlock(u32);
    static u32 calcSizeTevBlock(int);
    static u32 calcSizeIndBlock(int);
    static u32 calcSizePEBlock(u32, u32);
    void initialize();
    u32 countDLSize();
    void makeDisplayList_private(J3DDisplayListObj*);
    void setCurrentMtx();
    void calcCurrentMtx();
    void copy(J3DMaterial*);
    s32 newSharedDisplayList(u32);
    s32 newSingleSharedDisplayList(u32);

    virtual void calc(const Mtx);
    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void patch();
    virtual void diff(u32);
    virtual void reset();
    virtual void change();

    J3DMaterial() { initialize(); }
    ~J3DMaterial() {}

    J3DMaterial* getNext() { return mNext; }
    void setNext(J3DMaterial* material) {mNext = material; }
    J3DShape* getShape() { return mShape; }
    J3DJoint* getJoint() { return mJoint; }
    u32 getMaterialMode() { return mMaterialMode; }
    void setMaterialMode(u32 mode) { mMaterialMode = mode; }
    J3DTevBlock* getTevBlock() { return mTevBlock; }
    J3DColorBlock* getColorBlock() { return mColorBlock; }
    J3DTexGenBlock* getTexGenBlock() { return mTexGenBlock; }
    J3DDisplayListObj* getSharedDisplayListObj() { return mSharedDLObj; }
    J3DIndBlock* getIndBlock() { return mIndBlock; }
    J3DMaterialAnm* getMaterialAnm() {
        if ((u32)mMaterialAnm < 0xC0000000) {
            return mMaterialAnm;
        } else {
            return NULL;
        }
    }
    J3DNBTScale* getNBTScale() { return mTexGenBlock->getNBTScale(); }
    u16 getTexNo(u32 idx) { return mTevBlock->getTexNo(idx); }
    J3DGXColor* getTevKColor(u32 param_0) { return mTevBlock->getTevKColor(param_0); }
    J3DGXColorS10* getTevColor(u32 param_0) { return mTevBlock->getTevColor(param_0); }
    J3DFog* getFog() { return mPEBlock->getFog(); }
    J3DZMode* getZMode() { return mPEBlock->getZMode(); }
    J3DBlend* getBlend() { return mPEBlock->getBlend(); }
    J3DAlphaComp* getAlphaComp() { return mPEBlock->getAlphaComp(); }
    u8 getZCompLoc() { return mPEBlock->getZCompLoc(); }
    J3DTexMtx* getTexMtx(u32 idx) { return mTexGenBlock->getTexMtx(idx); }
    void setTexMtx(u32 idx, J3DTexMtx* texMtx) { mTexGenBlock->setTexMtx(idx, texMtx); }
    J3DTexCoord* getTexCoord(u32 idx) { return mTexGenBlock->getTexCoord(idx); }
    u16 getIndex() { return mIndex; }
    bool isDrawModeOpaTexEdge() { return (mMaterialMode & 3) == 0; }
    J3DPEBlock* getPEBlock() { return mPEBlock; }
    void onInvalid() { mInvalid = 1; }
    u32 getTexGenNum() const { return mTexGenBlock->getTexGenNum(); }
    u8 getTevStageNum() const { return mTevBlock->getTevStageNum(); }
    J3DIndTexOrder* getIndTexOrder(u32 i) { return mIndBlock->getIndTexOrder(i); }
    J3DIndTexMtx* getIndTexMtx(u32 i) { return mIndBlock->getIndTexMtx(i); }
    u8 getIndTexStageNum() const { return mIndBlock->getIndTexStageNum(); }

    void setTevColor(u32 i, const J3DGXColorS10* i_color) { mTevBlock->setTevColor(i, i_color); }
    void setTevKColor(u32 i, const J3DGXColor* i_color) { mTevBlock->setTevKColor(i, i_color); }
    void setMaterialAnm(J3DMaterialAnm* i_anm) { mMaterialAnm = i_anm; }
    void setCullMode(u8 i_mode) { mColorBlock->setCullMode(i_mode); }

    void addShape(J3DShape*) {}
    void getAmbColor(u32) {}
    void getColorChan(u32) {}
    void getColorChanNum() const {}
    void getCullMode() const {}
    void getCurrentMtx() const {}
    void getDither() const {}
    void getIndTevStage(u32) {}
    void getIndTexCoordScale(u32) {}
    void getLight(u32) {}
    void getMatColor(u32) {}
    void getTevKAlphaSel(u32) {}
    void getTevKColorSel(u32) {}
    void getTevOrder(u32) {}
    void getTevStage(u32) {}
    void getTevSwapModeTable(u32) {}
    void getZCompLoc() const {}
    void setJoint(J3DJoint*) {}
    void setLight(u32, J3DLightObj*) {}
    void setTevStageNum(u8) {}

public:
    /* 0x04 */ J3DMaterial* mNext;
    /* 0x08 */ J3DShape* mShape;
    /* 0x0C */ J3DJoint* mJoint;
    /* 0x10 */ u32 mMaterialMode;
    /* 0x14 */ u16 mIndex;
    /* 0x18 */ u32 mInvalid;
    /* 0x1C */ u32 field_0x1c;
    /* 0x20 */ u32 mDiffFlag;
    /* 0x24 */ J3DColorBlock* mColorBlock;
    /* 0x28 */ J3DTexGenBlock* mTexGenBlock;
    /* 0x2C */ J3DTevBlock* mTevBlock;
    /* 0x30 */ J3DIndBlock* mIndBlock;
    /* 0x34 */ J3DPEBlock* mPEBlock;
    /* 0x38 */ J3DMaterial* mpOrigMaterial;
    /* 0x3C */ J3DMaterialAnm* mMaterialAnm;
    /* 0x40 */ J3DCurrentMtx mCurrentMtx;
    /* 0x48 */ J3DDisplayListObj* mSharedDLObj;
};

class J3DPatchedMaterial : public J3DMaterial {
public:
    J3DPatchedMaterial() { initialize(); }
    void initialize();

    virtual void calc(const Mtx);
    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void reset();
    virtual void change();
};

class J3DLockedMaterial : public J3DMaterial {
public:
    J3DLockedMaterial() { initialize(); }
    void initialize();

    virtual void calc(const Mtx);
    virtual void makeDisplayList();
    virtual void makeSharedDisplayList();
    virtual void load();
    virtual void loadSharedDL();
    virtual void patch();
    virtual void diff(u32);
    virtual void reset();
    virtual void change();
};

#endif /* J3DMATERIAL_H */
