/**
 * d_a_obj_jump.cpp
 * Object - Wind Temple - Iron Boots springboard
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_jump.h"
#include "d/actor/d_a_player.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

namespace daObjJump {

Mtx daObjJump::Act_c::M_tmp_mtx;
const char Act_c::M_arcname[] = "Hjump";
const Attr_c Act_c::M_attr[2] = {
    {
        /* resSize          */ DEMO_SELECT(0x8000, 0x840),
        /* resIndex         */ 12,
        /* field_0x006      */ 6,
        /* cullSizeBoxMin   */ { -60, -1, -60 },
        /* cullSizeBoxMax   */ { 60, VERSION_SELECT(151, 151, 251, 251), 60 },
        /* field_0x014      */ 1,
        /* field_0x015      */ 0,
        /* field_0x016      */ 1,
        /* field_0x018      */ 40.0f,
        /* field_0x01C      */ 125.0f,
        /* field_0x020      */ 150.0f,
        /* field_0x024      */ 0.0f,
        /* field_0x028      */ 0.4f,
        /* field_0x02C      */ 0.7f,
        /* field_0x030      */ -0.15f,
        /* field_0x034      */ -0.02f,
        /* field_0x038      */ 0.1f,
        /* field_0x03C      */ 1.2f,
        /* field_0x040      */ 0x0f,
        /* field_0x041      */ 0x05,
        /* field_0x042      */ 0x05,
        /* field_0x043      */ 0x04,
        /* field_0x044      */ 0x04,
        /* field_0x045      */ 0x06,
        /* field_0x046      */ 0x04,
        /* field_0x047      */ 0x04,
        /* field_0x048      */ 0x01,
        /* field_0x049      */ { 0, 0, 0 },
        /* field_0x04C      */ 2.0f
    },
    {
        /* resSize          */ DEMO_SELECT(0x8000, 0x840),
        /* resIndex         */ 11,
        /* field_0x006      */ 5,
        /* cullSizeBoxMin   */ { -90, -1, -90 },
        /* cullSizeBoxMax   */ { 90, VERSION_SELECT(301, 301, 401, 401), 90 },
        /* field_0x014      */ 0,
        /* field_0x015      */ 0,
        /* field_0x016      */ 1,
        /* field_0x018      */ 160.0f,
        /* field_0x01C      */ 270.0f,
        /* field_0x020      */ 300.0f,
        /* field_0x024      */ 150.0f,
        /* field_0x028      */ 0.4f,
        /* field_0x02C      */ 0.7f,
        /* field_0x030      */ -0.15f,
        /* field_0x034      */ -0.02f,
        /* field_0x038      */ 0.1f,
        /* field_0x03C      */ 1.2f,
        /* field_0x040      */ 0x0f,
        /* field_0x041      */ 0x05,
        /* field_0x042      */ 0x05,
        /* field_0x043      */ 0x04,
        /* field_0x044      */ 0x04,
        /* field_0x045      */ 0x06,
        /* field_0x046      */ 0x04,
        /* field_0x047      */ 0x04,
        /* field_0x048      */ 0x01,
        /* field_0x049      */ { 0, 0, 0 },
        /* field_0x04C      */ 2.0f
    }
};
};

