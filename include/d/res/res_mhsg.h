#ifndef RES_MHSG_H
#define RES_MHSG_H

#include "global.h" // IWYU pragma: keep

enum MHSG_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MHSG_BDL_MHSG12=0x4,
    MHSG_BDL_MHSG15=0x5,
    MHSG_BDL_MHSG4H=0x6,
    MHSG_BDL_MHSG6=0x7,
    MHSG_BDL_MHSG9=0x8,
    
    /* DZB */
    MHSG_DZB_MHSG12=0xB,
    MHSG_DZB_MHSG15=0xC,
    MHSG_DZB_MHSG4H=0xD,
    MHSG_DZB_MHSG6=0xE,
    MHSG_DZB_MHSG9=0xF,
};

#endif /* RES_MHSG_H */
