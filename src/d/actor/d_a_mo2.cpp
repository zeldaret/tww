/**
 * d_a_mo2.cpp
 * Enemy - Moblin / モ２(Mo 2)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mo2.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_kantera.h"
#include "d/actor/d_a_player.h"
#include "d/d_camera.h"
#include "d/d_meter.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_kankyo.h"
#include "d/d_s_play.h"
#include "d/d_material.h"
#include "d/d_snap.h"
#include "d/res/res_mo2.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"

static s32 mo2_set;
static bool hio_set;
static u8 alerm_set;
static u8 rouya_mode; // jail_mode
static s8 camera_mode;
static s8 search_sp;
static mo2HIO_c l_mo2HIO;
static cXyz wind;
static fopAc_ac_c* target_info[10];
static s32 target_info_count;

static u16 mo2_tex_anm_idx[] = {0x0082, 0x0083, 0x0084, 0x0086, 0x0087, 0x0088, 0x0085};
static u16 mo2_tex_max_frame[] = {0x0003, 0x000D, 0x0021, 0x000C, 0x0002, 0x0009, 0x0002};
static dCcG_At_Spl mo2_at_kind[] = {dCcG_At_Spl_UNK0, dCcG_At_Spl_UNK6, dCcG_At_Spl_UNK7, dCcG_At_Spl_UNK0, dCcG_At_Spl_UNK0, dCcG_At_Spl_UNK7};
static dCcG_hitSe mo2_at_sm_kind[] = {dCcG_SE_UNK3, dCcG_SE_UNK3, dCcG_SE_UNK3, dCcG_SE_UNK3, dCcG_SE_UNK3, dCcG_SE_UNK6};
static int mo2_attack_ready_SE[] = {-0xDCF, JA_SE_CV_MO_KAMAE, JA_SE_CV_MO_KAMAE, -0xDCF, -0xDCF, JA_SE_CV_MO_KAMAE}; // TODO what is -0xDCF?
static int mo2_attack_go_SE[] = {JA_SE_CV_MO_JAB, JA_SE_CV_MO_HOOK, JA_SE_CV_MO_HOOK, JA_SE_CV_MO_JAB, JA_SE_CV_MO_JAB, JA_SE_CV_MO_HOOK};
static int mo2_attack_AP[] = {1, 2, 4, 0, 1, 2};
static f32 br_set_tm[] = {-100.0f, 28.0f, 38.0f, -100.0f, -100.0f, -100.0f};

struct attack_info_s {
    /* 0x00 */ int bckFileIdx;
    /* 0x04 */ f32 speed;
    /* 0x08 */ int soundFileIdx;
};

static attack_info_s Atsuki_info[] = {
    {MO2_BCK_ATSUKI01, 1.0f, MO2_BAS_ATSUKI01},
    {MO2_BCK_ATSUKI02, 1.0f, MO2_BAS_ATSUKI02},
    {MO2_BCK_ATSUKI03, 1.0f, MO2_BAS_ATSUKI03},
};

static attack_info_s Atate_info[] = {
    {MO2_BCK_ATATE01, 1.0f, MO2_BAS_ATATE01},
    {MO2_BCK_ATATE02, 1.0f, MO2_BAS_ATATE02},
    {MO2_BCK_ATATE03, 1.0f, MO2_BAS_ATATE03},
};

static attack_info_s Akaiten_info[] = {
    {MO2_BCK_AKAITEN01, 1.0f, MO2_BAS_AKAITEN01},
    {MO2_BCK_AKAITEN02, 1.0f, MO2_BAS_AKAITEN02},
    {MO2_BCK_AKAITEN03, 1.0f, MO2_BAS_AKAITEN03},
};

static attack_info_s Ahazushi_info[] = {
    {MO2_BCK_AHAZUSHI01, 1.0f, MO2_BAS_AHAZUSHI01},
    {MO2_BCK_AHAZUSHI02, 1.0f, MO2_BAS_AHAZUSHI02},
    {MO2_BCK_AHAZUSHI03, 1.0f, MO2_BAS_AHAZUSHI03},
};

static attack_info_s Najab_info[] = {
    {MO2_BCK_NAJAB, 1.0f, MO2_BAS_NAJAB},
    {MO2_BCK_NAJAB, 1.0f, MO2_BAS_NAJAB},
    {MO2_BCK_NAJAB, 1.0f, MO2_BAS_NAJAB},
};

static attack_info_s Nabigpunch_info[] = {
    {MO2_BCK_NABIGPUNCH01, 1.0f, MO2_BAS_NABIGPUNCH01},
    {MO2_BCK_NABIGPUNCH02, 1.0f, MO2_BAS_NABIGPUNCH02},
    {MO2_BCK_NABIGPUNCH03, 1.0f, MO2_BAS_NABIGPUNCH03},
};

static attack_info_s* attack_info[] = {
    Atsuki_info,
    Atate_info,
    Akaiten_info,
    Ahazushi_info,
    Najab_info,
    Nabigpunch_info,
};

static s8 joint_check[] = {
    -1,   -1, 0x0C, 0x13, -1, -1, -1, -1, -1, 0x09, 0x05, 0x01, 0x11, -1,   -1,   -1,   0x08, 0x04, 0x00, 0x10, -1,   -1, 0x14, -1, -1, 0x0D,
    0x12, -1, -1,   0x32, -1, -1, -1, -1, -1, -1,   -1,   -1,   0x0B, 0x07, 0x03, 0x0F, -1,   0x0A, 0x06, 0x02, 0x0E, -1, -1,   -1, -1, -1,
};

static f32 joint_scale_x = 1.0f;
static f32 joint_scale_y = 1.0f;
static f32 joint_scale_z = 1.0f;

/* 000000EC-000001E8       .text tex_anm_set__FP9mo2_classUs */
static void tex_anm_set(mo2_class* i_this, u16 idx) {
    i_this->m02DD = 1;
    i_this->m02DE = mo2_tex_max_frame[idx];
    i_this->m02DC = 0;
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Mo2", mo2_tex_anm_idx[idx]));
    JUT_ASSERT(1019, btp);
    i_this->m02C8.init(i_this->mpMorf->getModel()->getModelData(), btp, 0, 2, 1.0f, 0, -1, true, 0);
}

/* 000001E8-0000031C       .text anm_init__FP9mo2_classifUcfi */
static void anm_init(mo2_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (i_this->m05B0 == 0) {
        if (soundFileIdx >= 0) {
            i_this->mpMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("Mo2", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Mo2", soundFileIdx)
            );
        } else {
            i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Mo2", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    }
}

/* 0000031C-000004B0       .text yari_off_check__FP9mo2_class */
static void yari_off_check(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_48;
    cXyz cStack_54;

    if (i_this->mSpawnWeaponActor != 0) {
        i_this->m05AE = l_mo2HIO.m08A;
        MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x16), *calc_mtx);
        local_48.setall(0.0f);
        MtxPosition(&local_48, &cStack_54);
        i_this->mWeaponPcId = fopAcM_create(PROC_BOKO, daBoko_c::Type_MOBLIN_SPEAR_e, &cStack_54, fopAcM_GetRoomNo(actor));
        i_this->mbThrowWeapon = 1;
        i_this->mSpawnWeaponActorMode = i_this->mSpawnWeaponActor;
        i_this->mSpawnWeaponActor = 0;
        i_this->mbHasInnateWeapon = 0;
    }
    if (i_this->mbThrowWeapon != 0) {
        daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(i_this->mWeaponPcId);
        if ((boko != NULL) && (i_this->mSpawnWeaponActorMode != 2)) {
            boko->setRotAngleSpeed(cM_rndFX(2000.0f));
            s16 angleY = actor->shape_angle.y + 0x8000 + (s16)cM_rndFX(8000.0f);
            f32 speedY = 20.0f + cM_rndF(10.0f);
            f32 speedForward = 20.0f + cM_rndF(10.0f);
            boko->moveStateInit(speedForward, speedY, angleY);
            i_this->mbThrowWeapon = 0;
        }
    }
}

/* 000004EC-000009B8       .text smoke_set_s__FP9mo2_classf */
static void smoke_set_s(mo2_class* i_this, f32 rate) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    s32 attribCode;
    attribCode = 0;
    cXyz startPos = i_this->m05DC;
    startPos.y += 100.0f;
    cXyz endPos = i_this->m05DC;
    endPos.y -= 100.0f;
    linChk.Set(&startPos, &endPos, actor);

    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        endPos = linChk.GetCross();
        i_this->m05DC.y = endPos.y;
        attribCode = dComIfG_Bgsp()->GetAttributeCode(linChk);
    } else {
        i_this->m05DC.y -= 20000.0f;
    }

    if (i_this->m05F3 != 0 && attribCode != dBgS_Attr_GRASS_e) {
        return;
    }

    i_this->m05F3++;

    switch (attribCode) {
    case dBgS_Attr_NORMAL_e:
    case dBgS_Attr_DIRT_e:
    case dBgS_Attr_WOOD_e:
    case dBgS_Attr_STONE_e:
    case dBgS_Attr_SAND_e: {
        i_this->m05F4.remove();
        JPABaseEmitter* emitter1 = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00, &i_this->m05DC, &i_this->m05E8, NULL, l_mo2HIO.m022, &i_this->m05F4, fopAcM_GetRoomNo(actor)
        );
        if (emitter1) {
            emitter1->setRate(rate);
            emitter1->setSpread(1.0f);
            JGeometry::TVec3<f32> scale;
            scale.x = scale.y = scale.z = 1.5f;
            emitter1->setGlobalDynamicsScale(scale);
            scale.x = scale.y = scale.z = 3.6f + REG0_F(11);
            emitter1->setGlobalParticleScale(scale);
        }
        break;
    }
    case dBgS_Attr_GRASS_e:
        JPABaseEmitter* emitter2 = dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTKUSA00, &i_this->m05DC, &i_this->m05E8);
        if (emitter2) {
            emitter2->setRate(rate * 0.5f);
            emitter2->setMaxFrame(3);
        }
        break;
    }
}

/* 00000DF0-000010F8       .text ground_smoke_set__FP9mo2_class */
static void ground_smoke_set(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m05F0 == 0) {
        return;
    }

    i_this->m05F0--;

    if (i_this->m05F0 >= l_mo2HIO.m024) {
        i_this->m05E8.x = 0;
        i_this->m05E8.z = 0;
        cXyz sp8;
        sp8.x = 0.0f;
        sp8.y = 0.0f;
        MtxTrans(actor->current.pos.x, actor->current.pos.y + 7.5f, actor->current.pos.z, 0);
        if (i_this->m05F2 == 0) {
            sp8.z = -350.0f;
            cMtx_YrotM(*calc_mtx, i_this->m05EE);
            MtxPosition(&sp8, &i_this->m05DC);
            i_this->m05E8.y = i_this->m05EE;
            smoke_set_s(i_this, 6.0f);
            i_this->m05EE = i_this->m05EE + 2000 + REG0_S(7);
        } else if (i_this->m05F2 == 1) {
            cMtx_YrotM(*calc_mtx, actor->current.angle.y);
            cMtx_YrotM(*calc_mtx, i_this->m05EE);
            sp8.z = -55.0f;
            MtxPosition(&sp8, &i_this->m05DC);
            i_this->m05E8.y = i_this->m05EE;
            smoke_set_s(i_this, 6.0f);
            i_this->m05EE += 0x1FA0;
        } else if (i_this->m05F2 == 2) {
            MtxTrans(i_this->m2904.x, i_this->m2904.y + 7.5f, i_this->m2904.z, 0);
            cMtx_YrotM(*calc_mtx, i_this->m05EE);
            sp8.z = -12.5f;
            MtxPosition(&sp8, &i_this->m05DC);
            i_this->m05E8.y = i_this->m05EE;
            smoke_set_s(i_this, 6.0f);
            i_this->m05EE += 0x2000;
        } else if (i_this->m05F2 == 3) {
            cMtx_YrotM(*calc_mtx, actor->current.angle.y);
            cMtx_YrotM(*calc_mtx, i_this->m05EE);
            sp8.z = -37.5f;
            MtxPosition(&sp8, &i_this->m05DC);
            i_this->m05E8.y = i_this->m05EE;
            smoke_set_s(i_this, 2.0f);
            i_this->m05EE += 0x1FA0;
        } else if (i_this->m05F2 == 4) {
            if (i_this->m059C & 1) {
                i_this->m05DC = i_this->mDamageReaction.m100[14];
            } else {
                i_this->m05DC = i_this->mDamageReaction.m100[15];
            }
            if (i_this->mDamageReaction.m712 != 0) {
                i_this->m05DC.y = 512.5f;
            } else {
                i_this->m05DC.y -= 12.5f;
            }
            i_this->m05E8.y = cM_atan2s(actor->speed.x, actor->speed.z);
            smoke_set_s(i_this, 1.0f);
        }
    } else {
        i_this->m05DC.y = i_this->mDamageReaction.mSpawnY + 25000.0f;
    }

    if (i_this->m05F0 == 0) {
        i_this->m05F4.remove();
        i_this->m05F3 = 0;
    }
}

/* 000010F8-0000135C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r28 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        mo2_class* i_this = (mo2_class*)model->getUserArea();
        fopAc_ac_c* actor = &i_this->actor;
        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 0x1D) {
                cMtx_ZrotM(*calc_mtx, i_this->m2952);
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else {
                cMtx_YrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].y);
                cMtx_XrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].x);
                cMtx_ZrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].z);

                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);

                cXyz offset;
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                cXyz sp08;
                if (r28 == 0x00 || r28 == 0x01 || r28 == 0x02 || r28 == 0x03 || r28 == 0x04 || r28 == 0x05 || r28 == 0x06 || r28 == 0x07) {
                    offset.x = 0.0f;
                } else if (r28 == 0x12) {
                    offset.x = 200.0f;
                    offset.y = -100.0f;
                    MtxPosition(&offset, &sp08);
                    offset.x = 0.0f;
                    offset.y = 0.0f;
                    MtxPosition(&offset, &actor->eyePos);
                    actor->attention_info.position = actor->eyePos;
                    actor->attention_info.position.y += l_mo2HIO.m028;
                    if (l_mo2HIO.m008 == 0) {
                        i_this->m05D4 = cM_atan2s(sp08.x - actor->eyePos.x, sp08.z - actor->eyePos.z);
                    } else {
                        i_this->m05D4 = actor->current.angle.y;
                    }
                    offset.x = 20.75f;
                    offset.y = 18.5f;
                    offset.z = 0.0f;
                    MtxPosition(&offset, &i_this->m28C8);
                    offset.y = -45.0f;
                }
                MtxPosition(&offset, &i_this->mDamageReaction.m100[r28]);
            }
        }
    }
    return TRUE;
}

/* 0000135C-00001634       .text nodeCallBack_P__FP7J3DNodei */
static BOOL nodeCallBack_P(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r30 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        mo2_class* i_this = (mo2_class*)model->getUserArea();
        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            offset.x = 0.0f;
            offset.z = 0.0f;
            offset.y = 0.0f;
            if (r30 == 0x11) {
                if (i_this->mMode != 100) {
                    offset.x = 17.5f;
                    offset.y = -8.75f;
                    offset.z = 0.0f;
                    MtxPosition(&offset, &i_this->m28EC);
                }
            } else if (r30 == 0x10) {
                if (i_this->mMode != 100) {
                    MtxPosition(&offset, &i_this->m28F8);
                }
            } else if (r30 == 0x14) {
                offset.y = 0.0f;
                if (i_this->mMode != 100) {
                    MtxPosition(&offset, &i_this->m2034);
                }
                offset.x = -50.0f;
                MtxPosition(&offset, &i_this->m28E0);
                offset.x = 165.0f;
                MtxPosition(&offset, &i_this->m2040[0]);
                offset.x = -130.0f;
                MtxPosition(&offset, &i_this->m2040[1]);
                offset.z = 15.0f;
                cXyz cStack_c8;
                for (s32 i = 0; i < 16; i++) {
                    MtxPush();
                    offset.x = (0.25f * (460.0f + (2.0f * (3.5f * (i)) - 28.0f))) - 10.0f;
                    MtxRotX(0.73919827f * i, 0);
                    MtxPosition(&offset, &cStack_c8);
                    MtxPull();
                    MtxPosition(&cStack_c8, &i_this->m0DD8[i].m000[0]);
                }
                i_this->m28D4 = i_this->m0DD8[0].m000[0];
            } else if (r30 == 0x0E || r30 == 0x0F) {
                offset.y = 25.0f;
            } else {
                offset.y = 0.0f;
            }
            MtxPosition(&offset, &i_this->mDamageReaction.m100[r30]);
        }
    }
    return TRUE;
}

/* 00001634-00001A70       .text search_check_draw__FP9mo2_class */
static void search_check_draw(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (l_mo2HIO.m005 == 0) {
        return;
    }
    cXyz sp14[0x10];
    cXyz sp08;
    sp08.x = 0.0f;
    sp08.y = 0.0f;
    sp08.z = l_mo2HIO.m02C;
    int i;
    s16 r26 = 0;
    for (i = 0; i < 16; i++, r26 += 0x1000) {
        MtxTrans(actor->current.pos.x, 2.5f + i_this->mDamageReaction.mSpawnY, actor->current.pos.z, 0);
        cMtx_YrotM(*calc_mtx, r26);
        MtxPosition(&sp08, &sp14[0]);
        cMtx_YrotM(*calc_mtx, 0x1000);
        MtxPosition(&sp08, &sp14[1]);
    }
    sp08.z = l_mo2HIO.m030;
    for (i = 0; i < 16; i++, r26 += 0x1000) {
        MtxTrans(actor->current.pos.x, 2.5f + i_this->mDamageReaction.mSpawnY, actor->current.pos.z, 0);
        cMtx_YrotM(*calc_mtx, (int)r26);
        MtxPosition(&sp08, &sp14[0]);
        cMtx_YrotM(*calc_mtx, 0x1000);
        MtxPosition(&sp08, &sp14[1]);
    }

    sp08.x = 0.0f;
    sp08.z = l_mo2HIO.m02C;
    MtxTrans(actor->current.pos.x, actor->eyePos.y, actor->current.pos.z, 0);

    MtxPush();
    cMtx_YrotM(*calc_mtx, i_this->m05D4 - l_mo2HIO.m038);
    sp08.y = l_mo2HIO.m03C;
    MtxPosition(&sp08, &sp14[1]);
    MtxPull();

    MtxPush();
    sp08.y = l_mo2HIO.m03C;
    cMtx_YrotM(*calc_mtx, i_this->m05D4 + l_mo2HIO.m038);
    MtxPosition(&sp08, &sp14[2]);
    MtxPull();

    MtxPush();
    cMtx_YrotM(*calc_mtx, i_this->m05D4 - l_mo2HIO.m038);
    sp08.y = -l_mo2HIO.m03C;
    MtxPosition(&sp08, &sp14[4]);
    MtxPull();

    sp08.y = -l_mo2HIO.m03C;
    cMtx_YrotM(*calc_mtx, i_this->m05D4 + l_mo2HIO.m038);
    MtxPosition(&sp08, &sp14[5]);

    sp14[0] = actor->current.pos;
    sp14[0].y = actor->eyePos.y + l_mo2HIO.m03C;
    sp14[3] = actor->current.pos;
    sp14[3].y = actor->eyePos.y + l_mo2HIO.m03C;
    sp08.x = 0.0f;
    sp08.z = l_mo2HIO.m030;
    MtxTrans(actor->current.pos.x, actor->eyePos.y, actor->current.pos.z, 0);
    cMtx_YrotM(*calc_mtx, actor->current.angle.y);

    sp08.x = l_mo2HIO.m040.x;
    sp08.y = l_mo2HIO.m040.y;
    sp08.z = l_mo2HIO.m040.z;
    MtxPosition(&sp08, &sp14[7]);
    sp08.y = -l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[5]);
    sp08.x = -l_mo2HIO.m040.x;
    sp08.y = l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[6]);
    sp08.y = -l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[4]);
    sp08.x = l_mo2HIO.m040.x;
    sp08.y = l_mo2HIO.m040.y;
    sp08.z = l_mo2HIO.m04C;
    MtxPosition(&sp08, &sp14[1]);
    sp08.y = -l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[3]);
    sp08.x = -l_mo2HIO.m040.x;
    sp08.y = l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[0]);
    sp08.y = -l_mo2HIO.m040.y;
    MtxPosition(&sp08, &sp14[2]);
}

