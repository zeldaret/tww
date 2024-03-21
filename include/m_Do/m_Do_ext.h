#ifndef M_DO_EXT_H
#define M_DO_EXT_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/J3DGraphAnimator/J3DMaterialAnm.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JAZelAudio/JAIZelAnime.h"
#include "d/d_kankyo.h"

class JKRArchive;
class JKRAssertHeap;
class JKRExpHeap;
class JKRHeap;
class JKRSolidHeap;
struct ResTIMG;
class Z2Creature;
class J3DTexMtxAnm;

class mDoExt_baseAnm {
public:
    mDoExt_baseAnm() { mFrameCtrl = NULL; }
    virtual ~mDoExt_baseAnm() {}

    int initPlay(s16 i_frameMax, int i_attribute, f32 i_rate, s16 i_startF, s16 i_endF, bool);
    int play();

    J3DFrameCtrl* getFrameCtrl() { return mFrameCtrl; }
    f32 getPlaySpeed() { return mFrameCtrl->getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl->setRate(speed); }
    f32 getFrame() { return mFrameCtrl->getFrame(); }
    f32 getEndFrame() { return mFrameCtrl->getEnd(); }
    void setFrame(f32 frame) { mFrameCtrl->setFrame(frame); }
    void setPlayMode(int i_mode) { mFrameCtrl->setAttribute(i_mode); }
    void setLoopFrame(f32 i_frame) { mFrameCtrl->setLoop(i_frame); }
    BOOL isStop() {
        return mFrameCtrl->checkState(J3DFrameCtrl::STATE_STOP_E) || mFrameCtrl->getRate() == 0.0f;
    }
    BOOL isLoop() { return mFrameCtrl->checkState(J3DFrameCtrl::STATE_LOOP_E); }

private:
    /* 0x4 */ J3DFrameCtrl* mFrameCtrl;
};  // Size: 0x08

class mDoExt_btkAnm : public mDoExt_baseAnm {
public:
    mDoExt_btkAnm() { mpTexMtxAnm = NULL; }
    int init(J3DMaterialTable* i_matTable, J3DAnmTextureSRTKey* i_btk, BOOL i_anmPlay,
             int i_attribute, f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);
    void entry(J3DMaterialTable* i_matTable, f32 i_frame);
    void entry(J3DModelData *i_modelData, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    int init(J3DModelData* i_modelData, J3DAnmTextureSRTKey* i_btk, BOOL i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);

    int remove(J3DModelData* i_modelData) { return i_modelData->removeTexMtxAnimator(mpAnm); }
    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTextureSRTKey* getBtkAnm() const { return mpAnm; }

private:
    /* 0x08 */ J3DAnmTextureSRTKey* mpAnm;
    /* 0x0C */ J3DTexMtxAnm* mpTexMtxAnm;
    /* 0x10 */ u16 mUpdateMaterialNum;
};  // Size: 0x14

STATIC_ASSERT(sizeof(mDoExt_btkAnm) == 0x14);

class J3DTevColorAnm;
class J3DTevKColorAnm;
class mDoExt_brkAnm : public mDoExt_baseAnm {
public:
    mDoExt_brkAnm() {
        mpCRegAnm = NULL;
        mpKRegAnm = NULL;
    }
    int init(J3DMaterialTable* i_matTable, J3DAnmTevRegKey* i_brk, BOOL i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);
    void entry(J3DMaterialTable* i_matTable, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void entry(J3DModelData* i_modelData, f32 i_frame);

    int init(J3DModelData* i_modelData, J3DAnmTevRegKey* i_brk, BOOL i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);

    int remove(J3DModelData* i_modelData) { return i_modelData->removeTevRegAnimator(mpAnm); }
    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTevRegKey* getBrkAnm() const { return mpAnm; }

private:
    /* 0x08 */ J3DAnmTevRegKey* mpAnm;
    /* 0x0C */ J3DTevColorAnm* mpCRegAnm;
    /* 0x10 */ J3DTevKColorAnm* mpKRegAnm;
    /* 0x14 */ u16 mCRegUpdateMaterialNum;
    /* 0x16 */ u16 mKRegUpdateMaterialNum;
};  // Size: 0x18

STATIC_ASSERT(sizeof(mDoExt_brkAnm) == 0x18);

class mDoExt_bckAnm : public mDoExt_baseAnm {
public:
    mDoExt_bckAnm() { mAnm = NULL; }
    int init(J3DModelData * i_model, J3DAnmTransform* i_bck, int i_play, int i_attr,
                            f32 i_rate, s16 i_startF, s16 i_endF1, bool i_modify);
    void changeBckOnly(J3DAnmTransform* i_bck);
    void entry(J3DModelData* i_modelData, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void remove(J3DModelData* i_modelData) { i_modelData->getJointNodePointer(0)->setMtxCalc(NULL); }
    J3DAnmTransform* getBckAnm() const { return mAnmTransform; }

private:
    /* 0x08 */ J3DAnmTransform* mAnmTransform;
    /* 0x0C */ J3DMtxCalcMayaAnm* mAnm;
};  // Size: 0x10

STATIC_ASSERT(sizeof(mDoExt_bckAnm) == 0x10);

class mDoExt_btpAnm : public mDoExt_baseAnm {
public:
    mDoExt_btpAnm() { field_0xc = NULL; }
    int init(J3DModelData* i_modelData, J3DAnmTexPattern* i_btp, BOOL i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);
    int init(J3DMaterialTable* i_matTable, J3DAnmTexPattern* i_btp, BOOL i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);
    void entry(J3DModelData* i_modelData, s16 i_frame);
    void entry(J3DMaterialTable* i_matTable, s16 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    int remove(J3DModelData* i_modelData) { return i_modelData->removeTexNoAnimator(mpAnm); }
    J3DAnmTexPattern* getBtpAnm() const { return mpAnm; }

private:
    /* 0x08 */ J3DAnmTexPattern* mpAnm;
    /* 0x0C */ J3DTexNoAnm* field_0xc;
    /* 0x10 */ u16 mUpdateMaterialNum;
};

class mDoExt_blkAnm : public mDoExt_baseAnm {
public:
    int init(J3DDeformData* i_deformData, J3DAnmCluster* i_blk, BOOL i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 param_6);

