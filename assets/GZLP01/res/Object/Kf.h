#ifndef RES_KF_H
#define RES_KF_H

enum dRes_INDEX_KF {
    /* BDL  */
    dRes_INDEX_KF_BDL_KF_HAIR_e=0x6,
    /* BDLM */
    dRes_INDEX_KF_BDL_KF_e=0x9,
    /* BTP  */
    dRes_INDEX_KF_BTP_KF_e=0xC,
    dRes_INDEX_KF_BTP_CLOSE_e=0xD,
    /* BCKS */
    dRes_INDEX_KF_BCK_KF_BAKUHATU_e=0x10,
    dRes_INDEX_KF_BCK_KF_BARAMAKU_e=0x11,
    dRes_INDEX_KF_BCK_KF_OKORU_e=0x12,
    dRes_INDEX_KF_BCK_KF_TALK01_e=0x13,
    dRes_INDEX_KF_BCK_KF_TALK02_e=0x14,
    dRes_INDEX_KF_BCK_KF_TALK03_e=0x15,
    dRes_INDEX_KF_BCK_KF_TALK04_e=0x16,
    dRes_INDEX_KF_BCK_KF_WAIT01_e=0x17,
    dRes_INDEX_KF_BCK_KF_WAIT02_e=0x18,
    dRes_INDEX_KF_BCK_KF_WALK_e=0x19,
};

enum dRes_ID_KF {
    /* BDL  */
    dRes_ID_KF_BDL_KF_HAIR_e=0x0,
    /* BDLM */
    dRes_ID_KF_BDL_KF_e=0x1,
    /* BTP  */
    dRes_ID_KF_BTP_KF_e=0x2,
    dRes_ID_KF_BTP_CLOSE_e=0xD,
    /* BCKS */
    dRes_ID_KF_BCK_KF_BAKUHATU_e=0x3,
    dRes_ID_KF_BCK_KF_BARAMAKU_e=0x4,
    dRes_ID_KF_BCK_KF_OKORU_e=0x5,
    dRes_ID_KF_BCK_KF_TALK01_e=0x6,
    dRes_ID_KF_BCK_KF_TALK02_e=0x7,
    dRes_ID_KF_BCK_KF_TALK03_e=0x8,
    dRes_ID_KF_BCK_KF_TALK04_e=0x9,
    dRes_ID_KF_BCK_KF_WAIT01_e=0xA,
    dRes_ID_KF_BCK_KF_WAIT02_e=0xB,
    dRes_ID_KF_BCK_KF_WALK_e=0xC,
};

enum KF_HAIR_JNT {
    KF_HAIR_JNT_KF_HAIR_e=0x0,
};

enum KF_JNT {
    KF_JNT_CENTER_e=0x0,
    KF_JNT_BACKBONE_e=0x1,
    KF_JNT_NECK_e=0x2,
    KF_JNT_HEAD_e=0x3,
    KF_JNT_SHOULDEL_e=0x4,
    KF_JNT_ARML1_e=0x5,
    KF_JNT_ARML2_e=0x6,
    KF_JNT_HANDL_e=0x7,
    KF_JNT_SHOULDERR_e=0x8,
    KF_JNT_ARMR1_e=0x9,
    KF_JNT_ARMR2_e=0xA,
    KF_JNT_HANDR_e=0xB,
    KF_JNT_WAIST_e=0xC,
    KF_JNT_LEGL1_e=0xD,
    KF_JNT_LEGL2_e=0xE,
    KF_JNT_FOOTL_e=0xF,
    KF_JNT_LEGR1_e=0x10,
    KF_JNT_LEGR2_e=0x11,
    KF_JNT_FOOTR_e=0x12,
};

#endif /* !RES_KF_H */