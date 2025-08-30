#ifndef RES_WZ_H
#define RES_WZ_H

#include "global.h" // IWYU pragma: keep

enum WZ_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    WZ_BCK_AIRDOWN1=0x5,
    WZ_BCK_ATTACK1=0x6,
    WZ_BCK_ATTACK_S1=0x7,
    WZ_BCK_BATABATA1=0x8,
    WZ_BCK_DAMAGE1=0x9,
    WZ_BCK_DEFAULT_S1=0xA,
    WZ_BCK_DOWN1=0xB,
    WZ_BCK_KIZETU1=0xC,
    WZ_BCK_PRESS1=0xD,
    WZ_BCK_PRESS2=0xE,
    WZ_BCK_PRESS3=0xF,
    WZ_BCK_SYUTUGEN1=0x10,
    WZ_BCK_S_DEMO1=0x11,
    WZ_BCK_S_DEMO_WAIT1=0x12,
    WZ_BCK_TAME1=0x13,
    WZ_BCK_TAME2=0x14,
    WZ_BCK_TAME_S1=0x15,
    
    /* BDLM */
    WZ_BDL_WZ=0x18,
    WZ_BDL_WZ_KAMEN=0x19,
    WZ_BDL_WZ_STICK=0x1A,
    
    /* BRK */
    WZ_BRK_WZ=0x1D,
};

#endif /* RES_WZ_H */
