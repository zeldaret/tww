/**
 * d_a_obj_leaves.cpp
 * Object - Pile of orange leaves (fades away when blown with Deku Leaf)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_leaves.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_vochi.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"

#if VERSION == VERSION_DEMO
#include "m_Do/m_Do_hostIO.h"

class daObjLeaves_HIO_c : public JORReflexible {
public:
    daObjLeaves_HIO_c();
    virtual ~daObjLeaves_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ u8 m20;
    /* 0x21 */ u8 m21;
    /* 0x22 */ u8 m22;
    /* 0x23 */ u8 m23;
    /* 0x24 */ u8 m24;
}; // size = 0x28

static daObjLeaves_HIO_c l_HIO;
#endif

namespace {
const char l_arcname[] = "Vochi";

#if VERSION <= VERSION_JPN
static const dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 90.0f,
    }},
};

static const dCcD_SrcCyl l_fire_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
        /* Radius */ 70.0f,
        /* Height */ 50.0f,
    }},
};
#endif
} // namespace

#if VERSION == VERSION_DEMO
daObjLeaves_HIO_c::daObjLeaves_HIO_c() {
    mNo = -1;
    m08 = 150.0f;
    m0C = 115.0f;
    m10 = 95.0f;
    m14 = 8.0f;
    m18 = 160.0f;
    m1C = 200.0f;
    m20 = 0;
    m21 = 0;
    m22 = 0;
    m23 = 0;
    m24 = 0;
}
#endif

#if VERSION >= VERSION_USA
namespace {
static const dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 150.0f,
    }},
};
} // namespace
#endif

/* 00000078-000000D8       .text chk_appear__13daObjLeaves_cFv */
bool daObjLeaves_c::chk_appear() {
    s32 switchIndex = param_get_swSave();
    bool ret = true;
    if (switchIndex != 0xff) {
        ret = fopAcM_isSwitch(this, switchIndex) == FALSE;
    }
    return ret;
}

#if VERSION == VERSION_DEMO
void daObjLeaves_c::setPEmitter(JPABaseEmitter* emitter) {
    m_emitter_p = emitter;
}
#endif

/* 000000D8-00000148       .text init_mtx__13daObjLeaves_cFv */
void daObjLeaves_c::init_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000148-000002E4       .text birthEffect__13daObjLeaves_cFiP4cXyzP5csXyzP8_GXColor */
void daObjLeaves_c::birthEffect(int arg1, cXyz* arg2, csXyz* arg3, GXColor* arg4) {
#if VERSION == VERSION_DEMO
    struct ParticleData {
        /* 0x00 */ u16 m00;
        /* 0x04 */ s32 m04;
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
    }; // size = 0x14

    static ParticleData particle_data[] = {
        {dPa_name::ID_SCENE_822F, 0, 0, -12.0f},
        {dPa_name::ID_SCENE_A230, 1, 0, -12.0f},
        {dPa_name::ID_SCENE_822E, 0, 0, -12.0f},
        {dPa_name::ID_SCENE_8268, 0, 60, -3.0f},
        {dPa_name::ID_SCENE_8269, 0, 60, -3.0f},
        {dPa_name::ID_SCENE_826A, 0, 0, -12.0f},
    };
#else
    struct ParticleData {
        /* 0x00 */ u16 m00;
        /* 0x04 */ s32 m04;
        /* 0x08 */ s32 m08;
        /* 0x0C */ s32 m0C;
        /* 0x10 */ f32 m10;
    }; // size = 0x14

    static ParticleData particle_data[] = {
        {dPa_name::ID_SCENE_822F, 0, 0, 1, -12.0f},
        {dPa_name::ID_SCENE_A230, 1, 0, 1, -12.0f},
        {dPa_name::ID_SCENE_822E, 0, 0, 1, -12.0f},
        {dPa_name::ID_SCENE_8268, 0, 60, 120, -3.0f},
        {dPa_name::ID_SCENE_8269, 0, 60, 120, -3.0f},
        {dPa_name::ID_SCENE_826A, 0, 0, 1, -12.0f},
    };
#endif

    if (arg1 < 0 || arg1 >= 6) {
        JUT_ASSERT(VERSION_SELECT(427, 424, 428, 428), FALSE);
        return;
    }

    ParticleData* particle = &particle_data[arg1];

    m438 = particle->m04;
    switch (particle->m04) {
    case 0:
#if VERSION == VERSION_DEMO
        m_emitter_p =
#endif
            dComIfGp_particle_set(particle->m00, arg2, arg3, NULL, 0xff, NULL, -1, arg4);
        break;

    case 1:
        mSmokeCallback.remove();
#if VERSION == VERSION_DEMO
        m_emitter_p = dComIfGp_particle_setToon(particle->m00, arg2, arg3, NULL, l_HIO.m18, &mSmokeCallback);
#else
        dComIfGp_particle_setToon(particle->m00, arg2, arg3, NULL, 0xa0, &mSmokeCallback);
#endif
        break;

    default:
        JUT_ASSERT(VERSION_SELECT(470, 464, 468, 468), FALSE);
        break;
    }

    m430 = particle->m08;
#if VERSION == VERSION_DEMO
    m40C = particle->m0C;
#else
    m434 = particle->m0C;
    m40C = particle->m10;
#endif
}

