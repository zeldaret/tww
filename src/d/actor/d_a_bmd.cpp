/**
 * d_a_bmd.cpp
 * Boss - Kalle Demos (Core) / 森ボス (Forest Boss)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bmd.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_camera.h"
#include "d/d_kankyo_wether.h"
#include "d/d_lib.h"
#include "d/res/res_bmd.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "JSystem/JUtility/JUTReport.h"
#include "m_Do/m_Do_graphic.h"

class daBmd_HIO_c : public JORReflexible {
public:
    daBmd_HIO_c();
    virtual ~daBmd_HIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ s16 m14;
};

/* 000000EC-00000134       .text __ct__11daBmd_HIO_cFv */
daBmd_HIO_c::daBmd_HIO_c() {
    mNo = 0xFF;
    m05 = 0;
    m08 = 0.8f;
    m14 = 100;
    m0C = 1.0f;
    m10 = 0.5f;
}

static cXyz static_center_pos; // Unused
static daBmd_HIO_c l_HIO;

/* 00000134-00000240       .text core_nodeCallBack__FP7J3DNodei */
static BOOL core_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bmd_class* i_this = (bmd_class*)model->getUserArea();
        if (((i_this != 0) && (jntNo != 0)) && (jntNo != 5)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo < 7) {
                cMtx_XrotM(*calc_mtx, i_this->m90C[0].x);
                cMtx_ZrotM(*calc_mtx, i_this->m90C[0].z);
            } else {
                cMtx_XrotM(*calc_mtx, i_this->m90C[1].x);
                cMtx_ZrotM(*calc_mtx, i_this->m90C[1].z);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000240-000002CC       .text mk_draw__FP9bmd_class */
void mk_draw(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m2DC != 0) {
        g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &actor->tevStr);
        i_this->m2C8->entryDL();
        i_this->m2CC->setBaseTRMtx(i_this->m2C8->getModel()->getAnmMtx(1));
        g_env_light.setLightTevColorType(i_this->m2CC, &actor->tevStr);
        mDoExt_modelUpdateDL(i_this->m2CC);
    }
}

/* 000002CC-000005C8       .text daBmd_Draw__FP9bmd_class */
static BOOL daBmd_Draw(bmd_class* i_this) {
    J3DModel* pJVar11;

#if VERSION > VERSION_DEMO
    if (i_this->mB72 > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->mB72);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->mB72 == 1) {
        i_this->mB72 = 0;
        mDoGph_gInf_c::offBlure();
    }
#endif
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    pJVar11 = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(pJVar11, &i_this->actor.tevStr);
    if (i_this->mB70 != 0) {
        i_this->mpBrkAnm->entry(pJVar11->getModelData());
        i_this->mpBtkAnm->entry(pJVar11->getModelData());
    }
    i_this->mpMorf->entryDL();
    if (i_this->m306 < 100) {
        g_env_light.setLightTevColorType(i_this->m2C0->getModel(), &i_this->actor.tevStr);
        i_this->m2C0->entryDL();
    } else if (i_this->m306 < 0x6e) {
        g_env_light.setLightTevColorType(i_this->m2C4->getModel(), &i_this->actor.tevStr);
        i_this->m2C4->entryDL();
    }
    mk_draw(i_this);
    dComIfGd_setSimpleShadow2(
        &i_this->actor.current.pos, i_this->mAcch.GetGroundH(), 400.0f, i_this->mAcch.m_gnd, 0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj
    );
    dKy_tevstr_c tevstr = i_this->actor.tevStr;
    static cXyz g_pos(0.0f, 0.0f, 0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &g_pos, &tevstr);
    g_env_light.setLightTevColorType(i_this->m2D0, &tevstr);
    i_this->m2D4->entry(i_this->m2D0->getModelData());
    mDoExt_modelUpdateDL(i_this->m2D0);
    dSnap_RegistFig(DSNAP_TYPE_BMD, &i_this->actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00000604-00000734       .text anm_init__FP9bmd_classifUcfi */
void anm_init(bmd_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bmd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Ki", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000734-000010A4       .text damage__FP9bmd_class */
void damage(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    s16 sVar3;
    s16 sVar5;
    JPABaseEmitter* pJVar4;
    int iVar7;
    cXyz local_40;
    cXyz local_4c;
    static s32 jno[] = {0x1A, 0x23, 0x2C, 0x35, 0x3E};

#if VERSION > VERSION_DEMO
    bVar1 = false;
#endif
    local_40.setall(0.0f);
    switch (i_this->m302) {
    case 0:
        i_this->m302 = 1;
        i_this->m308[0] = 0x28;
        actor->speed.y = 0.0f;
        actor->gravity = 0.0f;
    // fallthrough
    case 1:
        if (i_this->m308[0] == 0x1e) {
            actor->gravity = -3.0f;
            i_this->m332 = 3;
        }
        if (actor->current.pos.y <= i_this->m328 + 5.0f) {
            anm_init(i_this, BMD_BCK_HANA_OTIRU, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m304 = 1;
            i_this->m302 = 2;
            sVar5 = fopAcM_searchPlayerAngleY(actor);
            i_this->m93C = sVar5;
            i_this->mBD8 = 2000.0f;
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F3, &actor->current.pos);
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_UNK_151);
            } else {
                mDoAud_bgmStart(JA_BGM_UNK_105);
            }
        }
        break;
    case 2:
        if (((s16)(REG0_S(1) + 10) == (s16)i_this->mpMorf->getFrame()) && (fopAcM_searchPlayerDistance(actor) < (REG0_F(8) + 400.0f))) {
            i_this->m904 = REG0_S(2) + 0x14;
            i_this->m314 = 0x1e;
        }
        if ((s16)i_this->mpMorf->getFrame() == 30) {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(jno); i++) {
                pJVar4 = dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0F4, &actor->current.pos, NULL, NULL, 0xB9, &i_this->mA90[i], fopAcM_GetRoomNo(actor));
                if (pJVar4 != NULL) {
                    pJVar4->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(jno[i]));
                }
            }
        }
        if ((s16)i_this->mpMorf->getFrame() == 10) {
            i_this->mBD8 = 2000.0f;
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BMD_BCK_HIRAKU_WAIT, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m302 = 3;
            i_this->m308[0] = l_HIO.m14;
            i_this->m940 = 0;
        }
        if ((s16)i_this->mpMorf->getFrame() > 25) {
            cLib_addCalc2(&i_this->mBDC, 1.0f, 1.0f, 0.1f);
        }
        break;
    case 3:
        i_this->mB71 = 2;
        if (i_this->m308[0] == 0) {
            i_this->m302 = 4;
            anm_init(i_this, BMD_BCK_HANA_TOJIRU, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m304 = 2;
            mDoAud_seStart(JA_SE_CM_BKM_FLW_WAVING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        cLib_addCalc2(&i_this->mBDC, 1.0f, 1.0f, 0.1f);
        break;
    case 4:
        if ((s16)i_this->mpMorf->getFrame() == 23) {
            mDoAud_seStart(JA_SE_CM_BKM_BODY_CLOSE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((s16)i_this->mpMorf->getFrame() == 27) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8100, &actor->current.pos);
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_BKM);
            } else {
                mDoAud_bgmStart(JA_BGM_KINDAN_BOSS);
            }
        }
        iVar7 = i_this->mpMorf->getFrame();
        if ((s16)iVar7 <= 15) {
            cLib_addCalc2(&i_this->mBDC, 1.0f, 1.0f, 0.1f);
        }
        if ((s16)i_this->mpMorf->getFrame() == 15) {
            i_this->mBD8 = 2000.0f;
        }
        iVar7 = i_this->mpMorf->getFrame();
        if ((s16)iVar7 < (s16)(REG0_S(5) + 0x14)) {
            sVar3 = REG0_S(3) + 200;
            i_this->m942 = 0;
        } else {
            i_this->m304 = 3;
            sVar3 = REG0_S(4) + 0x290;
#if VERSION == VERSION_DEMO
            if (i_this->m942 != 0)
#else
            if ((i_this->m942 != 0) && (REG0_S(9) == 0))
#endif
            {
                i_this->m942--;
                i_this->mMode = 5;
                i_this->m302 = 0;
                return;
            }
        }
        cLib_addCalcAngleS2(&i_this->m940, -0x4000, 1, sVar3);
        if (i_this->mpMorf->isStop()) {
            i_this->m302 = 5;
            i_this->m308[0] = 0x1e;
#if VERSION > VERSION_DEMO
            bVar1 = true;
#endif
        }
        break;
    case 5:
        cLib_addCalcAngleS2(&i_this->m940, -0x4000, 1, 0x290);
        if (i_this->m308[0] == 0) {
            i_this->mMode = 0;
            i_this->m302 = -1;
            i_this->m308[0] = 0x3c;
            i_this->m332 = 4;
#if VERSION > VERSION_DEMO
            bVar1 = true;
#endif
        }
        break;
    }
    if ((i_this->m302 >= 2) && (i_this->m302 <= 4)) {
        i_this->mA88[0] = 3;
    }
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 0x10, 0x200);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 0x10, 0x200);
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_40.y = 0.0f;
    local_40.x = 0.0f;
    local_40.z = actor->speedF;
    MtxPosition(&local_40, &local_4c);
    actor->current.pos.x += local_4c.x;
    actor->current.pos.z += local_4c.z;
    actor->current.pos.y += actor->speed.y;
    actor->speed.y = actor->speed.y + actor->gravity;
    if (actor->current.pos.y < i_this->m328) {
        actor->current.pos.y = i_this->m328;
        if (actor->speed.y < -20.0f) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            mDoAud_seStart(JA_SE_CM_BKM_BODY_FALL, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            actor->speed.y = 10.0f;
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F1, &actor->current.pos);
            dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0F2, &actor->current.pos, NULL, NULL, 0xB9, &i_this->mA90[5], (u8)actor->current.roomNo);
        } else {
            actor->speed.y = 0.0f;
        }
        cLib_addCalc0(&actor->speedF, 1.0f, 0.2f);
    }
