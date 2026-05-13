/**
 * d_a_obj_bemos.cpp
 * Enemy - Beamos
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_bemos.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_beam.h"
#include "d/actor/d_a_npc_os.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_a_obj.h"
#include "d/d_s_play.h"
#include "d/d_path.h"
#include "f_op/f_op_actor_mng.h"
#include "d/res/res_hmos.h"

static daBemos_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 70.0f,
        /* Height */ 210.0f,
    }},
};

static dCcD_SrcCyl l_cylGuard_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 200.0f,
        /* Height */ 400.0f,
    }},
};

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB | AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 65.0f,
    }},
};

/* 000000EC-00000194       .text __ct__13daBemos_HIO_cFv */
daBemos_HIO_c::daBemos_HIO_c() {
    mNo = -1;
    m08 = 400.0f;
    m0C = 900.0f;
    m10 = 0.0f;
    m14 = 0.3f;
    m18 = 0.3f;
    m1C = 3;
    m1E = 7;
    m20 = 0.1f;
    m24 = 0.07f;
    m28 = 0;
    m2A = 0;
    m2C = 0.0f;
    m30 = 0.0f;
    m34 = 0.0f;
    m38 = 0.0f;
    m3C = 0.0f;
    m40 = 400;
    m42 = 30;
    m48 = 100.0f;
    m44 = 200.0f;
    m4C = 0;
}

const char daBemos_c::m_arcname[] = "Hmos";

/* 00000194-0000033C       .text set_mtx__9daBemos_cFv */
void daBemos_c::set_mtx() {
    m2B8->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    m2B8->setBaseTRMtx(mDoMtx_stack_c::get());

    if (m6B8 != 2) {
        cXyz local_1C(0.0f, 0.0f, 60.0f);

        m2BC->setBaseScale(m360);
        mDoMtx_stack_c::transS(m2A4.x, m2A4.y, m2A4.z);
        mDoMtx_stack_c::ZXYrotM(m29C.x, m29C.y + current.angle.y, m29C.z);
        mDoMtx_stack_c::multVec(&local_1C, &m354);
        m2BC->setBaseTRMtx(mDoMtx_stack_c::get());

        if (m6B8 == 1) {
            cXyz local_08(0.0f, 0.0f, 0.0f);

            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::YrotM(m29C.y + current.angle.y);
            mDoMtx_stack_c::transM(local_08);
            m2C0->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
}

/* 0000033C-0000035C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daBemos_c*>(i_this)->CreateHeap();
}

/* 0000035C-00000498       .text CreateHeap1__9daBemos_cFv */
BOOL daBemos_c::CreateHeap1() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOS1));
    JUT_ASSERT(417, modelData != NULL);

    m2B8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2B8 == NULL) {
        return FALSE;
    }

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOSUP1));
    JUT_ASSERT(426, modelData != NULL);

    m2BC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2BC == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00000498-000006EC       .text CreateHeap2__9daBemos_cFv */
