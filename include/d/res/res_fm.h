#ifndef RES_FM_H
#define RES_FM_H

#include "global.h" // IWYU pragma: keep

enum FM_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    FM_BCK_ASITUKAMI=0x6,
    FM_BCK_DAMAGE=0x7,
    FM_BCK_DERU=0x8,
    FM_BCK_HIKIKOMU=0x9,
    FM_BCK_KUSIZASI=0xA,
    FM_BCK_MAHI=0xB,
    FM_BCK_MODORU=0xC,
    FM_BCK_NAGERU=0xD,
    FM_BCK_TUKAMU=0xE,
    FM_BCK_TUKAMU2WAIT=0xF,
    FM_BCK_TUMAMIWAIT=0x10,
    FM_BCK_WAIT=0x11,
    FM_BCK_YAYU=0x12,
    
    /* BDL */
    FM_BDL_FM=0x15,
    
    /* BDLM */
    FM_BDL_YPIT00=0x18,
    
    /* BTK */
    FM_BTK_YPIT00=0x1B,
};

#endif /* RES_FM_H */
