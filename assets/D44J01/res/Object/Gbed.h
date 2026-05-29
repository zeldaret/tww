#ifndef RES_GBED_H
#define RES_GBED_H

enum dRes_INDEX_GBED {
    /* BDL  */
    dRes_INDEX_GBED_BDL_K_GBED_e=0x4,
    /* DZB  */
    dRes_INDEX_GBED_DZB_K_GBED_e=0x7,
    dRes_INDEX_GBED_DZB_VTENG_e=0x8,
};

enum dRes_ID_GBED {
    /* BDL  */
    dRes_ID_GBED_BDL_K_GBED_e=0x4,
    /* DZB  */
    dRes_ID_GBED_DZB_K_GBED_e=0x7,
    dRes_ID_GBED_DZB_VTENG_e=0x8,
};

enum K_GBED_JNT {
    K_GBED_JNT_K_GBED_e=0x0,
    K_GBED_JNT_K_GBED_1_e=0x1,
    K_GBED_JNT_K_GS_e=0x2,
};

#endif /* !RES_GBED_H */