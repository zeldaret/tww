#ifndef RES_VZOUK_H
#define RES_VZOUK_H

#include "global.h" // IWYU pragma: keep

enum VZOUK_RES_FILE_ID {
    /* BCK */
    VZOUK_BCK_VZOUK=0x4,
    
    /* BDL */
    VZOUK_BDL_VZOUK=0x7,
    
    /* DZB */
    VZOUK_DZB_MAEKISI=0xA,
    VZOUK_DZB_ATOKISI=0xB,
};

enum VZOUK_RES_FILE_INDEX {
    /* BCK */
    VZOUK_INDEX_BCK_VZOUK=0x5,
    
    /* BDL */
    VZOUK_INDEX_BDL_VZOUK=0x8,
    
    /* DZB */
    VZOUK_INDEX_DZB_MAEKISI=0xB,
    VZOUK_INDEX_DZB_ATOKISI=0xC,
};

#endif /* RES_VZOUK_H */
