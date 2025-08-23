/**
 * d_a_obj_vmc.cpp
 * Object - Mound of soft soil + Makar tree
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vmc.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_vmc.h"

enum {
    STATE_BASE_MAIN,
    STATE_TREE_DEMO_WAIT,
    STATE_TREE_DEMO_MAIN,
    STATE_TREE_MAIN,
};

static dCcD_SrcCyl cyl_src_base = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_NoCrr_e,
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
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 10.0f,
    }},
};

#if VERSION == VERSION_DEMO
static dCcD_SrcCyl cyl_src_tree = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG | AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_IsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
        /* Height */ 300.0f,
    }},
};
#endif

const char daObjVmc::Act_c::M_arcname[4] = "Vmc";

/* 00000078-0000009C       .text solidHeapCB__Q28daObjVmc5Act_cFP10fopAc_ac_c */
BOOL daObjVmc::Act_c::solidHeapCB(fopAc_ac_c* i_ac) {
    return ((Act_c*)i_ac)->create_heap();
}

/* 0000009C-00000400       .text create_heap__Q28daObjVmc5Act_cFv */
bool daObjVmc::Act_c::create_heap() {
    /* Nonmatching */
    J3DModelData* mdl_bs_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, VMC_BDL_VMCBS);
    JUT_ASSERT(200, mdl_bs_data != NULL);
    mModelBase = mDoExt_J3DModel__create(mdl_bs_data, 0, 0x11020203);
    if (mModelBase == NULL)
        return false;

    J3DModelData* mdl_wd_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, VMC_BDL_VMCWD);
    JUT_ASSERT(207, mdl_wd_data != NULL);
    mModelTree = mDoExt_J3DModel__create(mdl_wd_data, 0, 0x11020203);
    if (mModelTree == NULL)
        return false;

    {
        J3DAnmTransform* bck_wg = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, VMC_BCK_VMCWG);
        JUT_ASSERT(215, bck_wg != NULL);
        BOOL ret = mBckAnmGrow.init(mdl_wd_data, bck_wg, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
        mBckAnmGrow.setPlaySpeed(0.75f);
        if (!ret)
            return false;
    }

    {
        J3DAnmTransform* bck_wh = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, VMC_BCK_VMCWH);
        JUT_ASSERT(226, bck_wh != NULL);
        if (!mBckAnmHookshot.init(mdl_wd_data, bck_wh, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false))
            return false;
    }

    BOOL ret = true;

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtxBase);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtxTree);

    mpBgBase = new dBgW();
    if (mpBgBase == NULL || mpBgBase->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, VMC_DZB_VMCBS), dBgW::MOVE_BG_e, &mMtxBase))
        ret = false;

    mpBgTree = new dBgW();
    if (mpBgTree == NULL || mpBgTree->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, VMC_DZB_VMCWD), dBgW::MOVE_BG_e, &mMtxTree))
        ret = false;

    if (ret != true)
        return false;
    return true;
}

/* 00000400-000005BC       .text CreateInit__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::CreateInit() {
    /* Nonmatching */
    fopAcM_SetMtx(this, mModelBase->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -0.0f, -300.0, 300.0f, 500.0f, 300.0f);
    mStts.Init(255, 255, this);
    mCyl.Set(cyl_src_base);
    mCyl.SetStts(&mStts);
    dComIfG_Bgsp()->Regist(mpBgBase, this);
    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        if (!dComIfG_Bgsp()->Regist(mpBgTree, this))
            mHasTreeBg = true;

        mBckAnmGrow.setFrame(mBckAnmGrow.getEndFrame());
#if VERSION == VERSION_DEMO
        mCyl.Set(cyl_src_tree);
#endif
        mState = STATE_TREE_MAIN;
        mHasTree = true;
    } else {
        mState = STATE_BASE_MAIN;
        mHasTree = false;
    }

    init_mtx();
    mHookshotAnim = false;
#if VERSION == VERSION_DEMO
    m4B4_demo = NULL;
