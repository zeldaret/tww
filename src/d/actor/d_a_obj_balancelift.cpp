/**
 * d_a_obj_balancelift.cpp
 * Object - Tower of the Gods - Pair of scales
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_balancelift.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_chain.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_lib.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Hten1.h"

dChain_packet_c* dChain_packet_create(int, dKy_tevstr_c*, f32);

// Defined in dolphin/mtx/quat.c but not declared in dolphin/mtx/quat.h.
extern "C" void PSQUATInverse(const Quaternion* src, Quaternion* inv);

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


static daBalancelift_HIO_c l_HIO;

/* 000000EC-00000160       .text __ct__19daBalancelift_HIO_cFv */
daBalancelift_HIO_c::daBalancelift_HIO_c() {
    mNo = -1;
    m08 = 45.0f;
    mPlateSpring = 0.05f;
    mRideSpring = 0.005f;
    mPlateDamp = 0.9f;
    mHitSwing = 25.0f;
    mSwingDamp = 0.65f;
    mSwingSpring = 0.9f;
    mMoveRange = 440.0f;
    mMaxLength = 1800.0f;
    mScale.set(2.0f, 2.0f, 2.0f);
}

const char daBalancelift_c::M_arcname[] = "Hten1";

/* 0000019C-00000264       .text daObjBlift_ride_actor_check__FP10fopAc_ac_c */
static int daObjBlift_ride_actor_check(fopAc_ac_c* i_actor) {
    int weight = 0;
    if (fopAc_IsActor(i_actor)) {
        if (fopAcM_GetName(i_actor) == fpcNm_Obj_Try_e) {
            weight = 1;
        } else if (fopAcM_GetName(i_actor) == fpcNm_PLAYER_e) {
            daPy_py_c* player = (daPy_py_c*)i_actor;
            weight++;
            fpc_ProcID grab_id = player->getGrabActorID();
            if (grab_id != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* grab_actor = fopAcM_SearchByID(grab_id);
                if (grab_actor != NULL) {
                    weight = daObjBlift_ride_actor_check(grab_actor) + 1;
                }
            }
        } else if (fopAcM_GetName(i_actor) == fpcNm_AM2_e || fopAcM_GetName(i_actor) == fpcNm_NPC_OS_e ||
                   fopAcM_GetName(i_actor) == fpcNm_NPC_CB1_e)
        {
            weight = 1;
        }
    }
    return weight;
}

/* 00000264-0000033C       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void ride_call_back(dBgW*, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    daBalancelift_c* i_this = (daBalancelift_c*)i_ac;
    int weight = daObjBlift_ride_actor_check(i_pt);

    cXyz pos = i_pt->current.pos;
    cXyz vec = pos - i_this->mPlatePos;
    vec *= l_HIO.mRideSpring;
    i_this->mPlateSpeed += vec;

    if (i_this->mSide == 0) {
        *i_this->mpWeight += weight;
    } else {
        *i_this->mpWeight -= weight;
    }
}

/* 0000033C-00000510       .text calc_quat__15daBalancelift_cFv */
void daBalancelift_c::calc_quat() {
    cXyz pos = current.pos;
    pos.y -= mLength;
    cXyz vec = pos - mPlatePos;
    vec *= l_HIO.mPlateSpring;
    mPlateSpeed += vec;
    mPlateSpeed *= l_HIO.mPlateDamp;
    mPlatePos += mPlateSpeed;

    cXyz top = mTopPos;
    cXyz base = current.pos;
    top -= mPlatePos;
    base -= mPlatePos;

    Quaternion quat;
    Quaternion out;

    daObj::quat_rotBaseY2(&quat, base);
    PSQUATInverse(&quat, &quat);
    mDoMtx_quatSlerp(&mArmQuat, &quat, &out, 0.1f + REG10_F(23));
    mArmQuat = out;

    daObj::quat_rotBaseY2(&quat, top);
    PSQUATInverse(&quat, &quat);
    mDoMtx_quatSlerp(&mPlateQuat, &quat, &out, 0.15f + REG10_F(24));
    mPlateQuat = out;
}