/* 000002E4-00000360       .text rideCallBack__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void rideCallBack(dBgW*, fopAc_ac_c* a_this, fopAc_ac_c* a_player) {
    daObjLeaves_c* i_this = (daObjLeaves_c*)a_this;

    if (fopAcM_GetName(a_player) == PROC_PLAYER) {
        daPy_py_c* player = (daPy_py_c*)a_player;
#if VERSION == VERSION_DEMO
        if (player->speedF >= l_HIO.m14) {
#else
        if (player->speedF >= 8.0f) {
#endif
            if (player->getFootOnGround()) {
                i_this->birthEffect(2, &player->current.pos, NULL, &i_this->tevStr.mColorK0);
#if VERSION == VERSION_DEMO
                i_this->setPEmitter(NULL);
#endif
            }
        }
    }
}

/* 00000360-00000384       .text solidHeapCB__13daObjLeaves_cFP10fopAc_ac_c */
BOOL daObjLeaves_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjLeaves_c*)a_this)->create_heap();
}

/* 00000384-00000494       .text create_heap__13daObjLeaves_cFv */
bool daObjLeaves_c::create_heap() {
    bool uVar5 = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, VOCHI_BDL_VOCHI);
    if (modelData == NULL) {
        JUT_ASSERT(VERSION_SELECT(550, 544, 548, 548), FALSE);
        uVar5 = false;
    } else {
        mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x31000202);
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, VOCHI_DZB_VOCHI), cBgW::MOVE_BG_e, &mModel->getBaseTRMtx());
        if (mModel == NULL || mpBgW == NULL) {
            uVar5 = false;
        } else {
            mpBgW->SetRideCallback(rideCallBack);
        }
    }
    return uVar5;
}

