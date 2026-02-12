/**
 * d_a_daiocta.cpp
 * Mini-Boss - Big Octo (body)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta.h"
#include "d/actor/d_a_bomb.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static daDaiocta_HIO_c l_HIO;

const s32 daDaiocta_c::m_heapsize = 63296; 
const char daDaiocta_c::m_arc_name[] = "daiocta";

const dCcD_SrcSph daDaiocta_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


const dCcD_SrcCps daDaiocta_c::m_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


/* 000000EC-000002B0       .text __ct__15daDaiocta_HIO_cFv */
daDaiocta_HIO_c::daDaiocta_HIO_c() {
    field_0x004 = 0;
    field_0x008 = 0;
    field_0x006 = 0;
    field_0x005 = 0;
    field_0x01C = 600.0;
    field_0x020 = 500.0;
    field_0x024 = 450.0;
    field_0x028 = 350.0;
    field_0x02C = 350.0;
    field_0x030 = 300.0;
    field_0x034 = 60.0;
    field_0x038 = 60.0;
    field_0x03C = 60.0;
    field_0x040 = 60.0;
    field_0x044 = 60.0;
    field_0x048 = 60.0;
    field_0x04C = 60.0;
    field_0x050 = 60.0;
    field_0x054 = 60.0;
    field_0x058 = 60.0;
    field_0x05C = 100.0;
    field_0x060 = 100.0;
    field_0x064 = 250.0;
    field_0x068 = 100.0;
    field_0x06C = 150.0;
    field_0x070 = 100.0;
    field_0x074 = 150.0;
    field_0x00C = 0x1e;
    field_0x00E = 0x3c;
    field_0x078 = 5000.0;
    field_0x07C = 4500.0;
    field_0x080 = 30.0;
    field_0x010 = 0x100;
    field_0x084 = 1800.0;
    field_0x012 = 0x1500;
    field_0x088 = 40.0;
    field_0x08C = 1.0;
    field_0x090 = 0.02;
    field_0x094 = 150.0;
    field_0x014 = -0x800;
    field_0x0FC = 0.0;
    field_0x100 = 5.0;
    field_0x104 = 700.0;
    field_0x0C0 = 8.0;
    field_0x0C4 = 8.0;
    field_0x0C8 = 3.0;
    field_0x0CC = 3.0;
    field_0x0D0 = 3.0;
    field_0x0D4 = 7.0;
    field_0x0D8 = 9.0;
    field_0x09C = 1.0;
    field_0x0A0 = 0.5;
    field_0x0A4 = 0.75;
    field_0x0A8 = 0.625;
    field_0x0AC = 0.625;
    field_0x0B0 = 0.5;
    field_0x0B4 = 1.0;
    field_0x0B8 = 1.0;
    field_0x0E0 = 20.0;
    field_0x016 = 0x1e;
    field_0x0E4 = 300.0;
    field_0x0E8 = 1200.0;
    field_0x0EC = 1.0;
    field_0x0F0 = 2.0;
    field_0x0F4 = 10.0;
    field_0x0F8 = 30.0;
    field_0x018 = 0x2d;
}

/* 00000334-00000358       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void coHit_CB(fopAc_ac_c* i_this, dCcD_GObjInf* i_unused1P, fopAc_ac_c* i_actor, dCcD_GObjInf* i_unused2P) {
    UNUSED(i_unused1P); UNUSED(i_unused2P);
    ((daDaiocta_c*)i_this)->_coHit(i_actor);
}

/* 00000358-000003DC       .text _coHit__11daDaiocta_cFP10fopAc_ac_c */
void daDaiocta_c::_coHit(fopAc_ac_c* i_actor) {
    if (i_actor != NULL && fpcM_GetName(i_actor) == PROC_BOMB) {
        daBomb_c* bomb_p = (daBomb_c *) i_actor;
        if ((field_0x056C == 2 || field_0x056C == 4 || field_0x056C == 1 || field_0x056C == 3) && 
            bomb_p->chk_state(daBomb_c::STATE_4)) {
            modeProc((Proc_e) 0, (Mode_e) 4);
        }
    }
}

/* 000003DC-00000470       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daDaiocta_c* actor_p = (daDaiocta_c *) model_p->getUserArea();
        JUT_ASSERT(0x1A4, actor_p != NULL);
        actor_p->_nodeControl(i_nodeP, model_p);
    }
    return TRUE;
}

/* 00000470-0000066C       .text _nodeControl__11daDaiocta_cFP7J3DNodeP8J3DModel */
void daDaiocta_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));
    mDoMtx_stack_c::multVecZero(&field_0x0290[jnt_no]);

    cXyz base;
    switch (jnt_no) {
        case 30:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21A0);
            break;
        case 36:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21AC);
            break;
        case 20:
            base.set(l_HIO.field_0x094, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x2434);
            break;
        case 6:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21B8);
            break;
        case 9:
            base.set(300.0f, -200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21C4);
            break; 
        case 7:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21D0);
            break;
        case 10:
            base.set(300.0f, 200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21DC);
            break;
        case 8:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21E8);
            break;
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000066C-0000068C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daDaiocta_c *)i_this)->_createHeap();
}

