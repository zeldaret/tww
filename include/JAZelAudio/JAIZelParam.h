#ifndef JAIZELPARAM_H
#define JAIZELPARAM_H

#include "dolphin/types.h"

namespace JAIZelParam {
    extern int SE_REGIST_MAX;
    extern int SOUND_SCENE_MAX;
    extern int STREAM_DECODED_BUFFERS;
    extern int SEQ_CONTROL_BUF_MAX;
    extern int STREAM_CONTROL_BUF_MAX;
    extern int AUTO_HEAP_MAX;
    extern int STAY_HEAP_MAX;
    extern int AUTO_HEAP_ROOM_SIZE;
    extern int STAY_HEAP_ROOM_SIZE;
    extern int SYSTEM_TRACK_MAX;
    extern int PLAY_TRACK_MAX;
    extern f32 DISTANCE_MAX;
    extern f32 MAX_VOLUME_DISTANCE;
    extern u8 DOLBY_CENTER_VALUE;
    extern f32 DOLBY_FLONT_DISTANCE_MAX;
    extern f32 DOLBY_BEHIND_DISTANCE_MAX;
    extern u16 DISTANCE_FX_PARAM;
    extern int DUMMY_POSITION_MAX;
    extern int DUMMY_POSITION_LIFE_TIME;
    extern const char* INIT_DATA_FILE_NAME;
    extern const char* WAVE_PATH;
    extern const char* SEQ_PATH;
    extern const char* STREAM_PATH;
    extern const char* SEQ_ARCH_FILE_NAME;
    extern f32 VOL_BGM_DEFAULT;
    extern u8 VOL_SE_SYSTEM_DEFAULT;
    extern u8 VOL_SE_LINK_VOICE_DEFAULT;
    extern u8 VOL_SE_LINK_MOTION_DEFAULT;
    extern u8 VOL_SE_LINK_FOOTNOTE_DEFAULT;
    extern u8 VOL_SE_CHAR_VOICE_DEFAULT;
    extern u8 VOL_SE_CHAR_MOVE_DEFAULT;
    extern u8 VOL_SE_OBJECT_DEFAULT;
    extern u8 VOL_SE_ATMOSPHERE_DEFAULT;
    extern f32 VOL_BGM_TALKING;
    extern u8 VOL_SE_SYSTEM_TALKING;
    extern u8 VOL_SE_LINK_VOICE_TALKING;
    extern u8 VOL_SE_LINK_MOTION_TALKING;
    extern u8 VOL_SE_LINK_FOOTNOTE_TALKING;
    extern u8 VOL_SE_CHAR_VOICE_TALKING;
    extern u8 VOL_SE_CHAR_MOVE_TALKING;
    extern u8 VOL_SE_OBJECT_TALKING;
    extern u8 VOL_SE_ATMOSPHERE_TALKING;
    extern f32 VOL_BGM_PAUSING;
    extern u8 VOL_SE_SYSTEM_PAUSING;
    extern u8 VOL_SE_LINK_VOICE_PAUSING;
    extern u8 VOL_SE_LINK_MOTION_PAUSING;
    extern u8 VOL_SE_LINK_FOOTNOTE_PAUSING;
    extern u8 VOL_SE_CHAR_VOICE_PAUSING;
    extern u8 VOL_SE_CHAR_MOVE_PAUSING;
    extern u8 VOL_SE_OBJECT_PAUSING;
    extern u8 VOL_SE_ATMOSPHERE_PAUSING;
    extern int BGM_SCENE_CHANGE_FO_TIME;
    extern f32 ENEMY_NEARBY_DIST;
    extern u8 ENEMY_NEARBY_TRACK;
    extern u8 ENEMY_NEARBY_TRACK_2;
    extern u8 BTL_KAITENGIRI_TRACK;
    extern u8 SWORD_NOT_USING_TRACK;
    extern int ENEMY_NEARBY_FADEIN_TIME;
    extern int ENEMY_NEARBY_FADEOUT_TIME;
    extern u8 COMMON_BATTLE_FO_DELAY;
    extern int BTL_KAITENGIRI_FADEIN_TIME;
    extern int BTL_KAITENGIRI_FADEOUT_TIME;
    extern int BTL_SWORD_USING_FADE_TIME;
    extern u8 MBOSS_ENEMY_NEARBY_TRACK;
    extern u8 MBOSS_BTL_KAITENGIRI_TRACK;
    extern u8 MBOSS_SWORD_USING_TRACK;
    extern int JAI_ZEL_NIGHT_FADEOUT_TIME;

    extern int DRAM_HEAP_SIZE;
    extern f32 MIN_DISTANCE_VOLUME;
    extern u8 SWORD_USING_TRACK;
};

#endif /* JAIZELPARAM_H */
