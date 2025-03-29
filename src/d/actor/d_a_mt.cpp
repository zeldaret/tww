/**
 * d_a_mt.cpp
 * Enemy - Magtail
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mt.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_player.h"

static int mt_count;
static int mt_all_count;
static int mt_fight_count;

static int btk_data[8] = {
    0,0,0,0,0,0,0,0
};
static int brk_data[8] = {
    0,0,0,0,0,0,0,0
};
static s16 mt_tex_anm_idx[8] = {
    0,0,0,0,0,0,0,0
};

static int scale_data[8] = {
    0,0,0,0,0,0,0,0
};

daMt_HIO_c l_HIO;

/* 000000EC-000001E8       .text __ct__10daMt_HIO_cFv */
daMt_HIO_c::daMt_HIO_c() {
    /* Nonmatching */
}

/* 00000230-000002D8       .text anm_init__FP8mt_classifUcfi */
void anm_init(mt_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000002D8-00000350       .text mt_a_d_sub__FPvPv */
void* mt_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000350-00000390       .text mt_check__FP8mt_class */
void mt_check(mt_class* i_this) {
    mt_fight_count = 0;
    mt_all_count = 0;
    fpcM_Search(&mt_a_d_sub, i_this);
}

/* 00000390-00000478       .text mt_bg_check__FP8mt_class */
void mt_bg_check(mt_class*) {
    /* Nonmatching */
}

/* 00000478-0000053C       .text tex_anm_set__FP8mt_classUs */
void tex_anm_set(mt_class*, unsigned short) {
    /* Nonmatching */
}

/* 0000053C-000005EC       .text mt_eye_tex_anm__FP8mt_class */
void mt_eye_tex_anm(mt_class*) {
    /* Nonmatching */
}

/* 000005EC-00000720       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000075C-0000098C       .text nodeCallBack_body__FP7J3DNodei */
static BOOL nodeCallBack_body(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000098C-00000B28       .text nodeCallBack_tail__FP7J3DNodei */
static BOOL nodeCallBack_tail(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000B28-0000171C       .text body_control2__FP8mt_class */
void body_control2(mt_class*) {
    /* Nonmatching */
}

/* 00001B54-00001E44       .text wall_check_sub__FP8mt_classP4cXyzP4cXyz */
void wall_check_sub(mt_class*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00001E44-00001F10       .text body_wall_check__FP8mt_class */
void body_wall_check(mt_class*) {
    /* Nonmatching */
}

/* 00001F10-000022D8       .text body_control1__FP8mt_class */
void body_control1(mt_class*) {
    /* Nonmatching */
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class*) {
    /* Nonmatching */
}

/* 000028BC-00002AB0       .text body_control4__FP8mt_class */
void body_control4(mt_class*) {
    /* Nonmatching */
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class*) {
    /* Nonmatching */
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class*) {
    /* Nonmatching */
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class*) {
    /* Nonmatching */
}

/* 00003360-0000361C       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class*) {
    /* Nonmatching */
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class*) {
    /* Nonmatching */
}

/* 000037B0-000042C4       .text mt_move__FP8mt_class */
void mt_move(mt_class*) {
    /* Nonmatching */
}

/* 000042C4-00005088       .text mt_fight__FP8mt_class */
void mt_fight(mt_class* i_this) {
    float fVar1;
    short sVar9;
    f32 fVar11;
    cXyz local_80;
    short local_74[6];
    cXyz local_68;
    cXyz local_5c;
    u64 local_50;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->m455) {
        case 0:
            mt_check(i_this);
            if (mt_fight_count < 2) {
                local_74[0] = 0;
                local_74[1] = 0;
                local_74[2] = 0;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 2) {
                local_74[0] = 0x2000;
                local_74[1] = 0x2000;
                local_74[2] = 0;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 3) {
                local_74[0] = 0;
                local_74[1] = 0xD000;
                local_74[2] = 0x3000;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 4) {
                local_74[0] = 0x2000;
                local_74[1] = 0xE000;
                local_74[2] = 0x5000;
                local_74[3] = 0xB000;
                local_74[4] = 0;
            } else {
                local_74[0] = 0;
                local_74[1] = 0x3000;
                local_74[2] = 0xD000;
                local_74[3] = 0x6000;
                local_74[4] = 0xA000;
            }

            if (dComIfGp_getAttention().Lockon() && i_this == dComIfGp_getAttention().LockonTarget(0)) {
                mt_count = 0;
            } else {
                mt_count++;
            }
            if (mt_count >= 5) {
                mt_count -= 5;
            }

            local_80 = player->current.pos - i_this->current.pos;
            local_68.x = local_80.x;
            local_68.y = local_80.y + REG6_F(5) + 90.0f;
            local_68.z = local_80.z;
            i_this->m496 = cM_atan2s(local_68.x, local_68.z);
            fVar11 = std::sqrtf(local_68.x * local_68.x + local_68.z * local_68.z);
            i_this->m494 = -cM_atan2s(local_68.y, fVar11);

            local_5c.x = (REG0_F(10) + 30.0f) * cM_ssin(i_this->m46A * 500);
            local_5c.y = (REG0_F(11) + 20.0f) * cM_scos(i_this->m46A * 1400) + 60.0f;
            local_5c.z = l_HIO.m28 + (REG0_F(12) + 30.0f) * cM_scos(i_this->m46A * 600); // TODO add

            sVar9 = (REG0_F(16) - 2000.0f) * cM_ssin(i_this->m46A * 1400);

            cMtx_YrotS(*calc_mtx, player->shape_angle.y + local_74[mt_count]);
            MtxPosition(&local_5c, &local_68);
            cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + local_68.x, 0.1f, REG0_F(10) + 4.0f);
            cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + local_68.z, 0.1f, REG0_F(10) + 4.0f);
            if (fopAcM_searchPlayerDistance(i_this) < l_HIO.m24 + 100.0f || (i_this->m18F9 != 0 && i_this->m466 == 0)) {
                cLib_addCalc2(&i_this->current.pos.y, i_this->mAcch.GetGroundH() + 40.0f, 0.5f, 3.0f);
                sVar9 = 0;
                i_this->m494 = 0;
                if (std::fabsf(i_this->current.pos.y - i_this->mAcch.GetGroundH() + 40.0f) < 2.0f) {
                    i_this->mC01 = 1;
                }
            } else {
                cLib_addCalc2(&i_this->current.pos.y, local_68.y + l_HIO.m18 + i_this->mAcch.GetGroundH(), 0.1f, 5.0f);
                if (i_this->m456 == 0) {
                    i_this->m456 = l_HIO.m10;
                    if (cM_rndF(1.0f) < l_HIO.m14 && i_this->m466 == 0) {
                        i_this->m455 = 1;
                        i_this->mC02 = 0;
                        cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                        local_5c.x = 0.0f;
                        local_5c.y = 30.0f;
                        local_5c.z = -30.0f;
                        MtxPosition(&local_5c, &i_this->m47C);
                        i_this->m47C += i_this->current.pos;
                        anm_init(i_this, 8, 2.3125, 2, 1.875, 0);
                        fopAcM_monsSeStart(i_this, JA_SE_CV_MG_ATTACK, 0);
                    }
                }
            }
            break;
        case 1:
            if (player->getCutType() == 0x10) {
                if (dComIfGp_getAttention().Lockon() && i_this == dComIfGp_getAttention().LockonTarget(0)) {
                    i_this->m454 = 6;
                    i_this->m456 = 0;
                    anm_init(i_this, 7, 2.0f, 0, 1.875f, 0);
                    break;
                }
            }
            i_this->mC02++;
            if (l_HIO.m30 <= i_this->mC02 && i_this->mC02 <= l_HIO.m32) {
                i_this->setBtAttackData(0.0f, 20.0f, 10000.0f, fopEn_enemy_c::OPENING_VERTICAL_JUMP_PARRY);
                i_this->setBtMaxDis(l_HIO.m34);
                i_this->setBtNowFrame(10.0f);
            }
            if (i_this->mC02 == l_HIO.m3C) {
                anm_init(i_this, 9, 2.0f, 0, 1.875f, 0);
            }
            if (i_this->mC02 == l_HIO.m38) {
                cMtx_YrotS(*calc_mtx, i_this->m496);
                cMtx_XrotM(*calc_mtx, i_this->m494);
                local_5c.x = 0.0f;
                local_5c.y = REG6_F(6) - 100.0f;
                local_5c.z = REG6_F(7) + 200.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
            }
            fVar11 = l_HIO.m2C;
            if (i_this->mC02 < l_HIO.m38) {
                fVar11 = REG0_F(11) + 4.0f;
                fVar1 = 0.1f;
            } else {
                fVar1 = 0.5f;
                if (i_this->mC02 == l_HIO.m3E) {
                    anm_init(i_this, 7, 2.0f, 0, 1.875f, 0);
                }
            }

            if (i_this->mC02 == l_HIO.m3E + REG0_S(3)) {
                fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_ATTACK, 0);
            }
            if (i_this->mC02 < l_HIO.m3E + 3 + REG6_S(7)) {
                i_this->mC04 = 1;
            }
            if (i_this->mC02 == l_HIO.m3E + 2) {
                i_this->m18D4 = 1;
            }
            if (l_HIO.m3E + 2 <= i_this->mC02 && i_this->mC02 <= l_HIO.m3E + 15) {
                i_this->mC04 = 2;
            }

            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, fVar1, fVar11);

            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;

            if (player->checkPlayerGuard() && i_this->mE48.ChkAtHit()) {
                i_this->m455 = 15;
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                local_5c.x = 0.0f;
                local_5c.y = 80.0f;
                local_5c.z = -120.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
                i_this->m462 = 10;
                i_this->m456 = 10;
                anm_init(i_this, 10, 2.0f, 2, 1.875f, 0);
                i_this->m18D4 = 0;
            }
            if (i_this->mC02 == l_HIO.m3A) {
                i_this->m455 = 0;
                i_this->m456 = l_HIO.m10;
                anm_init(i_this, 10, 2.3125f, 2, 1.875f, 0);
            }
            break;
        case 0xA:
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += i_this->gravity;
            if (i_this->speed.y < -100.0f) {
                i_this->speed.y = -100.0f;
            }
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m455 = 0;
            }
            break;
        case 0xF:
            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, 0.4f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, 0.4f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, 0.4f, 20.0f);
            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;
            if (i_this->m456 == 0) {
                i_this->m455 = 0;
                i_this->m456 = l_HIO.m10;
                anm_init(i_this, 10, 2.3125f, 2, 1.875f, 0);
            }
            break;
        case 0x11:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m455 = 0x17;
                i_this->m456 = cM_rndF(50.0f) + 50.0f;
                i_this->m48E = i_this->m456;
            }
            // TODO - GOTO
            break;
        case 0x14:
            break;
        case 0x17:
            break;
    }
}

