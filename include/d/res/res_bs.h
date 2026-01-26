#ifndef RES_BS_H
#define RES_BS_H

#include "global.h" // IWYU pragma: keep

enum BS_RES_FILE_ID {
    /* BCKS */
    BS_BCK_BS_TALK01=0x0,
    BS_BCK_BS_TALK02=0x1,
    BS_BCK_BS_TALK03=0x2,
    BS_BCK_BS_TALK04=0x3,
    BS_BCK_BS_WAIT01=0x4,
    BS_BCK_BS_LAUGH=0xC,
    BS_BCK_BS_PRAISE=0xD,
    BS_BCK_BS_ANGRY=0xF,
    BS_BCK_BS_MANTAN=0x10,
    
    /* BDLM */
    BS_BDL_BS=0x5,
    BS_BDL_BS_MET=0x6,
    
    /* BMDM */
    BS_BMD_SHOP_CURSOR01=0x7,
    
    /* BRK */
    BS_BRK_SHOP_CURSOR01=0x8,
    
    /* BTP */
    BS_BTP_BS=0x9,
    BS_BTP_LOOK=0xA,
    BS_BTP_MABA=0xB,
    BS_BTP_BS_PRAISE=0xE,
    
    /* BDL */
    BS_BDL_VSOLD=0x11,
};

enum BS_RES_FILE_INDEX {
    /* BCKS */
    BS_INDEX_BCK_BS_TALK01=0x8,
    BS_INDEX_BCK_BS_TALK02=0x9,
    BS_INDEX_BCK_BS_TALK03=0xA,
    BS_INDEX_BCK_BS_TALK04=0xB,
    BS_INDEX_BCK_BS_WAIT01=0xC,
    BS_INDEX_BCK_BS_LAUGH=0xD,
    BS_INDEX_BCK_BS_PRAISE=0xE,
    BS_INDEX_BCK_BS_ANGRY=0xF,
    BS_INDEX_BCK_BS_MANTAN=0x10,
    
    /* BDLM */
    BS_INDEX_BDL_BS=0x13,
    BS_INDEX_BDL_BS_MET=0x14,
    
    /* BMDM */
    BS_INDEX_BMD_SHOP_CURSOR01=0x17,
    
    /* BRK */
    BS_INDEX_BRK_SHOP_CURSOR01=0x1A,
    
    /* BTP */
    BS_INDEX_BTP_BS=0x1D,
    BS_INDEX_BTP_LOOK=0x1E,
    BS_INDEX_BTP_MABA=0x1F,
    BS_INDEX_BTP_BS_PRAISE=0x20,
    
    /* BDL */
    BS_INDEX_BDL_VSOLD=0x23,
};

#endif /* RES_BS_H */
