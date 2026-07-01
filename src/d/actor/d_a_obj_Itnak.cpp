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
    BOOL bVar3;
    
    mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ITNAK_BDL_ITNAK_e);
    JUT_ASSERT(0x141, mdl_data != 0);
    if(mdl_data != 0){
        this->mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11000002);
    }
    this->set_mtx();
    bVar3 = false;
    if ((mdl_data != (J3DModelData *)0x0) && (this->mpModel != (J3DModel *)0x0)) {
        bVar3 = true;
    }
    return bVar3;
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
  fpc_ProcID fVar2;
  cPhs_State PVar3;
  int uVar4;
  bool bVar4;
  f32 fVar5;
  
  fopAcM_ct(this, Act_c);
  PVar3 = dComIfG_resLoad(&this->mPhase, M_arcname);
  uVar4 = ::daObj::PrmAbstract(this, 0x8, 0);
  this->mInitParam = uVar4;
  if (PVar3 == cPhs_COMPLEATE_e) {
    bVar4 = fopAcM_entrySolidHeap(this, solidHeapCB, 0);
    if (bVar4) {
      this->mParam = this->mInitParam;
      this->cullMtx = this->mpModel->getBaseTRMtx();
      fopAcM_setCullSizeBox(this, -120.0, 0.0, -100.0, 120.0, 280.0, 150.0);
      cXyz pos(this->current.pos.x, this->current.pos.y + 100.0f, this->current.pos.z);
      this->mFloorPoly.SetPos(&pos);
      fVar2 = fopAcM_GetID(this);
      this->mFloorPoly.SetActorPid(fVar2);
      fVar5 = dComIfG_Bgsp()->GroundCross(&this->mFloorPoly);
      this->mGroundY = fVar5;
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
      PVar3 = cPhs_ERROR_e;
    }
  }
  return PVar3;

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
      int iVar1;
      bool bVar2;

      if (this->mInitParam == 1) {
          if (this->mParam == 1) {
              iVar1 = daObj::PrmAbstract(this, 8, 8);
              bVar2 = dComIfGs_isSwitch(iVar1, this->home.roomNo);
              if (bVar2 == 1) {
                  this->mParam = 0;
              }
          }
      }
      else if (this->mInitParam == 0) {
          if (this->mParam == 0) {
              iVar1 = daObj::PrmAbstract(this, 8, 8);
              bVar2 = dComIfGs_isSwitch(iVar1, this->home.roomNo);
              if (bVar2 == 1) {
                  this->mParam = 1;
              }
          }
      }
      else {
          this->mParam = 1;
      }
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    BOOL iVar1;
    cXyz local_14;
    cXyz cStack_20;
    cXyz local_2c;
    cXyz cStack_38;

    if (this->mParam == 1) {
        iVar1 = this->set_co_se(&this->mCyl1);
        if (iVar1 == 0) {
            this->mCyl1.SetR(68.0);
            this->mCyl1.SetH(230.0);
            this->mCyl1.SetC(this->current.pos);
            g_dComIfG_gameInfo.play.mCcS.Set((cCcD_Obj *)&this->mCyl1);
        }
        iVar1 = this->set_co_se( &this->mCyl2);
        if (iVar1 == 0) {
            local_14.x = 41.0;
            local_14.y = 44.0;
            local_14.z = 84.0;
            PSMTXMultVec(this->mMtx, &local_14, &cStack_20);
            this->mCyl2.SetR(62.0);
            this->mCyl2.SetH(121.0);
            this->mCyl2.SetC(cStack_20);
            g_dComIfG_gameInfo.play.mCcS.Set((cCcD_Obj *)&this->mCyl2);
        }
        iVar1 = this->set_co_se( &this->mCyl3);
        if (iVar1 == 0) {
            local_2c.x = -88.0;
            local_2c.y = 83.0;
            local_2c.z = 86.0;
            PSMTXMultVec(this->mMtx, &local_2c, &cStack_38);
            this->mCyl3.SetR(47.0);
            this->mCyl3.SetH(205.0);
            this->mCyl3.SetC(cStack_38);
            g_dComIfG_gameInfo.play.mCcS.Set( (cCcD_Obj *)&this->mCyl3);
        }
        fopAcM_rollPlayerCrash(this, 68.0, 0xd);
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

    if (this->mParam != 0) {
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
