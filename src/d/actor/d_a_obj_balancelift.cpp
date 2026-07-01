/**
 * d_a_obj_balancelift.cpp
 * Object - Tower of the Gods - Pair of scales
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_balancelift.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_chain.h"
#include "d/d_lib.h"
#include "d/d_path.h"
#include "d/d_resorce.h"
#include "d/d_s_play.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "m_Do/m_Do_ext.h"
#include "dolphin/mtx/quat.h"
#include "dolphin/mtx/vec.h"
#include "assets/GZLE01/res/Object/Hten1.h"

static daBalancelift_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 200.0f,
    }},
};


/* 000000EC-00000160       .text __ct__19daBalancelift_HIO_cFv */
daBalancelift_HIO_c::daBalancelift_HIO_c() {
    mNo = -1;
    field_0x08 = 45.0f;
    field_0x0C = 0.05f;
    field_0x10 = 0.005f;
    field_0x14 = 0.9f;
    field_0x18 = 25.0f;
    field_0x1C = 0.65f;
    field_0x20 = 0.9f;
    field_0x24 = 440.0f;
    field_0x28 = 1800.0f;
    field_0x2C = 2.0f;
    field_0x30 = 2.0f;
    field_0x34 = 2.0f;
}

const char daBalancelift_c::M_arcname[] = "Hten1";

/* 0000019C-00000264       .text daObjBlift_ride_actor_check__FP10fopAc_ac_c */
static s32 daObjBlift_ride_actor_check(fopAc_ac_c* i_this) {
    s32 result = 0;

    if (fopAc_IsActor(i_this)) {
        s16 procName = fopAcM_GetName(i_this);

        if (procName == fpcNm_Obj_Try_e) {
            result = 1;
        } else if (procName == fpcNm_PLAYER_e) {
            result = 1;
            fpc_ProcID grabActorID = ((daPy_py_c*)i_this)->getGrabActorID();
            if (grabActorID != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* actor = fopAcM_SearchByID(grabActorID);
                if (actor != NULL) {
                    result = daObjBlift_ride_actor_check(actor) + 1;
                }
            }
        } else if (procName == fpcNm_AM2_e || procName == fpcNm_NPC_OS_e || procName == fpcNm_NPC_CB1_e) {
            result = 1;
        }
    }

    return result;
}

/* 00000264-0000033C       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void ride_call_back(dBgW* bgw, fopAc_ac_c* actor1, fopAc_ac_c* actor2) {
    daBalancelift_c* lift = (daBalancelift_c*)actor1;
    s32 ride_count = daObjBlift_ride_actor_check(actor2);

    cXyz pos = actor2->current.pos;
    cXyz diff = pos - lift->field_0x2EC;
    PSVECScale(&diff, &diff, l_HIO.field_0x10);
    PSVECAdd(&lift->field_0x2F8, &diff, &lift->field_0x2F8);

    if (lift->field_0x31C == 0) {
        *lift->field_0x318 += ride_count;
    } else {
        *lift->field_0x318 -= ride_count;
    }
}

/* 0000033C-00000510       .text calc_quat__15daBalancelift_cFv */
void daBalancelift_c::calc_quat() {
    cXyz pos = current.pos;
    pos.y -= field_0x310;

    cXyz diff = pos - field_0x2EC;
    PSVECScale(&diff, &diff, l_HIO.field_0x0C);
    PSVECAdd(&field_0x2F8, &diff, &field_0x2F8);
    PSVECScale(&field_0x2F8, &field_0x2F8, l_HIO.field_0x14);
    PSVECAdd(&field_0x2EC, &field_0x2F8, &field_0x2EC);

    cXyz v1 = field_0x290;
    cXyz v2 = current.pos;
    v1 -= field_0x2EC;
    v2 -= field_0x2EC;

    Quaternion q;
    Quaternion result;
    daObj::quat_rotBaseY2(&q, v2);
    PSQUATInverse(&q, &q);
    C_QUATSlerp(&field_0x2CC, &q, &result, 0.1f + REG10_F(23));
    field_0x2CC = result;

    daObj::quat_rotBaseY2(&q, v1);
    PSQUATInverse(&q, &q);
    C_QUATSlerp(&field_0x2DC, &q, &result, 0.15f + REG10_F(24));
    field_0x2DC = result;
}

