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
#if VERSION == VERSION_DEMO
#include "m_Do/m_Do_controller_pad.h"
#endif
#include "m_Do/m_Do_graphic.h"
#include "JSystem/JUtility/JUTReport.h"

enum Action {
    ACTION_MOVE0_e = 0,
    ACTION_ATTACK0_e = 1,
    ACTION_ATTACK1_e = 2,
    ACTION_ATTACK2_e = 3,
    ACTION_ATTACKPZ_e = 4,
    ACTION_ATTACK_LAST_e = 5,
    ACTION_DEFENCE0_e = 10,
    ACTION_DAMAGE_e = 11,
    ACTION_DEMOWAIT_e = 20,
    ACTION_YAWAIT_e = 21,
    ACTION_FINISH_e = 30,
};

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
    m6E = 0xF;
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

#if VERSION == VERSION_DEMO
static f32 dummy_4327() {
    return 1.8f;
};
#endif

/* 0000023C-000003CC       .text j_demo__FP9gnd_class */
static u8 j_demo(gnd_class* i_this) {
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
            i_this->mpBtpAnm->init(i_this->mpMorf->getModel()->getModelData(), pJVar1, 1, 0, 1.0f, 0, -1, true, 0);
        }
        pAnm = (J3DAnmTextureSRTKey*)demo_actor->getP_BtkData("Gnd");
        if (pAnm != NULL) {
            i_this->mpBtkAnm->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
        }
        pJVar2 = (J3DAnmTevRegKey*)demo_actor->getP_BrkData("Gnd");
        if (pJVar2 != NULL) {
            i_this->mpBrkAnm->init(i_this->mpMorf->getModel()->getModelData(), pJVar2, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
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
static s32 checkGround(gnd_class* i_this, f32 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    return actor->current.pos.y < param_2 + 1.0f;
}

/* 000003EC-00000510       .text setRipple__FP9gnd_class */
static void setRipple(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (checkGround(i_this, 0.0f)) {
        if ((i_this->mAcch.ChkGroundHit()) && (dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_WATER_e)) {
            if (i_this->mRippleCb.getEmitter() == NULL) {
                static cXyz ripple_scale(1.0f, 1.0f, 1.0f);
                dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &actor->current.pos, NULL, &ripple_scale, 0xFF, &i_this->mRippleCb);
                if (i_this->mRippleCb.getEmitter() != NULL) {
                    i_this->mRippleCb.setRate(0.0f);
                }
            }
        }
    } else {
        i_this->mRippleCb.remove();
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
    dPa_name::ID_AK_SN_GNDAATTACK1HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK1HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDAATTACK1FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK1FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDAATTACK1BLURL00,
    dPa_name::ID_AK_SP_GNDAATTACK1BLURR00,
    dPa_name::ID_AK_SN_GNDAATTACK2HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK2HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDAATTACK2FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK2FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDAATTACK2BLURL00,
    dPa_name::ID_AK_SP_GNDAATTACK2BLURR00,
    dPa_name::ID_AK_SN_GNDAATTACK3HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK3HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDAATTACK3FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDAATTACK3FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDAATTACK3BLURL00,
    dPa_name::ID_AK_SP_GNDAATTACK3BLURR00,
    dPa_name::ID_AK_SN_GNDBATTACK1HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDBATTACK1HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDBATTACK1FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDBATTACK1FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDBATTACK1BLURL00,
    dPa_name::ID_AK_SP_GNDBATTACK1BLURR00,
    dPa_name::ID_AK_SN_GNDBATTACK2HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDBATTACK2HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDBATTACK2FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDBATTACK2FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDBATTACK2BLURL00,
    dPa_name::ID_AK_SP_GNDBATTACK2BLURR00,
    dPa_name::ID_AK_SN_GNDBATTACK3THANDSPLASH_8396,
    dPa_name::ID_AK_SN_GNDBATTACK3THANDSPLASH_8397,
    dPa_name::ID_AK_SN_GNDBATTACK3TFOOTSPLASH_8398,
    dPa_name::ID_AK_SN_GNDBATTACK3TFOOTSPLASH_8399,
    dPa_name::ID_AK_SP_GNDBATTACK3TBLURL00,
    dPa_name::ID_AK_SP_GNDBATTACK3TBLURR00,
    dPa_name::ID_AK_SN_GNDBATTACK3AHANDSPLASH_839A,
    dPa_name::ID_AK_SN_GNDBATTACK3AHANDSPLASH_839B,
    dPa_name::ID_AK_SN_GNDBATTACK3AFOOTSPLASH_839C,
    dPa_name::ID_AK_SN_GNDBATTACK3AFOOTSPLASH_839D,
    dPa_name::ID_AK_SP_GNDBATTACK3ABLURL00,
    dPa_name::ID_AK_SP_GNDBATTACK3ABLURR00,
    dPa_name::ID_AK_SN_GNDBATTACK3EHANDSPLASH_839E,
    dPa_name::ID_AK_SN_GNDBATTACK3EHANDSPLASH_839F,
    dPa_name::ID_AK_SN_GNDBATTACK3EFOOTSPLASH_83A0,
    dPa_name::ID_AK_SN_GNDBATTACK3EFOOTSPLASH_83A1,
    dPa_name::ID_AK_SP_GNDBATTACK3EBLURL00,
    dPa_name::ID_AK_SP_GNDBATTACK3EBLURR00,
    dPa_name::ID_AK_SN_GNDJATTACKTHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKTHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDJATTACKTFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKTFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDJATTACKTBLURL00,
    dPa_name::ID_AK_SP_GNDJATTACKTBLURR00,
    dPa_name::ID_AK_SN_GNDJATTACKJHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKJHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDJATTACKJFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKJFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDJATTACKJBLURL00,
    dPa_name::ID_AK_SP_GNDJATTACKJBLURR00,
    dPa_name::ID_AK_SN_GNDJATTACKAHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKAHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDJATTACKAFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKAFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDJATTACKABLURL00,
    dPa_name::ID_AK_SP_GNDJATTACKABLURR00,
    dPa_name::ID_AK_SN_GNDJATTACKEHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKEHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDJATTACKEFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDJATTACKEFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDJATTACKEBLURL00,
    dPa_name::ID_AK_SP_GNDJATTACKEBLURR00,
    dPa_name::ID_AK_SN_GNDNATTACK1HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDNATTACK1HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDNATTACK1FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDNATTACK1FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDNATTACK1BLURL00,
    dPa_name::ID_AK_SP_GNDNATTACK1BLURR00,
    dPa_name::ID_AK_SN_GNDNATTACK2HANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDNATTACK2HANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDNATTACK2FOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDNATTACK2FOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDNATTACK2BLURL00,
    dPa_name::ID_AK_SP_GNDNATTACK2BLURR00,
    dPa_name::ID_AK_SN_GNDCOUNTERLHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERLHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDCOUNTERLFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERLFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDCOUNTERLBLURL00,
    dPa_name::ID_AK_SP_GNDCOUNTERLBLURR00,
    dPa_name::ID_AK_SN_GNDCOUNTERRHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERRHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDCOUNTERRFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERRFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDCOUNTERRBLURL00,
    dPa_name::ID_AK_SP_GNDCOUNTERRBLURR00,
    dPa_name::ID_AK_SN_GNDCOUNTERRHANDSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERRHANDSPLASHR00,
    dPa_name::ID_AK_SN_GNDCOUNTERRFOOTSPLASHL00,
    dPa_name::ID_AK_SN_GNDCOUNTERRFOOTSPLASHR00,
    dPa_name::ID_AK_SP_GNDCOUNTERRBLURL00,
    dPa_name::ID_AK_SP_GNDCOUNTERRBLURR00,
    dPa_name::ID_NONE,
    dPa_name::ID_NONE,
    dPa_name::ID_NONE,
    dPa_name::ID_AK_SN_GNDKICKSPLASH00,
    dPa_name::ID_NONE,
    dPa_name::ID_NONE
};

static s32 ke_set_index[] = {0x1B, 0x1B, 0x2D, 0x2D};
static f32 ke_set_offsetxz[] = {-4.0f, 4.0f, -4.0f, 4.0f};

/* 0000054C-000005DC       .text splash_set__FP9gnd_class */
static void splash_set(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar3;

    pJVar3 = dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDLANDINGSPLASH00, &actor->current.pos);
    if (pJVar3 != NULL) {
        pJVar3->setGlobalPrmColor(i_this->mTevStr.mColorC0.r, i_this->mTevStr.mColorC0.g, i_this->mTevStr.mColorC0.b);
    }
}

/* 000005DC-000006B4       .text attack_eff_set__FP9gnd_classi */
static void attack_eff_set(gnd_class* i_this, int param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    for (s32 i = 0; i < 6; i++) {
        if (attack_eff_id[(i + param_2 * 6)] != 0) {
            i_this->mpAttackEffEmitter[i] = dComIfGp_particle_set(attack_eff_id[(i + param_2 * 6)], &actor->current.pos);
            ;
            if (i <= 3) {
                i_this->mpAttackEffEmitter[i]->setGlobalPrmColor(i_this->mTevStr.mColorC0.r, i_this->mTevStr.mColorC0.g, i_this->mTevStr.mColorC0.b);
            }
        }
    }
}

/* 000006B4-00000738       .text attack_eff_move__FP9gnd_class */
static void attack_eff_move(gnd_class* i_this) {
    J3DModel* pJVar3 = i_this->mpMorf->getModel();
    for (s32 i = 0; i < 6; i++) {
        if (i_this->mpAttackEffEmitter[i] != NULL) {
            i_this->mpAttackEffEmitter[i]->setGlobalRTMatrix(pJVar3->getAnmMtx(attack_eff_joint_d[i]));
        }
    }
}

/* 00000738-0000077C       .text attack_eff_remove__FP9gnd_class */
static void attack_eff_remove(gnd_class* i_this) {
    for (s32 i = 0; i < 6; i++) {
        if (i_this->mpAttackEffEmitter[i] != NULL) {
            i_this->mpAttackEffEmitter[i]->becomeInvalidEmitter();
            i_this->mpAttackEffEmitter[i] = NULL;
        }
    }
}

/* 0000077C-00000900       .text anm_init__FP9gnd_classifUcfi */
static void anm_init(gnd_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Gnd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Gnd", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Gnd", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
    attack_eff_remove(i_this);
    s32 unk_array[] = {
        GND_BCK_AATTACK1,
        GND_BCK_AATTACK2,
        GND_BCK_AATTACK3,
        GND_BCK_BATTACK1,
        GND_BCK_BATTACK2,
        GND_BCK_BATTACK3_TAME,
        GND_BCK_BATTACK3_ATTACK,
        GND_BCK_BATTACK3_END,
        GND_BCK_JATTACK_TAME,
        GND_BCK_JATTACK_JUMP,
        GND_BCK_JATTACK_ATTACK,
        GND_BCK_JATTACK_END,
        GND_BCK_NOM_ATTACK1,
        GND_BCK_NOM_ATTACK2,
        GND_BCK_COUNTERL,
        GND_BCK_COUNTERR,
        GND_BCK_COMBO_GANON,
        GND_BCK_KERI2
    };
    for (s32 i = 0; i < 18; i++) {
        if (bckFileIdx == unk_array[i]) {
            attack_eff_set(i_this, i);
            return;
        }
    }
}

/* 00000900-0000094C       .text z_s_sub__FPvPv */
static void* z_s_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_PZ)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 0000094C-00000C38       .text daGnd_Draw__FP9gnd_class */
static BOOL daGnd_Draw(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* pModel;
    cXyz local_34;

#if VERSION > VERSION_DEMO
    if (i_this->m155C > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->m155C);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->m155C == 1) {
        i_this->m155C = 0;
        mDoGph_gInf_c::offBlure();
    }
