//
// Generated by dtk
// Translation Unit: d_a_pw.cpp
//

#include "d/actor/d_a_pw.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_kankyo_rain.h"
#include "dolphin/types.h"
#include "f_op/f_op_camera_mng.h"
#include "f_pc/f_pc_manager.h"

/* 00000078-00000158       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000158-00000230       .text draw_SUB__FP8pw_class */
void draw_SUB(pw_class*) {
    /* Nonmatching */
}

/* 00000230-000004D4       .text daPW_Draw__FP8pw_class */
static BOOL daPW_Draw(pw_class*) {
    /* Nonmatching */
}

/* 000004D4-00000600       .text anm_init__FP8pw_classifUcfi */
void anm_init(pw_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
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
void BG_check(pw_class*) {
    /* Nonmatching */
}

/* 00001990-00001D60       .text Line_check__FP8pw_class4cXyzUc */
BOOL Line_check(pw_class*, cXyz, unsigned char) {
    /* Nonmatching */
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
void kougen_hani_check(pw_class*, unsigned char) {
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
    daPy_py_c* link = daPy_getPlayerActorClass();
    float randomValue;
    switch (i_this->m368) {
    case 0:
        anm_init(i_this, 0x23, 7.0, '\x02', 1.0, -1);
        i_this->m346 = 0;
        i_this->m368 += 1;
        break;

    case 0x1:
        f32 actor_distance = fopAcM_searchActorDistance(i_this, link);
        if (actor_distance < 500.0f) {
            anm_init(i_this, 0x10, 3.0, '\0', 1.0, -1);
            s16 actorYAngle = fopAcM_searchActorAngleY(i_this, link);
            i_this->m38C = actorYAngle;
            i_this->current.angle.y = i_this->m38C;
            i_this->shape_angle.y = i_this->m38C;
            i_this->m3A4 = -80.0f;
            i_this->m340 = 1;
            i_this->m368 += 1;
        }
        break;

    case 0x2:
        i_this->shape_angle.y += 0x1000;
        cLib_addCalc0(&i_this->m3A4, 1.0, 1.0);
        i_this->m39A += 7;
        if (i_this->m39A > 100) {
            i_this->m39A = 100;
        }
        BOOL iVar6 = i_this->m2B4->mFrameCtrl.checkPass(25.0f);
        if (iVar6 != FALSE) {
            i_this->m3A4 = 0.0f;
            first_mode_change(i_this);
            s16 actorAngleY = fopAcM_searchActorAngleY(i_this, link);
            i_this->m38C = actorAngleY;
            JPABaseEmitter* particle =
                dComIfGp_particle_set(0x82EE, &i_this->m2CC, &i_this->shape_angle);
            if (particle != NULL) {
                // JPASetRMtxSTVecfromMtx(i_this->m2B4->mpModel->mpNodeMtxm,
                // particle->mGlobalRotation, &particle->mGlobalTranslation);
            }
            i_this->attention_info.flags = 0;
            i_this->m368 = 0;
        }
        break;
    case 0x6:
        i_this->m39A += 10;
        if (i_this->m39A > 100) {
            i_this->m39A = 100;
        }
        BOOL tempVar10 = TRUE;
        if (!(i_this->m2B4->mFrameCtrl.getState() & 1) &&
            i_this->m2B4->mFrameCtrl.getRate() != 0.0f)
        {
            tempVar10 = FALSE;
        }
        if (tempVar10) {
            i_this->mBehaviorType = VisibleFromStart;
            i_this->m346 = 1;
            first_mode_change(i_this);
            i_this->m368 = 0xD;
        }
        break;
    case 0x7:
        f32 noticeDistance = fopAcM_searchActorDistance(i_this, daPy_getPlayerActorClass());
        if (noticeDistance < i_this->mNoticeRange) {
            s16 angleToLink = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
            i_this->m38C = angleToLink;
            i_this->current.angle.y = angleToLink;
            i_this->shape_angle.y = angleToLink;
            anm_init(i_this, 0x12, 3.0f, '\0', 1.0f, -1);
            i_this->m368 = 6;
        }
        break;
    case 0x8:
        i_this->m380 = 2;
        i_this->m346 = 1;
        f32 otherDistance = fopAcM_searchActorDistance(i_this, daPy_getPlayerActorClass());
        if (otherDistance < i_this->m3AC) {
            anm_init(i_this, 0x11, 3.0f, '\x02', 1.0, -1);
            i_this->m368 = 7;
        }
        break;
    case 0x9:
        i_this->m39A = 0;
        i_this->m39C = 0;
        i_this->m368 += 1;
    case 0xA:
        if (i_this->mBehaviorType == InvisibleAtStart) {
            i_this->m38C = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
        }
        i_this->m370 = fopAcM_create(0xC2, 0xFF000001, &i_this->m2CC, i_this->current.roomNo, NULL,
                                     NULL, 0xFF, NULL);
        if (i_this->m370 != -1) {
            i_this->m382 = 5;
            switch (i_this->mBehaviorType) {
            case OnlyLanternVisibleAtStart:
                i_this->m341 = 2;
                i_this->m368 = 8;
                break;
            case InvisibleAtStart:
                i_this->m368 = 8;
                break;
            default:
                i_this->m346 = 1;
                i_this->m368 = 0xD;
            }
        }
        break;
    case 0xB:
        cXyz camfwd;
        camera_class* pCamera = dComIfGp_getCamera(0);
        dKyr_get_vectle_calc(&i_this->current.pos, &pCamera->mLookat.mCenter, &camfwd);
        i_this->mActorPlace.pos.x = i_this->m2CC.x + camfwd.x * 150.0f;
        i_this->mActorPlace.pos.y = i_this->m2CC.y;
        i_this->mActorPlace.pos.z = i_this->m2CC.z + camfwd.z * 150.0f;
        fopAc_ac_c* searchResult;
        if (i_this->m370 != -1 && fopAcM_SearchByID(i_this->m370, &searchResult) &&
            searchResult != NULL && fpcM_GetName(&searchResult) == 0xC2)
        {
            searchResult->current.pos = i_this->m2CC;
            searchResult->current.angle.y = i_this->shape_angle.GetY();
            searchResult->scale = cXyz::BaseXYZ;  // Might not be this, but all ones.
            BOOL weirdBool = TRUE;
            if(i_this->m2B4->mFrameCtrl.getState() & 1 == 0 && i_this->m2B4->mFrameCtrl.getRate()) {
                weirdBool = FALSE;
            }
            if(weirdBool) {
                i_this->m341 = 0;
                i_this->mBehaviorType = VisibleFromStart;
                first_mode_change(i_this);
                i_this->m382 = 3;
                i_this->m346 = 1;
                i_this->m368 = 0xD;
            }
        }
        break;
    case 0xD:
        i_this->m384 = 0;
        i_this->m388 = 0;
        i_this->m38C = 0;
        i_this->m38E = 0;
        i_this->m340 = 0;
        i_this->m341 = 0;
        randomValue = cM_rndF(60.0f);
        i_this->m378 = (short) randomValue + 60.0f;
        if(i_this->m346 && i_this->m374 != 0x23) {
            anm_init(i_this,0x23,7.0f,'\x02', 1.0f, -1);
        } else if (i_this->m374 != 0x24) {
            anm_init(i_this,0x24,7.0,'\x02',1.0f, -1);
        }
        i_this->m368 += 1;
    case 0xE:                       // 0.0f is a placeholder for some local value
        cLib_addCalc0(&i_this->speedF, 0.0f, 1.0f);
        if(!i_this->m378) {
            i_this->m368 += 1;
            PART_OF_CASE_E:
            randomValue = cM_rndF(120.0f);
            i_this->m378 = (short) randomValue + 120.0f;
            if(i_this->m346 && i_this->m374 != 0x14) {
                anm_init(i_this,0x14, 7.0f, '\x02', 1.0f, -1);
            } else if (i_this->m374 != 0x15) {
                anm_init(i_this,0x15, 7.0f, '\x02', 1.0f, -1);
            }
            randomValue = cM_rndFX(16384.0f);
            i_this->m38C += (short) randomValue;
            if(i_this->mPathIndex == 0xFF || i_this->m348 == NULL) {
                i_this->m368 = 0x10;
            } else {
                i_this->m368 = 0x14;
            }
        }
        break;
    case 0xF:
        goto PART_OF_CASE_E;
    case 0x10:
        i_this->speedF = 5.0f;
        move_sound(i_this);
        if(i_this->m37A == 0) {
            if(Line_check(i_this, i_this->current.pos, 0) && hani_check(i_this)) {
                if(i_this->m378 == 0) {
                    i_this->m368 = 0xF;
                } 
            } else {
                i_this->m37A = 10;
            }
        }
        break;
    case 0x14:
        // Some wacky stuff here, needs a professional look - 0x80891D34
        if(i_this->mPathIndex != 0xFF && i_this->m348 != NULL) {
            i_this->speedF = 5.0f;
            move_sound(i_this);
            // This part is also wack. going to leave the rest
            // of case 0x14 alone.

        }
        break;
    case 0x19:
    case 0x1A:
        break;
    case 0x1B:
    case 0x1C:
        if (i_this->actor_status & 0x00100000 == 0) {
            i_this->m368 = 0x5A;
        } 
        break;
    case 0x65:
        if (i_this->m2B4->mFrameCtrl.getState() & 1 == 0 && i_this->m2B4->mFrameCtrl.getRate()) {
            break;
        }
    case 0x5A:
    case 0x5B:
        Big_pow_gattai_check(i_this);
        break;
    case 0x5C:
        break;
    case 0x64:
        anm_init(i_this, 0x17, 6.0f, '\0', 1.0f, -1);
        i_this->m368 += 1;
        break;
    case 0x6E:
        anm_init(i_this, 0xC, 7.0f, '\x02', 1.0f, -1);
        break;
    case 0x6F:
        if (i_this->m5C4.mpEmitter != NULL) {
            //set Actor Position
        }
        if(!i_this->mBgsAcch.ChkGroundHit()) break;
        // Some VTBL stuff?
        i_this->speedF = 0.0f;
        i_this->speed = cXyz::Zero;
        i_this->gravity = 0.0f;
        anm_init(i_this, 0x1D, 0.0f, '\0', 1.0f, -1);
        i_this->m368 += 1;
    case 0x70:
        if (i_this->m2B4->mFrameCtrl.getState() & 1 == 0 && i_this->m2B4->mFrameCtrl.getRate()) {
            i_this->m368 = 0x5A;
        }
    // Some default case stuff is happening
    }
    if(i_this->mJalhallaParentId == -1) {
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
static s32 daPW_Create(fopAc_ac_c*) {
    /* Nonmatching */
}
