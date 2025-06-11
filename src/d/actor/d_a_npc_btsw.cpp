/**
 * d_a_npc_btsw.cpp
 * NPC - Baito
 */

#include "d/actor/d_a_npc_btsw.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};


/* 000000EC-000001E8       .text __ct__16daNpc_Btsw_HIO_cFv */
daNpc_Btsw_HIO_c::daNpc_Btsw_HIO_c() {
    /* Nonmatching */
}

/* 000001E8-000003F4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000430-0000046C       .text daNpc_Btsw_getGameEndMsg__Fs */
void daNpc_Btsw_getGameEndMsg(short) {
    /* Nonmatching */
}

/* 0000046C-00000584       .text initTexPatternAnm__12daNpc_Btsw_cFb */
void daNpc_Btsw_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000584-00000610       .text playTexPatternAnm__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000610-00000708       .text setAnm__12daNpc_Btsw_cFSc */
void daNpc_Btsw_c::setAnm(signed char) {
    /* Nonmatching */
}

/* 00000708-0000085C       .text chkAttention__12daNpc_Btsw_cF4cXyzs */
void daNpc_Btsw_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 0000085C-00000908       .text eventOrder__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::eventOrder() {
    /* Nonmatching */
}

/* 00000908-00000AC4       .text checkOrder__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::checkOrder() {
    /* Nonmatching */
}

/* 00000AC4-00000CBC       .text next_msgStatus__12daNpc_Btsw_cFPUl */
void daNpc_Btsw_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00000CBC-00000DF0       .text getMsg__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::getMsg() {
    /* Nonmatching */
}

/* 00000DF0-00000F0C       .text anmAtr__12daNpc_Btsw_cFUs */
void daNpc_Btsw_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 00000F0C-00000F30       .text daNpc_Btsw_XyCheckCB__FPvi */
static s16 daNpc_Btsw_XyCheckCB(void*, int) {
    /* Nonmatching */
}

/* 00000F30-00001110       .text CreateInit__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::CreateInit() {
    /* Nonmatching */
}

/* 00001110-00001324       .text set_mtx__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::set_mtx() {
    /* Nonmatching */
}

/* 00001324-00001350       .text setAttention__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::setAttention() {
    /* Nonmatching */
}

/* 00001350-00001490       .text lookBack__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::lookBack() {
    /* Nonmatching */
}

/* 00001490-00001594       .text wait01__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::wait01() {
    /* Nonmatching */
}

/* 00001594-00001798       .text talk01__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::talk01() {
    /* Nonmatching */
}

/* 00001798-00001888       .text wait_action__12daNpc_Btsw_cFPv */
void daNpc_Btsw_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00001888-00001A40       .text dummy_event_action__12daNpc_Btsw_cFPv */
void daNpc_Btsw_c::dummy_event_action(void*) {
    /* Nonmatching */
}

/* 00001A40-00001B0C       .text checkNextMailThrowOK__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::checkNextMailThrowOK() {
    /* Nonmatching */
}

/* 00001B0C-00001BF0       .text TimerCountDown__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::TimerCountDown() {
    /* Nonmatching */
}

/* 00001BF0-000026EC       .text shiwake_game_action__12daNpc_Btsw_cFPv */
void daNpc_Btsw_c::shiwake_game_action(void*) {
    /* Nonmatching */
}

/* 000026EC-00002844       .text getdemo_action__12daNpc_Btsw_cFPv */
void daNpc_Btsw_c::getdemo_action(void*) {
    /* Nonmatching */
}

/* 00002844-000029A0       .text _draw__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_draw() {
    /* Nonmatching */
}

/* 000029A0-00002AF4       .text _execute__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_execute() {
    /* Nonmatching */
}

/* 00002AF4-00002B90       .text _delete__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_delete() {
    /* Nonmatching */
}

/* 00002B90-00002BB0       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002BB0-00002CAC       .text _create__12daNpc_Btsw_cFv */
cPhs_State daNpc_Btsw_c::_create() {
    /* Nonmatching */
}