/* 00000078-00000184       .text CreateHeap__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, attr().field_0x006);
    JUT_ASSERT(DEMO_SELECT(277, 282), model_data != NULL);
    
    mModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    if (mModel != NULL) {
        model_data->getJointTree().getJointNodePointer(attr().field_0x016)->setCallBack(jnodeCB_lower);
        mModel->setUserArea((u32)this);
    }
    return mModel != NULL;
}

/* 00000184-0000033C       .text Create__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Create() {
    unsigned int uVar2;
    field_0x338 = 1.0f;
    field_0x33C = 1.0f;
    cullMtx = mModel->getBaseTRMtx();
    init_mtx();
    fopAcM_setCullSizeBox(
        this,
        attr().cullSizeBoxMin.x,
        attr().cullSizeBoxMin.y,
        attr().cullSizeBoxMin.z,
        attr().cullSizeBoxMax.x,
        attr().cullSizeBoxMax.y,
        attr().cullSizeBoxMax.z
    );
    if (attr().field_0x014 != 0) {
        cXyz temp(current.pos.x, current.pos.y + 50.0f, current.pos.z);
        field_0x2D8.SetPos(&temp);
        uVar2 = fopAcM_GetID(this);
        field_0x2D8.SetActorPid(uVar2);
        field_0x32C = dComIfG_Bgsp()->GroundCross(&field_0x2D8);
    }
#if VERSION > VERSION_DEMO
    if (field_0x2D4 == 1) {
        actor_status &= ~0x3F;
        gbaName = 0;
    }
#endif
    mpBgW->SetRideCallback(rideCB);
    mode_wait_init();
    return TRUE;
}

/* 0000033C-00000544       .text Mthd_Create__Q29daObjJump5Act_cFv */
cPhs_State daObjJump::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjJump::Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        field_0x2D4 = prm_get_type();
        phase_state = MoveBGCreate(
            M_arcname,
            attr().resIndex,
            dBgS_MoveBGProc_Typical,
            attr().resSize
        );
        JUT_ASSERT(DEMO_SELECT(373, 384), (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000A04-00000A0C       .text Delete__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Delete() {
    return TRUE;
}

/* 00000A0C-00000A58       .text Mthd_Delete__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Mthd_Delete() {
    u32 result = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return result;
}

/* 00000A58-00000B78       .text set_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    float fVar1 = attr().field_0x020 - attr().field_0x024;
    float fVar2 = attr().field_0x01C - attr().field_0x018;
    float fVar3 = (field_0x33C - 1.0f);
    float fVar4 = (fVar1 + fVar2 * fVar3) / fVar1;
    mDoMtx_stack_c::transM(0.0f, attr().field_0x024, 0.0f);
    mDoMtx_stack_c::scaleM(1.0f, fVar4,1.0f);
    mDoMtx_stack_c::transM(0.0f, -attr().field_0x024, 0.0f);
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000B78-00000BB4       .text init_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::init_mtx() {
    mModel->setBaseScale(scale);
    set_mtx();
}

/* 00000BB4-00000D9C       .text set_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_push_flag() {
    field_0x345 = 0;
    if (field_0x344 != 0) {
        if (field_0x347 < 0xff) {
            field_0x347 += 1;
        }
        if (field_0x347 == attr().field_0x043) {
            field_0x345 = 1;
        }
    } else {
        field_0x347 = 0;
    }
    field_0x346 = 0;
    if (field_0x344 != 0) {
        field_0x348 = 0;
    } else {
        if (field_0x348 < 0xff) {
            field_0x348 += 1;
        }
        if (field_0x348 == attr().field_0x044) {
            field_0x346 = 1;
        }
    }
    field_0x34a = 0;
    if (field_0x349 != 0 && dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK100_e)) {
        if (field_0x34b < 0xff) {
            field_0x34b += 1;
        }
        if (field_0x34b == attr().field_0x045) {
            field_0x34a = 1;
        }
    } else {
        field_0x34b = 0;
    }
    field_0x34d = 0;
    if (field_0x34c != 0) {
        if (field_0x34f < 0xff) {
            field_0x34f += 1;
        }
        if (field_0x34f == attr().field_0x046) {
            field_0x34d = 1;
        }
    } else {
        field_0x34f = 0;
    }
    field_0x34e = 0;
    if (field_0x34c != 0) {
        field_0x350 = 0;
        return;
    }
    if (field_0x350 < 0xff) {
        field_0x350 += 1;
    }
    if (field_0x350 != attr().field_0x047) {
        return;
    }
    field_0x34e = 1;
}

/* 00000D9C-00000DB4       .text clear_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::clear_push_flag() {
    field_0x344 = 0;
    field_0x34c = 0;
    field_0x349 = 0;
    field_0x354 = 0;
}

/* 00000DB4-00000E1C       .text calc_vib_pos__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::calc_vib_pos() {
    f32 f2 = field_0x33C - field_0x338;
    field_0x340 = field_0x340 - f2 * attr().field_0x02C;
    field_0x340 = field_0x340 - field_0x340 * attr().field_0x028;
    field_0x33C = field_0x33C + field_0x340;
}

/* 00000E1C-00000E74       .text rideCB__Q29daObjJump5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjJump::Act_c::rideCB(dBgW*, fopAc_ac_c* param_2, fopAc_ac_c* param_3) {
    Act_c* i_this = (Act_c *) param_2;
    daPy_py_c* player = (daPy_py_c *) param_3;
    i_this->field_0x344 = 1;
    if (fopAcM_GetProfName(param_3) != PROC_PLAYER) {
        return;
    }
    i_this->field_0x349 = 1;
    if (player->checkEquipHeavyBoots()) {
        i_this->field_0x34c = 1;
    }
    if (fopAcM_GetSpeedF(player) > i_this->attr().field_0x04C) {
        i_this->field_0x354 = 1;
    }
}

/* 00000E74-00000F48       .text jnodeCB_lower__Q29daObjJump5Act_cFP7J3DNodei */
BOOL daObjJump::Act_c::jnodeCB_lower(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = (J3DModel*)j3dSys.getModel();
        Act_c* i_this = (Act_c *) model->getUserArea();
        J3DJoint* joint = (J3DJoint*) node;
        u16 jntNo = joint->getJntNo();
        PSMTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::get());
        mDoMtx_stack_c::scaleM(i_this->field_0x33C,1.0f,1.0f);
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        f32 f2 = i_this->attr().field_0x01C - i_this->attr().field_0x018;
        f32 f1 = f2 * (i_this->field_0x33C - 1.0f);
        j3dSys.mCurrentMtx[1][3] += f1;
    }
    return TRUE;
}