/* 00001A74-00001F0C       .text ke_control__FP9mo2_classP4ke_si */
static void ke_control(mo2_class* i_this, ke_s* param_2, int param_3) {
    s32 i;
    cXyz* pcVar5 = &param_2->m000[1];
    cXyz* pcVar4 = &param_2->m078[1];
    cXyz local_118;
    cXyz local_124;

    local_118.x = 0.0f;
    local_118.y = 0.0f;
    local_118.z = 21.875f;
    f32 x;
    f32 dVar10;
    f32 f27 = -6.25f;
    dBgS_GndChk local_10c;
    if (l_mo2HIO.m020 == 0) {
        Vec pos;
        pos = *pcVar5;
        pos.y += 75.0f;
        local_10c.SetPos(&pos);
        dVar10 = (dComIfG_Bgsp()->GroundCross(&local_10c) + 2.5f);
        if (dVar10 == -G_CM3D_F_INF) {
            dVar10 = G_CM3D_F_INF;
        }
        if (dVar10 - pcVar5->y > 50.0f) {
            dVar10 = pcVar5->y;
        }
    } else {
        dVar10 = (i_this->mDamageReaction.mSpawnY + 2.5f);
    }
    i = 1;
    for (; i < 10; i++, pcVar5++, pcVar4++) {
        x = wind.x + (pcVar4->x + (pcVar5->x - pcVar5[-1].x));
        f32 dVar8 = pcVar5->y + pcVar4->y + f27;
        f32 z2 = (wind.z + (pcVar5->z + pcVar4->z));
        if (dVar8 < dVar10) {
            dVar8 = dVar10;
        }
        f32 y = dVar8 - pcVar5[-1].y;
        f32 z = z2 - pcVar5[-1].z;
        s16 iVar2 = -cM_atan2s(y, z);
        s32 iVar3 = cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z)));
        cMtx_XrotS(*calc_mtx, iVar2);
        cMtx_YrotM(*calc_mtx, iVar3);
        MtxPosition(&local_118, &local_124);
        *pcVar4 = *pcVar5;
        pcVar5->x = pcVar5[-1].x + local_124.x;
        pcVar5->y = pcVar5[-1].y + local_124.y;
        pcVar5->z = pcVar5[-1].z + local_124.z;
        f32 temp_f29 = param_3 * 0.001f + 0.75f;
        pcVar4->x = temp_f29 * (pcVar5->x - pcVar4->x);
        pcVar4->y = temp_f29 * (pcVar5->y - pcVar4->y);
        pcVar4->z = temp_f29 * (pcVar5->z - pcVar4->z);
    }
}

/* 000020A4-000020E8       .text ke_draw__FP9mo2_classP4ke_si */
static void ke_draw(mo2_class* i_this, ke_s* param_2, int param_3) {
    cXyz* pcVar3 = i_this->m3Dline.getPos(param_3);
    for (s32 i = 0; i < 10; pcVar3++, i++) {
        *pcVar3 = param_2->m000[i];
    }
}

/* 000020E8-000021D8       .text ke_disp__FP9mo2_class */
static void ke_disp(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    ke_s* pkVar2 = i_this->m0DD8;
    cM_initRnd2(0xC, 0x7B, 0x32);
    wind.setall(0.0f);
    for (s32 i = 0; i < 16; i++, pkVar2++) {
        ke_control(i_this, pkVar2, i);
        ke_draw(i_this, pkVar2, i);
    }
#ifdef __MWERKS__
    i_this->m3Dline.update(10, 1.25f, (GXColor){0xFF, 0x64, 0, 0xFF}, 2, &actor->tevStr);
#else
    GXColor local_18 = (GXColor){0xFF, 0x64, 0, 0xFF};
    i_this->m3Dline.update(10, 1.25f, local_18, 2, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->m3Dline);
}

/* 000021D8-0000236C       .text br_draw__FP9mo2_class */
static void br_draw(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m0594 == 0) {
        return;
    }

    J3DModel* model = i_this->m058C;
    for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
        J3DMaterial* mat = model->getModelData()->getJointNodePointer(i)->getMesh();
        while (mat) {
            J3DShape* shape = mat->getShape();
            if (i_this->m0598 == 0) {
                if (i == 1) {
                    shape->show();
                } else {
                    shape->hide();
                }
            } else {
                if (i == 2) {
                    shape->show();
                } else {
                    shape->hide();
                }
            }
            mat = mat->getNext();
        }
    }

    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x16), *calc_mtx);
    MtxTrans(l_mo2HIO.m138 + 150.0f, 0.0f, 0.0f, true);
    cMtx_ZrotM(*calc_mtx, 0x4000);
    MtxScale(l_mo2HIO.m014 * i_this->m0590, l_mo2HIO.m014, l_mo2HIO.m014, true);
    model->setBaseTRMtx(*calc_mtx);

    g_env_light.setLightTevColorType(model, &actor->tevStr);
    mDoExt_modelUpdateDL(model);
}

/* 0000236C-00002418       .text daMo2_shadowDraw__FP9mo2_class */
static void daMo2_shadowDraw(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (!fopAcM_checkCarryNow(actor)) {
        cXyz shadowPos(actor->current.pos.x, actor->current.pos.y + 2.0f + REG0_F(1), actor->current.pos.z);
        i_this->mShadowHandle = dComIfGd_setShadow(
            i_this->mShadowHandle,
            1,
            i_this->mpMorf->getModel(),
            &shadowPos,
            1250.0f,
            50.0f,
            actor->current.pos.y,
            i_this->mDamageReaction.mAcch.GetGroundH(),
            i_this->mDamageReaction.mAcch.m_gnd,
            &actor->tevStr
        );
        ;
    }
}

/* 00002418-0000262C       .text daMo2_Draw__FP9mo2_class */
static BOOL daMo2_Draw(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();
    if (i_this->m02C1 != 0 || i_this->m2970 != 0 || i_this->m2A1C != 0 || (i_this->m2A08 != 0 && i_this->m2A08 != 100)) {
        return TRUE;
    }
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    if (i_this->mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        daMo2_shadowDraw(i_this);
        return TRUE;
    }
    if (i_this->mMode != 100) {
        i_this->m02C8.entry(model->getModelData(), i_this->m02DC);
        if (dScnPly_ply_c::pauseTimer == 0) {
            br_draw(i_this);
        }
        search_check_draw(i_this);
    }
    J3DShape* pJVar1 = model->getModelData()->getMaterialNodePointer(0x03)->getShape();
    if (i_this->mbHasInnateWeapon != 1) {
        pJVar1->hide();
    } else {
        pJVar1->show();
    }
    pJVar1 = model->getModelData()->getMaterialNodePointer(0x00)->getShape();
    if ((REG17_S(1) != 0) || (i_this->m2951 != 0)) {
        pJVar1->hide();
    } else {
        pJVar1->show();
    }
    if (i_this->m2A50 != NULL) {
        i_this->mpMorf->entryDL(i_this->m2A50);
    } else {
        i_this->mpMorf->entryDL();
    }
    if (i_this->mMode != 100) {
        i_this->m02C8.remove(model->getModelData());
    }
    if ((i_this->mbHasInnateWeapon == 1) && (l_mo2HIO.m020 <= 1)) {
        ke_disp(i_this);
    }
    daMo2_shadowDraw(i_this);
    dSnap_RegistFig(DSNAP_TYPE_MO2, actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000262C-00002AD0       .text way_pos_check__FP9mo2_classP4cXyz */
static void way_pos_check(mo2_class* i_this, cXyz* r31) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    dBgS_GndChk gndChk;
    cXyz sp2C;
    cXyz sp20;
    cXyz sp14;
    cXyz sp08;
    sp2C.x = 0.0f;
    sp2C.y = 50.0f;
    sp14 = actor->current.pos;
    sp14.y += 50.0f;
    for (int i = 0; i < 100; i++) {
        sp2C.z = 300.0f + cM_rndF(200.0f);
        MtxRotY(cM_rndF(M_PI * 2), 0);
        MtxPosition(&sp2C, &sp20);
        sp08.x = actor->current.pos.x + sp20.x;
        sp08.y = actor->current.pos.y + sp20.y;
        sp08.z = actor->current.pos.z + sp20.z;
        *r31 = sp08;
        linChk.Set(&sp14, &sp08, actor);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            gndChk.SetPos(&sp08);
            if (i_this->mDamageReaction.mAcch.GetGroundH() - dComIfG_Bgsp()->GroundCross(&gndChk) < 200.0f) {
                break;
            }
        }
    }
}

/* 00002AD0-00002D98       .text ground_4_check__FP9mo2_classisf */
static u8 ground_4_check(mo2_class* i_this, int r18, s16 r20, f32 f29) {
    fopAc_ac_c* actor = &i_this->actor;
    static f32 xad[] = {
        0.0f,
        0.0f,
        1.0f,
        -1.0f,
    };
    static f32 zad[] = {
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
    };
    static u8 check_bit[] = {
        0x01,
        0x02,
        0x04,
        0x08,
    };
    dBgS_GndChk gndChk;
    int i;
    u8 r19 = 0;
    cMtx_YrotS(*calc_mtx, r20);
    cXyz sp14;
    sp14.y = 100.0f;
    for (i = 0; i < r18; i++) {
        sp14.x = xad[i] * f29;
        sp14.z = zad[i] * f29;
        cXyz sp8;
        MtxPosition(&sp14, &sp8);
        sp8 += actor->current.pos;
        gndChk.SetPos(&sp8);
        sp8.y = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (sp8.y == -G_CM3D_F_INF) {
            sp8.y = G_CM3D_F_INF;
        }
        if (i_this->mDamageReaction.mAcch.GetGroundH() - sp8.y > 200.0f) {
            r19 |= check_bit[i];
        }
    }
    return r19;
}

/* 00002D98-00003188       .text daMo2_other_bg_check__FP9mo2_classP10fopAc_ac_c */
static BOOL daMo2_other_bg_check(mo2_class* i_this, fopAc_ac_c* r23) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    if (r23) {
        sp08 = r23->current.pos;
        sp08.y += 50.0f;
        sp14 = actor->current.pos;
        sp14.y = actor->eyePos.y;
        linChk.Set(&sp14, &sp08, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00003188-00003210       .text s_w_sub__FPvPv */
static void* s_w_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BOKO) {
        daBoko_c* boko = (daBoko_c*)param_1;
        if (fopAcM_GetParam(boko) == daBoko_c::Type_MOBLIN_SPEAR_e && !fopAcM_checkCarryNow(boko)) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = boko;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 00003210-000034EC       .text search_wepon__FP9mo2_class */
static s32 search_wepon(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    target_info_count = 0;
    for (int i = 0; i < ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(&s_w_sub, i_this);

    f32 f29 = 50.0f;
    if (target_info_count != 0) {
        fopAc_ac_c* r25;
        int i = 0;
        while (i < target_info_count) {
            r25 = target_info[i];
            cXyz sp18;
            sp18.x = r25->current.pos.x - actor->current.pos.x;
            sp18.y = 50.0f + r25->current.pos.y - actor->eyePos.y;
            sp18.z = r25->current.pos.z - actor->current.pos.z;
            f32 f4 = std::sqrtf(SQUARE(sp18.x) + SQUARE(sp18.z));
            if (f4 < f29 && !daMo2_other_bg_check(i_this, r25)) {
                if (std::fabsf(r25->current.pos.y + 50.0f - actor->eyePos.y) <= l_mo2HIO.m03C) {
                    s16 angleDiff = i_this->m05D4 - cM_atan2s(sp18.x, sp18.z);
                    if (angleDiff < 0) {
                        angleDiff = -angleDiff;
                    }
                    if ((u16)angleDiff < 0x1800) {
                        return fopAcM_GetID(r25);
                    }
                    cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
                    cXyz sp0C;
                    MtxPosition(&sp18, &sp0C);
                    if (std::fabsf(sp0C.x) < l_mo2HIO.m040.x && std::fabsf(sp0C.y) < l_mo2HIO.m040.y && sp0C.z > l_mo2HIO.m04C && sp0C.z < l_mo2HIO.m040.z) {
                        return fopAcM_GetID(r25);
                    }
                }
            }
            i++;
            if (i == target_info_count) {
                i = 0;
                f29 += 50.0f;
                if (f29 > 1500.0f) {
                    return fpcM_ERROR_PROCESS_ID_e;
                }
            }
        }
    } else {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    return fpcM_ERROR_PROCESS_ID_e;
}

/* 000034EC-00003570       .text s_b_sub__FPvPv */
static void* s_b_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BOMB) {
        daBomb_c* bomb = (daBomb_c*)param_1;
        if (!bomb->chk_state(daBomb_c::STATE_0)) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = bomb;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 00003570-00003874       .text search_bomb__FP9mo2_classi */
static fopAc_ac_c* search_bomb(mo2_class* i_this, int r26) {
    fopAc_ac_c* actor = &i_this->actor;
    if (!(i_this->m2960 & 0x0200)) {
        return NULL;
    }

    target_info_count = 0;
    for (int i = 0; i < ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(&s_b_sub, i_this);

    f32 f29 = 50.0f;
    if (target_info_count != 0) {
        fopAc_ac_c* r24;
        int i = 0;
        while (i < target_info_count) {
            r24 = target_info[i];
            cXyz sp28;
            sp28.x = r24->current.pos.x - actor->current.pos.x;
            sp28.y = 50.0f + r24->current.pos.y - actor->eyePos.y;
            sp28.z = r24->current.pos.z - actor->current.pos.z;
            f32 f0 = std::sqrtf(SQUARE(sp28.x) + SQUARE(sp28.z));
            if (f0 < f29 && !(f0 > 30.0f + i_this->m05C0) && !(daMo2_other_bg_check(i_this, r24) && r26)) {
                if (r26) {
                    if (std::fabsf(r24->current.pos.y + 50.0f - actor->eyePos.y) <= l_mo2HIO.m03C) {
                        s16 angleDiff = i_this->m05D4 - cM_atan2s(sp28.x, sp28.z);
                        if (angleDiff < 0) {
                            angleDiff = -angleDiff;
                        }
                        if ((u16)angleDiff < l_mo2HIO.m038) {
                            return r24;
                        }
                        cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
                        cXyz sp10;
                        MtxPosition(&sp28, &sp10);
                        if (std::fabsf(sp10.x) < l_mo2HIO.m040.x && std::fabsf(sp10.y) < l_mo2HIO.m040.y && sp10.z > l_mo2HIO.m04C && sp10.z < l_mo2HIO.m040.z)
                        {
                            return r24;
                        }
                    }
                } else {
                    return r24;
                }
            }
            i++;
            if (i == target_info_count) {
                i = 0;
                f29 += 50.0f;
                if (f29 > 1500.0f) {
                    return NULL;
                }
            }
        }
    } else {
        return NULL;
    }

    return NULL;
}

/* 00003874-000038F0       .text daMo2_wepon_view_check__FP9mo2_class */
static s32 daMo2_wepon_view_check(mo2_class* i_this) {
    if (i_this->m02E2 != 0) {
        return FALSE;
    }
    i_this->mWeaponPcId = search_wepon(i_this);
    if ((i_this->mWeaponPcId != fpcM_ERROR_PROCESS_ID_e) && (fopAcM_SearchByID(i_this->mWeaponPcId) != NULL)) {
        return TRUE;
    }
    return FALSE;
}

/* 000038F0-00003930       .text daMo2_bomb_view_check__FP9mo2_class */
static s32 daMo2_bomb_view_check(mo2_class* i_this) {
    i_this->mpBomb = search_bomb(i_this, 1);
    if (i_this->mpBomb != NULL) {
        return TRUE;
    }
    return FALSE;
}

/* 00003930-00003970       .text daMo2_bomb_check__FP9mo2_class */
static s32 daMo2_bomb_check(mo2_class* i_this) {
    i_this->mpBomb = search_bomb(i_this, 0);
    if (i_this->mpBomb != NULL) {
        return TRUE;
    }
    return FALSE;
}

/* 00003970-00003D10       .text daMo2_player_bg_check__FP9mo2_classP4cXyz */
static s32 daMo2_player_bg_check(mo2_class* i_this, cXyz* r22) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (search_sp != 0) {
        return FALSE;
    }
    if (i_this->mDamageReaction.m713 == 0 && std::fabsf(player->speedF) < 0.1f && player->checkGrabWear()) {
        return 2;
    }
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    sp08 = *r22;
    sp08.y += 75.0f;
    sp14 = actor->current.pos;
    sp14.y = actor->eyePos.y;
    linChk.Set(&sp14, &sp08, actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->mDamageReaction.m713 = 0;
        return TRUE;
    }
    return FALSE;
}

/* 00003D10-00003EC0       .text daMo2_player_view_check__FP9mo2_classP4cXyzss */
static BOOL daMo2_player_view_check(mo2_class* i_this, cXyz* r30, s16 r27, s16 r31) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (search_sp != 0) {
        return TRUE;
    }
    if (daMo2_player_bg_check(i_this, r30)) {
        return FALSE;
    }
    if (std::fabsf(player->current.pos.y + 50.0f - actor->eyePos.y) > l_mo2HIO.m03C) {
        return FALSE;
    }
    s16 angleDiff = i_this->m05D4 - r27;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }
    if ((u16)angleDiff < r31) {
        i_this->mDamageReaction.m713 = 1;
        return TRUE;
    }
    cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
    cXyz sp14;
    sp14.x = r30->x - actor->current.pos.x;
    sp14.y = r30->y - actor->current.pos.y;
    sp14.z = r30->z - actor->current.pos.z;
    cXyz sp08;
    MtxPosition(&sp14, &sp08);
    if (std::fabsf(sp08.x) < l_mo2HIO.m040.x && std::fabsf(sp08.y) < l_mo2HIO.m040.y && sp08.z > l_mo2HIO.m04C && sp08.z < l_mo2HIO.m040.z) {
        i_this->mDamageReaction.m713 = 2;
        return TRUE;
    } else {
        i_this->mDamageReaction.m713 = 0;
        return FALSE;
    }
}

/* 00003EC0-00003F04       .text daMo2_player_way_check__FP9mo2_class */
static s32 daMo2_player_way_check(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar2;

    sVar2 = actor->current.angle.y - dComIfGp_getPlayer(0)->shape_angle.y;
    if (sVar2 < 0) {
        sVar2 = -sVar2;
    }
    if ((u16)sVar2 < 0x4000) {
        return FALSE;
    }
    return TRUE;
}

/* 00003F04-00004040       .text wait_set__FP9mo2_class */
static void wait_set(mo2_class* i_this) {
    if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
        if (i_this->mMode == 1) {
            anm_init(i_this, MO2_BCK_KWAIT, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_KWAIT);
            i_this->m05A4[1] = cM_rndF(100.0f) + 100.0f;
            return;
        }
        anm_init(i_this, MO2_BCK_WAIT, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_WAIT);
        i_this->m05A4[1] = cM_rndF(60.0f) + 40.0f;
        return;
    }
    if (i_this->mDamageReaction.mAction >= mo2_class::Action_FIGHT_RUN_e) {
        anm_init(i_this, MO2_BCK_NBWAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NBWAIT);
    } else {
        anm_init(i_this, MO2_BCK_SKYORO, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_SKYORO);
    }
    i_this->m05A4[1] = cM_rndF(30.0f) + 50.0f;
}

/* 00004040-0000410C       .text walk_set__FP9mo2_class */
static void walk_set(mo2_class* i_this) {
    if (i_this->mbHasInnateWeapon != 0) {
        if (i_this->mMode == 1) {
            anm_init(i_this, MO2_BCK_KWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_KWALK);
            return;
        }
        anm_init(i_this, MO2_BCK_WALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_WALK);
        return;
    }
    if (i_this->m2943 == 0) {
        anm_init(i_this, MO2_BCK_NWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NWALK);
    } else {
        anm_init(i_this, MO2_BCK_NYWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NYWALK);
    }
}

/* 0000410C-00004170       .text fight_run_set__FP9mo2_class */
static void fight_run_set(mo2_class* i_this) {
    if (i_this->mbHasInnateWeapon != 0) {
        anm_init(i_this, MO2_BCK_WALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, MO2_BAS_WALK);
    } else {
        anm_init(i_this, MO2_BCK_SWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_SWALK);
    }
}

/* 00004170-000045F8       .text path_check__FP9mo2_class */
static void path_check(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    static u8 check_index[255];
    cXyz local_c8;
    cXyz local_d4;

    if ((i_this->ppd != NULL) && (i_this->mbHasInnateWeapon != 0 || (i_this->m2943 != 0))) {
        dBgS_LinChk chk;
        local_c8 = actor->current.pos;
        local_c8.y += REG13_F(0) + 10.0f;
        dPnt* point = &i_this->ppd->m_points[0];
        for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
            local_d4.x = point->m_position.x;
            local_d4.y = (10.0f + point->m_position.y) + REG13_F(1);
            local_d4.z = point->m_position.z;
            chk.Set(&local_c8, &local_d4, actor);
            if (!dComIfG_Bgsp()->LineCross(&chk)) {
                check_index[i] = 1;
            } else {
                check_index[i] = 0;
            }
        }

        f32 fDist = 100.0f;
        bool r7 = false;

        for (s32 j = 0; j < 100; j++) {
            point = &i_this->ppd->m_points[0];

            for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
                if (check_index[i] != 0) {
                    f32 x = actor->current.pos.x - point->m_position.x;
                    f32 y = actor->current.pos.y - point->m_position.y;
                    f32 z = actor->current.pos.z - point->m_position.z;

                    if (std::sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z)) < fDist) {
                        i_this->m2969 = i - (u8)i_this->mHasPath;
                        if (i_this->m2969 >= (s8)i_this->ppd->m_num) {
                            i_this->m2969 = i_this->ppd->m_num;
                        } else if (i_this->m2969 < 0) {
                            i_this->m2969 = 0;
                        }
                        r7 = true;
                        break;
                    }
                }
            }

            if (r7) {
                break;
            }

            fDist += 50.0f;
        }
        if (!r7) {
            i_this->m2968 = 0;
        } else {
            i_this->m2968 = i_this->mPathIndex + 1;
        }
    }
}

