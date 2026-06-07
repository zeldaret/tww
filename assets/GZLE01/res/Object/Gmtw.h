#ifndef RES_GMTW_H
#define RES_GMTW_H

enum dRes_INDEX_GMTW {
    /* BCK  */
    dRes_INDEX_GMTW_BCK_GMTW00_e=0x6,
    /* BDLM */
    dRes_INDEX_GMTW_BDL_GMTW00_e=0x9,
    /* BTK  */
    dRes_INDEX_GMTW_BTK_GMTW00_e=0xC,
    /* DZB  */
    dRes_INDEX_GMTW_DZB_GUMI0_e=0xF,
};

enum dRes_ID_GMTW {
    /* BCK  */
    dRes_ID_GMTW_BCK_GMTW00_e=0x6,
    /* BDLM */
    dRes_ID_GMTW_BDL_GMTW00_e=0x9,
    /* BTK  */
    dRes_ID_GMTW_BTK_GMTW00_e=0xC,
    /* DZB  */
    dRes_ID_GMTW_DZB_GUMI0_e=0xF,
};

enum GMTW00_JNT {
    GMTW00_JNT_ROOT_e=0x0,
    GMTW00_JNT_GMTW00_e=0x1,
    GMTW00_JNT_UE_e=0x2,
};

#endif /* !RES_GMTW_H */