/**
 * d_a_bk.cpp
 * Enemy - Bokoblin
 */

#include "d/actor/d_a_bk.h"
#include "d/res/res_bk.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_obj_search.h"
#include "d/actor/d_a_item.h"
#include "d/d_item_data.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_obj_search.h"
#include "d/d_bg_s_lin_chk.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"
#include "d/d_path.h"
#include "d/d_jnt_hit.h"
#include "d/d_cc_uty.h"
#include "d/d_material.h"
#include "d/d_snap.h"
#include "JSystem/JUtility/JUTReport.h"

static u8 dummy[0x49];

static u8 hio_set;
static u8 another_hit;
static u32 ken;
static s8 search_sp;
static bkHIO_c l_bkHIO;

// Needed for the .data section to match.
static Vec dummy_2100 = {1.0f, 1.0f, 1.0f};
static Vec dummy_2080 = {1.0f, 1.0f, 1.0f};
static u8 dummy_1811[] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static int bk_at_kind[] = { 0, 1, 0 };
static int bk_attack_ready_SE[] = { JA_SE_CV_BK_KAMAE, JA_SE_CV_BK_KAMAE, -0xDCF }; // TODO what is -0xDCF?
static int bk_attack_go_SE[] = { JA_SE_CV_BK_ATTACK_S, JA_SE_CV_BK_ATTACK_L, -0xDCF }; // TODO what is -0xDCF?
static int bk_attack_AP[] = { 1, 2, 1 };
static f32 br_set_tm[] = { -100.0f, -100.0f, -100.0f };

struct attack_info_s {
    /* 0x00 */ int bckFileIdx;
    /* 0x04 */ f32 speed;
    /* 0x08 */ int soundFileIdx;
};

static attack_info_s attack1_info[] = {
    { BK_BCK_BK_ATTACK1, 1.2f, BK_BAS_BK_ATTACK1 },
    { BK_BCK_BK_ATTACK2, 1.0f, BK_BAS_BK_ATTACK2 },
    { BK_BCK_BK_ATTACK3, 1.0f, BK_BAS_BK_ATTACK3 },
};

static attack_info_s jattack1_info[] = {
    { BK_BCK_BK_JATTACK1, 1.0f, -1 },
    { BK_BCK_BK_JATTACK2, 1.0f, BK_BAS_BK_JATTACK2 },
    { BK_BCK_BK_JATTACK3, 1.0f, BK_BAS_BK_JATTACK3 },
};

static attack_info_s kattack1_info[] = {
    { BK_BCK_BK_KERI1, 1.0f, BK_BAS_BK_KERI1 },
    { BK_BCK_BK_KERI2, 1.0f, BK_BAS_BK_KERI2 },
    { -BK_BTP_TMABATAKI, 1.0f, 0 }, // TODO: why is bckFileIdx negative and soundFileIdx zero? bug?
};

static attack_info_s* attack_info[] = {
    attack1_info,
    jattack1_info,
    kattack1_info,
};

static s8 joint_check[] = {
      -1,   -1, 0x0B, 0x07, 0x03, 0x0F,   -1, 0x0A, 0x06, 0x02, 0x0E,   -1,   -1,   -1,   -1,   -1,
    0x0C, 0x0D, 0x12, 0x32,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
    0x09, 0x05, 0x01, 0x11,   -1,   -1,   -1,   -1, 0x08, 0x04, 0x00, 0x10,   -1,   -1,   -1,   -1,
      -1,   -1,   -1, 0x13, 
};

/* 000000EC-00000234       .text anm_init__FP8bk_classifUcfi */
static void anm_init(bk_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (i_this->dr.mState == 0x13 && bckFileIdx != BK_BCK_BK_OTISOU1 && bckFileIdx != BK_BCK_BK_OTISOU2) {
        return;
    }
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("Bk", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Bk", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Bk", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000234-000005A8       .text yari_off_check__FP8bk_class */
static void yari_off_check(bk_class* i_this) {
    if (i_this->m0B34 == 0) {
        return;
    }
    
    daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(i_this->m1200);
    if (boko) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        fopAcM_cancelCarryNow(boko);
        
        if (i_this->m0B34 != 2) {
            boko->setRotAngleSpeed(cM_rndFX(2000.0f));
            s16 angleY = i_this->shape_angle.y + 0x8000 + (s16)cM_rndFX(8000.0f);
            f32 speedY = 20.0f + cM_rndF(20.0f);
            f32 speedForward = 20.0f + cM_rndF(10.0f);
            boko->moveStateInit(speedForward, speedY, angleY);
        }
        boko->current.angle.y = player->shape_angle.y;
        
        dBgS_LinChk linChk;
        linChk.Set(&i_this->eyePos, &boko->current.pos, i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            MtxP mtx = i_this->mpMorf->getModel()->getAnmMtx(0x10); // mune (chest) joint
            MTXCopy(mtx, *calc_mtx);
            boko->setMatrix(*calc_mtx);
            cXyz offset;
            offset.set(0.0f, 0.0f, 0.0f);
            MtxPosition(&offset, &boko->current.pos);
        }
    }
    
    i_this->m121F = 1;
    i_this->m0B34 = 0;
    i_this->m0B30 = 0;
}

/* 00000A1C-00000EE8       .text smoke_set_s__FP8bk_classf */
static void smoke_set_s(bk_class* i_this, f32 rate) {
    fopAc_ac_c* i_actor = i_this;
    dBgS_LinChk linChk;
    s32 attribCode;
    attribCode = 0;
    cXyz startPos = i_this->m0338;
    startPos.y += 100.0f;
    cXyz endPos = i_this->m0338;
    endPos.y -= 100.0f;
    linChk.Set(&startPos, &endPos, i_actor);
    
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        endPos = linChk.GetCross();
        i_this->m0338.y = endPos.y;
        attribCode = dComIfG_Bgsp()->GetAttributeCode(linChk);
    } else {
        i_this->m0338.y -= 20000.0f;
    }
    
    if (i_this->m034F != 0 && attribCode != dBgS_Attr_GRASS_e) {
        return;
    }
    
    i_this->m034F++;
    
    switch (attribCode) {
    case dBgS_Attr_NORMAL_e:
    case dBgS_Attr_DIRT_e:
    case dBgS_Attr_WOOD_e:
    case dBgS_Attr_STONE_e:
    case dBgS_Attr_SAND_e:
        i_this->m0350.end();
        JPABaseEmitter* emitter1 = dComIfGp_particle_setToon(
            0x2022, &i_this->m0338, &i_this->m0344, NULL, 0xB9,
            &i_this->m0350, fopAcM_GetRoomNo(i_this)
        );
        if (emitter1) {
            emitter1->setRate(rate);
            emitter1->setSpread(1.0f);
            JGeometry::TVec3<f32> scale;
            scale.x = scale.y = scale.z = 1.2f;
            emitter1->setGlobalScale(scale);
            scale.x = scale.y = scale.z = 1.5f + g_regHIO.mChild[0].mFloatRegs[16];
            emitter1->setGlobalParticleScale(scale);
        }
        break;
    case dBgS_Attr_GRASS_e:
        JPABaseEmitter* emitter2 = dComIfGp_particle_set(0x24, &i_this->m0338, &i_this->m0344);
        if (emitter2) {
            emitter2->setRate(rate * 0.5f);
            emitter2->setMaxFrame(3);
        }
        break;
    }
}

/* 00000EE8-000011F0       .text ground_smoke_set__FP8bk_class */
static void ground_smoke_set(bk_class* i_this) {
    if (i_this->m034C == 0) {
        return;
    }
    
    i_this->m034C--;
    
    if (i_this->m034C >= l_bkHIO.m00C) {
        i_this->m0344.x = 0;
        i_this->m0344.z = 0;
        cXyz sp8;
        sp8.x = 0.0f;
        sp8.y = 0.0f;
        MtxTrans(i_this->current.pos.x, i_this->current.pos.y + 7.5f, i_this->current.pos.z, 0);
        if (i_this->m034E == 0) {
            sp8.z = -350.0f;
            cMtx_YrotM(*calc_mtx, i_this->m034A);
            MtxPosition(&sp8, &i_this->m0338);
            i_this->m0344.y = i_this->m034A;
            smoke_set_s(i_this, 6.0f);
            i_this->m034A = i_this->m034A + 2000 + g_regHIO.mChild[0].mShortRegs[7];
        } else if (i_this->m034E == 1) {
            cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
            cMtx_YrotM(*calc_mtx, i_this->m034A);
            sp8.z = -55.0f;
            MtxPosition(&sp8, &i_this->m0338);
            i_this->m0344.y = i_this->m034A;
            smoke_set_s(i_this, 5.0f);
            i_this->m034A += 0x1FA0;
        } else if (i_this->m034E == 2) {
            MtxTrans(i_this->m11A8.x, i_this->m11A8.y + 7.5f, i_this->m11A8.z, 0);
            cMtx_YrotM(*calc_mtx, i_this->m034A);
            sp8.z = -12.5f;
            MtxPosition(&sp8, &i_this->m0338);
            i_this->m0344.y = i_this->m034A;
            smoke_set_s(i_this, 6.0f);
            i_this->m034A += 0x2000;
        } else if (i_this->m034E == 3) {
            cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
            cMtx_YrotM(*calc_mtx, i_this->m034A);
            sp8.z = -37.5f;
            MtxPosition(&sp8, &i_this->m0338);
            i_this->m0344.y = i_this->m034A;
            smoke_set_s(i_this, 2.0f);
            i_this->m034A += 0x1FA0;
        } else if (i_this->m034E == 4) {
            if (i_this->m02F8 & 1) {
                i_this->m0338 = i_this->dr.m100[14];
            } else {
                i_this->m0338 = i_this->dr.m100[15];
            }
            if (i_this->dr.m712 != 0) {
                i_this->m0338.y = 512.5f;
            } else {
                i_this->m0338.y -= 12.5f;
            }
            i_this->m0344.y = cM_atan2s(i_this->speed.x, i_this->speed.z);
            smoke_set_s(i_this, 1.0f);
        }
    } else {
        i_this->m0338.y = i_this->dr.mSpawnY + 25000.0f;
    }
    
    if (i_this->m034C == 0) {
        i_this->m0350.end();
        i_this->m034F = 0;
    }
}

