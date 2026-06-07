#ifndef RES_KB_H
#define RES_KB_H

enum dRes_INDEX_KB {
    /* BAS  */
    dRes_INDEX_KB_BAS_EAT1_e=0x7,
    dRes_INDEX_KB_BAS_JITA1_e=0x8,
    dRes_INDEX_KB_BAS_JITA2_e=0x9,
    dRes_INDEX_KB_BAS_NAKU1_e=0xA,
    dRes_INDEX_KB_BAS_RUN1_e=0xB,
    dRes_INDEX_KB_BAS_WAIT1_e=0xC,
    dRes_INDEX_KB_BAS_WALK1_e=0xD,
    /* BCK  */
    dRes_INDEX_KB_BCK_DAMAGE1_e=0x10,
    dRes_INDEX_KB_BCK_DASSUI_e=0x11,
    dRes_INDEX_KB_BCK_EAT1_e=0x12,
    dRes_INDEX_KB_BCK_JITA1_e=0x13,
    dRes_INDEX_KB_BCK_JITA2_e=0x14,
    dRes_INDEX_KB_BCK_NAKU1_e=0x15,
    dRes_INDEX_KB_BCK_RUN1_e=0x16,
    dRes_INDEX_KB_BCK_WAIT1_e=0x17,
    dRes_INDEX_KB_BCK_WALK1_e=0x18,
    /* BDLM */
    dRes_INDEX_KB_BDL_PG_e=0x1B,
    dRes_INDEX_KB_BDL_PG_BIG_e=0x1C,
    /* BMT  */
    dRes_INDEX_KB_BMT_PG_BIG_BUTI_e=0x1F,
    dRes_INDEX_KB_BMT_PG_BIG_KURO_e=0x20,
    dRes_INDEX_KB_BMT_PG_BIG_PINK_e=0x21,
    dRes_INDEX_KB_BMT_PG_BUTI_e=0x22,
    dRes_INDEX_KB_BMT_PG_KURO_e=0x23,
    dRes_INDEX_KB_BMT_PG_PINK_e=0x24,
    /* BTP  */
    dRes_INDEX_KB_BTP_PG_BIG_EYE1_e=0x27,
    dRes_INDEX_KB_BTP_PG_BIG_EYE2_e=0x28,
    dRes_INDEX_KB_BTP_PG_EYE1_e=0x29,
    dRes_INDEX_KB_BTP_PG_EYE2_e=0x2A,
};

enum dRes_ID_KB {
    /* BAS  */
    dRes_ID_KB_BAS_EAT1_e=0x7,
    dRes_ID_KB_BAS_JITA1_e=0x8,
    dRes_ID_KB_BAS_JITA2_e=0x9,
    dRes_ID_KB_BAS_NAKU1_e=0xA,
    dRes_ID_KB_BAS_RUN1_e=0xB,
    dRes_ID_KB_BAS_WAIT1_e=0xC,
    dRes_ID_KB_BAS_WALK1_e=0xD,
    /* BCK  */
    dRes_ID_KB_BCK_DAMAGE1_e=0x10,
    dRes_ID_KB_BCK_DASSUI_e=0x11,
    dRes_ID_KB_BCK_EAT1_e=0x12,
    dRes_ID_KB_BCK_JITA1_e=0x13,
    dRes_ID_KB_BCK_JITA2_e=0x14,
    dRes_ID_KB_BCK_NAKU1_e=0x15,
    dRes_ID_KB_BCK_RUN1_e=0x16,
    dRes_ID_KB_BCK_WAIT1_e=0x17,
    dRes_ID_KB_BCK_WALK1_e=0x18,
    /* BDLM */
    dRes_ID_KB_BDL_PG_e=0x1B,
    dRes_ID_KB_BDL_PG_BIG_e=0x1C,
    /* BMT  */
    dRes_ID_KB_BMT_PG_BIG_BUTI_e=0x1F,
    dRes_ID_KB_BMT_PG_BIG_KURO_e=0x20,
    dRes_ID_KB_BMT_PG_BIG_PINK_e=0x21,
    dRes_ID_KB_BMT_PG_BUTI_e=0x22,
    dRes_ID_KB_BMT_PG_KURO_e=0x23,
    dRes_ID_KB_BMT_PG_PINK_e=0x24,
    /* BTP  */
    dRes_ID_KB_BTP_PG_BIG_EYE1_e=0x27,
    dRes_ID_KB_BTP_PG_BIG_EYE2_e=0x28,
    dRes_ID_KB_BTP_PG_EYE1_e=0x29,
    dRes_ID_KB_BTP_PG_EYE2_e=0x2A,
};

enum PG_JNT {
    PG_JNT_LOCATOR1_e=0x0,
    PG_JNT_PG_SKELROOT_e=0x1,
    PG_JNT_J_PG_HIP_e=0x2,
    PG_JNT_J_PG_FOOT_LB_e=0x3,
    PG_JNT_J_PG_FOOT_RB_e=0x4,
    PG_JNT_J_PG_SPINE_e=0x5,
    PG_JNT_J_PG_FOOT_LA_e=0x6,
    PG_JNT_J_PG_FOOT_RA_e=0x7,
    PG_JNT_J_PG_HEAD_e=0x8,
    PG_JNT_J_PG_MIMI_L_e=0x9,
    PG_JNT_J_PG_MIMI_R_e=0xA,
    PG_JNT_J_PG_NESE_e=0xB,
    PG_JNT_J_PG_TAIL_e=0xC,
};

enum PG_BIG_JNT {
    PG_BIG_JNT_LOCATOR1_e=0x0,
    PG_BIG_JNT_PG_SKELROOT_e=0x1,
    PG_BIG_JNT_J_PG_HIP_e=0x2,
    PG_BIG_JNT_J_PG_FOOT_LB_e=0x3,
    PG_BIG_JNT_J_PG_FOOT_RB_e=0x4,
    PG_BIG_JNT_J_PG_SPINE_e=0x5,
    PG_BIG_JNT_J_PG_FOOT_LA_e=0x6,
    PG_BIG_JNT_J_PG_FOOT_RA_e=0x7,
    PG_BIG_JNT_J_PG_HEAD_e=0x8,
    PG_BIG_JNT_J_PG_MIMI_L_e=0x9,
    PG_BIG_JNT_J_PG_MIMI_R_e=0xA,
    PG_BIG_JNT_J_PG_NESE_e=0xB,
    PG_BIG_JNT_J_PG_TAIL_e=0xC,
};

#endif /* !RES_KB_H */