/* 0000068C-00000708       .text _createHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::_createHeap() {
    /* Nonmatching */
}

/* 00000708-000009B8       .text createAwaHeap__11daDaiocta_cFv */
void daDaiocta_c::createAwaHeap() {
    /* Nonmatching */
}

/* 000009B8-00000ABC       .text createSuikomiHeap__11daDaiocta_cFv */
void daDaiocta_c::createSuikomiHeap() {
    /* Nonmatching */
}

/* 00000ABC-00000C04       .text createBodyHeap__11daDaiocta_cFv */
void daDaiocta_c::createBodyHeap() {
    /* Nonmatching */
}

/* 00000C04-00000C64       .text createArrowHitHeap__11daDaiocta_cFv */
void daDaiocta_c::createArrowHitHeap() {
    /* Nonmatching */
}

/* 00000C64-00000D94       .text setMtx__11daDaiocta_cFv */
void daDaiocta_c::setMtx() {
    /* Nonmatching */
}

/* 00000D94-00000E2C       .text setSuikomiMtx__11daDaiocta_cFv */
void daDaiocta_c::setSuikomiMtx() {
    /* Nonmatching */
}

/* 00000E2C-00000EDC       .text setAwaMtx__11daDaiocta_cFv */
void daDaiocta_c::setAwaMtx() {
    /* Nonmatching */
}

/* 00000EDC-00000F70       .text initMtx__11daDaiocta_cFv */
void daDaiocta_c::initMtx() {
    /* Nonmatching */
}

/* 00000F70-0000116C       .text setEffect__11daDaiocta_cFUs */
void daDaiocta_c::setEffect(unsigned short) {
    /* Nonmatching */
}

/* 0000116C-0000129C       .text setAwaRandom__11daDaiocta_cFi */
void daDaiocta_c::setAwaRandom(int) {
    /* Nonmatching */
}

/* 0000129C-000013D8       .text initAwa__11daDaiocta_cFv */
void daDaiocta_c::initAwa() {
    /* Nonmatching */
}

/* 000013D8-00001548       .text execAwa__11daDaiocta_cFv */
void daDaiocta_c::execAwa() {
    /* Nonmatching */
}

/* 00001548-000015E8       .text isLivingEye__11daDaiocta_cFv */
void daDaiocta_c::isLivingEye() {
    /* Nonmatching */
}

/* 000015E8-00001684       .text isDead__11daDaiocta_cFv */
void daDaiocta_c::isDead() {
    /* Nonmatching */
}

/* 00001684-0000171C       .text isDamageEye__11daDaiocta_cFv */
void daDaiocta_c::isDamageEye() {
    /* Nonmatching */
}

/* 0000171C-000017B4       .text isDamageBombEye__11daDaiocta_cFv */
void daDaiocta_c::isDamageBombEye() {
    /* Nonmatching */
}

/* 000017B4-00001A7C       .text setRotEye__11daDaiocta_cFv */
void daDaiocta_c::setRotEye() {
    /* Nonmatching */
}

/* 00001A7C-00001EA0       .text setCollision__11daDaiocta_cFv */
void daDaiocta_c::setCollision() {
    /* Nonmatching */
}

/* 00001EA0-00001EB8       .text modeHideInit__11daDaiocta_cFv */
void daDaiocta_c::modeHideInit() {
    /* Nonmatching */
}

/* 00001EB8-00001F34       .text modeHide__11daDaiocta_cFv */
void daDaiocta_c::modeHide() {
    /* Nonmatching */
}

/* 00001F34-000020C8       .text modeAppearInit__11daDaiocta_cFv */
void daDaiocta_c::modeAppearInit() {
    /* Nonmatching */
}

/* 000020C8-0000236C       .text modeAppear__11daDaiocta_cFv */
void daDaiocta_c::modeAppear() {
    /* Nonmatching */
}

/* 0000236C-000023B0       .text modeWaitInit__11daDaiocta_cFv */
void daDaiocta_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000023B0-00002458       .text modeWait__11daDaiocta_cFv */
void daDaiocta_c::modeWait() {
    /* Nonmatching */
}

/* 00002458-000024D8       .text modeDamageInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageInit() {
    /* Nonmatching */
}

