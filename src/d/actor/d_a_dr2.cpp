/**
 * d_a_dr2.cpp
 * NPC - Gohma fight - Valoo (body & tail) + lava pit & ceiling rock
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_dr2.h"
#include "d/res/res_dr2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_btd.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_bg_s_movebg_actor.h"

class daDr2_HIO_c : public JORReflexible {
public:
    daDr2_HIO_c();
    virtual ~daDr2_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
}; // size = 0xC

static daDr2_HIO_c l_HIO;

static f32 hsx[] = { -10.0f, -10.0f, 0.0f, 10.0f, 10.0f, 0.0f };
static f32 hsz[] = { -7.0f, 7.0f, 12.0f, 7.0f, -7.0f, -12.0f };

/* 000000EC-00000110       .text __ct__11daDr2_HIO_cFv */
daDr2_HIO_c::daDr2_HIO_c()  {
    mNo = -1;
    m08 = 1.0f;
}

static BOOL daDr2_ToFore(dr2_class*) {
    return TRUE;
}

static BOOL daDr2_ToBack(dr2_class*) {
    return TRUE;
}

static void anm_init(dr2_class*, int, float, unsigned char, float, int) {
    *(f32*)NULL = 0.0f;
    *(f32*)NULL = -1.0f;
}

/* 00000110-00000380       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    J3DJoint* joint = (J3DJoint*)node;
    
    if (calcTiming == 0) {
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        dr2_class* i_this = (dr2_class*)model->getUserArea();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

            if (i_this->unk_40A == 3) {
                if ((jntNo - 3 <= 8u) || (jntNo == 2)) {
                    cMtx_YrotM(*calc_mtx, i_this->unk_400[jntNo - 0x22]);
                    cMtx_ZrotM(*calc_mtx, i_this->unk_400[jntNo - 0x16]);
                    model->setAnmMtx(jntNo, *calc_mtx);
                    MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
                }
            } else if (i_this->unk_40A == 1) {
                MtxScale(i_this->unk_40C, 1.0f, 1.0f, true);
                model->setAnmMtx(jntNo, *calc_mtx);

                if ((jntNo <= 3u) || (jntNo == 4)) {
                    MtxRotY(i_this->unk_3EC,1);
                    MtxRotZ(i_this->unk_3F0,1);
                    model->setAnmMtx(jntNo, *calc_mtx);
                    MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
                }
            } else if ((jntNo - 5 <= 6u) || (jntNo == 4)) {
                if (i_this->unk_40A == 2) {
                    cMtx_YrotM(*calc_mtx, i_this->unk_3BC[0]);
                    cMtx_ZrotM(*calc_mtx, i_this->unk_3D4[0]);
                } else {
                    MtxRotY(i_this->unk_3EC,1);
                    MtxRotZ(i_this->unk_3F0,1);
                }
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }

            if (jntNo == 11) {
                cXyz sp08;
                sp08.x = REG0_F(0) + 210.0f + 5.0f;
                sp08.y = REG0_F(1);
                sp08.z = REG0_F(2) + -10.0f + 5.0f;
                MtxPosition(&sp08, &i_this->unk_3B0);
            }
        }
    }
    return TRUE;
}

/* 00000380-000003F4       .text hahen_draw__FP9dr2_class */
void hahen_draw(dr2_class* i_this) {
    iwa_hahen_s * fragment = i_this->mRockFragments;
    for (s32 i = 0; i < 6; i++, fragment++) {
        if (fragment->unk_04) {
            g_env_light.setLightTevColorType(fragment->mpModel, &i_this->actor.tevStr);
            mDoExt_modelUpdate(fragment->mpModel);
        }
    }
}

