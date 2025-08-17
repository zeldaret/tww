#ifndef RES_MN_H
#define RES_MN_H

#include "global.h" // IWYU pragma: keep

enum MN_RES_FILE_ID {
    /* BCKS */
    MN_BCK_MN_TALK01=0x4,
    MN_BCK_MN_TALK02=0x5,
    MN_BCK_MN_WAIT01=0x6,
    MN_BCK_MN_BIKKURI=0x7,
    MN_BCK_MN_JUMP01=0x8,
    MN_BCK_MN_JUMP02=0x9,
    MN_BCK_MN_WAIT02=0xA,
    MN_BCK_MN_WALK=0xB,
    
    /* BDL */
    MN_BDL_MN_BAG=0x1,
    
    /* BDLM */
    MN_BDL_MN=0x2,
    
    /* BTP */
    MN_BTP_MN_MABA=0x3,
};

enum MN_RES_FILE_INDEX {
    /* BCKS */
    MN_INDEX_BCK_MN_TALK01=0x6,
    MN_INDEX_BCK_MN_TALK02=0x7,
    MN_INDEX_BCK_MN_WAIT01=0x8,
    MN_INDEX_BCK_MN_BIKKURI=0x9,
    MN_INDEX_BCK_MN_JUMP01=0xA,
    MN_INDEX_BCK_MN_JUMP02=0xB,
    MN_INDEX_BCK_MN_WAIT02=0xC,
    MN_INDEX_BCK_MN_WALK=0xD,
    
    /* BDL */
    MN_INDEX_BDL_MN_BAG=0x10,
    
    /* BDLM */
    MN_INDEX_BDL_MN=0x13,
    
    /* BTP */
    MN_INDEX_BTP_MN_MABA=0x16,
};

#endif /* RES_MN_H */
