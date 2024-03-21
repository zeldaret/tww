#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include "JSystem/J3DGraphBase/J3DDrawBuffer.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "f_op/f_op_view.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_rnd.h"
#include "global.h"

class ResTIMG;
class cM3dGPla;

class dDlst_base_c {
public:
    dDlst_base_c() {}
    virtual ~dDlst_base_c() {}
    virtual void draw() {}
};

class dDlst_2D_c : public dDlst_base_c {
public:
    dDlst_2D_c(ResTIMG * pTIMG, s16 w, s16 h, u8 alpha);
    virtual void draw();

    J2DPicture * getPicture() { return &mPicture; }
    void setAlpha(u8 alpha) { mAlpha = alpha; }

protected:
    /* 0x004 */ J2DPicture mPicture;
    /* 0x128 */ s16 mX;
    /* 0x12A */ s16 mY;
    /* 0x12C */ u8 mAlpha;
    /* 0x12D */ u8 field_0x12e[3];
};

class dDlst_2DTri_c : public dDlst_base_c {
public:
    virtual void draw();

    /* 0x04 */ s16 mX;
    /* 0x06 */ s16 mY;
    /* 0x08 */ GXColor mColor;
    /* 0x)C */ s16 mRot;
    /* 0x10 */ f32 mScaleX;
    /* 0x14 */ f32 mScaleY;
};

class dDlst_2DPoint_c : public dDlst_base_c {
public:
    virtual void draw();

    /* 0x04 */ s16 mPosX;
    /* 0x06 */ s16 mPosY;
    /* 0x08 */ GXColor mColor;
    /* 0x0C */ u8 mPointSize;
};

class dDlst_2DT_c : public dDlst_base_c {
public:
    virtual void draw();
    void init(u8* pTexData, u32 p1, GXTexFmt texFmt, u16 texW, u16 texH, f32 cx, f32 cy, s16 x0, s16 y0, s16 x1, s16 y1, u8 alpha, f32 sx, f32 sy) {
        mpTexData = pTexData;
        field_0x08 = p1;
        mTexFmt = (u8)texFmt;
        mTexW = texW;
        mTexH = texH;
        mCenterX = cx;
        mCenterY = cy;
        mX0 = x0;
        mY0 = y0;
        mX1 = x1;
        mY1 = y1;
        mAlpha = alpha;
        mScaleX = sx;
        mScaleY = sy;
    }

public:
    /* 0x04 */ u8* mpTexData;
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ u8 mTexFmt;
    /* 0x0D */ u8 mAlpha;
    /* 0x0E */ u16 mTexW;
    /* 0x10 */ u16 mTexH;
    /* 0x12 */ s16 mX0;
    /* 0x14 */ s16 mY0;
    /* 0x16 */ s16 mX1;
    /* 0x18 */ s16 mY1;
    /* 0x1C */ f32 mCenterX;
    /* 0x20 */ f32 mCenterY;
    /* 0x24 */ f32 mScaleX;
    /* 0x28 */ f32 mScaleY;
};

class dDlst_2DT2_c : public dDlst_base_c {
public:
    void init(ResTIMG* pTimg, f32, f32, f32, f32, u8, u8, u8, f32, f32);
    virtual void draw();

public:
    /* 0x04 */ GXTexObj mTex;
    /* 0x24 */ f32 mX;
    /* 0x28 */ f32 mY;
    /* 0x2C */ f32 mW;
    /* 0x30 */ f32 mH;
    /* 0x34 */ f32 mScrollS;
    /* 0x38 */ f32 mScrollT;
    /* 0x3C */ GXColor mColor;
    /* 0x40 */ u8 mMirrorS;
    /* 0x41 */ u8 mMirrorT;
    /* 0x42 */ u8 mAlpha;
};

class dDlst_2DM_c : public dDlst_base_c {
public:
    virtual void draw();

public:
    struct TexEntry {
        /* 0x00 */ u8* mpData;
        /* 0x04 */ u8 mFormat;
        /* 0x06 */ u16 mWidth;
        /* 0x08 */ u16 mHeight;
        /* 0x0A */ s16 mScrollX;
        /* 0x0C */ s16 mScrollY;
    };