/* 000045F8-00004898       .text path_check2__FP9mo2_class */
static void path_check2(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_9c;
    cXyz local_a8;
    dBgS_LinChk local_90;

    local_9c = actor->current.pos;
    local_9c.y += REG13_F(2) + 20.0f;
    local_a8 = i_this->m05C4;
    local_a8.y += REG13_F(3) + 10.0f;
    local_90.Set(&local_9c, &local_a8, actor);
    if (dComIfG_Bgsp()->LineCross(&local_90)) {
        i_this->m2968 = 0;
    }
}

/* 00004898-00004DEC       .text attack_set__FP9mo2_classUc */
static void attack_set(mo2_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar7;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->m2060 = 0;
    i_this->m2941 = 0;
    i_this->m2954 = fpcM_ERROR_PROCESS_ID_e;
    i_this->m2942 = 0;
    i_this->m2068 = 0.0f;
    i_this->m05A4[4] = 0;
    dVar7 = cM_rndF(100.0f);
    i_this->mWeaponSph.SetR(100.0f);
    if (i_this->mbHasInnateWeapon != 0) {
        if (((player->checkPlayerGuard()) && (cM_rndF(1.0f) < 0.5f)) && (param_2 == 0)) {
            i_this->m2060 = 3;
            i_this->m206C = 9.0f;
            i_this->m2070 = 16.0f;
            i_this->m2074 = 0.0f;
            i_this->m2078 = l_mo2HIO.m0D2;
        } else if (param_2 == 2) {
            i_this->m2060 = 2;
            i_this->m206C = 36.0f;
            i_this->m2070 = 52.0f;
            i_this->m2074 = 75.0f;
            i_this->m2078 = l_mo2HIO.m0D0;
        } else if (param_2 == 1) {
            i_this->m2060 = 1;
            i_this->m206C = 26.0f;
            i_this->m2070 = 34.0f;
            i_this->m2074 = 59.0f;
            i_this->m2078 = l_mo2HIO.m0CE;
        } else if (daMo2_player_way_check(i_this)) {
            if (dVar7 < l_mo2HIO.m07C) {
                i_this->m2060 = 0;
                i_this->m206C = 17.0f;
                i_this->m2070 = 27.0f;
                i_this->m2074 = 10.0f;
                i_this->m2078 = l_mo2HIO.m0CC;
            } else if ((dVar7 - l_mo2HIO.m07C) < l_mo2HIO.m080) {
                i_this->m2060 = 1;
                i_this->m206C = 26.0f;
                i_this->m2070 = 36.0f;
                i_this->m2074 = 59.0f;
                i_this->m2078 = l_mo2HIO.m0CE;
            } else {
                i_this->m2060 = 2;
                i_this->m206C = 36.0f;
                i_this->m2070 = 52.0f;
                i_this->m2074 = 75.0f;
                i_this->m2078 = l_mo2HIO.m0D0;
            }
        } else {
            i_this->m2060 = 2;
            i_this->m206C = 36.0f;
            i_this->m2070 = 52.0f;
            i_this->m2074 = 75.0f;
            i_this->m2078 = l_mo2HIO.m0D0;
        }
    } else if (dVar7 < l_mo2HIO.m084) {
        i_this->mWeaponSph.SetR(50.0f);
        i_this->m2060 = 4;
        i_this->m206C = 3.0f;
        i_this->m2070 = 8.0f;
        i_this->m2074 = 0.0f;
        i_this->m2078 = l_mo2HIO.m0D4;
    } else {
        i_this->m2060 = 5;
        i_this->m206C = 32.0f;
        i_this->m2070 = 39.0f;
        i_this->m2074 = 0.0f;
        i_this->m2078 = l_mo2HIO.m0D6;
    }
    i_this->m207E = 1;
    i_this->m2064 = 0;
    attack_info_s* info = attack_info[i_this->m2060];
    anm_init(i_this, info->bckFileIdx, 5.0f, J3DFrameCtrl::EMode_NONE, info->speed, info->soundFileIdx);
    if (mo2_attack_ready_SE[i_this->m2060] != -0xDCF) {
        fopAcM_monsSeStart(actor, mo2_attack_ready_SE[i_this->m2060], 0);
    }
    if (i_this->m2060 == 1) {
        i_this->m2946 = l_mo2HIO.m144;
        i_this->m2948 = l_mo2HIO.m146;
        i_this->m294A = l_mo2HIO.m148;
        i_this->m294C = l_mo2HIO.m14A;
        i_this->m2944 = 0;
        i_this->mParryOpeningType = fopEn_enemy_c::OPENING_ROLL_PARRY;
    } else if (i_this->m2060 == 2) {
        i_this->m2946 = l_mo2HIO.m14C;
        i_this->m2948 = l_mo2HIO.m14E;
        i_this->m294A = l_mo2HIO.m150;
        i_this->m294C = l_mo2HIO.m152;
        i_this->m2944 = 0;
        i_this->mParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
    } else if (i_this->m2060 == 5) {
        i_this->m2946 = l_mo2HIO.m154;
        i_this->m2948 = l_mo2HIO.m156;
        i_this->m294A = l_mo2HIO.m158;
        i_this->m294C = l_mo2HIO.m15A;
        i_this->m2944 = 0;
        i_this->mParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
    }
}

/* 00004DEC-00005734       .text jyunkai__FP9mo2_class */
static void jyunkai(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int pathIndex;
    dPath* pdVar3;
    SND_INFLUENCE* sound;
    s16 maxSpeed;
    f32 dVar12;
    f32 fVar13;
    int weaponPcId;
    cXyz local_3c;

    weaponPcId = i_this->mWeaponPcId;
    fopAcM_SearchByID(weaponPcId);
    i_this->mCoCyl.SetR(REG0_F(4) + 40.0f);
    switch (i_this->mDamageReaction.mMode) {
    case -10:
        i_this->m05A4[1] = 0x3c;
        i_this->mDamageReaction.mMode = -9;
        // Fall-through
    case -9:
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mMode = 2;
        }
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] > 0x1e) {
            return;
        }
        break;
    case 0:
        walk_set(i_this);
        // Fall-through
    case -1: {
        i_this->mDamageReaction.mMode = 1;
        if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
            if (i_this->m2968 != 0) {
                i_this->m2969 = i_this->m2969 + i_this->mHasPath;
                if (i_this->m2969 >= (s8)i_this->ppd->m_num) {
                    if ((i_this->ppd->m_closed & 1) != 0) {
                        i_this->m2969 = 0;
                    } else {
                        i_this->mHasPath = 0xff;
                        i_this->m2969 = i_this->ppd->m_num - 2;
                    }
                    pathIndex = (uint)i_this->ppd->m_nextID;
                    if (pathIndex != 0xffff) {
                        pdVar3 = dPath_GetRoomPath(pathIndex, fopAcM_GetRoomNo(actor));
                        i_this->ppd = pdVar3;
                        JUT_ASSERT(3535, i_this->ppd != NULL);
                    }
                } else if (i_this->m2969 < 0) {
                    i_this->mHasPath = 1;
                    i_this->m2969 = 1;
                }
                dPnt* point = &i_this->ppd->m_points[i_this->m2969];
                i_this->m05C4 = point->m_position;
            } else {
                way_pos_check(i_this, &i_this->m05C4);
            }
        } else {
            way_pos_check(i_this, &i_this->m05C4);
            i_this->m05A4[1] = cM_rndF(25.0f) + 30.0f;
        }
        i_this->m05A4[2] = 0x1e;
        // Fall-through
    }
    case 1: {
        if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
            maxSpeed = 0x400;
            dVar12 = l_mo2HIO.m050;
        } else {
            maxSpeed = 0x1000;
            dVar12 = l_mo2HIO.m054;
        }
        local_3c.x = i_this->m05C4.x - actor->current.pos.x;
        local_3c.z = i_this->m05C4.z - actor->current.pos.z;
        i_this->mDamageReaction.m4D0 = cM_atan2s(local_3c.x, local_3c.z);
        if ((i_this->m2968 != 0) && (i_this->mbHasInnateWeapon != 0 || (i_this->m2943 != 0))) {
            fVar13 = std::sqrtf(SQUARE(local_3c.x) + SQUARE(local_3c.z));
            if (fVar13 < (dVar12 * 0.25f) * 15.0f) {
                dPnt* point = i_this->ppd->m_points;
                point = &point[i_this->m2969];
                if (((point->mArg3 == 3) || (point->mArg3 == 7)) || (point->mArg3 == 8)) {
                    wait_set(i_this);
                    if (point->mArg3 >= 7) {
                        i_this->m05A4[1] = cM_rndF(80.0f) + 70.0f;
                    }
                    i_this->mDamageReaction.mMode = 2;
                } else {
                    i_this->mDamageReaction.mMode = -1;
                }
            }
            path_check2(i_this);
            if (((i_this->mCoCyl.ChkCoHit()) || (i_this->mDamageReaction.mAcch.ChkWallHit())) && (i_this->m05A4[2] == 0)) {
                wait_set(i_this);
                i_this->m05A4[1] = cM_rndF(80.0f) + 70.0f;
                i_this->mHasPath *= -1;
                i_this->mDamageReaction.mMode = 2;
            }
        } else {
            fVar13 = std::sqrtf(SQUARE(local_3c.x) + SQUARE(local_3c.z));
            if ((fVar13 < (dVar12 * 0.25f) * 2.0f) ||
                (i_this->m05A4[2] == 0 && ((i_this->mDamageReaction.mAcch.ChkWallHit()) || (ground_4_check(i_this, 1, actor->current.angle.y, 200.0f)))))
            {
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
        }
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, maxSpeed);
        cLib_addCalc2(&actor->speedF, dVar12, 1.0f, 5.0f);
        break;
    }
    case 2: {
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] == 0) {
            if ((i_this->m2968 != 0) && (i_this->mbHasInnateWeapon != 0 || (i_this->m2943 != 0))) {
                dPnt* point = i_this->ppd->m_points;
                point = &point[i_this->m2969];
                if ((point->mArg3 == 7) || (point->mArg3 == 8)) {
                    i_this->mDamageReaction.mMode = 4;
                    i_this->m05A4[1] = cM_rndF(100.0f) + 100.0f;
                    anm_init(i_this, MO2_BCK_KKEIKAI, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_KKEIKAI);
                    if (point->mArg3 == 7) {
                        i_this->mDamageReaction.m4D0 += -0x4000;
                    } else {
                        i_this->mDamageReaction.m4D0 += 0x4000;
                    }
                    break;
                }
            }
            i_this->mDamageReaction.mMode = 0;
            if ((i_this->mPathIndex != 0xFF) && (i_this->m2968 == 0)) {
                path_check(i_this);
            }
            if (((i_this->mbHasInnateWeapon == 0) && (i_this->m2943 == 0)) && (i_this->m05AE == 0)) {
                i_this->m2943 = 1;
            }
        }
        break;
    }
    case 4:
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
        // Fall-through
    case 3: {
        actor->speedF = 0.0f;
        int frame = i_this->mpMorf->getFrame();
        if ((frame == 3) || (frame == 0x35)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_SEARCH, 0);
        }
        if (((i_this->m05A4[1] == 0) && (i_this->mDamageReaction.mMode = 0, i_this->mPathIndex != 0xFF)) && (i_this->m2968 == 0)) {
            path_check(i_this);
        }
        break;
    }
    }
    int iVar6 = fopAcM_otoCheck(actor, 1000.0f);
    iVar6 += search_sp;
    if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
        if ((iVar6 != 0) ||
            (i_this->m05C0 < l_mo2HIO.m02C && (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038) != 0)))
        {
            if (i_this->mMode == 1) {
                i_this->mDamageReaction.mAction = mo2_class::Action_NAGE_e;
                if (rouya_mode != 0) {
                    i_this->mDamageReaction.mMode = -10;
                } else {
                    i_this->mDamageReaction.mMode = 0;
                }
                if (iVar6 != 0) {
                    sound = dKy_Sound_get();
                    i_this->m2A10 = sound->field_0x0;
                    i_this->m2A0C = 0x1e;
                }
            } else {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                i_this->m05A4[1] = 0;
                i_this->mDamageReaction.mMode = 0;
            }
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_FIND_ENEMY, 0);
        }
    } else if ((i_this->m2943 == 0) && (i_this->mDamageReaction.mMode == 2)) {
        int frame = i_this->mpMorf->getFrame();
        if (((frame == 0xb) || (frame == 0x19)) && (cM_rndF(1.0f) < 0.5f)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_LOSE_LANCE, 0);
        }
    }
    if ((i_this->mbHasInnateWeapon == 0) && (daMo2_wepon_view_check(i_this))) {
        i_this->mDamageReaction.mAction = mo2_class::Action_WEPON_SEARCH_e;
        i_this->mDamageReaction.mMode = -1;
    }
    if (daMo2_bomb_view_check(i_this)) {
        i_this->mDamageReaction.mAction = mo2_class::Action_B_NIGE_e;
        i_this->mDamageReaction.mMode = 0;
    }
}

