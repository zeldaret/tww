/**
 * d_a_obj_ice.cpp
 * Object - Block of ice (blocks treasure chests, enemies, rupees, etc.)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ice.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_rain.h"
#include "d/d_priority.h"
#include "d/d_procname.h"
#include "d/res/res_ikori.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_hostIO.h"

#if VERSION == VERSION_DEMO
class daObjIce_HIO_c : public JORReflexible {
public:
    daObjIce_HIO_c();
    virtual ~daObjIce_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ u8 m38;
    /* 0x39 */ u8 m39;
    /* 0x3A */ u8 m3A;
    /* 0x3B */ u8 m3B;
}; // size = 0x3C

static daObjIce_HIO_c l_HIO;
#endif

namespace {
static const char l_arcname[] = "Ikori";
static const f32 l_co_radius_table[] = {40.0f, 65.0f, 75.0f};
static const f32 l_co_height_table[] = {120.0f, 90.0f, 60.0f};
static const dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 65.0f,
        /* Height */ 140.0f,
    }},
};
} // namespace

#if VERSION == VERSION_DEMO
daObjIce_HIO_c::daObjIce_HIO_c() {
    mNo = -1;
    m08 = 40.0f;
    m0C = 120.0f;
    m10 = 65.0f;
    m14 = 90.0f;
    m18 = 75.0f;
    m1C = 60.0f;
    m20 = 1.0f;
    m24 = 0.0009f;
    m28 = 80.0f;
    m2C = 150.0f;
    m30 = 1.8f;
    m34 = 0.5f;
    m38 = 0;
    m39 = 0;
    m3A = 0;
    m3B = 1;
}
#endif

/* 00000078-000000F0       .text chk_appear__10daObjIce_cFv */
u8 daObjIce_c::chk_appear() {
    s32 switchIndex = param_get_swSave();
    u8 uVar2 = 0;
    if (switchIndex != 0xFF) {
        if (!fopAcM_isSwitch(this, switchIndex)) {
            uVar2 = 1;
        }
    } else {
        uVar2 = 1;
    }
    return uVar2;
}

/* 000000F0-0000018C       .text set_mtx__10daObjIce_cFv */
void daObjIce_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::scaleM(m44C, m450, m44C);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    cMtx_copy(mDoMtx_stack_c::get(), m40C);
}

/* 0000018C-000001C8       .text init_mtx__10daObjIce_cFv */
void daObjIce_c::init_mtx() {
    mModel->setBaseScale(scale);
    set_mtx();
}

/* 000001C8-000001EC       .text solidHeapCB__10daObjIce_cFP10fopAc_ac_c */
BOOL daObjIce_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjIce_c*)a_this)->create_heap();
}

/* 000001EC-000002E4       .text create_heap__10daObjIce_cFv */
bool daObjIce_c::create_heap() {
    bool uVar5 = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, IKORI_BDL_VICE);

    if (modelData == NULL) {
        JUT_ASSERT(DEMO_SELECT(392, 395), FALSE);
        uVar5 = false;
    } else {
        mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);

        cBgD_t* pcVar3 = (cBgD_t*)dComIfG_getObjectRes(l_arcname, IKORI_DZB_VICE);
        mBgw = dBgW_NewSet(pcVar3, cBgW::MOVE_BG_e, &m40C);

        if (mModel == NULL || mBgw == NULL) {
            uVar5 = false;
        }
    }
    return uVar5;
}

