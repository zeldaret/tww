#ifndef RES_GMJWP_H
#define RES_GMJWP_H

#include "global.h" // IWYU pragma: keep

enum GMJWP_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    GMJWP_BCK_GMJWP01=0x6,
    
    /* BDLM */
    GMJWP_BDL_GMJWP00=0x9,
    
    /* BRK */
    GMJWP_BRK_GMJWP01=0xC,
    
    /* BTK */
    GMJWP_BTK_GMJWP00=0xF,
    GMJWP_BTK_GMJWP02=0x10,
};

#endif /* RES_GMJWP_H */
