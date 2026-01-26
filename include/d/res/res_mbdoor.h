#ifndef RES_MBDOOR_H
#define RES_MBDOOR_H

#include "global.h" // IWYU pragma: keep

enum MBDOOR_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MBDOOR_BDL_S_MBD_L=0x4,
    MBDOOR_BDL_S_MBD_R=0x5,
    MBDOOR_BDL_S_MBDFU=0x6,
    MBDOOR_BDL_S_MBDTO=0x7,
    
    /* DZB */
    MBDOOR_DZB_S_MBDFU=0xA,
};

#endif /* RES_MBDOOR_H */
