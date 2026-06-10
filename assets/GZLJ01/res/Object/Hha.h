#ifndef RES_HHA_H
#define RES_HHA_H

enum dRes_INDEX_HHA {
    /* BCK  */
    dRes_INDEX_HHA_BCK_YGSTP00_e=0x6,
    /* BDLM */
    dRes_INDEX_HHA_BDL_HHA1_e=0x9,
    dRes_INDEX_HHA_BDL_HHA2_e=0xA,
    dRes_INDEX_HHA_BDL_YGSTP00_e=0xB,
    dRes_INDEX_HHA_BDL_YSWTR00_e=0xC,
    /* BTK  */
    dRes_INDEX_HHA_BTK_YGSTP00_e=0xF,
    dRes_INDEX_HHA_BTK_YSWTR00_01_e=0x10,
    dRes_INDEX_HHA_BTK_YSWTR00_02_e=0x11,
    /* DZB  */
    dRes_INDEX_HHA_DZB_HHA1_e=0x14,
    dRes_INDEX_HHA_DZB_HHA2_e=0x15,
};

enum dRes_ID_HHA {
    /* BCK  */
    dRes_ID_HHA_BCK_YGSTP00_e=0x6,
    /* BDLM */
    dRes_ID_HHA_BDL_HHA1_e=0x9,
    dRes_ID_HHA_BDL_HHA2_e=0xA,
    dRes_ID_HHA_BDL_YGSTP00_e=0xB,
    dRes_ID_HHA_BDL_YSWTR00_e=0xC,
    /* BTK  */
    dRes_ID_HHA_BTK_YGSTP00_e=0xF,
    dRes_ID_HHA_BTK_YSWTR00_01_e=0x10,
    dRes_ID_HHA_BTK_YSWTR00_02_e=0x11,
    /* DZB  */
    dRes_ID_HHA_DZB_HHA1_e=0x14,
    dRes_ID_HHA_DZB_HHA2_e=0x15,
};

enum HHA1_JNT {
    HHA1_JNT_HHA1_00_e=0x0,
    HHA1_JNT_LOCATOR2_e=0x1,
    HHA1_JNT_OS_BODY4_e=0x2,
};

enum HHA2_JNT {
    HHA2_JNT_HHA2_00_e=0x0,
    HHA2_JNT_LOCATOR2_e=0x1,
    HHA2_JNT_OS_BODY5_e=0x2,
};

enum YGSTP00_JNT {
    YGSTP00_JNT_YGUSH00_e=0x0,
    YGSTP00_JNT_A00_e=0x1,
    YGSTP00_JNT_WATER_e=0x2,
};

enum YSWTR00_JNT {
    YSWTR00_JNT_YSWTR00_e=0x0,
    YSWTR00_JNT_A00_e=0x1,
    YSWTR00_JNT_SOKUMEN_e=0x2,
    YSWTR00_JNT_SUIRYU_e=0x3,
};

#endif /* !RES_HHA_H */