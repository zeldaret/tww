#ifndef RES_HSEN1_H
#define RES_HSEN1_H

enum dRes_INDEX_HSEN1 {
    /* BDLM */
    dRes_INDEX_HSEN1_BDL_HSEN1_e=0x5,
    /* BTK  */
    dRes_INDEX_HSEN1_BTK_HSEN1_e=0x8,
    dRes_INDEX_HSEN1_BTK_HSEN2_e=0x9,
    /* DZB  */
    dRes_INDEX_HSEN1_DZB_HSEN1_e=0xC,
};

enum dRes_ID_HSEN1 {
    /* BDLM */
    dRes_ID_HSEN1_BDL_HSEN1_e=0x5,
    /* BTK  */
    dRes_ID_HSEN1_BTK_HSEN1_e=0x8,
    dRes_ID_HSEN1_BTK_HSEN2_e=0x9,
    /* DZB  */
    dRes_ID_HSEN1_DZB_HSEN1_e=0xC,
};

enum HSEN1_JNT {
    HSEN1_JNT_HSEN1_00_e=0x0,
    HSEN1_JNT_POLYSURFACE4_e=0x1,
    HSEN1_JNT_PURO_e=0x2,
};

#endif /* !RES_HSEN1_H */