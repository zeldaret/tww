/**
 * d_a_gnd.cpp
 * Boss - Ganondorf / ガノンＤ (Ganon D)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_gnd.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_pz.h"
#include "d/d_meter.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_gnd.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/JUtility/JUTReport.h"

class daGnd_HIO_c : public JORReflexible {
public:
    daGnd_HIO_c();
    virtual ~daGnd_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ u8 m10;
    /* 0x11 */ u8 m11;
    /* 0x12 */ u8 m12;
    /* 0x13 */ u8 m13[0x14 - 0x13];
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ u8 m44;
    /* 0x45 */ u8 m45;
    /* 0x46 */ u8 m46;
    /* 0x47 */ u8 m47[0x48 - 0x47];
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ f32 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
    /* 0x60 */ f32 m60;
    /* 0x64 */ f32 m64;
    /* 0x68 */ s16 m68;
    /* 0x6A */ s16 m6A;
    /* 0x6C */ s16 m6C;
    /* 0x6E */ s16 m6E;
    /* 0x70 */ s16 m70;
    /* 0x72 */ s16 m72;
    /* 0x74 */ s16 m74;
    /* 0x76 */ s16 m76;
    /* 0x78 */ f32 m78;
    /* 0x7C */ s16 m7C;
    /* 0x7E */ s16 m7E;
    /* 0x80 */ s16 m80;
    /* 0x82 */ s16 m82;
    /* 0x84 */ s16 m84;
    /* 0x86 */ s16 m86;
    /* 0x88 */ u8 m88;
    /* 0x89 */ u8 m89;
};

/* 000000EC-0000023C       .text __ct__11daGnd_HIO_cFv */
daGnd_HIO_c::daGnd_HIO_c() {
    mNo = -1;
    m05 = 0;
    m06 = 0;
    m07 = 1;
    m08 = 45.0f;
    m0C = 1.0f;
    m10 = 0;
    m11 = 0;
    m12 = 1;
    m14 = 5.0f;
    m18 = 629.0f;
    m1C = 1200.0f;
    m20 = 25.0f;
    m24 = 11.0f;
    m28 = -0.5f;
    m2C = 100.0f;
    m30 = -30.0f;
    m34 = 20.0f;
    m38 = -2.0f;
    m3C = 630.0f;
    m40 = 400.0f;
    m44 = 0;
    m45 = 1;
    m46 = 1;
    m48 = 35.0f;
    m4C = 0.0f;
    m50 = 5.0f;
    m54 = 15.0f;
    m58 = 0.0f;
    m5C = 30.0f;
    m60 = -2.0f;
    m64 = 8.0f;
    m68 = 0x1e;
    m6A = 0x1e;
    m6C = 0;
    m6E = 0xf;
    m70 = 10;
    m72 = 0;
    m74 = 10;
    m76 = 10;
    m78 = 600.0f;
    m7C = 10;
    m7E = 1;
    m80 = 0x1e;
    m82 = 3;
    m84 = 6;
    m86 = 0x46;
    m88 = 0;
    m89 = 0;
}

static cXyz non_pos(-20000.0f, -20000.0f, -20000.0f);
static bool hio_set;
static daGnd_HIO_c l_HIO;

/* 0000023C-000003CC       .text j_demo__FP9gnd_class */
u8 j_demo(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    dDemo_actor_c* demo_actor;
    J3DAnmTexPattern* pJVar1;
    J3DAnmTextureSRTKey* pAnm;
    J3DAnmTevRegKey* pJVar2;

    if (actor->demoActorID == 0) {
        if (i_this->m15B0 != 0) {
            i_this->m15B0 = 0;
        }
    } else {
        i_this->m15B0 = 1;
        demo_actor = dComIfGp_demo_getActor(actor->demoActorID);
        pJVar1 = (J3DAnmTexPattern*)demo_actor->getP_BtpData("Gnd");
        if (pJVar1 != NULL) {
            i_this->m02C4->init(i_this->mpMorf->getModel()->getModelData(), pJVar1, 1, 0, 1.0f, 0, -1, true, 0);
        }
        pAnm = (J3DAnmTextureSRTKey*)demo_actor->getP_BtkData("Gnd");
        if (pAnm != NULL) {
            i_this->m02BC->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
        }
        pJVar2 = (J3DAnmTevRegKey*)demo_actor->getP_BrkData("Gnd");
        if (pJVar2 != NULL) {
            i_this->m02C0->init(i_this->mpMorf->getModel()->getModelData(), pJVar2, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
        }
        dDemo_setDemoData(
            actor,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            i_this->mpMorf,
            "Gnd"
        );
    }
    return i_this->m15B0;
}

/* 000003CC-000003EC       .text checkGround__FP9gnd_classf */
s32 checkGround(gnd_class* i_this, f32 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    return actor->current.pos.y < param_2 + 1.0f;
}

/* 000003EC-00000510       .text setRipple__FP9gnd_class */
void setRipple(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (checkGround(i_this, 0.0f)) {
        if ((i_this->mAcch.ChkGroundHit()) && (dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_WATER_e)) {
            if (i_this->m15B4.getEmitter() == NULL) {
                static cXyz ripple_scale(1.0f, 1.0f, 1.0f);
                dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &actor->current.pos, NULL, &ripple_scale, 0xff, &i_this->m15B4);
                if (i_this->m15B4.getEmitter() != NULL) {
                    i_this->m15B4.setRate(0.0f);
                }
            }
        }
    } else {
        i_this->m15B4.remove();
    }
}

static daPz_c* pz;
static cXyz f_ctr[] = {
    cXyz(-34.5f, 129.7f, -26.3f), cXyz(-37.9f, 202.6f, -77.5f), cXyz(-11.5f, 446.0f, -235.0f), cXyz(7.3f, 293.0f, 55.9f), cXyz(-7.3f, -51.6f, 116.5f)
};

static cXyz f_eye[] = {
    cXyz(101.9f, 38.0f, 550.0f), cXyz(-10.0f, 7.0f, -644.0f), cXyz(-10.0f, 7.0f, -644.0f), cXyz(83.6f, 870.4f, -88.0f), cXyz(89.0f, 519.0f, -43.3f)
};

static s32 attack_eff_joint_d[] = {0x1A, 0x2C, 0x04, 0x07, 0x1A, 0x2C};
static u32 attack_eff_id[] = {
    dPa_name::ID_SCENE_8386, dPa_name::ID_SCENE_8387, dPa_name::ID_SCENE_8388, dPa_name::ID_SCENE_8389, dPa_name::ID_SCENE_C35D, dPa_name::ID_SCENE_C35E,
    dPa_name::ID_SCENE_838A, dPa_name::ID_SCENE_838B, dPa_name::ID_SCENE_838C, dPa_name::ID_SCENE_838D, dPa_name::ID_SCENE_C35F, dPa_name::ID_SCENE_C360,
    dPa_name::ID_SCENE_832D, dPa_name::ID_SCENE_832E, dPa_name::ID_SCENE_832F, dPa_name::ID_SCENE_8330, dPa_name::ID_SCENE_C32B, dPa_name::ID_SCENE_C32C,
    dPa_name::ID_SCENE_838E, dPa_name::ID_SCENE_838F, dPa_name::ID_SCENE_8390, dPa_name::ID_SCENE_8391, dPa_name::ID_SCENE_C361, dPa_name::ID_SCENE_C362,
    dPa_name::ID_SCENE_8392, dPa_name::ID_SCENE_8393, dPa_name::ID_SCENE_8394, dPa_name::ID_SCENE_8395, dPa_name::ID_SCENE_C363, dPa_name::ID_SCENE_C364,
    dPa_name::ID_SCENE_8396, dPa_name::ID_SCENE_8397, dPa_name::ID_SCENE_8398, dPa_name::ID_SCENE_8399, dPa_name::ID_SCENE_C365, dPa_name::ID_SCENE_C366,
    dPa_name::ID_SCENE_839A, dPa_name::ID_SCENE_839B, dPa_name::ID_SCENE_839C, dPa_name::ID_SCENE_839D, dPa_name::ID_SCENE_C367, dPa_name::ID_SCENE_C368,
    dPa_name::ID_SCENE_839E, dPa_name::ID_SCENE_839F, dPa_name::ID_SCENE_83A0, dPa_name::ID_SCENE_83A1, dPa_name::ID_SCENE_C369, dPa_name::ID_SCENE_C36A,
    dPa_name::ID_SCENE_83A2, dPa_name::ID_SCENE_83A3, dPa_name::ID_SCENE_83A4, dPa_name::ID_SCENE_83A5, dPa_name::ID_SCENE_C36B, dPa_name::ID_SCENE_C36C,
    dPa_name::ID_SCENE_83A6, dPa_name::ID_SCENE_83A7, dPa_name::ID_SCENE_83A8, dPa_name::ID_SCENE_83A9, dPa_name::ID_SCENE_C36D, dPa_name::ID_SCENE_C36E,
    dPa_name::ID_SCENE_83AA, dPa_name::ID_SCENE_83AB, dPa_name::ID_SCENE_83AC, dPa_name::ID_SCENE_83AD, dPa_name::ID_SCENE_C36F, dPa_name::ID_SCENE_C370,
    dPa_name::ID_SCENE_83AE, dPa_name::ID_SCENE_83AF, dPa_name::ID_SCENE_83B0, dPa_name::ID_SCENE_83B1, dPa_name::ID_SCENE_C371, dPa_name::ID_SCENE_C372,
    dPa_name::ID_SCENE_83B2, dPa_name::ID_SCENE_83B3, dPa_name::ID_SCENE_83B4, dPa_name::ID_SCENE_83B5, dPa_name::ID_SCENE_C373, dPa_name::ID_SCENE_C374,
    dPa_name::ID_SCENE_83B6, dPa_name::ID_SCENE_83B7, dPa_name::ID_SCENE_83B8, dPa_name::ID_SCENE_83B9, dPa_name::ID_SCENE_C375, dPa_name::ID_SCENE_C376,
    dPa_name::ID_SCENE_83BA, dPa_name::ID_SCENE_83BB, dPa_name::ID_SCENE_83BC, dPa_name::ID_SCENE_83BD, dPa_name::ID_SCENE_C377, dPa_name::ID_SCENE_C378,
    dPa_name::ID_SCENE_83BE, dPa_name::ID_SCENE_83BF, dPa_name::ID_SCENE_83C0, dPa_name::ID_SCENE_83C1, dPa_name::ID_SCENE_C379, dPa_name::ID_SCENE_C37A,
    dPa_name::ID_SCENE_83BE, dPa_name::ID_SCENE_83BF, dPa_name::ID_SCENE_83C0, dPa_name::ID_SCENE_83C1, dPa_name::ID_SCENE_C379, dPa_name::ID_SCENE_C37A,
    dPa_name::ID_NONE,       dPa_name::ID_NONE,       dPa_name::ID_NONE,       dPa_name::ID_SCENE_83D9, dPa_name::ID_NONE,       dPa_name::ID_NONE
};

static s32 ke_set_index[] = {0x1B, 0x1B, 0x2D, 0x2D};
static f32 ke_set_offsetxz[] = {-4.0f, 4.0f, -4.0f, 4.0f};
static s32 bougyo_d[] = {GND_BCK_BOUGYO1, GND_BCK_BOUGYO2, GND_BCK_BOUGYO4, GND_BCK_BOUGYO6, GND_BCK_BOUGYO7, GND_BCK_BOUGYO5};
static f32 f_fovy[] = {66.75f, 64.25f, 64.25f, 44.25f, 44.25f};
static s32 eff_d[] = {0x2F, 0x3C, 0x3D, 0x3E, 0x09, 0x0B, 0x0E, 0x11, 0x0D, 0x10, 0x1D, 0x20, 0x23, 0x1F, 0x22};
static s32 fl_check_d[] = {0x0A, 0x02, 0x02, 0x05, 0x05, 0x0A, 0x0F, 0x14, 0x0D, 0x12, 0x0A, 0x0F, 0x14, 0x0D, 0x12};
static f32 fl_scale[] = {1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f};

/* 0000054C-000005DC       .text splash_set__FP9gnd_class */
void splash_set(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar3;

    pJVar3 = dComIfGp_particle_set(dPa_name::ID_SCENE_833C, &actor->current.pos);
    if (pJVar3 != NULL) {
        pJVar3->setGlobalPrmColor(i_this->m0320.mColorC0.r, i_this->m0320.mColorC0.g, i_this->m0320.mColorC0.b);
    }
}

/* 000005DC-000006B4       .text attack_eff_set__FP9gnd_classi */
void attack_eff_set(gnd_class* i_this, int param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    for (s32 i = 0; i < 6; i++) {
        if (attack_eff_id[(i + param_2 * 6)] != 0) {
            i_this->mpAttackEffEmitter[i] = dComIfGp_particle_set(attack_eff_id[(i + param_2 * 6)], &actor->current.pos);
            ;
            if (i <= 3) {
                i_this->mpAttackEffEmitter[i]->setGlobalPrmColor(i_this->m0320.mColorC0.r, i_this->m0320.mColorC0.g, i_this->m0320.mColorC0.b);
            }
        }
    }
}

