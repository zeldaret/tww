#ifndef RES_MK_H
#define RES_MK_H

enum dRes_INDEX_MK {
    /* BCKS */
    dRes_INDEX_MK_BCK_MK_DA_e=0x5,
    dRes_INDEX_MK_BCK_MK_JIDA01_e=0x6,
    dRes_INDEX_MK_BCK_MK_JIDA02_e=0x7,
    dRes_INDEX_MK_BCK_MK_JUMP_e=0x8,
    dRes_INDEX_MK_BCK_MK_KEIKAI_e=0x9,
    dRes_INDEX_MK_BCK_MK_LAND_e=0xA,
    dRes_INDEX_MK_BCK_MK_RUN_e=0xB,
    dRes_INDEX_MK_BCK_MK_TALK01_e=0xC,
    dRes_INDEX_MK_BCK_MK_TALK02_e=0xD,
    dRes_INDEX_MK_BCK_MK_TIRABARE_e=0xE,
    dRes_INDEX_MK_BCK_MK_WAIT_e=0xF,
    dRes_INDEX_MK_BCK_MK_WALK_e=0x10,
    /* BDLM */
    dRes_INDEX_MK_BDL_MK_e=0x13,
    /* BTP  */
    dRes_INDEX_MK_BTP_MK_MABA_e=0x16,
};

enum dRes_ID_MK {
    /* BCKS */
    dRes_ID_MK_BCK_MK_DA_e=0x5,
    dRes_ID_MK_BCK_MK_JIDA01_e=0x6,
    dRes_ID_MK_BCK_MK_JIDA02_e=0x7,
    dRes_ID_MK_BCK_MK_JUMP_e=0x8,
    dRes_ID_MK_BCK_MK_KEIKAI_e=0x9,
    dRes_ID_MK_BCK_MK_LAND_e=0xA,
    dRes_ID_MK_BCK_MK_RUN_e=0xB,
    dRes_ID_MK_BCK_MK_TALK01_e=0xC,
    dRes_ID_MK_BCK_MK_TALK02_e=0xD,
    dRes_ID_MK_BCK_MK_TIRABARE_e=0xE,
    dRes_ID_MK_BCK_MK_WAIT_e=0xF,
    dRes_ID_MK_BCK_MK_WALK_e=0x10,
    /* BDLM */
    dRes_ID_MK_BDL_MK_e=0x13,
    /* BTP  */
    dRes_ID_MK_BTP_MK_MABA_e=0x16,
};

enum MK_JNT {
    MK_JNT_WORLD_ROOT_e=0x0,
    MK_JNT_BACKBONE_e=0x1,
    MK_JNT_NECK_e=0x2,
    MK_JNT_HEAD2_e=0x3,
    MK_JNT_HEAD_e=0x4,
    MK_JNT_SHOULDERL_e=0x5,
    MK_JNT_ARML1_e=0x6,
    MK_JNT_ARML2_e=0x7,
    MK_JNT_HANDL_e=0x8,
    MK_JNT_SHOULDERR_e=0x9,
    MK_JNT_ARMR1_e=0xA,
    MK_JNT_ARMR2_e=0xB,
    MK_JNT_HANDR_e=0xC,
    MK_JNT_WAIST_e=0xD,
    MK_JNT_LEGL1_e=0xE,
    MK_JNT_LEGL2_e=0xF,
    MK_JNT_FOOTL_e=0x10,
    MK_JNT_LEGR1_e=0x11,
    MK_JNT_LEGR2_e=0x12,
    MK_JNT_FOOTR_e=0x13,
};

#endif /* !RES_MK_H */