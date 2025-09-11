/**
 * d_a_kanban.cpp
 * Object - Cuttable sign
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kanban.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_bomb2.h"
#include "d/actor/d_a_sea.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_kanban.h"

class daKanban_HIO_c : public mDoHIO_entry_c {
public:
    daKanban_HIO_c();
    virtual ~daKanban_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0C */ f32 m0C;
}; // size = 0x10

static daKanban_HIO_c l_HIO;
static fopAc_ac_c* target_info[10];
static s32 target_info_count;

static s16 pl_cut_real_no_dt[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
static s16 pl_cut_no_dt[] = {255, 0, 4, 3, 3, 1, 0, 4, 4, 4, 1, 3, 1, 3, 1, 1, 1, 3, 1, 1, 0, 1, 0, 1, 0, 1, 1, 4, 0, 1, 1, 1};
static u32 cut_parts_arg_data[] = {
        0x2000000, 0x4000000, 0x800000, 0x1000000,
        0x7FE00000, 0x7FE00000, 0x7FE00000, 0x7FE00000,
        0x4000000, 0x800000, 0x1000000, 0x10000000,
        0x40000000, 0x7FE00000, 0x7FE00000, 0x7FE00000,
        0x400000, 0x200000, 0x2000000, 0x4000000,
        0x7FE00000, 0x7FE00000, 0x7FE00000, 0x7FE00000,
        0x200000, 0x2000000, 0x4000000, 0x800000,
        0x7FE00000, 0x7FE00000, 0x7FE00000, 0x7FE00000,
        0x8000000, 0x400000, 0x200000, 0x2000000,
        0x4000000, 0x800000, 0x1000000, 0x10000000,
};

/* 000000EC-0000012C       .text __ct__14daKanban_HIO_cFv */
daKanban_HIO_c::daKanban_HIO_c() {
    m04 = 0.0f;
    m08 = 0;
    m0A = 0;
    m0C = 0.8f;
}

/* 00000174-0000047C       .text daKanban_Draw__FP12kanban_class */
static BOOL daKanban_Draw(kanban_class* i_this) {
    J3DModel* model;
    cXyz sp0C;
    u32 uVar5;
    s32 i;

    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->actor.current.pos, &i_this->actor.tevStr);
    
    sp0C.set(
        i_this->actor.current.pos.x,
        i_this->actor.current.pos.y + 150.0f + REG8_F(18),
        i_this->actor.current.pos.z
    );

    i_this->actor.scale.set(l_HIO.m0C, l_HIO.m0C, l_HIO.m0C);
    i_this->m570 = 0;

    for (i = 0, uVar5 = i_this->m294; i < 11; i++, uVar5 >>= 1) {
        if (!(uVar5 & 1)) {
            continue;
        }

        model = i_this->m544[i];

        model->setBaseScale(i_this->actor.scale);
        MtxTrans(i_this->actor.current.pos.x + i_this->m2E4, i_this->actor.current.pos.y + i_this->m2E8, i_this->actor.current.pos.z + i_this->m2EC, false);
        cMtx_XrotM(*calc_mtx, i_this->m2AC.x);
        cMtx_ZrotM(*calc_mtx, i_this->m2AC.z);
        cMtx_YrotM(*calc_mtx, i_this->actor.shape_angle.y);
        cMtx_XrotM(*calc_mtx, i_this->actor.shape_angle.x);
        cMtx_ZrotM(*calc_mtx, i_this->actor.shape_angle.z);
        MtxTrans(i_this->m2CC.x - i_this->m2E4, i_this->m2CC.y - i_this->m2E8, i_this->m2CC.z - i_this->m2EC, true);
        model->setBaseTRMtx(*calc_mtx);

        g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
        mDoExt_modelUpdateDL(model);

        if (!i_this->m290 && i_this->m2C0 == 10) {
            if (i_this->m570) {
                dComIfGd_addRealShadow(i_this->m570, model);
            } else {
                i_this->m570 = dComIfGd_setShadow(i_this->m570, 1, model, &sp0C, REG8_F(19) + 800.0f, REG8_F(17) + 40.0f,
                                i_this->actor.current.pos.y, i_this->m350.GetGroundH(),
                                i_this->m350.m_gnd, &i_this->actor.tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
            }
        } else if (i_this->m290 && !i_this->m350.ChkGroundHit()) {
            fopAc_ac_c* pfVar3 = fopAcM_SearchByID(i_this->m2C8);
            if (pfVar3 != NULL) {
                if (i_this->m570) {
                    dComIfGd_addRealShadow(i_this->m570, model);
                } else {
                    i_this->m570 = dComIfGd_setShadow(i_this->m570, 1, model, &sp0C, REG8_F(19) + 800.0f, REG8_F(17) + 40.0f,
                                        i_this->actor.current.pos.y, i_this->m350.GetGroundH(),
                                        i_this->m350.m_gnd, &i_this->actor.tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
                }
            }
        }
    }

    return TRUE;
}

/* 0000047C-0000055C       .text shibuki_set__FP12kanban_class4cXyzf */
void shibuki_set(kanban_class* i_this, cXyz pos, float scaleXZ) {
    if (daSea_ChkArea(i_this->actor.current.pos.x, i_this->actor.current.pos.z)) {
        pos.y = daSea_calcWave(i_this->actor.current.pos.x, i_this->actor.current.pos.z);
    } else if (i_this->m350.MaskWaterIn()) {
        pos.y = i_this->m350.m_wtr.GetHeight();
    }

    fopKyM_createWpillar(&pos, scaleXZ, 0.5f, 0);

    fopAcM_seStart(&i_this->actor, JA_SE_OBJ_FALL_WATER_M, 0);
}

/* 0000055C-00000884       .text sea_water_check__FP12kanban_class */
BOOL sea_water_check(kanban_class* i_this) {
    u8 iVar3 = 0;
    f32 f4;
    f32 f0;
    f32 f1;

    if (REG8_S(1) != 0) {
        return FALSE;
    }

    i_this->m528 = i_this->actor.current.pos;
    i_this->actor.gravity = -3.0f;

    if (daSea_ChkArea(i_this->actor.current.pos.x, i_this->actor.current.pos.z)) {
        f1 = daSea_calcWave(i_this->actor.current.pos.x, i_this->actor.current.pos.z);
        i_this->m528.y = f1;
        if (i_this->m2C4 == 1) {
            i_this->m2A0 = 7.0f;
        }

        if (i_this->actor.current.pos.y < (f1 - 120.0f) + REG8_F(6)) {
            i_this->actor.gravity = 0.0f;
            i_this->actor.speedF = 0.0f;
            i_this->actor.speed.setall(0.0f);
            i_this->m2BC += (s16)(REG8_F(7) + 1000.0f);

            f0 = (REG8_F(8) + 147.0f) + (REG8_F(9) + 2.0f) * cM_ssin(i_this->m2BC);
            cLib_addCalc2(&i_this->actor.current.pos.y, f1 - f0, 1.0f, 30.0f);
            iVar3 = 1;
        }
    } else if (i_this->m350.MaskWaterIn()) {
        iVar3 = 2;
        f4 = i_this->m350.m_wtr.GetHeight();
        i_this->m528.y = i_this->m350.m_wtr.GetHeight();
        if (i_this->m2C4 == 1) {
            i_this->m2A0 = 7.0f;
        }

        i_this->actor.gravity = -3.0f;
        if (i_this->actor.current.pos.y < f4) {
            i_this->actor.gravity = 0.0f;
            i_this->actor.speedF = 0.0f;
            i_this->actor.speed.setall(0.0f);
            i_this->m2BC += (s16)(REG8_F(7) + 1000.0f);

            f0 = (REG8_F(8) + 147.0f) + (REG8_F(9) + 2.0f) * cM_ssin(i_this->m2BC);
            cLib_addCalc2(&i_this->actor.current.pos.y, f4 - f0, 1.0f, 30.0f);
            iVar3 = 1;
        }
    }

    if (iVar3 != 0) {
        if ((iVar3 == 1) && (i_this->m29C == 0)) {
            cXyz sp30(0.5f, 0.5f, 0.5f);
            i_this->m514.remove();
            dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->m528, NULL, &sp30, 0xFF, &i_this->m514);
            i_this->m2BC = 0;
            i_this->m29C = 1;
            i_this->m514.setRate(0.0f);
            cXyz sp24 = i_this->actor.current.pos;
            shibuki_set(i_this, sp24, 0.5f);
        }
        return TRUE;
    }

    i_this->m2A0 = 0.0f;
    return FALSE;
}

/* 00000884-00000940       .text bom_search_sub__FPvPv */
void* bom_search_sub(void* ac, void*) {
    if (fopAcM_IsActor(ac)) {
        bool bVar2 = false;
        s16 proc = fopAcM_GetName(ac);

        if (proc == PROC_BOMB) {
            daBomb_c* bomb = (daBomb_c*)ac;
            if (bomb->chk_state(daBomb_c::STATE_0)) {
                bVar2 = true;
            }
        } else if (proc == PROC_Bomb2) {
            daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)ac;
            if (bomb2->chk_explode()) {
                bVar2 = true;
            }
        }

        if (bVar2 && target_info_count < (s32)10) {
            target_info[target_info_count] = (fopAc_ac_c*)ac;
            target_info_count++;
        }
    }
    return NULL;
}

