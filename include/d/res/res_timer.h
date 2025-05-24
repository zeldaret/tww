#ifndef RES_TIMER_H
#define RES_TIMER_H

#include "global.h"

#if VERSION <= VERSION_JPN
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
