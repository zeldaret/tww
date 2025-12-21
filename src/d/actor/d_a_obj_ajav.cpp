/**
 * d_a_obj_ajav.cpp
 * Object - Stone wall blocking the entrance to Jabun's cave
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ajav.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_ajav.h"

static cXyz l_daObjAjav_co_offset[3] = {
    cXyz(0.0f, 2550.0f, 200.0f),
    cXyz(250.0f, 1270.0f, 200.0f),
    cXyz(-290.0f, 740.0f, 200.0f)
};

static cXyz l_daObjAjav_offset[6] = {
    cXyz(0.0f, 3000.0f, 0.0f),
    cXyz(500.0f, 2400.0f, 0.0f),
    cXyz(-300.0f, 1900.0f, 0.0f),
    cXyz(500.0f, 1400.0f, 0.0f),
    cXyz(-550.0f, 650.0f, 0.0f),
    cXyz(250.0f, 400.0f, 0.0f)
};

static cXyz l_daObjAjav_cyl_offset[6] = {
    cXyz(33.0f, 2541.0f, 220.0f),
    cXyz(465.0f, 2083.0f, 220.0f),
    cXyz(-137.7f, 1297.0f, 220.0f),
    cXyz(530.0f, 511.0f, 220.0f),
    cXyz(-124.5f, 118.0f, 220.0f),
    cXyz(530.0f, 118.0f, 220.0f)
};

static cXyz l_daObjAjav_rock_pos_table[6] = {
    cXyz(-170.0f, 3087.0f, 222.0f),
    cXyz(563.0f, 2384.0f, 222.0f),
    cXyz(-371.0f, 1880.0f, 222.0f),
    cXyz(615.0f, 1391.0f, 222.0f),
    cXyz(-494.0f, 748.0f, 222.0f),
    cXyz(249.0f, 535.0f, 222.0f)
};

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

static const s32 l_daObjAjav_idx_table[6] = {
    4, 5 ,6 ,7, 8, 9
};

static const char* const l_daObjAjav_ev_name[] = {
    "ajav_destroy0",
    "ajav_destroy1",
    "ajav_uzu"
};

/* 000000EC-00000170       .text daObjAjav_make_splash__9daObjAjavF4cXyzf */
void daObjAjav::daObjAjav_make_splash(cXyz param_1, float param_2) {
    cXyz scale;

    param_2 /= 2000.0f;
    param_2 = 4.0f + param_2;

    scale.x = param_2;
    scale.y = 4.0f;
    scale.z = scale.x;
    dComIfGp_particle_set(dPa_name::ID_COMMON_003C, &param_1,  NULL, &scale);
}

/* 000001AC-00000268       .text make_hamon__Q29daObjAjav6Part_cF4cXyzf */
void daObjAjav::Part_c::make_hamon(cXyz param_1, float param_2) {
    cXyz temp;

    param_2 /= 2000.0f;
    temp.x = 2.0f + param_2;
    temp.y = temp.x;
    temp.z = temp.x;

    param_1.y += 10.0f;
    
    f32 temp3;
    if (fopAcM_getWaterY(&param_1, &temp3) == TRUE) {
        param_1.y = temp3;
    }

    dComIfGp_particle_set(dPa_name::ID_COMMON_003F, &param_1, NULL, &temp);
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
BOOL daObjAjav::Part_c::set_mdl_area(const char* param_1, int param_2, unsigned long param_3) {
    J3DModelData* mdl_data;
    BOOL res = FALSE;
    mdl_data = (J3DModelData*) dComIfG_getObjectRes(param_1, param_2);
    JUT_ASSERT(600, mdl_data != NULL);

    if (mdl_data != NULL) {
        field_0x78 = mDoExt_J3DModel__create(mdl_data, 0x80000, param_3);
        res = TRUE;
    }

    return res;
}

/* 00000464-0000050C       .text init_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz4cXyz */
void daObjAjav::Part_c::init_mtx(cXyz i_translation, csXyz i_zxyRotation, cXyz i_scale) {
    field_0x78->setBaseScale(i_scale);
    mDoMtx_stack_c::transS(i_translation);
    mDoMtx_stack_c::ZXYrotM(i_zxyRotation);
    field_0x78->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x78->calc();
}

/* 0000050C-000005A8       .text set_flaw_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_flaw_mtx(cXyz param_1, csXyz param_2) {
    mDoMtx_stack_c::transS(param_1);
    mDoMtx_stack_c::ZXYrotM(param_2);
    mDoMtx_stack_c::transM(field_0x18);
    field_0x78->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x78->calc();
}

/* 000005A8-0000067C       .text set_fall_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_fall_mtx(cXyz param_1, csXyz param_2) {
    /* Nonmatching */
    mDoMtx_stack_c::transS(param_1);
    mDoMtx_stack_c::ZXYrotM(param_2);
    mDoMtx_stack_c::transM(field_0x18);
    mDoMtx_stack_c::transM(field_0x00);
    mDoMtx_stack_c::ZXYrotM(field_0x3C);
    mDoMtx_stack_c::transM(field_0x0C);
    field_0x78->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x78->calc();  
}

