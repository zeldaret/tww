#ifndef RES_TLOGO_H
#define RES_TLOGO_H

#include "global.h" // IWYU pragma: keep

#if VERSION != VERSION_PAL
enum TLOGO_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    TLOGO_BCK_TITLE_SHIP=0x8,
    
    /* BDLM */
    TLOGO_BDL_SUBTITLE_KIRARI=0xB,
    TLOGO_BDL_SUBTITLE_START_ANIM=0xC,
    TLOGO_BDL_TITLE_SHIP=0xD,
    
    /* BPK */
    TLOGO_BPK_TITLE_SHIP=0x10,
    
    /* BTK */
    TLOGO_BTK_SUBTITLE_KIRARI=0x13,
    TLOGO_BTK_SUBTITLE_START_ANIM=0x14,
    
    /* SCRN */
    TLOGO_BLO_TITLE_LOGO=0x17,
    
    /* TIMG */
    TLOGO_BTI_C_NINTENDO=0x1A,
    TLOGO_BTI_DUMMY=0x1B,
    TLOGO_BTI_LOGO_ZELDA_JPA=0x1C,
    TLOGO_BTI_LOGO_ZELDA_MAIN=0x1D,
    TLOGO_BTI_PRESS_START=0x1E,
};
#endif

#endif /* RES_TLOGO_H */
