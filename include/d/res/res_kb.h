#ifndef RES_KB_H
#define RES_KB_H

#include "global.h" // IWYU pragma: keep

enum KB_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    KB_BAS_EAT1=0x7,
    KB_BAS_JITA1=0x8,
    KB_BAS_JITA2=0x9,
    KB_BAS_NAKU1=0xA,
    KB_BAS_RUN1=0xB,
    KB_BAS_WAIT1=0xC,
    KB_BAS_WALK1=0xD,
    
    /* BCK */
    KB_BCK_DAMAGE1=0x10,
    KB_BCK_DASSUI=0x11,
    KB_BCK_EAT1=0x12,
    KB_BCK_JITA1=0x13,
    KB_BCK_JITA2=0x14,
    KB_BCK_NAKU1=0x15,
    KB_BCK_RUN1=0x16,
    KB_BCK_WAIT1=0x17,
    KB_BCK_WALK1=0x18,
    
    /* BDLM */
    KB_BDL_PG=0x1B,
    KB_BDL_PG_BIG=0x1C,
    
    /* BMT */
    KB_BMT_PG_BIG_BUTI=0x1F,
    KB_BMT_PG_BIG_KURO=0x20,
    KB_BMT_PG_BIG_PINK=0x21,
    KB_BMT_PG_BUTI=0x22,
    KB_BMT_PG_KURO=0x23,
    KB_BMT_PG_PINK=0x24,
    
    /* BTP */
    KB_BTP_PG_BIG_EYE1=0x27,
    KB_BTP_PG_BIG_EYE2=0x28,
    KB_BTP_PG_EYE1=0x29,
    KB_BTP_PG_EYE2=0x2A,
};

#endif /* RES_KB_H */
