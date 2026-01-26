#ifndef RES_ZK_H
#define RES_ZK_H

#include "global.h" // IWYU pragma: keep

enum ZK_RES_FILE_ID {
    /* BCKS */
    ZK_BCK_ZK_TALK01=0x0,
    ZK_BCK_ZK_TALK02=0x1,
    ZK_BCK_ZK_WAIT01=0x2,
    ZK_BCK_ZK_WAIT02=0x3,
    
    /* BDLM */
    ZK_BDL_ZK=0x4,
    
    /* BTP */
    ZK_BTP_MABA=0x5,
};

enum ZK_RES_FILE_INDEX {
    /* BCKS */
    ZK_INDEX_BCK_ZK_TALK01=0x5,
    ZK_INDEX_BCK_ZK_TALK02=0x6,
    ZK_INDEX_BCK_ZK_WAIT01=0x7,
    ZK_INDEX_BCK_ZK_WAIT02=0x8,
    
    /* BDLM */
    ZK_INDEX_BDL_ZK=0xB,
    
    /* BTP */
    ZK_INDEX_BTP_MABA=0xE,
};

#endif /* RES_ZK_H */
