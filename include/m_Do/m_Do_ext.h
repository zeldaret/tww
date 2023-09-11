#ifndef M_DO_EXT_H
#define M_DO_EXT_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

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
    mDoExt_baseAnm() { mpFrameCtrl = NULL; }
    virtual ~mDoExt_baseAnm() {}

    int initPlay(s16 i_frameMax, int i_attribute, f32 i_rate, s16 i_startF, s16 i_endF);
    int play();

    J3DFrameCtrl* getFrameCtrl() { return mpFrameCtrl; }
    f32 getPlaySpeed() { return mpFrameCtrl->getRate(); }
    void setPlaySpeed(f32 speed) { mpFrameCtrl->setRate(speed); }
    f32 getFrame() { return mpFrameCtrl->getFrame(); }
    f32 getEndFrame() { return mpFrameCtrl->getEnd(); }
    void setFrame(f32 frame) { mpFrameCtrl->setFrame(frame); }
    void setPlayMode(int i_mode) { mpFrameCtrl->setAttribute(i_mode); }
    void setLoopFrame(f32 i_frame) { mpFrameCtrl->setLoop(i_frame); }
    bool isStop() {
        bool stopped = true;
        if (!mpFrameCtrl->checkState(1) && mpFrameCtrl->getRate() != 0.0f) {
            stopped = false;
        }
        return stopped;
    }

private:
    /* 0x4 */ J3DFrameCtrl* mpFrameCtrl;
};  // Size: 0x08

class mDoExt_btkAnm : public mDoExt_baseAnm {
public:
    mDoExt_btkAnm() { mpTexMtxAnm = NULL; }
    int init(J3DMaterialTable* i_matTable, J3DAnmTextureSRTKey* i_btk, int i_anmPlay,
             int i_attribute, f32 i_rate, s16 i_start, s16 i_end, bool i_modify, bool i_entry);
    void entry(J3DMaterialTable* i_matTable, f32 i_frame);
    void entry(J3DModelData *i_modelData, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    int init(J3DModelData* i_modelData, J3DAnmTextureSRTKey* i_btk, int i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, bool i_entry) {
        return init(&i_modelData->getMaterialTable(), i_btk, i_anmPlay, i_attribute, i_rate,
                    i_start, i_end, i_modify, i_entry);
    }

    int remove(J3DModelData* i_modelData) { return i_modelData->removeTexMtxAnimator(mpAnm); }
    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTextureSRTKey* getBtkAnm() const { return mpAnm; }

private:
    /* 0x08 */ J3DAnmTextureSRTKey* mpAnm;
    /* 0x0C */ J3DTexMtxAnm* mpTexMtxAnm;
    /* 0x10 */ s16 mUpdateMaterialNum;
};  // Size: 0x14

STATIC_ASSERT(sizeof(mDoExt_btkAnm) == 0x14);

class J3DTevColorAnm;
class J3DTevKColorAnm;
class mDoExt_brkAnm : public mDoExt_baseAnm {
public:
    mDoExt_brkAnm() { mpAnm = NULL; }
    /* 8000D70C */ int init(J3DMaterialTable* i_matTable, J3DAnmTevRegKey* i_brk, int i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry);
    /* 8000D7A8 */ void entry(J3DMaterialTable* i_matTable, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void entry(J3DModelData* i_modelData, f32 i_frame) {
        entry(&i_modelData->getMaterialTable(), i_frame);
    }

    int init(J3DModelData* i_modelData, J3DAnmTevRegKey* i_brk, int i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 i_end, bool i_modify, int i_entry) {
        return init(&i_modelData->getMaterialTable(), i_brk, i_anmPlay, i_attribute, i_rate,
                    i_start, i_end, i_modify, i_entry);
    }

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
    mDoExt_bckAnm() { mpMtxCalc = NULL; }
    /* 8000D7DC */ int init(J3DModelData * i_model, J3DAnmTransform* i_bck, int i_play, int i_attr,
                            f32 i_rate, s16 i_startF, s16 i_endF1, bool i_modify);
    /* 8000D990 */ void changeBckOnly(J3DAnmTransform* i_bck);
    /* 8000D9CC */ void entry(J3DModelData* i_modelData, f32 i_frame);
    /* 8000D9E8 */ void entryJoint(J3DModelData* i_modelData, u16 i_jntNo, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }

    void remove(J3DModelData* i_modelData) { i_modelData->getJointNodePointer(0)->setMtxCalc(NULL); }

    J3DAnmTransform* getBckAnm() { return mAnm; }

    void removeJoint(J3DModelData* i_modelData, u16 i_idx) {
        J3DJoint* mpJnt = i_modelData->getJointNodePointer(i_idx);
        mpJnt->setMtxCalc(0);
    }

private:
    /* 0x08 */ J3DAnmTransform* mAnm;
    /* 0x0C */ J3DMtxCalc* mpMtxCalc;
};  // Size: 0x10

STATIC_ASSERT(sizeof(mDoExt_bckAnm) == 0x10);

class mDoExt_btpAnm : public mDoExt_baseAnm {
public:
    mDoExt_btpAnm() { mpAnm = NULL; }
    /* 8000D54C */ int init(J3DMaterialTable* i_matTable, J3DAnmTexPattern* i_btk, int i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 param_6);
    /* 8000D5E8 */ void entry(J3DMaterialTable* i_matTable, s16 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void entry(J3DModelData* i_modelData, s16 i_frame) {
        entry(&i_modelData->getMaterialTable(), i_frame);
    }

    int init(J3DModelData* i_modelData, J3DAnmTexPattern* i_btk, int i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 param_6) {
        return init(&i_modelData->getMaterialTable(), i_btk, i_anmPlay, i_attribute, i_rate,
                    i_start, param_6);
    }

    int remove(J3DModelData* i_modelData) { return i_modelData->removeTexNoAnimator(mpAnm); }

private:
    /* 0x14 */ J3DAnmTexPattern* mpAnm;
};

class mDoExt_blkAnm : public mDoExt_baseAnm {
public:
    /* 8000DA08 */ int init(J3DDeformData* i_deformData, J3DAnmCluster* i_blk, int i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 param_6);