/* 000006B4-00000738       .text attack_eff_move__FP9gnd_class */
void attack_eff_move(gnd_class* i_this) {
    J3DModel* pJVar3 = i_this->mpMorf->getModel();
    for (s32 i = 0; i < 6; i++) {
        if (i_this->mpAttackEffEmitter[i] != NULL) {
            i_this->mpAttackEffEmitter[i]->setGlobalRTMatrix(pJVar3->getAnmMtx(attack_eff_joint_d[i]));
        }
    }
}

/* 00000738-0000077C       .text attack_eff_remove__FP9gnd_class */
void attack_eff_remove(gnd_class* i_this) {
    for (s32 i = 0; i < 6; i++) {
        if (i_this->mpAttackEffEmitter[i] != NULL) {
            i_this->mpAttackEffEmitter[i]->becomeInvalidEmitter();
            i_this->mpAttackEffEmitter[i] = NULL;
        }
    }
}

/* 0000077C-00000900       .text anm_init__FP9gnd_classifUcfi */
void anm_init(gnd_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Gnd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Gnd", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Gnd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
    attack_eff_remove(i_this);
    s32 unk_array[] = {0x24, 0x25, 0x26, 0x27, 0x28, 0x2B, 0x29, 0x2A, 0x48, 0x47, 0x45, 0x46, 0x53, 0x54, 0x36, 0x37, 0x35, 0x4E};
    for (s32 i = 0; i < 0x12; i++) {
        if (bckFileIdx == unk_array[i]) {
            attack_eff_set(i_this, i);
            return;
        }
    }
}

/* 00000900-0000094C       .text z_s_sub__FPvPv */
void* z_s_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_PZ)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 0000094C-00000C38       .text daGnd_Draw__FP9gnd_class */
static BOOL daGnd_Draw(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    short sVar1;
    s16 uVar2;
    s16 uVar3;
    s16 uVar4;
    u32 uVar5;
    J3DModel* pModel;
    cXyz local_34;

    if (i_this->m155C > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->m155C);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->m155C == 1) {
        i_this->m155C = 0;
        mDoGph_gInf_c::offBlure();
    }
    pModel = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    if (i_this->m142C != 0) {
        uVar2 = actor->tevStr.mFogColor.r + i_this->m1426;
        if (0xff < (s16)uVar2) {
            uVar2 = 0xff;
        }
        sVar1 = actor->tevStr.mFogColor.g;
        uVar3 = sVar1 + i_this->m1426;
        if (0xff < (s16)uVar3) {
            uVar3 = 0xff;
        }
        uVar4 = sVar1 + ((s16)i_this->m1426 / 2);
        if (0xff < (s16)uVar4) {
            uVar4 = 0xff;
        }
        if (i_this->m142C > (s16)(REG8_S(5) + 0x14)) {
            cLib_addCalcAngleS2(&i_this->m1426, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m1428, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m1426, 0, 1, 0xe);
            cLib_addCalc0(&i_this->m1428, 1.0f, 2500.0f);
        }
        actor->tevStr.mFogColor.r = uVar2 & 0xff;
        actor->tevStr.mFogColor.g = uVar3 & 0xff;
        actor->tevStr.mFogColor.b = uVar4 & 0xff;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m1428;
    }
    g_env_light.setLightTevColorType(pModel, &actor->tevStr);
    i_this->m02C0->entry(pModel->getModelData());
    i_this->m02BC->entry(pModel->getModelData());
    i_this->m02C4->entry(pModel->getModelData());
    i_this->mpMorf->entryDL();
    local_34.set(actor->current.pos.x, actor->current.pos.y + 400.0f + REG0_F(0x12), actor->current.pos.z);
    uVar5 = dComIfGd_setShadow(
        i_this->m02C8,
        1,
        pModel,
        &local_34,
        REG0_F(0x13) + 1300.0f,
        200.0f,
        actor->current.pos.y,
        i_this->mAcch.GetGroundH(),
        i_this->mAcch.m_gnd,
        &actor->tevStr,
        0,
        1.0f,
        &dDlst_shadowControl_c::mSimpleTexObj
    );
    i_this->m02C8 = uVar5;
    dSnap_RegistFig(DSNAP_TYPE_UNKCE, actor, 1.0f, 1.0f, 1.0f);
    if (l_HIO.m07 != 0) {
        GXColor local_38 = {0xff, 100, 0, 0xff};
        i_this->m0B64.update(0x14, REG0_F(3) + 2.25f, local_38, 2, &actor->tevStr);
        dComIfGd_set3DlineMat(&i_this->m0B64);
    }
    return TRUE;
}

/* 00000C38-00000C6C       .text player_view_check__FP9gnd_classs */
s32 player_view_check(gnd_class* i_this, short param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar2;
    s16 uVar1;

    sVar2 = actor->shape_angle.y - param_2;
    uVar1 = sVar2;
    if (uVar1 < 0) {
        uVar1 = -sVar2;
    }
    if ((u16)(uVar1 & 0xffff) < 0x4000) {
        return TRUE;
    }
    return FALSE;
}

/* 00000C6C-00000F24       .text ke_control__FP9gnd_classP8gnd_ke_sf */
void ke_control(gnd_class* i_this, gnd_ke_s* param_2, float param_3) {
    /* Nonmatching */
    float fVar1;
    float fVar2;
    s16 iVar3;
    int iVar4;
    cXyz* pcVar5;
    cXyz* pcVar6;
    f32 dVar8;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    cXyz local_a8;
    cXyz local_b4;

    dVar12 = (i_this->mAcch.GetGroundH() + 3.0f);
    pcVar6 = &param_2->m000[1];
    pcVar5 = &param_2->m0F0[1];
    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
    local_a8.z = (l_HIO.m08 * param_3) * 0.5f;
    if (param_3 <= 0.05f) {
        local_a8.z = 0.0f;
    }
    dVar11 = (REG0_F(1) + -5.0f);
    dVar10 = (REG0_F(2) + 0.73f);
    for (s32 i = 1; i < 20; i++, pcVar6++, pcVar5++) {
        dVar13 = (pcVar5->x + (pcVar6->x - pcVar6[-1].x));
        dVar8 = (dVar11 + (pcVar6->y + pcVar5->y));
        if (dVar8 < dVar12) {
            dVar8 = dVar12;
        }
        fVar1 = (dVar8 - pcVar6[-1].y);
        dVar9 = fVar1;
        fVar2 = pcVar5->z + (pcVar6->z - pcVar6[-1].z);
        dVar8 = fVar2;
        iVar3 = -cM_atan2s(fVar1, fVar2);
        dVar8 = std::sqrtf((dVar9 * dVar9) + (dVar8 * dVar8));
        iVar4 = cM_atan2s(dVar13, dVar8);
        mDoMtx_XrotS(*calc_mtx, iVar3);
        mDoMtx_YrotM(*calc_mtx, (s16)iVar4);
        MtxPosition(&local_a8, &local_b4);
        *pcVar5 = *pcVar6;
        pcVar6->x = pcVar6[-1].x + local_b4.x;
        pcVar6->y = pcVar6[-1].y + local_b4.y;
        pcVar6->z = pcVar6[-1].z + local_b4.z;
        pcVar5->x = (dVar10 * (pcVar6->x - pcVar5->x));
        pcVar5->y = (dVar10 * (pcVar6->y - pcVar5->y));
        pcVar5->z = (dVar10 * (pcVar6->z - pcVar5->z));
    }
}

/* 00000F24-00000F68       .text ke_pos_set__FP9gnd_classP8gnd_ke_si */
void ke_pos_set(gnd_class* i_this, gnd_ke_s* param_2, int index) {
    cXyz* pcVar3;

    pcVar3 = i_this->m0B64.getPos(index);
    for (s32 i = 0; i < 20; pcVar3++, i++) {
        *pcVar3 = param_2->m000[i];
    }
}

/* 00000F68-00001140       .text ke_move__FP9gnd_class */
void ke_move(gnd_class* i_this) {
    gnd_ke_s* pDst;
    J3DModel* pJVar3;
    float fVar8;
    cXyz local_78;
    cXyz local_84;

    pDst = i_this->m03E4;
    pJVar3 = i_this->mpMorf->getModel();
    for (s32 i = 0; i < 4; i++, pDst++) {
        MTXCopy(pJVar3->getAnmMtx(ke_set_index[i]), *calc_mtx);
        local_84.set(*calc_mtx[0][0], *calc_mtx[0][1], *calc_mtx[0][2]);
        fVar8 = local_84.abs();
        if ((dComIfGp_evmng_startCheck("endhr")) && (dComIfGp_demo_get()->getFrameNoMsg() >= 300)) {
            fVar8 = 0.0f;
        }
        local_78.x = (-20.0f + REG0_F(4));
        local_78.y = ke_set_offsetxz[i];
        local_78.z = local_78.y;
        MtxPosition(&local_78, pDst->m000);
        ke_control(i_this, pDst, fVar8);
        ke_pos_set(i_this, pDst, i);
    }
}

/* 00001140-00001278       .text pos_move__FP9gnd_classSc */
void pos_move(gnd_class* i_this, signed char param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;

    if (param_2 == 0) {
        local_20 = i_this->m02D4 - actor->current.pos;
        cLib_addCalcAngleS2(&actor->current.angle.y, cM_atan2s(local_20.x, local_20.z), 5, i_this->m02F0 * i_this->m02F4);
        cLib_addCalc2(&i_this->m02F4, 1.0f, 1.0f, 0.05f);
    }
    cLib_addCalc2(&actor->speedF, i_this->m02F8, 1.0f, 6.0f);
    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = actor->speedF;
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_20, &local_2c);
    actor->speed.x = local_2c.x;
    actor->speed.z = local_2c.z;
    actor->current.pos += actor->speed;
    actor->current.pos.y += actor->speed.y;
    actor->speed.y += actor->gravity;
    actor->gravity = -5.0f;
}

/* 00001278-00001334       .text wait_set__FP9gnd_class */
void wait_set(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m03D8 <= 1) {
        anm_init(i_this, GND_BCK_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_LAUGH_WAIT, 0);
    } else {
        anm_init(i_this, GND_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    }
}

