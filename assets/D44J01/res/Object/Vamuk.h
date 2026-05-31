#ifndef RES_VAMUK_H
#define RES_VAMUK_H

enum dRes_INDEX_VAMUK {
    /* BDLM */
    dRes_INDEX_VAMUK_BDL_VAMUK_e=0x4,
    /* BTK  */
    dRes_INDEX_VAMUK_BTK_VAMUK_e=0x7,
};

enum dRes_ID_VAMUK {
    /* BDLM */
    dRes_ID_VAMUK_BDL_VAMUK_e=0x4,
    /* BTK  */
    dRes_ID_VAMUK_BTK_VAMUK_e=0x7,
};

enum VAMUK_JNT {
    VAMUK_JNT_ROOT_VAMUK_e=0x0,
    VAMUK_JNT_SC_AMUK_OUTSIDE_e=0x1,
    VAMUK_JNT_ZAMUK_INSIDE_e=0x2,
};

#endif /* !RES_VAMUK_H */