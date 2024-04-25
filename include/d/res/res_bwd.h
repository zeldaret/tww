#ifndef RES_BWD_H
#define RES_BWD_H

#include "global.h"

enum BWD_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    BWD_BCK_BWD_ATTACK=0x7,
    BWD_BCK_BWD_ATTACK_EAT=0x8,
    BWD_BCK_BWD_ATTACK_SHIPPAI=0x9,
    BWD_BCK_BWD_DAMAGE1=0xA,
    BWD_BCK_BWD_DAMAGE2=0xB,
    BWD_BCK_BWD_DEAD1=0xC,
    BWD_BCK_BWD_DEAD2=0xD,
    BWD_BCK_BWD_DEAD3=0xE,
    BWD_BCK_BWD_FLY=0xF,
    BWD_BCK_BWD_JATTACK1=0x10,
    BWD_BCK_BWD_JATTACK2=0x11,
    BWD_BCK_BWD_JATTACK3=0x12,
    BWD_BCK_BWD_NUKARERU=0x13,
    BWD_BCK_BWD_NUKARERU_LOOP=0x14,
    BWD_BCK_BWD_START=0x15,
    BWD_BCK_BWD_TEST=0x16,
    BWD_BCK_BWD_WAIT=0x17,
    BWD_BCK_GSP00=0x18,
    BWD_BCK_GSP01=0x19,
    
    /* BDLM */
    BWD_BDL_BERO=0x1C,
    BWD_BDL_BERO_SAKI=0x1D,
    BWD_BDL_BWD=0x1E,
    BWD_BDL_BWD_SHIPPOA=0x1F,
    BWD_BDL_BWD_SHIPPOB=0x20,
    BWD_BDL_GSP00=0x21,
    BWD_BDL_GSP01=0x22,
    BWD_BDL_HTAKI1=0x23,
    BWD_BDL_HTAKI2=0x24,
    BWD_BDL_HTRYF1=0x25,
    
    /* BRK */
    BWD_BRK_BWD=0x28,
    BWD_BRK_BWD_SHIPPOA=0x29,
    BWD_BRK_BWD_SHIPPOB=0x2A,
    BWD_BRK_GSP00=0x2B,
    BWD_BRK_GSP01=0x2C,
    BWD_BRK_HSAND1=0x2D,
    
    /* BTK */
    BWD_BTK_GSP00=0x30,
    BWD_BTK_GSP01=0x31,
    BWD_BTK_HSAND1=0x32,
    BWD_BTK_TAKI_END=0x33,
    BWD_BTK_TAKI_START=0x34,
    BWD_BTK_TAKI_WAIT=0x35,
    
    /* DZB */
    BWD_DZB_HTAKI1=0x38,
    BWD_DZB_HTRYF1=0x39,
};

#endif /* RES_BWD_H */