#endif
    pModel = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
#if VERSION > VERSION_DEMO
    if (i_this->mArrowHitFlashTimer != 0) {
        s16 uVar2 = actor->tevStr.mFogColor.r + i_this->m1426;
        if (uVar2 > 0xFF) {
            uVar2 = 0xFF;
        }
        s16 uVar3 = actor->tevStr.mFogColor.g + i_this->m1426;
        if (uVar3 > 0xFF) {
            uVar3 = 0xFF;
        }
        s16 uVar4 = actor->tevStr.mFogColor.g + (i_this->m1426 / 2);
        if (uVar4 > 0xFF) {
            uVar4 = 0xFF;
        }
        if (i_this->mArrowHitFlashTimer > (s16)(REG8_S(5) + 20)) {
            cLib_addCalcAngleS2(&i_this->m1426, 0x118, 1, 0x1e);
            cLib_addCalc2(&i_this->m1428, -50000.0f, 1.0f, 5000.0f);
        } else {
            cLib_addCalcAngleS2(&i_this->m1426, 0, 1, 0xe);
            cLib_addCalc0(&i_this->m1428, 1.0f, 2500.0f);
        }
        actor->tevStr.mFogColor.r = uVar2 & 0xFF;
        actor->tevStr.mFogColor.g = uVar3 & 0xFF;
        actor->tevStr.mFogColor.b = uVar4 & 0xFF;
        actor->tevStr.mFogStartZ = actor->tevStr.mFogStartZ + i_this->m1428;
    }
#endif
    g_env_light.setLightTevColorType(pModel, &actor->tevStr);
    i_this->mpBrkAnm->entry(pModel->getModelData());
    i_this->mpBtkAnm->entry(pModel->getModelData());
    i_this->mpBtpAnm->entry(pModel->getModelData());
    i_this->mpMorf->entryDL();
    local_34.set(actor->current.pos.x, actor->current.pos.y + 400.0f + REG0_F(18), actor->current.pos.z);
    i_this->m02C8 = dComIfGd_setShadow(
        i_this->m02C8,
        1,
        pModel,
        &local_34,
        REG0_F(19) + 1300.0f,
        200.0f,
        actor->current.pos.y,
        i_this->mAcch.GetGroundH(),
        i_this->mAcch.m_gnd,
        &actor->tevStr,
        0,
        1.0f,
        &dDlst_shadowControl_c::mSimpleTexObj
    );
    //! @bug(?): Same ID as Jalhalla?
    dSnap_RegistFig(DSNAP_TYPE_UNKCE, actor, 1.0f, 1.0f, 1.0f);
    if (l_HIO.m07 != 0) {
#ifdef __MWERKS__
        i_this->mLineMat.update(20, REG0_F(3) + 2.25f, (GXColor){0xFF, 100, 0, 0xFF}, 2, &actor->tevStr);
#else
        GXColor local_38 = (GXColor){0xFF, 100, 0, 0xFF};
        i_this->mLineMat.update(20, REG0_F(3) + 2.25f, local_38, 2, &actor->tevStr);
#endif
        dComIfGd_set3DlineMat(&i_this->mLineMat);
    }
    return TRUE;
}

/* 00000C38-00000C6C       .text player_view_check__FP9gnd_classs */
static s32 player_view_check(gnd_class* i_this, s16 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar2;
    s16 uVar1;

    sVar2 = actor->shape_angle.y - param_2;
    uVar1 = sVar2;
    if (uVar1 < 0) {
        uVar1 = -sVar2;
    }
    if ((u16)(uVar1 & 0xFFFF) < 0x4000) {
        return TRUE;
    }
    return FALSE;
}

/* 00000C6C-00000F24       .text ke_control__FP9gnd_classP8gnd_ke_sf */
static void ke_control(gnd_class* i_this, gnd_ke_s* param_2, f32 param_3) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 dVar12;
    cXyz* pcVar6;
    cXyz* pcVar5;
    f32 dVar8;
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
    f32 dVar11 = (REG0_F(1) + -5.0f);
    f32 dVar10 = (REG0_F(2) + 0.73f);
    for (i = 1; i < 20; i++, pcVar6++, pcVar5++) {
        x = (pcVar5->x + (pcVar6->x - pcVar6[-1].x));
        dVar8 = (dVar11 + (pcVar6->y + pcVar5->y));
        if (dVar8 < dVar12) {
            dVar8 = dVar12;
        }
        y = (dVar8 - pcVar6[-1].y);
        z = pcVar5->z + (pcVar6->z - pcVar6[-1].z);
        s16 iVar3 = -cM_atan2s(y, z);
        int iVar4 = cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z)));
        cMtx_XrotS(*calc_mtx, iVar3);
        cMtx_YrotM(*calc_mtx, iVar4);
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
static void ke_pos_set(gnd_class* i_this, gnd_ke_s* param_2, int index) {
    cXyz* pcVar3;

    pcVar3 = i_this->mLineMat.getPos(index);
    for (s32 i = 0; i < 20; pcVar3++, i++) {
        *pcVar3 = param_2->m000[i];
    }
}