/* 00000940-00000B84       .text shock_damage_check__FP12kanban_class */
BOOL shock_damage_check(kanban_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp1C;

    target_info_count = 0;

    for (s32 i = 0; i < 10; i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(bom_search_sub, &i_this->actor);

    if (target_info_count != 0) {
        for (s32 i = 0; i < target_info_count; i++) {
            sp1C.x = target_info[i]->current.pos.x - i_this->actor.current.pos.x;
            sp1C.z = target_info[i]->current.pos.z - i_this->actor.current.pos.z;

            if (std::sqrtf(sp1C.x * sp1C.x + sp1C.z * sp1C.z) < 1000.0f) {
                i_this->m2B2[4] = 100;
                i_this->m2B2[4] += REG8_S(4);
                return TRUE;
            }
        }
    }

    if (player->checkHammerQuake()) {
        sp1C = player->getSwordTopPos();
        
        sp1C.x -= i_this->actor.current.pos.x;
        sp1C.z -= i_this->actor.current.pos.z;

        if (std::sqrtf(sp1C.x * sp1C.x + sp1C.z * sp1C.z) < 1000.0f) {
            return TRUE;
        }
    }

    return FALSE;
}

/* 00000B84-00000E6C       .text cut_point_check__FP12kanban_class */
void cut_point_check(kanban_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    u32 parameters;
    u32 uVar8;
    u32 arg;
    s32 i;
    s32 uVar5;

    if (i_this->m2C4 == 0) {
        s16 y = a_this->shape_angle.y - fopAcM_searchPlayerAngleY(a_this);
        s16 sVar3 = abs(y);
        if (sVar3 > 0x6000) {
            i_this->m2C4 = 2;
        } else if (sVar3 > 0x2000 && sVar3 < 0x6000) {
            if (fopAcM_searchPlayerAngleY(a_this) & 0x80000000) {
                i_this->m2C4 = 2;
            }
        }
    }

    uVar5 = i_this->m2C4 * 8;
    parameters = 0;
    if ((i_this->m2C2 >> i_this->m2C4) & 1 || i_this->m2C2 & 2) {
        return;
    }

    i_this->m2C2 |= (1 << i_this->m2C4);
    if (i_this->m294 & 1) {
        i_this->m294 = 0x7FE;
        i_this->m29B = 0;
    }

    uVar8 = i_this->m294 << 0x14;
    for (i = 0; i < 8; i++) {
        arg = cut_parts_arg_data[uVar5 + i];
        if ((arg != 0x7FE00000) && ((uVar8 & arg))) {
            uVar8 ^= arg;
            parameters |= arg;
        }
    }

    if (parameters != 0) {
        cXyz sp18 = *i_this->m5B0.GetTgHitPosP();
        dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &sp18, &player->shape_angle);
        dScnPly_ply_c::setPauseTimer(1);
        a_this->current.angle.z = i_this->m2C4;
        
        fpc_ProcID fVar6 = fopAcM_createChild(PROC_KANBAN, fopAcM_GetID(a_this), parameters, &a_this->current.pos, fopAcM_GetRoomNo(a_this), &a_this->current.angle, &a_this->scale, 0, NULL);
        if (fVar6 != fpcM_ERROR_PROCESS_ID_e) {
            fopAcM_seStart(a_this, JA_SE_OBJ_BREAK_BOARD, 0);
            
            i_this->m294 = uVar8 >> 0x14;
            if (i_this->m2C4 == 1) {
                i_this->m298 = 0;
                if (i_this->m2C2 & 0x10) {
                    i_this->m298 = 1;
                }
                a_this->current.pos.y = i_this->m2F8.y - 70.0f;
                i_this->m2CC.y = 70.0f;
                i_this->m2E8 = 140.0f;
                i_this->m2A4 = 0.0f;
                i_this->m2A8 = 0.0f;
                i_this->m2C0 = 0xb;
            }

            if ((i_this->m2C2 & 5) == 5 || i_this->m2C4 == 4) {
                i_this->m2A4 = 25.0;
                i_this->m2A8 = 10.0;
            }
        }
        a_this->current.angle.z = 0;
    }
}

