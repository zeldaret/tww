#ifndef RES_BRIDGE_H
#define RES_BRIDGE_H

#include "global.h" // IWYU pragma: keep

enum BRIDGE_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    BRIDGE_BDL_OBM_BRIDGE=0x4,
    BRIDGE_BDL_OBM_BRIDGE2=0x5,
    BRIDGE_BDL_OBM_CHAIN1=0x6,
    
    /* DZB */
    BRIDGE_DZB_MBRDG=0x9,
    BRIDGE_DZB_MBRDG2=0xA,
};

#endif /* RES_BRIDGE_H */