/* 000003F4-0000048C       .text iwa_draw__FP9dr2_class */
void iwa_draw(dr2_class* i_this) {
    if (i_this->unk_4BA < 10) {
        g_env_light.setLightTevColorType(i_this->unk_418, &i_this->actor.tevStr);
        mDoExt_modelUpdateDL(i_this->unk_418);
        if (i_this->unk_424 != 0) {
            J3DModelData* modelData = i_this->unk_41C->getModelData();
            i_this->unk_420->entry(modelData, i_this->unk_420->getFrame());
            g_env_light.setLightTevColorType(i_this->unk_41C, &i_this->actor.tevStr);
            mDoExt_modelUpdateDL(i_this->unk_41C);
        }
    }
    hahen_draw(i_this);
}

/* 0000048C-00000594       .text dr_draw__FP9dr2_class */
void dr_draw(dr2_class* i_this) {
    if (i_this->unk_50C) {
        J3DModel* model = i_this->mpMorf2->getModel();
        mDoMtx_stack_c::transS(0.0f, REG0_F(5) + 10000.0f + 9720.0f, 0.0f);

        cXyz sp08;
        sp08.x = sp08.y = sp08.z = REG0_F(6) + 1.0f;
        model->setBaseScale(sp08);
        model->setBaseTRMtx(mDoMtx_stack_c::get());

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
        g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);

        i_this->mpMorf2->play(NULL, 0, 0);
        i_this->mpMorf2->calc();
        i_this->mpMorf2->entryDL();
    }
}

/* 00000594-0000064C       .text yuka_draw__FP9dr2_class */
void yuka_draw(dr2_class* i_this) {
    J3DModelData* modelData;

    if (!i_this->unk_43C) {
        g_env_light.setLightTevColorType(i_this->unk_428, &i_this->actor.tevStr);
        modelData = i_this->unk_428->getModelData();
        i_this->unk_430->entry(modelData, i_this->unk_430->getFrame());
        mDoExt_modelUpdateDL(i_this->unk_428);
    } else {
        g_env_light.setLightTevColorType(i_this->unk_42C, &i_this->actor.tevStr);
        modelData = i_this->unk_42C->getModelData();
        i_this->unk_434->entry(modelData, i_this->unk_434->getFrame());
        modelData = i_this->unk_42C->getModelData();
        i_this->unk_438->entry(modelData, i_this->unk_438->getFrame());
        mDoExt_modelUpdateDL(i_this->unk_42C);
    }
}

/* 0000064C-000006D4       .text daDr2_Draw__FP9dr2_class */
static BOOL daDr2_Draw(dr2_class* i_this) {
    J3DModel* model = i_this->mpMorf1->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
    i_this->mpMorf1->entryDL();
    iwa_draw(i_this);
    yuka_draw(i_this);
    dr_draw(i_this);
    return TRUE;
}

/* 000006D4-00000720       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* ac1, void* ac2) {
    if (fopAcM_IsActor(ac1) && fopAcM_GetName(ac1) == PROC_BTD) {
        return ac1;
    }
    return NULL;
}

/* 00000720-00000884       .text hahen_move__FP9dr2_class */
void hahen_move(dr2_class* i_this) {
    iwa_hahen_s* fragment = &i_this->mRockFragments[0];

    for (s32 i = 0; i < 6; i++, fragment++) {
        if (fragment->unk_04) {
            fragment->unk_08 += fragment->unk_14;
            if (i & 1) {
                fragment->unk_20.z += REG0_S(4) + 300;
                fragment->unk_20.x += REG0_S(3) + 256;
            } else {
                fragment->unk_20.z -= REG0_S(4) + 300;
                fragment->unk_20.x -= REG0_S(3) + 256;
            }
            fragment->unk_14.y -= REG0_F(7) + 0.5f;
            MtxTrans(fragment->unk_08.x, fragment->unk_08.y, fragment->unk_08.z, false);
            cMtx_YrotM(*calc_mtx, fragment->unk_20.y);
            cMtx_XrotM(*calc_mtx, fragment->unk_20.x);
            cMtx_ZrotM(*calc_mtx, fragment->unk_20.z);

            fragment->mpModel->setBaseTRMtx(*calc_mtx);

            if (fragment->unk_08.y < -100.0f) {
                fragment->unk_04 = false;
            }
        }
    }
}