/* 00000E6C-000012B8       .text mother_move__FP12kanban_class */
void mother_move(kanban_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch(i_this->m2C0) {
        case 10:
            if (i_this->m5B0.ChkTgHit()) {
                cCcD_Obj* hitObj = i_this->m5B0.GetTgHitObj();
                if (hitObj != NULL) {
                    fopAcM_ClearStatusMap(a_this);

                    switch (hitObj->GetAtType()) {
                        case AT_TYPE_SKULL_HAMMER:
                            i_this->m29A = 2;
                            if (player->getCutType() != 17) {
                                i_this->m29B = 0;
                                i_this->m2A4 = 0.0f;
                                i_this->m2A8 = 0.0f;
                                i_this->m29A = 1;
                                i_this->m2C0 = 20;
                                cXyz sp18 = *i_this->m5B0.GetTgHitPosP();
                                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &sp18, &player->shape_angle);
                                dScnPly_ply_c::setPauseTimer(1);
                                return;
                            }

                        case AT_TYPE_SWORD: {
                            s32 i = 0;
                            for (; i < 32; i++) {
                                if (pl_cut_real_no_dt[i] == player->getCutType()) {
                                    break;
                                }
                            }

                            if (i < 32 && pl_cut_no_dt[i] != 0xFF) {
                                i_this->m2C4 = pl_cut_no_dt[i];
                                cut_point_check(i_this);
                            }
                            break;
                        }
                        default:
                            i_this->m2C4 = 4;
                            cut_point_check(i_this);
                            break;
                    }
                }
            }
            break;

        case 11:
            a_this->current.angle.y = player->shape_angle.y + -0x4000;
            a_this->shape_angle.y = a_this->current.angle.y;
            i_this->m298 = 0;
            if (i_this->m294 & 0x100) {
                a_this->speedF = 20.0f;
                a_this->speed.y = 10.0f;
                a_this->gravity = -3.0f;
            } else {
                a_this->speedF = 3.0f;
                a_this->speed.y = 7.0f;
                a_this->gravity = -3.0f;
            }
            i_this->m2C0++;
            break;

        case 12:
            if (sea_water_check(i_this)) {
                i_this->m2BE = 2;
                i_this->m2C0 = 0x28;
            } else {
                if (i_this->m350.ChkWallHit()) {
                    a_this->speedF *= -1.0f;
                }

                if (a_this->speed.y < 0.0f) {
                    cLib_addCalcAngleS2(&a_this->shape_angle.x, 0x4000, 1, 0x1000);
                }

                if (i_this->m350.ChkGroundHit()) {
                    i_this->m2C6 = 0x800;
                    fopAcM_getGroundAngle(a_this, &i_this->m2AC);
                    a_this->speedF = 0.0;
                    a_this->gravity = 0.0;
                    i_this->m2C0 = 13;
                }
            }
            break;

        case 13:
            if (sea_water_check(i_this)) {
                i_this->m2BE = 2;
                i_this->m2C0 = 0x28;
                break;
            }

            cLib_addCalcAngleS2(&a_this->shape_angle.x, i_this->m2C6 + 0x4000, 1, 0x1000);
            i_this->m2C6 ^= 0xFF00;
            i_this->m298++;
            i_this->m298 &= 3;

            if (!(i_this->m298 & 1)) {
                i_this->m2C6 = 0x400;
            }

            if (!(i_this->m298 & 3)) {
                a_this->shape_angle.x = 0x4000;
                i_this->m2C6 = 0;
                i_this->m5B0.OffCoSetBit();
                i_this->m5B0.OffTgSetBit();
                i_this->m5B0.ClrTgHit();
                i_this->m2C0++;
            }

        case 14:
            if (sea_water_check(i_this)) {
                i_this->m2BE = 2;
                i_this->m2C0 = 0x28;
            } else if (i_this->m2B2[4] == 0 && shock_damage_check(i_this)) {
                a_this->speed.y = cM_rndF(10.0f) + 20.0f;
                a_this->gravity = -3.0f;
                i_this->m2C0 = 12;
            }
            break;

        case 0x14:
            i_this->m2C0++;

        case 0x15:
            i_this->m2B2[1] = 2;

            f32 fVar4 = 90.0f;
            if (i_this->m2C2 & 8) {
                fVar4 = 65.0f;
            }

            if (i_this->m2C2 & 0x10) {
                fVar4 = 20.0f;
            }

            cLib_addCalc2(&a_this->current.pos.y, i_this->m2F8.y - fVar4, 1.0f, 30.0f);
    }
}

