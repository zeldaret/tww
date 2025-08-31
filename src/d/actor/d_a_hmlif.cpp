/**
 * d_a_hmlif.cpp
 * Object - Tower of the Gods - Glowing platform 
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_hmlif.h"
#include "d/res/res_hmlif.h"
#include "d/res/res_hyuf1.h"
#include "d/res/res_hyuf2.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_path.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

char* daHmlif_c::m_arcname[] = {"Hmlif", "Hyuf1", "Hyuf2"};
const f32 daHmlif_c::m_speed[] = {
    1.6666666f,
    3.3333333f,
    5.0f,
    6.6666665f,
    8.333333f,
    10.0f,
    11.666667f,
    13.333333f,
    15.0f,
    16.666666f,
    18.333334f,
    20.0f,
    21.666666f,
    23.333334f,
    25.0f,
    26.666666f,
};
const s16 daHmlif_c::m_bmdidx[] = {HMLIF_BDL_HMLIF, HYUF1_BDL_HYUF1, HYUF2_BDL_HYUF2};
const s16 daHmlif_c::m_dzbidx[] = {HMLIF_DZB_HMLIF, HYUF1_DZB_HYUF1, HYUF2_DZB_HYUF2};
const s16 daHmlif_c::m_btpidx[] = {-1, HYUF1_BTP_HYUF1, HYUF2_BTP_HYUF2};
const s16 daHmlif_c::m_brkidx[] = {HMLIF_BRK_HMLIF, HYUF1_BRK_HYUF1, -1};

const f32 daHmlif_c::m_cull_box[][6] = {
    {-200.0f, -100.0f, -200.0f, 200.0f, 50.0f, 200.0f},
    {-200.0f, -100.0f, -200.0f, 200.0f, 450.0f, 200.0f},
    {-200.0f, -100.0f, -200.0f, 200.0f, 450.0f, 200.0f},
};
const s16 daHmlif_c::m_heapsize[] = {0xC60, 0x1B40, 0x1B40};

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW,
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
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 35.0f,
    }},
};

namespace daHmlif_prm {
inline u8 getSwitchNo(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 0) & 0xFF;
}
inline u8 getPathId(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 8) & 0xFF;
}
inline u8 getSpeed(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 16) & 0xF;
}
inline u8 getDirection(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 20) & 0x3;
}
inline u8 getStart(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 22) & 0x1F;
}
inline u8 getType(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 27) & 0xF;
}
inline u8 getSmooth(daHmlif_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 31) & 0x1;
}
inline u8 getSwitchNo2(daHmlif_c* i_this) {
    return i_this->home.angle.z & 0xff;
}
} // namespace daHmlif_prm

/* 00000078-00000080       .text Delete__9daHmlif_cFv */
BOOL daHmlif_c::Delete() {
    return TRUE;
}

/* 00000080-000000D8       .text daHmlifDelete__9daHmlif_cFv */
BOOL daHmlif_c::daHmlifDelete() {
    BOOL uVar1 = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, m_arcname[m489]);
    return uVar1;
}

/* 000000D8-0000042C       .text CreateHeap__9daHmlif_cFv */
BOOL daHmlif_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[m489], m_bmdidx[m489]);
    JUT_ASSERT(DEMO_SELECT(394, 399), modelData != NULL);

    u32 uVar1 = 0x11000022;
    if (m_btpidx[m489] != -1) {
        uVar1 |= 0x20000;
    }

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, uVar1);
    if (mpModel == NULL) {
        return FALSE;
    }

    m478 = daHmlif_prm::getSwitchNo2(this);
    mpBtp = NULL;

    if (m_btpidx[m489] != -1) {
        J3DAnmTexPattern* pbtp = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname[m489], m_btpidx[m489]);
        JUT_ASSERT(DEMO_SELECT(417, 422), pbtp != NULL);

        mpBtp = new mDoExt_btpAnm();
        if (mpBtp == NULL || !mpBtp->init(modelData, pbtp, 0, 0, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        m48A = 0;
        if (mpBtp != NULL && fopAcM_isSwitch(this, m478)) {
            m48A = 3;
        }
    }

    mpBrk = NULL;

    if (m_brkidx[m489] != -1) {
        J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname[m489], m_brkidx[m489]);
        JUT_ASSERT(DEMO_SELECT(442, 447), pbrk != NULL);

        mpBrk = new mDoExt_brkAnm();
        if ((mpBrk == NULL) || !mpBrk->init(modelData, pbrk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }
        mpBrk->setPlaySpeed(0.0f);
    }
    return TRUE;
}

