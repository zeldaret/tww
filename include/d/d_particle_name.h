#ifndef D_PARTICLE_NAME
#define D_PARTICLE_NAME

#include "dolphin/types.h"

namespace dPa_name {
    enum {
        ID_COMMON_SMOKE_DEBRIS = 0x2008,
        ID_COMMON_SMOKE_CLOUD = 0x2009,
        ID_COMMON_SMOKE_CIRCLE = 0x200A,
        ID_COMMON_LIGHT_FLASH = 0xB,
        ID_COMMON_PURPLE_HIT = 0xC,
        ID_COMMON_NORMAL_HIT = 0xD,
        ID_COMMON_BIG_HIT = 0xF,
        ID_COMMON_FUSE_SPARKS = 0x11,
        ID_COMMON_LIGHT_EXPLOSION = 0x272,
        ID_COMMON_STARS_SPIN = 0x27A,
        ID_COMMON_STARS_BLOW = 0x27B,
    };

    enum {
        ID_SCENE_END = 0x8466,
    };
    
    u16 j_o_id[];
    u16 s_o_id[];
}

#endif /* D_PARTICLE_NAME */