/* 000012B8-0000134C       .text mother_water_swim__FP12kanban_class */
void mother_water_swim(kanban_class* i_this) {
    switch (i_this->m2C0) {
        case 40:
            i_this->m2C6 = 0;
            i_this->actor.shape_angle.x = 0x4000;
            i_this->m5B0.OffCoSetBit();
            i_this->m5B0.OffTgSetBit();
            i_this->m5B0.ClrTgHit();
            i_this->m2C0++;

        case 41:
            sea_water_check(i_this);
            break;
    }
}

/* 0000134C-00001580       .text ret_keisan_move__FP12kanban_class */
BOOL ret_keisan_move(kanban_class* i_this) {
    cLib_addCalc0(&i_this->m2A0, 1.0f, 2.0f);
    f32 x = i_this->m2F8.x - i_this->actor.current.pos.x;
    f32 y = i_this->m2F8.y - i_this->actor.current.pos.y;
    f32 z = i_this->m2F8.z - i_this->actor.current.pos.z;
    cLib_addCalcAngleS2(&i_this->actor.current.angle.y, (s16)cM_atan2s(x, z), 1, 0x1000);
    i_this->actor.shape_angle = i_this->actor.current.angle;

    if (std::sqrtf(y * y) > 2.0f) {
        cLib_addCalc2(&i_this->actor.current.pos.y, i_this->m2F8.y, 1.0f, 10.0f);
        return FALSE;
    }

    if (std::sqrtf(x * x + z * z) < 2.0f) {
        i_this->actor.speedF = 0.0f;
        i_this->actor.current.pos = i_this->m2F8;
        return TRUE;
    }
    
    cLib_addCalc2(&i_this->actor.current.pos.x, i_this->m2F8.x, 1.0f, 10.0f);
    cLib_addCalc2(&i_this->actor.current.pos.z, i_this->m2F8.z, 1.0f, 10.0f);
    return FALSE;
}

