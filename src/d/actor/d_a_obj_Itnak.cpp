/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Itnak.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "res/Object/Itnak.h"

const daObjItnak::Act_c::Attr_c daObjItnak::Act_c::L_attr = {
    68.0f, 230.0f,        // cyl1_r, cyl1_h
    62.0f, 121.0f,        // cyl2_r, cyl2_h
    41.0f, 44.0f, 84.0f,  // cyl2_pos
    47.0f, 205.0f,        // cyl3_r, cyl3_h
    -88.0f, 83.0f, 86.0f  // cyl3_pos
};

namespace daObjItnak {
    static const dCcD_SrcCyl M_cyl_src = {
        {   // dCcD_SrcGObjInf
            {   // cCcD_SrcObj
                /* mFlags          0x00 */ 0,
                {   // cCcD_SrcObjHitInf
                    /* ObjAt.mType   0x04 */ { 0, 0, { 0 } },   // type=0, atp=0, SPrm=0
                    /* ObjTg.mType   0x10 */ { 0xFF1DFEFF, { 0x0000000F } },
                    /* ObjCo.mSPrm   0x18 */ { { 0x00000079 } },
                }
            },
            /* GAt 0x1C */ { 0, 0, 0, 0, { 0 } },     // Se=HM=Spl=Mtrl=0, SPrm=0
            /* GTg 0x24 */ { 0, 0, 0, 0, { 0x00000003 } }, // Se=HM=Spl=Mtrl=0, SPrm=3
            /* GCo 0x2C */ { { 0 } },
        },
  {   // cCcD_SrcCylAttr
      {   // cM3dGCylS mCyl
        { 0.0f, 0.0f, 0.0f },  // Vec mCenter
        100.0f,                 // mRadius
        200.0f,                 // mHeight
    }
},

    };
    const char daObjItnak::Act_c::M_arcname[] = "Itnak";

}

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
BOOL daObjItnak::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    u8 ret;
    ret = ((daObjItnak::Act_c*)i_this)->create_heap();
    return ret;
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
BOOL daObjItnak::Act_c::create_heap() {
    J3DModelData *mdl_data;
    BOOL ret;
    
    mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ITNAK_BDL_ITNAK_e);
    JUT_ASSERT(0x141, mdl_data != 0);
    if(mdl_data != 0){
        this->mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11000002);
    }
    this->set_mtx();
    ret = false;
    if ((mdl_data != (J3DModelData *)0x0) && (this->mpModel != (J3DModel *)0x0)) {
        ret = true;
    }
    return ret;
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
  fpc_ProcID actor_id;
  cPhs_State res_load_state;
  int is_visible;
  bool solid_heap;
  f32 ground_y;
  
  fopAcM_ct(this, Act_c);
  res_load_state = dComIfG_resLoad(&this->mPhase, M_arcname);
  is_visible = ::daObj::PrmAbstract(this, PRM_STATE_W, PRM_STATE_S);
  this->mInitVisible = is_visible;
  if (res_load_state == cPhs_COMPLEATE_e) {
    solid_heap = fopAcM_entrySolidHeap(this, solidHeapCB, 0);
    if (solid_heap) {
      this->mVisible = this->mInitVisible;
      this->cullMtx = this->mpModel->getBaseTRMtx();
      fopAcM_setCullSizeBox(this, -120.0, 0.0, -100.0, 120.0, 280.0, 150.0);
      cXyz pos(this->current.pos.x, this->current.pos.y + 100.0f, this->current.pos.z);
      this->mFloorPoly.SetPos(&pos);
      actor_id = fopAcM_GetID(this);
      this->mFloorPoly.SetActorPid(actor_id);
      ground_y = dComIfG_Bgsp()->GroundCross(&this->mFloorPoly);
      this->mGroundY = ground_y;
      this->mStts1.Init( 0xff, 0xff, this);
      this->mCyl1.Set(M_cyl_src);
      mCyl1.SetStts(&mStts1);
      mCyl1.SetTgVec((cXyz&)cXyz::Zero);
      this->mCyl1.OnTgNoHitMark();
      this->mStts2.Init( 0xff, 0xff, this);
      this->mCyl2.Set(M_cyl_src);
      mCyl2.SetStts(&mStts2);
      mCyl2.SetTgVec((cXyz&)cXyz::Zero);

      this->mCyl2.OnTgNoHitMark();
      this->mStts3.Init( 0xff, 0xff, this);
      this->mCyl3.Set(M_cyl_src);
      mCyl3.SetStts(&mStts3);
      mCyl3.SetTgVec((cXyz&)cXyz::Zero);

      this->mCyl3.OnTgNoHitMark();
    }
    else {
      res_load_state = cPhs_ERROR_e;
    }
  }
  return res_load_state;

}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    dComIfG_resDelete(&this->mPhase, M_arcname);
    return 1;
}

