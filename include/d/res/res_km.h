#ifndef RES_KM_H
#define RES_KM_H

#include "global.h" // IWYU pragma: keep

enum KM_RES_FILE_ID {
    /* BAS */
    KM_BAS_KM_WAIT01=0x0,
    
    /* BCK */
    KM_BCK_KM_WAIT01=0x1,
    
    /* BDLM */
    KM_BDL_KM=0x2,
    
    /* BTP */
    KM_BTP_MABA=0x3,
};

enum KM_RES_FILE_INDEX {
    /* BAS */
    KM_INDEX_BAS_KM_WAIT01=0x6,
    
    /* BCK */
    KM_INDEX_BCK_KM_WAIT01=0x9,
    
    /* BDLM */
    KM_INDEX_BDL_KM=0xC,
    
    /* BTP */
    KM_INDEX_BTP_MABA=0xF,
};

#endif /* RES_KM_H */
