#ifndef RES_LTUBW_H
#define RES_LTUBW_H

enum dRes_INDEX_LTUBW {
    /* BDL  */
    dRes_INDEX_LTUBW_BDL_ITUBW_e=0x6,
    dRes_INDEX_LTUBW_BDL_ITUHU_e=0x7,
    /* BDLM */
    dRes_INDEX_LTUBW_BDL_YWPFM00_e=0xA,
    /* BRK  */
    dRes_INDEX_LTUBW_BRK_YWPFM00_e=0xD,
    /* DZB  */
    dRes_INDEX_LTUBW_DZB_ITUBW_e=0x10,
    dRes_INDEX_LTUBW_DZB_ITUHT_e=0x11,
    dRes_INDEX_LTUBW_DZB_ITUSO_e=0x12,
};

enum dRes_ID_LTUBW {
    /* BDL  */
    dRes_ID_LTUBW_BDL_ITUBW_e=0x6,
    dRes_ID_LTUBW_BDL_ITUHU_e=0x7,
    /* BDLM */
    dRes_ID_LTUBW_BDL_YWPFM00_e=0xA,
    /* BRK  */
    dRes_ID_LTUBW_BRK_YWPFM00_e=0xD,
    /* DZB  */
    dRes_ID_LTUBW_DZB_ITUBW_e=0x10,
    dRes_ID_LTUBW_DZB_ITUHT_e=0x11,
    dRes_ID_LTUBW_DZB_ITUSO_e=0x12,
};

enum ITUBW_JNT {
    ITUBW_JNT_ITUBW_e=0x0,
};

enum ITUHU_JNT {
    ITUHU_JNT_ITUHU_e=0x0,
};

enum YWPFM00_JNT {
    YWPFM00_JNT_YWPMF00_e=0x0,
    YWPFM00_JNT_A00_e=0x1,
    YWPFM00_JNT_MOEFUTA_e=0x2,
};

#endif /* !RES_LTUBW_H */