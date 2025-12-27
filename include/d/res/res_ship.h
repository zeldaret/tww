#ifndef RES_SHIP_H
#define RES_SHIP_H

#include "global.h" // IWYU pragma: keep

enum SHIP_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    SHIP_BCK_AKIBI1=0x5,
    SHIP_BCK_DAMAGE1=0x6,
    SHIP_BCK_FN_LOOK_L=0x7,
    SHIP_BCK_FN_LOOK_R=0x8,
    SHIP_BCK_FN_LOSE1=0x9,
    SHIP_BCK_FN_MAST_OFF2=0xA,
    SHIP_BCK_FN_MAST_ON2=0xB,
    SHIP_BCK_FN_TALK_A=0xC,
    SHIP_BCK_FN_TALK_B=0xD,
    SHIP_BCK_KYAKKAN1=0xE,
    
    /* BDL */
    SHIP_BDL_FN_BODY=0x11,
    SHIP_BDL_FN_HEAD_H=0x12,
    SHIP_BDL_VFNCN=0x13,
    SHIP_BDL_VFNCR=0x14,
    
    /* TEX */
    SHIP_BTI_NEW_HO1=0x17,
};

#endif /* RES_SHIP_H */