/* 000011F0-00001454       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r28 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        bk_class* i_this = (bk_class*)model->getUserArea();
        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 0x13) { // ago joint
                mDoMtx_ZrotM(*calc_mtx, i_this->m11F4);
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else {
                mDoMtx_YrotM(*calc_mtx, i_this->dr.m088[r28].y);
                mDoMtx_XrotM(*calc_mtx, i_this->dr.m088[r28].x);
                mDoMtx_ZrotM(*calc_mtx, i_this->dr.m088[r28].z);
                
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
                
                cXyz offset;
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                cXyz sp08;
                if (r28 == 0x00 || r28 == 0x01 || r28 == 0x02 || r28 == 0x03 || r28 == 0x04 ||
                    r28 == 0x05 || r28 == 0x06 || r28 == 0x07
                ) {
                    offset.x = 0.0f;
                } else if (r28 == 0x12) {
                    offset.x = 200.0f;
                    offset.y = -100.0f;
                    MtxPosition(&offset, &sp08);
                    offset.x = 0.0f;
                    offset.y = 0.0f;
                    MtxPosition(&offset, &i_this->eyePos);
                    i_this->attention_info.position = i_this->eyePos;
                    i_this->attention_info.position.y += l_bkHIO.m024;
                    if (l_bkHIO.m009 == 0) {
                        i_this->m0330 = cM_atan2s(sp08.x - i_this->eyePos.x, sp08.z - i_this->eyePos.z);
                    } else {
                        i_this->m0330 = i_this->current.angle.y;
                    }
                    offset.x = 20.75f;
                    offset.y = 18.5f;
                    offset.z = 0.0f;
                    MtxPosition(&offset, &i_this->m116C);
                    offset.y = -45.0f;
                }
                MtxPosition(&offset, &i_this->dr.m100[r28]);
            }
        }
    }
    return TRUE;
}

/* 00001454-00001564       .text nodeCallBack_P__FP7J3DNodei */
static BOOL nodeCallBack_P(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r30 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        bk_class* i_this = (bk_class*)model->getUserArea();
        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            offset.x = 0.0f;
            offset.z = 0.0f;
            offset.y = 0.0f;
            if (r30 == 0x11) {
                offset.x = 17.5f;
                offset.y = -8.75f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m1190);
            } else if (r30 == 0x10) {
                MtxPosition(&offset, &i_this->m119C);
            } else if (r30 == 0x0E || r30 == 0x0F) {
                offset.y = 25.0f;
            } else {
                offset.y = 0.0f;
            }
            MtxPosition(&offset, &i_this->dr.m100[r30]);
        }
    }
    return TRUE;
}

/* 00001564-000019A4       .text search_check_draw__FP8bk_class */
static void search_check_draw(bk_class* i_this) {
    if (l_bkHIO.m005 == 0) {
        return;
    }
    cXyz sp14[0x10];
    cXyz sp08(0.0f, 0.0f, l_bkHIO.m028);
    int i;
    s16 r26 = 0;
    for (i = 0; i < 0x10; i++, r26 += 0x1000) {
        MtxTrans(i_this->current.pos.x, 2.5f + i_this->dr.mSpawnY, i_this->current.pos.z, 0);
        mDoMtx_YrotM(*calc_mtx, r26);
        MtxPosition(&sp08, &sp14[0]);
        mDoMtx_YrotM(*calc_mtx, 0x1000);
        MtxPosition(&sp08, &sp14[1]);
    }
    sp08.z = l_bkHIO.m02C;
    for (i = 0; i < 0x10; i++, r26 += 0x1000) {
        MtxTrans(i_this->current.pos.x, 2.5f + i_this->dr.mSpawnY, i_this->current.pos.z, 0);
        mDoMtx_YrotM(*calc_mtx, (int)r26);
        MtxPosition(&sp08, &sp14[0]);
        mDoMtx_YrotM(*calc_mtx, 0x1000);
        MtxPosition(&sp08, &sp14[1]);
    }
    
    sp08.x = 0.0f;
    sp08.z = l_bkHIO.m028;
    MtxTrans(i_this->eyePos.x, i_this->eyePos.y, i_this->eyePos.z, 0);
    
    MtxPush();
    mDoMtx_YrotM(*calc_mtx, i_this->m0330 - l_bkHIO.m034);
    sp08.y = l_bkHIO.m038;
    MtxPosition(&sp08, &sp14[1]);
    MtxPull();
    
    MtxPush();
    sp08.y = l_bkHIO.m038;
    mDoMtx_YrotM(*calc_mtx, i_this->m0330 + l_bkHIO.m034);
    MtxPosition(&sp08, &sp14[2]);
    MtxPull();
    
    MtxPush();
    mDoMtx_YrotM(*calc_mtx, i_this->m0330 - l_bkHIO.m034);
    sp08.y = -l_bkHIO.m038;
    MtxPosition(&sp08, &sp14[4]);
    MtxPull();
    
    sp08.y = -l_bkHIO.m038;
    mDoMtx_YrotM(*calc_mtx, i_this->m0330 + l_bkHIO.m034);
    MtxPosition(&sp08, &sp14[5]);
    
    sp14[0] = i_this->eyePos;
    sp14[0].y += l_bkHIO.m038;
    sp14[3] = i_this->eyePos;
    sp14[3].y -= l_bkHIO.m038;
    sp08.x = 0.0f;
    sp08.z = l_bkHIO.m02C;
    MtxTrans(i_this->eyePos.x, i_this->eyePos.y, i_this->eyePos.z, 0);
    mDoMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    
    sp08.x = l_bkHIO.m03C;
    sp08.y = l_bkHIO.m040;
    sp08.z = l_bkHIO.m044;
    MtxPosition(&sp08, &sp14[7]);
    sp08.y = -l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[5]);
    sp08.x = -l_bkHIO.m03C;
    sp08.y = l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[6]);
    sp08.y = -l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[4]);
    sp08.x = l_bkHIO.m03C;
    sp08.y = l_bkHIO.m040;
    sp08.z = l_bkHIO.m048;
    MtxPosition(&sp08, &sp14[1]);
    sp08.y = -l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[3]);
    sp08.x = -l_bkHIO.m03C;
    sp08.y = l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[0]);
    sp08.y = -l_bkHIO.m040;
    MtxPosition(&sp08, &sp14[2]);
}

/* 000019A8-00001B88       .text br_draw__FP8bk_class */
static void br_draw(bk_class* i_this) {
    if (i_this->m02F0 == 0) {
        return;
    }
    if (g_regHIO.mChild[6].mShortRegs[3] != 0) {
        return;
    }
    
    J3DModel* model = i_this->m02E8;
    for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
        J3DMaterial* mat = model->getModelData()->getJointNodePointer(i)->getMesh();
        while (mat) {
            J3DShape* shape = mat->getShape();
            if (i_this->m02F4 == 0) {
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
    
    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x2C), *calc_mtx);
    MtxTrans(150.0f + l_bkHIO.m100, g_regHIO.mChild[8].mFloatRegs[1], g_regHIO.mChild[8].mFloatRegs[2], 1);
    s16 angleX = g_regHIO.mChild[8].mShortRegs[6] + 0x4000;
    cMtx_XrotM(*calc_mtx, angleX);
    s16 angleZ = g_regHIO.mChild[8].mShortRegs[7] + 0x4000;
    cMtx_ZrotM(*calc_mtx, angleZ);
    MtxScale(l_bkHIO.m018 * i_this->m02EC, l_bkHIO.m018, l_bkHIO.m018, 1);
    model->setBaseTRMtx(*calc_mtx);
    
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    mDoExt_modelUpdateDL(model);
}

/* 00001B88-00001CD0       .text daBk_shadowDraw__FP8bk_class */
static void daBk_shadowDraw(bk_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    if (!fopAcM_checkCarryNow(i_this)) {
        cXyz shadowPos(
            i_this->current.pos.x,
            i_this->current.pos.y + 150.0f + g_regHIO.mChild[8].mFloatRegs[18],
            i_this->current.pos.z
        );
        f32 temp = 800.0f + g_regHIO.mChild[8].mFloatRegs[19];
        f32 shadowSize = 40.0f + g_regHIO.mChild[8].mFloatRegs[17];
        i_this->mShadowId = dComIfGd_setShadow(
            i_this->mShadowId, 1, model, &shadowPos, temp, shadowSize,
            i_this->current.pos.y, i_this->dr.mAcch.GetGroundH(),
            i_this->dr.mAcch.m_gnd, &i_this->tevStr,
            0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
        );
    }
    
    if (i_this->mShadowId) {
        daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(i_this->m1200);
        if (boko) {
            dComIfGd_addRealShadow(i_this->mShadowId, boko->model);
        }
        if (i_this->m02D4) {
            dComIfGd_addRealShadow(i_this->mShadowId, i_this->m02D0);
        }
        if (i_this->m02DC) {
            dComIfGd_addRealShadow(i_this->mShadowId, i_this->m02D8);
        }
    }
}

/* 00001CD0-00001F60       .text daBk_Draw__FP8bk_class */
static BOOL daBk_Draw(bk_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    if (i_this->m02B7 != 0xFF && i_this->mType == 6 && dComIfGs_isSwitch(i_this->m02B7, dComIfGp_roomControl_getStayNo())) {
        return TRUE;
    }
    if (i_this->m02BA != 0 || i_this->mType == 8 || i_this->m121C != 0 || i_this->m02DE != 0) {
        return TRUE;
    }
    
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        daBk_shadowDraw(i_this);
        return TRUE;
    }
    
    br_draw(i_this);
    
    search_check_draw(i_this);
    
    J3DModelData* modelData = model->getModelData();
    J3DJoint* rootJoint = modelData->getJointNodePointer(0x00);
    J3DShape* eyeShape = modelData->getMaterialNodePointer(0x00)->getShape();
    J3DShape* hatShape = modelData->getMaterialNodePointer(0x01)->getShape();
    J3DShape* bodyShape = modelData->getMaterialNodePointer(0x02)->getShape();
    eyeShape->hide();
    i_this->m02C4->entry(model->getModelData());
    if (i_this->m1230) {
        i_this->mpMorf->entryDL(i_this->m1230);
    } else {
        i_this->mpMorf->entryDL();
    }
    dComIfGd_setListMaskOff();
    eyeShape->show();
    model->getMatPacket(0x00)->unlock();
    hatShape->hide();
    bodyShape->hide();
    rootJoint->entryIn();
    hatShape->show();
    bodyShape->show();
    dComIfGd_setList();
    
    daBk_shadowDraw(i_this);
    
    if (i_this->m02D4 != 0) {
        g_env_light.setLightTevColorType(i_this->m02D0, &i_this->tevStr);
        mDoExt_modelUpdateDL(i_this->m02D0);
    }
    
    if (i_this->m02DC != 0) {
        g_env_light.setLightTevColorType(i_this->m02D8, &i_this->tevStr);
        mDoExt_modelUpdateDL(i_this->m02D8);
    }
    
    dSnap_RegistFig(DSNAP_TYPE_BK, i_this, 1.0f, 1.0f, 1.0f);
    
    return TRUE;
}

/* 00001F60-00002404       .text way_pos_check__FP8bk_classP4cXyz */
static void way_pos_check(bk_class* i_this, cXyz* r31) {
    fopAc_ac_c* i_actor = i_this;
    dBgS_LinChk linChk;
    dBgS_GndChk gndChk;
    cXyz sp2C;
    cXyz sp20;
    cXyz sp14;
    cXyz sp08;
    sp2C.x = 0.0f;
    sp2C.y = 50.0f;
    sp14 = i_this->current.pos;
    sp14.y += 50.0f;
    for (int i = 0; i < 100; i++) {
        sp2C.z = 300.0f + cM_rndF(200.0f);
        MtxRotY(cM_rndF(M_PI*2), 0);
        MtxPosition(&sp2C, &sp20);
        sp08.x = i_this->current.pos.x + sp20.x;
        sp08.y = i_this->current.pos.y + sp20.y;
        sp08.z = i_this->current.pos.z + sp20.z;
        *r31 = sp08;
        linChk.Set(&sp14, &sp08, i_actor);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            gndChk.SetPos(&sp08);
            if (i_this->dr.mAcch.GetGroundH() - dComIfG_Bgsp()->GroundCross(&gndChk) < 200.0f) {
                break;
            }
        }
    }
}

