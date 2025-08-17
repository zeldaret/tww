#ifndef RES_BB_H
#define RES_BB_H

#include "global.h" // IWYU pragma: keep

enum BB_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    BB_BAS_ATACK01=0x6,
    BB_BAS_EAT=0x7,
    BB_BAS_FLY01=0x8,
    BB_BAS_FLY02=0x9,
    BB_BAS_FLY03=0xA,
    BB_BAS_FLYB01=0xB,
    BB_BAS_FLYC=0xC,
    BB_BAS_FURA01=0xD,
    BB_BAS_GUSYA01=0xE,
    BB_BAS_LAND01=0xF,
    BB_BAS_LAND02=0x10,
    BB_BAS_WAIT=0x11,
    BB_BAS_WALK=0x12,
    
    /* BCK */
    BB_BCK_ATACK01=0x15,
    BB_BCK_DAMAGEP=0x16,
    BB_BCK_EAT=0x17,
    BB_BCK_FLY01=0x18,
    BB_BCK_FLY02=0x19,
    BB_BCK_FLY03=0x1A,
    BB_BCK_FLYB01=0x1B,
    BB_BCK_FLYC=0x1C,
    BB_BCK_FURA01=0x1D,
    BB_BCK_GUSYA01=0x1E,
    BB_BCK_LAND01=0x1F,
    BB_BCK_LAND02=0x20,
    BB_BCK_WAIT=0x21,
    BB_BCK_WALK=0x22,
    
    /* BDLM */
    BB_BDL_BB=0x25,
    BB_BDL_BB_TAIL=0x26,
    
    /* BTP */
    BB_BTP_TATACK=0x29,
    BB_BTP_TCLOSE=0x2A,
    BB_BTP_TDAMAGE=0x2B,
    BB_BTP_TKAIJO=0x2C,
    BB_BTP_TMABATAKI=0x2D,
    BB_BTP_TOPEN=0x2E,
};

#endif /* RES_BB_H */
