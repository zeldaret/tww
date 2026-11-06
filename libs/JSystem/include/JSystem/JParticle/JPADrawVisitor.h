#ifndef JPADRAWVISITOR_H
#define JPADRAWVISITOR_H

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JGeometry.h"
#include "dolphin/mtx/mtx.h"
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
    /* 0x000 */ JPADrawExecGenPrjMtx mGenPrjMtx;
    /* 0x004 */ JPADrawExecGenPrjTexMtx mGenPrjTexMtx;
    /* 0x008 */ JPADrawExecGenTexMtx0 mGenTexMtx0;
    /* 0x00C */ JPADrawExecGenIdtMtx mGenIdtMtx;
    /* 0x010 */ JPADrawExecSetTexMtx mSetTexMtx;
    /* 0x018 */ JPADrawExecSetPointSize mSetPointSize;
    /* 0x01C */ JPADrawExecSetLineWidth mSetLineWidth;
    /* 0x020 */ JPADrawExecRegisterColorEmitterPE mRegisterColorPrmEnv;
    /* 0x024 */ JPADrawExecRegisterColorEmitterP mRegisterColorPrm;
    /* 0x028 */ JPADrawExecRegisterColorEmitterE mRegisterColorEnv;
    /* 0x02C */ JPADrawExecRegisterColorChildPE mRegisterColorChildPrmEnv;
    /* 0x030 */ JPADrawExecRegisterPrmColorAnm mRegisterPrmColorAnm;
    /* 0x034 */ JPADrawExecRegisterPrmAlphaAnm mRegisterPrmAlphaAnm;
    /* 0x038 */ JPADrawExecRegisterEnvColorAnm mRegisterEnvColorAnm;
    /* 0x03C */ JPADrawExecRegisterPrmCEnv mRegisterPrmColor;
    /* 0x040 */ JPADrawExecRegisterPrmAEnv mRegisterPrmAlpha;
    /* 0x044 */ JPADrawExecLoadDefaultTexture mLoadDefaultTexture;
    /* 0x048 */ JPADrawExecLoadTexture mLoadTexture;
    /* 0x050 */ JPADrawExecLoadExTex mLoadExTexture;
    /* 0x054 */ JPADrawExecBillBoard mExecBillBoard;
    /* 0x058 */ JPADrawExecRotBillBoard mExecRotBillBoard;
    /* 0x05C */ JPADrawExecYBillBoard mExecYBillBoard;
    /* 0x060 */ JPADrawExecRotYBillBoard mExecRotYBillBoard;
    /* 0x064 */ JPADrawExecDirectional mExecDirectional;
    /* 0x068 */ JPADrawExecRotDirectional mExecRotDirectional;
    /* 0x06C */ JPADrawExecDirectionalCross mExecDirectionalCross;
    /* 0x070 */ JPADrawExecRotDirectionalCross mExecRotDirectionalCross;
    /* 0x074 */ JPADrawExecDirBillBoard mExecDirBillBoard;
    /* 0x078 */ JPADrawExecRotation mExecRotation;
    /* 0x07C */ JPADrawExecRotationCross mExecRotationCross;
    /* 0x080 */ JPADrawExecPoint mExecPoint;
    /* 0x084 */ JPADrawExecLine mExecLine;
    /* 0x088 */ JPADrawExecStripe mExecStripe;
    /* 0x08C */ JPADrawExecStripeCross mExecStripeCross;
    /* 0x090 */ JPADrawExecCallBack mExecCallBack;
    /* 0x098 */ JPADrawCalcScaleX mCalcScaleX;
    /* 0x09C */ JPADrawCalcScaleXBySpeed mCalcScaleXBySpeed;
    /* 0x0A0 */ JPADrawCalcScaleY mCalcScaleY;
    /* 0x0A4 */ JPADrawCalcScaleYBySpeed mCalcScaleYBySpeed;
    /* 0x0A8 */ JPADrawCalcScaleCopyX2Y mCalcScaleCopyX2Y;
    /* 0x0AC */ JPADrawCalcScaleAnmTimingNormal mCalcScaleAnmTimingNormal;
    /* 0x0B0 */ JPADrawCalcScaleAnmTimingRepeatX mCalcScaleAnmTimingRepeatX;
    /* 0x0B4 */ JPADrawCalcScaleAnmTimingRepeatY mCalcScaleAnmTimingRepeatY;
    /* 0x0B8 */ JPADrawCalcScaleAnmTimingReverseX mCalcScaleAnmTimingReverseX;
    /* 0x0BC */ JPADrawCalcScaleAnmTimingReverseY mCalcScaleAnmTimingReverseY;
    /* 0x0C0 */ JPADrawCalcColorPrm mCalcColorPrm;
    /* 0x0C8 */ JPADrawCalcColorEnv mCalcColorEnv;
    /* 0x0D0 */ JPADrawCalcColorCopyFromEmitter mCalcColorCopyFromEmitter;
    /* 0x0D4 */ JPADrawCalcColorAnmFrameNormal mCalcColorAnmFrameNormal;
    /* 0x0DC */ JPADrawCalcColorAnmFrameRepeat mCalcColorAnmFrameRepeat;
    /* 0x0E4 */ JPADrawCalcColorAnmFrameReverse mCalcColorAnmFrameReverse;
    /* 0x0EC */ JPADrawCalcColorAnmFrameMerge mCalcColorAnmFrameMerge;
    /* 0x0F4 */ JPADrawCalcColorAnmFrameRandom mCalcColorAnmFrameRandom;
    /* 0x0FC */ JPADrawCalcAlpha mCalcAlpha;
    /* 0x100 */ JPADrawCalcAlphaFlickNrmSin mCalcAlphaFlickNrmSin;
    /* 0x104 */ JPADrawCalcAlphaFlickAddSin mCalcAlphaFlickAddSin;
    /* 0x108 */ JPADrawCalcAlphaFlickMultSin mCalcAlphaFlickMultSin;
    /* 0x10C */ JPADrawCalcTextureAnmIndexNormal mCalcTextureAnmIndexNormal;
    /* 0x114 */ JPADrawCalcTextureAnmIndexRepeat mCalcTextureAnmIndexRepeat;
    /* 0x11C */ JPADrawCalcTextureAnmIndexReverse mCalcTextureAnmIndexReverse;
    /* 0x124 */ JPADrawCalcTextureAnmIndexMerge mCalcTextureAnmIndexMerge;
    /* 0x12C */ JPADrawCalcTextureAnmIndexRandom mCalcTextureAnmIndexRandom;
    /* 0x134 */ JPADrawCalcChildAlphaOut mCalcChildAlphaOut;
    /* 0x138 */ JPADrawCalcChildScaleOut mCalcChildScaleOut;
};

void dirTypeVel(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);
void dirTypePos(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);
void dirTypePosInv(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);
void dirTypeEmtrDir(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);
void dirTypePrevPtcl(JPABaseParticle*, JPABaseEmitter*, JGeometry::TVec3<f32>&);

void rotTypeY(f32, f32, Mtx&);
void rotTypeX(f32, f32, Mtx&);
void rotTypeZ(f32, f32, Mtx&);
void rotTypeXYZ(f32, f32, Mtx&);
void rotTypeYJiggle(f32, f32, Mtx&);

void basePlaneTypeXY(f32, f32, f32, f32, JGeometry::TVec3<f32>*);
void basePlaneTypeXZ(f32, f32, f32, f32, JGeometry::TVec3<f32>*);

#endif /* JPADRAWVISITOR_H */
