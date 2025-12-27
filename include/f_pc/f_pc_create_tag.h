
#ifndef F_PC_CREATE_TAG_H_
#define F_PC_CREATE_TAG_H_

#include "SSystem/SComponent/c_list.h"
#include "SSystem/SComponent/c_tag.h"

typedef struct create_tag {
    /* 0x00 */ create_tag_class base;
} create_tag;  // Size: 0x14

void fpcCtTg_ToCreateQ(create_tag* pTag);
void fpcCtTg_CreateQTo(create_tag* pTag);
s32 fpcCtTg_Init(create_tag* pTag, void* pUserData);

extern node_list_class g_fpcCtTg_Queue;

#endif