/* 0000259C-00002864       .text ground_4_check__FP8bk_classisf */
static u8 ground_4_check(bk_class* i_this, int r18, s16 r20, f32 f29) {
    static f32 xad[] = {
        0.0f, 0.0f, 1.0f, -1.0f,
    };
    static f32 zad[] = {
        1.0f, -1.0f, 0.0f, 0.0f,
    };
    static u8 check_bit[] = {
        0x01, 0x02, 0x04, 0x08,
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
        sp8 += i_this->current.pos;
        gndChk.SetPos(&sp8);
        sp8.y = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (sp8.y == -1e9f) {
            sp8.y = 1e9f;
        }
        if (i_this->dr.mAcch.GetGroundH() - sp8.y > 200.0f) {
            r19 |= check_bit[i];
        }
    }
    return r19;
}

/* 00002864-00002C4C       .text daBk_other_bg_check__FP8bk_classP10fopAc_ac_c */
static BOOL daBk_other_bg_check(bk_class* i_this, fopAc_ac_c* r23) {
    fopAc_ac_c* i_actor = i_this;
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    if (r23) {
        sp08 = r23->current.pos;
        sp08.y += 50.0f;
        sp14 = i_actor->eyePos;
        linChk.Set(&sp14, &sp08, i_actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return TRUE;
}

static fopAc_ac_c* target_info[10];
static s32 target_info_count;

/* 00002C4C-00002CD4       .text s_w_sub__FPvPv */
static void* s_w_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BOKO) {
        daBoko_c* boko = (daBoko_c*)param_1;
        // TODO: enum for boko type
        if (fopAcM_GetParam(boko) != 4 && !fopAcM_checkCarryNow(boko)) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = boko;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 00002CD4-00002FB0       .text search_wepon__FP8bk_class */
static uint search_wepon(bk_class* i_this) {
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
            sp18.x = r25->current.pos.x - i_this->eyePos.x;
            sp18.y = 50.0f + r25->current.pos.y - i_this->eyePos.y;
            sp18.z = r25->current.pos.z - i_this->eyePos.z;
            f32 f4 = sqrtf(sp18.x*sp18.x + sp18.z*sp18.z);
            if (f4 < f29 && !daBk_other_bg_check(i_this, r25)) {
                if (fabsf(r25->current.pos.y + 50.0f - i_this->eyePos.y) <= l_bkHIO.m038) {
                    s16 angleDiff = i_this->m0330 - cM_atan2s(sp18.x, sp18.z);
                    if (angleDiff < 0) {
                        angleDiff = -angleDiff;
                    }
                    if ((u16)angleDiff < 0x1800) {
                        return fopAcM_GetID(r25);
                    }
                    cMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
                    cXyz sp0C;
                    MtxPosition(&sp18, &sp0C);
                    if (fabsf(sp0C.x) < l_bkHIO.m03C &&
                        fabsf(sp0C.y) < l_bkHIO.m040 &&
                        sp0C.z > l_bkHIO.m048 &&
                        sp0C.z < l_bkHIO.m044
                    ) {
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

/* 00002FB0-0000302C       .text s_b_sub__FPvPv */
static void* s_b_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BOMB) {
        daBomb_c* bomb = (daBomb_c*)param_1;
        // TODO: why is it checking the bomb's params as a single field instead of just one param? bug?
        if (fopAcM_GetParam(bomb) != 0) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = bomb;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 0000302C-000033BC       .text search_bomb__FP8bk_classi */
static fopAc_ac_c* search_bomb(bk_class* i_this, BOOL r26) {
    if (!(i_this->m1208 & 0x0200)) {
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
            sp28.x = r24->current.pos.x - i_this->eyePos.x;
            sp28.y = 50.0f + r24->current.pos.y - i_this->eyePos.y;
            sp28.z = r24->current.pos.z - i_this->eyePos.z;
            cXyz sp1C;
            sp1C.x = r24->current.pos.x - i_this->current.pos.x;
            sp1C.z = r24->current.pos.z - i_this->current.pos.z;
            f32 f0 = sqrtf(sp28.x*sp28.x + sp28.z*sp28.z);
            f32 f5 = sqrtf(sp1C.x*sp1C.x + sp1C.z*sp1C.z);
            if (f0 < f29 && !(f5 > 30.0f + i_this->m031C) &&
                !(daBk_other_bg_check(i_this, r24) && r26)
            ) {
                if (r26) {
                    if (fabsf(r24->current.pos.y + 50.0f - i_this->eyePos.y) <= l_bkHIO.m038) {
                        s16 angleDiff = i_this->m0330 - cM_atan2s(sp28.x, sp28.z);
                        if (angleDiff < 0) {
                            angleDiff = -angleDiff;
                        }
                        if ((u16)angleDiff < l_bkHIO.m034) {
                            return r24;
                        }
                        cMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
                        cXyz sp10;
                        MtxPosition(&sp28, &sp10);
                        if (fabsf(sp10.x) < l_bkHIO.m03C &&
                            fabsf(sp10.y) < l_bkHIO.m040 &&
                            sp10.z > l_bkHIO.m048 &&
                            sp10.z < l_bkHIO.m044
                        ) {
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

/* 000033BC-00003438       .text daBk_wepon_view_check__FP8bk_class */
static BOOL daBk_wepon_view_check(bk_class* i_this) {
    if (i_this->m02CC != 0) {
        return FALSE;
    }
    i_this->m1200 = search_wepon(i_this);
    if (i_this->m1200 != fpcM_ERROR_PROCESS_ID_e) {
        if (fopAcM_SearchByID(i_this->m1200)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00003438-00003478       .text daBk_bomb_view_check__FP8bk_class */
static BOOL daBk_bomb_view_check(bk_class* i_this) {
    i_this->m11F8 = search_bomb(i_this, 1);
    return i_this->m11F8 != NULL ? TRUE : FALSE;
}

/* 00003478-000034B8       .text daBk_bomb_check__FP8bk_class */
static BOOL daBk_bomb_check(bk_class* i_this) {
    i_this->m11F8 = search_bomb(i_this, 0);
    if (i_this->m11F8) {
        return TRUE;
    }
    return FALSE;
}

/* 000034B8-0000385C       .text daBk_player_bg_check__FP8bk_classP4cXyz */
static BOOL daBk_player_bg_check(bk_class* i_this, cXyz* r22) {
    fopAc_ac_c* i_actor = i_this;
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (search_sp != 0 || i_this->mType == 0xA) {
        return FALSE;
    }
    if (i_this->dr.m713 == 0 && fabsf(player->speedF) < 0.1f && player->checkGrabWear()) {
        return TRUE;
    }
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    sp08 = *r22;
    sp08.y += 75.0f;
    sp14 = i_this->eyePos;
    linChk.Set(&sp14, &sp08, i_actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->dr.m713 = 0;
        return TRUE;
    }
    return FALSE;
}

/* 0000385C-00003A18       .text daBk_player_view_check__FP8bk_classP4cXyzss */
static BOOL daBk_player_view_check(bk_class* i_this, cXyz* r30, s16 r27, s16 r31) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (search_sp != 0 || i_this->mType == 0xA) {
        return TRUE;
    }
    if (daBk_player_bg_check(i_this, r30)) {
        return FALSE;
    }
    if (fabsf(player->current.pos.y + 50.0f - i_this->eyePos.y) > l_bkHIO.m038) {
        return FALSE;
    }
    s16 angleDiff = i_this->m0330 - r27;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }
    if ((u16)angleDiff < r31) {
        i_this->dr.m713 = 1;
        return TRUE;
    }
    cMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
    cXyz sp14;
    sp14.x = r30->x - i_this->current.pos.x;
    sp14.y = r30->y - i_this->current.pos.y;
    sp14.z = r30->z - i_this->current.pos.z;
    cXyz sp08;
    MtxPosition(& sp14, &sp08);
    if (fabsf(sp08.x) < l_bkHIO.m03C &&
        fabsf(sp08.y) < l_bkHIO.m040 &&
        sp08.z > l_bkHIO.m048 &&
        sp08.z < l_bkHIO.m044
    ) {
        i_this->dr.m713 = 1;
        return TRUE;
    } else {
        i_this->dr.m713 = 0;
        return FALSE;
    }
}

/* 00003A18-00003A5C       .text daBk_player_way_check__FP8bk_class */
static BOOL daBk_player_way_check(bk_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s16 angleDiff = i_this->current.angle.y - player->shape_angle.y;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }
    if ((u16)angleDiff < 0x4000) {
        return FALSE;
    }
    return TRUE;
}

/* 00003A5C-00003B2C       .text wait_set__FP8bk_class */
static void wait_set(bk_class* i_this) {
    if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
        anm_init(i_this, BK_BCK_BK_KYORO1, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_KYORO1);
    } else if (i_this->dr.mState >= 4) {
        anm_init(i_this, BK_BCK_BK_KYORO1, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_KYORO1);
    } else {
        anm_init(i_this, BK_BCK_BK_KYORO2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_KYORO2);
    }
    i_this->m0300[1] = 40.0f + cM_rndF(60.0f);
}

/* 00003B2C-00003C34       .text walk_set__FP8bk_class */
static void walk_set(bk_class* i_this) {
    if (i_this->m0B30 != 0 || i_this->m1214 != 0) {
        anm_init(i_this, BK_BCK_BK_WALK, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK);
    } else if (i_this->m11F3 == 0) {
        anm_init(i_this, BK_BCK_BK_NIGERU, 5.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_NIGERU);
    } else {
        anm_init(i_this, BK_BCK_BK_WALK, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK);
    }
    if (i_this->m0B30 == 0 && i_this->m121F != 0) {
        fopAcM_monsSeStart(i_this, JA_SE_CV_BK_LOST_BOKO, 0);
        i_this->m121F = 0;
    }
}

/* 00003C34-00003C74       .text fight_run_set__FP8bk_class */
static void fight_run_set(bk_class* i_this) {
    anm_init(i_this, BK_BCK_BK_RUN, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, l_bkHIO.m070, BK_BAS_BK_RUN);
}

/* 00003C74-00004104       .text path_check__FP8bk_classUc */
static void path_check(bk_class* i_this, u8 r19) {
    fopAc_ac_c* i_actor = i_this;
    
    if (i_this->ppd == NULL) {
        return;
    }
    if (i_this->m0B30 == 0 && i_this->m11F3 == 0 && i_this->mType != 4 && i_this->mType != 10 && i_this->mType != 6) {
        return;
    }
    
    u8 sp90[0x108];
    dBgS_LinChk linChk;
    cXyz sp18;
    sp18.set(i_this->current.pos);
    sp18.y += 100.0f;
    cXyz spc;
    
    dPath__Point* pnt = i_this->ppd->mpPnt;
    for (int i = 0; i < i_this->ppd->m_num; i++, pnt++) {
        spc.x = pnt->mPos.x;
        spc.y = pnt->mPos.y + 100.0f;
        spc.z = pnt->mPos.z;
        linChk.Set(&sp18, &spc, i_actor);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            sp90[i] = 1;
        } else {
            sp90[i] = 0;
        }
    }
    
    f32 f0 = 0.0f;
    bool r6 = false;
    for (int i2 = 0; i2 < 100; i2++, f0 += 50.0f) {
        pnt = i_this->ppd->mpPnt;
        for (int j = 0; j < i_this->ppd->m_num; j++, pnt++) {
            if (sp90[j] == 0) {
                continue;
            }
            f32 distX = i_this->current.pos.x - pnt->mPos.x;
            f32 distY = i_this->current.pos.y - pnt->mPos.y;
            f32 distZ = i_this->current.pos.z - pnt->mPos.z;
            if (sqrtf(distX*distX + distY*distY + distZ*distZ) < f0) {
                if (r19) {
                    i_this->m1216 = j;
                } else {
                    i_this->m1216 = j - i_this->m1217;
                    if (i_this->m1216 >= (s8)i_this->ppd->m_num) {
                        i_this->m1216 = i_this->ppd->m_num;
                    } else if (i_this->m1216 < 0) {
                        i_this->m1216 = 0;
                    }
                }
                r6 = true;
                break;
            }
        }
        if (r6) {
            break;
        }
    }
    
    if (!r6) {
        i_this->m1215 = 0;
    } else {
        i_this->m1215 = i_this->m02B6 + 1;
    }
}

/* 00004104-0000488C       .text jyunkai__FP8bk_class */
static void jyunkai(bk_class* i_this) {
    fopAc_ac_c* i_actor = i_this;
    
    if (i_this->mType == 4 || i_this->mType == 0xA) {
        i_this->dr.mState = 1;
        i_this->dr.m004 = 50;
        return;
    } else if (i_this->mType == 6) {
        i_this->dr.mState = 2;
        i_this->dr.m004 = 50;
        return;
    } else if (i_this->mType == 9) {
        i_this->dr.mState = 3;
        i_this->dr.m004 = 0;
        i_this->m0300[2] = 0;
        i_this->m120C = 0;
        i_this->m1210 = 0;
        path_check(i_this, 0);
        return;
    }
    
    cXyz sp10;
    
    switch (i_this->dr.m004) {
    case 0:
        walk_set(i_this);
        // Fall-through
    case -1:
        i_this->dr.m004 = 1;
        if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
            if (i_this->m1215 != 0) {
                i_this->m1216 += i_this->m1217;
                if (i_this->m1216 >= (s8)i_this->ppd->m_num) {
                    if (i_this->ppd->mLoops & 1) {
                        i_this->m1216 = 0;
                    } else {
                        i_this->m1217 = -1;
                        i_this->m1216 = i_this->ppd->m_num - 2;
                    }
                    if ((i_this->ppd->mNextPathId & 0xFFFF) != 0xFFFF) {
                        i_this->ppd = dPath_GetRoomPath(i_this->ppd->mNextPathId, fopAcM_GetRoomNo(i_this));
                        JUT_ASSERT(2924, i_this->ppd != 0);
                    }
                } else if (i_this->m1216 < 0) {
                    i_this->m1217 = 1;
                    i_this->m1216 = 1;
                }
                dPath__Point* point = &i_this->ppd->mpPnt[i_this->m1216];
                i_this->m0320 = point->mPos;
            } else {
                way_pos_check(i_this, &i_this->m0320);
            }
        } else {
            way_pos_check(i_this, &i_this->m0320);
            i_this->m0300[1] = 30.0f + cM_rndF(25.0f);
        }
        i_this->m0300[2] = 30;
        // Fall-through
    case 1:
        s16 r29;
        f32 f31;
        if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
            r29 = 0x400;
            f31 = l_bkHIO.m04C;
        } else {
            r29 = 0x1000;
            f31 = l_bkHIO.m050;
        }
        
        sp10.x = i_this->m0320.x - i_this->current.pos.x;
        sp10.z = i_this->m0320.z - i_this->current.pos.z;
        i_this->dr.m4D0 = cM_atan2s(sp10.x, sp10.z);
        
        if (i_this->m1215 != 0 && (i_this->m0B30 != 0 || i_this->m11F3 != 0)) {
            if (sqrtf(sp10.x*sp10.x + sp10.z*sp10.z) < f31 * 0.25f * 2.0f) {
                if (i_this->ppd->mpPnt[i_this->m1216].mArg3 == 3) {
                    wait_set(i_this);
                    i_this->dr.m004 = 2;
                } else {
                    i_this->dr.m004 = -1;
                }
            }
        } else if (sqrtf(sp10.x*sp10.x + sp10.z*sp10.z) < f31 * 0.25f * 2.0f ||
            (
                i_this->m0300[2] == 0 && (
                    i_this->dr.mAcch.ChkWallHit() ||
                    ground_4_check(i_this, 1, i_this->current.angle.y, 200.0f)
                )
            )
        ) {
            wait_set(i_this);
            i_this->dr.m004 = 2;
        }
        cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->dr.m4D0, 4, r29);
        cLib_addCalc2(&i_this->speedF, f31, 1.0f, 5.0f);
        break;
    case 2:
        i_this->speedF = 0.0f;
        if (i_this->m0B30 == 0 && i_this->m11F3 == 0) {
            int frame = i_this->mpMorf->getFrame();
            if ((frame == 0xB || frame == 0x19) && cM_rndF(1.0f) < 0.5f) {
                fopAcM_monsSeStart(i_this, JA_SE_CV_BK_SEARCH, 0);
            }
        }
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 0;
            if (i_this->m0B30 == 0 && i_this->m11F3 == 0 && i_this->m030A == 0) {
                i_this->m11F3 = 1;
            }
        }
        break;
    case 3:
        i_this->speedF = 0.0f;
        int frame = i_this->mpMorf->getFrame();
        if (frame == 3 || frame == 0x35) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BK_SEARCH, 0);
        }
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 0;
        }
        break;
    }
    
    s32 r3 = fopAcM_otoCheck(i_actor, 1000.0f);
    r3 += search_sp;
    
    if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
        if (r3 != 0 ||
            (
                i_this->m031C < l_bkHIO.m028 &&
                daBk_player_view_check(i_this, &i_this->dr.m714->current.pos, i_this->m0332, l_bkHIO.m034)
            )
        ) {
            i_this->dr.mState = 4;
            i_this->m0300[1] = 0;
            i_this->dr.m004 = 0;
        }
    } else if (i_this->m11F3 == 0 && i_this->dr.m004 == 2) {
        int frame = i_this->mpMorf->getFrame();
        if ((frame == 0xB || frame == 0x19) && cM_rndF(1.0f) < 0.5f) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BK_SEARCH_BOKO, 0);
        }
    }
    
    if (i_this->m0B30 == 0 && daBk_wepon_view_check(i_this)) {
        i_this->dr.mState = 0xC;
        i_this->dr.m004 = -1;
    }
    
    if (daBk_bomb_view_check(i_this)) {
        i_this->dr.mState = 9;
        i_this->dr.m004 = 0;
    }
}

