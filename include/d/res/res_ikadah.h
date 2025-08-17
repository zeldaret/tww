#ifndef RES_IKADAH_H
#define RES_IKADAH_H

#include "global.h" // IWYU pragma: keep

enum IKADAH_RES_FILE_ID { // IDs and indexes are synced
#if VERSION == VERSION_DEMO
    /* BCKS */
#else
    /* BCK */
#endif
    IKADAH_BCK_SVSHIP_KAITEN=0x5,
    
    /* BDL */
    IKADAH_BDL_VIKAE=0x8,
    IKADAH_BDL_VIKAH=0x9,
    IKADAH_BDL_VSVSP=0xA,
    IKADAH_BDL_VTSP=0xB,
    IKADAH_BDL_VTSP2=0xC,
    
    /* DZB */
    IKADAH_DZB_VIKAE=0xF,
    IKADAH_DZB_VIKAH=0x10,
    IKADAH_DZB_VSVSP=0x11,
    IKADAH_DZB_VTSP=0x12,
};

#endif /* RES_IKADAH_H */
