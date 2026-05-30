#ifndef RES_MTRYB_H
#define RES_MTRYB_H

enum dRes_INDEX_MTRYB {
    /* BDL  */
    dRes_INDEX_MTRYB_BDL_MTRYB_e=0x6,
    /* BDLM */
    dRes_INDEX_MTRYB_BDL_YTFBL00_e=0x9,
    /* BRK  */
    dRes_INDEX_MTRYB_BRK_YTFBL00_APP_e=0xC,
    dRes_INDEX_MTRYB_BRK_YTFBL00_CMN_e=0xD,
    /* DZB  */
    dRes_INDEX_MTRYB_DZB_MTRYB_e=0x10,
};

enum dRes_ID_MTRYB {
    /* BDL  */
    dRes_ID_MTRYB_BDL_MTRYB_e=0x6,
    /* BDLM */
    dRes_ID_MTRYB_BDL_YTFBL00_e=0x9,
    /* BRK  */
    dRes_ID_MTRYB_BRK_YTFBL00_APP_e=0xC,
    dRes_ID_MTRYB_BRK_YTFBL00_CMN_e=0xD,
    /* DZB  */
    dRes_ID_MTRYB_DZB_MTRYB_e=0x10,
};

enum MTRYB_JNT {
    MTRYB_JNT_MTRYB_e=0x0,
};

enum YTFBL00_JNT {
    YTFBL00_JNT_YTFBL00_e=0x0,
    YTFBL00_JNT_A00_e=0x1,
    YTFBL00_JNT_TRIFORCEBLOCKLIGHT_e=0x2,
};

#endif /* !RES_MTRYB_H */