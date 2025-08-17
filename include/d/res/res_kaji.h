#ifndef RES_KAJI_H
#define RES_KAJI_H

#include "global.h" // IWYU pragma: keep

enum KAJI_RES_FILE_ID {
    /* BAS */
    KAJI_BAS_KJ_ANG=0x0,
    KAJI_BAS_KJ_OMO=0x1,
    KAJI_BAS_KJ_TORI=0x2,
    KAJI_BAS_KJ_WAIT=0x3,
    
    /* BCK */
    KAJI_BCK_KJ_ANG=0x4,
    KAJI_BCK_KJ_OMO=0x5,
    KAJI_BCK_KJ_TORI=0x6,
    KAJI_BCK_KJ_WAIT=0x7,
    
    /* BDL */
    KAJI_BDL_ASODA=0x9,
};

enum KAJI_RES_FILE_INDEX {
    /* BAS */
    KAJI_INDEX_BAS_KJ_ANG=0x5,
    KAJI_INDEX_BAS_KJ_OMO=0x6,
    KAJI_INDEX_BAS_KJ_TORI=0x7,
    KAJI_INDEX_BAS_KJ_WAIT=0x8,
    
    /* BCK */
    KAJI_INDEX_BCK_KJ_ANG=0xB,
    KAJI_INDEX_BCK_KJ_OMO=0xC,
    KAJI_INDEX_BCK_KJ_TORI=0xD,
    KAJI_INDEX_BCK_KJ_WAIT=0xE,
    
    /* BDL */
    KAJI_INDEX_BDL_ASODA=0x11,
};

#endif /* RES_KAJI_H */
