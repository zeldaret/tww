/**
 * d_a_npc_pm1.cpp
 * NPC - Maggie (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_pm1.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Km.h"


    // struct anm_prm_c {
    //     /* 0x0 */ s8 mAnmIdx;
    //     /* 0x1 */ u8 field_0x1[2];
    //     /* 0x3 */ s8 mTexAnmIdx;
    //     /* 0x4 */ f32 mMorf;
    //     /* 0x8 */ f32 mPlaySpeed;
    //     /* 0xC */ int mLoopMode;
    // };  // Size: 0x10
const daNpc_Pm1_c::anm_prm_c mAnmParam = {
    0,
    0,
    0,
    0,
    0,
    0,
};

static daNpc_Pm1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_Pm1_HIO_cFv */
daNpc_Pm1_HIO_c::daNpc_Pm1_HIO_c() {
    /* Nonmatching */
}

/* 00000144-00000300       .text nodeCallBack_Pm__FP7J3DNodei */
static BOOL nodeCallBack_Pm(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000033C-0000044C       .text createInit__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::createInit() {
    /* Nonmatching */
  ActionFunc local_18;
  f32 local_14;
  int local_10;
  
  this->mEventCut.setActorInfo2( "Pm1", this);
 // this->attention_info.flags = Action_Talk|LockOn_Talk;
  this->attention_info.flags = 0x280|0x26d; //CREATE ENUM
  this->attention_info.distances[1] = 0xab;
  this->attention_info.distances[3] = 0xa9;
  this->gravity = -4.0;
  (this->field_0x798).x = this->current.pos.x;
  (this->field_0x798).y = this->current.pos.y;
  (this->field_0x798).z = this->current.pos.z;
  local_18 = 0x0;
  local_14 = 0xffffff;
  this->set_action(local_18, (void *)0x0);
  this->shape_angle.x = this->current.angle.x;
  this->shape_angle.y = this->current.angle.y;
  this->shape_angle.z = this->current.angle.z;
  this->mStts.Init(0xff, 0xff, (fopAc_ac_c *)this);
  this->mCyl.SetStts(&this->mStts);
  this->mCyl.Set(dNpc_cyl_src);
  this->mpMorf->setMorf( 0.0);
  this->field_0x7BC = 1;
  this->setMtx();
  return 1;
}

/* 0000044C-0000055C       .text setMtx__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setMtx() {
    /* Nonmatching */
    BOOL sVar1;
    char cVar2;
    int bVar3;

    if (this->field_0x7C7 == 0) {
    this->playTexPatternAnm();
    sVar1 = this->mpMorf->play(&this->eyePos, 0, 0);
    this->field_0x7B4 = sVar1;
    if (this->mpMorf->getFrame() < this->field_0x7A4) {
        this->field_0x7B4 = 1;
    }
    this->field_0x7A4 = this->mpMorf->getFrame();
    this->mObjAcch.CrrPos(g_dComIfG_gameInfo.play.mBgS);
    }
    cVar2 = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    this->tevStr.mRoomNo = cVar2;
    bVar3 = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    this->tevStr.mEnvrIdxOverride = bVar3;

    mDoMtx_stack_c::transS(this->current.pos.x, this->current.pos.y, this->current.pos.z);     
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    this->mpModel->setBaseTRMtx(mDoMtx_stack_c::now);
    this->mpModel->calc();
    this->setAttention();
}

/* 0000055C-00000664       .text anmResID__11daNpc_Pm1_cFiPiPi */
BOOL daNpc_Pm1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    /* Nonmatching */
    bool bVar1;
    u32 uVar2;
    static const int a_anm_idx_tbl[16] = { 0,0,0,5,0,0,0,2,0,0,0,4,0,0,0,1};
  bVar1 = false;
  if ((i_num > 0) && (i_num < 2)) {
    bVar1 = true;
  }
  if (!bVar1) {
    uVar2 = JUTAssertion::getSDevice();
    JUTAssertion::showAssert(uVar2, "d_a_npc_pm1.cpp", 0x11b, "0 <= i_num && i_num < ANM_END");
    OSPanic("d_a_npc_pm1.cpp", 0x11b, "Halt");
  }
  bVar1 = false;
  if ((o_bck_num != (int *)0x0) && (o_bas_num != (int *)0x0)) {
    bVar1 = true;
  }
  if (!bVar1) {
    uVar2 = JUTAssertion::getSDevice();
    JUTAssertion::showAssert(uVar2, "d_a_npc_pm1.cpp", 0x11c, "o_bck_num && o_bas_num");
    OSPanic("d_a_npc_pm1.cpp", 0x11c, "Halt");
  }
    *o_bck_num = a_anm_idx_tbl[i_num];
    *o_bas_num = a_anm_idx_tbl[i_num+4];
    return true;
}