/* 00000F68-00001140       .text ke_move__FP9gnd_class */
static void ke_move(gnd_class* i_this) {
    gnd_ke_s* pDst;
    J3DModel* pJVar3;
    f32 fVar8;
    cXyz local_78;
    cXyz local_84;

    pDst = &i_this->m03E4[0];
    pJVar3 = i_this->mpMorf->getModel();
    for (s32 i = 0; i < 4; i++, pDst++) {
        MTXCopy(pJVar3->getAnmMtx(ke_set_index[i]), *calc_mtx);
        local_84.set(*calc_mtx[0][0], *calc_mtx[0][1], *calc_mtx[0][2]);
        fVar8 = local_84.abs();
        if ((dComIfGp_evmng_startCheck("endhr")) && (dComIfGp_demo_get()->getFrameNoMsg() >= 300)) {
            fVar8 = 0.0f;
        }
        local_78.set((-20.0f + REG0_F(4)), ke_set_offsetxz[i], ke_set_offsetxz[i]);
        MtxPosition(&local_78, pDst->m000);
        ke_control(i_this, pDst, fVar8);
        ke_pos_set(i_this, pDst, i);
    }
}

/* 00001140-00001278       .text pos_move__FP9gnd_classSc */
static void pos_move(gnd_class* i_this, s8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;

    if (param_2 == 0) {
        local_20 = i_this->m02D4 - actor->current.pos;
        cLib_addCalcAngleS2(&actor->current.angle.y, cM_atan2s(local_20.x, local_20.z), DEMO_SELECT(REG0_S(3) + 5, 5), i_this->m02F0 * i_this->m02F4);
        cLib_addCalc2(&i_this->m02F4, 1.0f, 1.0f, 0.05f);
    }
    cLib_addCalc2(&actor->speedF, i_this->m02F8, 1.0f, 6.0f);
    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = actor->speedF;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_20, &local_2c);
    actor->speed.x = local_2c.x;
    actor->speed.z = local_2c.z;
    actor->current.pos += actor->speed;
    actor->current.pos.y += actor->speed.y;
    actor->speed.y += actor->gravity;
    actor->gravity = -5.0f;
}

/* 00001278-00001334       .text wait_set__FP9gnd_class */
static void wait_set(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m03D8 <= 1) {
        anm_init(i_this, GND_BCK_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GN_LAUGH_WAIT, 0);
    } else {
        anm_init(i_this, GND_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    }
}

