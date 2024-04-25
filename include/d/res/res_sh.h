#ifndef RES_SH_H
#define RES_SH_H

#include "global.h"

enum SH_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    SH_BAS_BCHAKUCHI=0x5,
    SH_BAS_BDAMAGE=0x6,
    SH_BAS_BFLY=0x7,
    SH_BAS_BHUKKI=0x8,
    SH_BAS_BJUMP=0x9,
    SH_BAS_BUCHI_CHAKU=0xA,
    SH_BAS_BUCHIWA=0xB,
    SH_BAS_PAWAY=0xC,
    SH_BAS_PFLY=0xD,
    SH_BAS_PHUKKI=0xE,
    SH_BAS_PUCHI_CHAKU=0xF,
    SH_BAS_PUCIWA=0x10,
    
    /* BCK */
    SH_BCK_BCHAKUCHI=0x13,
    SH_BCK_BDAMAGE=0x14,
    SH_BCK_BFLY=0x15,
    SH_BCK_BHUKKI=0x16,
    SH_BCK_BJAWS=0x17,
    SH_BCK_BJUMP=0x18,
    SH_BCK_BUCHI_CHAKU=0x19,
    SH_BCK_BUCHIWA=0x1A,
    SH_BCK_PAWAY=0x1B,
    SH_BCK_PFLY=0x1C,
    SH_BCK_PHUKKI=0x1D,
    SH_BCK_PUCHI_CHAKU=0x1E,
    SH_BCK_PUCHIWA=0x1F,
    
    /* BMDM */
    SH_BMD_SHB=0x22,
    SH_BMD_SHP=0x23,
};

#endif /* RES_SH_H */
