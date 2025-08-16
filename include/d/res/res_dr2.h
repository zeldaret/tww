#ifndef RES_DR2_H
#define RES_DR2_H

#include "global.h" // IWYU pragma: keep

enum DR2_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    DR2_BCK_DR_BOSS_DEMO1=0x9,
    DR2_BCK_DR_SIPPO_BOU1=0xA,
    DR2_BCK_DR_SIPPO_WAIT1=0xB,
    
    /* BDLM */
    DR2_BDL_IWA00=0xE,
    DR2_BDL_IWA01_1=0xF,
    DR2_BDL_IWA01_2=0x10,
    DR2_BDL_IWA01_3=0x11,
    DR2_BDL_IWA01_4=0x12,
    DR2_BDL_IWA01_5=0x13,
    DR2_BDL_IWA01_6=0x14,
    
    /* BMD */
    DR2_BMD_DR=0x17,
    DR2_BMD_DR_SIPPO=0x18,
    
    /* BMDM */
    DR2_BMD_GAN_MAGMA=0x1B,
    DR2_BMD_MBYO1=0x1C,
    DR2_BMD_MBYO2=0x1D,
    
    /* BRK */
    DR2_BRK_MBYO2=0x20,
    
    /* BTK */
    DR2_BTK_GAN_MAGMA=0x23,
    DR2_BTK_MBYO1=0x24,
    DR2_BTK_MBYO2=0x25,
    
    /* DZB */
    DR2_DZB_MBYO1=0x28,
    DR2_DZB_MBYO2=0x29,
};

#endif /* RES_DR2_H */
