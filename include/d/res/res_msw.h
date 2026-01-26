#ifndef RES_MSW_H
#define RES_MSW_H

#include "global.h" // IWYU pragma: keep

enum MSW_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MSW_BDL_MSWNG=0x4,
    MSW_BDL_OBM_CHAIN1=0x5,
    
    /* DZB */
    MSW_DZB_BRIDGE=0x8,
    MSW_DZB_MSWING=0x9,
    MSW_DZB_OBM_BRIDGE2=0xA,
};

#endif /* RES_MSW_H */