BOOL daBemos_c::CreateHeap2() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOS2));
    JUT_ASSERT(448, modelData != NULL);

    m2B8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2B8 == NULL) {
        return FALSE;
    }

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOSUP2));
    JUT_ASSERT(457, modelData != NULL);

    m2BC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2BC == NULL) {
        return FALSE;
    }

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOS2T));
    JUT_ASSERT(475, modelData != NULL);

    m2C0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2BC == NULL) {
        return FALSE;
    }

    m_sch_brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arcname, HMOS_BRK_HMOS2T));
    JUT_ASSERT(483, m_sch_brk != NULL);

    if (!mBrkAnm2.init(modelData, m_sch_brk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    return TRUE;
}

/* 000006EC-000007A8       .text CreateHeap3__9daBemos_cFv */
BOOL daBemos_c::CreateHeap3() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HMOS_BDL_HMOS3));
    JUT_ASSERT(496, modelData != NULL);

    m2B8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (m2B8 == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 000007A8-00000808       .text CreateHeap__9daBemos_cFv */
BOOL daBemos_c::CreateHeap() {
    switch (m6B8) {
        case 0:
            return CreateHeap1();
        case 1:
            return CreateHeap2();
        case 2:
            return CreateHeap3();
    }
    return FALSE;
}

/* 00000808-00000A4C       .text CreateInit1__9daBemos_cFv */
BOOL daBemos_c::CreateInit1() {
    u8 uStack_14 = fopAcM_GetParam(this) & 0xFF;
    if (uStack_14 == 0xff) {
        uStack_14 = 0;
    }
    m320 = uStack_14 * 100.0f + 500.0f;

    mSttsSph.Init(0xff, 0xff, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mSttsSph);
    mSph.OnTgNoConHit();

    blue_eye_wait_init();

    m2A4.set(current.pos);
    m2A4.y += REG10_F(19) + 260.0f;
    eyePos = m2A4;
    attention_info.position = eyePos;
    attention_info.position.y += 60.0f;

    m360.x = 0.0f;
    m360.y = 0.75f;
    m360.z = 1.0f;
    m314.setall(0.0f);
    m6A4 = 0;
    m310 = 0xff;

    cXyz groundPos(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mGndChk.SetPos(&groundPos);
    mGndChk.SetActorPid(fopAcM_GetID(this));
    m6A0 = dComIfG_Bgsp()->GroundCross(&mGndChk);

    cXyz pos(2.0f, 2.0f, 10.0f);
    parentActorID = fopAcM_createChild(PROC_Beam, fopAcM_GetID(this), 0x1000000, &m2A4, tevStr.mRoomNo, &current.angle, &pos);

    m6BF = shape_angle.z & 0x3f;
    m6C0 = (shape_angle.z >> 6) & 0x7f;
    shape_angle.z = 0;
    current.angle.z = 0;
    return TRUE;
}

/* 00000A4C-00000CBC       .text CreateInit2__9daBemos_cFv */
BOOL daBemos_c::CreateInit2() {
    u8 uStack_14 = fopAcM_GetParam(this) & 0xFF;
    s8 uStack_15 = (fopAcM_GetParam(this) >> 8) & 0xFF;

    if (uStack_14 == 0xff) {
        uStack_14 = 0;
    }
    m320 = uStack_14 * 100.0f + 500.0f;

    if (uStack_15 >= 0) {
        m6B2 = uStack_15 * 250 + 750;
    } else {
        m6B2 = uStack_15 * 250 - 500;
    }

    mSttsSph.Init(0xff, 0xff, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mSttsSph);
    mSph.OnTgNoConHit();

    red_eye_wait_init();

    m2A4.set(current.pos);
    m2A4.y += REG10_F(19) + 260.0f;
    eyePos = m2A4;
    attention_info.position = eyePos;
    attention_info.position.y += 60.0f;

    m360.x = 0.0f;
    m360.y = 0.75f;
    m360.z = 1.0f;
    m314.setall(0.0f);
    m6A4 = 0;
    m310 = 0xff;

    cXyz groundPos(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mGndChk.SetPos(&groundPos);
    mGndChk.SetActorPid(fopAcM_GetID(this));
    m6A0 = dComIfG_Bgsp()->GroundCross(&mGndChk);

    cXyz pos(2.0f, 2.0f, 10.0f);
    parentActorID = fopAcM_createChild(PROC_Beam, fopAcM_GetID(this), 0, &m2A4, tevStr.mRoomNo, &current.angle, &pos);

    m6BF = shape_angle.z & 0x3f;
    m6C0 = (shape_angle.z >> 6) & 0x7f;
    shape_angle.z = 0;
    current.angle.z = 0;
    return TRUE;
}

/* 00000CBC-00001384       .text CreateInit3__9daBemos_cFv */
BOOL daBemos_c::CreateInit3() {
    m6A8 = fopAcM_GetParam(this) & 0xFF;
    m6B9 = (fopAcM_GetParam(this) >> 8) & 0xFF;
    u8 tmp = (fopAcM_GetParam(this) >> 16) & 0xFF;
    dPath* pdVar3 = dPath_GetRoomPath(tmp, fopAcM_GetRoomNo(this));
    f32 fVar10 = 10.0f;
    f32 fVar1 = 0.0f;

    m320 = 1000.0f;

    if (m6B9 == 0xFF) {
        m6B9 = 0;
    }

    if (pdVar3 != NULL) {
        current.pos = pdVar3->m_points[0].m_position;
        home.pos = current.pos;
        shape_angle = csXyz::Zero;
        current.angle = shape_angle;
        cXyz local_3C = pdVar3->m_points[1].m_position;

        fopAcM_createChild(PROC_Bemos, fopAcM_GetID(this), m6A8 | 0x2fff0000 | m6B9 << 8, &local_3C, tevStr.mRoomNo, NULL, NULL, 2);
        m29C.y = cLib_targetAngleY(&current.pos, &local_3C);
        m29C.x = cLib_targetAngleX(&current.pos, &local_3C);
        current.angle.y = m29C.y;
        current.angle.x = m29C.x;
        shape_angle = current.angle;

        cXyz local_48 = local_3C - current.pos;
        m320 = local_48.absXZ();
        fVar10 = ((local_48.abs() - 70.0f) - 110.0f) * 0.01f;
        fVar1 = 20.0f;
        m6BD = 1;

    } else if (parentActorID != -1) {
        fopAc_ac_c* pfVar5 = fopAcM_SearchByID(parentActorID);
        shape_angle = csXyz::Zero;
        current.angle = shape_angle;

        cXyz local_54 = pfVar5->current.pos;
        m29C.y = cLib_targetAngleY(&current.pos, &local_54);
        m29C.x = cLib_targetAngleX(&current.pos, &local_54);
        current.angle.y = m29C.y;
        current.angle.x = m29C.x;
        shape_angle = current.angle;

        cXyz local_60 = local_54 - current.pos;
        m320 = local_60.absXZ();
        fVar10 = ((local_60.abs() - 70.0f) - 110.0f) * 0.01f;
        fVar1 = -20.0f;
        m6BD = 0;
    }

    mCyl.SetH(60.0f);
    m2A4 = current.pos;
    cXyz local_6C(0.0f, 0.0f, 80.0f);
    mDoMtx_stack_c::ZXYrotS(current.angle.x, current.angle.y, current.angle.z);
    cXyz local_78;
    mDoMtx_stack_c::multVec(&local_6C, &local_78);
    m2A4 += local_78;

    m6A4 = 0;
    yellow_eye_wait_init();

    cXyz local_9C(2.0f, 2.0f, fVar10);
    cXyz local_90;
    cXyz local_84(0.0f, fVar1, 40.0f);
    mDoMtx_stack_c::transS(m2A4.x, m2A4.y, m2A4.z);
    mDoMtx_stack_c::ZXYrotM(m29C.x, m29C.y, m29C.z);
    mDoMtx_stack_c::multVec(&local_84, &local_90);

    u32 uVar2 = 0x1000000;
    if (m6B9 == 2) {
        uVar2 |= 0x10000000;
    } else {
        uVar2 |= 0x40000000;
    }
    parentActorID = fopAcM_createChild(PROC_Beam, fopAcM_GetID(this), uVar2, &local_90, tevStr.mRoomNo, &m29C, &local_9C);
    current.angle.y = m29C.y;
    m6BB = 0;

    if (m6A8 != 0xff) {
        m6BA = fopAcM_isSwitch(this, m6A8);
    }

    if (m6BD != 0 && m6B9 != 2) {
        mSttsCyl.Init(0xff, 0xff, this);
        mCyl.Set(l_cylGuard_src);
        mCyl.SetStts(&mSttsCyl);
    }

    fopAcM_ClearStatusMap(this);
    return TRUE;
}

/* 00001384-0000148C       .text CreateInit__9daBemos_cFv */
cPhs_State daBemos_c::CreateInit() {
    if (m6B8 != 2) {
        mSttsCyl.Init(0xff, 0xff, this);
        mCyl.Set(l_cyl_src);
        mCyl.SetStts(&mSttsCyl);
        mCyl.OnTgNoConHit();
    }

    m29C = csXyz::Zero;
    m2FC = NULL;
    m300 = NULL;
    m304 = NULL;
    m308 = 0;
    m30C = 0;
    m6BC = 1;

    switch (m6B8) {
        case 0:
            CreateInit1();
            break;
        case 1:
            CreateInit2();
            break;
        case 2:
            CreateInit3();
            break;
    }

    set_mtx();
    fopAcM_SetMtx(this, m2B8->getBaseTRMtx());
    return cPhs_COMPLEATE_e;
}

/* 00003F90-0000403C       .text _create__9daBemos_cFv */
cPhs_State daBemos_c::_create() {
    fopAcM_ct_Retail(this, daBemos_c);
    cPhs_State ret = dComIfG_resLoad(&mPhase, m_arcname);
    m6B8 = fopAcM_GetParam(this) >> 0x1C;

    if (ret == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(this, daBemos_c);

        static s32 SHeapSize[] = {0x1740, 0x1E00, 0xBA0};
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, SHeapSize[m6B8])) {
            ret = CreateInit();
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

/* 0000148C-000016E4       .text blue_range_check__9daBemos_cFiP5csXyz */
BOOL daBemos_c::blue_range_check(int arg1, csXyz* arg2) {
    daPy_py_c* player = static_cast<daPy_py_c*>(dComIfGp_getPlayer(0));

    cXyz local_54(player->current.pos.x, player->getGroundY(), player->current.pos.z);
    cXyz local_60 = local_54 - current.pos;

    cXyz local_6C(cM_ssin(current.angle.y), 0.0f, cM_scos(current.angle.y));
    cXyz local_78(cM_scos(current.angle.y), 0.0f, -cM_ssin(current.angle.y));

    f32 fVar1 = m320;
    f32 fVar2 = l_HIO.m08;

    f32 inprod1 = local_6C.inprod(local_60);
    f32 inprod2 = local_78.inprod(local_60);
    f32 dist = std::sqrtf(inprod1 * inprod1 + inprod2 * inprod2);
    f32 tmp = local_60.y;

    if (arg1 != 0) {
        fVar2 += l_HIO.m30;
        fVar1 += l_HIO.m34;
    }

    if (inprod1 < fVar1 && inprod1 > 0.0f && std::fabsf(inprod2) < fVar2 && fabs(tmp) < 250.0f) {
        arg2->x = cM_atan2s(tmp + (m2A4.y - current.pos.y), dist);
        m6A4 = 1;
        return m6A4;
    }

    m6A4 = 0;
    return m6A4;
}

/* 000016E4-0000199C       .text red_range_check__9daBemos_cFiP5csXyz */
BOOL daBemos_c::red_range_check(int arg1, csXyz* arg2) {
    daPy_py_c* player = static_cast<daPy_py_c*>(dComIfGp_getPlayer(0));

    cXyz local_54(player->current.pos.x, player->getGroundY(), player->current.pos.z);
    cXyz local_60 = local_54 - current.pos;

    f32 fVar1 = m320;
    f32 absXZ = local_60.absXZ();

    s16 sVar2 = cM_atan2s(local_60.x, local_60.z);
    sVar2 -= current.angle.y;
    s16 iVar4 = sVar2 - m29C.y;

    if (m6BC == 0) {
        cXyz local_6C = player->current.pos - m36C;
        if (local_6C.abs() > 5.0f || abs(iVar4) > 0x1000) {
            m6BC = 1;
        } else {
            m6A4 = 0;
            return FALSE;
        }
    }

    if (arg1 != 0) {
        fVar1 += l_HIO.m2C;
    }

    if ((abs(iVar4) < 0x1000 || arg1 == 1) && absXZ < fVar1) {
        f32 tmp = m2A4.y - current.pos.y;
        arg2->x = cM_atan2s(-local_60.y + tmp, absXZ);
        arg2->y = sVar2;
        m6A4 = 1;
        return m6A4;
    }

    m6A4 = 0;
    return m6A4;
}

/* 0000199C-000019AC       .text yellow_range_check__9daBemos_cFiP5csXyz */
BOOL daBemos_c::yellow_range_check(int, csXyz*) {
    m6A4 = 1;
    return m6A4;
}

/* 000019AC-00001BF0       .text blue_eye_wait_init__9daBemos_cFv */
BOOL daBemos_c::blue_eye_wait_init() {
    if (m2FC == NULL) {
        cXyz local_1C = current.pos;
        local_1C.y += 210.0f;
        m2FC = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSWAIT00, &local_1C);
        if (m2FC != NULL) {
            m2FC->setGlobalPrmColor(0xA0, 0xB4, 0xFF);
            m2FC->setGlobalEnvColor(0x18, 0x9B, 0xD4);
        }
    }

    if (m300 == NULL) {
        cXyz local_28 = m2A4;
        local_28.x += cM_ssin(current.angle.y) * 60.0f;
        local_28.z += cM_scos(current.angle.y) * 60.0f;

        m300 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSEYE00, &local_28);
        if (m300 != NULL) {
            m300->setGlobalPrmColor(0x14, 0x36, 0xC3);
        }
    }

    if (m304 != NULL) {
        m304->becomeInvalidEmitter();
        m304 = NULL;
    }

    m360.set(0.0f, 0.75f, 1.0f);
    setEyeProc(&daBemos_c::blue_eye_wait);
    return TRUE;
}

/* 00001BF0-00001CAC       .text blue_eye_wait__9daBemos_cFv */
BOOL daBemos_c::blue_eye_wait() {
    if (getBeamActor() == NULL) {
        return FALSE;
    }

    csXyz tmp;
    if (blue_range_check(m6A4, &tmp)) {
        blue_eye_charge_init();
        return TRUE;
    }

    cLib_chaseUC(&m310, 0xff, 0xf);
    if (m310 == 0xff) {
        attention_info.flags = 0;
    }

    if (m300 != NULL) {
        m300->setGlobalTranslation(m354);
        m300->setGlobalAlpha(m310);
    }
    return FALSE;
}

/* 00001CAC-00001E14       .text blue_eye_charge_init__9daBemos_cFv */
BOOL daBemos_c::blue_eye_charge_init() {
    attention_info.flags = fopAc_Attn_LOCKON_MISC_e;

    if (m304 == NULL) {
        m304 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBALL00, &m2A4);
        if (m304 != NULL) {
            m304->setGlobalPrmColor(0x10, 0x23, 0xC0);
        }
    }

    if (m2FC != NULL) {
        m2FC->becomeInvalidEmitter();
        m2FC = NULL;
    }

    m6AC = 0;

    if (checkEyeProc(&daBemos_c::blue_eye_wait)) {
        m6AE = 0;
        m6B0 = l_HIO.m1C;
    } else {
        m6AE = l_HIO.m1E;
        m6B0 = l_HIO.m1E;
    }

    setEyeProc(&daBemos_c::blue_eye_charge);
    return TRUE;
}

/* 00001E14-00002174       .text blue_eye_charge__9daBemos_cFv */
BOOL daBemos_c::blue_eye_charge() {
    csXyz local_28;
    if (blue_range_check(m6A4, &local_28)) {
        cLib_chaseF(&m360.x, 1.0f, l_HIO.m14);
        cLib_chaseF(&m360.y, 1.0f, l_HIO.m14 * 0.25f);

        if (m6AE > m6B0) {
            if (m30C == NULL) {
                m30C = dComIfGp_particle_set(dPa_name::ID_AK_SN_LASERROOT00, &m354);
            }

            if (m360.x == 1.0f) {
                if (++m6AC >= 5.0f) {
                    if (m30C != NULL) {
                        m30C->becomeInvalidEmitter();
                        m30C = NULL;
                    }
                    blue_eye_search_init();
                }
            }
        } else {
            m6AE++;
        }

        cLib_chaseUC(&m310, 0, 0x1e);
        cLib_addCalcAngleS2(&m29C.x, local_28.x, 4, 0x400);
    } else if (m6AE <= 0) {
        cLib_chaseF(&m360.x, 0.0f, l_HIO.m18);
        cLib_chaseF(&m360.y, 0.75f, l_HIO.m18 * 0.25f);

        if (m360.x == 0.0f) {
            if (m30C != NULL) {
                m30C->becomeInvalidEmitter();
                m30C = NULL;
            }
            blue_eye_wait_init();
        }

        cLib_chaseUC(&m310, 0xff, 0xf);
        cLib_addCalcAngleS2(&m29C.x, 0, 4, 0x400);

        if (m6AC > 0) {
            m6AC--;
        }
    } else {
        m6AE--;
    }

    f32 fVar1 = 6.25f - (m6AC - 2.5f) * (m6AC - 2.5f);
    m314.setall(fVar1 * 1.6f);

    mSph.SetC(m2A4);
    dComIfG_Ccsp()->Set(&mSph);

    if (m300 != NULL) {
        m300->setGlobalTranslation(m354);
        m300->setGlobalAlpha(m310);
    }

    if (m30C != NULL) {
        JGeometry::TVec3<s16> tmp;
        tmp.x = m29C.x;
        tmp.y = m29C.y;
        tmp.z = m29C.z;
        tmp.y += current.angle.y;

        m30C->setGlobalTranslation(m354);
        m30C->setGlobalRotation(tmp);
        m30C->setGlobalScale(m314);
    }
    return FALSE;
}

/* 00002174-000021A4       .text blue_eye_search_init__9daBemos_cFv */
BOOL daBemos_c::blue_eye_search_init() {
    setEyeProc(&daBemos_c::blue_eye_search);
    m6AC = 0;
    return TRUE;
}

/* 000021A4-000023F0       .text blue_eye_search__9daBemos_cFv */
BOOL daBemos_c::blue_eye_search() {
    daBeam_c* beam = getBeamActor();

    if (beam == NULL) {
        return FALSE;
    }

    csXyz local_20;
    if (blue_range_check(m6A4, &local_20)) {
        cLib_addCalcAngleS2(&m29C.x, local_20.x, 4, 0x400);

        csXyz tmp = m29C;
        tmp.y += current.angle.y;

        if (!beam->beamCheck()) {
            beam->beamOn();
        }

        if (beam->m5F4 == 0) {
            beam->m5A8 = 0.0f;
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 5.0f;
                beam->m5F4 = 1;
            }
        } else {
            beam->m5A8 = 0.0f;
            beam->m588 = 5.0f;
        }
        beam->setPosAngle(m354, tmp);
    } else {
        if (beam->beamCheck()) {
            beam->beamOff();
        }

        BOOL bVar3;
        if (beam->m5F4 == 1) {
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            }

            if (beam->m5A8 < 4.0f) {
                beam->m5A8 += 1.0f;
                bVar3 = FALSE;
                goto end;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 0.0f;
                beam->m5F4 = 0;
            }
        } else {
            beam->m588 = 0.0f;
            beam->m5A8 = 0.0f;
        }
        bVar3 = TRUE;
    end:
        if (bVar3) {
            blue_eye_charge_init();
        }
    }

    mSph.SetC(m2A4);
    dComIfG_Ccsp()->Set(&mSph);
    return FALSE;
}

