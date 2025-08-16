#ifndef RES_MOZO_H
#define RES_MOZO_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum MOZO_RES_FILE_ID {
    /* BCKS */
    MOZO_BCK_MOZ=0x0,
    
    /* BRK */
    MOZO_BRK_MOZ=0x2,
    
    /* BTK */
    MOZO_BTK_MOZ=0x3,
    
    /* BDLM */
    MOZO_BDL_MOZ=0x4,
};

enum MOZO_RES_FILE_INDEX {
    /* BCKS */
    MOZO_INDEX_BCK_MOZ=0x6,
    
    /* BRK */
    MOZO_INDEX_BRK_MOZ=0x9,
    
    /* BTK */
    MOZO_INDEX_BTK_MOZ=0xC,
    
    /* BDLM */
    MOZO_INDEX_BDL_MOZ=0xF,
};
#else
enum MOZO_RES_FILE_ID {
    /* BCKS */
    MOZO_BCK_MOZ=0x6,
    
    /* BDLM */
    MOZO_BDL_MOZ=0x9,
    
    /* BRK */
    MOZO_BRK_MOZ=0xC,
    
    /* BTK */
    MOZO_BTK_MOZ=0xF,
};

enum MOZO_RES_FILE_INDEX {
    /* BCKS */
    MOZO_INDEX_BCK_MOZ=0x6,
    
    /* BDLM */
    MOZO_INDEX_BDL_MOZ=0x9,
    
    /* BRK */
    MOZO_INDEX_BRK_MOZ=0xC,
    
    /* BTK */
    MOZO_INDEX_BTK_MOZ=0xF,
};
#endif

#endif /* RES_MOZO_H */