/* 000002E4-000005F4       .text tg_hitCallback__10daObjIce_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjIce_c::tg_hitCallback(fopAc_ac_c* a_this, dCcD_GObjInf* arg1, fopAc_ac_c* arg2, dCcD_GObjInf* arg3) {
    daObjIce_c* i_this = (daObjIce_c*)a_this;
    cCcD_Obj* pcVar8 = arg1->GetTgHitObj();

    if (pcVar8 != NULL) {
        f32 x2;
        f32 y;
        f32 z2;
        cXyz sp20 = i_this->current.pos;
        cXyz* pPos = arg1->GetTgHitPosP();
        s16 idx = -i_this->shape_angle.y;
        f32 sin = cM_ssin(idx);
        f32 cos = cM_scos(idx);
        f32 x = pPos->x - sp20.x;
        f32 z = pPos->z - sp20.z;

        x2 = x * cos + z * sin;
        y = pPos->y - sp20.y;
        z2 = -x * sin + z * cos;
        i_this->m45C = 0;

        for (s32 i = 0; i < 3; i++) {
            f32 fVar6 = i_this->m44C * (i_this->scale.x * l_co_radius_table[i]);
            f32 fVar7 = i_this->m450 * (i_this->scale.y * l_co_height_table[i]);
            f32 fVar5 = i_this->m44C * (i_this->scale.z * l_co_radius_table[i]);
            if (y < fVar7 && (SQUARE(x2) / SQUARE(fVar6) + SQUARE(z2) / SQUARE(fVar5) < 1.0f)) {
                switch (pcVar8->GetAtType()) {
                case AT_TYPE_UNK20000:
                case AT_TYPE_FIRE:
                case AT_TYPE_FIRE_ARROW:
                    i_this->m45C = 2;
                    break;

                default: {
#if VERSION == VERSION_DEMO
                    i_this->m44C -= l_HIO.m24;
#else
                    i_this->m44C -= 0.0009f;
#endif
                    if (i_this->m44C < 0.0f) {
                        i_this->m44C = 0.0f;
                    }
                    i_this->m450 = 1.0f - cM_scos(i_this->m44C * 16384.0f);
                    if (i_this->m44C < 0.1f) {
                        i_this->m45C = 1;
                    }
                    csXyz sp18(0, 0, 0);
                    sp18.x = cM_atan2s(-pPos->y + i_this->current.pos.y, pPos->z - i_this->current.pos.z);
                    sp18.y = cM_atan2s(pPos->x - i_this->current.pos.x, pPos->z - i_this->current.pos.z);
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0465, pPos, &sp18, NULL, 0xFF, NULL, -1, &i_this->tevStr.mColorK0);
                    break;
                }
                case AT_TYPE_BOMB:
                    break;
                }
            }

            if (i_this->m45C != 0) {
                arg1->OnTgNoConHit();
                break;
            }
        }
    }
}

/* 000005F4-000008C0       .text _create__10daObjIce_cFv */
cPhs_State daObjIce_c::_create() {
    cPhs_State ret = cPhs_ERROR_e;
    fopAcM_SetupActor(this, daObjIce_c);

    if (fopAcM_IsFirstCreating(this)) {
        m448 = chk_appear();
    }

    if (m448 == 1) {
        ret = dComIfG_resLoad(&mPhase, l_arcname);
    }

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x1A20)) {
            if (dComIfG_Bgsp()->Regist(mBgw, this)) {
                ret = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mModel->getBaseTRMtx());
                m44C = 1.0f;
                m450 = 1.0f;
                init_mtx();

                f32 fVar1 = scale.x;
                if (fVar1 < scale.z) {
                    fVar1 = scale.z;
                }

                mStts.Init(0xFF, 0xFF, this);
                mCyl.Set(l_cyl_src);
                mCyl.SetStts(&mStts);
                mCyl.SetC(current.pos);
                mCyl.SetR(fVar1 * 75.0f);
                mCyl.SetH(scale.y * 120.0f);

                mCyl.OnTgNoAtHitInfSet();
                mCyl.SetTgHitCallback(tg_hitCallback);
                m454 = 255.0f;
                fopAcM_setCullSizeBox(this, scale.x * -80.0f, 0.0f, scale.z * -80.0f, scale.x * 80.0f, scale.y * 150.0f, scale.z * 80.0f);
                attention_info.position.x = current.pos.x;
                attention_info.position.y = current.pos.y + scale.y * 60.0f;
                attention_info.position.z = current.pos.z;
                eyePos = attention_info.position;
                m43C = &daObjIce_c::wait_act_proc;
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }

#if VERSION == VERISON_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("汎用氷", &l_HIO);
    }
#endif

    return ret;
}

/* 00000A78-00000B18       .text _delete__10daObjIce_cFv */
bool daObjIce_c::_delete() {
    if (m448 == 1) {
        dComIfG_resDelete(&mPhase, l_arcname);
#if VERSION > VERISON_DEMO
        if (heap != NULL && mBgw != NULL) {
#else
        if (mBgw != NULL) {
#endif
            if (mBgw->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBgw);
            }
#if VERSION > VERSION_DEMO
            mBgw = NULL;
#endif
        }
    }

#if VERSION == VERISON_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif
    return true;
}

