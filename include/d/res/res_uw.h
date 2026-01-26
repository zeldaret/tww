#ifndef RES_UW_H
#define RES_UW_H

#include "global.h" // IWYU pragma: keep

enum UW_RES_FILE_ID {
    /* BCKS */
    UW_BCK_UW_TALK01=0x4,
    UW_BCK_UW_TALK02=0x5,
    UW_BCK_UW_WAIT01=0x6,
    UW_BCK_UW_WAIT02=0x7,
    UW_BCK_UW_TALK03=0xB,
    UW_BCK_UW_TALK04=0xC,
    UW_BCK_UW_02HOKAN=0xD,
    UW_BCK_UW_HAPPY=0xE,
    UW_BCK_UW_MOJIMOJI=0xF,
    
    /* BDL */
    UW_BDL_UW=0x1,
    
    /* BDLM */
    UW_BDL_UW01_HEAD=0x2,
    UW_BDL_UW02_HEAD=0x8,
    
    /* BTP */
    UW_BTP_UW01_MABA=0x3,
    UW_BTP_UW02_MABA=0x9,
    
    /* BMT */
    UW_BMT_UW02=0xA,
};

enum UW_RES_FILE_INDEX {
    /* BCKS */
    UW_INDEX_BCK_UW_TALK01=0x7,
    UW_INDEX_BCK_UW_TALK02=0x8,
    UW_INDEX_BCK_UW_WAIT01=0x9,
    UW_INDEX_BCK_UW_WAIT02=0xA,
    UW_INDEX_BCK_UW_TALK03=0xB,
    UW_INDEX_BCK_UW_TALK04=0xC,
    UW_INDEX_BCK_UW_02HOKAN=0xD,
    UW_INDEX_BCK_UW_HAPPY=0xE,
    UW_INDEX_BCK_UW_MOJIMOJI=0xF,
    
    /* BDL */
    UW_INDEX_BDL_UW=0x12,
    
    /* BDLM */
    UW_INDEX_BDL_UW01_HEAD=0x15,
    UW_INDEX_BDL_UW02_HEAD=0x16,
    
    /* BTP */
    UW_INDEX_BTP_UW01_MABA=0x19,
    UW_INDEX_BTP_UW02_MABA=0x1A,
    
    /* BMT */
    UW_INDEX_BMT_UW02=0x1D,
};

#endif /* RES_UW_H */