/* 00000F48-00000F64       .text mode_wait_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait_init() {
    field_0x330 = 0;
    field_0x338 = 1.0f;
    field_0x352 = 0;
}

/* 00000F64-0000108C       .text mode_wait__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait() {
    if (field_0x352 <= 0 && (field_0x345 != 0 || field_0x346 != 0 || field_0x34a != 0 || field_0x34d != 0)) {
        field_0x340 += attr().field_0x030;
        field_0x352 = attr().field_0x048;
    }
    else if (field_0x352 > 0) {
        field_0x352 -= 1;
    }
    if (field_0x34f > attr().field_0x040) {
        fopAcM_seStart(this, JA_SE_OBJ_JUMP_SPR_CLOSE, 0);
        mode_w_l_init();
    }
}

/* 0000108C-000010B4       .text mode_w_l_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l_init() {
    field_0x330 = 1;
    field_0x338 = attr().field_0x038;
}

/* 000010B4-000010E8       .text mode_w_l__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l() {
    if (field_0x33C <= field_0x338) {
        mode_lower_init();
    }
}

/* 000010E8-000010FC       .text mode_lower_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower_init() {
    field_0x330 = 2;
    field_0x352 = 0;
}

/* 000010FC-00001200       .text mode_lower__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower() {
    if (field_0x352 <= 0 && field_0x34e != 0) {
        field_0x340 += attr().field_0x030;
        field_0x352 = attr().field_0x048;
    }
    else if (field_0x352 > 0) {
        field_0x352 -= 1;
    }
    if (field_0x350 > attr().field_0x041) {
        fopAcM_seStart(this, JA_SE_OBJ_JUMP_SPR_OPEN, 0);
        mode_l_u_init();
    }
}

/* 00001200-00001228       .text mode_l_u_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u_init() {
    field_0x330 = 3;
    field_0x338 = attr().field_0x03C;
}

/* 00001228-00001290       .text mode_l_u__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u() {
    if (field_0x33C >= field_0x338) {
        field_0x33C = field_0x338;
        field_0x340 = 0.0f;
        if (field_0x349 != 0) {
            daPy_py_c* player = daPy_getPlayerActorClass();
            player->onForceVomitJump();
        }
        mode_upper_init();
    }
}

/* 00001290-000012B8       .text mode_upper_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper_init() {
    field_0x330 = 4;
    field_0x334 = attr().field_0x042;
}

/* 000012B8-000012EC       .text mode_upper__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper() {
    s16 var = field_0x334;
    field_0x334 = var - 1;
    if ((s16)(var - 1) <= 0) {
        mode_u_w_init();
    }
}

/* 000012EC-00001304       .text mode_u_w_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w_init() {
    field_0x330 = 5;
    field_0x338 = 1.0f;
}

/* 00001304-00001338       .text mode_u_w__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w() {
    if (field_0x33C <= field_0x338) {
        mode_wait_init();
    }
}

/* 00001338-000014B0       .text Execute__Q29daObjJump5Act_cFPPA3_A4_f */
BOOL daObjJump::Act_c::Execute(Mtx** param_1) {
    /* Nonmatching */ 

    set_push_flag();

    typedef void (daObjJump::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjJump::Act_c::mode_wait,
        &daObjJump::Act_c::mode_w_l,
        &daObjJump::Act_c::mode_lower,
        &daObjJump::Act_c::mode_l_u,
        &daObjJump::Act_c::mode_upper,
        &daObjJump::Act_c::mode_u_w
    };

    (this->*mode_proc[field_0x330])();

    if ((field_0x330 == 0 || field_0x330 == 2) && field_0x354 != 0) {
        field_0x340 += attr().field_0x034;
    }
    calc_vib_pos();
    set_mtx();
    *param_1 = &M_tmp_mtx;
    clear_push_flag();
    return TRUE;
}

/* 000014B0-00001594       .text Draw__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();
    if (attr().field_0x014 != 0) {
        dComIfGd_setSimpleShadow2(
            &current.pos,
            field_0x32C,
            70.0f,
            field_0x2D8,
            shape_angle.y,
            1.0f,
            NULL
        );
    }
    return TRUE;
}

namespace daObjJump {
namespace {
/* 00001594-000015B4       .text Mthd_Create__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->Mthd_Create();
}

/* 000015B4-000015D4       .text Mthd_Delete__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->Mthd_Delete();
}

/* 000015D4-000015F4       .text Mthd_Execute__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->MoveBGExecute();
}

/* 000015F4-00001620       .text Mthd_Draw__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->MoveBGDraw();
}

/* 00001620-0000164C       .text Mthd_IsDelete__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjJump

actor_process_profile_definition g_profile_Obj_Jump = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0004,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Jump,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjJump::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Jump,
    /* Actor SubMtd */ &daObjJump::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