#endif
    mSmoke.setRateOff(0);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA7;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA7;
    attention_info.position = current.pos;
    attention_info.position.y += 40.0f;
    eyePos = attention_info.position;
    mLinkRangeCheck = true;
    eventInfo.setEventName("cb_sow");
}

/* 000005BC-00000730       .text _create__Q28daObjVmc5Act_cFv */
cPhs_State daObjVmc::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    mHasTreeBg = false;

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x32a0) != 0) {
            CreateInit();
        } else {
            ret = cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 0000098C-00000A14       .text _delete__Q28daObjVmc5Act_cFv */
bool daObjVmc::Act_c::_delete() {
    dComIfG_Bgsp()->Release(mpBgBase);
    if (mHasTreeBg == 1)
        dComIfG_Bgsp()->Release(mpBgTree);
    mSmoke.end();
    dComIfG_resDeleteDemo(&mPhs, M_arcname);
    return true;
}

/* 00000A14-00000AC4       .text set_mtx__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mModelBase->setBaseTRMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModelTree->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000AC4-00000B1C       .text init_mtx__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::init_mtx() {
    mModelBase->setBaseScale(scale);
    mModelTree->setBaseScale(scale);
    set_mtx();
}

/* 00000B1C-00000BD0       .text daObjVmc_base_main__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::daObjVmc_base_main() {
    if (mHasTree == 1) {
#if VERSION == VERSION_DEMO
        m4B4_demo =
#endif
        dComIfGp_particle_setToon(dPa_name::ID_SCENE_A1BC, &current.pos, &current.angle, NULL, 0xFF, &mSmoke, fopAcM_GetRoomNo(this));
#if VERSION == VERSION_DEMO
        mCyl.Set(cyl_src_tree);
#endif
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_UNK10000000_e);
        mState = STATE_TREE_DEMO_WAIT;
        shape_angle.y = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0)) + 0x1800;
        mTimer = 0;
    }
}

/* 00000BD0-00000BDC       .text daObjVmc_tree_demo_wait__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::daObjVmc_tree_demo_wait() {
    mState = STATE_TREE_DEMO_MAIN;
}

/* 00000BDC-00000D54       .text daObjVmc_tree_demo_main__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::daObjVmc_tree_demo_main() {
    mTimer++;
    if (mTimer == 10) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_CB_SEED_GERMIN, 0);
    } else if (mTimer == 40) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_CB_SEED_GROW, 0);
    }

    mBckAnmGrow.play();
    if (mBckAnmGrow.isStop()) {
        mState = STATE_TREE_MAIN;
        if (!dComIfG_Bgsp()->Regist(mpBgTree, this)) {
            mHasTreeBg = true;
        }
        fopAcM_OnStatus(this, fopAcStts_UNK200000_e);
        fopAcM_onSwitch(this, prm_get_swSave());
    }
}

/* 00000D54-00000EDC       .text daObjVmc_tree_main__Q28daObjVmc5Act_cFv */
void daObjVmc::Act_c::daObjVmc_tree_main() {
    if (!mHookshotAnim) {
        if (mCyl.ChkCoHit()) {
            J3DAnmTransform* bck_wh = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, VMC_BCK_VMCWH);
            JUT_ASSERT(DEMO_SELECT(430, 429), bck_wh != NULL);
            mBckAnmHookshot.init(mModelTree->getModelData(), bck_wh, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true);
            mHookshotAnim = true;
        }
    } else {
        if (mBckAnmHookshot.isStop()) {
            mHookshotAnim = false;
        } else {
            mBckAnmHookshot.play();
        }
    }

    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj != NULL) {
            fopAc_ac_c* at = hitObj->GetAc();
            if (at != NULL && fopAcM_GetName(at) == PROC_HOOKSHOT)
                dComIfGs_onEventBit(0x3420);
        }
    }
}

