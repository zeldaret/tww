/*
 * J3DVisibility.cpp
 */
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

void J3DVisibilityManager::setVisibility(J3DModelData* pModel) {
    u8 vis;

    if ((mbActive & 1) != 0 && (mAnmVisibility != NULL)) {
        for (u16 index = 0; index < pModel->getShapeNum(); index++) {
            vis = 0;
            mAnmVisibility->getVisibility(index, &vis);
            if (vis != 0) {
                pModel->getShapeNodePointer(index)->offFlag(1);
            } else {
                pModel->getShapeNodePointer(index)->onFlag(1);
            }
        }
    }
}

J3DVisibilityManager::~J3DVisibilityManager() {}