#if VERSION > VERSION_DEMO
    if ((bVar1) && (fopAcM_searchPlayerDistance(actor) < (REG8_F(8) + 200.0f))) {
        i_this->mMode = 5;
        i_this->m302 = 0;
        anm_init(i_this, BMD_BCK_HANA_TOJIRU, 1.0f, J3DFrameCtrl::EMode_NONE, 5.0f, -1);
    }
#endif
}

/* 000010A4-00001530       .text eat__FP9bmd_class */
void eat(bmd_class* i_this) {
    /* Nonmatching - regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp30;
    cXyz sp24;
    cXyz sp18;

    switch (i_this->m302) {
    case 0:
        i_this->m302 = 1;
        i_this->mB74 = 1;
        i_this->m304 = 2;
#if VERSION > VERSION_DEMO
        i_this->mB72 = 0x96;
#endif
        // fallthrough
    case 1:
        cLib_addCalcAngleS2(&i_this->m940, -0x4000, 1, 0x1000);
        if (i_this->mpMorf->isStop()) {
            i_this->m302 = 2;
            anm_init(i_this, BMD_BCK_HANA_EAT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m308[0] = 0x32;
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_BKM);
            } else {
                mDoAud_bgmStart(JA_BGM_KINDAN_BOSS);
            }
            fopAcM_seStart(actor, JA_SE_CM_BKM_BODY_EATING, 0);
        }
        break;
    case 2:
        if (i_this->m308[0] != 0) {
            return;
        }
        i_this->m302 = 3;
        anm_init(i_this, BMD_BCK_HANA_HAKIDASU, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_seStart(player_actor, JA_SE_CM_BKM_LINK_OUT, 0);
        return;
    case 3:
        if (i_this->mB78 == REG0_S(2) + 0x50) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F8, &actor->current.pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_80F7, &actor->current.pos);
            i_this->m314 = 100;
        }
        if (i_this->mB78 == 0x55) {
            sp18 = actor->current.pos;
            sp18.y += REG17_F(0) + 1000.0f;
            player->setThrowDamage(&sp18, i_this->mB96 + (REG0_S(6) + 0x5000), (REG17_F(1) + 50.0f), (REG17_F(2) + 120.0f), 4);
            i_this->m904 = REG0_S(2) + 0x14;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->m302 = 4;
        }
        break;
    case 4:
        if (i_this->mB76 > (s16)(REG0_S(7) + 0x82)) {
            i_this->m302 = 5;
            i_this->m308[0] = 0x1a;
        }
        break;
    case 5:
        if (fopAcM_searchPlayerDistanceXZ(actor) < 300.0f) {
            cMtx_YrotS(*calc_mtx, i_this->mB96);
            sp30.x = 0.0f;
            sp30.y = 0.0f;
            sp30.z = 350.0f;
            MtxPosition(&sp30, &sp24);
            sp24 += actor->current.pos;
            player->setPlayerPosAndAngle(&sp24, player_actor->shape_angle.y);
        }
        if (i_this->m308[0] == 0) {
            i_this->mMode = 0;
            i_this->m302 = -1;
            i_this->m308[0] = 0x3c;
            i_this->mB74 = 0x96;
            dComIfGp_event_reset();
            i_this->m940 = -0x4000;
            i_this->m332 = 4;
            i_this->m314 = 0;
#if VERSION > VERSION_DEMO
            i_this->mB72 = 1;
#endif
        }
        break;
    }
}

/* 00001530-00001684       .text move1__FP9bmd_class */
void move1(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_28.y = 0.0f;
    local_28.x = 0.0f;
    local_28.z = actor->speedF;
    MtxPosition(&local_28, &actor->speed);
    actor->current.pos += actor->speed;
    cLib_addCalc2(&i_this->m324, cM_ssin(i_this->m2FE * 400) * 20.0f, 0.1f, 10.0f);
    cLib_addCalcAngleS2(&actor->shape_angle.x, cM_ssin(i_this->m2FE * 500) * 700.0f, 0x10, 0x80);
    cLib_addCalcAngleS2(&actor->shape_angle.z, cM_scos(i_this->m2FE * 300) * 700.0f, 0x10, 0x80);
}

/* 00001684-00001B48       .text start__FP9bmd_class */
void start(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar2;
    f32 dVar4;
    cXyz local_28;

    i_this->m310 = 8;
    switch (i_this->m302) {
    case 0:
        anm_init(i_this, BMD_BCK_HIRAKU_WAIT, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m2C0->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_START1), J3DFrameCtrl::EMode_LOOP, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
        i_this->m302 = 1;
        i_this->m304 = 2;
        i_this->m2DC = 1;
    // fallthrough
    case 1:
        i_this->mBDC = 1.0f;
        sVar2 = fopAcM_searchPlayerAngleY(actor);
        i_this->m93C = sVar2;
        cMtx_YrotS(*calc_mtx, i_this->m93C);
        local_28.x = 0.0f;
        local_28.y = REG0_F(1) + 20.0f;
        local_28.z = REG0_F(2) + 90.0f;
        MtxPosition(&local_28, &i_this->m2E0);
        i_this->m2E0 += actor->current.pos;
        i_this->m2FA = i_this->m93C;
        dVar4 = fopAcM_searchPlayerDistance(actor);
        if (dVar4 < 500.0f) {
            i_this->m302 = 2;
            i_this->mB74 = 5;
            i_this->m940 = -0x4000;
            mDoAud_bgmStreamPlay();
        }
        break;
    case 2:
        i_this->m314 = 0x1e;
        sVar2 = fopAcM_searchPlayerAngleY(actor);
        i_this->m93C = sVar2;
        cMtx_YrotS(*calc_mtx, i_this->m93C);
        local_28.x = 0.0f;
        local_28.y = REG0_F(1) + 20.0f;
        local_28.z = REG0_F(2) + 90.0f;
        MtxPosition(&local_28, &i_this->m2E0);
        i_this->m2E0 += actor->current.pos;
        i_this->m2FA = i_this->m93C;
        i_this->mBDC = 1.0f;
        break;
    case 3:
        i_this->m314 = 0x1e;
        if (i_this->mB76 < 0xfa) {
            i_this->mBDC = 1.0f;
        }
        if (i_this->mB76 == 0x78) {
            anm_init(i_this, BMD_BCK_HANA_START1, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            mDoAud_seStart(JA_SE_CM_BKM_FLW_WAVING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == 0x96) {
            anm_init(i_this, BMD_BCK_HANA_START2, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mBD8 = 2000.0f;
            mDoAud_seStart(JA_SE_CM_BKM_FLW_TO_BUD, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == 0xb1) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8100, &actor->current.pos);
        }
        if (i_this->mB76 >= 0x96) {
            if (i_this->m331 > 0) {
                move1(i_this);
            }
            if (i_this->mB76 == 0xbe) {
                anm_init(i_this, BMD_BCK_HANA_WAIT, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
        }
        if (i_this->mB76 == 0xd2) {
            i_this->m332 = 5;
            mDoAud_seStart(JA_SE_CM_BKM_VINE_OUT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == 0x1c2) {
            i_this->m332 = 6;
            mDoAud_seStart(JA_SE_CM_BKM_ATKVINE_ENTER, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == 0x168) {
            mDoAud_seStart(JA_SE_CM_BKM_BODY_UP, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    }
}

/* 00001B48-00001EFC       .text end__FP9bmd_class */
void end(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar3;
    static s32 jno[] = {0x19, 0x22, 0x2B, 0x34, 0x3D};

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->m940 = 0;
    i_this->m304 = 1;
    switch (i_this->m302) {
    case 0:
        if (dComIfGp_getStartStageName()[0] == 'X') {
            dLib_setNextStageBySclsNum(0, actor->current.roomNo);
            mDoAud_seStart(JA_SE_LK_B_BOSS_WARP, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            dComIfGs_onEventBit(dSv_event_flag_c::KALLE_DEMOS_TRIALS_CLEAR);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0480);
            return;
        }
#if VERSION > VERSION_DEMO
        mDoAud_bgmStreamPrepare(JA_STRM_BOSS_CLEAR);
#endif
        anm_init(i_this, BMD_BCK_HANA_DEAD1, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m302 = 1;
        i_this->m332 = 8;
        i_this->m314 = 30000;
        // Fall-through
    case 1:
        if (i_this->mB76 < 0x1a4) {
            i_this->mBDC = 1.0f;
        }
        if (i_this->mB76 == REG0_S(2) + 300) {
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        if (i_this->mB76 == REG0_S(4) + 0x17c) {
            anm_init(i_this, BMD_BCK_HANA_DEAD2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            mDoAud_seStart(JA_SE_CM_BKM_END_FLW_WAVING, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == REG0_S(5) + 0x1c2) {
            anm_init(i_this, BMD_BCK_HANA_DEAD3, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            mDoAud_seStart(JA_SE_CM_BKM_END_FLW_LIFTUP, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->mBD8 = 2000.0f;
            i_this->m332 = 9;
            for (s32 i = 0; i < (s32)ARRAY_SIZE(jno); i++) {
                pJVar3 = dComIfGp_particle_set(dPa_name::ID_SCENE_80FF, &actor->current.pos);
                if (pJVar3 != NULL) {
                    pJVar3->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(jno[i]));
                }
            }
        }
        if (i_this->mB76 == 0x230) {
            mDoAud_seStart(JA_SE_CM_BKM_END_FLW_DIE, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->mB76 == REG0_S(6) + 0x276) {
            dComIfGs_onStageBossEnemy();
            fopAcM_createWarpFlower(&actor->current.pos, 0, fopAcM_GetRoomNo(actor), 0);
            i_this->m302 = 2;
            i_this->mB71 = 0;
        }
    case 2:
        break;
    }
}

/* 00001EFC-00002190       .text core_damage_check__FP9bmd_class */
void core_damage_check(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    cXyz local_38;
    CcAtInfo local_2c;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bVar2 = false;
    if (i_this->m310 != 0) {
        return;
    }
    if (i_this->mCoreSph.ChkTgHit() != 0) {
        i_this->m310 = 8;
        fopAcM_monsSeStart(actor, JA_SE_CV_BKM_DAMAGE, 0);
        i_this->m306 = 1;
        local_2c.pParticlePos = NULL;
        local_2c.mpObj = i_this->mCoreSph.GetTgHitObj();
        local_2c.pParticlePos = i_this->mCoreSph.GetTgHitPosP();
        fopAc_ac_c* pfVar4 = cc_at_check(actor, &local_2c);
        if (pfVar4 != NULL) {
            local_38.x = actor->eyePos.x - pfVar4->current.pos.x;
            local_38.z = actor->eyePos.z - pfVar4->current.pos.z;
            i_this->m90C[0].y = cM_atan2s(-local_38.x, -local_38.z);
        }
        i_this->mA88[1] = 10;
        if (actor->health <= 0) {
            bVar2 = true;
        }
    }
    local_38 = player->current.pos - actor->current.pos;
    local_38.y = 0.0f;
    if (!(player->checkForestWaterUse() && i_this->m304 != 0 && local_38.abs() < 300.0f) && !bVar2) {
        return;
    }
    if (!bVar2) {
        mDoAud_seStart(JA_SE_LK_LAST_HIT, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
    i_this->m306 = 100;
    i_this->mMode = 0xb;
    i_this->m302 = 0;
    i_this->mB74 = 100;
    dScnPly_ply_c::nextPauseTimer = 8;
    i_this->m310 = 20000;
    i_this->mBE0 = 2;
    i_this->mBDC = 1.0f;
    mDoAud_bgmStop(30);
#if VERSION == VERSION_DEMO
    mDoAud_bgmStreamPrepare(JA_STRM_BOSS_CLEAR);
#endif
}

/* 000021CC-00002EDC       .text core_move__FP9bmd_class */
void core_move(bmd_class* i_this) {
    /* Nonmatching - switch case */
    fopAc_ac_c* actor = &i_this->actor;
    int iVar1;
    bool bVar5;
    JPABaseEmitter* pJVar7;
    J3DModel* pJVar11;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    bVar5 = false;
    core_damage_check(i_this);
    switch (i_this->m306) {
    case 0:
        break;
    case 1:
        i_this->m2C0->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_DAMAGE), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
        i_this->m306 = 2;
        i_this->m918 = 0;
        i_this->m91C = REG0_F(9) + 6000.0f;
        i_this->m920 = 9000.0f;
        break;
    case 2:
        if (std::fabsf(i_this->m91C) < 200.0f) {
            i_this->m306 = 0;
            i_this->m2C0->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_WAIT), J3DFrameCtrl::EMode_LOOP, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
        }
        break;
    case 100:
        i_this->m2C4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_DEAD1), J3DFrameCtrl::EMode_NONE, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
        i_this->m306 = 0x65;
        i_this->m924 = actor->current.pos;
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y + (REG0_S(4) + 3000));
        local_40.y = 0.0f;
        local_40.x = 0.0f;
        local_40.z = REG0_F(15) + 7.0f;
        MtxPosition(&local_40, &i_this->m930);
        i_this->m930.y = REG0_F(11) + 50.0f;
        i_this->m93E = 0;
        i_this->m93C = 0;
        i_this->m308[2] = 0;
        fopAcM_monsSeStart(actor, JA_SE_CV_BKM_LAST_DAMAGE, 0);
        break;
    case 101:
        i_this->mA8C = 3;
        i_this->m93C = i_this->m93C + 0x800;
        i_this->m93E = i_this->m93E + 0x500;
        i_this->m924 += i_this->m930;
        i_this->m930.y = i_this->m930.y - (REG0_F(12) + 1.0f);
        if (i_this->m924.y <= (i_this->m328 - 10.0f) + REG0_F(13)) {
            i_this->m924.y = (i_this->m328 - 10.0f) + REG0_F(13);
            i_this->m306 = 0x66;
            mDoAud_bgmStreamPlay();
            i_this->m2C4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_DEAD2), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m930.y = 0.0f;
            i_this->m930.z = 0.0f;
            i_this->m930.x = 0.0f;
            bVar5 = true;
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_FALLDOWN, 0);
            mDoAud_seStart(JA_SE_CM_BKM_END_CORE_DROP, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    case 102:
        iVar1 = i_this->m2C4->getFrame();
        if (iVar1 == 14) {
            bVar5 = true;
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_JITABATA, 0);
        }
        i_this->mA8C = 3;
        if (i_this->m2C4->isStop()) {
            i_this->m2C4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_NDEAD1), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m306 = 0x67;
            i_this->m930.z = 10.0f;
            i_this->m930.x = 10.0f;
            i_this->m308[1] = REG0_S(6) + 0xc3;
        }
        break;
    case 103:
        iVar1 = i_this->m2C4->getFrame();
        if (iVar1 == 18) {
            bVar5 = true;
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_JITABATA, 0);
        }
        i_this->mA8C = 3;
        if (i_this->m2C4->isStop()) {
            i_this->m2C4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_NDEAD2), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m306 = 0x68;
        }
        break;
    case 104:
        if ((int)i_this->m2C4->getFrame() == 17 || (int)i_this->m2C4->getFrame() == 37) {
            bVar5 = true;
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_JITABATA, 0);
        }
        i_this->mA8C = 10;
        if (i_this->m2C4->isStop()) {
            i_this->m2C4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_LDEAD), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m306 = 0x69;
            i_this->m930.z = 0.0f;
            i_this->m930.x = 0.0f;
        }
        break;
    case 105:
        if ((s16)i_this->m2C4->getFrame() == 37) {
            pJVar7 = dComIfGp_particle_set(dPa_name::ID_SCENE_80FE, &actor->current.pos);
            if (pJVar7 != NULL) {
                pJVar7->setGlobalRTMatrix(i_this->m2C4->getModel()->getAnmMtx(5));
            }
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_DIE, 0);
        }
        if (i_this->m2C4->isStop()) {
            local_58 = i_this->m924;
            local_58.y += REG0_F(2) + 80.0f;
            fopAcM_createDisappear(actor, &local_58, 0xF, daDisItem_HEART_CONTAINER_e, 0xFF);
            i_this->m306 = 0x6e;
            i_this->m308[2] = 0xaa;
        }
        i_this->m924 += i_this->m930;
        if ((i_this->m308[1] & 0xF) == 0) {
            i_this->m930.x *= -1.0f;
            i_this->m930.z *= -1.0f;
        }
        cLib_addCalcAngleS2(&i_this->m93C, 0, 2, 0x800);
        cLib_addCalcAngleS2(&i_this->m93E, 0, 2, 0x800);
        break;
    case 110:
        if (i_this->m308[2] == 1) {
            i_this->mB74++;
            i_this->mB78 = 0;
            i_this->m306 = 0x6f;
        }
        break;
    case 111:
        break;
    }

    if (i_this->m306 < 100) {
        cMtx_YrotS(*calc_mtx, (s16)((i_this->m93C + 0x8000) - i_this->m90C[0].y));
        local_40.y = 0.0f;
        local_40.x = 0.0f;
        local_40.z = i_this->m91C * cM_ssin(i_this->m918);
        MtxPosition(&local_40, &local_4c);
        i_this->m90C[0].x = local_4c.z;
        i_this->m90C[0].z = local_4c.x;
        local_40.z = i_this->m920 * cM_ssin(i_this->m918 + (REG0_S(6) - 20000));
        MtxPosition(&local_40, &local_4c);
        i_this->m90C[1].x = local_4c.z;
        i_this->m90C[1].z = local_4c.x;
        i_this->m918 += REG0_S(5) + 6000;
        cLib_addCalc0(&i_this->m91C, 1.0f, (REG0_F(10) + 250.0f));
        cLib_addCalc0(&i_this->m920, 1.0f, (REG0_F(10) + 200.0f));
        pJVar11 = i_this->m2C0->getModel();
        mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
        mDoMtx_stack_c::YrotM(i_this->m93C);
        pJVar11->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->m2C0->play(&actor->eyePos, 0, 0);
        i_this->m2C0->calc();
        MTXCopy(pJVar11->getAnmMtx(6), *calc_mtx);
        local_40.x = 0.0f;
        local_40.y = -20.0f;
        local_40.z = 30.0f;
        MtxPosition(&local_40, &actor->eyePos);
        actor->attention_info.position = actor->eyePos;
        actor->attention_info.position.y += 50.0f;
        if (i_this->m304 != 0 &&
#if VERSION > VERSION_DEMO
            i_this->m940 == 0 &&
#endif
            i_this->mMode != 10)
        {
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        }
    } else {
        mDoMtx_stack_c::transS(i_this->m924.x, i_this->m924.y, i_this->m924.z);
        mDoMtx_stack_c::YrotM(i_this->m93C);
        mDoMtx_stack_c::XrotM(i_this->m93E);
        pJVar11 = i_this->m2C4->getModel();
        pJVar11->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->m2C4->play(&actor->eyePos, 0, 0);
        i_this->m2C4->calc();
        MTXCopy(pJVar11->getAnmMtx(REG0_S(4) + 1), *calc_mtx);
        local_40.z = 0.0f;
        local_40.y = 0.0f;
        local_40.x = 0.0f;
        MtxPosition(&local_40, &actor->eyePos);
        if (i_this->m306 >= 0x6F) {
            actor->eyePos.y += 20000.0f;
        }
    }
    i_this->mCoreSph.SetC(actor->eyePos);
    i_this->mCoreSph.SetR(50.0f);
    dComIfG_Ccsp()->Set(&i_this->mCoreSph);
    if (bVar5) {
        dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0FD, &i_this->m924, NULL, NULL, 0xB9, &i_this->mA90[6], (u8)actor->current.roomNo);
        mDoAud_seStart(JA_SE_CM_BKM_END_CORE_LEAP, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
}

/* 00002EDC-00002F40       .text mk_voice_set__FP9bmd_classUl */
void mk_voice_set(bmd_class* i_this, u32 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    mDoAud_monsSeStart(param_2, &i_this->m2E0, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

/* 00002F40-0000330C       .text mk_move__FP9bmd_class */
void mk_move(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar3;
    cXyz local_28;

    if (i_this->m2DC != 0) {
        switch (i_this->m2DC) {
        case 0:
            i_this->m308[3] = 0x96;
            break;
        case 1:
            if (i_this->m308[3] == 0) {
                i_this->m2C8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_CALL_01), J3DFrameCtrl::EMode_LOOP, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
                i_this->m308[3] = (s16)(cM_rndF(90.0f) + 60.0f);
                i_this->m2DC = 2;
                mk_voice_set(i_this, JA_SE_CV_CB_HELP);
            }
            break;
        case 2:
            if (i_this->m308[3] == 0) {
                i_this->m2C8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_CALL_02), J3DFrameCtrl::EMode_LOOP, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
                i_this->m308[3] = (s16)(cM_rndF(90.0f) + 60.0f);
                i_this->m2DC = 1;
                mk_voice_set(i_this, JA_SE_CV_CB_HELP);
            }
            break;
        case 3:
            i_this->m2C8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_CALL_01), J3DFrameCtrl::EMode_LOOP, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2DC = 10;
            mk_voice_set(i_this, JA_SE_CV_CB_HELP);
            break;
        case 4:
            i_this->m2C8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_CALL_03), J3DFrameCtrl::EMode_LOOP, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2DC = 10;
            mk_voice_set(i_this, JA_SE_CV_CB_HELP);
            break;
        case 5:
            i_this->m2C8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_DROP), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            i_this->m2DC = 6;
            break;
        case 6:
            if ((int)i_this->m2C8->getFrame() == 6) {
                local_28 = i_this->m2E0;
                local_28.y += 10.0f;
                pJVar3 = dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0FD, &local_28, NULL, NULL, 0xB9, &i_this->mA90[6], (u8)actor->current.roomNo);
                if (pJVar3 != NULL) {
                    pJVar3->mGlobalDynamicsScale.x = 0.5f;
                    pJVar3->mGlobalDynamicsScale.y = 0.5f;
                    pJVar3->mGlobalDynamicsScale.z = 0.5f;
                    pJVar3->mGlobalParticleScale.x = 0.5f;
                    pJVar3->mGlobalParticleScale.y = 0.5f;
                    pJVar3->mGlobalParticleScale.z = 0.5f;
                }
                mk_voice_set(i_this, JA_SE_CV_CB_SAVED);
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            break;
        }
        mDoMtx_stack_c::transS(i_this->m2E0.x, i_this->m2E0.y, i_this->m2E0.z);
        mDoMtx_stack_c::YrotM(i_this->m2FA);
        i_this->m2C8->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->m2C8->play(NULL, 0, 0);
        i_this->m2C8->calc();
    }
}

/* 0000330C-0000339C       .text damage_check__FP9bmd_class */
void damage_check(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if ((i_this->m331 == 0) && (i_this->m312 == 1)) {
        i_this->mMode = 3;
        i_this->m302 = 0;
        fopAcM_monsSeStart(actor, JA_SE_CV_BKM_CUT_VINE_ALL, 0);
    }
}

/* 0000339C-00003910       .text wait__FP9bmd_class */
void wait(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 dVar6;
    f32 fVar7;
    cXyz local_30;
    cXyz local_3c;

    if (i_this->m308[3] == 1) {
        mDoAud_seStart(JA_SE_CM_BKM_BODY_UP, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
    switch (i_this->m302) {
    case -1:
        i_this->m336 = actor->shape_angle.y;
        i_this->m308[1] = 100;
        i_this->m308[2] = 0x28;
        if (i_this->m308[0] == 0) {
            i_this->m302 = 0;
            i_this->m304 = 0;
            anm_init(i_this, BMD_BCK_HANA_WAIT, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            mDoAud_seStart(JA_SE_CM_BKM_VINE_OUT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->m308[3] = 0x5a;
        }
        break;
    case 0:
        i_this->m940 = -0x4000;
        i_this->m302 = 1;
        i_this->m318 = actor->home.pos;
        i_this->m318.x = i_this->m318.x + cM_rndFX(500.0f);
        i_this->m318.z = i_this->m318.z + cM_rndFX(500.0f);
        local_3c = i_this->m318 - player->current.pos;
        fVar7 = std::sqrtf(local_3c.x * local_3c.x + local_3c.z * local_3c.z);
        if (fVar7 > REG0_F(11) + 1000.0f) {
            local_30.y = 0.0f;
            local_30.x = 0.0f;
            local_30.z = REG0_F(12) + 1300.0f;
            cMtx_YrotS(*calc_mtx, cM_atan2s(local_3c.x, local_3c.z));
            MtxPosition(&local_30, &local_3c);
            i_this->m318 = player->current.pos + local_3c;
        }
    case 1:
        cLib_addCalc2(&actor->speedF, i_this->m331 * 0.15f, 1.0f, 0.1f);
        local_30 = i_this->m318 - actor->current.pos;
        cLib_addCalcAngleS2(&actor->current.angle.y, cM_atan2s(local_30.x, local_30.z), 0x10, 0x800);
        fVar7 = std::sqrtf(local_30.x * local_30.x + local_30.z * local_30.z);
        if (fVar7 < 50.0f) {
            i_this->m302 = 2;
            i_this->m308[0] = (s16)(int)(cM_rndF(150.0f) + 150.0f);
        }
        break;
    case 2:
        i_this->m330 = 1;
        cLib_addCalc0(&actor->speedF, 1.0f, 0.1f);
        if (i_this->m308[0] == 0) {
            i_this->m302 = 0;
        }
        break;
    }
    if (i_this->m302 >= 0) {
        move1(i_this);
        if (i_this->m308[1] == 0) {
            i_this->m308[1] = (s16)(int)(cM_rndF(200.0f) + 100.0f);
            i_this->m336 = (s16)(int)cM_rndFX(32768.0f);
            i_this->m338 = 0.0f;
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m336, 0x20, i_this->m338);
        cLib_addCalc2(&i_this->m338, 64.0f, 1.0f, 1.0f);
        if (i_this->m308[2] == 0) {
            dVar6 = fopAcM_searchPlayerDistance(actor);
            if (dVar6 < 1300.0f) {
                i_this->m308[2] = (s16)(int)(cM_rndF(50.0f) + 30.0f);
                if (cM_rndF(1.0f) < l_HIO.m08) {
                    i_this->mMode = 1;
                    i_this->m302 = 0;
                }
            } else {
                i_this->m308[2] = (s16)(int)(cM_rndF(50.0f) + 30.0f);
                if (cM_rndF(1.0f) < l_HIO.m08) {
                    i_this->mMode = 2;
                    i_this->m302 = 0;
                }
            }
        }
    }
}

/* 00003910-000039A4       .text attack_1__FP9bmd_class */
void attack_1(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->m302) {
    case 0:
        i_this->m308[0] = 0x32;
        i_this->m302 = 1;
        i_this->m332 = 1;
        break;
    case 1:
        if (i_this->m308[0] == 0) {
            i_this->mMode = 0;
            i_this->m302 = 0;
        }
        break;
    }
    cLib_addCalc0(&actor->speedF, 1.0f, 0.1f);
    move1(i_this);
}

/* 000039A4-00003A78       .text attack_2__FP9bmd_class */
void attack_2(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->m302) {
    case 0:
        i_this->m302 = 1;
        i_this->m332 = 2;
        i_this->m334 = 10;
        anm_init(i_this, BMD_BCK_HANA_ATTACK, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        break;
    case 1:
        if (i_this->m334 == 0) {
            i_this->m332 = 0;
            i_this->mMode = 0;
            i_this->m302 = 0;
            anm_init(i_this, BMD_BCK_HANA_WAIT, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        break;
    }
    cLib_addCalc0(&actor->speedF, 1.0f, 0.1f);
    move1(i_this);
}

/* 00003A78-00003BDC       .text move__FP9bmd_class */
void move(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;

    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    i_this->m332 = 0;
    switch (i_this->mMode) {
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
        break;
    case 5:
        eat(i_this);
        break;
    case 10:
        start(i_this);
        break;
    case 0xb:
        end(i_this);
        break;
    }
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    if (i_this->mMode != 3) {
        fVar1 = 0.0f;
        if (0 < i_this->m331) {
            fVar1 = REG0_F(18) + (i_this->m331 * (REG0_F(17) + 2.5f) + 250.0f);
            if (i_this->mMode == 10) {
                fVar1 += 100.0f;
            }
        }
        cLib_addCalc2(&actor->current.pos.y, fVar1 + (actor->home.pos.y + i_this->m324), 0.1f, 5.0f);
        damage_check(i_this);
    } else {
        i_this->m324 = 0.0f;
    }
}

static u16 eff_name[] = {dPa_name::ID_SCENE_80EE, dPa_name::ID_SCENE_80EF, dPa_name::ID_SCENE_80F5};
static u16 eff_joint[] = {0x0008, 0x0009, 0x0004};

/* 00003BDC-00003D48       .text eff_cont__FP9bmd_class */
void eff_cont(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mA7C); i++) {
        if (i_this->mA7C[i] != NULL) {
            if (i >= 2) {
                i_this->mA7C[i]->setGlobalRTMatrix(i_this->m2C4->getModel()->getAnmMtx(eff_joint[i]));
            } else {
                i_this->mA7C[i]->setGlobalRTMatrix(i_this->m2C0->getModel()->getAnmMtx(eff_joint[i]));
            }
            if (i_this->mA88[i] != 0) {
                i_this->mA88[i]--;
                if (i_this->mA88[i] == 0) {
                    i_this->mA7C[i]->becomeInvalidEmitter();
                    i_this->mA7C[i] = NULL;
                }
            }
        } else if (i_this->mA88[i] != NULL) {
            i_this->mA7C[i] = dComIfGp_particle_set(eff_name[i], &actor->current.pos);
        }
    }
}

/* 00003D48-00003E38       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW* bgw, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    bmd_class* i_this = (bmd_class*)i_ac;
#if VERSION == VERSION_DEMO
    if (i_this->m304 == 3)
#else
    if (i_this->m304 == 3 && !dScnPly_ply_c::isPause())
#endif
    {
        cLib_addCalc2(&i_pt->current.pos.x, i_ac->current.pos.x, 1.0f, REG0_F(2) + 400.0f);
        cLib_addCalc2(&i_pt->current.pos.y, i_ac->current.pos.y, 1.0f, REG0_F(2) + 400.0f);
        cLib_addCalc2(&i_pt->current.pos.z, i_ac->current.pos.z, 1.0f, REG0_F(2) + 400.0f);
        i_pt->old.pos = i_pt->current.pos;
        if (fopAcM_GetName(i_pt) == PROC_PLAYER) {
            i_this->m942 = 5;
        }
    }
}

/* 00003E38-000054D4       .text demo_camera__FP9bmd_class */
void demo_camera(bmd_class* i_this) {
    /* Nonmatching - switch case, regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_44;
    cXyz local_50;
    cXyz local_a4;
    cXyz local_b0;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    switch (i_this->mB74) {
    case 0:
        break;
    case 1: {
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            i_this->mB76 = 0;
            i_this->mB78 = 0;
            return;
        }
        i_this->mB74++;
        camera_class* camera2 = dComIfGp_getCamera(0);
        i_this->mB7C = camera2->mLookat.mEye;
        i_this->mB88 = camera2->mLookat.mCenter;
        local_44 = player_actor->current.pos - i_this->mB7C;
        i_this->mB96 = cM_atan2s(local_44.x, local_44.z);
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mB9C = 55.0f;
        player->changeOriginalDemo();
        // fallthrough
    }
    case 2:
        cMtx_YrotS(*calc_mtx, (int)i_this->mB96);
        if ((int)i_this->mB78 < REG0_S(0) + 0x55) {
            cLib_addCalc2(&i_this->mB88.x, actor->current.pos.x, 0.1f, 200.0f);
            cLib_addCalc2(&i_this->mB88.y, player_actor->current.pos.y + 300.0f + REG0_F(5), 0.2f, 200.0f);
            cLib_addCalc2(&i_this->mB88.z, actor->current.pos.z, 0.2f, 200.0f);
            local_44.x = 0.0f;
            local_44.y = REG0_F(7) + 100.0f;
            local_44.z = REG0_F(6) - 1100.0f;
            MtxPosition(&local_44, &local_50);
            cLib_addCalc2(&i_this->mB7C.x, actor->current.pos.x + local_50.x, 0.1f, 200.0f);
            cLib_addCalc2(&i_this->mB7C.y, player_actor->current.pos.y + local_50.y, 0.1f, 200.0f);
            cLib_addCalc2(&i_this->mB7C.z, actor->current.pos.z + local_50.z, 0.1f, 200.0f);
        } else if ((int)i_this->mB78 < REG0_S(1) + 100) {
            cLib_addCalc2(&i_this->mB88.y, actor->current.pos.y + 1200.0f + REG0_F(5), 0.2f, REG0_F(6) + 100.0f);
        } else {
            cLib_addCalc2(&i_this->mB88.x, player_actor->current.pos.x, 0.3f, 300.0f);
            cLib_addCalc2(&i_this->mB88.y, player_actor->current.pos.y + 70.0f + REG0_F(5), 0.3f, 300.0f);
            cLib_addCalc2(&i_this->mB88.z, player_actor->current.pos.z, 0.3f, 300.0f);
        }
        break;
    case 5:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            i_this->mB76 = 0;
            i_this->mB78 = 0;
            break;
        }
        i_this->mB74 = i_this->mB74 + 1;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mB9C = 60.0f;
        player->changeOriginalDemo();
        // Fall-through
    case 6:
        i_this->mB7C.x = 74.0f;
        i_this->mB7C.y = 283.0f;
        i_this->mB7C.z = 745.0f;
        i_this->mB88.x = -87.0f;
        i_this->mB88.y = 58.0f;
        i_this->mB88.z = 102.0f;
        local_50.x = REG0_F(7) + 61.0f;
        local_50.y = 0.0f;
        local_50.z = REG0_F(8) + 492.0f;
        player->setPlayerPosAndAngle(&local_50, -0x75fb);
        if (i_this->mB78 == 0x1e) {
            i_this->mB78 = 0;
            i_this->mB74++;
            i_this->m2DC = 3;
        }
        break;
    case 7:
        i_this->mB7C.x = -47.0f;
        i_this->mB7C.y = 115.0f;
        i_this->mB7C.z = 263.0f;
        i_this->mB88.x = -199.0f;
        i_this->mB88.y = -89.0f;
        i_this->mB88.z = -349.0f;
        if (i_this->mB78 == 0x1e) {
            i_this->mB78 = 0;
            i_this->mB74++;
        }
        break;
    case 8:
        i_this->mB7C.x = 2.0f;
        i_this->mB7C.y = 75.0f;
        i_this->mB7C.z = 403.0f;
        i_this->mB88.x = 401.0f;
        i_this->mB88.y = 228.0f;
        i_this->mB88.z = 957.0f;
        if (i_this->mB78 == 5) {
            player->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
            player->voiceStart(0x2e);
        }
        if (i_this->mB78 != 0x1e) {
            break;
        }
        i_this->mB78 = 0;
        i_this->mB74++;
        i_this->mB7C.x = -47.0f;
        i_this->mB7C.y = 115.0f;
        i_this->mB7C.z = 263.0f;
        i_this->mB88 = actor->eyePos;
        i_this->mB88.y += REG0_F(11) + 30.0f;
        i_this->m2DC = 4;
        // Fall-through
    case 9:
        cLib_addCalc2(&i_this->mB88.y, actor->eyePos.y + 30.0f, 0.2f, REG0_F(4) + 5.0f);
        if (i_this->mB78 == 0x1e) {
            i_this->m2C0->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_NEW_SDEMO1), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
            mDoAud_seStart(JA_SE_CM_BKM_CORE_ENTER, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            fopAcM_monsSeStart(actor, JA_SE_CV_BKM_ENTER, 0);
        }
        if (i_this->mB78 > 0x1e) {
            if (i_this->m2C0->isStop()) {
                i_this->mB78 = 0;
                i_this->mB74++;
                i_this->m2C0->setAnm(
                    (J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_NEW_SDEMO2), J3DFrameCtrl::EMode_LOOP, 1.0f, 1.0f, 0.0f, -1.0f, NULL
                );
            }
        }
        break;
    case 10:
        i_this->mB7C.x = 2.0f;
        i_this->mB7C.y = 75.0f;
        i_this->mB7C.z = 403.0f;
        i_this->mB88.x = 401.0f;
        i_this->mB88.y = 228.0f;
        i_this->mB88.z = 957.0f;
        if (i_this->mB78 == 5) {
            player->changeDemoMode(daPy_demo_c::DEMO_S_SURP_e);
            player->voiceStart(0x1d);
        }
        if (i_this->mB78 != 0x19) {
            break;
        }
        i_this->mB78 = 0;
        i_this->mB74++;
        i_this->mB88 = actor->eyePos;
        i_this->mB88.y += REG0_F(11) + 30.0f;
        // Fall-through
    case 11:
        i_this->mB7C.x = -139.0f;
        i_this->mB7C.y = 125.0f;
        i_this->mB7C.z = 475.0f;
        i_this->mB88.x = -93.0f;
        i_this->mB88.y = 164.0f;
        i_this->mB88.z = 104.0f;
        if (i_this->mB78 == 0x1e) {
            i_this->m2C0->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_NEW_SDEMO3), J3DFrameCtrl::EMode_NONE, (REG0_F(16) + 4.0f), 1.0f, 0.0f, -1.0f, NULL
            );
        }
        if (0x1b < i_this->mB78) {
            if (i_this->m2C0->isStop()) {
                i_this->mB78 = 0;
                i_this->mB74++;
                i_this->m2DC = 0;
                mk_voice_set(i_this, 0x48c6);
                i_this->m2C0->setAnm(
                    (J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_NEW_SDEMO4), J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL
                );
                i_this->mB88 = actor->eyePos;
                i_this->mB88.y += REG0_F(15) + 60.0f;
            }
        }
        break;
    case 12:
        if ((i_this->mB78 >= 0x14) && (i_this->mB78 <= 0x28)) {
            i_this->mB7C.x = 2.0f;
            i_this->mB7C.y = 75.0f;
            i_this->mB7C.z = 403.0f;
            i_this->mB88.x = 401.0f;
            i_this->mB88.y = 228.0f;
            i_this->mB88.z = 957.0f;
            if (i_this->mB78 == 0x14) {
                player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
                player->voiceStart(0x31);
            }
            i_this->m2C0->setPlaySpeed(0.0f);
            if (i_this->mB78 == 0x28) {
                i_this->mB7C.x = -139.0f;
                i_this->mB7C.y = 125.0f;
                i_this->mB7C.z = 475.0f;
                i_this->mB88 = actor->eyePos;
                i_this->mB88.y += REG0_F(15) + 60.0f;
                i_this->m2C0->setPlaySpeed(1.0f);
            }
        } else {
            cLib_addCalc2(&i_this->mB9C, REG0_F(12) + 35.0f, 0.2f, REG0_F(13) + 1.0f);
            cLib_addCalc2(&i_this->mB88.x, actor->eyePos.x, 0.2f, REG0_F(4) + 10.0f);
            cLib_addCalc2(&i_this->mB88.y, actor->eyePos.y + 10.0f + REG0_F(14), 0.2f, REG0_F(4) + 10.0f);
            cLib_addCalc2(&i_this->mB88.z, actor->eyePos.z, 0.2f, REG0_F(4) + 10.0f);
            if (i_this->m2C0->isStop()) {
                i_this->mB78 = REG0_S(6);
                i_this->m302 = 3;
                i_this->m2C0->setAnm(
                    (J3DAnmTransform*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_START3), J3DFrameCtrl::EMode_LOOP, 1.0f, 1.0f, 0.0f, -1.0f, NULL
                );
                i_this->m308[0] = 10;
                fopAcM_monsSeStart(actor, JA_SE_CV_BKM_LAUGH, 0);
                i_this->mB74 = 0xf;
                i_this->mB9C = REG0_F(8) + 55.0f;
                i_this->mB76 = REG0_S(7) + 0x6e;
                i_this->mB88 = actor->current.pos;
                i_this->mB88.y = REG0_F(3) + 500.0f;
                cMtx_YrotS(*calc_mtx, (int)actor->shape_angle.y);
                local_44.x = REG0_F(5) + 950.0f;
                local_44.y = REG0_F(6) + 150.0f;
                local_44.z = REG0_F(7) + 920.0f;
                MtxPosition(&local_44, &i_this->mB7C);
                i_this->mBA0 = 0.0f;
            }
        }
        break;
    case 15:
        if ((int)i_this->mB78 == REG0_S(6) + 0x37) {
            player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
        }
        if ((int)i_this->mB78 == REG0_S(7) + 100) {
            player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        }
        if (i_this->mB78 >= REG0_S(5) + 0xd2) {
            if (i_this->mB78 <= REG0_S(6) + 0x159) {
                cLib_addCalc2(&i_this->mB9C, REG0_F(6) + 40.0f, 0.05f, REG0_F(7) + 0.1f);
            } else {
                cLib_addCalc2(&i_this->mB9C, REG0_F(8) + 70.0f, 0.2f, REG0_F(9) + 2.0f);
            }
        }
        if (i_this->mB78 >= REG0_S(5) + 0x96) {
            cLib_addCalc2(&i_this->mB88.y, REG0_F(3) + 450.0f + 150.0f + 50.0f + 100.0f, 0.05f, i_this->mBA0 * 4.5f);
            cLib_addCalc2(&i_this->mB7C.y, (REG0_F(4) + 50.0f) - 50.0f, 0.05f, i_this->mBA0 * 3.0f);
            cLib_addCalc2(&i_this->mBA0, 1.0f, 1.0f, REG0_F(10) + 0.01f);
        }
        if (i_this->mB76 == 0x24e) {
            i_this->mB74 = 0x96;
            dComIfGp_event_reset();
            i_this->m332 = 7;
            i_this->mMode = 0;
            i_this->m302 = -1;
            i_this->m308[0] = 0x3c;
            i_this->mBE0 = 0;
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_BKM);
            } else {
                mDoAud_bgmStart(JA_BGM_KINDAN_BOSS);
            }
            i_this->mB71 = 1;
            g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossDemo();
        }
        break;
    case 100: {
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            i_this->mB76 = 0;
            i_this->mB78 = 0;
            break;
        }
        i_this->mB74++;
        camera_class* camera2 = dComIfGp_getCamera(0);
        i_this->mB7C = camera2->mLookat.mEye;
        i_this->mB88 = camera2->mLookat.mCenter;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->mB9C = 55.0f;
        player->changeOriginalDemo();
        // Fall-through
    }
    case 101:
        if ((i_this->mB78 >= 0x140) && (cLib_addCalc2(&i_this->mB9C, REG0_F(8) + 85.0f, 0.2f, 1.0f), i_this->mB78 == 0x140)) {
            i_this->m2DC = 5;
        }
        if (i_this->m924.y < i_this->m328 + 10.0f) {
            cLib_addCalc2(&i_this->mB88.x, actor->eyePos.x, 0.2f, 200.0f);
            cLib_addCalc2(&i_this->mB88.y, actor->eyePos.y + 20.0f + REG0_F(5), 0.5f, 200.0f);
            cLib_addCalc2(&i_this->mB88.z, actor->eyePos.z, 0.2f, 200.0f);
        } else {
            cLib_addCalc2(&i_this->mB88.x, i_this->m924.x, 0.2f, 200.0f);
            cLib_addCalc2(&i_this->mB88.y, i_this->m924.y, 0.5f, 200.0f);
            cLib_addCalc2(&i_this->mB88.z, i_this->m924.z, 0.2f, 200.0f);
        }
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y + (REG0_S(4) + 3000));
        local_44.x = 0.0f;
        local_44.y = REG0_F(7) + 70.0f;
        local_44.z = REG0_F(6) + 500.0f + 300.0f + 200.0f;
        MtxPosition(&local_44, &local_50);
        local_50 += actor->current.pos;
        if (local_50.y > i_this->m328 + 300.0f + REG0_F(8)) {
            local_50.y = i_this->m328 + 300.0f + REG0_F(8);
        }
        cLib_addCalc2(&i_this->mB7C.x, local_50.x, 0.5f, 200.0f);
        cLib_addCalc2(&i_this->mB7C.y, local_50.y, 0.8f, 200.0f);
        cLib_addCalc2(&i_this->mB7C.z, local_50.z, 0.5f, 200.0f);
        if (0x3c < i_this->mB76) {
            cMtx_YrotS(*calc_mtx, actor->shape_angle.y + (REG0_S(7) + 3000));
            local_44.x = REG0_F(11) + 200.0f;
            local_44.y = 0.0f;
            local_44.z = 0.0f;
            MtxPosition(&local_44, &local_50);
            local_50 += actor->current.pos;
            player->setPlayerPosAndAngle(&local_50, actor->shape_angle.y + (REG0_S(6) + 3000));
        }
        local_44.x = 0.0f;
        local_44.y = 0.0f;
        local_44.z = (REG0_F(6) + 500.0f + 300.0f + 200.0f) - 150.0f;
        MtxPosition(&local_44, &i_this->m2E0);
        i_this->m2E0 += actor->current.pos;
        i_this->m2FA = actor->shape_angle.y + (REG0_S(4) + 3000);
        break;
    case 102: {
        i_this->mB9C = REG0_F(8) + 55.0f;
        i_this->mB96 = actor->shape_angle.y + REG0_S(2);
        i_this->mB94 = -8000;
        i_this->mBA4 = 1500.0f;
        i_this->mBA0 = 0.0f;
        i_this->mB74 = 0x67;
        i_this->mB70 = 1;
        csXyz cStack_b8(0, 0, 0);
        cStack_b8.y = actor->shape_angle.y + 0x8BB8;
        fopAcM_create(PROC_NPC_CB1, 0, &i_this->m2E0, fopAcM_GetRoomNo(actor), &cStack_b8);
        i_this->m2DC = 0;
        // Fall-through
    }
    case 103: {
        s16 iVar6 = i_this->mBA0 * 22384.0f;
        cLib_addCalcAngleS2(&i_this->mB96, (s16)(actor->shape_angle.y + REG0_S(2)) + 0x5770, 0x10, iVar6);
        s16 r5 = i_this->mBA0 * 3000.0f;
        cLib_addCalcAngleS2(&i_this->mB94, -5000, 0x10, r5);
        cLib_addCalc2(&i_this->mBA4, 500.0f, 0.0625f, i_this->mBA0 * 1000.0f);
        cLib_addCalc2(&i_this->mBA0, REG0_F(10) + 0.0048f, 0.1f, 4.8e-05f);
        cMtx_YrotS(*calc_mtx, (int)i_this->mB96);
        cMtx_XrotM(*calc_mtx, i_this->mB94);
        local_44.y = 0.0f;
        local_44.x = 0.0f;
        local_44.z = i_this->mBA4;
        MtxPosition(&local_44, &local_50);
        i_this->mB7C = actor->current.pos + local_50;
        i_this->mB88 = actor->current.pos;
        i_this->mB88.y += REG0_S(3) + 100.0f;
        if (i_this->mB76 == 800) {
            i_this->mB74 = 0x96;
            dComIfGp_event_reset();
            i_this->m314 = 0;
            player->cancelOriginalDemo();
        }
        break;
    }
    case 150:
        i_this->mB74 = 0;
        camera->mCamera.Reset(i_this->mB88, i_this->mB7C);
        camera->mCamera.Start();
        camera->mCamera.SetTrimSize(0);
        break;
    }
    if (i_this->mB74 != 0) {
        f32 f1 = i_this->mBA8 * cM_ssin(i_this->mB78 * 0x3300);
        f32 f2 = i_this->mBA8 * cM_scos(i_this->mB78 * 0x3000);
        local_a4.x = i_this->mB7C.x + f1;
        local_a4.y = i_this->mB7C.y + f2;
        local_a4.z = i_this->mB7C.z;
        local_b0.x = i_this->mB88.x + f1;
        local_b0.y = i_this->mB88.y + f2;
        local_b0.z = i_this->mB88.z;
        s16 iVar6 = i_this->mBA8 * cM_scos(i_this->m2FE * 0x1c00) * 7.5f;
        camera->mCamera.Set(local_b0, local_a4, iVar6, i_this->mB9C);
        cLib_addCalc0(&i_this->mBA8, 1.0f, (REG0_F(16) + 2.0f));
        JUTReport(0x1e, 0x1ae, "K MAIN COUNT  %d", (int)i_this->mB76);
        JUTReport(0x19a, 0x1ae, "K SUB  COUNT  %d", (int)i_this->mB78);
        i_this->mB78++;
        i_this->mB76++;
    }
}

/* 000054D4-000055EC       .text bmd_kankyo__FP9bmd_class */
void bmd_kankyo(bmd_class* i_this) {
    dKy_custom_timeset(l_HIO.m0C);
    switch (i_this->mBE0) {
    case 0:
        dKy_custom_colset(0, 6, i_this->mBDC);
        cLib_addCalc0(&i_this->mBDC, 1.0f, 0.025f);
        i_this->m2D8 = (1.0f - i_this->mBDC) * 11.0f;
        break;
    case 1:
        dKy_custom_colset(0, 4, i_this->mBDC);
        cLib_addCalc0(&i_this->mBDC, 1.0f, 0.025f);
        i_this->m2D8 = (1.0f - i_this->mBDC) * 11.0f;
        break;
    case 2:
        dKy_custom_colset(5, 6, i_this->mBDC);
        cLib_addCalc0(&i_this->mBDC, 1.0f, 0.02f);
        i_this->m2D8 = i_this->mBDC * 11.0f;
        break;
    }
}

/* 000055EC-00005BF4       .text daBmd_Execute__FP9bmd_class */
static BOOL daBmd_Execute(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    cXyz local_88;

#if VERSION > VERSION_DEMO
    if (dComIfGp_getStartStageName()[0] == 'X') {
        i_this->mB72 = 0x32;
    }
#endif
    i_this->m2FE++;
    i_this->m330 = 0;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m308); i++) {
        if (i_this->m308[i] != 0) {
            i_this->m308[i]--;
        }
    }
    if (i_this->m310 != 0) {
        i_this->m310--;
    }
    if (i_this->m314 != 0) {
        i_this->m314--;
    }
    if (i_this->m312 != 0) {
        i_this->m312--;
    }
    if (i_this->m334 != 0) {
        i_this->m334--;
    }
    move(i_this);
    core_move(i_this);
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::now, *calc_mtx);
    if ((0 < i_this->m940) || (i_this->m314 != 0)) {
        MtxScale(0.0f, 0.0f, 0.0f, true);
    }
    MTXCopy(*calc_mtx, i_this->mA34);
    i_this->pm_bgw[5]->Move();
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m944); i++) {
        MTXCopy(mDoMtx_stack_c::now, *calc_mtx);
        cMtx_YrotM(*calc_mtx, (i * 13107.2f) + REG0_F(11));
        MtxTrans((REG0_F(4) - 200.0f), 0.0f, 0.0f, true);
        cMtx_ZrotM(*calc_mtx, i_this->m940);
        MtxTrans(-(REG0_F(4) - 200.0f), (15.0f + REG0_F(5)), REG0_F(6), true);
        if ((0 < i_this->m940) || (i_this->m314 != 0)) {
            MtxScale(0.0f, 0.0f, 0.0f, true);
        }
        MTXCopy(*calc_mtx, i_this->m944[i]);
        i_this->pm_bgw[i]->Move();
    }
    i_this->mpMorf->play(&actor->eyePos, 0, 0);
    i_this->mpMorf->calc();
    if (i_this->mB70 != 0) {
        i_this->mpBrkAnm->play();
        i_this->mpBtkAnm->play();
    }
    local_88 = actor->current.pos;
    local_88.y += REG0_F(7) + 200.0f;
    if (i_this->m304 != 0) {
        local_88.y += 10000.0f;
    }
    i_this->mBodySph.SetC(local_88);
    i_this->mBodySph.SetR(REG0_F(8) + 300.0f);
    dComIfG_Ccsp()->Set(&i_this->mBodySph);
    if (i_this->m904 != 0) {
        i_this->m904--;
        local_88 = actor->current.pos;
        local_88.y = 0.0f;
        cLib_addCalc2(&i_this->m908, REG0_F(4) + 800.0f, 1.0f, REG0_F(5) + 50.0f);
    } else {
        i_this->m908 = 0.0f;
        local_88.x = -20000.0f;
        local_88.y = 10000.0f;
        local_88.z = -10000.0f;
    }
    i_this->mCoCyl.SetC(local_88);
    i_this->mCoCyl.SetR(i_this->m908);
    i_this->mCoCyl.SetH(REG0_F(3) + 3000.0f);
    dComIfG_Ccsp()->Set(&i_this->mCoCyl);
    demo_camera(i_this);
    bmd_kankyo(i_this);
    eff_cont(i_this);
    i_this->mWindInfluence.mPos = actor->current.pos;
    i_this->mWindInfluence.mDir.x = 0.0f;
    i_this->mWindInfluence.mDir.y = 1.0f;
    i_this->mWindInfluence.mDir.z = 0.0f;
    cLib_addCalc0(&i_this->mBD8, 1.0f, 50.0f);
    i_this->mWindInfluence.mRadius = 2000.0f - i_this->mBD8;
    if (i_this->mBD8 > 1.0f) {
        i_this->mWindInfluence.mStrength = 1.0f;
        fVar2 = i_this->mWindInfluence.mRadius;
        if (fVar2 > 1500.0f) {
            i_this->mWindInfluence.mStrength = (2000.0f - fVar2) * 0.002f;
        }
    } else {
        i_this->mWindInfluence.mStrength = 0.0f;
    }
    mk_move(i_this);
    if (i_this->mB71 != 0) {
        if (actor->current.pos.y > 100.0f) {
            dCam_getBody()->SetTypeForce("Boss02", NULL);
        } else if (i_this->mB71 == 2) {
            dComIfGp_getCamera(0)->mCamera.SetTypeForce("Field", NULL);
            i_this->mB71 = 1;
        } else {
            dComIfGp_getCamera(0)->mCamera.SetTypeForce("Dungeon", NULL);
        }
    }
    mDoMtx_stack_c::transS(0.0f, 0.1f, 0.0f);
    i_this->m2D0->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->m2D4->setFrame(i_this->m2D8);
    return TRUE;
}

/* 00005BF4-00005BFC       .text daBmd_IsDelete__FP9bmd_class */
static BOOL daBmd_IsDelete(bmd_class*) {
    return TRUE;
}

/* 00005BFC-00005CF4       .text daBmd_Delete__FP9bmd_class */
static BOOL daBmd_Delete(bmd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    dComIfG_resDeleteDemo(&i_this->mPhs, "Bmd");
    mDoHIO_deleteChild(l_HIO.mNo);
    if (actor->heap != NULL) {
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->pm_bgw); i++) {
            if (i_this->pm_bgw[i] != NULL) {
                dComIfG_Bgsp()->Release(i_this->pm_bgw[i]);
            }
        }
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mA90); i++) {
        i_this->mA90[i].remove();
    }
    dKyw_pntwind_cut(&i_this->mWindInfluence);
    mDoAud_seDeleteObject(&i_this->m2E0);
    return TRUE;
}

