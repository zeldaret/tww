//
// Generated by dtk
// Translation Unit: c_request.cpp
//

#include "SSystem/SComponent/c_request.h"
#include "dolphin/types.h"

/* 80245364-80245390       .text cReq_Is_Done__FP18request_base_class */
BOOL cReq_Is_Done(request_base_class* i_this) {
    if (i_this->flag1 == 1) {
        i_this->flag1 = 0;
        return TRUE;
    }
    return FALSE;
}

/* 80245390-802453C0       .text cReq_Done__FP18request_base_class */
void cReq_Done(request_base_class* i_this) {
    i_this->flag0 = 0;
    i_this->flag1 = 1;
    i_this->flag2 = 0;
}

/* 802453C0-802453E0       .text cReq_Command__FP18request_base_classUc */
void cReq_Command(request_base_class* i_this, u8 param_1) {
    cReq_Create(i_this, param_1);
}

/* 802453E0-80245410       .text cReq_Create__FP18request_base_classUc */
void cReq_Create(request_base_class* i_this, u8 param_1) {
    i_this->flag0 = 1;
    i_this->flag1 = 0;
    i_this->flag2 = param_1;
}
