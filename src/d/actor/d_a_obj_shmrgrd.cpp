/**
 * d_a_obj_shmrgrd.cpp
 * Object - Skull Hammer switch (spiked) 
 */

#include "d/actor/d_a_obj_shmrgrd.h"
#include "d/res/res_shmrgrd.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

struct Attr_c {
    /* 0x00 */ f32 mVSpring;
    /* 0x04 */ f32 mIntVSpeedDecay;
    /* 0x08 */ f32 mExtVSpeedDecay;
    /* 0x0C */ f32 mVibMag0Mult;
    /* 0x10 */ f32 mVibSpring;
    /* 0x14 */ f32 mAngleSpeedDecay;
    /* 0x18 */ s16 mCrushDuration;
    /* 0x1C */ f32 m1C; // unused
    /* 0x20 */ f32 m20; // unused
    /* 0x24 */ f32 m24; // unused
};

const Attr_c L_attr = {
    /* mVSpring           */ 0.8f,
    /* mIntVSpeedDecay    */ 0.55f,
    /* mExtVSpeedDecay    */ 0.55f,
    /* mVibMag0Mult       */ 1.0f,
    /* mVibSpring         */ 0.99f,
    /* mAngleSpeedDecay   */ 0.18f,
    /* mCrushDuration     */ 18,
    /* m1C                */ 0.0f, 
    /* m20                */ 0.8f,
    /* m24                */ 0.45f
};

inline const Attr_c & attr() { return L_attr; }

int daObjShmrgrd_c::M_damage;
short daObjShmrgrd_c::M_damage_dir;
daObjShmrgrd_c* daObjShmrgrd_c::M_list_p;

const dCcD_SrcCyl daObjShmrgrd_c::M_cyl_src_co = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 79.0f,
        /* Height */ 112.5f,
    },
};
const dCcD_SrcCyl daObjShmrgrd_c::M_cyl_src_at = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 80.0f,
        /* Height */ 260.0f,
    },
};
const dCcD_SrcCyl daObjShmrgrd_c::M_cyl_src_tg = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
        /* Height */ 112.5f,
    },
};
const dCcD_SrcCyl daObjShmrgrd_c::M_cyl_src_gap_co = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 70.0f,
        /* Height */ 260.0f,
    },
};

const char daObjShmrgrd_c::M_arcname[] = "Shmrgrd";

const GXColor color = {0xA0, 0xA0, 0x80, 0xFF};

/* 000000EC-00000358       .text __ct__14daObjShmrgrd_cFv */
daObjShmrgrd_c::daObjShmrgrd_c() {
    mSmokeCb.setColor(color);
    mpNext = NULL;
}

/* 000005A8-000005C8       .text solidHeapCB__14daObjShmrgrd_cFP10fopAc_ac_c */
BOOL daObjShmrgrd_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjShmrgrd_c*>(i_this)->create_heap();
}

/* 000005C8-000006E0       .text create_heap__14daObjShmrgrd_cFv */
BOOL daObjShmrgrd_c::create_heap() {
    BOOL rt = FALSE;
    J3DModelData* mdl_data = static_cast<J3DModelData *>(dComIfG_getObjectRes(M_arcname, SHMRGRD_BDL_SHMRGRD));
    JUT_ASSERT(0x21A, mdl_data != NULL);
    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        if (mpModel) {
            mdl_data->getJointNodePointer(2)->setCallBack(jnodeCB);
            mpModel->setUserArea((u32) this);
            mpBgW = dBgW_NewSet((cBgD_t *)dComIfG_getObjectRes(M_arcname, SHMRGRD_DZB_HGBASE), cBgW::MOVE_BG_e, &mMtx);
            if (mpBgW) {
                rt = TRUE;
            }
        }
    }
    return rt;
}

