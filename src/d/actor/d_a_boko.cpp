/**
 * d_a_boko.cpp
 * Object - Enemy weapons
 */

#include "d/actor/d_a_boko.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_s_lin_chk.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_2100_2080.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

u32 daBoko_c::m_bound_se[6] = {
    JA_SE_CM_BOKOBOU_BOUND,
    JA_SE_CM_NATA_BOUND,
    JA_SE_OBJ_ST_CLUB_FALL,
    JA_SE_OBJ_TN_SWORD_FALL,
    JA_SE_CM_LANCE_BOUND,
    JA_SE_OBJ_TN_SWORD_FALL
};

s32 daBoko_c::m_heap_size[6] = {
    0x2300,
    0x1240,
    0x1240,
    0x1240,
    0x4200,
    0x2000
};

char* daBoko_c::m_arc_name[6] = {
    "Boko",  /* Boko stick */
    "Nata",  /* Bokoblin machete */
    "Club",  /* Stalfos mace/club */
    "Tkwn",  /* Darknut sword */
    "Spear", /* Moblin spear */
    "Pgsw"   /* Phantom Ganon's sword */
};

Vec daBoko_c::m_cull_min[6] = {
    {
        -20.0f,
        -10.0f,
        -95.0f,
    },
    {
        -20.0f,
        -10.0f,
        -95.0f,
    },
    {
        -35.0f,
        -35.0f,
        -125.0f,
    },
    {
        -45.0f,
        -10.0f,
        -145.0f,
    },
    {
        -20.0f,
        -20.0f,
        -180.0f,
    },
    {
        -50.0f,
        -20.0f,
        -140.0f,
    },
};

Vec daBoko_c::m_cull_max[6] = {
    {
        20.0f,
        10.0f,
        95.0f,
    },
    {
        20.0f,
        10.0f,
        95.0f,
    },
    {
        35.0f,
        35.0f,
        120.0f,
    },
    {
        45.0f,
        10.0f,
        130.0f,
    },
    {
        20.0f,
        20.0f,
        200.0f,
    },
    {
        50.0f,
        20.0f,
        120.0f,
    },
};

static cXyz l_break_particle_offset(0.0f, 0.0f, 30.0f);
dBgS_ObjGndChk daBoko_c::m_ground_check;
dBgS_ObjLinChk daBoko_c::m_line_check;

static dCcD_SrcSph sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK20000,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_WATER | AT_TYPE_FIRE | AT_TYPE_UNK20000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoHitMark_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,

    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 20.0f,
    },
};

static dCcD_SrcCps at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOKO_STICK,
        /* SrcObjAt  Atp     */ 0x01,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IGrpAll_e,
        /* SrcGObjAt Se      */ dCcG_SE_UNK1,
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
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 20.0f,
    },
};

const s16 daBoko_HIO_c0::throw_timer = 2;
const f32 daBoko_HIO_c0::throw_speed = 70.0f;

static daBoko_HIO_c l_HIO;

/* 000000EC-0000017C       .text keDraw__8daBoko_cFv */
void daBoko_c::keDraw() {
    GXColor color = {0xFF, 0x64, 0x00, 0xFF};
    mpLineMat->update(0xA, 1.25f, color, 2, &tevStr);
    dComIfGd_set3DlineMat(mpLineMat);
}

/* 0000017C-00000620       .text keCalc1__8daBoko_cFP6ke_c_si */
void daBoko_c::keCalc1(ke_c_s*, int) {
    /* Nonmatching */
}

/* 000009DC-00000B2C       .text keCalc__8daBoko_cFv */
void daBoko_c::keCalc() {
    /* Nonmatching */
}

/* 00000B2C-00000DC4       .text draw__8daBoko_cFv */
BOOL daBoko_c::draw() {
    /* Nonmatching */
}

/* 00000DC4-00000DE4       .text daBoko_Draw__FP8daBoko_c */
static BOOL daBoko_Draw(daBoko_c* i_this) {
    return i_this->draw();
}

/* 00000DE4-00000EB0       .text setTopRootPos__8daBoko_cFi */
void daBoko_c::setTopRootPos(int) {
    /* Nonmatching */
}

