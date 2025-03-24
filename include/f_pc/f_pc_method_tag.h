
#ifndef F_PC_METHOD_TAG_H_
#define F_PC_METHOD_TAG_H_

#include "SSystem/SComponent/c_tag.h"

typedef BOOL (*process_method_tag_func)(void*);

typedef struct process_method_tag_class {
    /* 0x00 */ create_tag_class mCreateTag;
    /* 0x14 */ process_method_tag_func mpFunc;
    /* 0x18 */ void* mpMthdData;
} process_method_tag_class;  // Size: 0x1C

BOOL fpcMtdTg_Do(process_method_tag_class* pMthd);
s32 fpcMtdTg_ToMethodQ(node_list_class* pList, process_method_tag_class* pMthd);
void fpcMtdTg_MethodQTo(process_method_tag_class* pMthd);
s32 fpcMtdTg_Init(process_method_tag_class* pMthd, process_method_tag_func pFunc, void* pMthdData);

#endif