/* 00005734-000060F8       .text fight_run__FP9mo2_class */
static void fight_run(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 target;
    s16 maxSpeed;
    f32 dVar9;
    f32 fVar10;

    dVar9 = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    i_this->mDamageReaction.m4D0 = i_this->m05D6;
    if ((i_this->m05B0 == 0) && (i_this->mDamageReaction.mMode != 0)) {
        maxSpeed = 0x400;
        if (i_this->mDamageReaction.mMode == 1) {
            maxSpeed = 0x800;
        }
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, maxSpeed);
    }
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        if (i_this->m05A4[1] == 0) {
            fight_run_set(i_this);
            i_this->mDamageReaction.mMode = 1;
            i_this->m2964 = 0;
        } else {
            actor->speedF = 0.0f;
            break;
        }
    case 1:
        fVar10 = 20.0f;
        if (i_this->m2964 != 0) {
            target = l_mo2HIO.m06C;
            i_this->m05F0 = l_mo2HIO.m024 + 4;
            i_this->m05F2 = 4;
        } else {
            if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                target = l_mo2HIO.m058;
            } else {
                target = l_mo2HIO.m05C;
            }
            fVar10 = 5.0f;
        }
        cLib_addCalc2(&actor->speedF, target, 1.0f, fVar10);
        if (daMo2_player_way_check(i_this)) {
            if (i_this->m2964 > 0x14) {
                i_this->m2964 = 0;
                anm_init(i_this, MO2_BCK_GAKEDEMO, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m05B0 = cM_rndF(10.0f) + 15.0f;
            }
            if (i_this->m05B0 == 1) {
                i_this->m05B0 = 0;
                fight_run_set(i_this);
            }
            if ((i_this->m05B0 == 0) && (i_this->m05C0 < l_mo2HIO.m030)) {
                i_this->mDamageReaction.mMode = 2;
                i_this->m05A4[4] = 0x32;
            }
        } else {
            if ((i_this->m2964 == 0) && (i_this->mbHasInnateWeapon != 0)) {
                i_this->m2964 = 1;
                anm_init(i_this, MO2_BCK_DASH, 5.0f, J3DFrameCtrl::EMode_LOOP, l_mo2HIO.m070, MO2_BAS_DASH);
            }
            if (i_this->m2964 != 0) {
                i_this->m2964 = i_this->m2964 + 1;
            }
            if ((i_this->m05B0 == 0) && (i_this->m05C0 < l_mo2HIO.m034)) {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_e;
                i_this->mDamageReaction.mMode = 0;
                return;
            }
        }
        break;
    case 2:
        i_this->m2964 = 0;
        fVar10 = cM_rndF(1.0f);
        if ((fVar10 < 0.3f) && (i_this->mbHasInnateWeapon == 0)) {
            i_this->mDamageReaction.mMode = 8;
            wait_set(i_this);
            fVar10 = cM_rndF(20.0f);
            i_this->m05A4[1] = (s16)(int)(fVar10 + 20.0f);
        } else {
            if (std::fabsf(dVar9) > 0.1f) {
                if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                    anm_init(i_this, MO2_BCK_BWALKLR, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_BWALKLR);
                } else {
                    anm_init(i_this, MO2_BCK_NBWALKLR, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NBWALKLR);
                }
                if (dVar9 > 0.0f) {
                    i_this->mDamageReaction.mMode = 5;
                } else {
                    i_this->mDamageReaction.mMode = 6;
                }
            } else {
                if (i_this->m05C0 < l_mo2HIO.m034) {
                    if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                        anm_init(i_this, MO2_BCK_BWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, -1.0f, MO2_BAS_BWALKFB);
                    } else {
                        anm_init(i_this, MO2_BCK_NBWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, -1.0f, MO2_BAS_NBWALKFB);
                    }
                    i_this->mDamageReaction.mMode = 4;
                } else {
                    if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                        anm_init(i_this, MO2_BCK_BWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_BWALKFB);
                    } else {
                        anm_init(i_this, MO2_BCK_NBWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NBWALKFB);
                    }
                    i_this->mDamageReaction.mMode = 3;
                }
            }
            i_this->m05A4[1] = (s16)(int)(cM_rndF(20.0f) + 20.0f);
        }
        break;
    case 3:
        cLib_addCalc2(&actor->speedF, l_mo2HIO.m064, 1.0f, 20.0f);
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mMode = 2;
        }
        break;
    case 4:
        if (i_this->m05BF != 2) {
            cLib_addCalc2(&actor->speedF, -l_mo2HIO.m064, 1.0f, 20.0f);
            if (i_this->m05A4[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
            }
        } else {
            i_this->mDamageReaction.mMode = 3;
            if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                anm_init(i_this, MO2_BCK_BWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_BWALKFB);
            } else {
                anm_init(i_this, MO2_BCK_NBWALKFB, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NBWALKFB);
            }
        }
        break;
    case 5:
        if (i_this->m05BF != 4) {
            i_this->m05D8 = 0x4000;
        } else {
            i_this->mDamageReaction.mMode = 6;
            i_this->m05D8 = -0x4000;
        }
        goto LAB_806ac350;
    case 6:
        if (i_this->m05BF != 8) {
            i_this->m05D8 = -0x4000;
        } else {
            i_this->mDamageReaction.mMode = 5;
            i_this->m05D8 = 0x4000;
        }
    LAB_806ac350:
        cLib_addCalc2(&actor->speedF, l_mo2HIO.m068, 1.0f, 30.0f);
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mMode = 2;
        }
        break;
    case 8:
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mMode = 2;
        }
    }
    if ((i_this->mDamageReaction.mMode >= 3) && (i_this->m05BA <= 2)) {
        if (i_this->m05C0 > l_mo2HIO.m030 + 75.0f) {
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 0;
        }
        if (((i_this->m05C0 < l_mo2HIO.m034 + 62.5f) && (i_this->m05C0 > l_mo2HIO.m034 - 62.5f)) && (i_this->m05A4[4] == 0)) {
            i_this->m05A4[4] = l_mo2HIO.m074;
            fVar10 = cM_rndF(100.0f);
            if (fVar10 < l_mo2HIO.m078) {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_e;
                i_this->mDamageReaction.mMode = 0;
            }
        }
        if (i_this->m05B6 == 0) {
            dAttention_c& attention = dComIfGp_getAttention();
            if ((i_this->mbHasInnateWeapon != 0) && (player->getCutType() != 0 && ((cc_pl_cut_bit_get() & i_this->m2960) != 0))) {
                if ((attention.Lockon()) && (actor == attention.LockonTarget(0))) {
                    i_this->mDamageReaction.mAction = mo2_class::Action_DEFENCE_e;
                    i_this->mDamageReaction.mMode = 0;
                }
            }
        }
    }
    if (((i_this->mbHasInnateWeapon != 0) && (i_this->m05C0 < l_mo2HIO.m034 - 62.5f)) &&
        (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038)))
    {
        i_this->m05A0++;
        if ((i_this->m05A0 >= 0xF) && (cM_rndF(1.0f) < 0.5f)) {
            i_this->m05A0 = 0;
            i_this->mDamageReaction.mAction = mo2_class::Action_OSHI_e;
            i_this->mDamageReaction.mMode = 0;
        }
    } else {
        i_this->m05A0 = 0;
    }
    if (daMo2_player_bg_check(i_this, &i_this->mDamageReaction.m714->current.pos)) {
        i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = -10;
    }
    if ((i_this->mbHasInnateWeapon == 0) && (daMo2_wepon_view_check(i_this))) {
        i_this->mDamageReaction.mAction = mo2_class::Action_WEPON_SEARCH_e;
        i_this->mDamageReaction.mMode = -1;
    }
    if (daMo2_bomb_view_check(i_this)) {
        i_this->mDamageReaction.mAction = mo2_class::Action_B_NIGE_e;
        i_this->mDamageReaction.mMode = 0;
    }
    i_this->m05BF = ground_4_check(i_this, 4, actor->current.angle.y, REG6_F(7) + 90.0f);
    if (i_this->m05BA != 0) {
        if (std::fabsf(actor->speedF) < 30.0f) {
            if (i_this->m05BE == 0) {
                i_this->mDamageReaction.m710 = 3;
            } else if (i_this->m05BE == 1) {
                i_this->mDamageReaction.m710 = 4;
            } else if ((i_this->m059C & 0x10) != 0) {
                i_this->mDamageReaction.m710 = 3;
            } else {
                i_this->mDamageReaction.m710 = 4;
            }
            cLib_addCalcAngleS2(&i_this->m2952, 12000, 2, 0x1800);
        } else {
            i_this->mDamageReaction.m710 = 1;
        }
    } else {
        i_this->mDamageReaction.m710 = 1;
        if (i_this->m05BC == 0) {
            i_this->m05BC = cM_rndF(100.0f) + 30.0f;
            if (i_this->m05BF == 4) {
                i_this->m05BE = 0;
                i_this->m05BA = 0x10;
            } else if (i_this->m05BF == 8) {
                i_this->m05BE = 1;
                i_this->m05BA = 0x10;
            } else if (i_this->m05BF == 2) {
                i_this->m05BE = 2;
                i_this->m05BA = 0x20;
            }
        }
    }
}

/* 000060F8-0000645C       .text yari_hit_check__FP9mo2_class */
static fopAc_ac_c* yari_hit_check(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* pcVar2;

    i_this->m2940 = 0;
    i_this->m291C = i_this->m2904;
    i_this->mWeapon2Sph.SetR(0.0f);
    if (i_this->m207E < 0) {
        return NULL;
    }
    if (i_this->m2060 == 5) {
        i_this->m2904 = i_this->m28F8;
    } else if ((i_this->m2060 == 3) || (i_this->m2060 == 4)) {
        i_this->m2904 = i_this->m28EC;
    } else {
        i_this->m2904 = i_this->m28D4;
        i_this->m2910 = i_this->m28E0;
        i_this->mWeapon2Sph.SetR(62.5f);
    }
    if (i_this->m207C != 0) {
        i_this->m207C--;
        return NULL;
    }
    if ((i_this->m2068 < i_this->m206C) || (i_this->m2068 > i_this->m2070)) {
        return NULL;
    }
    i_this->m2940 <<= 1;
    i_this->mWeaponSph.SetAtSpl(mo2_at_kind[i_this->m2060]);
    i_this->mWeapon2Sph.SetAtSpl(mo2_at_kind[i_this->m2060]);
    i_this->mWeaponSph.SetAtSe(mo2_at_sm_kind[i_this->m2060]);
    i_this->mWeapon2Sph.SetAtSe(mo2_at_sm_kind[i_this->m2060]);
    if ((i_this->m2060 == 2) || (i_this->m2060 == 1) || (i_this->m2060 == 5)) {
        i_this->mWeaponSph.SetAtType(AT_TYPE_UNK8);
        i_this->mWeapon2Sph.SetAtType(AT_TYPE_UNK8);
    } else {
        i_this->mWeaponSph.SetAtType(AT_TYPE_UNK800);
        i_this->mWeapon2Sph.SetAtType(AT_TYPE_UNK800);
    }
    if ((int)i_this->m2068 == (int)i_this->m206C) {
        fopAcM_monsSeStart(actor, mo2_attack_go_SE[i_this->m2060], 0);
    }
    if (i_this->m2941 == 0) {
        i_this->m2941++;
        i_this->mWeaponSph.StartCAt(i_this->m2904);
        i_this->mWeapon2Sph.StartCAt(i_this->m2910);
    } else {
        i_this->mWeaponSph.MoveCAt(i_this->m2904);
        i_this->mWeapon2Sph.MoveCAt(i_this->m2910);
        dComIfG_Ccsp()->Set(&i_this->mWeaponSph);
        dComIfG_Ccsp()->Set(&i_this->mWeapon2Sph);
        if ((i_this->m2060 == 2) || (i_this->m2060 == 1)) {
            dComIfG_Ccsp()->SetMass(&i_this->mWeaponSph, 3);
            dComIfG_Ccsp()->SetMass(&i_this->mWeapon2Sph, 3);
        }
        if ((i_this->mWeaponSph.ChkAtHit()) || (i_this->mWeapon2Sph.ChkAtHit())) {
            if (i_this->mWeaponSph.ChkAtHit()) {
                pcVar2 = i_this->mWeaponSph.GetAtHitObj();
            } else {
                pcVar2 = i_this->mWeapon2Sph.GetAtHitObj();
            }
            if (pcVar2->GetStts() == NULL) {
                return NULL;
            }
            return pcVar2->GetStts()->GetActor();
        }
    }
    return NULL;
}

/* 0000645C-000064B0       .text AtHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
static void AtHitCallback(fopAc_ac_c* a_this, dCcD_GObjInf*, fopAc_ac_c* actor, dCcD_GObjInf*) {
    mo2_class* i_this = (mo2_class*)a_this;
    if (rouya_mode == 0) {
        return;
    }
    if (fopAcM_GetName(actor) != PROC_PLAYER) {
        return;
    }
    if (!daPy_getPlayerActorClass()->checkGrabWear()) {
        return;
    }
    i_this->m2A48 = 1;
    i_this->m2A4A = 1;
    i_this->m2A4C = 200;
}

/* 000064B0-00006DD0       .text fight__FP9mo2_class */
static void fight(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar6;
    f32 fVar11;
    cXyz local_38;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->m02E0 = 2;
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        attack_set(i_this, 0);
        tex_anm_set(i_this, 6);
        i_this->mDamageReaction.mMode = 1;
        i_this->m05A4[2] = 8;
        // Fall-through
    case 1:
        i_this->mWeaponSph.SetAtAtp(mo2_attack_AP[i_this->m2060]);
        i_this->mWeapon2Sph.SetAtAtp(mo2_attack_AP[i_this->m2060]);
        i_this->m2068 += attack_info[i_this->m2060][i_this->m2064].speed;
        cLib_addCalc2(&actor->speedF, 0.0f, 1.0f, 20.0f);
        if ((i_this->m2060 == 3) && (i_this->m2064 == 0)) {
            actor->speedF = 30.0f;
        } else if ((i_this->m2060 == 5) && (i_this->m2064 == 1)) {
            if (i_this->m207E > 0) {
                actor->speedF = 70.0f;
            } else {
                actor->speedF = -30.0f;
            }
            i_this->m05F0 = l_mo2HIO.m024 + 3;
            i_this->m05F2 = 4;
        }
        if ((i_this->m2068 > i_this->m2074) && (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038))) {
            i_this->mDamageReaction.m710 = 1;
        }
        if (i_this->m207E > 0) {
            if (i_this->m2060 == 1) {
                int r3 = l_mo2HIO.m0D8 + l_mo2HIO.m0DA + l_mo2HIO.m0DC + l_mo2HIO.m0DE;
                if (((int)i_this->m2068 >= l_mo2HIO.m0D8) && ((int)i_this->m2068 <= r3)) {
                    i_this->m0594 = 1;
                    if (((int)i_this->m2068 >= l_mo2HIO.m0D8 + l_mo2HIO.m0DA) && ((int)i_this->m2068 < l_mo2HIO.m0DC + (l_mo2HIO.m0D8 + l_mo2HIO.m0DA))) {
                        i_this->m0598 = 1;
                    }
                    iVar6 = (int)i_this->m2068 - l_mo2HIO.m0D8;
                    if (iVar6 < (int)ARRAY_SIZE(l_mo2HIO.m0E0)) {
                        i_this->m0590 = l_mo2HIO.m0E0[iVar6];
                    }
                }
            } else if (i_this->m2060 == 2) {
                int r3 = l_mo2HIO.m108 + l_mo2HIO.m10A + l_mo2HIO.m10C + l_mo2HIO.m10E;
                if (((int)i_this->m2068 >= l_mo2HIO.m108) && ((int)i_this->m2068 <= r3)) {
                    i_this->m0594 = 1;
                    if (((int)i_this->m2068 >= l_mo2HIO.m108 + l_mo2HIO.m10A) && ((int)i_this->m2068 < l_mo2HIO.m10C + (l_mo2HIO.m108 + l_mo2HIO.m10A))) {
                        i_this->m0598 = 1;
                    }
                    iVar6 = (int)i_this->m2068 - l_mo2HIO.m108;
                    if (iVar6 < (int)ARRAY_SIZE(l_mo2HIO.m110)) {
                        i_this->m0590 = l_mo2HIO.m110[iVar6];
                    }
                }
            }
        }
        if (i_this->m0594 == 0) {
            if (((i_this->m2068 >= br_set_tm[i_this->m2060]) && (i_this->m2068 <= br_set_tm[i_this->m2060] + 2.0f)) && (i_this->m2060 == 2)) {
                i_this->m05F0 = l_mo2HIO.m024 + 0x10;
                i_this->m05F2 = 0;
                i_this->m05EE = actor->current.angle.y + 0x2000 + REG0_S(8);
            }
        }
        if (((i_this->m2060 == 1) && (i_this->m2068 >= 31.0f)) && (i_this->m2068 <= 32.1f)) {
            i_this->m05F0 = l_mo2HIO.m024 + 8;
            i_this->m05F2 = 2;
            mDoAud_seStart(JA_SE_CM_LANCE_HIT_FLOOR, &i_this->m28D4, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((i_this->m2060 == 2) && (i_this->m05A4[2] == 1)) {
            i_this->m05F0 = l_mo2HIO.m024 + 4;
            i_this->m05F2 = 4;
        }
        if (fopAcM_searchPlayerDistance(actor) < 500.0f) {
            if ((i_this->m2068 < i_this->m2078) || (i_this->m2942 != 0)) {
                i_this->mDamageReaction.m4D0 = i_this->m05D6;
            }
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x800);
        }
        fopAc_ac_c* hitActor = yari_hit_check(i_this);
        if (hitActor != NULL) {
            if (fopAcM_GetName(hitActor) == PROC_PLAYER) {
                if (player->checkPlayerGuard() && (i_this->m2060 != 3)) {
                    i_this->mpMorf->setPlaySpeed(-1.0f);
                    if (i_this->m05F0 != 0) {
                        i_this->m05F0 = l_mo2HIO.m024 + 6;
                    }
                    i_this->m207E = 0xFF;
                    i_this->mpMorf->play(&actor->eyePos, 0, 0);
                }
            } else if (fopAcM_GetName(hitActor) == PROC_MO2) {
                i_this->m2954 = fopAcM_GetID(hitActor);
            }
        } else {
            i_this->mWeaponSph.ClrAtHit();
            i_this->mWeapon2Sph.ClrAtHit();
            if (i_this->m2940 != 0) {
                if (i_this->m2940 == 2) {
                    i_this->mpMorf->setPlaySpeed(-1.0f);
                    i_this->m0594 = 0;
                    if (i_this->m05F0 != 0) {
                        i_this->m05F0 = l_mo2HIO.m024 + 6;
                    }
                    i_this->m207E = 0xFF;
                    i_this->mpMorf->play(&actor->eyePos, 0, 0);
                } else {
                    i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                    path_check(i_this);
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = 2;
                }
                i_this->m05BE = 1;
                i_this->m05BA = 0x10;
                local_38.x = local_38.y = local_38.z = 1.0f;
                dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &i_this->m2934, NULL, &local_38);
                mDoAud_seStart(JA_SE_LK_ROPE_HOOK_METAL, &i_this->m2934, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
        if (i_this->mpMorf->isStop()) {
            if (((((i_this->m2064 == 2) && (i_this->m207E > 0)) || (i_this->m2060 == 4 && (i_this->m2064 == 0))) || (i_this->m207E < 0 && (i_this->m2064 == 0))
                ) ||
                (i_this->m2060 == 5 && (i_this->m207E < 0 && (i_this->m2064 == 1))))
            {
                if (i_this->m2060 == 3) {
                    attack_set(i_this, 1);
                    i_this->mDamageReaction.m4D0 = i_this->m05D6;
                } else if (i_this->m2954 != fpcM_ERROR_PROCESS_ID_e) {
                    i_this->mDamageReaction.mAction = mo2_class::Action_AITE_MIRU_e;
                    i_this->mDamageReaction.mMode = 0;
                } else {
                    if (i_this->m05C0 < l_mo2HIO.m030) {
                        if (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038)) {
                            if ((cM_rndF(1.0f) < 0.5f) || (i_this->m207E < 0)) {
                                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                                i_this->mDamageReaction.mMode = 2;
                                i_this->m05A4[1] = 0;
                            } else {
                                i_this->mDamageReaction.mMode = 0;
                            }
                        } else {
                            if ((i_this->mbHasInnateWeapon != 0) || (i_this->m2943 != 0)) {
                                i_this->mDamageReaction.mAction = mo2_class::Action_P_LOST_e;
                                i_this->mDamageReaction.mMode = 0;
                                i_this->m05A4[1] = 0;
                            } else {
                                i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                                path_check(i_this);
                                wait_set(i_this);
                                i_this->mDamageReaction.mMode = -10;
                            }
                        }
                    } else {
                        i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                        path_check(i_this);
                        wait_set(i_this);
                        i_this->mDamageReaction.mMode = -10;
                    }
                }
            } else {
                attack_info_s* info = attack_info[i_this->m2060];
                if (i_this->m207E > 0) {
                    i_this->m2064++;
                    fVar11 = info[i_this->m2064].speed;
                } else {
                    i_this->m2064--;
                    fVar11 = -info[i_this->m2064].speed;
                }
                anm_init(i_this, info[i_this->m2064].bckFileIdx, 0.0f, J3DFrameCtrl::EMode_NONE, fVar11, info[i_this->m2064].soundFileIdx);
            }
        }
    }
}

