#ifndef RES_AH_H
#define RES_AH_H

#include "global.h" // IWYU pragma: keep

enum AH_RES_FILE_ID {
    /* BCKS */
    AH_BCK_AH_WAIT01=0x0,
    AH_BCK_AH_WAIT02=0x1,
    
    /* BDLM */
    AH_BDL_AH=0x2,
    
    /* BTP */
    AH_BTP_HOU=0x3,
    AH_BTP_MABA=0x4,
};

enum AH_RES_FILE_INDEX {
    /* BCKS */
    AH_INDEX_BCK_AH_WAIT01=0x5,
    AH_INDEX_BCK_AH_WAIT02=0x6,
    
    /* BDLM */
    AH_INDEX_BDL_AH=0x9,
    
    /* BTP */
    AH_INDEX_BTP_HOU=0xC,
    AH_INDEX_BTP_MABA=0xD,
};

#endif /* RES_AH_H */