/* 00000510-00000670       .text set_mtx__15daBalancelift_cFv */
void daBalancelift_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::quatM(&mArmQuat);
    mDoMtx_stack_c::transM(0.0f, -mLength, 0.0f);

    cXyz top_offset(0.0f, 300.0f, 0.0f);
    mDoMtx_stack_c::multVec(&top_offset, &mTopPos);
    mDoMtx_stack_c::multVec(&mSwingPos, &mSwingWorldPos);

    cXyz zero(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::multVec(&zero, &mPlateWorldPos);

    mDoMtx_stack_c::quatM(&mPlateQuat);
    mDoMtx_stack_c::scaleM(l_HIO.mScale.x, l_HIO.mScale.y, l_HIO.mScale.z);
    M_mdl->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);

    cXyz* pt = m_chain->mPt;
    pt[0] = mPlateWorldPos;
    pt[1] = mSwingWorldPos;
    pt[2] = current.pos;
}

/* 00000670-00000984       .text calc_weight__15daBalancelift_cFv */
void daBalancelift_c::calc_weight() {
    f32 length;

    if (mSide == 0) {
        if (*mpWeight == 0) {
            length = l_HIO.mMaxLength - 0.5f * l_HIO.mMoveRange;
        } else if (*mpWeight > 0) {
            length = l_HIO.mMaxLength;
        } else {
            length = l_HIO.mMaxLength - l_HIO.mMoveRange;
        }
        *mpFlag |= 1;
    } else {
        if (*mpWeight == 0) {
            length = l_HIO.mMaxLength - 0.5f * l_HIO.mMoveRange;
        } else if (*mpWeight > 0) {
            length = l_HIO.mMaxLength - l_HIO.mMoveRange;
        } else {
            length = l_HIO.mMaxLength;
        }
        *mpFlag |= 2;
    }

    if (*mpFlag == 3) {
        *mpWeight = 0;
        *mpFlag = 0;
    }

    f32 target = std::sqrtf(length * length - mSwingPos.abs2XZ());
    mLengthSpeed += 0.005f * (target - mLength);
    mLengthSpeed *= 0.92f;
    mLength += mLengthSpeed;

    cXyz vec = mSwingTarget - mSwingPos;
    vec *= l_HIO.mSwingSpring;
    mSwingSpeed += vec;
    mSwingSpeed *= l_HIO.mSwingDamp;
    mSwingPos += mSwingSpeed;

    if (std::fabsf(mLengthSpeed > 1.0f)) {
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
    JUT_ASSERT(419, modelData != NULL);

    M_mdl = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    JUT_ASSERT(421, M_mdl != NULL);

    m_chain = dChain_packet_create(3, &tevStr, 2.0f);
    JUT_ASSERT(423, m_chain != NULL);

    pm_bgw = new dBgW();
    pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTEN1_DZB_HTEN1_e), cBgW::MOVE_BG_e, &mMtx);
    pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    JUT_ASSERT(432, pm_bgw != NULL);

    return M_mdl != NULL && m_chain != NULL && pm_bgw != NULL;
}

/* 00000BA0-00000F34       .text CreateInit__15daBalancelift_cFv */
cPhs_State daBalancelift_c::CreateInit() {
    u8 path_id = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_id != 0xFF) {
        mpPath = dPath_GetRoomPath(path_id, fopAcM_GetRoomNo(this));
        if (mpPath != NULL && mpPath->m_num != 0) {
            current.pos = mpPath->m_points[0].m_position;
            home.pos = current.pos;
            if (mpPath->m_num > 1) {
                cXyz pos = mpPath->m_points[1].m_position;
                parentActorID = fopAcM_createChild(fpcNm_Balancelift_e, fopAcM_GetID(this), 0xFFFFFFFF, &pos,
                                                   tevStr.mRoomNo, NULL);
            }
        }

        mWeight = 0;
        mSide = 0;
        mpWeight = &mWeight;
        mFlag = 0;
        mpFlag = &mFlag;
        mLength = l_HIO.mMaxLength - 0.5f * l_HIO.mMoveRange;
    } else {
        mWeight = 0;
        mFlag = 0;
        if (parentActorID != fpcM_ERROR_PROCESS_ID_e) {
            daBalancelift_c* parent = (daBalancelift_c*)fopAcM_SearchByID(parentActorID);
            if (parent != NULL) {
                mSide = 1;
                mpWeight = &parent->mWeight;
                mpFlag = &parent->mFlag;
            } else {
                mSide = 0;
                mpWeight = &mWeight;
                mpFlag = &mFlag;
            }
        } else {
            mSide = 0;
            mpWeight = &mWeight;
            mpFlag = &mFlag;
        }
        mLength = l_HIO.mMaxLength - 0.5f * l_HIO.mMoveRange;
    }

    mLengthSpeed = 0.0f;
    dComIfG_Bgsp()->Regist(pm_bgw, this);

    mPlatePos = current.pos;
    mPlatePos.y -= mLength;
    mPlateSpeed = cXyz::Zero;
    mSwingSpeed = cXyz::Zero;
    mSwingPos = cXyz::Zero;
    mSwingTarget = cXyz::Zero;
    mArmQuat = ZeroQuat;
    mPlateQuat = ZeroQuat;

    scale.setall(2.0f);
    set_mtx();

    pm_bgw->SetRideCallback(ride_call_back);

    mStts.Init(0xC0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShield();
    mCyl.OnTgNoConHit();

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("天秤リフト", &l_HIO);
    }
    return cPhs_COMPLEATE_e;
}

