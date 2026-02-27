/**
 * d_a_obj_auzu.cpp
 * Object - Big Octo/Jabun's cave whirlpool
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_auzu.h"
#include "d/actor/d_a_kytag01.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_auzu.h"

namespace daObjAuzu {
namespace {
f32 L_radius = 2500.0f;
};

const char Act_c::M_arcname[] = "Auzu";
const Attr_c Act_c::M_attr[2] = {
    { 1.5f, 1.5f, 1.3f, 0.5f },
    { 2.0f, 2.0f, 2.0f, 1.0f }
};
};

/* 00000078-0000009C       .text solidHeapCB__Q29daObjAuzu5Act_cFP10fopAc_ac_c */
BOOL daObjAuzu::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 0000009C-000001F8       .text create_heap__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::create_heap() {
    bool create_result = false;
    J3DModelData* mdl_data = static_cast<J3DModelData *>(dComIfG_getObjectRes(M_arcname, AUZU_BDL_AUZU));
    JUT_ASSERT(0xE2, mdl_data != NULL);
    field_0x298 = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);

    J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey *>(dComIfG_getObjectRes(M_arcname, AUZU_BTK_AUZU));
    JUT_ASSERT(0xEC, btk_data != NULL);

    int init_result = field_0x29C.init(
        mdl_data, btk_data, TRUE, 
        J3DFrameCtrl::EMode_LOOP, attr().m0C, 
        0, -1, false, FALSE
    );

    if (field_0x298 && init_result != 0) {
        create_result = true;
    }

    return create_result;
}

/* 000001F8-000003B8       .text _create__Q29daObjAuzu5Act_cFv */
cPhs_State daObjAuzu::Act_c::_create() {
    cPhs_State state = cPhs_ERROR_e;
    field_0x2B0 = prm_get_type();
    fopAcM_SetupActor(this, daObjAuzu::Act_c);

    field_0x2B9 = is_exist();
    if (field_0x2B9 != 0) {
        state = dComIfG_resLoad(&field_0x290, M_arcname);
        if (state == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, solidHeapCB, 3456)) {
                fopAcM_SetMtx(this, field_0x298->getBaseTRMtx());
                init_mtx();
                f32 cull_xz = attr().m00 * 3000.0f;
                fopAcM_setCullSizeBox(this, 
                    -cull_xz, -30.0f, -cull_xz, 
                    cull_xz, 30.0f, cull_xz
                );
                field_0x2B8 = 0;

                if (prm_get_appear() == 1) {
                    field_0x2B4 = 0.0f;
                } else {
                    if (fopAcM_isSwitch(this, prm_get_swSave())) {
                        field_0x2B4 = 0.0f;
                    } else {
                        field_0x2B4 = 1.0f;
                    }
                }

                field_0x2BA = 0;
                field_0x2BC = -1;
                set_state_map();
            } else {
                state = cPhs_ERROR_e;
            }
        }
    }

    return state;
}

/* 0000045C-00000498       .text _delete__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_delete() {
    if (field_0x2B9 != 0) {
        dComIfG_resDeleteDemo(&field_0x290, M_arcname);
    }
    return true;
}

/* 00000498-000004E8       .text is_exist__Q29daObjAuzu5Act_cCFv */
bool daObjAuzu::Act_c::is_exist() const {
    if (field_0x2B0 == 0) {
        return dComIfGs_isEventBit(dSv_event_flag_c::ENDLESS_NIGHT);
    }
    return true;
}