    J3DAnmCluster* getBlkAnm() { return mpAnm; }

private:
    /* 0x14 */ J3DAnmCluster* mpAnm;
};

class mDoExt_bpkAnm : public mDoExt_baseAnm {
public:
    int init(J3DModelData*, J3DAnmColor*, int, int, f32, s16, s16, bool, int);
    int init(J3DMaterialTable*, J3DAnmColor*, int, int, f32, s16, s16, bool, int);

    void entry(J3DModelData*, f32);
    void entry(J3DMaterialTable*, f32);

private:
    /* 0x08 */ J3DAnmColor* mpAnm;
    /* 0x0C */ J3DMatColorAnm* field_0xc;
    /* 0x10 */ u16 mUpdateMaterialNum;
};

class mDoExt_bvaAnm : public mDoExt_baseAnm {
public:
    int init(J3DModel*, J3DAnmVisibilityFull*, int, int, f32, s16, s16, bool, int);
    void entry(J3DModel*, s16);

    int init(J3DModelData*, J3DAnmTransform*, int, int, f32, s16, s16, bool);

private:
    /* 0x08 */ J3DAnmVisibilityFull* mpAnm;
    /* 0x0C */ J3DVisibilityManager* field_0xc;
};

class mDoExt_AnmRatioPack {
public:
    ~mDoExt_AnmRatioPack() {}
    mDoExt_AnmRatioPack() {
        mRatio = 0.0f;
        mAnmTransform = NULL;
    }

    f32 getRatio() { return mRatio; }
    void setRatio(f32 ratio) { mRatio = ratio; }
    J3DAnmTransform* getAnmTransform() { return mAnmTransform; }
    void setAnmTransform(J3DAnmTransform* anm) { mAnmTransform = anm; }

private:
    /* 0x0 */ f32 mRatio;
    /* 0x4 */ J3DAnmTransform* mAnmTransform;
};  // Size: 0x8

class mDoExt_transAnmBas : public J3DAnmTransformKey {
public:
    mDoExt_transAnmBas(void* bas) { mBas = bas; }
    virtual ~mDoExt_transAnmBas() {}