/* 000006E0-00000964       .text _create__14daObjShmrgrd_cFv */
cPhs_State daObjShmrgrd_c::_create() {
    fopAcM_SetupActor(this, daObjShmrgrd_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x12A0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            init_mtx();
            fopAcM_setCullSizeBox(this, -90.0f, 0.0f, -90.0f, 90.0f, 120.0f, 90.0f);

            mSttsCo.Init(0xFF, 0xFF, this);
            mCylCo.Set(M_cyl_src_co);
            mCylCo.SetStts(&mSttsCo);
            mSttsTg.Init(0xFF, 0xFF, this);
            mCylTg.Set(M_cyl_src_tg);
            mCylTg.SetStts(&mSttsTg);
            mCylTg.OnTgNoHitMark();
            mSttsAt.Init(0xFF, 0xFF, this);
            mCylAt.Set(M_cyl_src_at);
            mCylAt.SetStts(&mSttsAt);
            mSttsGapCo.Init(0xFF, 0xFF, this);
            mCylGapCo.Set(M_cyl_src_gap_co);
            mCylGapCo.SetStts(&mSttsGapCo);

            mCrushTimer = 0;
            mCrushState = 0;
            m85C = 0.0f;
            mScaleY = 1.0f;
            mAngleZ = 0.0f;
            mAngleX = 0.0f;
            mAngleSpeedZ = 0.0f;
            mAngleSpeedX = 0.0f;
            mVSpeed = 0.0f;
            mTargetHFrac = 0.0f;

            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
            attention_info.distances[fopAc_Attn_TYPE_MISC_e] = 0x2D;
            if (is_switch()) {
                mCurHFrac = 0.0f;
                mTopPos = -85.0f;
                mode_lower_init();
            } else {
                mCurHFrac = 1.0f;
                mTopPos = 0.0f;
                mode_upper_init();
            }
            register_list();
            mDoMtx_copy(mpModel->getBaseTRMtx(), mMtx);
            dComIfG_Bgsp()->Regist(mpBgW, this);
            phase_state = cPhs_COMPLEATE_e;
        }
    }
    return phase_state;
}

/* 00000964-00000A14       .text _delete__14daObjShmrgrd_cFv */
bool daObjShmrgrd_c::_delete() {
    if (heap != NULL && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
            mpBgW = NULL;
        }
    }
    leave_list();
    mSmokeCb.remove();
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00000A14-00000A48       .text search_target_next__14daObjShmrgrd_cFP14daObjShmrgrd_c */
daObjShmrgrd_c* daObjShmrgrd_c::search_target_next(daObjShmrgrd_c* target) {
    daObjShmrgrd_c* cur = M_list_p;
    daObjShmrgrd_c* rt = NULL;
    while (cur != NULL) {
        if (cur->mpNext == target) {
            rt = cur;
            break;
        }
        cur = cur->mpNext;
    }
    return rt;
}

/* 00000A48-00000AA4       .text register_list__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::register_list() {
    mpNext = NULL;
    if (M_list_p == NULL) {
        M_list_p = this;
    } else {
        daObjShmrgrd_c* last = search_target_next(NULL);
        if (last) {
            last->mpNext = this;
        }
    }
}

/* 00000AA4-00000B18       .text leave_list__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::leave_list() {
    daObjShmrgrd_c* prev = search_target_next(this);
    if (prev == NULL) {
        if (mpNext == NULL) {
            M_list_p = NULL;
        } else if (this == M_list_p) {
            M_list_p = mpNext;
        }
    } else {
        prev->mpNext = mpNext;
    }
}

/* 00000B18-00000C8C       .text search_gap__14daObjShmrgrd_cFv */
daObjShmrgrd_c* daObjShmrgrd_c::search_gap() {
    daObjShmrgrd_c* node = M_list_p;
    daObjShmrgrd_c* rt = NULL;
    while (node != NULL) {
        cXyz delta = node->current.pos - current.pos;
        if (node->get_mode() == 0) {
            f32 mag = delta.absXZ();
            if (mag <= 165.0f) {
                mDoMtx_stack_c::YrotS(shape_angle.y);
                cXyz calcVec;
                mDoMtx_stack_c::multVec(&cXyz::BaseZ, &calcVec);
                f32 prod = calcVec.inprodXZ(delta);
                if (prod > 0.0f || prod > 0.0f) {
                    rt = node;
                    break;
                }
            }
        }
        node = node->mpNext;
    }
    return rt;
}

/* 00000C8C-00000D2C       .text daObjShmrgrd_get_at_v__FP4cXyzP4cXyz */
void daObjShmrgrd_get_at_v(cXyz* out, cXyz* other) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz dir = player->current.pos - *other;
    *out = cXyz::Zero;
    if (dir.normalizeRS()) {
        *out = dir;
    }
}

/* 00000D2C-00000DF0       .text set_gap_co__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::set_gap_co() {
    daObjShmrgrd_c* gap = search_gap();
    if (gap) {
        cXyz pos = gap->current.pos - current.pos;
        pos *= 0.5f;
        pos += current.pos;
        mCylGapCo.SetC(pos);
        cXyz at_v;
        daObjShmrgrd_get_at_v(&at_v, &pos);
        mCylGapCo.SetAtVec(at_v);
        dComIfG_Ccsp()->Set(&mCylGapCo);
    }
}

/* 00000DF0-00000E2C       .text init_mtx__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000E2C-00000E98       .text set_mtx__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000E98-00000EF4       .text check_player_angle__14daObjShmrgrd_cFP10fopAc_ac_c */
BOOL daObjShmrgrd_c::check_player_angle(fopAc_ac_c* ac) {
    s16 angle = ac->shape_angle.y - cLib_targetAngleY(&ac->current.pos, &current.pos);
    BOOL rt = FALSE;
    if (angle > -0x2000 && angle < 0x2000) {
        rt = TRUE;
    }
    return rt;
}