/* 00000474-000007C8       .text Create__9daHmlif_cFv */
BOOL daHmlif_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, m_cull_box[m489][0], m_cull_box[m489][1], m_cull_box[m489][2], m_cull_box[m489][3], m_cull_box[m489][4], m_cull_box[m489][5]);
    fopAcM_setCullSizeFar(this, 1.0f);
    set_mtx();
    m444 = daHmlif_prm::getPathId(this);
    m474 = daHmlif_prm::getSwitchNo(this);
    m445 = m444;

    if (m445 != 0xff) {
        ppd = dPath_GetRoomPath(m445, fopAcM_GetRoomNo(this));
        if (ppd == NULL) {
            m445 = 0xff;
            return FALSE;
        }
    } else {
        return FALSE;
    }

    if ((m474 != 0xff) && (ppd->mArg0 > ppd->m_num)) {
        return FALSE;
    }

    u8 uVar4 = daHmlif_prm::getStart(this);
    dPnt* pdVar7 = ppd->m_points;

    if (uVar4 == 0xff) {
        uVar4 = cM_rndF(ppd->m_num - 1);
    }

    if (uVar4 >= ppd->m_num) {
        uVar4 = 0;
    }

    pdVar7 += uVar4;
    current.pos = pdVar7->m_position;
    m450 = current.pos;
    m45C = current.pos;
    m448 = uVar4;
    uVar4 = daHmlif_prm::getDirection(this);

    switch (uVar4) {
    case 0:
        m446 = 1;
        break;
    case 1:
        m446 = -1;
        break;
    case 2:
        m446 = 1;
        if (cM_rnd() >= 0.5f) {
            m446 = -1;
        }
        break;
    default:
        m446 = 1;
        break;
    }
    m447 = m446;
    uVar4 = daHmlif_prm::getSpeed(this);
    if (uVar4 > 8) {
        uVar4 = 8;
    }
    m480 = m_speed[uVar4];
    fopAcM_SetSpeedF(this, m480);
    m47E = daHmlif_prm::getSmooth(this);
    if (m474 != 0xff) {
        pdVar7 = &ppd->m_points[ppd->mArg0];
        m468 = pdVar7->m_position;
    }

    if ((m489 == 1) || (m489 == 2)) {
        cXyz sp0C = current.pos;
        u32 atType = AT_TYPE_LIGHT_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_NORMAL_ARROW;
        sp0C.y += 200.0f;
        mSph.cM3dGSph::Set(sp0C, 30.0f);
        mSph.SetTgType(atType);
        mSph.SetTgGrp(cCcD_TgSPrm_IsOther_e);
        mStts.Init(0xff, 0xff, this);
        mSph.SetStts(&mStts);
        mSph.Set(l_sph_src);
    }
    return TRUE;
}

/* 000007C8-00000930       .text daHmlifCreate__9daHmlif_cFv */
cPhs_State daHmlif_c::daHmlifCreate() {
    fopAcM_SetupActor(this, daHmlif_c);
    m489 = daHmlif_prm::getType(this);
    cPhs_State PVar2 = dComIfG_resLoad(&mPhase, m_arcname[m489]);
    if (PVar2 == cPhs_COMPLEATE_e) {
        PVar2 = MoveBGCreate(m_arcname[m489], m_dzbidx[m489], dBgS_MoveBGProc_TypicalRotY, m_heapsize[m489]);
        if (PVar2 == cPhs_ERROR_e) {
            return cPhs_ERROR_e;
        }
    }
    return PVar2;
}

/* 00000AE8-00000B80       .text set_mtx__9daHmlif_cFv */
void daHmlif_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(current.angle.x, current.angle.y, current.angle.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mBgMtx);
}

/* 00000B80-00000BE4       .text Execute__9daHmlif_cFPPA3_A4_f */
BOOL daHmlif_c::Execute(Mtx** o_mtx) {
    move();
    set_se();
    anim_play();
    check_col();
    *o_mtx = &mBgMtx;
    set_mtx();
    return TRUE;
    ;
}

/* 00000BE4-00000C24       .text move__9daHmlif_cFv */
void daHmlif_c::move() {
    if (m445 != 0xff) {
        if (m47E) {
            lift_smooth_move();
        } else {
            lift_normal_move();
        }
    }
}

