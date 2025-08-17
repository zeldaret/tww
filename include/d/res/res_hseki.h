#ifndef RES_HSEKI_H
#define RES_HSEKI_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum HSEKI_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    HSEKI_BDL_HSEKI3=0x5,
    HSEKI_BDL_HSEKI32=0x6,
    HSEKI_BDL_HSEKI4=0x7,
    HSEKI_BDL_HSEKI42=0x8,
    HSEKI_BDL_HSEKI5=0x9,
    HSEKI_BDL_HSEKI52=0xA,
    
    /* BDLM */
    HSEKI_BDL_HMON1=0xD,
    HSEKI_BDL_HMON2=0xE,
    
    /* BRK */
    HSEKI_BRK_HMON1=0x11,
    HSEKI_BRK_HMON2=0x12,
};
#else
enum HSEKI_RES_FILE_ID { // IDs and indexes are synced
    /* BDLM */
    HSEKI_BDL_HMON1=0x4,
    HSEKI_BDL_HMON2=0x5,
    
    /* BRK */
    HSEKI_BRK_HMON1=0x8,
    HSEKI_BRK_HMON2=0x9,
};
#endif

#endif /* RES_HSEKI_H */