/* 000023F0-00002630       .text red_eye_wait_init__9daBemos_cFv */
BOOL daBemos_c::red_eye_wait_init() {
    if (m2FC == NULL) {
        cXyz local_1C = current.pos;
        local_1C.y += 210.0f;
        m2FC = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSWAIT00, &local_1C);
        if (m2FC != NULL) {
            m2FC->setGlobalPrmColor(0xFF, 0x80, 0xC8);
            m2FC->setGlobalEnvColor(0xD4, 0x18, 0xFF);
        }
    }

    if (m300 == NULL) {
        cXyz local_28 = m2A4;
        local_28.x += cM_ssin(current.angle.y) * 60.0f;
        local_28.z += cM_scos(current.angle.y) * 60.0f;

        m300 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSEYE00, &local_28);
        if (m300 != NULL) {
            m300->setGlobalPrmColor(0xC3, 0x14, 0x36);
        }
    }

    if (m304 != NULL) {
        m304->becomeInvalidEmitter();
        m304 = NULL;
    }

    m360.set(0.0f, 0.75f, 1.0f);
    setEyeProc(&daBemos_c::red_eye_wait);
    return TRUE;
}

/* 00002630-00002724       .text red_eye_wait__9daBemos_cFv */
BOOL daBemos_c::red_eye_wait() {
    daBeam_c* beam = getBeamActor();

    mBrkAnm2.play();

    if (beam == NULL) {
        return FALSE;
    }

    csXyz tmp;
    if (red_range_check(m6A4, &tmp)) {
        red_eye_charge_init();
        return TRUE;
    }

    cLib_addCalcAngleS2(&m29C.x, 0, 4, 0x400);
    m29C.y += m6B2;

    cLib_chaseUC(&m310, 0xff, 0xf);
    if (m310 == 0xff) {
        attention_info.flags = 0;
    }

    if (m300 != NULL) {
        m300->setGlobalTranslation(m354);
        m300->setGlobalAlpha(m310);
    }
    return TRUE;
}

