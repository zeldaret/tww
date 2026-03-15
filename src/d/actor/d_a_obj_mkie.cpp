/**
 * d_a_obj_mkie.cpp
 * Elephant statue in Earth Temple, that dissolves when hit with light.
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_mkie.h"
#include "d/res/res_mkieb.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

Mtx daObjMkie::Act_c::M_tmp_mtx;
const char daObjMkie::Act_c::M_arcname[] = "MkieB";
const dCcD_SrcTri daObjMkie::Act_c::M_tri_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_ShieldFrontRange_e,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGTriS
    {{
        /* a */ {0.0f, 0.0f, 0.0f},
        /* b */ {0.0f, 0.0f, 0.0f},
        /* c */ {0.0f, 0.0f, 0.0f},
    }},
};
const daObjMkie::Act_c::Attr_c daObjMkie::Act_c::M_attr[2] = {
    {
        "MkieB_die",
        1.0f,
        {
            {
                {-30.0f, 190.0f, 40.0f},
                {-65.0f, 50.0f, 75.0f},
                {65.0f, 50.0f, 75.0f},
            },
            {
                {-30.0f, 190.0f, 40.0f},
                {65.0f, 50.0f, 75.0f},
                {30.0f, 190.0f, 40.0f},
            },
            {
                {38.0f, 190.0f, 20.0f},
                {75.0f, 50.0f, 65.0f},
                {75.0f, 50.0f, -65.0f},
            },
            {
                {38.0f, 190.0f, 20.0f},
                {75.0f, 50.0f, -65.0f},
                {38.0f, 190.0f, -40.0f},
            },
            {
                {30.0f, 190.0f, -60.0f},
                {65.0f, 50.0f, -75.0f},
                {-65.0f, 50.0f, -75.0f},
            },
            {
                {30.0f, 190.0f, -60.0f},
                {-65.0f, 50.0f, -75.0f},
                {-30.0f, 190.0f, -60.0f},
            },
            {
                {-38.0f, 190.0f, -40.0f},
                {-75.0f, 50.0f, -65.0f},
                {-75.0f, 50.0f, 65.0f},
            },
            {{-38.0f, 190.0f, -40.0f}, {-75.0f, 50.0f, 65.0f}, {-38.0f, 190.0f, 20.0f}},
        },
    },
    {"MkieBAB_die",
     3.0f,
     {{
          {-90.0f, 570.0f, 170.0f},
          {-195.0f, 150.0f, 225.0f},
          {195.0f, 150.0f, 225.0f},
      },
      {
          {-90.0f, 570.0f, 170.0f},
          {195.0f, 150.0f, 225.0f},
          {90.0f, 570.0f, 170.0f},
      },
      {
          {120.0f, 570.0f, 60.0f},
          {225.f, 150.0f, 195.0f},
          {225.0f, 150.0f, -195.0f},
      },
      {
          {120.0f, 570.0f, 60.0f},
          {225.0f, 150.0f, -195.0f},
          {120.0f, 570.0f, -120.0f},
      },
      {
          {90.0f, 570.0f, -180.0f},
          {195.0f, 150.0f, -225.0f},
          {-195.0f, 150.0f, -225.0f},
      },
      {
          {90.0f, 570.0f, -180.0f},
          {-195.0f, 150.0f, -225.0f},
          {-90.0f, 570.0f, -180.0f},
      },
      {
          {-120.0f, 570.0f, -120.0f},
          {-225.0f, 150.0f, -195.0f},
          {-225.0f, 150.0f, 195.0f},
      },
      {{-120.0f, 570.0f, -120.0f}, {-225.0f, 150.0f, 195.0f}, {-120.0f, 570.0f, 60.0f}}}}
};

