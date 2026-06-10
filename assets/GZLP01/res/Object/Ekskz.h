#ifndef RES_EKSKZ_H
#define RES_EKSKZ_H

enum dRes_INDEX_EKSKZ {
    /* BCK  */
    dRes_INDEX_EKSKZ_BCK_YOCWD00_e=0x8,
    /* BDL  */
    dRes_INDEX_EKSKZ_BDL_EKSKZ_e=0xB,
    /* BDLM */
    dRes_INDEX_EKSKZ_BDL_YOCWD00_e=0xE,
    /* BRK  */
    dRes_INDEX_EKSKZ_BRK_YOCWD00_e=0x11,
    /* BTK  */
    dRes_INDEX_EKSKZ_BTK_YOCWD00_e=0x14,
    /* DZB  */
    dRes_INDEX_EKSKZ_DZB_EKSKZ_e=0x17,
};

enum dRes_ID_EKSKZ {
    /* BCK  */
    dRes_ID_EKSKZ_BCK_YOCWD00_e=0x8,
    /* BDL  */
    dRes_ID_EKSKZ_BDL_EKSKZ_e=0xB,
    /* BDLM */
    dRes_ID_EKSKZ_BDL_YOCWD00_e=0xE,
    /* BRK  */
    dRes_ID_EKSKZ_BRK_YOCWD00_e=0x11,
    /* BTK  */
    dRes_ID_EKSKZ_BTK_YOCWD00_e=0x14,
    /* DZB  */
    dRes_ID_EKSKZ_DZB_EKSKZ_e=0x17,
};

enum EKSKZ_JNT {
    EKSKZ_JNT_EKSKZ_e=0x0,
};

enum YOCWD00_JNT {
    YOCWD00_JNT_YOCWD00_e=0x0,
    YOCWD00_JNT_A00_e=0x1,
    YOCWD00_JNT_BIGINNER_e=0x2,
    YOCWD00_JNT_BIGOUTER_e=0x3,
    YOCWD00_JNT_INNER_e=0x4,
    YOCWD00_JNT_OUTER_e=0x5,
};

#endif /* !RES_EKSKZ_H */