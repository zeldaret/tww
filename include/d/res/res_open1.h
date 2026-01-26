#ifndef RES_OPEN1_H
#define RES_OPEN1_H

#include "global.h" // IWYU pragma: keep

#if VERSION > VERSION_DEMO
enum OPEN1_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    OPEN1_BLO_OPENING=0x4,
    
    /* TIMG */
    OPEN1_BTI_BLACK=0x7,
    OPEN1_BTI_DEMO_1=0x8,
    OPEN1_BTI_DEMO_2=0x9,
};
#endif

#endif /* RES_OPEN1_H */
