#ifndef RES_VDORA_H
#define RES_VDORA_H

#include "global.h" // IWYU pragma: keep

enum VDORA_RES_FILE_ID {
    /* BDL */
    VDORA_BDL_VDORA=0x3,
    
    /* BCKS */
    VDORA_BCK_05_VDORA_CUT02_HIT=0x6,
    VDORA_BCK_05_VDORA_CUT02_WAIT=0x7,
};

enum VDORA_RES_FILE_INDEX {
    /* BDL */
    VDORA_INDEX_BDL_VDORA=0x4,
    
    /* BCKS */
    VDORA_INDEX_BCK_05_VDORA_CUT02_HIT=0x7,
    VDORA_INDEX_BCK_05_VDORA_CUT02_WAIT=0x8,
};

#endif /* RES_VDORA_H */