/* 00006DD0-000071DC       .text nage__FP9mo2_class */
static void nage(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 iVar5;
    s16 maxSpeed;

    iVar5 = 0;
    maxSpeed = 0x400;
    i_this->m02E0 = 2;
    i_this->mDamageReaction.m710 = 1;
    i_this->mDamageReaction.m4D0 = i_this->m05D6;
    switch (i_this->mDamageReaction.mMode) {
    case -10:
        if (i_this->mDamageReaction.m713 == 2) {
            i_this->mDamageReaction.mMode = -5;
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_HOOK, 0);
            i_this->m2A4A = 1;
            i_this->m2A48 = 1;
            break;
        }
        if (((i_this->m05B4 != 0) || (i_this->m2A0C != 0)) ||
            (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038)))
        {
            i_this->m05A4[1] = l_mo2HIO.m00A + l_mo2HIO.m00C;
            i_this->m05A4[2] = l_mo2HIO.m00C;
            anm_init(i_this, MO2_BCK_KKEIKAI, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_KKEIKAI);
            i_this->mDamageReaction.mMode = -9;
            i_this->mDamageReaction.m713 = 0;
            i_this->m05A4[0] = REG0_S(7) + 0xf;
            if (camera_mode == 0) {
                i_this->m2A1D = 2;
                i_this->m2A40 = REG8_F(3) + 50.0f;
            }
        } else {
            iVar5 = 1;
            break;
        }
    case -9:
        maxSpeed = (i_this->m05A4[0] != 0) ? (s16)0 : (s16)0x1000;
        if (i_this->m05A4[1] == 0) {
            iVar5 = 2;
        } else if ((i_this->m05A4[2] == 0) && (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038) != 0))
        {
            i_this->mDamageReaction.mMode = -5;
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_ALERT, 0);
            i_this->m2A4A = 1;
            i_this->m2A48 = 1;
        }
        actor->speedF = 0.0f;
        break;
    case -8:
        break;
    case 0:
        maxSpeed = 0;
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, MO2_BCK_KWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, MO2_BAS_KWALK);
        }
        actor->speedF = 0.0f;
        break;
    case 1:
        cLib_addCalc2(&actor->speedF, l_mo2HIO.m058, 1.0f, 20.0f);
        if (i_this->m05C0 < l_mo2HIO.m030) {
            i_this->mDamageReaction.mMode = 2;
            anm_init(i_this, MO2_BCK_KNAGE, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_KNAGE);
        }
        break;
    case 2: {
        maxSpeed = 0xc00;
        cLib_addCalc0(&actor->speedF, 1.0f, 20.0f);
        int frame = i_this->mpMorf->getFrame();
        if (frame == REG0_S(6) + 0xf) {
            i_this->m2A09 = 2;
            i_this->mMode = 0;
        }
        if (i_this->mpMorf->isStop()) {
            iVar5 = 1;
        }
        break;
    }
    }
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, maxSpeed);
    if ((iVar5 != 0) || (daMo2_player_bg_check(i_this, &i_this->mDamageReaction.m714->current.pos) == 1)) {
        i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
        wait_set(i_this);
        if (iVar5 == 2) {
            i_this->m05A4[1] = 0;
        }
        i_this->mDamageReaction.mMode = 2;
        i_this->m2969 = i_this->m2969 - i_this->mHasPath;
        if (i_this->m2A1D != 0) {
            i_this->m2A1D = 10;
        }
    }
}

/* 000071DC-00007478       .text p_lost__FP9mo2_class */
static void p_lost(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m02E0 = 2;
    i_this->mDamageReaction.m710 = 0;
    switch (i_this->mDamageReaction.mMode) {
    case -10:
        if (i_this->mDamageReaction.m470 < 200.0f) {
            anm_init(i_this, MO2_BCK_UKYADEMO, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mDamageReaction.mMode = -9;
            tex_anm_set(i_this, 4);
            i_this->m05A4[1] = 0x23;
        }
        break;
    case -9:
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] == (s16)(REG17_S(5) + 0x19)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_STOLEN, 0);
        }
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
            i_this->mDamageReaction.mMode = 2;
        }
        break;
    case 0:
        i_this->mDamageReaction.mMode = 1;
        tex_anm_set(i_this, 4);
        anm_init(i_this, MO2_BCK_BKYORO, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_BKYORO);
        break;
    case 1:
        actor->speedF = 0.0f;
        if (((i_this->m059C & 0x1F) == 0) && (cM_rndF(1.0f) < 0.5f)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_SEARCH, 0);
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 2;
            i_this->m05A4[1] = 0;
        }
    }
    if ((((int)i_this->mpMorf->getFrame() > 25) && (i_this->m05A4[1] == 0)) &&
        (daMo2_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->m05D6, l_mo2HIO.m038)))
    {
        i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
        i_this->mDamageReaction.mMode = 2;
    }
}

/* 00007478-0000775C       .text b_nige__FP9mo2_class */
static void b_nige(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_10;

    if (!daMo2_bomb_check(i_this)) {
        i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = 2;
    } else {
        fopAc_ac_c* r3 = i_this->mpBomb;
        local_10.x = r3->current.pos.x - actor->current.pos.x;
        local_10.z = r3->current.pos.z - actor->current.pos.z;
        i_this->mDamageReaction.m4D0 = cM_atan2s(-local_10.x, -local_10.z);
        switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, MO2_BCK_SHAKKEN, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_SHAKKEN);
            i_this->m05A4[1] = 0x14;
        // Fall-through
        case 1:
            actor->speedF = 0.0f;
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0 + 0x8000, 2, 0x3000);
            if (i_this->m05A4[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
                anm_init(i_this, MO2_BCK_NWALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NWALK);
            }
            break;
        case 2:
            actor->speedF = l_mo2HIO.m060;
            i_this->m05F0 = l_mo2HIO.m024 + 3;
            i_this->m05F2 = 4;
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
            if (std::sqrtf(SQUARE(local_10.x) + SQUARE(local_10.z)) > 800.0f) {
                i_this->mDamageReaction.mMode = 3;
                anm_init(i_this, MO2_BCK_NBWAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_NBWAIT);
            }
            break;
        case 3:
            actor->speedF = 0.0f;
            i_this->mDamageReaction.m4D0 = i_this->m05D6;
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x1000);
            if (std::sqrtf(SQUARE(local_10.x) + SQUARE(local_10.z)) < 700.0f) {
                i_this->mDamageReaction.mMode = 0;
            }
        }
    }
}

/* 0000775C-000078A8       .text defence__FP9mo2_class */
static void defence(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m02E0 = 2;
    i_this->mDamageReaction.m710 = 1;
    i_this->mDamageReaction.m4D0 = i_this->m05D6;
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x400);
    i_this->mDamageReaction.m711 = 1;
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_BWALKFB, 5.0f, J3DFrameCtrl::EMode_NONE, -1.0f, MO2_BAS_BWALKFB);
        i_this->m05A4[1] = REG6_S(3) + 0x1e;
        tex_anm_set(i_this, 4);
        actor->speedF = -20.0f;
        // Fall-through
    case 1:
        i_this->mDefenseSph.SetR(62.5f);
        i_this->m2928 = i_this->m28E0;
        if (i_this->mpMorf->isStop()) {
            actor->speedF = 0.0f;
        }
        if (i_this->m05A4[1] == 0) {
            i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
            i_this->m05A4[1] = 0;
            i_this->mDamageReaction.mMode = 0;
        }
        break;
    }
}

/* 000078A8-000079C0       .text oshi__FP9mo2_class */
static void oshi(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m02E0 = 2;
    i_this->mDamageReaction.m4D0 = i_this->m05D6;
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x800);
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_ADOTSUKI, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_ADOTSUKI);
        tex_anm_set(i_this, 4);
        actor->speedF = 0.0f;
        // Fall-through
    case 1:
        i_this->m2928 = i_this->m28E0;
        i_this->mDefenseSph.SetR(87.5f);
        if (i_this->mpMorf->isStop()) {
            i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
            i_this->m05A4[1] = 0;
            i_this->mDamageReaction.mMode = 0;
        }
        break;
    }
}

/* 000079C0-00007DAC       .text hukki__FP9mo2_class */
static void hukki(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;
    cXyz local_38;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    local_2c.x = i_this->mDamageReaction.m100[10].x - i_this->mDamageReaction.m100[0xd].x;
    local_2c.z = i_this->mDamageReaction.m100[10].z - i_this->mDamageReaction.m100[0xd].z;
    cMtx_YrotS(*calc_mtx, cM_atan2s(local_2c.x, local_2c.z));
    local_2c.x = 0.0f;
    local_2c.y = 0.0f;
    i_this->m05B4 = 2;
    switch (i_this->mDamageReaction.mMode) {
    case 10:
        anm_init(i_this, MO2_BCK_OKIRUA, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_OKIRUA);
        i_this->m05A4[2] = 0xF;
        goto LAB_806ae194;
    case 12:
        anm_init(i_this, MO2_BCK_OKIRUU, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_OKIRUU);
        i_this->m05A4[2] = REG0_S(5) + 0xF;
    LAB_806ae194:
        tex_anm_set(i_this, 5);
        actor->speedF = 0.0f;
        i_this->mDamageReaction.mMode = 0xD;
        i_this->mDamageReaction.m480 = 0;
        local_2c.z = 125.0f;
        MtxPosition(&local_2c, &i_this->mDamageReaction.m458);
        actor->current.pos.y -= i_this->mDamageReaction.m44C.y;
        actor->old.pos.y -= i_this->mDamageReaction.m44C.y;
        i_this->mDamageReaction.m44C.y = 0.0f;
        // Fall-through
    case 13:
        i_this->m02E0 = 2;
        if (i_this->m05A4[2] <= REG6_S(5) + 6) {
            cLib_addCalc0(&i_this->mDamageReaction.m458.x, 1.0f, (REG6_F(5) + 100.0f) * 0.25f);
            cLib_addCalc0(&i_this->mDamageReaction.m458.z, 1.0f, (REG6_F(5) + 100.0f) * 0.25f);
            if (i_this->m05A4[2] >= REG6_S(6) + 1) {
                local_2c.z = 25.0f;
                MtxPosition(&local_2c, &local_38);
                actor->current.pos.x += local_38.x;
                actor->current.pos.z += local_38.z;
            }
        }
        if (i_this->m05A4[2] == 1) {
            i_this->m05F0 = l_mo2HIO.m024 + 6;
            i_this->m05F2 = 3;
        }
        if (i_this->mpMorf->isStop()) {
            if ((!player->checkGrabWear()) && (i_this->m05C0 < l_mo2HIO.m030)) {
                i_this->mDamageReaction.mMode = 0xe;
                i_this->m05A4[1] = 10;
            } else {
                i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
            i_this->mDamageReaction.m488 = 0;
        }
        break;
    case 14:
        i_this->mDamageReaction.m710 = 1;
        i_this->mDamageReaction.m4D0 = i_this->m05D6;
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x1000);
        if (i_this->m05A4[1] == 0) {
            if (l_mo2HIO.m009 == 0) {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_e;
                i_this->m2060 = 5;
                i_this->m2068 = REG0_F(8) + 29.0f;
                i_this->m206C = 32.0f;
                i_this->m2070 = 39.0f;
                i_this->m2074 = 0.0f;
                i_this->m2078 = l_mo2HIO.m0D6;
                i_this->m207E = 1;
                i_this->m2064 = 1;
                attack_info_s* info = attack_info[i_this->m2060];
                info++; // TODO: fakematch?
                anm_init(i_this, info->bckFileIdx, 5.0f, 0, info->speed, info->soundFileIdx);
                tex_anm_set(i_this, 6);
                i_this->mDamageReaction.mMode = 1;
                i_this->m2942 = 1;
            } else {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                i_this->mDamageReaction.mMode = 0;
            }
        }
        break;
    }
}

/* 00007DAC-00007ED4       .text aite_miru__FP9mo2_class */
static void aite_miru(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->m05A4[1] = REG0_S(8) + 0x14;
        actor->speedF = 0.0f;
        i_this->mDamageReaction.mMode = 1;
        tex_anm_set(i_this, 4);
        fopAcM_monsSeStart(actor, JA_SE_CV_MO_SEARCH, 0);
        // Fall-through
    case 1: {
        cLib_addCalcAngleS2(&i_this->m2952, 12000, 2, 0x1800);
        i_this->mDamageReaction.m710 = 1;
        if (i_this->m2954 != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* pfVar2 = fopAcM_SearchByID(i_this->m2954);
            if (pfVar2 != NULL) {
                i_this->mDamageReaction.m714 = pfVar2;
            }
        }
        if (i_this->m05A4[1] == 0) {
            i_this->m2954 = fpcM_ERROR_PROCESS_ID_e;
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            i_this->mDamageReaction.mMode = 0;
            path_check(i_this);
        }
    }
    }
}

/* 00007ED4-00008008       .text fail__FP9mo2_class */
static void fail(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    i_this->m05B4 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    actor->speedF = 0.0f;
    actor->speed.y = 0.0f;
    switch (i_this->mDamageReaction.mMode) {
    case 0: {
        local_18 = actor->current.pos;
        local_18.y += l_mo2HIO.m01C + 100.0f;
        u8 var_r6 = 0;
        if (i_this->m05A4[2] >= 0x3E8) {
            var_r6 = 1;
        }
        fopAcM_createDisappear(actor, &local_18, 10, var_r6, actor->stealItemBitNo);
        if (fopAcM_CheckStatus(actor, fopAcStts_BOSS_e)) {
            i_this->m2A1C = 1;
            i_this->mDamageReaction.mMode++;
        } else {
            fopAcM_delete(actor);
        }
        if (i_this->mDeathSwitch != 0) {
            dComIfGs_onSwitch(i_this->mDeathSwitch, fopAcM_GetRoomNo(actor));
        }
        fopAcM_onActor(actor);
        break;
    }
    case 1:
        break;
    }
}

/* 00008008-00008214       .text yogan_fail__FP9mo2_class */
static void yogan_fail(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m05B4 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    actor->speedF = 0.0f;
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        anm_init(i_this, MO2_BCK_AWATEDEMO, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mDamageReaction.mMode = 1;
        actor->speed.y = REG0_F(0x13) + 190.0f;
        fopAcM_monsSeStart(actor, JA_SE_CV_MO_ALERT, 0);
        i_this->mDamageReaction.m458.y = 0.0f;
        i_this->mDamageReaction.m44C.y = 0.0f;
        if (i_this->mbHasInnateWeapon != 0) {
            i_this->mSpawnWeaponActor = 1;
        }
        // Fall-through
    case 1:
        dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_FIREK_KASU, &actor->current.pos);
        dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_MAGT_FCHIP, &actor->current.pos);
        if ((i_this->m059C & 3U) == 0) {
            i_this->m05E8.y = cM_rndF(65536.0f);
            i_this->m05E8.x = -0x2000;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m28C8, &i_this->m05E8);
        }
        cLib_addCalcAngleS2(&actor->current.angle.x, -0x4000, 10, 0x200);
        if (actor->speed.y < 0.0f) {
            i_this->mDamageReaction.mAction = mo2_class::Action_FAIL_e;
            i_this->mDamageReaction.mMode = 0;
            i_this->m05A4[2] = 2000;
        }
    }
}

