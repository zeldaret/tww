/**
 * d_a_npc_kg2.cpp
 * NPC - Salvatore (Cannon Minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_snap.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* Height */ 80.0f,
    }},
};


/* 000000EC-00000194       .text __ct__15daNpc_Kg2_HIO_cFv */
daNpc_Kg2_HIO_c::daNpc_Kg2_HIO_c() {
    /* Nonmatching */
}

/* 00000194-00000368       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000003A4-0000048C       .text set_mtx__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::set_mtx() {
    /* Nonmatching */
}

/* 0000048C-000005A0       .text initTexPatternAnm__11daNpc_Kg2_cFb */
void daNpc_Kg2_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 000005A0-000006EC       .text playTexPatternAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 000006EC-00000838       .text setAnm__11daNpc_Kg2_cFScf */
void daNpc_Kg2_c::setAnm(signed char, float) {
    /* Nonmatching */
}

/* 00000838-000009E8       .text subAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::subAnm() {
    /* Nonmatching */
}

/* 000009E8-00000B3C       .text chkAttention__11daNpc_Kg2_cF4cXyzs */
BOOL daNpc_Kg2_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000B3C-00000BC0       .text eventOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::eventOrder() {
    /* Nonmatching */
}

/* 00000BC0-00000CC4       .text checkOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::checkOrder() {
    /* Nonmatching */
}

/* 00000CC4-00000E38       .text getMsg__11daNpc_Kg2_cFv */
u32 daNpc_Kg2_c::getMsg() {
    /* Nonmatching */
}

/* 00000E38-00001028       .text next_msgStatus__11daNpc_Kg2_cFPUl */
u16 daNpc_Kg2_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001028-000012EC       .text anmAtr__11daNpc_Kg2_cFUs */
void daNpc_Kg2_c::anmAtr(u16) {
    /* Nonmatching */
}

/* 000012EC-00001308       .text setAttention__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::setAttention() {
    /* Nonmatching */
}

/* 00001308-00001448       .text lookBack__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::lookBack() {
    /* Nonmatching */
}

/* 00001448-00001468       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001468-0000180C       .text CreateHeap__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000180C-00001A9C       .text CreateInit__11daNpc_Kg2_cFv */
int daNpc_Kg2_c::CreateInit() {
    /* Nonmatching */
    mActorAngle = current.angle;

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6E;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6E;

    gravity = -30.0f;
    setAction(&daNpc_Kg2_c::wait_action, NULL);

    mAttPos = current.pos;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    setCollision(60.0f, 150.0f);

    mEventCut.setActorInfo2("Kg2", this);
    mEventCut.setJntCtrlPtr(&m_jnt);

    field_0x72A[10] = 0;
    field_0x72A[11] = 0;
    field_0x72A[12] = 0;
    field_0x72A[13] = 0;

    field_0x74C = 0;

    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;

    field_0x750[0] = 0;
    mEventIdx = 4;

    mEventIdTable[0] = dComIfGp_evmng_getEventIdx("KG2_START_DEMO");
    mEventIdTable[1] = dComIfGp_evmng_getEventIdx("KG2_CLEAR_DEMO");
    mEventIdTable[2] = dComIfGp_evmng_getEventIdx("KG2_GETDEMO");
    mEventIdTable[3] = dComIfGp_evmng_getEventIdx("CANON_GAME");
    set_mtx();

    if (dComIfGs_getTime() >= 105.0f && dComIfGs_getTime() < 300.0f) {
        field_0x72A[0xC] = 0;  // field_0x738 = 0
        setAnm(1, -1.0f);
    } else {
        field_0x72A[0xC] = 1;  // field_0x738 = 1
        setAnm(13, 0.0f);
    }

    l_kg2_pointer = this;
    return 1;
}

/* 00001A9C-00001BDC       .text wait01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::wait01() {
    /* Nonmatching */
}

/* 00001BDC-00001CA4       .text talk01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::talk01() {
    /* Nonmatching */
}

/* 00001CA4-00001D88       .text evn_setAnm_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_setAnm_init(int) {
    /* Nonmatching */
}

/* 00001D88-00001E4C       .text evn_setAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::evn_setAnm() {
    /* Nonmatching */
}

/* 00001E4C-00001F14       .text evn_jnt_lock_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_jnt_lock_init(int) {
    /* Nonmatching */
}

/* 00001F14-00001F88       .text evn_talk_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00001F88-00001FBC       .text evn_talk__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::evn_talk() {
    /* Nonmatching */
}

