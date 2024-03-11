#ifndef F_F_OP_OVERLAP_MNG_H_
#define F_F_OP_OVERLAP_MNG_H_

#include "f_pc/f_pc_leaf.h"
#include "f_op/f_op_overlap_req.h"

struct request_base_class;

struct overlap_method_class {
    /* 0x00 */ leafdraw_method_class base;
};

class overlap_task_class : public leafdraw_class {
public:
    /* 0xC0 */ overlap_method_class* sub_method;
    /* 0xC4 */ request_base_class mRq;
    /* 0xC8 */ int mScenePId;
};  // Size: 0xCC

struct overlap_process_profile_definition {
    /* 0x00 */ leaf_process_profile_definition base;
    /* 0x24 */ overlap_method_class* sub_method;
};  // Size: 0x28

int fopOvlpM_SceneIsStop();
int fopOvlpM_SceneIsStart();
void fopOvlpM_Management();
int fopOvlpM_IsOutReq(overlap_task_class* i_this);
void fopOvlpM_Done(overlap_task_class* i_this);
void fopOvlpM_ToldAboutID(uint pid);
int fopOvlpM_IsPeek();
int fopOvlpM_IsDone();
int fopOvlpM_IsDoingReq();
int fopOvlpM_ClearOfReq();
request_base_class* fopOvlpM_Request(s16 procName, u16 peekTime);
int fopOvlpM_Cancel();
void fopOvlpM_Init();

#endif