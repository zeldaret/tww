#ifndef RES_DE_H
#define RES_DE_H

#include "global.h" // IWYU pragma: keep

enum DE_RES_FILE_ID {
    /* BCKS */
    DE_BCK_SLEEP=0x0,
    DE_BCK_SUFFER=0x1,
    DE_BCK_TALK01=0x2,
    DE_BCK_TALK02=0x3,
    DE_BCK_TALK03=0x4,
    DE_BCK_WAIT01=0x5,
    DE_BCK_WAKE=0x6,
    
    /* BDL */
    DE_BDL_DE=0x7,
    
    /* DZB */
    DE_DZB_DE=0x8,
};

enum DE_RES_FILE_INDEX {
    /* BCKS */
    DE_INDEX_BCK_SLEEP=0x5,
    DE_INDEX_BCK_SUFFER=0x6,
    DE_INDEX_BCK_TALK01=0x7,
    DE_INDEX_BCK_TALK02=0x8,
    DE_INDEX_BCK_TALK03=0x9,
    DE_INDEX_BCK_WAIT01=0xA,
    DE_INDEX_BCK_WAKE=0xB,
    
    /* BDL */
    DE_INDEX_BDL_DE=0xE,
    
    /* DZB */
    DE_INDEX_DZB_DE=0x11,
};

#endif /* RES_DE_H */
