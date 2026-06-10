#ifndef RES_CC_H
#define RES_CC_H

enum dRes_INDEX_CC {
    /* BAS  */
    dRes_INDEX_CC_BAS_ATACK01_e=0x8,
    dRes_INDEX_CC_BAS_ATACK02_e=0x9,
    dRes_INDEX_CC_BAS_ATACK03_e=0xA,
    dRes_INDEX_CC_BAS_HUSE2TACHI_e=0xB,
    dRes_INDEX_CC_BAS_HUSE_WALK_e=0xC,
    dRes_INDEX_CC_BAS_START_e=0xD,
    dRes_INDEX_CC_BAS_TACHI2HUSE_e=0xE,
    dRes_INDEX_CC_BAS_TACHI_WALK_e=0xF,
    dRes_INDEX_CC_BAS_TSTART01_e=0x10,
    dRes_INDEX_CC_BAS_TSTART02_e=0x11,
    /* BCK  */
    dRes_INDEX_CC_BCK_ATACK01_e=0x14,
    dRes_INDEX_CC_BCK_ATACK02_e=0x15,
    dRes_INDEX_CC_BCK_ATACK03_e=0x16,
    dRes_INDEX_CC_BCK_CC_BETA_e=0x17,
    dRes_INDEX_CC_BCK_CC_PTCL_e=0x18,
    dRes_INDEX_CC_BCK_DEKU_START_e=0x19,
    dRes_INDEX_CC_BCK_HUKKATSU_e=0x1A,
    dRes_INDEX_CC_BCK_HUSE2TACHI_e=0x1B,
    dRes_INDEX_CC_BCK_HUSE_WALK_e=0x1C,
    dRes_INDEX_CC_BCK_MAHI_e=0x1D,
    dRes_INDEX_CC_BCK_START_e=0x1E,
    dRes_INDEX_CC_BCK_TACHI2HUSE_e=0x1F,
    dRes_INDEX_CC_BCK_TACHI_WALK_e=0x20,
    dRes_INDEX_CC_BCK_TSTART01_e=0x21,
    dRes_INDEX_CC_BCK_TSTART02_e=0x22,
    /* BDLM */
    dRes_INDEX_CC_BDL_CC_BETA_e=0x25,
    dRes_INDEX_CC_BDL_CC_IWA_e=0x26,
    dRes_INDEX_CC_BDL_CC_PTCL_e=0x27,
    /* BMDM */
    dRes_INDEX_CC_BMD_CC_e=0x2A,
    /* BRK  */
    dRes_INDEX_CC_BRK_CC_e=0x2D,
    dRes_INDEX_CC_BRK_CC_BETA_e=0x2E,
    dRes_INDEX_CC_BRK_CC_IWA01_e=0x2F,
    dRes_INDEX_CC_BRK_CC_IWA02_e=0x30,
    /* BTK  */
    dRes_INDEX_CC_BTK_CC_IWA01_e=0x33,
    dRes_INDEX_CC_BTK_CC_IWA02_e=0x34,
};

enum dRes_ID_CC {
    /* BAS  */
    dRes_ID_CC_BAS_ATACK01_e=0x8,
    dRes_ID_CC_BAS_ATACK02_e=0x9,
    dRes_ID_CC_BAS_ATACK03_e=0xA,
    dRes_ID_CC_BAS_HUSE2TACHI_e=0xB,
    dRes_ID_CC_BAS_HUSE_WALK_e=0xC,
    dRes_ID_CC_BAS_START_e=0xD,
    dRes_ID_CC_BAS_TACHI2HUSE_e=0xE,
    dRes_ID_CC_BAS_TACHI_WALK_e=0xF,
    dRes_ID_CC_BAS_TSTART01_e=0x10,
    dRes_ID_CC_BAS_TSTART02_e=0x11,
    /* BCK  */
    dRes_ID_CC_BCK_ATACK01_e=0x14,
    dRes_ID_CC_BCK_ATACK02_e=0x15,
    dRes_ID_CC_BCK_ATACK03_e=0x16,
    dRes_ID_CC_BCK_CC_BETA_e=0x17,
    dRes_ID_CC_BCK_CC_PTCL_e=0x18,
    dRes_ID_CC_BCK_DEKU_START_e=0x19,
    dRes_ID_CC_BCK_HUKKATSU_e=0x1A,
    dRes_ID_CC_BCK_HUSE2TACHI_e=0x1B,
    dRes_ID_CC_BCK_HUSE_WALK_e=0x1C,
    dRes_ID_CC_BCK_MAHI_e=0x1D,
    dRes_ID_CC_BCK_START_e=0x1E,
    dRes_ID_CC_BCK_TACHI2HUSE_e=0x1F,
    dRes_ID_CC_BCK_TACHI_WALK_e=0x20,
    dRes_ID_CC_BCK_TSTART01_e=0x21,
    dRes_ID_CC_BCK_TSTART02_e=0x22,
    /* BDLM */
    dRes_ID_CC_BDL_CC_BETA_e=0x25,
    dRes_ID_CC_BDL_CC_IWA_e=0x26,
    dRes_ID_CC_BDL_CC_PTCL_e=0x27,
    /* BMDM */
    dRes_ID_CC_BMD_CC_e=0x2A,
    /* BRK  */
    dRes_ID_CC_BRK_CC_e=0x2D,
    dRes_ID_CC_BRK_CC_BETA_e=0x2E,
    dRes_ID_CC_BRK_CC_IWA01_e=0x2F,
    dRes_ID_CC_BRK_CC_IWA02_e=0x30,
    /* BTK  */
    dRes_ID_CC_BTK_CC_IWA01_e=0x33,
    dRes_ID_CC_BTK_CC_IWA02_e=0x34,
};

enum CC_BETA_JNT {
    CC_BETA_JNT_CC_BETA_e=0x0,
};

enum CC_IWA_JNT {
    CC_IWA_JNT_CC_ROCK_e=0x0,
};

enum CC_PTCL_JNT {
    CC_PTCL_JNT_CCB_CENTER_e=0x0,
    CC_PTCL_JNT_CCB_1_e=0x1,
    CC_PTCL_JNT_CCB_10_e=0x2,
    CC_PTCL_JNT_CCB_11_e=0x3,
    CC_PTCL_JNT_CCB_2_e=0x4,
    CC_PTCL_JNT_CCB_3_e=0x5,
    CC_PTCL_JNT_CCB_4_e=0x6,
    CC_PTCL_JNT_CCB_5_e=0x7,
    CC_PTCL_JNT_CCB_6_e=0x8,
    CC_PTCL_JNT_CCB_7_e=0x9,
    CC_PTCL_JNT_CCB_8_e=0xA,
    CC_PTCL_JNT_CCB_9_e=0xB,
};

enum CC_JNT {
    CC_JNT_CENTER_e=0x0,
    CC_JNT_BODY01_e=0x1,
    CC_JNT_BODY02_e=0x2,
    CC_JNT_BODY03_e=0x3,
    CC_JNT_DODAI_e=0x4,
    CC_JNT_PETA_e=0x5,
};

#endif /* !RES_CC_H */