    void* getBas() { return mBas; }

private:
    /* 0x2C */ void* mBas;
};  // Size: 0x30

class mDoExt_MtxCalcOldFrame {
public:
    mDoExt_MtxCalcOldFrame(J3DTransformInfo* param_1, Quaternion* param_2) {
        mOldFrameTransInfo = param_1;
        mOldFrameQuaternion = param_2;
        mOldFrameRate = 0.0f;
        mOldFrameFlg = false;
        field_0x1 = true;
        mOldFrameStartJoint = 0;
        mOldFrameEndJoint = 0;
        mOldFrameMorfCounter = 0.0f;
        field_0x8 = 0.0f;
        field_0x10 = 0.0f;
        field_0x14 = 0.0f;
    }
    
    void initOldFrameMorf(f32, u16, u16);
    void decOldFrameMorfCounter();

    bool getOldFrameFlg() { return mOldFrameFlg; }
    void onOldFrameFlg() { mOldFrameFlg = true; }
    f32 getOldFrameRate() { return mOldFrameRate; }
    J3DTransformInfo* getOldFrameTransInfo(int i) { return &mOldFrameTransInfo[i]; }
    u16 getOldFrameStartJoint() { return mOldFrameStartJoint; }
    u16 getOldFrameEndJoint() { return mOldFrameEndJoint; }
    Quaternion* getOldFrameQuaternion(int i_no) { return &mOldFrameQuaternion[i_no]; }
    f32 getOldFrameMorfCounter() { return mOldFrameMorfCounter; }

private:
    /* 0x00 */ bool mOldFrameFlg;
    /* 0x01 */ bool field_0x1;
    /* 0x04 */ f32 mOldFrameMorfCounter;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 mOldFrameRate;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u16 mOldFrameStartJoint;
    /* 0x1A */ u16 mOldFrameEndJoint;
    /* 0x1C */ J3DTransformInfo* mOldFrameTransInfo;
    /* 0x20 */ Quaternion* mOldFrameQuaternion;
};  // Size: 0x24

struct mDoExt_MtxCalcAnmBlendTbl : public J3DMtxCalcMaya {
    mDoExt_MtxCalcAnmBlendTbl(int num, mDoExt_AnmRatioPack* anmRatio) {
        mNum = num;
        mAnmRatio = anmRatio;
        for (int i = 0; i < mNum; i++) {
            if (!mAnmRatio[i].getAnmTransform()) {
                mAnmRatio[i].setRatio(0.0f);
            }
        }
    }

    virtual ~mDoExt_MtxCalcAnmBlendTbl() {};
    virtual void calc(u16);

    f32 getRatio(int i) { return mAnmRatio[i].getRatio(); }
    void setRatio(int i, f32 ratio) { mAnmRatio[i].setRatio(ratio); }
    J3DAnmTransform* getAnmTransform(int i) { return mAnmRatio[i].getAnmTransform(); }

    /* 0x50 */ int mNum;
    /* 0x54 */ mDoExt_AnmRatioPack* mAnmRatio;
};

struct mDoExt_MtxCalcAnmBlendTblOld : public mDoExt_MtxCalcAnmBlendTbl {
    typedef int (*CalcCallback)(u32, u16, J3DTransformInfo*, Quaternion*);

    mDoExt_MtxCalcAnmBlendTblOld(mDoExt_MtxCalcOldFrame* oldFrame, int num, mDoExt_AnmRatioPack* anmRatio) : mDoExt_MtxCalcAnmBlendTbl(num, anmRatio) {
        mOldFrame = oldFrame;
        mBeforeCallback = NULL;
        mAfterCallback = NULL;
        mUserArea = 0;
    }
    virtual ~mDoExt_MtxCalcAnmBlendTblOld();
    virtual void calc(u16);

    void setUserArea(u32 area)  { mUserArea = area; }
    void setBeforeCalc(CalcCallback callback) { mBeforeCallback = callback; }
    void setAfterCalc(CalcCallback callback) { mAfterCallback = callback; }

