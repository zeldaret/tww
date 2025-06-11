/**
 * d_a_npc_bmsw.cpp
 * NPC - Koboli (Rito mail sorter)
 */

#include "d/actor/d_a_npc_bmsw.h"
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


/* 000000EC-000001E4       .text __ct__16daNpc_Bmsw_HIO_cFv */
daNpc_Bmsw_HIO_c::daNpc_Bmsw_HIO_c() {
    /* Nonmatching */
}

/* 000001E4-000003FC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000438-00000550       .text nodeCallBackArm__FP7J3DNodei */
static BOOL nodeCallBackArm(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000550-000006F4       .text daNpc_Bmsw_getGameEndMsg__Fs */
void daNpc_Bmsw_getGameEndMsg(short) {
    /* Nonmatching */
}

/* 000006F4-00000808       .text initTexPatternAnm__12daNpc_Bmsw_cFb */
void daNpc_Bmsw_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000808-00000894       .text playTexPatternAnm__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000894-00000984       .text setAnm__12daNpc_Bmsw_cFSc */
void daNpc_Bmsw_c::setAnm(signed char) {
    /* Nonmatching */
}

/* 00000984-00000AD8       .text chkAttention__12daNpc_Bmsw_cF4cXyzs */
void daNpc_Bmsw_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000AD8-00000B28       .text eventOrder__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::eventOrder() {
    /* Nonmatching */
}

/* 00000B28-00000B68       .text checkOrder__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::checkOrder() {
    /* Nonmatching */
}

/* 00000B68-00000EF8       .text next_msgStatus__12daNpc_Bmsw_cFPUl */
void daNpc_Bmsw_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00000EF8-0000102C       .text getMsg__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::getMsg() {
    /* Nonmatching */
}

/* 0000102C-000010C0       .text anmAtr__12daNpc_Bmsw_cFUs */
void daNpc_Bmsw_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 000010C0-00001340       .text CreateInit__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::CreateInit() {
    /* Nonmatching */
}

/* 00001340-00001508       .text set_mtx__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::set_mtx() {
    /* Nonmatching */
}

/* 00001508-00001534       .text setAttention__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::setAttention() {
    /* Nonmatching */
}

/* 00001534-000016EC       .text lookBack__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::lookBack() {
    /* Nonmatching */
}

/* 000016EC-0000184C       .text wait01__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::wait01() {
    /* Nonmatching */
}

/* 0000184C-00001A84       .text talk01__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::talk01() {
    /* Nonmatching */
}

/* 00001A84-00001BA4       .text wait_action__12daNpc_Bmsw_cFPv */
void daNpc_Bmsw_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00001BA4-00001C70       .text checkNextMailThrowOK__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::checkNextMailThrowOK() {
    /* Nonmatching */
}

/* 00001C70-00001DA4       .text setGameGetRupee__12daNpc_Bmsw_cFs */
void daNpc_Bmsw_c::setGameGetRupee(short) {
    /* Nonmatching */
}

/* 00001DA4-00001E88       .text TimerCountDown__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::TimerCountDown() {
    /* Nonmatching */
}

/* 00001E88-00002950       .text shiwake_game_action__12daNpc_Bmsw_cFPv */
void daNpc_Bmsw_c::shiwake_game_action(void*) {
    /* Nonmatching */
}

/* 00002950-00002B24       .text _draw__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_draw() {
    /* Nonmatching */
}

/* 00002B24-00002CA4       .text _execute__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_execute() {
    /* Nonmatching */
}

/* 00002CA4-00002D40       .text _delete__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_delete() {
    /* Nonmatching */
}

/* 00002D40-00002D60       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002D60-00002ECC       .text _create__12daNpc_Bmsw_cFv */
cPhs_State daNpc_Bmsw_c::_create() {
    /* Nonmatching */
}

/* 00003524-00003CB0       .text CreateHeap__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::CreateHeap() {
    /* Nonmatching */
}

