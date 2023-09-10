/**
 * f_op_scene_tag.cpp
 * Scene Process Tag
 */

#include "f_op/f_op_scene_tag.h"

void fopScnTg_QueueTo(scene_tag_class* i_sceneTag) {
    cTg_SingleCut((create_tag_class*)i_sceneTag);
}

node_list_class g_fopScnTg_SceneList = {NULL, NULL, 0};

void fopScnTg_ToQueue(scene_tag_class* i_sceneTag) {
    cTg_Addition(&g_fopScnTg_SceneList, (create_tag_class*)i_sceneTag);
}

void fopScnTg_Init(scene_tag_class* i_sceneTag, void* pData) {
    cTg_Create((create_tag_class*)i_sceneTag, pData);
}