/* 00000B18-00000CA4       .text wait_act_proc__10daObjIce_cFv */
void daObjIce_c::wait_act_proc() {
    if (!mCyl.ChkTgHit() || mStts.GetTgApid() != mStts.GetTgOldApid()) {
        mCyl.OffAtNoConHit();
    }

    mStts.Move();
    mCyl.ClrTgHit();

    switch (m45C) {
    case 2:
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ICE_ROCK_MELT, 0);

    case 1: {
        m458 = 0x5a;
        JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_COMMON_0464, &current.pos, NULL, &scale, 0xFF, NULL, -1, &tevStr.mColorK0);
        if (emitter != NULL) {
#if VERSION == VERSION_DEMO
            JGeometry::TVec3<f32> s;
            s.set(scale.x, scale.y, scale.z);
#else
            JGeometry::TVec3<f32> s;
            s.set(scale);
#endif
            emitter->setGlobalDynamicsScale(s);
            s.x = scale.x;
            s.y = scale.x;
            s.z = scale.x;
            emitter->setGlobalParticleScale(s);
        }

        m43C = &daObjIce_c::fade_out_retire_act_proc;
        break;
    }
    default:
#if VERSION == VERSION_DEMO
        if (l_HIO.m3B == 1) {
            dComIfG_Ccsp()->Set(&mCyl);
        }

        if (l_HIO.m38 == 1) {
            if (mBgw != NULL && mBgw->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBgw);
            }
            m458 = 0x5A;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0464, &current.pos, NULL, &scale, 0xFF, NULL, -1, &tevStr.mColorK0);
            m43C = &daObjIce_c::fade_out_retire_act_proc;
        }
#else
        dComIfG_Ccsp()->Set(&mCyl);
#endif
        break;
    }
}

/* 00000CA4-00000DFC       .text fade_out_retire_act_proc__10daObjIce_cFv */
void daObjIce_c::fade_out_retire_act_proc() {
    f32 tmp2 = m44C;
    m454 -= 2.8333333f;
    tmp2 -= 0.011111111f;
    if (tmp2 < 0.0f) {
        tmp2 = 0.0f;
    }

    if (m454 < 0.0f) {
        m454 = 0.0f;
    }

    f32 tmp3 = 1.0f - cM_scos(tmp2 * 16384.0f);

    m44C = tmp2;
    m450 = tmp3;

    if (m44C < 0.4f && mBgw != NULL) {
        if (mBgw->ChkUsed()) {
            dComIfG_Bgsp()->Release(mBgw);
            param_on_swSave();
        }
    }

    m458--;
    if (m458 <= 0) {
        fopAcM_delete(this);
    }
}

/* 00000DFC-00000EB8       .text _execute__10daObjIce_cFv */
bool daObjIce_c::_execute() {
#if VERSION == VERSION_DEMO
    if (l_HIO.m3A == 1) {
        scale.setall(l_HIO.m20);
        mModel->setBaseScale(scale);
        mCyl.SetR(l_HIO.m18 * l_HIO.m20 * m44C);
        mCyl.SetH(l_HIO.m0C * l_HIO.m20 * m450);
        fopAcM_setCullSizeBox(this, -l_HIO.m28 * scale.x, 0.0f, -l_HIO.m28 * scale.z, l_HIO.m28 * scale.x, l_HIO.m2C * scale.y, l_HIO.m28 * scale.z);
    } else {
        mCyl.SetR(m44C * (l_HIO.m18 * scale.x));
        mCyl.SetH(m450 * (l_HIO.m0C * scale.y));
    }
#else
    mCyl.SetR(m44C * (scale.x * 75.0f));
    mCyl.SetH(m450 * (scale.y * 120.0f));
#endif
    set_mtx();

    if (mBgw != NULL && mBgw->ChkUsed()) {
        mBgw->Move();
    }
    (this->*m43C)();
    return true;
}

/* 00000EB8-00000F48       .text set_material_sub__FP11J3DMaterialUc */
void set_material_sub(J3DMaterial* material, unsigned char alpha) {
    while (material != NULL) {
        if (alpha == 0) {
            material->getShape()->hide();
        } else {
            material->getShape()->show();
            material->getTevKColor(3)->mColor.a = alpha;
        }
        material = material->getNext();
    }
}

/* 00000F48-00000FB0       .text set_material__FP8J3DModelUc */
void set_material(J3DModel* model, unsigned char alpha) {
    J3DModelData* modelData = model->getModelData();
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        set_material_sub(modelData->getJointNodePointer(i)->getMesh(), alpha);
    }
}