/* 0000488C-000048E4       .text ken_s_sub__FPvPv */
static void* ken_s_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_ITEM) {
        daItem_c* item = (daItem_c*)param_1;
        if (item->getItemNo() == DROPPED_SWORD) {
            return param_1;
        }
    }
    return NULL;
}

/* 000048E4-000053E0       .text stand__FP8bk_class */
static void stand(bk_class* i_this) {
    /* Nonmatching */
}

/* 000053E0-000054E0       .text s_s_sub__FPvPv */
static void* s_s_sub(void* r29, void* r30) {
    bk_class* i_this = (bk_class*)r30;
    if (fopAc_IsActor(r29) && fopAcM_GetName(r29) == PROC_OBJ_SEARCH) {
        daObj_Search::Act_c* search = (daObj_Search::Act_c*)r29;
        cXyz sp18 = i_this->home.pos - search->current.pos;
        if (sp18.abs() < 600.0f) {
            return r29;
        }
    }
    return NULL;
}

/* 000054E0-00005D40       .text stand2__FP8bk_class */
static void stand2(bk_class* i_this) {
    /* Nonmatching */
}

/* 00005D40-00006218       .text path_run__FP8bk_class */
static void path_run(bk_class* i_this) {
    /* Nonmatching */
}

/* 00006218-0000647C       .text attack_set__FP8bk_classUc */
static void attack_set(bk_class* i_this, u8 r28) {
    i_this->m0B5C = 0;
    i_this->m11F1 = 0;
    i_this->m11FC = -1;
    i_this->m11F2 = 0;
    i_this->m0B64 = 0.0f;
    i_this->m0300[4] = 0;
    cM_rndF(100.0f);
    i_this->m1040.SetR(60.0f + g_regHIO.mChild[8].mFloatRegs[3]);
    
    if (r28 == 2) {
        i_this->m1040.SetAtType(AT_TYPE_UNK2000);
        i_this->m1040.SetAtSe(dCcD_SE_UNK6);
    } else if (i_this->m02D5 != 0) {
        i_this->m1040.SetAtType(AT_TYPE_UNK800);
        i_this->m1040.SetAtSe(dCcD_SE_UNK2);
    } else {
        i_this->m1040.SetAtType(AT_TYPE_UNK2000);
        i_this->m1040.SetAtSe(dCcD_SE_UNK4);
    }
    
    if (r28 == 0) {
        i_this->m0B5C = 0;
        i_this->m0B68 = 23.0f + g_regHIO.mChild[6].mFloatRegs[4];
        i_this->m0B6C = 26.0f + g_regHIO.mChild[6].mFloatRegs[5];
        i_this->m0B70 = 45.0f;
        i_this->m0B74 = l_bkHIO.m09C;
    } else if (r28 == 1) {
        i_this->m0B5C = 1;
        i_this->m0B68 = 3.0f + g_regHIO.mChild[6].mFloatRegs[8];
        i_this->m0B6C = 9.0f + g_regHIO.mChild[6].mFloatRegs[9];
        i_this->m0B70 = 45.0f;
        i_this->m0B74 = 0.0f;
    } else if (r28 == 2) {
        i_this->m0B5C = 2;
        i_this->m0B68 = g_regHIO.mChild[6].mFloatRegs[4];
        i_this->m0B6C = 20.0f + g_regHIO.mChild[6].mFloatRegs[5];
        i_this->m0B70 = 45.0f;
        i_this->m0B74 = 0.0f;
        i_this->m1040.SetR(25.0f + g_regHIO.mChild[8].mFloatRegs[3]);
    }
    
    i_this->m0B7A = 1;
    i_this->m0B60 = 0;
    
    attack_info_s* info = attack_info[i_this->m0B5C];
    anm_init(i_this, info->bckFileIdx, 5.0f, J3DFrameCtrl::LOOP_ONCE_e, info->speed, info->soundFileIdx);
    if (bk_attack_ready_SE[i_this->m0B5C] != -0xDCF) {
        fopAcM_monsSeStart(i_this, bk_attack_ready_SE[i_this->m0B5C], 0);
    }
}

u16 learn_check;

/* 0000647C-000064D8       .text shot_s_sub__FPvPv */
static void* shot_s_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && (learn_check & 0x400) && fopAcM_GetName(param_1) == PROC_HIMO2) {
        return param_1;
    }
    return NULL;
}

