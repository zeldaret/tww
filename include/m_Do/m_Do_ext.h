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
    mDoExt_baseAnm() {}
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
    mDoExt_btkAnm() { mpAnm = 0; }
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

J3DModel* mDoExt_J3DModel__create(J3DModelData* i_modelData, u32 i_modelFlag, u32 i_differedDlistFlag);

void mDoExt_modelUpdate(J3DModel* i_model);
void mDoExt_modelUpdateDL(J3DModel* i_model);
void mDoExt_modelEntryDL(J3DModel* i_model);

#endif
