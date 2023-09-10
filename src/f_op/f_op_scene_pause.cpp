/**
 * f_op_scene_pause.cpp
 * Scene Process Pause
 */

#include "f_op/f_op_scene_pause.h"
#include "f_op/f_op_scene.h"
#include "f_pc/f_pc_manager.h"

int fopScnPause_Enable(scene_class* i_scene) {
    if (i_scene) {
        fpcM_PauseEnable(i_scene, 1);
        fpcM_PauseEnable(i_scene, 2);
        return 1;
    }

    return 0;
}

int fopScnPause_Disable(scene_class* i_scene) {
    if (i_scene) {
        void* tmp = (void*)i_scene->mBase.mBase.mLyTg.mpLayer->mpPcNode;

        if (!tmp) {
            fpcM_PauseDisable(i_scene, 1);
            fpcM_PauseDisable(i_scene, 2);
        } else if (fpcEx_IsExist((s32)((int*)tmp)[1]) == 1) {
            if (!fpcM_IsPause(tmp, 1)) {
                fpcM_PauseDisable(i_scene, 1);
            }

            if (!fpcM_IsPause(tmp, 2)) {
                fpcM_PauseDisable(i_scene, 2);
            }
        }

        return 1;
    }

    return 0;
}