/* 00000EF4-0000102C       .text set_damage__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::set_damage() {
    u8 attackState = daPy_getPlayerActorClass()->getCutType();
    M_damage = 0;
    M_damage_dir = 0;
    mSttsTg.Move();
    if (mCylTg.ChkTgHit()) {
        cCcD_Obj *hitObj = mCylTg.GetTgHitObj();
        fopAc_ac_c* hitActor = mCylTg.GetTgHitAc();
        if (hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER) && fopAcM_GetProfName(hitActor) == PROC_PLAYER) {
            if (check_player_angle(hitActor) && (attackState == 0x12 || attackState == 0x13)) {
                M_damage = 1;
            } else if (attackState == 0x11) {
                M_damage_dir = cM_atan2s(mCylTg.GetTgRVecP()->x, mCylTg.GetTgRVecP()->z);
                M_damage = 2;
            }
        }
        daObj::HitSeStart(&eyePos, current.roomNo, &mCylTg, 0x11);
        daObj::HitEff_hibana(this, &mCylTg);
        mCylTg.ClrTgHit();
    }
}

/* 0000102C-00001090       .text vib_start__14daObjShmrgrd_cFsf */
void daObjShmrgrd_c::vib_start(s16 dir, f32 mag) {
    mAngleSpeedZ = mag * attr().mVibMag0Mult * cM_scos(dir);
    mAngleSpeedX = mag * attr().mVibMag0Mult * cM_ssin(dir);
}

/* 00001090-00001108       .text vib_proc__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::vib_proc() {
    float angleAccelX = -(mAngleX * attr().mVibSpring) - mAngleSpeedX * attr().mAngleSpeedDecay;
    float angleAccelZ = -(mAngleZ * attr().mVibSpring) - mAngleSpeedZ * attr().mAngleSpeedDecay;

    mAngleSpeedZ += angleAccelZ;
    mAngleSpeedX += angleAccelX;
    mAngleZ += mAngleSpeedZ;
    mAngleX += mAngleSpeedX;
}

/* 00001108-00001114       .text crush_start__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::crush_start() {
    mCrushState = 1;
}

/* 00001114-00001178       .text crush_proc__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::crush_proc() {
    if (mCrushState == 1) {
        mScaleY = 0.2f;
        mCrushState = 2;
        mCrushTimer = attr().mCrushDuration;
    } else if (mCrushState == 2) {
        if (--mCrushTimer > 0) {
            return;
        }
        mScaleY = 1.0f;
        mCrushState = 0;
    }
}

/* 00001178-00001340       .text eff_crush__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::eff_crush() {
    if (mMode == MODE_UPPER) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_81B7, &current.pos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_81B8, &current.pos);
    }
    static const cXyz particle_scale(1.5f, 1.5f, 1.0f);
    JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2027, &current.pos, NULL, NULL, 200, &mSmokeCb, -1, NULL, NULL, &particle_scale);
    if (emitter) {
        emitter->setRate(30.0f);
        emitter->setMaxFrame(1);
        emitter->setLifeTime(45);
        emitter->setAwayFromCenterSpeed(0.0f);
        emitter->setAwayFromAxisSpeed(38.0f);
        static const JGeometry::TVec3<f32> vec(0.0f, 15.0f, 0.0f);
        emitter->setEmitterTranslation(vec);
    }
}

/* 00001340-000013FC       .text calc_top_pos__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::calc_top_pos() {
    float diff = mCurHFrac - mTargetHFrac;
    float decay = mCurHFrac > 0.0f && mCurHFrac < 1.0f
        ? attr().mIntVSpeedDecay
        : attr().mExtVSpeedDecay;

    mVSpeed -= diff * attr().mVSpring;
    mVSpeed -= mVSpeed * decay;
    mCurHFrac += mVSpeed;
    mCurHFrac = cLib_maxLimit(mCurHFrac, 1.0f);
    mTopPos = (1.0f - mCurHFrac) * -85.0f;
}

/* 000013FC-0000151C       .text jnodeCB__14daObjShmrgrd_cFP7J3DNodei */
BOOL daObjShmrgrd_c::jnodeCB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = (J3DModel*) j3dSys.getModel();
        daObjShmrgrd_c* i_this = (daObjShmrgrd_c*) model->getUserArea();
        J3DJoint* joint = (J3DJoint*) node;
        s32 jntNo = joint->getJntNo();

        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::transM(0.0f, (1.0f - i_this->mScaleY) * 20.0f, 0.0f);
        mDoMtx_stack_c::scaleM(1.0f, i_this->mScaleY, 1.0f);
        mDoMtx_stack_c::transM(0.0f, i_this->mTopPos, 0.0f);

        cXyz tmp(i_this->mAngleX, 1.0f, i_this->mAngleZ);
        Quaternion quat;
        daObj::quat_rotBaseY2(&quat, tmp);
        mDoMtx_stack_c::transM(0.0f, -20.0f, 0.0f);
        mDoMtx_stack_c::quatM(&quat);
        mDoMtx_stack_c::transM(0.0f, 20.0f, 0.0f);

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 0000151C-00001578       .text mode_upper_init__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_upper_init() {
    mCylTg.SetH(112.5f);
    mCylCo.SetH(112.5f);
    mTargetHFrac = 1.0f;
    mMode = MODE_UPPER;
}

