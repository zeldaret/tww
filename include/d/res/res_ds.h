#ifndef RES_DS_H
#define RES_DS_H

#include "global.h" // IWYU pragma: keep

enum DS_RES_FILE_ID {
    /* BMDM */
    DS_BMD_SHOP_CURSOR01=0x3,
    
    /* BRK */
    DS_BRK_SHOP_CURSOR01=0x4,
    
    /* BTP */
    DS_BTP_MABA01=0x5,
    DS_BTP_MABA02=0xC,
    
    /* BDLM */
    DS_BDL_CK=0xD,
    DS_BDL_GTYDS00=0x18,
    
    /* BDL */
    DS_BDL_CK_FLASCO=0x10,
    DS_BDL_CK_JAR=0x11,
    
    /* BTK */
    DS_BTK_GTYDS00=0x19,
    
    /* BCKS */
    DS_BCK_AMAZED=0x1A,
    DS_BCK_FLUT=0x1B,
    DS_BCK_MAKE=0x1C,
    DS_BCK_MEGANE=0x1D,
    DS_BCK_TALK01=0x1E,
    DS_BCK_WAIT01=0x1F,
    DS_BCK_WAIT02=0x20,
    DS_BCK_WALK=0x21,
};

enum DS_RES_FILE_INDEX {
    /* BMDM */
    DS_INDEX_BMD_SHOP_CURSOR01=0x9,
    
    /* BRK */
    DS_INDEX_BRK_SHOP_CURSOR01=0xC,
    
    /* BTP */
    DS_INDEX_BTP_MABA01=0xF,
    DS_INDEX_BTP_MABA02=0x10,
    
    /* BDLM */
    DS_INDEX_BDL_CK=0x13,
    DS_INDEX_BDL_GTYDS00=0x14,
    
    /* BDL */
    DS_INDEX_BDL_CK_FLASCO=0x17,
    DS_INDEX_BDL_CK_JAR=0x18,
    
    /* BTK */
    DS_INDEX_BTK_GTYDS00=0x1B,
    
    /* BCKS */
    DS_INDEX_BCK_AMAZED=0x1E,
    DS_INDEX_BCK_FLUT=0x1F,
    DS_INDEX_BCK_MAKE=0x20,
    DS_INDEX_BCK_MEGANE=0x21,
    DS_INDEX_BCK_TALK01=0x22,
    DS_INDEX_BCK_WAIT01=0x23,
    DS_INDEX_BCK_WAIT02=0x24,
    DS_INDEX_BCK_WALK=0x25,
};

#endif /* RES_DS_H */
