#ifndef RES_OQ_H
#define RES_OQ_H

#include "global.h" // IWYU pragma: keep

enum OQ_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    OQ_BCK_AATTACK1=0x6,
    OQ_BCK_AATTACK2_FUKU=0x7,
    OQ_BCK_AATTACK3=0x8,
    OQ_BCK_DEAD1=0x9,
    OQ_BCK_DEAD2=0xA,
    OQ_BCK_DEAD3=0xB,
    OQ_BCK_IKAKU=0xC,
    OQ_BCK_JET_ATTACK=0xD,
    OQ_BCK_JET_LOOP=0xE,
    OQ_BCK_JUMP=0xF,
    OQ_BCK_MOGURU=0x10,
    OQ_BCK_NOM_WAIT=0x11,
    OQ_BCK_SHIP_HIT=0x12,
    OQ_BCK_START=0x13,
    OQ_BCK_UMI_NEW_WAIT=0x14,
    
    /* BDLM */
    OQ_BDL_ISI=0x17,
    
    /* BMDM */
    OQ_BMD_OQ=0x1A,
    OQ_BMD_RED_OQ=0x1B,
    
    /* BRK */
    OQ_BRK_RED_OQ=0x1E,
};

#endif /* RES_OQ_H */
