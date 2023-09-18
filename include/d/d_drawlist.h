#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include "f_op/f_op_view.h"
#include "global.h"
#include "m_Do/m_Do_ext.h"

class dDlst_base_c {
public:
    dDlst_base_c() {}
    virtual void draw();
};

class dDlst_window_c {
public:
    dDlst_window_c() {}
    ~dDlst_window_c() {}
    void setViewPort(f32, f32, f32, f32, f32, f32);
    void setScissor(f32, f32, f32, f32);

    view_port_class* getViewPort() { return &mViewport; }

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
    dDlst_shadowSimple_c();

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

    void reset() { mCount = 0; }

    int set(cBgD_Vtx_t*, u16, u16, u16, cM3dGPla*);
    void draw();

    virtual dDlst_shadowTri_c* getTri() = 0;
    virtual s32 getTriMax() = 0;

    /* 0x4 */ u16 mCount;
    /* 0x6 */ u8 field_0x6[2];
};

class dDlst_shadowRealPoly_c : public dDlst_shadowPoly_c {
public:
    virtual dDlst_shadowTri_c* getTri();
    virtual s32 getTriMax();

    /* 0x8 */ dDlst_shadowTri_c mShadowTri[256];
};

class J3DCallBackPacket;
class dKy_tevstr_c;
class dDlst_shadowReal_c {
public:
    void reset();
    void imageDraw(f32 (*)[4]);
    void draw();
    u32 set(u32, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*, f32, f32);
    bool add(J3DModel*);
    ~dDlst_shadowReal_c() {}
    dDlst_shadowReal_c() { mState = 0; }

    bool isNoUse() { return mState == 0; }
    bool isUse() { return mState == 1; }
    bool checkKey(u32 i_key) { return mKey == i_key; }

private:
    /* 0x0000 */ u8 mState;
    /* 0x0001 */ u8 field_0x1;
    /* 0x0002 */ u8 mModelNum;
    /* 0x0003 */ u8 field_0x3;
    /* 0x0004 */ u32 mKey;
    /* 0x0008 */ Mtx mViewMtx;
    /* 0x0038 */ Mtx44 mRenderProjMtx;
    /* 0x0078 */ Mtx mReceiverProjMtx;
    /* 0x00A8 */ void* mpTexData;
    /* 0x00AC */ dDlst_shadowRealPoly_c mShadowRealPoly;
    /* 0x24B4 */ GXTexObj mTexData;
    /* 0x24D4 */ J3DDrawBuffer* mpDrawBuffer;
    /* 0x24D8 */ J3DCallBackPacket* mpPacket;
    /* 0x24DC */ J3DModel* mpModels[26];
};  // Size: 0x2544

