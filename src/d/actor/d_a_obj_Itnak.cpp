/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Itnak.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Itnak.h"

namespace daObjItnak {

namespace {
    struct Attr_c {
        /* 0x00 */ f32 mR0;
        /* 0x04 */ f32 mH0;
        /* 0x08 */ f32 mR1;
        /* 0x0C */ f32 mH1;
        /* 0x10 */ Vec mOffset1;
        /* 0x1C */ f32 mR2;
        /* 0x20 */ f32 mH2;
        /* 0x24 */ Vec mOffset2;
    };  // Size: 0x30

    const Attr_c L_attr = {
        68.0f, 230.0f, 62.0f, 121.0f, {41.0f, 44.0f, 84.0f}, 47.0f, 205.0f, {-88.0f, 83.0f, 86.0f},
    };
} // namespace

const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};

}; // namespace daObjItnak


const char daObjItnak::Act_c::M_arcname[] = "Itnak";

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
BOOL daObjItnak::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::create_heap() {
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ITNAK_BDL_ITNAK_e);
    JUT_ASSERT(321, mdl_data != NULL);

    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11000002);
    }
    set_mtx();
    return mdl_data != NULL && mpModel != NULL;
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
    fopAcM_ct(this, Act_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    mArg0 = param_get_arg0();

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            mDrawFlag = mArg0;
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -120.0f, 0.0f, -100.0f, 120.0f, 280.0f, 150.0f);

            cXyz pos(current.pos.x, 100.0f + current.pos.y, current.pos.z);
            mGndChk.SetPos(&pos);
            mGndChk.SetActorPid(fopAcM_GetID(this));
            mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);

            mStts0.Init(0xff, 0xff, this);
            mCyl0.Set(M_cyl_src);
            mCyl0.SetStts(&mStts0);
            mCyl0.SetTgVec((cXyz&)cXyz::Zero);
            mCyl0.OnTgNoHitMark();

            mStts1.Init(0xff, 0xff, this);
            mCyl1.Set(M_cyl_src);
            mCyl1.SetStts(&mStts1);
            mCyl1.SetTgVec((cXyz&)cXyz::Zero);
            mCyl1.OnTgNoHitMark();

            mStts2.Init(0xff, 0xff, this);
            mCyl2.Set(M_cyl_src);
            mCyl2.SetStts(&mStts2);
            mCyl2.SetTgVec((cXyz&)cXyz::Zero);
            mCyl2.OnTgNoHitMark();
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00000D40-00000DEC       .text set_mtx__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
    mpModel->calc();
}

/* 00000DEC-00000EB0       .text set_co_se__Q210daObjItnak5Act_cFP8dCcD_Cyl */
BOOL daObjItnak::Act_c::set_co_se(dCcD_Cyl* i_cyl) {
    if (i_cyl->ChkTgHit()) {
        daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), i_cyl, 0xD);
        dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
        daObj::HitEff_hibana(this, i_cyl);
        i_cyl->ClrTgHit();
        return TRUE;
    }
    return FALSE;
}

/* 00000EB0-00000F94       .text manage_draw_flag__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::manage_draw_flag() {
    if (mArg0 == 1) {
        if (mDrawFlag == 1 && is_switch() == true) {
            mDrawFlag = 0;
        }
    } else if (mArg0 == 0) {
        if (mDrawFlag == 0 && is_switch() == true) {
            mDrawFlag = 1;
        }
    } else {
        mDrawFlag = 1;
    }
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    if (mDrawFlag == 1) {
        if (!set_co_se(&mCyl0)) {
            mCyl0.SetR(68.0f);
            mCyl0.SetH(230.0f);
            mCyl0.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl0);
        }

        if (!set_co_se(&mCyl1)) {
            cXyz offset(41.0f, 44.0f, 84.0f);
            cXyz pos;
            cMtx_multVec(mMtx, &offset, &pos);
            mCyl1.SetR(62.0f);
            mCyl1.SetH(121.0f);
            mCyl1.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl1);
        }

        if (!set_co_se(&mCyl2)) {
            cXyz offset(-88.0f, 83.0f, 86.0f);
            cXyz pos;
            cMtx_multVec(mMtx, &offset, &pos);
            mCyl2.SetR(47.0f);
            mCyl2.SetH(205.0f);
            mCyl2.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl2);
        }

        fopAcM_rollPlayerCrash(this, 68.0f, 0xD);
    }
}

/* 00001118-00001158       .text _execute__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_execute() {
    set_mtx();
    manage_draw_flag();
    set_collision();
    return true;
}

/* 00001158-0000123C       .text _draw__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_draw() {
    if (mDrawFlag != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        mDoExt_modelUpdateDL(mpModel);

        cXyz pos = cXyz(current.pos.x, 30.0f + current.pos.y, current.pos.z);
        mShadowId = dComIfGd_setShadow(mShadowId, 1, mpModel, &pos, 800.0f, 60.0f, current.pos.y, mGroundY, mGndChk,
                                       &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    return true;
}

namespace daObjItnak {
namespace {
/* 0000123C-0000125C       .text Mthd_Create__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_create();
}

/* 0000125C-00001280       .text Mthd_Delete__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_delete();
}

/* 00001280-000012A4       .text Mthd_Execute__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_execute();
}

/* 000012A4-000012C8       .text Mthd_Draw__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_draw();
}

/* 000012C8-000012D0       .text Mthd_IsDelete__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjItnak

actor_process_profile_definition g_profile_Obj_Itnak = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Itnak_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjItnak::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Itnak_e,
    /* Actor SubMtd */ &daObjItnak::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