/* 00000EDC-000011D0       .text _execute__Q28daObjVmc5Act_cFv */
bool daObjVmc::Act_c::_execute() {
    /* Nonmatching */
    mCyl.SetC(current.pos);
#if VERSION > VERSION_DEMO
    if (mState == STATE_BASE_MAIN)
#endif
    {
        dComIfG_Ccsp()->Set(&mCyl);
    }

    switch (mState) {
    case STATE_BASE_MAIN:
        daObjVmc_base_main();
        break;
    case STATE_TREE_DEMO_WAIT:
        daObjVmc_tree_demo_wait();
        break;
    case STATE_TREE_DEMO_MAIN:
        daObjVmc_tree_demo_main();
        break;
    case STATE_TREE_MAIN:
        daObjVmc_tree_main();
        break;
    }
    set_mtx();

    cXyz dist = dComIfGp_getLinkPlayer()->current.pos - current.pos;
    if (!mLinkRangeCheck) {
#if VERSION <= VERSION_JPN
        if (dist.absXZ() > 110.0f)
#else
        if (dist.absXZ() > 110.0f || dist.y < -500.0f || dist.y > 500.0f)
#endif
            mLinkRangeCheck = true;
    } else {
#if VERSION <= VERSION_JPN
        if (dist.absXZ() < 100.0f)
#else
        if (dist.absXZ() < 100.0f && dist.y > -490.0f && dist.y < 490.0f)
#endif
            mLinkRangeCheck = false;
    }

    if (mLinkRangeCheck == true && dComIfGp_getCb1Player() != NULL && fopAcM_GetName(dComIfGp_getCb1Player()) == PROC_NPC_CB1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }

    if (mLinkRangeCheck == true && !mHasTree && fopAcM_GetName(dComIfGp_getPlayer(0)) == PROC_NPC_CB1) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_UNK10000000_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
    } else {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_UNK10000000_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
    }

    return true;
}

/* 000011D0-000012CC       .text _draw__Q28daObjVmc5Act_cFv */
bool daObjVmc::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModelBase, &tevStr);
    g_env_light.setLightTevColorType(mModelTree, &tevStr);
    if (mState < STATE_TREE_MAIN) {
        mBckAnmGrow.entry(mModelTree->getModelData());
    } else {
        mBckAnmHookshot.entry(mModelTree->getModelData());
    }
    mDoExt_modelUpdateDL(mModelTree);
    if (mState < STATE_TREE_MAIN) {
        mBckAnmGrow.remove(mModelTree->getModelData());
    } else {
        mBckAnmHookshot.remove(mModelTree->getModelData());
    }
    mDoExt_modelUpdateDL(mModelBase);
    return true;
}

namespace daObjVmc {
namespace {
/* 000012CC-000012EC       .text Mthd_Create__Q28daObjVmc25@unnamed@d_a_obj_vmc_cpp@FPv */
cPhs_State Mthd_Create(void* i_ac) {
    return ((Act_c*)i_ac)->_create();
}

/* 000012EC-00001310       .text Mthd_Delete__Q28daObjVmc25@unnamed@d_a_obj_vmc_cpp@FPv */
BOOL Mthd_Delete(void* i_ac) {
    return ((Act_c*)i_ac)->_delete();
}

/* 00001310-00001334       .text Mthd_Execute__Q28daObjVmc25@unnamed@d_a_obj_vmc_cpp@FPv */
BOOL Mthd_Execute(void* i_ac) {
    return ((Act_c*)i_ac)->_execute();
}

/* 00001334-00001358       .text Mthd_Draw__Q28daObjVmc25@unnamed@d_a_obj_vmc_cpp@FPv */
BOOL Mthd_Draw(void* i_ac) {
    return ((Act_c*)i_ac)->_draw();
}

/* 00001358-00001360       .text Mthd_IsDelete__Q28daObjVmc25@unnamed@d_a_obj_vmc_cpp@FPv */
BOOL Mthd_IsDelete(void* i_ac) {
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
}; // namespace daObjVmc

actor_process_profile_definition g_profile_Obj_Vmc = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Vmc,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVmc::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Vmc,
    /* Actor SubMtd */ &daObjVmc::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