class dDlst_shadowControl_c {
public:
    void init();
    void reset();
    void imageDraw(f32 (*)[4]);
    void draw(f32 (*)[4]);
    int setReal(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    int setReal2(u32, s8, J3DModel*, cXyz*, f32, f32, dKy_tevstr_c*);
    bool addReal(u32, J3DModel*);
    int setSimple(cXyz*, f32, f32, cXyz*, s16, f32, GXTexObj*);
    static void setSimpleTex(ResTIMG const*);

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

struct dDlst_alphaModelData_c;

struct dDlst_alphaModel_c {
public:
    enum Type {
        TYPE_SPHERE        = 0,
        TYPE_TWO_SPHERES   = 1,
        TYPE_SEARCHLIGHT   = 2,
        TYPE_CUBE          = 3,
        TYPE_SMALL_SPHERE  = 4,
        TYPE_THREE_SPHERES = 5,
    };
    
    dDlst_alphaModel_c();
    void create(int);
    void set(u8 type, Mtx mtx, u8 alpha);
    void draw(MtxP);
    s32 getNum() {
        return mNum;
    }
public:
    /* 0x00 */ _GXColor mColor;
    /* 0x04 */ s16 mCapacity;
    /* 0x06 */ s16 mNum;
    /* 0x08 */ dDlst_alphaModelData_c* mpData;
};  // Size: 0xC

class dDlst_list_c {
public:
    dDlst_list_c();
    ~dDlst_list_c();

    void init();
    void reset();
    void entryZSortXluDrawList(J3DDrawBuffer*, J3DPacket*, cXyz&);
    void set(dDlst_base_c**&, dDlst_base_c**&, dDlst_base_c*);
    void draw(dDlst_base_c**, dDlst_base_c**);
    void wipeIn(f32, GXColor&);
    void wipeIn(f32);
    void calcWipe();
    void set2DOpa(dDlst_base_c*);

    int setSimpleShadow(cXyz* param_0, f32 param_1, f32 param_2, cXyz* param_3, s16 param_4,
                        f32 param_5, _GXTexObj* param_6) {
        return mShadowControl.setSimple(param_0, param_1, param_2, param_3, param_4, param_5,
                                        param_6);
    }
    int setRealShadow2(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5, f32 param_6,
                       dKy_tevstr_c* pTevStr) {
        return mShadowControl.setReal2(id, param_2, pModel, pPos, param_5, param_6, pTevStr);
    }
    
    void setAlphaModel(u8 type, Mtx mtx, u8 alpha) {
        mpAlphaModel->set(type, mtx, alpha);
    }
    void setSpotModel(u8 type, Mtx mtx, u8 alpha) {
        mpSpotModel->set(type, mtx, alpha);
    }
    void setLightModel(u8 type, Mtx mtx, u8 alpha) {
        mpLightModel->set(type, mtx, alpha);
    }
    s32 getSpotModelNum() {
        return mpSpotModel->getNum();
    }
    s32 getLightModelNum() {
        return mpLightModel->getNum();
    }

    static void offWipe() { mWipe = false; }

    static bool mWipe;

private:
    /* 0x00000 */ J3DDrawBuffer* mpBufSkyOpa;
    /* 0x00004 */ J3DDrawBuffer* mpBufSkyXlu;
    /* 0x00008 */ J3DDrawBuffer* mpLinkBuf;
    /* 0x0000C */ J3DDrawBuffer* field_0x0000c;
    /* 0x00010 */ J3DDrawBuffer* field_0x00010;
    /* 0x00014 */ J3DDrawBuffer* mpBufWorldOpa;
    /* 0x00018 */ J3DDrawBuffer* mpBufWorldXlu;
    /* 0x0001C */ J3DDrawBuffer* mpBufInvisibleModelOpa;
    /* 0x00020 */ J3DDrawBuffer* mpBufInvisibleModelXlu;
    /* 0x00024 */ J3DDrawBuffer* mpWetherFxBuffer;
    /* 0x00028 */ J3DDrawBuffer* mpBufInvisibleModelMaskOffOpa;
    /* 0x0002C */ J3DDrawBuffer* mpBufInvisibleModelMaskOffXlu;
    /* 0x00030 */ J3DDrawBuffer* field_0x00030;
    /* 0x00034 */ J3DDrawBuffer* field_0x00034;
    /* 0x00038 */ J3DDrawBuffer* field_0x00038;
    /* 0x0003C */ u8 field_0x0003C[0x00050 - 0x0003C];
    /* 0x00050 */ void* field_0x00050;
    /* 0x00054 */ u8 field_0x00054[0x00094 - 0x00054];
    /* 0x00094 */ dDlst_base_c** field_0x00094;
    /* 0x00098 */ void* field_0x00098;
    /* 0x0009C */ dDlst_base_c* mp2DArr[64];
    /* 0x0019C */ dDlst_base_c** mp2DOpa;
    /* 0x001A0 */ dDlst_base_c*** mp2DOpaEnd;
    /* 0x001A4 */ u8 field_0x001A4[0x00224 - 0x001A4];
    /* 0x00224 */ dDlst_base_c** field_0x00224;
    /* 0x00228 */ dDlst_base_c*** field_0x00228;
    /* 0x0022C */ dDlst_window_c* field_0x0022c;
    /* 0x00230 */ dDlst_window_c* field_0x00230;
    /* 0x00234 */ camera_class* mpCamera;
    /* 0x00238 */ u8 field_0x00238[0x00244 - 0x00238];
    /* 0x00244 */ dDlst_alphaModel_c* mpAlphaModel;
    /* 0x00248 */ dDlst_alphaModel_c* mpSpotModel;
    /* 0x0024C */ dDlst_alphaModel_c* mpLightModel;
    /* 0x00250 */ dDlst_shadowControl_c mShadowControl;
    /* 0x16078 */ mDoExt_3DlineMatSortPacket m3DLineMatSortPacket[2];
    /* 0x160A0 */ dDlst_peekZ_c mPeekZ;
};  // Size: 0x16234

STATIC_ASSERT(sizeof(dDlst_list_c) == 0x16234);

void dDlst_texSpecmapST(const cXyz*, const dKy_tevstr_c*, J3DModelData*, float);

#endif /* D_D_DRAWLIST_H */
