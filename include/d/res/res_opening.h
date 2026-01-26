#ifndef RES_OPENING_H
#define RES_OPENING_H

#include "global.h" // IWYU pragma: keep

#if VERSION > VERSION_DEMO
enum OPENING_RES_FILE_ID { // IDs and indexes are synced
    /* SCRN */
    OPENING_BLO_OPENING=0x4,
    
    /* TIMG */
    OPENING_BTI_BLACK=0x7,
    OPENING_BTI_DEMO_1=0x8,
    OPENING_BTI_DEMO_2=0x9,
    OPENING_BTI_DEMO_3=0xA,
    OPENING_BTI_DEMO_4=0xB,
    OPENING_BTI_DEMO_4_2=0xC,
    OPENING_BTI_DEMO_5=0xD,
    OPENING_BTI_DEMO_6=0xE,
};
#endif

#endif /* RES_OPENING_H */