/* 00008214-000088F8       .text wepon_search__FP9mo2_class */
static void wepon_search(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(i_this->mWeaponPcId);
    f32 dVar9;

    if ((i_this->mDamageReaction.mMode < 2) && (boko == NULL || (boko != NULL && fopAcM_checkCarryNow(boko)))) {
        i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = 2;
        return;
    }
    dVar9 = 10000.0f;
    if (boko != NULL) {
        cXyz delta;
        delta.x = boko->current.pos.x - actor->current.pos.x;
        delta.z = boko->current.pos.z - actor->current.pos.z;
        i_this->mDamageReaction.m4D0 = cM_atan2s(delta.x, delta.z);
        dVar9 = std::sqrtf(SQUARE(delta.x) + SQUARE(delta.z));
    }
    switch (i_this->mDamageReaction.mMode) {
    case -1:
        i_this->mDamageReaction.mMode = 0;
        i_this->m2943 = 0;
        anm_init(i_this, MO2_BCK_SHAKKEN, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_SHAKKEN);
        if (dVar9 < 900.0f) {
            i_this->m05A4[1] = 0x14;
        } else {
            i_this->m05A4[1] = 200;
        }
        i_this->m05B2 = 5;
        tex_anm_set(i_this, 2);
        fopAcM_monsSeStart(actor, JA_SE_CV_MO_FIND_LANCE, 0);
        break;
    case 0:
        actor->speedF = 0.0f;
        if (i_this->m05B2 == 0) {
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 2, 0x3000);
            if ((i_this->mpMorf->isStop()) || (i_this->m05A4[1] == 0)) {
                i_this->mDamageReaction.mMode = 1;
                i_this->m05AE = l_mo2HIO.m08A;
                anm_init(i_this, MO2_BCK_SWALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_SWALK);
            }
        }
        break;
    case 1:
        actor->speedF = l_mo2HIO.m060;
        i_this->m05F0 = l_mo2HIO.m024 + 3;
        i_this->m05F2 = 4;
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
        if (ground_4_check(i_this, 1, actor->current.angle.y, 300.0f)) {
            anm_init(i_this, MO2_BCK_GAKEDEMO, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mDamageReaction.mMode = 3;
            i_this->m05A4[1] = 0x1e;
            i_this->m2943 = 1;
        } else {
            if (dVar9 < 300.0f) {
                i_this->mDamageReaction.mMode = 2;
                anm_init(i_this, MO2_BCK_SCATCH, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_SCATCH);
                i_this->m05A4[1] = 0x1d;
            } else {
                if ((i_this->m05AE == 0) || (i_this->mDamageReaction.mAcch.ChkWallHit())) {
                    i_this->m02E2 = 0x46;
                    i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                    i_this->m05A4[1] = 0;
                    i_this->m2943 = 1;
                }
            }
        }
        break;
    case 2: {
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] == 0x18) {
            if ((boko != NULL) && !fopAcM_checkCarryNow(boko)) {
                i_this->mbHasInnateWeapon = 1;
                fopAcM_delete(boko);
                fopAcM_seStart(actor, JA_SE_CM_LANCE_PICKUP, 0);
            } else {
                i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
        }
        if (i_this->m05A4[1] < 0xe) {
            i_this->mDamageReaction.m710 = 1;
            i_this->mDamageReaction.m4D0 = i_this->m05D6;
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x800);
        }
        if (i_this->mpMorf->isStop()) {
            if (((l_mo2HIO.m009 == 0) && (!player->checkGrabWear())) && (i_this->m05C0 < l_mo2HIO.m030)) {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_e;
                i_this->m2060 = 2;
                i_this->m2068 = REG0_F(8) + 33.0f;
                i_this->m206C = 36.0f;
                i_this->m2070 = 52.0f;
                i_this->m2074 = 75.0f;
                i_this->m2078 = l_mo2HIO.m0D0;
                i_this->m207E = 1;
                i_this->m2064 = 1;
                attack_info_s* info = attack_info[i_this->m2060];
                info++; // TODO: fakematch?
                anm_init(i_this, info->bckFileIdx, 5.0f, J3DFrameCtrl::EMode_NONE, info->speed, info->soundFileIdx);
                tex_anm_set(i_this, 6);
                i_this->mDamageReaction.mMode = 1;
                i_this->m2942 = 1;
            } else {
                i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
        }
        break;
    }
    case 3:
        if (dVar9 < 300.0f) {
            i_this->mDamageReaction.mMode = 2;
            anm_init(i_this, 0x6c, 2.0f, 0, 1.0f, 0x33);
            fopAcM_seStart(actor, JA_SE_CM_LANCE_PICKUP, 0);
            i_this->m05A4[1] = 0x1d;
            actor->speedF = 0.0f;
        } else {
            cLib_addCalc0(&actor->speedF, 1.0f, REG0_F(8) + 7.0f);
            if (actor->speedF > 1.0f) {
                i_this->m05F0 = l_mo2HIO.m024 + 4;
                i_this->m05F2 = 4;
            }
            if (i_this->m05A4[1] == 0) {
                i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
        }
    }
}

/* 000088F8-00008AF8       .text hip_damage__FP9mo2_class */
static void hip_damage(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_HIPDMG01, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_HIPDMG01);
        actor->speedF = REG6_F(0) + 100.0f;
        i_this->m05A4[0] = 0xF;
        i_this->m05F0 = l_mo2HIO.m024 + 3;
        i_this->m05F2 = 4;
        // Fall-through
    case 1:
        cLib_addCalc2(&actor->speedF, 0.0f, 1.0f, REG6_F(1) + 10.0f);
        if (i_this->m05A4[0] == 0) {
            i_this->mDamageReaction.mMode = 2;
            anm_init(i_this, MO2_BCK_HIPDMG02, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_HIPDMG02);
            i_this->m05A4[0] = 0x3c;
            i_this->mDamageReaction.m4D0 = actor->current.angle.y + 0x8000;
        }
        break;
    case 2:
        if ((i_this->m059C & 7) == 0) {
            i_this->m05E8.y = cM_rndF(65536.0f);
            i_this->m05E8.x = -0x2000;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m28C8, &i_this->m05E8);
        }
        actor->speedF = REG6_F(2) + 50.0f;
        if (i_this->m05A4[0] < REG6_S(1) + 0x28) {
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x500);
            if (i_this->m05A4[0] == 0) {
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                i_this->mDamageReaction.mMode = 0;
                i_this->m05B4 = 0;
                i_this->m05A4[1] = 0;
                break;
            }
        }
    }
}

/* 00008AF8-00008C20       .text d_mahi__FP9mo2_class */
static void d_mahi(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_KOKERUF, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_KOKERUF);
        i_this->m05A4[0] = 100;
        // Fall-through
    case 1:
        if ((i_this->m05A4[0] <= 0x50) && (i_this->m05A4[0] >= 0x28)) {
            if (i_this->m05A4[0] == 0x50) {
                enemy_piyo_set(actor);
            }
            fopAcM_seStart(actor, JA_SE_CM_MD_PIYO, 0);
        }
        actor->speedF = 0.0f;
        if (i_this->m05A4[0] == 0x1E) {
            i_this->mDamageReaction.m49E = 0xF;
        }
        if (i_this->m05A4[0] == 0) {
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 2;
        }
    }
}

/* 00008C20-00008CD8       .text d_sit__FP9mo2_class */
static void d_sit(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m05B4 = 5;
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_KOKERUF, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_KOKERUF);
        i_this->m05A4[0] = 0x32;
        // Fall-through
    case 1:
        actor->speedF = 0.0f;
        if (i_this->m05A4[0] == 0) {
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 2;
        }
    }
}

/* 00008CD8-00008E98       .text d_dozou__FP9mo2_class */
static void d_dozou(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m05B4 = 5;
    i_this->m02E0 = 2;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        i_this->mDamageReaction.mStts.Init(0xFF, 0xFF, actor);
        if (i_this->mFrozenInTimePose == 0) {
            anm_init(i_this, MO2_BCK_TACKLEDEMO, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
            i_this->mpMorf->setFrame(3.0f);
        } else {
            anm_init(i_this, MO2_BCK_WALK, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, MO2_BAS_WALK);
            i_this->mpMorf->setFrame(37.0f);
        }
        // Fall-through
    case 1:
        if (((i_this->mEnableSpawnSwitch != 0xFF) && (dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(actor)))) ||
            (i_this->mEnableSpawnSwitch == 0xFF && (dComIfGs_isEventBit(dSv_event_flag_c::COLORS_IN_HYRULE))))
        {
            i_this->mpMorf->setPlaySpeed(1.0f);
            i_this->mDamageReaction.mMode = 2;
        }
        break;
    case 2:
        if (i_this->mpMorf->isStop()) {
            i_this->mDamageReaction.mStts.Init(200, 0xFF, actor);
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            i_this->mDamageReaction.mMode = 0;
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            break;
        }
    }
}

/* 00008E98-00008EA8       .text carry__FP9mo2_class */
static void carry(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    actor->speed.y = 0.0f;
}

/* 00008EA8-0000910C       .text carry_drop__FP9mo2_class */
static void carry_drop(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    cLib_addCalc0(&i_this->mDamageReaction.m468, 1.0f, 5.5f);
    cLib_addCalc0(&i_this->mDamageReaction.m46C, 1.0f, 0.5f);
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x100);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x100);
    cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m05D6, 4, 0x800);
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        i_this->mDamageReaction.mMode = 1;
        anm_init(i_this, MO2_BCK_JSTART, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_JSTART);
    case 1:
        if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
            anm_init(i_this, MO2_BCK_JEND, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_JEND);
            i_this->mDamageReaction.mMode = 2;
            i_this->m05F0 = l_mo2HIO.m024 + 6;
            i_this->m05F2 = 3;
            i_this->mDamageReaction.mMaxFallDistance = 300.0f;
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_JAB, 0);
            fopAcM_seStart(actor, JA_SE_CM_MO_BB_LANDING, 0);
        }
        break;
    case 2:
        cLib_addCalc0(&i_this->mDamageReaction.m468, 1.0f, 50.0f);
        cLib_addCalc0(&i_this->mDamageReaction.m46C, 1.0f, 50.0f);
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x1000);
        cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x1000);
        cLib_addCalc0(&actor->speedF, 1.0f, 1.0f);
        if (i_this->mpMorf->isStop()) {
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            i_this->mDamageReaction.mMode = 0;
            actor->current.angle = actor->shape_angle;
            break;
        }
    }
}

/* 0000910C-000094DC       .text e3_demo__FP9mo2_class */
static void e3_demo(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = (camera_class*)dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    i_this->m05B4 = 5;
    i_this->mDamageReaction.m4D0 = fopAcM_searchPlayerAngleY(actor);
    camera->mCamera.SetTrimSize(2);
    switch (i_this->mDamageReaction.mMode) {
    case 0:
        anm_init(i_this, MO2_BCK_UKYADEMO, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m05A4[1] = 0x19;
        i_this->mDamageReaction.mMode = 1;
        dMeter_mtrHide();
        i_this->m2A4C = 200;
    case 1:
        if (i_this->m05A4[1] == 0) {
            anm_init(i_this, MO2_BCK_SWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_SWALK);
            i_this->mDamageReaction.mMode = 2;
            if (alerm_set == 0) {
                mDoAud_seStart(JA_SE_MAJUTOU_ALERM);
                alerm_set++;
            }
        }
        actor->speedF = 0.0f;
        break;
    case 2:
        cLib_addCalc0(&i_this->m2A40, 0.1f, 3.0f);
        cLib_addCalc2(&actor->speedF, l_mo2HIO.m058, 1.0f, 20.0f);
        if ((i_this->m05C0 < l_mo2HIO.m030) || (ground_4_check(i_this, 1, actor->current.angle.y, 100.0f))) {
            i_this->mDamageReaction.mMode = 3;
            anm_init(i_this, MO2_BCK_KNAGE, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_KNAGE);
        }
        break;
    case 3: {
        cLib_addCalc0(&actor->speedF, 1.0f, 20.0f);
        int frame = i_this->mpMorf->getFrame();
        if (frame == REG0_S(6) + 0xF) {
            i_this->m2A09 = 2;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mDamageReaction.mMode = 4;
            anm_init(i_this, MO2_BCK_SWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_SWALK);
        }
        break;
    }
    case 4:
        cLib_addCalc2(&actor->speedF, l_mo2HIO.m058, 1.0f, 20.0f);
        if ((fopAcM_searchPlayerDistance(actor) < 250.0f) || (ground_4_check(i_this, 1, actor->current.angle.y, 100.0f))) {
            i_this->mDamageReaction.mMode = 5;
            anm_init(i_this, MO2_BCK_WAITDEMO, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m05A4[1] = 0x1E;
            mDoAud_seStop(JA_SE_MAJUTOU_ALERM, 30);
            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_HOLDUP_e);
        }
        break;
    case 5:
        actor->speedF = 0.0f;
        if (i_this->m05A4[1] == 0) {
            i_this->m2A4B = 1;
        }
    }
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x800);
    if (!player->checkGrabWear()) {
        cLib_addCalcAngleS2(&player->current.angle.y, i_this->mDamageReaction.m4D0 + 0x8000, 4, 0x400);
        cLib_addCalcAngleS2(&player->shape_angle.y, i_this->mDamageReaction.m4D0 + 0x8000, 4, 0x400);
    }
}

/* 000094DC-000094F4       .text search_target__FP9mo2_class */
static s32 search_target(mo2_class* i_this) {
    i_this->mDamageReaction.m714 = dComIfGp_getPlayer(0);
    return 0;
}

/* 000094F4-00009A10       .text Mo2_move__FP9mo2_class */
static void Mo2_move(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;

    i_this->m05D8 = 0;
    i_this->mDamageReaction.m710 = 0;
    i_this->mDamageReaction.m711 = 0;
    cLib_addCalcAngleS2(&i_this->m2952, 0, 2, 0x800);
    if (i_this->mDamageReaction.mMode <= -0x64) {
        if (i_this->mDamageReaction.mAcch.ChkGroundLanding()) {
            tex_anm_set(i_this, 0);
        }
        i_this->m02E0 = 2;
        i_this->m05B4 = 5;
        if ((std::fabsf(i_this->mDamageReaction.m478) > 40.0f) && (!i_this->mDamageReaction.mAcch.ChkGroundHit())) {
            i_this->mWeaponSph.SetC(i_this->mDamageReaction.m100[0xc]);
            i_this->mWeaponSph.SetR(60.0f);
            i_this->mWeaponSph.OffAtVsPlayerBit();
            i_this->mWeaponSph.OnCoSetBit();
            i_this->mWeaponSph.SetAtSpl(dCcG_At_Spl_UNK1);
            dComIfG_Ccsp()->Set(&i_this->mWeaponSph);
            dComIfG_Ccsp()->SetMass(&i_this->mWeaponSph, 3);
            if ((i_this->mWeaponSph.ChkAtHit() != 0) && (actor->speed.y < -50.0f)) {
                actor->speed.y = 0.0f;
                i_this->mDamageReaction.m474 = 8000.0f;
            }
            i_this->mCoCyl.OffCoSetBit();
        }
    } else {
        i_this->mWeaponSph.OnAtVsPlayerBit();
        if (i_this->m2A1C == 0) {
            i_this->mCoCyl.OnCoSetBit();
        } else {
            i_this->mCoCyl.OffCoSetBit();
        }
        if ((i_this->mDamageReaction.m48A) && (i_this->mDamageReaction.m488 == 0)) {
            if (i_this->mDamageReaction.m48A == 1) {
                if (((i_this->mMode != 1) || (rouya_mode == 0)) && (i_this->mDamageReaction.mAction != mo2_class::Action_P_LOST_e || (i_this->m05A4[1] == 0))) {
                    i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                    i_this->mDamageReaction.mMode = 0;
                    i_this->m05A4[1] = 0;
                }
            } else {
                i_this->mDamageReaction.m4D0 = i_this->m05D6;
                actor->speedF = -30.0f;
                i_this->m05F0 = l_mo2HIO.m024 + 3;
                i_this->m05F2 = 4;
            }
        } else {
            if (i_this->m2A0C != 0) {
                i_this->m2A0C--;
                local_20 = i_this->m2A10 - actor->current.pos;
            } else {
                search_target(i_this);
                local_20 = i_this->mDamageReaction.m714->current.pos - actor->current.pos;
            }
            i_this->m05C0 = std::sqrtf(SQUARE(local_20.x) + SQUARE(local_20.z));
            i_this->m05D6 = cM_atan2s(local_20.x, local_20.z);
            i_this->mCoCyl.SetR(REG0_F(3) + 90.0f);
            if (i_this->m2A0B != 0) {
                i_this->m2A0B--;
                if (i_this->m2A0B == 0) {
                    i_this->mDamageReaction.mAction = mo2_class::Action_D_MAHI_e;
                    i_this->mDamageReaction.mMode = 0;
                }
            }
            switch (i_this->mDamageReaction.mAction) {
            case mo2_class::Action_JYUNKAI_e:
                jyunkai(i_this);
                break;
            case mo2_class::Action_FIGHT_RUN_e:
                fight_run(i_this);
                break;
            case mo2_class::Action_FIGHT_e:
                fight(i_this);
                break;
            case mo2_class::Action_NAGE_e:
                nage(i_this);
                break;
            case mo2_class::Action_DEFENCE_e:
                defence(i_this);
                break;
            case mo2_class::Action_OSHI_e:
                oshi(i_this);
                break;
            case mo2_class::Action_P_LOST_e:
                p_lost(i_this);
                break;
            case mo2_class::Action_B_NIGE_e:
                b_nige(i_this);
                break;
            case mo2_class::Action_HUKKI_e:
                hukki(i_this);
                break;
            case mo2_class::Action_WEPON_SEARCH_e:
                wepon_search(i_this);
                break;
            case mo2_class::Action_HIP_DAMAGE_e:
                hip_damage(i_this);
                break;
            case mo2_class::Action_AITE_MIRU_e:
                aite_miru(i_this);
                break;
            case mo2_class::Action_FAIL_e:
                fail(i_this);
                break;
            case mo2_class::Action_YOGAN_FAIL_e:
                yogan_fail(i_this);
                break;
            case mo2_class::Action_CARRY_e:
                carry(i_this);
                break;
            case mo2_class::Action_CARRY_DROP_e:
                carry_drop(i_this);
                break;
            case mo2_class::Action_D_SIT_e:
                d_sit(i_this);
                break;
            case mo2_class::Action_D_MAHI_e:
                d_mahi(i_this);
                break;
            case mo2_class::Action_D_DOZOU_e:
                d_dozou(i_this);
                break;
            case mo2_class::Action_E3_DEMO_e:
                e3_demo(i_this);
                break;
            }
        }
        if (i_this->mDamageReaction.mAction != mo2_class::Action_CARRY_e) {
            local_20.x = 0.0f;
            local_20.y = 0.0f;
            local_20.z = actor->speedF;
            if (((i_this->mDamageReaction.mAction != mo2_class::Action_HUKKI_e) && (i_this->mDamageReaction.mAction != mo2_class::Action_FAIL_e)) &&
                (i_this->mDamageReaction.m48A == 0))
            {
                i_this->mDamageReaction.m482 = actor->current.angle.y;
                cMtx_YrotS(*calc_mtx, actor->current.angle.y + i_this->m05D8);
            } else {
                cMtx_YrotS(*calc_mtx, i_this->mDamageReaction.m4D0);
            }
            MtxPosition(&local_20, &local_2c);
            actor->speed.x = local_2c.x;
            actor->speed.z = local_2c.z;
        }
    }
}

/* 00009A10-00009AC0       .text mo2_eye_tex_anm__FP9mo2_class */
static void mo2_eye_tex_anm(mo2_class* i_this) {
    if (i_this->m02E0 != 0) {
        i_this->m02E0--;
    } else {
        i_this->m02E0 = cM_rndF(50.0f) + 10.0f;
        if (i_this->m02DD == 0) {
            tex_anm_set(i_this, 3);
        }
    }
    if (i_this->m02DD != 0) {
        if (i_this->m02DC < i_this->m02DE) {
            i_this->m02DC++;
        } else {
            i_this->m02DD = 0;
        }
    }
}