/* 00005CF4-000064C0       .text useHeapInit__FP9bmd_class */
BOOL useHeapInit(bmd_class* i_this) {
    J3DModelData* pJVar2;
    mDoExt_McaMorf* morf;
    J3DAnmTevRegKey* pJVar5;
    int iVar6;
    J3DAnmTextureSRTKey* pAnm;
    dBgW* bgw;
    cBgD_t* pcVar9;
    J3DModel* pJVar13;

    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BMD_BKM),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmd", BMD_BCK_HANA_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->mpMorf = morf;
    pJVar13 = i_this->mpMorf->getModel();
    if (pJVar13 == NULL) {
        return FALSE;
    } else if (i_this->mpMorf == NULL) {
        return FALSE;
    }
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    pJVar5 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bmd", BMD_BRK_BKM);
    iVar6 = i_this->mpBrkAnm->init(pJVar13->getModelData(), pJVar5, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar6 == 0) {
        return FALSE;
    }
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL) {
        return FALSE;
    }
    pAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bmd", BMD_BTK_BKM);
    iVar6 = i_this->mpBtkAnm->init(pJVar13->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar6 == 0) {
        return FALSE;
    }
    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BMD_BKM_COA),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m2C0 = morf;
    pJVar13 = i_this->m2C0->getModel();
    if (pJVar13 == NULL) {
        return FALSE;
    }
    pJVar13->setUserArea((u32)i_this);
    for (u16 uVar16 = 0; uVar16 < pJVar13->getModelData()->getJointNum(); uVar16++) {
        pJVar13->getModelData()->getJointNodePointer(uVar16)->setCallBack(core_nodeCallBack);
    }
    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BMD_BKM_COA_DEADMODEL),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmd", BMD_BCK_COA_DEAD1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m2C4 = morf;
    if (i_this->m2C4->getModel() == NULL) {
        return FALSE;
    }
    bgw = new dBgW();
    i_this->pm_bgw[5] = bgw;
    JUT_ASSERT(0xf41, i_this->pm_bgw[5] != 0);
    if (i_this->pm_bgw[5] == NULL) {
        return FALSE;
    }
    pcVar9 = (cBgD_t*)dComIfG_getObjectRes("Bmd", BMD_DZB_COLL1);
    i_this->pm_bgw[5]->Set(pcVar9, dBgW::MOVE_BG_e, &i_this->mA34);
    i_this->pm_bgw[5]->SetCrrFunc(dBgS_MoveBGProc_Typical);
    i_this->pm_bgw[5]->SetRideCallback(ride_call_back);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m944); i++) {
        bgw = new dBgW();
        i_this->pm_bgw[i] = bgw;
        JUT_ASSERT(0xf53, i_this->pm_bgw[i] != 0);
        if (i_this->pm_bgw[i] == 0) {
            return FALSE;
        }
        pcVar9 = (cBgD_t*)dComIfG_getObjectRes("Bmd", BMD_DZB_COLL2);
        i_this->pm_bgw[i]->Set(pcVar9, dBgW::MOVE_BG_e, &i_this->m944[i]);
        i_this->pm_bgw[i]->SetCrrFunc(dBgS_MoveBGProc_Typical);
        i_this->pm_bgw[i]->SetRideCallback(ride_call_back);
    }
    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BMD_CB),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmd", BMD_BCK_CALL_01),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m2C8 = morf;
    if (i_this->m2C8->getModel() == NULL) {
        return FALSE;
    }
    pJVar2 = (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BMD_CB_FACE);
    pJVar13 = mDoExt_J3DModel__create(pJVar2, 0, 0x11020203);
    i_this->m2CC = pJVar13;
    if (i_this->m2CC == NULL) {
        return FALSE;
    }
    pJVar2 = (J3DModelData*)dComIfG_getObjectRes("Bmd", BMD_BDL_R00_EF);
    pJVar13 = mDoExt_J3DModel__create(pJVar2, 0, 0x11020203);
    i_this->m2D0 = pJVar13;
    if (i_this->m2D0 == NULL) {
        return FALSE;
    }
    i_this->m2D4 = new mDoExt_brkAnm();
    if (i_this->m2D4 == NULL) {
        return FALSE;
    }
    pJVar5 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bmd", BMD_BRK_R00_EF);
    iVar6 = i_this->m2D4->init(pJVar2, pJVar5, true, J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, false, 0);
    if (iVar6 == 0) {
        return FALSE;
    }
    return TRUE;
}

