/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "SSystem/SComponent/c_xyz.h"
#include "d/actor/d_a_obj_Itnak.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "dolphin/mtx/mtx.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_base.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_a_obj.h"
#include "res/Object/Itnak.h"

namespace daObjItnak {
namespace {

    struct Attr_c {
        /* 0x00 */ f32 field_0x00;  //  68.0f
        /* 0x04 */ f32 field_0x04;  // 230.0f
        /* 0x08 */ f32 field_0x08;  //  62.0f
        /* 0x0C */ f32 field_0x0C;  // 121.0f
        /* 0x10 */ f32 field_0x10;  //  41.0f
        /* 0x14 */ f32 field_0x14;  //  44.0f
        /* 0x18 */ f32 field_0x18;  //  84.0f
        /* 0x1C */ f32 field_0x1C;  //  47.0f
        /* 0x20 */ f32 field_0x20;  // 205.0f
        /* 0x24 */ f32 field_0x24;  // -88.0f
        /* 0x28 */ f32 field_0x28;  //  83.0f
        /* 0x2C */ f32 field_0x2C;  //  86.0f
    };

    struct Rodata_c {
        /* 0x00 */ Attr_c attr;
        /* 0x30 */ dCcD_SrcCyl M_cyl_src;
        /* 0x74 */ char m_arcname[6];
        /* 0x7A */ u16 pad_7A;
        // _create cull + ground
        /* 0x7C */ f32 cullMinX;
        /* 0x80 */ f32 cullMinY;
        /* 0x84 */ f32 cullMinZ;
        /* 0x88 */ f32 cullMaxX;
        /* 0x8C */ f32 cullMaxY;
        /* 0x90 */ f32 cullMaxZ;
        /* 0x94 */ f32 groundYOffset;
        // set_collision literals
        /* 0x98 */ f32 field_0x98;
        /* 0x9C */ f32 field_0x9C;
        /* 0xA0 */ f32 field_0xA0;
        /* 0xA4 */ f32 field_0xA4;
        /* 0xA8 */ f32 field_0xA8;
        /* 0xAC */ f32 field_0xAC;
        /* 0xB0 */ f32 field_0xB0;
        /* 0xB4 */ f32 field_0xB4;
        /* 0xB8 */ f32 field_0xB8;
        /* 0xBC */ f32 field_0xBC;
        /* 0xC0 */ f32 field_0xC0;
        /* 0xC4 */ f32 field_0xC4;
        // _draw shadow
        /* 0xC8 */ f32 shadowPosYOffset;
        /* 0xCC */ f32 shadowCasterSize;
        /* 0xD0 */ f32 shadowScaleXY;
        /* 0xD4 */ f32 shadowScaleZ;
    };
    
    static const Rodata_c L_attr = {
        /* L_attr */
        {
            68.0f, 230.0f, 62.0f, 121.0f,
            41.0f, 44.0f, 84.0f, 47.0f,
            205.0f, -88.0f, 83.0f, 86.0f,
        },
        /* M_cyl_src */
        {
            0, 0, 0, 0,
            ~(AT_TYPE_LIGHT | AT_TYPE_UNK400000 | AT_TYPE_WIND | AT_TYPE_UNK20000 | AT_TYPE_WATER),
            cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
            cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            0, 0, 0, 0, 0,
            0, 0, 0, 0,
            dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            0,
            {{
                {0.0f, 0.0f, 0.0f},
                100.0f,
                200.0f,
            }},
        },
      "Itnak",
        0,
        // cull box
        -120.0f, 0.0f, -100.0f,
         120.0f, 280.0f, 150.0f,
        100.0f,
        // set_collision pool (@4429+)
        68.0f, 230.0f, 41.0f, 44.0f, 84.0f, 62.0f,
        121.0f, -88.0f, 83.0f, 86.0f, 47.0f, 205.0f,
        // shadow
        30.0f, 800.0f, 60.0f, 1.0f,
    };

    inline const Attr_c& attr() { return L_attr.attr; }

