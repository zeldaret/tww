//
// Generated by dtk
// Translation Unit: f_pc_delete_tag.cpp
//

#include "SSystem/SComponent/c_list.h"
#include "f_pc/f_pc_delete_tag.h"
#include "dolphin/types.h"

node_list_class g_fpcDtTg_Queue = {NULL, NULL, 0};

// hack to make functions that return comparisons as int match
extern int __cntlzw(unsigned int);
inline BOOL checkEqual(s32 a, s32 b) {
    return (u32)__cntlzw(a - b) >> 5;
}

/* 8003D170-8003D188       .text fpcDtTg_IsEmpty__Fv */
BOOL fpcDtTg_IsEmpty() {
    return checkEqual(g_fpcDtTg_Queue.mSize, 0);
}

/* 8003D188-8003D1BC       .text fpcDtTg_ToDeleteQ__FP16delete_tag_class */
void fpcDtTg_ToDeleteQ(delete_tag_class* i_deleteTag) {
    i_deleteTag->mTimer = 1;
    cTg_Addition(&g_fpcDtTg_Queue, &i_deleteTag->mBase);
}

/* 8003D1BC-8003D1DC       .text fpcDtTg_DeleteQTo__FP16delete_tag_class */
void fpcDtTg_DeleteQTo(delete_tag_class* i_deleteTag) {
    cTg_SingleCut(&i_deleteTag->mBase);
}

/* 8003D1DC-8003D25C       .text fpcDtTg_Do__FP16delete_tag_classPFPv_i */
s32 fpcDtTg_Do(delete_tag_class* i_deleteTag, delete_tag_func i_func) {
    if (i_deleteTag->mTimer <= 0) {
        s32 ret;
        fpcDtTg_DeleteQTo(i_deleteTag);
        ret = i_func(i_deleteTag->mBase.mpTagData);
        if (ret == 0) {
            fpcDtTg_ToDeleteQ(i_deleteTag);
            return 0;
        } else {
            return 1;
        }
    } else {
        i_deleteTag->mTimer--;
        return 0;
    }
}

/* 8003D25C-8003D280       .text fpcDtTg_Init__FP16delete_tag_classPv */
s32 fpcDtTg_Init(delete_tag_class* i_deleteTag, void* i_data) {
    cTg_Create(&i_deleteTag->mBase, i_data);
    return 1;
}
