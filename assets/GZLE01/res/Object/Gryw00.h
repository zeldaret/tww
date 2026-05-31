#ifndef RES_GRYW00_H
#define RES_GRYW00_H

enum dRes_INDEX_GRYW00 {
    /* BCK  */
    dRes_INDEX_GRYW00_BCK_GRYW00_e=0x6,
    /* BDLM */
    dRes_INDEX_GRYW00_BDL_GRYW00_e=0x9,
    /* BTK  */
    dRes_INDEX_GRYW00_BTK_GRYW00_e=0xC,
    /* DZB  */
    dRes_INDEX_GRYW00_DZB_EWATER_e=0xF,
};

enum dRes_ID_GRYW00 {
    /* BCK  */
    dRes_ID_GRYW00_BCK_GRYW00_e=0x6,
    /* BDLM */
    dRes_ID_GRYW00_BDL_GRYW00_e=0x9,
    /* BTK  */
    dRes_ID_GRYW00_BTK_GRYW00_e=0xC,
    /* DZB  */
    dRes_ID_GRYW00_DZB_EWATER_e=0xF,
};

enum GRYW00_JNT {
    GRYW00_JNT_ROOT_e=0x0,
    GRYW00_JNT_GRYW00_e=0x1,
    GRYW00_JNT_WATER1_e=0x2,
};

#endif /* !RES_GRYW00_H */