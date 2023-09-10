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

class mDoExt_baseAnm {
public:
    mDoExt_baseAnm() {}
    /* 8000D320 */ int initPlay(s16 i_frameMax, int i_attribute, f32 i_rate, s16 i_startF,
                                s16 i_endF);
    /* 8000D428 */ int play();

    J3DFrameCtrl* getFrameCtrl() { return &mFrameCtrl; }
    f32 getPlaySpeed() { return mFrameCtrl.getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl.setRate(speed); }
    f32 getFrame() { return mFrameCtrl.getFrame(); }
    f32 getEndFrame() { return mFrameCtrl.getEnd(); }
    void setFrame(f32 frame) { mFrameCtrl.setFrame(frame); }
    void setPlayMode(int i_mode) { mFrameCtrl.setAttribute(i_mode); }
    void setLoopFrame(f32 i_frame) { mFrameCtrl.setLoop(i_frame); }
    bool isStop() {
        bool stopped = true;
        if (!mFrameCtrl.checkState(1) && mFrameCtrl.getRate() != 0.0f) {
            stopped = false;
        }
        return stopped;
    }

private:
    /* 0x0 */ J3DFrameCtrl mFrameCtrl;
};  // Size: 0x14

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
    /* 0x14 */ J3DAnmTextureSRTKey* mpAnm;
};  // Size: 0x18

STATIC_ASSERT(sizeof(mDoExt_btkAnm) == 0x18);

class mDoExt_brkAnm : public mDoExt_baseAnm {
public:
    mDoExt_brkAnm() { mpAnm = 0; }
    /* 8000D70C */ int init(J3DMaterialTable* i_matTable, J3DAnmTevRegKey* i_brk, int i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 param_6);
    /* 8000D7A8 */ void entry(J3DMaterialTable* i_matTable, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void entry(J3DModelData* i_modelData, f32 i_frame) {
        entry(&i_modelData->getMaterialTable(), i_frame);
    }

    int init(J3DModelData* i_modelData, J3DAnmTevRegKey* i_brk, int i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 param_6) {
        return init(&i_modelData->getMaterialTable(), i_brk, i_anmPlay, i_attribute, i_rate,
                    i_start, param_6);
    }

    int remove(J3DModelData* i_modelData) { return i_modelData->removeTevRegAnimator(mpAnm); }
    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTevRegKey* getBrkAnm() const { return mpAnm; }

private:
    /* 0x14 */ J3DAnmTevRegKey* mpAnm;
};  // Size: 0x18

STATIC_ASSERT(sizeof(mDoExt_brkAnm) == 0x18);

class mDoExt_bpkAnm : public mDoExt_baseAnm {
public:
    mDoExt_bpkAnm() { mpAnm = 0; }
    /* 8000D47C */ int init(J3DMaterialTable* i_matTable, J3DAnmColor* i_bpk, int i_anmPlay,
                            int i_attribute, f32 i_rate, s16 i_start, s16 param_6);
    /* 8000D518 */ void entry(J3DMaterialTable* i_matTable, f32 i_frame);

    void entry(J3DModelData* i_modelData) { entry(i_modelData, getFrame()); }
    void entry(J3DModelData* i_modelData, f32 i_frame) {
        entry(&i_modelData->getMaterialTable(), i_frame);
    }

    int init(J3DModelData* i_modelData, J3DAnmColor* i_bpk, int i_anmPlay, int i_attribute,
             f32 i_rate, s16 i_start, s16 param_6) {
        return init(&i_modelData->getMaterialTable(), i_bpk, i_anmPlay, i_attribute, i_rate,
                    i_start, param_6);
    }

    int remove(J3DModelData* i_modelData) { return i_modelData->removeMatColorAnimator(mpAnm); }

private:
    /* 0x14 */ J3DAnmColor* mpAnm;
};  // Size: 0x18

STATIC_ASSERT(sizeof(mDoExt_bpkAnm) == 0x18);

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
    /* 0x14 */ J3DAnmTransform* mAnm;
    /* 0x18 */ J3DMtxCalc* mpMtxCalc;
};  // Size: 0x1C

STATIC_ASSERT(sizeof(mDoExt_bckAnm) == 0x1C);

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

J3DModel* mDoExt_J3DModel__create(J3DModelData* i_modelData, u32 i_modelFlag, u32 i_differedDlistFlag);

void mDoExt_modelUpdate(J3DModel* i_model);
void mDoExt_modelUpdateDL(J3DModel* i_model);
void mDoExt_modelEntryDL(J3DModel* i_model);

#endif
