#ifndef RES_HI_H
#define RES_HI_H

#include "global.h" // IWYU pragma: keep

enum HI_RES_FILE_ID {
    /* BCKS */
    HI_BCK_HI_POSE=0x0,
    HI_BCK_HI_WAIT01=0x1,
    
    /* BDLM */
    HI_BDL_HI=0x2,
    
    /* BTP */
    HI_BTP_MABA=0x3,
    
    /* BTK */
    HI_BTK_HI=0x4,
};

enum HI_RES_FILE_INDEX {
    /* BCKS */
    HI_INDEX_BCK_HI_POSE=0x6,
    HI_INDEX_BCK_HI_WAIT01=0x7,
    
    /* BDLM */
    HI_INDEX_BDL_HI=0xA,
    
    /* BTP */
    HI_INDEX_BTP_MABA=0xD,
    
    /* BTK */
    HI_INDEX_BTK_HI=0x10,
};

#endif /* RES_HI_H */