/* 00000FB0-00001070       .text _draw__10daObjIce_cFv */
bool daObjIce_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    dComIfGd_setListMaskOff();
    set_material(mModel, m454);
    setEffectMtx();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();
    return true;
}

/* 00001070-000013A0       .text setEffectMtx__10daObjIce_cFv */
void daObjIce_c::setEffectMtx() {
    static Mtx mtx_adj = {
        {0.5f, 0.0f, 0.0f, 0.5f},
        {0.0f, -0.5f, 0.0f, 0.5f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };

    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    cXyz sp2C;
    cXyz sp20;
    cXyz sp14;
    cXyz* eye = &eyePos;
#if VERSION == VERSION_DEMO
    f32 fVar2 = l_HIO.m30 / scale.x;
    f32 fVar3 = l_HIO.m30 / scale.y;
#else
    f32 fVar2 = 1.8f / scale.x;
    f32 fVar3 = 1.8f / scale.y;
#endif
    camera_class* camera = dCam_getCamera();

    sp2C = *eye - camera->mLookat.mEye;
    dKyr_get_vectle_calc(&tevStr.mLightPosWorld, eye, &sp20);
    C_VECHalfAngle(&sp2C, &sp20, &sp14);
    C_MTXLookAt(sp98, &cXyz::Zero, &cXyz::BaseY, &sp14);

    mDoMtx_stack_c::scaleS(fVar2, fVar3, 1.0f);
    mDoMtx_stack_c::concat(mtx_adj);
    mDoMtx_stack_c::concat(sp98);
    mDoMtx_stack_c::get()[0][3] = 0.0f;
    mDoMtx_stack_c::get()[1][3] = 0.0f;
    mDoMtx_stack_c::get()[2][3] = 0.0f;
    cMtx_copy(mDoMtx_stack_c::get(), sp68);
#if VERSION == VERSION_DEMO
    mDoMtx_stack_c::scaleS(l_HIO.m34, l_HIO.m34, 1.0f);
#else
    mDoMtx_stack_c::scaleS(0.5f, 0.5f, 1.0f);
#endif
    mDoMtx_stack_c::concat(mtx_adj);
    mDoMtx_stack_c::concat(sp98);
    mDoMtx_stack_c::get()[0][3] = 0.0f;
    mDoMtx_stack_c::get()[1][3] = 0.0f;
    mDoMtx_stack_c::get()[2][3] = 0.0f;
    cMtx_copy(mDoMtx_stack_c::get(), sp38);

    J3DModelData* modelData = this->mModel->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* material = modelData->getMaterialNodePointer(i);
        for (u32 j = 0; j < 8; j++) {
            J3DTexGenBlock* genBlock = material->getTexGenBlock();
            J3DTexMtx* mtx = genBlock->getTexMtx(j);
            if (mtx != NULL) {
                J3DTexMtxInfo& mtxInfo = mtx->getTexMtxInfo();
                switch (mtxInfo.mInfo) {
                case 10:
                case 11:
                    switch (i) {
                    case 1:
                        mtxInfo.setEffectMtx(sp68);
                        break;
                    case 0:
                        mtxInfo.setEffectMtx(sp38);
                        break;
                    }
                    break;
                }
            }
        }
    }
}

/* 000013A0-000013C0       .text daObjIce_Create__FP10fopAc_ac_c */
static cPhs_State daObjIce_Create(fopAc_ac_c* i_this) {
    return ((daObjIce_c*)i_this)->_create();
}

/* 000013C0-000013E4       .text daObjIce_Delete__FP10daObjIce_c */
static BOOL daObjIce_Delete(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_delete();
}

/* 000013E4-00001408       .text daObjIce_Execute__FP10daObjIce_c */
static BOOL daObjIce_Execute(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_execute();
}

/* 00001408-0000142C       .text daObjIce_Draw__FP10daObjIce_c */
static BOOL daObjIce_Draw(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_draw();
}

/* 0000142C-00001434       .text daObjIce_IsDelete__FP10daObjIce_c */
static BOOL daObjIce_IsDelete(daObjIce_c*) {
    return TRUE;
}

static actor_method_class l_daObjIce_Method = {
    (process_method_func)daObjIce_Create,
    (process_method_func)daObjIce_Delete,
    (process_method_func)daObjIce_Execute,
    (process_method_func)daObjIce_IsDelete,
    (process_method_func)daObjIce_Draw,
};

actor_process_profile_definition g_profile_Obj_Ice = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ice,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjIce_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ice,
    /* Actor SubMtd */ &l_daObjIce_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
