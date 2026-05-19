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
        /* resSize          */ 2112,
        /* resIndex         */ 12,
        /* field_0x006      */ 6,
        /* cullSizeBoxMin   */ { -60, -1, -60 },
        /* cullSizeBoxMax   */ { 60, 251, 60 },
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
        /* resSize          */ 2112,
        /* resIndex         */ 11,
        /* field_0x006      */ 5,
        /* cullSizeBoxMin   */ { -90, -1, -90 },
        /* cullSizeBoxMax   */ { 90, 401, 90 },
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
    JUT_ASSERT(282, model_data != NULL);
    
    mModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    if (mModel != NULL) {
        model_data->getJointTree().getJointNodePointer(attr().field_0x016 & 0xffff)->setCallBack(jnodeCB_lower);
        mModel->setUserArea((u32)this);
    }
    return mModel != NULL;
}

/* 00000184-0000033C       .text Create__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Create() {
    /* Nonmatching */
    unsigned int uVar2;
    this->field_0x338 = 1.0f;
    this->field_0x33C = 1.0f;
    this->cullMtx = this->mModel->getBaseTRMtx();
    this->init_mtx();
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
        Vec temp;
        temp.z = current.pos.z;
        temp.y = 50.0f + current.pos.y;
        temp.x = current.pos.x;
        this->field_0x2D8.SetPos(&temp);
        uVar2 = fopAcM_GetID(this);
        this->field_0x2D8.SetActorPid(uVar2);
        this->field_0x32C = dComIfG_Bgsp()->GroundCross(&this->field_0x2D8);
    }
    if (this->field_0x2D4 == 1) {
        this->actor_status &= 0xffffffc0;
        this->gbaName = 0;
    }
    this->mpBgW->SetRideCallback(rideCB);
    this->mode_wait_init();
    return TRUE;
}

/* 0000033C-00000544       .text Mthd_Create__Q29daObjJump5Act_cFv */
cPhs_State daObjJump::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjJump::Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&this->mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        this->field_0x2D4 = prm_get_type();
        phase_state = MoveBGCreate(
            M_arcname,
            attr().resIndex,
            dBgS_MoveBGProc_Typical,
            attr().resSize
        );
        JUT_ASSERT(384, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
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
    dComIfG_resDelete(&mPhase, M_arcname);
    return result;
}

