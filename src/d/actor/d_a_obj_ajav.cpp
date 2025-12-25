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
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e | dCcG_TgSPrm_ShieldFrontRange_e,
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
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_ShieldFrontRange_e,
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

static f32 l_daObjAjav_hint_cyl_h_talbe[] = {3300.0f, 2360.0f, 1050.0f};

static f32 l_daObjAjav_cyl_r[6] = {
    629.0f, 294.8f, 491.0f,
    216.0f, 563.0f,  85.3f
};

static f32 l_daObjAjav_cyl_h[6] = {
    773.0f, 458.5f, 1100.5f,
    1401.9f, 1133.0f,  451.9
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
void daObjAjav::daObjAjav_make_splash(cXyz splash_pos, float param_2) {
    cXyz scale;

    param_2 /= 2000.0f;
    param_2 = 4.0f + param_2;

    scale.x = param_2;
    scale.y = 4.0f;
    scale.z = scale.x;
    dComIfGp_particle_set(dPa_name::ID_COMMON_003C, &splash_pos,  NULL, &scale);
}

/* 000001AC-00000268       .text make_hamon__Q29daObjAjav6Part_cF4cXyzf */
void daObjAjav::Part_c::make_hamon(cXyz hamon_pos, float param_2) {
    cXyz temp;

    param_2 /= 2000.0f;
    temp.x = 2.0f + param_2;
    temp.y = temp.x;
    temp.z = temp.x;

    hamon_pos.y += 10.0f;
    
    f32 temp3;
    if (fopAcM_getWaterY(&hamon_pos, &temp3) == TRUE) {
        hamon_pos.y = temp3;
    }

    dComIfGp_particle_set(dPa_name::ID_COMMON_003F, &hamon_pos, NULL, &temp);
}

/* 00000268-0000026C       .text no_proc__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::no_proc(daObjAjav::Act_c*) {
    return;
}

/* 0000026C-000003A8       .text init_data__Q29daObjAjav6Part_cF4cXyz4cXyzP12dKy_tevstr_cP4cXyz */
void daObjAjav::Part_c::init_data(cXyz actor_pos, cXyz param_2, dKy_tevstr_c* i_tevstr, cXyz* rock_pos) {
    mFallFromPos = param_2;
    field_0x0C = cXyz::Zero - mFallFromPos;
    field_0x3C = csXyz::Zero;
    field_0x18 = cXyz::Zero;
    field_0x24 = cXyz::Zero;
    mpTevStr = i_tevstr;
    m6C = *rock_pos + actor_pos;
#if VERSION > VERSION_DEMO
    setExeProc(&Part_c::no_proc);
    setDrawProc(&Part_c::draw_normal);
#else
    mExeProc = &Part_c::no_proc;
    mDrawProc = &Part_c::draw_normal;
#endif
}

/* 000003A8-00000464       .text set_mdl_area__Q29daObjAjav6Part_cFPCciUl */
BOOL daObjAjav::Part_c::set_mdl_area(const char* param_1, int param_2, unsigned long param_3) {
    J3DModelData* mdl_data;
    BOOL res = FALSE;
    mdl_data = (J3DModelData*) dComIfG_getObjectRes(param_1, param_2);
    JUT_ASSERT(600, mdl_data != NULL);

    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, param_3);
        res = TRUE;
    }

    return res;
}

