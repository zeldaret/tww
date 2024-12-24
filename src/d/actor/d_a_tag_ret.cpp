//
// Generated by dtk
// Translation Unit: d_a_tag_ret.cpp
//

#include "d/actor/d_a_tag_ret.h"
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player_main.h"

static dCcD_SrcCyl cyl_check_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 1000.0f,
        /* Height */ 100.0f,
    },
};

namespace daTagRet {
    /* 00000078-000001D4       .text _create__Q28daTagRet5Act_cFv */
    s32 Act_c::_create() {
        fopAcM_SetupActor(this, daTagRet::Act_c);

        if (checkItemGet(dItem_PEARL_FARORE_e, TRUE)) {
            return cPhs_STOP_e;
        }

        mStts.Init(0xFF, 0xFF, this);
        mCyl.Set(cyl_check_src);
        mCyl.SetR(1000.0f*scale.x);
        mCyl.SetH(100.0f*scale.y);
        mCyl.SetStts(&mStts);

        return cPhs_COMPLEATE_e;
    }

    /* 0000038C-00000394       .text _delete__Q28daTagRet5Act_cFv */
    bool Act_c::_delete() {
        return true;
    }

    /* 00000394-00000398       .text set_mtx__Q28daTagRet5Act_cFv */
    void Act_c::set_mtx() {
        return;
    }

    /* 00000398-00000460       .text _execute__Q28daTagRet5Act_cFv */
    bool Act_c::_execute() {
        mCyl.SetC(current.pos);
        mCyl.SetR(1000.0f*scale.x);
        mCyl.SetH(100.0f*scale.y);
        dComIfG_Ccsp()->Set(&mCyl);

        if (mCyl.ChkCoHit()) {
            u32 linkId = prm_get_linkID();
            daPy_getPlayerLinkActorClass()->onDekuSpReturnFlg(linkId);
        }

        set_mtx();

        return true;
    }

    /* 00000460-00000468       .text _draw__Q28daTagRet5Act_cFv */
    bool Act_c::_draw() {
        return true;
    }

    namespace {
        /* 00000468-00000488       .text Mthd_Create__Q28daTagRet25@unnamed@d_a_tag_ret_cpp@FPv */
        s32 Mthd_Create(void* i_this) {
            return ((Act_c*)i_this)->_create();
        }

        /* 00000488-000004AC       .text Mthd_Delete__Q28daTagRet25@unnamed@d_a_tag_ret_cpp@FPv */
        BOOL Mthd_Delete(void* i_this) {
            return ((Act_c*)i_this)->_delete();
        }

        /* 000004AC-000004D0       .text Mthd_Execute__Q28daTagRet25@unnamed@d_a_tag_ret_cpp@FPv */
        BOOL Mthd_Execute(void* i_this) {
            return ((Act_c*)i_this)->_execute();
        }

        /* 000004D0-000004F4       .text Mthd_Draw__Q28daTagRet25@unnamed@d_a_tag_ret_cpp@FPv */
        BOOL Mthd_Draw(void* i_this) {
            return ((Act_c*)i_this)->_draw();
        }

        /* 000004F4-000004FC       .text Mthd_IsDelete__Q28daTagRet25@unnamed@d_a_tag_ret_cpp@FPv */
        BOOL Mthd_IsDelete(void* i_this) {
            return TRUE;
        }

        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    };
};

actor_process_profile_definition g_profile_Tag_Ret = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Tag_Ret,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTagRet::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x005F,
    /* Actor SubMtd */ &daTagRet::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