/* 00003304-0000372C       .text CreateHeap__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000372C-00003838       .text MailCreateInit__9SwMail2_cFP4cXyzP4cXyz */
void SwMail2_c::MailCreateInit(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00003838-00003A64       .text getNextNo__9SwMail2_cFUc */
void SwMail2_c::getNextNo(unsigned char) {
    /* Nonmatching */
}

/* 00003A64-00003AF0       .text init__9SwMail2_cFv */
void SwMail2_c::init() {
    /* Nonmatching */
}

/* 00003AF0-00003B74       .text set_mtx__9SwMail2_cFv */
void SwMail2_c::set_mtx() {
    /* Nonmatching */
}

/* 00003B74-00003C00       .text set_mtx_throw__9SwMail2_cFv */
void SwMail2_c::set_mtx_throw() {
    /* Nonmatching */
}

/* 00003C00-00003CD8       .text DummyInit__9SwMail2_cFv */
void SwMail2_c::DummyInit() {
    /* Nonmatching */
}

/* 00003CD8-00003CF8       .text Dummy__9SwMail2_cFv */
void SwMail2_c::Dummy() {
    /* Nonmatching */
}

/* 00003CF8-00003E08       .text AppearInit__9SwMail2_cFv */
void SwMail2_c::AppearInit() {
    /* Nonmatching */
}

/* 00003E08-00003F64       .text Appear__9SwMail2_cFv */
void SwMail2_c::Appear() {
    /* Nonmatching */
}

/* 00003F64-00003F88       .text WaitInit__9SwMail2_cFv */
void SwMail2_c::WaitInit() {
    /* Nonmatching */
}

/* 00003F88-000040A4       .text Wait__9SwMail2_cFv */
void SwMail2_c::Wait() {
    /* Nonmatching */
}

/* 000040A4-000040EC       .text ThrowInit__9SwMail2_cF4cXyzUc */
void SwMail2_c::ThrowInit(cXyz, unsigned char) {
    /* Nonmatching */
}

/* 000040EC-000043D0       .text Throw__9SwMail2_cFv */
void SwMail2_c::Throw() {
    /* Nonmatching */
}

/* 000043D0-0000441C       .text EndInit__9SwMail2_cFv */
void SwMail2_c::EndInit() {
    /* Nonmatching */
}

/* 0000441C-000045B0       .text End__9SwMail2_cFv */
void SwMail2_c::End() {
    /* Nonmatching */
}

/* 000045B0-000045E4       .text SeDelete__9SwMail2_cFv */
void SwMail2_c::SeDelete() {
    /* Nonmatching */
}

/* 000045E4-0000460C       .text move__9SwMail2_cFv */
void SwMail2_c::move() {
    /* Nonmatching */
}

/* 0000460C-00004680       .text draw__9SwMail2_cFP12dKy_tevstr_c */
void SwMail2_c::draw(dKy_tevstr_c*) {
    /* Nonmatching */
}

/* 00004680-00004788       .text Move__8SwCam2_cFv */
void SwCam2_c::Move() {
    /* Nonmatching */
}

/* 00004788-000047A8       .text daNpc_Btsw_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Btsw_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_create();
}

/* 000047A8-000047C8       .text daNpc_Btsw_Delete__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Delete(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_delete();
}

/* 000047C8-000047E8       .text daNpc_Btsw_Execute__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Execute(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_execute();
}

/* 000047E8-00004808       .text daNpc_Btsw_Draw__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Draw(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_draw();
}

/* 00004808-00004810       .text daNpc_Btsw_IsDelete__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_IsDelete(daNpc_Btsw_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Btsw_Method = {
    (process_method_func)daNpc_Btsw_Create,
    (process_method_func)daNpc_Btsw_Delete,
    (process_method_func)daNpc_Btsw_Execute,
    (process_method_func)daNpc_Btsw_IsDelete,
    (process_method_func)daNpc_Btsw_Draw,
};

actor_process_profile_definition g_profile_NPC_BTSW = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BTSW,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Btsw_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_BTSW,
    /* Actor SubMtd */ &l_daNpc_Btsw_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