/* 00000464-0000050C       .text init_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz4cXyz */
void daObjAjav::Part_c::init_mtx(cXyz i_translation, csXyz i_zxyRotation, cXyz i_scale) {
    mpModel->setBaseScale(i_scale);
    mDoMtx_stack_c::transS(i_translation);
    mDoMtx_stack_c::ZXYrotM(i_zxyRotation);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 0000050C-000005A8       .text set_flaw_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_flaw_mtx(cXyz param_1, csXyz param_2) {
    mDoMtx_stack_c::transS(param_1);
    mDoMtx_stack_c::ZXYrotM(param_2);
    mDoMtx_stack_c::transM(field_0x18);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 000005A8-0000067C       .text set_fall_mtx__Q29daObjAjav6Part_cF4cXyz5csXyz */
void daObjAjav::Part_c::set_fall_mtx(cXyz i_pos, csXyz i_angle) {
    mDoMtx_stack_c::transS(i_pos);
    mDoMtx_stack_c::ZXYrotM(i_angle);
    mDoMtx_stack_c::transM(field_0x18);
    mDoMtx_stack_c::transM(mFallFromPos);
    mDoMtx_stack_c::ZXYrotM(field_0x3C);
    mDoMtx_stack_c::transM(field_0x0C);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();  
}

/* 0000067C-000006E4       .text fall_init__Q29daObjAjav6Part_cF4cXyz5csXyzsUs */
void daObjAjav::Part_c::fall_init(cXyz param_1, csXyz param_2, short param_3, unsigned short param_4) {
    field_0x24 = param_1;
    field_0x42 = param_2;

    field_0x58 = param_3;
    field_0x54 = param_4;
    field_0x56 = 0;

    field_0x5A = 0;
    setExeProc(&Part_c::fall_0);
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
    cXyz temp(0.0f, -10.0f, 0.0f);
    
    field_0x3C += field_0x42;

    if (check_angle(&field_0x3C.x, field_0x58)) {
        field_0x42.x *= -1;
    }

    if (check_angle(&field_0x3C.y, field_0x58)) {
        field_0x42.y *= -1;
    }

    field_0x18 += field_0x24;

    field_0x24.z *= 0.8f + (0.2f * cM_rnd());
    field_0x56++;
    if (field_0x56 == field_0x54) {
        temp = field_0x24 * 0.4f;
        temp.y = 5.0f;
        field_0x24 = temp;

        setExeProc(&Part_c::fall_1);

        field_0x56 = 0;
        
        field_0x42 = csXyz(field_0x42 * 0.3f);
        field_0x42.z = static_cast<int>(cM_rnd() * -2.0f) * s16(cM_rnd() * 511.0f);
    }
    set_fall_mtx(i_actor->current.pos, i_actor->shape_angle);
}

/* 0000095C-00000B8C       .text fall_1__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::fall_1(daObjAjav::Act_c* i_actor) {
    field_0x18 += field_0x24;
    field_0x18.y -= field_0x56 * 2.0f;
    field_0x3C += field_0x42;
  

    field_0x56++; 
    
    if (!field_0x5A) {
        if (field_0x18.y <= (field_0x0C.y - 100.0f)) {
            cXyz pos_in_world = (i_actor->current.pos + field_0x18) + mFallFromPos;
            pos_in_world.y = 0.0f;
            daObjAjav_make_splash(pos_in_world, mFallFromPos.y);
            field_0x5A = true;
            make_hamon(pos_in_world, mFallFromPos.y);
            mSePos = pos_in_world;
            mDoAud_seStart(JA_SE_OBJ_JB_STONE_FALL, &mSePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_actor)));
        }
    }

    if (field_0x18.y <= (field_0x0C.y - 1000.0f)) {
        setExeProc(&Part_c::no_proc);
        setDrawProc(&Part_c::no_proc);
    }
    set_fall_mtx(i_actor->current.pos, i_actor->shape_angle);
}

/* 00000B8C-00000C28       .text flaw__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::flaw(daObjAjav::Act_c* i_actor) {
    field_0x18 += mFlawPos;
    set_flaw_mtx(i_actor->current.pos, i_actor->shape_angle);
#if VERSION > VERSION_DEMO
    setExeProc(&Part_c::no_proc);
#else
    mExeProc = &Part_c::no_proc;
#endif
}

/* 00000C28-00000C6C       .text draw_normal__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_normal(daObjAjav::Act_c*) {
    g_env_light.setLightTevColorType(mpModel, mpTevStr);
    mDoExt_modelUpdateDL(mpModel);
}

/* 00000C6C-00000EA8       .text draw_flashing__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_flashing(daObjAjav::Act_c*) {
    u8 r, g, b;
    if (mpTevStr) {
        g_env_light.setLightTevColorType(mpModel, mpTevStr);
        J3DMaterial* mesh = mpModel->getModelData()->getJointNodePointer(0)->getMesh();
        if (mesh) {
            s16 theta = (s16)(((f32)field_0x56 / field_0x54) * 20479.0f) + 0x3000;
            f32 abs_sin_theta = std::abs(JMASSin(theta));

            r = mesh->getTevKColor(1)->mColor.r;
            g = mesh->getTevKColor(1)->mColor.g;
            b = mesh->getTevKColor(1)->mColor.b;

            mesh->getTevKColor(1)->mColor.r = abs_sin_theta * 85.0f;
            mesh->getTevKColor(1)->mColor.g = abs_sin_theta * 11.0f;
            mesh->getTevKColor(1)->mColor.b = abs_sin_theta *  9.0f;
        }
        mDoExt_modelUpdateDL(mpModel);
        if (mesh) {
            mesh->getTevKColor(1)->mColor.r = r;
            mesh->getTevKColor(1)->mColor.g = g;
            mesh->getTevKColor(1)->mColor.b = b;
        }
    }
}

/* 00000EA8-00000F10       .text draw_flashing_normal__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_flashing_normal(daObjAjav::Act_c* i_actor) {
    (void)&daObjAjav::Part_c::draw_shy; // fakematch?
    draw_flashing(i_actor);
    field_0x56++;
    if (field_0x56 == field_0x54) {
        setDrawProc(&Part_c::draw_normal);
    }
}

/* 00000F10-00001090       .text draw_shy__Q29daObjAjav6Part_cFPQ29daObjAjav5Act_c */
void daObjAjav::Part_c::draw_shy(daObjAjav::Act_c*) {
    u8 r, g, b;
    if (mpTevStr) {
        g_env_light.setLightTevColorType(mpModel, mpTevStr);
        J3DMaterial* mesh = mpModel->getModelData()->getJointNodePointer(0)->getMesh();
        if (mesh) {
            r = mesh->getTevKColor(1)->mColor.r;
            g = mesh->getTevKColor(1)->mColor.g;
            b = mesh->getTevKColor(1)->mColor.b;

            mesh->getTevKColor(1)->mColor.r = 0x55;
            mesh->getTevKColor(1)->mColor.g = 0x0B;
            mesh->getTevKColor(1)->mColor.b = 0x09;
        }
        mDoExt_modelUpdateDL(mpModel);
        if (mesh) {
            mesh->getTevKColor(1)->mColor.r = r;
            mesh->getTevKColor(1)->mColor.g = g;
            mesh->getTevKColor(1)->mColor.b = b;
        }
    }
}

/* 00001090-00001168       .text make_fall_rock__Q29daObjAjav6Part_cFi */
void daObjAjav::Part_c::make_fall_rock(int param_1) {
    JPABaseEmitter* particle_emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8427, &m6C);
    if (particle_emitter && mpTevStr) {
        if (param_1 != 0) {
            particle_emitter->setRate(20.0f);
        }
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &m6C, mpTevStr);
        particle_emitter->setGlobalPrmColor(mpTevStr->mColorK0.r, mpTevStr->mColorK0.g, mpTevStr->mColorK0.b);
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
    BOOL res = mStoneParts[0].set_mdl_area(M_arcname, l_daObjAjav_idx_table[0], 0x11000002);

    if (res != FALSE) {
        for (i = 1; i < ARRAY_SSIZE(mStoneParts); i++) {
            res = mStoneParts[i].set_mdl_area(M_arcname, l_daObjAjav_idx_table[i], 0x15021202);
            if (res == FALSE) break;
        }
    }

    if (res != FALSE) {
        cBgD_t* cbgd_res = (cBgD_t*)dComIfG_getObjectRes(M_arcname, AJAV_DZB_AJAV);
        mpBgW = dBgW_NewSet(cbgd_res, cBgW::MOVE_BG_e, &mMtx);
        if (mpBgW == NULL) {
            res = FALSE;
        } 
    }

    return res;
}

/* 00001288-0000166C       .text _create__Q29daObjAjav5Act_cFv */
cPhs_State daObjAjav::Act_c::_create() {
    cPhs_State rt = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjAjav::Act_c);

    mSwNo = fopAcM_GetParam(this) & 0xFF;
    mbResLoaded = false;
    if (check_ev() && !check_sw(mSwNo)) {
        rt = dComIfG_resLoad(&mPhs, M_arcname);
        if (rt == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, Act_c::solidHeapCB, 0)) {
                int i;
                for (i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
                    mStoneParts[i].init_data(current.pos, l_daObjAjav_offset[i], &tevStr, &l_daObjAjav_rock_pos_table[i]);
                }
                
                init_mtx();
                MTXCopy(mStoneParts[5].mpModel->getBaseTRMtx(), mMtx);
                set_tex();
                
                mSphStts.Init(0, 0xFF, this);
                mSph.SetStts(&mSphStts);
                mSph.Set(l_daObjAjav_sph_data);
                
                mCylStts.Init(0, 0xFF, this);
                mCyl.SetStts(&mCylStts);
                mCyl.Set(l_daObjAjav_cyl_data);
                mCyl.SetC(current.pos);

                for (i = 0; i < ARRAY_SSIZE(mHintCylStts); i++) {
                    mHintCylStts[i].Init(0, 0xFF, this);
                    mHintCyls[i].SetStts(&mHintCylStts[i]);
                    mHintCyls[i].Set(l_daObjAjav_hint_cyl_data);
                }

                set_co_offset();
                dComIfG_Bgsp()->Regist(mpBgW, this);

                mbResLoaded = true;
                mActionIdx = 0;
                mHintCylHits = 0;
            } else {
                rt = cPhs_ERROR_e;
            }
        }        
    }
    
    return rt;
}