/* 00009AC0-0000A3C0       .text damage_check__FP9mo2_class */
static u8 damage_check(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 sVar3;
    cXyz local_48;
    cXyz local_54;
    s8 hp;

    CcAtInfo atInfo;
    atInfo.mDamage = 0;
    u8 iVar12 = 0;
    u8 iVar11 = 0;
    i_this->mDamageReaction.mStts.Move();
    dComIfG_Ccsp()->Set(&i_this->mDefenseSph);
    i_this->mDefenseSph.SetC(i_this->m2928);
    if (i_this->mDefenseSph.ChkTgHit()) {
        cCcD_Obj* pcVar5 = i_this->mDefenseSph.GetTgHitObj();
        def_se_set(actor, pcVar5, 0x41);
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        local_48.x = 0.0f;
        local_48.y = 0.0f;
        local_48.z = -10.0f;
        MtxPosition(&local_48, &i_this->mDamageReaction.m42C);
        i_this->mDamageReaction.m4D4 = -15.0f;
        csXyz local_68(player->shape_angle);
        local_68.y += 0x8000;
        JPABaseEmitter* emitter = dComIfGp_particle_set(
            dPa_name::ID_AK_JN_ELEMENTKIKUZU00, &i_this->m2928, &local_68, NULL, 0xFF, NULL, -1, &actor->tevStr.mColorK0, &actor->tevStr.mColorK0, NULL
        );
        if (emitter != NULL) {
            emitter->setRate(10.0f);
            emitter->setMaxFrame(1);
            emitter->setSpread(0.2f);
            emitter->setVolumeSweep(0.15f);
            JGeometry::TVec3<f32> scale;
            scale.x = scale.y = scale.z = REG14_F(16) + 0.85f;
            emitter->setGlobalParticleScale(scale);
        }
        return 0;
    } else {
        i_this->m2928.y = -10000.0f;
        i_this->mDefenseSph.SetR(-200.0f);
        if ((i_this->m05B4 == 0) && (i_this->mHeadSph.ChkTgHit() || (i_this->mTgCyl.ChkTgHit()))) {
            i_this->m05A0 = 0;
            i_this->m2944 = -1;
            i_this->m294E = 0;
            i_this->m05B4 = REG0_S(7) + 5;
            if (i_this->mHeadSph.ChkTgHit()) {
                iVar12 = 1;
                atInfo.mpObj = i_this->mHeadSph.GetTgHitObj();
                atInfo.pParticlePos = i_this->mHeadSph.GetTgHitPosP();
            } else {
                if (i_this->mTgCyl.ChkTgHit()) {
                    iVar12 = 2;
                    atInfo.mpObj = i_this->mTgCyl.GetTgHitObj();
                    atInfo.pParticlePos = i_this->mTgCyl.GetTgHitPosP();
                }
            }
            if (atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW)) {
                if (atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
                    i_this->mEnemyIce.mFreezeDuration = REG0_S(3) + 300;
                    i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
                    path_check(i_this);
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = -10;
                } else {
                    i_this->mEnemyIce.mLightShrinkTimer = 1;
                }
                enemy_fire_remove(&i_this->mEnemyFire);
                i_this->m05F0 = 0;
                i_this->m05F4.remove();
                if (i_this->mbHasInnateWeapon != 0) {
                    i_this->mSpawnWeaponActor = 2;
                }
                i_this->m2A09 = 1;
                return 0;
            }
            if (atInfo.mpObj->ChkAtType(AT_TYPE_FIRE | AT_TYPE_FIRE_ARROW)) {
                (i_this->mEnemyFire).mFireDuration = REG0_S(2) + 100;
                i_this->m05B4 = 0x32;
            }
            hp = actor->health;
            at_power_check(&atInfo);
            if ((atInfo.mResultingAttackType == 10) || (atInfo.mResultingAttackType == 0xe)) {
                actor->health = 0x14;
            }
            atInfo.mpActor = cc_at_check(actor, &atInfo);
            if ((atInfo.mResultingAttackType == 10) || (atInfo.mResultingAttackType == 0xe)) {
                actor->health = hp;
                if ((atInfo.mResultingAttackType == 0xe) && (i_this->m2951 == 0)) {
                    i_this->m2951 = 1;
                    i_this->mDamageReaction.mAction = mo2_class::Action_P_LOST_e;
                    i_this->mDamageReaction.mMode = -10;
                }
            }
            i_this->m05B6 = 0x19;
            dKy_Sound_set(actor->current.pos, 100, fopAcM_GetID(actor), 5);
            if (l_mo2HIO.m007 != 0) {
                actor->health = 10;
            }
            i_this->m2960 |= atInfo.mPlCutBit;
            if (atInfo.mResultingAttackType == 10) {
                i_this->m2A0B = REG13_S(3) + 8;
                atInfo.mDamage = 1;
            } else {
                i_this->m2A0B = 0;
            }
            if (atInfo.mResultingAttackType == 1) {
                sVar3 = i_this->m05D6 - actor->current.angle.y;
                if (sVar3 < 0) {
                    sVar3 = -sVar3;
                }
                if (player->getCutType() == 5) {
                    iVar11 = 2;
                } else if ((u16)sVar3 > 0x4000) {
                    if (atInfo.mbDead != 0) {
                        iVar11 = 3;
                    } else if (iVar12 == 1) {
                        iVar11 = 4;
                    } else {
                        iVar11 = 6;
                    }
                } else if (atInfo.mbDead != 0) {
                    iVar11 = 1;
                } else if (iVar12 == 1) {
                    iVar11 = 4;
                } else {
                    iVar11 = 5;
                }
            } else if (atInfo.mResultingAttackType == 2) {
                iVar11 = 7;
                cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
            } else {
                if (atInfo.mbDead != 0) {
                    iVar11 = 7;
                } else {
                    iVar11 = 4;
                }
                cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
            }
        }
        if ((iVar11 != 0) && (i_this->mMode == 1)) {
            if (rouya_mode != 0) {
                i_this->mDamageReaction.mAction = mo2_class::Action_NAGE_e;
                i_this->mDamageReaction.mMode = -10;
                i_this->m05B4 = 0x32;
                iVar11 = 5;
            } else {
                i_this->mMode = 0;
                i_this->m2A09 = 1;
            }
        }
        switch (iVar11) {
        case 1:
            tex_anm_set(i_this, 4);
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 26.0f;
            cMtx_YrotS(*calc_mtx, i_this->m05D6);
            break;
        case 2:
            tex_anm_set(i_this, 4);
            i_this->mDamageReaction.m424 |= 0x40;
            cMtx_YrotS(*calc_mtx, actor->current.angle.y + 0x8000);
            i_this->mDamageReaction.m428 = 26.0f;
            break;
        case 3:
            tex_anm_set(i_this, 4);
            i_this->mDamageReaction.m424 |= 0x40;
            i_this->mDamageReaction.m428 = 26.0f;
            cMtx_YrotS(*calc_mtx, i_this->m05D6);
            break;
        case 4:
            tex_anm_set(i_this, 1);
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 23.0f;
            cMtx_YrotS(*calc_mtx, i_this->m05D6);
            break;
        case 5:
            tex_anm_set(i_this, 1);
            i_this->mDamageReaction.m424 |= 0x20;
            i_this->mDamageReaction.m428 = 23.0f;
            cMtx_YrotS(*calc_mtx, i_this->m05D6);
            anm_init(i_this, MO2_BCK_PAOMUKE, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_PAOMUKE);
            i_this->mDamageReaction.m48A = 10;
            i_this->mDamageReaction.m474 = 5000.0f;
            i_this->mDamageReaction.m70E = 7;
            if (i_this->m05DA == 0) {
                i_this->m05DA = 3;
                i_this->m05E8.x = 0;
            }
            break;
        case 6:
            tex_anm_set(i_this, 1);
            i_this->mDamageReaction.mAction = mo2_class::Action_HIP_DAMAGE_e;
            i_this->mDamageReaction.mMode = 0;
            i_this->m05B4 = 200;
            if (i_this->m05DA == 0) {
                i_this->m05DA = 10;
                i_this->m05E8.x = -0x4000;
            }
            break;
        case 7:
            tex_anm_set(i_this, 4);
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 26.0f;
        }
        if (i_this->mDamageReaction.m424 != 0) {
            local_54.x = 0.0f;
            local_54.y = 0.0f;
            local_54.z = -10.0f;
            MtxPosition(&local_54, &i_this->mDamageReaction.m42C);
            if (i_this->mDamageReaction.m428 < 25.0f) {
                i_this->mDamageReaction.m4D4 = -l_mo2HIO.m13C;
            } else {
                i_this->mDamageReaction.m428 = cM_rndF(10.0f) + 70.0f;
            }
        }
        if (iVar11 != 0) {
            if ((actor->health <= 0) && (atInfo.mbDead != 0)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_MO_FAINTED, 0);
                if (fopAcM_CheckStatus(actor, fopAcStts_BOSS_e)) {
                    i_this->m2A1D = 0x32;
                }
            } else if (iVar11 == 6) {
                fopAcM_monsSeStart(actor, JA_SE_CV_MO_DAMAGE_HIP, 0);
            } else {
                fopAcM_monsSeStart(actor, JA_SE_CV_MO_DAMAGE, 0);
            }
        }
    }
    return atInfo.mDamage;
}

/* 0000A3FC-0000A788       .text mo2_demo_camera__FP9mo2_class */
static void mo2_demo_camera(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    camera_class* camera2;

    dCam_getCamera();
    dCamera_c* camera = dCam_getBody();
    s8 r28 = true;
    switch (i_this->m2A1D) {
    case 0:
        r28 = false;
        break;
    case 1:
    case 2:
        mDoAud_seStart(JA_SE_MAJU_MO_CHECK, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        dComIfGp_getVibration().StartShock(REG0_S(2) + DEMO_SELECT(6, 4), -0x21, cXyz(0.0f, 1.0f, 0.0f));
        camera_mode = 1;
        camera->SetTrimSize(1);
        i_this->m2A44 = 55.0f;
        i_this->m2A1D = 3;
        i_this->m2A2C = actor->current.pos;
        i_this->m2A38 = REG0_F(8) + 200.0f;
        i_this->m2A3C = 0.0f;
        // Fall-through
    case 3:
        r28 = false;
        camera->SetTypeForce("Restrict", actor);
        camera->SetTrimTypeForce(1);
        break;
    case 10:
        camera->SetTrimSize(0);
        r28 = false;
        dMeter_mtrShow();
        i_this->m2A1D = 0;
        camera_mode = 0;
        break;
    case 0x32:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            r28 = false;
            break;
        }
        camera->Stop();
        camera->SetTrimSize(1);
        i_this->m2A1D = 0x33;
        camera2 = dComIfGp_getCamera(0);
        i_this->m2A20 = camera2->mLookat.mEye;
        i_this->m2A2C = camera2->mLookat.mCenter;
        i_this->m2A44 = 55.0f;
        i_this->m2A1E = 0;
        // Fall-through
    case 0x33:
        cLib_addCalc2(&i_this->m2A44, REG0_F(0xd) + 30.0f, 0.2f, REG0_F(0xe) + 0.4f);
        if (i_this->m2A1C == 0) {
            cLib_addCalc2(&i_this->m2A2C.x, actor->current.pos.x, 0.1f, 100.0f);
            cLib_addCalc2(&i_this->m2A2C.y, actor->current.pos.y + 230.0f + REG0_F(0xc), 0.1f, 100.0f);
            cLib_addCalc2(&i_this->m2A2C.z, actor->current.pos.z, 0.1f, 100.0f);
        }
        i_this->m2A1E++;
        if (i_this->m2A1E > 0x96) {
            camera->SetTrimSize(0);
            camera->Start();
            dMeter_mtrShow();
            dComIfGp_event_reset();
            fopAcM_delete(actor);
            return;
        }
        break;
    }
    if (r28) {
        camera->Set(i_this->m2A2C, i_this->m2A20, i_this->m2A44, 0);
    }
}

/* 0000A788-0000A8C0       .text kantera_get_init__FP9mo2_class */
static s32 kantera_get_init(mo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m2A08 == 0) {
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->base.position = actor->current.pos;
        params->base.angle.y = actor->current.angle.y;
        params->base.parameters = (fopAcM_GetParam(actor) & 0xff000000U) | 0xffff23; // TODO clean up parameters
        params->room_no = fopAcM_GetRoomNo(actor);
        i_this->m02E8 = fopAcM_create(PROC_KANTERA, NULL, params);
        i_this->m2A08++;
    } else if (i_this->m2A08 != 100) {
        kantera_class* kantera = (kantera_class*)fopAcM_SearchByID(i_this->m02E8);
        if (kantera != NULL) {
            kantera->mTargetActorID = fopAcM_GetID(i_this);
            i_this->m2A08 = 100;
            return FALSE;
        }
        i_this->m2A08++;
        if (i_this->m2A08 > 0x14) {
            fopAcM_delete(actor);
        }
        return TRUE;
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 0000A8C0-0000B618       .text daMo2_Execute__FP9mo2_class */
static BOOL daMo2_Execute(mo2_class* i_this) {
    fopEn_enemy_c* actor = &i_this->actor;
    s32 fVar1;
    u8 bVar6;
    int damageReact;
    s16 maxSpeed;
    s16 speedRatio;
    f32 dVar13;
    f32 fVar14;
    f32 fVar16;
    cXyz local_b8;
    cXyz cStack_c4;
    cXyz local_d0;
    cXyz local_dc;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    damageReact = enemy_ice(&i_this->mEnemyIce);
    if (damageReact != 0) {
        i_this->mpMorf->setPlayMode(J3DFrameCtrl::EMode_NONE);
        i_this->mpMorf->setPlaySpeed(3.0f);
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpMorf->calc();
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    enemy_fire(&i_this->mEnemyFire);
    if ((i_this->m2A4B != 0) || (i_this->m2A4C == 1)) {
        dComIfGp_setNextStage("majroom", 0, 0, 0xFF, 0.0f, 0, 1, 0);
        return TRUE;
    }
    if (i_this->m2A4C != 0) {
        i_this->m2A4C--;
        if (i_this->m2A4C == 0x1E) {
            mDoAud_seStop(JA_SE_MAJUTOU_ALERM, 30);
        }
    }
    if ((i_this->m2970 != 0) || (actor->home.pos.y - actor->current.pos.y > 4000.0f)) {
        fopAcM_delete(actor);
        return TRUE;
    }
    if (i_this->m2A4A != 0) {
        if (actor->eventInfo.checkCommandDemoAccrpt()) {
            i_this->m2A4A = 0;
        } else {
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    }
    if (i_this->m2A48 != 0) {
        i_this->m2A48--;
        if (i_this->m2A48 == 0) {
            if (camera_mode == 0) {
                i_this->m2A1D = 1;
            }
            i_this->mDamageReaction.mAction = mo2_class::Action_E3_DEMO_e;
            i_this->mDamageReaction.mMode = 0;
        }
    }
    if ((i_this->mDamageReaction.mAction == mo2_class::Action_JYUNKAI_e) && (player->checkGrabWear())) {
        if (i_this->mDamageReaction.mMode < 2) {
            l_mo2HIO.m02C = REG0_F(10) + 800.0f;
        } else {
            l_mo2HIO.m02C = REG0_F(0xb) + 1200.0f;
        }
        l_mo2HIO.m038 = 0x1932;
        l_mo2HIO.m040.x = 340.0f;
        l_mo2HIO.m040.z = 340.0f;
        l_mo2HIO.m04C = -200.0f;
    }
    bVar6 = 0;
    if (((l_mo2HIO.m006 == 0) || (CPad_CHECK_TRIG_B(0))) || (CPad_CHECK_HOLD_Y(0))) {
        i_this->m059C++;
        for (s32 i = 0; i < 5; i++) {
            if (i_this->m05A4[i] != 0) {
                i_this->m05A4[i]--;
            }
        }
        if (i_this->m05BA != 0) {
            i_this->m05BA--;
        }
        if (i_this->m05BC != 0) {
            i_this->m05BC--;
        }
        if (i_this->m05AE != 0) {
            i_this->m05AE--;
        }
        if (i_this->m02E2 != 0) {
            i_this->m02E2--;
        }
        if (i_this->m05B0 != 0) {
            i_this->m05B0--;
            i_this->m05F0 = l_mo2HIO.m024 + 4;
            i_this->m05F2 = 4;
        }
        if (i_this->mDamageReaction.m48A != 0) {
            i_this->mDamageReaction.m48A--;
        }
        if (i_this->m05B4 != 0) {
            i_this->m05B4--;
        }
        if (i_this->m05B6 != 0) {
            i_this->m05B6--;
        }
        if (((dComIfGs_isCollect(0, 0)) || (dComIfGs_isCollect(0, 1))) || (dComIfGs_isCollect(0, 2) || (dComIfGs_isCollect(0, 3)))) {
            rouya_mode = 0;
        } else {
            rouya_mode = 1;
        }
        if (i_this->m02C1 != 0) {
            if (dComIfGs_isSwitch(i_this->m02C1 - 1, fopAcM_GetRoomNo(actor))) {
                i_this->m02C1 = 0;
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            } else {
                fopAcM_OffStatus(actor, 0);
                actor->attention_info.flags = 0;
                return TRUE;
            }
        }
        fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
        i_this->m0594 = 0;
        i_this->m0598 = 0;
        mo2_eye_tex_anm(i_this);
        i_this->mDamageReaction.m438 = 0;
        if (i_this->m05B2 == 0) {
            i_this->mpMorf->play(&actor->eyePos, 0, 0);
        }
        if (i_this->mDamageReaction.mAction < mo2_class::Action_CARRY_e) {
            i_this->mpMorf->calc();
        }
        bVar6 = damage_check(i_this);
        Mo2_move(i_this);
        mo2_demo_camera(i_this);
        ground_smoke_set(i_this);
        if (i_this->m05B2 != 0) {
            i_this->m05B2--;
        }
        i_this->mDamageReaction.mpEnemy = actor;
        i_this->mDamageReaction.mEnemyType = damagereaction::TYPE_MOBLIN;
    }
    if (i_this->mDamageReaction.mAction != mo2_class::Action_CARRY_DROP_e) {
        actor->shape_angle = actor->current.angle;
    }
    damageReact = damage_reaction(&i_this->mDamageReaction);
    if (damageReact != 0) {
        i_this->m05F0 = 1;
        i_this->m2954 = fpcM_ERROR_PROCESS_ID_e;
        switch (damageReact) {
        case 1:
            anm_init(i_this, MO2_BCK_PAOMUKE, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_PAOMUKE);
            if ((i_this->mbHasInnateWeapon != 0) && ((actor->health <= 0 || (bVar6 >= 4)) || (cM_rndF(1.0f) < 0.5f))) {
                i_this->mSpawnWeaponActor = 1;
            }
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            break;
        case 2:
            anm_init(i_this, MO2_BCK_PUTSUBUSE, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_PUTSUBUSE);
            break;
        case 5:
            if (((i_this->mMode != 1) || (rouya_mode == 0)) &&
                (i_this->mDamageReaction.mAction != mo2_class::Action_FIGHT_RUN_e &&
                 ((i_this->mDamageReaction.mAction != mo2_class::Action_HUKKI_e && (i_this->mDamageReaction.mAction != mo2_class::Action_P_LOST_e)) &&
                  (i_this->m05A4[1] == 0))))
            {
                wait_set(i_this);
                i_this->mDamageReaction.mAction = mo2_class::Action_FIGHT_RUN_e;
                i_this->mDamageReaction.mMode = 0;
                i_this->m05A4[1] = 0x1e;
            }
            i_this->m05DA = 5;
            i_this->m05E8.x = -0x4000;
            break;
        case 10:
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 2;
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            path_check(i_this);
            break;
        case 0x14:
            i_this->m05DA = 1;
            i_this->m05E8.x = -0x4000;
            i_this->m05F0 = l_mo2HIO.m024 + 0x10;
            i_this->m05F2 = 1;
            i_this->mDamageReaction.m4C8[2] = l_mo2HIO.m088;
            break;
        case 0x15:
            i_this->m05DA = 1;
            i_this->m05E8.x = 0;
            i_this->mDamageReaction.m4C8[2] = l_mo2HIO.m088;
            break;
        case 0x1E:
            anm_init(i_this, MO2_BCK_PAOMUKE, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, MO2_BAS_PAOMUKE);
            if (i_this->mbHasInnateWeapon != 0) {
                i_this->mSpawnWeaponActor = 1;
            }
            i_this->mDamageReaction.mAction = mo2_class::Action_JYUNKAI_e;
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_FAINTED, 0);
        }
    }
    J3DModel* pJVar9 = i_this->mpMorf->getModel();
    MtxScale(l_mo2HIO.m010, l_mo2HIO.m010, l_mo2HIO.m010, true);
    pJVar9->setBaseTRMtx(*calc_mtx);
    if (i_this->mDamageReaction.mAction >= mo2_class::Action_CARRY_e) {
        i_this->mpMorf->calc();
    }
    enemy_fire(&i_this->mEnemyFire);
    yari_off_check(i_this);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->current.angle.y);
    local_b8.x = 0.0f;
    local_b8.y = 0.0f;
    local_b8.z = 35.0f;
    MtxPosition(&local_b8, &cStack_c4);
    i_this->mCoCyl.SetC(cStack_c4);
    dComIfG_Ccsp()->Set(&i_this->mCoCyl);
    dComIfG_Ccsp()->SetMass(&i_this->mCoCyl, 3);
    local_d0 = i_this->m28C8;
    local_dc = actor->current.pos;
    if (i_this->m05B4 != 0) {
        local_d0.y = local_d0.y - 20000.0f;
        local_dc.y = local_dc.y - 20000.0f;
    }
    if (i_this->mDamageReaction.mAction == mo2_class::Action_DEFENCE_e) {
        local_d0.y = local_d0.y - 20000.0f;
        local_dc.y = local_dc.y - 100.0f;
    }
    i_this->mTgCyl.SetC(local_dc);
    dComIfG_Ccsp()->Set(&i_this->mTgCyl);
    i_this->mHeadSph.SetC(local_d0);
    dComIfG_Ccsp()->Set(&i_this->mHeadSph);
    if (i_this->m05DA != 0) {
        i_this->m05DA--;
        if (i_this->m05DA == 0) {
            i_this->m05E8.y = actor->current.angle.y;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m28C8, &i_this->m05E8);
        }
    }
    if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
        dBgS_GndChk local_ac;
        cXyz pos;
        s16 sVar3 = 0x7FFF;
        s16 target = 0x7FFF;
        fVar14 = i_this->mDamageReaction.m480 != 0 ? 100.0f : 10.0f;
        dVar13 = fVar14;
        pos = actor->current.pos;
        pos.y += (50.0f - i_this->mDamageReaction.m44C.y);
        local_ac.SetPos(&pos);
        pos.y = dComIfG_Bgsp()->GroundCross(&local_ac);
        if (pos.y != -G_CM3D_F_INF) {
            Vec tmp;
            tmp.x = pos.x;
            tmp.y = pos.y + 50.0f;
            tmp.z = pos.z + fVar14;
            local_ac.SetPos(&tmp);
            fVar16 = dComIfG_Bgsp()->GroundCross(&local_ac);
            if (fVar16 != -G_CM3D_F_INF) {
                sVar3 = -cM_atan2s(fVar16 - pos.y, tmp.z - pos.z);
                if ((sVar3 > 0x2000) || (sVar3 < -0x2000)) {
                    sVar3 = 0;
                }
            }
            tmp.x = pos.x + fVar14;
            tmp.y = pos.y + 50.0f;
            tmp.z = pos.z;
            local_ac.SetPos(&tmp);
            fVar16 = dComIfG_Bgsp()->GroundCross(&local_ac);
            if (fVar16 != -G_CM3D_F_INF) {
                target = (s16)cM_atan2s(fVar16 - pos.y, tmp.x - pos.x);
                if ((target > 0x2000) || (target < -0x2000)) {
                    target = 0;
                }
            }
        }
        if (i_this->mDamageReaction.m480 != 0) {
            maxSpeed = 0x400;
            speedRatio = 1;
        } else {
            maxSpeed = 0x100;
            speedRatio = 8;
        }
        if (sVar3 != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->mDamageReaction.m48C.x, sVar3, speedRatio, maxSpeed);
        }
        if (target != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->mDamageReaction.m48C.z, target, speedRatio, maxSpeed);
        }
    }
    if (i_this->m2944 >= 0) {
        i_this->m2944++;
        if (i_this->m2944 == i_this->m2946) {
            i_this->m294E = i_this->m2948;
        }
        if (i_this->m2944 == i_this->m294A) {
            i_this->m294E = i_this->m294C;
        }
        if (i_this->m2944 > 200) {
            i_this->m2944 = -1;
        }
    }
    fVar1 = i_this->mParryOpeningType;
    actor->setBtStartFrame(0.0f);
    actor->setBtEndFrame(10.0f);
    actor->setBtMaxDis(10000.0f);
    actor->setBtAttackType(fVar1);
    actor->setBtMaxDis(l_mo2HIO.m140);
    if (i_this->m294E != 0) {
        i_this->m294E--;
        actor->setBtNowFrame(5.0f);
    } else {
        actor->setBtNowFrame(100.0f);
    }
    return TRUE;
}