cPhs_State daBalancelift_c::_create() {
    fopAcM_ct(this, daBalancelift_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xe40)) {
            ret = CreateInit();
        } else {
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(this, M_mdl->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -150.0f, -150.0f, -150.0f, 150.0f, 1000.0f, 150.0f);
        cMtx_copy(M_mdl->getBaseTRMtx(), mMtx);
    }
    return ret;
}

/* 00000F34-000010E0       .text daBalanceliftCreate__FPv */
static cPhs_State daBalanceliftCreate(void* i_this) {
    return ((daBalancelift_c*)i_this)->_create();
}

bool daBalancelift_c::_delete() {
    dComIfG_Bgsp()->Release(pm_bgw);
    dComIfG_resDelete(&mPhs, M_arcname);
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return true;
}

/* 0000129C-00001318       .text daBalanceliftDelete__FPv */
static BOOL daBalanceliftDelete(void* i_this) {
    return ((daBalancelift_c*)i_this)->_delete();
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
        fopAc_ac_c* hit_ac = mCyl.GetTgHitAc();
        cCcD_Obj* hit_obj = mCyl.GetTgHitObj();

        if (fopAc_IsActor(hit_ac) && fopAcM_GetProfName(hit_ac) == fpcNm_BOMB_e) {
            cXyz pos = mPlateWorldPos;
            pos.y -= 50.0f;
            cXyz dir = pos - hit_ac->current.pos;
            if (!dir.normalizeRS()) {
                dir.set(0.0f, 0.0f, 1.0f);
            }
            mPlateSpeed += dir * -20.0f;
            mLengthSpeed += 2.0f * -dir.y;
        } else if (hit_obj != NULL) {
            cXyz dir = *mCyl.GetTgRVecP();
            if (!dir.normalizeRS()) {
                dir.set(0.0f, 0.0f, 1.0f);
            }

            if (hit_obj->ChkAtType(AT_TYPE_WIND)) {
                mPlateSpeed += dir * -12.0f;
                mLengthSpeed += 2.0f * -dir.y;
            } else if (hit_obj->ChkAtType(AT_TYPE_SWORD)) {
                mPlateSpeed += dir * -8.0f;
                mLengthSpeed += 2.0f * -dir.y;

                cXyz* hit_pos = mCyl.GetTgHitPosP();
                if (hit_pos != NULL) {
                    cXyz diff = *hit_pos - mPlateWorldPos;
                    f32 dist = diff.abs();
                    mSwingSpeed += dir * l_HIO.mHitSwing;
                    mSwingTarget.y = dist;
                    mSwingPos.y = dist;
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, hit_pos);
                }
                fopAcM_seStart(this, JA_SE_OBJ_COL_SWS_NMTLP, 0);
            }
        }
    }

    mCyl.SetC(mPlateWorldPos);
    dComIfG_Ccsp()->Set(&mCyl);
    return false;
}

bool daBalancelift_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(M_mdl, &tevStr);
    mDoExt_modelUpdateDL(M_mdl);
    j3dSys.getDrawBuffer(J3DSysDrawBuf_Opa)->entryImm(m_chain, 0);
    return true;
}

/* 000016F0-00001774       .text daBalanceliftDraw__FPv */
static BOOL daBalanceliftDraw(void* i_this) {
    return ((daBalancelift_c*)i_this)->_draw();
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
