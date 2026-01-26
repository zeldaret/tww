#ifndef RES_PBCO_H
#define RES_PBCO_H

#include "global.h" // IWYU pragma: keep

enum PBCO_RES_FILE_ID {
    /* BDL */
    PBCO_BDL_PBCO=0x0,
    PBCO_BDL_PBC2=0x2,
    
    /* DZB */
    PBCO_DZB_PBCO=0x3,
};

enum PBCO_RES_FILE_INDEX {
    /* BDL */
    PBCO_INDEX_BDL_PBCO=0x4,
    PBCO_INDEX_BDL_PBC2=0x5,
    
    /* DZB */
    PBCO_INDEX_DZB_PBCO=0x8,
};

#endif /* RES_PBCO_H */
