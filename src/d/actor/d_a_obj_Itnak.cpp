/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Itnak.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_a_obj.h"
#include "d/d_kankyo.h"
#include "d/res/res_itnak.h"

namespace daObjItnak {
namespace {
static const Act_c::Attr_c L_attr = {
    68.0f, 230.0f, 62.0f, 121.0f, 41.0f, 44.0f,
    84.0f, 47.0f, 205.0f, -88.0f, 83.0f, 86.0f,
};
static inline const Act_c::Attr_c& attr() {
    return L_attr;
}
} // namespace
} // namespace daObjItnak

namespace daObjItnak {
const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};
} // namespace daObjItnak

const char daObjItnak::Act_c::M_arcname[] = "Itnak";

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
BOOL daObjItnak::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::create_heap() {
    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, ITNAK_BDL_ITNAK));
    JUT_ASSERT(321, mdl_data != NULL);

    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11000002);
    }

    set_mtx();
    return mdl_data != NULL && mpModel != NULL;
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
    fopAcM_ct_Retail(this, Act_c);

    cPhs_State phase = dComIfG_resLoad(&mPhase, M_arcname);
    mType = daObj::PrmAbstract(this, 8, 0);

    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            mDrawFlag = mType;

            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -120.0f, 0.0f, -100.0f, 120.0f, 280.0f, 150.0f);

            cXyz gnd_pos(current.pos.x, 100.0f + current.pos.y, current.pos.z);
            mGndChk.SetPos(&gnd_pos);
            mGndChk.SetActorPid(fopAcM_GetID(this));
            mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);

            mStts1.Init(0xFF, 0xFF, this);
            mCyl1.Set(M_cyl_src);
            mCyl1.SetStts(&mStts1);
            mCyl1.SetC(cXyz::Zero);
            mCyl1.OnTgNoHitMark();

            mStts2.Init(0xFF, 0xFF, this);
            mCyl2.Set(M_cyl_src);
            mCyl2.SetStts(&mStts2);
            mCyl2.SetC(cXyz::Zero);
            mCyl2.OnTgNoHitMark();

            mStts3.Init(0xFF, 0xFF, this);
            mCyl3.Set(M_cyl_src);
            mCyl3.SetStts(&mStts3);
            mCyl3.SetC(cXyz::Zero);
            mCyl3.OnTgNoHitMark();
        } else {
            phase = cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    dComIfG_resDelete(&mPhase, M_arcname);
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
int daObjItnak::Act_c::set_co_se(dCcD_Cyl* i_cyl) {
    if (i_cyl->ChkTgHit()) {
        daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), i_cyl, 0xD);
        dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 0x64);
        daObj::HitEff_hibana(this, i_cyl);
        i_cyl->ClrTgHit();
        return 1;
    }
    return 0;
}

/* 00000EB0-00000F94       .text manage_draw_flag__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::manage_draw_flag() {
    if (mType == 1) {
        if (mDrawFlag == 1) {
            if (is_switch() == 1) {
                mDrawFlag = 0;
            }
        }
    } else if (mType == 0) {
        if (mDrawFlag == 0) {
            if (is_switch() == 1) {
                mDrawFlag = 1;
            }
        }
    } else {
        mDrawFlag = 1;
    }
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    if (mDrawFlag == 1) {
        if (set_co_se(&mCyl1) == 0) {
            mCyl1.SetR(68.0f);
            mCyl1.SetH(230.0f);
            mCyl1.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl1);
        }
        if (set_co_se(&mCyl2) == 0) {
            cXyz src(41.0f, 44.0f, 84.0f);
            cXyz pos;
            cMtx_multVec(mMtx, &src, &pos);
            mCyl2.SetR(62.0f);
            mCyl2.SetH(121.0f);
            mCyl2.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl2);
        }
        if (set_co_se(&mCyl3) == 0) {
            cXyz src(-88.0f, 83.0f, 86.0f);
            cXyz pos;
            cMtx_multVec(mMtx, &src, &pos);
            mCyl3.SetR(47.0f);
            mCyl3.SetH(205.0f);
            mCyl3.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl3);
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

        cXyz pos(current.pos.x, 30.0f + current.pos.y, current.pos.z);
        mShadowId = dComIfGd_setShadow(mShadowId, 1, mpModel, &pos, 800.0f, 60.0f,
                                       current.pos.y, mGroundY, mGndChk, &tevStr, 0, 1.0f);
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
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Itnak,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjItnak::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Itnak,
    /* Actor SubMtd */ &daObjItnak::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
