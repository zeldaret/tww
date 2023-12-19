#ifndef JPADRAWVISITOR_H
#define JPADRAWVISITOR_H

#include "JSystem/JSupport/JSUList.h"
#include "dolphin/types.h"

class JPABaseEmitter;
class JPABaseParticle;
class JPABaseShape;
class JPAExTexShape;
class JPAExtraShape;
class JPASweepShape;
class JPADraw;
class JPADrawClipBoard;
class JPATextureResource;

class JPADrawContext {
public:
    /* 0x00 */ JPABaseEmitter* pbe;
    /* 0x04 */ JPABaseShape* pbsp;
    /* 0x08 */ JPAExtraShape* pesp;
    /* 0x0C */ JPASweepShape* pssp;
    /* 0x10 */ JPAExTexShape* petx;
    /* 0x14 */ JPADraw* mpDraw;
    /* 0x18 */ JSUList<JPABaseParticle>* mpActiveParticles;
    /* 0x1C */ JPATextureResource* mpTextureResource;
    /* 0x20 */ u16* pTexIdx;

    static JPADrawClipBoard* pcb;
};

class JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecEmitterVisitor() {}
    virtual void exec(const JPADrawContext* pDC) = 0;
};

class JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecParticleVisitor() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2) = 0;
};

class JPADrawExecGenPrjMtx : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecGenPrjMtx() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecGenPrjTexMtx : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecGenPrjTexMtx() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecGenTexMtx0 : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecGenTexMtx0() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecGenIdtMtx : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecGenIdtMtx() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecSetTexMtx : public JPADrawExecEmitterVisitor, public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecSetTexMtx() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecSetPointSize : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecSetPointSize() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecSetLineWidth : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecSetLineWidth() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRegisterColorEmitterPE : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecRegisterColorEmitterPE() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecRegisterColorEmitterP : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecRegisterColorEmitterP() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecRegisterColorEmitterE : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecRegisterColorEmitterE() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecRegisterColorChildPE : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecRegisterColorChildPE() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecRegisterPrmColorAnm : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRegisterPrmColorAnm() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRegisterPrmAlphaAnm : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRegisterPrmAlphaAnm() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRegisterEnvColorAnm : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRegisterEnvColorAnm() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRegisterPrmCEnv : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRegisterPrmCEnv() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRegisterPrmAEnv : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRegisterPrmAEnv() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecLoadDefaultTexture : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecLoadDefaultTexture() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecLoadTexture : public JPADrawExecEmitterVisitor, public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecLoadTexture() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecLoadExTex : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecLoadExTex() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecBillBoard : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecBillBoard() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotBillBoard : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotBillBoard() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecYBillBoard : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecYBillBoard() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotYBillBoard : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotYBillBoard() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecDirectional : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecDirectional() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotDirectional : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotDirectional() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecDirectionalCross : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecDirectionalCross() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotDirectionalCross : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotDirectionalCross() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecDirBillBoard : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecDirBillBoard() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotation : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotation() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecRotationCross : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecRotationCross() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecPoint : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecPoint() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecLine : public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecLine() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawExecStripe : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecStripe() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecStripeCross : public JPADrawExecEmitterVisitor {
public:
    virtual ~JPADrawExecStripeCross() {}
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawExecCallBack : public JPADrawExecEmitterVisitor, public JPADrawExecParticleVisitor {
public:
    virtual ~JPADrawExecCallBack() {}
    virtual void exec(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void exec(const JPADrawContext* pDC);
};

class JPADrawCalcEmitterVisitor {
public:
    virtual ~JPADrawCalcEmitterVisitor() {}
    virtual void calc(const JPADrawContext* pDC) = 0;
};

class JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcParticleVisitor() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2) = 0;
};

class JPADrawCalcScaleX : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleX() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleXBySpeed : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleXBySpeed() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleY : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleY() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleYBySpeed : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleYBySpeed() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleCopyX2Y : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleCopyX2Y() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleAnmTimingNormal : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleAnmTimingNormal() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleAnmTimingRepeatX : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleAnmTimingRepeatX() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleAnmTimingRepeatY : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleAnmTimingRepeatY() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleAnmTimingReverseX : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleAnmTimingReverseX() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcScaleAnmTimingReverseY : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcScaleAnmTimingReverseY() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcColorPrm : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorPrm() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorEnv : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorEnv() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorCopyFromEmitter : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorCopyFromEmitter() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcColorAnmFrameNormal : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorAnmFrameNormal() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorAnmFrameRepeat : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorAnmFrameRepeat() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorAnmFrameReverse : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorAnmFrameReverse() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorAnmFrameMerge : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorAnmFrameMerge() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcColorAnmFrameRandom : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcColorAnmFrameRandom() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcAlpha : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcAlpha() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcAlphaFlickNrmSin : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcAlphaFlickNrmSin() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcAlphaFlickAddSin : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcAlphaFlickAddSin() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcAlphaFlickMultSin : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcAlphaFlickMultSin() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcTextureAnmIndexNormal : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcTextureAnmIndexNormal() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcTextureAnmIndexRepeat : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcTextureAnmIndexRepeat() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcTextureAnmIndexReverse : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcTextureAnmIndexReverse() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcTextureAnmIndexMerge : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcTextureAnmIndexMerge() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcTextureAnmIndexRandom : public JPADrawCalcEmitterVisitor, public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcTextureAnmIndexRandom() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
    virtual void calc(const JPADrawContext* pDC);
};