/* 00000664-00000700       .text BtpNum2ResID__11daNpc_Pm1_cFiPi */
void daNpc_Pm1_c::BtpNum2ResID(int i_num, int* param_2) {
    /* Nonmatching */
    bool bVar1;
    u32 uVar2;
    static const int a_btp_arc_ix_tbl[4] = { 0,0,0,7};

    bVar1 = false;
    if ((i_num > 0) && (i_num < 1)) {
        bVar1 = true;
    }
    if (!bVar1) {
        uVar2 = JUTAssertion::getSDevice();
        JUTAssertion::showAssert
                    (uVar2, "d_a_npc_pm1.cpp", 0x131, "0 <= i_num && i_num < TEXPATTERN_END");
        OSPanic("d_a_npc_pm1.cpp", 0x131, "Halt");
    }
    *param_2 = a_btp_arc_ix_tbl[i_num];
}

/* 00000700-00000744       .text setAnm_tex__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setAnm_tex(signed char param_1) {
    /* Nonmatching */
    if ((param_1 >= 0) && (param_1 != this->field_0x7CD)) {
        this->field_0x7CD = param_1;
        this->initTexPatternAnm(true);
    }
}

/* 00000744-00000860       .text init_btp__11daNpc_Pm1_cFbi */
BOOL daNpc_Pm1_c::init_btp(bool i_modify, int i_num) {
    /* Nonmatching */
    J3DAnmTexPattern *anm_tex_pattern;
    u32 assertion_device;
    int is_btp_anm;
    J3DModelData *mdl_data;
    int btpId;

    mdl_data = this->mpMorf->getModel()->getModelData();
    if (i_num >= 0) {
    this->BtpNum2ResID(i_num, &btpId);
    anm_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Pm", btpId);
    this->m_head_tex_pattern = anm_tex_pattern;
    if (this->m_head_tex_pattern == (J3DAnmTexPattern *)0x0) {
        assertion_device = JUTAssertion::getSDevice();
        JUTAssertion::showAssert(assertion_device, "d_a_npc_pm1.cpp", 0x152, "m_head_tex_pattern != 0");
        OSPanic("d_a_npc_pm1.cpp", 0x152, "Halt");
    }
    is_btp_anm = this->mBtpAnm.init(mdl_data, this->m_head_tex_pattern, 1, 2, 1.0, 0, -1, i_modify,0);
    if (is_btp_anm == 0) {
        return 0;
    }
    this->mBtpFrame = 0;
    this->field_0x6F2 = 0;
    }
    return 1;
}

/* 00000860-000008A4       .text initTexPatternAnm__11daNpc_Pm1_cFb */
BOOL daNpc_Pm1_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 000008A4-00000968       .text playTexPatternAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000968-00000A34       .text setAnm_anm__11daNpc_Pm1_cFPQ211daNpc_Pm1_c9anm_prm_c */
BOOL daNpc_Pm1_c::setAnm_anm(daNpc_Pm1_c::anm_prm_c*) {
    /* Nonmatching */
}

/* 00000A34-00000A9C       .text setAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAnm() {
    /* Nonmatching */
}

/* 00000A9C-00000AA8       .text chngAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::chngAnmTag() {
    /* Nonmatching */
}

/* 00000AA8-00000AB4       .text ctrlAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmTag() {
    /* Nonmatching */
}

/* 00000AB4-00000AF4       .text chngAnmAtr__11daNpc_Pm1_cFUc */
void daNpc_Pm1_c::chngAnmAtr(unsigned char) {
    /* Nonmatching */
}

/* 00000AF4-00000AF8       .text ctrlAnmAtr__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmAtr() {
    /* Nonmatching */
}

/* 00000AF8-00000B60       .text setAnm_ATR__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::setAnm_ATR(int) {
    /* Nonmatching */
}

