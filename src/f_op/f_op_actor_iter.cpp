/**
 * f_op_actor_iter.cpp
 * Actor Process Iterator
 */

#include "f_op/f_op_actor_iter.h"
#include "SSystem/SComponent/c_list_iter.h"
#include "SSystem/SComponent/c_tag_iter.h"
#include "f_op/f_op_actor_tag.h"

int fopAcIt_Executor(fopAcIt_ExecutorFunc i_execFunc, void* i_data) {
    method_filter filter;
    filter.mpMethodFunc = (cNdIt_MethodFunc)i_execFunc;
    filter.mpUserData = i_data;
    return cLsIt_Method(&g_fopAcTg_Queue, (cNdIt_MethodFunc)cTgIt_MethodCall, &filter);
}

void* fopAcIt_Judge(fopAcIt_JudgeFunc i_judgeFunc, void* i_data) {
    judge_filter filter;
    filter.mpJudgeFunc = (cNdIt_JudgeFunc)i_judgeFunc;
    filter.mpUserData = i_data;
    return cLsIt_Judge(&g_fopAcTg_Queue, (cNdIt_JudgeFunc)cTgIt_JudgeFilter, &filter);
}
