/**
 * d_a_daiocta_eye.cpp
 * Mini-Boss - Big Octo (eye)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta_eye.h"
#include "d/actor/d_a_daiocta.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_func.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

const s32 daDaiocta_Eye_c::m_heapsize = 0xB20;
const char daDaiocta_Eye_c::m_arc_name[] = "daiocta";
const s32 daDaiocta_Eye_c::m_scale_damage_time = 8;

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};

static daDaiocta_Eye_HIO_c l_HIO;

/* 000000EC-000001B0       .text __ct__19daDaiocta_Eye_HIO_cFv */
daDaiocta_Eye_HIO_c::daDaiocta_Eye_HIO_c() {
    /* Instruction match */
    field_0x1C = 195.0f;
    field_0x04 = 0xF;
    field_0x08 = 5.0f;
    field_0x0C = 8.0f;
    field_0x10 = 0.0f;
    field_0x14 = 0.0f;
    field_0x18 = 30.0f;
    field_0x20 = 0x1000;
    field_0x22 = 0x4;
    field_0x24 = 0x4000;
    field_0x26 = 0x1000;
    field_0x28 = 0x1000;
    field_0x2A = 0x7FFF;
    field_0x2C = 0x2000;
    field_0x2E = 0x2000; 
}

/* 000001B0-000001FC       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daDaiocta_Eye_c* this_p = (daDaiocta_Eye_c *) model_p->getUserArea();
        if (this_p) {
            this_p->_nodeControl(i_nodeP, model_p);
        }
    }
    return TRUE;
}

/* 000001FC-000002B8       .text _nodeControl__15daDaiocta_Eye_cFP7J3DNodeP8J3DModel */
void daDaiocta_Eye_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    /* Instruction match */
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();
    cXyz tmp0(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));

    if (jnt_no == 2) {
        mDoMtx_stack_c::ZXYrotM(field_0x2E6);
        mDoMtx_stack_c::scaleM(field_0x460);
    }
    
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daDaiocta_Eye_c *)i_this)->_createHeap();
}

/* 000002D8-000004E4       .text _createHeap__15daDaiocta_Eye_cFv */
BOOL daDaiocta_Eye_c::_createHeap() {
    /* Instruction match */
    static Vec eye_sph_offset[] = {
        { 0, 0,0 },
    };

    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 1,
            /* mJointIndex */ 2,
            /* mRadius     */ 110.0f,
            /* mpOffsets   */ eye_sph_offset
        }
    };

    J3DModelData* modelData = static_cast<J3DModelData *>(dComIfG_getObjectRes(m_arc_name, 0x10));
    JUT_ASSERT(0xE9, modelData != NULL);

    field_0x2A8 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);

    if (!field_0x2A8) {
        return FALSE;
    }
    
    field_0x2A8->setUserArea((u32)this);

    field_0x2AC = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, 0x18);

    if (!field_0x2AC) {
        return FALSE;
    }

    int init_res = init_res = field_0x2B0.init(modelData, field_0x2AC, TRUE, 0, 
                                        1.0f, 0, -1, false, FALSE);
    
    if (init_res == 0) {
        return FALSE;
    }

    field_0x2C8 = (J3DAnmTextureSRTKey *) dComIfG_getObjectRes(m_arc_name, 0x23);
    
    if (!field_0x2C8) {
        return FALSE;
    }

    init_res = field_0x2CC.init(modelData, field_0x2C8, TRUE, 0, 
                                    1.0f, 0, -1, false, FALSE);
    
    if (init_res == 0) {
        return FALSE;
    }

    for (int i = 0; i < 3; i++) {
        if (i == 2) modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
    }

    field_0x470 = JntHit_create(field_0x2A8, search_data, ARRAY_SSIZE(search_data));

    if (field_0x470) {   
        jntHit = field_0x470;
    } else {
        return FALSE;
    }

    return TRUE;
}

/* 000004E4-00000510       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void coHit_CB(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* i_actor, dCcD_GObjInf*) {
    if(i_actor) {
        ((daDaiocta_Eye_c *)i_this)->_coHit(i_actor);
    }
}

/* 00000510-000005D0       .text _coHit__15daDaiocta_Eye_cFP10fopAc_ac_c */
void daDaiocta_Eye_c::_coHit(fopAc_ac_c* i_actor) {
    if (fpcM_GetName(i_actor) == PROC_BOMB) {
        daBomb_c* bomb_p = (daBomb_c *) i_actor;
        if (bomb_p->chk_state(daBomb_c::STATE_4)) {
            if (!field_0x294) {
                health = 0;
                field_0x294 = 1;
                field_0x295 = 1;
                dComIfGp_particle_set(
                    dPa_name::ID_SCENE_8206, &field_0x48C, &shape_angle, 
                    NULL, 0xFF, &field_0x478, fopAcM_GetRoomNo(this)
                );
                modeDeathInit();
            } else {
                field_0x297 = 1;
            }
        }
    }
}