/* 00000A58-00000B78       .text set_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    float fVar1 = attr().field_0x020 - attr().field_0x024;
    float fVar2 = attr().field_0x01C - attr().field_0x018;
    float fVar3 = (this->field_0x33C - 1.0f);
    float fVar4 = (fVar1 + fVar2 * fVar3) / fVar1;
    mDoMtx_stack_c::transM(0.0f, attr().field_0x024, 0.0f);
    mDoMtx_stack_c::scaleM(1.0f, fVar4,1.0f);
    mDoMtx_stack_c::transM(0.0f, -attr().field_0x024, 0.0f);
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000B78-00000BB4       .text init_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::init_mtx() {
    this->mModel->setBaseScale(this->scale);
    this->set_mtx();
    return;
}

/* 00000BB4-00000D9C       .text set_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_push_flag() {
    this->field_0x345 = 0;
    if (this->field_0x344 != 0) {
        if (this->field_0x347 < 0xff) {
            this->field_0x347 += 1;
        }
        if (this->field_0x347 == attr().field_0x043) {
            this->field_0x345 = 1;
        }
    } else {
        this->field_0x347 = 0;
    }
    this->field_0x346 = 0;
    if (this->field_0x344 != 0) {
        this->field_0x348 = 0;
    } else {
        if (this->field_0x348 < 0xff) {
            this->field_0x348 += 1;
        }
        if (this->field_0x348 == attr().field_0x044) {
            this->field_0x346 = 1;
        }
    }
    this->field_0x34a = 0;
    if (this->field_0x349 != 0 && dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK100_e)) {
        if (this->field_0x34b < 0xff) {
            this->field_0x34b += 1;
        }
        if (this->field_0x34b == attr().field_0x045) {
            this->field_0x34a = 1;
        }
    } else {
        this->field_0x34b = 0;
    }
    this->field_0x34d = 0;
    if (this->field_0x34c != 0) {
        if (this->field_0x34f < 0xff) {
            this->field_0x34f += 1;
        }
        if (this->field_0x34f == attr().field_0x046) {
            this->field_0x34d = 1;
        }
    } else {
        this->field_0x34f = 0;
    }
    this->field_0x34e = 0;
    if (this->field_0x34c != 0) {
        this->field_0x350 = 0;
        return;
    }
    if (this->field_0x350 < 0xff) {
        this->field_0x350 += 1;
    }
    if (this->field_0x350 != attr().field_0x047) {
        return;
    }
    this->field_0x34e = 1;
    return;
}

/* 00000D9C-00000DB4       .text clear_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::clear_push_flag() {
    this->field_0x344 = 0;
    this->field_0x34c = 0;
    this->field_0x349 = 0;
    this->field_0x354 = 0;
    return;
}

/* 00000DB4-00000E1C       .text calc_vib_pos__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::calc_vib_pos() {
    this->field_0x340 = this->field_0x340 - (this->field_0x33C - this->field_0x338) * attr().field_0x02C;
    this->field_0x340 = this->field_0x340 - this->field_0x340 * attr().field_0x028;
    this->field_0x33C = this->field_0x33C + this->field_0x340;
    return;
}

/* 00000E1C-00000E74       .text rideCB__Q29daObjJump5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjJump::Act_c::rideCB(dBgW*, fopAc_ac_c* param_2, fopAc_ac_c* param_3) {
    Act_c* pvVar4 = (Act_c *) param_2;
    daPy_py_c* player = (daPy_py_c *) param_3;
    pvVar4->field_0x344 = 1;
    if (fopAcM_GetProfName(param_3) != PROC_PLAYER) {
        return;
    }
    pvVar4->field_0x349 = 1;
    if (player->checkEquipHeavyBoots()) {
        pvVar4->field_0x34c = 1;
    }
    const Attr_c* a = &M_attr[pvVar4->field_0x2D4];
    if (fopAcM_GetSpeedF(player) > a->field_0x04C) {
        pvVar4->field_0x354 = 1;
    }
    return;
}

/* 00000E74-00000F48       .text jnodeCB_lower__Q29daObjJump5Act_cFP7J3DNodei */
BOOL daObjJump::Act_c::jnodeCB_lower(J3DNode* param_1, int param_2) {
    /* Nonmatching */
    if (param_2 == 0) {
        J3DModel* model = j3dSys.getModel();
        Act_c* pvVar4 = (Act_c *) model->getUserArea();
        J3DJoint* joint = (J3DJoint*) param_1;
        s32 jntNo = joint->getJntNo();
        PSMTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::get());
        mDoMtx_stack_c::scaleM(pvVar4->field_0x33C,1.0f,1.0f);
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        float fVar1 = M_attr[pvVar4->field_0x2D4].field_0x01C - M_attr[pvVar4->field_0x2D4].field_0x018;
        j3dSys.mCurrentMtx[1][3] += fVar1 * (pvVar4->field_0x33C - 1.0f);
    }
    return TRUE;
}

