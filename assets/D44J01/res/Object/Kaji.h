#ifndef RES_KAJI_H
#define RES_KAJI_H

enum dRes_INDEX_KAJI {
    /* BAS  */
    dRes_INDEX_KAJI_BAS_KJ_ANG_e=0x5,
    dRes_INDEX_KAJI_BAS_KJ_OMO_e=0x6,
    dRes_INDEX_KAJI_BAS_KJ_TORI_e=0x7,
    dRes_INDEX_KAJI_BAS_KJ_WAIT_e=0x8,
    /* BCK  */
    dRes_INDEX_KAJI_BCK_KJ_ANG_e=0xB,
    dRes_INDEX_KAJI_BCK_KJ_OMO_e=0xC,
    dRes_INDEX_KAJI_BCK_KJ_TORI_e=0xD,
    dRes_INDEX_KAJI_BCK_KJ_WAIT_e=0xE,
    /* BDL  */
    dRes_INDEX_KAJI_BDL_ASODA_e=0x11,
};

enum dRes_ID_KAJI {
    /* BAS  */
    dRes_ID_KAJI_BAS_KJ_ANG_e=0x0,
    dRes_ID_KAJI_BAS_KJ_OMO_e=0x1,
    dRes_ID_KAJI_BAS_KJ_TORI_e=0x2,
    dRes_ID_KAJI_BAS_KJ_WAIT_e=0x3,
    /* BCK  */
    dRes_ID_KAJI_BCK_KJ_ANG_e=0x4,
    dRes_ID_KAJI_BCK_KJ_OMO_e=0x5,
    dRes_ID_KAJI_BCK_KJ_TORI_e=0x6,
    dRes_ID_KAJI_BCK_KJ_WAIT_e=0x7,
    /* BDL  */
    dRes_ID_KAJI_BDL_ASODA_e=0x9,
};

enum ASODA_JNT {
    ASODA_JNT_ASODA_e=0x0,
};

#endif /* !RES_KAJI_H */