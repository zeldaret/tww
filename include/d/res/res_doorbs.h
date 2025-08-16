#ifndef RES_DOORBS_H
#define RES_DOORBS_H

#include "global.h" // IWYU pragma: keep

enum DOORBS_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    DOORBS_BDL_DOORDR=0x4,
    DOORBS_BDL_DOORKD=0x5,
    
    /* DZB */
    DOORBS_DZB_DOOR20_D=0x8,
    DOORBS_DZB_DOOR20_K=0x9,
};

#endif /* RES_DOORBS_H */