    /* 0x58 */ u32 mUserArea;
    /* 0x5C */ mDoExt_MtxCalcOldFrame* mOldFrame;
    /* 0x60 */ CalcCallback mBeforeCallback;
    /* 0x64 */ CalcCallback mAfterCallback;
};  // Size: 0x90

class mDoExt_McaMorfCallBack1_c {
public:
    virtual ~mDoExt_McaMorfCallBack1_c() {}
    virtual bool execute(u16, J3DTransformInfo*) = 0;
};

class mDoExt_McaMorfCallBack2_c {
public:
    virtual ~mDoExt_McaMorfCallBack2_c() = 0;
    virtual void execute(u16) = 0;
};

class mDoExt_zelAnime : public JAIZelAnime {
public:
    mDoExt_zelAnime() {}

public:
    /* 0x98 */ void* mpBasAnm;
};  // Size: 0x9C

class mDoExt_McaMorf : public J3DMtxCalcMaya {
public:
    mDoExt_McaMorf(J3DModelData* modelData, mDoExt_McaMorfCallBack1_c* callback1,
                   mDoExt_McaMorfCallBack2_c* callback2, J3DAnmTransform* anmTransform,
                   int loopMode, f32 param_5, int param_6, int param_7, int param_8,
                   void* basAnm, u32 modelFlag, u32 differedDlistFlag);
    virtual ~mDoExt_McaMorf();

    void calc();
    void calc(u16);
    void setAnm(J3DAnmTransform* bckAnm, int loopMode, f32 morf, f32 playSpeed, f32 startFrame, f32 endFrame, void* basAnm);
    void setMorf(f32);
    void update();
    void updateDL();
    void updateDL(J3DMaterialTable*);
    void entry();
    void entryDL();
    void entryDL(J3DMaterialTable*);
    BOOL play(Vec*, u32, s8);
    void stopZelAnime();

    J3DModel* getModel() { return mpModel; }
    u8 getPlayMode() { return mFrameCtrl.getAttribute(); }
    void setPlayMode(int mode) { mFrameCtrl.setAttribute(mode); }
    f32 getStartFrame() { return mFrameCtrl.getStart(); }
    void setStartFrame(f32 frame) { mFrameCtrl.setStart(frame); }
    f32 getEndFrame() { return mFrameCtrl.getEnd(); }
    void setEndFrame(f32 frame) { mFrameCtrl.setEnd(frame); }
    f32 getLoopFrame() { return mFrameCtrl.getLoop(); }
    void setLoopFrame(f32 frame) { mFrameCtrl.setLoop(frame); }
    f32 getPlaySpeed() { return mFrameCtrl.getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl.setRate(speed); }
    f32 getFrame() { return mFrameCtrl.getFrame(); }
    void setFrame(f32 frame) { mFrameCtrl.setFrame((s16)frame); }
    BOOL isStop() {
        return mFrameCtrl.checkState(J3DFrameCtrl::STATE_STOP_E) || mFrameCtrl.getRate() == 0.0f;
    }
    BOOL checkFrame(f32 frame) {
        return mFrameCtrl.checkPass(frame);
    }
    void changeAnm(J3DAnmTransform* bckAnm) { mpAnm = bckAnm; }
    J3DAnmTransform* getAnm() { return mpAnm; }
    f32 getMorfRatio() { return mCurMorf; }
    BOOL isLoop() { return mFrameCtrl.checkState(J3DFrameCtrl::STATE_LOOP_E); }
    BOOL isMorf() { return mCurMorf < 1.0f; }

    /* 0x50 */ J3DModel* mpModel;
    /* 0x54 */ J3DAnmTransform* mpAnm;
    /* 0x58 */ J3DFrameCtrl mFrameCtrl;
    /* 0x6C */ J3DTransformInfo* mpTransformInfo;
    /* 0x70 */ Quaternion* mpQuat;
    /* 0x74 */ f32 mCurMorf;
    /* 0x78 */ f32 mPrevMorf;
    /* 0x7C */ f32 mMorfStep;
    /* 0x80 */ mDoExt_zelAnime* mpSound;
    /* 0x84 */ mDoExt_McaMorfCallBack1_c * mpCallback1;
    /* 0x88 */ mDoExt_McaMorfCallBack2_c * mpCallback2;
};

class mDoExt_McaMorf2 : public J3DMtxCalcMaya {
public:
    mDoExt_McaMorf2(J3DModelData* modelData, mDoExt_McaMorfCallBack1_c* callback1,
                    mDoExt_McaMorfCallBack2_c* callback2,
                    J3DAnmTransform* anmTransform1, J3DAnmTransform* anmTransform2,
                    int loopMode, f32 param_5, int param_6, int param_7, int param_8,
                    void* basAnm, u32 modelFlag, u32 differedDlistFlag);
    ~mDoExt_McaMorf2();

