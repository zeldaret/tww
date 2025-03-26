//
// Generated by dtk
// Translation Unit: d_material.cpp
//

#include "d/d_material.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/types.h"

mDoExt_backupMaterial_c dMat_control_c::mTempBackup;
JKRSolidHeap* dMat_control_c::mHeap;
dMat_backup_c* dMat_control_c::mBackup;
dMat_ice_c* dMat_control_c::mIce;

/* 8006F62C-8006F69C       .text restore__13dMat_backup_cFv */
void dMat_backup_c::restore() {
    JUT_ASSERT(82, mModelData != NULL);
    field_0x8.restore(mModelData);
}

/* 8006F69C-8006F740       .text create__10dMat_ice_cFP16J3DMaterialTableP19J3DAnmTextureSRTKey */
void dMat_ice_c::create(J3DMaterialTable* param_1, J3DAnmTextureSRTKey* param_2) {
    mMaterialTable = param_1;
    int rt = mBtkAnm.init(mMaterialTable, param_2, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    JUT_ASSERT(98, rt != FALSE);
    mBtkAnm.entry(mMaterialTable, mBtkAnm.getFrameCtrl()->getFrame());
}

/* 8006F740-8006F780       .text play__10dMat_ice_cFv */
void dMat_ice_c::play() {
    mBtkAnm.play();
    mBtkAnm.entryFrame();
}

/* 8006F780-8006F83C       .text copy__10dMat_ice_cFP12J3DModelData */
void dMat_ice_c::copy(J3DModelData* modelData) {
    J3DMaterial* srcMat = mMaterialTable->getMaterialNodePointer(0);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        mat->copy(srcMat);
        mat->setMaterialAnm(srcMat->getMaterialAnm());
        mat->setMaterialMode(srcMat->getMaterialMode());
    }
    J3DTexture* srcTex = mMaterialTable->getTexture();
    if (srcTex->getNum() != 0) {
        modelData->setTexture(srcTex);
        modelData->setTextureName(mMaterialTable->getTextureName());
    }
}

/* 8006F83C-8006F90C       .text updateDL__10dMat_ice_cFP8J3DModelScP21mDoExt_invisibleModel */
void dMat_ice_c::updateDL(J3DModel* model, s8 backupNo, mDoExt_invisibleModel* inv) {
    J3DDrawBuffer* buffer0 = j3dSys.getDrawBuffer(0);
    J3DDrawBuffer* buffer1 = j3dSys.getDrawBuffer(1);
    J3DModelData* modelData = model->getModelData();
    if (backupNo < 0)
        dMat_control_c::push(modelData);
    dComIfGd_setList();
    copy(modelData);
    mDoExt_modelUpdateDL(model);
    if (backupNo < 0)
        dMat_control_c::pop(modelData);
    else
        dMat_control_c::restore(backupNo);

    if (inv != NULL)
        inv->entry();

    j3dSys.setDrawBuffer(buffer0, 0);
    j3dSys.setDrawBuffer(buffer1, 1);
}

/* 8006F90C-8006F9E0       .text updateDL__10dMat_ice_cFP14mDoExt_McaMorfScP21mDoExt_invisibleModel */
void dMat_ice_c::updateDL(mDoExt_McaMorf* morf, s8 backupNo, mDoExt_invisibleModel* inv) {
    J3DDrawBuffer* buffer0 = j3dSys.getDrawBuffer(0);
    J3DDrawBuffer* buffer1 = j3dSys.getDrawBuffer(1);
    J3DModelData* modelData = morf->getModel()->getModelData();
    if (backupNo < 0)
        dMat_control_c::push(modelData);
    dComIfGd_setList();
    copy(modelData);
    morf->updateDL();
    if (backupNo < 0)
        dMat_control_c::pop(modelData);
    else
        dMat_control_c::restore(backupNo);

    if (inv != NULL)
        inv->entry();

    j3dSys.setDrawBuffer(buffer0, 0);
    j3dSys.setDrawBuffer(buffer1, 1);
}

/* 8006F9E0-8006FAB0       .text entryDL__10dMat_ice_cFP8J3DModelScP21mDoExt_invisibleModel */
void dMat_ice_c::entryDL(J3DModel* model, s8 backupNo, mDoExt_invisibleModel* inv) {
    J3DDrawBuffer* buffer0 = j3dSys.getDrawBuffer(0);
    J3DDrawBuffer* buffer1 = j3dSys.getDrawBuffer(1);
    J3DModelData* modelData = model->getModelData();
    if (backupNo < 0)
        dMat_control_c::push(modelData);
    dComIfGd_setList();
    copy(modelData);
    mDoExt_modelEntryDL(model);
    if (backupNo < 0)
        dMat_control_c::pop(modelData);
    else
        dMat_control_c::restore(backupNo);

    if (inv != NULL)
        inv->entry();

    j3dSys.setDrawBuffer(buffer0, 0);
    j3dSys.setDrawBuffer(buffer1, 1);
}

/* 8006FAB0-8006FB84       .text entryDL__10dMat_ice_cFP14mDoExt_McaMorfScP21mDoExt_invisibleModel */
void dMat_ice_c::entryDL(mDoExt_McaMorf* morf, s8 backupNo, mDoExt_invisibleModel* inv) {
    J3DDrawBuffer* buffer0 = j3dSys.getDrawBuffer(0);
    J3DDrawBuffer* buffer1 = j3dSys.getDrawBuffer(1);
    J3DModelData* modelData = morf->getModel()->getModelData();
    if (backupNo < 0)
        dMat_control_c::push(modelData);
    dComIfGd_setList();
    copy(modelData);
    morf->entryDL();
    if (backupNo < 0)
        dMat_control_c::pop(modelData);
    else
        dMat_control_c::restore(backupNo);

    if (inv != NULL)
        inv->entry();

    j3dSys.setDrawBuffer(buffer0, 0);
    j3dSys.setDrawBuffer(buffer1, 1);
}

/* 8006FB84-8006FCF0       .text create__14dMat_control_cFP16J3DMaterialTableP19J3DAnmTextureSRTKey */
void dMat_control_c::create(J3DMaterialTable* param_1, J3DAnmTextureSRTKey* param_2) {
    mHeap = mDoExt_createSolidHeapFromSystem(0, 0);
    JUT_ASSERT(308, mHeap != NULL);
    JKRHeap* heap = mDoExt_setCurrentHeap(mHeap);
    mBackup = new dMat_backup_c[16];
    mIce = new dMat_ice_c();
    JUT_ASSERT(313, mBackup != NULL && mIce != NULL);
    mIce->create(param_1, param_2);
    mTempBackup.create(0x40);
    mDoExt_adjustSolidHeap(mHeap);
    mDoExt_setCurrentHeap(heap);
}

/* 8006FD4C-8006FD88       .text __dt__13dMat_backup_cFv */
dMat_backup_c::~dMat_backup_c() {}

/* 8006FD88-8006FD98       .text __ct__13dMat_backup_cFv */
dMat_backup_c::dMat_backup_c() {
    mModelData = NULL;
}

/* 8006FD98-8006FDBC       .text remove__14dMat_control_cFv */
void dMat_control_c::remove() {
    mDoExt_destroySolidHeap(mHeap);
}

/* 8006FDBC-8006FDF4       .text restore__14dMat_control_cFSc */
void dMat_control_c::restore(s8 param_1) {
    if (param_1 < 0) {
        return;
    }
    mBackup[param_1].restore();
}