    STATIC_ASSERT(sizeof(Attr_c) == 0x30);
    STATIC_ASSERT(sizeof(dCcD_SrcCyl) == 0x44);
    STATIC_ASSERT(offsetof(Rodata_c, M_cyl_src) == 0x30);
    STATIC_ASSERT(offsetof(Rodata_c, m_arcname) == 0x74);
    STATIC_ASSERT(offsetof(Rodata_c, pad_7A) == 0x7A);
    STATIC_ASSERT(offsetof(Rodata_c, cullMinX) == 0x7C);
    STATIC_ASSERT(offsetof(Rodata_c, groundYOffset) == 0x94);
    STATIC_ASSERT(offsetof(Rodata_c, shadowPosYOffset) == 0xC8);
    STATIC_ASSERT(sizeof(Rodata_c) == 0xD8);
}
}

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
BOOL daObjItnak::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjItnak::Act_c*>(i_this)->create_heap();
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::create_heap() {
    J3DModelData* L_modelData;
    bool ret;

    L_modelData = (J3DModelData *)dComIfG_getObjectRes(L_attr.m_arcname, dRes_INDEX_ITNAK_BDL_ITNAK_e);
    JUT_ASSERT(0x141, L_modelData != NULL);
    if (L_modelData != NULL) {
        mModel = mDoExt_J3DModel__create(L_modelData, 0, 0x11000002);
    }

    set_mtx();

    ret = FALSE;
    if (L_modelData != NULL) {
        if (mModel != NULL) {
            ret = TRUE;
        }
    }
    return ret;
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
    fopAcM_ct(this, Act_c);
    cPhs_State rt = dComIfG_resLoad(&mPhase, L_attr.m_arcname);
    mDrawMode = daObj::PrmAbstract<int>(this, PRM_VISIBLE_W, PRM_VISIBLE_S);

    if (rt == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(this, solidHeapCB, 0) != 0) {
            mVisible = mDrawMode;
            cullMtx = (MtxP)&mModel->getBaseTRMtx();
            fopAcM_setCullSizeBox(this,
                L_attr.cullMinX, L_attr.cullMinY, L_attr.cullMinZ,
                L_attr.cullMaxX, L_attr.cullMaxY, L_attr.cullMaxZ);            
            
            cXyz gndPos(current.pos);
            gndPos.y += 100.0f;
            mGndChk.SetPos(&gndPos);
            mGndChk.SetActorPid(fpcM_GetID(this));
            mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);

            mStts0.Init(0xFF, 0xFF, this);
            mCyl0.Set(L_attr.M_cyl_src);
            mCyl0.SetStts(&mStts0);
            mCyl0.SetTgVec((cXyz&)cXyz::Zero);
            mCyl0.OnTgNoHitMark();

            mStts1.Init(0xFF, 0xFF, this);
            mCyl1.Set(L_attr.M_cyl_src);
            mCyl1.SetStts(&mStts1);
            mCyl1.SetTgVec((cXyz&)cXyz::Zero);
            mCyl1.OnTgNoHitMark();
            
            mStts2.Init(0xFF, 0xFF, this);
            mCyl2.Set(L_attr.M_cyl_src);
            mCyl2.SetStts(&mStts2);
            mCyl2.SetTgVec((cXyz&)cXyz::Zero);
            mCyl2.OnTgNoHitMark();
        } else {
            rt = cPhs_ERROR_e;
        }
    }
    return rt;
}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, L_attr.m_arcname);
    return TRUE;
}

/* 00000D40-00000DEC       .text set_mtx__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mModel->setBaseTRMtx(mDoMtx_stack_c::now);
    PSMTXCopy(mDoMtx_stack_c::now, mMtx);
    mModel->calc();
}

/* 00000DEC-00000EB0       .text set_co_se__Q210daObjItnak5Act_cFP8dCcD_Cyl */
void daObjItnak::Act_c::set_co_se(dCcD_Cyl*) {
    /* Nonmatching */
}

/* 00000EB0-00000F94       .text manage_draw_flag__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::manage_draw_flag() {
    /* Nonmatching */
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    /* Nonmatching */
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
    float y;
    cXyz L_pPos;
    cXyz L_shadowPos;

    if (mVisible != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mModel, &tevStr);
        mDoExt_modelUpdateDL(mModel);
        float px = current.pos.x;
        float pz = current.pos.z;
        y = current.pos.y;
        float shadowY = L_attr.shadowPosYOffset + y;
        L_pPos.x = px;
        L_shadowPos.x = L_pPos.x;
        L_pPos.z = pz;
        L_shadowPos.z = pz;
        L_pPos.y = shadowY;
        L_shadowPos.y = L_pPos.y;
        mId = dComIfGd_setShadow(mId, 1, mModel, &L_pPos, L_attr.shadowCasterSize, L_attr.shadowScaleXY,
            y, mGroundY, mGndChk, &tevStr, 0, L_attr.shadowScaleZ, &dDlst_shadowControl_c::mSimpleTexObj);
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
