#ifndef JPADRAW_H
#define JPADRAW_H

#include "JSystem/JGeometry.h"
#include "JSystem/JParticle/JPADrawVisitor.h"
#include "JSystem/JParticle/JPADrawSetupTev.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx/mtx.h"
#include "global.h"

class JPADrawClipBoard {
public:
    JPADrawClipBoard() {}
    ~JPADrawClipBoard() {}

    typedef void(*DirTypeFunc)(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);
    typedef void(*RotTypeFunc)(f32, f32, Mtx&);
    typedef void(*BasePlaneTypeFunc)(f32, f32, f32, f32, JGeometry::TVec3<f32>*);

    /* 0x00 */ JPADrawSetupTev mSetupTev;
    /* 0x04 */ f32 mGlobalScaleX;
    /* 0x08 */ f32 mGlobalScaleY;
    /* 0x0C */ f32 mPivotX;
    /* 0x10 */ f32 mPivotY;
    /* 0x14 */ JGeometry::TVec2<f32> field_0x14[4];
    /* 0x34 */ MtxP mDrawMtxPtr;
    /* 0x34 */ Mtx mDrawYBBMtx;
    /* 0x68 */ Mtx mDrawMtx;
    /* 0x98 */ GXColor mPrmColor;
    /* 0x9C */ GXColor mEnvColor;
    /* 0xA0 */ DirTypeFunc mDirTypeFunc;
    /* 0xA4 */ RotTypeFunc mRotTypeFunc;
    /* 0xA8 */ BasePlaneTypeFunc mBasePlaneTypeFunc;
    /* 0xAC */ u32 field_0xa4;
    /* 0xB0 */ s16 mColorAnmFrame;
    /* 0xB2 */ s16 field_0xb2;
};

class JPADraw {
public:
    struct JPADrawVisitorDefFlags {
        /* 0x00 */ BOOL mbIsEnableDrawParent;
        /* 0x04 */ BOOL mbHasPrmAnm;
        /* 0x08 */ BOOL mbHasEnvAnm;
        /* 0x0C */ BOOL mbIsStripe;
        /* 0x10 */ BOOL mbIsPointOrLine;
        /* 0x14 */ BOOL mbIsEnableAlpha;
    };

    bool initialize(JPABaseEmitter*, JPATextureResource*);
    void draw(MtxP);
    void calc();
    void calcParticle(JPABaseParticle*);
    void calcChild(JPABaseParticle*);
    void initParticle(JPABaseParticle*);
    void initChild(JPABaseParticle*, JPABaseParticle*);
    bool loadTexture(u8, _GXTexMapID);
    void setDrawExecVisitorsBeforeCB(const JPADraw::JPADrawVisitorDefFlags&);
    void setDrawExecVisitorsAfterCB(const JPADraw::JPADrawVisitorDefFlags&);
    void setDrawCalcVisitors(const JPADraw::JPADrawVisitorDefFlags&);
    void setParticleClipBoard();
    void setChildClipBoard();
    void drawParticle();
    void drawChild();
    void zDraw();
    void zDrawParticle();
    void zDrawChild();
    void loadYBBMtx(MtxP);

    static JPADrawVisitorContainer vc;
    static JPADrawClipBoard cb;

    /* 0x00 */ JPADrawExecEmitterVisitor* mpExecEmtrVis[1];
    /* 0x04 */ JPADrawExecEmitterVisitor* mpExecEmtrPVis[5];
    /* 0x18 */ JPADrawExecEmitterVisitor* mpExecEmtrCVis[3];
    /* 0x24 */ JPADrawCalcEmitterVisitor* mpCalcEmtrVis[4];
    /* 0x34 */ JPADrawExecParticleVisitor* mpExecPtclVis[5];
    /* 0x48 */ JPADrawCalcParticleVisitor* mpCalcPtclVis[10];
    /* 0x70 */ JPADrawExecParticleVisitor* mpExecChldVis[4];
    /* 0x80 */ JPADrawCalcParticleVisitor* mpCalcChldVis[2];
    /* 0x88 */ u8 execEmtrVisNum;
    /* 0x89 */ u8 execEmtrPVisNum;
    /* 0x8A */ u8 execEmtrCVisNum;
    /* 0x8B */ u8 calcEmtrVisNum;
    /* 0x8C */ u8 execPtclVisNum;
    /* 0x8D */ u8 calcPtclVisNum;
    /* 0x8E */ u8 execChldVisNum;
    /* 0x8F */ u8 calcChldVisNum;
    /* 0x90 */ JPADrawContext dc;
    /* 0xB4 */ f32 mScaleOut;
    /* 0xB8 */ GXColor mPrmColor;
    /* 0xBC */ GXColor mEnvColor;
    /* 0xC0 */ u16 mTexIdx;
    /* 0xC2 */ u8 field_0xc2;
    /* 0xC3 */ u8 field_0xc3;
};

STATIC_ASSERT(sizeof(JPADraw) == 0xC4);

#endif /* JPADRAW_H */
