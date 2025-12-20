/**
 * d_a_obj_ajav.cpp
 * Object - Stone wall blocking the entrance to Jabun's cave
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ajav.h"
#include "d/d_procname.h"
#include "d/d_priority.h"


static Vec l_daObjAjav_co_offset[3];
static Vec l_daObjAjav_offset[6];
static Vec l_daObjAjav_cyl_offset[6];
static cXyz l_daObjAjav_rock_pos_table[6];

const char daObjAjav::Act_c::M_arcname[] = "Ajav";

static dCcD_SrcSph l_daObjAjav_sph_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 32,
        /* SrcObjTg  SPrm    */ 0xF,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 280.0f,
    }},
};

static dCcD_SrcCyl l_daObjAjav_cyl_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0x20,
        /* SrcObjTg  SPrm    */ 0x09,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, -40.0f, 0.0f},
        /* Radius */ 780.0f,
        /* Height */ 3300.0f,
    }},
};

static dCcD_SrcCyl l_daObjAjav_hint_cyl_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0x20,
        /* SrcObjTg  SPrm    */ 0x09,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, -40.0f, 0.0f},
        /* Radius */ 780.0f,
        /* Height */ 3300.0f,
    }},
};

static Vec l_daObjAjav_hint_cyl_h_talbe = {3300.0f, 2360.0f, 1050.0f};

static Vec l_daObjAjav_cyl_r[] = {
    {629.0f, 294.8f, 491.0f},
    {216.0f, 563.0f,  85.3f}
};

static Vec l_daObjAjav_cyl_h[] = {
    {773.0f, 458.5f, 1100.5f},
    {1401.9f, 1133.0f,  451.9}
};

/* 000000EC-00000170       .text daObjAjav_make_splash__9daObjAjavF4cXyzf */
void daObjAjav::daObjAjav_make_splash(cXyz, float) {
    /* Nonmatching */
}

/* 000001AC-00000268       .text make_hamon__Q29daObjAjav6Part_cF4cXyzf */
void daObjAjav::Part_c::make_hamon(cXyz, float) {
    /* Nonmatching */
}

/* 00000268-0000026C       .text no_proc__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::no_proc(daObjAjav::Act_c*) {
    return;
}

/* 0000026C-000003A8       .text init_data__Q29daObjAjav6Part_cF4cXyz4cXyzP12dKy_tevstr_cP4cXyz */
void daObjAjav::Part_c::init_data(cXyz param_1, cXyz param_2, dKy_tevstr_c* i_tevstr, cXyz* param_4) {
    field_0x00 = param_2;
    field_0x0C = cXyz::Zero - field_0x00;
    field_0x3C = csXyz::Zero;
    field_0x18 = cXyz::Zero;
    field_0x24 = cXyz::Zero;
    field_0x7C = i_tevstr;
    field_0x6C = *param_4 + param_1;
    field_0x80 = &daObjAjav::Part_c::no_proc;
    field_0x8C = &daObjAjav::Part_c::draw_normal;
}

/* 000003A8-00000464       .text set_mdl_area__Q29daObjAjav6Part_cFPCciUl */
void daObjAjav::Part_c::set_mdl_area(const char*, int, unsigned long) {
    /* Nonmatching */
}

/* 00000464-0000050C       .text init_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz4cXyz */
void daObjAjav::Part_c::init_mtx(cXyz, csXyz, cXyz) {
    /* Nonmatching */
}

/* 0000050C-000005A8       .text set_flaw_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_flaw_mtx(cXyz, csXyz) {
    /* Nonmatching */
}

/* 000005A8-0000067C       .text set_fall_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_fall_mtx(cXyz, csXyz) {
    /* Nonmatching */
}

/* 0000067C-000006E4       .text fall_init__Q29daObjAjav6Part_cF4cXyz5csXyzsUs */
void daObjAjav::Part_c::fall_init(cXyz, csXyz, short, unsigned short) {
    /* Nonmatching */
}

/* 000006E4-0000076C       .text check_angle__9daObjAjavFPss */
void daObjAjav::check_angle(short*, short) {
    /* Nonmatching */
}

/* 0000076C-0000095C       .text fall_0__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::fall_0(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 0000095C-00000B8C       .text fall_1__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::fall_1(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00000B8C-00000C28       .text flaw__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::flaw(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00000C28-00000C6C       .text draw_normal__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_normal(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00000C6C-00000EA8       .text draw_flashing__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_flashing(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00000EA8-00000F10       .text draw_flashing_normal__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_flashing_normal(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00000F10-00001090       .text draw_shy__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_shy(daObjAjav::Act_c*) {
    /* Nonmatching */
}

/* 00001090-00001168       .text make_fall_rock__Q29daObjAjav6Part_cFi */
void daObjAjav::Part_c::make_fall_rock(int) {
    /* Nonmatching */
}

/* 00001168-00001188       .text solidHeapCB__Q29daObjAjav5Act_cFP10fopAc_ac_c */
BOOL daObjAjav::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjAjav::Act_c*)i_this)->create_heap();
}

