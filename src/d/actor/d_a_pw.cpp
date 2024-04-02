/**
 * d_a_pw.cpp
 * Enemy - Poe
 */

#include "d/actor/d_a_pw.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_kankyo_rain.h"
#include "d/d_procname.h"
#include "dolphin/types.h"
#include "f_op/f_op_camera_mng.h"
#include "f_pc/f_pc_manager.h"

enum daPW__BehaviorType {
    VisibleFromStart = 0x0,
    InvisibleAtStart = 0x1,
    OnlyLanternVisibleAtStart = 0x2,
    JalhallaChildA = 0x3,
    JalhallaChildB = 0x4,
    UseDefault = 0xFF
};

enum PW_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    PW_BAS_ATTACK1=0x7,
    PW_BAS_NIGERU1=0x8,
    
    /* BCK */
    PW_BCK_ANSIN1=0xB,
    PW_BCK_ATTACK1=0xC,
    PW_BCK_BUNRETU1=0xD,
    PW_BCK_DAMAGE1=0xE,
    PW_BCK_DAMAGE_K1=0xF,
    PW_BCK_DERUA1=0x10,
    PW_BCK_DERUB1=0x11,
    PW_BCK_DERUB2=0x12,
    PW_BCK_DOKI1=0x13,
    PW_BCK_IDOU1=0x14,
    PW_BCK_IDOU2=0x15,
    PW_BCK_IKIGIRE1=0x16,
    PW_BCK_JITTAIKA1=0x17,
    PW_BCK_KIDUKU1=0x18,
    PW_BCK_KIDUKU2=0x19,
    PW_BCK_KIZETU1=0x1A,
    PW_BCK_NIGERU1=0x1B,
    PW_BCK_PRESS1=0x1C,
    PW_BCK_SIRIMOTI1=0x1D,
    PW_BCK_SYOUTEN1=0x1E,
    PW_BCK_TORITUKI1=0x1F,
    PW_BCK_TORITUKI2=0x20,
    PW_BCK_TORITUKI3=0x21,
    PW_BCK_TORITUKI_WAIT1=0x22,
    PW_BCK_WAIT1=0x23,
    PW_BCK_WAIT2=0x24,
    
    /* BDLM */
    PW_BDL_PW=0x27,
    
    /* BRK */
    PW_BRK_DEFAULT=0x2A,
    PW_BRK_HIT=0x2B,
    PW_BRK_JITTAIKA1=0x2C,
    
    /* BTP */
    PW_BTP_IROGAE1=0x2F,
};

static bool TORITUKI_ON = false;

/* 00000078-00000158       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000158-00000230       .text draw_SUB__FP8pw_class */
void draw_SUB(pw_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y + i_this->m3A4, i_this->current.pos.z);
    cMtx_YrotM(mDoMtx_stack_c::get(), i_this->shape_angle.y);
    cMtx_XrotM(mDoMtx_stack_c::get(), i_this->shape_angle.x);
    cMtx_ZrotM(mDoMtx_stack_c::get(), i_this->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    i_this->mpMorf->calc();
    
    enemy_fire(&i_this->mEnemyFire);

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
}

/* 00000230-000004D4       .text daPW_Draw__FP8pw_class */
static BOOL daPW_Draw(pw_class*) {
    /* Nonmatching */
}