/* 000064D8-000073B8       .text fight_run__FP8bk_class */
static void fight_run(bk_class* i_this) {
    /* Nonmatching - data offsets */
    daPy_py_c* player = daPy_getPlayerActorClass();
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    s8 r29 = 0;
    if (i_this->dr.mAcch.ChkGroundHit() && i_this->dr.mAcch.ChkWallHit()) {
        r29 = 1;
    }
    i_this->dr.m4D0 = i_this->m0332;
    
    if (i_this->dr.m004 != 0) {
        s16 r6 = 0x400;
        if (i_this->dr.m004 == 1) {
            r6 = 0x800;
        }
        if (i_this->dr.mAcch.ChkGroundHit()) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->dr.m4D0, 4, r6);
        }
    }
    
    switch (i_this->dr.m004) {
    case 0x00:
        if (i_this->m0300[1] == 0) {
            fight_run_set(i_this);
            i_this->dr.m004 = 1;
            i_this->m120C = 0;
            i_this->m1212 = cM_rndF(1000.0f);
        } else {
            i_this->speedF = 0.0f;
            break;
        }
        // Fall-through
    case 0x01:
        f32 scaleMag;
        if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
            scaleMag = l_bkHIO.m054;
        } else {
            scaleMag = l_bkHIO.m058;
        }
        cLib_addCalc2(&i_this->speedF, scaleMag, 1.0f, 5.0f);
        i_this->m1212++;
        if (daBk_player_way_check(i_this) && (i_this->m1212 & 0x30) && !r29) {
            if (i_this->m120C != 0) {
                anm_init(i_this, BK_BCK_BK_RUN, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, l_bkHIO.m070, BK_BAS_BK_RUN);
                i_this->m120C = 0;
            }
            if (i_this->m031C < l_bkHIO.m02C) {
                i_this->dr.m004 = 2;
                i_this->m0300[4] = 50;
            }
            break;
        } else {
            if (i_this->m120C == 0 && i_this->m0B30 != 0) {
                i_this->m120C = 1;
                i_this->m1210 = 0;
            }
        }
        
        if (i_this->m0B30 != 0) {
            i_this->speedF = l_bkHIO.m068;
            
            switch (i_this->m1210) {
            case 0:
                i_this->m1210 = 1;
                cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->dr.m4D0, 2, 0x2000);
                anm_init(i_this, BK_BCK_BK_JUMP2, 5.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP2);
                break;
            case 1:
                if (i_this->dr.mAcch.ChkGroundHit() && i_this->mpMorf->isStop()) {
                    anm_init(i_this, BK_BCK_BK_JUMP2, 0.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP2);
                    i_this->m1210 = 2;
                    i_this->m034C = l_bkHIO.m00C + 2;
                    i_this->m034E = 4;
                }
                break;
            case 2:
                i_this->speedF = 0.0f;
                cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->dr.m4D0, 2, 0x2000);
                if (i_this->dr.mAcch.ChkGroundHit() && i_this->mpMorf->isStop()) {
                    i_this->m1210 = 1;
                    anm_init(i_this, BK_BCK_BK_JUMP1, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP1);
                    i_this->speed.y = 65.0f + cM_rndF(10.0f + g_regHIO.mChild[8].mFloatRegs[7]) + g_regHIO.mChild[8].mFloatRegs[8];
                    if ((i_this->m02DD & 0xC) == 0) {
                        s16 temp = cM_rndFX(3000.0f + g_regHIO.mChild[6].mFloatRegs[13]);;
                        i_this->current.angle.y += temp;
                    }
                    fopAcM_monsSeStart(i_this, JA_SE_CV_BK_JUMP, 0);
                }
                break;
            }
            
        }
        
        if (i_this->m031C < l_bkHIO.m030) {
            i_this->dr.mState = 5;
            i_this->dr.m004 = 0;
            return;
        }
        break;
    case 0x02:
        i_this->m120C = 0;
        
        if (cM_rndF(1.0f) < 0.3f && i_this->m0B30 == 0) {
            i_this->dr.m004 = 8;
            wait_set(i_this);
            i_this->m0300[1] = 20.0f + cM_rndF(20.0f);
            break;
        }
        if ((i_this->m02DD & 0xC) == 0 && fabsf(stickPosX) > 0.1f) {
            if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            } else {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            }
            if (stickPosX > 0.0f) {
                i_this->dr.m004 = 5;
            } else {
                i_this->dr.m004 = 6;
            }
        } else if (i_this->m031C < l_bkHIO.m030) {
            if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            } else {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            }
            i_this->dr.m004 = 4;
        } else {
            if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            } else {
                anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
            }
            i_this->dr.m004 = 3;
        }
        i_this->m0300[1] = 20.0f + cM_rndF(20.0f);
        break;
    case 0x03:
        cLib_addCalc2(&i_this->speedF, l_bkHIO.m060, 1.0f, 20.0f);
        if (r29) {
            i_this->speed.y = 100.0f + g_regHIO.mChild[0].mFloatRegs[16];
            anm_init(i_this, BK_BCK_BK_JUMP1, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP1);
            fopAcM_monsSeStart(i_this, JA_SE_CV_BK_JUMP, 0);
            i_this->dr.m004 = 0x21;
            break;
        }
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 2;
        }
        break;
    case 0x21:
        if (i_this->dr.mAcch.ChkGroundHit()) {
            anm_init(i_this, BK_BCK_BK_JUMP2, 0.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP2);
            i_this->dr.m004++;
        }
        break;
    case 0x22:
        i_this->speedF = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->dr.m004 = 3;
        } else if ((i_this->m02DD & 0x2) == 0) {
            cLib_addCalc2(&i_this->speedF, -l_bkHIO.m060, 1.0f, 20.0f);
        }
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 2;
        } else {
            i_this->dr.m004 = 3;
        }
        if (i_this->m0B30 != 0 || i_this->m11F3 != 0) {
            anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
        } else {
            anm_init(i_this, BK_BCK_BK_WALK2, 10.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, BK_BAS_BK_WALK2);
        }
        break;
    case 0x04:
        break;
    case 0x05:
        if ((i_this->m02DD & 0x4) == 0) {
            i_this->m0334 = 0x4000;
            goto temp_860;
        } else {
            i_this->m0300[1] = 0;
            goto temp_860;
        }
    case 0x06:
        if ((i_this->m02DD & 0x8) == 0) {
            i_this->m0334 = -0x4000;
            goto temp_860;
        } else {
            i_this->m0300[1] = 0;
            goto temp_860;
        }
    temp_860:
        cLib_addCalc2(&i_this->speedF, l_bkHIO.m064, 1.0f, 30.0f);
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 2;
        }
        break;
    case 0x08:
        i_this->speedF = 0.0f;
        if (i_this->m0300[1] == 0) {
            i_this->dr.m004 = 2;
        }
        break;
    }
    
    if (i_this->dr.m004 >= 3 && i_this->m0314 <= 2) {
        if (i_this->m031C > l_bkHIO.m02C + 75.0f) {
            i_this->dr.mState = 0;
            i_this->dr.m004 = 0;
            path_check(i_this, 0);
        }
        if (i_this->m031C < l_bkHIO.m030 + 62.5f && i_this->m031C > l_bkHIO.m030 - 62.5f) {
            if (i_this->m0300[4] == 0) {
                i_this->m0300[4] = l_bkHIO.m078;
                if (cM_rndF(100.0f) < l_bkHIO.m07C) {
                    i_this->dr.mState = 5;
                    i_this->dr.m004 = 0;
                }
            }
        }
        if (i_this->m0310 == 0) {
            bool r27 = false;
            learn_check = i_this->m1208;
            fopAc_ac_c* r29 = (fopAc_ac_c*)fpcM_Search(shot_s_sub, i_this);
            if (r29) {
                if (r29->speedF > 10.0f) {
                    cXyz sp18 = (r29->current.pos - i_this->eyePos);
                    if (sp18.abs() < r29->speedF * 10.0f) {
                        r27 = true;
                    }
                }
            }
            dAttention_c& attention = dComIfGp_getAttention();
            if (i_this->m0B30 &&
                daBk_player_way_check(i_this) &&
                (
                    r27 || (
                        player->getCutType() != 0 &&
                        (cc_pl_cut_bit_get() & i_this->m1208) &&
                        attention.Lockon() &&
                        i_this == attention.LockonTarget(0)
                    )
                )
            ) {
                if (i_this->m02D4 != 0 && (cM_rndF(1.0f) <= 0.5f || l_bkHIO.m008 != 0)) {
                    i_this->dr.mState = 0xA;
                    i_this->dr.m004 = 0;
                    if (player->getCutType() == 0xA) {
                        i_this->m0300[1] = 0x1E;
                    } else {
                        i_this->m0300[1] = 0x0F;
                    }
                } else {
                    i_this->m030E = 0xA;
                    if ((ground_4_check(i_this, 4, i_this->current.angle.y, 200.0f) & 0xD) == 0) {
                        i_this->dr.mState = 5;
                        attack_set(i_this, 1);
                        anm_init(i_this, BK_BCK_BK_JUMP1, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP1);
                        i_this->dr.m004 = -0xA;
                        i_this->speedF = -60.0f + g_regHIO.mChild[0].mFloatRegs[3];
                        i_this->speed.y = 80.0f + g_regHIO.mChild[0].mFloatRegs[4];
                        fopAcM_monsSeStart(i_this, JA_SE_CV_BK_JUMP, 0);
                    }
                }
            }
        }
    }    
    
    if (i_this->m0B30 != 0 && i_this->m031C < l_bkHIO.m030 - 62.5f &&
        daBk_player_view_check(i_this, &i_this->dr.m714->current.pos, i_this->m0332, l_bkHIO.m034)
    ) {
        i_this->m02FC++;
        s16 temp = 0x19 + g_regHIO.mChild[0].mShortRegs[0];
        if (i_this->m02FC >= temp) {
            if (cM_rndF(1.0f) < 0.5f + g_regHIO.mChild[0].mFloatRegs[0] &&
                (ground_4_check(i_this, 4, i_this->current.angle.y, 200.0f) & 0xD) == 0
            ) {
                i_this->dr.mState = 7;
                i_this->dr.m004 = 0;
            }
            i_this->m02FC = 0;
        }
    } else {
        i_this->m02FC = 0;
    }
    if (daBk_player_bg_check(i_this, &i_this->dr.m714->current.pos)) {
        i_this->dr.mState = 0;
        i_this->dr.m004 = 0;
        path_check(i_this, 0);
    }
    if (i_this->m0B30 == 0 && daBk_wepon_view_check(i_this)) {
        i_this->dr.mState = 0xC;
        i_this->dr.m004 = -1;
    }
    if (daBk_bomb_view_check(i_this)) {
        i_this->dr.mState = 9;
        i_this->dr.m004 = 0;
    }
    i_this->m02DD = ground_4_check(i_this, 4, i_this->current.angle.y, 90.0f + g_regHIO.mChild[6].mFloatRegs[7]);
    if (i_this->m0314 != 0) {
        if (fabsf(i_this->speedF) < 30.0f) {
            if (i_this->m0318 == 0) {
                i_this->dr.m710 = 3;
            } else if (i_this->m0318 == 1) {
                i_this->dr.m710 = 4;
            } else if (i_this->m02F8 & 0x10) {
                i_this->dr.m710 = 3;
            } else {
                i_this->dr.m710 = 4;
            }
            cLib_addCalcAngleS2(&i_this->m11F4, 12000, 2, 0x1800);
        } else {
            i_this->dr.m710 = 1;
        }
    } else {
        i_this->dr.m710 = 1;
        if (i_this->m0316 == 0) {
            i_this->m0316 = 30.0f + cM_rndF(100.0f);
            if (i_this->m02DD == 4) {
                i_this->m0318 = 0;
                i_this->m0314 = 0x10;
            } else if (i_this->m02DD == 8) {
                i_this->m0318 = 1;
                i_this->m0314 = 0x10;
            } else if (i_this->m02DD == 2) {
                i_this->m0318 = 2;
                i_this->m0314 = 0x20;
            }
        }
    }
}

/* 000073B8-000075E8       .text yari_hit_check__FP8bk_class */
static void yari_hit_check(bk_class* i_this) {
    /* Nonmatching */
}

/* 000075E8-00007EF4       .text fight__FP8bk_class */
static void fight(bk_class* i_this) {
    /* Nonmatching */
}

