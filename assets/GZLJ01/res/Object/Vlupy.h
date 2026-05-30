#ifndef RES_VLUPY_H
#define RES_VLUPY_H

enum dRes_INDEX_VLUPY {
    /* BDLM */
    dRes_INDEX_VLUPY_BDL_VLUPY_e=0x5,
    /* BRK  */
    dRes_INDEX_VLUPY_BRK_VLUPY_e=0x8,
    /* BTK  */
    dRes_INDEX_VLUPY_BTK_VLUPY_e=0xB,
};

enum dRes_ID_VLUPY {
    /* BDLM */
    dRes_ID_VLUPY_BDL_VLUPY_e=0x5,
    /* BRK  */
    dRes_ID_VLUPY_BRK_VLUPY_e=0x8,
    /* BTK  */
    dRes_ID_VLUPY_BTK_VLUPY_e=0xB,
};

enum VLUPY_JNT {
    VLUPY_JNT_ROOT_VLUPY_e=0x0,
    VLUPY_JNT_VLUPY1_OUTSIDE_e=0x1,
    VLUPY_JNT_VLUPY2_INSIDE_e=0x2,
};

#endif /* !RES_VLUPY_H */