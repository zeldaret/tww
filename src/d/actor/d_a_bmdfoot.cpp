/**
 * d_a_bmdfoot.cpp
 * Boss - Kalle Demos (floor tentacles) / 森ボス足 (Forest boss feet)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bmdfoot.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_bmdfoot.h"
#include "d/actor/d_a_bmd.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

class daBmdfoot_HIO_c : public JORReflexible {
public:
    daBmdfoot_HIO_c();
    virtual ~daBmdfoot_HIO_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 m05;
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
};

/* 000000EC-00000114       .text __ct__15daBmdfoot_HIO_cFv */
daBmdfoot_HIO_c::daBmdfoot_HIO_c() {
    mNo = 0xFF;
    m08 = 1000;
    m06 = 3500;
}

static bmd_class* boss;
static bool hio_set;
static daBmdfoot_HIO_c l_HIO;

/* 00000114-000001D8       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bmdfoot_class* i_this = (bmdfoot_class*)model->getUserArea();
        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            MtxRotX(i_this->m2CC[jntNo].x, 1);
            MtxRotZ(i_this->m2CC[jntNo].z, 1);
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 000001D8-000002B0       .text daBmdfoot_Draw__FP13bmdfoot_class */
static BOOL daBmdfoot_Draw(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    J3DModel* pJVar1;

    if (i_this->mBC8 != 0) {
        pJVar1 = i_this->m2B4->getModel();
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
        g_env_light.setLightTevColorType(pJVar1, &actor->tevStr);
        i_this->btk->entry(pJVar1->getModelData());
        i_this->m2B4->entryDL();
        if (i_this->mBA8 >= 10) {
            pJVar1 = i_this->mAF4->getModel();
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->mBAC, &i_this->mAF8);
            g_env_light.setLightTevColorType(pJVar1, &i_this->mAF8);
            i_this->mAF4->entryDL();
        }
    }
    return TRUE;
}

/* 000002B0-000003D8       .text anm_init__FP13bmdfoot_classifUcfi */
void anm_init(bmdfoot_class* i_this, int bckFileIdx, float morf, unsigned char loopMode, float speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->m2B4->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bmdfoot", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            dComIfG_getObjectRes("Bmdfoot", soundFileIdx)
        );
    } else {
        i_this->m2B4->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bmdfoot", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            NULL
        );
    }
}

/* 000003D8-00000440       .text housi_off__FP13bmdfoot_class */
void housi_off(bmdfoot_class* i_this) {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m41C); i++) {
        if (i_this->m41C[i].getEmitter() != NULL) {
            i_this->m41C[i].getEmitter()->stopCreateParticle();
        }
    }
    if (i_this->m4B0.getEmitter() != NULL) {
        i_this->m4B0.end();
    }
}

/* 00000440-00000840       .text wait__FP13bmdfoot_class */
void wait(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    short sVar2;
    int iVar3;
    cXyz local_98;
    static s32 eff_id[] = {0x0A, 0x0C, 0x11};
    s32 i;

    iVar3 = i_this->m2B4->getFrame();
    local_98.setall(0.0f);
    
    for (i = 0; i < (s32)ARRAY_SIZE(i_this->m3F8); i++) {
        MTXCopy(i_this->m2B4->getModel()->getAnmMtx(eff_id[i]), *calc_mtx);
        MtxPosition(&local_98, &i_this->m3F8[i]);
        if (i_this->m3F4 == 0) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_80ED, &i_this->m3F8[i], NULL, NULL, 0xFF, &i_this->m41C[i]);
        }
        if (i_this->m41C[i].getEmitter() != NULL) {
            if (iVar3 == 0) {
                i_this->m41C[i].getEmitter()->playCreateParticle();
            } else if (iVar3 == 20) {
                i_this->m41C[i].getEmitter()->stopCreateParticle();
            }
        }
    }
    
    i_this->m3F4 = 1;
    
    switch (i_this->m2BC) {
    case -1:
        for (i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
            cLib_addCalc2(&i_this->m2CC[i].x, (s32)(0x10U - i) * (0.003f + REG12_F(3)), 0.1f, (0.008f + REG12_F(4)));
            i_this->m3A4[i] = 0.0f;
        }
        if (i_this->m2C0[2] == 0) {
            housi_off(i_this);
            i_this->m2BA = 1;
            i_this->m2BC = 0;
        }
        break;
    case 0:
        i_this->m2BC++;
        anm_init(i_this, BMDFOOT_BCK_ASI_WAIT, 50.0f, J3DFrameCtrl::EMode_LOOP, (cM_rndF(0.2f) + 0.9f), -1);
        i_this->m2C0[0] = (s16)(int)(cM_rndF(150.0f) + 100.0f);
        i_this->m3EC = (s16)(int)cM_rndFX(32768.0f);
        for (i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
            i_this->m3A4[i] = REG14_F(13) + (0.2f + cM_rndFX(0.1f));
        }
        break;
    case 1:
        i_this->m3EC = (i_this->m3EC + (s16)(REG14_S(4) + 0x200));
        if (boss->m332 == 1) {
            sVar2 = actor->current.angle.y - fopAcM_searchPlayerAngleY(actor);
            if (sVar2 < 0) {
                sVar2 = -sVar2;
            }
            if (sVar2 < l_HIO.m06) {
                housi_off(i_this);
                i_this->m2BA = 1;
                i_this->m2BC = 0;
            } else {
                i_this->m2C0[0] = (s16)(int)(cM_rndF(50.0f) + 50.0f);
            }
        } else {
            if (boss->m332 == 2) {
                housi_off(i_this);
                i_this->m2BA = 2;
                i_this->m2BC = 0;
            }
        }
        break;
    }
}