/* 00001334-00001974       .text move0__FP9gnd_class */
void move0(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    f32 fVar4;
    short sVar7;
    int iVar5;
    f32 dVar9;
    float fVar10;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar9 = fopAcM_searchPlayerDistance(actor);
    iVar5 = i_this->mpMorf->getFrame();
    bVar2 = false;
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_WALK, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, GND_BAS_WALK);
        i_this->mAnmType++;
        break;
    case 1:
        i_this->m02F8 = l_HIO.m14;
        bVar2 = true;
        if (dVar9 < l_HIO.m18) {
            anm_init(i_this, GND_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType = 2;
        } else {
            if (dVar9 > l_HIO.m1C) {
                anm_init(i_this, GND_BCK_HI_JUMP_START, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_HI_JUMP_START);
                i_this->mAnmType = 3;
                actor->speedF = 0.0f;
                i_this->m02F8 = 0.0f;
            }
        }
        break;
    case 2:
        bVar2 = true;
        i_this->m02F8 = 0.0f;
        sVar7 = fopAcM_searchPlayerAngleY(actor);
        iVar5 = player_view_check(i_this, sVar7);
        if (iVar5 != 0) {
            if ((dVar9 > l_HIO.m3C) && (i_this->m0302[1] == 0)) {
                i_this->mAnmType = 0;
            } else {
                if (dVar9 < l_HIO.m2C) {
                    i_this->mAnmType = 0x14;
                } else {
                    if (i_this->m0302[1] == 0) {
                        fVar10 = cM_rndF(100.0f);
                        if (fVar10 < l_HIO.m48) {
                            i_this->mMoveType = gnd_class::Move_Type_ATTACK1_e;
                            fVar10 = cM_rndF(1.0f);
                            if (fVar10 < 0.5f) {
                                i_this->mAnmType = 0;
                            } else {
                                i_this->mAnmType = 1;
                            }
                        } else {
                            i_this->mMoveType = gnd_class::Move_Type_ATTACK0_e;
                            if ((i_this->m03D8 == 0) || (l_HIO.m11 == 1)) {
                                i_this->mAnmType = 0;
                            } else if ((i_this->m03D8 == 1) || (l_HIO.m11 == 2)) {
                                i_this->mAnmType = 5;
                            } else {
                                fVar10 = cM_rndF(1.0f);
                                if (fVar10 < 0.5f) {
                                    i_this->mAnmType = 0;
                                } else {
                                    i_this->mAnmType = 5;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    case 3:
        actor->gravity = l_HIO.m28;
        if (iVar5 == 0xc) {
            actor->speed.y = l_HIO.m24;
            fVar4 = l_HIO.m20;
            actor->speedF = l_HIO.m20;
            i_this->m02F8 = fVar4;
            splash_set(i_this);
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_HI_JUMP_LOOP, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 4:
        mDoAud_seStart(JA_SE_CM_GN_ROBE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        actor->gravity = l_HIO.m28;
        if (actor->speed.y < 0.0f) {
            anm_init(i_this, GND_BCK_HI_JUMP_END1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 5:
        mDoAud_seStart(JA_SE_CM_GN_ROBE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        actor->gravity = l_HIO.m28;
        i_this->m02F0 = 0.0f;
        if (checkGround(i_this, 0.0f)) {
            anm_init(i_this, GND_BCK_HI_JUMP_END2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType = 6;
            splash_set(i_this);
        }
        break;
    case 6:
        i_this->m02F8 = 0.0f;
        i_this->m02F0 = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType = 2;
            anm_init(i_this, GND_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        break;
    case 0x14:
        anm_init(i_this, GND_BCK_JUMP1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_JUMP1);
        i_this->mAnmType = 0x15;
        break;
    case 0x15:
        bVar2 = true;
        i_this->m02F8 = 0.0f;
        actor->speedF = 0.0f;
        if (i_this->mpMorf->isStop()) {
            actor->speed.y = l_HIO.m34;
            fVar4 = l_HIO.m30;
            actor->speedF = l_HIO.m30;
            i_this->m02F8 = fVar4;
            anm_init(i_this, GND_BCK_JUMP2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType = 0x16;
        }
        break;
    case 0x16:
        actor->gravity = l_HIO.m38;
        bVar2 = true;
        if (checkGround(i_this, 0.0f)) {
            anm_init(i_this, GND_BCK_JUMP3, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_JUMP3);
            i_this->mAnmType = 0x17;
        }
        break;
    case 0x17:
        i_this->m02F8 = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType = 2;
            wait_set(i_this);
            i_this->m0302[1] = 0x14;
        }
    }
    if (bVar2 == 1) {
        i_this->m02D4 = player->current.pos;
    }
    pos_move(i_this, 0);
    i_this->m02F0 = 2000.0f;
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 2, 0x1000);
}

/* 00001974-000028D0       .text attack0__FP9gnd_class */
void attack0(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    s8 bVar2;
    s8 bVar3;
    s8 bVar4;
    s8 bVar5;
    int iVar10;
    short sVar11;
    mDoExt_McaMorf* pmVar13;
    f32 dVar15;

    daPy_py_c* player1 = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar15 = fopAcM_searchPlayerDistance(actor);
    pmVar13 = i_this->mpMorf;
    iVar10 = pmVar13->getFrame();
    bVar1 = false;
    bVar2 = false;
    bVar4 = false;
    bVar3 = false;
    bVar5 = false;
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_AATTACK1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_AATTACK1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_1, 0);
        i_this->mAnmType++;
        bVar5 = true;
        break;
    case 1:
        bVar1 = true;
        bVar5 = true;
        if (iVar10 < 0x17) {
            i_this->m02F8 = l_HIO.m54;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((iVar10 >= 13) && (iVar10 <= 16)) {
            i_this->m13B8[0] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_AATTACK2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_AATTACK2);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_2, 0);
            i_this->mAnmType++;
        }
        break;
    case 2:
        bVar1 = true;
        bVar5 = true;
        if (iVar10 < 0xc) {
            i_this->m02F8 = l_HIO.m50;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((iVar10 >= 5) && (iVar10 <= 10)) {
            i_this->m13B8[0] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            if (i_this->m03D4 != 0) {
                i_this->m03D4 = 0;
                goto block_136;
            }
            anm_init(i_this, GND_BCK_AATTACK3, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_AATTACK3);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_3, 0);
            i_this->mAnmType++;
        }
        if (iVar10 > l_HIO.m6A) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
        }
        break;
    case 3:
        bVar5 = true;
        if (iVar10 < 0x19) {
            i_this->m02F8 = l_HIO.m50;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((iVar10 >= 6) && (iVar10 <= 22)) {
            i_this->m13B8[0] = 1;
            i_this->m13B8[1] = 1;
        }
        if ((iVar10 >= l_HIO.m6C) && (iVar10 <= l_HIO.m6E)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
        }
        break;
    case 5:
        anm_init(i_this, GND_BCK_BATTACK1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_1, 0);
        i_this->mAnmType++;
        bVar5 = true;
        break;
    case 6:
        bVar5 = true;
        if ((iVar10 >= 9) && (iVar10 < 20)) {
            i_this->m02F8 = l_HIO.m54;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((iVar10 >= 13) && (iVar10 <= 17)) {
            i_this->m13B8[1] = 1;
        }
        bVar1 = true;
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_BATTACK2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK2);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_3, 0);
            i_this->mAnmType = 7;
        }
        break;
    case 7:
        bVar1 = true;
        bVar5 = true;
        i_this->m02F8 = l_HIO.m50;
        if ((iVar10 >= 8) && (iVar10 <= 23)) {
            i_this->m13B8[0] = 1;
            i_this->m13B8[1] = 1;
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        if (i_this->m03D4 != 0) {
            i_this->m03D4 = 0;
            goto block_136;
        }
        anm_init(i_this, GND_BCK_BATTACK3_TAME, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK3_TAME);
        i_this->mAnmType = 8;
        break;
    case 8:
        bVar5 = true;
        i_this->m02F8 = 0.0f;
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_BATTACK3_ATTACK, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK3_ATTACK);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_2, 0);
            i_this->mAnmType = 9;
            actor->speed.y = l_HIO.m5C;
            i_this->m02F8 = (dVar15 * (REG0_F(9) + 0.015f));
            splash_set(i_this);
        }
        break;
    case 9:
        bVar5 = true;
        if (actor->speed.y > 0.0f) {
            i_this->m02E0 = actor->speed;
        }
        bVar3 = true;
        bVar2 = true;
        if (iVar10 > l_HIO.m70) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_ROLL_PARRY;
        }
        actor->gravity = l_HIO.m60;
        i_this->m02F0 = 0.0f;
        if (checkGround(i_this, 0.0f)) {
            anm_init(i_this, GND_BCK_BATTACK3_END, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK3_END);
            i_this->mAnmType = 10;
            splash_set(i_this);
        }
        break;
    case 10:
        bVar5 = true;
        if (i_this->m03D8 >= 2) {
            i_this->m03D7 = 2;
        }
        actor->current.angle.y = actor->shape_angle.y;
        if ((iVar10 >= l_HIO.m72) && (iVar10 <= l_HIO.m74)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_ROLL_PARRY;
        }
        i_this->m02F8 = 0.0f;
        if ((iVar10 >= 3) && (iVar10 <= 5)) {
            i_this->m13B8[0] = 1;
            i_this->m13B8[1] = 1;
            i_this->m13C4[1] = 60.0f;
            i_this->m13C4[0] = 60.0f;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType = 0xb;
            i_this->m0302[0] = l_HIO.m76;
        }
        break;
    case 0xb:
        if (i_this->m03D8 >= 2) {
            i_this->m03D7 = 2;
        }
        actor->current.angle.y = actor->shape_angle.y;
        if (i_this->m0302[0] == 0) {
            bVar4 = true;
        }
        break;
    case 0xf:
        bVar1 = true;
        i_this->m02F0 = 8000.0f;
        i_this->m02F8 = 0.0f;
        if (i_this->m0302[0] == 0) {
            anm_init(i_this, GND_BCK_JATTACK_TAME, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_JATTACK_TAME);
            i_this->mAnmType++;
        }
        break;
    case 0x10:
        bVar1 = true;
        i_this->m02F0 = 8000.0f;
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_JATTACK_JUMP, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_4, 0);
            i_this->mAnmType++;
            actor->speed.y = REG0_F(9) + 30.0f;
            i_this->m02F8 = (dVar15 * (REG0_F(10) + 0.025f));
            splash_set(i_this);
        }
        break;
    case 0x11:
        actor->gravity = REG0_F(0xb) + -2.0f;
        i_this->m02F0 = 5000.0f;
        if (actor->speed.y <= 0.0f) {
            anm_init(i_this, GND_BCK_JATTACK_ATTACK, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_JATTACK_ATTACK);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_5, 0);
            i_this->mAnmType++;
            i_this->m02E0 = actor->speed;
            daPy_lk_c* player2 = daPy_getPlayerLinkActorClass();
            player2->clearDamageWait();
            player2->mDamageWaitTimer = 0;
        }
        break;
    case 0x12:
        bVar3 = true;
        i_this->m13B8[0] = 4;
        i_this->m13B8[1] = 4;
        if (checkGround(i_this, 0.0f)) {
            anm_init(i_this, GND_BCK_JATTACK_END, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_JATTACK_END);
            i_this->mAnmType++;
            actor->speedF = 0.0f;
            i_this->m02F8 = 0.0f;
            splash_set(i_this);
        }
        break;
    case 0x13:
        if (iVar10 <= 4) {
            i_this->m13B8[0] = 4;
            i_this->m13B8[1] = 4;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    case 0x14:
    block_136:
        bVar5 = true;
        anm_init(i_this, GND_BCK_KERI1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_KERI1);
        i_this->mAnmType = 0x15;
        break;
    case 0x15:
        bVar5 = true;
        i_this->m02F0 = 5000.0f;
        i_this->m02F8 = l_HIO.m64;
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_KERI2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_4, 0);
            i_this->mAnmType = 0x16;
        }
        break;
    case 0x16:
        bVar5 = true;
        if ((iVar10 >= 0) && (iVar10 <= 4)) {
            i_this->m13B8[1] = 3;
            i_this->m13C4[1] = REG0_F(0xc) + 170.0f;
        }
        if ((iVar10 == 0x14) && (i_this->m03D4 == 0)) {
            i_this->m13D1 = REG0_S(4) + 0xd;
        }
        if (i_this->mpMorf->isStop()) {
            if (i_this->m03D4 != 0) {
                i_this->m03D4 = 0;
                if (i_this->m03D8 == 0) {
                    i_this->m02F8 = 0.0f;
                    wait_set(i_this);
                    i_this->mAnmType = 0x17;
                    i_this->m0302[0] = 150;
                } else {
                    i_this->mAnmType = 0xf;
                    i_this->m0302[0] = REG0_S(7);
                }
            } else {
                bVar5 = true;
                i_this->mAnmType = 0x1a;
                wait_set(i_this);
                i_this->m0302[0] = REG0_S(5) + 0x2d;
            }
        }
        break;
    case 0x17:
        if (i_this->m0302[0] == 0) {
            anm_init(i_this, GND_BCK_KUZUKU, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType = 0x18;
        }
        break;
    case 0x18:
        if (pmVar13->isStop()) {
            sVar11 = fopAcM_searchPlayerAngleY(actor);
            iVar10 = player_view_check(i_this, sVar11);
            if (iVar10 != 0) {
                bVar4 = true;
            } else {
                anm_init(i_this, GND_BCK_FURIMUKU, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_GN_NOTICE, 0);
                i_this->mAnmType = 0x19;
                i_this->m0302[0] = 0x14;
            }
        }
        break;
    case 0x19:
        bVar2 = true;
        if (i_this->m0302[0] == 0) {
            bVar4 = true;
        }
        break;
    case 0x1a:
        i_this->m02F8 = 0.0f;
        bVar5 = true;
        if (i_this->m0302[0] == 0) {
            bVar4 = true;
        }
    }
    actor->speedF = i_this->m02F8;
    if (bVar1) {
        i_this->m02D4 = player1->current.pos;
        pos_move(i_this, 0);
    } else {
        pos_move(i_this, 1);
    }
    i_this->m02F0 = 2000.0f;
    if (!bVar2) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x2000);
    } else {
        sVar11 = fopAcM_searchPlayerAngleY(actor);
        cLib_addCalcAngleS2(&actor->shape_angle.y, sVar11, 4, (s16)(bVar2 << 0xc));
    }
    if (bVar3) {
        cLib_addCalc2(&actor->current.pos.x, player1->current.pos.x, 0.8f, std::fabsf(i_this->m02E0.x));
        cLib_addCalc2(&actor->current.pos.z, player1->current.pos.z, 0.8f, std::fabsf(i_this->m02E0.z));
    }
    if (bVar4) {
        i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
        i_this->mAnmType = 0;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0302[1] = l_HIO.m68;
    }
    if (((l_HIO.m44 == 0) && (i_this->m03D8 < 2)) && (bVar5)) {
        i_this->m13CE = 0;
        i_this->m03D7 = 5;
    }
}

