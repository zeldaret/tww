//
// Generated by dtk
// Translation Unit: c_tag_iter.cpp
//

#include "SSystem/SComponent/c_tag_iter.h"
#include "SSystem/SComponent/c_tag.h"
#include "dolphin/types.h"

/* 8024560C-80245640       .text cTgIt_MethodCall__FP16create_tag_classP13method_filter */
int cTgIt_MethodCall(create_tag_class* pTag, method_filter* pMethodFilter) {
    return pMethodFilter->mpMethodFunc((node_class*)pTag->mpTagData, pMethodFilter->mpUserData);
}

/* 80245640-80245674       .text cTgIt_JudgeFilter__FP16create_tag_classP12judge_filter */
void* cTgIt_JudgeFilter(create_tag_class* pTag, judge_filter* pJudgeFilter) {
    return pJudgeFilter->mpJudgeFunc((node_class*)pTag->mpTagData, pJudgeFilter->mpUserData);
}