/* 0000087C-00000D8C       .text attack_1__FP13bmdfoot_class */
void attack_1(bmdfoot_class* i_this) {
    /* Nonmatching - retail-only regalloc */
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    bool bVar2;
    short sVar3;
    short sVar5;
    J3DModel* pJVar9;
    s32 i;
    cXyz local_5c;
    cXyz cStack_68;
    static s32 jno[] = {0x0A, 0x0C, 0x11};
    static s32 col_joint[] = {0x01, 0x03, 0x05, 0x07, 0x09};

    bVar2 = false;
    local_5c.setall(0.0f);
    
    switch (i_this->m2BC) {
    case 0:
        i_this->m2C0[0] = cM_rndF(20.0f);
        i_this->m2BC++;
    case 1:
        i_this->mBC4 = 0.0f;
        if (i_this->m2C0[0] == 0) {
            anm_init(i_this, BMDFOOT_BCK_ASI_ATTACK1, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m2BC++;
            i_this->mBD0 = 0x1e;
        }
        break;
    case 2:
        if (i_this->mBD0 == 0) {
            i_this->mBD0 = 0x1e;
        }
        if (i_this->m2B4->isStop()) {
            anm_init(i_this, BMDFOOT_BCK_ASI_ATTACK_LOOP, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m2C0[0] = 0x3c;
            i_this->m2BC++;
        }
        break;
    case 3:
        if (i_this->mBD0 == 0) {
            i_this->mBD0 = 0x1e;
        }
        for (i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
            i_this->m3A4[i] = 0.0f;
            cLib_addCalc0(&i_this->m2CC[i].z, 0.1f, 0.05f);
        }
        if (i_this->m2C0[0] == 0) {
            anm_init(i_this, BMDFOOT_BCK_ASI_ATTACK2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m2BC++;
            i_this->m2C0[0] = REG14_S(2) + 0x1c;
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_PREP, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    case 4:
        bVar2 = true;
        if (i_this->m2C0[0] == 1) {
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_ATTACK, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            for (s32 i = 0; i < (s32)ARRAY_SIZE(jno); i++) {
                MTXCopy(i_this->m2B4->getModel()->getAnmMtx(jno[i]), *calc_mtx);
                MtxPosition(&local_5c, &cStack_68);
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8065, &cStack_68, 0xFF, g_whiteColor, g_whiteColor, 0);
            }
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8066, &i_this->mAE8, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_A06A, &i_this->mAE8, 0xB9, g_whiteColor, g_whiteColor, 0);
        }
        if (i_this->m2B4->isStop()) {
            i_this->m2BA = 0;
            i_this->m2BC = 0;
        }
        break;
    }
    
    sVar3 = fopAcM_searchPlayerAngleY(actor) - actor->current.angle.y;
    if (sVar3 > l_HIO.m06) {
        sVar5 = l_HIO.m06;
    } else if (sVar3 < (s16)-l_HIO.m06) {
        sVar5 = -l_HIO.m06;
    } else {
        sVar5 = sVar3;
    }
    cLib_addCalcAngleS2(&i_this->m2BE, sVar5, 4, i_this->mBC4 + 128.0f);
    cLib_addCalc2(&i_this->mBC4, 10000.0f, 1.0f, REG0_F(7) + 20.0f);
    
    if (bVar2) {
        pJVar9 = i_this->m2B4->getModel();
        for (i = 0; i < (s32)ARRAY_SIZE(i_this->m50C); i++) {
            MTXCopy(pJVar9->getAnmMtx((i_this->m2B8 & 7U) + col_joint[i]), *calc_mtx);
            MtxPosition(&local_5c, &cStack_68);
            i_this->m50C[i].SetC(cStack_68);
            i_this->m50C[i].SetR(40.0f);
            i_this->m50C[i].OnAtSetBit();
            i_this->m50C[i].OffCoSetBit();
            dComIfG_Ccsp()->Set(&i_this->m50C[i]);
        }
    }
}

/* 00000D8C-00001180       .text ug_move__FP13bmdfoot_class */
s32 ug_move(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    u32 uVar4;
    f32 dVar5;
    f32 dVar6;
    float fVar7;
    cXyz local_4c;
    cXyz cStack_58;
    cXyz local_64;

    daPy_py_c* apdVar3 = daPy_getPlayerActorClass();
    uVar4 = 0;
    switch (i_this->mBA8) {
    case 0:
        break;
    case 1:
        i_this->mBAC = actor->current.pos;
        i_this->mBAC.y = boss->m328;
        i_this->mBB8.y = actor->current.angle.y;
        i_this->mBC0 = 0.0f;
        i_this->mBA8 = 2;
        fVar7 = cM_rndF(10000.0f);
        i_this->m2B8 = (s16)(int)fVar7;
        dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0FC, &i_this->mBAC, &i_this->mBB8, NULL, 0xB9, &i_this->m4B0, (u8)actor->current.roomNo);
        break;
    case 0xa:
        break;
    case 2:
        local_64 = apdVar3->current.pos - i_this->mBAC;
        fVar7 = local_64.abs();
        dVar5 = (fVar7 * 10.0f);
        if (dVar5 > (REG14_F(14) + 10000.0f)) {
            dVar5 = (REG14_F(14) + 10000.0f);
        }
        dVar6 = cM_ssin(i_this->m2B8 * (REG14_S(3) + 2000));
        s16 r28 = dVar5 * dVar6;
        s16 r4 = r28 + cM_atan2s(local_64.x, local_64.z);
        cLib_addCalcAngleS2(&i_this->mBB8.y, r4, 0x10, 0x2000);
        local_4c.y = 0.0f;
        local_4c.x = 0.0f;
        local_4c.z = REG14_F(16) + 20.0f;
        cMtx_YrotS(*calc_mtx, (int)i_this->mBB8.y);
        MtxPosition(&local_4c, &cStack_58);
        i_this->mBAC += cStack_58;
        i_this->mBC0 = i_this->mBC0 + local_4c.z;
        fVar7 = local_64.abs();
        if ((fVar7 < 300.0f) || (i_this->mBC0 > REG14_F(15) + 3000.0f)) {
            i_this->mBA8 = 10;
            if (i_this->m4B0.getEmitter() != NULL) {
                i_this->m4B0.end();
            }
            uVar4 = 1;
        }
        break;
    }
    MtxTrans(i_this->mBAC.x, i_this->mBAC.y, i_this->mBAC.z, false);
    cMtx_YrotM(*calc_mtx, i_this->mBB8.y);
    J3DModel* model = i_this->mAF4->getModel();
    model->setBaseTRMtx(*calc_mtx);
    i_this->mAF4->play(NULL, 0, 0);
    i_this->mAF4->calc();
    return uVar4;
}

/* 00001180-00001B00       .text attack_2__FP13bmdfoot_class */
void attack_2(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    bool bVar1;
    J3DAnmTransform* pJVar2;
    cXyz local_3c;
    cXyz local_48;
    static s32 col_joint[] = {0x11, 0x0F, 0x0C, 0x09};

    local_3c.z = 0.0f;
    local_3c.y = 0.0f;
    local_3c.x = 0.0f;
    boss->m334 = 10;
    switch (i_this->m2BC) {
    case 0:
        i_this->m2C0[0] = (s16)(int)cM_rndF(20.0f);
        i_this->m2BC++;
    case 1:
        i_this->mBC4 = 0.0f;
        if (i_this->m2C0[0] == 0) {
            anm_init(i_this, BMDFOOT_BCK_ASI_UMARU, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m2BC++;
            i_this->m2C0[0] = 5;
            i_this->mBD0 = 0x1e;
        }
        break;
    case 2:
        if ((s32)i_this->m2B4->getFrame() == 49) {
            MTXCopy(i_this->m2B4->getModel()->getAnmMtx(0x11), *calc_mtx);
            MtxPosition(&local_3c, &local_48);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8065, &local_48, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8066, &local_48, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_A06A, &local_48, 0xB9, g_whiteColor, g_whiteColor, 0);
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_IN_G, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m2B4->isStop()) {
            anm_init(i_this, BMDFOOT_BCK_ASI_UMARU_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m2BC++;
            i_this->mBA8 = 1;
        }
        break;
    case 3:
        mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_DIG, &i_this->mBAC, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        if (ug_move(i_this)) {
            pJVar2 = (J3DAnmTransform*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BCK_ASI_DATTACK1);
            i_this->mAF4->setAnm(pJVar2, J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2BC++;
        }
        break;
    case 4:
        if ((s32)i_this->mAF4->getFrame() == 2) {
            local_48 = i_this->mBAC;
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8065, &local_48, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8066, &local_48, 0xFF, g_whiteColor, g_whiteColor, 0);
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_A06A, &local_48, 0xB9, g_whiteColor, g_whiteColor, 0);
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_OUT_G, &i_this->mBAC, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        ug_move(i_this);
        bVar1 = true;
        if (i_this->mAF4->isStop()) {
            pJVar2 = (J3DAnmTransform*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BCK_ASI_DATTACK2);
            i_this->mAF4->setAnm(pJVar2, J3DFrameCtrl::EMode_LOOP, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2C0[0] = 0xb4;
            i_this->m2BC++;
        }
        break;
    case 5:
        ug_move(i_this);
        mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_L_ATK, &i_this->mBAC, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        for (s32 i = 0; i < (s32)ARRAY_SIZE(col_joint); i++) {
            MTXCopy(i_this->mAF4->getModel()->getAnmMtx(col_joint[i]), *calc_mtx);
            MtxPosition(&local_3c, &local_48);
            i_this->m50C[i].SetC(local_48);
            i_this->m50C[i].SetR(40.0f);
            dComIfG_Ccsp()->Set(&i_this->m50C[i]);
        }
        if (i_this->m2C0[0] == 0) {
            pJVar2 = (J3DAnmTransform*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BCK_ASI_DATTACK3);
            i_this->mAF4->setAnm(pJVar2, J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2BC++;
        }
        break;
    case 6:
        ug_move(i_this);
        if ((s32)i_this->mAF4->getFrame() == 12) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F9, &i_this->mBAC);
            dComIfGp_particle_set(dPa_name::ID_SCENE_80FA, &i_this->mBAC);
            i_this->m498[0].x = i_this->mBAC.x;
            i_this->m498[0].y = i_this->mBAC.y;
            i_this->m498[0].z = i_this->mBAC.z;
            dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0FB, &i_this->m498[0], NULL, NULL, 0xB9, &i_this->m458[0], (u8)actor->current.roomNo);
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_IN_G2, &i_this->mBAC, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mAF4->isStop()) {
            anm_init(i_this, BMDFOOT_BCK_ASI_NUKU, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m2BC++;
            i_this->mBA8 = 0;
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_OUT_G2, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    case 7:
        if ((s32)i_this->m2B4->getFrame() == 13) {
            local_48 = actor->current.pos;
            local_48.y = i_this->mBAC.y;
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F9, &local_48);
            dComIfGp_particle_set(dPa_name::ID_SCENE_80FA, &local_48);
            i_this->m498[1].x = local_48.x;
            i_this->m498[1].y = local_48.y;
            i_this->m498[1].z = local_48.z;
            dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0FB, &i_this->m498[1], NULL, NULL, 0xB9, &i_this->m458[1], (u8)actor->current.roomNo);
        }
        if (i_this->m2B4->isStop()) {
            i_this->m2BA = 0;
            i_this->m2BC = 0;
        }
    }
    MTXCopy(i_this->m2B4->getModel()->getAnmMtx(4), *calc_mtx);
    MtxPosition(&local_3c, &local_48);
    i_this->m50C[4].SetC(local_48);
    i_this->m50C[4].SetR(50.0f);
    i_this->m50C[4].OffAtSetBit();
    i_this->m50C[4].OnCoSetBit();
    dComIfG_Ccsp()->Set(&i_this->m50C[4]);
}

/* 00001B00-00001CDC       .text damage__FP13bmdfoot_class */
void damage(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    f32 dVar5;
    float fVar9;

    switch (i_this->m2BC) {
    case 0:
        anm_init(i_this, BMDFOOT_BCK_ASI_NOBIKIRU, 40.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m2BC++;
        i_this->m2C0[0] = 0x1e;
        fVar9 = cM_rndFX(32768.0f);
        i_this->m3EC = (s16)(int)fVar9;
        for (s32 i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
            i_this->m3A4[i] = (0.3f + cM_rndFX(0.2f));
        }
    case 1:
        if (i_this->m2C0[0] != 0) {
            dVar5 = ((fopAcM_GetParam(actor) & 0xf) * 0.01f);
            for (s32 i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
                cLib_addCalc2(&i_this->m2CC[i].x, -(dVar5 + (0.05f + ((i) * (0.03f + REG14_F(3))))), 0.1f, REG14_F(4) + 0.1f);
            }
        }
        if (boss->m331 > 0) {
            i_this->m2BA = 0;
            i_this->m2BC = -1;
            i_this->m2C0[2] = 0x14;
        }
        break;
    }
}

/* 00001CDC-00001ED8       .text start__FP13bmdfoot_class */
void start(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    
    for (s32 i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
        i_this->m2CC[i].z = 0;
        i_this->m3A4[i] = 0;
    }
    
    switch (i_this->m2BC) {
    case 0:
        if (boss->m332 == 6) {
            i_this->m2BC = 1;
            i_this->m2C0[0] = (s16)(int)cM_rndF(10.0f);
        }
        break;
    case 1:
        if (i_this->m2C0[0] == 0) {
            i_this->mBC8 = 1;
            anm_init(i_this, BMDFOOT_BCK_ASI_START1, 1.0f, J3DFrameCtrl::EMode_NONE, (cM_rndF(0.2f) + 0.9f), -1);
            i_this->m2BC = 2;
        }
        break;
    case 2:
        if (i_this->m2B4->isStop()) {
            anm_init(i_this, BMDFOOT_BCK_ASI_START2, 30.0f, J3DFrameCtrl::EMode_LOOP, (cM_rndF(0.2f) + 0.9f), -1);
            i_this->m2BC = 3;
        }
        break;
    case 3:
        if ((s32)i_this->m2B4->getFrame() == 2) {
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_MOVE_1, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (boss->m332 == 7) {
            i_this->m2BA = 0;
            i_this->m2BC = 0;
        }
        break;
    }
}

/* 00001ED8-00001FB8       .text end__FP13bmdfoot_class */
void end(bmdfoot_class* i_this) {
    for (s32 i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
        i_this->m2CC[i].z = 0;
        i_this->m3A4[i] = 0;
    }
    if (boss->mB76 == 2) {
        anm_init(i_this, BMDFOOT_BCK_ASI_DEAD_LOOP, 30.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    }
    if (boss->mB76 == REG8_S(8) + 0x17c) {
        anm_init(i_this, BMDFOOT_BCK_ASI_DEAD, 30.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
    }
}

/* 00001FB8-000021B8       .text move__FP13bmdfoot_class */
void move(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    s16 sVar1;
    cXyz local_20;
    cXyz cStack_2c;

    if (boss != NULL) {
        sVar1 = (u16)(fopAcM_GetParam(actor) & 0xF) << 13;
        cMtx_YrotS(*calc_mtx, boss->shape_angle.y);
        cMtx_XrotM(*calc_mtx, boss->shape_angle.x);
        cMtx_ZrotM(*calc_mtx, boss->shape_angle.z);
        cMtx_YrotM(*calc_mtx, sVar1);
        actor->current.angle.y = sVar1 + boss->shape_angle.y;
        local_20.x = 0.0f;
        local_20.y = REG14_F(3);
        local_20.z = REG14_F(4) + 180.0f;
        MtxPosition(&local_20, &cStack_2c);
        actor->current.pos = boss->current.pos + cStack_2c;
        switch (i_this->m2BA) {
        case 0:
            wait(i_this);
            break;
        case 1:
            attack_1(i_this);
            break;
        case 2:
            attack_2(i_this);
            break;
        case 3:
            damage(i_this);
            if (boss->m332 == 8) {
                i_this->m2BA = 0xb;
                i_this->m2BC = 0;
            }
            break;
        case 10:
            start(i_this);
            break;
        case 0xb:
            end(i_this);
        }
        if (boss->m332 == 3) {
            housi_off(i_this);
            i_this->m2BA = 3;
            i_this->m2BC = 0;
            i_this->mBA8 = 0;
        }
    }
}

/* 000021B8-00002204       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* search, void* param_2) {
    if ((fopAc_IsActor(search)) && (fopAcM_GetName(search) == PROC_BMD)) {
        return search;
    } else {
        return NULL;
    }
}

/* 00002204-00002594       .text daBmdfoot_Execute__FP13bmdfoot_class */
static BOOL daBmdfoot_Execute(bmdfoot_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    short sVar1;
    J3DModel* pJVar5;
    cXyz local_68;
    s32 i;

    if (boss == NULL) {
        boss = (bmd_class*)fpcM_Search(s_a_d_sub, i_this);
    }
    i_this->m2B8++;
    for (i = 0; i < (s32)ARRAY_SIZE(i_this->m2C0); i++) {
        if (i_this->m2C0[i] != 0) {
            i_this->m2C0[i]--;
        }
    }
    if (i_this->m2C8[0] != 0) {
        i_this->m2C8[0]--;
    }
    move(i_this);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->current.angle.y + i_this->m2BE);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    cMtx_ZrotM(*calc_mtx, actor->current.angle.z + i_this->m2BE * 2);
    pJVar5 = i_this->m2B4->getModel();
    pJVar5->setBaseTRMtx(*calc_mtx);
    i_this->m2B4->play(NULL, 0, 0);
    i_this->m2B4->calc();
    if (i_this->mBD0 != 0) {
        if (i_this->mBD0 == 0x1e) {
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_MOVE_2, &i_this->mAE8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        i_this->mBD0 = i_this->mBD0 + -1;
    }
    sVar1 = 29 - i_this->mBD0;
    if (sVar1 >= 30) {
        sVar1 = sVar1 % 30;
    }
    i_this->btk->setFrame(sVar1);
    MTXCopy(pJVar5->getAnmMtx(REG14_S(6) + 0x10), *calc_mtx);
    local_68.z = 0.0f;
    local_68.y = 0.0f;
    local_68.x = 0.0f;
    MtxPosition(&local_68, &i_this->mAE8);
    if ((boss != NULL) && (i_this->mAE8.y < boss->m328)) {
        i_this->mAE8.y = boss->m328;
    }
    cLib_addCalcAngleS2(&i_this->m2BE, 0, 0x10, 0x80);
    s16 sVar1_2;
    if (i_this->m2BA < 3) {
        sVar1_2 = l_HIO.m08;
    } else {
        sVar1_2 = REG0_S(4);
    }
    cLib_addCalcAngleS2(&actor->current.angle.x, sVar1_2, 0x10, 0x80);
    for (i = 2; i <= (s32)ARRAY_SIZE(i_this->m3A4); i++) {
        f32 f1 = i_this->m3A4[i] * cM_ssin(i_this->m3EC + i * (REG0_S(6) + 9000));
        cLib_addCalc2(&i_this->m2CC[i].z, f1, 0.05f, 0.01f + REG14_F(5));
        cLib_addCalc0(&i_this->m2CC[i].x, 0.05f, 0.005f + REG14_F(5));
    }
    return TRUE;
}

/* 00002594-0000259C       .text daBmdfoot_IsDelete__FP13bmdfoot_class */
static BOOL daBmdfoot_IsDelete(bmdfoot_class*) {
    return TRUE;
}

/* 0000259C-000026B0       .text daBmdfoot_Delete__FP13bmdfoot_class */
static BOOL daBmdfoot_Delete(bmdfoot_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->m2AC, "Bmdfoot");
    if (i_this->mBD2 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    mDoAud_seDeleteObject(&i_this->mAE8);
    mDoAud_seDeleteObject(&i_this->mBAC);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m41C); i++) {
        i_this->m41C[i].end();
    }
    i_this->m458[0].end();
    i_this->m458[1].end();
    i_this->m4B0.end();
    boss = NULL;
    return TRUE;
}

/* 000026B0-000029B4       .text useHeapInit__FP13bmdfoot_class */
s32 useHeapInit(bmdfoot_class* i_this) {
    mDoExt_McaMorf* pmVar1;
    mDoExt_btkAnm* pmVar5;
    J3DAnmTextureSRTKey* pAnm;
    int iVar7;
    J3DModel* pJVar9;

    pmVar1 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BMD_ASI),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BCK_ASI_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        cM_rndF(0.2f) + 0.9f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m2B4 = pmVar1;
    pJVar9 = i_this->m2B4->getModel();
    if (pJVar9 == NULL) {
        return FALSE;
    }
#if VERSION > VERSION_DEMO
    if (i_this->m2B4 == NULL) {
        return FALSE;
    }
#endif
    
    pJVar9->setUserArea((u32)i_this);
    for (u16 uVar16 = 0; uVar16 < pJVar9->getModelData()->getJointNum(); uVar16++) {
        pJVar9->getModelData()->getJointNodePointer(uVar16)->setCallBack(nodeCallBack);
    }
    pmVar5 = new mDoExt_btkAnm();
    i_this->btk = pmVar5;
    JUT_ASSERT(DEMO_SELECT(1416, 1426), i_this->btk);
    pAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BTK_ASI);
    iVar7 = i_this->btk->init(pJVar9->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
#if VERSION > VERSION_DEMO
    if (iVar7 == 0) {
        return FALSE;
    }
#endif
    
    pmVar1 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BMD_ASI),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmdfoot", BMDFOOT_BCK_ASI_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        cM_rndF(0.2f) + 0.9f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->mAF4 = pmVar1;
    if (i_this->mAF4->getModel() == NULL) {
        return FALSE;
    }
    
    return TRUE;
}

/* 000029FC-00002A1C       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c* a_this) {
    bmdfoot_class* i_this = (bmdfoot_class*)a_this;
    return useHeapInit(i_this);
}

/* 00002A1C-00002E88       .text daBmdfoot_Create__FP10fopAc_ac_c */
static cPhs_State daBmdfoot_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
    cPhs_State res;

    fopAcM_SetupActor(a_this, bmdfoot_class);
    bmdfoot_class* i_this = (bmdfoot_class*)a_this;
    res = dComIfG_resLoad(&i_this->m2AC, "Bmdfoot");
    if (res == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    } else if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    i_this->m458[0].setFollowOff();
    i_this->m458[1].setFollowOff();
    if (!fopAcM_entrySolidHeap(a_this, solidHeapCB, 0x5040)) {
        return cPhs_ERROR_e;
    }
    if (hio_set == 0) {
        hio_set = 1;
        i_this->mBD2 = 1;
        l_HIO.mNo = mDoHIO_createChild("森ボス足", &l_HIO); // Forest boss feet
    }
    a_this->health = 2;
    i_this->m2B8 = (s16)(int)cM_rndF(10000.0f);
    boss = NULL;
    i_this->m4D0.Init(0xFF, 0, a_this);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m50C); i++) {
        i_this->m50C[i].SetStts(&i_this->m4D0);
        i_this->m50C[i].Set(cc_sph_src);
    }
    a_this->attention_info.position.y = -20000.0f;
    a_this->eyePos.y = -20000.0f;
    if (!(g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossDemo()) && (dComIfGp_getStartStageName()[0] != 'X')) {
        i_this->m2BA = 10;
    } else {
        i_this->mBC8 = 1;
    }
#if VERSION > VERSION_DEMO
    i_this->mAF8 = a_this->tevStr;
#endif
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daBmdfoot_Method = {
    (process_method_func)daBmdfoot_Create,
    (process_method_func)daBmdfoot_Delete,
    (process_method_func)daBmdfoot_Execute,
    (process_method_func)daBmdfoot_IsDelete,
    (process_method_func)daBmdfoot_Draw,
};

actor_process_profile_definition g_profile_BMDFOOT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMDFOOT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmdfoot_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BMDFOOT,
    /* Actor SubMtd */ &l_daBmdfoot_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