    /* 0x04 */ s16 mX0;
    /* 0x06 */ s16 mY0;
    /* 0x08 */ s16 mX1;
    /* 0x0A */ s16 mY1;
    /* 0x0C */ u8 mTex1Wrap;
    /* 0x0D */ GXColor mC0;
    /* 0x11 */ GXColor mC1;
    /* 0x18 */ TexEntry mTex[2];
};

class dDlst_2Dm_c : public dDlst_base_c {
public:
    void init(ResTIMG*, ResTIMG*, f32, f32);
    void setPos(s16, s16, s16, s16);
    void setScale(f32, f32);
    void setScroll(int, s16, s16);
    virtual void draw();
    void setAlpha(u8) {}
    void setBlackColor(GXColor& c) { mC0 = c; }
    void setWhiteColor(GXColor& c) { mC1 = c; }

public:
    struct TexEntry {
        /* 0x00 */ GXTexObj mTexObj;
        /* 0x20 */ GXTlutObj mTlutObj;
        /* 0x2C */ s16 mScrollX;
        /* 0x2E */ s16 mScrollY;
        /* 0x30 */ u8 mbHasTlut;
        /* 0x31 */ u8 pad[3];
    };

    /* 0x04 */ s16 mX0;
    /* 0x06 */ s16 mY0;
    /* 0x08 */ s16 mX1;
    /* 0x0A */ s16 mY1;
    /* 0x0C */ f32 mScaleX;
    /* 0x10 */ f32 mScaleY;
    /* 0x14 */ GXColor mC0;
    /* 0x18 */ GXColor mC1;
    /* 0x1C */ TexEntry mTex[2];
};

class dDlst_2DMt_tex_c {
public:
    u8 check() { return mValid; }
    int getCI() { return mCI; }
    GXTexObj* getTexObj() { return &mTexObj; }
    GXTlutObj* getTlutObj() { return &mTlutObj; }
    GXColor getColor() { return mColor; }
    f32 getS() { return mS; }
    f32 getT() { return mT; }
    f32 getSw() { return mSw; }
    f32 getTw() { return mTw; }

public:
    /* 0x00 */ u8 mValid;
    /* 0x01 */ u8 mCI;
    /* 0x04 */ GXTexObj mTexObj;
    /* 0x24 */ GXTlutObj mTlutObj;
    /* 0x30 */ GXColor mColor;
    /* 0x34 */ f32 mS;
    /* 0x38 */ f32 mT;
    /* 0x3C */ f32 mSw;
    /* 0x40 */ f32 mTw;
};

class dDlst_2DMt_c : public dDlst_base_c {
public:
    virtual void draw();

public:
    /* 0x04 */ u8 mTexNum;
    /* 0x08 */ dDlst_2DMt_tex_c* mTex;
    /* 0x0C */ s16 mX0;
    /* 0x0E */ s16 mY0;
    /* 0x10 */ s16 mX1;
    /* 0x12 */ s16 mY1;
};

class dDlst_effectLine_c : public dDlst_base_c {
public:
    void update(cXyz&, GXColor&, u16, u16, u16, u16, f32, f32, f32, f32);
    virtual void draw();

public:
    /* 0x04 */ cM_rnd_c mRnd;
    /* 0x10 */ cXyz mPos;
    /* 0x1C */ GXColor mColor;
    /* 0x20 */ u16 field_0x20;
    /* 0x22 */ u16 field_0x22;
    /* 0x24 */ u16 field_0x24;
    /* 0x26 */ u16 field_0x26;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};

class dDlst_snapShot_c : public dDlst_base_c {
public:
    ~dDlst_snapShot_c() {};
    void draw();
};

class dDlst_window_c {
public:
    dDlst_window_c() {}
    ~dDlst_window_c() {}
    void setViewPort(f32, f32, f32, f32, f32, f32);
    void setScissor(f32, f32, f32, f32);

    view_port_class* getViewPort() { return &mViewport; }
    s8 getCameraID() { return mCameraID; }
    void setCameraID(int id) { mCameraID = id; }
    void setMode(int mode) { mMode = mode; }

private:
    /* 0x00 */ view_port_class mViewport;
    /* 0x28 */ s8 mCameraID;
    /* 0x29 */ s8 mMode;
};

