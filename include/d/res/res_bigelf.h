#ifndef RES_BIGELF_H
#define RES_BIGELF_H

#include "global.h" // IWYU pragma: keep

enum BIGELF_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    BIGELF_BCK_ENTER=0x6,
    BIGELF_BCK_FL_DEMO=0x7,
    BIGELF_BCK_WAIT01=0x8,
    
    /* BDLM */
    BIGELF_BDL_DY=0xB,
    BIGELF_BDL_DY_FL=0xC,
    
    /* BRK */
    BIGELF_BRK_DY_BODY=0xF,
    BIGELF_BRK_DY_FL=0x10,
    
    /* BTK */
    BIGELF_BTK_DY_BODY=0x13,
};

#endif /* RES_BIGELF_H */
