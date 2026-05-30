#ifndef RES_TT_H
#define RES_TT_H

enum dRes_INDEX_TT {
    /* BAS  */
    dRes_INDEX_TT_BAS_POSE_CC_e=0x6,
    dRes_INDEX_TT_BAS_POSE_ND_e=0x7,
    dRes_INDEX_TT_BAS_POSE_NL_e=0x8,
    dRes_INDEX_TT_BAS_POSE_NR_e=0x9,
    dRes_INDEX_TT_BAS_STEP01_e=0xA,
    dRes_INDEX_TT_BAS_TALK01_e=0xB,
    dRes_INDEX_TT_BAS_TALK02_e=0xC,
    dRes_INDEX_TT_BAS_TURN_e=0xD,
    dRes_INDEX_TT_BAS_WAIT01_e=0xE,
    /* BCK  */
    dRes_INDEX_TT_BCK_POSE_CC_e=0x11,
    dRes_INDEX_TT_BCK_POSE_ND_e=0x12,
    dRes_INDEX_TT_BCK_POSE_NL_e=0x13,
    dRes_INDEX_TT_BCK_POSE_NR_e=0x14,
    dRes_INDEX_TT_BCK_STEP01_e=0x15,
    dRes_INDEX_TT_BCK_TALK01_e=0x16,
    dRes_INDEX_TT_BCK_TALK02_e=0x17,
    dRes_INDEX_TT_BCK_TURN_e=0x18,
    dRes_INDEX_TT_BCK_WAIT01_e=0x19,
    /* BDLM */
    dRes_INDEX_TT_BDL_TT_e=0x1C,
    /* BTP  */
    dRes_INDEX_TT_BTP_MABA01_e=0x1F,
};

enum dRes_ID_TT {
    /* BAS  */
    dRes_ID_TT_BAS_POSE_CC_e=0x6,
    dRes_ID_TT_BAS_POSE_ND_e=0x7,
    dRes_ID_TT_BAS_POSE_NL_e=0x8,
    dRes_ID_TT_BAS_POSE_NR_e=0x9,
    dRes_ID_TT_BAS_STEP01_e=0xA,
    dRes_ID_TT_BAS_TALK01_e=0xB,
    dRes_ID_TT_BAS_TALK02_e=0xC,
    dRes_ID_TT_BAS_TURN_e=0xD,
    dRes_ID_TT_BAS_WAIT01_e=0xE,
    /* BCK  */
    dRes_ID_TT_BCK_POSE_CC_e=0x11,
    dRes_ID_TT_BCK_POSE_ND_e=0x12,
    dRes_ID_TT_BCK_POSE_NL_e=0x13,
    dRes_ID_TT_BCK_POSE_NR_e=0x14,
    dRes_ID_TT_BCK_STEP01_e=0x15,
    dRes_ID_TT_BCK_TALK01_e=0x16,
    dRes_ID_TT_BCK_TALK02_e=0x17,
    dRes_ID_TT_BCK_TURN_e=0x18,
    dRes_ID_TT_BCK_WAIT01_e=0x19,
    /* BDLM */
    dRes_ID_TT_BDL_TT_e=0x1C,
    /* BTP  */
    dRes_ID_TT_BTP_MABA01_e=0x1F,
};

enum TT_JNT {
    TT_JNT_WORLD_ROOT_e=0x0,
    TT_JNT_BACKBONE1_e=0x1,
    TT_JNT_NECK_e=0x2,
    TT_JNT_HEAD_e=0x3,
    TT_JNT_SHOULDERL_e=0x4,
    TT_JNT_ARML1_e=0x5,
    TT_JNT_ARML2_e=0x6,
    TT_JNT_HANDL_e=0x7,
    TT_JNT_SHOULDERR_e=0x8,
    TT_JNT_ARMR1_e=0x9,
    TT_JNT_ARMR2_e=0xA,
    TT_JNT_HANDR_e=0xB,
    TT_JNT_WAIST_e=0xC,
    TT_JNT_LEGL1_e=0xD,
    TT_JNT_LEGL2_e=0xE,
    TT_JNT_FOOTL_e=0xF,
    TT_JNT_LEGR1_e=0x10,
    TT_JNT_LEGR2_e=0x11,
    TT_JNT_FOOTR_e=0x12,
};

#endif /* !RES_TT_H */