/* 00000D40-00000DEC       .text set_mtx__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_mtx() {
    Vec* pBaseScale = this->mpModel->getBaseScale();
    pBaseScale->x = this->scale.x;
    pBaseScale->y = this->scale.y;
    pBaseScale->z = this->scale.z;

    mDoMtx_stack_c::transS( this->current.pos.x, this->current.pos.y, this->current.pos.z);
    mDoMtx_stack_c::ZXYrotM( this->shape_angle.x, this->shape_angle.y, this->shape_angle.z);
    this->mpModel->setBaseTRMtx(mDoMtx_stack_c::now);
    PSMTXCopy(mDoMtx_stack_c::now, this->mMtx);

    this->mpModel->calc();
}

/* 00000DEC-00000EB0       .text set_co_se__Q210daObjItnak5Act_cFP8dCcD_Cyl */
BOOL daObjItnak::Act_c::set_co_se(dCcD_Cyl* i_collision) {
    if (i_collision->ChkTgHit() != 0) {
        daObj::HitSeStart(&this->current.pos, this->current.roomNo, i_collision, 0xd);
        dKy_Sound_set(this->current.pos, 4, fopAcM_GetID(this), 100);
        ::daObj::HitEff_hibana(this, i_collision);
        i_collision->ClrTgHit();
        return TRUE;
    }
    return FALSE;
}


/* 00000EB0-00000F94       .text manage_draw_flag__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::manage_draw_flag() {
      int switch_no;
      bool is_switch;

      if (this->mInitVisible == 1) {
          if (this->mVisible == 1) {
              switch_no = daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
              is_switch = dComIfGs_isSwitch(switch_no, this->home.roomNo);
              if (is_switch == 1) {
                  this->mVisible = 0;
              }
          }
      }
      else if (this->mInitVisible == 0) {
          if (this->mVisible == 0) {
              switch_no = daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
              is_switch = dComIfGs_isSwitch(switch_no, this->home.roomNo);
              if (is_switch == 1) {
                  this->mVisible = 1;
              }
          }
      }
      else {
          this->mVisible = 1;
      }
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    BOOL was_hit;
    cXyz cyl2_pos;
    cXyz cyl2_world_pos;
    cXyz cyl3_pos;
    cXyz cyl3_world_pos;

    if (this->mVisible == 1) {
        was_hit = this->set_co_se(&this->mCyl1);
        if (was_hit == 0) {
            this->mCyl1.SetR(L_attr.cyl1_r);
            this->mCyl1.SetH(L_attr.cyl1_h);
            this->mCyl1.SetC(this->current.pos);
            g_dComIfG_gameInfo.play.mCcS.Set((cCcD_Obj *)&this->mCyl1);
        }
        was_hit = this->set_co_se( &this->mCyl2);
        if (was_hit == 0) {
            cyl2_pos.x = L_attr.cyl2_pos_x;
            cyl2_pos.y = L_attr.cyl2_pos_y;
            cyl2_pos.z = L_attr.cyl2_pos_z;
            PSMTXMultVec(this->mMtx, &cyl2_pos, &cyl2_world_pos);
            this->mCyl2.SetR(L_attr.cyl2_r);
            this->mCyl2.SetH(L_attr.cyl2_h);
            this->mCyl2.SetC(cyl2_world_pos);
            g_dComIfG_gameInfo.play.mCcS.Set((cCcD_Obj *)&this->mCyl2);
        }
        was_hit = this->set_co_se( &this->mCyl3);
        if (was_hit == 0) {
            cyl3_pos.x = L_attr.cyl3_pos_x;
            cyl3_pos.y = L_attr.cyl3_pos_y;
            cyl3_pos.z = L_attr.cyl3_pos_z;
            PSMTXMultVec(this->mMtx, &cyl3_pos, &cyl3_world_pos);
            this->mCyl3.SetR(L_attr.cyl3_r);
            this->mCyl3.SetH(L_attr.cyl3_h);
            this->mCyl3.SetC(cyl3_world_pos);
            g_dComIfG_gameInfo.play.mCcS.Set( (cCcD_Obj *)&this->mCyl3);
        }
        fopAcM_rollPlayerCrash(this, L_attr.cyl1_r, 0xd);
    }
}

/* 00001118-00001158       .text _execute__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_execute() {
    this->set_mtx();
    this->manage_draw_flag();
    this->set_collision();
    return true;
}

/* 00001158-0000123C       .text _draw__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_draw() {
    u32 shadow_id;

    if (this->mVisible != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &this->current.pos, &this->tevStr);
        g_env_light.setLightTevColorType(this->mpModel, &this->tevStr);
        mDoExt_modelUpdateDL(this->mpModel);
        cXyz scale = cXyz(this->current.pos.x, this->current.pos.y + 30.0f, this->current.pos.z);
        shadow_id = dComIfGd_setShadow(this->mShadowId, 1, this->mpModel, &scale, 800.0, 60.0, this->current.pos.y, this->mGroundY,
                            this->mFloorPoly, &this->tevStr, 0, 1.0,
                            &dDlst_shadowControl_c::mSimpleTexObj);
        this->mShadowId = shadow_id;
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