/* 00000884-0000130C       .text iwa_move__FP9dr2_class */
void iwa_move(dr2_class* i_this) {
    fopAc_ac_c* a_this = &i_this->actor;
    cXyz sp58;
    cXyz sp4C;
    cXyz sp40;

    if (i_this->unk_514 == NULL) {
        i_this->unk_514 = (btd_class*)fpcM_Search(s_a_d_sub, &i_this->actor);
    }
    
    btd_class* btd = i_this->unk_514;
    if (i_this->unk_4CA != 0) {
        i_this->unk_4CA--;
    }

    switch(i_this->unk_4BA) {
        case -1:
            if (std::fabsf(a_this->current.pos.y - a_this->home.pos.y) > 200.0f) {
                i_this->unk_410 = 0.0f;
            }

            if (i_this->unk_4C8 == 0) {
                cLib_addCalc2(&a_this->current.pos.y, a_this->home.pos.y, 0.5f, 30.0f);

                if (std::fabsf(a_this->current.pos.y - a_this->home.pos.y) < 1.0f) {
                    i_this->unk_4BA = 0;
                }
            } else {
                i_this->unk_4C8--;
            }

        case 0:
            cLib_addCalcAngleS2(&i_this->unk_4B4.x, 0, 1, 0x100);
            cLib_addCalcAngleS2(&i_this->unk_4B4.y, 0, 1, 0x100);

            if (i_this->unk_40A == 1 || i_this->unk_4CA != 0) {
                if (i_this->unk_4CC == 0) {
                    i_this->unk_4CC = REG0_S(5) + 3;
                    i_this->unk_4CE = cM_rndFX(REG0_F(7) + 300.0f);
                    i_this->unk_4D0 = cM_rndFX(REG0_F(6) + 20.0f);
                    if (!i_this->unk_50E) {
                        i_this->unk_50D = REG0_S(5) + 1;
                        i_this->unk_50E = true;
                        i_this->unk_510 = 20;
                        fopAcM_seStartCurrent(a_this, JA_SE_CM_BTD_STN_FALL, 0);
                    }
                } else {
                    i_this->unk_4CC--;
                }
            } else {
                i_this->unk_4CE = 0;
                i_this->unk_4D0 = 0.0f;
            }

            cLib_addCalcAngleS2(&i_this->unk_4B4.z, i_this->unk_4CE, 1, REG0_S(6) + 0x100);
            cLib_addCalc2(&i_this->unk_4A8.y, (i_this->unk_4D0 + a_this->home.pos.y) - 50.0f, 0.5f, 50.0f);
            
            if (i_this->unk_4CA == 1) {
                i_this->unk_4BA++;
                i_this->unk_50D = REG0_S(2) + 30;
                i_this->unk_50E = true;
                i_this->unk_510 = 1;
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0B8, &i_this->unk_4A8, &i_this->unk_4B4, NULL, 0xb9, &i_this->unk_4EC, fopAcM_GetRoomNo(a_this));
                fopAcM_seStartCurrent(a_this, JA_SE_CM_BTD_ROCK_FALL, 0);
            }
            break;

        case 1: {
            i_this->unk_4A8.y += a_this->speed.y;
            a_this->speed.y -= REG0_F(2) + 10.0f;

            f32 fVar11 = btd->m02FC[3].y + REG0_F(3);
            if (i_this->unk_4A8.y < fVar11) {
                i_this->unk_4A8.y = fVar11;
                i_this->unk_4BA = 2;
                i_this->unk_400[0] = 0x32;
                btd->m02F6 = true;
                fopAcM_seStartCurrent(a_this, JA_SE_CM_BTD_ROCK_HIT, 0);
                dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
            break;
        }
        case 2:
            i_this->unk_40A = 3;
            cLib_addCalc2(&i_this->unk_414, 2000.0f, 0.5f, 100.0f);

            i_this->unk_4A8.y = btd->m02FC[3].y + REG0_F(3);
            i_this->unk_4B4.y = i_this->unk_514->current.angle.y;
            
            if (btd->m02FC[3].y < REG0_F(6) + 100.0f) {
                i_this->unk_4C0 = (REG0_F(6) + 100.0f) - btd->m02FC[3].y;
                i_this->unk_4C0 *= REG0_F(7) + 0.3f;
            }

            sp4C = btd->m02FC[3] - btd->m02FC[4];
            sp4C.y += REG0_F(5) + -330.0f + i_this->unk_4C0;
            cLib_addCalcAngleS2(&i_this->unk_4B4.x, -cM_atan2s(sp4C.y, std::sqrtf(sp4C.x * sp4C.x + sp4C.z * sp4C.z)), 1, 0x200);

            if (!btd->m02F6) {
                i_this->unk_4BA = 3;
#if VERSION == VERSION_DEMO
                i_this->unk_4D4_demo = 
#endif
                dComIfGp_particle_set(dPa_name::ID_SCENE_80B7, &i_this->unk_4A8, &i_this->unk_4B4, NULL, 0xFF, &i_this->unk_4D8);
                i_this->unk_424 = 1;
            }
            break;

        case 3:
            i_this->unk_4A8.y = btd->m02FC[8].y + 100.0f + REG0_F(9);
            cLib_addCalcAngleS2(&i_this->unk_4B4.x, 0, 1, 0x100);
            cLib_addCalcAngleS2(&i_this->unk_4B4.y, 0, 1, 0x100);

            if (i_this->unk_4A8.y > a_this->home.pos.y - 1200.0f) {
                a_this->current.pos.y += REG0_F(9) + 100.0f;
                i_this->unk_40A = 0;
            }

            if (i_this->unk_4A8.y > a_this->home.pos.y - 50.0f) {
                i_this->unk_4A8.y = a_this->home.pos.y - 50.0f;
                i_this->unk_4BA = -1;
                i_this->unk_4C8 = 0x82;
                a_this->speed.y = 0.0f;
                i_this->unk_4C0 = 0.0f;
#if VERSION == VERSION_DEMO
                if (i_this->unk_4D4_demo != NULL) {
                    i_this->unk_4D4_demo->becomeInvalidEmitter();
                    i_this->unk_4D4_demo = NULL;
                }
#else
                i_this->unk_4D8.remove();
#endif
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0B8, &i_this->unk_4A8, &i_this->unk_4B4, NULL, 0xb9, &i_this->unk_4EC, fopAcM_GetRoomNo(a_this));

                i_this->unk_50D = REG0_S(2) + 10;
                i_this->unk_50E = true;
                i_this->unk_510 = 2;

                dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                fopAcM_seStartCurrent(a_this, JA_SE_CM_BTD_ROCK_ATTACH, 0);
            }
            break;

        case 10: {
            i_this->unk_4BA++;

            iwa_hahen_s* fragment = &i_this->mRockFragments[0];
            for (s32 i = 0; i < 6; i++, fragment++) {
                if (!fragment->unk_04) {
                    fragment->unk_04 = true;
                    fragment->unk_08 = i_this->unk_4A8;
                    fragment->unk_20 = i_this->unk_4B4;
                    cMtx_YrotS(*calc_mtx, fragment->unk_20.y);
                    cMtx_XrotM(*calc_mtx, fragment->unk_20.x);
                    sp58.x = (REG0_F(2) + 3.0f) * hsx[i];
                    sp58.y = 0.0f;
                    sp58.z = (REG0_F(2) + 3.0f) * hsz[i];
                    MtxPosition(&sp58, &fragment->unk_14);
                }
            }
        }
        case 11:
            i_this->unk_40A = 0;
            break;
    }

    switch (i_this->unk_50E) {
        case 1:
            if (i_this->unk_4D4 != NULL) {
                i_this->unk_4D4->becomeInvalidEmitter();
            }

            i_this->unk_4D4 = dComIfGp_particle_set(dPa_name::ID_SCENE_80B9, &i_this->unk_4A8);
            if (i_this->unk_4D4 != NULL) {
                i_this->unk_4D4->setRate(i_this->unk_50D);
                i_this->unk_50E++;
            }
            break;

        case 2:
            if (i_this->unk_510 != 0) {
                i_this->unk_510--;
                if (i_this->unk_510 == 0 
#if VERSION > VERSION_DEMO
                    && i_this->unk_4D4 != NULL
#endif
                ) {
                    i_this->unk_4D4->becomeInvalidEmitter();
                }
            }

#if VERSION > VERSION_DEMO
            if (i_this->unk_4D4 != NULL)
#endif
            {
                if (i_this->unk_4D4->isEnableDeleteEmitter()) {
                    i_this->unk_50E = false;
                    i_this->unk_4D4 = NULL;
                    break;
                }
            }

            JSUList<JPABaseParticle>* list = i_this->unk_4D4->getParticleList();
            JSULink<JPABaseParticle>* link = list->getFirst();
            while (link != list->getEnd()) {
                JGeometry::TVec3<f32> tvec;
                link->getObject()->getGlobalPosition(tvec);
                sp40.x = tvec.x;
                sp40.y = tvec.y;
                sp40.z = tvec.z;
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8062, &sp40, 0xB9);
                link = link->getNext();
            }
            break;
    }

    if (i_this->unk_424 != 0) {
        i_this->unk_420->setFrame(i_this->unk_424);
        i_this->unk_424++;
        if (i_this->unk_424 > 180) {
            i_this->unk_424 = 0;
        }
    }

    hahen_move(i_this);
}