/* 00007EF4-00008108       .text p_lost__FP8bk_class */
static void p_lost(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008108-00008470       .text b_nige__FP8bk_class */
static void b_nige(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008470-00008580       .text defence__FP8bk_class */
static void defence(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008580-00008654       .text oshi__FP8bk_class */
static void oshi(bk_class* i_this) {
    i_this->dr.mState = 5;
    attack_set(i_this, 1);
    anm_init(i_this, BK_BCK_BK_JUMP1, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_JUMP1);
    i_this->dr.m004 = -0xA;
    i_this->speedF = -90.0f + g_regHIO.mChild[6].mFloatRegs[10];
    i_this->speed.y = 85.0f + g_regHIO.mChild[6].mFloatRegs[11];
    fopAcM_monsSeStart(i_this, JA_SE_CV_BK_JUMP, 0);
}

/* 00008654-00008C38       .text hukki__FP8bk_class */
static void hukki(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008C38-00008D1C       .text aite_miru__FP8bk_class */
static void aite_miru(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008D1C-00008ECC       .text fail__FP8bk_class */
static void fail(bk_class* i_this) {
    /* Nonmatching */
}

/* 00008ECC-000090E0       .text yogan_fail__FP8bk_class */
static void yogan_fail(bk_class* i_this) {
    /* Nonmatching */
}

/* 000090E0-0000924C       .text water_fail__FP8bk_class */
static void water_fail(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000924C-00009944       .text wepon_search__FP8bk_class */
static void wepon_search(bk_class* i_this) {
    /* Nonmatching */
}

/* 00009944-00009AFC       .text d_dozou__FP8bk_class */
static void d_dozou(bk_class* i_this) {
    /* Nonmatching */
}

/* 00009AFC-00009B0C       .text carry__FP8bk_class */
static void carry(bk_class* i_this) {
    i_this->speed.y = 0.0f;
}

/* 00009B0C-00009DF0       .text carry_drop__FP8bk_class */
static void carry_drop(bk_class* i_this) {
    /* Nonmatching */
}

/* 00009DF0-00009F1C       .text d_mahi__FP8bk_class */
static void d_mahi(bk_class* i_this) {
    /* Nonmatching */
}

/* 00009F1C-0000A350       .text tubo_wait__FP8bk_class */
static void tubo_wait(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000A350-0000A630       .text z_demo_1__FP8bk_class */
static void z_demo_1(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000A630-0000A9BC       .text b_hang__FP8bk_class */
static void b_hang(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000A9BC-0000AC6C       .text rope_on__FP8bk_class */
static void rope_on(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000AC6C-0000AC84       .text search_target__FP8bk_class */
static BOOL search_target(bk_class* i_this) {
    i_this->dr.m714 = dComIfGp_getPlayer(0);
    return FALSE;
}

/* 0000AC84-0000B25C       .text Bk_move__FP8bk_class */
static void Bk_move(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000B25C-0000B324       .text bk_eye_tex_anm__FP8bk_class */
static void bk_eye_tex_anm(bk_class* i_this) {
    if (i_this->m02C8 != 0) {
        i_this->m02C8--;
    } else {
        i_this->m02C8 = 20.0f + cM_rndF(100.0f);
        i_this->m02CA = 3.0f + cM_rndF(3.0f);
    }
    if (i_this->m02CA != 0) {
        i_this->m02CA--;
        i_this->m02C4->setFrame(6.0f);
    } else {
        i_this->m02C4->setFrame(0.0f);
    }
}

/* 0000B324-0000BC98       .text damage_check__FP8bk_class */
static void damage_check(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000BCD4-0000BD30       .text s_s2_sub__FPvPv */
static void* s_s2_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_OBJ_SEARCH) {
        if (daObj_Search::Act_c::getFindFlag()) {
            return param_1;
        }
    }
    return NULL;
}

/* 0000BD30-0000C2D0       .text waki_set__FP8bk_class */
static void waki_set(bk_class* i_this) {
    /* Nonmatching */
}

/* 0000C2D0-0000CC68       .text demo_camera__FP8bk_class */
static void demo_camera(bk_class* i_this) {
    /* Nonmatching */
    JUTReport(410, 430, "K SUB  COUNT  %d");
}

/* 0000CC68-0000CD00       .text tate_mtx_set__FP8bk_class */
static void tate_mtx_set(bk_class* i_this) {
    if (i_this->m02D4 != 0) {
        int jointIdx = 0x25; // tate joint
        MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIdx), *calc_mtx);
        i_this->m02D0->setBaseTRMtx(*calc_mtx);
        cXyz sp08;
        sp08.x = g_regHIO.mChild[8].mFloatRegs[12];
        sp08.y = g_regHIO.mChild[8].mFloatRegs[13];
        sp08.z = g_regHIO.mChild[8].mFloatRegs[14];
        MtxPosition(&sp08, &i_this->m11CC);
    }
}

/* 0000CD00-0000CE18       .text bou_mtx_set__FP8bk_class */
static void bou_mtx_set(bk_class* i_this) {
    if (i_this->m02DC != 0) {
        int jointIdx = 0x2C + g_regHIO.mChild[7].mShortRegs[4]; // buki joint
        MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIdx), *calc_mtx);
        s16 angleY = 0x4000 + g_regHIO.mChild[7].mShortRegs[0];
        cMtx_YrotM(*calc_mtx, angleY);
        s16 angleX = g_regHIO.mChild[7].mShortRegs[1];
        cMtx_XrotM(*calc_mtx, angleX);
        s16 angleZ = g_regHIO.mChild[7].mShortRegs[2];
        cMtx_ZrotM(*calc_mtx, angleZ);
        MtxTrans(
            0.01f * g_regHIO.mChild[7].mFloatRegs[9],
            0.01f * g_regHIO.mChild[7].mFloatRegs[10],
            0.01f * g_regHIO.mChild[7].mFloatRegs[11] + 50.0f,
            1
        );
        i_this->m02D8->setBaseTRMtx(*calc_mtx);
    }
}

/* 0000CE18-0000DD1C       .text daBk_Execute__FP8bk_class */
static BOOL daBk_Execute(bk_class* i_this) {
    another_hit = 0;
    
    if (i_this->m1220 != NULL) {
        i_this->m1220->m664 = 0;
    }
    
    if (i_this->m121C != 0 || i_this->home.pos.y - i_this->current.pos.y > 4000.0f) {
        if (i_this->m0B30 != 0) {
            fopAc_ac_c* temp = fopAcM_SearchByID(i_this->m1200);
            if (temp != NULL) {
                fopAcM_delete(temp);
            }
        }
        fopAcM_delete(i_this);
        return TRUE;
    }
    
    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->setPlayMode(J3DFrameCtrl::LOOP_ONCE_e);
        i_this->mpMorf->setPlaySpeed(3.0f);
        i_this->mpMorf->play(&i_this->eyePos, 0, 0);
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        tate_mtx_set(i_this);
        bou_mtx_set(i_this);
        return TRUE;
    }
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    
    if (i_this->mType == 8) {
        for (int i = 0; i < ARRAY_SIZE(i_this->m0300); i++) {
            if (i_this->m0300[i] != 0) {
                i_this->m0300[i]--;
            }
        }
        waki_set(i_this);
        return TRUE;
    }
    
    if (l_bkHIO.m006 == 0 || CPad_CHECK_TRIG_B(0) || CPad_CHECK_HOLD_Y(0)) {
        i_this->m02F8++;
        for (int i = 0; i < ARRAY_SIZE(i_this->m0300); i++) {
            if (i_this->m0300[i] != 0) {
                i_this->m0300[i]--;
            }
        }
        if (i_this->m0314 != 0) {
            i_this->m0314--;
        }
        if (i_this->m0316 != 0) {
            i_this->m0316--;
        }
        if (i_this->m030A != 0) {
            i_this->m030A--;
        }
        if (i_this->m02CC != 0) {
            i_this->m02CC--;
        }
        if (i_this->dr.m48A != 0) {
            i_this->dr.m48A--;
        }
        if (i_this->m030E != 0) {
            i_this->m030E--;
        }
        if (i_this->m0310 != 0) {
            i_this->m0310--;
        }
        if (i_this->m0B78 != 0) {
            i_this->m0B78--;
        }
        
        if (i_this->m02B7 != 0xFF && i_this->mType == 6 && dComIfGs_isSwitch(i_this->m02B7, dComIfGp_roomControl_getStayNo())) {
            return TRUE;
        }
        
        if (i_this->m1214 != 0) {
            daBoko_c* temp = (daBoko_c*)fopAcM_SearchByID(i_this->m1200);
            if (temp != NULL) {
                i_this->m1214 = 0;
                i_this->m0B30 = 1;
                fopAcM_setCarryNow(temp, FALSE);
                MtxTrans(-10000.0f, -10000.0f, 0.0f, 0);
                temp->setMatrix(*calc_mtx);
            }
        }
        
        if (i_this->m02BA != 0x00) {
            if (i_this->m02BA == 0xFF) {
                f32 f30;
                if (i_this->m02B5 != 0xFF) {
                    f30 = i_this->m02B5 * 10.0f;
                } else {
                    f30 = 300.0f;
                }
                
                fopAc_ac_c* r23 = fopAcM_SearchByID(i_this->m1204);
                if (i_this->m030E == 0 && (fopAcM_searchPlayerDistance(i_this) < f30 || r23 == NULL)) {
                    i_this->m02BA = 0;
                    if (r23 == NULL) {
                        i_this->m0300[0] = 50;
                        i_this->m0310 = 20;
                        if (fabsf(i_this->speedF) > 10.0f) {
                            another_hit = 1;
                        } else {
                            i_this->scale.x = i_this->scale.y = i_this->scale.z = 0.5f;
                        }
                    }
                    i_this->m0B88.SetR(62.5f);
                } else {
                    if (r23 != NULL) {
                        i_this->current.pos = r23->current.pos;
                        if (r23->speedF > 1.0f) {
                            i_this->speedF = r23->speedF;
                            i_this->shape_angle = r23->shape_angle;
                            i_this->current.angle = r23->shape_angle;
                        }
                    } else {
                        i_this->m0B88.SetC(i_this->current.pos);
                        i_this->m0B88.SetR(10.0f);
                        dComIfG_Ccsp()->Set(&i_this->m0B88);
                        cCcD_Obj* r3 = i_this->m0B88.GetCoHitObj();
                        if (r3 != NULL) {
                            fopAc_ac_c* temp = r3->GetAc();
                            if (temp != NULL) {
                                i_this->m1204 = fopAcM_GetID(temp);
                            }
                        }
                    }
                    return TRUE;
                }
            } else {
                if (dComIfGs_isSwitch(i_this->m02BA - 1, fopAcM_GetRoomNo(i_this))) {
                    i_this->m02BA = 0;
                } else {
                    return TRUE;
                }
            }
        }
        
        i_this->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
        fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
        i_this->m02F0 = 0;
        i_this->m02F4 = 0;
        i_this->m0B7B = 0;
        
        bk_eye_tex_anm(i_this);
        i_this->dr.m438 = 0;
        i_this->setBtAttackData(100.0f, 100.0f, 10000.0f, 0);
        i_this->setBtNowFrame(0.0f);
        damage_check(i_this);
        Bk_move(i_this);
        demo_camera(i_this);
        ground_smoke_set(i_this);
        if (i_this->m030C != 0) {
            i_this->m030C--;
        }
        i_this->dr.mpEnemy = i_this;
        i_this->dr.mEnemyType = 2;
    }
    if (i_this->dr.mState != 0x1F) {
        i_this->shape_angle = i_this->current.angle;
    }
    
    int r3 = damage_reaction(&i_this->dr);
    if (r3 != 0) {
        i_this->m034C = 1;
        i_this->m11FC = -1;
        switch (r3) {
        case 1:
            anm_init(i_this, BK_BCK_BK_AOMUKE, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_AOMUKE);
            if (i_this->m0B30 != 0) {
                i_this->m0B34 = 1;
            }
            i_this->dr.mState = 0;
            break;
        case 2:
            anm_init(i_this, BK_BCK_BK_UTUBUSE, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_UTUBUSE);
            break;
        case 5:
            if (i_this->dr.mState != 4 && i_this->dr.mState != 0xB) {
                wait_set(i_this);
                i_this->dr.mState = 4;
                i_this->dr.m004 = 0;
                i_this->m0300[1] = 30;
            }
            i_this->m0336 = 5;
            i_this->m0344.x = -0x4000;
            break;
        case 10:
            wait_set(i_this);
            i_this->dr.m004 = 2;
            i_this->dr.mState = 0;
            path_check(i_this, 0);
            break;
        case 20:
            i_this->m0336 = 1;
            i_this->m0344.x = -0x4000;
            i_this->m034C = l_bkHIO.m00C + 0x10;
            i_this->m034E = 1;
            i_this->dr.m4C8[2] = l_bkHIO.m08C;
            break;
        case 21:
            i_this->m0336 = 1;
            i_this->m0344.x = 0;
            i_this->dr.m4C8[2] = l_bkHIO.m08C;
            break;
        case 30:
            anm_init(i_this, BK_BCK_BK_AOMUKE, 2.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, BK_BAS_BK_AOMUKE);
            if (i_this->m0B30 != 0) {
                i_this->m0B34 = 1;
            }
            i_this->dr.mState = 0;
            fopAcM_monsSeStart(i_this, JA_SE_CV_BK_FAINTED, 0);
            break;
        }
    }
    
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);
    model->setBaseTRMtx(*calc_mtx);
    if (i_this->m030C == 0) {
        i_this->mpMorf->play(&i_this->eyePos, 0, 0);
    }
    i_this->mpMorf->calc();
    
    enemy_fire(&i_this->mEnemyFire);
    
    if (i_this->m0B30 != 0) {
        daBoko_c* r29 = (daBoko_c*)fopAcM_SearchByID(i_this->m1200);
        if (r29 != NULL) {
            if (fopAcM_checkCarryNow(r29)) {
                if (i_this->m0B7B == 0) {
                    int jointIdx = 0x2C; // buki joint
                    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIdx), *calc_mtx);
                    s16 angleY = 0x3E80 + g_regHIO.mChild[8].mShortRegs[1];
                    cMtx_YrotM(*calc_mtx, angleY);
                    s16 angleX = g_regHIO.mChild[8].mShortRegs[2];
                    cMtx_XrotM(*calc_mtx, angleX);
                    s16 angleZ = g_regHIO.mChild[8].mShortRegs[3];
                    cMtx_ZrotM(*calc_mtx, angleZ);
                    MtxTrans(
                        g_regHIO.mChild[8].mFloatRegs[9],
                        g_regHIO.mChild[8].mFloatRegs[10],
                        g_regHIO.mChild[8].mFloatRegs[11] + 65.0f,
                        1
                    );
                } else {
                    MtxTrans(
                        i_this->home.pos.x,
                        i_this->home.pos.y,
                        i_this->home.pos.z,
                        0
                    );
                    cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
                    MtxTrans(
                        g_regHIO.mChild[6].mFloatRegs[7] - 40.0f,
                        g_regHIO.mChild[6].mFloatRegs[8] + 68.0f,
                        g_regHIO.mChild[6].mFloatRegs[9] + 82.0f,
                        1
                    );
                    s16 angleX = 0x5B1B + g_regHIO.mChild[8].mShortRegs[5];
                    cMtx_XrotM(*calc_mtx, angleX);
                }
                r29->setMatrix(*calc_mtx);
                cXyz sp64;
                sp64.x = g_regHIO.mChild[8].mFloatRegs[12];
                sp64.y = g_regHIO.mChild[8].mFloatRegs[13];
                sp64.z = g_regHIO.mChild[8].mFloatRegs[14];
                MtxPosition(&sp64, &i_this->m1178);
            }
        } else {
            i_this->m0B30 = 0;
        }
    }
    
    tate_mtx_set(i_this);
    bou_mtx_set(i_this);
    yari_off_check(i_this);
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, 0);
    cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    cXyz sp58(0.0f, 0.0f, 35.0f);
    cXyz sp4C;
    MtxPosition(&sp58, &sp4C);
    i_this->m0B88.SetC(sp4C);
    dComIfG_Ccsp()->Set(&i_this->m0B88);
    // Using the inline breaks the match.
    // dComIfG_Ccsp()->SetMass(&i_this->m0B88, 3);
    dComIfG_Ccsp()->mMass_Mng.Set(&i_this->m0B88, 3);
    
    cXyz sp40 = i_this->m116C;
    cXyz sp34 = i_this->current.pos;
    if (i_this->m030E != 0) {
        sp40.y -= 20000.0f;
        sp34.y -= 20000.0f;
    }
    if (i_this->dr.mState == 0xA) {
        sp40.y -= 20000.0f;
        sp34.y -= 100.0f;
    }
    i_this->m0CB8.SetC(sp34);
    dComIfG_Ccsp()->Set(&i_this->m0CB8);
    i_this->m0DE8.SetC(sp40);
    dComIfG_Ccsp()->Set(&i_this->m0DE8);
    
    if (i_this->m0336 != 0) {
        i_this->m0336--;
        if (i_this->m0336 == 0) {
            i_this->m0344.y = i_this->current.angle.y;
            dComIfGp_particle_set(0xE, &i_this->m116C, &i_this->m0344);
        }
    }
    
    if (i_this->dr.mAcch.ChkGroundHit() || i_this->dr.mState == 0x13) {
        dBgS_GndChk gndChk;
        s16 r21 = 0x7FFF;
        s16 r23 = 0x7FFF;
        f32 f31 = i_this->dr.m480 != 0 ? 100.0f : 10.0f;
        cXyz sp28 = i_this->current.pos;
        sp28.y += 50.0f - i_this->dr.m44C.y;
        gndChk.SetPos(&sp28);
        sp28.y = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (sp28.y != -1e9f) {
            Vec temp;
            temp.x = sp28.x;
            temp.y = 50.0f + sp28.y;
            temp.z = sp28.z + f31;
            gndChk.SetPos(&temp);
            f32 f1 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (f1 != -1e9f) {
                r21 = (s16)-cM_atan2s(f1 - sp28.y, temp.z - sp28.z);
                if (r21 > 0x2000 || r21 < -0x2000) {
                    r21 = 0;
                }
            }
            temp.x = sp28.x + f31;
            temp.y = 50.0f + sp28.y;
            temp.z = sp28.z;
            gndChk.SetPos(&temp);
            f1 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (f1 != -1e9f) {
                r23 = (s16)cM_atan2s(f1 - sp28.y, temp.x - sp28.x);
                if (r23 > 0x2000 || r23 < -0x2000) {
                    r23 = 0;
                }
            }
        }
        if (i_this->dr.mState == 0x13) {
            r23 = 0;
            r21 = 0;
        }
        if (r21 != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->dr.m48C.x, r21, 1, 0x400);
        }
        if (r23 != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->dr.m48C.z, r23, 1, 0x400);
        }
    }
    
    return TRUE;
}

