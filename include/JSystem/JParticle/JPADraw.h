#ifndef JPADRAW_H
#define JPADRAW_H

#include "dolphin/types.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXEnum.h"
#include "JSystem/JParticle/JPAParticle.h"

class JPABaseShapeArc;
class JPAExtraShapeArc;
class JPASweepShapeArc;
class JPAExTexShapeArc;
class JPATextureResource;
class JPABaseEmitter;
class JPABaseParticle;

class JPADraw;
class JPADrawExecEmitterVisitor;
class JPADrawExecParticleVisitor;

class JPADrawContext {
    /* 0x00 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x04 */ JPABaseShapeArc* mpBaseArc;
    /* 0x08 */ JPAExtraShapeArc* mpExtraArc;
    /* 0x0C */ JPASweepShapeArc* mpSweepArc;
    /* 0x10 */ JPAExTexShapeArc* mpExTexShape;
    /* 0x14 */ JPADraw* mpDraw;
    /* 0x18 */ JSUPtrList* mpActiveParticles;
    /* 0x1C */ JPATextureResource* mpTextureResource;
    /* 0x20 */ s16* mpTexIdxArray;
};

class JPADraw {
public:
    enum JPADrawVisitorDefFlags {};
    
    void initialize(JPABaseEmitter*, JPATextureResource*);
    void draw(float(*)[4]);
    void calc();
    void calcParticle(JPABaseParticle*);
    void calcChild(JPABaseParticle*);
    void initParticle(JPABaseParticle*);
    void initChild(JPABaseParticle*, JPABaseParticle*);
    void loadTexture(unsigned char, _GXTexMapID);
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
    void loadYBBMtx(float(*)[4]);
    
    /* 0x00 */ JPADrawExecEmitterVisitor* mpExecEmtrVis[1];
    /* 0x04 */ JPADrawExecEmitterVisitor* mpExecEmtrPVis[5];
    /* 0x18 */ JPADrawExecEmitterVisitor* mpExecEmtrCVis[3];
    /* 0x24 */ JPADrawExecParticleVisitor* mpCalcEmtrVis[4];
    /* 0x34 */ JPADrawExecParticleVisitor* mpExecPtclVis[5];
    /* 0x48 */ JPADrawExecParticleVisitor* mpCalcPtclVis[10];
    /* 0x70 */ JPADrawExecParticleVisitor* mpExecChldVis[4];
    /* 0x80 */ JPADrawExecParticleVisitor* mpCalcChldVis[2];
    /* 0x88 */ u8 mExecEmtrVisNum;
    /* 0x89 */ u8 mExecEmtrPVisNum;
    /* 0x8A */ u8 mExecEmtrCVisNum;
    /* 0x8B */ u8 mCalcEmtrVisNum;
    /* 0x8C */ u8 mExecPtclVisNum;
    /* 0x8D */ u8 mCalcPtclVisNum;
    /* 0x8E */ u8 mExecChldVisNum;
    /* 0x8F */ u8 mCalcChldVisNum;
    /* 0x90 */ JPADrawContext mDrawContext;
    /* 0xB4 */ f32 mScaleOut;
    /* 0xB8 */ _GXColor mPrmColor;
    /* 0xBC */ _GXColor mEnvColor;
    /* 0xC0 */ s16 mTexIdx;
    /* 0xC2 */ u8 field_0xc2;
    /* 0xC3 */ u8 field_0xC3[0xC4 - 0xC3];
};

#endif /* JPADRAW_H */
