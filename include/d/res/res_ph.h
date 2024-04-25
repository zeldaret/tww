#ifndef RES_PH_H
#define RES_PH_H

#include "global.h"

enum PH_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    PH_BAS_BCHAKUCHI=0x5,
    PH_BAS_BDAMAGE=0x6,
    PH_BAS_BFLY=0x7,
    PH_BAS_BHUKKI=0x8,
    PH_BAS_BJUMP=0x9,
    PH_BAS_BUCHI_CHAKU=0xA,
    PH_BAS_BUCHIWA=0xB,
    PH_BAS_PAWAY=0xC,
    PH_BAS_PFLY=0xD,
    PH_BAS_PHUKKI=0xE,
    PH_BAS_PUCHI_CHAKU=0xF,
    PH_BAS_PUCHIWA=0x10,
    
    /* BCK */
    PH_BCK_BCHAKUCHI=0x13,
    PH_BCK_BDAMAGE=0x14,
    PH_BCK_BFLY=0x15,
    PH_BCK_BHUKKI=0x16,
    PH_BCK_BJAWS=0x17,
    PH_BCK_BJUMP=0x18,
    PH_BCK_BUCHI_CHAKU=0x19,
    PH_BCK_BUCHIWA=0x1A,
    PH_BCK_PAWAY=0x1B,
    PH_BCK_PFLY=0x1C,
    PH_BCK_PHUKKI=0x1D,
    PH_BCK_PUCHI_CHAKU=0x1E,
    PH_BCK_PUCHIWA=0x1F,
    
    /* BDLM */
    PH_BDL_PHB=0x22,
    PH_BDL_PHP=0x23,
};

#endif /* RES_PH_H */