/* 0000DD1C-0000DD24       .text daBk_IsDelete__FP8bk_class */
static BOOL daBk_IsDelete(bk_class* i_this) {
    return TRUE;
}

/* 0000DD24-0000DDD8       .text daBk_Delete__FP8bk_class */
static BOOL daBk_Delete(bk_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "Bk");
    if (i_this->heap) {
        i_this->mpMorf->stopZelAnime();
    }
    if (i_this->m121D) {
        hio_set = 0;
        mDoHIO_root.mDoHIO_deleteChild(l_bkHIO.mChildID);
    }
    i_this->m0350.end();
    i_this->dr.mParticleCallBack.end();
    enemy_fire_remove(&i_this->mEnemyFire);
    return TRUE;
}

static u8 temp[0x25C] = {};

/* 0000DDD8-0000E2C8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    bk_class* i_this = (bk_class*)i_actor;
    
    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bk", BK_BDL_BK),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bk", BK_BCK_BK_SUWARI),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Bk", BK_BAS_BK_SUWARI),
        0x00080000,
        0x37221203
    );
    if (i_this->mpMorf == NULL || i_this->mpMorf->getModel() == NULL) {
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
    
    if (i_this->m02DC != 0) {
        i_this->m1230 = (J3DMaterialTable*)dComIfG_getObjectRes("Bk", BK_BMT_PINK);
    } else if (i_this->m02D4 != 0) {
        i_this->m1230 = (J3DMaterialTable*)dComIfG_getObjectRes("Bk", BK_BMT_GREEN);
    }
    
    i_this->m02C4 = new mDoExt_btpAnm();
    if (i_this->m02C4 == NULL) {
        // Bug: This function is supposed to return a boolean but here it returns a phase state instead.
        // TODO: Check what happens when this bug occurs.
        return cPhs_ERROR_e;
    }
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Bk", BK_BTP_TMABATAKI);
    if (!i_this->m02C4->init(model->getModelData(), btp, 1, 0, 1.0f, 0, -1, false, 0)) {
        // Bug: Same as above.
        // TODO check this case as well.
        return cPhs_ERROR_e;
    }
    
    J3DModelData* modelData;
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bk", BK_BMD_BK_KB);
    JUT_ASSERT(9418, modelData != 0);
    if (i_this->m02D5 & 0x40) {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Bk", BK_BMT_BK_KEN);
        modelData->setMaterialTable(bmt, J3DMatCopyFlag_Material);
    } else {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Bk", BK_BMT_BK_BOKO);
        modelData->setMaterialTable(bmt, J3DMatCopyFlag_Material);
    }
    i_this->m02E8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02E8 == NULL) {
        // Bug: Same as above.
        // TODO check this case as well.
        return cPhs_ERROR_e;
    }
    i_this->m02E8->setBaseScale(i_this->scale);
    
    if (i_this->m02D4 != 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bk", BK_BMD_BK_TATE);
        i_this->m02D0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(9445, modelData != 0);
    }
    
    if (i_this->m02DC != 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bk", BK_BDL_BOUEN);
        i_this->m02D8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(9454, modelData != 0);
    }
    
    static Vec hip_offset[] = {
        {0.0f, 0.0f, 0.0f},
    };
    static Vec momo_offset[] = {
        {-10.0f, 0.0f, 0.0f},
        {20.0f, 0.0f, 0.0f},
    };
    static Vec sune_offset[] = {
        {0.0f, -2.0f, 0.0f},
        {15.0f, -2.0f, 0.0f},
    };
    static Vec shipo_offset[] = {
        {0.0f, -1.0f, 0.0f},
        {22.0f, -1.0f, 0.0f},
    };
    static Vec mune1_offset[] = {
        {15.0f, 0.0f, 0.0f},
        {40.0f, 0.0f, 0.0f},
    };
    static Vec mune2_offset[] = {
        {40.0f, 0.0f, 0.0f},
        {60.0f, 0.0f, 0.0f},
    };
    static Vec udeL_offset[] = {
        {0.0f, 0.0f, 0.0f},
        {45.0f, 0.0f, 0.0f},
    };
    static Vec udeR_offset[] = {
        {0.0f, 0.0f, 0.0f},
        {-45.0f, 0.0f, 0.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 1, // Sphere
            /* mJointIndex */ 0x01, // hip1 joint
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ hip_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x03, // momoL joint
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ momo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x04, // suneL1 joint
            /* mRadius     */ 2.5f,
            /* mpOffsets   */ sune_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x08, // momorR joint
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ momo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x09, // suneR1 joint
            /* mRadius     */ 2.5f,
            /* mpOffsets   */ sune_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x0C, // sippo1 joint
            /* mRadius     */ 3.0f,
            /* mpOffsets   */ shipo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x0D, // sippo2 joint
            /* mRadius     */ 2.5f,
            /* mpOffsets   */ shipo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x0E, // sippo3 joint
            /* mRadius     */ 1.5f,
            /* mpOffsets   */ shipo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x0F, // sippo4 joint
            /* mRadius     */ 2.5f,
            /* mpOffsets   */ shipo_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x10, // mune joint
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ mune1_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x10, // mune joint
            /* mRadius     */ 15.0f,
            /* mpOffsets   */ mune2_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x21, // udeL2 joint
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ udeL_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x22, // udeL3 joint
            /* mRadius     */ 3.0f,
            /* mpOffsets   */ udeL_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x29, // udeR2 joint
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ udeR_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x2A, // udeR3 joint
            /* mRadius     */ 3.0f,
            /* mpOffsets   */ udeR_offset,
        },
    };
    i_this->mpJntHit = JntHit_create(i_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (i_this->mpJntHit) {
        i_this->jntHit = i_this->mpJntHit;
    } else {
        return FALSE;
    }
    
    return TRUE;
}

