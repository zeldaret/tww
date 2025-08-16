#ifndef RES_TIMER_H
#define RES_TIMER_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum TIMER_RES_FILE_ID { // IDs and indexes are synced
    /* ROOT */
    TIMER_ARC_TIMER=0x0,
    
    /* SCRN */
    TIMER_BLO_SHIP_RACE0=0x4,
};
#elif VERSION <= VERSION_JPN
enum TIMER_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    TIMER_BLO_SHIP_RACE0=0x3,
};
#else
enum TIMER_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    TIMER_BLO_SHIP_RACE0=0x4,
    
    /* TIMG */
    TIMER_BTI_RUPY_NUM_DOT_2=0x7,
};
#endif

#endif /* RES_TIMER_H */