/* 000028D0-00002B68       .text attack1__FP9gnd_class */
void attack1(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int iVar1 = i_this->mpMorf->getFrame();
    s8 bVar4 = false;
    float fVar3 = REG0_F(0xd) + 110.0f;
    i_this->m13C4[1] = fVar3;
    i_this->m13C4[0] = fVar3;
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_NOM_ATTACK1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_NOM_ATTACK1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_4, 0);
        i_this->mAnmType = 5;
        break;
    case 1:
        anm_init(i_this, GND_BCK_NOM_ATTACK2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_NOM_ATTACK2);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_6, 0);
        i_this->mAnmType = 6;
        break;
    case 5:
        if ((iVar1 >= 0xf) && (iVar1 <= 0x12)) {
            i_this->m13B8[0] = 1;
        } else {
            i_this->m02D4 = player->current.pos;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    case 6:
        if ((iVar1 >= 0xc) && (iVar1 <= 0x22)) {
            i_this->m13B8[1] = 1;
        } else {
            i_this->m02D4 = player->current.pos;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    }
    i_this->m02F8 = l_HIO.m14;
    pos_move(i_this, 0);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 2, 0x1000);
    if (bVar4) {
        i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
        i_this->mAnmType = 0;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0302[1] = 0;
    }
}

/* 00002B68-00002D7C       .text attack2__FP9gnd_class */
void attack2(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar1;
    float fVar3;
    s8 bVar4;

    iVar1 = i_this->mpMorf->getFrame();
    bVar4 = false;
    fVar3 = REG0_F(0xd) + 110.0f;
    i_this->m13C4[1] = fVar3;
    i_this->m13C4[0] = fVar3;
    i_this->m13CE = 0;
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_COUNTERL, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_COUNTERL);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_4, 0);
        i_this->mAnmType = 2;
        break;
    case 1:
        anm_init(i_this, GND_BCK_COUNTERR, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_COUNTERR);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_1, 0);
        i_this->mAnmType = 3;
        break;
    case 2:
        if (iVar1 >= 4) {
            i_this->m13B8[0] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    case 3:
        if (iVar1 >= 6) {
            i_this->m13B8[1] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    }
    if (bVar4) {
        i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
        i_this->mAnmType = 0;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0302[1] = 0;
    }
}

/* 00002D7C-00003688       .text attackPZ__FP9gnd_class */
void attackPZ(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar3;
    daPz_c* pdVar5;
    J3DAnmTextureSRTKey* pAnm;
    JPABaseEmitter* pJVar11;
    mDoExt_McaMorf* pmVar12;
    f32 dVar16;
    float fVar17;
    cXyz local_3c;
    cXyz cStack_48;
    cXyz local_54;

    pdVar5 = pz;
    local_54 = pz->current.pos - actor->current.pos;
    fVar17 = local_54.abs();
    dVar16 = fVar17;
    short sVar14 = cM_atan2s(actor->current.pos.x - pz->current.pos.x, actor->current.pos.z - pz->current.pos.z);
    i_this->mDamageInvulnerabilityTimer1 = 5;
    i_this->m13CE = 0;
    pmVar12 = i_this->mpMorf;
    int iVar8 = pmVar12->getFrame();
    bVar3 = false;
    switch (i_this->mAnmType) {
    case 0:
        if (dVar16 > (REG6_F(1) + 1000.0f)) {
            mDoMtx_YrotS(*calc_mtx, sVar14);
            local_3c.x = 0.0f;
            local_3c.y = 0.0f;
            local_3c.z = -(REG0_F(1) + 1000.0f);
            MtxPosition(&local_3c, &cStack_48);
            pz->current.pos = actor->current.pos + cStack_48;
        }
        pz->shape_angle.y = sVar14;
        pz->current.angle.y = sVar14;
        i_this->m031A = sVar14;
        i_this->mAnmType = 1;
        i_this->m155E = 1;
        i_this->m0302[0] = 0x14;
        pdVar5->m073F = 1;
        actor->speedF = 0.0f;
        i_this->m02F8 = 0.0f;
        mDoAud_changeBgmStatus(1);
    case 1:
        i_this->m02F0 = 0.0f;
        if (i_this->m0302[0] == 0) {
            anm_init(i_this, GND_BCK_KIZUKUL, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_NOTICE, 0);
            pAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Gnd", GND_BTK_KIZUKU_EYE);
            i_this->m02BC->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            i_this->mAnmType = 2;
        }
        break;
    case 2:
        i_this->m02F0 = 0.0f;
        break;
    case 3:
        i_this->mAnmType = 5;
    case 5:
        anm_init(i_this, GND_BCK_HI_JUMP_START, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_HI_JUMP_START);
        i_this->mAnmType++;
        break;
    case 6:
        i_this->m02F0 = 8000.0f;
        actor->gravity = REG0_F(0x11) + -0.5f;
        if (iVar8 == 0xc) {
            actor->speed.y = REG0_F(0x13) + 10.0f;
            i_this->m02F8 = (dVar16 * (REG0_F(0x12) + 0.018f));
            splash_set(i_this);
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_HI_JUMP_LOOP, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 7:
        mDoAud_seStart(JA_SE_CM_GN_ROBE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        actor->gravity = REG0_F(0x11) + -0.5f;
        if (actor->speed.y < 0.0f) {
            anm_init(i_this, GND_BCK_HI_JUMP_END1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 8:
        mDoAud_seStart(JA_SE_CM_GN_ROBE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        actor->gravity = REG0_F(0x11) + -0.5f;
        i_this->m02F0 = 0.0f;
        iVar8 = checkGround(i_this, 0.0f);
        if (iVar8 != 0) {
            anm_init(i_this, GND_BCK_HI_JUMP_END2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
            i_this->m02E0 = actor->speed;
            splash_set(i_this);
        }
        break;
    case 9:
        bVar3 = true;
        i_this->m02F8 = 0.0f;
        i_this->m02F0 = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType++;
            anm_init(i_this, GND_BCK_BINTA1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BINTA1);
        }
        break;
    case 10:
        bVar3 = true;
        if (pmVar12->isStop()) {
            i_this->mAnmType++;
            anm_init(i_this, GND_BCK_BINTA2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BINTA2);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_ZELDA, 0);
            pJVar11 = dComIfGp_particle_set(dPa_name::ID_SCENE_837E, &actor->current.pos);
            i_this->m13EC = pJVar11;
            pJVar11 = i_this->m13EC;
            if (pJVar11 != NULL) {
                pJVar11->setGlobalPrmColor(i_this->m0320.mColorC0.r, i_this->m0320.mColorC0.g, i_this->m0320.mColorC0.b);
            }
        }
        break;
    case 0xb:
        if (iVar8 == REG0_S(5) + 2) {
            i_this->m155C = 0x96;
            pdVar5->m08B0 = 1;
            pdVar5 = pz;
            mDoAud_seStart(JA_SE_LK_LAST_HIT, &pdVar5->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(pdVar5)));
            dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (iVar8 == REG0_S(6) + 2) {
            i_this->m155E = 4;
            i_this->m1560 = 0;
        }
        if (i_this->m13EC != NULL) {
            if (i_this->mpMorf->isStop()) {
                i_this->m13EC->becomeInvalidEmitter();
                i_this->m13EC = NULL;
            } else {
                i_this->m13EC->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x23));
            }
        }
    }
    actor->speedF = i_this->m02F8;
    mDoMtx_YrotS(*calc_mtx, i_this->m031A);
    local_3c.x = REG0_F(0x10) + -20.0f;
    local_3c.y = 0.0f;
    local_3c.z = REG0_F(0x11) + 100.0f;
    MtxPosition(&local_3c, &cStack_48);
    i_this->m02D4 = pz->current.pos + cStack_48;
    pos_move(i_this, 0);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x2000);
    if (bVar3) {
        cLib_addCalc2(&actor->current.pos.x, i_this->m02D4.x, 0.2f, std::fabsf(i_this->m02E0.x));
        cLib_addCalc2(&actor->current.pos.z, i_this->m02D4.z, 0.2f, std::fabsf(i_this->m02E0.z));
    }
}

/* 00003688-000038B0       .text attack_last__FP9gnd_class */
void attack_last(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int iVar1 = i_this->mpMorf->getFrame();
    i_this->m13C4[1] = REG0_F(0xd) + 110.0f;
    i_this->m13CE = 0;
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_LAST_ATTACK_TAME, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_7, 0);
        i_this->mAnmType = 1;
        break;
    case 1:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_LAST_ATTACK_ATTACK, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_LAST_ATTACK_ATTACK);
            i_this->mAnmType = 2;
        }
        if (iVar1 > l_HIO.m7C) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_GANONDORF_FINISHER_PARRY;
        }
        break;
    case 2:
        if ((iVar1 >= l_HIO.m7E) && (iVar1 <= l_HIO.m80)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_GANONDORF_FINISHER_PARRY;
        }
        if ((iVar1 >= 6) && (iVar1 <= 9)) {
            i_this->m13B8[1] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = 0;
        }
        break;
    }
    if (player->checkLastComboWait()) {
        i_this->mMoveType = gnd_class::Move_Type_FINISH_e;
        i_this->mAnmType = 0;
        i_this->mDamageInvulnerabilityTimer1 = 5;
        i_this->m13CE = 0;
    }
}

