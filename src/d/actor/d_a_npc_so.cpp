/**
 * d_a_npc_so.cpp
 * NPC - Fishman (blue fish)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_so.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_ship.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_lib.h"
#include "f_op/f_op_kankyo_mng.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "m_Do/m_Do_mtx.h"

char* daNpc_So_c::m_arc_name = "So";

static cXyz cyl_offset_B[] = {
    cXyz(15.0f, 0.0f, 0.0f),
    cXyz(-15.0f, 0.0f, 0.0f),
};

static __jnt_hit_data_c search_data[] = {
    {0, 4, 2.0f, &cyl_offset_B[0]},
    {0, 8, 2.0f, &cyl_offset_B[0]},
};

/* 000003EC-00000438 0002F8 004C+00 1/1 0/0 0/0 .text            nodeControl_CB__FP7J3DNodei */
static int nodeControl_CB(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        J3DModel* model = j3dSys.getModel();
        if (model != NULL) {
            daNpc_So_c* a_this = (daNpc_So_c*)model->getUserArea();
            if (a_this != NULL) {
                a_this->_nodeControl(i_node, model);
            }
        }
    }
    return 1;
}

/* 00000438-00000568       .text _nodeControl__10daNpc_So_cFP7J3DNodeP8J3DModel */
void daNpc_So_c::_nodeControl(J3DNode* i_node, J3DModel* i_model) {
    /* Nonmatching - needs HIO field mapping through JntHit_HIO_c */
}

/* 00000B14-00000B78 000A20 0064+00 1/1 0/0 0/0 .text            jntHitCreateHeap__10daNpc_So_cFv */
bool daNpc_So_c::jntHitCreateHeap() {
    mpJntHit2 = JntHit_create(mpMorf->getModel(), search_data, 2);
    if (mpJntHit2 != NULL) {
        jntHit = mpJntHit2;
        return true;
    }
    return false;
}

/* 00000800-00000B14       .text _createHeap__10daNpc_So_cFv */
int daNpc_So_c::_createHeap() {
    /* Nonmatching - needs mBtp and embedded type access */
}

/* 000000EC-000002A4       .text __ct__14daNpc_So_HIO_cFv */
daNpc_So_HIO_c::daNpc_So_HIO_c() {
    /* Nonmatching */
}

daNpc_So_HIO_c daNpc_So_c::m_heapsize;

/* 000002A4-000002D0       .text searchEsa_CB__FPvPv */
void searchEsa_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchEsa((fopAc_ac_c*)i_actor);
}

/* 000002D0-000002F8       .text _searchEsa__10daNpc_So_cFP10fopAc_ac_c */
void daNpc_So_c::_searchEsa(fopAc_ac_c* i_actor) {
    if (fopAcM_GetProfName(i_actor) == PROC_OBJ_SEARCH) {
        if (*(u8*)((u32)i_actor + 0x298) == 0) {
            // Return i_actor (found)
            return;
        }
    }
    // Return NULL (not found) - handled by fopAcIt_Judge
}


/* 000004B0-000004DC       .text searchTagSo_CB__FPvPv */
void searchTagSo_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchTagSo((fopAc_ac_c*)i_actor);
}

/* 000004DC-0000054C       .text _searchTagSo__10daNpc_So_cFP10fopAc_ac_c */
void daNpc_So_c::_searchTagSo(fopAc_ac_c* i_actor) {
    if (fopAcM_GetProfName(i_actor) == PROC_TAG_SO) {
        if (m0A79 != *(u8*)((u32)i_actor + 0x290))
            return;
        if (*(u8*)((u32)i_actor + 0x298) == 1)
            return;
        m0A7C = *(f32*)((u32)i_actor + 0x294);
        m0A80.x = i_actor->current.pos.x;
        m0A80.y = i_actor->current.pos.y;
        m0A80.z = i_actor->current.pos.z;
        current.pos.x = m0A80.x;
        current.pos.y = m0A80.y;
        current.pos.z = m0A80.z;
    }
}

/* 0000054C-00000578       .text searchMinigameTagSo_CB__FPvPv */
void searchMinigameTagSo_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchMinigameTagSo((fopAc_ac_c*)i_actor);
}

/* 00000578-000005C8       .text _searchMinigameTagSo__10daNpc_So_cFP10fopAc_ac_c */
void daNpc_So_c::_searchMinigameTagSo(fopAc_ac_c* i_actor) {
    if (fopAcM_GetProfName(i_actor) == PROC_TAG_SO) {
        if (*(u8*)((u32)i_actor + 0x298) != 1)
            return;
        mB90.x = i_actor->current.pos.x;
        mB90.y = i_actor->current.pos.y;
        mB90.z = i_actor->current.pos.z;
        mB9C = i_actor->shape_angle.y;
        *(u8*)((u32)this + 0xBAE) = 1;
    }
}