/* 000005D0-000006C0       .text setMtx__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::setMtx() {
    field_0x2A8->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    field_0x2A8->setBaseTRMtx(mDoMtx_stack_c::get());
    
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(l_HIO.field_0x10, l_HIO.field_0x14, l_HIO.field_0x18);
    mDoMtx_stack_c::multVecZero(&field_0x48C);
}

/* 000006C0-00000A6C       .text checkTgHit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::checkTgHit() {
    /* Nonmatching */
    field_0x424.Move();
    cCcD_Obj* tg_hit_obj = field_0x2F8.GetTgHitObj();
    if (tg_hit_obj) {
        mDoAud_onEnemyDamage();
        u8 damaged = 0;
        
        if (tg_hit_obj->ChkAtType(AT_TYPE_NORMAL_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = 1;
        } else if (tg_hit_obj->ChkAtType(AT_TYPE_ICE_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = 1;
        } else if (tg_hit_obj->ChkAtType(AT_TYPE_FIRE_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = 1;
        } else if (tg_hit_obj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 4;
            damaged = 1;
        } else if (tg_hit_obj->ChkAtType(AT_TYPE_HOOKSHOT)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = 1;
        } else if (tg_hit_obj->ChkAtType(AT_TYPE_BOOMERANG)) {
            fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 32);
            health--;
            damaged = 1;
        }

        if (damaged == 1) {        
            daPy_py_c* player_p = daPy_getPlayerActorClass();
            cXyz sp1C = *field_0x2F8.GetTgHitPosP();
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &sp1C);
            if (health <= 0) {
                cXyz sp28(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &sp1C, &player_p->shape_angle, &sp28);
                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
                health = 0;
                modeDeathInit();
            } else {
                modeDamageInit();
            }
        }
    }
}

/* 00000A6C-00000A78       .text modeWaitInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWaitInit() {
    field_0x29C = MODE_WAIT;
}

/* 00000A78-00000A98       .text modeWait__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWait() {
    checkTgHit();
}

/* 00000A98-00000BD8       .text modeDamageInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamageInit() {
    field_0x29C = MODE_DAMAGE;
    field_0x46C = m_scale_damage_time;
    field_0x296 = 1;

    J3DModelData* model_data_p = field_0x2A8->getModelData();
    field_0x2AC = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, 0x18);
    field_0x2B0.init(model_data_p, field_0x2AC, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    field_0x2C8 = (J3DAnmTextureSRTKey *) dComIfG_getObjectRes(m_arc_name, 0x23);
    field_0x2CC.init(model_data_p, field_0x2C8, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
 
    fopAcM_monsSeStart(field_0x474, 0x48C8, 0);
}

/* 00000BD8-00000CD0       .text modeDamage__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamage() {
    static float scale_table[] = {
        1.0f, 0.975f, 
        1.0f, 0.95f, 
        1.0f, 0.9f,
        1.0f, 0.85f
    };

    dLib_scaleAnime(
        &field_0x460.x, scale_table, 
        ARRAY_SSIZE(scale_table), &field_0x46C, 
        0.2f, 10.0f, 0.025f
    );
    field_0x460.y = field_0x460.x;
    field_0x460.z = field_0x460.x;

    if (field_0x2CC.isStop() && field_0x2B0.isStop() && field_0x46C == 0) {
        modeWaitInit();
    } else if (field_0x46C == 0) {
        field_0x46C = m_scale_damage_time;
    } 
}

/* 00000CD0-00000E20       .text modeDeathInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeathInit() {
    field_0x29C = MODE_DEATH;
    field_0x296 = 1;
    field_0x460.setall(1.0f);
    field_0x2AC = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, 0x19);
    field_0x2B0.init(field_0x2A8->getModelData(), field_0x2AC, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    field_0x2C8 = (J3DAnmTextureSRTKey *) dComIfG_getObjectRes(m_arc_name, 0x24);
    field_0x2CC.init(field_0x2A8->getModelData(), field_0x2C8, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    fopAcM_monsSeStart(field_0x474, 0x48CB, 0);
}

/* 00000E20-00000E2C       .text modeDeath__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeath() {
    field_0x294 = 1;
}

/* 00000E2C-00000ED0       .text modeProcCall__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeProcCall() {
    static ModeProcFunc mode_proc[] = {
        &daDaiocta_Eye_c::modeWait,
        &daDaiocta_Eye_c::modeDamage,
        &daDaiocta_Eye_c::modeDeath,
    };
    (this->*mode_proc[field_0x29C])();
}

/* 00000ED0-00001120       .text _execute__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_execute() {
    /* Instruction match */
    if (!field_0x298) {
        return false;
    }

    if (field_0x294 == 1) {
        field_0x2F8.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
    }

    field_0x2EC = l_HIO.field_0x24;
    field_0x2EE = l_HIO.field_0x26;
    field_0x2F0 = l_HIO.field_0x28;
    field_0x2F2 = l_HIO.field_0x2A;
    field_0x2F4 = l_HIO.field_0x2C;
    field_0x2F6 = l_HIO.field_0x2E;

    field_0x2B0.play();
    field_0x2CC.play();

    field_0x296 = 0;
    field_0x297 = 0;
    modeProcCall();
    setMtx();

    attention_info.position = current.pos;

    attention_info.position.y += 100.0f;
    
    eyePos = current.pos;

    cLib_addCalcAngleS2(&field_0x2E6.x, field_0x2E0, l_HIO.field_0x22 + 1, l_HIO.field_0x20);
    cLib_addCalcAngleS2(&field_0x2E6.y, field_0x2E2, l_HIO.field_0x22 + 1, l_HIO.field_0x20);
    cLib_addCalcAngleS2(&field_0x2E6.z, field_0x2E4, l_HIO.field_0x22 + 1, l_HIO.field_0x20);
    field_0x2F8.SetR(l_HIO.field_0x1C);
    field_0x2F8.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x2F8);

    field_0x498.set(0, shape_angle.y, 0);

    cXyz sp08 = current.pos;
    sp08.y += 1000.0f;
    f32 water_height = dBgS_GetWaterHeight(sp08);

    if (current.pos.y < water_height) {
        if (field_0x478.getEmitter()) {
            field_0x478.end();
        }
    } else if (field_0x29C != MODE_DEATH) {
        attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 34;
    }
    
    if (field_0x29C == MODE_DEATH || dComIfGp_event_runCheck()) {
        attention_info.flags = 0;
    }

    return false;
}