/* 00001580-00001770       .text mother_return_move__FP12kanban_class */
void mother_return_move(kanban_class* i_this) {
    fopAc_ac_c* a_this = static_cast<fopAc_ac_c*>(&i_this->actor);
    
    switch (i_this->m2C0) {
        case 30:
            if (dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e)) {
                break;
            }
            i_this->m2B2[0] = cM_rndF(30.0f);
            i_this->m2C0++;

        case 31:
            if (i_this->m2B2[0] == 0) {
                i_this->m2CC.x = 0.0f;
                i_this->m2CC.y = 0.0f;
                i_this->m2CC.z = 0.0f;
                i_this->m2E4 = 0.0f;
                i_this->m2E8 = 0.0f;
                i_this->m2EC = 0.0f;
                i_this->m2C6 = 0;
                if (ret_keisan_move(i_this)) {
                    i_this->m2C0++;
                }
            }
            break;

        case 32: {
            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m2F0.y, 1, 0x1000);
            s16 sVar2 = cLib_distanceAngleS(a_this->current.angle.y, i_this->m2F0.y);
            if (sVar2 < 0x100) {
                a_this->current.angle.y = i_this->m2F0.y;
                i_this->m2C0++;
            }
            break;
        }
        case 33:
            if (i_this->m294 == 0x7FE) {
                i_this->m2C2 = 0;
                i_this->m2C4 = 0;
                i_this->m29B = 1;
                i_this->m5B0.OnTgSetBit();
                i_this->m5B0.OnCoSetBit();
                i_this->m2A4 = 105.0f;
                i_this->m2A8 = 50.0f;
                fopAcM_SetStatusMap(a_this, 0x38);
                i_this->m2BE = 0;
                i_this->m2C0 = 10;
                return;
            }
            break;
    }

    if (i_this->m2B2[0] == 0 && i_this->m2C0 >= 31) {
        cLib_addCalcAngleS2(&a_this->current.angle.x, i_this->m2F0.x, 1, 0x1000);
        cLib_addCalcAngleS2(&a_this->current.angle.z, i_this->m2F0.z, 1, 0x1000);
        a_this->shape_angle = a_this->current.angle;
    }
}

/* 00001770-00001B50       .text parts_move__FP12kanban_class */
void parts_move(kanban_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch(i_this->m2C0) {
        case 0x6e:
            i_this->m298 = 0;
            a_this->current.angle.y = fopAcM_searchActorAngleY(player, a_this);
            if (i_this->m2C4 != 1) {
                a_this->current.angle.y += cM_rndFX(8000.0f);
                kanban_class* kanban = (kanban_class*)fopAcM_SearchByID(i_this->m2C8);
                if (kanban != NULL) {
                    a_this->speedF = cM_rndFX(2.0f) + 10.0f;
                    a_this->speed.y = cM_rndFX(5.0f) + 20.0f;
                    a_this->gravity = -5.0f;
                    if (kanban->m29A == 2) {
                        a_this->current.angle.y = player->shape_angle.y + -0x4000;
                        a_this->speedF = cM_rndFX(5.0f) + 15.0f;
                        a_this->speed.y = cM_rndFX(5.0f) + 30.0f;
                        a_this->gravity = -5.0f;
                    }
                }
                a_this->shape_angle.y = a_this->current.angle.y;
                i_this->m2C0 = 0x6f;
            } else {
                a_this->shape_angle.y = a_this->current.angle.y;
                i_this->m298 = 0;
                if (i_this->m294 & 0x100) {
                    a_this->speedF = 20.0f;
                    a_this->speed.y = 10.0f;
                    a_this->gravity = -3.0f;
                } else {
                    a_this->speedF = 3.0f;
                    a_this->speed.y = 7.0f;
                    a_this->gravity = -3.0f;
                }
                i_this->m2C0 = 0x78;
            }
            break;

        case 0x6f:
            if (i_this->m350.ChkWallHit()) {
                a_this->speedF *= -1.0f;
            }

            a_this->shape_angle.x += 0x1000;

            if (i_this->m350.ChkGroundHit()) {
                a_this->speedF = 5.0;
                a_this->speed.y = 10.0;
                i_this->m2C0++;
            }
            break;

        case 0x70:
            cLib_addCalcAngleS2(&a_this->shape_angle.x, 0x4000, 1, 0x1000);
            if (i_this->m350.ChkGroundHit()) {
                i_this->m2C6 = 0x800;
                fopAcM_getGroundAngle(a_this, &i_this->m2AC);
                a_this->speedF = 0.0f;
                a_this->gravity = 0.0f;
                i_this->m2C0++;
            }
            break;

        case 0x71:
            cLib_addCalcAngleS2(&a_this->shape_angle.x, i_this->m2C6 + 0x4000, 1, 0x1000);
            i_this->m2C6 ^= 0xFF00;
            i_this->m298++;
            i_this->m298 &= 3;
            if ((i_this->m298 & 1) == 0) {
                i_this->m2C6 = 0x400;
            }

            if ((i_this->m298 & 3) == 0) {
                a_this->shape_angle.x = 0x4000;
                i_this->m2C6 = 0;
                i_this->m5B0.OffCoSetBit();
                i_this->m5B0.OffTgSetBit();
                i_this->m5B0.ClrTgHit();
                i_this->m2C0++;
            }
            break;

        case 0x72:
            if ((i_this->m2B2[4] == 0) && shock_damage_check(i_this)) {
                a_this->speed.y = cM_rndF(10.0f) + 20.0f;
                a_this->gravity = -3.0f;
                i_this->m2C0 = 0x70;
            }
            break;

        case 0x78:
            if (i_this->m350.ChkWallHit()) {
                a_this->speedF *= -1.0f;
            }

            if (a_this->speed.y < 0.0f) {
                cLib_addCalcAngleS2(&a_this->shape_angle.x, 0x4000, 1, 0x1000);
            }

            if (i_this->m350.ChkGroundHit()) {
                a_this->shape_angle.x = 0x4000;
                i_this->m2C6 = 0x800;
                fopAcM_getGroundAngle(a_this, &i_this->m2AC);
                a_this->speedF = 0.0f;
                a_this->gravity = 0.0f;
                i_this->m2C0 = 0x71;
            }
            break;
    }
}

