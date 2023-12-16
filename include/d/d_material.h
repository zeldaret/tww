#ifndef D_MATERIAL_H
#define D_MATERIAL_H

#include "m_Do/m_Do_ext.h"

class J3DMaterialTable;
class J3DAnmTextureSRTKey;
class mDoExt_McaMorf;
class mDoExt_invisibleModel;
class J3DModel;
class J3DModelData;

class dMat_backup_c {
public:
    dMat_backup_c();
    ~dMat_backup_c();
    void restore();

    /* 0x00 */ J3DModelData* mModelData;
    /* 0x04 */ u8 field_0x4[4];
    /* 0x08 */ mDoExt_backupMaterial_c field_0x8;
};

class dMat_ice_c {
public:
    void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);
    void play();
    void copy(J3DModelData*);
    void updateDL(J3DModel*, s8, mDoExt_invisibleModel*);
    void updateDL(mDoExt_McaMorf*, s8, mDoExt_invisibleModel*);
    void entryDL(J3DModel*, s8, mDoExt_invisibleModel*);
    void entryDL(mDoExt_McaMorf*, s8, mDoExt_invisibleModel*);

    /* 0x00 */ J3DMaterialTable* field_0x0;
    /* 0x04 */ mDoExt_btkAnm field_0x4;
};

class dMat_control_c {
public:
    static void icePlay() { mIce->play(); }
    static void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);
    static void remove();
    static void restore(s8);

    static void iceEntryDL(J3DModel* model, s8 param_2, mDoExt_invisibleModel* invisModel) {
        mIce->entryDL(model, param_2, invisModel);
    }
    static void iceEntryDL(mDoExt_McaMorf* morf, s8 param_2, mDoExt_invisibleModel* invisModel) {
        mIce->entryDL(morf, param_2, invisModel);
    }
    static void iceUpdateDL(J3DModel* model, s8 param_2, mDoExt_invisibleModel* invisModel) {
        mIce->updateDL(model, param_2, invisModel);
    }
    static void iceUpdateDL(mDoExt_McaMorf* morf, s8 param_2, mDoExt_invisibleModel* invisModel) {
        mIce->updateDL(morf, param_2, invisModel);
    }

    // TODO:
    static void pop(J3DModelData*) {}
    static void push(J3DModelData*) {}

    static mDoExt_backupMaterial_c mTempBackup;
    static JKRSolidHeap* mHeap;
    static dMat_backup_c* mBackup;
    static dMat_ice_c* mIce;
};

#endif /* D_MATERIAL_H */