/* 00001FBC-00002070       .text evn_createItem_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_createItem_init(int) {
    /* Nonmatching */
}

/* 00002070-000021EC       .text privateCut__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::privateCut() {
    /* Nonmatching */
}

/* 000021EC-00002250       .text processMove__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::processMove() {
    /* Nonmatching */
}

/* 00002250-00002334       .text wait_action__11daNpc_Kg2_cFPv */
int daNpc_Kg2_c::wait_action(void*) {
    if (mActionStatus == 0) {
        field_0x760 = 1;
        mActionStatus += 1;
    } else if (mActionStatus != -1) {
        s16 local_1 = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        field_0x72C = chkAttention(current.pos, local_1);
        field_0x750[0] = 0;
        switch(field_0x760) {
            case 1:
                wait01();
                break;
            case 2:
                talk01();
                break;
        }
        lookBack();
        setAttention();
    }
    return 1;
}

/* 00002334-00002590       .text event_wait_action__11daNpc_Kg2_cFPv */
u32 daNpc_Kg2_c::event_wait_action(void*) {
    if (mActionStatus == 0) {
        field_0x760 = 1;
        mActionStatus += 1;
    } else if (mActionStatus != -1) {
        s16 local_1 = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        field_0x72C = chkAttention(current.pos, local_1);
        lookBack();
        setAttention();

        if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
            if (mEventIdx == 0) {
                field_0x750[0] = 3;
                mEventIdx = 3;
            } else if (mEventIdx == 3) {
                if (canon_game_result == 1) {
                    field_0x750[0] = 3;
                    mEventIdx = 1;
                } else {
                    field_0x750[0] = 1;
                    field_0x74C = 0x314E;
                }
            } else if (mEventIdx == 1) {
                field_0x750[0] = 3;
                mEventIdx = 2;
                u8 local_2 = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B703) + 1, 3);
                dComIfGs_setEventReg(dSv_event_flag_c::UNK_B703, local_2);
            } else if (mEventIdx == 2) {
                field_0x750[0] = 1;
                field_0x74C = 0x315A;
            } else {
                mEventIdx = 4;
            }

            dComIfGp_event_reset();
            setAction(&daNpc_Kg2_c::wait_action, NULL);
        }
    }
    return 1;
}

/* 00002590-000027BC       .text _create__11daNpc_Kg2_cFv */
cPhs_State daNpc_Kg2_c::_create() {
    /* Nonmatching */
}

/* 00002B6C-00002BFC       .text _delete__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_delete() {
    /* Nonmatching */
}

/* 00002BFC-00002D14       .text _execute__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_execute() {
    /* Nonmatching */
}

/* 00002D14-00002E74       .text _draw__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_draw() {
    /* Nonmatching */
    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    mBtpAnm.entry(model_data, field_0x704);
    mpMorf->entryDL();
    model_data->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());

    if (field_0x72A[0xB] != NULL) {
        model_data = field_0x6D4->getModelData();
        g_env_light.setLightTevColorType(field_0x6D4, &tevStr);
        field_0x6D8.entry(model_data, field_0x737);
        mDoExt_modelUpdateDL(field_0x6D4);
        model_data->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());
    }

    cXyz shadow_pos(
        current.pos.z,
        current.pos.y + 150.0f,
        current.pos.x
    );

    mShadowId = dComIfGd_setShadow(
        mShadowId,
        1,
        mpMorf->getModel(),
        &shadow_pos,
        800.0f,
        20.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr
    );

    dSnap_RegistFig(DSNAP_TYPE_NPC_KG2, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return true;
}

/* 00002E74-00002E94       .text daNpc_Kg2_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kg2_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_create();
}

/* 00002E94-00002EB4       .text daNpc_Kg2_Delete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Delete(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_delete();
}

/* 00002EB4-00002ED4       .text daNpc_Kg2_Execute__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Execute(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_execute();
}

/* 00002ED4-00002EF4       .text daNpc_Kg2_Draw__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Draw(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_draw();
}

/* 00002EF4-00002EFC       .text daNpc_Kg2_IsDelete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_IsDelete(daNpc_Kg2_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kg2_Method = {
    (process_method_func)daNpc_Kg2_Create,
    (process_method_func)daNpc_Kg2_Delete,
    (process_method_func)daNpc_Kg2_Execute,
    (process_method_func)daNpc_Kg2_IsDelete,
    (process_method_func)daNpc_Kg2_Draw,
};

actor_process_profile_definition g_profile_NPC_KG2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg2_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG2_e,
    /* Actor SubMtd */ &l_daNpc_Kg2_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
