#ifndef RES_DBARREL_H
#define RES_DBARREL_H

#include "global.h" // IWYU pragma: keep

enum DBARREL_RES_FILE_ID {
    /* BCK */
    DBARREL_BCK_02_TR_CD=0x0,
    DBARREL_BCK_02_TR_FL=0x1,
    DBARREL_BCK_02_TR_IN=0x2,
    DBARREL_BCK_02_TR_RL=0x3,
    
    /* BDL */
    DBARREL_BDL_KTARU_02=0x5,
    
    /* BTP */
    DBARREL_BTP_02_TR_C1=0x6,
};

enum DBARREL_RES_FILE_INDEX {
    /* BCK */
    DBARREL_INDEX_BCK_02_TR_CD=0x5,
    DBARREL_INDEX_BCK_02_TR_FL=0x6,
    DBARREL_INDEX_BCK_02_TR_IN=0x7,
    DBARREL_INDEX_BCK_02_TR_RL=0x8,
    
    /* BDL */
    DBARREL_INDEX_BDL_KTARU_02=0xB,
    
    /* BTP */
    DBARREL_INDEX_BTP_02_TR_C1=0xE,
};

#endif /* RES_DBARREL_H */
