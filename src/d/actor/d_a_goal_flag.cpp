/**
 * d_a_goal_flag.cpp
 * Object - Big red finish line flag (Boating Course, Flight Control Platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_goal_flag.h"
#include "d/d_path.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

#include "assets/l_txa_dummy_hataTEX.h"

static Vec l_pos[] = {
    { -1000.0f,    0.0f, 0.0f }, 
    {  -750.0f,    0.0f, 0.0f }, 
    {  -500.0f,    0.0f, 0.0f }, 
    {  -250.0f,    0.0f, 0.0f }, 
    {     0.0f,    0.0f, 0.0f }, 
    {   250.0f,    0.0f, 0.0f }, 
    {   500.0f,    0.0f, 0.0f }, 
    {   750.0f,    0.0f, 0.0f }, 
    {  1000.0f,    0.0f, 0.0f }, 
    { -1000.0f, -100.0f, 0.0f }, 
    {  -750.0f, -100.0f, 0.0f }, 
    {  -500.0f, -100.0f, 0.0f }, 
    {  -250.0f, -100.0f, 0.0f }, 
    {     0.0f, -100.0f, 0.0f }, 
    {   250.0f, -100.0f, 0.0f }, 
    {   500.0f, -100.0f, 0.0f }, 
    {   750.0f, -100.0f, 0.0f }, 
    {  1000.0f, -100.0f, 0.0f }, 
    { -1000.0f, -200.0f, 0.0f }, 
    {  -750.0f, -200.0f, 0.0f }, 
    {  -500.0f, -200.0f, 0.0f }, 
    {  -250.0f, -200.0f, 0.0f }, 
    {     0.0f, -200.0f, 0.0f }, 
    {   250.0f, -200.0f, 0.0f }, 
    {   500.0f, -200.0f, 0.0f }, 
    {   750.0f, -200.0f, 0.0f }, 
    {  1000.0f, -200.0f, 0.0f }, 
    { -1000.0f, -300.0f, 0.0f }, 
    {  -750.0f, -300.0f, 0.0f }, 
    {  -500.0f, -300.0f, 0.0f }, 
    {  -250.0f, -300.0f, 0.0f }, 
    {     0.0f, -300.0f, 0.0f }, 
    {   250.0f, -300.0f, 0.0f }, 
    {   500.0f, -300.0f, 0.0f }, 
    {   750.0f, -300.0f, 0.0f }, 
    {  1000.0f, -300.0f, 0.0f }, 
    { -1000.0f, -400.0f, 0.0f }, 
    {  -750.0f, -400.0f, 0.0f }, 
    {  -500.0f, -400.0f, 0.0f }, 
    {  -250.0f, -400.0f, 0.0f }, 
    {     0.0f, -400.0f, 0.0f }, 
    {   250.0f, -400.0f, 0.0f }, 
    {   500.0f, -400.0f, 0.0f }, 
    {   750.0f, -400.0f, 0.0f }, 
    {  1000.0f, -400.0f, 0.0f } 
};

static cXy l_texCoord[] = {
    {   1.0f,  0.0f }, 
    { 0.875f,  0.0f }, 
    {  0.75f,  0.0f }, 
    { 0.625f,  0.0f }, 
    {   0.5f,  0.0f }, 
    { 0.375f,  0.0f }, 
    {  0.25f,  0.0f }, 
    { 0.125f,  0.0f }, 
    {   0.0f,  0.0f }, 
    {   1.0f, 0.25f }, 
    { 0.875f, 0.25f }, 
    {  0.75f, 0.25f }, 
    { 0.625f, 0.25f }, 
    {   0.5f, 0.25f }, 
    { 0.375f, 0.25f }, 
    {  0.25f, 0.25f }, 
    { 0.125f, 0.25f }, 
    {   0.0f, 0.25f }, 
    {   1.0f,  0.5f }, 
    { 0.875f,  0.5f }, 
    {  0.75f,  0.5f }, 
    { 0.625f,  0.5f }, 
    {   0.5f,  0.5f }, 
    { 0.375f,  0.5f }, 
    {  0.25f,  0.5f }, 
    { 0.125f,  0.5f }, 
    {   0.0f,  0.5f }, 
    {   1.0f, 0.75f }, 
    { 0.875f, 0.75f }, 
    {  0.75f, 0.75f }, 
    { 0.625f, 0.75f }, 
    {   0.5f, 0.75f }, 
    { 0.375f, 0.75f }, 
    {  0.25f, 0.75f }, 
    { 0.125f, 0.75f }, 
    {   0.0f, 0.75f }, 
    {   1.0f,  1.0f }, 
    { 0.875f,  1.0f }, 
    {  0.75f,  1.0f }, 
    { 0.625f,  1.0f }, 
    {   0.5f,  1.0f }, 
    { 0.375f,  1.0f }, 
    {  0.25f,  1.0f }, 
    { 0.125f,  1.0f }, 
    {   0.0f,  1.0f } 
};

#include "assets/l_goal_flag_DL.h"
#include "assets/l_goal_flag_matDL.h"
l_goal_flag_matDL(l_txa_dummy_hataTEX);

static const char* sub_arcname_tbl[] = {
    "Gflag",
    "Tgflag"
};
static const char arcname[] = "Cloth";

static daGFlag_HIO_c l_HIO;

daGFlag_HIO_c::~daGFlag_HIO_c() {
    m04 = -1;
}

/* 000000EC-00000210       .text setTexObj__16daGFlag_packet_cFUc */
void daGFlag_packet_c::setTexObj(unsigned char) {
    /* Nonmatching */
    static char* arc_name_tbl[] = {
        "Gflag",
        "Tgflag"
    };
}

