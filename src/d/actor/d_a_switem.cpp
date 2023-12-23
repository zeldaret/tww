//
// Generated by dtk
// Translation Unit: d_a_switem.cpp
//

#include "d/actor/d_a_switem.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_draw_tag.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/actor/d_a_item.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 25.0f,
        /* Height */ 50.0f,
    },
};

/* 00000078-00000080       .text _delete__10daSwItem_cFv */
bool daSwItem_c::_delete() {
    return true;
}

/* 00000080-00000154       .text CreateInit__10daSwItem_cFv */
BOOL daSwItem_c::CreateInit() {
    int itemBitNo = daSwItem_prm::getItemBitNo(this);
    mAtTypeTrigger = daSwItem_prm::getAtType(this);

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetR(mScale.x * 25.0f);
    mCyl.SetH(mScale.y * 50.0f);

    if (fopAcM_isItem(this, itemBitNo) && itemBitNo != 0x7F) {
        return FALSE;
    }

    fopDwTg_DrawQTo(&mDwTg);
    return TRUE;
}

/* 00000154-00000250       .text _create__10daSwItem_cFv */
s32 daSwItem_c::_create() {
    fopAcM_SetupActor(this, daSwItem_c);

    if (!CreateInit()) {
        return cPhs_ERROR_e;
    }

    return cPhs_COMPLEATE_e;
}

/* 00000408-000006DC       .text _execute__10daSwItem_cFv */
bool daSwItem_c::_execute() {
    /* Nonmatching */
    bool triggered = false;
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* obj = mCyl.GetTgHitObj();
        if(obj) {
            switch (mAtTypeTrigger) {
            case 0xFF:
                triggered = true;
                break;
            case 0:
                if (obj->ChkAtType(AT_TYPE_SWORD) || obj->ChkAtType(AT_TYPE_BOKO_STICK) ||
                    obj->ChkAtType(AT_TYPE_STALFOS_MACE) || obj->ChkAtType(AT_TYPE_MACHETE) ||
                    obj->ChkAtType(AT_TYPE_DARKNUT_SWORD))
                {
                    triggered = true;
                }
                break;
            case 1:
                if (obj->ChkAtType(AT_TYPE_BOMB)) {
                    triggered = true;
                }
                break;
            case 2:
                if (obj->ChkAtType(AT_TYPE_BOOMERANG)) {
                    triggered = true;
                }
                break;
            case 3:
                if (obj->ChkAtType(AT_TYPE_SKULL_HAMMER)) {
                    triggered = true;
                }
                break;
            case 4:
                if (obj->ChkAtType(AT_TYPE_FIRE_ARROW) || obj->ChkAtType(AT_TYPE_ICE_ARROW) ||
                    obj->ChkAtType(AT_TYPE_LIGHT_ARROW) || obj->ChkAtType(AT_TYPE_NORMAL_ARROW))
                {
                    triggered = true;
                }
                break;
            case 5:
                if (obj->ChkAtType(0x8000)) {
                    triggered = true;
                }
                break;
            }
        }
    }

    if (triggered && !mSpawnedItem) {
        int itemTbl = daSwItem_prm::getItemTbl(this);
        int itemBitNo = daSwItem_prm::getItemBitNo(this);
        if (fopAcM_isItem(this, daSwItem_prm::getItemBitNo(this))) {
            itemBitNo = 0x7F;
        }

        csXyz angle(0, orig.angle.y, 0);
        u32 itemProcId = fopAcM_createItemFromTable(
            &current.pos, itemTbl, itemBitNo,
            fopAcM_GetHomeRoomNo(this), 0, &angle, 1
        );

        daItem_c* item = (daItem_c*)fopAcM_SearchByID(itemProcId);
        if(item) {
            if (isRupee(item->getItemNo()) || isRupeeInAllCreateTable(itemTbl)) {
                fopAcM_seStart(this, JA_SE_OBJ_LUPY_OUT, 0);
            } else {
                fopAcM_seStart(this, JA_SE_OBJ_ITEM_OUT, 0);
            }
        }

        mSpawnedItem = true;
    }

    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);

    return true;
}

/* 000006DC-0000076C       .text isRupeeInAllCreateTable__10daSwItem_cFi */
BOOL daSwItem_c::isRupeeInAllCreateTable(int param_1) {
    ItemTableList* itemTableList = dComIfGp_getItemTable();
    if (param_1 >= 0x20 && param_1 <= 0x3E && itemTableList) {
        u8* itemNo = itemTableList->mItemTables[param_1 - 0x20];
        for (int i = 0; i < 0x10; i++) {
            if (isRupee(*itemNo)) {
                return true;
            }
            itemNo++;
        }
    }
    return false;
}

/* 0000076C-00000774       .text _draw__10daSwItem_cFv */
bool daSwItem_c::_draw() {
    return true;
}

/* 00000774-00000794       .text daSwItem_Create__FPv */
static BOOL daSwItem_Create(void* i_this) {
    return static_cast<daSwItem_c*>(i_this)->_create();
}

/* 00000794-000007B8       .text daSwItem_Delete__FPv */
static BOOL daSwItem_Delete(void* i_this) {
    return static_cast<daSwItem_c*>(i_this)->_delete();
}

/* 000007B8-000007DC       .text daSwItem_Draw__FPv */
static BOOL daSwItem_Draw(void* i_this) {
    return static_cast<daSwItem_c*>(i_this)->_draw();
}

/* 000007DC-00000800       .text daSwItem_Execute__FPv */
static BOOL daSwItem_Execute(void* i_this) {
    return static_cast<daSwItem_c*>(i_this)->_execute();
}

/* 00000800-00000808       .text daSwItem_IsDelete__FPv */
static BOOL daSwItem_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daSwItemMethodTable = {
    (process_method_func)daSwItem_Create,
    (process_method_func)daSwItem_Delete,
    (process_method_func)daSwItem_Execute,
    (process_method_func)daSwItem_IsDelete,
    (process_method_func)daSwItem_Draw,
};

actor_process_profile_definition g_profile_SW_ITEM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_SW_ITEM,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daSwItem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x013A,
    /* Actor SubMtd */ &daSwItemMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
