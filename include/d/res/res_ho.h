#ifndef RES_HO_H
#define RES_HO_H

#include "global.h" // IWYU pragma: keep

enum HO_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    HO_BCK_HO_GLAD=0x6,
    HO_BCK_HO_TALK01=0x7,
    HO_BCK_HO_TALK02=0x8,
    HO_BCK_HO_WAIT01=0x9,
    
    /* BDL */
    HO_BDL_HO_PEND=0xC,
    
    /* BDLM */
    HO_BDL_HO=0xF,
    
    /* BTP */
    HO_BTP_HO_MABA01=0x12,
};

#endif /* RES_HO_H */
