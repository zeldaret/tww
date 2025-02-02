//
// Generated by dtk
// Translation Unit: JAIZelAnime.cpp
//

#include "JAZelAudio/JAIZelAnime.h"
#include "dolphin/types.h"
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
void JAIZelAnime::startAnimSound(void*, u32, JAISound**, JAInter::Actor*, u8) {
    /* Nonmatching */
}

/* 802ACD34-802ACFA0       .text setSpeedModifySound__11JAIZelAnimeFP8JAISoundP22JAIAnimeFrameSoundDataf */
void JAIZelAnime::setSpeedModifySound(JAISound*, JAIAnimeFrameSoundData*, f32) {
    /* Nonmatching */
}

/* 802ACFA0-802AD008       .text setPlayPosition__11JAIZelAnimeFf */
void JAIZelAnime::setPlayPosition(f32) {
    /* Nonmatching */
}