/* 00002724-0000288C       .text red_eye_charge_init__9daBemos_cFv */
BOOL daBemos_c::red_eye_charge_init() {
    attention_info.flags = fopAc_Attn_LOCKON_MISC_e;

    if (m304 == NULL) {
        m304 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBALL00, &m2A4);
        if (m304 != NULL) {
            m304->setGlobalPrmColor(0xC0, 0x10, 0x23);
        }
    }

    if (m2FC != NULL) {
        m2FC->becomeInvalidEmitter();
        m2FC = NULL;
    }

    m6AC = 0;

    if (checkEyeProc(&daBemos_c::red_eye_wait)) {
        m6AE = 0;
        m6B0 = l_HIO.m28;
    } else {
        m6AE = l_HIO.m2A;
        m6B0 = l_HIO.m2A;
    }

    setEyeProc(&daBemos_c::red_eye_charge);
    return TRUE;
}

/* 0000288C-00002C04       .text red_eye_charge__9daBemos_cFv */
BOOL daBemos_c::red_eye_charge() {
    mBrkAnm2.play();

    csXyz local_28;
    if (red_range_check(m6A4, &local_28)) {
        cLib_chaseF(&m360.x, 1.0f, l_HIO.m20);
        cLib_chaseF(&m360.y, 1.0f, l_HIO.m20 * 0.25f);

        if (m6AE > l_HIO.m28) {
            cLib_addCalcAngleS(&m29C.x, local_28.x, 2, 0x400, 0);

            if (m30C == NULL) {
                m30C = dComIfGp_particle_set(dPa_name::ID_AK_SN_LASERROOT00, &m354);
            }

            if (m360.x == 1.0f) {
                if (++m6AC >= 5.0f) {
                    if (m30C != NULL) {
                        m30C->becomeInvalidEmitter();
                        m30C = NULL;
                    }
                    red_eye_search_init();
                }
            }
        } else {
            m6AE++;
        }

        cLib_chaseUC(&m310, 0, 0x1e);
    } else if (m6AE <= 0) {
        cLib_chaseF(&m360.x, 0.0f, l_HIO.m24);
        cLib_chaseF(&m360.y, 0.75f, l_HIO.m24 * 0.25f);

        if (m360.x == 0.0f) {
            if (m30C != NULL) {
                m30C->becomeInvalidEmitter();
                m30C = NULL;
            }
            red_eye_wait_init();
        }

        cLib_chaseUC(&m310, 0xff, 0xf);
        cLib_addCalcAngleS2(&m29C.x, 0, 4, 0x400);

        if (m6AC > 0) {
            m6AC--;
        }
    } else {
        m6AE--;
    }

    mSph.SetC(m2A4);
    dComIfG_Ccsp()->Set(&mSph);

    f32 fVar1 = 6.25f - (m6AC - 2.5f) * (m6AC - 2.5f);
    m314.setall(fVar1 * 1.6f);

    if (m300 != NULL) {
        m300->setGlobalTranslation(m354);
        m300->setGlobalAlpha(m310);
    }

    if (m30C != NULL) {
        JGeometry::TVec3<s16> tmp;
        tmp.x = m29C.x;
        tmp.y = m29C.y;
        tmp.z = m29C.z;
        tmp.y += current.angle.y;

        m30C->setGlobalTranslation(m354);
        m30C->setGlobalRotation(tmp);
        m30C->setGlobalScale(m314);
    }
    return TRUE;
}