/* 00000F48-00000F64       .text mode_wait_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait_init() {
    this->field_0x330 = 0;
    this->field_0x338 = 1.0f;
    this->field_0x352 = 0;
    return;
}

/* 00000F64-0000108C       .text mode_wait__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait() {
    if (this->field_0x352 <= 0 && (this->field_0x345 != 0 || this->field_0x346 != 0 || this->field_0x34a != 0 || this->field_0x34d != 0)) {
        this->field_0x340 += attr().field_0x030;
        this->field_0x352 = attr().field_0x048;
    }
    else if (this->field_0x352 > 0) {
        this->field_0x352 -= 1;
    }
    if (this->field_0x34f > attr().field_0x040) {
        fopAcM_seStart(this, JA_SE_OBJ_JUMP_SPR_CLOSE, 0);
        this->mode_w_l_init();
    }
    return;
}

/* 0000108C-000010B4       .text mode_w_l_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l_init() {
    this->field_0x330 = 1;
    this->field_0x338 = attr().field_0x038;
    return;
}

/* 000010B4-000010E8       .text mode_w_l__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l() {
    if (this->field_0x33C <= this->field_0x338) {
        this->mode_lower_init();
    }
    return;
}

/* 000010E8-000010FC       .text mode_lower_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower_init() {
    this->field_0x330 = 2;
    this->field_0x352 = 0;
    return;
}

/* 000010FC-00001200       .text mode_lower__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower() {
    if (this->field_0x352 <= 0 && this->field_0x34e != 0) {
        this->field_0x340 += attr().field_0x030;
        this->field_0x352 = attr().field_0x048;
    }
    else if (this->field_0x352 > 0) {
        this->field_0x352 -= 1;
    }
    if (this->field_0x350 > attr().field_0x041) {
        fopAcM_seStart(this, JA_SE_OBJ_JUMP_SPR_OPEN, 0);
        this->mode_l_u_init();
    }
    return;
}

/* 00001200-00001228       .text mode_l_u_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u_init() {
    this->field_0x330 = 3;
    this->field_0x338 = attr().field_0x03C;
    return;
}

/* 00001228-00001290       .text mode_l_u__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u() {
    if (this->field_0x33C >= this->field_0x338) {
        this->field_0x33C = this->field_0x338;
        this->field_0x340 = 0.0f;
        if (*(u8*)(&this->field_0x349) != 0) {
            daPy_py_c* player = daPy_getPlayerActorClass();
            player->onForceVomitJump();
        }
        this->mode_upper_init();
    }
    return;
}

/* 00001290-000012B8       .text mode_upper_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper_init() {
    this->field_0x330 = 4;
    this->field_0x334 = attr().field_0x042;
    return;
}

/* 000012B8-000012EC       .text mode_upper__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper() {
    s16 var = this->field_0x334;
    this->field_0x334 = var - 1;
    if ((s16)(var - 1) <= 0) {
        mode_u_w_init();
    }
    return;
}

/* 000012EC-00001304       .text mode_u_w_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w_init() {
    this->field_0x330 = 5;
    this->field_0x338 = 1.0f;
    return;
}

/* 00001304-00001338       .text mode_u_w__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w() {
    if (this->field_0x33C <= this->field_0x338) {
        this->mode_wait_init();
    }
    return;
}

/* 00001338-000014B0       .text Execute__Q29daObjJump5Act_cFPPA3_A4_f */
BOOL daObjJump::Act_c::Execute(Mtx** param_1) {
    /* Nonmatching */ 

    this->set_push_flag();

    typedef void (daObjJump::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjJump::Act_c::mode_wait,
        &daObjJump::Act_c::mode_w_l,
        &daObjJump::Act_c::mode_lower,
        &daObjJump::Act_c::mode_l_u,
        &daObjJump::Act_c::mode_upper,
        &daObjJump::Act_c::mode_u_w
    };

    (this->*mode_proc[this->field_0x330])();

    if ((this->field_0x330 == 0 || this->field_0x330 == 2) && this->field_0x354 != 0) {
        this->field_0x340 += attr().field_0x034;
    }
    this->calc_vib_pos();
    this->set_mtx();
    *param_1 = &M_tmp_mtx;
    this->clear_push_flag();
    return TRUE;
}

/* 000014B0-00001594       .text Draw__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(this->mModel, &tevStr);
    dComIfGd_setList();
    mDoExt_modelUpdateDL(this->mModel);
    dComIfGd_setListInvisisble();
    if (attr().field_0x014 != 0) {
        dComIfGd_setSimpleShadow2(
            &current.pos,
            this->field_0x32C,
            70.0f,
            this->field_0x2D8,
            this->shape_angle.y,
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
    return ((daObjJump::Act_c*)i_this)->Draw();
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
