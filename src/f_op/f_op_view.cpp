/**
 * f_op_view.cpp
 * View Process Framework
 */

#include "f_op/f_op_view.h"
#include "f_pc/f_pc_manager.h"

BOOL fopVw_Draw(view_class* i_this) {
    return fpcLf_DrawMethod(i_this->sub_method, i_this);
}

BOOL fopVw_Execute(view_class* i_this) {
    return fpcMtd_Execute(&i_this->sub_method->base, i_this);
}

BOOL fopVw_IsDelete(void* i_this) {
    view_class* _this = (view_class*)i_this;
    return fpcMtd_IsDelete(&_this->sub_method->base, _this);
}

BOOL fopVw_Delete(view_class* i_this) {
    return fpcMtd_Delete(&i_this->sub_method->base, i_this);
}

cPhs_State fopVw_Create(void* i_this) {
    view_class* _this = (view_class*)i_this;

    view_process_profile_definition* pProf =
        (view_process_profile_definition*)fpcM_GetProfile(_this);
    _this->sub_method = pProf->sub_method;
    _this->field_0xc4 = pProf->unk28;

    return fpcMtd_Create(&_this->sub_method->base, _this);
}

leafdraw_method_class g_fopVw_Method = {
    (process_method_func)fopVw_Create,
    (process_method_func)fopVw_Delete,
    (process_method_func)fopVw_Execute,
    (process_method_func)fopVw_IsDelete,
    (process_method_func)fopVw_Draw,
};