STATIC_ASSERT(sizeof(dDlst_window_c) == 0x2C);

class dDlst_peekZ_c {
public:
    struct dDlst_peekZ_entry {
        /* 0x0 */ s16 x;
        /* 0x2 */ s16 y;
        /* 0x4 */ u32* dst;
    };

    dDlst_peekZ_c() { mCount = 0; }
    int newData(s16, s16, u32*);
    void peekData();

    /* 0x0 */ u8 mCount;
    /* 0x4 */ dDlst_peekZ_entry mEntries[50];
};  // Size: 0x194

STATIC_ASSERT(sizeof(dDlst_peekZ_c) == 0x194);

class dDlst_shadowSimple_c {
public:
    void draw();
    void set(cXyz*, f32, f32, cXyz*, s16, f32, GXTexObj*);
    dDlst_shadowSimple_c() {}
    ~dDlst_shadowSimple_c() {}

    /* 0x00 */ u8 mAlpha;
    /* 0x04 */ GXTexObj* mpTexObj;
    /* 0x08 */ Mtx mVolumeMtx;
    /* 0x38 */ Mtx mMtx;
};  // Size: 0x68

struct cBgD_Vtx_t;

class dDlst_shadowTri_c {
public:
    ~dDlst_shadowTri_c() {}
    dDlst_shadowTri_c() {}

    /* 0x0 */ cXyz mPos[3];
};

class dDlst_shadowPoly_c {
public:
    dDlst_shadowPoly_c() { reset(); }
    virtual ~dDlst_shadowPoly_c() {}

    virtual dDlst_shadowTri_c* getTri() = 0;
    virtual s32 getTriMax() = 0;

    void reset() { mCount = 0; }

    int set(cBgD_Vtx_t*, u16, u16, u16, cM3dGPla*);
    int set(cXyz&, cXyz&, cXyz&);
    void draw();

    /* 0x4 */ u16 mCount;
    /* 0x6 */ u8 field_0x6[2];
};

class dDlst_shadowRealPoly_c : public dDlst_shadowPoly_c {
public:
    virtual ~dDlst_shadowRealPoly_c() {}

    virtual dDlst_shadowTri_c* getTri() { return mShadowTri; }
    virtual s32 getTriMax() { return ARRAY_SIZE(mShadowTri); }

    /* 0x8 */ dDlst_shadowTri_c mShadowTri[256];
};