    J3DAnmCluster* getBlkAnm() { return mpAnm; }

private:
    /* 0x14 */ J3DAnmCluster* mpAnm;
};

class mDoExt_AnmRatioPack {
public:
    /* 80140DF0 */ ~mDoExt_AnmRatioPack();
    /* 80140E2C */ mDoExt_AnmRatioPack();

    void setRatio(f32 ratio) { mRatio = ratio; }
    f32 getRatio() { return mRatio; }
    J3DAnmTransform* getAnmTransform() { return mAnmTransform; }
    void setAnmTransform(J3DAnmTransform* anm) { mAnmTransform = anm; }

private:
    /* 0x0 */ f32 mRatio;
    /* 0x4 */ J3DAnmTransform* mAnmTransform;
};  // Size: 0x8

class mDoExt_MtxCalcOldFrame {
public:
    /* 8000F848 */ void initOldFrameMorf(f32, u16, u16);
    /* 8000F8CC */ void decOldFrameMorfCounter();

    f32 getOldFrameRate() { return mOldFrameRate; }
    J3DTransformInfo* getOldFrameTransInfo(int i) { return &mOldFrameTransInfo[i]; }
    u16 getOldFrameStartJoint() { return mOldFrameStartJoint; }
    Quaternion* getOldFrameQuaternion(int i_no) { return &mOldFrameQuaternion[i_no]; }

private:
    /* 0x00 */ bool mOldFrameFlg;
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

struct mDoExt_MtxCalcAnmBlendTblOld
    : public J3DMtxCalcNoAnm<J3DMtxCalcCalcTransformMaya, J3DMtxCalcJ3DSysInitMaya> {
    /* 80014EB0 */ virtual ~mDoExt_MtxCalcAnmBlendTblOld();
    /* 8000F4B0 */ virtual void calc();

    /* 0x4 */ int mNum;
    /* 0x8 */ mDoExt_AnmRatioPack* mAnmRatio;
};  // Size: 0xC

struct mDoExt_MtxCalcAnmBlendTbl : public mDoExt_MtxCalcAnmBlendTblOld {
    /* 800D00BC */ J3DAnmTransform* getAnm(int);

    /* 80014F3C */ virtual ~mDoExt_MtxCalcAnmBlendTbl();
    /* 8000F26C */ virtual void calc();

    /* 0xC */ mDoExt_MtxCalcOldFrame* mOldFrame;
};

class mDoExt_McaMorfCallBack1_c {
public:
    virtual void execute(u16, J3DTransformInfo*) = 0;
};

class mDoExt_3DlineMat_c {
public:
    /* 0x0 */ void* field_0x0;
    /* 0x4 */ mDoExt_3DlineMat_c* field_0x4;
};

class mDoExt_3DlineMatSortPacket : public J3DPacket {
public:
    mDoExt_3DlineMatSortPacket() { mp3DlineMat = NULL; }

    void reset() { mp3DlineMat = NULL; }

    void setMat(mDoExt_3DlineMat_c*);
    virtual void draw();
    virtual ~mDoExt_3DlineMatSortPacket();

private:
    /* 0x10 */ mDoExt_3DlineMat_c* mp3DlineMat;
};

J3DModel* mDoExt_J3DModel__create(J3DModelData* i_modelData, u32 i_modelFlag, u32 i_differedDlistFlag);

void mDoExt_modelUpdate(J3DModel* i_model);
void mDoExt_modelUpdateDL(J3DModel* i_model);
void mDoExt_modelEntryDL(J3DModel* i_model);

JKRExpHeap* mDoExt_getCommandHeap();
JKRExpHeap* mDoExt_getZeldaHeap();
JKRExpHeap* mDoExt_getGameHeap();
JKRExpHeap* mDoExt_getArchiveHeap();

extern JKRExpHeap* zeldaHeap;
extern JKRExpHeap* gameHeap;
extern JKRExpHeap* archiveHeap;

#endif