/* 000024D8-000025C4       .text modeDamage__11daDaiocta_cFv */
void daDaiocta_c::modeDamage() {
    /* Nonmatching */
}

/* 000025C4-0000268C       .text modeDamageBombInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBombInit() {
    /* Nonmatching */
}

/* 0000268C-00002778       .text modeDamageBomb__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBomb() {
    /* Nonmatching */
}

/* 00002778-000028FC       .text modeDemoInit__11daDaiocta_cFv */
void daDaiocta_c::modeDemoInit() {
    /* Nonmatching */
}

/* 000028FC-00003150       .text modeDemo__11daDaiocta_cFv */
void daDaiocta_c::modeDemo() {
    /* Nonmatching */
}

/* 00003150-00003284       .text modeDeleteInit__11daDaiocta_cFv */
void daDaiocta_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00003284-000036A8       .text modeDelete__11daDaiocta_cFv */
void daDaiocta_c::modeDelete() {
    /* Nonmatching */
}

/* 000036A8-00003888       .text modeProc__11daDaiocta_cFQ211daDaiocta_c6Proc_eQ211daDaiocta_c6Mode_e */
void daDaiocta_c::modeProc(daDaiocta_c::Proc_e, daDaiocta_c::Mode_e) {
    /* Nonmatching */
}

/* 00003888-00003AF4       .text setAnm__11daDaiocta_cFv */
void daDaiocta_c::setAnm() {
    /* Nonmatching */
}

/* 00003AF4-00003B20       .text setWater__11daDaiocta_cFv */
void daDaiocta_c::setWater() {
    /* Nonmatching */
}

/* 00003B20-00003D20       .text _execute__11daDaiocta_cFv */
bool daDaiocta_c::_execute() {
    /* Nonmatching */
}

/* 00003D20-00003E58       .text drawAwa__11daDaiocta_cFv */
void daDaiocta_c::drawAwa() {
    /* Nonmatching */
}

/* 00003E58-00003F4C       .text drawSuikomi__11daDaiocta_cFv */
void daDaiocta_c::drawSuikomi() {
    /* Nonmatching */
}

/* 00003F4C-0000412C       .text drawDebug__11daDaiocta_cFv */
void daDaiocta_c::drawDebug() {
    /* Nonmatching */
}

/* 0000412C-00004244       .text _draw__11daDaiocta_cFv */
bool daDaiocta_c::_draw() {
    /* Nonmatching */
}

/* 00004244-00004364       .text getArg__11daDaiocta_cFv */
void daDaiocta_c::getArg() {
    /* Nonmatching */
}

/* 00004364-00004660       .text createInit__11daDaiocta_cFv */
void daDaiocta_c::createInit() {
    /* Nonmatching */
}

/* 00004660-00004918       .text _create__11daDaiocta_cFv */
cPhs_State daDaiocta_c::_create() {
    fopAcM_SetupActor(this, daDaiocta_c);
    cPhs_State state = dComIfG_resLoad(&field_0x0580, m_arc_name);

    if (state == cPhs_COMPLEATE_e) {
        getArg();

        if (mSwitchNo != 0xFF && dComIfGs_isSwitch(mSwitchNo, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }
    
    return state;
}

/* 00005098-0000513C       .text _delete__11daDaiocta_cFv */
bool daDaiocta_c::_delete() {
    /* Nonmatching */
}

/* 0000513C-0000515C       .text daDaioctaCreate__FPv */
static cPhs_State daDaioctaCreate(void* i_this) {
    return ((daDaiocta_c*)i_this)->_create();
}

/* 0000515C-00005180       .text daDaioctaDelete__FPv */
static BOOL daDaioctaDelete(void* i_this) {
    return ((daDaiocta_c*)i_this)->_delete();
}

/* 00005180-000051A4       .text daDaioctaExecute__FPv */
static BOOL daDaioctaExecute(void* i_this) {
    return ((daDaiocta_c*)i_this)->_execute();
}

/* 000051A4-000051C8       .text daDaioctaDraw__FPv */
static BOOL daDaioctaDraw(void* i_this) {
    return ((daDaiocta_c*)i_this)->_draw();
}

/* 000051C8-000051D0       .text daDaioctaIsDelete__FPv */
static BOOL daDaioctaIsDelete(void*) {
    return TRUE;
}

static actor_method_class daDaioctaMethodTable = {
    (process_method_func)daDaioctaCreate,
    (process_method_func)daDaioctaDelete,
    (process_method_func)daDaioctaExecute,
    (process_method_func)daDaioctaIsDelete,
    (process_method_func)daDaioctaDraw,
};

actor_process_profile_definition g_profile_DAIOCTA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DAIOCTA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDaiocta_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DAIOCTA,
    /* Actor SubMtd */ &daDaioctaMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