/* 00000210-00000330       .text setToonTexObj__16daGFlag_packet_cFv */
void daGFlag_packet_c::setToonTexObj() {
    /* Nonmatching */
}

/* 00000330-00000978       .text draw__16daGFlag_packet_cFv */
void daGFlag_packet_c::draw() {
    /* Nonmatching */
}

/* 00000978-00000A04       .text setBackNrm__16daGFlag_packet_cFv */
void daGFlag_packet_c::setBackNrm() {
    /* Nonmatching */
}

/* 00000A04-00000E78       .text setNrmVtx__16daGFlag_packet_cFP4cXyzii */
void daGFlag_packet_c::setNrmVtx(cXyz*, int, int) {
    /* Nonmatching */
}

/* 00000EB4-00000F80       .text getRacePath__13daGoal_Flag_cFUc */
BOOL daGoal_Flag_c::getRacePath(unsigned char) {
    /* Nonmatching */
}

/* 00000F80-000010F4       .text RopeMove__13daGoal_Flag_cFv */
void daGoal_Flag_c::RopeMove() {
    /* Nonmatching, .data offsets */
    // TODO: wtf is going on in this method?
    static const f32 down_offset[] = {
        0.0f, 150.0f, 225.0f, 150.0f
    };
    for (int i = 0; i < field_0x16AC; i++) {
        cXyz& temp = getRopePos(i, field_0x169C[i])[0];
        temp = getRopePos(i, 0)[0];
        for (u32 j = 0; (s32)j < (s32)(field_0x169C[i] * 4); j++) {
            s32 temp3 = j & 3;
            s32 temp4 = (int)j >> 2;
            if (temp3 != 0) {
                cXyz& temp7 = getRopePos(i, temp4)[0];
                cXyz& temp8 = getRopePos(i, temp4 + 1)[0];
                cXyz& temp6 = getRopePos(i, temp4)[temp3];
                // looks like a LERP
                f32 temp9 = (f32)temp3 * 0.25f;
                f32 temp10 = 1.0f - temp9;
                temp6 = (temp7 * temp10) + (temp8 * temp9);
                temp6.y -= down_offset[temp3];
            }
        }
    }
}

/* 000010F4-0000123C       .text CreateBuoyRaces__13daGoal_Flag_cFv */
void daGoal_Flag_c::CreateBuoyRaces() {
    /* Nonmatching */
}