/* 00000510-00000670       .text set_mtx__15daBalancelift_cFv */
void daBalancelift_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::quatM(&field_0x2CC);
    mDoMtx_stack_c::transM(0.0f, -field_0x310, 0.0f);

    cXyz vec(0.0f, 300.0f, 0.0f);
    PSMTXMultVec(mDoMtx_stack_c::get(), &vec, &field_0x290);
    PSMTXMultVec(mDoMtx_stack_c::get(), &field_0x29C, &field_0x2C0);

    cXyz zero(0.0f, 0.0f, 0.0f);
    PSMTXMultVec(mDoMtx_stack_c::get(), &zero, &field_0x304);

    mDoMtx_stack_c::quatM(&field_0x2DC);
    mDoMtx_stack_c::scaleM(l_HIO.field_0x2C, l_HIO.field_0x30, l_HIO.field_0x34);

    M_mdl->setBaseTRMtx(mDoMtx_stack_c::get());
    PSMTXCopy(mDoMtx_stack_c::get(), field_0x330);

    cXyz* data = (cXyz*)*(void**)((u8*)m_chain + 0x24);
    data[0] = field_0x304;
    data[1] = field_0x2C0;
    data[2] = current.pos;
}

/* 00000670-00000984       .text calc_weight__15daBalancelift_cFv */
void daBalancelift_c::calc_weight() {
    f32 weight;

    if (field_0x31C == 0) {
        s16 val = *field_0x318;
        if (val == 0) {
            weight = l_HIO.field_0x28 - 0.5f * l_HIO.field_0x24;
        } else if (val > 0) {
            weight = l_HIO.field_0x28;
        } else {
            weight = l_HIO.field_0x28 - l_HIO.field_0x24;
        }
        *field_0x320 |= 1;
    } else {
        s16 val = *field_0x318;
        if (val == 0) {
            weight = l_HIO.field_0x28 - 0.5f * l_HIO.field_0x24;
        } else if (val > 0) {
            weight = l_HIO.field_0x28 - l_HIO.field_0x24;
        } else {
            weight = l_HIO.field_0x28;
        }
        *field_0x320 |= 2;
    }

    if (*field_0x320 == 3) {
        *field_0x318 = 0;
        *field_0x320 = 0;
    }

    Vec horiz;
    horiz.x = field_0x29C.x;
    horiz.y = 0.0f;
    horiz.z = field_0x29C.z;
    f32 horiz_mag_sq = PSVECSquareMag(&horiz);

    f32 vert_sq = weight * weight - horiz_mag_sq;
    if (vert_sq > 0.0f) {
        vert_sq = std::sqrtf(vert_sq);
    }

    field_0x368 += 0.005f * (vert_sq - field_0x310);
    field_0x368 *= 0.92f;
    field_0x310 += field_0x368;

    cXyz diff = field_0x2A8 - field_0x29C;
    PSVECScale(&diff, &diff, l_HIO.field_0x20);
    PSVECAdd(&field_0x2B4, &diff, &field_0x2B4);
    PSVECScale(&field_0x2B4, &field_0x2B4, l_HIO.field_0x1C);
    PSVECAdd(&field_0x29C, &field_0x2B4, &field_0x29C);

    if (std::fabsf((f32)(field_0x368 > 1.0f)) != 0.0f) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_TENBIN_LIFT_MOVE, 0);
    }
}

/* 00000984-000009A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daBalancelift_c*)i_this)->CreateHeap();
}

/* 000009A4-00000BA0       .text CreateHeap__15daBalancelift_cFv */
BOOL daBalancelift_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTEN1_BDL_HTEN1_e);
    JUT_ASSERT(0x1a3, modelData != NULL);

    M_mdl = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    JUT_ASSERT(0x1a5, M_mdl != NULL);

    m_chain = dChain_packet_create(3, &tevStr, 2.0f);
    JUT_ASSERT(0x1a7, m_chain != NULL);

    pm_bgw = new dBgW();
    pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTEN1_DZB_HTEN1_e), dBgW::MOVE_BG_e, &field_0x330);
    pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    JUT_ASSERT(0x1b0, pm_bgw != NULL);

    return M_mdl != NULL && m_chain != NULL && pm_bgw != NULL;
}

