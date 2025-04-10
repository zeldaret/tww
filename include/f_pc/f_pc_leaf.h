
#ifndef F_PC_LEAF_H_
#define F_PC_LEAF_H_

#include "f_pc/f_pc_base.h"
#include "f_pc/f_pc_draw_priority.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_profile.h"

typedef struct leafdraw_method_class {
    /* 0x00 */ process_method_class base;
    /* 0x10 */ process_method_func mpDrawFunc;
} leafdraw_method_class;

typedef struct leafdraw_class {
    /* 0x00 */ base_process_class base;
    /* 0xB8 */ leafdraw_method_class* mpDrawMtd;
    /* 0xBC */ s8 mbUnk0;
    /* 0xBD */ u8 mbUnk1;
    /* 0xBE */ draw_priority_class mDwPi;
} leafdraw_class;

typedef struct leaf_process_profile_definition {
    /* 0x00 */ process_profile_definition base;
    /* 0x1C */ leafdraw_method_class* sub_method; // Subclass methods
    /* 0x20 */ s16 mPriority; // mDrawPriority
} leaf_process_profile_definition;

s16 fpcLf_GetPriority(leafdraw_class* pLeaf);
BOOL fpcLf_DrawMethod(leafdraw_method_class* pMthd, void* pUserData);
BOOL fpcLf_Draw(leafdraw_class* pMthd);
BOOL fpcLf_Execute(leafdraw_class* pLeaf);
BOOL fpcLf_IsDelete(leafdraw_class* pLeaf);
BOOL fpcLf_Delete(leafdraw_class* pLeaf);
cPhs_State fpcLf_Create(leafdraw_class* pLeaf);

extern int g_fpcLf_type;
extern leafdraw_method_class g_fpcLf_Method;

#endif
