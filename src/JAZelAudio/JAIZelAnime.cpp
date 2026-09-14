#include "JAZelAudio/JAIZelAnime.h"
#include "JSystem/JAudio/JAIConst.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "dolphin/mtx/mtxvec.h"
#include "m_Do/m_Do_audio.h"

/* 802AC830-802AC888       .text setAnimSound__11JAIZelAnimeFP3VecffUlSc */
void JAIZelAnime::setAnimSound(Vec* pos, f32 frame, f32 rate, u32 mtrlSndId, s8 reverb) {
    u32 r6 = (mtrlSndId & 0x00FFFFFF) + (reverb << 24);
    if (rate == 0.0f) {
        return;
    }
    if (rate < 0.0f) {
        rate *= -1.0f;
    }
    setAnimSoundVec(mDoAud_zelAudio_c::getInterface(), pos, frame, rate, r6, 0);
}

/* 802AC888-802ACD34       .text startAnimSound__11JAIZelAnimeFPvUlPP8JAISoundPQ27JAInter5ActorUc */
// NONMATCHING - 1 missing reg move
void JAIZelAnime::startAnimSound(void* i_basic, u32 i_soundID, JAISound** i_sound, JAInter::Actor* i_actor, u8 param_4) {
    JAIZelBasic* basic = (JAIZelBasic*)i_basic;

    if ((int)basic->field_0x0207 != 0) {
        return;
    }

    #if VERSION >= VERSION_USA
    if (basic->field_0x0224 == 0x12 && basic->mIslandRoomNo == 0x2C && basic->field_0x0239 == 9 && basic->field_0x0028 < 30) {
        return;
    }
    #endif

    switch (i_soundID) {
    case JA_SE_CM_DRG_MTOP_HAND:
    case JA_SE_CV_DRG_MTOP_BIKU:
    case JA_SE_CV_DRG_MTOP_ABARE:
    case JA_SE_CV_DRG_MTOP_AKUBI:
        mDoAud_seStart(i_soundID, i_actor->field_0x4);
        return;
    case JA_SE_FT_PW_RUN_AWAY:
        mDoAud_seStart(i_soundID, i_actor->field_0x4);
        return;
    }

    if (basic->field_0x0201 == 1) {
        return;
    }
    if (basic->field_0x0206 == 1) {
        return;
    }

    #if VERSION >= VERSION_USA
    if (basic->checkStreamPlaying(JA_STRM_BOSS_CLEAR)
        || basic->checkStreamPlaying(JA_STRM_BST_CLEAR)
        || basic->checkStreamPlaying(JA_STRM_DK_CLEAR)
        || basic->checkStreamPlaying(JA_STRM_BWD_CLEAR))
    {
        if (i_soundID == JA_SE_LK_FT_WALK || i_soundID == JA_SE_LK_FT_JUMP) {
            return;
        }
    }
    #endif

    if (basic->field_0x0046 == 1) {
        switch (i_soundID) {
        case JA_SE_LK_FT_WALK:
        case JA_SE_FT_LADDER_CLIMB:
        case JA_SE_FT_LADDER_CLIMB_D:
            i_soundID = JA_SE_LK_WALK_HEAVY;
            break;
        case JA_SE_LK_FT_JUMP:
            i_soundID = JA_SE_LK_JUMP_HEAVY;
            break;
        }
    } else if (i_soundID == JA_SE_LK_WALK_HEAVY) {
        i_soundID = JA_SE_LK_FT_WALK;
    }

    if (basic->checkStreamPlaying(JA_STRM_DEMO_04_01)) {
        switch (i_actor->field_0xc) {
        case 0x16:
        case 0x13:
        case 0x14:
        case 0x18:
            return;
        }
    }

    int var_r27 = (i_actor->field_0xc & 0xFF000000) >> 0x18;
    i_actor->field_0xc &= 0xFFFFFF;

    if (i_actor->field_0x4 != NULL) {
        MtxP m = basic->getCurCamera(0)->field_0x8;
        Vec spC = *i_actor->field_0x4;
        MTXMultVec(m, &spC, &spC);
        f32 temp_f4 = SQUARE(spC.x) + SQUARE(spC.y) + SQUARE(spC.z);
        f32 var_f31 = std::sqrtf(temp_f4);

        switch (i_soundID) {
        case JA_SE_CM_KAMOME_WING:
            if (var_f31 > JAIGlobalParameter::getParamDistanceMax()) {
                return;
            }
            break;
        default:
            if (var_f31 > JAIGlobalParameter::getParamDistanceMax()) {
                return;
            }
            break;
        case JA_SE_CM_DK_WING_ENTER:
        case JA_SE_CM_DK_WING_NORMAL:
        case JA_SE_CM_DK_WING_GO_UP:
        case JA_SE_CM_DK_FOOTNOTE:
        case JA_SE_CV_KAMOME:
            break;
        }
    }

    switch (i_actor->field_0xc) {
    case 0xF:
        basic->seStart(JA_SE_FT_SUSBRIDGE_R, i_actor->field_0x4, i_actor->field_0xc, var_r27);
        break;
    case 0x10:
        basic->seStart(JA_SE_FT_SUSBRIDGE_C, i_actor->field_0x4, i_actor->field_0xc, var_r27);
        break;
    }

    if (basic->field_0x0045 == 1) {
        switch (i_soundID) {
        case JA_SE_LK_FT_BOUND:
            break;
        case JA_SE_LK_FT_WALK:
        case JA_SE_LK_FT_JUMP:
        case JA_SE_LK_HD_NORMAL:
        case JA_SE_LK_WALK_HEAVY:
        case JA_SE_LK_JUMP_HEAVY:
        case JA_SE_FT_LADDER_CLIMB:
        case JA_SE_FT_LADDER_CLIMB_D:
            basic->seStart(JA_SE_LK_FT_SW_SHIELD, i_actor->field_0x4, 0, var_r27);
            break;
        }
    }

    if (*i_sound) {
        (*i_sound)->stop(0);
    }

    basic->startSoundActor(i_soundID, i_sound, i_actor, 0, 0);

    if (*i_sound) {
        (*i_sound)->setPortData(9, var_r27);
    }
}