/* 00001B3C-00001C08       .text _delete__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_delete() {
    if (DEMO_SELECT(true, heap != NULL) && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
#if VERSION > VERSION_DEMO
            mpBgW = NULL;
#endif
        }
    }

    if (DEMO_SELECT(mbResLoaded == 1, true)) {
        dComIfG_resDelete(&mPhs, M_arcname);
    }

    for (int i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        mDoAud_seDeleteObject(&mStoneParts[i].mSePos);
    }
    return TRUE;
}

/* 00001C08-00001CA8       .text init_mtx__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::init_mtx() {
    for (int i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        mStoneParts[i].init_mtx(current.pos, shape_angle, scale);
    }
}

/* 00001CA8-00001CE4       .text set_tex__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::set_tex() {
    J3DModelData* model_data = mStoneParts[0].mpModel->getModelData();
    J3DTexture* model_texture = model_data->getTexture();
    JUTNameTab* name_table = model_data->getTextureName();

    for (int i = 1; i < ARRAY_SSIZE(mStoneParts); i++) {
        J3DModelData* model_data_i = mStoneParts[i].mpModel->getModelData(); 
        model_data_i->setTexture(model_texture);
        model_data_i->setTextureName(name_table);
    }
}

/* 00001CE4-00001E3C       .text set_co_offset__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::set_co_offset() {
    s32 i, j;
    JUT_ASSERT(DEMO_SELECT(1173, 1172), (M_status >= 0) && (M_status < STATUS_MAX - 1));
    mSphCoOffset = l_daObjAjav_co_offset[M_status];
    mSph.SetC(current.pos + mSphCoOffset);
    mCyl.SetH(l_daObjAjav_hint_cyl_h_talbe[M_status]);

    for (i = get_stone_row(), j = 0; j < ARRAY_SSIZE(mHintCyls); i++, j++) {
        mHintCyls[j].SetC(current.pos + l_daObjAjav_cyl_offset[i]);
        mHintCyls[j].SetR(l_daObjAjav_cyl_r[i]);
        mHintCyls[j].SetH(l_daObjAjav_cyl_h[i]);
    }
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
BOOL daObjAjav::Act_c::check_all_wait() {
    int i;
    BOOL res = TRUE;
    for (i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        if (!mStoneParts[i].checkExeProc(&Part_c::no_proc)) {
            res = FALSE;
            break;
        }
    }
    return res;
}

/* 00001FE4-0000201C       .text check_end__Q29daObjAjav5Act_cFv */
BOOL daObjAjav::Act_c::check_end() {
    BOOL rt = FALSE;
    if (M_status == (STATUS_MAX - 1)) {
        rt = check_all_wait();
    }
    return rt;
}