    void ERROR_EXIT();
    void calc(u16);
    void setAnm(J3DAnmTransform*, J3DAnmTransform*, f32, int, f32, f32, f32, f32, void*);
    void setMorf(f32);
    BOOL play(Vec*, u32, s8);
    void entryDL();
    void calc();
    void stopZelAnime();

    J3DModel* getModel() { return mpModel; }
    u8 getPlayMode() { return mFrameCtrl.getAttribute(); }
    void setPlayMode(int mode) { mFrameCtrl.setAttribute(mode); }
    f32 getStartFrame() { return mFrameCtrl.getStart(); }
    void setStartFrame(f32 frame) { mFrameCtrl.setStart(frame); }
    f32 getEndFrame() { return mFrameCtrl.getEnd(); }
    void setEndFrame(f32 frame) { mFrameCtrl.setEnd(frame); }
    f32 getLoopFrame() { return mFrameCtrl.getLoop(); }
    void setLoopFrame(f32 frame) { mFrameCtrl.setLoop(frame); }
    f32 getPlaySpeed() { return mFrameCtrl.getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl.setRate(speed); }
    f32 getFrame() { return mFrameCtrl.getFrame(); }
    void setFrame(f32 frame) { mFrameCtrl.setFrame((s16)frame); }
    BOOL isStop() {
        return mFrameCtrl.checkState(J3DFrameCtrl::STATE_STOP_E) || mFrameCtrl.getRate() == 0.0f;
    }
    BOOL checkFrame(f32 frame) {
        return mFrameCtrl.checkPass(frame);
    }
    BOOL isMorf() { return mCurMorf < 1.0f; }
    void setAnmRate(f32) {} // TODO

    /* 0x50 */ J3DModel* mpModel;
    /* 0x54 */ J3DAnmTransform* mpAnm1;
    /* 0x58 */ J3DAnmTransform* mpAnm2;
    /* 0x5C */ J3DTransformInfo* mpTransformInfo;
    /* 0x60 */ Quaternion* mpQuat;
    /* 0x64 */ J3DFrameCtrl mFrameCtrl;
    /* 0x78 */ f32 mCurMorf;
    /* 0x7C */ f32 mPrevMorf;
    /* 0x80 */ f32 mMorfStep;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ mDoExt_zelAnime* mpSound;
    /* 0x8C */ mDoExt_McaMorfCallBack1_c * mpCallback1;
    /* 0x90 */ mDoExt_McaMorfCallBack2_c * mpCallback2;
};

class mDoExt_3DlineMat_c {
public:
    virtual int getMaterialID() = 0;
    virtual void setMaterial() = 0;
    virtual void draw() = 0;

public:
    /* 0x0 */ /* vtable */
    /* 0x4 */ mDoExt_3DlineMat_c* mpNextLineMat;
};

class mDoExt_3DlineMatSortPacket : public J3DPacket {
public:
    mDoExt_3DlineMatSortPacket() { mp3DlineMat = NULL; }

    void reset() { mp3DlineMat = NULL; }

    void setMat(mDoExt_3DlineMat_c* pMat);
    virtual void draw();
    virtual ~mDoExt_3DlineMatSortPacket();

private:
    /* 0x10 */ mDoExt_3DlineMat_c* mp3DlineMat;
};

class mDoExt_backupMatBlock_c {
public:
    mDoExt_backupMatBlock_c();
    ~mDoExt_backupMatBlock_c();

