/**
 * d_a_fganon.cpp
 * Enemy - Phantom Ganon
 */

#include "d/actor/d_a_fganon.h"
#include "d/d_procname.h"
#include "JSystem/JUtility/JUTReport.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_mant.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_fganon.h"
#include "d/res/res_pgsw.h"
#include "f_op/f_op_camera.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

fganon_class* master;
u8 hio_set;
daFganon_HIO_c l_HIO;

/* 000000EC-000001A0       .text __ct__14daFganon_HIO_cFv */
daFganon_HIO_c::daFganon_HIO_c() {
    mNo = -0x1;
    m05 = 0;
    m06 = 0;
    m08 = 60;
    m0A = 500;
    m0C = 1500.0f;
    m10 = 400.0f;
    m14 = 1500.0f;
    m18 = 400.0f;
    m1C = 45.0f;
    m20 = 45.0f;
    m24 = 2.0f;
    m28 = 2.0f;
    m2C = 30.0f;
    m30 = -270.0f;
    m34 = -600.0f;
    m38 = 270.0f;
    m3C = 50;
    m3E = 1;
    m40 = 32;
    m44 = 600.0f;
    m48 = 150;
}

/* 000001A0-000002C8       .text anm_init__FP12fganon_classifUcfi */
void anm_init(fganon_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {    
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("Fganon", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Fganon", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    }
    else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Fganon", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000002C8-00000338       .text tama_draw__FP12fganon_class */
/* Renders PG's Energy Ball model */
void tama_draw(fganon_class* i_this) {
    if (i_this->m671 != 0) {
        J3DModel* pModel = i_this->mpEnergySphereModel;
        i_this->mpBrkAnm3->entry(pModel->getModelData());
        i_this->mpBtkAnm->entry(pModel->getModelData());
        mDoExt_modelUpdateDL(pModel);
    }
}

/* 00000338-00000420       .text daFganon_Draw__FP12fganon_class */
/* Renders all part's of Phantom Ganon's model including his body, sword, and energy ball */
static BOOL daFganon_Draw(fganon_class* i_this) {
    dSnap_RegistFig(DSNAP_TYPE_FGANON, i_this, 1.0f, 1.0f, 1.0f);
    J3DModel* pModel = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(pModel, &i_this->tevStr);
    i_this->mpBrkAnm1->entry(pModel->getModelData());
    i_this->mpMorf->entryDL();
    if (i_this->m2D0 != 2) {
        pModel = i_this->mpKenModel;
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->mKenTevStr);
        g_env_light.setLightTevColorType(pModel, &i_this->mKenTevStr);
        i_this->mpBrkAnm2->entry(pModel->getModelData());
        mDoExt_modelUpdateDL(pModel);
    }
    tama_draw(i_this);
    return TRUE;
}

/* 00000420-00000554       .text deru_brk__FP12fganon_class */
/* Appear Animation 1 */
void deru_brk(fganon_class* i_this) {
    J3DAnmTevRegKey* ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_MAIN1);
    i_this->mpBrkAnm1->init(i_this->mpMorf->getModel()->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_KEN1);
    i_this->mpBrkAnm2->init(i_this->mpKenModel->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    fopAcM_seStart(i_this, JA_SE_CM_PG_APPEAR, 0);
    i_this->mbIsMaterialized = TRUE;
}

/* 00000554-000006B8       .text kieru_brk__FP12fganon_classUc */
/* Disappear Animation 1 */
void kieru_brk(fganon_class* i_this, unsigned char param_2) {
    J3DAnmTevRegKey* ptrkAnm;
    if ((param_2 == 0) || (param_2 == 1)) {
        ptrkAnm = (J3DAnmTevRegKey *)(J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_KIERU_MAIN1);
        i_this->mpBrkAnm1->init(i_this->mpMorf->getModel()->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
        fopAcM_seStart(i_this, JA_SE_CM_PG_DISAPPEAR, 0);
    }
    if ((param_2 == 0) || (param_2 == 2)) {
        ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Pgsw", PGSW_BRK_KIERU_KEN1);
        i_this->mpBrkAnm2->init(i_this->mpKenModel->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    }
    i_this->mbIsMaterialized = FALSE;
}

/* 000006B8-000007EC       .text deru_brk2__FP12fganon_class */
/* Appear Animation 2 */
void deru_brk2(fganon_class* i_this) {
    J3DAnmTevRegKey* ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_MAIN2);
    i_this->mpBrkAnm1->init(i_this->mpMorf->getModel()->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_KEN2);
    i_this->mpBrkAnm2->init(i_this->mpKenModel->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    fopAcM_seStart(i_this, JA_SE_CM_PG_APPEAR, 0);
    i_this->mbIsMaterialized = TRUE;
}

/* 000007EC-00000920       .text kieru_brk2__FP12fganon_class */
/* Dissapear Animation 2 */
void kieru_brk2(fganon_class* i_this) {
    J3DAnmTevRegKey* ptrkAnm;
    ptrkAnm = (J3DAnmTevRegKey *)(J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_KIERU_MAIN2);
    i_this->mpBrkAnm1->init(i_this->mpMorf->getModel()->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_KIERU_KEN2);
    i_this->mpBrkAnm2->init(i_this->mpKenModel->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, 0);
    fopAcM_seStart(i_this, JA_SE_CM_PG_DISAPPEAR, 0);
    i_this->mbIsMaterialized = FALSE;
}

/* 00000920-00000AEC       .text pos_move__FP12fganon_classUc */
void pos_move(fganon_class* i_this, unsigned char param_2) {
    cXyz local_44;
    if (param_2 == 0) {
        local_44 = i_this->m38C - i_this->current.pos;
        s16 yTarget = cM_atan2s(local_44.x,local_44.z);
        f32 fVar2 = std::sqrtf(local_44.x * local_44.x + local_44.z * local_44.z);
        s16 xTarget = -cM_atan2s(local_44.y, fVar2);
        s16 yMaxStep = (s16)(i_this->m39C * i_this->m3A0);
        s16 scale =  5;
        cLib_addCalcAngleS2(&i_this->current.angle.y, yTarget, scale + REG0_S(3), yMaxStep);
        s16 xMaxStep = (s16)(i_this->m39C * i_this->m3A0);
        cLib_addCalcAngleS2(&i_this->current.angle.x, xTarget, scale + REG0_S(3), xMaxStep);
    }
    cLib_addCalc2(&i_this->m3A0, 1.0f, 1.0f, 0.05f);
    local_44.x = 0.0f;
    local_44.y = 0.0f;
    local_44.z = i_this->speedF;
    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    MtxPosition(&local_44, &i_this->speed);
    i_this->current.pos += i_this->speed;
}

/* 00000AEC-00000C14       .text fly_se_set__FP12fganon_class */
void fly_se_set(fganon_class* i_this) {
    cXyz local_34 = i_this->current.pos - i_this->old.pos;
    uint uVar2 = (uint)(local_34.abs() * 3.5f);
    if (uVar2 > 100) {
        uVar2 = 100;
    }
    fopAcM_seStart(i_this, JA_SE_CM_PG_FLYING, uVar2);
}

/* 00000C14-00001170       .text fly__FP12fganon_class */
void fly(fganon_class* i_this) {   
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;

    if ((((i_this->m384 & 0xF) == 0) && (cM_rndF(1.0f) < 0.5f)) || (i_this->m388 == -10)) {
        i_this->m398 = player->shape_angle.y;
    }

    switch (i_this->m388) {
    case -10:
        deru_brk(i_this);
        i_this->current.pos = i_this->home.pos;
        i_this->current.pos.y = player->current.pos.y + l_HIO.m10;
        i_this->shape_angle.y = fopAcM_searchPlayerAngleY(a_this);
        i_this->m388 = 1;
        anm_init(i_this, FGANON_BCK_WAIT1, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m3A4[1] = 60;
        break;
    case 0:
        anm_init(i_this, FGANON_BCK_WAIT1, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m388++;
        i_this->m3A0 = 0.0f;
        i_this->m3A4[1] = (short)(cM_rndF(50.0f) + 50.0f);
        // Fall-through
    case 1:
        if (i_this->m68A == 1) {
            anm_init(i_this, FGANON_BCK_WAIT1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        mDoMtx_YrotS(*calc_mtx, i_this->m398);
        cXyz offset;
        offset.z = l_HIO.m0C;
        offset.y = l_HIO.m10;
        offset.x = 0.0f;
        cXyz transformedPos;
        MtxPosition(&offset, &transformedPos);
        i_this->m38C = player->current.pos + transformedPos;
        offset = i_this->m38C - i_this->current.pos;
        if (offset.abs() > REG0_F(12) + 300.0f) {
            cLib_addCalc2(&i_this->speedF, REG0_F(15) + 30.0f, 1.0f, REG0_F(13) + 2.0f);
        } else {
            cLib_addCalc0(&i_this->speedF, 1.0f, REG0_F(14) + 1.0f);
        }
        i_this->m39C = REG0_F(5) + 1500.0f;
        cLib_addCalcAngleS2(&i_this->shape_angle.y, fopAcM_searchPlayerAngleY(i_this), 10, 0x400);
        
        cLib_addCalc2(&i_this->m3BC, REG0_F(11) + 50.0f, 1.0f, 2.0f);
        break;
    }

    pos_move(i_this, 0);
    
    fly_se_set(i_this);
    
    if (i_this->m3A4[1] == 0) {
        i_this->m386 = 6;
        i_this->m388 = 0;
    }
    
    if (i_this->m3A4[2] == 0) {
        i_this->m386 = 2;
        i_this->m388 = 0;
    }
}

/* 000015A8-00001BD0       .text shot__FP12fganon_class */
void shot(fganon_class* i_this) {    
    cLib_addCalcAngleS2(&i_this->shape_angle.y, fopAcM_searchPlayerAngleY(i_this), 10, 0x400);
    switch(i_this->m388) {
        case 0: {
            if (!i_this->m408) {
                anm_init(i_this, FGANON_BCK_TAME1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m388++;
                i_this->m3A4[0] = 40;
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_MAKE_S, 0);
                // Fall-through
            } else {
                break;
            }
        }
        case 1: {
            if (i_this->m3A4[0] == 30) {
                i_this->m408 = 1;
            }
            if (i_this->m3A4[0] < 30) {
                fopAcM_seStart(i_this, JA_SE_CM_PG_EBALL_MAKING_S, 0);
            }
            if (i_this->m3A4[0] == 0) {
                anm_init(i_this, FGANON_BCK_NAGERU1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m388++;
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_FIRE_S, 0);
                mDoAud_seStart(JA_SE_CM_PG_EBALL_FIRE_S, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            break;
        }
        case 2: {
            s32 mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
            if (REG0_S(0) + 14 == mFrame) {
                i_this->m409 = 1;
                i_this->m688 = 0;
                i_this->m687 = 0;
                i_this->m689 = 0;
            }            
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, FGANON_BCK_WAIT1, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m388++;
            }
            // Fall-through
        }
        case 3: {
            if (i_this->m408 == 5) {
                cXyz local_34 = i_this->m3E0 - i_this->eyePos;
                if (local_34.abs() < REG0_F(1) + (i_this->m404 * (REG0_F(0) + 10.0f) + 400.0f)) {
                    if (i_this->m689 == 0) {
                        if (cM_rndF(1.0f) < 0.5f) {
                            anm_init(i_this, FGANON_BCK_TENNISLR1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        }
                        else {
                            anm_init(i_this, FGANON_BCK_TENNISRL1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        }
                        i_this->m388++;
                        fopAcM_monsSeStart(i_this, JA_SE_CV_PG_REFLECT_EBALL, 0);
                        mDoAud_seStart(JA_SE_CM_PG_SWING_S, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                        i_this->m687++;
                        if ((i_this->m688 >= 7) || ((i_this->m687 >= 4) && (cM_rndF(1.0f) < 0.3f))) {
                            i_this->m689 = 1;
                        }
                    }
                    else if (i_this->m2BC == 2) {
                        i_this->m386 = 2;
                        i_this->m388 = 0;
                        return;
                    }
                }
            }
            break;
        }
        case 4: {
            if (((s32)i_this->mpMorf->getFrame() >= 5) && ((s32)i_this->mpMorf->getFrame() <= 15)) {
                i_this->m686 = 1;
            }
            if (i_this->mpMorf->isStop() || ((i_this->m2BC >= 1) && (i_this->mpMorf->getFrame() >= 20.0f)))
            {
                anm_init(i_this, FGANON_BCK_WAIT1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m388 = 3;
            }
            // Fall-through
        }
    }
    cLib_addCalc0(&i_this->speedF, 1.0f, REG0_F(14) + 1.0f);
    pos_move(i_this, 0);
    fly_se_set(i_this);
    if ((i_this->m388 >= 2) && (i_this->m408 == 0)) {
        i_this->m386 = 5;
        i_this->m388 = 0;
    }
    if ((i_this->m388 == 3) || (i_this->m388 == 4)) {
        mDoAud_monsSeStart(JA_SE_OBJ_PG_EBALL_FLY_S, &i_this->m3E0, 100, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
    }
}

/* 00001BD0-000020B8       .text spinattack__FP12fganon_class */
void spinattack(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;
    int mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
    switch(i_this->m388) {
        case 0: {
            i_this->shape_angle.y = player->shape_angle.y;
            i_this->m388 = 1;
            // Fall-through
        }
        case 1: {
            mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            cXyz offset(0.0f, l_HIO.m2C + 100.0f, l_HIO.m30);
            cXyz transformedPos;
            MtxPosition(&offset, &transformedPos);
            i_this->current.pos = player->current.pos + transformedPos;
            linChk.Set(&player->eyePos, &i_this->current.pos, a_this);
            if (!dComIfG_Bgsp()->LineCross(&linChk)) {
                i_this->current.pos.y -= 100.0f;
                anm_init(i_this, FGANON_BCK_WAIT1, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m388 = 2;
                i_this->m3A4[0] = 30;
                deru_brk(i_this);
                // Fall-through
            }
            else {
                i_this->shape_angle.y = cM_rndFX(0x8000);
                break;
            }
        }
        case 2: {
            if (i_this->m3A4[0] == 0) {
                anm_init(i_this, FGANON_BCK_KAITEN1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m388 = 3;
                i_this->speedF = 0.0f;
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_FIRE_S, 0);
            }
            break;
        }
        case 3: {
            if (mFrame == 14) {
                fopAcM_seStart(i_this, JA_SE_CM_PG_SWING_L, 0);
            }
            i_this->m685 = 1;
            i_this->mWeponSph.SetAtAtp(8);
            if (mFrame == l_HIO.m3E) {
              i_this->m6AC = l_HIO.m40 - l_HIO.m3E;
            }
            float fVar9;
            float fVar10;
            if ((mFrame >= 13) && (mFrame <= 24)) {
                fVar9 = 20.0f;
                fVar10 = 4.0f;
            }
            else {
                fVar9 = 0.0f;
                fVar10 = 4.0f;
            }
            cLib_addCalc2(&i_this->speedF, fVar9, 1.0f, fVar10);
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->current.angle.x = 0;
            pos_move(i_this, 1);
            if (i_this->mpMorf->isStop()) {
                i_this->m386 = 2;
                i_this->m388 = 0;
            }
            break;
        }
    }
}

/* 000020B8-00002614       .text fly2__FP12fganon_class */
void fly2(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;

    if ((((i_this->m384 & 0xF) == 0) && (cM_rndF(1.0f) < 0.5f)) || (i_this->m388 == -10)) {
        i_this->m398 = player->shape_angle.y;
    }
    switch (i_this->m388) {
    case -10:
        deru_brk(i_this);
        i_this->current.pos = i_this->home.pos;
        i_this->current.pos.y = player->current.pos.y + l_HIO.m18;
        i_this->shape_angle.y = fopAcM_searchPlayerAngleY(a_this);
        i_this->m388 = 1;
        anm_init(i_this, FGANON_BCK_WAIT1, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m3A4[1] = 40;
        break;
    case 0:
        anm_init(i_this, FGANON_BCK_WAIT1, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m388++;
        i_this->m3A0 = 0.0f;
        i_this->m3A4[1] = (short)(cM_rndF(50.0f) + 50.0f);
        // Fall-through
    case 1:
        if (i_this->m68A == 1) {
            anm_init(i_this, FGANON_BCK_WAIT1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        mDoMtx_YrotS(*calc_mtx, i_this->m398);
        cXyz offset;
        offset.z = l_HIO.m14;
        offset.y = l_HIO.m18;
        offset.x = 0.0f;
        cXyz transformedPos;
        MtxPosition(&offset, &transformedPos);
        i_this->m38C = player->current.pos + transformedPos;
        offset = i_this->m38C - i_this->current.pos;
        if (offset.abs() > REG0_F(12) + 300.0f) {
            cLib_addCalc2(&i_this->speedF, REG0_F(15) + 30.0f, 1.0f, REG0_F(13) + 2.0f);
        } else {
            cLib_addCalc0(&i_this->speedF, 1.0f, REG0_F(14) + 1.0f);
        }
        i_this->m39C = REG0_F(5) + 1500.0f;
        cLib_addCalcAngleS2(&i_this->shape_angle.y, fopAcM_searchPlayerAngleY(i_this), 10, 0x400);
        
        cLib_addCalc2(&i_this->m3BC, REG0_F(11) + 50.0f, 1.0f, 2.0f);
        break;
    }

    pos_move(i_this, 0);
    
    fly_se_set(i_this);
    
    if (i_this->m3A4[1] == 0) {
        i_this->m386 = 11;
        i_this->m388 = 0;
    }
    
    if (i_this->m3A4[2] == 0) {
        i_this->m386 = 2;
        i_this->m388 = 0;
    }
}

/* 00002614-000029C8       .text tama_set__FP12fganon_class */
void tama_set(fganon_class* i_this) {
    if (i_this->m671 != 0) {
        mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
        cXyz offset;
        offset.x = 0.0f;
        offset.y = -i_this->m680;
        offset.z = i_this->m680;
        cXyz transformedPos;
        MtxPosition(&offset, &transformedPos);
        cXyz tempPos(i_this->current.pos.x + transformedPos.x, transformedPos.y + (400.0f + i_this->current.pos.y + REG8_F(4)), i_this->current.pos.z + transformedPos.z);
        i_this->m664 = tempPos;
        switch (i_this->m671) {
            case 1: {
                for (int i = 0; i < 2; i++) {
                    if (i_this->mEmitters3[i] != NULL) {
                        i_this->mEmitters3[i]->becomeInvalidEmitter();
                        i_this->mEmitters3[i] = NULL;
                    }
                }
                i_this->mEmitters3[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_821A, &tempPos, NULL);
                i_this->mEmitters3[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_821B, &tempPos, NULL);
                i_this->m672 = 250;
                i_this->m671 = 2;
                i_this->mpBrkAnm3->setPlaySpeed(1.0f);
            }
            case 2: {
                break;
            }
            case 3: {
                i_this->mpBrkAnm3->setPlaySpeed(-1.0f);
                i_this->m671 = 4;
                dComIfGp_particle_set(dPa_name::ID_SCENE_8242, &tempPos, &i_this->shape_angle);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8243, &tempPos, &i_this->shape_angle);
                break;
            }
            case 4: {
                i_this->m672 -= 50;
                for (int i = 0; i < 2; i++) {
                    if (i_this->mEmitters3[i] != NULL) {
                        i_this->mEmitters3[i]->setGlobalAlpha(i_this->m672);
                    }
                }
                if (i_this->m672 == 0) {
                    i_this->m671 = 5;
                }
                break;
            }
            case 5:
            case 6:
            case 7:
            case 8: {
                i_this->m671++;
                break;
            }
            case 9: {
                i_this->m671 = 0;
                break;
            }
        }
        for (int i = 0; i < 2; i++) {
            if (i_this->mEmitters3[i] != NULL) {
                if (i_this->m672 != 0) {
                    i_this->mEmitters3[i]->setGlobalTranslation(tempPos.x, tempPos.y, tempPos.z);
                } else {
                    i_this->mEmitters3[i]->becomeInvalidEmitter();
                    i_this->mEmitters3[i] = NULL;
                }
            }
        }
        mDoMtx_stack_c::transS(tempPos.x, tempPos.y, tempPos.z);
        i_this->mpEnergySphereModel->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpBrkAnm3->play();
        i_this->mpBtkAnm->play();
    }
}

/* 000029C8-00002A38       .text mahou_set__FP12fganon_class */
void mahou_set(fganon_class* i_this) {
    for (int i = 0; i < 8; i++) {
        fopAcM_create(PROC_FGMAHOU, i, &i_this->m664, i_this->current.roomNo);
    }
    i_this->m670 = 0;
}

/* 00002A38-000030C4       .text shot2__FP12fganon_class */
void shot2(fganon_class* i_this) {
    cLib_addCalcAngleS2(&i_this->shape_angle.y, fopAcM_searchPlayerAngleY(i_this), 10, 0x400);
    int mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
    switch(i_this->m388) {
        case 0: {
            anm_init(i_this, FGANON_BCK_TAME_S1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            for (int i = 0; i < 2; i++) {
                if (i_this->mEmitters2[i] != NULL) {
                    i_this->mEmitters2[i]->becomeInvalidEmitter();
                    i_this->mEmitters2[i] = NULL;
                }
            }
            i_this->mEmitters2[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_8218, &i_this->current.pos, NULL);
            i_this->mEmitters2[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_8219, &i_this->current.pos, NULL);
            fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_MAKE_L, 0);
            i_this->m388++;
            // Fall-through
        }
        case 1: {
            fopAcM_seStart(i_this, JA_SE_CM_PG_EBALL_MAKING_L, 0);
            for (int i = 0; i < 2; i++) {
                if (i_this->mEmitters2[i] != NULL) {
                    i_this->mEmitters2[i]->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x1A));
                }
            }
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, FGANON_BCK_TAME_S2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m3A4[0] = l_HIO.m3C;
                i_this->m388++;
                for (int i = 0; i < 2; i++) {
                    if (i_this->mEmitters2[i] != NULL) {
                        i_this->mEmitters2[i]->becomeInvalidEmitter();
                        i_this->mEmitters2[i] = NULL;
                    }
                }
            }
            if (mFrame == 28) {
                i_this->m671 = 1;
                i_this->m680 = 0.0f;
            }
            break;
        }
        case 2: {
            fopAcM_seStart(i_this, JA_SE_CM_PG_EBALL_MAKING_L, 0);
            if (i_this->m3A4[0] == 0) {
                anm_init(i_this, FGANON_BCK_NAGERU_S1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m388++;
                i_this->mEmitters2[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_821C, &i_this->current.pos, NULL);
                i_this->mEmitters2[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_821D, &i_this->current.pos, NULL);
            }
            else {
                break;
            }
        }
        case 3: {
            if (mFrame == REG8_S(5) + 15) {
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_FIRE_L, 0);
                mDoAud_seStart(JA_SE_CM_PG_EBALL_FIRE_L, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            if (mFrame >= REG8_S(5) + 15) {
                cLib_addCalc2(&i_this->m680, REG8_F(6) + 250.0f, 1.0f, REG8_F(7) + 50.0f);
                if (mFrame == REG8_S(6) + 16) {
                    i_this->m671 = 3;
                }
            
                if (mFrame == REG8_S(7) + 16) {
                    mahou_set(i_this);
                }
            }
            for (int i = 0; i < 2; i++) {
                if (i_this->mEmitters2[i] != NULL) {
                    int jointNo = (i * 9) + 14;
                    i_this->mEmitters2[i]->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(jointNo));
                }
            }
            if (i_this->mpMorf->isStop()) {
                i_this->m3A4[0] = 60;
                i_this->m388 = 4;
                for (int i = 0; i < 2; i++) {
                    if (i_this->mEmitters2[i] != NULL) {
                        i_this->mEmitters2[i]->becomeInvalidEmitter();
                        i_this->mEmitters2[i] = NULL;
                    }
                }
            }
            break;
        }
        case 4: {
            if (i_this->m68A == 1) {
                anm_init(i_this, FGANON_BCK_WAIT1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            if (i_this->m3A4[0] == 0) {
                i_this->m386 = 9;
                i_this->m388 = 0;
            }
            break;
        }
        default: {
            break;
        }
    }
    cLib_addCalc0(&i_this->speedF, 1.0f, REG0_F(14) + 1.0f);
    pos_move(i_this,0);
    fly_se_set(i_this);
    tama_set(i_this);
}

/* 000030C4-00003690       .text spinattack2__FP12fganon_class */
void spinattack2(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;
    int mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
    switch(i_this->m388) {
        case 0: {
            i_this->shape_angle.y = player->shape_angle.y + i_this->m68F * 0x3333;
            i_this->m388 = 1;
            if (i_this->m68F == 0) {
                for (int i = 1; i < 5; i++) {
                    fopAcM_create(PROC_FGANON, (i * 16) | 3, &i_this->current.pos, i_this->current.roomNo);
                }
            }
        }
        case 1: {
            mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            cXyz offset;
            offset.x = 0.0f;
            offset.y = l_HIO.m2C;
            offset.z = l_HIO.m34;
            cXyz transformedPos;
            MtxPosition(&offset, &transformedPos);
            i_this->current.pos = player->current.pos + transformedPos;
            anm_init(i_this, 10, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m388 = 2;
            deru_brk(i_this);
            i_this->m38C = player->current.pos;
        }
        case 2: {
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->speedF = REG8_F(4) + 5.0f;
            i_this->current.angle.x = 0;
            pos_move(i_this, 1);
            cXyz local_e4;
            local_e4 = i_this->m38C - i_this->current.pos;
            if (local_e4.abs() < l_HIO.m38) {
                anm_init(i_this, 9, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m388 = 3;
                i_this->speedF = 0.0f;
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_EBALL_FIRE_S, 0);
                break;
            }
            else {
                break;
            }
        }
        case 3: {
            if (mFrame == 14) {
                fopAcM_seStart(i_this, JA_SE_CM_PG_SWING_L, 0);
            }
            i_this->m685 = 1;
            i_this->mWeponSph.SetAtAtp(8);
            if (mFrame == l_HIO.m3E) {
              i_this->m6AC = l_HIO.m40 - l_HIO.m3E;
            }
            if (i_this->mpMorf->isStop()) {
                if (i_this->m68F == 0) {
                    i_this->m388 = 4;
                    i_this->m3A4[0] = 40;
                    anm_init(i_this, FGANON_BCK_WAIT1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
                else {
                    i_this->m386 = 2;
                    i_this->m388 = 0;
                }
            }
            break;
        }
        case 4: {
            if (i_this->m3A4[0] == 0) {
                i_this->m386 = 2;
                i_this->m388 = 0;
            }
            break;
        }
        default:
            break;
    }
}

/* 00003690-00003B3C       .text down__FP12fganon_class */
void down(fganon_class* i_this) {
    switch(i_this->m388) {
        case 0: {
            anm_init(i_this, 6, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m388++;
            i_this->speed.y = 0.0f;
        }
        case 1: {
            i_this->m3AE = 5;
            if (i_this->mAcch.ChkGroundHit()) {
                if (i_this->mpMorf->isStop()) {
                    i_this->m388++;
                    anm_init(i_this, FGANON_BCK_TYAKUTI1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                }
            }
            i_this->m3A4[0] = l_HIO.m48;
            break;
        }
        case 2: {
            if (i_this->mpMorf->isStop()) {
                i_this->m388++;
                anm_init(i_this, 8, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            break;
        }
        case 3: {
            int mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
            if (mFrame == 2) {
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_TIRED, 0);
            }
            break;
        }
        case 10: {
            anm_init(i_this, 7, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m388 = 2;
        }
        default:
            break;
    }
    i_this->current.pos.y += i_this->speed.y;
    i_this->speed.y -= 0.5f;
    if (i_this->speed.y < -15.0f) {
        i_this->speed.y = -15.0f;
    }
    
    s8 bVar3 = FALSE;
    dBgS_ObjGndChk_Spl gndChk;
    Vec sp2C;
    sp2C = i_this->current.pos;
    sp2C.y += 300.0f;
    gndChk.SetPos(&sp2C);
    f32 height = dComIfG_Bgsp()->GroundCross(&gndChk);
    if (height != C_BG_MIN_HEIGHT && i_this->current.pos.y <= height) {
        bVar3 = TRUE;
    }
    if ((i_this->m3A4[0] == 0) || bVar3) {
        i_this->m386 = 2;
        i_this->m388 = 0;
        if (i_this->m2BC != 0) {
            i_this->health = 100;
        }
    }
}

/* 00003F7C-00004300       .text kabe_check__FP12fganon_class */
BOOL kabe_check(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = l_HIO.m34 + 100.0f;
    for (int i = 0; i < 8; i++) {
        cMtx_YrotS(*calc_mtx, i * 0x2000);
        cXyz transformedPos;
        MtxPosition(&offset, &transformedPos);
        cXyz tempPos = player->eyePos + transformedPos;
        linChk.Set(&player->eyePos, &tempPos, a_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00004300-000044CC       .text deru__FP12fganon_class */
void deru(fganon_class* i_this) {
    i_this->m3AE = 3;
    switch(i_this->m388) {
    case 0:
        if(l_HIO.m06 != 0) {
            if (l_HIO.m06 == 1) {
                i_this->m386 = 5;
                i_this->m388 = -10;
                i_this->m3A4[2] = l_HIO.m0A;
            }
            else if (l_HIO.m06 == 2) {
                i_this->m386 = 7;
                i_this->m388 = 0;
            }
            else if (l_HIO.m06 == 3) {
                i_this->m386 = 9;
                i_this->m388 = -10;
                i_this->m3A4[2] = l_HIO.m0A;
            }
            else if (l_HIO.m06 == 4) {
                i_this->m386 = 10;
                i_this->m388 = 0;
            }
        }
        else {
            if (i_this->m2BC == 0) {
                if (cM_rndF(1.0f) < 0.5f) {
                    i_this->m386 = 5;
                    i_this->m388 = -10;
                    i_this->m3A4[2] = l_HIO.m0A;
                }
                else {
                    i_this->m386 = 7;
                    i_this->m388 = 0;
                }
            }
            else {
                if ((cM_rndF(1.0f) < 0.4f) && !kabe_check(i_this)) {
                    i_this->m386 = 10;
                    i_this->m388 = 0;
                }
                else {
                    if (cM_rndF(1.0f) < 0.5f) {
                        i_this->m386 = 9;
                        i_this->m388 = -10;
                        i_this->m3A4[2] = l_HIO.m0A;
                    }
                    else {
                        i_this->m386 = 5;
                        i_this->m388 = -10;
                        i_this->m3A4[2] = l_HIO.m0A;
                    }
                }
            }
        }
        break;
    }
}

/* 000044CC-00004584       .text kieru__FP12fganon_class */
void kieru(fganon_class* i_this) {
    i_this->m3AE = 3;
    switch(i_this->m388) {
        case 0: {
            if ((i_this->m408 == 1) || (i_this->m408 == 2)) {
                i_this->m408 = 35;
            }
            kieru_brk(i_this, 0);
            if (i_this->m68F != 0) {
                i_this->m388 = 1;
                i_this->m3A4[0] = 30;
            }
            else {
                i_this->m386 = 0;
                i_this->m388 = 0;
            }
            break;
        }
        case 1: {
            if (i_this->m3A4[0] == 0) {
                fopAcM_delete(i_this);
            }
            break;
        }
    }
}

/* 00004584-00004BC8       .text fail__FP12fganon_class */
void fail(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;

    i_this->m3AE = 3;
    switch(i_this->m388) {
        case 0: {
            kieru_brk(i_this, 1);
            i_this->m388 = 1;
            anm_init(i_this, 7, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            break;
        }
        case 1: {
            if (i_this->mpMorf->isStop()) {
                i_this->m388 = 2;
                i_this->m3A4[0] = 30;
                
                dBgS_LinChk linChk;
                
                cMtx_YrotS(*calc_mtx, i_this->home.angle.y);

                cXyz offset;
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 10000.0f;

                cXyz transformedPos;
                MtxPosition(&offset, &transformedPos);

                offset = i_this->home.pos;
                offset.y += 100.0f;

                transformedPos += offset;

                linChk.Set(&offset, &transformedPos, a_this);

                cMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(0x18), *calc_mtx);
                
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;

                MtxPosition(&offset, &transformedPos);

                if (dComIfG_Bgsp()->LineCross(&linChk)) {
                    offset = linChk.GetCross();
                }

                i_this->m6A0 = i_this->shape_angle.y - cM_atan2s(transformedPos.x - offset.x, transformedPos.z - offset.z) + 0x7058 + REG0_S(8);
                i_this->m6A4 = REG0_S(5) + 0x80;
                i_this->m6A8 = 100;
                break;
            }
            else {
                break;
            }
        }
        case 2: {
            if (i_this->m3A4[0] == 0) {
                cLib_addCalcAngleS2(&i_this->m6A2, i_this->m6A0, 1, ((s16)i_this->m69C)+i_this->m6A4);
                i_this->m694 += i_this->m698;
                i_this->m698 += i_this->m69C;
                i_this->m69C += REG12_F(10) + 3.0f;
                
                if (i_this->m69C > 1000.0f + REG12_F(3)) {
                    i_this->m69C = 1000.0f + REG12_F(3);
                }

                if (i_this->m694 >= 15884.0f) {
                    i_this->m694 = 15884.0f;
                    i_this->m6A4 = REG0_S(6) + 0x800;
                    if (i_this->m698 > REG12_F(1) + 700.0f) {
                        i_this->m698 *= -(REG12_F(2) + 0.4f);
                        fopAcM_seStart(i_this, JA_SE_OBJ_TN_SWORD_FALL, i_this->m6A8);
                        if (i_this->m6A8 >= 30) {
                            i_this->m6A8 -= 20;
                        }
                        if (i_this->m6A6 == 0) {
                            i_this->m6A6 = REG0_S(1) + 30;
                        }
                    }
                    else {
                        i_this->m698 = 0.0f;
                        i_this->m3A4[0] = 0;
                        i_this->m388 = 3;
                    }
                }
            }
            break;
        }
        case 3: {
            if (i_this->m3A4[0] == 0) {
                kieru_brk(i_this, 2);
                i_this->m3A4[0] = 10;
                i_this->m388 = 4;
                i_this->mBokoID = fopAcM_create(PROC_BOKO, 5, &i_this->current.pos, i_this->current.roomNo);
            }
            break;
        }
        case 4: {
            daBoko_c* act = (daBoko_c*)fopAcM_SearchByID(i_this->mBokoID);
            if (act != NULL) {
                if (!fopAcM_checkCarryNow(act)) {
                    fopAcM_setCarryNow(act, 0);
                }
                act->setMatrix(i_this->mpKenModel->getBaseTRMtx());
                if (i_this->m3A4[0] == 0) {
                    fopAcM_delete(i_this);
                    act->m2BC = 1;
                    fopAcM_cancelCarryNow(act);
                }
            }
            break;
        }
        default: 
            break;
    }
}

/* 00004BC8-00004DB4       .text standby__FP12fganon_class */
void standby(fganon_class* i_this) {
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    i_this->m3AE = 3;
    switch(i_this->m388) {
        case -1: {
            if (i_this->m2BC == 2) {
                if (!dComIfGs_checkGetItem(dItem_LIGHT_ARROW_e)) {
                    i_this->current.pos.y = -20000.0f;
                    break;
                }
            }
            else if ((i_this->m2BC == 1) && dComIfGs_checkGetItem(dItem_LIGHT_ARROW_e)) {
                i_this->current.pos.y = -20000.0f;
                break;
            }
            float xOffset = player->current.pos.x - i_this->home.pos.x;
            float zOffset = player->current.pos.z - i_this->home.pos.z;
            float distXZ = std::sqrtf(xOffset * xOffset + zOffset * zOffset);
            if (distXZ < i_this->m2BD * 10.0f) {
                i_this->m3A4[0] = l_HIO.m08;
                i_this->m388 = 1;
                fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
                i_this->mB89 = 22;
            }
            break;
        }
        case 0: {
            i_this->m3A4[0] = l_HIO.m08;
            i_this->m388++;
            // fallthrough
        }
        case 1: {
            if (i_this->m3A4[0] == 0) {
                i_this->m386 = 1;
                i_this->m388 = 0;
                i_this->m69C = 0.0f;
                i_this->m698 = 0.0f;
                i_this->m694 = 0.0f;
            }
        }
    }
    
}

/* 00004DB4-00005128       .text start__FP12fganon_class */
void start(fganon_class* i_this) {
    cXyz offset;
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    i_this->m3AE = 3;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    switch(i_this->m388) {
        case 0: {
            offset = player->current.pos - i_this->home.pos;
            float distXZ = std::sqrtf(offset.x * offset.x + offset.z * offset.z);
            if (distXZ < i_this->m2BD * 10.0f) {
                i_this->mB54 = 1;
                i_this->m388 = 1;
                anm_init(i_this, FGANON_BCK_WAIT1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                mDoAud_bgmAllMute(30);
            }
            break;
        }
        case 1: {
            i_this->shape_angle.y = fopAcM_searchPlayerAngleY(a_this);
            break;
        }
        case 2: {
            anm_init(i_this, FGANON_BCK_WARAU1, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            fopAcM_monsSeStart(i_this, JA_SE_CV_PG_LAUGH_2, 0);
            i_this->m388 = 3;
            break;
        }
        case 4: {
            i_this->m388 = 5;
            i_this->m3A4[0] = REG0_S(0) + 0x50;
            anm_init(i_this, FGANON_BCK_TAME1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        case 5: {
            if (i_this->m3A4[0] == (s16)(REG0_S(0) + 0x4B)) {
                i_this->m408 = 1;
                mDoAud_subBgmStart(JA_BGM_P_GANON_1);
            }
            if (i_this->m3A4[0] <= (s16)(REG0_S(0) + 0x4B)) {
                fopAcM_seStart(i_this, JA_SE_CM_PG_EBALL_MAKING_S, 0);
            }
            offset.x = 0.0f;
            offset.y = i_this->speedF * 0.5f;
            offset.z = -i_this->speedF;
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            MtxPosition(&offset, &i_this->speed);
            i_this->current.pos += i_this->speed;
            float fVar1;
            if (i_this->m3A4[0] == 0) {
                fVar1 = 0.0f;
            }
            else {
                fVar1 = REG0_F(7) + 20.0f;
            }
            cLib_addCalc2(&i_this->speedF, fVar1, 1.0f, REG0_F(5) + 0.5f);
        }
    }
}

/* 00005128-00005350       .text end__FP12fganon_class */
void end(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;

    i_this->m3AE = 3;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    s32 mFrame = i_this->mpMorf->mFrameCtrl.getFrame();
    switch(i_this->m388) {
        case 0: {
            i_this->m388 = 1;
            anm_init(i_this, FGANON_BCK_LAST_DAMAGE1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mB54 = 50;
            dComIfGs_onEventBit(0x3f20); // PG_DEFEATED? It appears further down in `energy_ball_move`
            break;
        case 1: {
            if (mFrame == 104) {
                kieru_brk(i_this, 0);
            }
            break;
        }
        case 2: {
            deru_brk(i_this);
            anm_init(i_this, FGANON_BCK_WARAU1, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            fopAcM_monsSeStart(i_this, JA_SE_CV_PG_LAUGH_2, 0);
            i_this->m388 = 3;
            break;
        }
        case 4: {
            deru_brk(i_this);
            anm_init(i_this, FGANON_BCK_SARU1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m388 = 5;
            i_this->speed.y = 0.0f;
            fopAcM_seStart(i_this, JA_SE_CM_PG_END_1, 0);
        }
        case 5:
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += REG8_F(8) + 0.2f;
            if (i_this->speed.y > REG8_F(9) + 20.0f) {
                i_this->speed.y = REG8_F(9) + 20.0f;
            }
            if (mFrame == 28) {
                kieru_brk2(i_this);
            }
            if (mFrame == 48) {
                i_this->m388 = 6;
            }
        }
        case 6:
            break;
    }
}

/* 00005350-000056A4       .text last_end__FP12fganon_class */
void last_end(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;

    i_this->m3AE = 3;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    switch(i_this->m388) {
        case 0: {
            i_this->m388 = 1;
            anm_init(i_this, FGANON_BCK_MOGAKU1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mB54 = 100;
            i_this->m3C0 = 10000.0f;
            i_this->m3A4[0] = REG0_S(4) + 25;
            i_this->m3A4[1] = 150;
        }
        case 1: {
            if (i_this->m3A4[1] == 0) {
                i_this->m388 = 2;
                i_this->m3A4[1] = 20;
                i_this->m2D0 = 1;
                i_this->mB54++;
            }
            break;
        }
        case 2: {
            cLib_addCalc2(&i_this->scale.x, 0.1f, 1.0f, 0.05f);
            cLib_addCalc2(&i_this->scale.z, 0.1f, 1.0f, 0.05f);
            cLib_addCalc2(&i_this->scale.y, 0.1f, 1.0f, 0.05f);
            if (i_this->m3A4[1] == 0) {
                i_this->m388 = 3;
                i_this->m3A4[1] = 30;
                fopAcM_seStart(i_this, JA_SE_CM_L_ARROW_PASS_AWAY, 0);
            }
            break;
        }
        case 3: {
            cLib_addCalc0(&i_this->scale.x, 0.1f, 0.05f); 
            cLib_addCalc0(&i_this->scale.z, 0.1f, 0.05f);
            cLib_addCalc2(&i_this->scale.y, 10.0f, 0.1f, 1.0f);
            if (i_this->m3A4[1] == 0) {
                i_this->scale.x = 0.0f;
                i_this->scale.y = 0.0f;
                i_this->scale.z = 0.0f;
                i_this->m388 = 4;
                i_this->m3A4[1] = 30;
            }
            break;
        }
        case 4: {
            if (i_this->m3A4[1] <= 4) {
                if (i_this->m3A4[1] == 4) {
                    i_this->mBokoID = fopAcM_create(PROC_BOKO, 5, &i_this->current.pos, i_this->current.roomNo);
                }
                daBoko_c* mBoko = (daBoko_c*)fopAcM_SearchByID(i_this->mBokoID);
                if (mBoko != NULL) {
                    i_this->m2D0 = 2;
                    if (!fopAcM_checkCarryNow(mBoko)) {
                        fopAcM_setCarryNow(mBoko, 0);
                    }
                    mBoko->setMatrix(i_this->mpKenModel->getBaseTRMtx());
                    if (i_this->m3A4[1] == 1) {
                        fopAcM_cancelCarryNow(mBoko);
                        i_this->m388 = 5;
                        i_this->mB54++;
                        i_this->mB56 = 0;
                    }
                }
            }
            break;
        }
        case 5:
            break;
        default:
            break;
    }
    i_this->tevStr.mFogColor.b = 0xFF;
    i_this->tevStr.mFogColor.g = 0xFF;
    i_this->tevStr.mFogColor.r = 0xFF;
    i_this->tevStr.mFogStartZ = REG8_F(10);
    i_this->tevStr.mFogEndZ = i_this->m3C0;
    if (i_this->m3A4[0] <= 1) {
        if (i_this->m3A4[0] == 1) {
            i_this->m68E = 1;
            i_this->m3C0 = 5100.0f;
        }
        cLib_addCalc2(&i_this->m3C0, 100.0f, 1.0f, REG0_F(4) + 63.5f);
    }
    cLib_addCalcAngleS2(&i_this->current.angle.x, 0, 4, 0x800);
}

/* 000056A4-00006288       .text damage_check__FP12fganon_class */
void damage_check(fganon_class* i_this) {
    CcAtInfo atInfo;
    cXyz* pPos;

    csXyz local_a0;
    cXyz local_44;
    cXyz local_80;
    cXyz local_98;
    JPABaseEmitter* mEmitter;
    float distXZ;

    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (i_this->m3AE != 0) {
        return;
    }
    atInfo.pParticlePos = NULL;
    if (i_this->mCyl.ChkTgHit()) {
        atInfo.mpObj = i_this->mCyl.GetTgHitObj();
        if (atInfo.mpObj) {
            atInfo.pParticlePos = i_this->mCyl.GetTgHitPosP();
            atInfo.mpActor = atInfo.mpObj->GetAc();
            if (i_this->m2BC == 2) {
                if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                    fopAcM_monsSeStart(i_this, JA_SE_CV_PG_DIE, 0);
                    fopAcM_seStart(a_this, JA_SE_CM_PG_END_2, 0);
                    
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->eyePos, NULL);
                    
                    local_44.z = 2.0f;
                    local_44.y = 2.0f;
                    local_44.x = 2.0f;
                    
                    local_a0.z = 0.0f;
                    local_a0.x = 0.0f;
                    local_a0.y = fopAcM_searchPlayerAngleY(i_this);
                    
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->eyePos, &local_a0, &local_44);
                    dKy_SordFlush_set(i_this->eyePos, 1);

                    i_this->m386 = 22;
                    i_this->m388 = 0;
                    i_this->m3AE = 1000;

                    mDoAud_subBgmStop();
                    if (i_this->m408 != 0) {
                        i_this->m408 = 35;
                    }

                    fopAcM_seStart(a_this, JA_SE_CM_L_ARROW_SHRINK, 0);

                    mEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8405, &i_this->current.pos, NULL);
                    if (mEmitter != NULL) {
                        mEmitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(10));
                    }

                    mEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8406, &i_this->current.pos, NULL);
                    if (mEmitter != NULL) {
                        mEmitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(10));
                    }

                    i_this->speedF = 0.0f;
                }
                else {
                    i_this->m386 = 2;
                    i_this->m388 = 0;
                    if ((i_this->m408 == 1) || (i_this->m408 == 2)) {
                        i_this->m408 = 35;
                    }
                }

                i_this->m671 = 0;

                for (int i = 0; i < 2; i++) {
                    if(i_this->mEmitters3[i] != NULL) {
                        i_this->mEmitters3[i]->becomeInvalidEmitter();
                        i_this->mEmitters3[i] = NULL;
                    }
                }

                return;
            }
            if (atInfo.mpActor && (fopAcM_GetName(atInfo.mpActor) == PROC_FGMAHOU)) {
                i_this->m670++;

                anm_init(i_this, 6, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);

                i_this->m3A4[0] = 60;

                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_HIT_EBALL, 0);

                if(i_this->m670 < 5) {
                    return;
                }

                dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->eyePos, NULL);

                local_44.z = 2.0f;
                local_44.y = 2.0f;
                local_44.x = 2.0f;

                local_a0.z = 0.0f;
                local_a0.x = 0.0f;
                local_a0.y = fopAcM_searchPlayerAngleY(i_this);

                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->eyePos, &local_a0, &local_44);
                dKy_SordFlush_set(i_this->eyePos, 1);
                
                i_this->m386 = 8;
                i_this->m388 = 0;
                i_this->m3B0 = REG8_F(11) + 80.0f;
                i_this->m3B8 = REG8_S(2) + 7;

                local_80 = i_this->current.pos - player->current.pos;

                i_this->m3B4 = cM_atan2s(local_80.x, local_80.z);
                distXZ = std::sqrtf(local_80.x * local_80.x + local_80.z * local_80.z);
                
                i_this->m3B6 = -cM_atan2s(local_80.y, distXZ);
                
                i_this->speedF = 0.0f;
                return;
            }
        }
    }
    if (i_this->m68F) {
        if ((i_this->mCyl.ChkTgHit()) || (master->m386 == 8)) {
            mEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_826B, &i_this->current.pos, NULL);
            if (mEmitter != NULL) {
                mEmitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            }
            fopAcM_delete(i_this);
        }
    }
    else {
        if ((i_this->mCyl.ChkTgHit()) || (i_this->m68C)) {
            i_this->m3AE = 6;
            if (i_this->mCyl.ChkTgHit()) {
                if(((i_this->m386 == 8) || (i_this->m386 == 7)) || (i_this->m386 == 10)) {
                    atInfo.mpObj = i_this->mCyl.GetTgHitObj();
                    pPos = i_this->mCyl.GetTgHitPosP();
                    atInfo.pParticlePos = pPos;
                    atInfo.mpActor = at_power_check(&atInfo);
                    if((atInfo.mpObj != NULL) && (atInfo.mpObj->ChkAtType(AT_TYPE_SWORD)) && (dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_1_e ||
                                                                                              dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_3_e ||
                                                                                              dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_2_e)) {
                        atInfo.mpActor = cc_at_check(i_this, &atInfo);
                        if (atInfo.mbDead) {
                            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->eyePos, NULL);
                            
                            local_44.x = 2.0f;
                            local_44.y = 2.0f;
                            local_44.z = 2.0f;
                        }
                        else {
                            local_44.x = 1.0f;
                            local_44.y = 1.0f;
                            local_44.z = 1.0f;
                        }
                        if (i_this->health <= 0) {
                            fopAcM_monsSeStart(i_this, JA_SE_CV_PG_DAMAGE_L, 0);
                        }
                        else {
                            fopAcM_monsSeStart(i_this, JA_SE_CV_PG_DAMAGE_S, 0);
                        }

                        local_a0.z = 0.0f;
                        local_a0.x = 0.0f;
                        local_a0.y = fopAcM_searchPlayerAngleY(i_this);

                        dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, pPos, &local_a0, &local_44);

                        if ((i_this->m386 == 7) || (i_this->m386 == 10)) {
                            i_this->m386 = 8;
                            i_this->m388 = 0;
                        }
                        else if (i_this->m2BC == 0) {
                            if (i_this->health <= 0) {
                                i_this->m386 = 21;
                                i_this->m388 = 0;
                                i_this->m3AE = 1000;
                                mDoAud_subBgmStop();
                            }
                            else {
                                i_this->m690 -= atInfo.mDamage;
                                if (i_this->m690 <= 0) {
                                    i_this->m690 = 10;
                                    i_this->m386 = 2;
                                    i_this->m388 = 0;
                                }
                                else {
                                    i_this->m388 = 10;
                                }
                            }
                        }
                        else if (i_this->m2BC == 1) {
                            i_this->m386 = 3;
                            i_this->m388 = 0;
                            i_this->health = 0;
                            mDoAud_subBgmStop();
                        }
                    }
                }
            }
            else {
                fopAcM_monsSeStart(i_this, JA_SE_CV_PG_HIT_EBALL, 0);
                dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->eyePos, NULL);

                local_44.z = 2.0f;
                local_44.y = 2.0f;
                local_44.x = 2.0f;

                local_a0.z = 0.0f;
                local_a0.x = 0.0f;
                local_a0.y = fopAcM_searchPlayerAngleY(i_this);

                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->eyePos, &local_a0, &local_44);
                dKy_SordFlush_set(i_this->eyePos, 1);

                i_this->m386 = 8;
                i_this->m388 = 0;
                i_this->m3B0 = REG8_F(11) + 80.0f;
                i_this->m3B8 = REG8_S(2) + 7;

                local_98 = i_this->current.pos - player->current.pos;
                i_this->m3B4 = cM_atan2s(local_98.x, local_98.z);
                distXZ = std::sqrtf(local_98.x * local_98.x + local_98.z * local_98.z);
                i_this->m3B6 = -cM_atan2s(local_98.y, distXZ);
                i_this->speedF = 0.0f;
            }
        }
    }
}

/* 00006288-00006560       .text move__FP12fganon_class */
s32 move(fganon_class* i_this) {    
    int res = 0;
    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e) && i_this->m386) {
        if (i_this->m386 == 10) {
            dCam_getBody()->SetTypeForce("P_Ganon3", NULL);
        }
        else if (i_this->m2BC != 1) {
            dCam_getBody()->SetTypeForce("P_Ganon1", NULL);
        }
        else {
            dCam_getBody()->SetTypeForce("P_Ganon2", NULL);
        }
    }
    if ((i_this->m2BC == 0) && (i_this->m386 < 20)) {
        fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
        if ((i_this->m386 == 0) && (player->current.pos.y < 710.0f)) {
            return 0;
        }
        if ((i_this->m386 != 2) && (player->current.pos.y < 710.0f)) {
            i_this->m386 = 2;
            i_this->m388 = 0;
        }
    }
    switch(i_this->m386) {
    case 0:
        standby(i_this);
        break;
    case 1:
        deru(i_this);
        break;
    case 2:
        kieru(i_this);
        break;
    case 3:
        fail(i_this);
        res = 1;
        break;
    case 5:
        fly(i_this);
        res = 1;
        break;
    case 6:
        shot(i_this);
        res = 1;
        break;
    case 7:
        spinattack(i_this);
        res = 1;
        break;
    case 9:
        fly2(i_this);
        res = 1;
        break;
    case 11:
        shot2(i_this);
        res = 1;
        break;
    case 10:
        spinattack2(i_this);
        break;
    case 8:
        down(i_this);
        res = 1;
        break;
    case 20:
        start(i_this);
        break;
    case 21:
        end(i_this);
        break;
    case 22:
        last_end(i_this);
        break;    
    default:
        break;
    }
    damage_check(i_this);
    i_this->m68C = 0;
    cXyz* ccMove = i_this->mStts.GetCCMoveP();
    if (ccMove != NULL) {
        i_this->current.pos.x += ccMove->x;
        i_this->current.pos.y += ccMove->y;
        i_this->current.pos.z += ccMove->z;
    }
    if (i_this->m3B0 > 0.01f) {
        cXyz offset(0.0f, 0.0f, i_this->m3B0);
        cMtx_YrotS(*calc_mtx, i_this->m3B4);
        cMtx_XrotM(*calc_mtx, i_this->m3B6);
        cXyz transformedPos;
        MtxPosition(&offset, &transformedPos);
        i_this->current.pos += transformedPos;
        cLib_addCalc0(&i_this->m3B0, 1.0f, 7.0f);
    }
    return res;
}

/* 00006560-00007434       .text demo_camera__FP12fganon_class */
void demo_camera(fganon_class* i_this) {
    camera_class* camera;
    camera_class* camera2;
    fopAc_ac_c* a_this;
    daPy_py_c* player;
    cXyz offset;
    cXyz transformedPos;
    float yPos;
    float zPos;
    float yPos2;
    float zPos2;
    s8 bVar3;
    
    a_this = (fopAc_ac_c*)i_this;

    player = (daPy_py_c*)daPy_getPlayerActorClass();
    camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    bVar3 = TRUE;
    switch(i_this->mB54) {
        case 1: {
            if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(a_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCmd_INDEMO_e);
                bVar3 = FALSE;
                break;
            }
            i_this->mB54++;
            
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);

            i_this->mB56 = 0;
            i_this->mB84 = 60.0f;
            i_this->mB80 = 0.0f;

            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_UNK18_e);
        }
        case 2: {
            transformedPos.x = -300306.0f;
            transformedPos.y = 715.0f; 
            transformedPos.z = -303407.0f;

            player->setPlayerPosAndAngle(&transformedPos, -0x7BCD);
            
            i_this->mB68.x = -300319.0f;
            i_this->mB68.y = 812.0f;
            i_this->mB68.z = -303342.0f;

            i_this->mB5C.x = -300440.0f;
            i_this->mB5C.y = 787.0f;
            i_this->mB5C.z = -303137.0f;
            
            if (i_this->mB56 == 2) {
                mDoAud_seStart(JA_SE_CV_PG_LAUGH_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            
            if (i_this->mB56 == 30) {
                player->changeDemoMode(daPy_demo_c::DEMO_UNK35_e);
            }
            
            if (i_this->mB56 == 45) {
                deru_brk2(i_this);
            }
            
            if (i_this->mB56 != 47) {
                break;
            }
            
            i_this->mB54 = 3;
            i_this->mB56 = 0;
            
            zPos = REG8_F(2) + -303109.0f;
            yPos = REG8_F(1) + 745.0f;
            
            i_this->current.pos.x = REG8_F(0) + -300294.0f;
            i_this->current.pos.y = yPos;
            i_this->current.pos.z = zPos;
            
            zPos2 = REG8_F(5) + -303635.0f;
            yPos2 = REG8_F(4) + 770.0f;
            
            i_this->mB5C.x = REG8_F(3) + -300169.0f;
            i_this->mB5C.y = yPos2;
            i_this->mB5C.z = zPos2;

            i_this->mB68 = i_this->current.pos;
            i_this->mB68.y += REG0_F(0) + 160.0f;
        }
        case 3: {
            if (i_this->mB56 > 60) {
                cLib_addCalc2(&i_this->mB5C.x, -300269.0f, 0.1f, i_this->mB80 * 100.0f);
                cLib_addCalc2(&i_this->mB5C.y, 870.0f, 0.1f, i_this->mB80 * 100.0f);
                cLib_addCalc2(&i_this->mB5C.z, -303335.0, 0.1f, i_this->mB80 * 300.0f);
                
                i_this->mB68.x = i_this->current.pos.x;
                i_this->mB68.z = i_this->current.pos.z;

                cLib_addCalc2(&i_this->mB68.y, ((i_this->current.pos.y + 230.0f) - 70.0f) + 55.0f, 0.1f, i_this->mB80 * 55.0f);
                cLib_addCalc2(&i_this->mB80, 0.1f, 1.0f, REG8_F(7) + 0.01f);
            }
            if (i_this->mB56 == 110) {
                i_this->m388 = 2;
            }
            if (i_this->mB56 == 180) {
                i_this->m388 = 4;
            }
            if (i_this->mB56 == 280) {
                i_this->m386 = 6;
                i_this->m388 = 1;
                i_this->m3A4[0] = 29;
                i_this->mB54 = 150;
                if (i_this->m2BF != 0xFF) {
                    dComIfGs_onSwitch(i_this->m2BF, fopAcM_GetRoomNo(a_this));
                }
            }
            break;
        }
        case 50: {
            if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(a_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCmd_INDEMO_e);
                bVar3 = FALSE;
                break;
            }
            i_this->mB54++;

            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);

            i_this->mB56 = 0;
            i_this->mB84 = 55.0f;
            i_this->mB80 = 0.0f;

            player->changeOriginalDemo();

            i_this->shape_angle.y = 0;
        }
        case 51: {
            i_this->current.pos.x = -300202.0f;
            i_this->current.pos.y = 715.0f;
            i_this->current.pos.z = -301859.0f;

            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            
            offset.x = REG0_F(0) - 150.0f;
            offset.y = REG0_F(1) + 20.0f;
            offset.z = REG0_F(2) + 500.0f;
            
            MtxPosition(&offset, &transformedPos);

            i_this->mB5C = i_this->current.pos + transformedPos;

            offset.x = REG0_F(3);
            offset.y = 0.0f;
            offset.z = REG0_F(5) + 280.0f;
            
            MtxPosition(&offset, &transformedPos);
            transformedPos += i_this->current.pos;
            transformedPos.y = 715.0f;
            
            player->setPlayerPosAndAngle(&transformedPos, -0x8000);

            i_this->mB68 = i_this->eyePos;
            i_this->mB68.y += REG0_F(6) - 40.0f;
            if (i_this->mB56 > 0x96) {
                i_this->mB54++;
                i_this->mB56 = 0;
                
                i_this->mB68.x = -299898.0f;
                i_this->mB68.y = 1188.0f;
                i_this->mB68.z = -301158.0f;

                i_this->mB5C.x = -299703.0f;
                i_this->mB5C.y = 921.0f;
                i_this->mB5C.z = -300851.0f;

                player->changeDemoMode(daPy_demo_c::DEMO_UNK1A_e);
            }
            break;
        }
        case 52: {
            yPos = player->current.pos.y;
            transformedPos.x = -300202.0f;
            transformedPos.y = yPos;
            transformedPos.z = -301859.0f;
            
            player->setPlayerPosAndAngle(&transformedPos, 0.0f);
            
            if (i_this->mB56 == 10) {
                i_this->m388++;
            }

            i_this->current.pos.x = (i_this->mB68.x - 50.0f) + REG0_F(4);
            i_this->current.pos.y = i_this->mB68.y + REG0_F(5);
            i_this->current.pos.z = (i_this->mB68.z - 100.0f) + REG0_F(6);

            i_this->shape_angle.y = REG0_S(0) + 2000;
            if (i_this->mB56 == 40) {
                i_this->mB54++;
                i_this->mB56 = 0;
            }
            break;
        }
        case 53: {
            i_this->mB68.x = -300098.0f;
            i_this->mB68.y = 580.0f;
            i_this->mB68.z = -301997.0f;
            
            i_this->mB5C.x = -300274.0f;
            i_this->mB5C.y = 929.0f;
            i_this->mB5C.z = -301770.0f;

            if (i_this->mB56 != 30) { 
                break;
            }
            i_this->mB54++;
            i_this->mB56 = 0;

            i_this->mB5C.x = -299703.0f;
            i_this->mB5C.y = 921.0f;
            i_this->mB5C.z = -300851.f;

            i_this->speed.y = 0.0f;

            i_this->mB68 = i_this->eyePos;
            i_this->mB68.y -= REG0_F(11) + 30.0f;
            i_this->m388++;
        }
        case 54: {
            cLib_addCalc2(&i_this->mB68.y, (i_this->eyePos.y - 30.0f) + REG0_F(11), 0.1f, 20.0f);
            if (i_this->mB56 == 100) {
                i_this->mB54 = 55;
                player->changeDemoMode(daPy_demo_c::DEMO_UNK0F_e);
                i_this->mB56 = 0;
            }
            else {
                break;
            }
        }
        case 55: {
            if (i_this->mB56 == 20) {
                mDoAud_seStart(JA_SE_CV_PG_LAUGH_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(a_this)));
            }

            i_this->mB68 = player->current.pos;
            i_this->mB68.y += REG8_F(3);

            offset.x = 0.0f;
            offset.y = REG8_F(4) + 1500.0f;
            offset.z = REG8_F(5) + 2000.0f;

            cMtx_YrotS(*calc_mtx, player->shape_angle.y + i_this->mB76 + REG8_S(5));
            MtxPosition(&offset, &transformedPos);

            i_this->mB76 += REG8_S(6) + 30;
            i_this->mB5C = player->current.pos + transformedPos;

            if (i_this->mB56 != 130) {
                break;
            }

            if (i_this->mSwitchNo != 0xFF) {
                dComIfGs_onSwitch(i_this->mSwitchNo, fopAcM_GetRoomNo(a_this));
            }

            if (i_this->m2BF != 0xFF) {
                dComIfGs_offSwitch(i_this->m2BF, fopAcM_GetRoomNo(a_this));
            }

            i_this->mB54 = 150;
            fopAcM_delete(a_this);
            goto case_150;
        }
        case 100: {
            if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(a_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCmd_INDEMO_e);
                bVar3 = FALSE;
                break;
            }
            i_this->mB54++;

            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);

            i_this->mB56 = 0;
            i_this->mB84 = 60.0f;
            i_this->mB80 = 0.0f;

            player->changeOriginalDemo();

            camera2 = dComIfGp_getCamera(0);

            i_this->mB5C = camera2->mLookat.mEye;
            i_this->mB68 = camera2->mLookat.mCenter;

            i_this->shape_angle.y = fopAcM_searchPlayerAngleY(a_this);
        }
        case 101: {
            cLib_addCalc2(&i_this->mB68.x, i_this->current.pos.x, 0.1f, 200.0f);
            cLib_addCalc2(&i_this->mB68.y, i_this->eyePos.y - 50.0f, 0.1f, 200.0f);
            cLib_addCalc2(&i_this->mB68.z, i_this->current.pos.z, 0.1f, 200.0f);
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            
            offset.x = 0.0f;
            offset.y = REG8_F(0) + -100.0f;
            offset.z = REG8_F(1) + 400.0f;
            
            MtxPosition(&offset, &transformedPos);

            transformedPos += i_this->current.pos;

            {
                dBgS_LinChk linChk;
                linChk.Set(&i_this->mB68, &transformedPos, a_this);
                
                if (dComIfG_Bgsp()->LineCross(&linChk)) {
                    transformedPos = linChk.GetCross();
                    transformedPos.y += REG8_F(18) + 20.0f;
    
                }
            }
            
            cLib_addCalc2(&i_this->mB5C.x, transformedPos.x, 0.1f, i_this->mB80 * 50.0f);
            cLib_addCalc2(&i_this->mB5C.y, transformedPos.y, 0.1f, i_this->mB80 * 50.0f);
            cLib_addCalc2(&i_this->mB5C.z, transformedPos.z, 0.1f, i_this->mB80 * 50.0f);
            cLib_addCalc2(&i_this->mB80, 1.0f, 1.0f, REG8_F(7) + 0.1f);
            break;
        }
        case 0:
        default: {
            break;
        }
        case 103: {
            if (i_this->mB56 > REG0_S(2) + 8) {
                cLib_addCalc2(&i_this->mB68.y, player->current.pos.y + REG0_F(9), 0.8f, REG0_F(10) + 30.0f);
            }

            if (i_this->mB56 <= REG0_S(3) + 80) {
                break;
            }

            i_this->mB54 = 150;

            fopAcM_delete(a_this);
            
            if (REG0_S(3) == 0) {
                dComIfGs_onSwitch(i_this->mSwitchNo, fopAcM_GetRoomNo(a_this));
            }
        }
        case 150: {
        case_150:
            camera->mCamera.SetTrimSize(0);
            camera->mCamera.Start();
            dMeter_mtrShow();
            dComIfGp_event_reset();
            i_this->mB54 = 0;
        }
    }
    if (i_this->mB54 && bVar3) {
        camera->mCamera.Set(i_this->mB68, i_this->mB5C, i_this->mB84, 0);
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->mB56);
        i_this->mB56++;
    }
}

/* 00007434-0000778C       .text ball_bg_check__FP12fganon_class */
BOOL ball_bg_check(fganon_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    dBgS_LinChk linChk;
    cXyz posVec = i_this->m3E0 + (i_this->m3E0 - i_this->m3EC) * 1.05f;
    linChk.Set(&i_this->m3E0, &posVec, a_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->m3E0 = linChk.GetCross();
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/* 0000778C-00008614       .text energy_ball_move__FP12fganon_class */
void energy_ball_move(fganon_class* i_this) {
    daPy_py_c* player;
    fopAc_ac_c* a_this;
    
    CcAtInfo atInfo;
    
    cXyz local_50;
    cXyz local_5c;
    cXyz local_68;

    s8 bVar5;
    s8 bVar2;
    u8 bVar3;

    player = (daPy_py_c*)dComIfGp_getPlayer(0);
    a_this = (fopAc_ac_c*)i_this;

    local_50.x = 0.0f;
    local_50.y = 0.0f;
    local_50.z = 0.0f;
    bVar5 = FALSE;
    
    if (i_this->m408 == 0) {
        return;
    }

    atInfo.pParticlePos = NULL;

    if (i_this->m408 == 35) {    
        if (i_this->m688 != 0) {
            mDoAud_changeSubBgmStatus(8);
            i_this->m688 = 0;
        }
        
        for(int i = 0; i < 2; i++) {
            if (i_this->mEmitters2[i] != NULL) {
                i_this->mEmitters2[i]->becomeInvalidEmitter();
                i_this->mEmitters2[i] = NULL;
            }
        }

        i_this->m408 = 0;
        return;
    }

    if (i_this->m408 == 1) {
        for(int i = 0; i < 2; i++) {
            if (i_this->mEmitters2[i] != NULL) {
                i_this->mEmitters2[i]->becomeInvalidEmitter();
                i_this->mEmitters2[i] = NULL;
            }
        }
        i_this->mEmitters2[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_81CE, &a_this->current.pos, NULL);
        i_this->mEmitters2[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_81CF, &a_this->current.pos, NULL);
        i_this->m408 = 2;
    }
    if (i_this->m408 == 2) {
        cMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(0xE), *calc_mtx);
        MtxTrans(REG12_F(0) + 30.0f, REG12_F(1) + 30.0f, REG12_F(2), TRUE);
        MtxPosition(&local_50, &i_this->m3E0);
         
        for(int i = 0; i < 2; i++) {
            if(i_this->mEmitters2[i] != NULL) {
                i_this->mEmitters2[i]->setGlobalRTMatrix(*calc_mtx);
            }
        }

        if (i_this->m409) {
            i_this->m409 = 0;
            i_this->m408 = 3;
            
            local_5c = player->eyePos - i_this->m3E0;
            local_5c.y -= REG0_F(18) + 50.0f;

            cMtx_YrotS(*calc_mtx, cM_atan2s(local_5c.x, local_5c.z));            
            cMtx_XrotM(*calc_mtx, -cM_atan2s(local_5c.y, std::sqrtf(local_5c.x * local_5c.x + local_5c.z * local_5c.z)));

            if (i_this->m2BC == 0) {
              local_50.z = l_HIO.m1C;
            }
            else {
              local_50.z = l_HIO.m20;
            }

            i_this->m404 = local_50.z;
            MtxPosition(&local_50, &i_this->m3F8);
            i_this->m40A = 5;
            i_this->mBallAtSph.ClrAtHit();
        }
    }
    if (i_this->m408 >= 3) {
        i_this->m3EC = i_this->m3E0;
        i_this->m3E0 += i_this->m3F8;
        mDoMtx_stack_c::transS(i_this->m3E0.x, i_this->m3E0.y, i_this->m3E0.z);
        for(int i = 0; i < 2; i++) {
            if (i_this->mEmitters2[i] != NULL) {
                i_this->mEmitters2[i]->setGlobalRTMatrix(mDoMtx_stack_c::get());
            }
        }
        bVar2 = FALSE;
        local_5c = a_this->eyePos - i_this->m3E0;
        local_5c.y -= 50.0f;
        if (local_5c.abs() < i_this->m404 + 200.0f + REG0_F(3)) {
            if (i_this->m686 != 0) {
                bVar5 = 1;
            }
            else {
                if (i_this->m408 == 5) {
                    if (i_this->m2BC != 2) {
                        i_this->m68C = 1;
                    }
                    else {
                        if (i_this->m40A != 0) {
                            return;
                        }
                        i_this->m386 = 2;
                        i_this->m388 = 0;
                        i_this->m40A = 50;
                        return;
                    }
                }
            }
        }
        
        bVar3 = FALSE;
        if(i_this->m408 == 4) {
            if (player->checkBottleSwing()) {
                local_5c = player->eyePos - i_this->m3E0;
                local_5c.y -= 30.0f;
                if (local_5c.abs() < REG0_F(2) + 100.0f) {
                    bVar3 = TRUE;
                }
            }
        }

        if (((i_this->mBallTgSph.ChkTgHit() || (bVar5 != 0)) || bVar3) && (i_this->m40A == 0)) {
            if (i_this->mBallTgSph.ChkTgHit()) {
                atInfo.mpObj = i_this->mBallTgSph.GetTgHitObj();
                at_power_check(&atInfo);
            }
            else {
                atInfo.mResultingAttackType = 0xFF;
                atInfo.mpObj = NULL;
            }
            if ((atInfo.mpObj && atInfo.mResultingAttackType == 1 && atInfo.mpObj->ChkAtType(AT_TYPE_SWORD) &&
                 (dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_1_e ||
                  dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_3_e ||
                  dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_2_e)) ||
                bVar3)
            {
                local_5c = a_this->eyePos - i_this->m3E0;
                local_5c.y -= REG0_F(17) + 30.0f;

                cMtx_YrotS(*calc_mtx, cM_atan2s(local_5c.x, local_5c.z));
                cMtx_XrotM(
                    *calc_mtx, -cM_atan2s(local_5c.y, std::sqrtf(local_5c.x * local_5c.x + local_5c.z * local_5c.z))
                );

                local_50.z = i_this->m404;

                MtxPosition(&local_50, &i_this->m3F8);

                i_this->m408 = 5;

                dScnPly_ply_c::setPauseTimer(2);

                bVar2 = TRUE;

                s32 lVar11 = i_this->m688 + 2;
                if (lVar11 > 7) {
                    lVar11 = 7;
                }
                mDoAud_changeSubBgmStatus(lVar11);
                i_this->m688++;
                dComIfGs_onEventBit(0x3f20);
            } else if (bVar5) {
                local_5c = player->eyePos - i_this->m3E0;
                local_5c.y -= REG0_F(18) + 50.0f;

                cMtx_YrotS(*calc_mtx, cM_atan2s(local_5c.x, local_5c.z));
                cMtx_XrotM(*calc_mtx, -cM_atan2s(local_5c.y, std::sqrtf(local_5c.x * local_5c.x + local_5c.z * local_5c.z)));

                local_50.z = i_this->m404;

                MtxPosition(&local_50, &i_this->m3F8);
                
                i_this->m408 = 4;
                bVar2 = TRUE;
            }
            if (bVar2) {
                if (i_this->m2BC == 0) {
                    i_this->m404 += l_HIO.m24;
                }
                else {
                    i_this->m404 += l_HIO.m28;
                }
                csXyz local_7c(0,0,0);
                local_7c.y = (short)cM_atan2s(i_this->m3F8.x, i_this->m3F8.z);
                dComIfGp_particle_set(dPa_name::ID_SCENE_81F0, &i_this->m3E0, &local_7c);
#if VERSION == VERSION_USA
                mDoAud_seStart(JA_SE_LK_PG_BOMB_STRIKE, &i_this->m3E0, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(a_this)));
#endif
                i_this->m3E0 += i_this->m3F8;
                i_this->m40A = 5;
            }
        }
    
        local_68 = i_this->m3E0;

        if (i_this->m40A != 0) {
            i_this->m40A--;
            local_68.x = -20000.0f;
            local_68.y = -20000.0f;
            local_68.z = 20000.0f;
        }

        if (i_this->m408 == 3) {
            i_this->mBallAtSph.StartCAt(local_68);
            i_this->m408 = 4;
        }

        else {
            i_this->mBallAtSph.MoveCAt(local_68);
        }

        i_this->mBallAtSph.SetR(REG0_F(6) + 25.0f);

        i_this->mBallTgSph.SetC(local_68);
        i_this->mBallTgSph.SetR(REG0_F(7) + 100.0f);

        dComIfG_Ccsp()->Set(&i_this->mBallTgSph);
        dComIfG_Ccsp()->Set(&i_this->mBallAtSph);

        if ((i_this->m68C || ball_bg_check(i_this)) || i_this->mBallAtSph.ChkAtHit()) {
            if (i_this->m688 != 0) {
                if (i_this->m68C != 0) {
                    mDoAud_changeSubBgmStatus(10);
                }
                else {
                    if (i_this->mBallAtSph.ChkAtHit()) {
                        mDoAud_changeSubBgmStatus(9);
                    }
                    else {
                        mDoAud_changeSubBgmStatus(8);
                    }
                }
                i_this->m688 = 0;
            }
            i_this->m408 = 0;

            if (i_this->mEmitters2[0] != NULL) {
                i_this->mEmitters2[0]->setGlobalAlpha(0);
            }

            if (i_this->mEmitters2[1] != NULL) {
                i_this->mEmitters2[1]->becomeInvalidEmitter();
                i_this->mEmitters2[1] = NULL;
            }

            csXyz local_7c(0,0,0);

            dComIfGp_particle_set(dPa_name::ID_SCENE_81EE, &i_this->m3E0, &local_7c, 0);
            dComIfGp_particle_set(dPa_name::ID_SCENE_81EF, &i_this->m3E0, &local_7c, 0);

            mDoAud_seStart(JA_SE_OBJ_PG_EBALL_EXP_S, &i_this->m3E0, 100, dComIfGp_getReverb(fopAcM_GetRoomNo(a_this)));

            if (i_this->mBallAtSph.ChkAtHit() != 0) {
                atInfo.mpActor = i_this->mBallAtSph.GetAtHitObj()->GetAc();
                if ((atInfo.mpActor && (fopAcM_GetName(atInfo.mpActor) == PROC_PLAYER)) && (i_this->m386 != 22)) {
                    i_this->m68B = 1;
                    i_this->m386 = 5;
                    i_this->m388 = 1;
                    i_this->m3A4[1] = (cM_rndF(30.0f)) + 70.f;
                }
            }
        }
    }
    local_5c = a_this->home.pos - i_this->m3E0;
        
    if (local_5c.abs() > 10000.0f) {
        i_this->m408 = 35;
    }
}

/* 00008614-000086B4       .text mahou_se_set__FPvPv */
/* Play PG's magic sound effect */
void* mahou_se_set(void* i_act, void* i_other) {  
    fganon_class* i_this = (fganon_class*)i_act;
    if ((fopAc_IsActor(i_this)) && (((base_process_class*)i_this)->mProcName == PROC_FGMAHOU)) {
        if (i_this->health == 0) {
            fopAcM_seStartCurrent(i_this, JA_SE_OBJ_PG_EBALL_FLY_L, 0);
        }
        return i_act;
    }
    return NULL;
}

static u32 jno[2] = {0x7, 0xD};
static u16 eno[2] = {dPa_name::ID_SCENE_81CD, dPa_name::ID_SCENE_81CC};

/* 000086B4-0000924C       .text daFganon_Execute__FP12fganon_class */
static BOOL daFganon_Execute(fganon_class* i_this) {
    cXyz local_70;
    cXyz local_7c;
    cXyz local_94;
    cXyz local_84;

    local_70.x = 0.0f;
    local_70.y = 0.0f;
    local_70.z = 0.0f;

    if (i_this->mB89 >= 2) {
        i_this->mB89--;
        if (i_this->mB89 == 1) {
            mDoAud_subBgmStart(JA_BGM_P_GANON_2);
        }
    }

    fpcM_Search(&mahou_se_set, i_this);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);

    if (((((i_this->m386 == 5) || (i_this->m386 == 9)) || (i_this->m386 == 7)) || (i_this->m386 == 10)) && ((i_this->m68B != 0 && (i_this->m68A == 0)))) {
        i_this->m68B = 0;
        anm_init(i_this, FGANON_BCK_WARAU1, 6.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m68A = 60;
        fopAcM_monsSeStart(i_this, JA_SE_CV_PG_LAUGH_3, 0);
    }

    i_this->m384++;
    for (int i = 0; i < 5; i++){
        if (i_this->m3A4[i] != 0)
            i_this->m3A4[i] -= 1;
    }

    if (i_this->m68A != 0)
        i_this->m68A--;
    if (i_this->m3AE != 0)
        i_this->m3AE--;
    if (i_this->m3B8 != 0)
        i_this->m3B8--;

    if (l_HIO.m05 == 0) {
        if (i_this->mbIsMaterialized != 0) {
            i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        }
        else {
            fopAcM_OffStatus(i_this, 0);
            i_this->attention_info.flags = 0;
        }
        if (move(i_this) != 0) {
            i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        }
        i_this->mpMorf->play(&i_this->eyePos, 0, 0);
        i_this->mpBrkAnm1->play();
        i_this->mpBrkAnm2->play();
    }
    
    local_94.x = i_this->m3BC * cM_ssin(i_this->m384 * (REG0_S(6) + 700));
    local_94.y = i_this->m3BC * cM_ssin(i_this->m384 * (REG0_S(6) + 750));
    local_94.z = i_this->m3BC * cM_scos(i_this->m384 * (REG0_S(6) + 720));
    
    cLib_addCalc0(&i_this->m3BC, 1.0f, 1.0f);

    J3DModel* mpModel = i_this->mpMorf->getModel();
    
    mpModel->setBaseScale(i_this->scale);
    
    mDoMtx_stack_c::transS(i_this->current.pos.x + local_94.x, i_this->current.pos.y + local_94.y, i_this->current.pos.z + local_94.z);
    
    float scale = i_this->m3B8 * (REG0_F(14) + 500.0f);
    float sin = cM_ssin(i_this->m384 * 0x2100);
    float cos = cM_scos(i_this->m384 * 0x2300);
    
    mDoMtx_stack_c::YrotM(i_this->shape_angle.y + (short)(scale * sin));
    mDoMtx_stack_c::XrotM(i_this->shape_angle.x + (short)(scale * cos));
    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->mpMorf->calc();

    cMtx_copy(mpModel->getAnmMtx(27), *calc_mtx);
    
    MtxPosition(&local_70, &i_this->eyePos);
    
    i_this->attention_info.position = i_this->eyePos;
    i_this->attention_info.position.y += 30.0f;
    
    if (i_this->m2D0 == 0) {
        cMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(24), *calc_mtx);
        
        cMtx_YrotM(*calc_mtx, REG8_S(1) - 400);
        cMtx_XrotM(*calc_mtx, REG8_S(2) - 400);
        cMtx_ZrotM(*calc_mtx, (REG8_S(3) + 1) + 0x7FFF);
        
        MtxTrans(REG8_F(9), REG8_F(10), REG8_F(11) + 85.0f, TRUE);
        MtxTrans(REG0_F(12), REG0_F(13), REG0_F(14) + 90.0f, TRUE);
        
        cMtx_ZrotM(*calc_mtx, i_this->m6A0);
        cMtx_XrotM(*calc_mtx, i_this->m694);
        cMtx_ZrotM(*calc_mtx, -i_this->m6A0);

        int iVar4 = 0;
        if (i_this->m6A6 != 0) {
            sin = cM_ssin(i_this->m6A6 * (REG0_S(2) + 0x1800));
            iVar4 = (REG0_F(14) + 400.0f) * (i_this->m6A6 * sin);
            i_this->m6A6--;
        }
        cMtx_ZrotM(*calc_mtx, i_this->m6A2 + iVar4);
        MtxTrans(-REG0_F(12), -REG0_F(13), -(REG0_F(14) + 90.0f), TRUE);
        i_this->mpKenModel->setBaseTRMtx(*calc_mtx);
    }

    demo_camera(i_this);
    energy_ball_move(i_this);
    
    for (int i = 0; i < 2; i++) {
        if ((i_this->mbIsMaterialized != 0) && (i_this->m386 != 22)) {
            if (i_this->mEmitters1[i] != NULL) {
                i_this->mEmitters1[i]->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(jno[i]));
            }
            else {
                i_this->mEmitters1[i] = dComIfGp_particle_set(eno[i], &i_this->current.pos, NULL);
            }
        }
        else {
            if (i_this->mEmitters1[i] != NULL) {
                i_this->mEmitters1[i]->becomeInvalidEmitter();
                i_this->mEmitters1[i] = NULL;
            }
        }
    }
    if (i_this->mbIsMaterialized != 0) {
        mDoMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(10), *calc_mtx);
        local_70.x = 0.0f;
        local_70.y = 0.0f;
        local_70.z = 0.0f;
        MtxPosition(&local_70, &local_7c);
        local_7c.y -= REG0_F(0) + 150.0f;
        if (i_this->m68F == 0) {
            i_this->mCyl.OnCoSetBit();
        }
        else {
            i_this->mCyl.OffCoSetBit();
        }
    }
    else {
        i_this->mCyl.OffCoSetBit();
        float z = i_this->m68F * -1000.0f;
        local_7c.x = 20000.0f;
        local_7c.y = 20000.0f;
        local_7c.z = z;
    }

    i_this->mCyl.SetC(local_7c);
    i_this->mCyl.SetH(REG8_F(3) + 250.0f);
    i_this->mCyl.SetR(REG8_F(4) + 70.0f);

    dComIfG_Ccsp()->Set(&i_this->mCyl);
    
    local_84.x = -10000.0f;
    local_84.y = -10000.0f;
    local_84.z = -10000.0f;

    if (i_this->m685 != 0) {
        i_this->mWeponSph.SetR(REG0_F(13) + 60.0f);
        mDoMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(24), *calc_mtx);
        local_70.x = 0.0f;
        local_70.y = 0.0f;
        local_70.z = 100.0f;
        MtxPosition(&local_70, &local_84);
        i_this->m685 = 0;
        if (i_this->m684 == 0) {
            i_this->mWeponSph.StartCAt(local_84);
            i_this->m684 = 1;
        }
        else {
            i_this->mWeponSph.MoveCAt(local_84);
        }
    } else {
        i_this->m684 = 0;
        i_this->mWeponSph.SetC(local_84);
    }
    dComIfG_Ccsp()->Set(&i_this->mWeponSph);
    i_this->m686 = 0;
    mant_class* cape = (mant_class*)fopAcM_SearchByID(i_this->mCapeID);
    if (cape != NULL) {
        mDoMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(REG0_S(5) + 20), *calc_mtx);
        local_70.x = REG0_F(0) + 35.0f;
        local_70.y = REG0_F(1);
        local_70.z = REG0_F(2) + -30.0f;
        MtxPosition(&local_70, &cape->m1BE0);
        mDoMtx_copy(i_this->mpMorf->getModel()->getAnmMtx(REG0_S(6) + 11), *calc_mtx);
        local_70.x = REG0_F(3) + 35.0f;
        local_70.y = REG0_F(4);
        local_70.z = REG0_F(5) + 30.0f;
        MtxPosition(&local_70, &cape->m1BEC);
        cape->current.pos = i_this->eyePos;
        cape->current.angle = i_this->current.angle;
        float fVar1;
        if ((i_this->mbIsMaterialized != 0) && (i_this->m68E == 0)) {
            fVar1 = 1.0f;
        }
        else {
            fVar1 = 0.0f;
        }
        cLib_addCalc2(&cape->scale.y, fVar1 , 1.0f, REG0_F(8) + 0.1f);
    }
    if (i_this->m6AC != 0) {
        i_this->m6AC--;
        i_this->setBtAttackData(0.0f, 10.0f, 10000.0f, 1);
        i_this->setBtMaxDis(l_HIO.m44);
        i_this->setBtNowFrame(5.0f);
    }
    else {
        i_this->setBtNowFrame(100.0f);
    }
    return TRUE;
}

/* 0000924C-00009254       .text daFganon_IsDelete__FP12fganon_class */
static BOOL daFganon_IsDelete(fganon_class*) {
    return TRUE;
}

/* 00009254-000093B4       .text daFganon_Delete__FP12fganon_class */
static BOOL daFganon_Delete(fganon_class* i_this) {    
    if ((i_this->mB8A) && (dComIfG_resDelete(&i_this->mPhs2, "Pgsw"), i_this->mB8A != 1))
        dComIfG_resDelete(&i_this->mPhs1, "Fganon");
    
    if (i_this->mB88 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }

    mDoAud_seDeleteObject(&i_this->m3E0);

    if (i_this->mCapeID != 0xFFFF) // bug?
        fopAcM_delete(fopAcM_SearchByID(i_this->mCapeID));

    if (i_this->mB89)
        mDoAud_subBgmStop();

    for (int i = 0; i < 4; i++) {
        if (i_this->mEmitters2[i])
            i_this->mEmitters2[i]->becomeInvalidEmitter();
    }
    
    for (int i = 0; i < 2; i++) {
        if (i_this->mEmitters1[i])
            i_this->mEmitters1[i]->becomeInvalidEmitter();
    }
    return TRUE;
}

/* 000093B4-000097FC       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_act) {
    J3DModelData* pModelData;
    J3DAnmTevRegKey* ptrkAnm;
    J3DAnmTextureSRTKey* ptsrtkAnm;
    int iVar4;
    
    fganon_class* i_this = (fganon_class*)i_act;
    
    mDoExt_McaMorf* morf = new mDoExt_McaMorf((J3DModelData *)dComIfG_getObjectRes("Fganon", FGANON_BDL_BPG), NULL, NULL, 
                                              (J3DAnmTransformKey *)dComIfG_getObjectRes("Fganon", FGANON_BCK_WAIT1), 
                                              J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    
    i_this->mpMorf = morf;
    if ((i_this->mpMorf == NULL || i_this->mpMorf->getModel() == NULL))
        return FALSE;
    
    i_this->mpBrkAnm1 = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm1 == NULL)
        return FALSE;

    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_MAIN1);
    iVar4 = i_this->mpBrkAnm1->init(i_this->mpMorf->mpModel->getModelData(), ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0);
    if (iVar4 == 0)
        return FALSE;

    pModelData = (J3DModelData *)dComIfG_getObjectRes("Pgsw", PGSW_BDL_BPG_KEN1);
    i_this->mpKenModel = mDoExt_J3DModel__create(pModelData, 0, 0x11020203);
    if (i_this->mpKenModel == NULL)
        return FALSE;

    pModelData = i_this->mpKenModel->getModelData();
    i_this->mpBrkAnm2 = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm2 == NULL)  
        return FALSE;

    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_DERU_KEN1);
    iVar4 = i_this->mpBrkAnm2->init(pModelData, ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0);
    if (iVar4 == 0)
        return FALSE;
    
    pModelData = (J3DModelData *)dComIfG_getObjectRes("Fganon", FGANON_BDL_YDKBL00);
    i_this->mpEnergySphereModel = mDoExt_J3DModel__create(pModelData, 0, 0x11020203);
    if (i_this->mpEnergySphereModel == NULL)
        return FALSE;
    
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL)
        return FALSE;

    ptsrtkAnm = (J3DAnmTextureSRTKey *)dComIfG_getObjectRes("Fganon", FGANON_BTK_YDKBL00);
    iVar4 = i_this->mpBtkAnm->init(pModelData, ptsrtkAnm, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, FALSE, 0);
    if (iVar4 == 0)
        return FALSE;

    i_this->mpBrkAnm3 = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm3 == NULL)
        return FALSE;

    ptrkAnm = (J3DAnmTevRegKey *)dComIfG_getObjectRes("Fganon", FGANON_BRK_YDKBL00);
    iVar4 = i_this->mpBrkAnm3->init(pModelData, ptrkAnm, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0);
    if (iVar4 == 0)
        return FALSE;

    return TRUE;
}

static dCcD_SrcCyl cc_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_UNK8 | AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ dCcG_TgHitMark_Nrm_e,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, -150.0f, 0.0f,
        /* Radius */ 100.0f,
        /* Height */ 100.0f,
    },
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

static dCcD_SrcSph ball_tg_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 60.0f,
    },
};

static dCcD_SrcSph ball_at_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0x2,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
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
        /* Radius */ 30.0f,
    },
};

/* 00009844-00009C70       .text daFganon_Create__FP10fopAc_ac_c */
static cPhs_State daFganon_Create(fopAc_ac_c* i_act) {
    fganon_class* i_this = (fganon_class*)i_act;
    fopAcM_SetupActor(i_act, fganon_class);
    s32 res;
    s32 res2;
    
    if (fopAcM_IsFirstCreating(i_this)) {
        i_this->mSwitchNo = fopAcM_GetParam(i_this) >> 0x10;
    }
    
    if ((i_this->mSwitchNo != 0xFF) && (dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo()) != 0)) {
        if (((fopAcM_GetParam(i_this) & 0xF) == 2) && !(dComIfGs_isEventBit(0x3A08))) { // Probably a flag to do with beating FF1 so PG spawns?
            fopAcM_create(PROC_BOKO, 5, &i_this->current.pos, i_this->current.roomNo);
        }
        return cPhs_ERROR_e;
    }

    i_this->mB8A = 1;
    res = dComIfG_resLoad(&i_this->mPhs2, "Pgsw");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }

    i_this->mB8A = 2;
    res2 = dComIfG_resLoad(&i_this->mPhs1, "Fganon");
    if (res2 == cPhs_COMPLEATE_e) {
        i_this->m2BC  = fopAcM_GetParam(i_this) & 0xF;
        i_this->m2BD  = fopAcM_GetParam(i_this) >> 8;
        i_this->mSwitchNo = fopAcM_GetParam(i_this) >> 0x10;
        i_this->m2BF  = fopAcM_GetParam(i_this) >> 0x18;
        if (i_this->m2BC == 3) {
            i_this->m68F = (fopAcM_GetParam(i_this) >> 4) & 0xF;
        }
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }

        i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;

        if (hio_set == 0) {
            i_this->mB88 = 1;
            hio_set = 1;
            if (i_this->m2BC == 2) {
                l_HIO.mNo = mDoHIO_createChild("ファントムガノン③", (JORReflexible *)&l_HIO);
            }
            else if (i_this->m2BC == 1) {
                l_HIO.mNo = mDoHIO_createChild("ファントムガノン②", (JORReflexible *)&l_HIO);
            }
            else {
                l_HIO.mNo = mDoHIO_createChild("ファントムガノン①", (JORReflexible *)&l_HIO);
            }
        }

        i_this->mAcch.Set(fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_this));
        i_this->mAcch.OffSameActorChk();
        i_this->mAcchCir.SetWall(200.0f, 200.0f);
        
        i_this->mStts.Init(0xFA, 0xFF, i_act);
        
        i_this->mCyl.Set(cc_cyl_src);
        i_this->mCyl.SetStts(&i_this->mStts);
        i_this->mCyl.OnTgNoHitMark();
        
        i_this->mBallTgSph.Set(ball_tg_sph_src); 
        i_this->mBallTgSph.SetStts(&i_this->mStts);
        i_this->mBallTgSph.OnTgNoHitMark();
        
        i_this->mBallAtSph.Set(ball_at_sph_src);
        i_this->mBallAtSph.SetStts(&i_this->mStts);
        
        i_this->mWeponSph.Set(wepon_sph_src);
        i_this->mWeponSph.SetStts(&i_this->mStts);

        if (i_this->m68F == 0) {
            master = i_this;
            if (i_this->m2BC == 0) {
                i_this->m386 = 20;
                i_this->m388 = 0;
                kieru_brk(i_this, 0);
                i_this->max_health = 30;
                i_this->health = 30;
                i_this->m690 = 10;
            }
            else {
                i_this->max_health = 100;
                i_this->health = 100;
                i_this->m386 = 0;
                i_this->m388= -1;
            }
            i_this->current.pos.y += 10000.0f;
        }
        else {
            i_this->m386 = 10;
            i_this->m388 = 0;
            deru_brk(i_this);
        }
        i_this->initBt(REG8_F(8) + 300.0f, 300.0f);
        i_this->mCapeID = fopAcM_create(PROC_MANT, 1, &i_this->current.pos, i_this->current.roomNo);
        daFganon_Execute(i_this);
    }
    return res2;
    
}

static actor_method_class l_daFganon_Method = {
    (process_method_func)daFganon_Create,
    (process_method_func)daFganon_Delete,
    (process_method_func)daFganon_Execute,
    (process_method_func)daFganon_IsDelete,
    (process_method_func)daFganon_Draw,
};

actor_process_profile_definition g_profile_FGANON = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_FGANON,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(fganon_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00E6,
    /* Actor SubMtd */ &l_daFganon_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
