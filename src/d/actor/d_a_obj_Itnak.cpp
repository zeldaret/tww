/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Itnak.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "res/Object/Itnak.h"

namespace daObjItnak {

    const char Act_c::M_arcname[] = "Itnak";

    namespace {
        struct Attr_c {
            /* 0x00 */ u8 _pad[0xC8 - 0x00];
            /* 0xC8 */ f32 shadowPosYOffset;
            /* 0xCC */ f32 shadowCasterSize;
            /* 0xD0 */ f32 shadowScaleXY;
            /* 0xD4 */ f32 shadowScaleZ;
        };
        const Attr_c L_attr = {
            /* 0x00 */ {0},
            /* field_0xC8 */ 30.0f,
            /* field_0xCC */ 800.0f,
            /* field_0xD0 */ 60.0f,
            /* field_0xD4 */ 1.0f
        };

        inline static const Attr_c& attr() { return L_attr; }

        STATIC_ASSERT(sizeof(Attr_c) == 0xD8);
    }
}

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
BOOL daObjItnak::Act_c::solidHeapCB(fopAc_ac_c*) {
    return create_heap() & 0xFF;
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
BOOL daObjItnak::Act_c::create_heap() {
    J3DModelData* L_modelData;
    BOOL ret;

    L_modelData = (J3DModelData *)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ITNAK_BDL_ITNAK_e);
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
    /* Nonmatching */
}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000D40-00000DEC       .text set_mtx__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_mtx() {
    /* Nonmatching */
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
    const Attr_c& L_attr = attr();
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
            y, mGroundY, mFloorPoly, &tevStr, 0, L_attr.shadowScaleZ, &dDlst_shadowControl_c::mSimpleTexObj);
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