/* 000038B0-000042D0       .text defence0__FP9gnd_class */
void defence0(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    int iVar3;
    short sVar4;
    f32 dVar7;
    float fVar8;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s8 cVar7 = 0;
    i_this->m03D7 = 10;
    dVar7 = fopAcM_searchPlayerDistance(actor);
    if ((actor->current.pos.y > REG0_F(0xb) + (i_this->mAcch.GetGroundH() + 200.0f)) && (i_this->mAnmType < 0xf)) {
        i_this->mAnmType = 0x14;
    }
    switch (i_this->mAnmType) {
    case 0:
        if ((i_this->m03D8 == 2) && (player->current.pos.y - i_this->mAcch.GetGroundH() > REG0_F(0x13) + 300.0f)) {
            i_this->m03DC = 0;
            i_this->mBlockHitCount = 2;
        } else {
            if (((player->mCutType == 15) && (cM_rndF(1.0f) < 0.8f)) || ((i_this->m03DB == 1 && (cM_rndF(1.0f) < 0.05f)) && (i_this->m03D8 == 2))) {
                i_this->m03DC = 5;
                sVar4 = fopAcM_searchPlayerAngleY(actor);
                i_this->m03DE = sVar4 + (REG0_S(4) + 0x7800);
            }
        }
        anm_init(i_this, bougyo_d[i_this->m03DC], 4.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
    block_15:
        i_this->m03DA = 0;
        if (((l_HIO.m46 != 0) && (i_this->m03DC != 5)) && (i_this->mBlockHitCount >= 3 && (cM_rndF(1.0f) < 0.2f))) {
            if (cM_rndF(1.0f) < 0.5f) {
                i_this->m03E0 = 65536.0f;
            } else {
                i_this->m03E0 = -65536.0f;
            }
            if (l_HIO.m12 == 1) {
                actor->speed.y = REG0_F(7) + 20.0f;
                i_this->m02F8 = REG0_F(8) + -20.0f;
                i_this->m03DA = REG0_S(2) + 10;
            } else {
                actor->speed.y = REG0_F(9) + 15.0f;
                i_this->m02F8 = REG0_F(10) + -5.0f;
            }
            i_this->m0310 = 0.0f;
            splash_set(i_this);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_DEFENCE_3, 0);
        } else {
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_DEFENCE_1, 0);
        }
        i_this->mAnmType = 10;
        break;
    case 10:
        if (((i_this->m03D8 == 2) && (player->current.pos.y - i_this->mAcch.GetGroundH() > REG0_F(0x13) + 300.0f)) && (i_this->m03DC != 0)) {
            i_this->m03DC = 0;
            i_this->mBlockHitCount = 2;
            anm_init(i_this, bougyo_d[i_this->m03DC], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            goto block_15;
        }
        actor->gravity = REG0_F(0xb) + -4.0f;
        if (checkGround(i_this, 0.0f)) {
            i_this->m02F8 = 0.0f;
            if (l_HIO.m12 == 0) {
                if (((dVar7 < (REG0_F(2) + 400.0f)) && (i_this->m03DC != 5)) && (i_this->m0302[1] == (s16)(REG0_S(5) + 1))) {
                    i_this->mMoveType = gnd_class::Move_Type_ATTACK2_e;
                    if (cM_rndF(1.0f) < 0.5f) {
                        i_this->mAnmType = 0;
                    } else {
                        i_this->mAnmType = 1;
                    }
                    i_this->m13CE = 0;
                }
            } else if (i_this->m03DA != 0) {
                i_this->m03DA--;
                if (i_this->m03DA == 0) {
                    i_this->mMoveType = gnd_class::Move_Type_ATTACK2_e;
                    if (cM_rndF(1.0f) < 0.5f) {
                        i_this->mAnmType = 0;
                    } else {
                        i_this->mAnmType = 1;
                    }
                    i_this->m13CE = 0;
                }
            }
        }
        if ((((i_this->m0302[0] == 0) && (i_this->m0302[1] == 0)) && (checkGround(i_this, 0.0f))) && (i_this->m03DA == 0)) {
            cVar7 = 1;
        } else if (i_this->mBlockHit != 0) {
            i_this->mBlockHit = 0;
            bVar1 = false;
            if (checkGround(i_this, 0.0f)) {
                if ((i_this->mBlockHitCount >= 8) && (cM_rndF(1.0f) < 0.3f)) {
                    i_this->mAnmType = 0xf;
                    i_this->mBlockHitCount = 0;
                    bVar1 = true;
                } else {
                    if ((i_this->mBlockHitCount >= 4) && (cM_rndF(1.0f) < 0.5f)) {
                        i_this->mParryTimer = REG0_S(6) + 0xd;
                        bVar1 = true;
                    }
                }
            }
            if (!bVar1) {
                i_this->mAnmType = 0;
                if (i_this->mBlockHitCount <= 1) {
                    i_this->m03DC = 0;
                } else {
                    for (s32 i = 0; i < 20; i++) {
                        s8 r5 = cM_rndF(4.99f);
                        if (r5 != i_this->m03DC) {
                            i_this->m03DB = i_this->m03DC;
                            i_this->m03DC = r5;
                            break;
                        }
                    }
                }
            }
            i_this->m0302[1] = REG0_S(4) + 0x19;
            if (i_this->mAnmType < 2) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_GUARD, 0);
            } else {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_JUMP, 0);
            }
        }
        break;
    case 0xf:
        anm_init(i_this, GND_BCK_BOUGYO3, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BOUGYO3);
        i_this->mAnmType++;
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_DEFENCE_2, 0);
        actor->speed.y = REG0_F(5) + 33.0f;
        fVar8 = REG0_F(6) + 30.0f;
        actor->speedF = fVar8;
        i_this->m02F8 = fVar8;
        iVar3 = cM_atan2s(-actor->current.pos.x, -actor->current.pos.z);
        actor->current.angle.y = (s16)iVar3;
        fVar8 = cM_rndF(1.0f);
        if (fVar8 < 0.5f) {
            i_this->m0302[1] = 100;
        } else {
            i_this->m0302[1] = 0;
        }
        i_this->m13CE = 0;
        splash_set(i_this);
        i_this->m031C = 0;
        break;
    case 0x10:
        actor->gravity = REG0_F(7) + -2.0f;
        if (checkGround(i_this, 0.0f)) {
            if (i_this->m031C == 0) {
                splash_set(i_this);
                i_this->m031C = 1;
            }
            i_this->m02F8 = 0.0f;
            if (i_this->mpMorf->isStop()) {
                if (i_this->m0302[1] != 0) {
                    cVar7 = 1;
                } else {
                    cVar7 = 2;
                }
            }
        } else {
            i_this->m13CE = 0;
        }
        break;
    case 0x14:
        anm_init(i_this, GND_BCK_SURETIGAI, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mAnmType++;
        break;
    case 0x15:
        if (i_this->mpMorf->isStop()) {
            cVar7 = 1;
        } else {
            if (checkGround(i_this, 0.0f)) {
                i_this->m02F8 = 0.0f;
                anm_init(i_this, GND_BCK_BOUGYO4, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mAnmType++;
            }
        }
        break;
    case 0x16:
        if (i_this->mpMorf->isStop()) {
            cVar7 = 1;
        }
    }
    if (i_this->m03DC != 5) {
        sVar4 = fopAcM_searchPlayerAngleY(actor);
        cLib_addCalcAngleS2(&actor->shape_angle.y, sVar4, 2, REG0_S(8) + 0x2000);
    } else {
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m03DE, 2, REG0_S(8) + 0x2000);
    }
    i_this->m13B8[0] = 10;
    i_this->m13B8[1] = 0xb;
    pos_move(i_this, 1);
    if (cVar7 != 0) {
        actor->current.angle.y = actor->shape_angle.y;
        if (cVar7 == 1) {
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
        } else {
            i_this->mMoveType = gnd_class::Move_Type_ATTACK0_e;
            anm_init(i_this, GND_BCK_BATTACK3_TAME, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK3_TAME);
            i_this->mAnmType = 8;
        }
    }
}

/* 000042D0-00004330       .text finish__FP9gnd_class */
void finish(gnd_class* i_this) {
    i_this->mDamageInvulnerabilityTimer1 = 5;
    i_this->m13CE = 0;
    switch (i_this->mAnmType) {
    case 0:
        i_this->m155E = 100;
        i_this->mAnmType = 1;
        break;
    case 1:
        i_this->mAnmType = 2;
        break;
    case 2:
        i_this->mAnmType = 3;
        break;
    case 3:
        break;
    }
}

/* 00004330-00004760       .text damage__FP9gnd_class */
void damage(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar3;
    int iVar2;
    f32 dVar6;

    i_this->m13CE = 0;
    if (i_this->m03D9 != 0) {
        if (i_this->m03D9 == 1) {
            i_this->mMoveType = gnd_class::Move_Type_ATTACKPZ_e;
            i_this->mAnmType = 0;
            i_this->m13CE = 0;
        } else {
            i_this->m155E = 10;
        }
        i_this->m03D9 = 0;
        return;
    }
    switch (i_this->mAnmType) {
    case 0:
        anm_init(i_this, GND_BCK_DAMAGEA, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mAnmType = 1;
        i_this->m0302[0] = l_HIO.m86;
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_DAMAGE_3, 0);
    case 1:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_DAMAGEA_LOOP, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType = 9;
            i_this->m0302[1] = 10;
        }
        break;
    case 5:
        anm_init(i_this, GND_BCK_DAMAGEB, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_DAMAGE_2, 0);
        i_this->m0302[0] = l_HIO.m86;
        i_this->mAnmType = 6;
    case 6:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_DAMAGEB_LOOP, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType = 10;
            i_this->m0302[1] = 0xf;
        }
        break;
    case 9:
        if (i_this->m0302[1] != 0) {
            goto block_35;
        }
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_UMEKI, 0);
        i_this->m0302[1] = 0x14;
        goto block_35;
    case 10:
        if (i_this->m0302[1] == 0) {
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_UMEKI, 0);
            i_this->m0302[1] = 0x1e;
        }
    block_35:
        if ((((i_this->m155E == 0) && (i_this->m0302[0] < 30)) && (actor->health < 25)) && (i_this->m03D8 == 2)) {
            sVar3 = fopAcM_searchPlayerAngleY(actor);
            iVar2 = player_view_check(i_this, sVar3);
            if ((iVar2 != 0) && (dVar6 = fopAcM_searchPlayerDistance(actor), dVar6 < l_HIO.m78)) {
                i_this->mMoveType = gnd_class::Move_Type_ATTACK_LAST_e;
                i_this->mAnmType = 0;
                i_this->m13CE = 1;
                i_this->mDamageInvulnerabilityTimer2 = 30;
                return;
            }
        }
        if (i_this->m0302[0] == 0) {
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
            i_this->m13CE = 1;
            i_this->mDamageInvulnerabilityTimer2 = 30;
        }
        break;
    case 0x14:
        anm_init(i_this, GND_BCK_DAMAGEC, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_DAMAGE_1, 0);
        i_this->mAnmType = 10;
    }
    pos_move(i_this, 1);
    i_this->m02F8 = 0.0f;
}

/* 00004760-0000501C       .text damage_check__FP9gnd_class */
void damage_check(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar1;
    s8 bVar4;
    s8 bVar5;
    s16 uVar7;
    cCcD_Obj* pcVar9;
    short sVar11;
    gnd_class* pfVar10;
    JPABaseEmitter* pJVar10;
    daArrow_c* pfVar13;
    cXyz* pcVar16;
    dCcD_GObjInf* objinf;
    float fVar17;
    cXyz local_5c;
    cXyz local_68;
    CcAtInfo local_50;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    for (s32 i = 0; i < 2; i++) {
        objinf = &i_this->mSwordSphs[i];
        if (objinf->ChkTgHit()) {
            pcVar9 = objinf->GetTgHitObj();
            def_se_set(actor, pcVar9, 0x40);
            i_this->m0310 = REG0_F(0x13) + 30.0f;
            sVar11 = fopAcM_searchPlayerAngleY(actor);
            i_this->m0314 = sVar11 + 0x8000;
            i_this->mBlockHitCount++;
            i_this->mBlockHit = 1;
            pcVar16 = objinf->GetTgHitPosP();
            dKy_SordFlush_set(*pcVar16, 0);
            local_5c.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, pcVar16, &actor->shape_angle, &local_5c);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8380, pcVar16, &actor->shape_angle);
        }
        if (objinf->ChkAtHit()) {
            pcVar9 = objinf->GetAtHitObj();
            if (pcVar9->GetStts() == NULL) {
                pfVar10 = NULL;
            } else {
                pfVar10 = (gnd_class*)pcVar9->GetStts()->GetActor();
            }
            if (fopAcM_GetName(pfVar10) == PROC_PLAYER) {
                if (i_this->mAnmType == 0x16) {
                    i_this->m03D4 = 1;
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                } else {
                    if (player->checkPlayerGuard()) {
                        dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                        if ((i_this->mAnmType == 2) || (i_this->mAnmType == 7)) {
                            i_this->m03D4 = 1;
                        }
                    }
                }
            }
        }
    }
    if (i_this->mDamageInvulnerabilityTimer1 != 0) {
        return;
    }
    if (i_this->mChestSph.ChkTgHit()) {
        bVar4 = false;
        local_50.mpObj = i_this->mChestSph.GetTgHitObj();
        if (local_50.mpObj == NULL) {
            return;
        }
        if ((local_50.mpObj)->GetStts() == NULL) {
            pfVar13 = NULL;
        } else {
            pfVar13 = (daArrow_c*)(local_50.mpObj)->GetStts()->GetActor();
        }
        if (((pfVar13 != NULL) && (fopAcM_GetName(pfVar13) == PROC_ARROW)) && (pfVar13->isSetByZelda() != false)) {
            sVar11 = actor->shape_angle.y - pfVar13->current.angle.y;
            uVar7 = sVar11;
            if (uVar7 < 0) {
                uVar7 = -sVar11;
            }
            if ((((uVar7 & 0xffff) < 0x4000) && (i_this->m03D8 < 2)) || (pfVar13->mbLinkReflect != 0)) {
                bVar4 = true;
            } else {
                i_this->m13CE = 2;
            }
        }
        if ((!bVar4) && (i_this->m13CE != 0)) {
            i_this->mMoveType = gnd_class::Move_Type_DEFENCE0_e;
            if (i_this->m13CE == 1) {
                pcVar9 = i_this->mChestSph.GetTgHitObj();
                def_se_set(actor, pcVar9, 0x40);
                i_this->m0310 = REG0_F(0x13) + 30.0f;
                sVar11 = fopAcM_searchPlayerAngleY(actor);
                i_this->m0314 = sVar11 + 0x8000;
                pcVar16 = i_this->mChestSph.GetTgHitPosP();
                dKy_SordFlush_set(*pcVar16, 0);
                local_68.setall(2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, pcVar16, &actor->shape_angle, &local_68);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8380, pcVar16, &actor->shape_angle);
                fopAcM_monsSeStart(actor, JA_SE_CV_GN_DEFENCE_1, 0);
                if (cM_rndF(1.0f) < 0.5f) {
                    anm_init(i_this, GND_BCK_BOUGYO1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                } else {
                    anm_init(i_this, GND_BCK_BOUGYO2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                }
                i_this->m0302[0] = 20;
                i_this->mAnmType = 10;
                return;
            }
            i_this->mAnmType = 0xf;
            i_this->mBlockHitCount = 0;
            return;
        }
    }
    if ((i_this->mDamageInvulnerabilityTimer2 == 0) || (i_this->mChestSph.ChkTgHit())) {
        bVar4 = false;
        if ((i_this->mDamageCyl.ChkTgHit()) || (i_this->mHeadSph.ChkTgHit() || (i_this->mChestSph.ChkTgHit()))) {
            i_this->mDamageInvulnerabilityTimer1 = 7;
            bVar5 = false;
            if (i_this->mHeadSph.ChkTgHit()) {
                local_50.mpObj = i_this->mHeadSph.GetTgHitObj();
                local_50.pParticlePos = i_this->mHeadSph.GetTgHitPosP();
                bVar4 = true;
            } else {
                if (i_this->mChestSph.ChkTgHit()) {
                    local_50.mpObj = i_this->mChestSph.GetTgHitObj();
                    local_50.pParticlePos = i_this->mChestSph.GetTgHitPosP();
                    bVar5 = true;
                } else {
                    local_50.mpObj = i_this->mDamageCyl.GetTgHitObj();
                    local_50.pParticlePos = i_this->mDamageCyl.GetTgHitPosP();
                }
            }
            local_50.mpActor = cc_at_check(actor, &local_50);
            if ((bVar5) && (local_50.mpActor != NULL)) {
                dComIfGp_particle_set(dPa_name::ID_SCENE_8382, local_50.pParticlePos, &local_50.mpActor->current.angle);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8383, local_50.pParticlePos, &local_50.mpActor->current.angle);
                i_this->m142E = 1;
                i_this->m142C = REG8_S(4) + 0x1e;
                for (s32 i = 0; i < 15; i++) {
                    fVar17 = cM_rndFX(30.0f);
                    i_this->m14A8[i].x = fVar17;
                    fVar17 = cM_rndFX(30.0f);
                    i_this->m14A8[i].y = fVar17;
                    fVar17 = cM_rndFX(30.0f);
                    i_this->m14A8[i].z = fVar17;
                }
                i_this->m15AC = REG0_F(0x13) + 20.0f;
            } else if ((player->mCutType == 5) || (player->mCutType == 15)) {
                dComIfGp_particle_set(dPa_name::ID_SCENE_8381, local_50.pParticlePos, &actor->shape_angle);
            } else {
                pJVar10 = dComIfGp_particle_set(dPa_name::ID_SCENE_837F, local_50.pParticlePos, &actor->shape_angle);
                if (pJVar10 != NULL) {
                    pJVar10->setGlobalPrmColor(i_this->m0320.mColorC0.r, i_this->m0320.mColorC0.g, i_this->m0320.mColorC0.b);
                }
            }
            sVar1 = actor->health;
            if (sVar1 <= 25) {
                if (i_this->m03D8 == 1) {
                    actor->health = 25;
                    i_this->m03D8 = 2;
                    i_this->m03D9 = 2;
                }
            } else if ((sVar1 <= 50) && (i_this->m03D8 == 0)) {
                if (fopAcM_GetName(local_50.mpActor) == PROC_ARROW) {
                    if (pfVar13->isSetByZelda() != 0) {
                        i_this->m03D9 = 1;
                    }
                } else {
                    actor->health = 50;
                }
            }
            if (actor->health < 0) {
                actor->health = 0;
            }
            if (i_this->mMoveType != gnd_class::Move_Type_DAMAGE_e) {
                i_this->mMoveType = gnd_class::Move_Type_DAMAGE_e;
                if (bVar4) {
                    i_this->mAnmType = 5;
                } else {
                    i_this->mAnmType = 0;
                }
                i_this->m13CE = 0;
            } else {
                i_this->mAnmType = 0x14;
            }
            fopAcM_monsSeStart(actor, JA_SE_CV_MO_DAMAGE, 0);
        }
    }
}

