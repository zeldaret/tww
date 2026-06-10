#ifndef RES_VARFI_H
#define RES_VARFI_H

enum dRes_INDEX_VARFI {
    /* BDLM */
    dRes_INDEX_VARFI_BDL_VARFI_e=0x4,
    /* BTK  */
    dRes_INDEX_VARFI_BTK_VARFI_e=0x7,
};

enum dRes_ID_VARFI {
    /* BDLM */
    dRes_ID_VARFI_BDL_VARFI_e=0x4,
    /* BTK  */
    dRes_ID_VARFI_BTK_VARFI_e=0x7,
};

enum VARFI_JNT {
    VARFI_JNT_ROOT_VARFI_e=0x0,
    VARFI_JNT_SC_ARRI_OUTSIDE_e=0x1,
    VARFI_JNT_Z_ARRFI_INSIDE_e=0x2,
};

#endif /* !RES_VARFI_H */