/* 00001578-00001690       .text mode_upper__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_upper() {
    if (M_damage == 1) {
        mode_u_l_init();
    } else if (is_switch()) {
        mode_u_l_init();
    } else if (M_damage == 2) {
        vib_start(M_damage_dir, 1.0f);
        fopAcM_seStart(this, JA_SE_OBJ_HAMMER_SW_SWING, 0);
    }
}

/* 00001690-00001718       .text mode_u_l_init__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_u_l_init() {
    fopAcM_seStart(this, JA_SE_OBJ_HAMMER_SW_ON, 0);
    mTargetHFrac = 0.0f;
    mMode = MODE_U_L;
}

/* 00001718-0000179C       .text mode_u_l__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_u_l() {
    if (mCurHFrac <= 0.0f) {
        on_switch();
        mode_lower_init();
    }
}

/* 0000179C-000017C0       .text mode_lower_init__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_lower_init() {
    mTargetHFrac = 0.0f;
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
    mMode = MODE_LOWER;
}

/* 000017C0-000017C4       .text mode_lower__14daObjShmrgrd_cFv */
void daObjShmrgrd_c::mode_lower() {
}

/* 000017C4-000019D4       .text _execute__14daObjShmrgrd_cFv */
bool daObjShmrgrd_c::_execute() {
    typedef void (daObjShmrgrd_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjShmrgrd_c::mode_upper,
        &daObjShmrgrd_c::mode_u_l,
        &daObjShmrgrd_c::mode_lower,
    };

    set_damage();
    if (M_damage == 1) {
        crush_start();
        eff_crush();
    }

    (this->*mode_proc[mMode])();

    calc_top_pos();
    vib_proc();
    crush_proc();
    set_mtx();
    mCylTg.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCylTg);

    if (mMode == MODE_UPPER) {
        mCylCo.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCylCo);
        cXyz at_v;
        daObjShmrgrd_get_at_v(&at_v, &current.pos);
        mCylAt.SetAtVec(at_v);
        mCylAt.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCylAt);
        set_gap_co();
    }

    attention_info.position.y = current.pos.y + mTopPos + 125.0f;
    eyePos.y = current.pos.y + mTopPos + 75.0f;

    if (heap && mpBgW) {
        if (mpBgW->ChkUsed()) {
            mpBgW->Move();
        }
    }

    return true;
}

/* 000019D4-00001A74       .text _draw__14daObjShmrgrd_cFv */
bool daObjShmrgrd_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

namespace {
/* 00001A74-00001A94       .text Mthd_Create__29@unnamed@d_a_obj_shmrgrd_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<daObjShmrgrd_c*>(i_this)->_create();
}

/* 00001A94-00001AB8       .text Mthd_Delete__29@unnamed@d_a_obj_shmrgrd_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<daObjShmrgrd_c*>(i_this)->_delete();
}

/* 00001AB8-00001ADC       .text Mthd_Execute__29@unnamed@d_a_obj_shmrgrd_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<daObjShmrgrd_c*>(i_this)->_execute();
}

/* 00001ADC-00001B00       .text Mthd_Draw__29@unnamed@d_a_obj_shmrgrd_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<daObjShmrgrd_c*>(i_this)->_draw();
}

/* 00001B00-00001B08       .text Mthd_IsDelete__29@unnamed@d_a_obj_shmrgrd_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class Shmrgrd_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Shmrgrd = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Shmrgrd,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjShmrgrd_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Shmrgrd,
    /* Actor SubMtd */ &Shmrgrd_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