    void store(J3DMaterial*);
    void restore(J3DMaterial*);

private:
    /* 0x000 */ J3DGXColor mMatColor[2];
    /* 0x008 */ u8 mColorChanNum;
    /* 0x00A */ J3DColorChan mColorChan[4];
    /* 0x012 */ J3DGXColor mAmbColor[2];
    /* 0x01C */ u32 mTexGenNum;
    /* 0x020 */ J3DTexCoord mTexCoord[8];
    /* 0x040 */ J3DTexMtx mTexMtx[8];
    /* 0x660 */ u8 mTevStageNum;
    /* 0x662 */ u16 mTexNo[8];
    /* 0x672 */ J3DGXColorS10 mTevColor[4];
    /* 0x692 */ J3DGXColor mTevKColor[4];
    /* 0x6A2 */ J3DTevStage mTevStage[8];
    /* 0x6E4 */ J3DIndTevStage mIndTevStage[8];
    /* 0x704 */ J3DTevOrder mTevOrder[4];
    /* 0x714 */ u8 mTevKColorSel[4];
    /* 0x718 */ u8 mTevKAlphaSel[4];
    /* 0x71C */ J3DTevSwapModeTable mTevSwapModeTable[4];
    /* 0x720 */ u8 mIndTexStageNum;
    /* 0x721 */ J3DIndTexOrder mIndTexOrder[4];
    /* 0x734 */ J3DIndTexMtx mIndTexMtx[3];
    /* 0x788 */ J3DIndTexCoordScale mIndTexCoordScale[4];
    /* 0x798 */ J3DFog mFog;
    /* 0x7C4 */ J3DAlphaComp mAlphaComp;
    /* 0x7C8 */ J3DBlend mBlend;
    /* 0x7CC */ J3DZMode mZMode;
    /* 0x7CE */ u8 mZCompLoc;
    /* 0x7D0 */ J3DMaterialAnm* mMaterialAnm;
    /* 0x7D4 */ u32 mMaterialMode;
};

class mDoExt_backupMaterial_c {
public:
    mDoExt_backupMaterial_c() { mBackupMatBlock = NULL; }
    bool create(J3DModelData*);
    bool create(u16);
    void restore(J3DModelData*);

private:
    /* 0x00 */ mDoExt_backupMatBlock_c* mBackupMatBlock;
    /* 0x04 */ J3DTexture* mTexture;
    /* 0x08 */ JUTNameTab* mTextureName;
};

class mDoExt_invJntPacket : public J3DPacket {
public:
    mDoExt_invJntPacket() {}
    ~mDoExt_invJntPacket() {}

    void draw();

    void setJoint(J3DModel* i_model, u16 i_jntNum) {
        mModel = i_model;
        mJntNum = i_jntNum;
    }

    /* 0x10 */ J3DModel* mModel;
    /* 0x14 */ u16 mJntNum;
};

class mDoExt_invisibleModel {
public:
    BOOL create(J3DModel*);

    void entry();
    void entryMaskOff();

    void updateDL(J3DModel*);
    void updateDL(mDoExt_McaMorf*);

    J3DModel* mModel;
    mDoExt_invJntPacket* mpPackets;
};

class mDoExt_offCupOnAupPacket : public J3DPacket {
public:
    ~mDoExt_offCupOnAupPacket();

    void draw();
    
    void entryOpa() { j3dSys.getDrawBuffer(0)->entryImm(this, 0); }
};

class mDoExt_onCupOffAupPacket : public J3DPacket {
public:
    ~mDoExt_onCupOffAupPacket();

    void draw();
    
    void entryOpa() { j3dSys.getDrawBuffer(0)->entryImm(this, 0); }
};

class mDoExt_3Dline_c {
public:
    mDoExt_3Dline_c();
    ~mDoExt_3Dline_c();