/* 00000EB0-00000F60       .text setBaseMatrix__8daBoko_cFv */
void daBoko_c::setBaseMatrix() {
    /* Nonmatching */
}

/* 00000F60-00000FA4       .text checkNoDraw__8daBoko_cFv */
BOOL daBoko_c::checkNoDraw() {
    return m2B9 || mCurrentAction == 4 || (mCurrentAction == 3 && dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80_e));
}

/* 00000FA4-00001340       .text setFlameEffect__8daBoko_cFv */
void daBoko_c::setFlameEffect() {
    /* Nonmatching */
}

/* 00001340-000013CC       .text setRoomInfo__8daBoko_cFv */
void daBoko_c::setRoomInfo() {
    int roomNo;
    if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
        roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    } else {
        roomNo = dComIfGp_roomControl_getStayNo();
    }
    current.roomNo = tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
}

/* 000013CC-0000155C       .text setThrowReverse__8daBoko_cFs */
void daBoko_c::setThrowReverse(s16) {
    /* Nonmatching */
}

/* 0000155C-000015E0       .text procWait_init__8daBoko_cFv */
BOOL daBoko_c::procWait_init() {
    speedF = 0.0f;
    m2C0 = 0;
    m2C2 = 0;
    mCurrentProc = &daBoko_c::procWait;
    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    mCurrentAction = 0;
    fopAcM_cancelCarryNow(this);
    gravity = -3.0f;
    return TRUE;
}

/* 000015E0-000016E4       .text procWait__8daBoko_cFv */
BOOL daBoko_c::procWait() {
    if (fopAcM_checkCarryNow(this)) {
        gravity = 0.0f;
        mCurrentProc = &daBoko_c::procCarry;
        speedF = 0.0f;
        speed = cXyz::Zero;
        if (mCurrentAction != 3) {
            mCurrentAction = 2;
        }
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        m2BC = 0;
        procCarry();
    } else if (m2BC == 0) {
        fopAcM_posMoveF(this, NULL);
        mAcch.CrrPos(*dComIfG_Bgsp());
        if (!mAcch.ChkGroundHit()) {
            procMove_init();
        }
        setRoomInfo();
        setBaseMatrix();
    }
    return TRUE;
}

/* 000016E4-0000175C       .text procMove_init__8daBoko_cFv */
BOOL daBoko_c::procMove_init() {
    mCurrentProc = &daBoko_c::procMove;
    mCurrentAction = 1;
    fopAcM_setCarryNow(this, FALSE);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    m2BB = 0x14;
    m2BC = 0;
    return TRUE;
}

/* 0000175C-00001E94       .text procMove__8daBoko_cFv */
BOOL daBoko_c::procMove() {
    /* Nonmatching */
}

/* 00001E94-000021B8       .text procThrow__8daBoko_cFv */
BOOL daBoko_c::procThrow() {
    /* Nonmatching */
}