/* 00000B60-00000C1C       .text anmAtr__11daNpc_Pm1_cFUs */
void daNpc_Pm1_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 00000C1C-00000C74       .text setStt__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00000C74-00000C7C       .text next_msgStatus__11daNpc_Pm1_cFPUl */
u16 daNpc_Pm1_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00000C7C-00000C84       .text getMsg__11daNpc_Pm1_cFv */
u32 daNpc_Pm1_c::getMsg() {
    /* Nonmatching */
}

/* 00000C84-00000CD4       .text eventOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::eventOrder() {
    /* Nonmatching */
}

/* 00000CD4-00000D14       .text checkOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::checkOrder() {
    /* Nonmatching */
}

/* 00000D14-00000EA4       .text lookBack__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::lookBack() {
    /* Nonmatching */
}

/* 00000EA4-00000F24       .text chkAttention__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::chkAttention() {
    /* Nonmatching */
}

/* 00000F24-00000F88       .text setAttention__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAttention() {
    /* Nonmatching */
}

/* 00000F88-00000FB4       .text decideType__11daNpc_Pm1_cFi */
bool daNpc_Pm1_c::decideType(int) {
    /* Nonmatching */
}

/* 00000FB4-0000103C       .text event_actionInit__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 0000103C-0000104C       .text event_action__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::event_action() {
    /* Nonmatching */
}

/* 0000104C-00001154       .text privateCut__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::privateCut() {
    /* Nonmatching */
}

/* 00001154-00001174       .text endEvent__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::endEvent() {
    /* Nonmatching */
}

/* 00001174-000011D4       .text event_proc__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::event_proc() {
    /* Nonmatching */
}

/* 000011D4-00001280       .text set_action__11daNpc_Pm1_cFM11daNpc_Pm1_cFPCvPvPv_iPv */
BOOL daNpc_Pm1_c::set_action(ActionFunc, void*) {
    /* Nonmatching */
}

/* 00001280-00001378       .text wait01__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::wait01() {
    /* Nonmatching */
}

/* 00001378-00001408       .text talk01__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::talk01() {
    /* Nonmatching */
}

/* 00001408-000014BC       .text wait_action1__11daNpc_Pm1_cFPv */
int daNpc_Pm1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 000014BC-00001558       .text demo__11daNpc_Pm1_cFv */
u8 daNpc_Pm1_c::demo() {
    /* Nonmatching */
    if(demoActorID == 0){
        if(field_0x7C7 != 0){
            field_0x7C7 = 0;
        }
    }else{
        field_0x7C7 = 1;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(
            this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf,
            "Pm"
        );
    }
    return field_0x7C7;
}

/* 00001558-000016BC       .text _draw__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_draw() {
    /* Nonmatching */
}

/* 000016BC-00001818       .text _execute__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_execute() {
    /* Nonmatching */
}

/* 00001818-0000189C       .text _delete__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_delete() {
    /* Nonmatching */
    fopAcM_RegisterDeleteID(this);

    dComIfG_resDeleteDemo(&mPhase,"Pm");

    if(mpMorf != NULL){
        mpMorf->stopZelAnime();
    }
    if(l_HIO.field_0x8 >= 0){
        l_HIO.field_0x8 += -1;
        if(l_HIO.field_0x8 < 0){
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return true;
}

/* 0000189C-000018BC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000018BC-00001A2C       .text _create__11daNpc_Pm1_cFv */
cPhs_State daNpc_Pm1_c::_create() {
    /* Nonmatching */
}

/* 00001E5C-00002168       .text CreateHeap__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00002168-00002188       .text daNpc_Pm1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Pm1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_create();
}

/* 00002188-000021A8       .text daNpc_Pm1_Delete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Delete(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_delete();
}

/* 000021A8-000021C8       .text daNpc_Pm1_Execute__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Execute(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_execute();
}

/* 000021C8-000021E8       .text daNpc_Pm1_Draw__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Draw(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_draw();
}

/* 000021E8-000021F0       .text daNpc_Pm1_IsDelete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_IsDelete(daNpc_Pm1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Pm1_Method = {
    (process_method_func)daNpc_Pm1_Create,
    (process_method_func)daNpc_Pm1_Delete,
    (process_method_func)daNpc_Pm1_Execute,
    (process_method_func)daNpc_Pm1_IsDelete,
    (process_method_func)daNpc_Pm1_Draw,
};

actor_process_profile_definition g_profile_NPC_PM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_PM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Pm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_PM1_e,
    /* Actor SubMtd */ &l_daNpc_Pm1_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