/* 00001334-00001974       .text move0__FP9gnd_class */
static void move0(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar2;
    f32 fVar4;
    f32 dVar9;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar9 = fopAcM_searchPlayerDistance(actor);
    int frame = i_this->mpMorf->getFrame();
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
        if (player_view_check(i_this, fopAcM_searchPlayerAngleY(actor))) {
            if ((dVar9 > l_HIO.m3C) && (i_this->m0302[1] == 0)) {
                i_this->mAnmType = 0;
            } else if (dVar9 < l_HIO.m2C) {
                i_this->mAnmType = 0x14;
            } else if (i_this->m0302[1] == 0) {
                if (cM_rndF(100.0f) < l_HIO.m48) {
                    i_this->mAction = ACTION_ATTACK1_e;
                    if (cM_rndF(1.0f) < 0.5f) {
                        i_this->mAnmType = 0;
                    } else {
                        i_this->mAnmType = 1;
                    }
                } else {
                    i_this->mAction = ACTION_ATTACK0_e;
                    if ((i_this->m03D8 == 0) || (l_HIO.m11 == 1)) {
                        i_this->mAnmType = 0;
                    } else if ((i_this->m03D8 == 1) || (l_HIO.m11 == 2)) {
                        i_this->mAnmType = 5;
                    } else if (cM_rndF(1.0f) < 0.5f) {
                        i_this->mAnmType = 0;
                    } else {
                        i_this->mAnmType = 5;
                    }
                }
            }
        }
        break;
    case 3:
        actor->gravity = l_HIO.m28;
        if (frame == 12) {
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
        fopAcM_seStart(actor, JA_SE_CM_GN_ROBE, 0);
        actor->gravity = l_HIO.m28;
        if (actor->speed.y < 0.0f) {
            anm_init(i_this, GND_BCK_HI_JUMP_END1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 5:
        fopAcM_seStart(actor, JA_SE_CM_GN_ROBE, 0);
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
static void attack0(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    s8 bVar2;
    s8 bVar3;
    s8 bVar4;
    s8 bVar5;

    daPy_py_c* player1 = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 dVar15 = fopAcM_searchPlayerDistance(actor);
    int frame = i_this->mpMorf->getFrame();
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
        if (frame < 23) {
            i_this->m02F8 = l_HIO.m54;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((frame >= 13) && (frame <= 16)) {
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
        if (frame < 12) {
            i_this->m02F8 = l_HIO.m50;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((frame >= 5) && (frame <= 10)) {
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
        if (frame > l_HIO.m6A) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
        }
        break;
    case 3:
        bVar5 = true;
        if (frame < 25) {
            i_this->m02F8 = l_HIO.m50;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((frame >= 6) && (frame <= 22)) {
            i_this->m13B8[0] = 1;
            i_this->m13B8[1] = 1;
        }
        if ((frame >= l_HIO.m6C) && (frame <= l_HIO.m6E)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_JUMP_PARRY;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mAction = ACTION_MOVE0_e;
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
        if ((frame >= 9) && (frame < 20)) {
            i_this->m02F8 = l_HIO.m54;
        } else {
            i_this->m02F8 = l_HIO.m4C;
        }
        if ((frame >= 13) && (frame <= 17)) {
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
        if ((frame >= 8) && (frame <= 23)) {
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
        if (frame > l_HIO.m70) {
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
        if ((frame >= l_HIO.m72) && (frame <= l_HIO.m74)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_ROLL_PARRY;
        }
        i_this->m02F8 = 0.0f;
        if ((frame >= 3) && (frame <= 5)) {
            i_this->m13B8[0] = 1;
            i_this->m13B8[1] = 1;
            i_this->m13C4[1] = 60.0f;
            i_this->m13C4[0] = 60.0f;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType = 0xB;
            i_this->m0302[0] = l_HIO.m76;
        }
        break;
    case 0xB:
        if (i_this->m03D8 >= 2) {
            i_this->m03D7 = 2;
        }
        actor->current.angle.y = actor->shape_angle.y;
        if (i_this->m0302[0] == 0) {
            bVar4 = true;
        }
        break;
    case 0xF:
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
        actor->gravity = REG0_F(11) + -2.0f;
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
        if (frame <= 4) {
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
        if ((frame >= 0) && (frame <= 4)) {
            i_this->m13B8[1] = 3;
            i_this->m13C4[1] = REG0_F(12) + 170.0f;
        }
        if ((frame == 20) && (i_this->m03D4 == 0)) {
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
                    i_this->mAnmType = 0xF;
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
        if (i_this->mpMorf->isStop()) {
            if (player_view_check(i_this, fopAcM_searchPlayerAngleY(actor))) {
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
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 4, (s16)(bVar2 << 0xc));
    }
    if (bVar3) {
        cLib_addCalc2(&actor->current.pos.x, player1->current.pos.x, 0.8f, std::fabsf(i_this->m02E0.x));
        cLib_addCalc2(&actor->current.pos.z, player1->current.pos.z, 0.8f, std::fabsf(i_this->m02E0.z));
    }
    if (bVar4) {
        i_this->mAction = ACTION_MOVE0_e;
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
static void attack1(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int frame = i_this->mpMorf->getFrame();
    s8 bVar4 = false;
    f32 fVar3 = REG0_F(13) + 110.0f;
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
        if ((frame >= 15) && (frame <= 18)) {
            i_this->m13B8[0] = 1;
        } else {
            i_this->m02D4 = player->current.pos;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    case 6:
        if ((frame >= 12) && (frame <= 34)) {
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
        i_this->mAction = ACTION_MOVE0_e;
        i_this->mAnmType = 0;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0302[1] = 0;
    }
}

/* 00002B68-00002D7C       .text attack2__FP9gnd_class */
static void attack2(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar3;
    s8 bVar4;

    int frame = i_this->mpMorf->getFrame();
    bVar4 = false;
    fVar3 = REG0_F(13) + 110.0f;
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
        if (frame >= 4) {
            i_this->m13B8[0] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    case 3:
        if (frame >= 6) {
            i_this->m13B8[1] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            bVar4 = true;
        }
        break;
    }
    if (bVar4) {
        i_this->mAction = ACTION_MOVE0_e;
        i_this->mAnmType = 0;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0302[1] = 0;
    }
}

/* 00002D7C-00003688       .text attackPZ__FP9gnd_class */
static void attackPZ(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar3;
    daPz_c* pdVar5;
    J3DAnmTextureSRTKey* pAnm;
    f32 dVar16;
    f32 fVar17;
    cXyz local_3c;
    cXyz cStack_48;
    cXyz local_54;

    pdVar5 = pz;
    local_54 = pz->current.pos - actor->current.pos;
    fVar17 = local_54.abs();
    dVar16 = fVar17;
    s16 sVar14 = cM_atan2s(actor->current.pos.x - pz->current.pos.x, actor->current.pos.z - pz->current.pos.z);
    i_this->mDamageInvulnerabilityTimer1 = 5;
    i_this->m13CE = 0;
    int frame = i_this->mpMorf->getFrame();
    bVar3 = false;
    switch (i_this->mAnmType) {
    case 0:
        if (dVar16 > (REG6_F(1) + 1000.0f)) {
            cMtx_YrotS(*calc_mtx, sVar14);
            local_3c.set(0.0f, 0.0f, -(REG0_F(1) + 1000.0f));
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
            i_this->mpBtkAnm->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
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
        actor->gravity = REG0_F(17) + -0.5f;
        if (frame == 12) {
            actor->speed.y = REG0_F(19) + 10.0f;
            i_this->m02F8 = (dVar16 * (REG0_F(18) + 0.018f));
            splash_set(i_this);
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GND_BCK_HI_JUMP_LOOP, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 7:
        fopAcM_seStart(actor, JA_SE_CM_GN_ROBE, 0);
        actor->gravity = REG0_F(17) + -0.5f;
        if (actor->speed.y < 0.0f) {
            anm_init(i_this, GND_BCK_HI_JUMP_END1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 8:
        fopAcM_seStart(actor, JA_SE_CM_GN_ROBE, 0);
        actor->gravity = REG0_F(17) + -0.5f;
        i_this->m02F0 = 0.0f;
        if (checkGround(i_this, 0.0f)) {
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
        if (i_this->mpMorf->isStop()) {
            i_this->mAnmType++;
            anm_init(i_this, GND_BCK_BINTA2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BINTA2);
            fopAcM_monsSeStart(actor, JA_SE_CV_GN_ATTACK_ZELDA, 0);
            i_this->m13EC = dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDBINTASPLASH00, &actor->current.pos);
            if (i_this->m13EC != NULL) {
                i_this->m13EC->setGlobalPrmColor(i_this->mTevStr.mColorC0.r, i_this->mTevStr.mColorC0.g, i_this->mTevStr.mColorC0.b);
            }
        }
        break;
    case 0xB:
        if (frame == REG0_S(5) + 2) {
#if VERSION > VERSION_DEMO
            i_this->m155C = 0x96;
#endif
            pdVar5->m08B0 = 1;
            pdVar5 = pz;
            fopAcM_seStart(pdVar5, JA_SE_LK_LAST_HIT, 0);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (frame == REG0_S(6) + 2) {
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
    cMtx_YrotS(*calc_mtx, i_this->m031A);
    local_3c.set(REG0_F(16) + -20.0f, 0.0f, REG0_F(17) + 100.0f);
    MtxPosition(&local_3c, &cStack_48);
    i_this->m02D4 = pz->current.pos + cStack_48;
    pos_move(i_this, 0);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x2000);
    if (bVar3) {
        cLib_addCalc2(&actor->current.pos.x, i_this->m02D4.x, 0.2f, std::fabsf(i_this->m02E0.x));
        cLib_addCalc2(&actor->current.pos.z, i_this->m02D4.z, 0.2f, std::fabsf(i_this->m02E0.z));
    }
}

static s32 bougyo_d[] = {GND_BCK_BOUGYO1, GND_BCK_BOUGYO2, GND_BCK_BOUGYO4, GND_BCK_BOUGYO6, GND_BCK_BOUGYO7, GND_BCK_BOUGYO5};

/* 00003688-000038B0       .text attack_last__FP9gnd_class */
static void attack_last(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int frame = i_this->mpMorf->getFrame();
    i_this->m13C4[1] = REG0_F(13) + 110.0f;
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
        if (frame > l_HIO.m7C) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_GANONDORF_FINISHER_PARRY;
        }
        break;
    case 2:
        if ((frame >= l_HIO.m7E) && (frame <= l_HIO.m80)) {
            i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_GANONDORF_FINISHER_PARRY;
        }
        if ((frame >= 6) && (frame <= 9)) {
            i_this->m13B8[1] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mAction = ACTION_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = 0;
        }
        break;
    }
    if (player->checkLastComboWait()) {
        i_this->mAction = ACTION_FINISH_e;
        i_this->mAnmType = 0;
        i_this->mDamageInvulnerabilityTimer1 = 5;
        i_this->m13CE = 0;
    }
}

/* 000038B0-000042D0       .text defence0__FP9gnd_class */
static void defence0(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    int iVar3;
    f32 dVar7;
    f32 fVar8;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s8 cVar7 = 0;
    i_this->m03D7 = 10;
    dVar7 = fopAcM_searchPlayerDistance(actor);
    if ((actor->current.pos.y > REG0_F(11) + (i_this->mAcch.GetGroundH() + 200.0f)) && (i_this->mAnmType < 0xF)) {
        i_this->mAnmType = 0x14;
    }
    switch (i_this->mAnmType) {
    case 0:
#if VERSION == VERSION_DEMO
        if (((player->getCutType() == 15) && (cM_rndF(1.0f) < 0.8f)) || ((i_this->m03DB == 1 && (cM_rndF(1.0f) < 0.05f)) && (i_this->m03D8 == 2))) {
            i_this->m03DC = 5;
            s16 angle = fopAcM_searchPlayerAngleY(actor);
            angle += REG0_S(4);
            i_this->m03DE = angle + 0x7800;
        } else if (player->current.pos.y - i_this->mAcch.GetGroundH() > 50.0f) {
            i_this->m03DC = 0;
        }
#else
        if ((i_this->m03D8 == 2) && (player->current.pos.y - i_this->mAcch.GetGroundH() > REG0_F(19) + 300.0f)) {
            i_this->m03DC = 0;
            i_this->mBlockHitCount = 2;
        } else {
            if (((player->getCutType() == 15) && (cM_rndF(1.0f) < 0.8f)) || ((i_this->m03DB == 1 && (cM_rndF(1.0f) < 0.05f)) && (i_this->m03D8 == 2))) {
                i_this->m03DC = 5;
                s16 angle = fopAcM_searchPlayerAngleY(actor);
                angle += REG0_S(4);
                i_this->m03DE = angle + 0x7800;
            }
        }
#endif
        anm_init(i_this, bougyo_d[i_this->m03DC], DEMO_SELECT(5.0f, 4.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
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
#if VERSION > VERSION_DEMO
        if (((i_this->m03D8 == 2) && (player->current.pos.y - i_this->mAcch.GetGroundH() > REG0_F(19) + 300.0f)) && (i_this->m03DC != 0)) {
            i_this->m03DC = 0;
            i_this->mBlockHitCount = 2;
            anm_init(i_this, bougyo_d[i_this->m03DC], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            goto block_15;
        }
#endif
        actor->gravity = REG0_F(11) + -4.0f;
        if (checkGround(i_this, 0.0f)) {
            i_this->m02F8 = 0.0f;
            if (l_HIO.m12 == 0) {
                if (((dVar7 < (REG0_F(2) + 400.0f)) && (i_this->m03DC != 5)) && (i_this->m0302[1] == (s16)(REG0_S(5) + 1))) {
                    i_this->mAction = ACTION_ATTACK2_e;
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
                    i_this->mAction = ACTION_ATTACK2_e;
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
                    i_this->mAnmType = 0xF;
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
    case 0xF:
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
        } else if (checkGround(i_this, 0.0f)) {
            i_this->m02F8 = 0.0f;
            anm_init(i_this, GND_BCK_BOUGYO4, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAnmType++;
        }
        break;
    case 0x16:
        if (i_this->mpMorf->isStop()) {
            cVar7 = 1;
        }
    }
    if (i_this->m03DC != 5) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 2, REG0_S(8) + 0x2000);
    } else {
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m03DE, 2, REG0_S(8) + 0x2000);
    }
    i_this->m13B8[0] = 10;
    i_this->m13B8[1] = 0xB;
    pos_move(i_this, 1);
    if (cVar7 != 0) {
        actor->current.angle.y = actor->shape_angle.y;
        if (cVar7 == 1) {
            i_this->mAction = ACTION_MOVE0_e;
            i_this->mAnmType = 0;
        } else {
            i_this->mAction = ACTION_ATTACK0_e;
            anm_init(i_this, GND_BCK_BATTACK3_TAME, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GND_BAS_BATTACK3_TAME);
            i_this->mAnmType = 8;
        }
    }
}

/* 000042D0-00004330       .text finish__FP9gnd_class */
static void finish(gnd_class* i_this) {
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
static void damage(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->m13CE = 0;
    if (i_this->m03D9 != 0) {
        if (i_this->m03D9 == 1) {
            i_this->mAction = ACTION_ATTACKPZ_e;
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
            i_this->m0302[1] = 0xF;
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
#if VERSION == VERSION_DEMO
        if ((actor->health < 30) && (i_this->m03D8 == 2))
#else
        if ((((i_this->m155E == 0) && (i_this->m0302[0] < 30)) && (actor->health < 25)) && (i_this->m03D8 == 2))
#endif
        {
            if ((player_view_check(i_this, fopAcM_searchPlayerAngleY(actor))) && (fopAcM_searchPlayerDistance(actor) < l_HIO.m78)) {
                i_this->mAction = ACTION_ATTACK_LAST_e;
                i_this->mAnmType = 0;
                i_this->m13CE = 1;
                i_this->mDamageInvulnerabilityTimer2 = 30;
                return;
            }
        }
        if (i_this->m0302[0] == 0) {
            i_this->mAction = ACTION_MOVE0_e;
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
static void damage_check(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar5;
    s16 uVar7;
    cCcD_Obj* pcVar9;
    s16 sVar11;
    fopAc_ac_c* pfVar10;
    JPABaseEmitter* pJVar10;
    daArrow_c* pfVar13;
    cXyz local_5c;
    cXyz local_68;
    CcAtInfo local_50;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    for (s32 i = 0; i < 2; i++) {
        if (i_this->mSwordSphs[i].ChkTgHit()) {
            pcVar9 = i_this->mSwordSphs[i].GetTgHitObj();
            def_se_set(actor, pcVar9, 0x40);
            i_this->m0310 = REG0_F(19) + 30.0f;
            i_this->m0314 = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            i_this->mBlockHitCount++;
            i_this->mBlockHit = 1;
            dKy_SordFlush_set(*i_this->mSwordSphs[i].GetTgHitPosP(), 0);
            local_5c.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, i_this->mSwordSphs[i].GetTgHitPosP(), &actor->shape_angle, &local_5c);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDHITNG00, i_this->mSwordSphs[i].GetTgHitPosP(), &actor->shape_angle);
        }
        if (i_this->mSwordSphs[i].ChkAtHit()) {
            pcVar9 = i_this->mSwordSphs[i].GetAtHitObj();
            if (pcVar9->GetStts() == NULL) {
                pfVar10 = NULL;
            } else {
                pfVar10 = pcVar9->GetStts()->GetActor();
            }
            if (fopAcM_GetName(pfVar10) == PROC_PLAYER) {
                if (i_this->mAnmType == 0x16) {
                    i_this->m03D4 = 1;
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                } else if (player->checkPlayerGuard()) {
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                    if ((i_this->mAnmType == 2) || (i_this->mAnmType == 7)) {
                        i_this->m03D4 = 1;
                    }
                }
            }
        }
    }
    if (i_this->mDamageInvulnerabilityTimer1 != 0) {
        return;
    }
    if (i_this->mChestSph.ChkTgHit()) {
        s8 bVar4;
        bVar4 = false;
        local_50.mpObj = i_this->mChestSph.GetTgHitObj();
#if VERSION > VERSION_DEMO
        if (local_50.mpObj == NULL) {
            return;
        }
#endif
        if (local_50.mpObj->GetStts() == NULL) {
            pfVar13 = NULL;
        } else {
            pfVar13 = (daArrow_c*)local_50.mpObj->GetStts()->GetActor();
        }
        if (((pfVar13 != NULL) && (fopAcM_GetName(pfVar13) == PROC_ARROW)) && (pfVar13->isSetByZelda() != false)) {
            sVar11 = actor->shape_angle.y - pfVar13->current.angle.y;
            uVar7 = sVar11;
            if (uVar7 < 0) {
                uVar7 = -sVar11;
            }
            if ((((u16)(uVar7 & 0xFFFF) < 0x4000) && (i_this->m03D8 < 2)) || (pfVar13->isLinkReflect() != 0)) {
                bVar4 = true;
            } else {
                i_this->m13CE = 2;
            }
        }
        if ((!bVar4) && (i_this->m13CE != 0)) {
            i_this->mAction = ACTION_DEFENCE0_e;
            if (i_this->m13CE == 1) {
                pcVar9 = i_this->mChestSph.GetTgHitObj();
                def_se_set(actor, pcVar9, 0x40);
                i_this->m0310 = REG0_F(19) + 30.0f;
                i_this->m0314 = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                dKy_SordFlush_set(*i_this->mChestSph.GetTgHitPosP(), 0);
                local_68.setall(2.0f);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, i_this->mChestSph.GetTgHitPosP(), &actor->shape_angle, &local_68);
                dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDHITNG00, i_this->mChestSph.GetTgHitPosP(), &actor->shape_angle);
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
            i_this->mAnmType = 0xF;
            i_this->mBlockHitCount = 0;
            return;
        }
    }
    if ((i_this->mDamageInvulnerabilityTimer2 == 0) || (i_this->mChestSph.ChkTgHit())) {
        s8 bVar4;
        bVar4 = false;
        if ((i_this->mDamageCyl.ChkTgHit()) || (i_this->mHeadSph.ChkTgHit() || (i_this->mChestSph.ChkTgHit()))) {
            i_this->mDamageInvulnerabilityTimer1 = 7;
            bVar5 = false;
            if (i_this->mHeadSph.ChkTgHit()) {
                local_50.mpObj = i_this->mHeadSph.GetTgHitObj();
                local_50.pParticlePos = i_this->mHeadSph.GetTgHitPosP();
                bVar4 = true;
            } else if (i_this->mChestSph.ChkTgHit()) {
                local_50.mpObj = i_this->mChestSph.GetTgHitObj();
                local_50.pParticlePos = i_this->mChestSph.GetTgHitPosP();
                bVar5 = true;
            } else {
                local_50.mpObj = i_this->mDamageCyl.GetTgHitObj();
                local_50.pParticlePos = i_this->mDamageCyl.GetTgHitPosP();
            }
            local_50.mpActor = cc_at_check(actor, &local_50);
            if ((bVar5) && (local_50.mpActor != NULL)) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDLIGHTARROW00, local_50.pParticlePos, &local_50.mpActor->current.angle);
                dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDLIGHTARROW01, local_50.pParticlePos, &local_50.mpActor->current.angle);
#if VERSION > VERSION_DEMO
                i_this->m142E = 1;
                i_this->mArrowHitFlashTimer = REG8_S(4) + 0x1e;
                for (s32 i = 0; i < 15; i++) {
                    i_this->m14A8[i].x = cM_rndFX(30.0f);
                    i_this->m14A8[i].y = cM_rndFX(30.0f);
                    i_this->m14A8[i].z = cM_rndFX(30.0f);
                }
                i_this->m15AC = REG0_F(19) + 20.0f;
#endif
            } else if ((player->getCutType() == 5) || (player->getCutType() == 15)) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDASPECIALHIT00, local_50.pParticlePos, &actor->shape_angle);
            } else {
                pJVar10 = dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDHITOK00, local_50.pParticlePos, &actor->shape_angle);
                if (pJVar10 != NULL) {
                    pJVar10->setGlobalPrmColor(i_this->mTevStr.mColorC0.r, i_this->mTevStr.mColorC0.g, i_this->mTevStr.mColorC0.b);
                }
            }
#if VERSION == VERSION_DEMO
            if (actor->health <= 30) {
                if (l_HIO.m10 == 1) {
                    actor->health = 30;
                    l_HIO.m10 = 2;
                    i_this->m03D9 = 2;
                }
            } else if ((actor->health <= 60) && (l_HIO.m10 == 0)) {
                if (fopAcM_GetName(local_50.mpActor) == PROC_ARROW) {
                    JUTReport(440, 240, "YA HIT2 ");
                    pfVar13 = (daArrow_c*)local_50.mpActor;
                    if (pfVar13->isSetByZelda() != 0) {
                        i_this->m03D9 = 1;
                        JUTReport(440, 260, "YA HIT3 ");
                    }
                } else {
                    actor->health = 60;
                }
            }
#else
            if (actor->health <= 25) {
                if (i_this->m03D8 == 1) {
                    actor->health = 25;
                    i_this->m03D8 = 2;
                    i_this->m03D9 = 2;
                }
            } else if ((actor->health <= 50) && (i_this->m03D8 == 0)) {
                if (fopAcM_GetName(local_50.mpActor) == PROC_ARROW) {
                    pfVar13 = (daArrow_c*)local_50.mpActor;
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
#endif
            if (i_this->mAction != ACTION_DAMAGE_e) {
                i_this->mAction = ACTION_DAMAGE_e;
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
static void* shot_s_sub(void* param_1, void*) {
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
static void demowait(gnd_class* i_this) {
    i_this->mDamageInvulnerabilityTimer1 = 5;
    i_this->m13CE = 0;
}

/* 000050B0-000050C8       .text yawait__FP9gnd_class */
static void yawait(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    actor->current.pos.y = 0.0f;
    i_this->m13CE = 0;
}

/* 000050C8-000054F0       .text gnd_move__FP9gnd_class */
static void gnd_move(gnd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar6;
    s16 uVar5;
    daArrow_c* pvVar7;
    f32 dVar9;
    f32 fVar10;
    cXyz local_28;
    cXyz cStack_34;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mAction) {
    case ACTION_MOVE0_e:
        move0(i_this);
        break;
    case ACTION_ATTACK0_e:
        attack0(i_this);
        break;
    case ACTION_ATTACK1_e:
        attack1(i_this);
        break;
    case ACTION_ATTACK2_e:
        attack2(i_this);
        break;
    case ACTION_ATTACKPZ_e:
        attackPZ(i_this);
        break;
    case ACTION_ATTACK_LAST_e:
        attack_last(i_this);
        break;
    case ACTION_DEFENCE0_e:
        defence0(i_this);
        break;
    case ACTION_DAMAGE_e:
        damage(i_this);
        break;
    case ACTION_DEMOWAIT_e:
        demowait(i_this);
        break;
#if VERSION > VERSION_DEMO
    case ACTION_YAWAIT_e:
        yawait(i_this);
        break;
#endif
    case ACTION_FINISH_e:
        finish(i_this);
        return;
    }
    if ((i_this->m03D8 >= 2) && (i_this->mAction != ACTION_DAMAGE_e)) {
        i_this->mDamageInvulnerabilityTimer2 = 3;
    }
    if (((player->getCutType() == 5) || (player->getCutType() == 15)) && (i_this->m03D8 < 2)) {
        i_this->m13CE = 0;
        i_this->m03D7 = 0;
    }
    if (i_this->m13CE != 0) {
        s8 bVar2;
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
                    if ((u16)(uVar5 & 0xFFFF) < 0x4000) {
                        i_this->m13CE = 0;
                    } else {
                        i_this->mAction = ACTION_DEFENCE0_e;
                        if (checkGround(i_this, 50.0f)) {
                            i_this->mAnmType = 0xF;
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
        if ((bVar2) || (player->getCutType() != 0 && (dVar9 < l_HIO.m40))) {
            if (i_this->mAction != ACTION_DEFENCE0_e) {
                i_this->mAction = ACTION_DEFENCE0_e;
                i_this->mAnmType = 0;
                i_this->mBlockHitCount = 0;
                i_this->m03DB = 0;
                i_this->m03DC = 0;
            }
            i_this->m0302[0] = DEMO_SELECT(REG0_S(3) + 10, 10);
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
    f32 f1 = i_this->m0310;
    f32 f0 = 0.01f;
    if (f1 > f0) {
        local_28.x = 0.0f;
        local_28.y = 0.0f;
        local_28.z = f1;
        cMtx_YrotS(*calc_mtx, i_this->m0314);
        MtxPosition(&local_28, &cStack_34);
        actor->current.pos += cStack_34;
        cLib_addCalc0(&i_this->m0310, 1.0f, (REG0_F(12) + 7.0f));
    }
}

static f32 f_fovy[] = {66.75f, 64.25f, 64.25f, 44.25f, 44.25f};

/* 000054F0-00006B04       .text demo_camera__FP9gnd_class */
static void demo_camera(gnd_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar12;
    J3DAnmTextureSRTKey* pAnm;
    f32 dVar20;
    cXyz local_54;
    cXyz cStack_60;
    cXyz local_90;
#if VERSION > VERSION_DEMO
    cXyz local_e4;
    cXyz local_f0;
#endif

    daPy_py_c* player = daPy_getPlayerActorClass();
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    daPz_c* r28 = pz;
    s8 bVar3 = false;
    local_90.setall(0.0f);
#if VERSION > VERSION_DEMO
    f32 var_f31 = 0.0f;
#endif
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
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = DEMO_SELECT(0.0f, var_f31);
        player->changeOriginalDemo();
#if VERSION > VERSION_DEMO
        i_this->m15AC = var_f31;
#endif
        i_this->m15A4 = REG0_F(6) + 55.0f;
        i_this->m157C.x = REG0_F(0) + 400.0f;
        i_this->m157C.y = REG0_F(1) + 100.0f;
        i_this->m157C.z = REG0_F(2) - 200.0f;
        i_this->m1588.x = REG0_F(3);
        i_this->m1588.y = REG0_F(4) + 200.0f;
        i_this->m1588.z = REG0_F(5);
        // fallthrough
    case 0x2: {
        s16 angle = cM_atan2s(actor->current.pos.x - pz->current.pos.x, actor->current.pos.z - pz->current.pos.z);
        angle += REG0_S(0);
        actor->shape_angle.y = angle + 0x4000;
        actor->current.angle.y = actor->shape_angle.y;
        if (i_this->m1560 > REG0_S(1) + 0x19) {
#if VERSION > VERSION_DEMO
            i_this->m155C = 0x82;
#endif
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
        cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
        MtxPosition(&i_this->m157C, &i_this->m1564);
        MtxPosition(&i_this->m1588, &i_this->m1570);
        if (i_this->m1560 > REG0_S(2) + 0x3c) {
            i_this->m155E++;
            i_this->m1560 = 0;
#if VERSION > VERSION_DEMO
            i_this->m155C = 0x32;
#endif
        }
        break;
    }
    case 0x3:
        if (i_this->m1560 == DEMO_SELECT(REG0_S(3) + 10, 10)) {
            i_this->mAnmType++;
        }
        MtxTrans(pz->current.pos.x, pz->current.pos.y, pz->current.pos.z, false);
        cMtx_YrotM(*calc_mtx, pz->shape_angle.y);
        i_this->m157C.x = REG0_F(10) + 100.0f;
        i_this->m157C.y = REG0_F(11) + 50.0f;
        i_this->m157C.z = REG0_F(12) - 300.0f;
        MtxPosition(&i_this->m157C, &i_this->m1564);
        i_this->m1570 = actor->current.pos;
        i_this->m1570.y += REG0_F(13) + 150.0f;
        sVar12 = fopAcM_searchPlayerAngleY(actor);
        player->setPlayerPosAndAngle(&player->current.pos, (s16)(sVar12 + 0x8000));
        break;
    case 0x4:
        cLib_addCalc2(&i_this->m1570.y, 100.0f, 0.8f, 10.0f);
        if (i_this->m1560 < 0xF) {
            break;
        }
        i_this->m155E = 5;
        i_this->m1560 = 0;
        i_this->m15A4 = 75.0f;
        // fallthrough
    case 0x5:
        cMtx_YrotS(*calc_mtx, player->shape_angle.y);
        local_54.set(REG0_F(4) + -50.0f, REG0_F(5) + 50.0f, REG0_F(6) + 100.0f);
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = player->current.pos + cStack_60;
        i_this->m1570 = player->current.pos;
        i_this->m1570.y += REG0_F(7) + 90.0f;
        cLib_addCalc2(&i_this->m15A4, 55.0f, 0.8f, 10.0f);
#if VERSION > VERSION_DEMO
        i_this->m155C = 0x32;
#endif
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
            i_this->mpBtkAnm->init(i_this->mpMorf->getModel()->getModelData(), pAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            i_this->mAction = ACTION_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = l_HIO.m68;
            i_this->m155E = 0x96;
#if VERSION == VERSION_DEMO
            if (l_HIO.m10 == 0) {
                l_HIO.m10 = 1;
            }
#else
            i_this->m03D8 = 1;
#endif
        }
        break;
    case 0xA:
        if (i_this->mAction != ACTION_MOVE0_e) {
            return;
        }
        switch (checkGround(i_this, 0.0f)) {
        default:
            return;
        case 0:
            if (!actor->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
                return;
            }
        }
        i_this->m155E++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = DEMO_SELECT(0.0f, var_f31);
        player->changeOriginalDemo();
        cMtx_YrotS(*calc_mtx, pz->shape_angle.y);
        local_54.set(REG0_F(4) + 150.0f, REG0_F(5) + 50.0f, REG0_F(6) + 150.0f);
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = pz->current.pos + cStack_60;
        i_this->m1570 = pz->eyePos;
        i_this->m1570.y += REG0_F(7) - 30.0f;
        r28->m08B0 = 2;
        i_this->mAction = ACTION_DEMOWAIT_e;
#if VERSION > VERSION_DEMO
        i_this->m15AC = var_f31;
#endif
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
            i_this->mAction = ACTION_MOVE0_e;
            i_this->mAnmType = 0;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->m0302[1] = l_HIO.m68;
            i_this->m155E = 0x96;
            r28->m0740 = 1;
#if VERSION == VERSION_DEMO
            l_HIO.m10 = 2;
#else
            i_this->m03D8 = 2;
#endif
        }
        break;
#if VERSION == VERSION_DEMO
    case 0x64:
#else
    case 0x14:
#endif
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, DEMO_SELECT(dEvtFlag_STAFF_ALL_e, dEvtFlag_NOPARTNER_e), 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m155E++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
#if VERSION > VERSION_DEMO
        i_this->m1560 = 0;
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = var_f31;
        player->changeOriginalDemo();
        dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        i_this->m15AC = REG0_F(18) + 5.0f;
        i_this->m155C = 100;
        // fallthrough
    case 0x15:
        i_this->m1570 = player->current.pos;
        i_this->m1570.y += REG8_F(10) + 50.0f;
        cMtx_YrotS(*calc_mtx, player->shape_angle.y);
        local_54.x = REG8_F(1) + 200.0f;
        local_54.y = REG8_F(2) + 30.0f;
        local_54.z = REG8_F(3) + 300.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = cStack_60 + player->current.pos;
        if (i_this->m1560 > (s16)(REG12_S(0) + 0xF)) {
            i_this->m155E++;
            i_this->m1560 = 0;
            break;
        }
        var_f31 = REG8_F(13);
        break;
    case 0x16:
        cLib_addCalc2(&i_this->m1570.x, actor->current.pos.x, 0.5f, REG8_F(6) + 70.0f);
        cLib_addCalc2(&i_this->m1570.y, actor->eyePos.y + REG8_F(4), 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m1570.z, actor->current.pos.z + REG8_F(5), 0.5f, REG8_F(6) + 70.0f);
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        local_54.x = REG8_F(7) + -300.0f;
        local_54.y = REG8_F(8) + 100.0f;
        local_54.z = REG8_F(9) + 500.0f;
        MtxPosition(&local_54, &cStack_60);
        i_this->m1564 = cStack_60 + actor->current.pos;
        if (0x1e < i_this->m1560) {
            i_this->m1560 = 0;
            if (i_this->mAction != ACTION_DAMAGE_e) {
                i_this->mAction = ACTION_MOVE0_e;
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
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
// fallthrough
#endif
    case 0x65:
        i_this->m15A4 = 55.0f;
        i_this->m15A0 = 0.0f;
        i_this->m1560 = 0;
        player->changeOriginalDemo();
        i_this->mDamageCyl.OffCoSetBit();
        anm_init(i_this, GND_BCK_COMBO_GANON, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        player->changeDemoMode(daPy_demo_c::DEMO_UNK_070_e);
        r28->m073F = 1;
        i_this->m155E++;
        player->setPlayerPosAndAngle(&local_90, (s16)0);
        actor->current.pos = local_90;
        actor->shape_angle.y = 0;
        actor->current.angle.y = 0;
        pz->current.pos = local_90;
        pz->current.pos.x += 400.0f;
        i_this->m13F0[0] = dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDFINISHOFF00, &actor->current.pos);
        i_this->m13F0[1] = dComIfGp_particle_set(dPa_name::ID_AK_SN_GNDFINISHOFF01, &actor->current.pos);
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
            fopAcM_seStart(actor, JA_SE_LK_SW_CRT_HIT, 0);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        if ((((i_this->m1560 == DEMO_SELECT(REG0_S(3) + 19, 19)) || (i_this->m1560 == REG0_S(4) + 39)) || (i_this->m1560 == REG0_S(5) + 67)) ||
            (i_this->m1560 == REG0_S(6) + 69))
        {
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
            dVar20 = REG0_F(1) + 0.4f;
            cLib_addCalc2(&i_this->m1570.x, f_ctr[i_this->m1562].x, dVar20, i_this->m1588.x * i_this->m15A0);
            cLib_addCalc2(&i_this->m1570.y, f_ctr[i_this->m1562].y, dVar20, i_this->m1588.y * i_this->m15A0);
            cLib_addCalc2(&i_this->m1570.z, f_ctr[i_this->m1562].z, dVar20, i_this->m1588.z * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.x, f_eye[i_this->m1562].x, dVar20, i_this->m157C.x * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.y, f_eye[i_this->m1562].y, dVar20, i_this->m157C.y * i_this->m15A0);
            cLib_addCalc2(&i_this->m1564.z, f_eye[i_this->m1562].z, dVar20, i_this->m157C.z * i_this->m15A0);
            cLib_addCalc2(&i_this->m15A4, f_fovy[i_this->m1562], dVar20, i_this->m15A8 * i_this->m15A0);
        }
        if (i_this->m1560 == 74) {
            fopAcM_seStart(actor, JA_SE_CM_GN_SW_SPIKE_HEAD, 0);
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
#if VERSION == VERSION_DEMO
        if (CPad_CHECK_TRIG_DOWN(0)) {
            player->cancelOriginalDemo();
            i_this->m155E--;
        }
#endif
        break;
    case 0x96:
        camera->mCamera.SetTrimSize(0);
        camera->mCamera.Start();
        dMeter_mtrShow();
        dComIfGp_event_reset();
        i_this->m155E = 0;
        player->cancelOriginalDemo();
#if VERSION > VERSION_DEMO
        i_this->m155C = 1;
#endif
        break;
    default:
        break;
    }
    if (i_this->m155E != 0) {
#if VERSION == VERSION_DEMO
        camera->mCamera.Set(i_this->m1570, i_this->m1564, i_this->m15A4, 0);
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->m1560);
        i_this->m1560++;
#else
        f32 fx = i_this->m15AC * cM_ssin(i_this->m1560 * 0x3500);
        f32 fy = i_this->m15AC * cM_scos(i_this->m1560 * 0x3900);
        local_e4.x = i_this->m1564.x + fx;
        local_e4.y = i_this->m1564.y + fy;
        local_e4.z = i_this->m1564.z;
        local_f0.x = i_this->m1570.x + fx;
        local_f0.y = i_this->m1570.y + fy;
        local_f0.z = i_this->m1570.z;
        s16 r6 = (var_f31 + (i_this->m15AC * cM_scos(i_this->m02CC * 0x1c00) * 7.5f));
        camera->mCamera.Set(local_f0, local_e4, r6, i_this->m15A4);
        cLib_addCalc0(&i_this->m15AC, 1.0f, (REG0_F(16) + 1.0f));
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->m1560);
        i_this->m1560++;
#endif
    }
}

#if VERSION > VERSION_DEMO
static s32 eff_d[] = {0x2F, 0x3C, 0x3D, 0x3E, 0x09, 0x0B, 0x0E, 0x11, 0x0D, 0x10, 0x1D, 0x20, 0x23, 0x1F, 0x22};
static s32 fl_check_d[] = {0x0A, 0x02, 0x02, 0x05, 0x05, 0x0A, 0x0F, 0x14, 0x0D, 0x12, 0x0A, 0x0F, 0x14, 0x0D, 0x12};
static f32 fl_scale[] = {1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f};

/* 00006B04-00006D0C       .text body_flash__FP9gnd_class */
static void body_flash(gnd_class* i_this) {
    f32 fVar2;
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
            i_this->mArrowHitEffectTimer[i] = 100;
        }
        if (i_this->mArrowHitEffectTimer[i] != 0) {
            i_this->mArrowHitEffectTimer[i]--;
            MTXCopy(pJVar10->getAnmMtx(eff_d[i]), *calc_mtx);
            MtxPosition(&i_this->m14A8[i], &local_48);
            fVar2 = (REG8_F(0) + 0.01f) * (i_this->mArrowHitEffectTimer[i] * fl_scale[i]);
            if (i_this->mpArrowHitEmitter[i] == NULL) {
                i_this->mpArrowHitEmitter[i] = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER00, &local_48);
            } else {
                i_this->mpArrowHitEmitter[i]->setGlobalTranslation(local_48.x, local_48.y, local_48.z);
                JGeometry::TVec3<f32> scale(fVar2, fVar2, fVar2);
                i_this->mpArrowHitEmitter[i]->setGlobalScale(scale);
            }
        } else if (i_this->mpArrowHitEmitter[i] != NULL) {
            i_this->mpArrowHitEmitter[i]->becomeInvalidEmitter();
            i_this->mpArrowHitEmitter[i] = NULL;
        }
    }
}
#endif

/* 00006D0C-000076B8       .text daGnd_Execute__FP9gnd_class */
static BOOL daGnd_Execute(gnd_class* i_this) {
    static s32 w_d[] = {0x1B, 0x2D};
    static s32 w_asi[] = {0x04, 0x07};
    static s32 at_spl_d[] = {0x00, 0x01, 0x02, 0x05, 0x06, 0x07, 0x0A};
    fopEn_enemy_c* actor = &i_this->actor;
    f32 fVar4;
    J3DModel* pJVar7;
    cXyz local_8c;
    cXyz local_98;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (i_this->m02B4 == 0) {
        i_this->mAction = ACTION_DEMOWAIT_e;
    }
    if (j_demo(i_this)) {
        i_this->mpMorf->calc();
        i_this->mpBrkAnm->play();
        i_this->mpBtkAnm->play();
        i_this->mpBtpAnm->play();
        pJVar7 = i_this->mpMorf->getModel();
        pJVar7->setBaseScale(actor->scale);
        mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
        mDoMtx_stack_c::ZXYrotM(actor->shape_angle.x, actor->shape_angle.y, actor->shape_angle.z);
        pJVar7->setBaseTRMtx(mDoMtx_stack_c::get());
        ke_move(i_this);
        return TRUE;
    }
#if VERSION > VERSION_DEMO
    setRipple(i_this);
#endif
    if (pz == NULL) {
        pz = (daPz_c*)fpcM_Search(z_s_sub, i_this);
    }
#if VERSION == VERSION_DEMO
    i_this->m03D8 = l_HIO.m10;
#else
    if (l_HIO.m10 != 0) {
        i_this->m03D8 = l_HIO.m10 - 1;
    }
#endif
    if (actor->stealItemBitNo == 0x23) {
        actor->stealItemBitNo++;
        mDoAud_changeBgmStatus(2);
    }
#if VERSION > VERSION_DEMO
    if ((fopAcM_GetParam(actor) & 0xFF) == 0x23) {
        i_this->mAction = ACTION_YAWAIT_e;
        i_this->m155E = 0x14;
        fopAcM_SetParam(actor, 0);
    }
#endif
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
#if VERSION > VERSION_DEMO
    if (i_this->mArrowHitFlashTimer != 0) {
        i_this->mArrowHitFlashTimer--;
    }
#endif
    if (l_HIO.m05 == 0) {
        gnd_move(i_this);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        g_env_light.settingTevStruct(TEV_TYPE_BG1, &actor->current.pos, &i_this->mTevStr);
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        if (i_this->mpMorf->isStop()) {
            attack_eff_remove(i_this);
        }
        i_this->mpBrkAnm->play();
        i_this->mpBtkAnm->play();
        i_this->mpBtpAnm->play();
    }
    pJVar7 = i_this->mpMorf->getModel();
    fVar4 = l_HIO.m0C;
    actor->scale.z = l_HIO.m0C;
    actor->scale.y = fVar4;
    actor->scale.x = fVar4;
    pJVar7->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    cLib_addCalc0(&i_this->m03E0, (REG0_F(17) + 0.5f), (REG0_F(18) + 6053.5f));
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
    i_this->mHeadSph.SetR((REG0_F(11) + 70.0f) * l_HIO.m0C);
    dComIfG_Ccsp()->Set(&i_this->mHeadSph);
    MTXCopy(pJVar7->getAnmMtx(9), *calc_mtx);
    MtxPosition(&local_8c, &local_98);
    local_98.y -= REG0_F(10) + 20.0f;
    i_this->mChestSph.SetC(local_98);
    i_this->mChestSph.SetR((REG0_F(11) + 170.0f) * l_HIO.m0C);
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
        if ((i_this->m13B8[i] != 0) && (player->getCutType() != 5 || (i_this->m03D8 >= 2))) {
            i_this->mSwordSphs[i].SetAtHitMark(0xD);
            if (i_this->m13B8[i] == 3) {
                MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
                cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
                local_8c.set(REG0_F(14), REG0_F(15) + 100.0f, REG0_F(16) + 300.0f);
                i_this->m13BC[i] = at_spl_d[l_HIO.m84];
            } else if (i_this->m13B8[i] >= 10) {
                MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
                if (i_this->m13B8[i] == 10) {
                    local_8c.set(0.0f, REG0_F(15) + 60.0f, 0.0f);
                } else {
                    local_8c.set(0.0f, REG0_F(16) + 230.0f, 0.0f);
                }
                i_this->m13C4[i] = REG0_F(17) + 100.0f;
                if (l_HIO.m45 != 0) {
                    i_this->mSwordSphs[i].OffTgShield();
                    i_this->mSwordSphs[i].OnTgNoHitMark();
                } else {
                    i_this->mSwordSphs[i].OnTgShield();
                    i_this->mSwordSphs[i].OffTgNoHitMark();
                }
            } else {
                MTXCopy(pJVar7->getAnmMtx(w_d[i]), *calc_mtx);
                local_8c.set(REG0_F(9) + 50.0f, REG0_F(10), REG0_F(11));
                i_this->m13BC[i] = at_spl_d[l_HIO.m82];
                if (i_this->m13B8[i] == 4) {
                    i_this->mSwordSphs[i].SetAtHitMark(0xF);
                }
            }
            i_this->mSwordSphs[i].SetR(i_this->m13C4[i]);
            i_this->mSwordSphs[i].SetAtSpl((dCcG_At_Spl)i_this->m13BC[i]);
            MtxPosition(&local_8c, &i_this->m13A0[i]);
            i_this->mSwordSphs[i].SetC(i_this->m13A0[i]);
            cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
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
            i_this->m13C4[i] = REG0_F(13) + 150.0f;
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
    actor->setBtNowFrame(15.0f);
    actor->setBtAttackData(10.0f, 20.0f, 10000.0f, i_this->mNextParryOpeningType);
    actor->setBtMaxDis(REG0_F(4) + 600.0f);
    i_this->mNextParryOpeningType = fopEn_enemy_c::OPENING_NONE;
    if (l_HIO.m89 != 0) {
        l_HIO.m89 = 0;
        i_this->m155E = 10;
    }
    demo_camera(i_this);
    ke_move(i_this);
    attack_eff_move(i_this);
#if VERSION > VERSION_DEMO
    body_flash(i_this);
#endif
    return TRUE;
}

/* 000076B8-000076C0       .text daGnd_IsDelete__FP9gnd_class */
static BOOL daGnd_IsDelete(gnd_class*) {
    return TRUE;
}

/* 000076C0-00007738       .text daGnd_Delete__FP9gnd_class */
static BOOL daGnd_Delete(gnd_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Gnd");
    i_this->mRippleCb.remove();
    if (i_this->m15E0 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

/* 00007738-00007A78       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    J3DAnmTevRegKey* pBrk;
    J3DAnmTextureSRTKey* pBtk;
    J3DAnmTexPattern* pBtp;
    gnd_class* i_this = (gnd_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
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
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Gnd", GND_BRK_SAMPLE);
    if (!i_this->mpBrkAnm->init(i_this->mpMorf->getModel()->getModelData(), pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL) {
        return FALSE;
    }
    pBtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Gnd", GND_BTK_SAMPLE);
    if (!i_this->mpBtkAnm->init(i_this->mpMorf->getModel()->getModelData(), pBtk, true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    i_this->mpBtpAnm = new mDoExt_btpAnm();
    if (i_this->mpBtpAnm == NULL) {
        return FALSE;
    }
    pBtp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Gnd", GND_BTP_SAMPLE);
    if (!i_this->mpBtpAnm->init(i_this->mpMorf->getModel()->getModelData(), pBtp, 1, 2)) {
        return FALSE;
    }
    if (!i_this->mLineMat.init(4, 20, 0)) {
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

    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Gnd");
    if (res == cPhs_COMPLEATE_e) {
        pz = NULL;
        i_this->m02B4 = (s8)fopAcM_GetParam(a_this) & 0xF;
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        a_this->attention_info.distances[2] = 4;
        if (hio_set == 0) {
            i_this->m15E0 = 1;
            hio_set = 1;
            l_HIO.mNo = mDoHIO_createChild("ガノンＤ", &l_HIO); // Ganon D
        }
        actor->initBt(REG0_F(6) + 400.0f, REG0_F(5) + 150.0f);
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcch.OffSameActorChk();
        i_this->mAcchCir.SetWall(200.0f, 200.0f);
        i_this->mStts.Init(0xFF, 0xFF, a_this);
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
        a_this->max_health = DEMO_SELECT(90, 75);
        a_this->health = DEMO_SELECT(90, 75);
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