/* 00001120-000011EC       .text _draw__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_draw() {
    if (field_0x298 == 0) {
        return false;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(field_0x2A8, &tevStr);
    
    field_0x2CC.entry(field_0x2A8->getModelData());
    field_0x2B0.entry(field_0x2A8->getModelData());

    mDoExt_modelUpdateDL(field_0x2A8);

    field_0x2CC.remove(field_0x2A8->getModelData());
    field_0x2B0.remove(field_0x2A8->getModelData());
    
    return true;
}

/* 000011EC-000012D4       .text createInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::createInit() {
    /* Instruction match */
    field_0x298 = 0;
    cullMtx = field_0x2A8->getBaseTRMtx();
    field_0x424.Init(0, 0, this);
    field_0x2F8.Set(l_sph_src);
    field_0x2F8.SetStts(&field_0x424);
    field_0x2F8.SetCoHitCallback(coHit_CB);
    max_health = 4;
    health = max_health;
    field_0x460.setall(1.0f);
    if (parentActorID != -1) {
        fopAc_ac_c* parent_p = fopAcM_SearchByID(parentActorID);
        if (parent_p && fopAc_IsActor(parent_p) && fpcM_GetName(parent_p) == PROC_DAIOCTA) {
            field_0x474 = (daDaiocta_c *) parent_p;
        }
    }
}

/* 000012D4-00001450       .text _create__15daDaiocta_Eye_cFv */
cPhs_State daDaiocta_Eye_c::_create() {
    fopAcM_SetupActor(this, daDaiocta_Eye_c);
    cPhs_State result = dComIfG_resLoad(&field_0x2A0, m_arc_name);
    if (result == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return result;
}

/* 00001764-000017B4       .text _delete__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_delete() {
    dComIfG_resDelete(&field_0x2A0, m_arc_name);
    field_0x478.remove();
    return true;
}

/* 000017B4-000017D4       .text daDaiocta_EyeCreate__FPv */
static cPhs_State daDaiocta_EyeCreate(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_create();
}

/* 000017D4-000017F8       .text daDaiocta_EyeDelete__FPv */
static BOOL daDaiocta_EyeDelete(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_delete();
}

/* 000017F8-0000181C       .text daDaiocta_EyeExecute__FPv */
static BOOL daDaiocta_EyeExecute(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_execute();
}

/* 0000181C-00001840       .text daDaiocta_EyeDraw__FPv */
static BOOL daDaiocta_EyeDraw(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_draw();
}

/* 00001840-00001848       .text daDaiocta_EyeIsDelete__FPv */
static BOOL daDaiocta_EyeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daDaiocta_EyeMethodTable = {
    (process_method_func)daDaiocta_EyeCreate,
    (process_method_func)daDaiocta_EyeDelete,
    (process_method_func)daDaiocta_EyeExecute,
    (process_method_func)daDaiocta_EyeIsDelete,
    (process_method_func)daDaiocta_EyeDraw,
};

actor_process_profile_definition g_profile_DAIOCTA_EYE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DAIOCTA_EYE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDaiocta_Eye_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DAIOCTA_EYE,
    /* Actor SubMtd */ &daDaiocta_EyeMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