/* 000021B8-00002624       .text procCarry__8daBoko_cFv */
BOOL daBoko_c::procCarry() {
    if (fopAcM_checkCarryNow(this) || m2BA == 0) {
        mDoMtx_multVecZero(mpModel->getBaseTRMtx(), &current.pos);
        mDoMtx_MtxToRot(mpModel->getBaseTRMtx(), &shape_angle);
    }
    fopAc_ac_c* link = dComIfGp_getLinkPlayer();
    cXyz linkFootPos(link->current.pos.x, link->current.pos.y + 5.0f, link->current.pos.z);
    if (!fopAcM_checkCarryNow(this)) {
        fopAcM_setCarryNow(this, FALSE);
        setTopRootPos(1);
        if (m2BA != 0) {
            mCurrentProc = &daBoko_c::procThrow;
            mCurrentAction = 6;
            gravity = 0.0f;
            shape_angle.x = m2CA;
            shape_angle.y = link->shape_angle.y;
            current.angle.y = shape_angle.y;
            speedF = 70.0f * cM_scos(shape_angle.x);
            speed.y = -70.0f * cM_ssin(shape_angle.x);
            m2C8 = 2;
            m2BA = 0;
            mCps.ResetAtHit();
            m_line_check.Set(&linkFootPos, &current.pos, this);
            if (dComIfG_Bgsp()->LineCross(&m_line_check)) {
                current.pos = m_line_check.GetCross();
                cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(m_line_check);
                current.pos += *triPla->GetNP() * 10.0f;
                setThrowReverse(cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z));
            } else {
                procThrow();
            }
        } else if (m2BC != 0) {
            if (shape_angle.z >= 0x4000) {
                shape_angle.z = 0;
                shape_angle.x += 0x8000;
                shape_angle.y += 0x8000;
            }
            procWait_init();
        } else {
            current.angle.y = shape_angle.y + 0x8000;
            if (mCurrentAction == 3) {
                m_line_check.Set(&linkFootPos, &current.pos, this);
                if (dComIfG_Bgsp()->LineCross(&m_line_check)) {
                    current.pos = m_line_check.GetCross();
                }
            }
            procMove_init();
            int i;
            for (i = 0; i < 3; i++) {
                m_ground_check.SetPos(&current.pos);
                if (dComIfG_Bgsp()->GroundCross(&m_ground_check) != -G_CM3D_F_INF) {
                    break;
                }
                current.pos.x -= 50.0f * cM_ssin(shape_angle.y);
                current.pos.z -= 50.0f * cM_scos(shape_angle.y);
            }
            if (i == 3) {
                current.pos = linkFootPos;
                current.pos.y = 50.0f;
            }
            old.pos = current.pos;
            current.pos.y -= 5.0f;
            m2C0 = 0;
            gravity = -3.0f;
            procMove();
        }
    }
    return TRUE;
}

/* 00002624-00002A04       .text execute__8daBoko_cFv */
BOOL daBoko_c::execute() {
    /* Nonmatching */
}

/* 00002A04-00002A24       .text daBoko_Execute__FP8daBoko_c */
static BOOL daBoko_Execute(daBoko_c* i_this) {
    return i_this->execute();
}

/* 00002A24-00002A2C       .text daBoko_IsDelete__FP8daBoko_c */
static BOOL daBoko_IsDelete(daBoko_c* i_this) {
    return TRUE;
}

/* 00002A2C-00002AA4       .text bokoDelete__8daBoko_cFv */
BOOL daBoko_c::bokoDelete() {
    mDoAud_seDeleteObject(&m2D0);
    mParticleCallBack.end();
    dKy_plight_cut(&mLight);
    dComIfG_resDelete(&mPhs, m_arc_name[fopAcM_GetParam(this)]);
    return TRUE;
}

/* 00002AA4-00002AC8       .text daBoko_Delete__FP8daBoko_c */
static BOOL daBoko_Delete(daBoko_c* i_this) {
    i_this->bokoDelete();
    return TRUE;
}

/* 00002AC8-00002AE8       .text daBoko_createHeap__FP10fopAc_ac_c */
static BOOL daBoko_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daBoko_c*>(i_this)->createHeap();
}

/* 00002AE8-00002CFC       .text createHeap__8daBoko_cFv */
BOOL daBoko_c::createHeap() {
    /* Nonmatching */
}

/* 00002DE4-00003154       .text create__8daBoko_cFv */
cPhs_State daBoko_c::create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daBoko_c);
}

/* 00003154-000032F0       .text __ct__8daBoko_cFv */
daBoko_c::daBoko_c() {
}

/* 00003824-00003844       .text daBoko_Create__FP10fopAc_ac_c */
static cPhs_State daBoko_Create(fopAc_ac_c* i_this) {
    return static_cast<daBoko_c*>(i_this)->create();
}

static actor_method_class l_daBoko_Method = {
    (process_method_func)daBoko_Create,
    (process_method_func)daBoko_Delete,
    (process_method_func)daBoko_Execute,
    (process_method_func)daBoko_IsDelete,
    (process_method_func)daBoko_Draw,
};

actor_process_profile_definition g_profile_BOKO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0009,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOKO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBoko_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOKO,
    /* Actor SubMtd */ &l_daBoko_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