/* 0000067C-000006E4       .text fall_init__Q29daObjAjav6Part_cF4cXyz5csXyzsUs */
void daObjAjav::Part_c::fall_init(cXyz param_1, csXyz param_2, short param_3, unsigned short param_4) {
    field_0x24 = param_1;
    field_0x42 = param_2;

    field_0x54[2] = param_3;
    field_0x54[0] = param_4;
    field_0x54[1] = 0;

    field_0x5A = 0;
    field_0x80 = &Part_c::fall_0;
}

/* 000006E4-0000076C       .text check_angle__9daObjAjavFPss */
BOOL daObjAjav::check_angle(short* param_1, short param_2) {
    BOOL rt = FALSE;
    if (abs(*param_1) >= param_2) {
        s16 temp = abs(*param_1) - param_2;
        if (*param_1 > 0) {
            *param_1 = param_2 - temp;
        } else {
            *param_1 = -(param_2 - temp);
        }
        rt = TRUE;
    }
    return rt;
}

/* 0000076C-0000095C       .text fall_0__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::fall_0(daObjAjav::Act_c* i_actor) {
    /* Nonmatching */
    // wtf is going on in this function?
    field_0x3C += field_0x42;
    if (check_angle(&field_0x3C.x, *(s16*)&field_0x54[2])) {
        field_0x42.x *= -1;
    }
    if (check_angle(&field_0x3C.y, *(s16*)&field_0x54[2])) {
        field_0x42.y *= -1;
    }

    field_0x18 += field_0x24;

    f32 rnd = cM_rnd();
    rnd = 0.2f * rnd;
    rnd = 0.8f + rnd;
    field_0x24.z = field_0x24.z * rnd;
    field_0x54[1]++;
    if (field_0x54[1] == field_0x54[0]) {
        cXyz temp = field_0x24 * 0.4f;
        temp.y = 5.0f;
        field_0x24 = temp;

        field_0x80 = &Part_c::fall_1;

        field_0x54[1] = 0;

        field_0x42 = field_0x42 * 0.3f;

        s32 rnd2 = cM_rnd() * 511.0f;
        s32 rnd3 = cM_rnd() * -2.0f;
        field_0x42.z = rnd3 * rnd2;
    }
    set_fall_mtx(i_actor->current.pos, i_actor->shape_angle);
}

/* 0000095C-00000B8C       .text fall_1__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::fall_1(daObjAjav::Act_c* i_actor) {
    /* Nonmatching, .rodata, .data */
    field_0x18 += field_0x24;
    field_0x18.y -= field_0x54[1] * 2.0f;
    field_0x3C += field_0x42;
  

    field_0x54[1]++; 
    
    if (!field_0x5A) {
        if (field_0x18.y <= (field_0x0C.y - 100.0f)) {
            cXyz temp2 = (i_actor->current.pos + field_0x18) + field_0x00;
            temp2.y = 0.0f;
            daObjAjav_make_splash(temp2, field_0x00.y);
            field_0x5A = true;
            make_hamon(temp2, field_0x00.y);
            field_0x48 = temp2;
            mDoAud_seStart(JA_SE_OBJ_JB_STONE_FALL, &field_0x48, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_actor)));
        }
    }

    if (field_0x18.y <= (field_0x0C.y - 1000.0f)) {
        field_0x80 = &Part_c::no_proc;
        field_0x8C = &Part_c::no_proc;
    }
    set_fall_mtx(i_actor->current.pos, i_actor->shape_angle);
}