/* 0000201C-000020B0       .text to_broken__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::to_broken() {
    mEventIdx = dComIfGp_evmng_getEventIdx(l_daObjAjav_ev_name[M_status]);
    mActionIdx = 1;
    if (!eventInfo.checkCommandDemoAccrpt()) {
        fopAcM_orderOtherEventId(this, mEventIdx);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
}

/* 000020B0-00002124       .text damage_part__Q29daObjAjav5Act_cFv */
BOOL daObjAjav::Act_c::damage_part() {
    BOOL rt = FALSE;
    if (M_status < STATUS_MAX - 1 && mSph.ChkTgHit()) {
        to_broken();
        mSph.ClrTgHit();
        rt = TRUE;
    }
    return rt;
}

/* 00002124-000021EC       .text make_shot_rock__Q29daObjAjav5Act_cFv */
void daObjAjav::Act_c::make_shot_rock() {
    cXyz sph_center = mSph.GetC();
    JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8426, &sph_center);
    if (emitter) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &sph_center, &tevStr);
        emitter->setGlobalPrmColor(
            tevStr.mColorK0.r,
            tevStr.mColorK0.g,
            tevStr.mColorK0.b
        );
    }
}

/* 000021EC-000022F0       .text make_hamon2__Q29daObjAjav5Act_cF4cXyzf */
void daObjAjav::Act_c::make_hamon2(cXyz param_1, float param_2) {
    cXyz temp;

    param_2 /= 3000.0f;
    temp.x = 1.0f + param_2;
    temp.y = temp.x;
    temp.z = temp.x;

    param_1.y += 10.0f;
    
    f32 temp3;
    if (fopAcM_getWaterY(&param_1, &temp3) == TRUE) {
        param_1.y = temp3;
    }

    JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8454, &param_1, NULL, &temp);

    if (emitter) {
        g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
        emitter->setGlobalPrmColor(
            tevStr.mColorC0.r,
            tevStr.mColorC0.g,
            tevStr.mColorC0.b
        );
    }
}

