#ifndef D_MATERIAL_H
#define D_MATERIAL_H

#include "dolphin/types.h"

class J3DMaterialTable;
class J3DAnmTextureSRTKey;
class mDoExt_McaMorf;
class mDoExt_invisibleModel;

class dMat_ice_c {
public:
    void play();
    void entryDL(mDoExt_McaMorf*, s8, mDoExt_invisibleModel*);
};

class dMat_control_c {
public:
    static void icePlay() { mIce->play(); }
    static void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);

    static void iceEntryDL(mDoExt_McaMorf* morf, s8 param_2, mDoExt_invisibleModel* invisModel) {
        mIce->entryDL(morf, param_2, invisModel);
    }

    static dMat_ice_c* mIce;
};

#endif /* D_MATERIAL_H */