#ifndef RES_RSH_H
#define RES_RSH_H

#include "global.h"

enum RSH_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    RSH_BAS_RS_JAMP=0x8,
    RSH_BAS_RS_PUSH=0x9,
    RSH_BAS_RS_SWING=0xA,
    RSH_BAS_RS_TALK01=0xB,
    RSH_BAS_RS_TALK02=0xC,
    RSH_BAS_RS_TALK03=0xD,
    RSH_BAS_RS_TAME=0xE,
    RSH_BAS_RS_WAIT01=0xF,
    RSH_BAS_RS_WAIT02=0x10,
    RSH_BAS_RS_WALK=0x11,
    
    /* BCK */
    RSH_BCK_RS_JAMP=0x14,
    RSH_BCK_RS_PUSH=0x15,
    RSH_BCK_RS_SWING=0x16,
    RSH_BCK_RS_TALK01=0x17,
    RSH_BCK_RS_TALK02=0x18,
    RSH_BCK_RS_TALK03=0x19,
    RSH_BCK_RS_TAME=0x1A,
    RSH_BCK_RS_WAIT01=0x1B,
    RSH_BCK_RS_WAIT02=0x1C,
    RSH_BCK_RS_WALK=0x1D,
    
    /* BDLM */
    RSH_BDL_RS=0x20,
    
    /* BMDM */
    RSH_BMD_SHOP_CURSOR01=0x23,
    
    /* BRK */
    RSH_BRK_SHOP_CURSOR01=0x26,
    
    /* BTP */
    RSH_BTP_RS_MABA01=0x29,
};

#endif /* RES_RSH_H */