/* 0000123C-00001450       .text goal_check__13daGoal_Flag_cFv */
int daGoal_Flag_c::goal_check() {
    /* Nonmatching, .rodata */
    int o_ret;
    cXyz temp1 = dComIfGp_getPlayer(0)->current.pos - field_0x1658[0];

    cXyz temp2 = field_0x1658[1] - field_0x1658[0];
    temp2.y = 0.0f;
    temp2 = temp2.normZP();

    temp1.y = 0.0f;

    f32 mag = (field_0x1658[1] - field_0x1658[0]).absXZ();
    f32 dot = VECDotProduct(&temp2, &temp1);
    
    cXyz temp4;
    temp4.x = temp2.z;
    temp4.y = 0.0f;
    temp4.z = -temp2.x;

    f32 dot2 = VECDotProduct(&temp4, &temp1);

    o_ret = 0;
    if (dot > 0.0f && dot < mag) {
        if (field_0x1680 > 0.0f && dot2 <= 0.0f) {
            o_ret = 1;
        } else if (field_0x1680 <= 0.0f && dot2 > 0.0f) {
            o_ret = -1;
        }
    }

    field_0x1680 = dot2;
    return o_ret;
}

/* 00001450-0000183C       .text flag_move__13daGoal_Flag_cFv */
void daGoal_Flag_c::flag_move() {
    /* Nonmatching */
}

/* 0000183C-00001970       .text get_cloth_anim_sub_factor__FP4cXyzP4cXyzP4cXyzf */
void get_cloth_anim_sub_factor(cXyz*, cXyz*, cXyz*, float) {
    /* Nonmatching */
}

/* 00001970-00001CC0       .text get_cloth_anim_factor__13daGoal_Flag_cFP4cXyzP4cXyzP4cXyzii */
void daGoal_Flag_c::get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int) {
    /* Nonmatching */
}

/* 00001CC0-00001CE0       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_actor) {
    return ((daGoal_Flag_c*)i_actor)->CreateHeap();
}

/* 00001CE0-00001D74       .text CreateHeap__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::CreateHeap() {
    for (int i = 0; i < field_0x16AC; i++) {
        if (!field_0x16B0[i].init(1, (field_0x169C[i] << 2) + 1, 0)) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00001D74-00001DB4       .text getDemoAction__13daGoal_Flag_cFi */
void daGoal_Flag_c::getDemoAction(int param_1) {
    /* Nonmatching */
    static char* ActionNames[] = { 
        "00_dummy",
        "01_dummy",
        "02_dummy",
        "03_dummy",
        "04_dummy" 
    };
    dComIfGp_evmng_getMyActIdx(param_1, ActionNames, 5, FALSE, 0);
}

/* 00001DB4-00001F60       .text RaceStart__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::RaceStart() {
    /* Nonmatching */
    field_0x1720 = &daGoal_Flag_c::TimerExecute;
    return TRUE;
}

/* 00001F60-00002290       .text TimerExecute__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::TimerExecute() {
    /* Nonmatching */
    field_0x1720 = &daGoal_Flag_c::RaceEnd;
    static char* event_name_tbl[] = {
        "race_goal_cam",
        "race_fail_cam",
    };
}

/* 00002290-000023E0       .text RaceEnd__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::RaceEnd() {
    /* Nonmatching */
    static char* event_name_tbl[] = {
        "race_goal_cam",
        "race_fail_cam",
    };
}

/* 000023E0-00002400       .text daGoal_FlagCreate__FPv */
static cPhs_State daGoal_FlagCreate(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_create();
}

