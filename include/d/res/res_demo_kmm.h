#ifndef RES_DEMO_KMM_H
#define RES_DEMO_KMM_H

#include "global.h" // IWYU pragma: keep

enum DEMO_KMM_RES_FILE_ID {
    /* BMD */
    DEMO_KMM_BMD_KA=0x0,
    
    /* BCKS */
    DEMO_KMM_BCK_04_KA_CUT06_KEIKOKU=0x1,
    DEMO_KMM_BCK_KA_WAIT1=0x2,
};

enum DEMO_KMM_RES_FILE_INDEX {
    /* BMD */
    DEMO_KMM_INDEX_BMD_KA=0x4,
    
    /* BCKS */
    DEMO_KMM_INDEX_BCK_04_KA_CUT06_KEIKOKU=0x7,
    DEMO_KMM_INDEX_BCK_KA_WAIT1=0x8,
};

#endif /* RES_DEMO_KMM_H */