/* 0000B618-0000B620       .text daMo2_IsDelete__FP9mo2_class */
static BOOL daMo2_IsDelete(mo2_class*) {
    return TRUE;
}

/* 0000B620-0000B720       .text daMo2_Delete__FP9mo2_class */
static BOOL daMo2_Delete(mo2_class* i_this) {
#if VERSION > VERSION_DEMO
    fopAc_ac_c* actor = &i_this->actor;
#endif
    dComIfG_resDeleteDemo(&i_this->mPhsMo2, "Mo2");
    dComIfG_resDeleteDemo(&i_this->mPhsSpear, "Spear");
    if (i_this->m2A0A != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_mo2HIO.mNo);
        camera_mode = 0;
    }
#if VERSION > VERSION_DEMO
    if (actor->heap != NULL) {
        i_this->mpMorf->stopZelAnime();
    }
#endif
    i_this->m05F4.remove();
    i_this->mDamageReaction.mParticleCallBack.remove();
    enemy_fire_remove(&i_this->mEnemyFire);
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&i_this->m28D4);
    mDoAud_seDeleteObject(&i_this->m2934);
#endif
    return TRUE;
}

/* 0000B720-0000B784       .text useArrowHeapInit__FP10fopAc_ac_c */
static u8 useArrowHeapInit(fopAc_ac_c* a_this) {
    static Vec kosi_cyl_offset[] = {
        {0.0f, 20.0f, 20.0f},
        {0.0f, 0.0f, 20.0f},
    };
    static Vec mata_cyl_offset[] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, -20.0f, 0.0f},
    };
    static Vec mune_cyl_offset[] = {
        {40.0f, 20.0f, 0.0f},
        {0.0f, 20.0f, 0.0f},
    };
    static Vec kata_l_sph_offset[] = {{10.0f, -10.0f, 0.0f}};
    static Vec ude_cyl_offset[] = {
        {85.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };
    static Vec te_cyl_offset[] = {
        {50.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };
    static Vec momo_cyl_offset[] = {
        {20.0f, 0.0f, 0.0f},
        {5.0f, 0.0f, 0.0f},
    };
    static Vec asi_cyl_offset[] = {
        {25.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x01,
            /* mRadius     */ 25.0f,
            /* mpOffsets   */ kosi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x02,
            /* mRadius     */ 25.0f,
            /* mpOffsets   */ mata_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x03,
            /* mRadius     */ 35.0f,
            /* mpOffsets   */ mune_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x0A,
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ kata_l_sph_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0A,
            /* mRadius     */ 10.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0B,
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ te_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x11,
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ kata_l_sph_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x11,
            /* mRadius     */ 10.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x12,
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ te_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x27,
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ momo_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x28,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x29,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x2C,
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ momo_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x2D,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x2E,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
    };
    mo2_class* i_this = (mo2_class*)a_this;
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mpJntHit = JntHit_create(i_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (i_this->mpJntHit != NULL) {
        actor->jntHit = i_this->mpJntHit;
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 0000B784-0000BAFC       .text createHeap__FP10fopAc_ac_c */
static BOOL createHeap(fopAc_ac_c* a_this) {
    mo2_class* i_this = (mo2_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Mo2", MO2_BDL_MO),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Mo2", MO2_BCK_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        dComIfG_getObjectRes("Mo2", MO2_BAS_WAIT),
        0x00080000,
        0x37441422
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    J3DModel* model = i_this->mpMorf->getModel();
    for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
        s32 r3 = joint_check[i];
        if (r3 < 0) {
            continue;
        }
        if (r3 == 0x0E || r3 == 0x0F || r3 == 0x10 || r3 == 0x11 || r3 == 0x14) {
            model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_P);
        } else {
            model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }
    if (i_this->mMode != 1) {
        i_this->m2A50 = (J3DMaterialTable*)dComIfG_getObjectRes("Mo2", MO2_BMT_MO_GREEN);
    }
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Mo2", mo2_tex_anm_idx[3]));
    JUT_ASSERT(DEMO_SELECT(8843, 8863), btp);
    if (!i_this->m02C8.init(i_this->mpMorf->getModel()->getModelData(), btp, FALSE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    i_this->m3Dline.init(16, 10, 0);
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mo2", MO2_BMD_KB);
    JUT_ASSERT(DEMO_SELECT(8881, 8901), modelData != NULL);
    J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Mo2", MO2_BMT_MO_BLUR);
    modelData->setMaterialTable(bmt, J3DMatCopyFlag_Material);
    i_this->m058C = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m058C == NULL) {
        return FALSE;
    }
    i_this->m058C->setBaseScale(a_this->scale);
    if (useArrowHeapInit(a_this)) {
        return TRUE;
    }
    return FALSE;
}

/* 0000BAFC-0000C148       .text daMo2_Create__FP10fopAc_ac_c */
static cPhs_State daMo2_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 90.0f,
            /* Height */ 125.0f,
        }},
    };
    static dCcD_SrcCyl tg_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Unk1_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 45.0f,
            /* Height */ 137.5f,
        }},
    };
    static dCcD_SrcSph head_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Unk1_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 55.0f,
        }},
    };
    static dCcD_SrcSph wepon_sph_src = {
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
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
        }},
    };
    static dCcD_SrcSph wepon2_sph_src = {
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
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph defence_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK6,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };

    static u8 fire_j[] = {0x1A, 0x03, 0x11, 0x12, 0x0A, 0x0B, 0x2C, 0x2D, 0x27, 0x28};
    static f32 fire_sc[] = {2.3f, 2.3f, 1.4f, 1.2f, 1.4f, 1.2f, 1.4f, 1.2f, 1.4f, 1.2f};

    fopAcM_SetupActor(a_this, mo2_class);
    mo2_class* i_this = (mo2_class*)a_this;
    cPhs_State res = dComIfG_resLoad(&i_this->mPhsSpear, "Spear");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    cPhs_State res2 = dComIfG_resLoad(&i_this->mPhsMo2, "Mo2");
    if (res2 != cPhs_COMPLEATE_e) {
        return res2;
    }
    i_this->mMode = fopAcM_GetParam(a_this);
    if ((i_this->mMode == 1) && (kantera_get_init(i_this) != 0)) {
        return cPhs_INIT_e;
    }
    a_this->gbaName = 2;
    if ((!strcmp(dComIfGp_getStartStageName(), "ITest63")) || (!strcmp(dComIfGp_getStartStageName(), "GanonJ"))) {
        search_sp = 1;
    } else {
        search_sp = 0;
    }
    i_this->mFrozenInTimePose = (fopAcM_GetParam(a_this) >> 8);
    i_this->mPathIndex = (fopAcM_GetParam(a_this) >> 0x10);
    i_this->mEnableSpawnSwitch = (fopAcM_GetParam(a_this) >> 0x18);
    i_this->mDeathSwitch = a_this->current.angle.z;
    a_this->current.angle.z = 0;
    a_this->current.angle.x = 0;
    if (i_this->mDeathSwitch == 0xFF) {
        i_this->mDeathSwitch = 0;
    }
    if ((i_this->mDeathSwitch != 0) && (i_this->mDeathSwitch <= 0x7F)) {
        fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
        search_sp = 1;
    }
    if (((dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101)) && (i_this->mDeathSwitch != 0)) &&
        (dComIfGs_isSwitch(i_this->mDeathSwitch, fopAcM_GetRoomNo(a_this))))
    {
        return cPhs_ERROR_e;
    }
    if (!strcmp(dComIfGp_getStartStageName(), "Hyroom")) {
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex2("mo2", 1);
    } else {
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("mo2", 0);
    }
    if (!fopAcM_entrySolidHeap(a_this, createHeap, 0)) {
        return cPhs_ERROR_e;
    }
    if (hio_set == 0) {
        l_mo2HIO.mNo = mDoHIO_createChild("モ２", &l_mo2HIO); // Mo 2
        l_mo2HIO.m020 = 0;
        camera_mode = 0;
        i_this->m2A0A = 1;
        hio_set = 1;
        alerm_set = 0;
    }
    fopAcM_SetMin(a_this, -200.0f, -50.0f, -100.0f);
    fopAcM_SetMax(a_this, 125.0f, 250.0f, 250.0f);
    fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
    i_this->mpMorf->getModel()->setUserArea((u32)a_this);
    i_this->actor.setBtHeight(162.5f);
    i_this->actor.setBtBodyR(125.0f);
    i_this->mDamageReaction.m70C = 1;
    i_this->mDamageReaction.mSpawnY = a_this->current.pos.y;
    i_this->mDamageReaction.mMaxFallDistance = 1000.0f;
    i_this->mbHasInnateWeapon = 1;
    i_this->mDamageReaction.mInvincibleTimer = 5;
#if VERSION == VERSION_DEMO
    if (((dComIfGs_isCollect(0, 0)) || (dComIfGs_isCollect(0, 1))) || (dComIfGs_isCollect(0, 2)))
#else
    if (((dComIfGs_isCollect(0, 0)) || (dComIfGs_isCollect(0, 1))) || (dComIfGs_isCollect(0, 2) || (dComIfGs_isCollect(0, 3))))
#endif
    {
        rouya_mode = 0;
    } else {
        rouya_mode = 1;
    }
    if ((i_this->mMode != 1) || (rouya_mode == 0)) {
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    }
    if (i_this->mMode == 5) {
        anm_init(i_this, MO2_BCK_BB_FLY, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, MO2_BAS_BB_FLY);
        i_this->mDamageReaction.mAction = mo2_class::Action_CARRY_e;
        i_this->mDamageReaction.mMaxFallDistance = 100000.0f;
    }
    if (i_this->mPathIndex != 0xFF) {
        i_this->ppd = dPath_GetRoomPath(i_this->mPathIndex, fopAcM_GetRoomNo(a_this));
        if (i_this->ppd == NULL) {
            return cPhs_ERROR_e;
        }
        i_this->m2968 = i_this->mPathIndex + 1;
        i_this->mHasPath = 1;
    }
    if (i_this->mEnableSpawnSwitch != 0xFF) {
        i_this->m02C1 = i_this->mEnableSpawnSwitch + 1;
    }
    if (i_this->mMode == 0xf) {
        i_this->mDamageReaction.mAction = mo2_class::Action_D_DOZOU_e;
        i_this->m02C1 = 0;
    }
    i_this->mDamageReaction.mAcch.Set(
        fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mDamageReaction.mAcchCir, fopAcM_GetSpeed_p(a_this)
    );
    i_this->mDamageReaction.mAcchCir.SetWall(50.0f, 50.0f);
    i_this->mDamageReaction.mAcch.ClrRoofNone();
    i_this->mDamageReaction.mAcch.m_roof_crr_height = REG0_F(7) + 100.0f;
    a_this->health = 10;
    a_this->max_health = 10;
    i_this->mDamageReaction.mStts.Init(200, 0xFF, a_this);
    i_this->mCoCyl.Set(co_cyl_src);
    i_this->mCoCyl.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mTgCyl.Set(tg_cyl_src);
    i_this->mTgCyl.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mHeadSph.Set(head_sph_src);
    i_this->mHeadSph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mWeaponSph.Set(wepon_sph_src);
    i_this->mWeaponSph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mWeapon2Sph.Set(wepon2_sph_src);
    i_this->mWeapon2Sph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mWeaponSph.SetAtHitCallback(AtHitCallback);
    i_this->mWeapon2Sph.SetAtHitCallback(AtHitCallback);
    i_this->mDefenseSph.Set(defence_sph_src);
    i_this->mDefenseSph.SetStts(&i_this->mDamageReaction.mStts);
    a_this->model = i_this->mpMorf->getModel();
    i_this->mEnemyIce.mpActor = a_this;
    i_this->mEnemyIce.mWallRadius = REG0_F(6) + 70.0f;
    i_this->mEnemyIce.mCylHeight = REG0_F(7) + 200.0f;
    i_this->mEnemyIce.mParticleScale = 1.5f;
    i_this->mEnemyIce.mDeathSwitch = i_this->mDeathSwitch;
    i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
    i_this->mEnemyFire.mpActor = a_this;
    for (s32 i = 0; i < 10; i++) {
        i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
        i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
    }
    a_this->stealItemLeft = 5;
    // !@bug(?): Why is this function called twice?
    daMo2_Execute(i_this);
#if VERSION > VERSION_DEMO
    daMo2_Execute(i_this);
#endif
    return res2;
}

static actor_method_class l_daMo2_Method = {
    (process_method_func)daMo2_Create,
    (process_method_func)daMo2_Delete,
    (process_method_func)daMo2_Execute,
    (process_method_func)daMo2_IsDelete,
    (process_method_func)daMo2_Draw,
};

actor_process_profile_definition g_profile_MO2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MO2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mo2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MO2,
    /* Actor SubMtd */ &l_daMo2_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
