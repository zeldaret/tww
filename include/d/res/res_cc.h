#ifndef RES_CC_H
#define RES_CC_H

#include "global.h" // IWYU pragma: keep

enum CC_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    CC_BAS_ATACK01=0x8,
    CC_BAS_ATACK02=0x9,
    CC_BAS_ATACK03=0xA,
    CC_BAS_HUSE2TACHI=0xB,
    CC_BAS_HUSE_WALK=0xC,
    CC_BAS_START=0xD,
    CC_BAS_TACHI2HUSE=0xE,
    CC_BAS_TACHI_WALK=0xF,
    CC_BAS_TSTART01=0x10,
    CC_BAS_TSTART02=0x11,
    
    /* BCK */
    CC_BCK_ATACK01=0x14,
    CC_BCK_ATACK02=0x15,
    CC_BCK_ATACK03=0x16,
    CC_BCK_CC_BETA=0x17,
    CC_BCK_CC_PTCL=0x18,
    CC_BCK_DEKU_START=0x19,
    CC_BCK_HUKKATSU=0x1A,
    CC_BCK_HUSE2TACHI=0x1B,
    CC_BCK_HUSE_WALK=0x1C,
    CC_BCK_MAHI=0x1D,
    CC_BCK_START=0x1E,
    CC_BCK_TACHI2HUSE=0x1F,
    CC_BCK_TACHI_WALK=0x20,
    CC_BCK_TSTART01=0x21,
    CC_BCK_TSTART02=0x22,
    
    /* BDLM */
    CC_BDL_CC_BETA=0x25,
    CC_BDL_CC_IWA=0x26,
    CC_BDL_CC_PTCL=0x27,
    
    /* BMDM */
    CC_BMD_CC=0x2A,
    
    /* BRK */
    CC_BRK_CC=0x2D,
    CC_BRK_CC_BETA=0x2E,
    CC_BRK_CC_IWA01=0x2F,
    CC_BRK_CC_IWA02=0x30,
    
    /* BTK */
    CC_BTK_CC_IWA01=0x33,
    CC_BTK_CC_IWA02=0x34,
};

#endif /* RES_CC_H */