#if VERSION <= VERSION_JPN
bool daObjLeaves_c::checkCollision() {
    bool ret = false;

    if (mSph.ChkTgHit() != 0) {
        cCcD_Obj* hitObj = mSph.GetTgHitObj();

        if (hitObj != NULL) {
            u32 cVar5 = hitObj->GetAtType();
            switch (cVar5) {
            case AT_TYPE_WIND: {
                fopAc_ac_c* player = dComIfGp_getPlayer(0);
                s16 iVar3 = cM_atan2s(current.pos.x - player->current.pos.x, current.pos.z - player->current.pos.z);
                csXyz sp0C;
                sp0C.x = 0;
                sp0C.y = iVar3;
                sp0C.z = 0;
                birthEffect(0, &current.pos, &sp0C, &tevStr.mColorK0);
                birthEffect(1, &current.pos, &sp0C, NULL);
                fopAcM_seStartCurrent(this, JA_SE_OBJ_OCHIBA_BLOW, 0);
                ret = true;
                break;
            }
            case AT_TYPE_BOMB:
                birthEffect(5, &current.pos, NULL, &tevStr.mColorK0);
                fopAcM_seStartCurrent(this, JA_SE_OBJ_OCHIBA_BLOW, 0);
                ret = true;
                break;

            default:
                f32 abs = (*mSph.GetTgHitPosP() - current.pos).absXZ();
#if VERSION == VERSION_DEMO
                if (abs < l_HIO.m10)
#elif VERSION == VERSION_JPN
                if (abs < 95.0f)
#else
                if (abs < 110.0f)
#endif
                {
                    switch (cVar5) {
                    case AT_TYPE_HOOKSHOT:
                    case AT_TYPE_MACHETE:
                    case AT_TYPE_BOOMERANG:
                    case AT_TYPE_UNK8:
                    case AT_TYPE_SWORD:
                    case AT_TYPE_BOKO_STICK:
                    case AT_TYPE_UNK2000:
                    case AT_TYPE_SPIKE:
                    case AT_TYPE_UNK800:
                    case AT_TYPE_NORMAL_ARROW:
                    case AT_TYPE_LIGHT_ARROW:
                    case AT_TYPE_ICE_ARROW:
                    case AT_TYPE_DARKNUT_SWORD:
                    case AT_TYPE_UNK2000000:
                    case AT_TYPE_STALFOS_MACE:
                    case AT_TYPE_MOBLIN_SPEAR:
                        birthEffect(2, mSph.GetTgHitPosP(), NULL, &tevStr.mColorK0);
#if VERSION == VERSION_DEMO
                        m_emitter_p = NULL;
#endif
                        break;

                    case AT_TYPE_SKULL_HAMMER:
                        birthEffect(5, &current.pos, NULL, &tevStr.mColorK0);
                        fopAcM_seStartCurrent(this, JA_SE_OBJ_OCHIBA_BLOW, 0);
#if VERSION == VERSION_DEMO
                        m_emitter_p = NULL;
#endif
                        break;

                    case AT_TYPE_FIRE:
                    case AT_TYPE_FIRE_ARROW:
                    case AT_TYPE_UNK20000:
                        birthEffect(3, &current.pos, NULL, NULL);
                        birthEffect(4, &current.pos, NULL, NULL);
                        m538 = 1;
                        fopAcM_seStartCurrent(this, JA_SE_OBJ_OCHIBA_BURN, 0);
                        ret = true;
                        break;
                    }
                }
            }
        }

        mSph.ClrTgHit();
    }
    return ret;
}
#else
/* 00000494-000008C0       .text tg_hitCallback__13daObjLeaves_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjLeaves_c::tg_hitCallback(fopAc_ac_c* a_this, dCcD_GObjInf* arg1, fopAc_ac_c*, dCcD_GObjInf*) {
    daObjLeaves_c* i_this = (daObjLeaves_c*)a_this;
    cCcD_Obj* hitObj = arg1->GetTgHitObj();

    if (hitObj == NULL) {
        return;
    }

    u32 cVar5 = hitObj->GetAtType();
    switch (cVar5) {
    case AT_TYPE_WIND: {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        s16 iVar3 = cM_atan2s(a_this->current.pos.x - player->current.pos.x, a_this->current.pos.z - player->current.pos.z);
        csXyz sp0C;
        sp0C.x = 0;
        sp0C.y = iVar3;
        sp0C.z = 0;
        i_this->birthEffect(0, &a_this->current.pos, &sp0C, &a_this->tevStr.mColorK0);
        i_this->birthEffect(1, &a_this->current.pos, &sp0C, NULL);
        fopAcM_seStartCurrent(a_this, JA_SE_OBJ_OCHIBA_BLOW, 0);
        i_this->m44C = true;
        break;
    }
    case AT_TYPE_BOMB:
        i_this->birthEffect(5, &a_this->current.pos, NULL, &a_this->tevStr.mColorK0);
        fopAcM_seStartCurrent(a_this, JA_SE_OBJ_OCHIBA_BLOW, 0);
        i_this->m44C = true;
        break;

    default:
        f32 abs = (*i_this->mSph.GetTgHitPosP() - a_this->current.pos).absXZ();
        if (abs < 110.0f) {
            switch (cVar5) {
            case AT_TYPE_HOOKSHOT:
            case AT_TYPE_MACHETE:
            case AT_TYPE_BOOMERANG:
            case AT_TYPE_UNK8:
            case AT_TYPE_SWORD:
            case AT_TYPE_BOKO_STICK:
            case AT_TYPE_UNK2000:
            case AT_TYPE_SPIKE:
            case AT_TYPE_UNK800:
            case AT_TYPE_NORMAL_ARROW:
            case AT_TYPE_LIGHT_ARROW:
            case AT_TYPE_ICE_ARROW:
            case AT_TYPE_DARKNUT_SWORD:
            case AT_TYPE_UNK2000000:
            case AT_TYPE_STALFOS_MACE:
            case AT_TYPE_MOBLIN_SPEAR:
                i_this->birthEffect(2, i_this->mSph.GetTgHitPosP(), NULL, &a_this->tevStr.mColorK0);
                break;

            case AT_TYPE_SKULL_HAMMER:
                i_this->birthEffect(5, &a_this->current.pos, NULL, &a_this->tevStr.mColorK0);
                fopAcM_seStartCurrent(i_this, JA_SE_OBJ_OCHIBA_BLOW, 0);
                break;

            case AT_TYPE_FIRE:
            case AT_TYPE_FIRE_ARROW:
            case AT_TYPE_UNK20000:
                i_this->birthEffect(3, &a_this->current.pos, NULL, NULL);
                i_this->birthEffect(4, &a_this->current.pos, NULL, NULL);
                fopAcM_seStartCurrent(a_this, JA_SE_OBJ_OCHIBA_BURN, 0);
                i_this->m44C = true;
                break;
            }
        }
    }
}
#endif

#if VERSION <= VERSION_JPN
void daObjLeaves_c::registFireCollision() {
    if (m538 == 1) {
        mStts.Move();
        dComIfG_Ccsp()->Set(&mCyl);
    }
}
#endif

/* 000008C0-00000B08       .text _create__13daObjLeaves_cFv */
cPhs_State daObjLeaves_c::_create() {
    cPhs_State PVar4 = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjLeaves_c);

    if (base.mInitState == 0) {
        m43C = chk_appear();
    }

    if (m43C == true) {
        PVar4 = dComIfG_resLoad(&mPhase, l_arcname);
    }

    if (PVar4 == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xC20) == true) {
            if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                PVar4 = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mModel->getBaseTRMtx());
                init_mtx();
                mStts.Init(0xff, 0xff, this);
                mSph.Set(l_sph_src);
                mSph.SetStts(&mStts);