/* 0000501C-0000509C       .text shot_s_sub__FPvPv */
void* shot_s_sub(void* param_1, void* param_2) {
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;

    if ((((fopAc_IsActor(actor)) && (fopAcM_GetName(actor) == PROC_HIMO2)) || (fopAcM_GetName(actor) == PROC_BOOMERANG) ||
         (fopAcM_GetName(actor) == PROC_HOOKSHOT) || (fopAcM_GetName(actor) == PROC_ARROW)) &&
        (actor->speedF >= 10.0f))
    {
        return actor;
    }
    return NULL;
}

/* 0000509C-000050B0       .text demowait__FP9gnd_class */
void demowait(gnd_class* i_this) {
    i_this->mDamageInvulnerabilityTimer1 = 5;
    i_this->m13CE = 0;
}

/* 000050B0-000050C8       .text yawait__FP9gnd_class */
void yawait(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    actor->current.pos.y = 0.0f;
    i_this->m13CE = 0;
}

/* 000050C8-000054F0       .text gnd_move__FP9gnd_class */
void gnd_move(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    float fVar3;
    short sVar6;
    s16 uVar5;
    daArrow_c* pvVar7;
    f32 dVar9;
    float fVar10;
    cXyz local_28;
    cXyz cStack_34;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mMoveType) {
    case gnd_class::Move_Type_MOVE0_e:
        move0(i_this);
        break;
    case gnd_class::Move_Type_ATTACK0_e:
        attack0(i_this);
        break;
    case gnd_class::Move_Type_ATTACK1_e:
        attack1(i_this);
        break;
    case gnd_class::Move_Type_ATTACK2_e:
        attack2(i_this);
        break;
    case gnd_class::Move_Type_ATTACKPZ_e:
        attackPZ(i_this);
        break;
    case gnd_class::Move_Type_ATTACK_LAST_e:
        attack_last(i_this);
        break;
    case gnd_class::Move_Type_DEFENCE0_e:
        defence0(i_this);
        break;
    case gnd_class::Move_Type_DAMAGE_e:
        damage(i_this);
        break;
    case gnd_class::Move_Type_DEMOWAIT_e:
        demowait(i_this);
        break;
    case gnd_class::Move_Type_YAWAIT_e:
        yawait(i_this);
        break;
    case gnd_class::Move_Type_FINISH_e:
        finish(i_this);
        return;
    }
    if ((i_this->m03D8 >= 2) && (i_this->mMoveType != gnd_class::Move_Type_DAMAGE_e)) {
        i_this->mDamageInvulnerabilityTimer2 = 3;
    }
    if (((player->mCutType == 5) || (player->mCutType == 15)) && (i_this->m03D8 < 2)) {
        i_this->m13CE = 0;
        i_this->m03D7 = 0;
    }
    if (i_this->m13CE != 0) {
        bVar2 = false;
        pvVar7 = (daArrow_c*)fpcM_Search(shot_s_sub, i_this);
        if (pvVar7 != NULL) {
            local_28 = pvVar7->current.pos - actor->eyePos;
            if (fopAcM_GetName(pvVar7) == PROC_ARROW) {
                fVar10 = local_28.abs();
                if (((fVar10 < pvVar7->speedF * 10.0f) && (pvVar7->isSetByZelda() != false)) && (i_this->m03D8 < 2)) {
                    sVar6 = actor->shape_angle.y - pvVar7->current.angle.y;
                    uVar5 = sVar6;
                    if (uVar5 < 0) {
                        uVar5 = -sVar6;
                    }
                    if ((uVar5 & 0xffff) < 0x4000) {
                        i_this->m13CE = 0;
                    } else {
                        i_this->mMoveType = gnd_class::Move_Type_DEFENCE0_e;
                        if (checkGround(i_this, 50.0f)) {
                            i_this->mAnmType = 0xf;
                        } else {
                            i_this->mAnmType = 0;
                        }
                        i_this->mDamageInvulnerabilityTimer1 = 0x1e;
                        i_this->m03DB = 0;
                    }
                }
            } else {
                fVar10 = local_28.abs();
                if (fVar10 < pvVar7->speedF * 10.0f) {
                    bVar2 = true;
                }
            }
        }
        dVar9 = fopAcM_searchPlayerDistance(actor);
        if ((bVar2) || (player->mCutType != 0 && (dVar9 < l_HIO.m40))) {
            if (i_this->mMoveType != gnd_class::Move_Type_DEFENCE0_e) {
                i_this->mMoveType = gnd_class::Move_Type_DEFENCE0_e;
                i_this->mAnmType = 0;
                i_this->mBlockHitCount = 0;
                i_this->m03DB = 0;
                i_this->m03DC = 0;
            }
            i_this->m0302[0] = 10;
        }
    }
    damage_check(i_this);
    i_this->m13CE = 1;
    dCcD_Stts* stts = &i_this->mStts;
    if (stts != NULL) {
        actor->current.pos.x += stts->GetCCMoveP()->x;
        actor->current.pos.y += stts->GetCCMoveP()->y;
        actor->current.pos.z += stts->GetCCMoveP()->z;
    }
    fVar3 = i_this->m0310;
    if (fVar3 > 0.01f) {
        local_28.setall(0.0f);
        mDoMtx_YrotS(*calc_mtx, i_this->m0314);
        MtxPosition(&local_28, &cStack_34);
        actor->current.pos += cStack_34;
        cLib_addCalc0(&i_this->m0310, 1.0f, (REG0_F(0xc) + 7.0f));
    }
}