class JPADrawCalcChildAlphaOut : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcChildAlphaOut() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawCalcChildScaleOut : public JPADrawCalcParticleVisitor {
public:
    virtual ~JPADrawCalcChildScaleOut() {}
    virtual void calc(const JPADrawContext* pDC, JPABaseParticle* param_2);
};

class JPADrawVisitorContainer {
public:
    JPADrawExecGenPrjMtx field_0x0;
    JPADrawExecGenPrjTexMtx field_0x4;
    JPADrawExecGenTexMtx0 field_0x8;
    JPADrawExecGenIdtMtx field_0xc;
    JPADrawExecSetTexMtx field_0x10;
    JPADrawExecSetPointSize field_0x18;
    JPADrawExecSetLineWidth field_0x1c;
    JPADrawExecRegisterColorEmitterPE field_0x20;
    JPADrawExecRegisterColorEmitterP field_0x24;
    JPADrawExecRegisterColorEmitterE field_0x28;
    JPADrawExecRegisterColorChildPE field_0x2c;
    JPADrawExecRegisterPrmColorAnm field_0x30;
    JPADrawExecRegisterPrmAlphaAnm field_0x34;
    JPADrawExecRegisterEnvColorAnm field_0x38;
    JPADrawExecRegisterPrmCEnv field_0x3c;
    JPADrawExecRegisterPrmAEnv field_0x40;
    JPADrawExecLoadDefaultTexture field_0x44;
    JPADrawExecLoadTexture field_0x48;
    JPADrawExecLoadExTex field_0x50;
    JPADrawExecBillBoard field_0x54;
    JPADrawExecRotBillBoard field_0x58;
    JPADrawExecYBillBoard field_0x5c;
    JPADrawExecRotYBillBoard field_0x60;
    JPADrawExecDirectional field_0x64;
    JPADrawExecRotDirectional field_0x68;
    JPADrawExecDirectionalCross field_0x6c;
    JPADrawExecRotDirectionalCross field_0x70;
    JPADrawExecDirBillBoard field_0x74;
    JPADrawExecRotation field_0x78;
    JPADrawExecRotationCross field_0x7c;
    JPADrawExecPoint field_0x80;
    JPADrawExecLine field_0x84;
    JPADrawExecStripe field_0x88;
    JPADrawExecStripeCross field_0x8c;
    JPADrawExecCallBack field_0x90;
    JPADrawCalcScaleX field_0x98;
    JPADrawCalcScaleXBySpeed field_0x9c;
    JPADrawCalcScaleY field_0xa0;
    JPADrawCalcScaleYBySpeed field_0xa4;
    JPADrawCalcScaleCopyX2Y field_0xa8;
    JPADrawCalcScaleAnmTimingNormal field_0xac;
    JPADrawCalcScaleAnmTimingRepeatX field_0xb0;
    JPADrawCalcScaleAnmTimingRepeatY field_0xb4;
    JPADrawCalcScaleAnmTimingReverseX field_0xb8;
    JPADrawCalcScaleAnmTimingReverseY field_0xbc;
    JPADrawCalcColorPrm field_0xc0;
    JPADrawCalcColorEnv field_0xc8;
    JPADrawCalcColorCopyFromEmitter field_0xd0;
    JPADrawCalcColorAnmFrameNormal field_0xd4;
    JPADrawCalcColorAnmFrameRepeat field_0xdc;
    JPADrawCalcColorAnmFrameReverse field_0xe4;
    JPADrawCalcColorAnmFrameMerge field_0xec;
    JPADrawCalcColorAnmFrameRandom field_0xf4;
    JPADrawCalcAlpha field_0xfc;
    JPADrawCalcAlphaFlickNrmSin field_0x100;
    JPADrawCalcAlphaFlickAddSin field_0x104;
    JPADrawCalcAlphaFlickMultSin field_0x108;
    JPADrawCalcTextureAnmIndexNormal field_0x10c;
    JPADrawCalcTextureAnmIndexRepeat field_0x114;
    JPADrawCalcTextureAnmIndexReverse field_0x11c;
    JPADrawCalcTextureAnmIndexMerge field_0x124;
    JPADrawCalcTextureAnmIndexRandom field_0x12c;
    JPADrawCalcChildAlphaOut field_0x134;
    JPADrawCalcChildScaleOut field_0x138;
};

#endif /* JPADRAWVISITOR_H */