/* 000005C8-000005E8       .text daNpc_So_XyCheckCB__FPvi */
static s16 daNpc_So_XyCheckCB(void* i_this, int i_param) {
    return ((daNpc_So_c*)i_this)->XyCheckCB(i_param);
}

/* 000005E8-00000680       .text XyCheckCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyCheckCB(int i_param) {
    void* esa = fopAcIt_Judge((fopAcIt_JudgeFunc)searchEsa_CB, this);
    if (esa != NULL) {
        return 0;
    }
    if (m06D3 != 2) {
        return 0;
    }
    if (g_dComIfG_gameInfo.play.mMinigameFlags & 0x10000) {
        if (*(u8*)((u32)&g_dComIfG_gameInfo + 0x5BD3 + i_param) == 0x82) {
            return 1;
        }
    }
    return 0;
}

/* 00000680-000006A0       .text daNpc_So_XyEventCB__FPvi */
static s16 daNpc_So_XyEventCB(void* i_this, int i_param) {
    return ((daNpc_So_c*)i_this)->XyEventCB(i_param);
}

/* 000006A0-000006EC       .text XyEventCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyEventCB(int i_param) {
    mBDC = dComIfGp_getPEvtManager()->getEventIdx("SO_ESA_XY", 0xFF);
    return mBDC;
}

/* 000006EC-0000070C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daNpc_So_c*)i_this)->_createHeap();
}


/* 00000A84-00000C8C       .text checkTgHit__10daNpc_So_cFv */
void daNpc_So_c::checkTgHit() {
    /* Nonmatching */
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    mB40 = m_heapsize.m00FC;
    mB3C = m_heapsize.m00F8;
    mB38 = m_heapsize.m00C8;
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    mB40 = m_heapsize.m0130;
    mB3C = m_heapsize.m006C;
    mB38 = m_heapsize.m0134;
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    mB40 = m_heapsize.m0130;
    mB3C = m_heapsize.m006C;
    mB38 = m_heapsize.m0138;
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    mB40 = m_heapsize.m013C;
    mB3C = m_heapsize.m0140;
    mB38 = m_heapsize.m0144;
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
void daNpc_So_c::getMsg() {
    /* Nonmatching */
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
void daNpc_So_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
    /* Nonmatching */
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    /* Nonmatching */
}

/* 00001430-00001524       .text setAnm__10daNpc_So_cFScb */
void daNpc_So_c::setAnm(signed char, bool) {
    /* Nonmatching */
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    /* Nonmatching */
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    /* Nonmatching */
}

/* 000016E8-00001718       .text modeWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeWaitInit() {
    /* Nonmatching */
}

/* 00001718-0000171C       .text modeWait__10daNpc_So_cFv */
void daNpc_So_c::modeWait() {
    /* Nonmatching */
}

/* 0000171C-0000175C       .text modeHideInit__10daNpc_So_cFv */
void daNpc_So_c::modeHideInit() {
    /* Nonmatching */
}

/* 0000175C-00001778       .text modeHide__10daNpc_So_cFv */
void daNpc_So_c::modeHide() {
    /* Nonmatching */
}

/* 00001778-00001880       .text modeJumpInit__10daNpc_So_cFv */
void daNpc_So_c::modeJumpInit() {
    /* Nonmatching */
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    /* Nonmatching */
}

/* 000019F0-00001A6C       .text modeSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeSwimInit() {
    /* Nonmatching */
}

/* 00001A6C-00001DB8       .text modeSwim__10daNpc_So_cFv */
void daNpc_So_c::modeSwim() {
    /* Nonmatching */
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    /* Nonmatching */
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    /* Nonmatching */
}

/* 00002144-0000217C       .text modeEventFirstWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWaitInit() {
    /* Nonmatching */
}

/* 0000217C-000022D0       .text modeEventFirstWait__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWait() {
    /* Nonmatching */
}

/* 000022D0-00002314       .text modeEventFirstInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstInit() {
    /* Nonmatching */
}

/* 00002314-000023C8       .text modeEventFirst__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirst() {
    /* Nonmatching */
}

/* 000023C8-0000240C       .text modeEventFirstEndInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEndInit() {
    /* Nonmatching */
}

/* 0000240C-000024C0       .text modeEventFirstEnd__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEnd() {
    /* Nonmatching */
}

/* 000024C0-00002504       .text modeEventEsaInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsaInit() {
    /* Nonmatching */
}

/* 00002504-00002594       .text modeEventEsa__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsa() {
    /* Nonmatching */
}

/* 00002594-000025B0       .text modeEventMapopenInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopenInit() {
    /* Nonmatching */
}

/* 000025B0-00002670       .text modeEventMapopen__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopen() {
    /* Nonmatching */
}

/* 00002670-000026B4       .text modeEventBowInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventBowInit() {
    /* Nonmatching */
}

/* 000026B4-000027F8       .text modeEventBow__10daNpc_So_cFv */
void daNpc_So_c::modeEventBow() {
    /* Nonmatching */
}

