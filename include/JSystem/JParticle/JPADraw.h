#ifndef JPADRAW_H
#define JPADRAW_H

#include "dolphin/types.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx/mtx.h"

class JPABaseShape;
class JPAExtraShape;
class JPASweepShape;
class JPAExTexShape;
class JPATextureResource;
class JPABaseEmitter;
class JPABaseParticle;
struct JSUPtrList;

class JPADraw;
class JPADrawExecEmitterVisitor;
class JPADrawExecParticleVisitor;
class JPADrawClipBoard;
class JPADrawVisitorContainer;

class JPADrawContext {
public:
    /* 0x00 */ JPABaseEmitter* pbe;
    /* 0x04 */ JPABaseShape* pbsp;
    /* 0x08 */ JPAExtraShape* pesp;
    /* 0x0C */ JPASweepShape* pssp;
    /* 0x10 */ JPAExTexShape* petx;
    /* 0x14 */ JPADraw* mpDraw;
    /* 0x18 */ JSUPtrList* mpActiveParticles;
    /* 0x1C */ JPATextureResource* mpTextureResource;
    /* 0x20 */ u16* pTexIdx;

    static JPADrawClipBoard* pcb;
};

class JPADraw {
public:
    struct JPADrawVisitorDefFlags {
        /* 0x00 */ u32 mbIsEnableDrawParent;
        /* 0x04 */ u32 mbHasPrmAnm;
        /* 0x08 */ u32 mbHasEnvAnm;
        /* 0x0C */ u32 mbIsStripe;
        /* 0x10 */ u32 mbIsPointOrLine;
        /* 0x04 */ u32 mbIsEnableAlpha;
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
    /* 0x24 */ JPADrawExecParticleVisitor* mpCalcEmtrVis[4];
    /* 0x34 */ JPADrawExecParticleVisitor* mpExecPtclVis[5];
    /* 0x48 */ JPADrawExecParticleVisitor* mpCalcPtclVis[10];
    /* 0x70 */ JPADrawExecParticleVisitor* mpExecChldVis[4];
    /* 0x80 */ JPADrawExecParticleVisitor* mpCalcChldVis[2];
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
    /* 0xC0 */ s16 mTexIdx;
    /* 0xC2 */ u8 field_0xc2;
    /* 0xC3 */ u8 field_0xc3;
};

STATIC_ASSERT(sizeof(JPADraw) == 0xC4);

#endif /* JPADRAW_H */