/* 000004D4-00000600       .text anm_init__FP8pw_classifUcfi */
void anm_init(pw_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("AM", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000600-000006F4       .text kantera_break__FP8pw_class */
void kantera_break(pw_class*) {
    /* Nonmatching */
}

/* 000006F4-000007CC       .text Big_pow_gattai_check__FP8pw_class */
void Big_pow_gattai_check(pw_class*) {
    /* Nonmatching */
}

/* 000007CC-000008B0       .text Big_pow_down_check__FP8pw_class */
void Big_pow_down_check(pw_class*) {
    /* Nonmatching */
}

/* 000008B0-0000121C       .text body_atari_check__FP8pw_class */
void body_atari_check(pw_class*) {
    /* Nonmatching */
}

/* 00001258-000016FC       .text kantera_atari_check__FP8pw_class */
void kantera_atari_check(pw_class*) {
    /* Nonmatching */
}

/* 000016FC-000018FC       .text kantera_calc__FP8pw_class */
void kantera_calc(pw_class*) {
    /* Nonmatching */
}

/* 000018FC-00001990       .text BG_check__FP8pw_class */
void BG_check(pw_class* i_this) {
    i_this->mAcchCir.SetWall(70.0f, 140.0f);

    i_this->current.pos.y -= i_this->mCorrectionOffsetY;
    i_this->old.pos.y -= i_this->mCorrectionOffsetY;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->current.pos.y += i_this->mCorrectionOffsetY;
    i_this->old.pos.y += i_this->mCorrectionOffsetY;
}

/* 00001990-00001D60       .text Line_check__FP8pw_class4cXyzUc */
BOOL Line_check(pw_class* i_this, cXyz destPos, u8 r22) {
    fopAc_ac_c* actor = i_this;
    dBgS_LinChk linChk;
    i_this->m314 = destPos;
    if (!r22) {
        cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        cXyz sp14(0.0f, 0.0f, 200.0f);
        MtxPosition(&sp14, &destPos);
        i_this->m314 = destPos + i_this->current.pos;
    }
    i_this->m314.y += 80.0f;
    destPos = i_this->m314;
    i_this->m308 = i_this->current.pos;
    i_this->m308.y += 80.0f;
    linChk.Set(&i_this->m308, &destPos, actor);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return FALSE;
    }
    i_this->m38C = i_this->current.angle.y + 0x8000;
    return TRUE;
}

/* 00002198-00002254       .text alpha_anime__FP8pw_class */
void alpha_anime(pw_class*) {
    /* Nonmatching */
}

/* 00002254-00002400       .text fuwafuwa_calc__FP8pw_class */
void fuwafuwa_calc(pw_class*) {
    /* Nonmatching */
}

/* 00002400-00002560       .text kougen_hani_check__FP8pw_classUc */
void kougen_hani_check(pw_class*, u8) {
    /* Nonmatching */
}

/* 00002560-00002714       .text kyori_sub__FP8pw_class */
void kyori_sub(pw_class*) {
    /* Nonmatching */
}

/* 00002714-0000289C       .text hani_check__FP8pw_class */
BOOL hani_check(pw_class*) {
    /* Nonmatching */
}

/* 0000289C-000029C8       .text next_dousa_check__FP8pw_class */
void next_dousa_check(pw_class*) {
    /* Nonmatching */
}

/* 000029C8-00002A54       .text move_sound__FP8pw_class */
void move_sound(pw_class*) {
    /* Nonmatching */
}

/* 00002A54-00002A90       .text first_mode_change__FP8pw_class */
void first_mode_change(pw_class*) {
    /* Nonmatching */
}

/* 00002A90-00003B08       .text action_dousa__FP8pw_class */
void action_dousa(pw_class* i_this) {
    /* Nonmatching */
    daPy_py_c* player = daPy_getPlayerActorClass();
    camera_class* camera = dComIfGp_getCamera(0);
    cXyz camfwd;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, PW_BCK_WAIT1, 7.0, J3DFrameCtrl::LOOP_REPEAT_e, 1.0, -1);
        i_this->m346 = 0;
        i_this->mState += 1;
        break;
    case 0x1:
        if (fopAcM_searchPlayerDistance(i_this) < 500.0f) {
            anm_init(i_this, PW_BCK_DERUA1, 3.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            i_this->m38C = fopAcM_searchPlayerAngleY(i_this);
            i_this->current.angle.y = i_this->m38C;
            i_this->shape_angle.y = i_this->m38C;
            i_this->m3A4 = -80.0f;
            i_this->m340 = 1;
            i_this->mState += 1;
        }
        break;
    case 0x2:
        i_this->shape_angle.y += 0x1000;
        cLib_addCalc0(&i_this->m3A4, 1.0f, 3.0f);
        i_this->m39A += 7;
        if (i_this->m39A > 100) {
            i_this->m39A = 100;
        }
        if (i_this->mpMorf->checkFrame(25.0f)) {
            i_this->m3A4 = 0.0f;
            first_mode_change(i_this);
            i_this->m38C = fopAcM_searchPlayerAngleY(i_this);
            JPABaseEmitter* particle = dComIfGp_particle_set(0x82EE, &i_this->m2CC, &i_this->shape_angle);
            if (particle != NULL) {
                particle->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x17)); // j_pw_item_r1 joint
            }
            i_this->attention_info.flags = 0;
            i_this->mState = 0x0A;
        }
        break;
    case 0x9:
        i_this->m39A = 0;
        i_this->m39C = 0;
        i_this->mState += 1;
        // Fall-through
    case 0xA:
        if (i_this->mBehaviorType == InvisibleAtStart) {
            i_this->m38C = fopAcM_searchPlayerAngleY(i_this);
        }
        i_this->mKanteraID = fopAcM_create(PROC_KANTERA, 0xFF000001, &i_this->m2CC, i_this->current.roomNo);
        if (i_this->mKanteraID != fpcM_ERROR_PROCESS_ID_e) {
            i_this->m382 = 5;
            switch (i_this->mBehaviorType) {
            case InvisibleAtStart:
                i_this->mState = 0xB;
                break;
            case OnlyLanternVisibleAtStart:
                i_this->m341 = 2;
                i_this->mState = 8;
                break;
            default:
                i_this->m346 = 1;
                i_this->mState = 0xD;
                break;
            }
        }
        break;
    case 0xB:
        dKyr_get_vectle_calc(&i_this->current.pos, &camera->mLookat.mEye, &camfwd);
        i_this->mActorPlace.pos.x = i_this->m2CC.x + camfwd.x * 150.0f;
        i_this->mActorPlace.pos.y = i_this->m2CC.y;
        i_this->mActorPlace.pos.z = i_this->m2CC.z + camfwd.z * 150.0f;
        fopAc_ac_c* kantera;
        if (i_this->mKanteraID != fpcM_ERROR_PROCESS_ID_e &&
            fopAcM_SearchByID(i_this->mKanteraID, &kantera) && kantera != NULL &&
            fopAcM_GetName(kantera) == PROC_KANTERA)
        {
            kantera->current.pos = i_this->m2CC;
            kantera->current.angle.y = i_this->shape_angle.y;
            kantera->scale.setall(1.0f);
            if (i_this->mpMorf->isStop()) {
                i_this->m341 = 0;
                i_this->mBehaviorType = VisibleFromStart;
                first_mode_change(i_this);
                i_this->m382 = 3;
                i_this->m346 = 1;
                i_this->mState = 0xD;
            }
        }
        break;
    case 0x6:
        i_this->m39A += 10;
        if (i_this->m39A > 100) {
            i_this->m39A = 100;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mBehaviorType = VisibleFromStart;
            i_this->m346 = 1;
            first_mode_change(i_this);
            i_this->mState = 0xD;
        }
        break;
    case 0x7:
        if (fopAcM_searchPlayerDistance(i_this) < i_this->mNoticeRange) {
            i_this->m38C = fopAcM_searchPlayerAngleY(i_this);
            i_this->current.angle.y = i_this->m38C;
            i_this->shape_angle.y = i_this->m38C;
            anm_init(i_this, PW_BCK_DERUB2, 3.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            i_this->mState = 6;
        }
        break;
    case 0x8:
        i_this->m380 = 2;
        i_this->m346 = 1;
        if (fopAcM_searchPlayerDistance(i_this) < i_this->m3AC) {
            anm_init(i_this, PW_BCK_DERUB1, 3.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            i_this->mState = 7;
        }
        break;
    case 0xD:
        for (int i = 0; i < 4; i++) {
            i_this->m384[i] = 0;
        }
        i_this->m340 = 0;
        i_this->m341 = 0;
        i_this->m378 = cM_rndF(60.0f) + 60.0f;
        if (i_this->m346 && i_this->mBckIdx != PW_BCK_WAIT1) {
            anm_init(i_this, PW_BCK_WAIT1, 7.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        } else if (i_this->mBckIdx != PW_BCK_WAIT2) {
            anm_init(i_this, PW_BCK_WAIT2, 7.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        }
        i_this->mState += 1;
        // Fall-through
    case 0xE:
        cLib_addCalc0(&i_this->speedF, 1.0f, 1.0f);
        if (i_this->m378) {
            break;
        }
        i_this->mState += 1;
        // Fall-through
    case 0xF:
        i_this->m378 = cM_rndF(120.0f) + 120.0f;
        if (i_this->m346 == 1) {
            if (i_this->mBckIdx != PW_BCK_IDOU1) {
                anm_init(i_this, PW_BCK_IDOU1, 7.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            }
        } else {
            if (i_this->mBckIdx != PW_BCK_IDOU2) {
                anm_init(i_this, PW_BCK_IDOU2, 7.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            }
        }
        i_this->m38C += (s16)cM_rndFX(16384.0f);
        if (i_this->mPathIndex != 0xFF && i_this->mpPath != NULL) {
            i_this->mState = 0x14;
        } else {
            i_this->mState = 0x10;
        }
        break;
    case 0x10:
        i_this->speedF = 5.0f;
        move_sound(i_this);
        if (i_this->m37A == 0) {
            if (Line_check(i_this, i_this->current.pos, 0) || hani_check(i_this)) {
                i_this->m37A = 10;
            } else if (i_this->m378 == 0) {
                i_this->mState = 0xF;
            }
        }
        break;
    case 0x14:
        i_this->m2FC = i_this->current.pos;
        if (i_this->mPathIndex != 0xFF && i_this->mpPath != NULL) {
            i_this->speedF = 5.0f;
            move_sound(i_this);
            dPath__Point* pnt = &i_this->mpPath->mpPnt[i_this->mPathPntIdx];
            f32 delta_x = pnt->mPos.x - i_this->current.pos.x;
            f32 delta_z = pnt->mPos.z - i_this->current.pos.z;
            i_this->m38C = cM_atan2s(delta_x, delta_z);
            f32 dist_xz = sqrtf(delta_x*delta_x + delta_z*delta_z);
            if (dist_xz < 80.0f) {
                i_this->mPathPntIdx++;
                if (i_this->mPathPntIdx >= i_this->mpPath->m_num) {
                    i_this->mPathPntIdx = 0;
                }
            }
        }
        break;
    case 0x19:
        i_this->m38C = fopAcM_searchPlayerAngleY(i_this);
        anm_init(i_this, PW_BCK_DAMAGE_K1, 9.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->speedF = -2.0f;
        i_this->mState += 1;
        break;
    case 0x1A:
        break;
    case 0x1B:
    case 0x1C:
        if (!fopAcM_CheckStatus(i_this, fopAcStts_HOOK_CARRY_e)) {
            i_this->mState = 0x5A;
        }
        break;
    case 0x65:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        // Fall-through
    case 0x5A:
    case 0x5B:
        // TODO
        Big_pow_gattai_check(i_this);
        break;
    case 0x5C:
        break;
    case 0x64:
        anm_init(i_this, PW_BCK_JITTAIKA1, 6.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->mState += 1;
        break;
    case 0x6E:
        anm_init(i_this, PW_BCK_ATTACK1, 7.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        // TODO
        i_this->mState += 1;
        break;
    case 0x6F:
        if (i_this->m5C4.mpEmitter != NULL) {
            i_this->mActorPlace.pos = i_this->current.pos;
            i_this->mActorPlace.angle = i_this->shape_angle;
        }
        if (!i_this->mAcch.ChkGroundHit())
            break;
        i_this->m5C4.end();
        i_this->speedF = 0.0f;
        i_this->speed.setall(0.0f);
        i_this->gravity = 0.0f;
        anm_init(i_this, PW_BCK_SIRIMOTI1, 0.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->mState += 1;
    case 0x70:
        // Fall-through
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 0x5A;
        }
        break;
    }
    
    if (i_this->mState <= 0xB) {
        return;
    }
    if (i_this->m37C == 0 && i_this->mState < 0x5A) {
        if (i_this->mState == 0x0E || i_this->mState == 0x10 || i_this->mState == 0x14) {
            if (!hani_check(i_this) && fopAcM_searchPlayerDistance(i_this) < 500.0f && fabsf(i_this->current.pos.y - player->current.pos.y) < 100.0f) {
                if (!Line_check(i_this, i_this->current.pos, 1) && (i_this->m346 == 1 || !TORITUKI_ON)) {
                    i_this->mAction = 1;
                    i_this->mState = 0x1E;
                }
            }
        }
    }
    
    if (i_this->mState >= 10 && i_this->mState < 90) {
        alpha_anime(i_this);
    }
    
    if (i_this->mJalhallaID == fpcM_ERROR_PROCESS_ID_e) {
        fuwafuwa_calc(i_this);
    }
}

/* 00003B08-000042B8       .text action_kougeki__FP8pw_class */
void action_kougeki(pw_class*) {
    /* Nonmatching */
}

/* 000042B8-00004C50       .text action_itai__FP8pw_class */
void action_itai(pw_class*) {
    /* Nonmatching */
}

/* 00004C50-00004FFC       .text action_demo__FP8pw_class */
void action_demo(pw_class*) {
    /* Nonmatching */
}

/* 00004FFC-000052B8       .text action_torituku__FP8pw_class */
void action_torituku(pw_class*) {
    /* Nonmatching */
}

/* 000052B8-00005CA4       .text action_big_demo__FP8pw_class */
void action_big_demo(pw_class*) {
    /* Nonmatching */
}

/* 00005CA4-000061FC       .text daPW_Execute__FP8pw_class */
static BOOL daPW_Execute(pw_class*) {
    /* Nonmatching */
}

/* 000061FC-00006204       .text daPW_IsDelete__FP8pw_class */
static BOOL daPW_IsDelete(pw_class*) {
    return TRUE;
}

/* 00006204-000062B0       .text daPW_Delete__FP8pw_class */
static BOOL daPW_Delete(pw_class*) {
    /* Nonmatching */
}

/* 000062B0-000066D8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00006720-00006BDC       .text daPW_Create__FP10fopAc_ac_c */
static s32 daPW_Create(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    fopAcM_SetupActor(i_actor, pw_class);
}