/* 00000BA0-00000F34       .text CreateInit__15daBalancelift_cFv */
int daBalancelift_c::CreateInit() {
    u32 pathNo = (fopAcM_GetParam(this) >> 16) & 0xFF;

    if (pathNo != 0xFF) {
        field_0x360 = dPath_GetRoomPath(pathNo, current.roomNo);

        if (field_0x360 != NULL && field_0x360->m_num != 0) {
            current.pos = field_0x360->m_points[0].m_position;
            home.pos = current.pos;

            if (field_0x360->m_num > 1) {
                cXyz pos = field_0x360->m_points[1].m_position;
                parentActorID = fopAcM_createChild(fpcNm_Balancelift_e, fopAcM_GetID(this), -1,
                                                   &pos, tevStr.mRoomNo, NULL, NULL, -1, NULL);
            }
        }

        field_0x314 = 0;
        field_0x31C = 0;
        field_0x318 = &field_0x314;
        field_0x31E = 0;
        field_0x320 = &field_0x31E;
        field_0x310 = l_HIO.field_0x28 - 0.5f * l_HIO.field_0x24;
    } else {
        field_0x314 = 0;
        field_0x31E = 0;

        if (parentActorID != fpcM_ERROR_PROCESS_ID_e) {
            daBalancelift_c* partner = (daBalancelift_c*)fopAcM_SearchByID(parentActorID);
            if (partner != NULL) {
                field_0x31C = 1;
                field_0x318 = &partner->field_0x314;
                field_0x320 = &partner->field_0x31E;
            } else {
                field_0x31C = 0;
                field_0x318 = &field_0x314;
                field_0x320 = &field_0x31E;
            }
        } else {
            field_0x31C = 0;
            field_0x318 = &field_0x314;
            field_0x320 = &field_0x31E;
        }

        field_0x310 = l_HIO.field_0x28 - 0.5f * l_HIO.field_0x24;
    }

    field_0x368 = 0.0f;
    dComIfG_Bgsp()->Regist(pm_bgw, this);

    field_0x2EC = current.pos;
    field_0x2EC.y -= field_0x310;

    field_0x2F8 = cXyz::Zero;
    field_0x2B4 = cXyz::Zero;
    field_0x29C = cXyz::Zero;
    field_0x2A8 = cXyz::Zero;
    field_0x2CC = ZeroQuat;
    field_0x2DC = ZeroQuat;

    scale.set(2.0f, 2.0f, 2.0f);

    set_mtx();

    pm_bgw->SetRideCallback(ride_call_back);

    mStts.Init(0xC0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShield();
    mCyl.OnTgNoConHit();

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("\x93V\x94\x89\x83\x8A\x83\x74\x83\x67", &l_HIO);
    }

    return cPhs_COMPLEATE_e;
}

/* 00000F34-000010E0       .text daBalanceliftCreate__FPv */
static cPhs_State daBalanceliftCreate(void* i_this) {
    fopAcM_ct((fopAc_ac_c*)i_this, daBalancelift_c);

    daBalancelift_c* actor = (daBalancelift_c*)i_this;
    cPhs_State phase = dComIfG_resLoad(&actor->mPhase, daBalancelift_c::M_arcname);

    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap((fopAc_ac_c*)i_this, CheckCreateHeap, 0xE40)) {
            phase = (cPhs_State)actor->CreateInit();
            actor->cullMtx = actor->M_mdl->getBaseTRMtx();
            fopAcM_setCullSizeBox((fopAc_ac_c*)i_this, -150.0f, -150.0f, -150.0f, 150.0f, 1000.0f, 150.0f);
            PSMTXCopy(actor->M_mdl->getBaseTRMtx(), actor->field_0x330);
        } else {
            phase = cPhs_ERROR_e;
        }
    }

    return phase;
}