/* 00002400-00002968       .text _create__13daGoal_Flag_cFv */
cPhs_State daGoal_Flag_c::_create() {
    /* Nonmatching, .data and .rodata offsets */
    cPhs_State rt;
    u8 temp;
    dPath* path_ptr;

    fopAcM_SetupActor(this, daGoal_Flag_c);

    u32 prm = fopAcM_GetParam(this) & 0xFF;
    rt = dComIfG_resLoad(&field_0x1618, "Cloth");

    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }

    if (prm == 0 || prm == 0xFF) {
        temp = 0;
        rt = dComIfG_resLoad(&field_0x1620, "Gflag");
        scale.set(1.05f, 1.0f, 1.0f);
    } else {
        temp = 1;
        rt = dComIfG_resLoad(&field_0x1620, "Tgflag");
        scale.set(0.98f, 1.0f, 1.0f);
    }

    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }

    prm = (fopAcM_GetParam(this) >> 0x10) & 0xFF;
    if (prm != 0xFF) {
        path_ptr = dPath_GetRoomPath(prm, fopAcM_GetRoomNo(this));
        if (path_ptr) {
            BOOL path = getRacePath(path_ptr->m_nextID);
            if (path != FALSE) {
                if (fopAcM_entrySolidHeap(this, checkCreateHeap, 0x10000)) {
                    CreateBuoyRaces();
                } else {
                    return cPhs_ERROR_e;
                }
            }
        } else {
            return cPhs_ERROR_e;
        }
    } else {
        return cPhs_ERROR_e;
    }

    cXyz* pos_array = field_0x0290.getPos();
    for (int i = 0; i < 45; i++, pos_array++) {
        pos_array->set(l_pos[i]);
    }

    field_0x0290.setTexObj(temp);
    field_0x0290.setToonTexObj();

    path_ptr = dPath_GetRoomPath((fopAcM_GetParam(this) >> 0x10) & 0xFF, fopAcM_GetRoomNo(this));

    if (path_ptr) {
        field_0x1658[0].set(path_ptr->m_points[0].m_position);
        field_0x1658[1].set(path_ptr->m_points[1].m_position);
    }
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    MTXCopy(mDoMtx_stack_c::get(), field_0x1628);
    if (
        strcmp(dComIfGp_getStartStageName(), "Ocean") == 0 &&
        dComIfGp_getStartStagePoint() == 1
    ) {
        u16 temp2 = l_HIO.m18;
        u16 reg = (u16)dComIfGs_getEventReg(0xAAFF) * 10;
        temp2 -= reg;
        field_0x1674 = fopMsgM_Timer_create(PROC_TIMER, 2, temp2, 3, 0, 221.0f, 439.0f, 32.0f, 419.0f, NULL);
        
        u32 temp3 = 0;
        temp3 |= 0x2000000;
        field_0x1678 = fopMsgM_create(PROC_MINIGAME_STARTER, NULL, NULL, &temp3, &temp3, NULL);

        dComIfGp_startMiniGame(1);
        dComIfGp_setMiniGameRupee(0);

        setAction(&daGoal_Flag_c::RaceStart);     
        field_0x1688 = 0;
    }

    cXyz temp5 = dComIfGp_getPlayer(0)->current.pos - field_0x1658[0];

    cXyz temp6 = field_0x1658[1] - field_0x1658[0];
    temp6.y = 0.0f;
    temp6 = temp6.normZP();

    cXyz temp7;
    temp7.x = temp6.z;
    temp7.y = 0.0f;
    temp7.z = -temp6.x;

    field_0x1680 = VECDotProduct(&temp7, &temp5);
    field_0x1684 = 0;

    for (int i = 0; i < 20; i++) {
        flag_move();
    }

    return cPhs_COMPLEATE_e;
}

/* 000029CC-00002AAC       .text daGoal_FlagDelete__FPv */
static BOOL daGoal_FlagDelete(void*) {
    /* Nonmatching */
}

/* 00002AAC-00002B14       .text daGoal_FlagExecute__FPv */
static BOOL daGoal_FlagExecute(void*) {
    /* Nonmatching */
}

/* 00002B14-00002CA4       .text daGoal_FlagDraw__FPv */
static BOOL daGoal_FlagDraw(void*) {
    /* Nonmatching */
}

/* 00002CA4-00002CAC       .text daGoal_FlagIsDelete__FPv */
static BOOL daGoal_FlagIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGoal_FlagMethodTable = {
    (process_method_func)daGoal_FlagCreate,
    (process_method_func)daGoal_FlagDelete,
    (process_method_func)daGoal_FlagExecute,
    (process_method_func)daGoal_FlagIsDelete,
    (process_method_func)daGoal_FlagDraw,
};

actor_process_profile_definition g_profile_Goal_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Goal_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGoal_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Goal_Flag,
    /* Actor SubMtd */ &daGoal_FlagMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