/* 00002C04-00002C3C       .text red_eye_search_init__9daBemos_cFv */
BOOL daBemos_c::red_eye_search_init() {
    m6B6 = l_HIO.m42;
    setEyeProc(&daBemos_c::red_eye_search);
    return TRUE;
}

/* 00002C3C-00002EF4       .text red_eye_search__9daBemos_cFv */
BOOL daBemos_c::red_eye_search() {
    mBrkAnm2.play();

    daBeam_c* beam = getBeamActor();
    if (beam == NULL) {
        return FALSE;
    }

    csXyz local_20;
    if (red_range_check(m6A4, &local_20)) {
        cLib_addCalcAngleS2(&m29C.x, local_20.x, 4, 0x400);
        cLib_addCalcAngleS2(&m29C.y, local_20.y, 1, l_HIO.m40);

        csXyz tmp = m29C;
        tmp.y += current.angle.y;

        if (!beam->beamCheck()) {
            beam->beamOn();
        }

        if (beam->m5F4 == 0) {
            beam->m5A8 = 0.0f;
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 5.0f;
                beam->m5F4 = 1;
            }
        } else {
            beam->m5A8 = 0.0f;
            beam->m588 = 5.0f;
        }
        beam->setPosAngle(m354, tmp);
        if (m6B6 > 0) {
            m6B6--;
        } else {
            daPy_py_c* player = static_cast<daPy_py_c*>(dComIfGp_getPlayer(0));
            m36C = player->current.pos;
            m6BC = 0;
        }
    } else {
        if (beam->beamCheck()) {
            beam->beamOff();
        }

        BOOL bVar3;
        if (beam->m5F4 == 1) {
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            }

            if (beam->m5A8 < 4.0f) {
                beam->m5A8 += 1.0f;
                bVar3 = FALSE;
                goto end;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 0.0f;
                beam->m5F4 = 0;
            }
        } else {
            beam->m588 = 0.0f;
            beam->m5A8 = 0.0f;
        }
        bVar3 = TRUE;
    end:
        if (bVar3) {
            red_eye_charge_init();
        }
    }

    mSph.SetC(m2A4);
    dComIfG_Ccsp()->Set(&mSph);
    return FALSE;
}