/* 00001188-00001288       .text create_heap__Q29daObjAjav5Act_cFv */
BOOL daObjAjav::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00001288-0000166C       .text _create__Q29daObjAjav5Act_cFv */
cPhs_State daObjAjav::Act_c::_create() {
    cPhs_State rt = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjAjav::Act_c);

    field_0x290 = fopAcM_GetParam(this) & 0xFF;
    field_0xC23 = 0;
    BOOL is_event = dComIfGs_isEventBit(0xA02);
    if (is_event != FALSE && !dComIfGs_isSwitch(field_0x290, fopAcM_GetHomeRoomNo(this))) {
        rt = dComIfG_resLoad(&mPhs, M_arcname);
        if (rt == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, Act_c::solidHeapCB, 0)) {
                int i;
                for (i = 0; i < (int)ARRAY_SIZE(field_0x890); i++) {
                    field_0x890[i].init_data(current.pos, l_daObjAjav_offset[i], &tevStr, &l_daObjAjav_rock_pos_table[i]);
                }
                
                init_mtx();
                MTXCopy(field_0x890[5].field_0x78->getBaseTRMtx(), field_0x854);
                set_tex();
                
                field_0x29C.Init(0, 0xFF, this);
                field_0x2D8.SetStts(&field_0x29C);
                field_0x2D8.Set(l_daObjAjav_sph_data);
                
                field_0x410.Init(0, 0xFF, this);
                field_0x44C.SetStts(&field_0x410);
                field_0x44C.Set(l_daObjAjav_cyl_data);
                field_0x44C.SetC(current.pos);

                for (i = 0; i < 2; i++) {
                    field_0x57C[i].Init(0, 0xFF, this);
                    field_0x5F4[i].SetStts(&field_0x57C[i]);
                    field_0x5F4[i].Set(l_daObjAjav_hint_cyl_data);
                }
                set_co_offset();
                dComIfG_Bgsp()->Regist(field_0xC2C, this);
                field_0xC23 = 1;
                field_0xC24 = 0;
                field_0xC28 = 0;
            } else {
                rt = cPhs_ERROR_e;
            }
        }        
    }
    
    return rt;
}

/* 00001B3C-00001C08       .text _delete__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_delete() {
    /* Nonmatching */
}

/* 00001C08-00001CA8       .text init_mtx__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00001CA8-00001CE4       .text set_tex__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::set_tex() {
    /* Nonmatching */
}

/* 00001CE4-00001E3C       .text set_co_offset__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::set_co_offset() {
    /* Nonmatching */
}

/* 00001E3C-00001EA0       .text daObjAjav_limit_angle__9daObjAjavFPss */
void daObjAjav::daObjAjav_limit_angle(short*, short) {
    /* Nonmatching */
}

/* 00001EA0-00001F54       .text daObjAjav_get_rot_speed__9daObjAjavF4cXyz4cXyzs */
void daObjAjav::daObjAjav_get_rot_speed(cXyz, cXyz, short) {
    /* Nonmatching */
}

/* 00001F54-00001FE4       .text check_all_wait__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::check_all_wait() {
    /* Nonmatching */
}

/* 00001FE4-0000201C       .text check_end__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::check_end() {
    /* Nonmatching */
}

/* 0000201C-000020B0       .text to_broken__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::to_broken() {
    /* Nonmatching */
}

/* 000020B0-00002124       .text damage_part__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::damage_part() {
    /* Nonmatching */
}

/* 00002124-000021EC       .text make_shot_rock__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::make_shot_rock() {
    /* Nonmatching */
}

/* 000021EC-000022F0       .text make_hamon2__Q29daObjAjav5Act_cF4cXyzf */
void daObjAjav::Act_c::make_hamon2(cXyz, float) {
    /* Nonmatching */
}

/* 000022F0-000024A4       .text set_hamon__Q29daObjAjav5Act_cFf */
void daObjAjav::Act_c::set_hamon(float) {
    /* Nonmatching */
}

/* 000024A4-00002CF4       .text _execute__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_execute() {
    /* Nonmatching */
}

/* 00002D50-00002DCC       .text _draw__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjAjav {
namespace {
/* 00002DCC-00002DEC       .text Mthd_Create__Q29daObjAjav26@unnamed@d_a_obj_ajav_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAjav::Act_c*)i_this)->_create();
}

/* 00002DEC-00002E10       .text Mthd_Delete__Q29daObjAjav26@unnamed@d_a_obj_ajav_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAjav::Act_c*)i_this)->_delete();
}

/* 00002E10-00002E34       .text Mthd_Execute__Q29daObjAjav26@unnamed@d_a_obj_ajav_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAjav::Act_c*)i_this)->_execute();
}

/* 00002E34-00002E58       .text Mthd_Draw__Q29daObjAjav26@unnamed@d_a_obj_ajav_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAjav::Act_c*)i_this)->_draw();
}

/* 00002E58-00002E60       .text Mthd_IsDelete__Q29daObjAjav26@unnamed@d_a_obj_ajav_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAjav

actor_process_profile_definition g_profile_Obj_Ajav = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ajav,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAjav::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ajav,
    /* Actor SubMtd */ &daObjAjav::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