/* 00000078-00000250       .text CreateHeap__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, MKIEB_BDL_MKIEB);
    JUT_ASSERT(0x192, model_data != NULL);
    mModelBase = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);

    J3DModelData* model_data_van = (J3DModelData*)dComIfG_getObjectRes(M_arcname, MKIEB_BDL_YLSMF00);
    JUT_ASSERT(0x19b, model_data_van != NULL);
    mModelVan = mDoExt_J3DModel__create(model_data_van, 0x80000, 0x11000022);

    J3DAnmTevRegKey* brk_van = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, MKIEB_BRK_YLSMF00);
    JUT_ASSERT(0x1a5, brk_van != NULL);
    int init = mBrkVan.init(model_data_van, brk_van, true, 0, 1.0f, 0, -1, false, 0);

    bool ret = false;
    if (mModelBase != NULL && mModelVan != NULL && init != 0) {
        ret = true;
    }
    return ret;
}

/* 00000250-000002EC       .text init_cc__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::init_cc() {
    for (int i = 0; i < 8; i++) {
        mStts[i].Init(0xff, 0xff, this);
        mTri[i].Set(M_tri_src);
        mTri[i].SetStts(&mStts[i]);
        mTri[i].OnTgNoHitMark();
    }
    set_cc_pos();
}

/* 000002EC-00000420       .text set_cc_pos__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::set_cc_pos() {
    for (int i = 0; i < 8; i++) {
        Vec src[3];
        Vec dst[3];
        src[0] = M_attr[mType].table[i][0];
        src[1] = M_attr[mType].table[i][1];
        src[2] = M_attr[mType].table[i][2];
        mDoMtx_multVecArray(mModelBase->getBaseTRMtx(), src, dst, 3);
        mTri[i].setPos(&dst[0], &dst[1], &dst[2]);
    }
}

/* 00000420-00000568       .text Create__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::Create() {
    fopAcM_SetMtx(this, mModelBase->getBaseTRMtx());
    init_mtx();
    {
        const Attr_c* mAttrPtr = M_attr + mType;
        float initialScale = mAttrPtr->mScale;
        fopAcM_setCullSizeBox(
            this, initialScale * -80.0f, initialScale * -1.0f, initialScale * -80.0f, initialScale * 80.0f, initialScale * 230.0f, initialScale * 80.0f
        );
    }
    init_cc();

    if (daObj::PrmAbstract<Prm_e>(this, PRM_FLAG_W, PRM_FLAG_S) != 0) {
        actor_status &= ~0x3F;
        gbaName = 0;
    }

    mCcInit = false;
    mBaseAnmPlaying = false;

    {
        const Attr_c* mAttrPtr = M_attr + mType;
        attention_info.position.y = current.pos.y + mAttrPtr->mScale * 130.0f;
    }
    eyePos = attention_info.position;
    mEvtIdx = dComIfGp_evmng_getEventIdx(M_attr[mType].name, prm_get_evId());
    return true;
}

/* 00000568-00000754       .text Mthd_Create__Q29daObjMkie5Act_cFv */
cPhs_State daObjMkie::Act_c::Mthd_Create() {
    cPhs_State phase_state = cPhs_ERROR_e;
    fopAcM_ct(this, daObjMkie::Act_c);
    mSwitch = !fopAcM_isSwitch(this, prm_get_swSave());
    if (mSwitch && (phase_state = dComIfG_resLoad(&mPhs, M_arcname), phase_state == cPhs_COMPLEATE_e)) {
        mType = prm_get_type();
        const Attr_c* mAttrPtr = M_attr + mType;
        float initialScale = mAttrPtr->mScale;
        scale.setall(initialScale);
        phase_state = MoveBGCreate(M_arcname, MKIEB_DZB_MKIEB, dBgS_MoveBGProc_Trans, 0x1b20);
        JUT_ASSERT(0x216, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000BF0-00000BF8       .text Delete__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::Delete() {
    return true;
}

/* 00000BF8-00000C54       .text Mthd_Delete__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::Mthd_Delete() {
    BOOL ret = true;
    if (mSwitch != false) {
        ret = MoveBGDelete();
        dComIfG_resDelete(&mPhs, M_arcname);
    }
    return ret;
}

/* 00000C54-00000CF8       .text set_mtx__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModelBase->setBaseTRMtx(mDoMtx_stack_c::get());
    mModelVan->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale);
    cMtx_copy(mDoMtx_stack_c::now, M_tmp_mtx);
}

/* 00000CF8-00000D50       .text init_mtx__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::init_mtx() {
    mModelBase->setBaseScale(scale);
    mModelVan->setBaseScale(scale);
    set_mtx();
}

/* 00000D50-00000DF4       .text chk_light__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::chk_light() {
    BOOL ret = false;

    if (dComIfGp_getDetect().chk_light(&eyePos)) {
        ret = true;
    } else {
        for (int i = 0; i < 8; i++) {
            if (mTri[i].ChkTgHit()) {
                mTri[i].ClrTgHit();
                ret = true;
            }
        }
    }
    return ret;
}

/* 00000DF4-00000E84       .text eff_break__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::eff_break() {
    _GXColor envColor;
    envColor.r = (u8)tevStr.mColorC0.r;
    envColor.g = (u8)tevStr.mColorC0.g;
    envColor.b = (u8)tevStr.mColorC0.b;
    envColor.a = (u8)tevStr.mColorC0.a;

    dComIfGp_particle_set(dPa_name::ID_SCENE_81A0, &current.pos, &shape_angle, &scale, 0xff, NULL, -1, &tevStr.mColorK0, &envColor, NULL);
}

/* 00000E84-00000EF4       .text sound_melt__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::sound_melt() {
    fopAcM_seStart(this, JA_SE_OBJ_L_OBJ_BRK_TAME, 0);
}

/* 00000EF4-00000F7C       .text sound_break__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::sound_break() {
    static const u32 se_break[] = {
        JA_SE_OBJ_L_STATUE_BREAK,
        JA_SE_OBJ_L_STATUE_L_BREAK,
    };
    fopAcM_seStart(this, se_break[mType], 0);
}

/* 00000F7C-00000FD0       .text vib_break__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::vib_break() {
    dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
}

/* 00000FD0-00001094       .text mode_wait__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_wait() {
    if (chk_light() & 0xff) {
        mLightCnt += 1;
    } else {
        mLightCnt = 0;
    }

    if (mLightCnt > 20) {
        mode_demoWait_init();
    } else {
        if (mCcInit != false) {
            set_cc_pos();
        }
        if (!fopAcM_cullingCheck(this)) {
            for (int i = 0; i < 8; i++) {
                dComIfG_Ccsp()->Set(&mTri[i]);
            }
        }
    }
}

/* 00001094-000010A8       .text mode_demoWait_init__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_demoWait_init() {
    mEvtPlaying = false;
    mModeProc = 1;
}

/* 000010A8-00001168       .text mode_demoWait__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_demoWait() {
    bool demo = false;

    if (dComIfGp_evmng_existence(mEvtIdx)) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            demo = true;
            mEvtPlaying = true;
        } else {
            fopAcM_orderOtherEventId(this, mEvtIdx, prm_get_evId());
            eventInfo.onCondition(2);
        }
    } else {
        demo = true;
    }

    if (demo) {
        mode_demo_init();
    }
}

/* 00001168-000011FC       .text mode_demo_init__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_demo_init() {
    mModeProc = 2;
    mState = 10;
    if (!prm_get_correct()) {
        mDoAud_seStart(JA_SE_READ_RIDDLE_1);
    }
    mBroken = false;
    mBaseAnmPlaying = false;
}

/* 000011FC-00001338       .text mode_demo__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_demo() {
    if (mState > 0 && (mState -= 1, mState == 0)) {
        eff_break();
        sound_melt();
        fopAcM_onSwitch(this, prm_get_swSave());
    }

    if (mState == 0) {
        mBaseAnmPlaying = mBrkVan.play();
        if (!mBroken && mBaseAnmPlaying) {
            sound_break();
            vib_break();
            mBroken = true;
        }
    }

    if (mEvtPlaying && dComIfGp_evmng_endCheck(mEvtIdx)) {
        dComIfGp_event_reset();
        mEvtPlaying = false;
    }

    if (!mEvtPlaying && mState == 0 && mBaseAnmPlaying) {
        mStatueDelete = true;
    }
}

/* 00001338-000013DC       .text mode_proc_call__Q29daObjMkie5Act_cFv */
void daObjMkie::Act_c::mode_proc_call() {
    static void (Act_c::* mode_proc[])() = {
        &Act_c::mode_wait,
        &Act_c::mode_demoWait,
        &Act_c::mode_demo,
    };

    (this->*mode_proc[mModeProc])();
}

/* 000013DC-000014A0       .text Execute__Q29daObjMkie5Act_cFPPA3_A4_f */
BOOL daObjMkie::Act_c::Execute(Mtx** pMtx) {
    attention_info.position.x = current.pos.x;
    const Attr_c* mAttrPtr = M_attr + mType;
    attention_info.position.y = current.pos.y + mAttrPtr->mScale * 130.0f;
    attention_info.position.z = current.pos.z;

    eyePos = attention_info.position;
    mode_proc_call();
    if (mStatueDelete) {
        fopAcM_delete(this);
    }
    mCcInit = false;
    set_mtx();
    *pMtx = &M_tmp_mtx;
    return true;
}

/* 000014A0-000015B8       .text Draw__Q29daObjMkie5Act_cFv */
BOOL daObjMkie::Act_c::Draw() {
    if (!mBaseAnmPlaying) {
        bool flagVan = false;
        if (mModeProc == 2) {
            if (mState == 0) {
                flagVan = true;
            }
        }
        g_env_light.settingTevStruct(0, &current.pos, &tevStr);
        if (flagVan) {
            g_env_light.setLightTevColorType(mModelVan, &tevStr);
            J3DModelData* modelData = mModelVan->getModelData();
            mBrkVan.entry(modelData, mBrkVan.getFrame());
        } else {
            g_env_light.setLightTevColorType(mModelBase, &tevStr);
        }

        dComIfGd_setListBG();
        if (flagVan) {
            mDoExt_modelUpdateDL(mModelVan);
        } else {
            mDoExt_modelUpdateDL(mModelBase);
        }
        dComIfGd_setList();
    }

    return true;
}

namespace daObjMkie {
namespace {
/* 000015B8-000015D8       .text Mthd_Create__Q29daObjMkie26@unnamed@d_a_obj_mkie_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjMkie::Act_c*)i_this)->Mthd_Create();
}

/* 000015D8-000015F8       .text Mthd_Delete__Q29daObjMkie26@unnamed@d_a_obj_mkie_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjMkie::Act_c*)i_this)->Mthd_Delete();
}

/* 000015F8-00001618       .text Mthd_Execute__Q29daObjMkie26@unnamed@d_a_obj_mkie_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjMkie::Act_c*)i_this)->MoveBGExecute();
}

/* 00001618-00001644       .text Mthd_Draw__Q29daObjMkie26@unnamed@d_a_obj_mkie_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjMkie::Act_c*)i_this)->MoveBGDraw();
}

/* 00001644-00001670       .text Mthd_IsDelete__Q29daObjMkie26@unnamed@d_a_obj_mkie_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjMkie::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjMkie

actor_process_profile_definition g_profile_Obj_Mkie = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Mkie,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMkie::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Mkie,
    /* Actor SubMtd */ &daObjMkie::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