/* 00002EF4-00003040       .text eye_break_init__9daBemos_cFv */
BOOL daBemos_c::eye_break_init() {
    if (m304 == NULL) {
        m304 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBALL00, &m2A4);
        if (m304 != NULL) {
            if (m6B8 == 0) {
                m304->setGlobalPrmColor(0x10, 0x23, 0xC0);
            } else {
                m304->setGlobalPrmColor(0xc0, 0x10, 0x23);
            }
        }
    }

    dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &m2A4);
    m6AC = 0;
    attention_info.flags = 0;
    setEyeProc(&daBemos_c::eye_break);
    fopAcM_ClearStatusMap(this);
    return TRUE;
}

/* 00003040-00003498       .text eye_break__9daBemos_cFv */
BOOL daBemos_c::eye_break() {
    daBeam_c* beam = getBeamActor();
    if (beam != NULL) {
        if (beam->beamCheck()) {
            beam->beamOff();
        }

        if (beam->m5F4 == 1) {
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            }

            if (beam->m5A8 < 4.0f) {
                beam->m5A8 += 1.0f;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 0.0f;
                beam->m5F4 = 0;
            }
        } else {
            beam->m588 = 0.0f;
            beam->m5A8 = 0.0f;
        }
    }

    cLib_addCalcAngleS2(&m29C.x, 0, 2, 0x800);
    cLib_chaseF(&m360.x, 1.0f, 0.2f);
    cLib_chaseF(&m360.y, 1.0f, 0.05f);

    if (++m6AC > 0) {
        if (m2FC != NULL) {
            m2FC->becomeInvalidEmitter();
        }

        if (m300 != NULL) {
            m300->becomeInvalidEmitter();
        }

        if (m304 != NULL) {
            m304->becomeInvalidEmitter();
        }

        if (m308 != NULL) {
            m308->becomeInvalidEmitter();
        }

        if (m30C != NULL) {
            m30C->becomeInvalidEmitter();
        }

        m2FC = NULL;
        m300 = NULL;
        m304 = NULL;
        m308 = NULL;
        m30C = NULL;

        csXyz tmp = m29C;
        tmp.y += current.angle.y;
        m360 = cXyz::Zero;

        GXColor local_34;
        GXColor local_38;

        if (m6B8 == 0) {
            local_34 = (GXColor){0x10, 0x23, 0xC0, 0x00};
            local_38 = (GXColor){0x14, 0x36, 0xC3, 0x00};
        } else {
            local_34 = (GXColor){0xC0, 0x10, 0x23, 0x00};
            local_38 = (GXColor){0xC3, 0x14, 0x36, 0x00};
        }

        dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBREAK00, &m2A4, &tmp, NULL, 0xff, NULL, fopAcM_GetRoomNo(this), &local_34);
        dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBREAK01, &m2A4, &tmp, NULL, 0xff, NULL, fopAcM_GetRoomNo(this), &local_38);

        if (beam != NULL) {
            fopAcM_delete(beam);
        }

        fopAcM_seStart(this, JA_SE_OBJ_COL_SWC_CHNL, 0);
        cXyz local_28 = m2A4;
        local_28.x += cM_ssin(tmp.y) * 30.0f;
        local_28.z += cM_scos(tmp.y) * 30.0f;

        fopAcM_createItemFromTable(&local_28, m6BF, m6C0, fopAcM_GetRoomNo(this), 0, &tmp, 1, NULL);

        setEyeProc(&daBemos_c::eye_dummy);
    }
    return TRUE;
}

