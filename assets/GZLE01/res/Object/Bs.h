#ifndef RES_BS_H
#define RES_BS_H

enum dRes_INDEX_BS {
    /* BCKS */
    dRes_INDEX_BS_BCK_BS_TALK01_e=0x8,
    dRes_INDEX_BS_BCK_BS_TALK02_e=0x9,
    dRes_INDEX_BS_BCK_BS_TALK03_e=0xA,
    dRes_INDEX_BS_BCK_BS_TALK04_e=0xB,
    dRes_INDEX_BS_BCK_BS_WAIT01_e=0xC,
    dRes_INDEX_BS_BCK_BS_LAUGH_e=0xD,
    dRes_INDEX_BS_BCK_BS_PRAISE_e=0xE,
    dRes_INDEX_BS_BCK_BS_ANGRY_e=0xF,
    dRes_INDEX_BS_BCK_BS_MANTAN_e=0x10,
    /* BDLM */
    dRes_INDEX_BS_BDL_BS_e=0x13,
    dRes_INDEX_BS_BDL_BS_MET_e=0x14,
    /* BMDM */
    dRes_INDEX_BS_BMD_SHOP_CURSOR01_e=0x17,
    /* BRK  */
    dRes_INDEX_BS_BRK_SHOP_CURSOR01_e=0x1A,
    /* BTP  */
    dRes_INDEX_BS_BTP_BS_e=0x1D,
    dRes_INDEX_BS_BTP_LOOK_e=0x1E,
    dRes_INDEX_BS_BTP_MABA_e=0x1F,
    dRes_INDEX_BS_BTP_BS_PRAISE_e=0x20,
    /* BDL  */
    dRes_INDEX_BS_BDL_VSOLD_e=0x23,
};

enum dRes_ID_BS {
    /* BCKS */
    dRes_ID_BS_BCK_BS_TALK01_e=0x0,
    dRes_ID_BS_BCK_BS_TALK02_e=0x1,
    dRes_ID_BS_BCK_BS_TALK03_e=0x2,
    dRes_ID_BS_BCK_BS_TALK04_e=0x3,
    dRes_ID_BS_BCK_BS_WAIT01_e=0x4,
    dRes_ID_BS_BCK_BS_LAUGH_e=0xC,
    dRes_ID_BS_BCK_BS_PRAISE_e=0xD,
    dRes_ID_BS_BCK_BS_ANGRY_e=0xF,
    dRes_ID_BS_BCK_BS_MANTAN_e=0x10,
    /* BDLM */
    dRes_ID_BS_BDL_BS_e=0x5,
    dRes_ID_BS_BDL_BS_MET_e=0x6,
    /* BMDM */
    dRes_ID_BS_BMD_SHOP_CURSOR01_e=0x7,
    /* BRK  */
    dRes_ID_BS_BRK_SHOP_CURSOR01_e=0x8,
    /* BTP  */
    dRes_ID_BS_BTP_BS_e=0x9,
    dRes_ID_BS_BTP_LOOK_e=0xA,
    dRes_ID_BS_BTP_MABA_e=0xB,
    dRes_ID_BS_BTP_BS_PRAISE_e=0xE,
    /* BDL  */
    dRes_ID_BS_BDL_VSOLD_e=0x11,
};

enum BS_JNT {
    BS_JNT_CENTER_e=0x0,
    BS_JNT_BACKBONE1_e=0x1,
    BS_JNT_BACKBONE2_e=0x2,
    BS_JNT_NECK_e=0x3,
    BS_JNT_HEAD_e=0x4,
    BS_JNT_SHOULDERL_e=0x5,
    BS_JNT_ARML1_e=0x6,
    BS_JNT_ARML2_e=0x7,
    BS_JNT_HANDL_e=0x8,
    BS_JNT_SHOULDERR_e=0x9,
    BS_JNT_ARMR1_e=0xA,
    BS_JNT_ARMR2_e=0xB,
    BS_JNT_HANDR_e=0xC,
    BS_JNT_WAIST_e=0xD,
    BS_JNT_LEGL1_e=0xE,
    BS_JNT_LEGL2_e=0xF,
    BS_JNT_FOOTL_e=0x10,
    BS_JNT_LEGR1_e=0x11,
    BS_JNT_LEGR2_e=0x12,
    BS_JNT_FOOTR_e=0x13,
};

enum BS_MET_JNT {
    BS_MET_JNT_BS_MET_e=0x0,
};

enum SHOP_CURSOR01_JNT {
    SHOP_CURSOR01_JNT_CURSOR01_e=0x0,
};

enum VSOLD_JNT {
    VSOLD_JNT_VSOLD_MODEL_e=0x0,
};

#endif /* !RES_BS_H */