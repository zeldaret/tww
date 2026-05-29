#ifndef RES_OB_H
#define RES_OB_H

enum dRes_INDEX_OB {
    /* BCKS */
    dRes_INDEX_OB_BCK_TALK_e=0x6,
    dRes_INDEX_OB_BCK_THANK_e=0x7,
    dRes_INDEX_OB_BCK_THANK02_e=0x8,
    dRes_INDEX_OB_BCK_WAIT_e=0x9,
    dRes_INDEX_OB_BCK_WALK_e=0xA,
    dRes_INDEX_OB_BCK_LAUGH_e=0xB,
    dRes_INDEX_OB_BCK_SHUTUP01_e=0xC,
    dRes_INDEX_OB_BCK_SHUTUP02_e=0xD,
    /* BDL  */
    dRes_INDEX_OB_BDL_OB_e=0x10,
    /* BDLM */
    dRes_INDEX_OB_BDL_OBA_HEAD_e=0x13,
    /* BTP  */
    dRes_INDEX_OB_BTP_MABA_A_e=0x16,
};

enum dRes_ID_OB {
    /* BCKS */
    dRes_ID_OB_BCK_TALK_e=0x0,
    dRes_ID_OB_BCK_THANK_e=0x1,
    dRes_ID_OB_BCK_THANK02_e=0x2,
    dRes_ID_OB_BCK_WAIT_e=0x3,
    dRes_ID_OB_BCK_WALK_e=0x4,
    dRes_ID_OB_BCK_LAUGH_e=0x8,
    dRes_ID_OB_BCK_SHUTUP01_e=0x9,
    dRes_ID_OB_BCK_SHUTUP02_e=0xA,
    /* BDL  */
    dRes_ID_OB_BDL_OB_e=0x5,
    /* BDLM */
    dRes_ID_OB_BDL_OBA_HEAD_e=0x6,
    /* BTP  */
    dRes_ID_OB_BTP_MABA_A_e=0x7,
};

enum OB_JNT {
    OB_JNT_WORLD_ROOT_e=0x0,
    OB_JNT_BACKBONE_e=0x1,
    OB_JNT_NECK_e=0x2,
    OB_JNT_HEAD_e=0x3,
    OB_JNT_SHOULDERL_e=0x4,
    OB_JNT_ARML1_e=0x5,
    OB_JNT_ARML2_e=0x6,
    OB_JNT_HANDL_e=0x7,
    OB_JNT_SHOULDERR_e=0x8,
    OB_JNT_ARMR1_e=0x9,
    OB_JNT_ARMR2_e=0xA,
    OB_JNT_HANDR_e=0xB,
    OB_JNT_WAIST_e=0xC,
    OB_JNT_LEGL1_e=0xD,
    OB_JNT_LEGL2_e=0xE,
    OB_JNT_FOOTL_e=0xF,
    OB_JNT_LEGR1_e=0x10,
    OB_JNT_LEGR2_e=0x11,
    OB_JNT_FOOTR_e=0x12,
};

enum OBA_HEAD_JNT {
    OBA_HEAD_JNT_HEAD_e=0x0,
};

#endif /* !RES_OB_H */