/* 00003498-000034BC       .text eye_dummy__9daBemos_cFv */
BOOL daBemos_c::eye_dummy() {
    if (m6B8 == 1) {
        mBrkAnm2.setFrame(10.0f);
    }
    return FALSE;
}

/* 000034BC-00003638       .text yellow_eye_wait_init__9daBemos_cFv */
BOOL daBemos_c::yellow_eye_wait_init() {
    if (m2FC == NULL) {
        cXyz local_20 = current.pos;
        cXyz local_2C(0.0f, 0.0f, 20.0f);
        mDoMtx_stack_c::ZXYrotS(current.angle.x + 0x4000, current.angle.y, current.angle.z);
        cXyz local_38;
        mDoMtx_stack_c::multVec(&local_2C, &local_38);
        local_20 += local_38;
        m2FC = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSWAIT00, &local_20, &current.angle);

        if (m2FC != NULL) {
            m2FC->setGlobalPrmColor(0xB4, 0xB4, 0x78);
            m2FC->setGlobalEnvColor(0x80, 0x80, 0x14);
        }
    }

    if (m304 != NULL) {
        m304->becomeInvalidEmitter();
        m304 = NULL;
    }

    setEyeProc(&daBemos_c::yellow_eye_wait);
    return TRUE;
}

/* 00003638-00003798       .text yellow_eye_wait__9daBemos_cFv */
BOOL daBemos_c::yellow_eye_wait() {
    daBeam_c* beam = getBeamActor();

    if (beam == NULL || (m6A8 != 0xff && fopAcM_isSwitch(this, m6A8)) || (m6B9 == 1 && daNpc_Os_c::getCattleRoomNo() != fopAcM_GetRoomNo(this))) {
        if (beam->m5F4 != 0) {
            if (beam->beamCheck()) {
                beam->beamOff();
            }

            if (beam->m5F4 == 1) {
                if (beam->m588 < 5.0f) {
                    beam->m588 += 1.0f;
                }

                if (beam->m5A8 < 4.0f) {
                    beam->m5A8 += 1.0f;
                } else {
                    beam->m5A8 = 0.0f;
                    beam->m588 = 0.0f;
                    beam->m5F4 = 0;
                }
            } else {
                beam->m588 = 0.0f;
                beam->m5A8 = 0.0f;
            }
        }
        return FALSE;
    }

    if (yellow_range_check(m6A4, NULL)) {
        yellow_eye_search_init();
    }
    return FALSE;
}

/* 00003798-00003890       .text yellow_eye_search_init__9daBemos_cFv */
BOOL daBemos_c::yellow_eye_search_init() {
    if (m304 == NULL) {
        m304 = dComIfGp_particle_set(dPa_name::ID_AK_SN_BMOSBALL00, &m2A4);
        if (m304 != NULL) {
            m304->setGlobalPrmColor(0xA0, 0xC0, 0x14);
        }
    }

    if (m2FC != NULL) {
        m2FC->becomeInvalidEmitter();
        m2FC = NULL;
    }

    setEyeProc(&daBemos_c::yellow_eye_search);
    m6AC = 0;
    return TRUE;
}

/* 00003890-00003A80       .text yellow_eye_search__9daBemos_cFv */
BOOL daBemos_c::yellow_eye_search() {
    daBeam_c* beam = getBeamActor();

    if (beam == NULL) {
        return FALSE;
    }

    if (yellow_range_check(m6A4, NULL) && (m6A8 == 0xff || !fopAcM_isSwitch(this, m6A8))) {
        if (!beam->beamCheck()) {
            beam->beamOn();
        }

        if (beam->m5F4 == 0) {
            beam->m5A8 = 0.0f;
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 5.0f;
                beam->m5F4 = 1;
            }
        } else {
            beam->m5A8 = 0.0f;
            beam->m588 = 5.0f;
        }
    } else {
        if (beam->beamCheck()) {
            beam->beamOff();
        }

        BOOL bVar3;
        if (beam->m5F4 == 1) {
            if (beam->m588 < 5.0f) {
                beam->m588 += 1.0f;
            }

            if (beam->m5A8 < 4.0f) {
                beam->m5A8 += 1.0f;
                bVar3 = FALSE;
                goto end;
            } else {
                beam->m5A8 = 0.0f;
                beam->m588 = 0.0f;
                beam->m5F4 = 0;
                bVar3 = TRUE;
            }
        } else {
            beam->m588 = 0.0f;
            beam->m5A8 = 0.0f;
            bVar3 = TRUE;
        }
        bVar3 = TRUE;
    end:

        if (bVar3) {
            yellow_eye_wait_init();
        }
    }

    return FALSE;
}

/* 00003A80-00003C5C       .text event_move__9daBemos_cFv */
void daBemos_c::event_move() {
    if (m6B8 == 2 && m6BD != 0 && m6A8 != 0xff) {
        u8 bVar4 = m6BA;
        m6BA = fopAcM_isSwitch(this, m6A8);
        if (m6BA != bVar4 && m6BA == 1 && !dComIfGs_isEventBit(0x1010)) {
            dComIfGs_onEventBit(0x1010);
            m6BB = 1;
        }

        if (m6BB == 1) {
            if (!eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderOtherEvent(this, "hmos3cam");
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            } else {
                m6BB = 2;
            }
        } else if (this->m6BB == 2) {
            int iVar1 = dComIfGp_evmng_getMyStaffId("Hmos3", NULL, 0);
            if (dComIfGp_evmng_endCheck("hmos3cam")) {
                dComIfGp_event_reset();
                m6BB = 0;
            } else {
                dComIfGp_evmng_cutEnd(iVar1);
            }
        }
    }

    if (m6B8 == 2 && m6A8 != 0xff && fopAcM_isSwitch(this, m6A8)) {
        if (m2FC != NULL) {
            m2FC->becomeInvalidEmitter();
            m2FC = NULL;
        }
    }
}