/* 0000130C-0000172C       .text move__FP9dr2_class */
void move(dr2_class* i_this) {
    fopAc_ac_c* a_this = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* foundActor = fopAcM_SearchByID(i_this->unk_3FC);

    if (i_this->unk_40A == 3) {
        for (s32 i = 2; i < 12; i++) {
            i_this->unk_3BC[i] = i_this->unk_414 * cM_ssin(i_this->unk_2BC * 2800 + i * 3000);
            i_this->unk_3D4[i] = i_this->unk_414 * cM_scos(i_this->unk_2BC * 2300 + i * 2000);
        }
    } else {
        i_this->unk_40A = 0;
        if (foundActor != NULL && foundActor->health == 3) {
            cXyz sp30 = player->getLeftHandPos() - foundActor->current.pos;
            cXyz sp24;

            cMtx_YrotS(*calc_mtx, -player->shape_angle.y);
            MtxPosition(&sp30, &sp24);

            s32 atan = cM_atan2s(sp24.z, -sp24.y);
            i_this->actor.current.angle.y = player->shape_angle.y;
            s16 atan2 = atan;
            atan2 *= (REG0_F(3) + -0.125f);
            
            cLib_addCalcAngleS2(&i_this->unk_3BC[0], atan2, 0x10, 0x40);
            cLib_addCalcAngleS2(&i_this->unk_3D4[0], 0, 0x10, 0x40);
            i_this->unk_40A = 2;
        } else if (foundActor != NULL && foundActor->health == 2) {
            i_this->unk_40A = 1;
#if VERSION == VERSION_DEMO
            i_this->actor.current.angle.y = fopAcM_searchPlayerAngleY(&i_this->actor);
#else
            i_this->actor.current.angle.y = fopAcM_searchPlayerAngleY(a_this);
#endif
            player->shape_angle.y = i_this->actor.current.angle.y - -0x8000;
            player->current.angle.y = i_this->actor.current.angle.y - -0x8000;

            cLib_addCalc2(&i_this->unk_3EC, REG0_F(9) + -0.175f, 0.5f, REG0_F(10) + 0.0125f);
            cLib_addCalc0(&i_this->unk_3F0, 0.5f, 0.10000000149011612f);

            if (i_this->unk_3EC < -0.1f) {
                cLib_addCalc2(&i_this->unk_40C, 1.04f, 0.1f, REG0_F(14) + 0.005f);
            }
        } else {
            i_this->unk_40C = 0.98f;
            i_this->actor.current.angle.y = i_this->actor.home.angle.y;

            i_this->unk_3F4 += 0.04f;
            if (i_this->unk_3F4 > 6.2831855f) {
                i_this->unk_3EC -= 6.2831855f;
            }

            i_this->unk_3F8 += 0.05f;
            if (i_this->unk_3F8 > 6.2831855f) {
                i_this->unk_3F0 -= 6.2831855f;
            }

            i_this->unk_3EC = i_this->unk_410 * cM_fsin(i_this->unk_3F4);
            i_this->unk_3F0 = i_this->unk_410 * cM_fsin(i_this->unk_3F8);

            if (foundActor != NULL && foundActor->health == 1) {
                cLib_addCalc2(&i_this->unk_410, 0.0f, 0.5f, 0.001f);
                i_this->unk_4CC = 20;
            } else {
                cLib_addCalc2(&i_this->unk_410, 0.048f, 0.5f, 0.001f);
            }
        }
    }

    i_this->mpMorf1->play(&a_this->eyePos, 0, 0);
    i_this->mpMorf1->calc();
}

