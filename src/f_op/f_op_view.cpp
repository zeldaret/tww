/**
 * f_op_view.cpp
 * View Process Framework
 */

#include "f_op/f_op_view.h"
#include "f_pc/f_pc_manager.h"

void fopVw_Draw(view_class* i_this) {
    fpcLf_DrawMethod(i_this->mSubMtd, i_this);
}

void fopVw_Execute(view_class* i_this) {
    fpcMtd_Execute(&i_this->mSubMtd->mBase, i_this);
}

s32 fopVw_IsDelete(void* i_this) {
    view_class* _this = (view_class*)i_this;
    return fpcMtd_IsDelete(&_this->mSubMtd->mBase, _this);
}

s32 fopVw_Delete(view_class* i_this) {
    return fpcMtd_Delete(&i_this->mSubMtd->mBase, i_this);
}

s32 fopVw_Create(void* i_this) {
    view_class* _this = (view_class*)i_this;

    view_process_profile_definition* pProf =
        (view_process_profile_definition*)fpcM_GetProfile(_this);
    _this->mSubMtd = pProf->mSubMtd;
    _this->field_0xc4 = pProf->unk28;

    return fpcMtd_Create(&_this->mSubMtd->mBase, _this);
}

leafdraw_method_class g_fopVw_Method = {
    (process_method_func)fopVw_Create,  (process_method_func)fopVw_Delete,
    (process_method_func)fopVw_Execute, (process_method_func)fopVw_IsDelete,
    (process_method_func)fopVw_Draw,
};