/* 00003C5C-00003F00       .text guard_proc__9daBemos_cFv */
void daBemos_c::guard_proc() {
    if (m6B8 == 2 && m6BD == 1) {
        daBeam_c* beam = getBeamActor();

        if (beam != NULL && beam->m5F4 != 0) {
            fopAc_ac_c* player = dComIfGp_getLinkPlayer();

            cXyz local_40 = player->current.pos - current.pos;
            cXyz local_4C = current.pos;
            cXyz local_58;
            cXyz local_64;
            cXyz local_70 = cXyz::BaseZ;
            cXyz local_7C = cXyz::BaseX;
            mDoMtx_stack_c::ZXYrotS(current.angle.x, current.angle.y, current.angle.z);
            mDoMtx_stack_c::multVec(&local_70, &local_58);
            mDoMtx_stack_c::multVec(&local_7C, &local_64);
            f32 fVar2 = local_40.inprod(local_58);
            f32 fVar3 = local_40.inprod(local_64);
            local_58 *= fVar2;

            if (fVar3 > 0.0f) {
                local_64 *= -(l_HIO.m44 - 20.0f);
            } else {
                local_64 *= l_HIO.m44 - 20.0f;
            }

            local_4C += local_58;
            local_4C += local_64;

            if (dComIfGp_checkPlayerStatus1(0, daPyStts1_DEKU_LEAF_FLY_e)) {
                local_4C.y -= 50.0f;
                mCyl.SetC(local_4C);
                mCyl.SetR(l_HIO.m44);
                mCyl.SetH(100.0f);
            } else {
                local_4C.y -= l_HIO.m48 * 0.5f;
                mCyl.SetC(local_4C);
                mCyl.SetR(l_HIO.m44);
                mCyl.SetH(l_HIO.m48);
            }
            dComIfG_Ccsp()->Set(&mCyl);
        }
    }
}

/* 00003F00-00003F70       .text getBeamActor__9daBemos_cFv */
daBeam_c* daBemos_c::getBeamActor() {
    fopAc_ac_c* ac = fopAcM_SearchByID(parentActorID);
    if (ac == NULL) {
        return NULL;
    }

    if (fopAcM_IsActor(ac) && fopAcM_GetProfName(ac) == PROC_Beam) {
        return static_cast<daBeam_c*>(ac);
    }
    return NULL;
}

/* 00003F70-00003F90       .text daBemosCreate__FPv */
static cPhs_State daBemosCreate(void* i_this) {
    return ((daBemos_c*)i_this)->_create();
}

bool daBemos_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, m_arcname);

    if (m2FC != NULL) {
        m2FC->becomeInvalidEmitter();
    }

    if (m300 != NULL) {
        m300->becomeInvalidEmitter();
    }

    if (m304 != NULL) {
        m304->becomeInvalidEmitter();
    }

    if (m308 != NULL) {
        m308->becomeInvalidEmitter();
    }

    if (m30C != NULL) {
        m30C->becomeInvalidEmitter();
    }

    m2FC = NULL;
    m300 = NULL;
    m304 = NULL;
    m308 = NULL;
    m30C = NULL;
    return true;
}

/* 00004ACC-00004BC0       .text daBemosDelete__FPv */
static BOOL daBemosDelete(void* i_this) {
    return ((daBemos_c*)i_this)->_delete();
}

bool daBemos_c::_execute() {
    if (m6B8 != 2) {
        if (mSph.ChkTgHit()) {
            eye_break_init();
            mSph.ClrTgHit();
        }
    }

    (this->*m290)();
    event_move();
    set_mtx();

    if (m6B8 != 2) {
        mSttsCyl.Move();
        mSttsSph.Move();
        if (mCyl.ChkTgHit()) {
            daObj::HitEff_hibana(this, &mCyl);
            daObj::HitSeStart(&current.pos, current.roomNo, &mCyl, 0xd);
        }
        mCyl.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    } else if (m6B9 != 2) {
        guard_proc();
    }

    fopAcM_setGbaName(this, dItem_BOW_e, 0x23, 0x2c);
    return false;
}

/* 00004BC0-00004CF0       .text daBemosExecute__FPv */
static BOOL daBemosExecute(void* i_this) {
    return ((daBemos_c*)i_this)->_execute();
}

bool daBemos_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(m2B8, &tevStr);
    mDoExt_modelUpdateDL(m2B8);

    if (m6B8 != 2 && m360.x > 0.0f) {
        g_env_light.setLightTevColorType(m2BC, &tevStr);
        mDoExt_modelUpdateDL(m2BC);
    }

    if (m6B8 == 1) {
        g_env_light.setLightTevColorType(m2C0, &tevStr);
        mBrkAnm2.entry(m2C0->getModelData());
        mDoExt_modelUpdateDL(m2C0);
    }

    if (m6B8 < 2) {
        dComIfGd_setSimpleShadow2(&current.pos, m6A0, 90.0f, mGndChk);
    }
    return true;
}

/* 00004CF0-00004E10       .text daBemosDraw__FPv */
static BOOL daBemosDraw(void* i_this) {
    return ((daBemos_c*)i_this)->_draw();
}

/* 00004E10-00004E18       .text daBemosIsDelete__FPv */
static BOOL daBemosIsDelete(void*) {
    return TRUE;
}

static actor_method_class daBemosMethodTable = {
    (process_method_func)daBemosCreate,
    (process_method_func)daBemosDelete,
    (process_method_func)daBemosExecute,
    (process_method_func)daBemosIsDelete,
    (process_method_func)daBemosDraw,
};

actor_process_profile_definition g_profile_Bemos = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Bemos,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBemos_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Bemos,
    /* Actor SubMtd */ &daBemosMethodTable,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