/* 802ACD34-802ACFA0       .text setSpeedModifySound__11JAIZelAnimeFP8JAISoundP22JAIAnimeFrameSoundDataf */
// NONMATCHING - idk how the pitch factor switch is supposed to look
void JAIZelAnime::setSpeedModifySound(JAISound* i_sound, JAIAnimeFrameSoundData* i_data, f32 param_2) {
    f32 base_pitch = i_data->mPitch;
    if (i_data->mPitchFactor != 0) {
        switch (i_sound->field_0x1c) {
        case 6:
            break;
        case 0x12:
        case 0x17:
            base_pitch += i_data->mPitchFactor * (param_2 - 1.0f) / 32;
            break;
        }
    }

    i_sound->setPitch(base_pitch, 0, 5);

    int base_volume = i_data->mVolume;
    if (param_2 == 0.0f) {
        base_volume = 0;
    }

    if (i_data->mVolumeFactor != 0) {
        if (i_sound->getID() == JA_SE_LK_HOFUKU) {
            if (param_2 < 0.0f) {
                param_2 *= -1.0f;
            }

            if (param_2 < 1.2f) {
                base_volume = 0;
            } else {
                base_volume = (int)((param_2 - 1.2f) * 35.0f);
            }
        } else {
            switch (i_sound->field_0x1c) {
            case 19:
                base_volume += (int)(i_data->mVolumeFactor * (param_2 - 1.0f));
                break;
            default:
                base_volume += (int)(i_data->mVolumeFactor * 2.0f * (param_2 - 1.0f));
                break;
            }
        }

        if ((s16)base_volume > 127) {
            base_volume = 127;
        } else if ((s16)base_volume < 0) {
            base_volume = 0;
        }
    }

    if (i_sound->getID() == JA_SE_LK_HOFUKU) {
        if (i_sound->field_0x18 <= 1) {
            i_sound->setVolume((u8)base_volume / 127.0f, 0, 5);
        }
    } else {
        i_sound->setVolume((u8)base_volume / 127.0f, 0, 5);
    }
}

/* 802ACFA0-802AD008       .text setPlayPosition__11JAIZelAnimeFf */
// NONMATCHING - supposed to check if unsigned value is less than or equal to 0?
void JAIZelAnime::setPlayPosition(f32 param_0) {
    if (mpAsData == NULL) {
        return;
    }

    int var_r0 = mpAsData->datas;
    int count = 0;
    int i = 0;
    
    while ((u32)var_r0 > 0) {
        if (mpAsData->mAfsData[i].mStartFrame >= param_0) {
            break;
        }

        count++;
        i++;
        var_r0--;
    }

    if (mDataCounterInc == 1) {
        dataCounter = count;
        mCurrentTime = param_0;
    } else {
        dataCounter = count;
        mCurrentTime = param_0;
    }    
}
