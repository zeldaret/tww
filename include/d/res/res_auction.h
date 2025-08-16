#ifndef RES_AUCTION_H
#define RES_AUCTION_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum AUCTION_RES_FILE_ID { // IDs and indexes are synced
    /* ROOT */
    AUCTION_ARC_AUCTION=0x0,
    
    /* SCRN */
    AUCTION_BLO_AUCTION1=0x5,
    AUCTION_BLO_AUCTION2=0x6,
    
    /* TIMG */
    AUCTION_BTI_BET_ICON=0x9,
};
#else
enum AUCTION_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    AUCTION_BLO_AUCTION1=0x4,
    AUCTION_BLO_AUCTION2=0x5,
    
    /* TIMG */
    AUCTION_BTI_BET_ICON=0x8,
};
#endif

#endif /* RES_AUCTION_H */