/* 000004E8-00000554       .text set_mtx__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    field_0x298->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000554-000005B8       .text init_mtx__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::init_mtx() {
    field_0x298->setBaseScale(
        cXyz(
            scale.x * attr().m00,
            scale.y,
            scale.z * attr().m00
        )
    );
    set_mtx();
}

/* 000005B8-00000624       .text set_state_map__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::set_state_map() {
    if (prm_get_appear() != 1) {
        if (is_appear()) {
            fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
        } else {
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        }
    }
}

/* 00000624-00000788       .text ship_whirl__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::ship_whirl() {
    daShip_c* ship_p = dComIfGp_getShipActor();
    if (ship_p && fopAcM_GetName(ship_p) == PROC_SHIP) {
        f32 sqr_mag_xz = fopAcM_searchActorDistanceXZ2(this, ship_p);
#if VERSION > VERSION_DEMO
        f32 fVar1 = (daObjAuzu::L_radius * attr().m08) * (daObjAuzu::L_radius * attr().m08);
        f32 fVar2 = (daObjAuzu::L_radius * attr().m04) * (daObjAuzu::L_radius * attr().m04);
#else
        f32 fVar2 = (daObjAuzu::L_radius * attr().m04) * (daObjAuzu::L_radius * attr().m04);
        f32 fVar1 = (daObjAuzu::L_radius * attr().m08) * (daObjAuzu::L_radius * attr().m08);
#endif
        if (sqr_mag_xz < fVar2) {
            if (field_0x2B4 > 0.01f) {
                bgm_start();
                if (sqr_mag_xz < fVar1) {
                    ship_p->onWhirlFlg(fopAcM_GetID(this), prm_get_linkID());
                } else {
                    ship_p->onWhirlFlgDirect(fopAcM_GetID(this), prm_get_linkID());
                }
            } else {
                ship_p->offWhirlFlg();
            }
        }
    }
}

/* 00000788-000007DC       .text bgm_start__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::bgm_start() {
    if (field_0x2B0 == 0 && !field_0x2BA) {
        field_0x2BA = 1;
        mDoAud_subBgmStart(JA_BGM_DIOCTA_BATTLE);
    }
}

/* 000007DC-00000AF8       .text _execute__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_execute() {
    f32 fVar2;
#if VERSION > VERSION_JPN
    set_mtx();
#endif
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        ship_whirl();
    } else {
        if (DEMO_SELECT(true, field_0x2B4 > 0.01f)) {
            daPy_lk_c* link_p = daPy_getPlayerLinkActorClass();
            fopAcM_searchActorDistanceXZ2(this, daPy_getPlayerLinkActorClass());
            if (fopAcM_searchActorDistanceXZ2(this, link_p) < (daObjAuzu::L_radius * attr().m04) * (daObjAuzu::L_radius * attr().m04)) {
                link_p->setWhirlId(fopAcM_GetID(this));
            }
        }
    }

    field_0x29C.play();

    if (prm_get_appear() == 1) {
        if (field_0x2B8) {
            fVar2 = 1.0f;
        } else {
            fVar2 = 0.0f;
        }
    } else {
        if (fopAcM_isSwitch(this, prm_get_swSave())) {
            fVar2 = 0.0f;
        } else {
            fVar2 = 1.0f;
        }
    }

    cLib_chaseF(&field_0x2B4, fVar2, 0.02f);
    s8 param = s8(100.0f * field_0x2B4);
    fopAcM_seStart(this, JA_SE_ATM_SWIRL, param);

    if (field_0x2B4 > 0.0f && fpcM_IsErrorID(field_0x2BC)) {
        cXyz sp30;
        sp30.x = (field_0x2B4 * (daObjAuzu::L_radius * attr().m00)) / 5000.0f;
        sp30.z = (field_0x2B4 * ((daObjAuzu::L_radius + 500.0f) * attr().m00)) / 5000.0f;
        field_0x2BC = fopAcM_create(PROC_KYTAG01, -1, &current.pos, tevStr.mRoomNo, &current.angle, &sp30);
    } else if (field_0x2B4 > 0.0f && fpcM_IsErrorID(field_0x2BC) == FALSE) {
        kytag01_class* kytag01_p = (kytag01_class *) fopAcM_SearchByID(field_0x2BC);
        if (kytag01_p){
            kytag01_p->mWaveInfo.mInnerRadius = field_0x2B4 * (daObjAuzu::L_radius * attr().m00);
            kytag01_p->mWaveInfo.mOuterRadius = field_0x2B4 * ((daObjAuzu::L_radius + 500.0f) * attr().m00);
        } 
    } else if (field_0x2B4 == 0.0f && fpcM_IsErrorID(field_0x2BC) == FALSE) {
        kytag01_class* kytag01_p = (kytag01_class *) fopAcM_SearchByID(field_0x2BC);
        if (kytag01_p){
            fopAcM_delete(kytag01_p);
        }
    }

    set_state_map();
    return true;
}

/* 00000AF8-00000B88       .text set_material__Q29daObjAuzu5Act_cFP11J3DMaterialUc */
void daObjAuzu::Act_c::set_material(J3DMaterial* i_materialP, u8 i_alphaVal) {
    while (i_materialP != NULL) {
        if (i_alphaVal == 0) {
            i_materialP->getShape()->hide();
        } else {
            i_materialP->getShape()->show();
            i_materialP->getTevKColor(3)->mColor.a = i_alphaVal;
        }
        i_materialP = i_materialP->getNext();
    }
}

/* 00000B88-00000C38       .text _draw__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(field_0x298, &tevStr);
    field_0x29C.entry(field_0x298->getModelData());
    J3DModelData* model_data_p = field_0x298->getModelData();
    u8 alpha = u8(field_0x2B4 * 255.5f) & 0xFF;
    set_material(
        model_data_p->getJointNodePointer(0)->getMesh(), 
        alpha
    );
    mDoExt_modelUpdateDL(field_0x298);

    return true;
}

namespace daObjAuzu {
namespace {
/* 00000C38-00000C58       .text Mthd_Create__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_create();
}

/* 00000C58-00000C7C       .text Mthd_Delete__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_delete();
}

/* 00000C7C-00000CA0       .text Mthd_Execute__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_execute();
}

/* 00000CA0-00000CC4       .text Mthd_Draw__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_draw();
}

/* 00000CC4-00000CCC       .text Mthd_IsDelete__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
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
}; // namespace daObjAuzu

actor_process_profile_definition g_profile_Obj_Auzu = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Auzu,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAuzu::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Auzu,
    /* Actor SubMtd */ &daObjAuzu::Mthd_Table,
    /* Status       */ 0x06 | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