/* 000054F0-00006B04       .text demo_camera__FP9gnd_class */
void demo_camera(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    float fVar2;
    s8 bVar3;
    int iVar9;
    short sVar12;
    J3DAnmTextureSRTKey* pAnm;
    f32 dVar19;
    f32 dVar20;
    cXyz local_54;
    cXyz cStack_60;
    cXyz local_e4;
    cXyz local_f0;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* pcVar18 = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    daPz_c* pdVar7 = pz;
    bVar3 = false;
    dVar19 = 0.0f;
    cStack_60.setall(0.0f);
    switch (i_this->m155E) {
    case 0:
        break;
    case 0x1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m155E++;
        pcVar18->mCamera.Stop();
        pcVar18->mCamera.SetTrimSize(2);
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = dVar19;
        player->changeOriginalDemo();
        i_this->m15AC = dVar19;
        i_this->m15A4 = REG0_F(6) + 55.0f;
        i_this->m157C.x = REG0_F(0) + 400.0f;
        i_this->m157C.y = REG0_F(1) + 100.0f;
        i_this->m157C.z = REG0_F(2) - 200.0f;
        i_this->m1588.x = REG0_F(3);
        i_this->m1588.y = REG0_F(4) + 200.0f;
        i_this->m1588.z = REG0_F(5);
        // fallthrough
    case 0x2:
        actor->shape_angle.y = (cM_atan2s(actor->current.pos.x - pz->current.pos.x, actor->current.pos.z - pz->current.pos.z)) + (REG0_S(0) + 0x4000);
        actor->current.angle.y = actor->shape_angle.y;
        if (i_this->m1560 > REG0_S(1) + 0x19) {
            i_this->m155C = 0x82;
            cLib_addCalc2(&i_this->m157C.x, REG0_F(6) + 130.0f, 0.6f, i_this->m15A0 * 270.0f);
            cLib_addCalc2(&i_this->m157C.y, REG0_F(7) + 230.0f, 0.6f, i_this->m15A0 * 80.0f);
            cLib_addCalc2(&i_this->m157C.z, REG0_F(8), 0.6f, i_this->m15A0 * 100.0f);
            cLib_addCalc2(&i_this->m1588.y, REG0_F(9) + 280.0f, 0.6f, i_this->m15A0 * 80.0f);
            cLib_addCalc2(&i_this->m15A0, 1.0f, 1.0f, (REG0_F(7) + 1.0f) * 0.02f);
        } else {
            i_this->m157C.x = REG0_F(0) + 400.0f;
            i_this->m157C.y = REG0_F(1) + 150.0f;
            i_this->m157C.z = REG0_F(2);
            i_this->m1588.x = REG0_F(3);
            i_this->m1588.y = REG0_F(4) + 200.0f;
            i_this->m1588.z = REG0_F(5);
        }
        MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
        mDoMtx_YrotM(*calc_mtx, actor->shape_angle.y);
        MtxPosition(&i_this->m157C, &i_this->m1564);
        MtxPosition(&i_this->m1588, &i_this->m1570);
        if (i_this->m1560 > REG0_S(2) + 0x3c) {
            i_this->m155E++;
            i_this->m1560 = 0;
            i_this->m155C = 0x32;
        }
        break;
    case 0x3:
        if (i_this->m1560 == 10) {
            i_this->mAnmType++;
        }
        MtxTrans(pz->current.pos.x, pz->current.pos.y, pz->current.pos.z, false);
        mDoMtx_YrotM(*calc_mtx, pz->shape_angle.y);
        i_this->m157C.x = REG0_F(10) + 100.0f;
        i_this->m157C.y = REG0_F(0xb) + 50.0f;
        i_this->m157C.z = REG0_F(0xc) - 300.0f;
        MtxPosition(&i_this->m157C, &i_this->m1564);
        i_this->m1570 = actor->current.pos;
        i_this->m1570.y += REG0_F(0xd) + 150.0f;
        sVar12 = fopAcM_searchPlayerAngleY(actor);
        player->setPlayerPosAndAngle(&player->current.pos, (s16)(sVar12 + 0x8000));
        break;
    case 0x4:
        cLib_addCalc2(&i_this->m1570.y, 100.0f, 0.8f, 10.0f);
        if (i_this->m1560 < 0xf) {
            break;
        }
        i_this->m155E = 5;
        i_this->m1560 = 0;
        i_this->m15A4 = 75.0f;
        // fallthrough
    case 0x5:
        mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);
        local_54.x = REG0_F(4) + -50.0f;
        local_54.y = REG0_F(5) + 50.0f;
        local_54.z = REG0_F(6) + 100.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = player->current.pos + cStack_60;
        i_this->m1570 = player->current.pos;
        i_this->m1570.y += REG0_F(7) + 90.0f;
        cLib_addCalc2(&i_this->m15A4, 55.0f, 0.8f, 10.0f);
        i_this->m155C = 0x32;
        if (l_HIO.m88 == 0) {
            if (i_this->m1560 == 5) {
                player->changeDemoMode(daPy_demo_c::DEMO_S_SURP_e);
            }
            if (i_this->m1560 == 25) {
                bVar3 = true;
            }
        } else {
            if (i_this->m1560 == 5) {
                player->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
            }
            if (i_this->m1560 == 60) {
                player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
            }
            if (i_this->m1560 == 150) {
                bVar3 = true;
            }
        }
        if (bVar3) {
            pAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Gnd", GND_BTK_SAMPLE);
            i_this->m02BC->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = l_HIO.m68;
            i_this->m155E = 0x96;
            i_this->m03D8 = 1;
        }
        break;
    case 0xA:
        if (i_this->mMoveType != gnd_class::Move_Type_MOVE0_e) {
            return;
        }
        if (checkGround(i_this, 0.0f)) {
            return;
        }
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m155E++;
        pcVar18->mCamera.Stop();
        pcVar18->mCamera.SetTrimSize(2);
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = dVar19;
        player->changeOriginalDemo();
        mDoMtx_YrotS(*calc_mtx, pz->shape_angle.y);
        local_54.x = REG0_F(4) + 150.0f;
        local_54.y = REG0_F(5) + 50.0f;
        local_54.z = REG0_F(6) + 150.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = pz->current.pos + cStack_60;
        i_this->m1570 = pz->eyePos;
        i_this->m1570.y = i_this->m1570.y + (REG0_F(7) - 30.0f);
        pdVar7->m08B0 = 2;
        i_this->mMoveType = gnd_class::Move_Type_DEMOWAIT_e;
        i_this->m15AC = dVar19;
        // fallthrough
    case 0xB:
        cLib_addCalc2(&i_this->m1570.x, pz->eyePos.x, 0.1f, 20.0f);
        cStack_60.y = (pz->eyePos.y + REG0_F(7)) - 30.0f;
        if (cStack_60.y < 40.0f) {
            cStack_60.y = 40.0f;
        }
        cLib_addCalc2(&i_this->m1570.y, cStack_60.y, 0.1f, 20.0f);
        cLib_addCalc2(&i_this->m1570.z, pz->eyePos.z, 0.1f, 20.0f);
        if (i_this->m1560 >= REG0_S(0) + 100) {
            i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = l_HIO.m68;
            i_this->m155E = 0x96;
            pdVar7->m0740 = 1;
            i_this->m03D8 = 2;
        }
        break;
    case 0x14:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_NOPARTNER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m155E++;
        pcVar18->mCamera.Stop();
        pcVar18->mCamera.SetTrimSize(2);
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = dVar19;
        player->changeOriginalDemo();
        dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        i_this->m15AC = REG0_F(0x12) + 5.0f;
        i_this->m155C = 100;
        // fallthrough
    case 0x15:
        i_this->m1570 = player->current.pos;
        i_this->m1570.y += REG8_F(10) + 50.0f;
        mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);
        local_54.x = REG8_F(1) + 200.0f;
        local_54.y = REG8_F(2) + 30.0f;
        local_54.z = REG8_F(3) + 300.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = cStack_60 + player->current.pos;
        if (i_this->m1560 > (s16)(REG12_S(0) + 0xf)) {
            i_this->m155E++;
            i_this->m1560 = 0;
            break;
        }
        dVar19 = REG8_F(0xd);
        break;
    case 0x16:
        cLib_addCalc2(&i_this->m1570.x, actor->current.pos.x, 0.5f, REG8_F(6) + 70.0f);
        cLib_addCalc2(&i_this->m1570.y, actor->eyePos.y + REG8_F(4), 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m1570.z, actor->current.pos.z + REG8_F(5), 0.5f, REG8_F(6) + 70.0f);
        mDoMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        local_54.x = REG8_F(7) + -300.0f;
        local_54.y = REG8_F(8) + 100.0f;
        local_54.z = REG8_F(9) + 500.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = cStack_60 + actor->current.pos;
        if (0x1e < i_this->m1560) {
            i_this->m1560 = 0;
            if (i_this->mMoveType != gnd_class::Move_Type_DAMAGE_e) {
                i_this->mMoveType = gnd_class::Move_Type_MOVE0_e;
                i_this->mAnmType = 0;
                actor->current.angle.y = actor->shape_angle.y;
                i_this->m0302[1] = l_HIO.m68;
            }
            i_this->m155E = 0x96;
        }
        break;
    case 0x64:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m155E++;
        pcVar18->mCamera.Stop();
        pcVar18->mCamera.SetTrimSize(2);
        // fallthrough
    case 0x65:
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = 0.0f;
        i_this->m1560 = 0;
        player->changeOriginalDemo();
        i_this->mDamageCyl.OffCoSetBit();
        anm_init(i_this, GND_BCK_COMBO_GANON, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        player->changeDemoMode(daPy_demo_c::DEMO_UNK_070_e);
        pdVar7->m073F = 1;
        i_this->m155E++;
        player->setPlayerPosAndAngle(&cStack_60, (s16)0);
        actor->current.pos = cStack_60;
        actor->shape_angle.y = 0;
        actor->current.angle.y = 0;
        pz->current.pos = cStack_60;
        pz->current.pos.x += 400.0f;
        i_this->m13F0[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_8384, &actor->current.pos);
        i_this->m13F0[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_8385, &actor->current.pos);
        i_this->m1562 = 0;
        // fallthrough
    case 0x66:
        for (s32 i = 0; i < 2; i++) {
            if (i_this->m13F0[i] != NULL) {
                if (i_this->mpMorf->isStop()) {
                    i_this->m13F0[i]->becomeInvalidEmitter();
                    i_this->m13F0[i] = 0;
                } else {
                    i_this->m13F0[i]->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x30));
                }
            }
        }
        if (i_this->m1560 == 34) {
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_LAST_HIT_1, 0);
        }
        if (i_this->m1560 == 74) {
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_LAST_HIT_2, 0);
        }
        if (i_this->m1560 == 30) {
            mDoAud_seStart(JA_SE_LK_SW_CRT_HIT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        iVar9 = i_this->m1560;
        if ((((iVar9 == 19) || (iVar9 == REG0_S(4) + 0x27)) || (iVar9 == REG0_S(5) + 0x43)) || (iVar9 == REG0_S(6) + 0x45)) {
            i_this->m1562++;
            if ((i_this->m1562 == 2) || (i_this->m1562 == 4)) {
                i_this->m1588.x = std::fabsf(f_ctr[i_this->m1562].x - f_ctr[i_this->m1562 - 1].x);
                i_this->m1588.y = std::fabsf(f_ctr[i_this->m1562].y - f_ctr[i_this->m1562 - 1].y);
                i_this->m1588.z = std::fabsf(f_ctr[i_this->m1562].z - f_ctr[i_this->m1562 - 1].z);
                i_this->m157C.x = std::fabsf(f_eye[i_this->m1562].x - f_eye[i_this->m1562 - 1].x);
                i_this->m157C.y = std::fabsf(f_eye[i_this->m1562].y - f_eye[i_this->m1562 - 1].y);
                i_this->m157C.z = std::fabsf(f_eye[i_this->m1562].z - f_eye[i_this->m1562 - 1].z);
                i_this->m15A8 = std::fabsf(f_fovy[i_this->m1562] - f_fovy[i_this->m1562 - 1]);
            }
        }
        if (((i_this->m1562 == 0) || (i_this->m1562 == 1)) || (i_this->m1562 == 3)) {
            i_this->m1570 = f_ctr[i_this->m1562];
            i_this->m1564 = f_eye[i_this->m1562];
            i_this->m15A4 = f_fovy[i_this->m1562];
        } else {
            i_this->m15A0 = REG0_F(0) + 0.1f;
            dVar20 = (REG0_F(1) + 0.4f);
            cLib_addCalc2(&i_this->m1570.x, f_ctr[i_this->m1562].x, dVar20, i_this->m1588.x * i_this->m15A0);
            cLib_addCalc2(&i_this->m1570.y, f_ctr[i_this->m1562].y, dVar20, i_this->m1588.y * i_this->m15A0);
            cLib_addCalc2(&i_this->m1570.z, f_ctr[i_this->m1562].z, dVar20, i_this->m1588.z * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.x, f_eye[i_this->m1562].x, dVar20, i_this->m157C.x * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.y, f_eye[i_this->m1562].y, dVar20, i_this->m157C.y * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.z, f_eye[i_this->m1562].z, dVar20, i_this->m157C.z * i_this->m15A0);
            cLib_addCalc2(&i_this->m15A4, f_fovy[i_this->m1562], dVar20, i_this->m15A8 * i_this->m15A0);
        }
        if (i_this->m1560 == 74) {
            mDoAud_seStart(JA_SE_CM_GN_SW_SPIKE_HEAD, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            mDoAud_bgmStop(10);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (i_this->m1560 == 74) {
            mDoGph_gInf_c::startFadeOut((s8)(REG0_S(8) + 50));
            mDoGph_gInf_c::setFadeColor((JUtility::TColor&)g_saftyWhiteColor);
        }
        if (i_this->m1560 == 124) {
            dComIfGp_setNextStage("GTower", 2, 0, 9, 0.0f, 0, 1, 7);
        }
        break;
    case 0x96:
        pcVar18->mCamera.SetTrimSize(0);
        pcVar18->mCamera.Start();
        dMeter_mtrShow();
        dComIfGp_event_reset();
        i_this->m155E = 0;
        player->cancelOriginalDemo();
        i_this->m155C = 1;
        break;
    default:
        break;
    }
    if (i_this->m155E != 0) {
        f32 fx = i_this->m15AC * cM_ssin(i_this->m1560 * 0x3500);
        f32 fy = i_this->m15AC * cM_scos(i_this->m1560 * 0x3900);
        local_e4.x = i_this->m1564.x + fx;
        local_e4.y = i_this->m1564.y + fy;
        local_e4.z = i_this->m1564.z;
        local_f0.x = i_this->m1570.x + fx;
        local_f0.y = i_this->m1570.y + fy;
        local_f0.z = i_this->m1570.z;
        s16 r6 = (dVar19 + (i_this->m15AC * cM_scos(i_this->m02CC * 0x1c00) * 7.5f));
        pcVar18->mCamera.Set(local_f0, local_e4, r6, i_this->m15A4);
        cLib_addCalc0(&i_this->m15AC, 1.0f, (REG0_F(0x10) + 1.0f));
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->m1560);
        i_this->m1560++;
    }
}

/* 00006B04-00006D0C       .text body_flash__FP9gnd_class */
void body_flash(gnd_class* i_this) {
    /* Nonmatching */
    float fVar2;
    J3DModel* pJVar10;
    cXyz local_48;

    pJVar10 = i_this->mpMorf->getModel();
    if (i_this->m142E != 0) {
        i_this->m142E++;
        if (i_this->m142E > 100) {
            i_this->m142E = 0;
        }
    }
    for (s32 i = 0; i < 15; i++) {
        if (i_this->m142E == fl_check_d[i]) {
            i_this->m13F8[i] = 100;
        }
        if (i_this->m13F8[i] != 0) {
            i_this->m13F8[i]--;
            MTXCopy(pJVar10->getAnmMtx(eff_d[i]), *calc_mtx);
            MtxPosition(&i_this->m14A8[i], &local_48);
            fVar2 = (REG8_F(0) + 0.01f) * (i_this->m13F8[i] * fl_scale[i]);
            if (i_this->m1430[i] == NULL) {
                i_this->m1430[i] = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &local_48);
            } else {
                i_this->m1430[i]->setGlobalTranslation(local_48.x, local_48.y, local_48.z);
                JGeometry::TVec3<f32> scale(fVar2, fVar2, fVar2);
                i_this->m1430[i]->setGlobalScale(scale);
            }
        } else {
            if (i_this->m1430[i] != NULL) {
                i_this->m1430[i]->becomeInvalidEmitter();
                i_this->m1430[i] = NULL;
            }
        }
    }
}

