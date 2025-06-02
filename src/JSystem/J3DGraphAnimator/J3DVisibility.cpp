/**
 * J3DVisibility.cpp
 * J3DGraphAnimator - Visibility Manager
 */

#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

/* 802F36BC-802F377C       .text setVisibility__20J3DVisibilityManagerFP12J3DModelData */
void J3DVisibilityManager::setVisibility(J3DModelData* pModel) {
    u8 visibility;

    if ((mbActive & 1) != 0 && mAnmVisibility != NULL) {
        for (u16 index = 0; index < pModel->getShapeNum(); index++) {
            visibility = 0;
            mAnmVisibility->getVisibility(index, &visibility);
            if (visibility != 0) {
                pModel->getShapeNodePointer(index)->offFlag(J3DShpFlag_Hide);
            } else {
                pModel->getShapeNodePointer(index)->onFlag(J3DShpFlag_Hide);
            }
        }
    }
}