/* 000027F8-0000283C       .text modeTalkInit__10daNpc_So_cFv */
void daNpc_So_c::modeTalkInit() {
    /* Nonmatching */
}

/* 0000283C-0000289C       .text modeTalk__10daNpc_So_cFv */
void daNpc_So_c::modeTalk() {
    /* Nonmatching */
}

/* 0000289C-0000296C       .text modeDisappearInit__10daNpc_So_cFv */
void daNpc_So_c::modeDisappearInit() {
    /* Nonmatching */
}

/* 0000296C-00002A90       .text modeDisappear__10daNpc_So_cFv */
void daNpc_So_c::modeDisappear() {
    /* Nonmatching */
}

/* 00002A90-00002B60       .text modeDebugInit__10daNpc_So_cFv */
void daNpc_So_c::modeDebugInit() {
    /* Nonmatching */
}

/* 00002B60-00002B64       .text modeDebug__10daNpc_So_cFv */
void daNpc_So_c::modeDebug() {
    /* Nonmatching */
}

/* 00002B64-00002B68       .text modeGetRupeeInit__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupeeInit() {
    /* Nonmatching */
}

/* 00002B68-00002C6C       .text modeGetRupee__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupee() {
    /* Nonmatching */
}

/* 00002C6C-00002CC0       .text modeEventTriForceInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForceInit() {
    /* Nonmatching */
}

/* 00002CC0-00002D80       .text modeEventTriForce__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForce() {
    /* Nonmatching */
}

/* 00002D80-00003110       .text modeProc__10daNpc_So_cFQ210daNpc_So_c6Proc_ei */
void daNpc_So_c::modeProc(daNpc_So_c::Proc_e, int) {
    /* Nonmatching */
}

/* 00003110-00003264       .text eventOrder__10daNpc_So_cFv */
void daNpc_So_c::eventOrder() {
    /* Nonmatching */
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    /* Nonmatching */
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    /* Nonmatching */
}

/* 000033F4-00003844       .text _execute__10daNpc_So_cFv */
bool daNpc_So_c::_execute() {
    /* Nonmatching */
}

/* 00003844-000038E0       .text debugDraw__10daNpc_So_cFv */
void daNpc_So_c::debugDraw() {
    /* Nonmatching */
}

/* 000038E0-00003954       .text hudeDraw__10daNpc_So_cFv */
void daNpc_So_c::hudeDraw() {
    /* Nonmatching */
}

/* 00003954-00003B00       .text _draw__10daNpc_So_cFv */
bool daNpc_So_c::_draw() {
    /* Nonmatching */
}

/* 00003B00-00003DF8       .text createInit__10daNpc_So_cFv */
void daNpc_So_c::createInit() {
    /* Nonmatching */
}

/* 00003DF8-00003E24       .text getArg__10daNpc_So_cFv */
void daNpc_So_c::getArg() {
    /* Nonmatching */
}

/* 00003E24-00003F38       .text _create__10daNpc_So_cFv */
cPhs_State daNpc_So_c::_create() {
    /* Nonmatching */
}

/* 000046E4-00004754       .text _delete__10daNpc_So_cFv */
bool daNpc_So_c::_delete() {
    /* Nonmatching */
}

/* 00004754-00004774       .text daNpc_SoCreate__FPv */
static cPhs_State daNpc_SoCreate(void* i_this) {
    return ((daNpc_So_c*)i_this)->_create();
}

/* 00004774-00004798       .text daNpc_SoDelete__FPv */
static BOOL daNpc_SoDelete(void* i_this) {
    return ((daNpc_So_c*)i_this)->_delete();
}

/* 00004798-000047BC       .text daNpc_SoExecute__FPv */
static BOOL daNpc_SoExecute(void* i_this) {
    return ((daNpc_So_c*)i_this)->_execute();
}

/* 000047BC-000047E0       .text daNpc_SoDraw__FPv */
static BOOL daNpc_SoDraw(void* i_this) {
    return ((daNpc_So_c*)i_this)->_draw();
}

/* 000047E0-000047E8       .text daNpc_SoIsDelete__FPv */
static BOOL daNpc_SoIsDelete(void*) {
    return TRUE;
}

#include "d/actor/d_a_npc_so_cut.inc"
#include "d/d_cc_d.h"

const dCcD_SrcSph daNpc_So_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_UNK8 & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


static actor_method_class daNpc_SoMethodTable = {
    (process_method_func)daNpc_SoCreate,
    (process_method_func)daNpc_SoDelete,
    (process_method_func)daNpc_SoExecute,
    (process_method_func)daNpc_SoIsDelete,
    (process_method_func)daNpc_SoDraw,
};

actor_process_profile_definition g_profile_NPC_SO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_SO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_So_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_SO,
    /* Actor SubMtd */ &daNpc_SoMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
