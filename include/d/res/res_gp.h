#ifndef RES_GP_H
#define RES_GP_H

#include "global.h" // IWYU pragma: keep

enum GP_RES_FILE_ID {
    /* BCKS */
    GP_BCK_GIVE=0x0,
    GP_BCK_GRIN=0x1,
    GP_BCK_HAIR=0x2,
    GP_BCK_TALK02=0x3,
    GP_BCK_TALK03=0x4,
    GP_BCK_WAIT01=0x5,
    GP_BCK_WALK=0x8,
    
    /* BDLM */
    GP_BDL_GP=0x6,
    
    /* BTP */
    GP_BTP_MABA01=0x7,
};

enum GP_RES_FILE_INDEX {
    /* BCKS */
    GP_INDEX_BCK_GIVE=0x5,
    GP_INDEX_BCK_GRIN=0x6,
    GP_INDEX_BCK_HAIR=0x7,
    GP_INDEX_BCK_TALK02=0x8,
    GP_INDEX_BCK_TALK03=0x9,
    GP_INDEX_BCK_WAIT01=0xA,
    GP_INDEX_BCK_WALK=0xB,
    
    /* BDLM */
    GP_INDEX_BDL_GP=0xE,
    
    /* BTP */
    GP_INDEX_BTP_MABA01=0x11,
};

#endif /* RES_GP_H */
