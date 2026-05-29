#ifndef RES_YCAGE_H
#define RES_YCAGE_H

enum dRes_INDEX_YCAGE {
    /* BCK  */
    dRes_INDEX_YCAGE_BCK_YHRBR00_e=0x7,
    /* BDLM */
    dRes_INDEX_YCAGE_BDL_YCAGE00_e=0xA,
    dRes_INDEX_YCAGE_BDL_YHRBR00_e=0xB,
    /* BRK  */
    dRes_INDEX_YCAGE_BRK_YCAGE00_e=0xE,
    dRes_INDEX_YCAGE_BRK_YHRBR00_e=0xF,
    /* BTK  */
    dRes_INDEX_YCAGE_BTK_YCAGE00_e=0x12,
    dRes_INDEX_YCAGE_BTK_YHRBR00_e=0x13,
    /* DZB  */
    dRes_INDEX_YCAGE_DZB_KEKKAI_e=0x16,
};

enum dRes_ID_YCAGE {
    /* BCK  */
    dRes_ID_YCAGE_BCK_YHRBR00_e=0x7,
    /* BDLM */
    dRes_ID_YCAGE_BDL_YCAGE00_e=0xA,
    dRes_ID_YCAGE_BDL_YHRBR00_e=0xB,
    /* BRK  */
    dRes_ID_YCAGE_BRK_YCAGE00_e=0xE,
    dRes_ID_YCAGE_BRK_YHRBR00_e=0xF,
    /* BTK  */
    dRes_ID_YCAGE_BTK_YCAGE00_e=0x12,
    dRes_ID_YCAGE_BTK_YHRBR00_e=0x13,
    /* DZB  */
    dRes_ID_YCAGE_DZB_KEKKAI_e=0x16,
};

enum YCAGE00_JNT {
    YCAGE00_JNT_YCAGE_e=0x0,
    YCAGE00_JNT_A00_e=0x1,
    YCAGE00_JNT_KEKKAI_e=0x2,
};

enum YHRBR00_JNT {
    YHRBR00_JNT_YHRBR00_e=0x0,
    YHRBR00_JNT_A00_e=0x1,
    YHRBR00_JNT_HIRALBARRIER_e=0x2,
};

#endif /* !RES_YCAGE_H */