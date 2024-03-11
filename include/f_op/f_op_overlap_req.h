#ifndef F_F_OP_OVERLAP_REQ_H_
#define F_F_OP_OVERLAP_REQ_H_

#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SComponent/c_request.h"

struct layer_class;
class overlap_task_class;

class overlap_request_class : public request_base_class {
public:
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ s16 mDelay;
    /* 0x04 */ u16 field_0x4;
    /* 0x06 */ u16 mPeektime;
    /* 0x08 */ u32 mIsPeek;
    /* 0x0C */ u32 field_0xc;
    /* 0x10 */ s16 mProcName;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ uint mPId;
    /* 0x18 */ request_of_phase_process_class mPhs;
    /* 0x20 */ overlap_task_class * mpTask;
    /* 0x24 */ layer_class* pCurrentLayer;
};

int fopOvlpReq_OverlapClr(overlap_request_class* param_1);
overlap_request_class* fopOvlpReq_Request(overlap_request_class*, s16, u16);
s32 fopOvlpReq_Handler(overlap_request_class*);
BOOL fopOvlpReq_Cancel(overlap_request_class*);
BOOL fopOvlpReq_Is_PeektimeLimit(overlap_request_class*);

#endif
