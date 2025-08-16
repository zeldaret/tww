#ifndef RES_BL_H
#define RES_BL_H

#include "global.h" // IWYU pragma: keep

enum BL_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    BL_BAS_ATACK=0x6,
    BL_BAS_FLY=0x7,
    BL_BAS_HAKKEN=0x8,
    BL_BAS_OOWARAI=0x9,
    BL_BAS_START01=0xA,
    BL_BAS_START02=0xB,
    BL_BAS_UCHIWA=0xC,
    BL_BAS_WARAU=0xD,
    
    /* BCK */
    BL_BCK_ATACK=0x10,
    BL_BCK_FLY=0x11,
    BL_BCK_HAKKEN=0x12,
    BL_BCK_HAKKENN=0x13,
    BL_BCK_OOWARAI=0x14,
    BL_BCK_START01=0x15,
    BL_BCK_START02=0x16,
    BL_BCK_UCHIWA=0x17,
    BL_BCK_WARAU=0x18,
    
    /* BDLM */
    BL_BDL_BL=0x1B,
    
    /* BTK */
    BL_BTK_OFF=0x1E,
    BL_BTK_ON=0x1F,
};

#endif /* RES_BL_H */
