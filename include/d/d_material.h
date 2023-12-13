#ifndef D_MATERIAL_H
#define D_MATERIAL_H

#include "dolphin/types.h"

class J3DMaterialTable;
class J3DAnmTextureSRTKey;
class mDoExt_McaMorf;
class mDoExt_invisibleModel;
class J3DModel;
class J3DModelData;

class dMat_ice_c {
public:
    void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);
    void play();
    void copy(J3DModelData*);
    void updateDL(J3DModel*, s8, mDoExt_invisibleModel*);
    void updateDL(mDoExt_McaMorf*, s8, mDoExt_invisibleModel*);
    void entryDL(J3DModel*, s8, mDoExt_invisibleModel*);
    void entryDL(mDoExt_McaMorf*, s8, mDoExt_invisibleModel*);
};

class dMat_control_c {
public:
    static void icePlay() { mIce->play(); }
    static void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);

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

    static dMat_ice_c* mIce;
};

#endif /* D_MATERIAL_H */