/* 0000172C-00001810       .text dr_move__FP9dr2_class */
void dr_move(dr2_class* i_this) {
    if (i_this->unk_4C6 != 0) {
        i_this->unk_4C6--;
    }

    switch (i_this->unk_4C4) {
        case 0:
            if (i_this->unk_50C) {
                i_this->unk_4C6 = 0;
                J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Dr2", DR2_BCK_DR_BOSS_DEMO1);
                i_this->mpMorf2->setAnm(pAnimRes, 0, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
                i_this->unk_4C4 = 1;
            }
            break;

        case 1:
            if (!i_this->unk_50C) {
                i_this->unk_4C4 = false;
            }
            break;

    }
}

/* 00001810-000019B8       .text yuka_move__FP9dr2_class */
void yuka_move(dr2_class* i_this) {
    if (dComIfGs_isStageBossEnemy() 
#if VERSION > VERSION_DEMO
    && (dComIfGp_getStartStageName()[0] != 'X')
#endif
) {
        i_this->unk_43C = true;
        i_this->unk_434->setFrame(299.0f);
        i_this->unk_438->setFrame(299.0f);
    }

    Mtx sp08;
    MTXScale(sp08, REG0_F(9) + 1.0f, REG0_F(9) + 1.0f, REG0_F(9) + 1.0f);

    if (i_this->unk_43C) {
        MtxTrans(0.0f, -10000.0f, 0.0f, false);
    } else {
        MtxTrans(0.0f, 0.0f, 0.0f, false);
        i_this->unk_430->play();
    }

    i_this->unk_428->setBaseTRMtx(*calc_mtx);
    MTXConcat(*calc_mtx, sp08, i_this->unk_440);

    i_this->mpBgW1->Move();
    if (!i_this->unk_43C) {
        MtxTrans(0.0f, -10000.0f, 0.0f, false);
    } else {
        MtxTrans(0.0f, 0.0f, 0.0f, false);
        i_this->unk_434->play();
        i_this->unk_438->play();
    }

    i_this->unk_42C->setBaseTRMtx(*calc_mtx);
    MTXConcat(*calc_mtx, sp08, i_this->unk_470);
    i_this->mpBgW2->Move();
}

/* 000019B8-00001B90       .text daDr2_Execute__FP9dr2_class */
static BOOL daDr2_Execute(dr2_class* i_this) {
    i_this->unk_2BC++;

    for (s32 i = 0; i < 5; i++) {
        if (i_this->unk_400[i] != 0) {
            i_this->unk_400[i]--;
        }
    }

    move(i_this);

    fopAcM_SearchByID(i_this->unk_3FC);
    i_this->actor.scale.x = i_this->actor.scale.y = i_this->actor.scale.z = l_HIO.m08;

    J3DModel* model = i_this->mpMorf1->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
    model->setBaseScale(i_this->actor.scale);
    mDoMtx_stack_c::transS(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z);
    mDoMtx_stack_c::YrotM(i_this->actor.current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    iwa_move(i_this);

    mDoMtx_stack_c::transS(i_this->unk_4A8.x, i_this->unk_4A8.y, i_this->unk_4A8.z);

    mDoMtx_stack_c::YrotM(i_this->unk_4B4.y);
    mDoMtx_stack_c::XrotM(i_this->unk_4B4.x);
    mDoMtx_stack_c::YrotM(i_this->actor.home.angle.y);
    mDoMtx_stack_c::ZrotM(i_this->unk_4B4.z);
    mDoMtx_stack_c::YrotM(-i_this->unk_4B4.y);

    i_this->unk_418->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->unk_41C->setBaseTRMtx(mDoMtx_stack_c::get());

    dr_move(i_this);
    yuka_move(i_this);
    return TRUE;
}

/* 00001B90-00001B98       .text daDr2_IsDelete__FP9dr2_class */
static BOOL daDr2_IsDelete(dr2_class*) {
    return TRUE;
}

/* 00001B98-00001C58       .text daDr2_Delete__FP9dr2_class */
static BOOL daDr2_Delete(dr2_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Dr2");
    mDoHIO_deleteChild(l_HIO.mNo);
    i_this->unk_4D8.remove();
    i_this->unk_4EC.remove();
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&i_this->unk_4A8);
#endif
    dComIfG_Bgsp()->Release(i_this->mpBgW1);
    dComIfG_Bgsp()->Release(i_this->mpBgW2);
    return TRUE;
}

/* 00001C58-00002458       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    dr2_class* i_this = (dr2_class*)a_this;

    i_this->mpMorf1 = new mDoExt_McaMorf((J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BMD_DR_SIPPO), NULL, NULL, NULL, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203);
    
    if ((i_this->mpMorf1 == NULL) || (i_this->mpMorf1->mpModel == NULL)) {
        return FALSE;
    }

    for (u16 i = 0; i < i_this->mpMorf1->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf1->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }
    i_this->mpMorf1->getModel()->setUserArea((u32)i_this);

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BDL_IWA00);
    JUT_ASSERT(DEMO_SELECT(1347, 1361), modelData != NULL);

    i_this->unk_418 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->unk_418 == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BMD_GAN_MAGMA);
    JUT_ASSERT(DEMO_SELECT(1356, 1370), modelData != NULL);

    i_this->unk_41C = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->unk_41C == NULL) {
        return FALSE;
    }

    i_this->unk_420 = new mDoExt_btkAnm();
    if (i_this->unk_420 == NULL) {
        return FALSE;
    }

    J3DAnmTextureSRTKey* srtKey = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dr2", DR2_BTK_GAN_MAGMA);
    BOOL init = i_this->unk_420->init(i_this->unk_41C->getModelData(), srtKey, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
#if VERSION > VERSION_DEMO
    if (!init) {
        return FALSE;
    }
#endif

    for (s32 i = 0; i < 6; i++) {
        static s32 hahen_model[] = { 15, 16, 17, 18, 19, 20 };

        modelData = (J3DModelData*)dComIfG_getObjectRes("Dr2", hahen_model[i]);
        i_this->mRockFragments[i].mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->mRockFragments[i].mpModel == NULL) {
            return FALSE;
        }
    }

    i_this->mpMorf2 = new mDoExt_McaMorf((J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BMD_DR), 
                            NULL, NULL, (J3DAnmTransformKey*)dComIfG_getObjectRes("Dr2", DR2_BCK_DR_BOSS_DEMO1), 
                            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203);

    if (i_this->mpMorf2 == NULL || i_this->mpMorf2->mpModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BMD_MBYO1);
    JUT_ASSERT(DEMO_SELECT(1405, 1429), modelData != NULL);

    i_this->unk_428 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->unk_428 == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Dr2", DR2_BMD_MBYO2);
    JUT_ASSERT(DEMO_SELECT(1412, 1436), modelData != NULL);

    i_this->unk_42C = mDoExt_J3DModel__create(modelData,0,0x11020203);
    if (i_this->unk_42C == NULL) {
        return FALSE;
    }

    i_this->unk_430 = new mDoExt_btkAnm();
    if (i_this->unk_430 == NULL) {
        return FALSE;
    }

    srtKey = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dr2", DR2_BTK_MBYO1);
    if (!i_this->unk_430->init(i_this->unk_428->getModelData(), srtKey, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    i_this->unk_434 = new mDoExt_btkAnm();
    if (i_this->unk_434 == NULL) {
        return FALSE;
    }

    srtKey = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dr2", DR2_BTK_MBYO2);
    if (!i_this->unk_434->init(i_this->unk_42C->getModelData(), srtKey, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    i_this->unk_438 = new mDoExt_brkAnm();
    if (i_this->unk_438 == NULL) {
        return FALSE;
    }

    J3DAnmTevRegKey* tevRegKey = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dr2", DR2_BRK_MBYO2);
    if (!i_this->unk_438->init(i_this->unk_42C->getModelData(), tevRegKey, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    i_this->mpBgW1 = new dBgW();
    if (i_this->mpBgW1 == NULL) {
        return FALSE;
    }

    i_this->mpBgW2 = new dBgW();
    if (i_this->mpBgW2 == NULL) {
        return FALSE;
    }

    cBgD_t* cBgD = (cBgD_t*)dComIfG_getObjectRes("Dr2", DR2_DZB_MBYO1);
    i_this->mpBgW1->Set(cBgD, dBgW::MOVE_BG_e, &i_this->unk_440);
    i_this->mpBgW1->SetCrrFunc(dBgS_MoveBGProc_Typical);

    cBgD = (cBgD_t*)dComIfG_getObjectRes("Dr2", DR2_DZB_MBYO2);
    i_this->mpBgW2->Set(cBgD, dBgW::MOVE_BG_e, &i_this->unk_470);
    i_this->mpBgW2->SetCrrFunc(dBgS_MoveBGProc_Typical);

    return TRUE;
}

/* 000024A0-00002668       .text daDr2_Create__FP10fopAc_ac_c */
static cPhs_State daDr2_Create(fopAc_ac_c* a_this) {
    dr2_class* i_this = (dr2_class*)a_this;

    fopAcM_SetupActor(&i_this->actor, dr2_class);

    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Dr2");
    if (ret == cPhs_COMPLEATE_e) {
        i_this->unk_4EC.setFollowOff();
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0xDFE0)) {
            return cPhs_ERROR_e;
        }

        if (dComIfG_Bgsp()->Regist(i_this->mpBgW1, a_this)) {
            return cPhs_ERROR_e;
        }

        if (dComIfG_Bgsp()->Regist(i_this->mpBgW2, a_this)) {
            return cPhs_ERROR_e;
        }

        l_HIO.mNo = mDoHIO_createChild("ドラゴンシッポ", &l_HIO);
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->base.parameters = 0x511;
        params->room_no = a_this->current.roomNo;

        i_this->unk_3FC = fopAcM_Create(PROC_KUI, NULL, params);
        i_this->unk_4A8.x = a_this->home.pos.x;
        i_this->unk_4A8.y = a_this->home.pos.y + REG0_F(7) - 50.0f;
        i_this->unk_4A8.z = a_this->home.pos.z;
    }
    return ret;
}

static actor_method_class l_daDr2_Method = {
    (process_method_func)daDr2_Create,
    (process_method_func)daDr2_Delete,
    (process_method_func)daDr2_Execute,
    (process_method_func)daDr2_IsDelete,
    (process_method_func)daDr2_Draw,
};

actor_process_profile_definition g_profile_DR2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DR2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dr2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DR2,
    /* Actor SubMtd */ &l_daDr2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