/* 0000E310-0000EA2C       .text daBk_Create__FP10fopAc_ac_c */
static s32 daBk_Create(fopAc_ac_c* i_actor) {
    /* Nonmatching - data */
    fopAcM_SetupActor(i_actor, bk_class);
    bk_class* i_this = (bk_class*)i_actor;
    
    s32 phase_state = dComIfG_resLoad(&i_this->mPhase, "Bk");
    if (phase_state == cPhs_COMPLEATE_e) {
        i_this->gbaName = 1;
        
        if (strcmp(dComIfGp_getStartStageName(), "ITest63") == 0 ||
            strcmp(dComIfGp_getStartStageName(), "GanonJ") == 0)
        {
            search_sp = 1;
        } else {
            search_sp = 0;
        }
        
        i_this->mType = fopAcM_GetParam(i_this) & 0xF;
        i_this->m02B9 = fopAcM_GetParam(i_this) & 0x10;
        i_this->m02D4 = fopAcM_GetParam(i_this) & 0x20;
        if (i_this->mType == 0xB) {
            i_this->m02D4 = 0;
            i_this->m02DC = 1;
            i_this->mType = 4;
        }
        i_this->m02D5 = fopAcM_GetParam(i_this) & 0xC0;
        i_this->m02B5 = fopAcM_GetParam(i_this) >> 8 & 0xFF;
        i_this->m02B6 = fopAcM_GetParam(i_this) >> 16 & 0xFF;
        i_this->m02B7 = fopAcM_GetParam(i_this) >> 24 & 0xFF;
        i_this->m02B8 = i_this->current.angle.z;
        i_this->current.angle.z = 0;
        i_this->current.angle.x = 0;
        if (i_this->m02B8 == 0xFF) {
            i_this->m02B8 = 0;
        }
        
        if (i_this->m02B8 != 0) {
            if (dComIfGs_isSwitch(i_this->m02B8, fopAcM_GetRoomNo(i_this))) {
                return cPhs_ERROR_e;
            }
        }
        if (i_this->m02B9 != 0) {
            if (dComIfGs_isSwitch(i_this->m02B7, fopAcM_GetRoomNo(i_this))) {
                return cPhs_ERROR_e;
            }
            i_this->m02B7 = 0xFF;
        }
        
        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Bk", 0);
        
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x17B20)) {
            return cPhs_ERROR_e;
        }
        
        if (!hio_set) {
            l_bkHIO.mChildID = mDoHIO_root.mDoHIO_createChild("ボコちゃん", &l_bkHIO); // "Boko-chan"
            i_this->m121D = 1;
            hio_set = 1;
        }
        
        ken = 0;
        
        if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
            return cPhs_ERROR_e;
        }
        
        fopAcM_SetMin(i_this, -200.0f, -50.0f, -100.0f);
        fopAcM_SetMax(i_this, 125.0f, 250.0f, 250.0f);
        fopAcM_SetMtx(i_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        i_this->mpMorf->getModel()->setUserArea((u32)i_this);
        i_this->initBt(162.5f, 125.0f);
        
        i_this->dr.m70C = 1;
        i_this->dr.mSpawnY = i_this->current.pos.y;
        i_this->dr.mMaxFallDistance = 1000.0f;
        
        if (i_this->m02B6 != 0xFF) {
            i_this->ppd = dPath_GetRoomPath(i_this->m02B6, fopAcM_GetRoomNo(i_this));
            if (i_this->ppd == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->m1215 = i_this->m02B6 + 1;
            i_this->m1217 = 1;
        }
        
        if (i_this->mType == 4 || i_this->mType == 0xA) {
            i_this->dr.mState = 1;
            if (i_this->mType == 0xA) {
                i_this->dr.m004 = -0x14;
                fopAcM_OnStatus(i_this, fopAcStts_BOSS_e);
            } else {
                i_this->dr.m004 = -1;
            }
            i_this->m0300[1] = 1000.0f + cM_rndF(1000.0f);
        } else if (i_this->mType == 6) {
            i_this->dr.mState = 2;
            i_this->dr.mMaxFallDistance = 300.0f;
        } else if (i_this->mType == 7) {
            i_this->dr.mState = 0x1D;
            i_this->dr.mMaxFallDistance = 300.0f;
        } else if (i_this->mType == 5) {
            anm_init(i_this, BK_BCK_BK_HAKOBI, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            i_this->dr.mState = 0x1E;
            i_this->dr.mMaxFallDistance = 100000.0f;
        } else if (i_this->mType == 2 || i_this->mType == 3) {
            i_this->m02BA = 0xFF;
            i_this->dr.mState = 0xF;
            i_this->m030E = 0xA;
        } else if (i_this->mType == 9) {
            i_this->dr.mState = 3;
            i_this->m1216 = i_this->current.angle.z;
            i_this->m1217 = i_this->current.angle.y;
            i_this->current.angle.z = 0;
            i_this->current.angle.y = 0;
        }
        
        if (i_this->m02B7 != 0xFF) {
            if (i_this->mType != 6) {
                i_this->m02BA = i_this->m02B7 + 1;
            }
        }
        
        if (i_this->mType == 0xF) {
            i_this->dr.mState = 0x17;
            i_this->m02BA = 0;
        }
        
        if (i_this->mType != 8 && i_this->m02DC == 0 &&
            strcmp(dComIfGp_getStartStageName(), "A_mori") != 0)
        {
            u32 weaponType; // TODO enum
            if (i_this->m02D5 & 0x40) {
                weaponType = 1;
            } else if (i_this->m02D5 & 0x80) {
                weaponType = 7;
            } else {
                weaponType = 0;
            }
            i_this->m1200 = fopAcM_create(PROC_BOKO, weaponType, &i_this->current.pos, fopAcM_GetRoomNo(i_this));
            i_this->m1214 = 1;
            i_this->m02D5 &= 0x40;
        } else {
            i_this->m11F3 = 1;
        }
        
        i_this->dr.mAcch.Set(
            fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this),
            i_this, 1, &i_this->dr.mAcchCir,
            fopAcM_GetSpeed_p(i_this)
        );
        i_this->dr.mAcchCir.SetWall(40.0f, 40.0f);
        i_this->dr.mAcch.ClrRoofNone();
        i_this->dr.mAcch.SetRoofCrrHeight(80.0f + g_regHIO.mChild[0].mFloatRegs[7]);
        i_this->dr.mAcch.OnLineCheck();
        i_this->dr.mInvincibleTimer = 5;
        
        if (i_this->m02D4 != 0) {
            i_this->max_health = i_this->health = 7;
        } else {
            i_this->max_health = i_this->health = 5;
        }
        
        i_this->dr.mStts.Init(200, 0xFF, i_this);
        static dCcD_SrcCyl co_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ 0,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VSGRP,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 62.5f,
                /* Height */ 100.0f,
            },
        };
        i_this->m0B88.Set(co_cyl_src);
        i_this->m0B88.SetStts(&i_this->dr.mStts);
        static dCcD_SrcCyl tg_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ 0,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ G_TG_MARK_UNK1,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 30.0f,
                /* Height */ 112.5f,
            },
        };
        i_this->m0CB8.Set(tg_cyl_src);
        i_this->m0CB8.SetStts(&i_this->dr.mStts);
        static dCcD_SrcSph head_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ 0,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ G_TG_MARK_UNK1,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 37.5f,
            },
        };
        i_this->m0DE8.Set(head_sph_src);
        i_this->m0DE8.SetStts(&i_this->dr.mStts);
        static dCcD_SrcSph wepon_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK800,
                /* SrcObjAt  Atp     */ 2,
                /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_ENEMY | AT_SPRM_VS_PLAYER | AT_SPRM_VS_OTHER,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ G_AT_MARK_NORMAL_HIT,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ G_AT_SPRM_NO_CON_HIT,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ 0,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 100.0f,
            },
        };
        i_this->m1040.Set(wepon_sph_src);
        i_this->m1040.SetStts(&i_this->dr.mStts);
        static dCcD_SrcSph defence_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ 0,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ dCcD_SE_UNK6,
                /* SrcGObjTg HitMark */ G_TG_MARK_PURPLE_HIT,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_SHIELD | G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 62.5f,
            },
        };
        i_this->m0F14.Set(defence_sph_src);
        i_this->m0F14.SetStts(&i_this->dr.mStts);
        
        i_this->m02CC = 5;
        i_this->model = i_this->mpMorf->getModel();
        
        i_this->mEnemyIce.mpActor = i_this;
        i_this->mEnemyIce.mWallRadius = 50.0f + g_regHIO.mChild[0].mFloatRegs[4];
        i_this->mEnemyIce.mCylHeight = 180.0f + g_regHIO.mChild[0].mFloatRegs[5];
        i_this->mEnemyIce.mDeathSwitch = i_this->m02B8;
        
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = i_this;
        static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
            0x12,
            0x10,
            0x29,
            0x2A,
            0x21,
            0x22,
            0x08,
            0x09,
            0x03,
            0x04,
        };
        static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
            2.0f,
            2.0f,
            1.2f,
            1.0f,
            1.2f,
            1.0f,
            1.2f,
            1.0f,
            1.2f,
            1.0f,
        };
        for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }
        
        i_this->stealItemLeft = 3;
        
        daBk_Execute(i_this);
    }
    
    return phase_state;
}

static actor_method_class l_daBk_Method = {
    (process_method_func)daBk_Create,
    (process_method_func)daBk_Delete,
    (process_method_func)daBk_Execute,
    (process_method_func)daBk_IsDelete,
    (process_method_func)daBk_Draw,
};

actor_process_profile_definition g_profile_BK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00B0,
    /* Actor SubMtd */ &l_daBk_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
