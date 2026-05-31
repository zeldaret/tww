#ifndef RES_BL_H
#define RES_BL_H

enum dRes_INDEX_BL {
    /* BAS  */
    dRes_INDEX_BL_BAS_ATACK_e=0x6,
    dRes_INDEX_BL_BAS_FLY_e=0x7,
    dRes_INDEX_BL_BAS_HAKKEN_e=0x8,
    dRes_INDEX_BL_BAS_OOWARAI_e=0x9,
    dRes_INDEX_BL_BAS_START01_e=0xA,
    dRes_INDEX_BL_BAS_START02_e=0xB,
    dRes_INDEX_BL_BAS_UCHIWA_e=0xC,
    dRes_INDEX_BL_BAS_WARAU_e=0xD,
    /* BCK  */
    dRes_INDEX_BL_BCK_ATACK_e=0x10,
    dRes_INDEX_BL_BCK_FLY_e=0x11,
    dRes_INDEX_BL_BCK_HAKKEN_e=0x12,
    dRes_INDEX_BL_BCK_HAKKENN_e=0x13,
    dRes_INDEX_BL_BCK_OOWARAI_e=0x14,
    dRes_INDEX_BL_BCK_START01_e=0x15,
    dRes_INDEX_BL_BCK_START02_e=0x16,
    dRes_INDEX_BL_BCK_UCHIWA_e=0x17,
    dRes_INDEX_BL_BCK_WARAU_e=0x18,
    /* BDLM */
    dRes_INDEX_BL_BDL_BL_e=0x1B,
    /* BTK  */
    dRes_INDEX_BL_BTK_OFF_e=0x1E,
    dRes_INDEX_BL_BTK_ON_e=0x1F,
};

enum dRes_ID_BL {
    /* BAS  */
    dRes_ID_BL_BAS_ATACK_e=0x6,
    dRes_ID_BL_BAS_FLY_e=0x7,
    dRes_ID_BL_BAS_HAKKEN_e=0x8,
    dRes_ID_BL_BAS_OOWARAI_e=0x9,
    dRes_ID_BL_BAS_START01_e=0xA,
    dRes_ID_BL_BAS_START02_e=0xB,
    dRes_ID_BL_BAS_UCHIWA_e=0xC,
    dRes_ID_BL_BAS_WARAU_e=0xD,
    /* BCK  */
    dRes_ID_BL_BCK_ATACK_e=0x10,
    dRes_ID_BL_BCK_FLY_e=0x11,
    dRes_ID_BL_BCK_HAKKEN_e=0x12,
    dRes_ID_BL_BCK_HAKKENN_e=0x13,
    dRes_ID_BL_BCK_OOWARAI_e=0x14,
    dRes_ID_BL_BCK_START01_e=0x15,
    dRes_ID_BL_BCK_START02_e=0x16,
    dRes_ID_BL_BCK_UCHIWA_e=0x17,
    dRes_ID_BL_BCK_WARAU_e=0x18,
    /* BDLM */
    dRes_ID_BL_BDL_BL_e=0x1B,
    /* BTK  */
    dRes_ID_BL_BTK_OFF_e=0x1E,
    dRes_ID_BL_BTK_ON_e=0x1F,
};

enum BL_JNT {
    BL_JNT_HEAD_e=0x0,
    BL_JNT_AGO_e=0x1,
};

#endif /* !RES_BL_H */