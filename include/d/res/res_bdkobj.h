#ifndef RES_BDKOBJ_H
#define RES_BDKOBJ_H

#include "global.h" // IWYU pragma: keep

enum BDKOBJ_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    BDKOBJ_BDL_GWOOD00=0x4,
    BDKOBJ_BDL_S_TBLOCK=0x5,
    BDKOBJ_BDL_S_TOWER_BRIDGE=0x6,
    BDKOBJ_BDL_S_TPOLE=0x7,
    BDKOBJ_BDL_SHAHENL=0x8,
    BDKOBJ_BDL_SHAHENS=0x9,
    
    /* DZB */
    BDKOBJ_DZB_S_TOWER_BRIDGE=0xC,
};

#endif /* RES_BDKOBJ_H */
