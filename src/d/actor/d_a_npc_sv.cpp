/**
 * d_a_npc_sv.cpp
 * NPC - Salvage Corp group members
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_sv.h"
#include "d/d_com_lib_game.h"

static char* l_npc_staff_id[] = { "Sv0", "Sv1", "Sv2", "Sv3" };

static const char* l_arcname_tbl[] = { "Sv", "Sv", "Sv", "Sv" };

static sSvAnmDat l_npc_anm_wait = { 0, 0x08, 0xFF };

static sSvAnmDat l_npc_anm_talk = {
    1,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_talk2 = {
    2,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_talk3 = {
    3,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_ya1[] = { {
                                         4,
                                         0x08,
                                         1,
                                     },
                                     {
                                         0,
                                         0x08,
                                         0xFF,
                                     } };

static sSvAnmDat l_npc_anm_ya2[] = { {
                                         4,
                                         0x08,
                                         1,
                                     },
                                     {
                                         1,
                                         0x08,
                                         0xFF,
                                     } };

static sSvAnmDat l_npc_anm_mawasi = {
    5,
    0x00,
    0xFF,
};

static sSvAnmDat l_npc_anm_kyoro = {
    1,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_unun[] = { {
                                          2,
                                          0x08,
                                          1,
                                      },
                                      {
                                          0xFF,
                                          0x08,
                                          0,
                                      } };

static sSvAnmDat l_npc_anm_sisi[] = { {
                                          3,
                                          0x08,
                                          1,
                                      },
                                      {
                                          0xFF,
                                          0x08,
                                          0,
                                      } };

static sSvAnmDat l_npc_anm_byebye[] = { {
                                            4,
                                            0x08,
                                            1,
                                        },
                                        {
                                            0xFF,
                                            0x08,
                                            0,
                                        } };

static sSvAnmDat l_npc_anm_shi[] = { {
                                         5,
                                         0x08,
                                         1,
                                     },
                                     {
                                         0xFF,
                                         0x08,
                                         0,
                                     } };

static sSvAnmDat* l_npc_anm_sv1_tbl[] = {
    &l_npc_anm_wait, &l_npc_anm_kyoro, l_npc_anm_unun, l_npc_anm_sisi, l_npc_anm_byebye, l_npc_anm_shi,
};

static u32 l_npc_se_sv1_tbl[] = { 0, 0, JA_SE_CV_SALV_CRUE_AGREE, JA_SE_CV_SALV_CRUE_SI, JA_SE_CV_SALV_CRUE_BYE, 0 };

static NpcDatStruct l_npc_dat = {}; // TODO

static u32 l_msg_sv_p1_1st_talk1[] = { 0x34BD, 0x34BE, 0x34BF, 0x34C0, 0x0002, 0x34C1, 0x34C2, 0x34C3, 0x0001, 0x34C4, 0x34E8, 0x0002, 0x34C5, 0x0004, 0x0000 };
static u32 l_msg_sv_p1_1st_talk2[] = { 0x34BD, 0x34BE, 0x34BF, 0x34C0, 0x0002, 0x34C1, 0x34C2, 0x34C3, 0x0001, 0x34C6, 0x34E9, 0x0002, 0x34C7, 0x0004, 0x0000 };

static u32 l_msg_sv_p1_2nd_talk1[] = { 0x34C8, 0x34C9, 0x34EA, 0x0002, 0x34CA, 0x0004, 0x0000 };
static u32 l_msg_sv_p1_2nd_talk2[] = { 0x34C8, 0x34CB, 0x0002, 0x34CC, 0x0004, 0x0000 };

static u32 l_msg_sv_p1_3rd_talk1[] = { 0x34CD, 0x34D0, 0x0002, 0x34D1, 0x0003, 0x0000 };
static u32 l_msg_sv_p1_3rd_talk2[] = { 0x34CD, 0x34CE, 0x0002, 0x34CF, 0x0003, 0x0000 };

static u32 l_msg_sv_p2_1st_talk[] = { 0x34D9, 0x34DA, 0x34DB, 0x0002, 0x34DC, 0x0004, 0x0000 };
static u32 l_msg_sv_p2_2nd_talk[] = { 0x34DD, 0x34DE, 0x0002, 0x34DF, 0x0003, 0x0000 };

static u32 l_msg_sv_p3_1st_talk[] = { 0x34D2, 0x34D3, 0x34D4, 0x0002, 0x34D5, 0x0004, 0x0000 };
static u32 l_msg_sv_p3_2nd_talk[] = { 0x34D6, 0x34D7, 0x0002, 0x34D8, 0x0003, 0x0000 };

static u32 l_msg_sv_p4_1st_talk[] = { 0x34E0, 0x34E1, 0x34E2, 0x34E3, 0x34E4, 0x0005, 0x0000 };
static u32 l_msg_sv_p4_2nd_talk[] = { 0x34E5, 0x34E6, 0x34E7, 0x0005, 0x0000 };

static u32* l_msg_sv_talk_tbl[] = { l_msg_sv_p1_1st_talk1, l_msg_sv_p1_1st_talk2, l_msg_sv_p1_2nd_talk1, l_msg_sv_p1_2nd_talk2,
                                    l_msg_sv_p1_3rd_talk1, l_msg_sv_p1_3rd_talk2, l_msg_sv_p2_1st_talk,  l_msg_sv_p2_2nd_talk,
                                    l_msg_sv_p3_1st_talk,  l_msg_sv_p3_2nd_talk,  l_msg_sv_p4_1st_talk,  l_msg_sv_p4_2nd_talk };

static u16 l_msg_sv_flag_tbl[] = { 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 0x00 };

static u16 l_event_id_tbl[] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02 };

static u32 l_get_item_no[] = { 0xE5 };

typedef int (daNpcSv_c::*ExecuteInit_t)();
static ExecuteInit_t l_execute_init[] = {
    &daNpcSv_c::executeWaitInit,
    &daNpcSv_c::executeTalkInit,
};

typedef void (daNpcSv_c::*MoveProc_t)();
static MoveProc_t moveProc[] = {
    &daNpcSv_c::executeWait,
    &daNpcSv_c::executeTalk,
};

/* 00000078-0000021C       .text __ct__9daNpcSv_cFv */
daNpcSv_c::daNpcSv_c() {
    /* Nonmatching */
}