/* 00006D0C-000076B8       .text daGnd_Execute__FP9gnd_class */
static BOOL daGnd_Execute(gnd_class* i_this) {
    static s32 w_d[] = {0x1B, 0x2D};
    static s32 w_asi[] = {0x04, 0x07};
    static s32 at_spl_d[] = {0x00, 0x01, 0x02, 0x05, 0x06, 0x07, 0x0A};
    fopEn_enemy_c* actor = &i_this->actor;
    s8 fVar1;
    f32 fVar4;
    J3DModel* pJVar7;
    cM3dGSph* sph;
    cXyz local_8c;
    cXyz local_98;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (i_this->m02B4 == 0) {
        i_this->mMoveType = gnd_class::Move_Type_DEMOWAIT_e;
    }
    if (j_demo(i_this)) {
        i_this->mpMorf->calc();
        i_this->m02C0->play();
        i_this->m02BC->play();
        i_this->m02C4->play();
        pJVar7 = i_this->mpMorf->getModel();
        pJVar7->setBaseScale(actor->scale);
        mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
        mDoMtx_stack_c::ZXYrotM(actor->shape_angle.x, actor->shape_angle.y, actor->shape_angle.z);
        pJVar7->setBaseTRMtx(mDoMtx_stack_c::get());
        ke_move(i_this);
        return TRUE;
    }
    setRipple(i_this);
    if (pz == NULL) {
        pz = (daPz_c*)fpcM_Search(z_s_sub, i_this);
    }
    if (l_HIO.m10 != 0) {
        i_this->m03D8 = l_HIO.m10 - 1;
    }
    if (actor->stealItemBitNo == 0x23) {
        actor->stealItemBitNo++;
        mDoAud_changeBgmStatus(2);
    }
    if ((fopAcM_GetParam(actor) & 0xffU) == 0x23) {
        i_this->mMoveType = gnd_class::Move_Type_YAWAIT_e;
        i_this->m155E = 0x14;
        fopAcM_SetParam(actor, 0);
    }
    i_this->m02CC++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m0302[i] != 0) {
            i_this->m0302[i]--;
        }
    }
    if (i_this->mDamageInvulnerabilityTimer1 != 0) {
        i_this->mDamageInvulnerabilityTimer1--;
    }
    if (i_this->mDamageInvulnerabilityTimer2 != 0) {
        i_this->mDamageInvulnerabilityTimer2--;
    }
    if (i_this->m0318 != 0) {
        i_this->m0318--;
    }
    if (i_this->m142C != 0) {
        i_this->m142C--;
    }
    if (l_HIO.m05 == 0) {
        gnd_move(i_this);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        g_env_light.settingTevStruct(TEV_TYPE_BG1, &actor->current.pos, &i_this->m0320);
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        if (i_this->mpMorf->isStop()) {
            attack_eff_remove(i_this);
        }
        i_this->m02C0->play();
        i_this->m02BC->play();
        i_this->m02C4->play();
    }
    pJVar7 = i_this->mpMorf->getModel();
    fVar4 = l_HIO.m0C;
    actor->scale.z = l_HIO.m0C;
    actor->scale.y = fVar4;
    actor->scale.x = fVar4;
    pJVar7->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    cLib_addCalc0(&i_this->m03E0, (REG0_F(0x11) + 0.5f), (REG0_F(0x12) + 6053.5f));
    mDoMtx_stack_c::YrotM(actor->shape_angle.y + (s16)i_this->m03E0);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    pJVar7->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->mpMorf->calc();
    local_8c.setall(0.0f);
    MTXCopy(pJVar7->getAnmMtx(0x30), *calc_mtx);
    MtxPosition(&local_8c, &actor->eyePos);
    actor->attention_info.position = actor->current.pos;
    actor->attention_info.position.y += 290.0f;
    i_this->mDamageCyl.SetC(actor->current.pos);
    i_this->mDamageCyl.SetR(80.0f);
    i_this->mDamageCyl.SetH(220.0f);
    dComIfG_Ccsp()->Set(&i_this->mDamageCyl);
    i_this->mHeadSph.SetC(actor->eyePos);
    i_this->mHeadSph.SetR((REG0_F(0xb) + 70.0f) * l_HIO.m0C);
    dComIfG_Ccsp()->Set(&i_this->mHeadSph);
    MTXCopy(pJVar7->getAnmMtx(9), *calc_mtx);
    MtxPosition(&local_8c, &local_98);
    local_98.y -= REG0_F(10) + 20.0f;
    i_this->mChestSph.SetC(local_98);
    i_this->mChestSph.SetR((REG0_F(0xb) + 170.0f) * l_HIO.m0C);
    dComIfG_Ccsp()->Set(&i_this->mChestSph);
    if (i_this->m03D7 != 0) {
        i_this->m03D7--;
        i_this->mDamageCyl.OffTgSetBit();
        i_this->mHeadSph.OffTgSetBit();
    } else {
        i_this->mDamageCyl.OnTgSetBit();
        i_this->mHeadSph.OnTgSetBit();
    }
    for (s32 i = 0; i < 2; i++) {
        MTXCopy(pJVar7->getAnmMtx(w_asi[i]), *calc_mtx);
        local_8c.setall(0.0f);
        MtxPosition(&local_8c, &i_this->m15C8[i]);
        if ((i_this->m13B8[i] != 0) && (player->mCutType != 5 || (i_this->m03D8 >= 2))) {
            i_this->mSwordSphs[i].SetAtHitMark(0xd);
            if (i_this->m13B8[i] == 3) {
                MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
                mDoMtx_YrotM(*calc_mtx, actor->shape_angle.y);
                local_8c.x = REG0_F(0xe);
                local_8c.y = REG0_F(0xf) + 100.0f;
                local_8c.z = REG0_F(0x10) + 300.0f;
                i_this->m13BC[i] = at_spl_d[l_HIO.m84];
            } else if (i_this->m13B8[i] >= 10) {
                MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
                if (i_this->m13B8[i] == 10) {
                    local_8c.x = 0.0f;
                    local_8c.y = REG0_F(0xf) + 60.0f;
                    local_8c.z = 0.0f;
                } else {
                    local_8c.x = 0.0f;
                    local_8c.y = REG0_F(0x10) + 230.0f;
                    local_8c.z = 0.0f;
                }
                i_this->m13C4[i] = REG0_F(0x11) + 100.0f;
                if (l_HIO.m45 != 0) {
                    i_this->mSwordSphs[i].OffTgShield();
                    i_this->mSwordSphs[i].OnTgNoHitMark();
                } else {
                    i_this->mSwordSphs[i].OnTgShield();
                    i_this->mSwordSphs[i].OffTgNoHitMark();
                }
            } else {
                MTXCopy(pJVar7->getAnmMtx(w_d[i]), *calc_mtx);
                local_8c.x = REG0_F(9) + 50.0f;
                local_8c.y = REG0_F(10);
                local_8c.z = REG0_F(0xb);
                i_this->m13BC[i] = at_spl_d[l_HIO.m82];
                if (i_this->m13B8[i] == 4) {
                    i_this->mSwordSphs[i].SetAtHitMark(0xf);
                }
            }
            sph = &i_this->mSwordSphs[i];
            sph->SetR(i_this->m13C4[i]);
            i_this->mSwordSphs[i].SetAtSpl((dCcG_At_Spl)i_this->m13BC[i]);
            MtxPosition(&local_8c, &i_this->m13A0[i]);
            sph->SetC(i_this->m13A0[i]);
            mDoMtx_YrotS(*calc_mtx, actor->shape_angle.y);
            local_8c.x = 0.0f;
            local_8c.y = 0.0f;
            local_8c.z = 1.0f;
            MtxPosition(&local_8c, &local_98);
            i_this->mSwordSphs[i].SetAtVec(local_98);

            if (i_this->m13B8[i] < 10) {
                if (player->current.pos.y - i_this->mAcch.GetGroundH() < 50.0f) {
                    i_this->mSwordSphs[i].OnAtSetBit();
                } else {
                    i_this->mSwordSphs[i].OffAtSetBit();
                }
            } else {
                i_this->mSwordSphs[i].OffAtSetBit();
            }
            i_this->m13B8[i] = 0;
            i_this->m13C4[i] = REG0_F(0xd) + 150.0f;
        } else {
            i_this->m13CC[i] = 0;
            i_this->mSwordSphs[i].SetC(non_pos);
        }
        dComIfG_Ccsp()->Set(&i_this->mSwordSphs[i]);
    }
    if (i_this->mParryTimer != 0) {
        i_this->mParryTimer--;
        i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
    }
    if (i_this->m13D1 != 0) {
        i_this->m13D1--;
        i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_ROLL_PARRY;
    }
    actor->mBtNowFrame = 15.0f;
    fVar1 = i_this->mNextParryOpeningType;
    actor->mBtStartFrame = 10.0f;
    actor->mBtEndFrame = 20.0f;
    actor->mBtMaxDis = 10000.0f;
    actor->mBtAttackType = fVar1;
    actor->mBtMaxDis = REG0_F(4) + 600.0f;
    i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_NONE;
    if (l_HIO.m89 != 0) {
        l_HIO.m89 = 0;
        i_this->m155E = 10;
    }
    demo_camera(i_this);
    ke_move(i_this);
    attack_eff_move(i_this);
    body_flash(i_this);
    return TRUE;
}

/* 000076B8-000076C0       .text daGnd_IsDelete__FP9gnd_class */
static BOOL daGnd_IsDelete(gnd_class*) {
    return TRUE;
}

/* 000076C0-00007738       .text daGnd_Delete__FP9gnd_class */
static BOOL daGnd_Delete(gnd_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Gnd");
    i_this->m15B4.remove();
    if (i_this->m15E0 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

/* 00007738-00007A78       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    mDoExt_McaMorf* morf;
    J3DAnmTevRegKey* pJVar2;
    int iVar3;
    J3DAnmTextureSRTKey* pAnm;
    J3DAnmTexPattern* pJVar6;
    gnd_class* i_this = (gnd_class*)a_this;

    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Gnd", GND_BDL_GND),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Gnd", GND_BCK_SAMPLE),
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
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->m02C0 = new mDoExt_brkAnm();
    if (i_this->m02C0 == NULL) {
        return FALSE;
    }
    pJVar2 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Gnd", GND_BRK_SAMPLE);
    iVar3 = i_this->m02C0->init(i_this->mpMorf->getModel()->getModelData(), pJVar2, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    i_this->m02BC = new mDoExt_btkAnm();
    if (i_this->m02BC == NULL) {
        return FALSE;
    }
    pAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Gnd", GND_BTK_SAMPLE);
    iVar3 = i_this->m02BC->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    i_this->m02C4 = new mDoExt_btpAnm();
    if (i_this->m02C4 == NULL) {
        return FALSE;
    }
    pJVar6 = (J3DAnmTexPattern*)dComIfG_getObjectRes("Gnd", GND_BTP_SAMPLE);
    iVar3 = i_this->m02C4->init(i_this->mpMorf->getModel()->getModelData(), pJVar6, 1, 2, 1.0f, 0, -1, false, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    iVar3 = i_this->m0B64.init(4, 0x14, 0);
    if (!iVar3) {
        return FALSE;
    }
    return TRUE;
}

/* 00007AC0-00007CFC       .text daGnd_Create__FP10fopAc_ac_c */
static cPhs_State daGnd_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_SWORD,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Nrm_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, -150.0f, 0.0f},
            /* Radius */ 100.0f,
            /* Height */ 100.0f,
        }},
    };
    static dCcD_SrcSph head_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_SWORD,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
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
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph chest_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_LIGHT_ARROW,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
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
            /* Radius */ 100.0f,
        }},
    };
    static dCcD_SrcSph wepon_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
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
            /* Radius */ 70.0f,
        }},
    };

    fopAcM_SetupActor(a_this, gnd_class);
    gnd_class* i_this = (gnd_class*)a_this;
    fopEn_enemy_c* actor = &i_this->actor;
    float fVar1;
    cPhs_State res;

    res = dComIfG_resLoad(&i_this->mPhase, "Gnd");
    if (res == cPhs_COMPLEATE_e) {
        pz = NULL;
        i_this->m02B4 = (s8)fopAcM_GetParam(i_this) & 0xf;
        if (!fopAcM_entrySolidHeap(actor, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        actor->attention_info.distances[2] = 4;
        if (hio_set == 0) {
            i_this->m15E0 = 1;
            hio_set = 1;
            l_HIO.mNo = mDoHIO_createChild("ガノンＤ", &l_HIO); // Ganon D
        }
        fVar1 = REG0_F(5) + 150.0f;
        actor->mBtHeight = REG0_F(6) + 400.0f;
        actor->mBtBodyR = fVar1;
        i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
        i_this->mAcch.OffSameActorChk();
        i_this->mAcchCir.SetWall(200.0f, 200.0f);
        i_this->mStts.Init(0xff, 0xff, actor);
        i_this->mDamageCyl.Set(cc_cyl_src);
        i_this->mDamageCyl.SetStts(&i_this->mStts);
        i_this->mHeadSph.Set(head_sph_src);
        i_this->mHeadSph.SetStts(&i_this->mStts);
        i_this->mChestSph.Set(chest_sph_src);
        i_this->mChestSph.SetStts(&i_this->mStts);
        for (s32 i = 0; i < 2; i++) {
            i_this->mSwordSphs[i].Set(wepon_sph_src);
            i_this->mSwordSphs[i].SetStts(&i_this->mStts);
        }
        daGnd_Execute(i_this);
        actor->max_health = 0x4b;
        actor->health = 0x4b;
        if (i_this->m02B4 != 0) {
            mDoAud_bgmStart(JA_BGM_GANON_BATTLE);
        }
    }
    return res;
}

static actor_method_class l_daGnd_Method = {
    (process_method_func)daGnd_Create,
    (process_method_func)daGnd_Delete,
    (process_method_func)daGnd_Execute,
    (process_method_func)daGnd_IsDelete,
    (process_method_func)daGnd_Draw,
};

actor_process_profile_definition g_profile_GND = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_GND,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(gnd_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_GND,
    /* Actor SubMtd */ &l_daGnd_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
