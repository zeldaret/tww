#ifndef RES_PF_H
#define RES_PF_H

enum dRes_INDEX_PF {
    /* BCKS */
    dRes_INDEX_PF_BCK_CRY_e=0x5,
    dRes_INDEX_PF_BCK_REGRET_e=0x6,
    dRes_INDEX_PF_BCK_SPIT_e=0x7,
    dRes_INDEX_PF_BCK_TALK01_e=0x8,
    dRes_INDEX_PF_BCK_WAIT01_e=0x9,
    dRes_INDEX_PF_BCK_WALK01_e=0xA,
    dRes_INDEX_PF_BCK_WALK02_e=0xB,
    dRes_INDEX_PF_BCK_WISH_e=0xC,
    /* BDLM */
    dRes_INDEX_PF_BDL_PF_e=0xF,
    /* BTP  */
    dRes_INDEX_PF_BTP_MABA01_e=0x12,
};

enum dRes_ID_PF {
    /* BCKS */
    dRes_ID_PF_BCK_CRY_e=0x0,
    dRes_ID_PF_BCK_REGRET_e=0x1,
    dRes_ID_PF_BCK_SPIT_e=0x2,
    dRes_ID_PF_BCK_TALK01_e=0x3,
    dRes_ID_PF_BCK_WAIT01_e=0x4,
    dRes_ID_PF_BCK_WALK01_e=0x5,
    dRes_ID_PF_BCK_WALK02_e=0x6,
    dRes_ID_PF_BCK_WISH_e=0x7,
    /* BDLM */
    dRes_ID_PF_BDL_PF_e=0x8,
    /* BTP  */
    dRes_ID_PF_BTP_MABA01_e=0x9,
};

enum PF_JNT {
    PF_JNT_WORLD_ROOT_e=0x0,
    PF_JNT_BACKBONE1_e=0x1,
    PF_JNT_BACKBONE2_e=0x2,
    PF_JNT_NECK_e=0x3,
    PF_JNT_HEAD_e=0x4,
    PF_JNT_SHOULDERL_e=0x5,
    PF_JNT_ARML1_e=0x6,
    PF_JNT_ARML2_e=0x7,
    PF_JNT_HANDL_e=0x8,
    PF_JNT_SHOULDERR_e=0x9,
    PF_JNT_ARMR1_e=0xA,
    PF_JNT_ARMR2_e=0xB,
    PF_JNT_HANDR_e=0xC,
    PF_JNT_WAIST_e=0xD,
    PF_JNT_LEGL1_e=0xE,
    PF_JNT_LEGL2_e=0xF,
    PF_JNT_FOOTL_e=0x10,
    PF_JNT_LEGR1_e=0x11,
    PF_JNT_LEGR2_e=0x12,
    PF_JNT_FOOTR_e=0x13,
};

#endif /* !RES_PF_H */