/* 00005088-00005A04       .text mt_move_maru__FP8mt_class */
void mt_move_maru(mt_class*) {
    /* Nonmatching */
}

/* 00005B9C-00005C54       .text water_damage_se_set__FP8mt_class */
void water_damage_se_set(mt_class*) {
    /* Nonmatching */
}

/* 00005C54-0000614C       .text damage_check__FP8mt_class */
void damage_check(mt_class*) {
    /* Nonmatching */
}

/* 00006188-000074D4       .text daMt_Execute__FP8mt_class */
static BOOL daMt_Execute(mt_class*) {
    /* Nonmatching */
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class*) {
    return TRUE;
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class*) {
    /* Nonmatching */
}

static s16 bmd_data[8] = {
    0,0,0,0,0,0,0,0
};

static int br_bmd[3] = {
    0,0,0
};

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_ac) {
    mt_class* actor = (mt_class*) i_ac;
    for (int i = 0; i < 8; i++) {
        actor->mpMorfs[i] = new mDoExt_McaMorf(
            (J3DModelData*) dComIfG_getObjectRes("Mt", bmd_data[i]),
            NULL, NULL, NULL,
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
            0x800000, 0x37440402
        );
        if (actor->mpMorfs[i] == NULL) {
            return FALSE;
        }
        J3DModel* model = actor->mpMorfs[i]->getModel();
        if (model == NULL) {
            return FALSE;
        }
        J3DModelData* modelData = model->getModelData();
        actor->btk[i] = new mDoExt_btkAnm();
        JUT_ASSERT(0x11C0, actor->btk[i]);
        if (!actor->btk[i]->init(modelData, (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Mt", btk_data[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        actor->brk[i] = new mDoExt_brkAnm();
        JUT_ASSERT(0x11CD, actor->brk[i]);
        if (!actor->brk[i]->init(modelData, (J3DAnmTevRegKey*) dComIfG_getObjectRes("Mt", brk_data[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        if (i == 0) {
            anm_init(actor, 10, 2.8125, 2, 1.875, 0); // TODO wrong
            J3DAnmTexPattern* pat;
            for (int j = 0; j < 2; j++) {
                pat = (J3DAnmTexPattern*) dComIfG_getObjectRes("Mt", mt_tex_anm_idx[j]);
                pat->searchUpdateMaterialID(modelData);
            }
            actor->m340 = new J3DTexNoAnm[pat->getUpdateMaterialNum()];
            for (int j = 0; j < pat->getUpdateMaterialNum(); j++) {
                actor->m340[i].setAnmIndex(j);
            }
            tex_anm_set(actor, 0);
        }

        model->setUserArea((u32) actor);
        for (int jntNo = 0; jntNo < modelData->getJointNum(); jntNo++) {
            if (i == 0) {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_head);
                }
            } else if (i == 7) {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_tail);
                }
            } else {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_body);
                }
            }
        }

        actor->m600[i] = scale_data[i];
    }

    for (int i = 0; i < 3; i++) {
        J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Mt", br_bmd[i]);
        JUT_ASSERT(0x127A, modelData != NULL);
        actor->br_modelL[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(0x127D, actor->br_modelL[i] != NULL);
        actor->br_modelR[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(0x127F, actor->br_modelR[i] != NULL);
        actor->br_modelL[i]->setBaseScale(actor->scale);
        actor->br_modelR[i]->setBaseScale(actor->scale);
    }

    return TRUE;
}

static dCcD_SrcSph sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK8,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK7,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 200.0f,
    },
};

static cPhs_State daMt_Create(fopAc_ac_c* i_ac) {
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK7,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 200.0f,
        },
    };

    fopAcM_SetupActor(i_ac, mt_class);
    mt_class* i_this = (mt_class*) i_ac;

    cPhs_State phase_state = dComIfG_resLoad(&i_this->mPhs, "Mt");
    if (phase_state == cPhs_COMPLEATE_e) {
        i_ac->gbaName = 5;
        i_this->m2B4 = fopAcM_GetParam(i_this) & 0xFF;
        if (i_this->m2B4 == 0xFF) {
            i_this->m2B4 = 0;
        }

        i_this->m2B5 = (fopAcM_GetParam(i_this) >> 8) & 0x7F;
        i_this->m2B6 = (fopAcM_GetParam(i_this) >> 0xF) & 0x1;
        i_this->m2B7 = (fopAcM_GetParam(i_this) >> 0x10) & 0xFF;
        i_this->m2B8 = (fopAcM_GetParam(i_this) >> 0x18) & 0xFF;

        if (i_this->m2B6 == 0) {
            i_this->m2B9 = i_ac->current.angle.z;
            if (i_this->m2B9 != 0) {
                if (dComIfGs_isSwitch(i_this->m2B9, fopAcM_GetRoomNo(i_ac))) {
                    return cPhs_ERROR_e;
                }
            }
        } else {
            i_this->m2BA = i_ac->current.angle.z;
        }
        i_ac->current.angle.z = 0;

        i_ac->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("magtail", 0);
        if (!fopAcM_entrySolidHeap(i_this, CallbackCreateHeap, 0x1BFC8)) {
            return cPhs_ERROR_e;
        }

        i_this->initBt(162.5f, 200.0f);
        if (i_this->m2B4 >= 10) {
            switch (i_this->m2B5) {
                case 1:
                    i_this->m488 = 1000;
                    break;
                case 2:
                    i_this->m488 = 500;
                    break;
                case 3:
                    i_this->m488 = 250;
                    break;
                case 11:
                    i_this->m488 = -1000;
                    break;
                case 12:
                    i_this->m488 = -500;
                    break;
                case 13:
                    i_this->m488 = -250;
                    break;
            }
        } else if (i_this->m2B7 != 0xFF) {
            i_this->mpPath = dPath_GetRoomPath(i_this->m2B7, fopAcM_GetRoomNo(i_ac));
            if (i_this->mpPath == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->m2BC = i_this->m2B7 + 1;
            i_this->m2BE = 1;
            i_this->m47C = i_this->mpPath->m_points[0].m_position; // TODO might not be a cXyz assignment
        }
        if (i_this->m2B8 != 0xFF) {
            i_this->m2BB = i_this->m2B8 + 1;
        }
        fopAcM_SetMtx(i_ac, i_this->mpMorfs[1]->getModel()->getBaseTRMtx());
        fopAcM_SetMin(i_ac, -200.0f, -200.0f, -200.0f);
        fopAcM_SetMax(i_ac, 200.0f, 200.0f, 200.0f);
        i_ac->gravity = -3.0f;
        i_this->m46A = cM_rndF(32768.0f);
        for (int i = 0; i < 64; i++) {
            i_this->m6F4[i] = i_ac->current.pos;
            i_this->m9F4[i] = i_ac->current.angle;
        }
        i_this->mAcch.Set(fopAcM_GetPosition_p(i_ac), fopAcM_GetOldPosition_p(i_ac), i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_ac));
        i_this->mAcchCir.SetWall(50.0f, REG0_F(0) + 19.0f);
        i_this->mStts.Init(250, 2, i_this);
        // for
        i_this->mE48.SetAtAtp(2);
        i_this->mEyeSph.Set(eye_sph_src);
        i_this->mEyeSph.SetStts(&i_this->mStts);
        i_this->m18F0 = 1.0f;
        i_this->m18FB = 2;
        i_this->max_health = 8;
        i_this->health = 8;
        i_this->m1900 = i_this;
        i_this->m1AB1 = i_this->m2B9;
        daMt_Execute(i_this);
    }
}

static actor_method_class l_daMt_Method = {
    (process_method_func)daMt_Create,
    (process_method_func)daMt_Delete,
    (process_method_func)daMt_Execute,
    (process_method_func)daMt_IsDelete,
    (process_method_func)daMt_Draw,
};

actor_process_profile_definition g_profile_MT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mt_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MT,
    /* Actor SubMtd */ &l_daMt_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e | fopAcStts_UNK8000000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