/* 00003CB0-00003DBC       .text MailCreateInit__8SwMail_cFP4cXyzP4cXyz */
void SwMail_c::MailCreateInit(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00003DBC-00003FE8       .text getNextNo__8SwMail_cFUc */
void SwMail_c::getNextNo(unsigned char) {
    /* Nonmatching */
}

/* 00003FE8-00004074       .text init__8SwMail_cFv */
void SwMail_c::init() {
    /* Nonmatching */
}

/* 00004074-000040F8       .text set_mtx__8SwMail_cFv */
void SwMail_c::set_mtx() {
    /* Nonmatching */
}

/* 000040F8-00004184       .text set_mtx_throw__8SwMail_cFv */
void SwMail_c::set_mtx_throw() {
    /* Nonmatching */
}

/* 00004184-0000425C       .text DummyInit__8SwMail_cFv */
void SwMail_c::DummyInit() {
    /* Nonmatching */
}

/* 0000425C-0000427C       .text Dummy__8SwMail_cFv */
void SwMail_c::Dummy() {
    /* Nonmatching */
}

/* 0000427C-0000438C       .text AppearInit__8SwMail_cFv */
void SwMail_c::AppearInit() {
    /* Nonmatching */
}

/* 0000438C-000044E8       .text Appear__8SwMail_cFv */
void SwMail_c::Appear() {
    /* Nonmatching */
}

/* 000044E8-0000450C       .text WaitInit__8SwMail_cFv */
void SwMail_c::WaitInit() {
    /* Nonmatching */
}

/* 0000450C-00004628       .text Wait__8SwMail_cFv */
void SwMail_c::Wait() {
    /* Nonmatching */
}

/* 00004628-00004670       .text ThrowInit__8SwMail_cF4cXyzUc */
void SwMail_c::ThrowInit(cXyz, unsigned char) {
    /* Nonmatching */
}

/* 00004670-00004954       .text Throw__8SwMail_cFv */
void SwMail_c::Throw() {
    /* Nonmatching */
}

/* 00004954-000049A0       .text EndInit__8SwMail_cFv */
void SwMail_c::EndInit() {
    /* Nonmatching */
}

/* 000049A0-00004B34       .text End__8SwMail_cFv */
void SwMail_c::End() {
    /* Nonmatching */
}

/* 00004B34-00004B68       .text SeDelete__8SwMail_cFv */
void SwMail_c::SeDelete() {
    /* Nonmatching */
}

/* 00004B68-00004B90       .text move__8SwMail_cFv */
void SwMail_c::move() {
    /* Nonmatching */
}

/* 00004B90-00004C04       .text draw__8SwMail_cFP12dKy_tevstr_c */
void SwMail_c::draw(dKy_tevstr_c*) {
    /* Nonmatching */
}

/* 00004C04-00004D0C       .text Move__7SwCam_cFv */
void SwCam_c::Move() {
    /* Nonmatching */
}

/* 00004D0C-00004D2C       .text daNpc_Bmsw_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bmsw_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_create();
}

/* 00004D2C-00004D4C       .text daNpc_Bmsw_Delete__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Delete(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_delete();
}

/* 00004D4C-00004D6C       .text daNpc_Bmsw_Execute__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Execute(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_execute();
}

/* 00004D6C-00004D8C       .text daNpc_Bmsw_Draw__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Draw(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_draw();
}

/* 00004D8C-00004D94       .text daNpc_Bmsw_IsDelete__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_IsDelete(daNpc_Bmsw_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Bmsw_Method = {
    (process_method_func)daNpc_Bmsw_Create,
    (process_method_func)daNpc_Bmsw_Delete,
    (process_method_func)daNpc_Bmsw_Execute,
    (process_method_func)daNpc_Bmsw_IsDelete,
    (process_method_func)daNpc_Bmsw_Draw,
};

actor_process_profile_definition g_profile_NPC_BMSW = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BMSW,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bmsw_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_BMSW,
    /* Actor SubMtd */ &l_daNpc_Bmsw_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