    int init(u16, int, int);

public:
    /* 0x00 */ cXyz* mpSegments;
    /* 0x04 */ u8* mpSize;
    /* 0x08 */ cXyz* mPosArr[2];
    /* 0x10 */ cXy* mTexArr[2];
};

class mDoExt_3DlineMat0_c : public mDoExt_3DlineMat_c {
public:
    int init(u16, u16, int);
    void setMaterial();
    void draw();
    void update(u16, f32, GXColor&, u16, dKy_tevstr_c*);
    void update(u16, GXColor&, dKy_tevstr_c*);
    int getMaterialID();

public:
    /* 0x08 */ GXColor mColor;
    /* 0x0C */ dKy_tevstr_c* mpTevStr;
    /* 0x10 */ s16 mNumLines;
    /* 0x12 */ s16 mNumSegmentsPerLine;
    /* 0x14 */ u16 m14;
    /* 0x16 */ u8 m16;
    /* 0x17 */ u8 m17[0x18 - 0x17];
    /* 0x18 */ mDoExt_3Dline_c* mpLines;
};

class mDoExt_3DlineMat1_c : public mDoExt_3DlineMat_c {
public:
    int init(u16, u16, ResTIMG*, int);
    void setMaterial();
    void draw();
    void update(u16, f32, GXColor&, u16, dKy_tevstr_c*);
    void update(u16, GXColor&, dKy_tevstr_c*);
    int getMaterialID();

public:
    /* 0x08 */ GXTexObj mTexObj;
    /* 0x28 */ GXColor mColor;
    /* 0x2C */ dKy_tevstr_c* mpTevStr;
    /* 0x30 */ u16 mNumLines;
    /* 0x32 */ u16 m32;
    /* 0x34 */ u16 m34;
    /* 0x36 */ u8 mCurArr;
    /* 0x37 */ u8 m37[0x38 - 0x37];
    /* 0x38 */ mDoExt_3Dline_c* mpLines;
};

J3DModel* mDoExt_J3DModel__create(J3DModelData* i_modelData, u32 i_modelFlag, u32 i_differedDlistFlag);

void mDoExt_modelUpdate(J3DModel* i_model);
void mDoExt_modelUpdateDL(J3DModel* i_model);
void mDoExt_modelEntryDL(J3DModel* i_model);

void mDoExt_modelTexturePatch(J3DModelData*);

JKRExpHeap* mDoExt_getCommandHeap();
JKRExpHeap* mDoExt_getZeldaHeap();
JKRExpHeap* mDoExt_getGameHeap();
JKRExpHeap* mDoExt_getArchiveHeap();
JKRExpHeap* mDoExt_createCommandHeap(u32 heapSize, JKRHeap* i_heap);
JKRExpHeap* mDoExt_createArchiveHeap(u32 heapSize, JKRHeap* i_heap);
JKRExpHeap* mDoExt_createZeldaHeap(u32 heapSize, JKRHeap* i_heap);
JKRExpHeap* mDoExt_createGameHeap(u32 heapSize, JKRHeap* i_heap);

s32 mDoExt_getSafeArchiveHeapSize();
s32 mDoExt_getSafeGameHeapSize();
s32 mDoExt_getSafeZeldaHeapSize();
s32 mDoExt_getSafeCommandHeapSize();

void mDoExt_setSafeArchiveHeapSize();
void mDoExt_setSafeGameHeapSize();
void mDoExt_setSafeZeldaHeapSize();
void mDoExt_setSafeCommandHeapSize();

s32 mDoExt_resIDToIndex(JKRArchive*, u16);

JKRSolidHeap * mDoExt_createSolidHeapFromGameToCurrent(u32 size, u32 align);
JKRSolidHeap * mDoExt_createSolidHeapToCurrent(u32, JKRHeap *, u32 align);
JKRSolidHeap * mDoExt_createSolidHeapFromGame(u32 i_size, u32 i_alignment);
JKRSolidHeap * mDoExt_createSolidHeapFromSystem(u32 i_size, u32 i_alignment);
void mDoExt_restoreCurrentHeap();
s32 mDoExt_adjustSolidHeap(JKRSolidHeap * pHeap);
void mDoExt_destroySolidHeap(JKRSolidHeap * pHeap);
JKRHeap* mDoExt_setCurrentHeap(JKRHeap* pHeap);

JUTFont* mDoExt_getMesgFont();
JUTFont* mDoExt_getRubyFont();

extern JKRExpHeap* zeldaHeap;
extern JKRExpHeap* gameHeap;
extern JKRExpHeap* commandHeap;
extern JKRExpHeap* archiveHeap;

#endif