#if VERSION == VERSION_DEMO
                mSph.SetC(current.pos.x, current.pos.y - 115.0f, current.pos.z);
#else
                cXyz sp08(current.pos.x, current.pos.y - 115.0f, current.pos.z);
                mSph.SetC(sp08);
#if VERSION >= VERSION_USA
                mSph.SetR(150.0f);
#endif
#endif
#if VERSION <= VERSION_JPN
                mCyl.Set(l_fire_cyl_src);
                mCyl.SetStts(&mStts);
                mCyl.SetC(current.pos);
#endif
#if VERSION > VERSION_JPN
                mSph.SetTgHitCallback(tg_hitCallback);
#endif
                m408 = 255.0f;
                mMemberFunc = &daObjLeaves_c::wait_proc;
                mSmokeCallback.setTevStr(&tevStr);
                mSmokeCallback.setRateOff(0);
                mSmokeCallback.setFollowOff();
            }
        } else {
            PVar4 = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("落ち葉", &l_HIO);
    }
#endif
    return PVar4;
}

/* 00000CC0-00000D74       .text _delete__13daObjLeaves_cFv */
bool daObjLeaves_c::_delete() {
    if (m43C == true) {
        dComIfG_resDelete(&mPhase, l_arcname);
#if VERSION == VERSION_DEMO
        if (mMemberFunc != &daObjLeaves_c::wait_proc && m438 == 1)
#endif
        {
            mSmokeCallback.remove();
        }
#if VERSION > VERSION_DEMO
        if (heap != NULL && mpBgW != NULL)
#else
        if (mpBgW != NULL)
#endif
        {
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
#if VERSION > VERSION_DEMO
            mpBgW = NULL;
#endif
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif

    return true;
}

/* 00000D74-00000E84       .text wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::wait_proc() {
#if VERSION == VERSION_DEMO
    mSph.SetR(l_HIO.m08);
    mSph.SetC(current.pos.x, current.pos.y - l_HIO.m0C, current.pos.z);
#endif
    mpBgW->Move();
    mStts.Move();

#if VERSION <= VERSION_JPN
    if (!checkCollision())
#else
    mSph.ClrTgHit();
    if (!m44C)
#endif
    {
        dComIfG_Ccsp()->Set(&mSph);
    } else {
        param_on_swSave();
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);

        if (mpBgW != NULL && mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }

#if VERSION == VERSION_DEMO
        if (m_emitter_p != NULL)
#endif
        {
            mMemberFunc = &daObjLeaves_c::alpha_calc_start_wait_proc;
        }
#if VERSION == VERSION_DEMO
        else
        {
            mMemberFunc = &daObjLeaves_c::item_set_wait_proc;
        }
#endif
    }
}

/* 00000E84-00000EB4       .text alpha_calc_start_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::alpha_calc_start_wait_proc() {
#if VERSION == VERSION_DEMO
    registFireCollision();
    JUT_ASSERT(908, m_emitter_p != NULL);

    if (m_emitter_p->getFrame() >= m430) {
        mMemberFunc = &daObjLeaves_c::item_set_wait_proc;
    }
#elif VERSION == VERSION_JPN
    registFireCollision();
    if (m430 <= 0) {
        mMemberFunc = &daObjLeaves_c::item_set_wait_proc;
    }
#endif

#if VERSION > VERSION_JPN
    if (m430 <= 0) {
        mMemberFunc = &daObjLeaves_c::item_set_wait_proc;
    }
#endif
}

/* 00000EB4-00000FB8       .text item_set_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::item_set_wait_proc() {
#if VERSION <= VERSION_JPN
    registFireCollision();
#endif
    m408 += m40C;
#if VERSION == VERSION_DEMO
    if (m408 <= l_HIO.m1C)
#else
    if (m408 <= 200.0f)
#endif
    {
        s32 item = param_get_itemNo();
        s32 itemSaveBit = param_get_itemSaveBitNo();

        cXyz sp10 = current.pos;
        csXyz angle(0, 0, 0);

        sp10.y -= 30.0f;
        fopAcM_createItemFromTable(&sp10, item, itemSaveBit, fopAcM_GetHomeRoomNo(this), 0, &angle, 1, NULL);
#if VERSION == VERSION_DEMO
        if (m_emitter_p != NULL)
#endif
        {
            mMemberFunc = &daObjLeaves_c::retire_wait_proc;
        }
#if VERSION == VERSION_DEMO
        else
        {
            mMemberFunc = &daObjLeaves_c::retire_wait_without_particle_proc;
        }
#endif
    }
}

/* 00000FB8-00001010       .text retire_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::retire_wait_proc() {
#if VERSION <= VERSION_JPN
    registFireCollision();
#endif
#if VERSION == VERSION_DEMO
    JUT_ASSERT(961, m_emitter_p != NULL);
#endif

#if VERSION == VERSION_DEMO
    m408 += m40C;
    if (m408 <= 0.0f) {
        m408 = 0.0f;
        if (m_emitter_p->isEnableDeleteEmitter()) {
            fopAcM_delete(this);
            m_emitter_p = NULL;
            m538 = 0;
        }
    }
#else
    m408 += m40C;
    if (m408 <= 0.0f) {
        m408 = 0.0f;
        if (m434 <= 0) {
            fopAcM_delete(this);
#if VERSION == VERSION_JPN
            m538 = 0;
#endif
        }
    }
#endif
}

#if VERSION == VERSION_DEMO
void daObjLeaves_c::retire_wait_without_particle_proc() {
    registFireCollision();
    m408 += m40C;
    if (m408 <= 0.0f) {
        m408 = 0.0f;
        fopAcM_delete(this);
        m_emitter_p = NULL;
        m538 = 0;
    }
}
#endif

/* 00001010-0000107C       .text _execute__13daObjLeaves_cFv */
bool daObjLeaves_c::_execute() {
#if VERSION >= VERSION_JPN
    m430--;
    if (m430 <= 0) {
        m430 = 0;
    }

    m434--;
    if (m434 <= 0) {
        m434 = 0;
    }
#endif
    (this->*mMemberFunc)();
    return true;
}

/* 0000107C-000011B0       .text set_material_sub__FP11J3DMaterialUc */
void set_material_sub(J3DMaterial* material, unsigned char alpha) {
    while (material != NULL) {
        if (alpha == 0) {
            material->getShape()->hide();
        } else {
            material->getShape()->show();
            if (alpha != 0xFF) {
                material->setMaterialMode(4);
                material->getZMode()->setUpdateEnable(0);
                material->getBlend()->setType(1);
                material->getBlend()->setSrcFactor(4);
                material->getBlend()->setDstFactor(5);
            }
            material->getTevKColor(3)->mColor.a = alpha;
        }

        material = material->getNext();
    }
}

/* 000011B0-00001218       .text set_material__FP8J3DModelUc */
void set_material(J3DModel* model, unsigned char alpha) {
    J3DModelData* modelData = model->getModelData();
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        set_material_sub(modelData->getJointNodePointer(i)->getMesh(), alpha);
    }
}

/* 00001218-00001290       .text _draw__13daObjLeaves_cFv */
bool daObjLeaves_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    set_material(mModel, m408);
    mDoExt_modelUpdateDL(mModel);
    return true;
}