/* 00001B50-00001D58       .text chield_parts_move__FP12kanban_class */
void chield_parts_move(kanban_class* i_this) {
    switch (i_this->m2C0) {
        case 0x82:
            if (dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e)) {
                break;
            }
            i_this->m2B2[0] = cM_rndF(30.0f);
            i_this->m2C0++;

        case 0x83:
            if (i_this->m2B2[0] == 0) {
                i_this->m2CC.x = 0.0f;
                i_this->m2CC.y = 0.0f;
                i_this->m2CC.z = 0.0f;
                i_this->m2E4 = 0.0f;
                i_this->m2E8 = 0.0f;
                i_this->m2EC = 0.0f;
                i_this->m2C6 = 0;
                if (ret_keisan_move(i_this)) {
                    i_this->m2C0++;
                }
            }
            break;

        case 0x84: {
            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->m2F0.y, 1, 0x1000);
            s16 sVar3 = cLib_distanceAngleS(i_this->actor.current.angle.y, i_this->m2F0.y);
            if (sVar3 < 0x100) {
                i_this->actor.current.angle.y = i_this->m2F0.y;
                i_this->m2C0++;
                kanban_class* kanban = (kanban_class*)fopAcM_SearchByID(i_this->m2C8);
                if (kanban != NULL) {
                    kanban->m294 ^= i_this->m294;
                }
            }
            break;
        }
        case 0x85:
            kanban_class* kanban = (kanban_class*)fopAcM_SearchByID(i_this->m2C8);
            if (kanban != NULL) {
                if (kanban->m29B == 1) {
                    fopAcM_delete(&i_this->actor);
                }

                if (kanban->m29B == 2) {
                    i_this->m2BE = 100;
                    i_this->m2C0 = 0x6e;
                }
            }
            break;
    }

    if (i_this->m2B2[0] == 0 && i_this->m2C0 >= 0x83) {
        cLib_addCalcAngleS2(&i_this->actor.current.angle.x, i_this->m2F0.x, 1, 0x1000);
        cLib_addCalcAngleS2(&i_this->actor.current.angle.z, i_this->m2F0.z, 1, 0x1000);
        i_this->actor.shape_angle = i_this->actor.current.angle;
    }
}

/* 00001D58-00001DEC       .text chield_water_swim__FP12kanban_class */
void chield_water_swim(kanban_class* i_this) {
    switch (i_this->m2C0) {
        case 140:
            i_this->m2C6 = 0;
            i_this->actor.shape_angle.x = 0x4000;
            i_this->m5B0.OffCoSetBit();
            i_this->m5B0.OffTgSetBit();
            i_this->m5B0.ClrTgHit();
            i_this->m2C0++;

        case 141:
            sea_water_check(i_this);
            break;
    }
}

static fpc_ProcID l_msgId = fpcM_ERROR_PROCESS_ID_e;