/* 000022F0-000024A4       .text set_hamon__Q29daObjAjav5Act_cFf */
void daObjAjav::Act_c::set_hamon(float param_1) {
    cXyz current_pos;
    cXyz base_z;
    cXyz base_x;
    cXyz temp_base_x;

    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &base_z);
    base_z *= 1300.0f;

    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseX, &base_x);

    for (int i = 0; i < 2; i++) {
        current_pos = current.pos;

        temp_base_x = base_x;
        temp_base_x *= (i * -2.0f + 1.0f) * 400.0f;
        
        current_pos += base_z;
        current_pos += temp_base_x;

        make_hamon2(current_pos, param_1);
    }
}

/* 000024A4-00002CF4       .text _execute__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_execute() {
    static cXyz flaw_pos[] = {
        cXyz(0.0f, 0.0f, 0.0f),
        cXyz(0.0f, 0.0f, 0.0f),
        cXyz(0.0f, 40.0f, 0.0f),
        cXyz(30.0f, 30.0f, 0.0f),
        cXyz(-20.0f, 0.0f, 0.0f),
        cXyz(20.0f, 0.0f, 0.0f)
    };    
    
    cXyz temp(12.0f, -10.0f, 55.0f);
    bool stone_broken = false;

    // this bool is checked for falsehood once, set to true and then never read from again
    bool useless_bool = false; 
    
    csXyz temp4;
    int i, cond;

    for (i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        mStoneParts[i].set_se_pos(current.pos);
    }

    switch (mActionIdx) {
    case 0:
        if (!damage_part()) {
            for (i = 0; i < 2; i++) {
                mHintCylStts[i].Move();
                if (mHintCyls[i].ChkTgHit()) {
                    if (!useless_bool) {
                        mHintCylHits++;
                        if (mHintCylHits >= STATUS_MAX - 1) {
                            to_broken();
                            mHintCylHits = 0;
                            stone_broken = true;
                        }
                        useless_bool = true;
                    }
                    mHintCyls[i].ClrTgHit();
                }
            }
            if (stone_broken != true) {
                mCylStts.Move();
                if (mCyl.ChkTgHit()) {
                    cond = get_stone_row();
                    for (int j = get_stone_row(); j < (cond + 2); j++) {
                        mStoneParts[j].make_fall_rock(1);
                        mStoneParts[j].field_0x56 = 0;
                        mStoneParts[j].field_0x54 = 30;
                        mStoneParts[j].setDrawProc(&Part_c::draw_flashing_normal);
                    }
                    mCyl.ClrTgHit(); 
                }
            }
        }
        break;
    case 1:
        if (eventInfo.checkCommandDemoAccrpt()) {
            cond = get_stone_row();
            for (i = get_stone_row(); i < (cond + 2); i++) {
                temp.x = 12.0f;
                if ((i & 1) == 0) {
                    temp.x *= -1.0f;
                }
                temp4 = daObjAjav_get_rot_speed(mSphCoOffset, mStoneParts[i].mFallFromPos, 0x1FF);
                mStoneParts[i].fall_init(temp, temp4, 0x1FF, (s16)(cM_rnd() * 9.0f) + 7);
                mDoAud_seStart(JA_SE_OBJ_JB_STONE_BRK, &mStoneParts[i].mSePos,0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mStoneParts[i].setDrawProc(&Part_c::draw_normal);
                mStoneParts[i].make_fall_rock(0);
            }
            
            make_shot_rock();

            int idx = get_stone_row();
            set_hamon(mStoneParts[idx].field_0x18.y);

            M_status++;
            if (M_status < STATUS_MAX - 1) {
                cond = get_stone_row();
                for (i = get_stone_row(); i < (cond + 2); i++) {
                    mStoneParts[i].mFlawPos = flaw_pos[i];
                    mStoneParts[i].setExeProc(&Part_c::flaw); 
                }
                set_co_offset();
                mActionIdx = 2;
            } else {
                mActionIdx = 3;
                mCutsceneEndDelay = 60;
            }
        } else {
            fopAcM_orderOtherEventId(this, mEventIdx);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 2:
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            dComIfGp_event_reset();
            if (M_status < STATUS_MAX - 1) {
                mActionIdx = 0;
            } else {
                mActionIdx = 4;
            }
        }
        break;
    case 3:
        if (check_end()) {
            if (mCutsceneEndDelay == 0) {
                dComIfGp_evmng_cutEnd(dComIfGp_evmng_getMyStaffId("Ajav"));
                if (DEMO_SELECT(true, heap != NULL) && mpBgW != NULL) {
                    if (mpBgW->ChkUsed()) {
                        dComIfG_Bgsp()->Release(mpBgW);
#if VERSION > VERSION_DEMO
                        mpBgW = NULL;
#endif
                    }
                }
                on_sw(mSwNo);
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                mDoAud_subBgmStop();
                mActionIdx = 2;
                M_status++;
            } else {
                mCutsceneEndDelay--;
            }
        }
        break;
    case 4:
        break;
    default:
        mActionIdx = 0;
        break;
    }

    if (M_status < STATUS_MAX - 1) {
        dComIfG_Ccsp()->Set(&mSph);
        dComIfG_Ccsp()->Set(&mCyl);
        for (i = 0; i < 2; i++) {
            dComIfG_Ccsp()->Set(&mHintCyls[i]);
        }
    }

    for (i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        mStoneParts[i].execute(this);
    }

    if (mpBgW && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }

    return true;
}

/* 00002CF4-00002D50       .text set_se_pos__Q29daObjAjav6Part_cF4cXyz */
void daObjAjav::Part_c::set_se_pos(cXyz i_pos) {
    mSePos = i_pos + mFallFromPos;
    mSePos += field_0x18;
}

/* 00002D50-00002DCC       .text _draw__Q29daObjAjav5Act_cFv */
bool daObjAjav::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    for (int i = 0; i < ARRAY_SSIZE(mStoneParts); i++) {
        mStoneParts[i].draw(this);
    }
    return true;
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
