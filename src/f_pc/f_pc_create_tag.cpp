//
// Generated by dtk
// Translation Unit: f_pc_create_tag.cpp
//

#include "f_pc/f_pc_create_tag.h"

node_list_class g_fpcCtTg_Queue = {NULL, NULL, 0};

/* 8003D078-8003D0A4       .text fpcCtTg_ToCreateQ__FP10create_tag */
void fpcCtTg_ToCreateQ(create_tag* i_createTag) {
    cTg_Addition(&g_fpcCtTg_Queue, &i_createTag->base);
}

/* 8003D0A4-8003D0C4       .text fpcCtTg_CreateQTo__FP10create_tag */
void fpcCtTg_CreateQTo(create_tag* i_createTag) {
    cTg_SingleCut(&i_createTag->base);
}

/* 8003D0C4-8003D0E8       .text fpcCtTg_Init__FP10create_tagPv */
s32 fpcCtTg_Init(create_tag* i_createTag, void* i_data) {
    cTg_Create(&i_createTag->base, i_data);
    return 1;
}
