#ifndef RES_HO_H
#define RES_HO_H

enum dRes_INDEX_HO {
    /* BCKS */
    dRes_INDEX_HO_BCK_HO_GLAD_e=0x6,
    dRes_INDEX_HO_BCK_HO_TALK01_e=0x7,
    dRes_INDEX_HO_BCK_HO_TALK02_e=0x8,
    dRes_INDEX_HO_BCK_HO_WAIT01_e=0x9,
    /* BDL  */
    dRes_INDEX_HO_BDL_HO_PEND_e=0xC,
    /* BDLM */
    dRes_INDEX_HO_BDL_HO_e=0xF,
    /* BTP  */
    dRes_INDEX_HO_BTP_HO_MABA01_e=0x12,
};

enum dRes_ID_HO {
    /* BCKS */
    dRes_ID_HO_BCK_HO_GLAD_e=0x6,
    dRes_ID_HO_BCK_HO_TALK01_e=0x7,
    dRes_ID_HO_BCK_HO_TALK02_e=0x8,
    dRes_ID_HO_BCK_HO_WAIT01_e=0x9,
    /* BDL  */
    dRes_ID_HO_BDL_HO_PEND_e=0xC,
    /* BDLM */
    dRes_ID_HO_BDL_HO_e=0xF,
    /* BTP  */
    dRes_ID_HO_BTP_HO_MABA01_e=0x12,
};

enum HO_PEND_JNT {
    HO_PEND_JNT_VHAPL_MODEL_e=0x0,
};

enum HO_JNT {
    HO_JNT_WORLD_ROOT_e=0x0,
    HO_JNT_BACKBONE_e=0x1,
    HO_JNT_HEAD_e=0x2,
    HO_JNT_SHOULDERL_e=0x3,
    HO_JNT_ARML1_e=0x4,
    HO_JNT_ARML2_e=0x5,
    HO_JNT_HANDL_e=0x6,
    HO_JNT_SHOULDERR_e=0x7,
    HO_JNT_ARMR1_e=0x8,
    HO_JNT_ARMR2_e=0x9,
    HO_JNT_HANDR_e=0xA,
    HO_JNT_WAIST_e=0xB,
    HO_JNT_LEGL1_e=0xC,
    HO_JNT_LEGL2_e=0xD,
    HO_JNT_FOOTL_e=0xE,
    HO_JNT_LEGR1_e=0xF,
    HO_JNT_LEGR2_e=0x10,
    HO_JNT_FOOTR_e=0x11,
};

#endif /* !RES_HO_H */