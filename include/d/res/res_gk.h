#ifndef RES_GK_H
#define RES_GK_H

#include "global.h" // IWYU pragma: keep

enum GK_RES_FILE_ID {
    /* BCKS */
    GK_BCK_GK_TALK01=0x0,
    GK_BCK_GK_TALK02=0x1,
    GK_BCK_GK_TALK03=0x2,
    GK_BCK_GK_WAIT01=0x3,
    GK_BCK_GK_WALK=0x4,
    
    /* BDL */
    GK_BDL_GK_HAIR=0x5,
    GK_BDL_GK_HAT=0x6,
    
    /* BDLM */
    GK_BDL_GK=0x7,
    
    /* BTP */
    GK_BTP_GK=0x8,
};

enum GK_RES_FILE_INDEX {
    /* BCKS */
    GK_INDEX_BCK_GK_TALK01=0x6,
    GK_INDEX_BCK_GK_TALK02=0x7,
    GK_INDEX_BCK_GK_TALK03=0x8,
    GK_INDEX_BCK_GK_WAIT01=0x9,
    GK_INDEX_BCK_GK_WALK=0xA,
    
    /* BDL */
    GK_INDEX_BDL_GK_HAIR=0xD,
    GK_INDEX_BDL_GK_HAT=0xE,
    
    /* BDLM */
    GK_INDEX_BDL_GK=0x11,
    
    /* BTP */
    GK_INDEX_BTP_GK=0x14,
};

#endif /* RES_GK_H */
