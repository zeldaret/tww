#ifndef RES_DS_H
#define RES_DS_H

enum dRes_INDEX_DS {
    /* BMDM */
    dRes_INDEX_DS_BMD_SHOP_CURSOR01_e=0x9,
    /* BRK  */
    dRes_INDEX_DS_BRK_SHOP_CURSOR01_e=0xC,
    /* BTP  */
    dRes_INDEX_DS_BTP_MABA01_e=0xF,
    dRes_INDEX_DS_BTP_MABA02_e=0x10,
    /* BDLM */
    dRes_INDEX_DS_BDL_CK_e=0x13,
    dRes_INDEX_DS_BDL_GTYDS00_e=0x14,
    /* BDL  */
    dRes_INDEX_DS_BDL_CK_FLASCO_e=0x17,
    dRes_INDEX_DS_BDL_CK_JAR_e=0x18,
    /* BTK  */
    dRes_INDEX_DS_BTK_GTYDS00_e=0x1B,
    /* BCKS */
    dRes_INDEX_DS_BCK_AMAZED_e=0x1E,
    dRes_INDEX_DS_BCK_FLUT_e=0x1F,
    dRes_INDEX_DS_BCK_MAKE_e=0x20,
    dRes_INDEX_DS_BCK_MEGANE_e=0x21,
    dRes_INDEX_DS_BCK_TALK01_e=0x22,
    dRes_INDEX_DS_BCK_WAIT01_e=0x23,
    dRes_INDEX_DS_BCK_WAIT02_e=0x24,
    dRes_INDEX_DS_BCK_WALK_e=0x25,
};

enum dRes_ID_DS {
    /* BMDM */
    dRes_ID_DS_BMD_SHOP_CURSOR01_e=0x3,
    /* BRK  */
    dRes_ID_DS_BRK_SHOP_CURSOR01_e=0x4,
    /* BTP  */
    dRes_ID_DS_BTP_MABA01_e=0x5,
    dRes_ID_DS_BTP_MABA02_e=0xC,
    /* BDLM */
    dRes_ID_DS_BDL_CK_e=0xD,
    dRes_ID_DS_BDL_GTYDS00_e=0x18,
    /* BDL  */
    dRes_ID_DS_BDL_CK_FLASCO_e=0x10,
    dRes_ID_DS_BDL_CK_JAR_e=0x11,
    /* BTK  */
    dRes_ID_DS_BTK_GTYDS00_e=0x19,
    /* BCKS */
    dRes_ID_DS_BCK_AMAZED_e=0x1A,
    dRes_ID_DS_BCK_FLUT_e=0x1B,
    dRes_ID_DS_BCK_MAKE_e=0x1C,
    dRes_ID_DS_BCK_MEGANE_e=0x1D,
    dRes_ID_DS_BCK_TALK01_e=0x1E,
    dRes_ID_DS_BCK_WAIT01_e=0x1F,
    dRes_ID_DS_BCK_WAIT02_e=0x20,
    dRes_ID_DS_BCK_WALK_e=0x21,
};

enum SHOP_CURSOR01_JNT {
    SHOP_CURSOR01_JNT_CURSOR01_e=0x0,
};

enum CK_JNT {
    CK_JNT_WORLD_ROOT_e=0x0,
    CK_JNT_BACKBONE_e=0x1,
    CK_JNT_HEAD_e=0x2,
    CK_JNT_GOGGLE_e=0x3,
    CK_JNT_SHOULDERL_e=0x4,
    CK_JNT_ARML1_e=0x5,
    CK_JNT_ARML2_e=0x6,
    CK_JNT_HANDL_e=0x7,
    CK_JNT_SHOULDERR_e=0x8,
    CK_JNT_ARMR1_e=0x9,
    CK_JNT_ARMR2_e=0xA,
    CK_JNT_HANDR_e=0xB,
    CK_JNT_WAIST_e=0xC,
    CK_JNT_LEGL1_e=0xD,
    CK_JNT_LEGL2_e=0xE,
    CK_JNT_FOOTL_e=0xF,
    CK_JNT_LEGR1_e=0x10,
    CK_JNT_LEGR2_e=0x11,
    CK_JNT_FOOTR_e=0x12,
};

enum GTYDS00_JNT {
    GTYDS00_JNT_GTYDS00_e=0x0,
    GTYDS00_JNT_A00_e=0x1,
    GTYDS00_JNT_SMOKE1_e=0x2,
    GTYDS00_JNT_SMOKE2_e=0x3,
};

enum CK_FLASCO_JNT {
    CK_FLASCO_JNT_FLASCO_e=0x0,
};

enum CK_JAR_JNT {
    CK_JAR_JNT_JAR_e=0x0,
};

#endif /* !RES_DS_H */