/* 00001DEC-000022A8       .text daKanban_Execute__FP12kanban_class */
static BOOL daKanban_Execute(kanban_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    for (s32 i = 0; i < 5; i++) {
        if (i_this->m2B2[i] != 0) {
            i_this->m2B2[i]--;
        }
    }

    switch (i_this->m2BE) {
        case 0:
#if VERSION <= VERSION_JPN
            mother_move(i_this);
            if (i_this->m2C2 == 0 && i_this->m2C0 != 20 && i_this->m2C0 != 21) 
#endif
            {
                if (i_this->actor.eventInfo.checkCommandTalk()) {
                    if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
                        if (dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
                            l_msgId = fopMsgM_messageSet(fopAcM_GetParam(&i_this->actor), &i_this->actor.eyePos);
                        }
                    } else {
                        msg_class* pmVar3 = fopMsgM_SearchByID(l_msgId);
                        if (pmVar3 != NULL && pmVar3->mStatus == fopMsgStts_BOX_CLOSED_e) {
                            pmVar3->mStatus = fopMsgStts_MSG_DESTROYED_e;
                            dComIfGp_event_reset();
                            l_msgId = -1;
                        }
                    }
                } else {
#if VERSION <= VERSION_JPN
                    i_this->actor.eventInfo.onCondition(dEvtCnd_CANTALK_e);
#else
                    if (i_this->m2C2 == 0 && i_this->m2C0 != 0x14 && i_this->m2C0 != 0x15) {
                        i_this->actor.eventInfo.onCondition(dEvtCnd_CANTALK_e);
                    }
                    mother_move(i_this);
#endif
                }
            }

            if (i_this->m2C0 != 14) {
                fopAcM_rollPlayerCrash(&i_this->actor, 35.0f, 0);
            }

            i_this->m5B0.SetC(i_this->actor.current.pos);
            i_this->m5B0.SetH(i_this->m2A4);
            i_this->m5B0.SetR(i_this->m2A8);
            dComIfG_Ccsp()->Set(&i_this->m5B0);

            if (i_this->m294 != 1 && i_this->m294 != 0x7FE && player->getTactMusic() == 4) {
                i_this->actor.gravity = 0.0f;
                i_this->actor.speedF = 0.0f;
                i_this->actor.speed.set(0.0f, 0.0f, 0.0f);
                i_this->m2BE = 1;
                i_this->m2C0 = 30;
            }
            break;
        
        case 1:
            mother_return_move(i_this);
            break;

        case 2:
            mother_water_swim(i_this);
            if (player->getTactMusic() == 4) {
                i_this->m514.remove();
                i_this->actor.gravity = 0.0;
                i_this->actor.speedF = 0.0;
                i_this->actor.speed.set(0.0f, 0.0f, 0.0f);
                i_this->m2BE = 1;
                i_this->m2C0 = 30;
            }
            break;

        case 100:
            parts_move(i_this);
            if (player->getTactMusic() == 4) {
                i_this->actor.gravity = 0.0;
                i_this->actor.speedF = 0.0;
                i_this->actor.speed.set(0.0f, 0.0f, 0.0f);
                i_this->m2BE = 0x65;
                i_this->m2C0 = 0x82;
            } else if (sea_water_check(i_this)) {
                i_this->m2BE = 0x66;
                i_this->m2C0 = 0x8c;
            }
            break;

        case 101:
            chield_parts_move(i_this);
            break;
            
        case 102:
            chield_water_swim(i_this);
            if (player->getTactMusic() == 4) {
                i_this->m514.remove();
                i_this->actor.gravity = 0.0;
                i_this->actor.speedF = 0.0;
                i_this->actor.speed.set(0.0f, 0.0f, 0.0f);
                i_this->m2BE = 0x65;
                i_this->m2C0 = 0x82;
            }
            break;
    }

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cXyz sp14;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = i_this->actor.speedF;
    cXyz sp08;
    MtxPosition(&sp14, &sp08);

    i_this->actor.speed.x = sp08.x;
    i_this->actor.speed.y += i_this->actor.gravity;
    i_this->actor.speed.z = sp08.z;

    if (i_this->m2A4) {
        fopAcM_posMove(&i_this->actor, i_this->m574.GetCCMoveP());
    } else {
        fopAcM_posMove(&i_this->actor, NULL);
    }

    i_this->m310.SetWall(0.0f, 40.0f);

    if (i_this->m2BE != 1 && i_this->m2BE != 0x65 && i_this->m2B2[1] == 0) {
        i_this->actor.current.pos.y = i_this->actor.current.pos.y + i_this->m2E8;
        i_this->actor.old.pos.y = i_this->actor.old.pos.y + i_this->m2E8;
        i_this->actor.current.pos.y = i_this->actor.current.pos.y - i_this->m2A0;
        i_this->actor.old.pos.y = i_this->actor.old.pos.y - i_this->m2A0;
        i_this->m350.CrrPos(*dComIfG_Bgsp());
        i_this->actor.current.pos.y = i_this->actor.current.pos.y + i_this->m2A0;
        i_this->actor.old.pos.y = i_this->actor.old.pos.y + i_this->m2A0;
        i_this->actor.current.pos.y = i_this->actor.current.pos.y - i_this->m2E8;
        i_this->actor.old.pos.y = i_this->actor.old.pos.y - i_this->m2E8;
    }
    return TRUE;
}

/* 000022A8-000022B0       .text daKanban_IsDelete__FP12kanban_class */
static BOOL daKanban_IsDelete(kanban_class*) {
    return TRUE;
}

/* 000022B0-00002300       .text daKanban_Delete__FP12kanban_class */
static BOOL daKanban_Delete(kanban_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "Kanban");
    i_this->m514.remove();
    l_msgId = -1;
    return 1;
}

/* 00002300-0000249C       .text setTex__FP12J3DModelData */
void setTex(J3DModelData* modelData) {
    J3DTexture* texture = modelData->getTexture();
    if (texture != NULL) {
        JUTNameTab* textureName = modelData->getTextureName();
        if (textureName != NULL) {
            for (u16 i = 0; i < texture->getNum(); i++) {
                static ResTIMG* l_Txi_HamaR0;
                
                const char* pcVar2 = textureName->getName(i);

                if (*pcVar2 == 'T') {
                    l_Txi_HamaR0 = texture->getResTIMG(i);
                } else if (*pcVar2 == 'd') {
                    texture->setResTIMG(i, *l_Txi_HamaR0);
                }
            }
            mDoExt_modelTexturePatch(modelData);
        }
    }
}

