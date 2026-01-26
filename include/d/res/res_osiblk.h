#ifndef RES_OSIBLK_H
#define RES_OSIBLK_H

#include "global.h" // IWYU pragma: keep

enum OSIBLK_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    OSIBLK_BDL_OBM_OSIHIKIBLK1=0x4,
    OSIBLK_BDL_OBM_OSIHIKIBLK2=0x5,
    
    /* DZB */
    OSIBLK_DZB_OBM_OSIHIKIBLK1=0x8,
    OSIBLK_DZB_OBM_OSIHIKIBLK2=0x9,
};

#endif /* RES_OSIBLK_H */