/* 00001290-000012B0       .text daObjLeaves_Create__FP13daObjLeaves_c */
static cPhs_State daObjLeaves_Create(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_create();
}

/* 000012B0-000012D4       .text daObjLeaves_Delete__FP13daObjLeaves_c */
static BOOL daObjLeaves_Delete(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_delete();
}

/* 000012D4-000012F8       .text daObjLeaves_Execute__FP13daObjLeaves_c */
static BOOL daObjLeaves_Execute(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_execute();
}

/* 000012F8-0000131C       .text daObjLeaves_Draw__FP13daObjLeaves_c */
static BOOL daObjLeaves_Draw(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_draw();
}

/* 0000131C-00001324       .text daObjLeaves_IsDelete__FP13daObjLeaves_c */
static BOOL daObjLeaves_IsDelete(daObjLeaves_c*) {
    return TRUE;
}

static actor_method_class l_daObjLeaves_Method = {
    (process_method_func)daObjLeaves_Create,
    (process_method_func)daObjLeaves_Delete,
    (process_method_func)daObjLeaves_Execute,
    (process_method_func)daObjLeaves_IsDelete,
    (process_method_func)daObjLeaves_Draw,
};

actor_process_profile_definition g_profile_Obj_Leaves = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Leaves,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjLeaves_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Leaves,
    /* Actor SubMtd */ &l_daObjLeaves_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_3_e,
};
