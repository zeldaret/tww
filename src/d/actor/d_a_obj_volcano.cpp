/**
 * d_a_obj_volcano.cpp
 * Object - Fire Mountain Exterior - Lava
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_volcano.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_ykzyg.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl cyl_check_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ICE_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 300.0f,
        /* Height */ 3000.0f,
    }},
};

const char daObjVolcano::Act_c::M_arcname[] = "Ykzyg";


/* 00000078-000003CC       .text StartFire__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::StartFire() {
    /* Nonmatching */
    
    this->field_0x4E8 = 0;
    this->field_0x4F4 = 1;
    J3DFrameCtrl* fc = field_0x328.getFrameCtrl(); 
    fc->setFrame(0.0f); 
    fc->setRate(1.0f);
    if (mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Regist(mpBgW, this);
        }
    }
    this->field_0x2C8[0] = dComIfGp_particle_set(
                                            0x805a, &this->field_0x4B8[1],
                                            &this->current.angle,
                                            &this->field_0x4AC, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[1] = dComIfGp_particle_set(
                                            0x805b, &this->field_0x4B8[2],
                                            &this->current.angle,
                                            &this->field_0x4AC, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[2] = dComIfGp_particle_set(
                                            0x805c, &this->field_0x4B8[3],
                                            &this->current.angle,
                                            &this->field_0x4AC, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[3] = dComIfGp_particle_set(
                                            0x8194, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[4] = dComIfGp_particle_set(
                                            0x8195, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[5] = dComIfGp_particle_set(
                                            0x8196, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[6] = dComIfGp_particle_set(
                                            0x8197, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[7] = dComIfGp_particle_set(
                                            0x8198, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[8] = dComIfGp_particle_set(
                                            0x8199, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
    this->field_0x2C8[9] = dComIfGp_particle_set(
                                            0x819a, &this->current.pos,
                                            &this->current.angle,
                                            NULL, 0xff,
                                            NULL, -1,
                                            NULL, NULL,
                                            NULL);
}

/* 000003CC-00000470       .text StopFire__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::StopFire() {
    /* Nonmatching */
    if (mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (this->field_0x2C8[i] != NULL) {
            this->field_0x2C8[i]->setMaxFrame(-1);
            this->field_0x2C8[i]->setStatus(JPAPtclStts_FirstFrame);
        }
    }
}

/* 00000470-00000758       .text CreateHeap__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData * model_data = (J3DModelData *)dComIfG_getObjectRes(M_arcname, YKZYG_BDL_QKZYG);
    JUT_ASSERT(0xbf, model_data != NULL);

    field_0x2F8 = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000222);
    J3DAnmTextureSRTKey * btk = (J3DAnmTextureSRTKey *)dComIfG_getObjectRes(M_arcname, YKZYG_BTK_QKZYG);
    JUT_ASSERT(0xca, btk != NULL);

    s32 btkRet = field_0x2FC.init(model_data, btk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE);
    J3DModelData * model_data_fire = (J3DModelData *)dComIfG_getObjectRes(M_arcname, YKZYG_BDL_YMNKZ00);
    JUT_ASSERT(0xe1, model_data_fire != NULL);

    field_0x310 = mDoExt_J3DModel__create(model_data_fire, 0x80000, 0x11000222);
    J3DAnmTextureSRTKey * btk_f = (J3DAnmTextureSRTKey *)dComIfG_getObjectRes(M_arcname, YKZYG_BTK_YMNKZ00);
    JUT_ASSERT(0xec, btk_f != NULL);
    
    s32 btkFRet = field_0x314.init(model_data_fire, btk_f, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE);
    
    J3DAnmTevRegKey * brk_f = (J3DAnmTevRegKey *)dComIfG_getObjectRes(M_arcname, YKZYG_BRK_YMNKZ00);
    JUT_ASSERT(0xf3, brk_f != NULL);
    s32 brkRet = field_0x328.init(model_data_fire, brk_f, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE);

    field_0x4F4 = 1;
    return field_0x2F8 != NULL && field_0x310 != NULL && btkRet != 0  && btkFRet != 0 && brkRet != 0;
}

/* 00000758-000009C8       .text Create__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Create() {
    /* Nonmatching */
    cullMtx = field_0x2F8->getBaseTRMtx();
    init_mtx();
    fopAcM_setCullSizeBox
                (this, -1600.0f,-500.0f,-1800.0f,1700.0f,2500.0f,1900.0f);
    field_0x340.Init(0xff, 0xff, this);
    field_0x37C.Set(cyl_check_src);
    field_0x4B8[0] = current.pos;
    field_0x37C.SetC(field_0x4B8[0]);
    field_0x4EC = field_0x37C.GetH();
    field_0x4F0 = field_0x37C.GetR();
    field_0x37C.SetStts(&field_0x340);

    field_0x4B8[1] = current.pos;
    field_0x4B8[1].y += 5000.0f;
    field_0x4B8[2] = current.pos;
    field_0x4B8[2].y += 5000.0f;
    field_0x4B8[3] = current.pos;
    field_0x4B8[3].y += 2400.0f;
    field_0x4AC.x = 2.0f;
    field_0x4AC.y = 2.0f;   
    field_0x4AC.z = 2.0f;

    for (int i = 0; i < 10; i++) {
        this->field_0x2C8[i] = NULL;
    }
    int switchIndex = prm_get_swSave();
    if (fopAcM_isSwitch(this, switchIndex)) {
        field_0x4B8[0].y = home.pos.y - 2000.0f;
        StopFire();
        field_0x4F8 = 0.0f;
        if (dComIfGs_getStartPoint() == 2 && current.roomNo == dComIfGs_getRestartRoomNo()) {
            field_0x500 = 6;
        } else {
            field_0x500 = 3;
        }
    } else {
        field_0x4B8[0].y = home.pos.y + 2000.0f;
        StartFire();
        field_0x4F8 = 1.0f;
        field_0x500 = 0;
    }
    field_0x4FC = dComIfGp_evmng_getEventIdx("FREEZE_VOLCANO");
    field_0x4FE = dComIfGp_evmng_getEventIdx("FIRE_VOLCANO");
    return TRUE;
}

/* 000009C8-00000BA0       .text Mthd_Create__Q212daObjVolcano5Act_cFv */
cPhs_State daObjVolcano::Act_c::Mthd_Create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daObjVolcano::Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&field_0x2F0, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, 0x11, NULL, 0xaed0);
        JUT_ASSERT(0x143, (phase_state == cPhs_ERROR_e) || (phase_state == cPhs_COMPLEATE_e));
    }
    return phase_state;
}

/* 00000E58-00000E60       .text Delete__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Delete() {
    return TRUE;
}

/* 00000E60-00000EC0       .text Mthd_Delete__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Mthd_Delete() {
    /* Nonmatching */
    u32 result = MoveBGDelete();
    mDoAud_seDeleteObject(field_0x4B8);
    dComIfG_resDelete(&field_0x2F0, M_arcname);
    return result;
}

/* 00000EC0-00000F84       .text set_mtx__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000F84-00000FDC       .text init_mtx__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000FDC-0000103C       .text daObjVolcano_fire_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_demo_wait() {
    /* Nonmatching */
}

/* 0000103C-00001160       .text daObjVolcano_fire_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_demo_main() {
    /* Nonmatching */
}

