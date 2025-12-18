/**
 * d_a_obj_aygr.cpp
 * Object - Lookout Platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_aygr.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

Mtx daObjAygr::Act_c::M_tmp_mtx;
const char daObjAygr::Act_c::M_arcname[] = "Aygr";

/* 00000078-000002A4       .text CreateHeap__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::CreateHeap() {
    /* Nonmatching */

    BOOL temp;
    J3DModelData* model_data_yagura = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 0x4);
    JUT_ASSERT(0x50, model_data_yagura != NULL);

    mModel1 = mDoExt_J3DModel__create(model_data_yagura, 0, 0x11020203);

    if (!mModel1) {
        return FALSE;
    }

    u8 prm = daObjAygr::Act_c::prm_get_mdl();
    if (prm != 0) {
        J3DModelData* model_data_hashigo = (J3DModelData*) dComIfG_getObjectRes(M_arcname, 5);
        JUT_ASSERT(0x59, model_data_hashigo != NULL);

        mModel2 = mDoExt_J3DModel__create(model_data_hashigo, 0,0x11020203);

        if (!mModel2) {
            return FALSE;
        }

        temp = TRUE;
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        PSMTXCopy(mDoMtx_stack_c::now, m2dc);

        mpBgW = new dBgW();

        if (mpBgW == NULL || mpBgW->Set((cBgD_t*) dComIfG_getObjectRes(M_arcname, 0x9), cBgW::MOVE_BG_e, &m2dc) != 0) {
            temp = FALSE;
        }

        if (temp != TRUE) {
            return FALSE;
        }
        m30C = TRUE;
    } else {
        mModel2 = NULL;
        mpBgW = NULL;
        m30C = false;
    }

    return TRUE;

}

/* 000002A4-00000310       .text Create__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Create() {

    fopAcM_SetMtx(this, mModel1->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeBox(this, -500.0f, -100.0f, -500.0f, 500.0f, 4000.0f, 500.0f);
    return TRUE;
}

/* 00000310-000004D4       .text Mthd_Create__Q29daObjAygr5Act_cFv */
cPhs_State daObjAygr::Act_c::Mthd_Create() {
    
    dBgS_MoveBgActor* actor = static_cast<dBgS_MoveBgActor*>(this);
    fopAcM_SetupActor(this, Act_c);
    m30C = 0;
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);   

    if (phase_state == cPhs_COMPLEATE_e)
    {
        phase_state = MoveBGCreate(M_arcname, 8, NULL, 0x85f0);
        if (actor->mpBgW)
        {
            if (actor->mpBgW->ChkUsed())
            {
                actor->mpBgW->Move();
                actor->mpBgW->SetLock();
            }
        }
        if (prm_get_mdl())
        {
            dComIfG_Bgsp()->Regist(mpBgW, this);
            if (mpBgW)
            {
                if (mpBgW->ChkUsed())
                {
                    mpBgW->Move();
                    mpBgW->SetLock();
                }
            }
        }

        JUT_ASSERT(0xb7, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }

    return phase_state;
    
}

/* 000004D4-000004DC       .text Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Delete() {
    return TRUE;
}

/* 000004DC-0000054C       .text Mthd_Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Mthd_Delete() {
    
    if (m30C)
        dComIfG_Bgsp()->Release(this->mpBgW);
    
    u32 result = MoveBGDelete();
    dComIfG_resDelete(&mPhase, M_arcname);
    
    return result;
}

/* 0000054C-000005F8       .text set_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::set_mtx() {

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get()); 
    
    if (prm_get_mdl())
        mModel2->setBaseTRMtx(mDoMtx_stack_c::get());
    
    MTXCopy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 000005F8-00000674       .text init_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::init_mtx() {
    
    mModel1->setBaseScale(scale);
    if (prm_get_mdl())
        mModel2->setBaseScale(scale);
    set_mtx();
}

/* 00000674-000006B0       .text Execute__Q29daObjAygr5Act_cFPPA3_A4_f */
BOOL daObjAygr::Act_c::Execute(Mtx** pMtx) {
   set_mtx();
  *pMtx = &M_tmp_mtx;
  return TRUE;
}

/* 000006B0-0000079C       .text Draw__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Draw() {

      g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);      
      g_env_light.setLightTevColorType(mModel1, &tevStr);

      if (prm_get_mdl()) 
        g_env_light.setLightTevColorType(mModel2, &tevStr);
  
      dComIfGd_setListBG();
      mDoExt_modelUpdateDL(mModel1);
      
      if (prm_get_mdl()) 
        mDoExt_modelUpdateDL(mModel2);
      
      dComIfGd_setList();

      return TRUE;
}

namespace daObjAygr {
namespace {
/* 0000079C-000007BC       .text Mthd_Create__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Create();
}

/* 000007BC-000007DC       .text Mthd_Delete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Delete();
}

/* 000007DC-000007FC       .text Mthd_Execute__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->MoveBGExecute();
}

/* 000007FC-00000828       .text Mthd_Draw__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Draw();
}

/* 00000828-00000854       .text Mthd_IsDelete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Aygr = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAygr

actor_process_profile_definition g_profile_Obj_Aygr = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Aygr,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAygr::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Aygr,
    /* Actor SubMtd */ &daObjAygr::Mthd_Aygr,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
