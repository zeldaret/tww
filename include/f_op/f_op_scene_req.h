#ifndef F_F_OP_SCENE_REQ_H_
#define F_F_OP_SCENE_REQ_H_

#include "f_pc/f_pc_node_req.h"

class scene_class;

class scene_request_class {
public:
    node_create_request mCrtReq;
    scene_request_class* mFadeRequest;
    request_of_phase_process_class mReqPhsProcCls;
    u8 field_0x70[4];
};

uint fopScnRq_Request(int, scene_class*, s16, void*, s16, u16);
s32 fopScnRq_ReRequest(uint, s16, void*);
s32 fopScnRq_Handler(void);

#endif
