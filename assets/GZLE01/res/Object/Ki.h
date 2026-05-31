#ifndef RES_KI_H
#define RES_KI_H

enum dRes_INDEX_KI {
    /* BAS  */
    dRes_INDEX_KI_BAS_ATTACK1_e=0x7,
    dRes_INDEX_KI_BAS_BITA1_e=0x8,
    dRes_INDEX_KI_BAS_DAMAGE1_e=0x9,
    dRes_INDEX_KI_BAS_FLY1_e=0xA,
    dRes_INDEX_KI_BAS_FLY2_e=0xB,
    dRes_INDEX_KI_BAS_WAIT1_e=0xC,
    /* BCK  */
    dRes_INDEX_KI_BCK_ATTACK1_e=0xF,
    dRes_INDEX_KI_BCK_BITA1_e=0x10,
    dRes_INDEX_KI_BCK_DAMAGE1_e=0x11,
    dRes_INDEX_KI_BCK_FLY1_e=0x12,
    dRes_INDEX_KI_BCK_FLY2_e=0x13,
    dRes_INDEX_KI_BCK_WAIT1_e=0x14,
    /* BDLM */
    dRes_INDEX_KI_BDL_FK_e=0x17,
    dRes_INDEX_KI_BDL_KI_e=0x18,
    /* BTK  */
    dRes_INDEX_KI_BTK_FK_e=0x1B,
    /* BTP  */
    dRes_INDEX_KI_BTP_AKE1_e=0x1E,
    dRes_INDEX_KI_BTP_GURU1_e=0x1F,
    dRes_INDEX_KI_BTP_METOJI1_e=0x20,
    dRes_INDEX_KI_BTP_TOJI1_e=0x21,
};

enum dRes_ID_KI {
    /* BAS  */
    dRes_ID_KI_BAS_ATTACK1_e=0x7,
    dRes_ID_KI_BAS_BITA1_e=0x8,
    dRes_ID_KI_BAS_DAMAGE1_e=0x9,
    dRes_ID_KI_BAS_FLY1_e=0xA,
    dRes_ID_KI_BAS_FLY2_e=0xB,
    dRes_ID_KI_BAS_WAIT1_e=0xC,
    /* BCK  */
    dRes_ID_KI_BCK_ATTACK1_e=0xF,
    dRes_ID_KI_BCK_BITA1_e=0x10,
    dRes_ID_KI_BCK_DAMAGE1_e=0x11,
    dRes_ID_KI_BCK_FLY1_e=0x12,
    dRes_ID_KI_BCK_FLY2_e=0x13,
    dRes_ID_KI_BCK_WAIT1_e=0x14,
    /* BDLM */
    dRes_ID_KI_BDL_FK_e=0x17,
    dRes_ID_KI_BDL_KI_e=0x18,
    /* BTK  */
    dRes_ID_KI_BTK_FK_e=0x1B,
    /* BTP  */
    dRes_ID_KI_BTP_AKE1_e=0x1E,
    dRes_ID_KI_BTP_GURU1_e=0x1F,
    dRes_ID_KI_BTP_METOJI1_e=0x20,
    dRes_ID_KI_BTP_TOJI1_e=0x21,
};

enum FK_JNT {
    FK_JNT_KI_ALLROOT_e=0x0,
    FK_JNT_J_KI_SPINE_e=0x1,
    FK_JNT_J_KI_ARM_L1_e=0x2,
    FK_JNT_J_KI_ARM_L2_e=0x3,
    FK_JNT_J_KI_ARM_LE_e=0x4,
    FK_JNT_J_KI_FINGER1_L_e=0x5,
    FK_JNT_J_KI_FINGER2_L_e=0x6,
    FK_JNT_J_KI_ARM_R1_e=0x7,
    FK_JNT_J_KI_ARM_R2_e=0x8,
    FK_JNT_J_KI_ARM_RE_e=0x9,
    FK_JNT_J_KI_FINGER1_R_e=0xA,
    FK_JNT_J_KI_FINGER2_R_e=0xB,
    FK_JNT_J_KI_FOOT_L_e=0xC,
    FK_JNT_J_KI_FOOT_R_e=0xD,
    FK_JNT_J_KI_HEAD_e=0xE,
    FK_JNT_J_KI_JAW_e=0xF,
};

enum KI_JNT {
    KI_JNT_KI_ALLROOT_e=0x0,
    KI_JNT_J_KI_SPINE_e=0x1,
    KI_JNT_J_KI_ARM_L1_e=0x2,
    KI_JNT_J_KI_ARM_L2_e=0x3,
    KI_JNT_J_KI_ARM_LE_e=0x4,
    KI_JNT_J_KI_FINGER1_L_e=0x5,
    KI_JNT_J_KI_FINGER2_L_e=0x6,
    KI_JNT_J_KI_ARM_R1_e=0x7,
    KI_JNT_J_KI_ARM_R2_e=0x8,
    KI_JNT_J_KI_ARM_RE_e=0x9,
    KI_JNT_J_KI_FINGER1_R_e=0xA,
    KI_JNT_J_KI_FINGER2_R_e=0xB,
    KI_JNT_J_KI_FOOT_L_e=0xC,
    KI_JNT_J_KI_FOOT_R_e=0xD,
    KI_JNT_J_KI_HEAD_e=0xE,
    KI_JNT_J_KI_JAW_e=0xF,
};

#endif /* !RES_KI_H */