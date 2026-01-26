#ifndef RES_SEARCH_H
#define RES_SEARCH_H

#include "global.h" // IWYU pragma: keep

enum SEARCH_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    SEARCH_BDL_S_BEAM=0x4,
    SEARCH_BDL_S_SEARCH=0x5,
    
    /* DZB */
    SEARCH_DZB_S_BASE=0x8,
    SEARCH_DZB_S_SEARCH_LIGHTA=0x9,
    SEARCH_DZB_S_SEARCH_LIGHTB=0xA,
};

#endif /* RES_SEARCH_H */