/* 00006508-00006528       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c* a_this) {
    bmd_class* i_this = (bmd_class*)a_this;
    return useHeapInit(i_this);
}

/* 00006528-00006908       .text daBmd_Create__FP10fopAc_ac_c */
static cPhs_State daBmd_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph body_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 300.0f,
        }},
    };
    static dCcD_SrcSph core_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcCyl co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Nrm_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
            /* Height */ 400.0f,
        }},
    };
    cPhs_State res;
    cXyz local_30;

    bmd_class* i_this = (bmd_class*)a_this;
    fopAcM_ct(a_this, bmd_class);
    res = dComIfG_resLoad(&i_this->mPhs, "Bmd");
#if VERSION == VERSION_DEMO
    if (res == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    }
#endif
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mA90); i++) {
        i_this->mA90[i].setFollowOff();
    }
    if (dComIfGs_isStageBossEnemy() && (dComIfGp_getStartStageName()[0] != 'X')) {
        if ((!dComIfGs_checkGetItem(dItem_PEARL_FARORE_e)) || (REG0_S(6) != 0)) {
            local_30.x = 100.0f;
            local_30.y = 0.0f;
            local_30.z = 800.0f;
            fopAcM_create(PROC_NPC_CB1, 0, &local_30, fopAcM_GetRoomNo(a_this));
        }
        res = cPhs_ERROR_e;
    } else if (!fopAcM_entrySolidHeap(a_this, solidHeapCB, 0x96000)) {
        res = cPhs_ERROR_e;
    } else {
#if VERSION > VERSION_DEMO
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->pm_bgw); i++) {
            if (dComIfG_Bgsp()->Regist(i_this->pm_bgw[i], a_this) != false) {
                return cPhs_ERROR_e;
            }
        }