/* 00000C24-00000CA8       .text set_se__9daHmlif_cFv */
void daHmlif_c::set_se() {
    if (old.pos != current.pos) {
        fopAcM_seStart(this, JA_SE_OBJ_FLOAT_LIFT_MOVE, 0);
    }
}

/* 00000CA8-00000D94       .text anim_play__9daHmlif_cFv */
void daHmlif_c::anim_play() {
    if (fopAcM_isSwitch(this, m478)) {
        m48A++;
        if (m48A > 3) {
            m48A = 3;
        }
    } else {
        m48A--;
        if (m48A < 0) {
            m48A = 0;
        }
    }

    if (mpBrk != NULL) {
        if (old.pos == current.pos) {
            mpBrk->setPlayMode(J3DFrameCtrl::EMode_NONE);
        } else {
            mpBrk->setPlayMode(J3DFrameCtrl::EMode_LOOP);
            mpBrk->setPlaySpeed(1.0f);
        }
        mpBrk->play();
    }
}

/* 00000D94-00000F10       .text check_col__9daHmlif_cFv */
void daHmlif_c::check_col() {
    if (mSph.ChkTgHit()) {
        cCcD_Obj* pcVar2 = mSph.GetTgHitObj();
        if (pcVar2 != NULL) {
            if (pcVar2->ChkAtType(AT_TYPE_NORMAL_ARROW) || pcVar2->ChkAtType(AT_TYPE_FIRE_ARROW) || pcVar2->ChkAtType(AT_TYPE_ICE_ARROW) ||
                pcVar2->ChkAtType(AT_TYPE_LIGHT_ARROW))
            {
                mSph.ClrTgHit();
                if (!fopAcM_isSwitch(this, m478)) {
                    fopAcM_seStart(this, JA_SE_OBJ_ARROW_SW_ON, 0);
                }
                fopAcM_onSwitch(this, m478);
            }
        }
    }

    if ((m489 == 1) || (m489 == 2)) {
        cXyz sp08 = current.pos;
        if (m489 == 1) {
            sp08.y += 240.0f;
        } else {
            sp08.y -= 250.0f;
        }
        mSph.SetC(sp08);
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 00000F10-000010C4       .text lift_smooth_move__9daHmlif_cFv */
void daHmlif_c::lift_smooth_move() {
    s16 iVar4 = cM_atan2s(m450.x - m45C.x, m450.z - m45C.z);
    f32 speed = fopAcM_GetSpeedF(this);
    f32 fVar1 = m450.x - current.pos.x;
    f32 fVar2 = m450.y - current.pos.y;
    f32 fVar3 = m450.z - current.pos.z;
    f32 sqrt = std::sqrtf(SQUARE(fVar1) + SQUARE(fVar2) + SQUARE(fVar3));
    cLib_addCalcAngleS2(&current.angle.y, iVar4, 10, 0x400);
    cLib_addCalc2(&speedF, m480, 0.4f, 1.0f);

    cXyz sp18;
    sp18.x = sp18.y = 0.0f;
    sp18.z = speed;
    mDoMtx_stack_c::YrotS(current.angle.y);
    cXyz sp0C;
    mDoMtx_stack_c::multVec(&sp18, &sp0C);

    current.pos.x += sp0C.x;
    current.pos.y += sp0C.y;
    current.pos.z += sp0C.z;

    if (sqrt < 80.0f) {
        set_next_pnt();
    }
}

/* 000010C4-00001270       .text lift_normal_move__9daHmlif_cFv */
void daHmlif_c::lift_normal_move() {
    f32 f31 = 50.0f;
    f32 f30 = 4.0f;
    f32 f29 = 1.0f;
    f32 f00 = 2.2f;

    switch (m488) {
    case 0:
        m488 = 1;
        m484 = 0;
        set_next_pnt();

    case 1:
        m484++;
        if (cLib_addCalc(&speedF, m480, 1.0f / f30, f29, m480 / 6.6666665f) == 0.0f) {
            m488 = 2;
        }
        break;

    case 2:
        m484 = 0;
        if ((current.pos - m450).abs() < f31) {
            m488 = 3;
        }
        break;

    case 3:
        m484++;
        if (cLib_addCalc(&speedF, m480 / f00, 1.0f / f30, f29, m480 / 6.6666665f) == 0.0f) {
            m488 = 0;
        }
        break;
    }

    cLib_addCalcPos2(&current.pos, m450, 1.0f, fopAcM_GetSpeedF(this));
}

BOOL daHmlif_c::check_path_point(cXyz, cXyz, cXyz, s8) {
}

/* 00001270-00001410       .text set_next_pnt__9daHmlif_cFv */
void daHmlif_c::set_next_pnt() {
    s8 uVar1 = m448;
    BOOL iVar5 = FALSE;
    if (m445 != 0xff) {
        if (chkSwitchPathType()) {
            int roomNo = fopAcM_GetRoomNo(this);
            if (((ppd == dPath_GetRoomPath(m444, roomNo)) && (uVar1 == ppd->mArg0)) || (ppd != dPath_GetRoomPath(m444, roomNo) && (uVar1 == 0))) {
                iVar5 = setNextPath();
            }
        }

        if (!iVar5) {
            m448 += m446;
            dPath* pdVar2 = ppd;
            if (dPath_ChkClose(ppd)) {
                if (m448 > (s8)pdVar2->m_num - 1) {
                    m448 = 0;
                } else if (m448 < 0) {
                    m448 = pdVar2->m_num - 1;
                }
            } else if (m448 > pdVar2->m_num - 1) {
                m446 = -1;
                m448 = ppd->m_num - 2;
            } else if (m448 < 0) {
                m446 = 1;
                m448 = 1;
            }
        }

        m45C = m450;
        dPnt* pnt = &ppd->m_points[m448];
        m450 = pnt->m_position;
    }
}

/* 00001410-00001520       .text setNextPath__9daHmlif_cFv */
BOOL daHmlif_c::setNextPath() {
    int roomNo = fopAcM_GetRoomNo(this);
    BOOL uVar5 = FALSE;
    dPath* pdVar4 = ppd;
    dPath* pInPath = dPath_GetRoomPath(m444, roomNo);
    dPath* pdVar1 = dPath_GetNextRoomPath(pInPath, roomNo);

    if (fopAcM_isSwitch(this, m474)) {
        if (pdVar4 == pInPath) {
            m447 = m446;
        }
        ppd = pdVar1;
        m448 = 1;
        m446 = 1;
        uVar5 = TRUE;
    } else if (ppd != pInPath) {
        m445 = m444;
        ppd = pInPath;
        if (ppd->mArg0 == ppd->m_num) {
            m447 = -1;
        } else if (ppd->mArg0 == 0) {
            m447 = 1;
        }
        m446 = m447;
        m448 = ppd->mArg0 + m446;
        uVar5 = TRUE;
    }
    return uVar5;
}

/* 00001520-00001534       .text chkSwitchPathType__9daHmlif_cFv */
bool daHmlif_c::chkSwitchPathType() {
    return m474 != 0xFF;
}

/* 00001534-00001610       .text Draw__9daHmlif_cFv */
BOOL daHmlif_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    if (mpBtp != NULL) {
        mpBtp->entry(mpModel->getModelData(), m48A);
    }

    if (mpBrk != NULL) {
        mpBrk->entry(mpModel->getModelData());
    }

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 00001610-00001630       .text daHmlif_Create__FPv */
static cPhs_State daHmlif_Create(void* v_this) {
    return ((daHmlif_c*)v_this)->daHmlifCreate();
}

/* 00001630-00001650       .text daHmlif_Delete__FPv */
static BOOL daHmlif_Delete(void* v_this) {
    return ((daHmlif_c*)v_this)->daHmlifDelete();
}

/* 00001650-0000167C       .text daHmlif_Draw__FPv */
static BOOL daHmlif_Draw(void* v_this) {
    return ((daHmlif_c*)v_this)->MoveBGDraw();
}

/* 0000167C-0000169C       .text daHmlif_Execute__FPv */
static BOOL daHmlif_Execute(void* v_this) {
    return ((daHmlif_c*)v_this)->MoveBGExecute();
}

/* 0000169C-000016A4       .text daHmlif_IsDelete__FPv */
static BOOL daHmlif_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daHmlifMethodTable = {
    (process_method_func)daHmlif_Create,
    (process_method_func)daHmlif_Delete,
    (process_method_func)daHmlif_Execute,
    (process_method_func)daHmlif_IsDelete,
    (process_method_func)daHmlif_Draw,
};

actor_process_profile_definition g_profile_Hmlif = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Hmlif,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daHmlif_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Hmlif,
    /* Actor SubMtd */ &daHmlifMethodTable,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