/* 00001160-00001284       .text daObjVolcano_fire_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_main() {
    /* Nonmatching */
}

/* 00001284-000013E4       .text daObjVolcano_freeze_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_demo_wait() {
    /* Nonmatching */
}

/* 000013E4-00001558       .text daObjVolcano_freeze_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_demo_main() {
    /* Nonmatching */
}

/* 00001558-000015E8       .text daObjVolcano_freeze_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_main() {
    /* Nonmatching */
}

/* 000015E8-0000164C       .text daObjVolcano_fail_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fail_demo_wait() {
    /* Nonmatching */
}

/* 0000164C-00001740       .text daObjVolcano_fail_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fail_demo_main() {
    /* Nonmatching */
}

/* 00001740-0000199C       .text Execute__Q212daObjVolcano5Act_cFPPA3_A4_f */
BOOL daObjVolcano::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 0000199C-00001A2C       .text set_material__Q212daObjVolcano5Act_cFP11J3DMaterialUc */
void daObjVolcano::Act_c::set_material(J3DMaterial*, unsigned char) {
    /* Nonmatching */
}

/* 00001A2C-00001B8C       .text Draw__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjVolcano {
namespace {
/* 00001B8C-00001BAC       .text Mthd_Create__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Mthd_Create();
}

/* 00001BAC-00001BCC       .text Mthd_Delete__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Mthd_Delete();
}

/* 00001BCC-00001BEC       .text Mthd_Execute__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->MoveBGExecute();
}

/* 00001BEC-00001C18       .text Mthd_Draw__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Draw();
}

/* 00001C18-00001C44       .text Mthd_IsDelete__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVolcano

actor_process_profile_definition g_profile_Obj_Volcano = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Volcano,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVolcano::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Volcano,
    /* Actor SubMtd */ &daObjVolcano::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
