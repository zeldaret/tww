/**
 * d_a_tag_kb_item.cpp
 *
 */

#include "d/actor/d_a_tag_kb_item.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

/* 00000078-000000C8       .text _delete__13daTagKbItem_cFv */
bool daTagKbItem_c::_delete() {
#if VERSION != VERSION_JPN
    if (field_0x2a0 != 0xff && field_0x2a4 != 0xff) {
        dComIfGs_offSwitch(field_0x2a4, orig.roomNo);
    }
#endif
    return 1;
}

/* 000000C8-0000010C       .text CreateInit__13daTagKbItem_cFv */
void daTagKbItem_c::CreateInit() {
    field_0x2a0 = fopAcM_GetParam(this);
    s8 paramBit = fopAcM_GetParamBit(fopAcM_GetParam(this), 8, 8);
    field_0x29c = paramBit;
    field_0x2a1 = fopAcM_GetParamBit(fopAcM_GetParam(this), 0x10, 8);
    field_0x2a4 = fopAcM_GetParamBit(fopAcM_GetParam(this), 0x18, 8);
    field_0x298 = 0;
    field_0x299 = 0;
    mpActor = NULL;
}

/* 0000010C-000001BC       .text _create__13daTagKbItem_cFv */
int daTagKbItem_c::_create() {
    fopAcM_SetupActor(this, daTagKbItem_c);

    CreateInit();
    if (field_0x29c != 0x1f && dComIfGs_isItem(field_0x29c, orig.roomNo) ||
        field_0x2a4 != 0xff && dComIfGs_isSwitch(field_0x2a4, orig.roomNo))
    {
        return cPhs_ERROR_e;
    }
    return cPhs_COMPLEATE_e;
}

/* 000001BC-000001C4       .text _execute__13daTagKbItem_cFv */
bool daTagKbItem_c::_execute() {
#if VERSION == VERSION_JPN
    if (field_0x29c != 0x1f && dComIfGs_isItem(field_0x29c, orig.roomNo) ||
        field_0x2a4 != 0xff && dComIfGs_isSwitch(field_0x2a4, orig.roomNo))
    {
        fopAcM_delete(this);
    }
#endif
    return 1;
}

/* 000001C4-000001CC       .text _draw__13daTagKbItem_cFv */
bool daTagKbItem_c::_draw() {
    return 1;
}

/* 000001CC-000001EC       .text daTagKbItem_Create__FPv */
static int daTagKbItem_Create(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_create();
}

/* 000001EC-00000210       .text daTagKbItem_Delete__FPv */
static int daTagKbItem_Delete(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_delete();
}

/* 00000210-00000234       .text daTagKbItem_Draw__FPv */
static int daTagKbItem_Draw(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_draw();
}

/* 00000234-00000258       .text daTagKbItem_Execute__FPv */
static int daTagKbItem_Execute(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_execute();
}

/* 00000258-00000260       .text daTagKbItem_IsDelete__FPv */
static int daTagKbItem_IsDelete(void* i_this) {
    return 1;
}

static actor_method_class daTagKbItemMethodTable = {
    (process_method_func)daTagKbItem_Create,  (process_method_func)daTagKbItem_Delete,
    (process_method_func)daTagKbItem_Execute, (process_method_func)daTagKbItem_IsDelete,
    (process_method_func)daTagKbItem_Draw,
};

actor_process_profile_definition g_profile_TAG_KB_ITEM = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_TAG_KB_ITEM,
    &g_fpcLf_Method.mBase,
    sizeof(daTagKbItem_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0127,
    &daTagKbItemMethodTable,
    fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