/* 0000129C-00001318       .text daBalanceliftDelete__FPv */
static BOOL daBalanceliftDelete(void* i_this) {
    daBalancelift_c* actor = (daBalancelift_c*)i_this;
    dComIfG_Bgsp()->Release(actor->pm_bgw);
    dComIfG_resDelete(&actor->mPhase, daBalancelift_c::M_arcname);
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00001318-0000133C       .text daBalanceliftExecute__FPv */
static BOOL daBalanceliftExecute(void* i_this) {
    return ((daBalancelift_c*)i_this)->_execute();
}

/* 0000133C-000016F0       .text _execute__15daBalancelift_cFv */
bool daBalancelift_c::_execute() {
    calc_weight();
    calc_quat();
    set_mtx();

    pm_bgw->Move();
    mStts.Move();

    if (mCyl.ChkTgHit()) {
        fopAc_ac_c* hitActor = mCyl.GetTgHitAc();
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();

        if (fopAc_IsActor(hitActor) && fopAcM_GetProfName(hitActor) == fpcNm_BOMB_e) {
            cXyz pos = field_0x304;
            pos.y -= 50.0f;
            cXyz diff = pos - hitActor->current.pos;
            if (!diff.normalizeRS()) {
                diff.x = 0.0f;
                diff.y = 0.0f;
                diff.z = 1.0f;
            }
            PSVECAdd(&field_0x2F8, &(diff * -20.0f), &field_0x2F8);
            field_0x368 += 2.0f * -diff.y;
        } else if (hitObj != NULL) {
            cXyz normal = *mCyl.GetTgRVecP();
            if (!normal.normalizeRS()) {
                normal.x = 0.0f;
                normal.y = 0.0f;
                normal.z = 1.0f;
            }

            if (hitObj->ChkAtType(AT_TYPE_WIND)) {
                PSVECAdd(&field_0x2F8, &(normal * -12.0f), &field_0x2F8);
                field_0x368 += 2.0f * -normal.y;
            } else if (hitObj->ChkAtType(AT_TYPE_SWORD)) {
                PSVECAdd(&field_0x2F8, &(normal * -8.0f), &field_0x2F8);
                field_0x368 += 2.0f * -normal.y;

                cXyz* hitPos = mCyl.GetTgHitPosP();
                cXyz diff = *hitPos - field_0x304;
                f32 dist_sq = PSVECSquareMag(&diff);
                f32 dist;
                if (dist_sq > 0.0f) {
                    dist = std::sqrtf(dist_sq);
                } else {
                    dist = dist_sq;
                }

                PSVECAdd(&field_0x2B4, &(normal * l_HIO.field_0x18), &field_0x2B4);
                field_0x2A8.y = dist;
                field_0x29C.y = dist;

                dComIfGp_particle_set(0xC, mCyl.GetTgHitPosP());
            }

            fopAcM_seStart(this, JA_SE_OBJ_COL_SWS_NMTLP, 0);
        }
    }

    mCyl.SetC(field_0x304);
    dComIfG_Ccsp()->Set(&mCyl);

    return false;
}

/* 000016F0-00001774       .text daBalanceliftDraw__FPv */
static BOOL daBalanceliftDraw(void* i_this) {
    daBalancelift_c* actor = (daBalancelift_c*)i_this;
    dKy_tevstr_c* tevstr = &actor->tevStr;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, tevstr);
    g_env_light.setLightTevColorType(actor->M_mdl, tevstr);
    mDoExt_modelUpdateDL(actor->M_mdl);
    j3dSys.getDrawBuffer(0)->entryImm(actor->m_chain, 0);
    return TRUE;
}

/* 00001774-0000177C       .text daBalanceliftIsDelete__FPv */
static BOOL daBalanceliftIsDelete(void*) {
    return TRUE;
}

static actor_method_class daBalanceliftMethodTable = {
    (process_method_func)daBalanceliftCreate,
    (process_method_func)daBalanceliftDelete,
    (process_method_func)daBalanceliftExecute,
    (process_method_func)daBalanceliftIsDelete,
    (process_method_func)daBalanceliftDraw,
};

actor_process_profile_definition g_profile_Balancelift = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Balancelift_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBalancelift_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Balancelift_e,
    /* Actor SubMtd */ &daBalanceliftMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