/* 0000249C-00002614       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    kanban_class* i_this = (kanban_class*)a_this;

    mDoMtx_stack_c::transS(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z);
    mDoMtx_stack_c::YrotM(i_this->actor.shape_angle.y);
    
    u32 uVar5 = i_this->m294;
    for (s32 i = 0; i < 11; i++, uVar5 >>= 1) {
        if (!i_this->m290 || (uVar5 & 1)) {
            static s32 kanban_bdl[] = {
                KANBAN_BDL_KANBAN, 
                KANBAN_BDL_KANBAN_01,
                KANBAN_BDL_KANBAN_02,
                KANBAN_BDL_KANBAN_03,
                KANBAN_BDL_KANBAN_04,
                KANBAN_BDL_KANBAN_05,
                KANBAN_BDL_KANBAN_06,
                KANBAN_BDL_KANBAN_07,
                KANBAN_BDL_KANBAN_08,
                KANBAN_BDL_KANBAN_09,
                KANBAN_BDL_KANBAN_10,
            };

            J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kanban", kanban_bdl[i]);
            JUT_ASSERT(VERSION_SELECT(1920, 1920, 1919, 1919), modelData != NULL);

            setTex(modelData);

            J3DModel* model = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
            if (model == NULL) {
                return FALSE;
            }
            i_this->m544[i] = model;

            model->setBaseScale(i_this->actor.scale);
            model->setBaseTRMtx(mDoMtx_stack_c::get());

            if (i == 9 || i_this->m290) {
                fopAcM_SetMtx(&i_this->actor, model->getBaseTRMtx());
            }
        }
    }

    return TRUE;
}

/* 00002614-00002A5C       .text daKanban_Create__FP10fopAc_ac_c */
static cPhs_State daKanban_Create(fopAc_ac_c* a_this) {
    static u32 kut_size_dt[] = { 0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0, 0x5C0 };
    static dCcD_SrcCyl cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Unk255_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 0.0f,
            /* Height */ 0.0f,
        }},
    };

    u32 maxHeapSize = 0;
    kanban_class* i_this = (kanban_class*)a_this;

    fopAcM_SetupActor(&i_this->actor, kanban_class);
    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Kanban");

    if (ret == cPhs_COMPLEATE_e) {
        i_this->m294 = fopAcM_GetParam(a_this) >> 0x14;
        a_this->shape_angle = a_this->current.angle;
        i_this->m2D8 = a_this->current.pos;
        i_this->m2F0 = a_this->current.angle;
        i_this->m2F8 = a_this->current.pos;
        i_this->m290 = true;

        if (i_this->m294 == 0) {
            i_this->m290 = false;
            fopAcM_SetStatusMap(a_this, 0x38);
            i_this->m2A4 = 105.0f;
            i_this->m2A8 = 50.0f;
            i_this->m294 = 1;
            maxHeapSize = 0x3F40;
        } else {
            i_this->m2C4 = a_this->current.angle.z;
            a_this->current.angle.z = 0;
            a_this->shape_angle.z = 0;

            u32 idx = i_this->m294;
            for (s32 i = 0; i < 11; i++) {
                if (idx & 1) {
                    maxHeapSize += kut_size_dt[i];
                }
                idx >>= 1;
            }
        }

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, maxHeapSize)) {
            return cPhs_ERROR_e;
        }

        a_this->eyePos.set(a_this->current.pos.x, a_this->current.pos.y + 40.0f, a_this->current.pos.z);

        a_this->attention_info.position.x = a_this->eyePos.x;
        a_this->attention_info.position.y = a_this->eyePos.y + 60.0f;
        a_this->attention_info.position.z = a_this->eyePos.z;

        a_this->attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 5;
        a_this->attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 6;
        a_this->attention_info.flags = fopAc_Attn_TALKFLAG_READ_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
        
        i_this->m350.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->m310,
                        fopAcM_GetSpeed_p(a_this), fopAcM_GetAngle_p(a_this), fopAcM_GetShapeAngle_p(a_this));
        i_this->m310.SetWall(20.0f, 30.0f);

        i_this->m350.SetWaterCheckOffset(300.0f);
        i_this->m574.Init(0xFF, 0, a_this);
        i_this->m5B0.Set(cyl_src);
        i_this->m5B0.SetStts(&i_this->m574);

        if (i_this->m290) {
            i_this->m2C8 = fopAcM_GetLinkId(a_this);
            if (i_this->m2C8 == -1) {
                return cPhs_ERROR_e;
            }

            kanban_class* ac = (kanban_class*)fopAcM_SearchByID(i_this->m2C8);
            if (ac != NULL) {
                i_this->m2F8 = ac->m2F8;
                i_this->m2F0 = ac->m2F0;
                a_this->current.pos = i_this->m2F8;
                a_this->current.pos.y = i_this->m2F8.y - 70.0f;
                i_this->m2CC.y = 70.0f;
                i_this->m2E8 = 140.0f;
                i_this->m304 = i_this->m2CC;
                i_this->m2BE = 100;
                i_this->m2C0 = 0x6e;
            } else {
                return cPhs_ERROR_e;
            }
        } else {
            i_this->m2BE = 0;
            i_this->m2C0 = 10;
        }
    }
    return ret;
}

static actor_method_class l_daKanban_Method = {
    (process_method_func)daKanban_Create,
    (process_method_func)daKanban_Delete,
    (process_method_func)daKanban_Execute,
    (process_method_func)daKanban_IsDelete,
    (process_method_func)daKanban_Draw,
};

actor_process_profile_definition g_profile_KANBAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KANBAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kanban_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KANBAN,
    /* Actor SubMtd */ &l_daKanban_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
