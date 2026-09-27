/**
 * d_a_tag_kb_item.cpp
 *
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tag_kb_item.h"

namespace daTagKbItem_prm {
    inline u32 getItemNo(daTagKbItem_c* i_this) { return fopAcM_GetParam(i_this) & 0xFF; }
    inline s8 getItemBitNo(daTagKbItem_c* i_this) { return (fopAcM_GetParam(i_this) >> 8) & 0xFF; }
    inline s8 getEnemyKind(daTagKbItem_c* i_this) { return (fopAcM_GetParam(i_this) >> 16) & 0xFF; }
    inline u32 getSwBitNo(daTagKbItem_c* i_this) { return (fopAcM_GetParam(i_this) >> 24) & 0xFF; }
};

/* 00000078-000000C8       .text _delete__13daTagKbItem_cFv */
bool daTagKbItem_c::_delete() {
#if VERSION > VERSION_JPN
    if (mItemNo != dItemNo_NONE_e && mSwBitNo != 0xff) {
        fopAcM_offSwitch(this, mSwBitNo);
    }
#endif
    return true;
}

/* 000000C8-0000010C       .text CreateInit__13daTagKbItem_cFv */
void daTagKbItem_c::CreateInit() {
    mItemNo = daTagKbItem_prm::getItemNo(this);
    mItemBitNo = daTagKbItem_prm::getItemBitNo(this);
    mEnemyKind = daTagKbItem_prm::getEnemyKind(this);
    mSwBitNo = daTagKbItem_prm::getSwBitNo(this);
    field_0x298 = false;
    field_0x299 = 0;
    mpActor = NULL;
}

/* 0000010C-000001BC       .text _create__13daTagKbItem_cFv */
cPhs_State daTagKbItem_c::_create() {
    fopAcM_ct(this, daTagKbItem_c);

    CreateInit();
    if ((mItemBitNo != 0x1f && fopAcM_isItem(this, mItemBitNo)) ||
        (mSwBitNo != 0xff && fopAcM_isSwitch(this, mSwBitNo)))
    {
        return cPhs_ERROR_e;
    }
    return cPhs_COMPLEATE_e;
}

/* 000001BC-000001C4       .text _execute__13daTagKbItem_cFv */
bool daTagKbItem_c::_execute() {
#if VERSION <= VERSION_JPN
    if ((mItemBitNo != 0x1f && fopAcM_isItem(this, mItemBitNo)) ||
        (mSwBitNo != 0xff && fopAcM_isSwitch(this, mSwBitNo)))
    {
        fopAcM_delete(this);
    }
#endif
    return true;
}

/* 000001C4-000001CC       .text _draw__13daTagKbItem_cFv */
bool daTagKbItem_c::_draw() {
    return true;
}

/* 000001CC-000001EC       .text daTagKbItem_Create__FPv */
static cPhs_State daTagKbItem_Create(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_create();
}

/* 000001EC-00000210       .text daTagKbItem_Delete__FPv */
static BOOL daTagKbItem_Delete(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_delete();
}

/* 00000210-00000234       .text daTagKbItem_Draw__FPv */
static BOOL daTagKbItem_Draw(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_draw();
}

/* 00000234-00000258       .text daTagKbItem_Execute__FPv */
static BOOL daTagKbItem_Execute(void* i_this) {
    return static_cast<daTagKbItem_c*>(i_this)->_execute();
}

/* 00000258-00000260       .text daTagKbItem_IsDelete__FPv */
static BOOL daTagKbItem_IsDelete(void* i_this) {
    UNUSED(i_this);
    return TRUE;
}

static actor_method_class daTagKbItemMethodTable = {
    (process_method_func)daTagKbItem_Create,
    (process_method_func)daTagKbItem_Delete,
    (process_method_func)daTagKbItem_Execute,
    (process_method_func)daTagKbItem_IsDelete,
    (process_method_func)daTagKbItem_Draw,
};

actor_process_profile_definition g_profile_TAG_KB_ITEM = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_TAG_KB_ITEM_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTagKbItem_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_TAG_KB_ITEM_e,
    /* Actor SubMtd */ &daTagKbItemMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