#endif
        l_HIO.mNo = mDoHIO_createChild("森ボス", &l_HIO); // Forest Boss
        a_this->health = 0xf;
        a_this->max_health = 0xf;
        for (s32 i = 0; i < 20; i++) {
            fopAcM_prm_class* params = fopAcM_CreateAppend();
            params->base.parameters = i;
            fopAcM_create(PROC_BMDHAND, 0, params);
        }
        for (s32 i = 0; i < 8; i++) {
            fopAcM_prm_class* params = fopAcM_CreateAppend();
            params->base.parameters = i;
            fopAcM_create(PROC_BMDFOOT, 0, params);
        }
        a_this->home.pos.y += REG0_F(2) + 20.0f;
        a_this->current.pos.y = a_this->home.pos.y;
        i_this->m328 = a_this->current.pos.y;
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcchCir.SetWall(500.0f, 1000.0f);
        i_this->mStts.Init(0xff, 0, a_this);
        i_this->mBodySph.SetStts(&i_this->mStts);
        i_this->mBodySph.Set(body_sph_src);
        i_this->mCoreSph.SetStts(&i_this->mStts);
        i_this->mCoreSph.Set(core_sph_src);
        i_this->mCoCyl.SetStts(&i_this->mStts);
        i_this->mCoCyl.Set(co_cyl_src);
        i_this->m308[2] = 200;
        if (!dComIfGs_isStageBossDemo() && (dComIfGp_getStartStageName()[0] != 'X')) {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0480);
            i_this->mMode = 10;
            i_this->mBE0 = 1;
            i_this->mBDC = 1.0f;
        } else {
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_BKM);
            } else {
                mDoAud_bgmStart(JA_BGM_KINDAN_BOSS);
            }
            i_this->mB71 = 1;
        }
        dKyw_pntwind_set(&i_this->mWindInfluence);
        a_this->attention_info.distances[2] = 4;
        daBmd_Execute(i_this);
        res = cPhs_COMPLEATE_e;
    }
    return res;
}

static actor_method_class l_daBmd_Method = {
    (process_method_func)daBmd_Create,
    (process_method_func)daBmd_Delete,
    (process_method_func)daBmd_Execute,
    (process_method_func)daBmd_IsDelete,
    (process_method_func)daBmd_Draw,
};

actor_process_profile_definition g_profile_BMD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmd_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BMD,
    /* Actor SubMtd */ &l_daBmd_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