class J3DCallBackPacket;
class dKy_tevstr_c;
class dDlst_shadowReal_c {
public:
    void reset();
    void imageDraw(f32 (*)[4]);
    void draw();
    u32 set(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    u32 set2(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    bool add(J3DModel*);
    void init();
    ~dDlst_shadowReal_c() {
        delete mpTexData;
        delete mpDrawBuffer;
    }
    dDlst_shadowReal_c() { mState = 0; }

    bool isNoUse() { return mState == 0; }
    bool isUse() { return mState != 0; }
    bool checkKey(u32 i_key) { return mKey == i_key; }

    enum { MODEL_MAX = 0x1A };

private:
    /* 0x0000 */ u8 mState;
    /* 0x0001 */ s8 field_0x1;
    /* 0x0002 */ u8 mAlpha;
    /* 0x0003 */ u8 mModelNum;
    /* 0x0004 */ u32 mKey;
    /* 0x0008 */ Mtx mViewMtx;
    /* 0x0038 */ Mtx44 mRenderProjMtx;
    /* 0x0078 */ Mtx mReceiverProjMtx;
    /* 0x00A8 */ void* mpTexData;
    /* 0x00AC */ dDlst_shadowRealPoly_c mShadowRealPoly;
    /* 0x24B4 */ GXTexObj mTexObj;
    /* 0x24D4 */ J3DDrawBuffer* mpDrawBuffer;
    /* 0x24D8 */ J3DCallBackPacket* mpCallBack;
    /* 0x24DC */ J3DModel* mpModels[MODEL_MAX];
};  // Size: 0x2544

class dDlst_shadowControl_c {
public:
    dDlst_shadowControl_c() { mRealNum = 0; }
    void init();
    void reset();
    void imageDraw(Mtx);
    void draw(Mtx);
    int setReal(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    int setReal2(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    bool addReal(u32, J3DModel*);
    int setSimple(cXyz*, f32, f32, cXyz*, s16, f32, GXTexObj*);

    static void setSimpleTex(void*);
    static GXTexObj* getSimpleTex() { return &mSimpleTexObj; }
    static GXTexObj mSimpleTexObj;

private:
    /* 0x00000 */ u8 mRealNum;
    /* 0x00001 */ u8 mSimpleNum;
    /* 0x00004 */ dDlst_shadowSimple_c mSimple[128];
    /* 0x03404 */ int mNextID;
    /* 0x03408 */ dDlst_shadowReal_c mReal[8];
};  // Size: 0x15E28

STATIC_ASSERT(sizeof(dDlst_shadowControl_c) == 0x15E28);

class dDlst_mirrorPacket : public J3DPacket {
public:
    void init(ResTIMG*);
    void update(Mtx, u8, f32);
    virtual void draw();

    /* 0x0010 */ u8 field_0x0010[0x0040 - 0x0010];
    /* 0x0040 */ Mtx mPosMtx;
    /* 0x0070 */ u8 field_0x0070[0x0080 - 0x0070];
    /* 0x0080 */ Mtx mTexMtx;
    /* 0x00B0 */ dDlst_shadowRealPoly_c mShadowPoly;
    /* 0x24B8 */ GXTexObj mTexObj;
    /* 0x24D8 */ u8 mAlpha;
};

struct view_port_class;
struct view_class;
struct camera_class;

struct dDlst_alphaModelData_c {
public:
    dDlst_alphaModelData_c();
    ~dDlst_alphaModelData_c();
    void set(u8, Mtx, u8);
    void draw(Mtx);

public:
    /* 0x00 */ u8 mType;
    /* 0x01 */ u8 mAlpha;
    /* 0x04 */ MtxP mpMtx;
};

struct dDlst_alphaModel_c {
public:
    enum Type {
        TYPE_SPHERE = 0,
        TYPE_TWO_SPHERES = 1,
        TYPE_SEARCHLIGHT = 2,
        TYPE_CUBE = 3,
        TYPE_SMALL_SPHERE = 4,
        TYPE_THREE_SPHERES = 5,
    };

    dDlst_alphaModel_c();
    static dDlst_alphaModel_c * create(int);
    BOOL set(u8 type, Mtx mtx, u8 alpha);
    BOOL draw(Mtx);
    s32 getNum() { return mNum; }
    void setColor(GXColor& color) { mColor = color; }
    GXColor & getColor() { return mColor; }
    void reset() { mNum = 0; }

public:
    /* 0x00 */ GXColor mColor;
    /* 0x04 */ s16 mCapacity;
    /* 0x06 */ s16 mNum;
    /* 0x08 */ dDlst_alphaModelData_c* mpData;
};  // Size: 0xC

struct dDlst_alphaModelPacket : public J3DPacket {
public:
    virtual void draw();

public:
    /* 0x10 */ u8 mType;
    /* 0x11 */ GXColor mColor;
    /* 0x18 */ Mtx* mMtxP;
};

struct dDlst_alphaVolPacket : public J3DPacket {
public:
    virtual void draw();

public:
    /* 0x10 */ Mtx mtx;
};

struct dDlst_alphaInvVolPacket : public J3DPacket {
public:
    virtual void draw();

public:
    /* 0x10 */ Mtx mtx;
};

class dDlst_list_c {
public:
    dDlst_list_c();
    ~dDlst_list_c();

    bool init();
    void reset();
    void entryZSortXluDrawList(J3DDrawBuffer*, J3DPacket*, cXyz&);
    bool set(dDlst_base_c**&, dDlst_base_c**&, dDlst_base_c*);
    void draw(dDlst_base_c**, dDlst_base_c**);
    static void wipeIn(f32, GXColor&);
    static void wipeIn(f32);
    static void wipeOut(f32 rate) { wipeIn(-rate); }
    static void wipeOut(f32 rate, GXColor& color) { wipeIn(-rate, color); }
    static void calcWipe();

    J3DDrawBuffer* getOpaListP1() { return mpOpaListP1; }
    J3DDrawBuffer* getOpaListSky() { return mpOpaListSky; }
    J3DDrawBuffer* getOpaListFilter() { return mpOpaListFilter; }
    J3DDrawBuffer* getOpaList2D() { return mpOpaList2D; }
    J3DDrawBuffer* getXluList() { return mpXluList; }
    J3DDrawBuffer* getXluListP1() { return mpXluListP1; }

    void setXluDrawList(J3DDrawBuffer* buffer) { j3dSys.setDrawBuffer(buffer, XLU_BUFFER); }
    void setOpaDrawList(J3DDrawBuffer* buffer) { j3dSys.setDrawBuffer(buffer, OPA_BUFFER); }
    void setOpaList() { setOpaDrawList(mpOpaList); }
    void setXluList() { setXluDrawList(mpXluList); }
    void setOpaListInvisible() { setOpaDrawList(mpOpaListInvisible); }
    void setXluListInvisible() { setXluDrawList(mpXluListInvisible); }
    void setOpaListMaskOff() { setOpaDrawList(mpOpaListMaskOff); }
    void setXluListMaskOff() { setXluDrawList(mpXluListMaskOff); }
    void setOpaListSky() { setOpaDrawList(mpOpaListSky); }
    void setXluListSky() { setXluDrawList(mpXluListSky); }
    void setOpaListP0() { setOpaDrawList(mpOpaListP0); }
    void setXluListP0() { setXluDrawList(mpOpaListP0); }
    void setOpaListP1() { setOpaDrawList(mpOpaListP1); }
    void setXluListP1() { setXluDrawList(mpXluListP1); }
    void setOpaListBG() { setOpaDrawList(mpOpaListBG); }
    void setXluListBG() { setXluDrawList(mpXluListBG); }
    void setOpaListFilter() { setOpaDrawList(mpOpaListFilter); }
    void setXluListFilter() { setXluDrawList(mpOpaListFilter); }
    void setOpaList2D() { setOpaDrawList(mpOpaList2D); }
    void setXluList2D() { setXluDrawList(mpOpaList2D); }

    void entryZSortXluList(J3DPacket* i_packet, cXyz& pos) {
        entryZSortXluDrawList(mpXluList, i_packet, pos);
    }

    void entryZSortXluListMaskOff(J3DPacket* i_packet, cXyz& pos) {
        entryZSortXluDrawList(mpXluListMaskOff, i_packet, pos);
    }

    void set2DOpaTop(dDlst_base_c* pItem) { set(mp2DOpaTop, mp2DOpaTopEnd, pItem); }
    void set2DOpa(dDlst_base_c* pItem) { set(mp2DOpa, mp2DOpaEnd, pItem); }
    void set2DXlu(dDlst_base_c* pItem) { set(mp2DXlu, mp2DXluEnd, pItem); }

    void drawCopy2D() { draw(mpCopy2DArr, mpCopy2D); }
    void draw2DOpaTop() { draw(mp2DOpaTopArr, mp2DOpaTop); }
    void draw2DOpa() { draw(mp2DOpaArr, mp2DOpa); }
    void draw2DXlu() { draw(mp2DXluArr, mp2DXlu); }

    void drawOpaDrawList(J3DDrawBuffer * drawBuffer) { j3dSys.setDrawModeOpaTexEdge(); drawBuffer->draw(); }
    void drawTailOpaDrawList(J3DDrawBuffer * drawBuffer) { j3dSys.setDrawModeOpaTexEdge(); drawBuffer->drawTail(); }
    void drawXluDrawList(J3DDrawBuffer * drawBuffer) { j3dSys.setDrawModeXlu(); drawBuffer->draw(); }
    void drawOpaListSky() { drawOpaDrawList(mpOpaListSky); }
    void drawXluListSky() { drawXluDrawList(mpXluListSky); }
    void drawOpaListP0() { drawTailOpaDrawList(mpOpaListP0); }
    void drawOpaListP1() { drawOpaDrawList(mpOpaListP1); }
    void drawXluListP1() { drawOpaDrawList(mpXluListP1); }
    void drawOpaListBG() { drawOpaDrawList(mpOpaListBG); }
    void drawXluListBG() { drawXluDrawList(mpXluListBG); }
    void drawOpaList() { drawOpaDrawList(mpOpaList); }
    void drawXluList() { drawXluDrawList(mpXluList); }
    void drawOpaListFilter() { drawOpaDrawList(mpOpaListFilter); }
    void drawOpaListMaskOff() { drawOpaDrawList(mpOpaListMaskOff); }
    void drawXluListMaskOff() { drawXluDrawList(mpXluListMaskOff); }
    void drawOpaListInvisible() { drawOpaDrawList(mpOpaListInvisible); }
    void drawXluListInvisible() { drawXluDrawList(mpXluListInvisible); }
    void drawOpaList2D() { drawOpaDrawList(mpOpaList2D); }

    int setSimpleShadow(cXyz* param_0, f32 param_1, f32 param_2, cXyz* param_3, s16 param_4,
                        f32 param_5, GXTexObj* param_6) {
        return mShadowControl.setSimple(param_0, param_1, param_2, param_3, param_4, param_5,
                                        param_6);
    }
    int setRealShadow(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5, f32 param_6,
                      dKy_tevstr_c* pTevStr) {
        return mShadowControl.setReal(id, param_2, pModel, pPos, param_5, param_6, pTevStr);
    }
    int setRealShadow2(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5, f32 param_6,
                       dKy_tevstr_c* pTevStr) {
        return mShadowControl.setReal2(id, param_2, pModel, pPos, param_5, param_6, pTevStr);
    }
    bool addRealShadow(u32 id, J3DModel* pModel) {
        return mShadowControl.addReal(id, pModel);
    }

    void drawShadow(Mtx mtx) { mShadowControl.draw(mtx); }
    void imageDrawShadow(Mtx mtx) { mShadowControl.imageDraw(mtx); }

    void set3DlineMat(mDoExt_3DlineMat_c* mat) {
        m3DLineMatSortPacket[mat->getMaterialID()].setMat(mat);
    }

    void setAlphaModel(u8 type, Mtx mtx, u8 alpha) { mpAlphaModel->set(type, mtx, alpha); }
    void setSpotModel(u8 type, Mtx mtx, u8 alpha) { mpSpotModel->set(type, mtx, alpha); }
    void setLightModel(u8 type, Mtx mtx, u8 alpha) { mpLightModel->set(type, mtx, alpha); }

    void drawAlphaModel(Mtx mtx) { mpAlphaModel->draw(mtx); }
    void drawSpotModel(Mtx mtx) { mpSpotModel->draw(mtx); }
    void drawLightModel(Mtx mtx) { mpLightModel->draw(mtx); }

    s32 getSpotModelNum() { return mpSpotModel->getNum(); }
    s32 getLightModelNum() { return mpLightModel->getNum(); }
    void setAlphaModelColor(GXColor& color) { mpAlphaModel->setColor(color); }
    void setSpotModelColor(GXColor& color) { mpSpotModel->setColor(color); }
    void setLightModelColor(GXColor& color) { mpLightModel->setColor(color); }
    GXColor& getAlphaModelColor() { return mpAlphaModel->getColor(); }
    GXColor& getSpotModelColor() { return mpSpotModel->getColor(); }
    GXColor& getLightModelColor() { return mpLightModel->getColor(); }
    void resetAlphaModel() { mpAlphaModel->reset(); }
    void resetSpotModel() { mpSpotModel->reset(); }
    void resetLightModel() { mpLightModel->reset(); }

    void setWindow(dDlst_window_c* pWindow) { mpWindow = pWindow; }
    void setViewport(view_port_class* pViewPort) { mpViewPort = pViewPort; }
    view_port_class* getViewport() { return mpViewPort; }
    void setView(view_class* pView) { mpCamera = (camera_class*)pView; }
    view_class* getView() { return (view_class*)mpCamera; }

    static void offWipe() { mWipe = false; }
    static f32 getWipeRate() { return mWipeRate; }

    void newPeekZdata(s16 x, s16 y, u32 * data) { mPeekZ.newData(x, y, data); }
    void peekZdata() { mPeekZ.peekData(); }

    static ResTIMG* getToonImage() { return mToonImage; }
    static void setToonImage(ResTIMG* image) { mToonImage = image; }
    static ResTIMG* getToonExImage() { return mToonExImage; }
    static void setToonExImage(ResTIMG* image) { mToonExImage = image; }

    static bool mWipe;
    static GXColor mWipeColor;
    static f32 mWipeRate;
    static f32 mWipeSpeed;
    static dDlst_2DT2_c mWipeDlst;
    static ResTIMG * mToonImage;
    static ResTIMG * mToonExImage;

    /* 0x00000 */ J3DDrawBuffer* mpOpaListSky;
    /* 0x00004 */ J3DDrawBuffer* mpXluListSky;
    /* 0x00008 */ J3DDrawBuffer* mpOpaListP0;
    /* 0x0000C */ J3DDrawBuffer* mpOpaListP1;
    /* 0x00010 */ J3DDrawBuffer* mpXluListP1;
    /* 0x00014 */ J3DDrawBuffer* mpOpaListBG;
    /* 0x00018 */ J3DDrawBuffer* mpXluListBG;
    /* 0x0001C */ J3DDrawBuffer* mpOpaList;
    /* 0x00020 */ J3DDrawBuffer* mpXluList;
    /* 0x00024 */ J3DDrawBuffer* mpOpaListFilter;
    /* 0x00028 */ J3DDrawBuffer* mpOpaListMaskOff;
    /* 0x0002C */ J3DDrawBuffer* mpXluListMaskOff;
    /* 0x00030 */ J3DDrawBuffer* mpOpaListInvisible;
    /* 0x00034 */ J3DDrawBuffer* mpXluListInvisible;
    /* 0x00038 */ J3DDrawBuffer* mpOpaList2D;
    /* 0x0003C */ dDlst_base_c* mpCopy2DArr[4];
    /* 0x0004C */ dDlst_base_c** mpCopy2D;
    /* 0x00050 */ dDlst_base_c** mpCopy2DEnd;
    /* 0x00054 */ dDlst_base_c* mp2DOpaTopArr[16];
    /* 0x00094 */ dDlst_base_c** mp2DOpaTop;
    /* 0x00098 */ dDlst_base_c** mp2DOpaTopEnd;
    /* 0x0009C */ dDlst_base_c* mp2DOpaArr[64];
    /* 0x0019C */ dDlst_base_c** mp2DOpa;
    /* 0x001A0 */ dDlst_base_c** mp2DOpaEnd;
    /* 0x001A4 */ dDlst_base_c* mp2DXluArr[32];
    /* 0x00224 */ dDlst_base_c** mp2DXlu;
    /* 0x00228 */ dDlst_base_c** mp2DXluEnd;
    /* 0x0022C */ dDlst_window_c* mpWindow;
    /* 0x00230 */ view_port_class* mpViewPort;
    /* 0x00234 */ camera_class* mpCamera; // should be view_class*
    /* 0x00238 */ u8 field_0x00238[0x00244 - 0x00238];
    /* 0x00244 */ dDlst_alphaModel_c* mpAlphaModel;
    /* 0x00248 */ dDlst_alphaModel_c* mpSpotModel;
    /* 0x0024C */ dDlst_alphaModel_c* mpLightModel;
    /* 0x00250 */ dDlst_shadowControl_c mShadowControl;
    /* 0x16078 */ mDoExt_3DlineMatSortPacket m3DLineMatSortPacket[2];
    /* 0x160A0 */ dDlst_peekZ_c mPeekZ;
};  // Size: 0x16234

STATIC_ASSERT(sizeof(dDlst_list_c) == 0x16234);

void dDlst_texSpecmapST(const cXyz*, const dKy_tevstr_c*, J3DModelData*, f32);

#endif /* D_D_DRAWLIST_H */
