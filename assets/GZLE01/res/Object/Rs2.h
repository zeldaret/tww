#ifndef RES_RS2_H
#define RES_RS2_H

enum dRes_INDEX_RS2 {
    /* BCKS */
    dRes_INDEX_RS2_BCK_RS_JAMP_e=0x5,
    dRes_INDEX_RS2_BCK_RS_PUSH_e=0x6,
    dRes_INDEX_RS2_BCK_RS_SWING_e=0x7,
    dRes_INDEX_RS2_BCK_RS_TALK01_e=0x8,
    dRes_INDEX_RS2_BCK_RS_TALK02_e=0x9,
    dRes_INDEX_RS2_BCK_RS_TALK03_e=0xA,
    dRes_INDEX_RS2_BCK_RS_TAME_e=0xB,
    dRes_INDEX_RS2_BCK_RS_WAIT01_e=0xC,
    dRes_INDEX_RS2_BCK_RS_WAIT02_e=0xD,
    dRes_INDEX_RS2_BCK_RS_WALK_e=0xE,
    /* BDLM */
    dRes_INDEX_RS2_BDL_RS_e=0x11,
    /* BTP  */
    dRes_INDEX_RS2_BTP_RS_MABA01_e=0x14,
};

enum dRes_ID_RS2 {
    /* BCKS */
    dRes_ID_RS2_BCK_RS_JAMP_e=0x0,
    dRes_ID_RS2_BCK_RS_PUSH_e=0x1,
    dRes_ID_RS2_BCK_RS_SWING_e=0x2,
    dRes_ID_RS2_BCK_RS_TALK01_e=0x3,
    dRes_ID_RS2_BCK_RS_TALK02_e=0x4,
    dRes_ID_RS2_BCK_RS_TALK03_e=0x5,
    dRes_ID_RS2_BCK_RS_TAME_e=0x6,
    dRes_ID_RS2_BCK_RS_WAIT01_e=0x7,
    dRes_ID_RS2_BCK_RS_WAIT02_e=0x8,
    dRes_ID_RS2_BCK_RS_WALK_e=0x9,
    /* BDLM */
    dRes_ID_RS2_BDL_RS_e=0xA,
    /* BTP  */
    dRes_ID_RS2_BTP_RS_MABA01_e=0xB,
};

enum RS_JNT {
    RS_JNT_WORLD_ROOT_e=0x0,
    RS_JNT_BACKBONE_e=0x1,
    RS_JNT_HEAD_e=0x2,
    RS_JNT_RIDDON_e=0x3,
    RS_JNT_HOOD1_e=0x4,
    RS_JNT_HOOD2_e=0x5,
    RS_JNT_SHOULDERL_e=0x6,
    RS_JNT_ARML1_e=0x7,
    RS_JNT_ARML2_e=0x8,
    RS_JNT_ARML3_e=0x9,
    RS_JNT_HANDL_e=0xA,
    RS_JNT_SHOULDERR_e=0xB,
    RS_JNT_ARMR1_e=0xC,
    RS_JNT_ARMR2_e=0xD,
    RS_JNT_ARMR3_e=0xE,
    RS_JNT_HANDR_e=0xF,
    RS_JNT_WAIST_e=0x10,
    RS_JNT_LEGL1_e=0x11,
    RS_JNT_LEGL2_e=0x12,
    RS_JNT_FOOTL_e=0x13,
    RS_JNT_LEGR1_e=0x14,
    RS_JNT_LEGR2_e=0x15,
    RS_JNT_FOOTR_e=0x16,
};

#endif /* !RES_RS2_H */