/* 00000528-00000640       .text daNpc_People_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_People_nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000640-00000660       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpcSv_c*)i_this)->createHeap();
}

/* 00000660-000006B8       .text phase_1__FP9daNpcSv_c */
cPhs_State phase_1(daNpcSv_c* i_this) {
    fopAcM_ct(i_this, daNpcSv_c);
    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 000006B8-00000738       .text phase_2__FP9daNpcSv_c */
cPhs_State phase_2(daNpcSv_c* i_this) {
    cPhs_State state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getNpcNo()]);

    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x3800)) {
            state = i_this->createInit();
        } else {
#if VERSION > VERSION_DEMO
            i_this->mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 00000738-00000768       .text _create__9daNpcSv_cFv */
cPhs_State daNpcSv_c::_create() {
    static cPhs__Handler l_method[] = { (cPhs__Handler)&phase_1, (cPhs__Handler)&phase_2, (cPhs__Handler)NULL };

    return dComLbG_PhaseHandler(&mPhaseCreate, l_method, this);
}

/* 00000768-00000A04       .text createHeap__9daNpcSv_cFv */
BOOL daNpcSv_c::createHeap() {
    /* Nonmatching */
}

/* 00000A04-00000C74       .text createInit__9daNpcSv_cFv */
cPhs_State daNpcSv_c::createInit() {
    /* Nonmatching */
    return cPhs_COMPLEATE_e;
}

/* 00000C74-00000CD8       .text _delete__9daNpcSv_cFv */
bool daNpcSv_c::_delete() {
    /* Nonmatching */
}

/* 00000CD8-00000DAC       .text _draw__9daNpcSv_cFv */
bool daNpcSv_c::_draw() {
    /* Nonmatching */
}

/* 00000DAC-00000F90       .text _execute__9daNpcSv_cFv */
bool daNpcSv_c::_execute() {
    /* Nonmatching */
}

/* 00000F90-00000FB8       .text executeCommon__9daNpcSv_cFv */
void daNpcSv_c::executeCommon() {
    /* Nonmatching */
}

/* 00000FB8-00001000       .text executeSetMode__9daNpcSv_cFUc */
void daNpcSv_c::executeSetMode(u8 i_initIdx) {
    mMoveState = (this->*l_execute_init[i_initIdx])();
}

/* 00001000-00001080       .text executeWaitInit__9daNpcSv_cFv */
BOOL daNpcSv_c::executeWaitInit() {
    /* Nonmatching */
}

/* 00001080-0000131C       .text executeWait__9daNpcSv_cFv */
void daNpcSv_c::executeWait() {
    /* Nonmatching */
}

/* 0000131C-00001338       .text executeTalkInit__9daNpcSv_cFv */
BOOL daNpcSv_c::executeTalkInit() {
    /* Nonmatching */
}

/* 00001338-000013B8       .text executeTalk__9daNpcSv_cFv */
void daNpcSv_c::executeTalk() {
    /* Nonmatching */
}

/* 000013B8-000013EC       .text checkOrder__9daNpcSv_cFv */
void daNpcSv_c::checkOrder() {
    /* Nonmatching */
}

/* 000013EC-00001458       .text eventOrder__9daNpcSv_cFv */
void daNpcSv_c::eventOrder() {
    /* Nonmatching */
}

/* 00001458-00001570       .text eventMove__9daNpcSv_cFv */
void daNpcSv_c::eventMove() {
    /* Nonmatching */
}

/* 00001570-00001744       .text privateCut__9daNpcSv_cFv */
void daNpcSv_c::privateCut() {
    /* Nonmatching */
}

/* 00001744-00001814       .text eventMesSetInit__9daNpcSv_cFi */
void daNpcSv_c::eventMesSetInit(int) {
    /* Nonmatching */
}

/* 00001814-0000184C       .text eventMesSet__9daNpcSv_cFv */
void daNpcSv_c::eventMesSet() {
    /* Nonmatching */
}

/* 0000184C-000018F0       .text eventGetItemInit__9daNpcSv_cFi */
void daNpcSv_c::eventGetItemInit(int) {
    /* Nonmatching */
}

/* 000018F0-000018F8       .text eventGetItem__9daNpcSv_cFv */
bool daNpcSv_c::eventGetItem() {
    return true;
}

/* 000018F8-000019E0       .text eventSetAngleInit__9daNpcSv_cFv */
void daNpcSv_c::eventSetAngleInit() {
    /* Nonmatching */
}

/* 000019E0-00001A74       .text eventAttentionInit__9daNpcSv_cFi */
void daNpcSv_c::eventAttentionInit(int) {
    /* Nonmatching */
}

/* 00001A74-00001BC8       .text eventAttention__9daNpcSv_cFv */
void daNpcSv_c::eventAttention() {
    /* Nonmatching */
}

/* 00001BC8-00001BD4       .text eventTurnOkInit__9daNpcSv_cFv */
void daNpcSv_c::eventTurnOkInit() {
    /* Nonmatching */
}

/* 00001BD4-00001CF0       .text talk2__9daNpcSv_cFiP10fopAc_ac_c */
void daNpcSv_c::talk2(int, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001CF0-00001DC8       .text next_msgStatus__9daNpcSv_cFPUl */
u16 daNpcSv_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001DC8-00001EB4       .text getMsg__9daNpcSv_cFv */
u32 daNpcSv_c::getMsg() {
    /* Nonmatching */
}

/* 00001EB4-00001EBC       .text setMessage__9daNpcSv_cFUl */
void daNpcSv_c::setMessage(u32 i_message) {
    mCurrMsgNo = i_message;
}

/* 00001EBC-00001F74       .text setAnmFromMsgTag__9daNpcSv_cFv */
void daNpcSv_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 00001F74-00001F94       .text getPrmNpcNo__9daNpcSv_cFv */
void daNpcSv_c::getPrmNpcNo() {
    /* Nonmatching */
}

/* 00001F94-0000209C       .text setMtx__9daNpcSv_cFv */
void daNpcSv_c::setMtx() {
    /* Nonmatching */
}

/* 0000209C-000023D4       .text chkAttention__9daNpcSv_cFv */
void daNpcSv_c::chkAttention() {
    /* Nonmatching */
}

/* 000023D4-00002520       .text lookBack__9daNpcSv_cFv */
void daNpcSv_c::lookBack() {
    /* Nonmatching */
}

/* 00002520-000025E8       .text playAnm__9daNpcSv_cFv */
void daNpcSv_c::playAnm() {
    /* Nonmatching */
}

/* 000025E8-000026C8       .text setAnm__9daNpcSv_cFUcif */
void daNpcSv_c::setAnm(u8, int, f32) {
    /* Nonmatching */
}

/* 000026C8-00002768       .text setAnmTbl__9daNpcSv_cFP9sSvAnmDat */
void daNpcSv_c::setAnmTbl(sSvAnmDat*) {
    /* Nonmatching */
}

/* 00002768-000027E0       .text setCollision__9daNpcSv_cFP8dCcD_Cyl4cXyzff */
void daNpcSv_c::setCollision(dCcD_Cyl*, cXyz, f32, f32) {
    /* Nonmatching */
}

/* 000027E0-0000293C       .text getTalkNo__9daNpcSv_cFv */
void daNpcSv_c::getTalkNo() {
    /* Nonmatching */
}

/* 0000293C-00002958       .text isTalkOK__9daNpcSv_cFv */
void daNpcSv_c::isTalkOK() {
    /* Nonmatching */
}

/* 00002958-00002978       .text daNpc_PeopleCreate__FPv */
static cPhs_State daNpc_PeopleCreate(void* i_this) {
    return ((daNpcSv_c*)i_this)->_create();
}

/* 00002978-0000299C       .text daNpc_PeopleDelete__FPv */
static BOOL daNpc_PeopleDelete(void* i_this) {
    return ((daNpcSv_c*)i_this)->_delete();
}

/* 0000299C-000029C0       .text daNpc_PeopleExecute__FPv */
static BOOL daNpc_PeopleExecute(void* i_this) {
    return ((daNpcSv_c*)i_this)->_execute();
}

/* 000029C0-000029E4       .text daNpc_PeopleDraw__FPv */
static BOOL daNpc_PeopleDraw(void* i_this) {
    return ((daNpcSv_c*)i_this)->_draw();
}

/* 000029E4-000029EC       .text daNpc_PeopleIsDelete__FPv */
static BOOL daNpc_PeopleIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_PeopleMethodTable = {
    (process_method_func)daNpc_PeopleCreate,
    (process_method_func)daNpc_PeopleDelete,
    (process_method_func)daNpc_PeopleExecute,
    (process_method_func)daNpc_PeopleIsDelete,
    (process_method_func)daNpc_PeopleDraw,
};

actor_process_profile_definition g_profile_NPC_SV = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SV_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcSv_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SV_e,
    /* Actor SubMtd */ &daNpc_PeopleMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
