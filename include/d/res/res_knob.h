#ifndef RES_KNOB_H
#define RES_KNOB_H

#include "global.h" // IWYU pragma: keep

enum KNOB_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    KNOB_BCK_DOOROPENADOOR=0x5,
    KNOB_BCK_DOOROPENBDOOR=0x6,
    
    /* BDL */
    KNOB_BDL_DOOR=0x9,
    KNOB_BDL_DOOR_A=0xA,
    KNOB_BDL_DOOR_B=0xB,
    KNOB_BDL_DOOR_C=0xC,
    KNOB_BDL_DOOR_D=0xD,
    KNOB_BDL_DOOR_E=0xE,
    KNOB_BDL_DOOR_F=0xF,
    KNOB_BDL_DOOR_G=0x10,
    KNOB_BDL_DOOR_H=0x11,
    
    /* DZB */
    KNOB_DZB_DOOR=0x14,
};

#endif /* RES_KNOB_H */
