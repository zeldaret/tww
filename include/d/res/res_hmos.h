#ifndef RES_HMOS_H
#define RES_HMOS_H

#include "global.h" // IWYU pragma: keep

enum HMOS_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    HMOS_BDL_HMOS1=0x5,
    HMOS_BDL_HMOS2=0x6,
    HMOS_BDL_HMOS3=0x7,
    HMOS_BDL_HMOSUP1=0x8,
    HMOS_BDL_HMOSUP2=0x9,
    
    /* BDLM */
    HMOS_BDL_HMOS2T=0xC,
    
    /* BRK */
    HMOS_BRK_HMOS2T=0xF,
    HMOS_BRK_HMOSUP1=0x10,
    HMOS_BRK_HMOSUP2=0x11,
};

#endif /* RES_HMOS_H */