/* 00000B8C-00000C28       .text flaw__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::flaw(daObjAjav::Act_c* i_actor) {
    /* Nonmatching */
    field_0x18 += field_0x30;
    set_flaw_mtx(i_actor->current.pos, i_actor->shape_angle);
    field_0x80 = &Part_c::no_proc;
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
void daObjAjav::Part_c::make_fall_rock(int param_1) {
    JPABaseEmitter* particle_emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8427, &field_0x6C);
    if (particle_emitter && field_0x7C) {
        if (param_1 != 0) {
            particle_emitter->setRate(20.0f);
        }
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &field_0x6C, field_0x7C);
        particle_emitter->setGlobalPrmColor(field_0x7C->mColorK0.r, field_0x7C->mColorK0.g, field_0x7C->mColorK0.b);
    }    
}

const char daObjAjav::Act_c::M_arcname[] = "Ajav";

/* 00001168-00001188       .text solidHeapCB__Q29daObjAjav5Act_cFP10fopAc_ac_c */
BOOL daObjAjav::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjAjav::Act_c*)i_this)->create_heap();
}

/* 00001188-00001288       .text create_heap__Q29daObjAjav5Act_cFv */
BOOL daObjAjav::Act_c::create_heap() {
    int i;
    BOOL res = field_0x890[0].set_mdl_area(M_arcname, l_daObjAjav_idx_table[0], 0x11000002);

    if (res != FALSE) {
        for (i = 1; i < ARRAY_SSIZE(field_0x890); i++) {
            res = field_0x890[i].set_mdl_area(M_arcname, l_daObjAjav_idx_table[i], 0x15021202);
            if (res == FALSE) break;
        }
    }

    if (res != FALSE) {
        cBgD_t* cbgd_res = (cBgD_t*)dComIfG_getObjectRes(M_arcname, AJAV_DZB_AJAV);
        field_0xC2C = dBgW_NewSet(cbgd_res, cBgW::MOVE_BG_e, &field_0x854);
        if (field_0xC2C == NULL) {
            res = FALSE;
        } 
    }

    return res;
}

/* 00001288-0000166C       .text _create__Q29daObjAjav5Act_cFv */
cPhs_State daObjAjav::Act_c::_create() {
    cPhs_State rt = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjAjav::Act_c);

    field_0x290 = fopAcM_GetParam(this) & 0xFF;
    field_0xC23 = 0;
    if (check_ev() && !check_sw()) {
        rt = dComIfG_resLoad(&mPhs, M_arcname);
        if (rt == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, Act_c::solidHeapCB, 0)) {
                int i;
                for (i = 0; i < ARRAY_SSIZE(field_0x890); i++) {
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

                for (i = 0; i < ARRAY_SSIZE(field_0x57C); i++) {
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
    if (heap != NULL && field_0xC2C != NULL) {
        if (field_0xC2C->ChkUsed()) {
            dComIfG_Bgsp()->Release(field_0xC2C);
            field_0xC2C = NULL;
        }
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    for (int i = 0; i < ARRAY_SSIZE(field_0x890); i++) {
        mDoAud_seDeleteObject(&field_0x890[i].field_0x48);
    }
    return TRUE;
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
void daObjAjav::daObjAjav_limit_angle(short* param_1, short param_2) {
    if (abs(*param_1) > param_2) {
        if (*param_1 > 0) {
            *param_1 = param_2;
        } else {
            *param_1 = -param_2;
        }
    }
}

/* 00001EA0-00001F54       .text daObjAjav_get_rot_speed__9daObjAjavF4cXyz4cXyzs */
csXyz daObjAjav::daObjAjav_get_rot_speed(cXyz param_1, cXyz param_2, short param_3) {
    cXyz temp = param_1 - param_2;

    csXyz temp2 = csXyz::Zero;
    temp2.x = temp.y;
    temp2.y = temp.x;

    daObjAjav_limit_angle(&temp2.x, param_3);
    daObjAjav_limit_angle(&temp2.y, param_3);
    
    return temp2;
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
