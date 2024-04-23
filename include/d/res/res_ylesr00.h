#ifndef RES_YLESR00_H
#define RES_YLESR00_H

#include "global.h"

enum YLESR00_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    YLESR00_BCK_YLESR00=0x6,
    
    /* BMDM */
    YLESR00_BMD_YHTFR00=0x9,
    YLESR00_BMD_YLESR00=0xA,
    
    /* BRK */
    YLESR00_BRK_YHTFR00=0xD,
    YLESR00_BRK_YLESR00=0xE,
    
    /* BTK */
    YLESR00_BTK_YHTFR00=0x11,
    YLESR00_BTK_YLESR00=0x12,
};

#endif /* RES_YLESR00_H */
