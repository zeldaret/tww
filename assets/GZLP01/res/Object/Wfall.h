#ifndef RES_WFALL_H
#define RES_WFALL_H

enum dRes_INDEX_WFALL {
    /* BDL  */
    dRes_INDEX_WFALL_BDL_HSUI1_e=0x7,
    /* BDLM */
    dRes_INDEX_WFALL_BDL_YSMNM00_e=0xA,
    dRes_INDEX_WFALL_BDL_YSWTR00_e=0xB,
    /* BRK  */
    dRes_INDEX_WFALL_BRK_YSMNM00_e=0xE,
    /* BTK  */
    dRes_INDEX_WFALL_BTK_YSMNM00_e=0x11,
    dRes_INDEX_WFALL_BTK_YSWTR00_e=0x12,
    /* DZB  */
    dRes_INDEX_WFALL_DZB_HSUI1_e=0x15,
};

enum dRes_ID_WFALL {
    /* BDL  */
    dRes_ID_WFALL_BDL_HSUI1_e=0x7,
    /* BDLM */
    dRes_ID_WFALL_BDL_YSMNM00_e=0xA,
    dRes_ID_WFALL_BDL_YSWTR00_e=0xB,
    /* BRK  */
    dRes_ID_WFALL_BRK_YSMNM00_e=0xE,
    /* BTK  */
    dRes_ID_WFALL_BTK_YSMNM00_e=0x11,
    dRes_ID_WFALL_BTK_YSWTR00_e=0x12,
    /* DZB  */
    dRes_ID_WFALL_DZB_HSUI1_e=0x15,
};

enum HSUI1_JNT {
    HSUI1_JNT_PCUBE8_e=0x0,
};

enum YSMNM00_JNT {
    YSMNM00_JNT_UMI4_e=0x0,
};

enum YSWTR00_JNT {
    YSWTR00_JNT_YSWTR00_e=0x0,
    YSWTR00_JNT_A00_e=0x1,
    YSWTR00_JNT_SOKUMEN_e=0x2,
    YSWTR00_JNT_SUIRYU_e=0x3,
};

#endif /* !RES_WFALL_H */