#ifndef RES_UG_H
#define RES_UG_H

enum dRes_INDEX_UG {
    /* BCKS */
    dRes_INDEX_UG_BCK_UG01HEAD_SIT01_e=0x7,
    dRes_INDEX_UG_BCK_UG01HEAD_SIT02_e=0x8,
    dRes_INDEX_UG_BCK_UG01HEAD_TALK01_e=0x9,
    dRes_INDEX_UG_BCK_UG01HEAD_TALK02_e=0xA,
    dRes_INDEX_UG_BCK_UG01HEAD_WAIT01_e=0xB,
    dRes_INDEX_UG_BCK_UG01HEAD_WALK_e=0xC,
    dRes_INDEX_UG_BCK_UG_SIT01_e=0xD,
    dRes_INDEX_UG_BCK_UG_SIT02_e=0xE,
    dRes_INDEX_UG_BCK_UG_TALK01_e=0xF,
    dRes_INDEX_UG_BCK_UG_TALK02_e=0x10,
    dRes_INDEX_UG_BCK_UG_WAIT01_e=0x11,
    dRes_INDEX_UG_BCK_UG_WALK_e=0x12,
    /* BDL  */
    dRes_INDEX_UG_BDL_UG_e=0x15,
    /* BDLM */
    dRes_INDEX_UG_BDL_UG01_HEAD_e=0x18,
    dRes_INDEX_UG_BDL_UG02_HEAD_e=0x19,
    /* BMT  */
    dRes_INDEX_UG_BMT_UG02_e=0x1C,
    /* BTP  */
    dRes_INDEX_UG_BTP_UG01_MABA_e=0x1F,
    dRes_INDEX_UG_BTP_UG02_MABA_e=0x20,
};

enum dRes_ID_UG {
    /* BCKS */
    dRes_ID_UG_BCK_UG01HEAD_SIT01_e=0x8,
    dRes_ID_UG_BCK_UG01HEAD_SIT02_e=0x9,
    dRes_ID_UG_BCK_UG01HEAD_TALK01_e=0xA,
    dRes_ID_UG_BCK_UG01HEAD_TALK02_e=0xB,
    dRes_ID_UG_BCK_UG01HEAD_WAIT01_e=0xC,
    dRes_ID_UG_BCK_UG01HEAD_WALK_e=0xD,
    dRes_ID_UG_BCK_UG_SIT01_e=0xE,
    dRes_ID_UG_BCK_UG_SIT02_e=0xF,
    dRes_ID_UG_BCK_UG_TALK01_e=0x10,
    dRes_ID_UG_BCK_UG_TALK02_e=0x11,
    dRes_ID_UG_BCK_UG_WAIT01_e=0x12,
    dRes_ID_UG_BCK_UG_WALK_e=0x13,
    /* BDL  */
    dRes_ID_UG_BDL_UG_e=0x2,
    /* BDLM */
    dRes_ID_UG_BDL_UG01_HEAD_e=0x3,
    dRes_ID_UG_BDL_UG02_HEAD_e=0x4,
    /* BMT  */
    dRes_ID_UG_BMT_UG02_e=0x5,
    /* BTP  */
    dRes_ID_UG_BTP_UG01_MABA_e=0x6,
    dRes_ID_UG_BTP_UG02_MABA_e=0x7,
};

enum UG_JNT {
    UG_JNT_WORLD_ROOT_e=0x0,
    UG_JNT_BACKBONE_e=0x1,
    UG_JNT_NECK_e=0x2,
    UG_JNT_HEAD_e=0x3,
    UG_JNT_SHOULDERL_e=0x4,
    UG_JNT_ARML1_e=0x5,
    UG_JNT_ARML2_e=0x6,
    UG_JNT_SHOULDERR_e=0x7,
    UG_JNT_ARMR1_e=0x8,
    UG_JNT_ARMR2_e=0x9,
    UG_JNT_WAIST_e=0xA,
    UG_JNT_LEGL1_e=0xB,
    UG_JNT_LEGL2_e=0xC,
    UG_JNT_FOOTL_e=0xD,
    UG_JNT_LEGR1_e=0xE,
    UG_JNT_LEGR2_e=0xF,
    UG_JNT_FOOTR_e=0x10,
};

enum UG01_HEAD_JNT {
    UG01_HEAD_JNT_HEAD2_e=0x0,
    UG01_HEAD_JNT_HAIR_e=0x1,
};

enum UG02_HEAD_JNT {
    UG02_HEAD_JNT_UG02_HEAD_e=0x0,
};

#endif /* !RES_UG_H */