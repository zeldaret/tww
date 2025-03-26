#ifndef F_PC_NODE_REQ_H_
#define F_PC_NODE_REQ_H_

#include "SSystem/SComponent/c_phase.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_method_tag.h"
#include "f_pc/f_pc_base.h"

typedef struct layer_class layer_class;
typedef struct process_node_class process_node_class;

typedef struct node_create_request_method_class {
    /* 0x00 */ process_method_func mpExecuteFunc;
    /* 0x04 */ process_method_func mpCancelFunc;
    /* 0x08 */ process_method_func mpUnkFunc;
    /* 0x0C */ process_method_func mpPostMethodFunc;
} node_create_request_method_class;  // Size: 0x10
// needed to match struct copy
typedef struct unk_process_node_class {
    /* 0x00 */ process_node_class* mpNodeProc;
    /* 0x04 */ fpc_ProcID mProcId;
} unk_process_node_class;  // Size: 0x08

typedef struct node_create_request {
    /* 0x00 */ create_tag_class mCreateTag;
    /* 0x14 */ process_method_tag_class mProcMthCls;
    /* 0x30 */ request_of_phase_process_class mReqPhsProc;
    /* 0x38 */ cPhs__Handler* mpPhsHandler;
    /* 0x3C */ node_create_request_method_class* mpNodeCrReqMthCls;
    /* 0x40 */ s32 mParameter;
    /* 0x44 */ uint mRequestId;
    /* 0x48 */ unk_process_node_class mNodeProc;
    /* 0x50 */ layer_class* mpLayerClass;
    /* 0x54 */ fpc_ProcID mCreatingID;
    /* 0x58 */ s16 mProcName;
    /* 0x5C */ void* mpUserData;
    /* 0x60 */ s16 unk_0x60;
} node_create_request;  // Size: 0x64

typedef struct request_node_class {
    node_class base;
    node_create_request* mNodeCrReq;
} request_node_class;

void fpcNdRq_RequestQTo(node_create_request* pNodeCreateReq);
void fpcNdRq_ToRequestQ(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_phase_IsCreated(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_phase_Create(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_phase_IsDeleteTiming(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_phase_IsDeleted(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_phase_Delete(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_DoPhase(node_create_request* pNodeCreateReq);
cPhs_State fpcNdRq_Execute(node_create_request* pNodeCreateReq);
BOOL fpcNdRq_Delete(node_create_request* pNodeCreateReq);
BOOL fpcNdRq_Cancel(node_create_request* pNodeCreateReq);
s32 fpcNdRq_Handler(void);
s32 fpcNdRq_IsPossibleTarget(process_node_class* pProcNode);
s32 fpcNdRq_IsIng(process_node_class* pProcNode);
node_create_request* fpcNdRq_Create(u32 pRequestSize);
node_create_request* fpcNdRq_ChangeNode(u32 pRequestSize, process_node_class* pProcNode,
                                        s16 param_3, void* param_4);
node_create_request* fpcNdRq_DeleteNode(u32 pRequestSize, process_node_class* pProcNode);
node_create_request* fpcNdRq_CreateNode(u32 pRequestSize, s16 param_2, void* param_3);
node_create_request*
fpcNdRq_Request(u32 param_1, int param_2, process_node_class* param_3, s16 param_4,
                void* param_5, node_create_request_method_class* pNodeCreateRequestMethodClass);
s32 fpcNdRq_ReChangeNode(uint i_requestID, s16 i_procName, void* i_data);
s32 fpcNdRq_ReRequest(uint i_requestID, s16 i_procName, void* i_data);

#endif
